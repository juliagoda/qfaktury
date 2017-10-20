#include "MainWindow.h"
#include "Bill.h"
#include "Buyers.h"
#include "Const.h"
#include "CorrectGross.h"
#include "DateWidgetItem.h"
#include "DeliveryNote.h"
#include "Duplicate.h"
#include "Goods.h"
#include "GoodsIssuedNotes.h"
#include "Invoice.h"
#include "InvoiceGross.h"
#include "InvoiceRR.h"
#include "OwnCalendar.h"
#include "Send.h"
#include "Setting.h"
#include "User.h"
#include "XmlDataLayer.h"

#include "JlCompress.h"
#include "quazipdir.h"

#include <QDesktopServices>
#include <QDesktopWidget>
#include <QFileDialog>
#include <QInputDialog>
#include <QPdfWriter>
#include <QPrintPreviewDialog>
#include <QPrinter>
#include <QProcess>
#include <QTimer>

MainWindow *MainWindow::m_instance = nullptr;
bool MainWindow::shouldHidden = false;

/** Constructor
 */

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  ui->setupUi(this);
  m_instance = this;
  init();
}

MainWindow *MainWindow::instance() {
  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;
  return m_instance;
}

/** Destructor
 */

MainWindow::~MainWindow() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  saveAllSett();

  if (timer != 0)
    timer = 0;
  delete timer;

  if (dl != 0)
    dl = 0;
  delete dl;

  if (ui != 0)
    ui = 0;
  delete ui;

  m_instance = nullptr;

  if (plugActions.count() > 0) {

    foreach (QAction *plugAct_single, plugActions) {

      if (plugAct_single != 0)
        plugAct_single = 0;
      delete plugAct_single;
    }
  }
}

/**
 * init() method
 */

void MainWindow::init() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  // first run
  if (firstRun()) {

    // towary/uslugi - wymiary
    ui->tableT->setColumnWidth(0, 50);
    ui->tableT->setColumnWidth(1, 140);
    ui->tableT->setColumnWidth(3, 50);
    ui->tableT->setColumnWidth(4, 70);
    ui->tableT->setColumnWidth(5, 70);
    ui->tableT->setColumnWidth(6, 65); // netto1
    ui->tableT->setColumnWidth(7, 65); // netto2
    ui->tableT->setColumnWidth(8, 65); // netto3
    ui->tableT->setColumnWidth(9, 65); // netto4
    ui->tableT->setColumnWidth(10, 65);

    saveAllSettAsDefault();

    QMessageBox::information(
        this, "QFaktury",
        trUtf8("Program zawiera konwersję walut w oknie edycji faktury lub "
               "podczas jej tworzenia. By jej używać, powinieneś mieć dostęp "
               "do internetu oraz poprawnie ustawiony czas systemowy."));
    QMessageBox::information(
        this, "QFaktury",
        trUtf8("W przypadku zmiany lokalizacji systemu, sposób formatowania "
               "liczb może się zmienić. Efekt ten może być widoczny po "
               "restarcie programu."));

    if (QMessageBox::information(
            this, "QFaktury",
            trUtf8("Czy chcesz skonfigurować firmę? Opcja ta "
                   "przy starcie programu będzie widoczna "
                   "tylko przy pierwszym uruchomieniu."),
            trUtf8("Tak"), trUtf8("Nie"), 0, 0, 1) == 0) {
      userDataClick();
    }

  } else {

    ui->filtrStart->setDisplayFormat(sett().getDateFormat());
    ui->filtrStart->setDate(sett().getValueAsDate("filtrStart"));
    ui->filtrEnd->setDisplayFormat(sett().getDateFormat());
    ui->filtrEnd->setDate(sett().getValueAsDate("filtrEnd"));

    ui->warehouseFromDate->setDisplayFormat(sett().getDateFormat());
    ui->warehouseFromDate->setDate(
        sett().getValueAsDate("filtrStartWarehouse"));
    ui->warehouseToDate->setDisplayFormat(sett().getDateFormat());
    ui->warehouseToDate->setDate(sett().getValueAsDate("filtrEndWarehouse"));
  }

  setupDir();

  if (!ifEmergTemplateExists())
    createEmergTemplate();

  if (ui->tableH->rowCount() != 0) {

    ui->invoiceEdAction->setEnabled(true);
    ui->invoiceDelAction->setEnabled(true);

    if (ui->tableK->rowCount() != 0)
      ui->sendEmailAction->setEnabled(true);
    else
      ui->sendEmailAction->setDisabled(true);

  } else {

    ui->invoiceEdAction->setDisabled(true);
    ui->invoiceDelAction->setDisabled(true);
    ui->sendEmailAction->setDisabled(true);
  }

  if (ui->tableK->rowCount() != 0) {

    ui->editBuyersAction->setEnabled(true);
    ui->delBuyersAction->setEnabled(true);
    ui->actionPrintBuyer->setEnabled(true);

    if (ui->tableH->rowCount() != 0) {
      ui->sendEmailAction->setEnabled(true);
    } else {
      ui->sendEmailAction->setDisabled(true);
    }

  } else {

    ui->editBuyersAction->setDisabled(true);
    ui->delBuyersAction->setDisabled(true);
    ui->actionPrintBuyer->setDisabled(true);
    ui->sendEmailAction->setDisabled(true);
  }

  if (ui->tableT->rowCount() != 0) {

    ui->editGoodsAction->setEnabled(true);
    ui->delGoodsAction->setEnabled(true);

  } else {

    ui->editGoodsAction->setDisabled(true);
    ui->delGoodsAction->setDisabled(true);
  }

  // choose data access mode
  dl = new XmlDataLayer();

  // towary/uslugi - wymiary
  ui->tableT->setColumnWidth(0, sett().value("towCol0", QVariant(50)).toInt());
  ui->tableT->setColumnWidth(1, sett().value("towCol1", QVariant(140)).toInt());
  ui->tableT->setColumnWidth(3, sett().value("towCol2", QVariant(50)).toInt());
  ui->tableT->setColumnWidth(4, sett().value("towCol3", QVariant(70)).toInt());
  ui->tableT->setColumnWidth(5, sett().value("towCol4", QVariant(70)).toInt());
  ui->tableT->setColumnWidth(
      6, sett().value("towCol5", QVariant(65)).toInt()); // net1
  ui->tableT->setColumnWidth(
      7, sett().value("towCol6", QVariant(65)).toInt()); // net2
  ui->tableT->setColumnWidth(
      8, sett().value("towCol7", QVariant(65)).toInt()); // net3
  ui->tableT->setColumnWidth(9, sett().value("towCol8", QVariant(65)).toInt());
  ; // net4
  ui->tableT->setColumnWidth(10, sett().value("towCol9", QVariant(65)).toInt());

  ui->tableH->setColumnWidth(0, sett().value("histCol0", QVariant(0)).toInt());
  ui->tableH->setColumnWidth(1,
                             sett().value("histCol1", QVariant(120)).toInt());
  ui->tableH->setColumnWidth(3,
                             sett().value("histCol2", QVariant(120)).toInt());
  ui->tableH->setColumnWidth(4,
                             sett().value("histCol3", QVariant(140)).toInt());
  ui->tableH->setColumnWidth(5,
                             sett().value("histCol4", QVariant(120)).toInt());
  ui->tableM->setColumnWidth(0, sett().value("wareCol0", QVariant(0)).toInt());
  ui->tableM->setColumnWidth(1,
                             sett().value("wareCol1", QVariant(120)).toInt());
  ui->tableM->setColumnWidth(3,
                             sett().value("wareCol2", QVariant(120)).toInt());
  ui->tableM->setColumnWidth(4,
                             sett().value("wareCol3", QVariant(140)).toInt());
  ui->tableM->setColumnWidth(5,
                             sett().value("wareCol4", QVariant(120)).toInt());

  ui->tableK->setColumnWidth(0,
                             sett().value("custCol0", QVariant(140)).toInt());
  ui->tableK->setColumnWidth(1,
                             sett().value("custCol1", QVariant(140)).toInt());
  ui->tableK->setColumnWidth(2,
                             sett().value("custCol2", QVariant(100)).toInt());
  ui->tableK->setColumnWidth(3,
                             sett().value("custCol3", QVariant(120)).toInt());
  ui->tableK->setColumnWidth(4,
                             sett().value("custCol4", QVariant(140)).toInt());
  ui->tableK->setColumnWidth(5,
                             sett().value("custCol5", QVariant(170)).toInt());
  ui->tableK->setColumnWidth(6,
                             sett().value("custCol6", QVariant(170)).toInt());

  // add Icon
  QIcon icon;
  icon.addPixmap(QPixmap(":/res/icons/qfaktury_48.png"), QIcon::Normal,
                 QIcon::Off);
  this->setWindowIcon(icon);
  this->setWindowTitle(sett().getVersion(qAppName()));

  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(tabChanged()));
  timer->start(1000);

  qDebug() << "application path: "
           << QStandardPaths::standardLocations(QStandardPaths::AppDataLocation)
                  .at(1);

  calendar = new ownCalendarWidget;
  ui->calendarLayout->addWidget(calendar);

  // connect slots
  connect(ui->actionBug, &QAction::triggered, [this]() {
    QDesktopServices::openUrl(
        QUrl("https://github.com/juliagoda/qfaktury/issues"));
  });

  connect(ui->applyFiltrBtn, SIGNAL(clicked(bool)), this,
          SLOT(rereadHist(bool)));
  connect(ui->findWarehouses, SIGNAL(clicked(bool)), this,
          SLOT(rereadWarehouses(bool)));
  connect(ui->fileData_companyAction, SIGNAL(triggered()), this,
          SLOT(userDataClick()));
  connect(ui->fileEndAction, SIGNAL(triggered()), this, SLOT(close()));
  connect(ui->addBuyersAction, SIGNAL(triggered()), this, SLOT(buyerClick()));
  connect(ui->delBuyersAction, SIGNAL(triggered()), this, SLOT(buyerDel()));
  connect(ui->editBuyersAction, SIGNAL(triggered()), this, SLOT(buyerEd()));
  connect(ui->addInvoiceAction, SIGNAL(triggered()), this, SLOT(newInv()));
  connect(ui->invoiceDelAction, SIGNAL(triggered()), this, SLOT(delFHist()));
  connect(ui->warehouseDelAction, SIGNAL(triggered()), this, SLOT(delMHist()));
  connect(ui->invoiceEdAction, SIGNAL(triggered()), this, SLOT(editFHist()));
  connect(ui->warehouseEdAction, SIGNAL(triggered()), this,
          SLOT(warehouseEdit()));
  connect(ui->invoiceDuplAction, SIGNAL(triggered()), this,
          SLOT(newDuplicate()));
  connect(ui->invoiceGrossAction, SIGNAL(triggered()), this,
          SLOT(newInvGross()));
  connect(ui->invoiceBillAction, SIGNAL(triggered()), this, SLOT(newInvBill()));
  connect(ui->invoiceCorrAction, SIGNAL(triggered()), this, SLOT(newCor()));
  connect(ui->invoiceRRAction, SIGNAL(triggered()), this, SLOT(newInvRR()));
  connect(ui->invoiceProFormaAction, SIGNAL(triggered()), this,
          SLOT(newPForm()));
  connect(ui->addGoodsAction, SIGNAL(triggered()), this, SLOT(goodsAdd()));
  connect(ui->actionPrintBuyer, SIGNAL(triggered()), this,
          SLOT(printBuyerList()));
  connect(ui->editGoodsAction, SIGNAL(triggered()), this, SLOT(goodsEdit()));
  connect(ui->delGoodsAction, SIGNAL(triggered()), this, SLOT(goodsDel()));

  /** Slot used to display aboutQt informations.
   */

  connect(ui->action_Qt, &QAction::triggered, [this]() {
    QMessageBox::aboutQt(this, sett().getVersion(qAppName()));
  });

  connect(ui->helpAbout_appAction, SIGNAL(triggered()), this,
          SLOT(aboutProg()));
  connect(ui->fileSettingsAction, SIGNAL(triggered()), this, SLOT(settClick()));

  /** Slot help
   */

  connect(ui->helpAction, &QAction::triggered, [this]() {
    QDesktopServices::openUrl(QUrl("https://github.com/juliagoda/qfaktury"));
  });

  connect(ui->actionCreateBackup, SIGNAL(triggered()), this,
          SLOT(createFirstWinBackup()));
  connect(ui->actionLoadBackup, SIGNAL(triggered()), this, SLOT(loadBackup()));
  connect(ui->hideOrganizer, SIGNAL(clicked(bool)), this,
          SLOT(openHideOrganizer()));
  connect(calendar, SIGNAL(activated(const QDate &)), this,
          SLOT(noteDownTask(const QDate &)));
  connect(ui->tableH, SIGNAL(cellDoubleClicked(int, int)), this,
          SLOT(editFHist()));
  connect(ui->tableH, SIGNAL(customContextMenuRequested(QPoint)), this,
          SLOT(showTableMenuH(QPoint)));
  connect(ui->tableK, SIGNAL(cellDoubleClicked(int, int)), this,
          SLOT(buyerEd()));
  connect(ui->tableK, SIGNAL(customContextMenuRequested(QPoint)), this,
          SLOT(showTableMenuK(QPoint)));
  connect(ui->tableM, SIGNAL(customContextMenuRequested(QPoint)), this,
          SLOT(showTableMenuM(QPoint)));
  connect(ui->tableM, SIGNAL(cellDoubleClicked(int, int)), this,
          SLOT(warehouseEdit()));
  connect(ui->tableT, SIGNAL(cellDoubleClicked(int, int)), this,
          SLOT(goodsEdit()));
  connect(ui->tableT, SIGNAL(customContextMenuRequested(QPoint)), this,
          SLOT(showTableMenuT(QPoint)));
  connect(ui->sendEmailAction, SIGNAL(triggered()), this,
          SLOT(sendEmailToBuyer()));

  connect(ui->tableH, SIGNAL(itemClicked(QTableWidgetItem *)), this,
          SLOT(mainUpdateStatus(QTableWidgetItem *)));
  connect(ui->tableK, SIGNAL(itemClicked(QTableWidgetItem *)), this,
          SLOT(mainUpdateStatus(QTableWidgetItem *)));
  connect(ui->tableT, SIGNAL(itemClicked(QTableWidgetItem *)), this,
          SLOT(mainUpdateStatus(QTableWidgetItem *)));
  connect(ui->tableM, SIGNAL(itemClicked(QTableWidgetItem *)), this,
          SLOT(mainUpdateStatus(QTableWidgetItem *)));
  connect(ui->tableK, SIGNAL(cellClicked(int, int)), this,
          SLOT(openWebTableK(int, int)));

  readBuyer();
  readHist();
  readWarehouses();
  readGoods();
  categorizeYears();
  checkTodayTask();
  loadPlugins();

  if (!ifpdfDirExists()) {

    createPdfDir();

  } else {

    QDir _dir(sett().getPdfDir());
    _dir.setFilter(QDir::Files);
    QStringList filters;
    filters << "*.pdf";

    _dir.setNameFilters(filters);
    QStringList files = _dir.entryList();

    if (files.isEmpty())
      generatePdfFromList();
  }
}

