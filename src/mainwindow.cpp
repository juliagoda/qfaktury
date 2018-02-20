#include "mainwindow.h"
#include "bill.h"
#include "buyers.h"
#include "const.h"
#include "correctgross.h"
#include "datewidgetitem.h"
#include "deliverynote.h"
#include "duplicate.h"
#include "goods.h"
#include "goodsissuednotes.h"
#include "invoice.h"
#include "invoicegross.h"
#include "invoicerr.h"
#include "owncalendar.h"
#include "send.h"
#include "setting.h"
#include "user.h"
#include "xmldatalayer.h"
#include "organizer.h"
#include "saftfile.h"

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
#include <QDateEdit>
#include <QPointer>


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

  if (timer != 0 || backupTimerOften != 0) {
    timer = 0;
    backupTimerOften = 0;
  }

  delete timer;
  delete backupTimerOften;


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

    //if (ui->tableK->rowCount() != 0)
     // ui->sendEmailAction->setEnabled(true);
    //else
    //  ui->sendEmailAction->setDisabled(true);

  } else {

    ui->invoiceEdAction->setDisabled(true);
    ui->invoiceDelAction->setDisabled(true);
    //ui->sendEmailAction->setDisabled(true);
  }

  if (ui->tableK->rowCount() != 0) {

    ui->editBuyersAction->setEnabled(true);
    ui->delBuyersAction->setEnabled(true);
    ui->actionPrintBuyer->setEnabled(true);

   // if (ui->tableH->rowCount() != 0) {
   //   ui->sendEmailAction->setEnabled(true);
   // } else {
   //   ui->sendEmailAction->setDisabled(true);
    //}

  } else {

    ui->editBuyersAction->setDisabled(true);
    ui->delBuyersAction->setDisabled(true);
    ui->actionPrintBuyer->setDisabled(true);
   // ui->sendEmailAction->setDisabled(true);
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
  connect(ui->findInvoiceAction, SIGNAL(triggered()), this, SLOT(findInvoicePdf()));
  connect(ui->filtrEnd, SIGNAL(dateChanged(const QDate &)), this, SLOT(checkDateRange(const QDate &)));
  connect(ui->warehouseToDate, SIGNAL(dateChanged(const QDate &)), this, SLOT(checkDateRange(const QDate &)));
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

  connect(ui->generateJPKbtn, SIGNAL(clicked(bool)), this, SLOT(openJPKGenerator()));
  connect(ui->fileExportCSVAction, SIGNAL(triggered()), this,
          SLOT(createFirstWinCsv()));
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
  loadPlugins();

  checkIntervalsForBackup();

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


void MainWindow::checkIntervalsForBackup() {

    QSettings settings("elinux", "qfaktury");

    settings.beginGroup("backup_settings");
    if (settings.value("regular_backup").toBool()) {
      if (!settings.value("backup_interval").toString().isEmpty() &&
          !settings.value("backup_interval").toString().isNull()) {

        backupTimerOften = new QTimer(this);
        QString num = settings.value("backup_interval").toString();
        num.chop(1);

        if (settings.value("backup_interval").toString().back() == 'h') {

          backupTimerOften->setInterval(
              num.toInt() * 60 * 60 *
              1000); // checks regularly after chosen hours
          backupTimerOften->setSingleShot(false);

        } else if (settings.value("backup_interval").toString().back() == 'm') {

          backupTimerOften->setInterval(
              num.toInt() * 60 * 1000); // checks regularly after chosen minutes
          backupTimerOften->setSingleShot(false);

        } else {

          backupTimerOften->setInterval(
              60000); // checks once after 1 minute for days, weeks or months
          backupTimerOften->setSingleShot(true);
        }

        connect(backupTimerOften, SIGNAL(timeout()), this,
                SLOT(intervalBackup()));
        backupTimerOften->start();
      }
    }
    settings.endGroup();
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

  if (dl->ifThereOldDocuments(sett().getInoiveDocName(), sett().getInvoicesDir(), QStringList("h*.xml"
                                                                                              "k*.xml")))
    dl->separateOldDocuments(sett().getInvoicesDir());

  if (dl->ifThereOldDocuments(sett().getWarehouseDocName(), sett().getWarehouseFullDir(), QStringList("m*.xml")))
    dl->separateOldDocuments(sett().getWarehouseFullDir());
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


int MainWindow::getInvoiceTypeFullName(QString invoiceType) {

  if (invoiceType == "FVAT")
    return 1;
  else if (invoiceType == "FPro")
    return 2;
  else if (invoiceType == "korekta")
    return 3;
  else if (invoiceType == "FBrutto")
    return 4;
  else if (invoiceType == "kbrutto")
    return 5;
  else if (invoiceType == "rachunek")
    return 6;
  else if (invoiceType == "duplikat")
    return 7;
  else if (invoiceType == "RR")
    return 8;
  else if (invoiceType == "RW")
    return 10;
  else
    return 1;
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
              trUtf8("<p>Tworzenie plików PKGBUILD: Piotr \"sir_lucjan\" "
                     "Górski</p>") +
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
      corWindow->makeInvoice(false);
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
      billWindow->makeInvoice(false);
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
      invWindow->makeInvoice(false);
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
      invWindow->makeInvoice(false);
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
      invWindow->makeInvoice(false);
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
      invWindow->makeInvoice(false);
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
      dupWindow->makeInvoice(false);
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
      delivNoteWindow->makeInvoice(false);

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
      goodsNoteWindow->makeInvoice(false);

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


void MainWindow::findInvoicePdf() {

    QDesktopServices::openUrl(QUrl(sett().getPdfDir(), QUrl::TolerantMode));
  //  QString fileName = QFileDialog::getOpenFileName(this,
  //  tr("Wybierz fakturę / dokument magazynu"), sett().getPdfDir(), tr("Image Files (*.pdf)"));
}


void MainWindow::checkDateRange(const QDate &date) {

   if (date.year() > QDate::currentDate().year()) {

       QMessageBox::information(this,"Filtr faktur","Rok dla wyszukiwanej faktury nie powinien być większy niż aktualny.");

          // e.g. casting to the class you know its connected with
          QDateEdit* dateEd = qobject_cast<QDateEdit*>(sender());
          if( dateEd != NULL )
          {
             dateEd->setDate(QDate::currentDate());
          }
   }
}


void MainWindow::noteDownTask(const QDate &date) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  //is automatically set to 0 when the referenced object is destroyed
  QPointer<Organizer> organizer = new Organizer(ui->todayExercise, date);

  if (organizer.isNull())
      delete organizer;

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


  QSettings settings("elinux", "qfaktury");

  settings.beginGroup("backup_settings");
  bool backupPathSett = !settings.value("backup_path").toString().isEmpty() &&
                        !settings.value("backup_path").toString().isNull();

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

  if (backupPathSett) {
    directoryComboBox = new QLineEdit(
        QDir::toNativeSeparators(settings.value("backup_path").toString()));
    QString checkSlashPath = directoryComboBox->text();
    if (!checkSlashPath.endsWith('/'))
      checkSlashPath += '/';
    QStringRef fileName(&checkSlashPath, checkSlashPath.lastIndexOf('/') + 1,
                        checkSlashPath.lastIndexOf('.') - 1);
    fileComboBox->setText(fileName.toString());
  } else {
    directoryComboBox =
        new QLineEdit(QDir::toNativeSeparators(QDir::currentPath()));
  }

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
  settings.endGroup();

  qDebug() << sett().fileName();
}

void MainWindow::intervalBackup() {

  QSettings settings("elinux", "qfaktury");

  settings.beginGroup("backup_settings");
  QString timeString = settings.value("backup_interval").toString();
  timeString.chop(1);
  int timeInt = timeString.toInt();

  QChar periodTimeSymb = settings.value("backup_interval").toString().back();


  if (!settings.value("lastBackupDate").toString().isEmpty() &&
      !settings.value("lastBackupDate").toString().isEmpty()) {
    if (periodTimeSymb == 'D' && (settings.value("lastBackupDate").toInt() <
                                  QDate::currentDate().dayOfYear() - timeInt))
      createBackupWithoutGUI();
    else if (periodTimeSymb == 'W' &&
             (settings.value("lastBackupDate").toInt() <
              QDate::currentDate().dayOfYear() - (timeInt * 7)))
      createBackupWithoutGUI();
    else if (periodTimeSymb == 'M' &&
             settings.value("lastBackupDate").toInt() <
                 (QDate::currentDate().dayOfYear() - (timeInt * 31)))
      createBackupWithoutGUI();
    else
      createBackupWithoutGUI(); // It's sure that will be in minutes or hours
                                // then from QTimer connection
  } else {
    createBackupWithoutGUI(); // just create backup. Needed if user starts
                              // qfaktury first time after newly added features
  }

  settings.setValue("lastBackupDate", QDate::currentDate().dayOfYear());
  settings.endGroup();
}

QString MainWindow::whichBackupPath() {

  QSettings settings("elinux", "qfaktury");

  settings.beginGroup("backup_settings");
  qDebug() << "backup_path in whichBackupPath function: " << QDir::toNativeSeparators(settings.value("backup_path").toString());
  if (!settings.value("backup_path").toString().isEmpty() &&
          !settings.value("backup_path").toString().isNull()) {
    return settings.value("backup_path").toString();
  } else {
    return sett().getWorkingDir();
  }
  settings.endGroup();
  return sett().getWorkingDir();
}

void MainWindow::createBackupWithoutGUI() {

  QString checkPath = (whichBackupPath().endsWith('/'))
                          ? whichBackupPath()
                          : whichBackupPath() + "/";

  bool completed =
      (JlCompress::compressDir(checkPath + QString("backup.zip"),
                               sett().getWorkingDir(), true, QDir::AllDirs) &&
       JlCompress::compressFiles(checkPath + QString("backup-configs.zip"),
                                 (QStringList()
                                  << sett().fileName()
                                  << sett().fileName().left(
                                         sett().fileName().lastIndexOf("/")) +
                                         "/user.conf")));



  QSettings settings("elinux", "qfaktury");

  settings.beginGroup("backup_settings");
  qDebug() << "Saved backup path is: " << settings.value("backup_path").toString();
  if (settings.value("backup_every_time").toBool()) {
    if (completed) {


      qDebug() << "Created archive with interval in " + checkPath +
                        "backup.zip and " + checkPath + "backup-configs.zip";
      checkPath.chop(1);
      QMessageBox::information(
          this, trUtf8("Tworzenie kopii zapasowej"),
          "Stworzenie kopii zapasowej zakończyło się sukcesem! Zostało stworzone w ścieżce: \"" + checkPath + "\"");

    } else {

        qDebug() << "Archive had not been created with interval in " + checkPath +
                        "backup.zip and " + checkPath + "backup-configs.zip";
      checkPath.chop(1);
      QMessageBox::warning(
          this, "Tworzenie kopii zapasowej",
          "Stworzenie kopii zapasowej zakończyło "
          "się niepowodzeniem. Sprawdź, czy masz uprawnienia "
          "do odczytu i zapisu w wybranym folderze. Upewnij się także, "
          "że ścieżka: \"" +
              checkPath + "\" istnieje.");
    }
  } else {

    if (completed)
      qDebug() << "Created archive with interval in " + checkPath +
                      "backup.zip and " + checkPath + "backup-configs.zip";
    else
      qDebug() << "Archive had not been created with interval in " + checkPath +
                      "backup.zip and " + checkPath + "backup-configs.zip";
  }

  settings.endGroup();
}

void MainWindow::choosePathBackup() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  QString directory =
      QDir::toNativeSeparators(QFileDialog::getExistingDirectory(
          this, tr("Find Files"), sett().getWorkingDir()));

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


void MainWindow::openJPKGenerator() {

    qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

    //is automatically set to 0 when the referenced object is destroyed
    QPointer<Saftfile> saftfileWindow = new Saftfile();

    if (saftfileWindow.isNull())
        delete saftfileWindow;
}

// methods that will put into new class

void MainWindow::createFirstWinCsv() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  sett().beginGroup("csv_settings");
  bool csvPathSett = !sett().value("csv_path").toString().isEmpty() &&
                     !sett().value("csv_path").toString().isNull();

  QPushButton *browseButton =
      new QPushButton(trUtf8("&Szukaj katalogu..."), this);
  connect(browseButton, &QAbstractButton::clicked, this,
          &MainWindow::choosePathCsv);

  QPushButton *okButton = new QPushButton(trUtf8("&Zatwierdź"), this);
  connect(okButton, &QAbstractButton::clicked, this,
          &MainWindow::createCsvFiles);

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

  if (csvPathSett) {
    directoryComboBox = new QLineEdit(
        QDir::toNativeSeparators(sett().value("csv_path").toString()));
  } else {
    directoryComboBox =
        new QLineEdit(QDir::toNativeSeparators(sett().getCSVDir()));
  }

  QGridLayout *mainLayout = new QGridLayout;
  mainLayout->addWidget(new QLabel(trUtf8("Podaj ścieżkę docelową:")), 0, 0);
  mainLayout->addWidget(directoryComboBox, 0, 1, 1, 2);
  mainLayout->addWidget(browseButton, 2, 2);
  mainLayout->addWidget(okButton, 4, 2);
  mainLayout->addWidget(cancButton, 4, 3);

  windBack = new QWidget();
  windBack->setLayout(mainLayout);

  windBack->setWindowTitle(trUtf8("Podaj miejsce dla plików csv"));
  const QRect screenGeometry = QApplication::desktop()->screenGeometry(this);
  windBack->resize(screenGeometry.width() / 2, screenGeometry.height() / 3);

  windBack->show();
  sett().endGroup();

  qDebug() << sett().fileName();
}

void MainWindow::choosePathCsv() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  QString directory =
      QDir::toNativeSeparators(QFileDialog::getExistingDirectory(
          this, tr("Find Files"), sett().getCSVDir()));

  if (!directory.isEmpty()) {
    directoryComboBox->setText(directory);
  }
}