bool MainWindow::ifpdfDirExists() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  QDir mainPath(sett().getPdfDir());

  if (!mainPath.exists()) {

    return false;
  } else {

    return true;
  }
}

void MainWindow::createPdfDir() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  QDir mainPath;
  mainPath.mkpath(sett().getPdfDir());
  generatePdfFromList();
}

void MainWindow::generatePdfFromList() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  shouldHidden = true;

  for (int i = 0; i < ui->tableH->rowCount(); i++) {
    ui->tableH->setCurrentCell(i, 0);
    editFHist();
  }

  for (int i = 0; i < ui->tableM->rowCount(); i++) {
    ui->tableM->setCurrentCell(i, 0);
    warehouseEdit();
  }

  shouldHidden = false;
}

bool MainWindow::ifEmergTemplateExists() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  QFileInfo fileInfo(sett().getEmergTemplate());

  if (fileInfo.exists() && fileInfo.isFile())
    return true;
  else
    return false;
}

void MainWindow::createEmergTemplate() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  QDir mainPath(QDir::homePath() + "/.local/share/data/elinux/template");

  if (!mainPath.exists()) {

    mainPath.mkpath(QDir::homePath() + "/.local/share/data/elinux/template");
  }

  QFile file(sett().getEmergTemplate());

  if (file.open(QIODevice::WriteOnly)) {

    QTextStream stream(&file);

    QStringList::const_iterator constIterator;
    for (constIterator = blackEmergTemplate.constBegin();
         constIterator != blackEmergTemplate.constEnd(); ++constIterator)
      stream << (*constIterator).toLocal8Bit().constData() << endl;

    file.close();
  }
}

/**
 *  Loads PyQt plugins
 */

void MainWindow::loadPlugins() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  QDir allFiles;
  QString path = QString();
  path = sett().getAppDirs() + "plugins/";
  allFiles.setPath(path);
  allFiles.setFilter(QDir::Files);
  QStringList filters = QStringList() << "*.py"
                                      << "*.Py"
                                      << "*.PY"
                                      << "*.pY";
  allFiles.setNameFilters(filters);
  QStringList files = allFiles.entryList();

  if (!files.isEmpty()) {

    int i = 0;

    QStringList::const_iterator constIterator;

    for (constIterator = files.constBegin(); constIterator != files.constEnd();
         ++constIterator) {

      QFile script(path + QString((*constIterator).toLocal8Bit().constData()));

      if (!script.open(QIODevice::ReadOnly)) {

        QFile(script.fileName()).setPermissions(QFileDevice::ReadOwner);
      }

      QTextStream t(&script);
      t.readLine();
      QAction *action = new QAction(t.readLine().remove("# "), this);
      plugActions.append(action);
      action->setData(QVariant(i));
      connect(action, SIGNAL(triggered()), this, SLOT(pluginSlot()));
      ui->menuPlugins->addAction(action);
      customActions[i] =
          path + QString((*constIterator).toLocal8Bit().constData());

      ++i;
    }
  }

  ui->menuPlugins->addSeparator();
  ui->menuPlugins->addAction(trUtf8("Informacje"), this, SLOT(pluginInfoSlot()))
      ->setIcon(QIcon(":/res/icons/informacja_dodatki.png"));
}

/**
 * firstRun setup()
 */

bool MainWindow::firstRun() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  bool ok = sett().value("firstrun", true).toBool();

  ui->filtrStart->setDate(QDate(QDate::currentDate().year(), 1, 1));
  ui->filtrEnd->setDate(QDate(QDate::currentDate().year(), 12, 31));

  ui->warehouseFromDate->setDate(QDate(QDate::currentDate().year(), 1, 1));
  ui->warehouseToDate->setDate(QDate(QDate::currentDate().year(), 12, 31));

  sett().checkSettings();

  return ok;
}

/**
 * categorizing files according to the years and putting them to separated
 * folders
 */

void MainWindow::categorizeYears() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  if (dl->ifThereOldInvoice())
    dl->separateOldInvoices();
}

void MainWindow::checkTodayTask(QString whatToDo) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  QString today = QDate::currentDate().toString();
  qDebug() << "TODAY IS " << today;

  QString planDir =
      QDir::homePath() + "/.local/share/data/elinux/plans/" + today + ".txt";

  QFile filename(planDir);

  QTextStream in(&filename);

  ui->todayExercise->setStyleSheet("QTextEdit"
                                   "{padding-left: 10px;"
                                   "padding-right: 10px;"
                                   "padding-top: 30px;"
                                   "padding-bottom: 30px;"
                                   "background-color: white;}");

  ui->todayExercise->clear();

  if (whatToDo != "remove") {

    if (filename.exists()) {

      if (!filename.open(QIODevice::ReadOnly | QIODevice::Text)) {

        QFileInfo check_file(filename.fileName());

        if (check_file.exists() && check_file.isFile()) {

          QFile(filename.fileName())
              .setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner);
        }
      }

      while (!in.atEnd()) {

        QString line = in.readLine();

        if (line.isNull()) {
          ui->todayExercise->append("<br>");
        }

        calendarNoteJustify(line);
      }

      ui->todayExercise->setStyleSheet("QTextEdit"
                                       "{padding-left: 10px;"
                                       "padding-right: 10px;"
                                       "padding-top: 30px;"
                                       "padding-bottom: 30px;"
                                       "background-color: white;"
                                       "color: #e51919;"
                                       "font-weight: bold;}");

      filename.close();

    } else {

      calendarNoteJustify(trUtf8("Dziś nie masz nic do zrobienia"));
    }

  } else {

    calendarNoteJustify(trUtf8("Dziś nie masz nic do zrobienia"));
  }
}

void MainWindow::openWebTableK(int row, int column) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  if (column == 6) {
    if ((!ui->tableK->item(row, column)->text().isEmpty()) &&
        (ui->tableK->item(row, column)->text() != "-")) {
      QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
      QDesktopServices::openUrl(
          QUrl(ui->tableK->item(row, column)->text(), QUrl::TolerantMode));
      QApplication::restoreOverrideCursor();
    }
  }
}

/** save sett() before quit
 * save column width
 */

void MainWindow::saveColumnWidth() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  // width of the columns in the towary "goods" tab
  sett().setValue("towCol0", ui->tableT->columnWidth(0));
  sett().setValue("towCol1", ui->tableT->columnWidth(1));
  sett().setValue("towCol2", ui->tableT->columnWidth(2));
  sett().setValue("towCol3", ui->tableT->columnWidth(3));
  sett().setValue("towCol4", ui->tableT->columnWidth(4));
  sett().setValue("towCol5", ui->tableT->columnWidth(5));
  sett().setValue("towCol6", ui->tableT->columnWidth(6));
  sett().setValue("towCol7", ui->tableT->columnWidth(7));
  sett().setValue("towCol8", ui->tableT->columnWidth(8));
  sett().setValue("towCol9", ui->tableT->columnWidth(9));
  sett().setValue("towCol10", ui->tableT->columnWidth(10));

  // width of the columns in the history tab
  sett().setValue("histCol0", ui->tableH->columnWidth(0));
  sett().setValue("histCol1", ui->tableH->columnWidth(1));
  sett().setValue("histCol2", ui->tableH->columnWidth(2));
  sett().setValue("histCol3", ui->tableH->columnWidth(3));
  sett().setValue("histCol4", ui->tableH->columnWidth(4));
  sett().setValue("histCol5", ui->tableH->columnWidth(5));

  // width of the columns in the customers tab
  sett().setValue("custCol0", ui->tableK->columnWidth(0));
  sett().setValue("custCol1", ui->tableK->columnWidth(1));
  sett().setValue("custCol2", ui->tableK->columnWidth(2));
  sett().setValue("custCol3", ui->tableK->columnWidth(3));
  sett().setValue("custCol4", ui->tableK->columnWidth(4));
  sett().setValue("custCol5", ui->tableK->columnWidth(5));
  sett().setValue("custCol6", ui->tableK->columnWidth(6));

  sett().setValue("wareCol0", ui->tableM->columnWidth(0));
  sett().setValue("wareCol1", ui->tableM->columnWidth(1));
  sett().setValue("wareCol2", ui->tableM->columnWidth(2));
  sett().setValue("wareCol3", ui->tableM->columnWidth(3));
  sett().setValue("wareCol4", ui->tableM->columnWidth(4));
  sett().setValue("wareCol5", ui->tableM->columnWidth(5));
}

/** Saves all sett() as default - first run
 */

void MainWindow::saveAllSettAsDefault() {
  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;
  sett().resetSettings();
}

/** Saves all sett()
 */