void MainWindow::createCsvFiles() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  bool csvPathSett = sett().value("csv_path").toString() != "";

  if (csvPathSett) {

    qDebug() << "Path csv have been set in settings";
    QDir csvDir(sett().value("csv_path").toString());
    if (!csvDir.exists())
      csvDir.mkpath(sett().value("csv_path").toString());

  } else {

    qDebug() << "Default csv path will be used";
    QDir csvDir(sett().getCSVDir());
    if (!csvDir.exists())
      csvDir.mkpath(sett().getCSVDir());
  }

  if (directoryComboBox->text().isEmpty()) {

    QMessageBox::warning(windBack, trUtf8("Brakująca ścieżka"),
                         trUtf8("Nazwa dla archiwum oraz ścieżka dla "
                                "tworzonego archiwum nie może być pominięta"));

  } else {

    qDebug() << "directory path for csv in new window has not been empty";
    qDebug() << "If export_buyers in qfaktury.conf is set: "
             << sett().value("export_buyers").toBool();
    qDebug() << "If export_goods in qfaktury.conf is set: "
             << sett().value("export_goods").toBool();
    qDebug() << "If export_invoices in qfaktury.conf is set: "
             << sett().value("export_invoices").toBool();
    qDebug() << "If export_warehouses in qfaktury.conf is set: "
             << sett().value("export_warehouses").toBool();

    sett().beginGroup("csv_settings");
    createSellersCsvFiles();
    if (sett().value("export_buyers").toBool())
      createBuyersCsvFiles();
    if (sett().value("export_goods").toBool())
      createProductsCsvFiles();
    if (sett().value("export_invoices").toBool())
      createInvoicesCsvFiles(QDate(QDate::currentDate().year(), 1, 1),
                             QDate(QDate::currentDate().year(), 12, 31));
    if (sett().value("export_warehouses").toBool())
      createWareCsvFiles(QDate(QDate::currentDate().year(), 1, 1),
                         QDate(QDate::currentDate().year(), 12, 31));
    sett().endGroup();

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

void MainWindow::createBuyersCsvFiles() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  if (!idCvsBuyer.isEmpty())
    idCvsBuyer.clear();

  QString checkSlashPath = directoryComboBox->text();
  if (!checkSlashPath.endsWith('/'))
    checkSlashPath += '/';
  QFile csv(checkSlashPath + "/kontrahenci_buyers.csv");
  qDebug() << "Buyers csv path: " << csv.fileName();
  csv.open(QFile::WriteOnly | QFile::Text);
  csv.resize(0);

  QTextStream in(&csv);

  QString row = QString();
  if (sett().value("csv_format").toString() == "EU")
    row = "id_klient,typ,nazwa,ulica,miejscowosc,kod_pocztowy,tel,email,fax,"
          "NIP,nazwa_banku,nr_konta,bic_swift,krs,strona_www";
  else
    row = "id_klient;typ;nazwa;ulica;miejscowosc;kod_pocztowy;tel;email;fax;"
          "NIP;nazwa_banku;nr_konta;bic_swift;krs;strona_www";

  in << row << endl;

  QVector<BuyerData> buyersXml = dl->buyersSelectAllData();

  for (int i = 0; i < buyersXml.size(); ++i) {

    QString type = (buyersXml.at(i).type != "") ? buyersXml.at(i).type : "null";
    QString name = (buyersXml.at(i).name != "") ? buyersXml.at(i).name : "null";
    QString address =
        (buyersXml.at(i).address != "") ? buyersXml.at(i).address : "null";
    QString city =
        (buyersXml.at(i).place != "") ? buyersXml.at(i).place : "null";
    QString code = (buyersXml.at(i).code != "") ? buyersXml.at(i).code : "null";
    QString tel =
        (buyersXml.at(i).phone != "") ? buyersXml.at(i).phone : "null";
    QString email =
        (buyersXml.at(i).email != "") ? buyersXml.at(i).email : "null";
    QString fax = (buyersXml.at(i).fax != "") ? buyersXml.at(i).fax : "null";
    QString tic = (buyersXml.at(i).tic != "") ? buyersXml.at(i).tic : "null";
    QString bankname =
        (buyersXml.at(i).bank != "") ? buyersXml.at(i).bank : "null";
    QString account_nr =
        (buyersXml.at(i).account != "") ? buyersXml.at(i).account : "null";
    QString swift_bic =
        (buyersXml.at(i).swift != "") ? buyersXml.at(i).swift : "null";
    QString krs = (buyersXml.at(i).krs != "") ? buyersXml.at(i).krs : "null";
    QString www = (buyersXml.at(i).www != "") ? buyersXml.at(i).www : "null";

    QString next_row = QString();

    qDebug() << "insert tic to idCvsBuyer: " << buyersXml.at(i).tic;
    QString buyTic = buyersXml.at(i).tic;
    idCvsBuyer.insert(
        buyTic.remove(QChar('-')),
        QString::number(
            i +
            1)); // according to the tic, because the number is always unique
    // invData.custTic.remove('-'), because of validation choice option. When
    // validation on data is unchecked, users can put tic into app without '-'
    // characters

    if (sett().value("csv_format").toString() == "EU")
      next_row = QString::number(i + 1) + "," + type + "," + name + "," +
                 address + "," + city + "," + code + "," + tel + "," + email +
                 "," + fax + "," + tic + "," + bankname + "," + account_nr +
                 "," + swift_bic + "," + krs + "," + www;
    else
      next_row = QString::number(i + 1) + ";" + type + ";" + name + ";" +
                 address + ";" + city + ";" + code + ";" + tel + ";" + email +
                 ";" + fax + ";" + tic + ";" + bankname + ";" + account_nr +
                 ";" + swift_bic + ";" + krs + ";" + www;

    in << next_row << endl;
  }

  csv.close();
}