void MainWindow::saveAllSett() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  // saves filtr
  sett().setValue("filtrStart", ui->filtrStart->text());
  sett().setValue("filtrEnd", ui->filtrEnd->text());

  sett().setValue("filtrStartWarehouse", ui->warehouseFromDate->text());
  sett().setValue("filtrEndWarehouse", ui->warehouseToDate->text());

  saveColumnWidth();

  // saves unsaved
  sett().sync();
}

/** Clears content of the QTableWidget passed in the input
 *  @param QTableWidget
 */

void MainWindow::tableClear(QTableWidget *tab) {
  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;
  tab->setRowCount(0);
}

/** Used while adding new row
 */

void MainWindow::insertRow(QTableWidget *t, int row) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  t->insertRow(row);

  for (int i = 0; i < t->columnCount(); i++) {

    t->setItem(row, i, new QTableWidgetItem());
  }
}

int MainWindow::getMaxSymbol() const {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  int max = *std::max_element(allSymbols.begin(), allSymbols.end());
  return max;
}

int MainWindow::getMaxSymbolWarehouse() const {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  int max =
      *std::max_element(allSymbolsWarehouse.begin(), allSymbolsWarehouse.end());
  return max;
}

/** Reads the invoices from the directory passed in the input.
 *  @param QString - directory from where the invoices should be read
 */

void MainWindow::readHist() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  QVector<InvoiceData> invoicesVec;
  invoicesVec =
      dl->invoiceSelectAllData(ui->filtrStart->date(), ui->filtrEnd->date());
  allSymbols = dl->getAllSymbols();
  ui->tableH->setSortingEnabled(false);

  for (int i = 0; i < invoicesVec.size(); ++i) {

    insertRow(ui->tableH, ui->tableH->rowCount());
    QString text = invoicesVec.at(i).id;
    ui->tableH->item(ui->tableH->rowCount() - 1, 0)->setText(text);
    qDebug("Added ID of file");
    text = invoicesVec.at(i).invNr;
    ui->tableH->item(ui->tableH->rowCount() - 1, 1)->setText(text);
    qDebug("Added file name");
    ui->tableH->setItem(ui->tableH->rowCount() - 1, 2,
                        new DateWidgetItem(invoicesVec.at(i).sellingDate));
    qDebug("Added file date");
    text = invoicesVec.at(i).type;
    ui->tableH->item(ui->tableH->rowCount() - 1, 3)->setText(text);
    qDebug("Added file type");
    text = invoicesVec.at(i).custName;
    ui->tableH->item(ui->tableH->rowCount() - 1, 4)->setText(text);
    qDebug("Added buyer's name");
    text = invoicesVec.at(i).custTic;
    ui->tableH->item(ui->tableH->rowCount() - 1, 5)->setText(text);
    qDebug("Added file NIP");
  }

  ui->tableH->setSortingEnabled(true);
}

/** Reads the invoices from the directory passed in the input.
 *  @param QString - directory from where the invoices should be read
 */

void MainWindow::readWarehouses() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  QVector<WarehouseData> wareVec;
  wareVec = dl->warehouseSelectAllData(ui->warehouseFromDate->date(),
                                       ui->warehouseToDate->date());
  allSymbolsWarehouse = dl->getAllSymbolsWarehouse();
  ui->tableM->setSortingEnabled(false);

  for (int i = 0; i < wareVec.size(); ++i) {

    insertRow(ui->tableM, ui->tableM->rowCount());
    QString text = wareVec.at(i).id;
    ui->tableM->item(ui->tableM->rowCount() - 1, 0)->setText(text);
    qDebug("Added ID of file");
    text = wareVec.at(i).invNr;
    ui->tableM->item(ui->tableM->rowCount() - 1, 1)->setText(text);
    qDebug("Added file name");
    ui->tableM->setItem(ui->tableM->rowCount() - 1, 2,
                        new DateWidgetItem(wareVec.at(i).sellingDate));
    qDebug("Added file date");
    text = wareVec.at(i).type;
    ui->tableM->item(ui->tableM->rowCount() - 1, 3)->setText(text);
    qDebug("Added file type");
    text = wareVec.at(i).custName;
    ui->tableM->item(ui->tableM->rowCount() - 1, 4)->setText(text);
    qDebug("Added buyer's name");
    text = wareVec.at(i).custTic;
    ui->tableM->item(ui->tableM->rowCount() - 1, 5)->setText(text);
    qDebug("Added file NIP");
  }

  ui->tableM->setSortingEnabled(true);
}

/** Reads customers from the XML
 */

void MainWindow::readBuyer() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  tableClear(ui->tableK);
  ui->tableK->setSortingEnabled(false);
  QVector<BuyerData> buyerVec = dl->buyersSelectAllData();

  for (int i = 0; i < buyerVec.size(); ++i) {

    qDebug() << "liczba kolumn: " << ui->tableK->columnCount();
    insertRow(ui->tableK, ui->tableK->rowCount());
    QString text = buyerVec.at(i).name;
    ui->tableK->item(ui->tableK->rowCount() - 1, 0)->setText(text);
    text = buyerVec.at(i).type;
    ui->tableK->item(ui->tableK->rowCount() - 1, 1)->setText(text);
    text = buyerVec.at(i).place;
    ui->tableK->item(ui->tableK->rowCount() - 1, 2)->setText(text);
    text = buyerVec.at(i).address;
    ui->tableK->item(ui->tableK->rowCount() - 1, 3)->setText(text);
    text = buyerVec.at(i).phone;
    ui->tableK->item(ui->tableK->rowCount() - 1, 4)->setText(text);
    text = buyerVec.at(i).email;
    qDebug() << "liczba kolumn: " << ui->tableK->columnCount();
    ui->tableK->item(ui->tableK->rowCount() - 1, 5)->setText(text);
    text = buyerVec.at(i).www;
    ui->tableK->item(ui->tableK->rowCount() - 1, 6)->setText(text);
    ui->tableK->item(ui->tableK->rowCount() - 1, 6)
        ->setTextColor(QColor(30, 144, 255));
  }

  ui->tableK->setSortingEnabled(true);
}

/** Reads goods from the XML
 */

void MainWindow::readGoods() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  tableClear(ui->tableT);
  QVector<ProductData> prodVec = dl->productsSelectAllData();

  for (int i = 0; i < prodVec.size(); ++i) {

    insertRow(ui->tableT, ui->tableT->rowCount());
    QString text = QString::number(prodVec.at(i).id);
    ui->tableT->item(ui->tableT->rowCount() - 1, 0)->setText(text);
    text = prodVec.at(i).name;
    ui->tableT->item(ui->tableT->rowCount() - 1, 1)->setText(text);
    text = prodVec.at(i).desc;
    ui->tableT->item(ui->tableT->rowCount() - 1, 2)->setText(text);
    text = prodVec.at(i).code;
    ui->tableT->item(ui->tableT->rowCount() - 1, 3)->setText(text);
    text = prodVec.at(i).pkwiu;
    ui->tableT->item(ui->tableT->rowCount() - 1, 4)->setText(text);
    text = prodVec.at(i).type;
    ui->tableT->item(ui->tableT->rowCount() - 1, 5)->setText(text);
    text = prodVec.at(i).quanType;
    ui->tableT->item(ui->tableT->rowCount() - 1, 6)->setText(text);
    text = sett().numberToString(prodVec.at(i).prices[0]);
    ui->tableT->item(ui->tableT->rowCount() - 1, 7)->setText(text);
    text = sett().numberToString(prodVec.at(i).prices[0]);
    ui->tableT->item(ui->tableT->rowCount() - 1, 8)->setText(text);
    text = sett().numberToString(prodVec.at(i).prices[0]);
    ui->tableT->item(ui->tableT->rowCount() - 1, 9)->setText(text);
    text = sett().numberToString(prodVec.at(i).prices[0]);
    ui->tableT->item(ui->tableT->rowCount() - 1, 10)->setText(text);
    text = QString::number(prodVec.at(i).vat);
    ui->tableT->item(ui->tableT->rowCount() - 1, 11)->setText(text);
  }

  ui->tableT->setSortingEnabled(true);
}

/** Creates directories if required
 */

void MainWindow::setupDir() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  workingDir = sett().getWorkingDir();
  QDir dir(workingDir);
  QDir mainPath(QDir::homePath() + "/.local/share/data");

  if (!mainPath.exists()) {

    mainPath.mkpath(QDir::homePath() + "/.local/share/data");
  }

  if (!dir.exists()) {

    dir.mkdir(workingDir);
    dir.mkdir(workingDir + sett().getDataDir());
    dir.mkdir(workingDir + sett().getWarehouseDir());
  }

  if (!dir.exists(workingDir + sett().getDataDir())) {

    dir.mkdir(workingDir + sett().getDataDir());
  }

  if (!dir.exists(workingDir + sett().getWarehouseDir())) {

    dir.mkdir(workingDir + sett().getWarehouseDir());
  }
}

// ----------------------------------------  SLOTS
// ---------------------------------//

void MainWindow::keyPressEvent(QKeyEvent *event) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  if (event->key() == Qt::Key_F5) {

    newInv();
  }

  if (event->key() == Qt::Key_Return) {

    switch (ui->tabWidget2->currentIndex()) {
    case 0: {

      editFHist();
      break;
    }
    case 1: {

      buyerEd();
      break;
    }
    case 2: {

      goodsEdit();
      break;
    }
    }
  }

  if (event->modifiers() == Qt::ControlModifier &&
      event->key() == Qt::Key_PageUp) {

    if (ui->tabWidget2->currentIndex() != ui->tabWidget2->count() - 1) {

      ui->tabWidget2->setCurrentIndex(ui->tabWidget2->currentIndex() + 1);

    } else {

      ui->tabWidget2->setCurrentIndex(0);
    }
  }

  if (event->modifiers() == Qt::ControlModifier &&
      event->key() == Qt::Key_PageDown) {

    if (ui->tabWidget2->currentIndex() != 0) {

      ui->tabWidget2->setCurrentIndex(ui->tabWidget2->currentIndex() - 1);

    } else {

      ui->tabWidget2->setCurrentIndex(ui->tabWidget2->count() - 1);
    }
  }
}

/** Slot
 *  Just show the message.
 */

void MainWindow::pluginInfoSlot() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  QMessageBox::information(
      this, trUtf8("QFaktury"),
      trUtf8("To menu służy do obsługi pluginów pythona, \n np. archiwizacji "
             "danych, generowania raportów etc.\n\n") +
          trUtf8("Skrypty pythona sa czytane z folderu \"~/elinux/plugins/\"."),
      trUtf8("Ok"), 0, 0, 1);
}

/** Slot
 *  Used while calling python script from the menu
 */

void MainWindow::pluginSlot() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  QString program = QString("python");

  QAction *a = static_cast<QAction *>(this->sender());

  int scriptId = a->data().toInt();

  QStringList args;
  args += customActions[scriptId];
  args += QString("%1").arg(winId(), 0, 10);

  qDebug() << find(winId())->windowTitle();

  QProcess *cmd = new QProcess(this);

  cmd->start(program, args);

  if (!cmd->waitForStarted()) {

    QMessageBox::information(this, trUtf8("QFaktury"),
                             trUtf8("Uruchomienie się nie powiodło."),
                             QMessageBox::Ok);
  }

  if (cmd != 0)
    cmd = 0;
  delete cmd;
  if (a != 0)
    a = 0;
  delete a;
}

/** Slot
 *  Shows context menu
 */

void MainWindow::showTableMenuT(QPoint p) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  QMenu *menuTableT = new QMenu(ui->tableT);
  menuTableT->addAction(ui->addGoodsAction);
  menuTableT->addAction(ui->delGoodsAction);
  menuTableT->addAction(ui->editGoodsAction);
  menuTableT->exec(ui->tableT->mapToGlobal(p));

  menuTableT = 0;
  delete menuTableT;
}

/** Slot
 *  Show context menu
 */
void MainWindow::showTableMenuK(QPoint p) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  QMenu *menuTable = new QMenu(ui->tableK);
  menuTable->addAction(ui->addBuyersAction);
  menuTable->addAction(ui->delBuyersAction);
  menuTable->addAction(ui->editBuyersAction);
  menuTable->exec(ui->tableK->mapToGlobal(p));

  menuTable = 0;
  delete menuTable;
}