void MainWindow::createProductsCsvFiles() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  if (!idCvsProducts.isEmpty())
    idCvsProducts.clear();

  QString checkSlashPath = directoryComboBox->text();
  if (!checkSlashPath.endsWith('/'))
    checkSlashPath += '/';
  QFile csv(checkSlashPath + "/produkty_goods.csv");
  qDebug() << "Products csv path: " << csv.fileName();
  csv.open(QFile::WriteOnly | QFile::Text);
  csv.resize(0);

  QTextStream in(&csv);

  QString row = QString();
  if (sett().value("csv_format").toString() == "EU")
    row = "id_produkt,typ,nazwa,vat,opis,kod,pkwiu,jednostka,netto1,netto2,"
          "netto3,netto4";
  else
    row = "id_produkt;typ;nazwa;vat;opis;kod;pkwiu;jednostka;netto1;netto2;"
          "netto3;netto4";

  in << row << endl;

  QVector<ProductData> productsXml = dl->productsSelectAllData();

  for (int i = 0; i < productsXml.size(); ++i) {

    QString type =
        (productsXml.at(i).type != "") ? productsXml.at(i).type : "null";
    QString name =
        (productsXml.at(i).name != "") ? productsXml.at(i).name : "null";
    QString vat = (QString::number(productsXml.at(i).vat) != "")
                      ? QString::number(productsXml.at(i).vat)
                      : "null";
    QString desc =
        (productsXml.at(i).desc != "") ? productsXml.at(i).desc : "null";
    QString code =
        (productsXml.at(i).code != "") ? productsXml.at(i).code : "null";
    QString pkwiu =
        (productsXml.at(i).pkwiu != "") ? productsXml.at(i).pkwiu : "null";
    QString quantity_type = (productsXml.at(i).quanType != "")
                                ? productsXml.at(i).quanType
                                : "null";
    QString net1 =
        (sett().numberToString(productsXml.at(i).prices[0], 'f', 2) != "")
            ? sett().numberToString(productsXml.at(i).prices[0], 'f', 2)
            : "null";
    QString net2 =
        (sett().numberToString(productsXml.at(i).prices[1], 'f', 2) != "")
            ? sett().numberToString(productsXml.at(i).prices[1], 'f', 2)
            : "null";
    QString net3 =
        (sett().numberToString(productsXml.at(i).prices[2], 'f', 2) != "")
            ? sett().numberToString(productsXml.at(i).prices[2], 'f', 2)
            : "null";
    QString net4 =
        (sett().numberToString(productsXml.at(i).prices[3], 'f', 2) != "")
            ? sett().numberToString(productsXml.at(i).prices[3], 'f', 2)
            : "null";

    if (!productsXml.at(i).code.isEmpty() && !productsXml.at(i).code.isNull()) {
      idCvsProducts.insert(productsXml.at(i).code, QString::number(i + 1));
      qDebug() << "productsXml.at(i).code: " << productsXml.at(i).code;
      qDebug() << "idCvsProducts.count(): " << idCvsProducts.count();
    } else {
      idCvsProducts.insert(
          productsXml.at(i).name,
          QString::number(
              i + 1)); // sometimes there is no code given for some product
      qDebug() << "productsXml.at(i).name: " << productsXml.at(i).name;
      qDebug() << "idCvsProducts.count(): " << idCvsProducts.count();
    }

    QString next_row = QString();

    if (sett().value("csv_format").toString() == "EU")
      next_row = QString::number(i + 1) + "," + type + "," + name + "," + vat +
                 "," + desc + "," + code + "," + pkwiu + "," + quantity_type +
                 "," + net1 + "," + net2 + "," + net3 + "," + net4;
    else
      next_row = QString::number(i + 1) + ";" + type + ";" + name + ";" + vat +
                 ";" + desc + ";" + code + ";" + pkwiu + ";" + quantity_type +
                 ";" + net1 + ";" + net2 + ";" + net3 + ";" + net4;

    in << next_row << endl;
  }

  csv.close();
}