void MainWindow::showTableMenuM(QPoint p) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  QMenu *menuTable = new QMenu(ui->tableM);
  menuTable->addAction(ui->WZAction);
  menuTable->addAction(ui->RWAction);
  menuTable->addAction(ui->warehouseEdAction);
  menuTable->addAction(ui->warehouseDelAction);
  menuTable->exec(ui->tableM->mapToGlobal(p));

  menuTable = 0;
  delete menuTable;
}

/** Slot
 *  Show context menu
 */
void MainWindow::showTableMenuH(QPoint p) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  QMenu *menuTable = new QMenu(ui->tableH);
  menuTable->addAction(ui->addInvoiceAction);
  menuTable->addAction(ui->invoiceGrossAction);
  menuTable->addAction(ui->invoiceRRAction);
  menuTable->addAction(ui->invoiceBillAction);
  menuTable->addSeparator();
  menuTable->addAction(ui->invoiceProFormaAction);
  menuTable->addAction(ui->invoiceCorrAction);
  menuTable->addAction(ui->invoiceDuplAction);
  menuTable->addSeparator();
  menuTable->addAction(ui->invoiceEdAction);
  menuTable->addAction(ui->invoiceDelAction);
  menuTable->exec(ui->tableH->mapToGlobal(p));
  delete menuTable;
  menuTable = NULL;
}

/** Slot
 *  StatusBar slot
 */

void MainWindow::mainUpdateStatus(QTableWidgetItem *item) {

  // cast is required since the names of method and objects inside MainWindow
  // class and
  // QMainWindow and UiMainWindow are the same... I guess there is a way to
  // avoid it.

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  QStatusBar *stat = qobject_cast<QMainWindow *>(this)->statusBar();

  QTableWidget *table = item->tableWidget();
  QString message = QString();
  message += table->horizontalHeaderItem(1)->text() + " : " +
             table->item(item->row(), 1)->text() + ", ";
  message += table->horizontalHeaderItem(2)->text() + " : " +
             table->item(item->row(), 2)->text() + ", ";
  message += table->horizontalHeaderItem(3)->text() + " : " +
             table->item(item->row(), 3)->text();

  stat->showMessage(trUtf8("Wybrana pozycja: ") + message);
}

/** Slot which enables/disables menu. It's possible to add/remove
 * goods/customers
 *  only if this is the current tab.
 */

void MainWindow::tabChanged() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  // history
  if (ui->tableH->rowCount() != 0) {

    ui->invoiceEdAction->setEnabled(true);
    ui->invoiceDelAction->setEnabled(true);

  } else {

    ui->invoiceEdAction->setDisabled(true);
    ui->invoiceDelAction->setDisabled(true);
  }

  // buyers
  if (ui->tableK->rowCount() != 0) {

    ui->editBuyersAction->setEnabled(true);
    ui->delBuyersAction->setEnabled(true);

  } else {

    ui->editBuyersAction->setDisabled(true);
    ui->delBuyersAction->setDisabled(true);
  }

  // goods
  if (ui->tableT->rowCount() != 0) {

    ui->editGoodsAction->setEnabled(true);
    ui->delGoodsAction->setEnabled(true);

  } else {

    ui->editGoodsAction->setDisabled(true);
    ui->delGoodsAction->setDisabled(true);
  }
}

/** Slot used to read the invoices, calls readHist.
 */
void MainWindow::rereadHist(bool) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  if (ui->filtrStart->date() > ui->filtrEnd->date()) {

    QMessageBox::information(
        this, trUtf8("Filtr dat"),
        trUtf8("Data początkowa nie może być większa od daty końcowej"));

  } else {

    tableClear(ui->tableH);
    ui->tableH->setSortingEnabled(false);
    readHist();
  }
}

/** Slot used to read the invoices, calls readHist.
 */
void MainWindow::rereadWarehouses(bool) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  if (ui->warehouseFromDate->date() > ui->warehouseToDate->date()) {

    QMessageBox::information(
        this, trUtf8("Filtr dat"),
        trUtf8("Data początkowa nie może być większa od daty końcowej"));

  } else {

    tableClear(ui->tableM);
    ui->tableM->setSortingEnabled(false);
    readWarehouses();
  }
}

/** Slot used to display information about QFaktury
 */

void MainWindow::aboutProg() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  QMessageBox::about(
      this, trUtf8("O programie"),
      trUtf8("<h2>Program do wystawiania faktur</h2><br/><p>") +
          sett().getVersion(qAppName()) + trUtf8("<br/>Wymagane Qt >= 5.0.0") +
          trUtf8("<br/>Kompilowane z Qt ") + QT_VERSION_STR +
          trUtf8("<br/>Twoja aktualna wersja - Qt ") + qVersion() +
          trUtf8("</p><p>Dawny koordynator projektu: Grzegorz Rękawek</p>  "
                 "<p>Aktualny koordynator projektu: Jagoda \"juliagoda\" "
                 "Górska</p>"
                 "<p>Dawni programiści: Tomasz Pielech, Rafał Rusin "
                 "http://people.apache.org/~rr/, Sławomir Patyk, Jagoda "
                 "Górska</p>"
                 "<p>Aktualni programiści: Jagoda \"juliagoda\" Górska</p>") +
          trUtf8(
              "<p>Ikony: Dariusz Arciszewski, Jagoda \"juliagoda\" Górska </p>"
              "<p>Portowanie na Qt5: "
              "Jagoda \"juliagoda\" Górska</p><br/>") +
          trUtf8("<p>Testy w środowisku Arch Linux: Piotr \"sir_lucjan\" "
                 "Górski && Paweł \"pavbaranov\" Baranowski</p>") +
          trUtf8("<h2><center>UWAGA!!!</center></h2>") +
          trUtf8("<p align=\"justify\">Ten program komputerowy dostarczany "
                 "jest przez autora w formie \"takiej, jaki jest\". ") +
          trUtf8("Autor nie udziela żadnej gwarancji oraz rękojmi, że program "
                 "będzie działał ") +
          trUtf8("prawidłowo, jest odpowiedniej jakości oraz że spełni "
                 "oczekiwania ") +
          trUtf8("użytkownika. Autor nie odpowiada za jakiekolwiek straty "
                 "wynikające z użytkowania ") +
          trUtf8("programu, w tym utratą spodziewanych korzyści, danych, "
                 "informacji ") +
          trUtf8("gospodarczych lub koszt urządzeń lub programów "
                 "zastępczych.</p>"));
}

/** Slot used to edit the invoice from list of invoices.
 */

void MainWindow::editFHist() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  if (ui->tableH->selectedItems().count() <= 0) {

    QMessageBox::information(this, trUtf8("QFaktury"),
                             trUtf8("Faktura nie wybrana. Nie mozna edytować."),
                             trUtf8("Ok"), 0, 0, 1);
    return;
  }

  ui->tableH->setSortingEnabled(false);

  int row = 0;
  row = ui->tableH->selectedItems().at(0)->row();

  if (ui->tableH->item(row, 3)->text() == trUtf8("korekta")) {

    // QMessageBox::information( this, trUtf8("QFaktury"), "Jeszcze nie ma",
    // QMessageBox::Ok );
    Correction *corWindow = new Correction(this, dl, s_WIN_CORRECT_EDIT, true);
    corWindow->correctionInit(true);
    corWindow->readCorrData(ui->tableH->item(row, 0)->text());

    if (corWindow->exec() == QDialog::Accepted) {

      rereadHist(true);
    }

    if (corWindow->getKAdded())
      readBuyer();

    corWindow = 0;
    delete corWindow;
  }

  if (ui->tableH->item(row, 3)->text() == trUtf8("kbrutto")) {

    // QMessageBox::information( this, trUtf8("QFaktury"), "Jeszcze nie ma",
    // QMessageBox::Ok );
    CorrectGross *corWindow =
        new CorrectGross(this, dl, s_WIN_CORRECT_EDIT, true);
    corWindow->correctionInit(true);
    corWindow->readCorrData(ui->tableH->item(row, 0)->text());

    if (shouldHidden) {

      QSizePolicy sp_retain = corWindow->sizePolicy();
      sp_retain.setRetainSizeWhenHidden(true);
      corWindow->setSizePolicy(sp_retain);
      corWindow->hide();
      corWindow->makeInvoice();
    } else {

      if (corWindow->exec() == QDialog::Accepted) {

        rereadHist(true);
      }

      if (corWindow->getKAdded())
        readBuyer();
    }

    corWindow = 0;
    delete corWindow;
  }

  if (ui->tableH->item(row, 3)->text() == trUtf8("rachunek")) {

    Bill *billWindow = new Bill(this, dl, s_BILL_EDIT);
    billWindow->readData(ui->tableH->item(row, 0)->text());
    billWindow->setfName(ui->tableH->item(row, 0)->text());
    billWindow->billInit();
    billWindow->setWindowTitle(trUtf8("Edytuje Rachunek"));

    if (shouldHidden) {

      QSizePolicy sp_retain = billWindow->sizePolicy();
      sp_retain.setRetainSizeWhenHidden(true);
      billWindow->setSizePolicy(sp_retain);
      billWindow->hide();
      billWindow->makeInvoice();
    } else {

      if (billWindow->exec() == QDialog::Accepted) {

        rereadHist(true);
      }

      if (billWindow->getKAdded())
        readBuyer();
    }

    billWindow = 0;
    delete billWindow;
  }

  if (ui->tableH->item(row, 3)->text() == trUtf8("FVAT")) {

    Invoice *invWindow = new Invoice(this, dl, s_WIN_INVOICE_EDIT);

    invWindow->readData(ui->tableH->item(row, 0)->text());
    invWindow->setfName(ui->tableH->item(row, 0)->text());

    if (shouldHidden) {

      QSizePolicy sp_retain = invWindow->sizePolicy();
      sp_retain.setRetainSizeWhenHidden(true);
      invWindow->setSizePolicy(sp_retain);
      invWindow->hide();
      invWindow->makeInvoice();
    } else {

      if (invWindow->exec() == QDialog::Accepted) {

        rereadHist(true);
      }

      if (invWindow->getKAdded())
        readBuyer();
    }

    invWindow = 0;
    delete invWindow;
  }

  if (ui->tableH->item(row, 3)->text() == trUtf8("RR")) {

    InvoiceRR *invWindow = new InvoiceRR(this, dl, s_RR);
    invWindow->invoiceRRInit();

    invWindow->readData(ui->tableH->item(row, 0)->text());
    invWindow->setfName(ui->tableH->item(row, 0)->text());

    if (shouldHidden) {

      QSizePolicy sp_retain = invWindow->sizePolicy();
      sp_retain.setRetainSizeWhenHidden(true);
      invWindow->setSizePolicy(sp_retain);
      invWindow->hide();
      invWindow->makeInvoice();
    } else {

      if (invWindow->exec() == QDialog::Accepted) {

        rereadHist(true);
      }

      if (invWindow->getKAdded())
        readBuyer();
    }

    invWindow = 0;
    delete invWindow;
  }

  if (ui->tableH->item(row, 3)->text() == trUtf8("FPro")) {

    Invoice *invWindow = new Invoice(this, dl, s_WIN_PROFORMA_EDIT);

    invWindow->readData(ui->tableH->item(row, 0)->text());
    invWindow->setfName(ui->tableH->item(row, 0)->text());

    if (shouldHidden) {

      QSizePolicy sp_retain = invWindow->sizePolicy();
      sp_retain.setRetainSizeWhenHidden(true);
      invWindow->setSizePolicy(sp_retain);
      invWindow->hide();
      invWindow->makeInvoice();
    } else {
      if (invWindow->exec() == QDialog::Accepted) {

        rereadHist(true);
      }

      if (invWindow->getKAdded())
        readBuyer();
    }

    invWindow = 0;
    delete invWindow;
  }

  if (ui->tableH->item(row, 3)->text() == trUtf8("FBrutto")) {

    InvoiceGross *invWindow = new InvoiceGross(this, dl, s_BR_INVOICE_EDIT);

    invWindow->readData(ui->tableH->item(row, 0)->text());
    invWindow->setfName(ui->tableH->item(row, 0)->text());

    if (shouldHidden) {

      QSizePolicy sp_retain = invWindow->sizePolicy();
      sp_retain.setRetainSizeWhenHidden(true);
      invWindow->setSizePolicy(sp_retain);
      invWindow->hide();
      invWindow->makeInvoice();
    } else {
      if (invWindow->exec() == QDialog::Accepted) {

        rereadHist(true);
      }

      if (invWindow->getKAdded())
        readBuyer();
    }

    invWindow = 0;
    delete invWindow;
  }

  if (ui->tableH->item(row, 3)->text() == trUtf8("duplikat")) {

    Duplicate *dupWindow = new Duplicate(this, dl, s_WIN_DUPLICATE_LOOK, true);

    dupWindow->readData(ui->tableH->item(row, 0)->text());
    dupWindow->duplicateInit();
    dupWindow->setIsEditAllowed(false);
    dupWindow->setfName(ui->tableH->item(row, 0)->text());

    if (shouldHidden) {

      QSizePolicy sp_retain = dupWindow->sizePolicy();
      sp_retain.setRetainSizeWhenHidden(true);
      dupWindow->setSizePolicy(sp_retain);
      dupWindow->hide();
      dupWindow->makeInvoice();
    } else {

      if (dupWindow->exec() == QDialog::Accepted) {

        rereadHist(true);
      }

      if (dupWindow->getKAdded())
        readBuyer();
    }

    dupWindow = 0;
    delete dupWindow;
  }

  ui->tableH->setSortingEnabled(true);
}