void MainWindow::createSellersCsvFiles() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  if (!idCvsSeller.isEmpty())
    idCvsSeller.clear();

  QString checkSlashPath = directoryComboBox->text();
  if (!checkSlashPath.endsWith('/'))
    checkSlashPath += '/';
  QFile csv(checkSlashPath + "/sprzedawcy_sellers.csv");
  qDebug() << "Sellers csv path: " << csv.fileName();
  csv.open(QFile::WriteOnly | QFile::Text);
  csv.resize(0);

  QTextStream in(&csv);

  QString row = QString();
  if (sett().value("csv_format").toString() == "EU")
    row = "id_sprzedawca,nazwa,adres,miejscowosc,kod_pocztowy,oddzial,NIP,"
          "REGON,KRS,nazwa_banku,nr_konta,SWIFT_BIC,tel,fax,email,www";
  else
    row = "id_sprzedawca;nazwa;adres;miejscowosc;kod_pocztowy;oddzial;NIP;"
          "REGON;KRS;nazwa_banku;nr_konta;SWIFT_BIC;tel;fax;email;www";

  in << row << endl;

  QString next_row = QString();

  QSettings settings("elinux", "user");

  QString name = (settings.value("name").toString() != "")
                     ? settings.value("name").toString()
                     : "null";
  QString address = (settings.value("address").toString() != "")
                        ? settings.value("address").toString()
                        : "null";
  QString city = (settings.value("city").toString() != "")
                     ? settings.value("city").toString()
                     : "null";
  QString zip = (settings.value("zip").toString() != "")
                    ? settings.value("zip").toString()
                    : "null";
  QString tic = (settings.value("tic").toString() != "")
                    ? settings.value("tic").toString()
                    : "null";
  QString regon = (settings.value("regon").toString() != "")
                      ? settings.value("regon").toString()
                      : "null";
  QString krs = (settings.value("krs").toString() != "")
                    ? settings.value("krs").toString()
                    : "null";
  QString bankname = (settings.value("bank").toString() != "")
                         ? settings.value("bank").toString()
                         : "null";
  QString account = (settings.value("account").toString() != "")
                        ? settings.value("account").toString()
                        : "null";
  QString swift_bic = (settings.value("swift").toString() != "")
                          ? settings.value("swift").toString()
                          : "null";
  QString tel = (settings.value("phone").toString() != "")
                    ? settings.value("phone").toString()
                    : "null";
  QString fax = (settings.value("fax").toString() != "")
                    ? settings.value("fax").toString()
                    : "null";
  QString email = (settings.value("email").toString() != "")
                      ? settings.value("email").toString()
                      : "null";
  QString www = (settings.value("website").toString() != "")
                    ? settings.value("website").toString()
                    : "null";

  idCvsSeller.insert(
      address,
      QString::number(
          1)); // address is the best choice, if there are other branches

  if (sett().value("csv_format").toString() == "EU")
    next_row = QString::number(1) + "," + name + "," + address + "," + city +
               "," + zip + ",glowny," + tic + "," + regon + "," + krs + "," +
               bankname + "," + account + "," + swift_bic + "," + tel + "," +
               fax + "," + email + "," + www;
  else
    next_row = QString::number(1) + ";" + name + ";" + address + ";" + city +
               ";" + zip + ";glowny;" + tic + ";" + regon + ";" + krs + ";" +
               bankname + ";" + account + ";" + swift_bic + ";" + tel + ";" +
               fax + ";" + email + ";" + www;

  in << next_row << endl;

  for (int i = 1; i < settings.value("sellerCount").toInt(); ++i) {

    QSettings setts("elinux", "user");
    setts.beginGroup("seller" + QString::number(i));

    QString name = (setts.value("name").toString() != "")
                       ? setts.value("name").toString()
                       : "null";
    QString address = (setts.value("address").toString() != "")
                          ? setts.value("address").toString()
                          : "null";
    QString city = (setts.value("city").toString() != "")
                       ? setts.value("city").toString()
                       : "null";
    QString zip = (setts.value("zip").toString() != "")
                      ? setts.value("zip").toString()
                      : "null";
    QString tic = (setts.value("tic").toString() != "")
                      ? setts.value("tic").toString()
                      : "null";
    QString regon = (setts.value("regon").toString() != "")
                        ? setts.value("regon").toString()
                        : "null";
    QString krs = (setts.value("krs").toString() != "")
                      ? setts.value("krs").toString()
                      : "null";
    QString bankname = (setts.value("bank").toString() != "")
                           ? setts.value("bank").toString()
                           : "null";
    QString account = (setts.value("account").toString() != "")
                          ? setts.value("account").toString()
                          : "null";
    QString swift_bic = (setts.value("swift").toString() != "")
                            ? setts.value("swift").toString()
                            : "null";
    QString tel = (setts.value("phone").toString() != "")
                      ? setts.value("phone").toString()
                      : "null";
    QString fax = (setts.value("fax").toString() != "")
                      ? setts.value("fax").toString()
                      : "null";
    QString email = (setts.value("email").toString() != "")
                        ? setts.value("email").toString()
                        : "null";
    QString www = (setts.value("website").toString() != "")
                      ? setts.value("website").toString()
                      : "null";

    idCvsSeller.insert(address, QString::number(i + 1)); // address is the best
                                                         // choice, if there are
                                                         // other branches
                                                         // (unique value is
                                                         // needed)

    if (sett().value("csv_format").toString() == "EU")
      next_row = QString::number(i + 1) + "," + name + "," + address + "," +
                 city + "," + zip + ",poboczny," + tic + "," + regon + "," +
                 krs + "," + bankname + "," + account + "," + swift_bic + "," +
                 tel + "," + fax + "," + email + "," + www;
    else
      next_row = QString::number(i + 1) + ";" + name + ";" + address + ";" +
                 city + ";" + zip + ";poboczny;" + tic + ";" + regon + ";" +
                 krs + ";" + bankname + ";" + account + ";" + swift_bic + ";" +
                 tel + ";" + fax + ";" + email + ";" + www;

    in << next_row << endl;
    setts.endGroup();
  }

  settings.endGroup();
  csv.close();
}