void MainWindow::warehouseEdit() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  if (ui->tableM->selectedItems().count() <= 0) {

    QMessageBox::information(
        this, trUtf8("QFaktury"),
        trUtf8("Dokument magazynu nie został wybrany. Nie można edytować."),
        trUtf8("Ok"), 0, 0, 1);
    return;
  }

  ui->tableM->setSortingEnabled(false);

  int row = 0;
  row = ui->tableM->selectedItems().at(0)->row();

  if (ui->tableM->item(row, 3)->text() == trUtf8("WZ")) {

    DeliveryNote *delivNoteWindow = new DeliveryNote(this, dl, s_WZ);
    delivNoteWindow->readWarehouseData(ui->tableM->item(row, 0)->text());
    delivNoteWindow->setfName(ui->tableM->item(row, 0)->text());

    if (shouldHidden) {

      QSizePolicy sp_retain = delivNoteWindow->sizePolicy();
      sp_retain.setRetainSizeWhenHidden(true);
      delivNoteWindow->setSizePolicy(sp_retain);
      delivNoteWindow->hide();
      delivNoteWindow->makeInvoice();

    } else {

      if (delivNoteWindow->exec() == QDialog::Accepted) {

        rereadWarehouses(true);
        rereadHist(true);
      }

      if (delivNoteWindow->getKAdded())
        readBuyer();
    }

    delivNoteWindow = 0;
    delete delivNoteWindow;
  }

  if (ui->tableM->item(row, 3)->text() == trUtf8("RW")) {

    GoodsIssuedNotes *goodsNoteWindow = new GoodsIssuedNotes(this, dl, s_RW);
    goodsNoteWindow->readWarehouseData(ui->tableM->item(row, 0)->text());
    goodsNoteWindow->setfName(ui->tableM->item(row, 0)->text());

    if (shouldHidden) {

      QSizePolicy sp_retain = goodsNoteWindow->sizePolicy();
      sp_retain.setRetainSizeWhenHidden(true);
      goodsNoteWindow->setSizePolicy(sp_retain);
      goodsNoteWindow->hide();
      goodsNoteWindow->makeInvoice();

    } else {

      if (goodsNoteWindow->exec() == QDialog::Accepted) {

        rereadWarehouses(true);
      }

      if (goodsNoteWindow->getKAdded())
        readBuyer();
    }

    goodsNoteWindow = 0;
    delete goodsNoteWindow;
  }

  ui->tableM->setSortingEnabled(true);
}

void MainWindow::delFHist() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  if (ui->tableH->selectedItems().count() <= 0) {

    QMessageBox::information(
        this, trUtf8("QFaktury"),
        trUtf8("Faktura nie została wybrana. Nie można usuwać."), trUtf8("Ok"),
        0, 0, 1);
    return;
  }

  if (QMessageBox::warning(
          this, sett().getVersion(qAppName()),
          trUtf8("Czy napewno chcesz usunąć tą fakturę z historii?"),
          trUtf8("Tak"), trUtf8("Nie"), 0, 0, 1) == 0) {

    QString name = ui->tableH->item(ui->tableH->currentRow(), 0)->text();
    dl->invoiceDeleteData(name);
    ui->tableH->removeRow(ui->tableH->currentRow());
    allSymbols = dl->getAllSymbols();
  }
}

void MainWindow::delMHist() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  if (ui->tableM->selectedItems().count() <= 0) {

    QMessageBox::information(
        this, trUtf8("QFaktury"),
        trUtf8("Dokument magazynu nie został wybrany. Nie można usuwać."),
        trUtf8("Ok"), 0, 0, 1);
    return;
  }

  if (QMessageBox::warning(
          this, sett().getVersion(qAppName()),
          trUtf8("Czy napewno chcesz usunąć ten dokument magazynu z historii?"),
          trUtf8("Tak"), trUtf8("Nie"), 0, 0, 1) == 0) {

    QString name = ui->tableM->item(ui->tableM->currentRow(), 0)->text();
    dl->warehouseDeleteData(name);
    ui->tableM->removeRow(ui->tableM->currentRow());
    allSymbolsWarehouse = dl->getAllSymbolsWarehouse();
  }
}

/** Slot used to edit data of the current company
 */

void MainWindow::userDataClick() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  User *userDataWindow = new User(this);
  userDataWindow->show();

  userDataWindow = 0;
  delete userDataWindow;
}

/** Slot used to edit edit sett()
 */

void MainWindow::settClick() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  Setting *settWindow = new Setting(this);
  settWindow->show();

  settWindow = 0;
  delete settWindow;
}

/** Slot used to add new customer
 */

void MainWindow::buyerClick() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  Buyers *buyersWindow;
  buyersWindow = new Buyers(this, 0, dl);

  if (buyersWindow->exec() == QDialog::Accepted) {

    ui->tableK->setSortingEnabled(false);
    insertRow(ui->tableK, ui->tableK->rowCount());
    QStringList row = buyersWindow->getRetBuyer().split("|");

    ui->tableK->item(ui->tableK->rowCount() - 1, 0)->setText(row[0]); // name
    ui->tableK->item(ui->tableK->rowCount() - 1, 1)->setText(row[1]); // type
    ui->tableK->item(ui->tableK->rowCount() - 1, 2)->setText(row[2]); // place
    ui->tableK->item(ui->tableK->rowCount() - 1, 3)->setText(row[3]); // address
    ui->tableK->item(ui->tableK->rowCount() - 1, 4)->setText(row[4]); // telefon
    ui->tableK->item(ui->tableK->rowCount() - 1, 5)->setText(row[8]); // email
    ui->tableK->item(ui->tableK->rowCount() - 1, 6)->setText(row[9]); // www*/
    ui->tableK->setSortingEnabled(true);
  }

  buyersWindow = 0;
  delete buyersWindow;
}

/** Slot used to delete current customer
 */

void MainWindow::buyerDel() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  if (ui->tableK->selectedItems().count() <= 0) {

    QMessageBox::information(
        this, trUtf8("QFaktury"),
        trUtf8("Kontrahent nie został wybrany. Nie można usuwac."),
        trUtf8("Ok"), 0, 0, 1);
    return;
  }

  if (QMessageBox::warning(
          this, trUtf8("QFaktury"),
          trUtf8("Czy napewno chcesz usunąć kontrahenta: ") +
              ui->tableK->item(ui->tableK->currentRow(), 0)->text() +
              trUtf8(" ?"),
          trUtf8("Tak"), trUtf8("Nie"), 0, 0, 1) == 0) {

    dl->buyersDeleteData(ui->tableK->item(ui->tableK->currentRow(), 0)->text());
    ui->tableK->removeRow(ui->tableK->currentRow());
  }
}

/** Slot used to edit customer
 */

void MainWindow::buyerEd() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  if (ui->tableK->selectedItems().count() <= 0) {

    QMessageBox::information(this, trUtf8("QFaktury"),
                             trUtf8("Kontrahent nie został wybrany."),
                             trUtf8("Ok"), 0, 0, 1);
    return;
  }

  int row = ui->tableK->selectedItems()[0]->row();

  Buyers *buyersWindow = new Buyers(this, 1, dl);
  buyersWindow->selectData(
      ui->tableK->item(row, 0)->text(),
      sett().getCustomerType(ui->tableK->item(row, 1)->text()));

  if (buyersWindow->exec() == QDialog::Accepted) {

    ui->tableK->setSortingEnabled(false);
    QStringList rowTxt = buyersWindow->getRetBuyer().split("|");
    ui->tableK->item(row, 0)->setText(rowTxt[0]); // name
    ui->tableK->item(row, 1)->setText(rowTxt[1]); // type
    ui->tableK->item(row, 2)->setText(rowTxt[2]); // place
    ui->tableK->item(row, 3)->setText(rowTxt[3]); // address
    ui->tableK->item(row, 4)->setText(rowTxt[4]); // telefon
    ui->tableK->item(row, 5)->setText(rowTxt[8]); // email
    ui->tableK->item(row, 6)->setText(rowTxt[9]); // www
    ui->tableK->setSortingEnabled(true);
  }

  buyersWindow = 0;
  delete buyersWindow;
}

void MainWindow::printBuyerList() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  QPrinter printer(QPrinter::HighResolution);
  QPrintPreviewDialog preview(&printer, this);
  preview.setWindowFlags(Qt::Window);
  preview.setWindowTitle(trUtf8("Lista kontrahentów"));

  connect(&preview, SIGNAL(paintRequested(QPrinter *)), this,
          SLOT(printList(QPrinter *)));
  if (preview.exec() == 1) {

    QMessageBox::warning(
        this, trUtf8("Drukowanie"),
        trUtf8("Prawdopobnie nie masz skonfigurowanej drukarki. Wykrywana "
               "nazwa domyślnej drukarki to: ") +
            printer.printerName() +
            trUtf8(". Status domyślnej drukarki (poprawny o ile drukarka ma "
                   "możliwość raportowania statusu do systemu): ") +
            printer.printerState());
  }
}

/** Slot print
 *  Helper slot used to display print preview
 */