void MainWindow::createInvoicesCsvFiles(QDate from, QDate to) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  if (!idCvsInvoices.isEmpty())
    idCvsInvoices.clear();

  QString checkSlashPath = directoryComboBox->text();
  if (!checkSlashPath.endsWith('/'))
    checkSlashPath += '/';
  QFile csv(checkSlashPath + "/faktury_invoices.csv");
  csv.open(QFile::WriteOnly | QFile::Text);
  csv.resize(0);

  QTextStream in(&csv);

  QString row = QString();
  if (sett().value("csv_format").toString() == "EU")
    row = "id_faktura,typ,data_sprzedazy,data_duplikatu,data_wystawienia,data_"
          "zaplaty,id_klient,id_sprzedawca,id_produkt1,id_produkt2,id_produkt3,"
          "id_produkt4,ilosc1,netto1,brutto1,ilosc2,netto2,brutto2,ilosc3,"
          "netto3,brutto3,ilosc4,netto4,brutto4,sposob_platnosci,waluta";
  else
    row = "id_faktura;typ;data_sprzedazy;data_duplikatu,data_wystawienia;data_"
          "zaplaty;id_klient;id_sprzedawca;id_produkt1;id_produkt2;id_produkt4;"
          "id_produkt4;ilosc1;netto1;brutto1;ilosc2;netto2;brutto2;ilosc3;"
          "netto3;brutto3;ilosc4;netto4;brutto4;sposob_platnosci;waluta";

  in << row << endl;

  QVector<InvoiceData> invoicesXml = dl->invoiceSelectAllData(from, to);

  for (int i = 0; i < invoicesXml.size(); ++i) {
    InvoiceData invData = dl->invoiceSelectData(
        invoicesXml.at(i).id, getInvoiceTypeFullName(invoicesXml.at(i).type),
        true);
    QString type =
        (invoicesXml.at(i).type != "") ? invoicesXml.at(i).type : "null";
    QString sellDate =
        (invData.sellingDate.toString(sett().getDateFormat()) != "")
            ? invData.sellingDate.toString(sett().getDateFormat())
            : "null";
    QString prodDate =
        (invData.productDate.toString(sett().getDateFormat()) != "")
            ? invData.productDate.toString(sett().getDateFormat())
            : "null";
    QString duplDate = (invData.duplDate.toString(sett().getDateFormat()) != "")
                           ? invData.duplDate.toString(sett().getDateFormat())
                           : "null";
    QString payDate = (invData.liabDate.toString(sett().getDateFormat()) != "")
                          ? invData.liabDate.toString(sett().getDateFormat())
                          : "null";

    QString id_customer = (invData.custTic.remove('-') != "")
                              ? idCvsBuyer[invData.custTic.remove('-')]
                              : "null";
    // invData.custTic.remove('-'), because of validation choice option. When
    // validation on data is unchecked, users can put tic into app without '-'
    // characters

    qDebug() << "invData.custTic: " << invData.custTic;
    qDebug() << "invData.sellerAddress: " << invData.sellerAddress;
    QString id_seller = (invData.sellerAddress != "")
                            ? idCvsSeller[invData.sellerAddress]
                            : "null";
    QStringList id_products = QStringList();

    QString quantity1 = QString();
    QString nett1 = QString();
    QString gross1 = QString();
    QString quantity2 = QString();
    QString nett2 = QString();
    QString gross2 = QString();
    QString quantity3 = QString();
    QString nett3 = QString();
    QString gross3 = QString();
    QString quantity4 = QString();
    QString nett4 = QString();
    QString gross4 = QString();

    qDebug() << "invData.products.count(): "
             << QString::number(invData.products.count());
    for (int k = 0; k < invData.products.count(); k++) {
      qDebug() << "idCvsProducts[invData.products[k].code]: "
               << idCvsProducts[invData.products[k].code];
      qDebug() << "idCvsProducts[invData.products[k].name]: "
               << idCvsProducts[invData.products[k].name];
      qDebug() << "invData.products[k].code: " << invData.products[k].code;
      qDebug() << "invData.products[k].name: " << invData.products[k].name;
      if (idCvsProducts[invData.products[k].code] != "") {
        qDebug() << "id_products for code: "
                 << idCvsProducts[invData.products[k].code];
        id_products << ((idCvsProducts[invData.products[k].code] != "")
                            ? idCvsProducts[invData.products[k].code]
                            : "null");
      } else {
        qDebug() << "id_products for name: "
                 << idCvsProducts[invData.products[k].name];
        id_products << ((idCvsProducts[invData.products[k].name] != "")
                            ? idCvsProducts[invData.products[k].name]
                            : "null");
      }

      if (k == 0) {
        quantity1 = sett().numberToString(invData.products[k].quantity, 'f', 2);
        nett1 = sett().numberToString(invData.products[k].nett, 'f', 2);
        gross1 = sett().numberToString(invData.products[k].gross, 'f', 2);
      }
      if (k == 1) {
        quantity2 = sett().numberToString(invData.products[k].quantity, 'f', 2);
        nett2 = sett().numberToString(invData.products[k].nett, 'f', 2);
        gross2 = sett().numberToString(invData.products[k].gross, 'f', 2);
      }
      if (k == 2) {
        quantity3 = sett().numberToString(invData.products[k].quantity, 'f', 2);
        nett3 = sett().numberToString(invData.products[k].nett, 'f', 2);
        gross3 = sett().numberToString(invData.products[k].gross, 'f', 2);
      }
      if (k == 3) {
        quantity4 = sett().numberToString(invData.products[k].quantity, 'f', 2);
        nett4 = sett().numberToString(invData.products[k].nett, 'f', 2);
        gross4 = sett().numberToString(invData.products[k].gross, 'f', 2);
      }

      if (k == invData.products.count() - 1) { // if we are at the end of loop
        if (k < 3) { // if number of last transaction was less than 3
          for (int j = 4 - (3 - k); j < 4;
               j++) { // we want fill values with "null", only if there aren't 4
                      // transaction until now
            id_products << "null"; // we have now empty values for values taken
                                   // from last transaction number to number 4
            qDebug() << "id_products for null: null";
          }
        }
      }
    }

    if (quantity1.isEmpty() && nett1.isEmpty() && gross1.isEmpty()) {
      quantity1 = "null";
      nett1 = "null";
      gross1 = "null";
    }
    if (quantity2.isEmpty() && nett2.isEmpty() && gross2.isEmpty()) {
      quantity2 = "null";
      nett2 = "null";
      gross2 = "null";
    }
    if (quantity3.isEmpty() && nett3.isEmpty() && gross3.isEmpty()) {
      quantity3 = "null";
      nett3 = "null";
      gross3 = "null";
    }
    if (quantity4.isEmpty() && nett4.isEmpty() && gross4.isEmpty()) {
      quantity4 = "null";
      nett4 = "null";
      gross4 = "null";
    }

    QString paymentMethod =
        (!invData.paymentType.isEmpty() && !invData.paymentType.isNull())
            ? invData.paymentType
            : "null";
    QString currency =
        (!invData.currencyType.isEmpty() && !invData.currencyType.isNull())
            ? invData.currencyType
            : "null";

    idCvsInvoices.insert(
        invoicesXml.at(i).id,
        QString::number(i + 1)); // because name of filename is always unique

    QString next_row = QString();

    if (sett().value("csv_format").toString() == "EU")
      next_row =
          QString::number(i + 1) + "," + type + "," + sellDate + "," +
          duplDate + "," + prodDate + "," + payDate + "," + id_customer + "," +
          id_seller + "," + id_products.at(0) + "," + id_products.at(1) + "," +
          id_products.at(2) + "," + id_products.at(3) + "," + quantity1 + "," +
          nett1 + "," + gross1 + "," + quantity2 + "," + nett2 + "," + gross2 +
          "," + quantity3 + "," + nett3 + "," + gross3 + "," + quantity4 + "," +
          nett4 + "," + gross4 + "," + paymentMethod + "," + currency;
    else
      next_row =
          QString::number(i + 1) + ";" + type + ";" + sellDate + ";" +
          duplDate + ";" + prodDate + ";" + payDate + ";" + id_customer + ";" +
          id_seller + ";" + id_products.at(0) + ";" + id_products.at(1) + ";" +
          id_products.at(2) + ";" + id_products.at(3) + ";" + quantity1 + ";" +
          nett1 + ";" + gross1 + ";" + quantity2 + ";" + nett2 + ";" + gross2 +
          ";" + quantity3 + ";" + nett3 + ";" + gross3 + ";" + quantity4 + ";" +
          nett4 + ";" + gross4 + "," + paymentMethod + ";" + currency;

    in << next_row << endl;
  }

  csv.close();
}