void MainWindow::printList(QPrinter *printer) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  if (ui->tableK->rowCount() != 0) {

    QTextDocument doc(trUtf8("Lista kontrahentów"));
    QStringList list = QStringList();
    list << "<!doctype html>"
         << "<head>"
         << "<meta charset=\"utf-8\" />"
         << "</head>";
    list << "<style type=\"text/css\">";
    list << "strong { font-weight: 500; }";
    list << ".page_break {page-break-inside: avoid;}";
    list << "</style>";
    list << "<body>";

    QVector<BuyerData> buyerVec = dl->buyersSelectAllData();

    for (int i = 0; i < buyerVec.size(); ++i) {

      QString text = buyerVec.at(i).name;
      list << "<strong>" + trUtf8("Nazwa:  ") + "</strong>" +
                  changeIfEmpty(text);
      list << "<br/>";
      text = buyerVec.at(i).type;
      list << "<strong>" + trUtf8("Rodzaj:  ") + "</strong>" +
                  changeIfEmpty(text);
      list << "<br/>";
      text = buyerVec.at(i).place;
      list << "<strong>" + trUtf8("Miejscowość:  ") + "</strong>" +
                  changeIfEmpty(text);
      list << "<br/>";
      text = buyerVec.at(i).address;
      list << "<strong>" + trUtf8("Adres:  ") + "</strong>" +
                  changeIfEmpty(text);
      list << "<br/>";
      text = buyerVec.at(i).phone;
      list << "<strong>" + trUtf8("Tel:  ") + "</strong>" + changeIfEmpty(text);
      list << "<br/>";
      text = buyerVec.at(i).account;
      list << "<strong>" + trUtf8("Nr konta:  ") + "</strong>" +
                  changeIfEmpty(text);
      list << "<br/>";
      text = buyerVec.at(i).email;
      list << "<strong>" + trUtf8("Email:  ") + "</strong>" +
                  changeIfEmpty(text);
      list << "<br/>";
      text = buyerVec.at(i).www;
      list << "<strong>" + trUtf8("Strona:  ") + "</strong>" +
                  changeIfEmpty(text);
      list << "<p> --------------------------------------------- </p>";
      list << "<p class=\"page_break\"></p>";
    }

    list << "</body>";
    list << "</html>";

    QFile file(sett().getWorkingDir() + "/buyerContacts.html");

    bool removed = false;

    if (file.exists())
      removed = file.remove();

    if (!removed) {

      QFile(file.fileName())
          .setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner);
      file.remove();
    }

    if (!file.open(QIODevice::WriteOnly)) {

      QFile(file.fileName())
          .setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner);
    }

    QTextStream stream(&file);

    for (QStringList::Iterator it = list.begin(); it != list.end(); ++it)
      stream << *it << "\n";

    file.close();

    doc.setHtml(list.join(" "));
    doc.print(printer);

  } else {

    if (QMessageBox::warning(
            this, trUtf8("Brak kontrahentów"),
            trUtf8("Aby móc wydrukować listę kontaktów, musisz mieć "
                   "wprowadzonego co najmniej jednego kontrahenta do tabeli. "
                   "Czy chcesz dodać teraz dane twojego kontrahenta?"),
            trUtf8("Tak"), trUtf8("Nie"), 0, 0, 1) == 0) {
      buyerClick();
    }
  }
}

QString MainWindow::changeIfEmpty(QString text) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  QString result = QString();

  if (text.isEmpty()) {
    result = "-";
  } else {
    result = text;
  }

  return result;
}

/** Slot used for creating new invoices
 */

void MainWindow::newInv() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  Invoice *invWindow = new Invoice(this, dl, s_INVOICE);

  if (invWindow->exec() == QDialog::Accepted) {

    ui->tableH->setSortingEnabled(false);
    insertRow(ui->tableH, ui->tableH->rowCount());
    QStringList row = invWindow->getRet().split("|");
    ui->tableH->item(ui->tableH->rowCount() - 1, 0)
        ->setText(row[0]); // file name
    ui->tableH->item(ui->tableH->rowCount() - 1, 1)->setText(row[1]); // symbol
    ui->tableH->item(ui->tableH->rowCount() - 1, 2)->setText(row[2]); // date
    ui->tableH->item(ui->tableH->rowCount() - 1, 3)->setText(row[3]); // type
    ui->tableH->item(ui->tableH->rowCount() - 1, 4)->setText(row[4]); // buyer
    ui->tableH->item(ui->tableH->rowCount() - 1, 5)->setText(row[5]); // NIP
    ui->tableH->setSortingEnabled(true);

  } else {

    rereadHist(true);
  }

  if (invWindow->getKAdded())
    readBuyer();
  dl->checkAllSymbInFiles();
  allSymbols = dl->getAllSymbols();

  invWindow = 0;
  delete invWindow;
}

void MainWindow::newInvRR() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  InvoiceRR *invWindow = new InvoiceRR(this, dl, s_RR);
  invWindow->invoiceRRInit();

  if (invWindow->exec() == QDialog::Accepted) {

    ui->tableH->setSortingEnabled(false);
    insertRow(ui->tableH, ui->tableH->rowCount());
    QStringList row = invWindow->getRet().split("|");
    ui->tableH->item(ui->tableH->rowCount() - 1, 0)
        ->setText(row[0]); // file name
    ui->tableH->item(ui->tableH->rowCount() - 1, 1)->setText(row[1]); // symbol
    ui->tableH->item(ui->tableH->rowCount() - 1, 2)->setText(row[2]); // date
    ui->tableH->item(ui->tableH->rowCount() - 1, 3)->setText(row[3]); // type
    ui->tableH->item(ui->tableH->rowCount() - 1, 4)->setText(row[4]); // buyer
    ui->tableH->item(ui->tableH->rowCount() - 1, 5)->setText(row[5]); // NIP
    ui->tableH->setSortingEnabled(true);

  } else {

    rereadHist(true);
  }

  if (invWindow->getKAdded())
    readBuyer();
  dl->checkAllSymbInFiles();
  allSymbols = dl->getAllSymbols();

  invWindow = 0;
  delete invWindow;
}

/** Slot used for creating new invoices
 */
void MainWindow::newInvBill() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  Bill *billWindow = new Bill(this, dl, s_BILL);

  billWindow->setWindowTitle(trUtf8("Rachunek"));
  billWindow->billInit();

  if (billWindow->exec() == QDialog::Accepted) {

    ui->tableH->setSortingEnabled(false);
    insertRow(ui->tableH, ui->tableH->rowCount());
    QStringList row = billWindow->getRet().split("|");
    ui->tableH->item(ui->tableH->rowCount() - 1, 0)
        ->setText(row[0]); // file name
    ui->tableH->item(ui->tableH->rowCount() - 1, 1)->setText(row[1]); // symbol
    ui->tableH->item(ui->tableH->rowCount() - 1, 2)->setText(row[2]); // date
    ui->tableH->item(ui->tableH->rowCount() - 1, 3)->setText(row[3]); // type
    ui->tableH->item(ui->tableH->rowCount() - 1, 4)->setText(row[4]); // buyer
    ui->tableH->item(ui->tableH->rowCount() - 1, 5)->setText(row[5]); // NIP
    ui->tableH->setSortingEnabled(true);

  } else {

    rereadHist(true);
  }

  if (billWindow->getKAdded())
    readBuyer();
  dl->checkAllSymbInFiles();
  allSymbols = dl->getAllSymbols();
  billWindow = 0;
  delete billWindow;
}

/** Slot used for creating new invoices
 */
void MainWindow::newInvGross() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  InvoiceGross *invWindow = new InvoiceGross(this, dl, s_FBRUTTO);
  invWindow->setWindowTitle(trUtf8("Faktura VAT Brutto"));

  if (invWindow->exec() == QDialog::Accepted) {

    ui->tableH->setSortingEnabled(false);
    insertRow(ui->tableH, ui->tableH->rowCount());
    QStringList row = invWindow->getRet().split("|");
    ui->tableH->item(ui->tableH->rowCount() - 1, 0)
        ->setText(row[0]); // file name
    ui->tableH->item(ui->tableH->rowCount() - 1, 1)->setText(row[1]); // symbol
    ui->tableH->item(ui->tableH->rowCount() - 1, 2)->setText(row[2]); // date
    ui->tableH->item(ui->tableH->rowCount() - 1, 3)->setText(row[3]); // type
    ui->tableH->item(ui->tableH->rowCount() - 1, 4)->setText(row[4]); // buyer
    ui->tableH->item(ui->tableH->rowCount() - 1, 5)->setText(row[5]); // NIP
    ui->tableH->setSortingEnabled(true);

  } else {

    rereadHist(true);
  }

  if (invWindow->getKAdded())
    readBuyer();
  dl->checkAllSymbInFiles();
  allSymbols = dl->getAllSymbols();
  invWindow = 0;
  delete invWindow;
}

/** Slot used to create new ProForma Invoice
 */

void MainWindow::newPForm() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  Invoice *invWindow = new Invoice(this, dl, s_PROFORMA);
  invWindow->setWindowTitle(trUtf8("Faktura Pro Forma"));
  invWindow->backBtnClick();

  if (invWindow->exec() == QDialog::Accepted) {

    ui->tableH->setSortingEnabled(false);
    insertRow(ui->tableH, ui->tableH->rowCount());
    QStringList row = invWindow->getRet().split("|");
    ui->tableH->item(ui->tableH->rowCount() - 1, 0)
        ->setText(row[0]); // file name
    ui->tableH->item(ui->tableH->rowCount() - 1, 1)->setText(row[1]); // symbol
    ui->tableH->item(ui->tableH->rowCount() - 1, 2)->setText(row[2]); // date
    ui->tableH->item(ui->tableH->rowCount() - 1, 3)->setText(row[3]); // type
    ui->tableH->item(ui->tableH->rowCount() - 1, 4)->setText(row[4]); // buyer
    ui->tableH->item(ui->tableH->rowCount() - 1, 5)->setText(row[5]); // NIP
    ui->tableH->setSortingEnabled(true);

  } else {

    rereadHist(true);
  }

  if (invWindow->getKAdded())
    readBuyer();
  dl->checkAllSymbInFiles();
  allSymbols = dl->getAllSymbols();
  invWindow = 0;
  delete invWindow;
}

/** Slot used to create new Correction
 */

void MainWindow::newCor() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  if (ui->tableH->selectedItems().count() <= 0) {

    QMessageBox::information(
        this, trUtf8("QFaktury"),
        trUtf8("Faktura nie została wybrana. Wybierz fakurę, do "
               "której chcesz wystawić korektę."),
        trUtf8("Ok"), 0, 0, 1);
    return;
  }

  int row = ui->tableH->selectedItems()[0]->row();

  QStringList invTypes = QStringList();
  invTypes << "FVAT"
           << "FBrutto";

  if (invTypes.contains(ui->tableH->item(row, 3)->text())) {

    ui->tableH->setSortingEnabled(false);

    Correction *corWindow;

    if (ui->tableH->item(row, 3)->text().contains("FVAT")) {

      corWindow = new Correction(this, dl, s_CORRECT_TITLE, false);

    } else {

      corWindow = new CorrectGross(this, dl, s_CORRECT_BRUTTO, false);
    }

    corWindow->correctionInit(false);
    corWindow->readData(ui->tableH->item(row, 0)->text());
    corWindow->setWindowTitle(trUtf8("Nowa korekta"));

    if (corWindow->exec() == QDialog::Accepted) {

      insertRow(ui->tableH, ui->tableH->rowCount());
      QStringList row = corWindow->getRet().split("|");
      int newRow = ui->tableH->rowCount() - 1;
      ui->tableH->item(newRow, 0)->setText(row[0]); // file name
      ui->tableH->item(newRow, 1)->setText(row[1]); // symbol
      ui->tableH->item(newRow, 2)->setText(row[2]); // date
      ui->tableH->item(newRow, 3)->setText(row[3]); // type
      ui->tableH->item(newRow, 4)->setText(row[4]); // nabywca
      ui->tableH->item(newRow, 5)->setText(row[5]); // NIP

    } else {

      rereadHist(true);
    }

    if (corWindow->getKAdded())
      readBuyer();
    dl->checkAllSymbInFiles();
    allSymbols = dl->getAllSymbols();
    corWindow = 0;
    delete corWindow;
    ui->tableH->setSortingEnabled(true);

  } else {

    QMessageBox::information(this, "QFaktury",
                             trUtf8("Do faktury typu ") +
                                 ui->tableH->item(row, 3)->text() +
                                 (" nie wystawiamy korekt."),
                             QMessageBox::Ok);
  }
}

/** Slot
 *  Creates duplicate
 */

void MainWindow::newDuplicate() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  if (ui->tableH->selectedItems().count() <= 0) {

    QMessageBox::information(this, trUtf8("QFaktury"),
                             trUtf8("Faktura nie wybrana. Wybierz fakurę, do "
                                    "której chcesz wystawić duplikat."),
                             trUtf8("Ok"), 0, 0, 1);
    return;
  }

  int row = ui->tableH->selectedItems()[0]->row();

  // types of invoices for which it's ok to issue a duplicate
  QStringList invTypes = QStringList();
  invTypes << "FVAT"
           << "FBrutto";

  if (invTypes.contains(ui->tableH->item(row, 3)->text())) {

    Duplicate *dupWindow = new Duplicate(this, dl, s_DUPLICATE, false);

    dupWindow->readData(ui->tableH->item(row, 0)->text());
    dupWindow->setWindowTitle(trUtf8("Nowy duplikat"));
    dupWindow->duplicateInit();

    if (dupWindow->exec() == QDialog::Accepted) {

      insertRow(ui->tableH, ui->tableH->rowCount());
      QStringList row = dupWindow->getRet().split("|");
      int newRow = ui->tableH->rowCount() - 1;
      ui->tableH->item(newRow, 0)->setText(row[0]); // file name
      ui->tableH->item(newRow, 1)->setText(row[1]); // symbol
      ui->tableH->item(newRow, 2)->setText(row[2]); // date
      ui->tableH->item(newRow, 3)->setText(row[3]); // type
      ui->tableH->item(newRow, 4)->setText(row[4]); // nabywca
      ui->tableH->item(newRow, 5)->setText(row[5]); // NIP

    } else {

      rereadHist(true);
    }

    if (dupWindow->getKAdded())
      readBuyer();
    dl->checkAllSymbInFiles();
    allSymbols = dl->getAllSymbols();
    dupWindow = 0;
    delete dupWindow;
    ui->tableH->setSortingEnabled(true);

  } else {

    QMessageBox::information(this, "QFaktury",
                             trUtf8("Do faktury typu ") +
                                 ui->tableH->item(row, 3)->text() +
                                 (" nie wystawiamy duplikatów."),
                             QMessageBox::Ok);
  }
}

/** Slot used to add goods
 */

void MainWindow::goodsAdd() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  Goods *goodsWindow = new Goods(this, 0, dl);

  if (goodsWindow->exec() == QDialog::Accepted) {

    ui->tableT->setSortingEnabled(false);
    insertRow(ui->tableT, ui->tableT->rowCount());
    QStringList row = goodsWindow->getRetGoods().split("|");
    ui->tableT->item(ui->tableT->rowCount() - 1, 0)->setText(row[0]);
    ui->tableT->item(ui->tableT->rowCount() - 1, 1)->setText(row[1]);
    ui->tableT->item(ui->tableT->rowCount() - 1, 2)->setText(row[2]);
    ui->tableT->item(ui->tableT->rowCount() - 1, 3)->setText(row[3]);
    ui->tableT->item(ui->tableT->rowCount() - 1, 4)->setText(row[4]);
    ui->tableT->item(ui->tableT->rowCount() - 1, 5)->setText(row[5]);
    ui->tableT->item(ui->tableT->rowCount() - 1, 6)->setText(row[6]);
    ui->tableT->item(ui->tableT->rowCount() - 1, 7)->setText(row[7]);
    ui->tableT->item(ui->tableT->rowCount() - 1, 8)->setText(row[8]);
    ui->tableT->item(ui->tableT->rowCount() - 1, 9)->setText(row[9]);
    ui->tableT->item(ui->tableT->rowCount() - 1, 10)->setText(row[10]);
    ui->tableT->item(ui->tableT->rowCount() - 1, 11)->setText(row[11]);
    ui->tableT->setSortingEnabled(true);
  }

  goodsWindow = 0;
  delete goodsWindow;
}

/** Slot used to delete goods
 */
void MainWindow::goodsDel() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  if (ui->tableT->selectedItems().count() <= 0) {

    QMessageBox::information(
        this, trUtf8("QFaktury"),
        trUtf8("Towar nie został wybrany. Nie można usuwać."), trUtf8("Ok"), 0,
        0, 1);
    return;
  }

  int row = ui->tableT->currentRow();

  if (QMessageBox::warning(this, trUtf8("QFaktury"),
                           trUtf8("Czy napewno chcesz usunąć towar ") +
                               ui->tableT->item(row, 0)->text() + "/" +
                               ui->tableT->item(row, 1)->text() + "?",
                           trUtf8("Tak"), trUtf8("Nie"), 0, 0, 1) == 0) {

    dl->productsDeleteData(ui->tableT->item(row, 0)->text());
    ui->tableT->removeRow(row);
  }
}

/** Slot used for editing goods
 */

void MainWindow::goodsEdit() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  if (ui->tableT->selectedItems().count() <= 0) {

    QMessageBox::information(
        this, trUtf8("QFaktury"),
        trUtf8("Towar nie został wybrany. Nie można edytować."), trUtf8("Ok"),
        0, 0, 1);
    return;
  }

  int row = ui->tableT->selectedItems()[0]->row();

  Goods *goodsWindow = new Goods(this, 1, dl);
  goodsWindow->selectData(
      ui->tableT->item(row, 0)->text(),
      sett().getProductType(ui->tableT->item(row, 5)->text()));

  if (goodsWindow->exec() == QDialog::Accepted) {

    ui->tableT->setSortingEnabled(false);
    QStringList rowTxt = goodsWindow->getRetGoods().split("|");
    ui->tableT->item(row, 0)->setText(rowTxt[0]);
    ui->tableT->item(row, 1)->setText(rowTxt[1]);
    ui->tableT->item(row, 2)->setText(rowTxt[2]);
    ui->tableT->item(row, 3)->setText(rowTxt[3]);
    ui->tableT->item(row, 4)->setText(rowTxt[4]);
    ui->tableT->item(row, 5)->setText(rowTxt[5]);
    ui->tableT->item(row, 6)->setText(rowTxt[6]);
    ui->tableT->item(row, 7)->setText(rowTxt[7]);
    ui->tableT->item(row, 8)->setText(rowTxt[8]);
    ui->tableT->item(row, 9)->setText(rowTxt[9]);
    ui->tableT->item(row, 10)->setText(rowTxt[10]);
    ui->tableT->item(row, 11)->setText(rowTxt[11]);
    ui->tableT->setSortingEnabled(true);
  }

  goodsWindow = 0;
  delete goodsWindow;
}

void MainWindow::noteDownTask(const QDate &taskDate) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  windowTask = new QWidget;

  addTaskBtn = new QPushButton;
  addTaskBtn->setObjectName("addTaskButton");

  QPushButton *addNextTask = new QPushButton;
  addNextTask->setText(trUtf8("Dodaj kolejne"));

  QPushButton *delTasks = new QPushButton;
  delTasks->setText(trUtf8("Usuń zadania"));

  QString planDir = QDir::homePath() + "/.local/share/data/elinux/plans/" +
                    taskDate.toString() + ".txt";
  QFile filename(planDir);

  if (filename.exists())
    addTaskBtn->setText(trUtf8("Zastąp zadanie"));
  else
    addTaskBtn->setText(trUtf8("Dodaj zadanie"));

  cancelTaskBtn = new QPushButton;
  cancelTaskBtn->setText(trUtf8("Anuluj zadanie"));

  QHBoxLayout *buttons = new QHBoxLayout;
  buttons->addWidget(addTaskBtn);
  if (filename.exists())
    buttons->addWidget(addNextTask);
  buttons->addWidget(cancelTaskBtn);
  if (filename.exists())
    buttons->addWidget(delTasks);

  QTextEdit *taskDescription = new QTextEdit;

  QFileInfo check_file(filename.fileName());

  if (check_file.exists() && check_file.isFile()) {

    if (!filename.open(QIODevice::ReadOnly | QIODevice::Text)) {

      QFile(filename.fileName())
          .setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner);
    }

    QTextStream in(&filename);

    while (!in.atEnd()) {

      QString line = in.readLine();

      if (line.isNull()) {
        taskDescription->insertPlainText("\n");
      }

      taskDescription->insertPlainText(line);
      taskDescription->insertPlainText("\n");
      taskDescription->moveCursor(QTextCursor::End);
    }

    filename.close();
  }

  QVBoxLayout *mainElements = new QVBoxLayout;
  mainElements->addWidget(taskDescription);
  mainElements->addLayout(buttons);

  windowTask->setLayout(mainElements);
  windowTask->show();

  markedDate = taskDate;

  connect(addTaskBtn, SIGNAL(clicked()), this, SLOT(addTaskToList()));
  connect(addNextTask, SIGNAL(clicked()), this, SLOT(addNextTask()));
  connect(delTasks, SIGNAL(clicked()), this, SLOT(delTasksFromDay()));
  connect(cancelTaskBtn, SIGNAL(clicked()), this, SLOT(cancelTaskWidget()));
}

void MainWindow::cancelTaskWidget() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  windowTask->hide();

  foreach (QWidget *w, windowTask->findChildren<QWidget *>()) {
    if (!w->windowFlags() && Qt::Window)
      delete w;
  }

  if (windowTask != 0)
    windowTask = 0;
  delete windowTask;
}

void MainWindow::delTasksFromDay() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  QFile file(QDir::homePath() + "/.local/share/data/elinux/plans/" +
             markedDate.toString() + ".txt");
  bool removed = false;

  if (file.exists())
    removed = file.remove();

  if (removed) {

    QMessageBox::information(
        this, trUtf8("Usuwanie zadań"),
        trUtf8("Zadania z wybranego dnia zostały pomyślnie usunięte"),
        QMessageBox::Ok);

  } else {

    file.setPermissions(QFileDevice::ReadOther | QFileDevice::WriteOther);
    removed = file.remove();

    if (removed) {

      QMessageBox::information(
          this, trUtf8("Usuwanie zadań"),
          trUtf8("Zadania z wybranego dnia zostały pomyślnie usunięte"),
          QMessageBox::Ok);

    } else {

      QMessageBox::critical(
          this, trUtf8("Usuwanie zadań"),
          trUtf8("Zadania z wybranego dnia nie mogły zostać pomyślnie "
                 "usunięte. Zrestartuj program, by wyeliminować ewentualny "
                 "brak aktualnych danych o plikach."),
          QMessageBox::Ok);
    }
  }

  cancelTaskWidget();

  checkTodayTask("remove");
}

void MainWindow::addTaskToList() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  QString planDir = QDir::homePath() + "/.local/share/data/elinux/plans";

  QDir mainPath(planDir);

  if (!mainPath.exists()) {

    mainPath.mkdir(planDir);
  }

  QString filename = planDir + "/" + markedDate.toString(Qt::TextDate) + ".txt";

  QTextEdit *button = windowTask->findChild<QTextEdit *>();

  QFile file(filename);

  if (file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text)) {
    QTextStream stream(&file);
    stream << button->toPlainText() << endl;

    if (stream.status() == QTextStream::Ok) {

      QMessageBox::information(this, trUtf8("Dodawanie zadania"),
                               trUtf8("Zadanie zostało pomyślnie stworzone"),
                               QMessageBox::Ok);

      cancelTaskWidget();

      checkTodayTask(QString("insert"));

    } else {

      QFile(file.fileName())
          .setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner);

      QMessageBox::critical(
          this, trUtf8("Dodawanie zadania"),
          trUtf8("Zadanie nie mogło zostać dodane. Sprawdź, czy istnieje "
                 "ścieżka: ") +
              planDir +
              trUtf8(" . Jeśli istnieje to sprawdź, czy masz uprawnienia do "
                     "zapisu i odczytu w podanej ścieżce."),
          QMessageBox::Ok);
    }
  } else {

    QFileInfo check_file(file.fileName());

    if (check_file.exists() && check_file.isFile()) {

      QFile(file.fileName())
          .setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner);

      addTaskToList();
    }
  }
}