void MainWindow::createWareCsvFiles(QDate from, QDate to) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  if (!idCvsWarehouses.isEmpty())
    idCvsWarehouses.clear();

  QString checkSlashPath = directoryComboBox->text();
  if (!checkSlashPath.endsWith('/'))
    checkSlashPath += '/';
  QFile csv(checkSlashPath + "/magazyny_warehouses.csv");
  csv.open(QFile::WriteOnly | QFile::Text);
  csv.resize(0);

  QTextStream in(&csv);

  QString row = QString();
  if (sett().value("csv_format").toString() == "EU")
    row = "id_magazyn,typ,data_sprzedazy,data_duplikatu,data_wydania_towaru,"
          "data_przyjecia_towaru,miejsce_odbioru_towaru,miejsce_wydania_towaru,"
          "dzial_kosztu,id_klient,id_sprzedawca,id_produkt1,id_produkt2,id_"
          "produkt3,id_produkt4,ilosc1,netto1,wydana_ilosc1,wymagana_ilosc1,"
          "ilosc2,netto2,wydana_ilosc2,wymagana_ilosc2,ilosc3,netto3,wydana_"
          "ilosc3,wymagana_ilosc3,ilosc4,netto4,wydana_ilosc4,wymagana_ilosc4,"
          "sposob_platnosci";
  else
    row = "id_magazyn;typ;data_sprzedazy;data_duplikatu;data_wydania_towaru;"
          "data_przyjecia_towaru;miejsce_odbioru_towaru;miejsce_wydania_towaru;"
          "dzial_kosztu;id_klient;id_sprzedawca;id_produkt1;id_produkt2;id_"
          "produkt3;id_produkt4;ilosc1;netto1;wydana_ilosc1;wymagana_ilosc1;"
          "ilosc2;netto2;wydana_ilosc2;wymagana_ilosc2;ilosc3;netto3;wydana_"
          "ilosc3;wymagana_ilosc3;ilosc4;netto4;wydana_ilosc4;wymagana_ilosc4;"
          "sposob_platnosci";

  in << row << endl;

  QVector<WarehouseData> wareXml = dl->warehouseSelectAllData(from, to);

  for (int i = 0; i < wareXml.size(); ++i) {
    WarehouseData invData = dl->warehouseSelectData(
        wareXml.at(i).id, getInvoiceTypeFullName(wareXml.at(i).type), true);
    QString type = (wareXml.at(i).type != "") ? wareXml.at(i).type : "null";
    QString sellDate =
        (invData.sellingDate.toString(sett().getDateFormat()) != "")
            ? invData.sellingDate.toString(sett().getDateFormat())
            : "null";
    QString prodDate =
        (invData.productDate.toString(sett().getDateFormat()) != "")
            ? invData.productDate.toString(sett().getDateFormat())
            : "null";
    QString duplDate = (invData.duplDate.toString(sett().getDateFormat()) != "")
                           ? invData.duplDate.toString(sett().getDateFormat())
                           : "null";
    QString giveDate =
        (invData.goodFromDate.toString(sett().getDateFormat()) != "")
            ? invData.goodFromDate.toString(sett().getDateFormat())
            : "null";
    QString takeDate =
        (invData.goodToDate.toString(sett().getDateFormat()) != "")
            ? invData.goodToDate.toString(sett().getDateFormat())
            : "null";
    QString givePlace =
        (invData.goodFromPlace != "") ? invData.goodFromPlace : "null";
    QString takePlace =
        (invData.goodToPlace != "") ? invData.goodToPlace : "null";
    QString departCost =
        (invData.departmentCost != "") ? invData.departmentCost : "null";

    QString id_customer = (invData.custTic.remove('-') != "")
                              ? idCvsBuyer[invData.custTic.remove('-')]
                              : "null";
    // invData.custTic.remove('-'), because of validation choice option. When
    // validation on data is unchecked, users can put tic into app without '-'
    // characters

    qDebug() << "invData.custTic: " << invData.custTic;
    qDebug() << "invData.sellerAddress: " << invData.sellerAddress;
    QString id_seller = (invData.sellerAddress != "")
                            ? idCvsSeller[invData.sellerAddress]
                            : "null";
    QStringList id_products = QStringList();

    QString quantity1 = QString();
    QString nett1 = QString();
    QString givAm1 = QString();
    QString reqAm1 = QString();
    QString quantity2 = QString();
    QString nett2 = QString();
    QString givAm2 = QString();
    QString reqAm2 = QString();
    QString quantity3 = QString();
    QString nett3 = QString();
    QString givAm3 = QString();
    QString reqAm3 = QString();
    QString quantity4 = QString();
    QString nett4 = QString();
    QString givAm4 = QString();
    QString reqAm4 = QString();

    qDebug() << "invData.products.count(): "
             << QString::number(invData.products.count());
    for (int k = 0; k < invData.products.count(); k++) {
      qDebug() << "idCvsProducts[invData.products[k].code]: "
               << idCvsProducts[invData.products[k].code];
      qDebug() << "idCvsProducts[invData.products[k].name]: "
               << idCvsProducts[invData.products[k].name];
      qDebug() << "invData.products[k].code: " << invData.products[k].code;
      qDebug() << "invData.products[k].name: " << invData.products[k].name;
      if (idCvsProducts[invData.products[k].code] != "") {
        qDebug() << "id_products for code: "
                 << idCvsProducts[invData.products[k].code];
        id_products << ((idCvsProducts[invData.products[k].code] != "")
                            ? idCvsProducts[invData.products[k].code]
                            : "null");
      } else {
        qDebug() << "id_products for name: "
                 << idCvsProducts[invData.products[k].name];
        id_products << ((idCvsProducts[invData.products[k].name] != "")
                            ? idCvsProducts[invData.products[k].name]
                            : "null");
      }

      if (k == 0) {
        quantity1 = sett().numberToString(invData.products[k].quantity, 'f', 2);
        nett1 = sett().numberToString(invData.products[k].nett, 'f', 2);
        givAm1 =
            sett().numberToString(invData.products[k].givedOutAmount, 'f', 2);
        reqAm1 =
            sett().numberToString(invData.products[k].requiredAmount, 'f', 2);
      }
      if (k == 1) {
        quantity2 = sett().numberToString(invData.products[k].quantity, 'f', 2);
        nett2 = sett().numberToString(invData.products[k].nett, 'f', 2);
        givAm2 =
            sett().numberToString(invData.products[k].givedOutAmount, 'f', 2);
        reqAm2 =
            sett().numberToString(invData.products[k].requiredAmount, 'f', 2);
      }
      if (k == 2) {
        quantity3 = sett().numberToString(invData.products[k].quantity, 'f', 2);
        nett3 = sett().numberToString(invData.products[k].nett, 'f', 2);
        givAm3 =
            sett().numberToString(invData.products[k].givedOutAmount, 'f', 2);
        reqAm3 =
            sett().numberToString(invData.products[k].requiredAmount, 'f', 2);
      }
      if (k == 3) {
        quantity4 = sett().numberToString(invData.products[k].quantity, 'f', 2);
        nett4 = sett().numberToString(invData.products[k].nett, 'f', 2);
        givAm4 =
            sett().numberToString(invData.products[k].givedOutAmount, 'f', 2);
        reqAm4 =
            sett().numberToString(invData.products[k].requiredAmount, 'f', 2);
      }

      if (k == invData.products.count() - 1) { // if we are at the end of loop
        if (k < 3) { // if number of last transaction was less than 3
          for (int j = 4 - (3 - k); j < 4;
               j++) { // we want fill values with "null", only if there aren't 4
                      // transaction until now
            id_products << "null"; // we have now empty values for values taken
                                   // from last transaction number to number 4
            qDebug() << "id_products for null: null";
          }
        }
      }
    }

    if (quantity1.isEmpty() && nett1.isEmpty() && givAm1.isEmpty() &&
        reqAm1.isEmpty()) {
      quantity1 = "null";
      nett1 = "null";
      givAm1 = "null";
      reqAm1 = "null";
    }
    if (quantity2.isEmpty() && nett2.isEmpty() && givAm2.isEmpty() &&
        reqAm2.isEmpty()) {
      quantity2 = "null";
      nett2 = "null";
      givAm2 = "null";
      reqAm2 = "null";
    }
    if (quantity3.isEmpty() && nett3.isEmpty() && givAm3.isEmpty() &&
        reqAm3.isEmpty()) {
      quantity3 = "null";
      nett3 = "null";
      givAm3 = "null";
      reqAm3 = "null";
    }
    if (quantity4.isEmpty() && nett4.isEmpty() && givAm4.isEmpty() &&
        reqAm4.isEmpty()) {
      quantity4 = "null";
      nett4 = "null";
      givAm4 = "null";
      reqAm4 = "null";
    }

    QString paymentMethod =
        (invData.paymentType != "") ? invData.paymentType : "null";
    //  QString currency = (invData.currencyType != "") ? invData.currencyType :
    //  "null";

    idCvsWarehouses.insert(
        wareXml.at(i).id,
        QString::number(i + 1)); // because name of filename is always unique

    QString next_row = QString();

    if (sett().value("csv_format").toString() == "EU")
      next_row = QString::number(i + 1) + "," + type + "," + sellDate + "," +
                 duplDate + "," + prodDate + "," + giveDate + "," + takeDate +
                 "," + givePlace + "," + takePlace + "," + departCost + "," +
                 id_customer + "," + id_seller + "," + id_products.at(0) + "," +
                 id_products.at(1) + "," + id_products.at(2) + "," +
                 id_products.at(3) + "," + quantity1 + "," + nett1 + "," +
                 givAm1 + "," + reqAm1 + "," + quantity2 + "," + nett2 + "," +
                 givAm2 + "," + reqAm2 + "," + quantity3 + "," + nett3 + "," +
                 givAm3 + "," + reqAm3 + "," + quantity4 + "," + nett4 + "," +
                 givAm4 + "," + reqAm4 + "," + paymentMethod;
    else
      next_row = QString::number(i + 1) + ";" + type + ";" + sellDate + ";" +
                 duplDate + ";" + prodDate + ";" + giveDate + ";" + takeDate +
                 ";" + givePlace + ";" + takePlace + ";" + departCost + ";" +
                 id_customer + ";" + id_seller + ";" + id_products.at(0) + ";" +
                 id_products.at(1) + ";" + id_products.at(2) + ";" +
                 id_products.at(3) + ";" + quantity1 + ";" + nett1 + ";" +
                 givAm1 + ";" + reqAm1 + ";" + quantity2 + ";" + nett2 + ";" +
                 givAm2 + ";" + reqAm2 + ";" + quantity3 + ";" + nett3 + ";" +
                 givAm3 + ";" + reqAm3 + ";" + quantity4 + ";" + nett4 + ";" +
                 givAm4 + ";" + reqAm4 + ";" + paymentMethod;

    in << next_row << endl;
  }

  csv.close();
}