void MainWindow::addNextTask() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  QString planDir = QDir::homePath() + "/.local/share/data/elinux/plans";

  QString filename = planDir + "/" + markedDate.toString(Qt::TextDate) + ".txt";

  QTextEdit *button = windowTask->findChild<QTextEdit *>();

  QFile file(filename);
  if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {

    QTextStream stream(&file);
    stream << "\n" << endl;
    stream << button->toPlainText() << endl;

    if (stream.status() == QTextStream::Ok) {

      QMessageBox::information(
          this, trUtf8("Dopisywanie kolejnego zadania"),
          trUtf8("Dodatkowe zadanie zostało pomyślnie dodane."),
          QMessageBox::Ok);

      cancelTaskWidget();

      checkTodayTask();

    } else {

      QFileInfo check_file(file.fileName());

      if (check_file.exists() && check_file.isFile()) {

        QFile(file.fileName())
            .setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner);

        QTextStream stream(&file);
        stream << "\n" << endl;
        stream << button->toPlainText() << endl;

        if (stream.status() == QTextStream::Ok) {

          QMessageBox::information(
              this, trUtf8("Dopisywanie kolejnego zadania"),
              trUtf8("Dodatkowe zadanie zostało pomyślnie dodane."),
              QMessageBox::Ok);

          cancelTaskWidget();

          checkTodayTask();

        } else {

          QMessageBox::critical(
              this, trUtf8("Dopisywanie kolejnego zadania"),
              trUtf8("Dodatkowe zadanie nie mogło zostać dodane. Sprawdź, czy "
                     "istnieje ścieżka: ") +
                  planDir +
                  trUtf8(" . Jeśli istnieje to sprawdź, czy masz uprawnienia "
                         "do zapisu i odczytu w podanej ścieżce."),
              QMessageBox::Ok);
        }
      }
    }
  }
}

void MainWindow::openHideOrganizer() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  if (ui->organizer->isHidden()) {

    ui->organizer->show();
    ui->hideOrganizer->setText(">>");

  } else {

    ui->organizer->hide();
    ui->hideOrganizer->setText("<<");
  }
}

/** Slot close
 */

bool MainWindow::close() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  if (QMessageBox::question(this, trUtf8("Potwierdź"),
                            trUtf8("Czy chcesz wyjść z programu?"),
                            QMessageBox::Yes | QMessageBox::No,
                            QMessageBox::Yes) == QMessageBox::Yes) {

    saveAllSett();
    return QMainWindow::close();

  } else {

    return false;
  }
}

void MainWindow::createFirstWinBackup() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  QPushButton *browseButton =
      new QPushButton(trUtf8("&Szukaj katalogu..."), this);
  connect(browseButton, &QAbstractButton::clicked, this,
          &MainWindow::choosePathBackup);

  QPushButton *okButton = new QPushButton(trUtf8("&Zatwierdź"), this);
  connect(okButton, &QAbstractButton::clicked, this, &MainWindow::createBackup);

  QPushButton *cancButton = new QPushButton(trUtf8("&Zakończ"), this);
  connect(cancButton, &QAbstractButton::clicked, this, [=]() {
    foreach (QWidget *w, windBack->findChildren<QWidget *>()) {
      if (!w->windowFlags() && Qt::Window)
        w->deleteLater();
    }

    windBack->close();
    if (windBack != 0)
      windBack = 0;
    windBack->deleteLater();
  });

  fileComboBox = new QLineEdit();

  directoryComboBox =
      new QLineEdit(QDir::toNativeSeparators(QDir::currentPath()));

  QGridLayout *mainLayout = new QGridLayout(this);
  mainLayout->addWidget(new QLabel(trUtf8("Twoja nazwa archiwum:")), 0, 0);
  mainLayout->addWidget(fileComboBox, 0, 1, 1, 2);
  mainLayout->addWidget(new QLabel(trUtf8("Podaj ścieżkę docelową:")), 2, 0);
  mainLayout->addWidget(directoryComboBox, 2, 1);
  mainLayout->addWidget(browseButton, 2, 2);
  mainLayout->addWidget(okButton, 4, 2);
  mainLayout->addWidget(cancButton, 4, 3);

  windBack = new QWidget();
  windBack->setLayout(mainLayout);

  windBack->setWindowTitle(trUtf8("Podaj miejsce dla kopii zapasowej"));
  const QRect screenGeometry = QApplication::desktop()->screenGeometry(this);
  windBack->resize(screenGeometry.width() / 2, screenGeometry.height() / 3);

  windBack->show();

  qDebug() << sett().fileName();
}

void MainWindow::choosePathBackup() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  QString directory =
      QDir::toNativeSeparators(QFileDialog::getExistingDirectory(
          this, tr("Find Files"), QDir::currentPath()));

  if (!directory.isEmpty()) {
    directoryComboBox->setText(directory);
  }
}

void MainWindow::createBackup() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  QStringList listConf = QStringList()
                         << sett().fileName()
                         << sett().fileName().left(
                                sett().fileName().lastIndexOf("/")) +
                                "/user.conf";

  QMessageBox::warning(this, "", listConf.at(1));

  if (fileComboBox->text().isEmpty() || directoryComboBox->text().isEmpty()) {

    QMessageBox::warning(windBack, trUtf8("Brakująca ścieżka"),
                         trUtf8("Nazwa dla archiwum oraz ścieżka dla "
                                "tworzonego archiwum nie może być pominięta"));

  } else {

    if (JlCompress::compressDir(directoryComboBox->text() + QString("/") +
                                    fileComboBox->text() + QString(".zip"),
                                sett().getWorkingDir(), true, QDir::AllDirs) &&
        JlCompress::compressFiles(directoryComboBox->text() + QString("/") +
                                      fileComboBox->text() +
                                      QString("-configs.zip"),
                                  listConf)) {
      qDebug() << "Created archive";
      QMessageBox::information(
          windBack, trUtf8("Tworzenie kopii zapasowej"),
          trUtf8("Stworzenie kopii zapasowej zakończyło się sukcesem!"));

    } else {

      qDebug() << "Archive had not been created";
      QMessageBox::warning(
          windBack, trUtf8("Tworzenie kopii zapasowej"),
          trUtf8("Stworzenie kopii zapasowej zakończyło "
                 "się niepowodzeniem. Sprawdź, czy masz uprawnienia "
                 "do odczytu i zapisu w wybranym folderze."));
    }

    qDebug() << directoryComboBox->text() + QString("/") +
                    fileComboBox->text() + QString(".zip");

    foreach (QWidget *w, windBack->findChildren<QWidget *>()) {
      if (!w->windowFlags() && Qt::Window)
        delete w;
    }

    windBack->close();
    if (windBack != 0)
      windBack = 0;
    delete windBack;
  }
}

void MainWindow::loadBackup() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  QMessageBox msgBox;
  msgBox.setText(
      trUtf8("Wczytywanie kopii zapasowej nadpisze obecny stan. Wpierw musisz "
             "wybrać katalog, następnie pojawi się okno z jego zawartością."));
  msgBox.setInformativeText(trUtf8("Chcesz kontynuować?"));
  msgBox.setIcon(QMessageBox::Information);
  msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
  msgBox.setDefaultButton(QMessageBox::Ok);
  int ret = msgBox.exec();

  switch (ret) {
  case QMessageBox::Ok:

    QString fileName = QFileDialog::getOpenFileName(
        this, trUtf8("Wybierz kopię zapasową"),
        QFileDialog::getExistingDirectory(this, trUtf8("Znajdź"),
                                          QDir::currentPath()),
        trUtf8("pliki archiwalne (*.zip)"));

    if (fileName.endsWith("-configs.zip")) {

      QStringList configsList = QStringList() << "qfaktury.conf"
                                              << "user.conf";
      QStringList confList = JlCompress::extractFiles(
          fileName, configsList,
          sett().fileName().left(sett().fileName().lastIndexOf("/")));

      if (confList.count() > 0)
        QMessageBox::information(
            this, trUtf8("Kopia zapasowa plików konfiguracyjnych"),
            trUtf8("Wczytywanie kopii zapasowej zakończyło się sukcesem!"));
      else
        QMessageBox::warning(
            this, trUtf8("Kopia zapasowa plików konfiguracyjnych"),
            trUtf8("W archiwum brakuje plików konfiguracyjnych dla QFaktury. "
                   "Jesteś pewien, że wybrałeś plik z przyrostkiem "
                   "\"-configs.zip ?\""));

    } else {

      QStringList listEl =
          JlCompress::extractDir(fileName, sett().getWorkingDir());

      if (listEl.contains("customers.xml") && listEl.contains("products.xml")) {
        QMessageBox::information(
            this, trUtf8("Kopia zapasowa głównego katalogu"),
            trUtf8("Wczytywanie kopii zapasowej zakończyło się sukcesem!"));
      } else {
        QMessageBox::information(
            this, trUtf8("Kopia zapasowa głównego katalogu"),
            trUtf8("Wczytywanie kopii zapasowej zakończyło się niepowodzeniem! "
                   "Kopia zapasowa powinna zawierać co najmniej listę "
                   "produktów i kontrahentów."));
      }
    }

    break;
  }
}

/** Slot for sending email to buyers
 */

void MainWindow::sendEmailToBuyer() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  Send *sendEmailWidget = new Send(
      dl->buyersSelectAllData(),
      dl->invoiceSelectAllData(ui->filtrStart->date(), ui->filtrEnd->date()),
      this);
  sendEmailWidget->show();
}

/*
 *  Slot for delivery note creation (WZ)
 */

void MainWindow::on_WZAction_triggered() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  DeliveryNote *noteWindow = new DeliveryNote(this, dl, s_WZ);
  noteWindow->setWindowTitle(trUtf8("WZ"));
  noteWindow->backBtnClick();

  if (noteWindow->exec() == QDialog::Accepted) {

    ui->tableM->setSortingEnabled(false);
    insertRow(ui->tableM, ui->tableM->rowCount());
    QStringList row = noteWindow->getRetWarehouse().split("|");
    ui->tableM->item(ui->tableM->rowCount() - 1, 0)
        ->setText(row[0]); // file name
    ui->tableM->item(ui->tableM->rowCount() - 1, 1)->setText(row[1]); // symbol
    ui->tableM->item(ui->tableM->rowCount() - 1, 2)->setText(row[2]); // date
    ui->tableM->item(ui->tableM->rowCount() - 1, 3)->setText(row[3]); // type
    ui->tableM->item(ui->tableM->rowCount() - 1, 4)->setText(row[4]); // buyer
    ui->tableM->item(ui->tableM->rowCount() - 1, 5)->setText(row[5]); // NIP
    ui->tableM->setSortingEnabled(true);

    rereadWarehouses(true);
    rereadHist(true);

  } else {

    rereadWarehouses(true);
    rereadHist(true);
  }

  dl->checkAllSymbWareInFiles();
  allSymbolsWarehouse = dl->getAllSymbolsWarehouse();
  noteWindow = 0;
  delete noteWindow;
}

// ----------------------------------------  SLOTS
// ---------------------------------//

void MainWindow::on_RWAction_triggered() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  GoodsIssuedNotes *noteWindow = new GoodsIssuedNotes(this, dl, s_RW);
  noteWindow->setWindowTitle(trUtf8("RW"));
  noteWindow->backBtnClick();

  if (noteWindow->exec() == QDialog::Accepted) {

    ui->tableM->setSortingEnabled(false);
    insertRow(ui->tableM, ui->tableM->rowCount());
    QStringList row = noteWindow->getRetWarehouse().split("|");
    ui->tableM->item(ui->tableM->rowCount() - 1, 0)
        ->setText(row[0]); // file name
    ui->tableM->item(ui->tableM->rowCount() - 1, 1)->setText(row[1]); // symbol
    ui->tableM->item(ui->tableM->rowCount() - 1, 2)->setText(row[2]); // date
    ui->tableM->item(ui->tableM->rowCount() - 1, 3)->setText(row[3]); // type
    ui->tableM->item(ui->tableM->rowCount() - 1, 4)->setText(row[4]); // buyer
    ui->tableM->item(ui->tableM->rowCount() - 1, 5)->setText(row[5]); // NIP
    ui->tableM->setSortingEnabled(true);

    rereadWarehouses(true);

  } else {

    rereadWarehouses(true);
  }

  dl->checkAllSymbWareInFiles();
  allSymbolsWarehouse = dl->getAllSymbolsWarehouse();
  noteWindow = 0;
  delete noteWindow;
}
