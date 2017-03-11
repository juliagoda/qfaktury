
#include <QTextCodec>
#include <QMessageBox>
#include <QApplication>
#include <QEvent>
#include <QMenu>
#include <QUrl>
#include <QtXml/qdom.h>
#include <QTextStream>
#include <QtDebug>
#include <QDesktopServices>
#include <QProcess>
#include <QTimer>
#include <QPrintPreviewDialog>

#include "Setting.h"
#include "User.h"
#include "Goods.h"
#include "Invoice.h"
#include "Correction.h"
#include "Duplicate.h"
#include "InvoiceGross.h"
#include "CorrectGross.h"
#include "Bill.h"
#include "Buyers.h"
#include "DateWidgetItem.h"
#include "Const.h"
#include "MainWindow.h"

#include "XmlDataLayer.h"

MainWindow* MainWindow::m_instance = nullptr;

/** Constructor
 */

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    m_instance = this;
    init();
}

MainWindow* MainWindow::instance()
{
    return m_instance;
}

/** Destructor
 */

MainWindow::~MainWindow() {

	saveAllSett();

    if (timer != 0) timer = 0;
    delete timer;

    if (dl != 0) dl = 0;
    delete dl;

    if (ui != 0) ui = 0;
    delete ui;

    m_instance = nullptr;


    if (plugActions.count() > 0) {

        foreach (QAction* plugAct_single, plugActions) {

            if (plugAct_single != 0) plugAct_single = 0;
            delete plugAct_single;
       }
    }
}

/**
 * init() method
 */

void MainWindow::init() {

	// first run
    if (firstRun()) {

        // towary/uslugi - wymiary
        ui->tableT->setColumnWidth(0, 50);
        ui->tableT->setColumnWidth(1, 140);
        ui->tableT->setColumnWidth(3, 40);
        ui->tableT->setColumnWidth(4, 60);
        ui->tableT->setColumnWidth(5, 50);
        ui->tableT->setColumnWidth(6, 55); // netto1
        ui->tableT->setColumnWidth(7, 55); // netto2
        ui->tableT->setColumnWidth(8, 55); // netto3
        ui->tableT->setColumnWidth(9, 55); // netto4
        ui->tableT->setColumnWidth(10, 55);

        setupDir();
		saveAllSettAsDefault();

        QMessageBox::information(this, "QFaktury", trUtf8("Program zawiera konwersję walut w oknie edycji faktury lub podczas jej tworzenia. By jej używać, powinieneś mieć dostęp do internetu oraz poprawnie ustawiony czas systemowy."));
        QMessageBox::information(this, "QFaktury", trUtf8("W przypadku zmiany lokalizacji systemu sposób formatowania liczb może się zmienić. Efekt ten może być widoczny po restarcie programu."));


        if (QMessageBox::warning(this, "QFaktury", trUtf8("Czy chcesz skonfigurować firmę? Opcja ta przy starcie programu będzie widoczna tylko przy pierwszym uruchomieniu."), trUtf8("Tak"), trUtf8("Nie"), 0, 0,
				1) == 0) {
            userDataClick();
		}

	} else {


		setupDir();

        ui->filtrStart->setDisplayFormat(sett().getDateFormat());
        ui->filtrStart->setDate(sett().getValueAsDate("filtrStart"));
        ui->filtrEnd->setDisplayFormat(sett().getDateFormat());
        ui->filtrEnd->setDate(sett().getValueAsDate("filtrEnd"));
	}

    if (ui->tableH->rowCount() != 0) {

        ui->invoiceEdAction->setEnabled(true);
        ui->invoiceDelAction->setEnabled(true);

    } else {

        ui->invoiceEdAction->setDisabled(true);
        ui->invoiceDelAction->setDisabled(true);
    }

    if (ui->tableK->rowCount() != 0) {

        ui->editBuyersAction->setEnabled(true);
        ui->delBuyersAction->setEnabled(true);

    } else {

        ui->editBuyersAction->setDisabled(true);
        ui->delBuyersAction->setDisabled(true);

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
    ui->tableT->setColumnWidth(0, sett().value("towCol0", QVariant(50)) .toInt());
    ui->tableT->setColumnWidth(1, sett().value("towCol1", QVariant(140)) .toInt());
    ui->tableT->setColumnWidth(3, sett().value("towCol2", QVariant(40)) .toInt());
    ui->tableT->setColumnWidth(4, sett().value("towCol3", QVariant(60)) .toInt());
    ui->tableT->setColumnWidth(5, sett().value("towCol4", QVariant(50)) .toInt());
    ui->tableT->setColumnWidth(6, sett().value("towCol5", QVariant(55)) .toInt()); // net1
    ui->tableT->setColumnWidth(7, sett().value("towCol6", QVariant(55)) .toInt()); // net2
    ui->tableT->setColumnWidth(8, sett().value("towCol7", QVariant(55)) .toInt()); // net3
    ui->tableT->setColumnWidth(9, sett().value("towCol8", QVariant(55)) .toInt());; // net4
    ui->tableT->setColumnWidth(10, sett().value("towCol9", QVariant(55)) .toInt());

    ui->tableH->setColumnWidth(0, sett().value("histCol0", QVariant(0)) .toInt());
    ui->tableH->setColumnWidth(1, sett().value("histCol1", QVariant(40)) .toInt());
    ui->tableH->setColumnWidth(3, sett().value("histCol2", QVariant(40)) .toInt());
    ui->tableH->setColumnWidth(4, sett().value("histCol3", QVariant(140)) .toInt());
    ui->tableH->setColumnWidth(5, sett().value("histCol4", QVariant(50)) .toInt());

    ui->tableK->setColumnWidth(0, sett().value("custCol0", QVariant(50)) .toInt());
    ui->tableK->setColumnWidth(1, sett().value("custCol1", QVariant(140)) .toInt());
    ui->tableK->setColumnWidth(2, sett().value("custCol2", QVariant(40)) .toInt());
    ui->tableK->setColumnWidth(3, sett().value("custCol3", QVariant(60)) .toInt());
    ui->tableK->setColumnWidth(4, sett().value("custCol4", QVariant(50)) .toInt());
    ui->tableK->setColumnWidth(5, sett().value("custCol5", QVariant(140)) .toInt());
    ui->tableK->setColumnWidth(6, sett().value("custCol6", QVariant(140)) .toInt());

	// add Icon
	QIcon icon;
	icon.addPixmap(QPixmap(":/res/icons/qfaktury_48.png"),
			QIcon::Normal, QIcon::Off);
	this->setWindowIcon(icon);
	this->setWindowTitle( sett().getVersion(qAppName() ));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(tabChanged()));
    timer->start(1000);

    qDebug() << "application path: " << QStandardPaths::standardLocations(QStandardPaths::AppDataLocation).at(1);

    calendar = new ownCalendarWidget;
    ui->calendarLayout->addWidget(calendar);

	// connect slots
    connect(ui->actionBug, SIGNAL (triggered()), this, SLOT(reportBug()));
    connect(ui->applyFiltrBtn, SIGNAL (clicked(bool)), this, SLOT(rereadHist(bool)));
    connect(ui->fileData_companyAction, SIGNAL(triggered()), this, SLOT(userDataClick()));
    connect(ui->fileEndAction, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->addBuyersAction, SIGNAL(triggered()), this, SLOT(buyerClick()));
    connect(ui->delBuyersAction, SIGNAL(triggered()), this, SLOT(buyerDel()));
    connect(ui->editBuyersAction, SIGNAL(triggered()), this, SLOT(buyerEd()));
    connect(ui->addInvoiceAction, SIGNAL(triggered()), this, SLOT(newInv()));
    connect(ui->invoiceDelAction, SIGNAL(triggered()), this, SLOT(delFHist()));
    connect(ui->invoiceEdAction, SIGNAL(triggered()), this, SLOT(editFHist()));
    connect(ui->invoiceDuplAction, SIGNAL(triggered()), this, SLOT(newDuplicate()));
    connect(ui->invoiceGrossAction, SIGNAL(triggered()), this, SLOT(newInvGross()));
    connect(ui->invoiceBillAction, SIGNAL(triggered()), this, SLOT(newInvBill()));
    connect(ui->invoiceCorrAction, SIGNAL(triggered()), this, SLOT(newCor()));
    connect(ui->invoiceProFormaAction, SIGNAL(triggered()), this, SLOT(newPForm()));
    connect(ui->addGoodsAction, SIGNAL(triggered()), this, SLOT(goodsAdd()));
    connect(ui->actionPrintBuyer, SIGNAL(triggered()), this, SLOT(printBuyerList()));
    connect(ui->editGoodsAction, SIGNAL(triggered()), this, SLOT(goodsEdit()));
    connect(ui->delGoodsAction, SIGNAL(triggered()), this, SLOT(goodsDel()));
    connect(ui->pomocO_QtAction, SIGNAL(triggered()), this, SLOT(aboutQt()));
    connect(ui->helpAbout_appAction, SIGNAL(triggered()), this, SLOT(aboutProg()));
    connect(ui->fileSettingsAction, SIGNAL(triggered()), this, SLOT(settClick()));
    connect(ui->helpAction, SIGNAL(triggered()), this, SLOT(help()));
    connect(ui->action_Qt, SIGNAL(triggered()), this, SLOT(aboutQt()));
    connect(ui->hideOrganizer, SIGNAL(clicked(bool)), this, SLOT(openHideOrganizer()));
    connect(calendar, SIGNAL(activated(const QDate&)), this, SLOT(noteDownTask(const QDate&)));
    connect(ui->tableH, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(editFHist()));
    connect(ui->tableH, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showTableMenuH(QPoint)));
    connect(ui->tableK, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(buyerEd()));
    connect(ui->tableK, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showTableMenuK(QPoint)));
    connect(ui->tableT, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(goodsEdit()));
    connect(ui->tableT, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showTableMenuT(QPoint)));


    connect(ui->tableH, SIGNAL(itemClicked(QTableWidgetItem *)), this, SLOT(mainUpdateStatus(QTableWidgetItem *)));
    connect(ui->tableK, SIGNAL(itemClicked(QTableWidgetItem *)), this, SLOT(mainUpdateStatus(QTableWidgetItem *)));
    connect(ui->tableT, SIGNAL(itemClicked(QTableWidgetItem *)), this, SLOT(mainUpdateStatus(QTableWidgetItem *)));
    connect(ui->tableK, SIGNAL (cellClicked(int, int)), this, SLOT(openWebTableK(int,int)));



    readBuyer();
	readHist();
    readGoods();
    categorizeYears();
    checkTodayTask();
	loadPlugins();

}

/**
 *  Loads PyQt plugins
 */

void MainWindow::loadPlugins() {

	QDir allFiles;
    QString path = QString();
    path = sett().getAppDirs() + "plugins/";
	allFiles.setPath(path);
	allFiles.setFilter(QDir::Files);
	QStringList filters;
	filters << "*.py" << "*.Py" << "*.PY" << "*.pY";
	allFiles.setNameFilters(filters);
	QStringList files = allFiles.entryList();
	int i, max = files.count();

	for (i = 0; i < max; ++i) {

        QFile script(path + allFiles[i]);

        if (!script.open(QIODevice::ReadOnly)) {
			// return;
		} else {

            QTextStream t(&script);
            t.readLine();
			QAction *action = new QAction(t.readLine ().remove ("# "), this);
            plugActions.append(action);
			action->setData(QVariant(i));
			connect(action, SIGNAL(triggered()), this, SLOT (pluginSlot()));
            ui->menuPlugins->addAction(action);
			customActions[i] = path + allFiles[i];
		}
	}

    ui->menuPlugins->addSeparator();
    ui->menuPlugins->addAction(trUtf8("Informacje"), this, SLOT (pluginInfoSlot()));
}

/**
 * firstRun setup()
 */

bool MainWindow::firstRun() {

	bool ok = sett().value("firstrun", true).toBool();

	// qDebug() << "firstRun" << ok;
	if (ok) {

		sett().checkSettings();
        // sets dates for filter
        ui->filtrStart->setDate(QDate(QDate::currentDate().year(),1,1));
        ui->filtrEnd->setDate(QDate(QDate::currentDate().year(),12,31));
		return ok;

	} else {

        ui->filtrStart->setDate(QDate(QDate::currentDate().year(),1,1));
        ui->filtrEnd->setDate(QDate(QDate::currentDate().year(),12,31));
		sett().checkSettings();
		return ok;
	}
}

/**
 * categorizing files according to the years and putting them to separated folders
 */

void MainWindow::categorizeYears() {

    if (dl->ifThereOldInvoice()) dl->separateOldInvoices();
}


void MainWindow::checkTodayTask(QString whatToDo) {

    QString today = QDate::currentDate().toString();
    qDebug() << "TODAY IS " << today;

    QString planDir = QDir::homePath() + "/.local/share/data/elinux/plans/" + today + ".txt";


    QFile filename (planDir);

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

            if(!filename.open(QIODevice::ReadOnly  | QIODevice::Text)) {
                QMessageBox::information(0, "error", filename.errorString());
            }


            while(!in.atEnd()) {

                QString line = in.readLine();

                if (line.isNull()) {
                    ui->todayExercise->append ("<br>");
                }

                ui->todayExercise->append (line);

                QTextCursor cursor = ui->todayExercise->textCursor();
                QTextBlockFormat textBlockFormat = cursor.blockFormat();
                textBlockFormat.setAlignment(Qt::AlignHCenter);
                cursor.mergeBlockFormat(textBlockFormat);
                ui->todayExercise->setTextCursor(cursor);

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

            ui->todayExercise->append(trUtf8("Dziś nie masz nic do zrobienia"));

            QTextCursor cursor = ui->todayExercise->textCursor();
            QTextBlockFormat textBlockFormat = cursor.blockFormat();
            textBlockFormat.setAlignment(Qt::AlignHCenter);
            cursor.mergeBlockFormat(textBlockFormat);
            ui->todayExercise->setTextCursor(cursor);

        }

    } else {

        ui->todayExercise->append(trUtf8("Dziś nie masz nic do zrobienia"));

        QTextCursor cursor = ui->todayExercise->textCursor();
        QTextBlockFormat textBlockFormat = cursor.blockFormat();
        textBlockFormat.setAlignment(Qt::AlignHCenter);
        cursor.mergeBlockFormat(textBlockFormat);
        ui->todayExercise->setTextCursor(cursor);
    }
}


void MainWindow::openWebTableK(int row,int column)
{
    if (column == 6)
        {
        if ((!ui->tableK->item(row,column)->text().isEmpty()) && (ui->tableK->item(row,column)->text() != "-")) {
            QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
            QDesktopServices::openUrl(QUrl(ui->tableK->item(row,column)->text(), QUrl::TolerantMode));
            QApplication::restoreOverrideCursor();
        }
    }
}

/** save sett() before quit
 * save column width
 */

void MainWindow::saveColumnWidth() {

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
}

/** Saves all sett() as default - first run
 */

void MainWindow::saveAllSettAsDefault() {

	sett().resetSettings();
}

/** Saves all sett()
 */

void MainWindow::saveAllSett() {

    // saves filtr
    sett().setValue("filtrStart", ui->filtrStart->text());
    sett().setValue("filtrEnd", ui->filtrEnd->text());

	saveColumnWidth();

    // saves unsaved
	sett().sync();
}

/** Clears content of the QTableWidget passed in the input
 *  @param QTableWidget
 */

void MainWindow::tableClear(QTableWidget * tab) {

    tab->setRowCount(0);
}

/** Used while adding new row
 */

void MainWindow::insertRow(QTableWidget *t, int row) {

	t->insertRow(row);

	for (int i = 0; i < t->columnCount(); i++) {

		t->setItem(row, i, new QTableWidgetItem());
	}
}


int const MainWindow::getMaxSymbol()
{
    int max = *std::max_element(allSymbols.begin(), allSymbols.end());
    return max;
}

/** Reads the invoices from the directory passed in the input.
 *  @param QString - directory from where the invoices should be read
 */

void MainWindow::readHist() {

	QVector<InvoiceData> invoicesVec;
    invoicesVec = dl->invoiceSelectAllData(ui->filtrStart->date(), ui->filtrEnd->date());
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
        ui->tableH -> setItem(ui->tableH->rowCount() - 1, 2, new DateWidgetItem(invoicesVec.at(i).sellingDate));
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

/** Reads customers from the XML
 */

void MainWindow::readBuyer() {

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
        ui->tableK->item(ui->tableK->rowCount() - 1, 6)->setTextColor(QColor(30,144,255));

	}

    ui->tableK->setSortingEnabled(true);
}

/** Reads goods from the XML
 */

void MainWindow::readGoods() {

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

	workingDir = sett().getWorkingDir();
	QDir dir(workingDir);
    QDir mainPath(QDir::homePath() + "/.local/share/data");

    if (!mainPath.exists()) {

        mainPath.mkpath(QDir::homePath() + "/.local/share/data");
    }

	if (!dir.exists()) {

		dir.mkdir(workingDir);
		dir.mkdir(workingDir + sett().getDataDir());
	}

	if (!dir.exists(workingDir + sett().getDataDir())) {

		dir.mkdir(workingDir + sett().getDataDir());
	}
}


// ----------------------------------------  SLOTS ---------------------------------//

void MainWindow::keyPressEvent(QKeyEvent * event) {

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

	if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_PageUp) {

        if (ui->tabWidget2->currentIndex() != ui->tabWidget2->count() - 1) {

            ui->tabWidget2->setCurrentIndex(ui->tabWidget2->currentIndex() + 1);

		} else {

            ui->tabWidget2->setCurrentIndex(0);
		}
	}

	if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_PageDown) {

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

	QMessageBox::information(this, trUtf8("QFaktury"),
			trUtf8("To menu służy do obsługi pluginów pythona, \n np. archiwizacji danych, generowania raportów etc.\n\n") +
			trUtf8("Skrypty pythona sa czytane z folderu \"~/elinux/plugins/\"."),
			trUtf8("Ok"), 0, 0, 1);

}

/** Slot
 *  Used while calling python script from the menu
 */

void MainWindow::pluginSlot() {

    QString program = QString("python");

	QAction *a = static_cast<QAction *> (this->sender());

	int scriptId = a->data().toInt();

	QStringList args;
	args += customActions[scriptId];
	args += QString("%1").arg(winId(), 0, 10);

	qDebug() << find(winId())->windowTitle();

	QProcess *cmd = new QProcess(this);

	cmd->start(program, args);

	if (!cmd->waitForStarted()) {

		QMessageBox::information(this, trUtf8("QFaktury"), trUtf8(
				"Uruchomienie się nie powiodło."), QMessageBox::Ok);
	}

    if (cmd != 0) cmd = 0;
    delete cmd;
    if (a != 0) a = 0;
    delete a;
}

/** Slot
 *  Shows context menu
 */

void MainWindow::showTableMenuT(QPoint p) {

	// qDebug() << __FUNCTION__ << __LINE__;
    QMenu *menuTableT = new QMenu(ui->tableT);
    menuTableT->addAction(ui->addGoodsAction);
    menuTableT->addAction(ui->delGoodsAction);
    menuTableT->addAction(ui->editGoodsAction);
    menuTableT->exec(ui->tableT->mapToGlobal(p));
	delete menuTableT;
	menuTableT = NULL;
}


/** Slot
 *  Show context menu
 */
void MainWindow::showTableMenuK(QPoint p) {

	// qDebug() << __FUNCTION__ << __LINE__;
    QMenu *menuTable = new QMenu(ui->tableK);
    menuTable->addAction(ui->addBuyersAction);
    menuTable->addAction(ui->delBuyersAction);
    menuTable->addAction(ui->editBuyersAction);
    menuTable->exec(ui->tableK->mapToGlobal(p));
	delete menuTable;
	menuTable = NULL;
}


/** Slot
 *  Show context menu
 */
void MainWindow::showTableMenuH(QPoint p) {

	// qDebug() << __FUNCTION__ << __LINE__;
    QMenu *menuTable = new QMenu(ui->tableH);
    menuTable->addAction(ui->addInvoiceAction);
    menuTable->addAction(ui->invoiceGrossAction);
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

	// cast is required since the names of method and objects inside MainWindow class and
	// QMainWindow and UiMainWindow are the same... I guess there is a way to avoid it.
    QStatusBar* stat = qobject_cast<QMainWindow *>(this)->statusBar();

	QTableWidget *table = item->tableWidget();
    QString message = QString();
	message += table->horizontalHeaderItem(1)->text() + " : " + table->item(item->row(), 1)->text() + ", ";
	message += table->horizontalHeaderItem(2)->text() + " : " + table->item(item->row(), 2)->text() + ", ";
	message += table->horizontalHeaderItem(3)->text() + " : " + table->item(item->row(), 3)->text();

	stat->showMessage(trUtf8("Wybrana pozycja: ") + message);
}

/** Slot which enables/disables menu. It's possible to add/remove goods/customers
 *  only if this is the current tab.
 */

void MainWindow::tabChanged() {

    // disables Edit and Remove actions _ONLY_

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

	//  qDebug( __FUNCTION__ );

    if (ui->filtrStart->date() > ui->filtrEnd->date()) {

        QMessageBox::information(this, trUtf8("Filtr dat"), trUtf8("Data początkowa nie może być większa od daty końcowej"));

    } else {

        tableClear(ui->tableH);
        ui->tableH->setSortingEnabled(false);
        readHist();

    }
}

/** Slot used to display aboutQt informations.
 */

void MainWindow::aboutQt() {

	QMessageBox::aboutQt(this, sett().getVersion(qAppName()));
}

/** Slot used to display information about QFaktury
 */

void MainWindow::aboutProg() {

    QMessageBox::about(this,
             trUtf8("O programie"),
             trUtf8("<h2>Program do wystawiania faktur</h2><br/><p>") + sett().getVersion(qAppName()) + trUtf8("<br/>Wymagane Qt >= 5.0.0") + trUtf8("<br/>Kompilowane z Qt ") + QT_VERSION_STR + trUtf8("<br/>Twoja aktualna wersja - Qt ") + qVersion() +
             trUtf8("</p><p>Koordynator projektu: Grzegorz Rękawek</p>  <p>Programiści: Tomasz Pielech, Rafał Rusin http://people.apache.org/~rr/, Sławomir Patyk, Jagoda Górska</p>") +
             trUtf8("<p>Ikony: Dariusz Arciszewski </p><p>Portowanie na Qt5: Jagoda \"juliagoda\" Górska</p><br/>") +
             trUtf8("<h2><center>UWAGA!!!</center></h2>") +
             trUtf8("<p align=\"justify\">Ten program komputerowy dostarczany jest przez autora w formie \"takiej, jaki jest\". ") +
             trUtf8("Autor nie udziela żadnej gwarancji oraz rękojmi, że program będzie działał ") +
             trUtf8("prawidłowo, jest odpowiedniej jakości oraz że spełni oczekiwania ") +
             trUtf8("użytkownika. Autor nie odpowiada za jakiekolwiek straty wynikające z użytkowania ") +
             trUtf8("programu, w tym utratą spodziewanych korzyści, danych, informacji ") +
             trUtf8("gospodarczych lub koszt urządzeń lub programów zastępczych.</p>"));
}

/** Slot used to edit the invoice from list of invoices.
 */

void MainWindow::editFHist() {

    if (ui->tableH->selectedItems().count() <= 0) {

        QMessageBox::information(this, trUtf8("QFaktury"), trUtf8("Faktura nie wybrana. Nie mozna edytować."), trUtf8("Ok"), 0, 0, 1);
        return;
    }

    ui->tableH->setSortingEnabled(false);

    int row = 0;
    row = ui->tableH->selectedItems().at(0)->row();

    if (ui->tableH->item(row, 3)->text() == trUtf8("korekta")) {

        // QMessageBox::information( this, trUtf8("QFaktury"), "Jeszcze nie ma", QMessageBox::Ok );
        Correction *corWindow = new Correction(this, dl, s_WIN_CORRECT_EDIT, true);
        corWindow->correctionInit(true);
        corWindow->readCorrData(ui->tableH->item(row, 0)->text());

        if (corWindow->exec() == QDialog::Accepted) {

            rereadHist(true);
        }

        if (corWindow->getKAdded()) readBuyer();
        delete corWindow;
        corWindow = 0;
    }

    if (ui->tableH->item(row, 3)->text() == trUtf8("kbrutto")) {

        // QMessageBox::information( this, trUtf8("QFaktury"), "Jeszcze nie ma", QMessageBox::Ok );
        CorrectGross *corWindow = new CorrectGross(this, dl, s_WIN_CORRECT_EDIT, true);
        corWindow->correctionInit(true);
        corWindow->readCorrData(ui->tableH->item(row, 0)->text());

        if (corWindow->exec() == QDialog::Accepted) {

            rereadHist(true);
        }

        if (corWindow->getKAdded()) readBuyer();
        delete corWindow;
        corWindow = 0;
    }


    if (ui->tableH->item(row, 3)->text() == trUtf8("rachunek")) {

        Bill *billWindow = new Bill(this, dl, s_BILL_EDIT);
        billWindow->readData(ui->tableH->item(row, 0)->text());
        billWindow->setfName(ui->tableH->item(row, 0)->text());
        billWindow->billInit();
        billWindow->setWindowTitle(trUtf8("Edytuje Rachunek"));

        if (billWindow->exec() == QDialog::Accepted) {

            rereadHist(true);
        }

        if (billWindow->getKAdded()) readBuyer();
        delete billWindow;
        billWindow = 0;
    }

    if (ui->tableH->item(row, 3)->text() == trUtf8("FVAT")) {

        Invoice *invWindow = new Invoice(this, dl, s_WIN_INVOICE_EDIT);

        invWindow->readData(ui->tableH->item(row, 0)->text());
        invWindow->setfName(ui->tableH->item(row, 0)->text());

        if (invWindow->exec() == QDialog::Accepted) {

            rereadHist(true);
        }

        if (invWindow->getKAdded()) readBuyer();
        delete invWindow;
        invWindow = 0;
    }

    if (ui->tableH->item(row, 3)->text() == trUtf8("FPro")) {

        Invoice *invWindow = new Invoice(this, dl, s_WIN_PROFORMA_EDIT);

        invWindow->readData(ui->tableH->item(row, 0)->text());
        invWindow->setfName(ui->tableH->item(row, 0)->text());
        if (invWindow->exec() == QDialog::Accepted) {

            rereadHist(true);
        }

        if (invWindow->getKAdded()) readBuyer();
        delete invWindow;
        invWindow = 0;
    }

    if (ui->tableH->item(row, 3)->text() == trUtf8("FBrutto")) {

        InvoiceGross *invWindow = new InvoiceGross(this, dl, s_BR_INVOICE_EDIT);

        invWindow->readData(ui->tableH->item(row, 0)->text());
        invWindow->setfName(ui->tableH->item(row, 0)->text());
        if (invWindow->exec() == QDialog::Accepted) {

            rereadHist(true);
        }

        if (invWindow->getKAdded()) readBuyer();
        delete invWindow;
        invWindow = 0;
    }

    if (ui->tableH->item(row, 3)->text() == trUtf8("duplikat")) {

        Duplicate *dupWindow = new Duplicate(this, dl, s_WIN_DUPLICATE_LOOK, true);

        dupWindow->readData(ui->tableH->item(row, 0)->text());
        dupWindow->duplicateInit();
        dupWindow->setIsEditAllowed(false);
        dupWindow->setfName(ui->tableH->item(row, 0)->text());

        if (dupWindow->exec() == QDialog::Accepted) {

            rereadHist(true);
        }

        if (dupWindow->getKAdded()) readBuyer();
        delete dupWindow;
        dupWindow = 0;
    }

    ui->tableH->setSortingEnabled(true);
}
/** Slot used to delete invoices
 */

void MainWindow::delFHist() {

    if (ui->tableH->selectedItems().count() <= 0) {

		QMessageBox::information(this, trUtf8("QFaktury"), trUtf8("Faktura nie wybrana. Nie mozna usuwać."), trUtf8("Ok"), 0, 0, 1);
		return;
	}

	if (QMessageBox::warning(this, sett().getVersion(qAppName()), trUtf8("Czy napewno chcesz usnąć tą fakturę z historii?"), trUtf8("Tak"),
			trUtf8("Nie"), 0, 0, 1) == 0) {

        QString name = ui->tableH->item (ui->tableH->currentRow(), 0)->text();
		dl->invoiceDeleteData(name);
        ui->tableH->removeRow(ui->tableH->currentRow());
        allSymbols = dl->getAllSymbols();
	}
}

/** Slot used to edit data of the current company
 */

void MainWindow::userDataClick() {

	// qDebug("%s %s:%d", __FUNCTION__, __FILE__, __LINE__);
    User* userDataWindow = new User(this);
    userDataWindow->exec();
    delete userDataWindow;
    userDataWindow = 0;

}

/** Slot used to edit edit sett()
 */

void MainWindow::settClick() {

	// qDebug ("%s %s:%d", __FUNCTION__, __FILE__, __LINE__);
    Setting *settWindow = new Setting(this);
	settWindow->exec();
	delete settWindow;
    settWindow = 0;
}

/** Slot used to add new customer
 */

void MainWindow::buyerClick() {

    Buyers *buyersWindow;
    buyersWindow = new Buyers(this, 0, dl);
	//qDebug ("%s %s:%d", __FUNCTION__, __FILE__, __LINE__);

    if (buyersWindow->exec() == QDialog::Accepted) {

        ui->tableK->setSortingEnabled(false);
        insertRow(ui->tableK, ui->tableK->rowCount());
        QStringList row = buyersWindow->getRetBuyer().split("|");

        ui->tableK->item(ui->tableK->rowCount() - 1, 0)->setText(row[0]); // name
        ui->tableK->item(ui->tableK->rowCount() - 1, 1)->setText(row[1]); // type
        ui->tableK->item(ui->tableK->rowCount() - 1, 2)->setText(row[2]); // place
        ui->tableK->item(ui->tableK->rowCount() - 1, 3)->setText(row[3]); // address
        ui->tableK->item(ui->tableK->rowCount() - 1, 4)->setText(row[4]); // telefon
        ui->tableK->item(ui->tableK->rowCount() - 1, 5)->setText(row[9]); // email
        ui->tableK->item(ui->tableK->rowCount() - 1, 6)->setText(row.last()); // www*/
        ui->tableK->setSortingEnabled(true);


	}

    delete buyersWindow;
    buyersWindow = 0;
}

/** Slot used to delete current customer
 */

void MainWindow::buyerDel() {

    if (ui->tableK->selectedItems().count() <= 0) {

		QMessageBox::information(this, trUtf8("QFaktury"), trUtf8("Kontrahent nie wybrany. Nie mozna usuwac."), trUtf8("Ok"), 0, 0, 1);
		return;
	}

	if (QMessageBox::warning(this, trUtf8("QFaktury"), trUtf8("Czy napewno chcesz usunąć kontrahenta: ") +
            ui->tableK->item(ui->tableK->currentRow(), 0)->text() + trUtf8(" ?"), trUtf8("Tak"), trUtf8("Nie"), 0, 0, 1) == 0) {

            dl->buyersDeleteData(ui->tableK->item(ui->tableK->currentRow(), 0)->text());
            ui->tableK->removeRow(ui->tableK->currentRow());
	}
}

/** Slot used to edit customer
 */

void MainWindow::buyerEd() {

    if (ui->tableK->selectedItems().count() <= 0) {

        QMessageBox::information(this, trUtf8("QFaktury"), trUtf8("Kontrahent nie wybrany."), trUtf8("Ok"), 0, 0, 1);
        return;
    }

    int row = ui->tableK->selectedItems()[0]->row();

    Buyers *buyersWindow = new Buyers(this, 1, dl);
    buyersWindow->selectData(ui->tableK->item(row, 0)->text(),
            sett().getCustomerType(ui->tableK->item(row, 1)->text()));

    if (buyersWindow->exec() == QDialog::Accepted) {

        ui->tableK->setSortingEnabled(false);
        QStringList rowTxt = buyersWindow->getRetBuyer().split("|");
        ui->tableK->item(row, 0)->setText(rowTxt[0]); // name
        ui->tableK->item(row, 1)->setText(rowTxt[1]); // type
        ui->tableK->item(row, 2)->setText(rowTxt[2]); // place
        ui->tableK->item(row, 3)->setText(rowTxt[3]); // address
        ui->tableK->item(row, 4)->setText(rowTxt[4]); // telefon
        ui->tableK->item(row, 5)->setText(rowTxt.last()); // www
        ui->tableK->setSortingEnabled(true);
    }

    delete buyersWindow;
    buyersWindow = NULL;

}


void MainWindow::printBuyerList() {


    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

   QPrinter printer(QPrinter::HighResolution);
   QPrintPreviewDialog preview(&printer, this);
   preview.setWindowFlags(Qt::Window);
   preview.setWindowTitle(trUtf8("Lista kontrahentów"));

   connect(&preview, SIGNAL(paintRequested(QPrinter *)), this, SLOT(printList(QPrinter *)));
   if (preview.exec() == 1) {
   }

}


/** Slot print
 *  Helper slot used to display print preview
 */


void MainWindow::printList(QPrinter *printer) {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

   if (ui->tableK->rowCount() != 0) {


   QTextDocument doc(trUtf8("Lista kontrahentów"));
   QString s = QString();
   QStringList list = QStringList();
   list << "<!doctype html>" << "<head>" << "<meta charset=\"utf-8\" />" << "</head>" << "<body>";


   QVector<BuyerData> buyerVec = dl->buyersSelectAllData();

   for (int i = 0; i < buyerVec.size(); ++i) {

       QString text = buyerVec.at(i).name;
       list << "<strong>" + trUtf8("Nazwa:  ") + "</strong>" + changeIfEmpty(text);
       list << "<br/>";
       text = buyerVec.at(i).type;
       list << "<strong>" + trUtf8("Rodzaj:  ") + "</strong>" + changeIfEmpty(text);
       list << "<br/>";
       text = buyerVec.at(i).place;
       list << "<strong>" + trUtf8("Miejscowość:  ") + "</strong>" + changeIfEmpty(text);
       list << "<br/>";
       text = buyerVec.at(i).address;
       list << "<strong>" + trUtf8("Adres:  ") + "</strong>" + changeIfEmpty(text);
       list << "<br/>";
       text = buyerVec.at(i).phone;
       list << "<strong>" + trUtf8("Tel:  ") + "</strong>" + changeIfEmpty(text);
       list << "<br/>";
       text = buyerVec.at(i).account;
       list << "<strong>" + trUtf8("Nr konta:  ") + "</strong>" + changeIfEmpty(text);
       list << "<br/>";
       text = buyerVec.at(i).email;
       list << "<strong>" + trUtf8("Email:  ") + "</strong>" + changeIfEmpty(text);
       list << "<br/>";
       text = buyerVec.at(i).www;
       list << "<strong>" + trUtf8("Strona:  ") + "</strong>" + changeIfEmpty(text);
       list << "<p> --------------------------------------------- </p>";
       list << "<br />";

   }

   QFile file(sett().getWorkingDir() + "/buyerContacts.html");

   if (file.exists()) file.remove();

   if (file.open(QIODevice::WriteOnly)) {

       QTextStream stream(&file);
       for (QStringList::Iterator it = list.begin(); it
               != list.end(); ++it)
           stream << *it << "\n";

       file.close();
   }


   doc.setHtml(list.join(" "));
   doc.print(printer);

    } else {

       if (QMessageBox::warning(this, trUtf8("Brak kontrahentów"), trUtf8("Aby móc wydrukować listę kontaktów, musisz mieć wprowadzonego co najmniej jednego kontrahenta do tabeli. Czy chcesz dodać teraz dane twojego kontrahenta?"), trUtf8("Tak"), trUtf8("Nie"), 0, 0,
               1) == 0) {
           buyerClick();
       }

   }

}


QString MainWindow::changeIfEmpty(QString text)
{
    QString result = QString();

    if (text.isEmpty()) { result = "-"; } else { result = text; }

    return  result;
}

/** Slot used for creating new invoices
 */

void MainWindow::newInv() {

    Invoice *invWindow = new Invoice(this, dl, s_INVOICE);

    if (invWindow->exec() == QDialog::Accepted) {

        ui->tableH->setSortingEnabled(false);
        insertRow(ui->tableH, ui->tableH->rowCount());
        QStringList row = invWindow->getRet().split("|");
        ui->tableH->item(ui->tableH->rowCount() - 1, 0)->setText(row[0]); // file name
        ui->tableH->item(ui->tableH->rowCount() - 1, 1)->setText(row[1]); // symbol
        ui->tableH->item(ui->tableH->rowCount() - 1, 2)->setText(row[2]); // date
        ui->tableH->item(ui->tableH->rowCount() - 1, 3)->setText(row[3]); // type
        ui->tableH->item(ui->tableH->rowCount() - 1, 4)->setText(row[4]); // buyer
        ui->tableH->item(ui->tableH->rowCount() - 1, 5)->setText(row[5]); // NIP
        ui->tableH->setSortingEnabled(true);

    } else {

        rereadHist(true);
    }

    if (invWindow->getKAdded()) readBuyer();
    dl->checkAllSymbInFiles();
    allSymbols = dl->getAllSymbols();

    delete invWindow;
    invWindow = NULL;
}


/** Slot used for creating new invoices
 */
void MainWindow::newInvBill() {

    Bill *billWindow = new Bill(this, dl, s_BILL);

    billWindow->setWindowTitle(trUtf8("Rachunek"));
    billWindow->billInit();

    if (billWindow->exec() == QDialog::Accepted) {

        ui->tableH->setSortingEnabled(false);
        insertRow(ui->tableH, ui->tableH->rowCount());
        QStringList row = billWindow->getRet().split("|");
        ui->tableH->item(ui->tableH->rowCount() - 1, 0)->setText(row[0]); // file name
        ui->tableH->item(ui->tableH->rowCount() - 1, 1)->setText(row[1]); // symbol
        ui->tableH->item(ui->tableH->rowCount() - 1, 2)->setText(row[2]); // date
        ui->tableH->item(ui->tableH->rowCount() - 1, 3)->setText(row[3]); // type
        ui->tableH->item(ui->tableH->rowCount() - 1, 4)->setText(row[4]); // buyer
        ui->tableH->item(ui->tableH->rowCount() - 1, 5)->setText(row[5]); // NIP
        ui->tableH->setSortingEnabled(true);

    } else {

        rereadHist(true);
    }

    if (billWindow->getKAdded()) readBuyer();
    dl->checkAllSymbInFiles();
    allSymbols = dl->getAllSymbols();
    delete billWindow;
    billWindow = NULL;
}


/** Slot used for creating new invoices
 */
void MainWindow::newInvGross() {

    InvoiceGross *invWindow = new InvoiceGross(this, dl, s_FBRUTTO);
    invWindow->setWindowTitle(trUtf8("Faktura VAT Brutto"));

    if (invWindow->exec() == QDialog::Accepted) {

        ui->tableH->setSortingEnabled(false);
        insertRow(ui->tableH, ui->tableH->rowCount());
        QStringList row = invWindow->getRet().split("|");
        ui->tableH->item(ui->tableH->rowCount() - 1, 0)->setText(row[0]); // file name
        ui->tableH->item(ui->tableH->rowCount() - 1, 1)->setText(row[1]); // symbol
        ui->tableH->item(ui->tableH->rowCount() - 1, 2)->setText(row[2]); // date
        ui->tableH->item(ui->tableH->rowCount() - 1, 3)->setText(row[3]); // type
        ui->tableH->item(ui->tableH->rowCount() - 1, 4)->setText(row[4]); // buyer
        ui->tableH->item(ui->tableH->rowCount() - 1, 5)->setText(row[5]); // NIP
        ui->tableH->setSortingEnabled(true);

    } else {

        rereadHist(true);
    }

    if (invWindow->getKAdded()) readBuyer();
    dl->checkAllSymbInFiles();
    allSymbols = dl->getAllSymbols();
    delete invWindow;
    invWindow = NULL;
}


/** Slot used to create new ProForma Invoice
 */

void MainWindow::newPForm() {

    Invoice *invWindow = new Invoice(this, dl, s_PROFORMA);
    invWindow->setWindowTitle(trUtf8("Faktura Pro Forma"));
    invWindow->backBtnClick();

    if (invWindow->exec() == QDialog::Accepted) {

        ui->tableH->setSortingEnabled(false);
        insertRow(ui->tableH, ui->tableH->rowCount());
        QStringList row = invWindow->getRet().split("|");
        ui->tableH->item(ui->tableH->rowCount() - 1, 0)->setText(row[0]); // file name
        ui->tableH->item(ui->tableH->rowCount() - 1, 1)->setText(row[1]); // symbol
        ui->tableH->item(ui->tableH->rowCount() - 1, 2)->setText(row[2]); // date
        ui->tableH->item(ui->tableH->rowCount() - 1, 3)->setText(row[3]); // type
        ui->tableH->item(ui->tableH->rowCount() - 1, 4)->setText(row[4]); // buyer
        ui->tableH->item(ui->tableH->rowCount() - 1, 5)->setText(row[5]); // NIP
        ui->tableH->setSortingEnabled(true);

    } else {

        rereadHist(true);
    }

    if (invWindow->getKAdded()) readBuyer();
    dl->checkAllSymbInFiles();
    allSymbols = dl->getAllSymbols();
    delete invWindow;
    invWindow = NULL;
}

/** Slot used to create new Correction
 */

void MainWindow::newCor() {

    if (ui->tableH->selectedItems().count() <= 0) {

        QMessageBox::information(this, trUtf8("QFaktury"), trUtf8("Faktura nie wybrana. Wybierz fakurę, do której chcesz wystawić korektę."), trUtf8("Ok"), 0, 0, 1);
        return;
    }

    int row = ui->tableH->selectedItems()[0]->row();

    QStringList invTypes = QStringList();
    invTypes << "FVAT" << "FBrutto";

    if (invTypes.contains(ui->tableH->item(row, 3)->text())) {

        ui->tableH->setSortingEnabled(false);

        Correction *corWindow;

        if (ui->tableH->item(row, 3)->text().contains("FVAT")) {

            corWindow = new Correction(this, dl, s_CORRECT_TITLE, false);

        } else  {

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

        if (corWindow->getKAdded()) readBuyer();
        dl->checkAllSymbInFiles();
        allSymbols = dl->getAllSymbols();
        delete corWindow;
        corWindow = NULL;
        ui->tableH->setSortingEnabled(true);

    } else {

        QMessageBox::information(this, "QFaktury",
                trUtf8("Do faktury typu ") + ui->tableH->item(row, 3)->text()
                + (" nie wystawiamy korekt."), QMessageBox::Ok);
    }
}

/** Slot
 *  Creates duplicate
 */

void MainWindow::newDuplicate() {

    if (ui->tableH->selectedItems().count() <= 0) {

        QMessageBox::information(this, trUtf8("QFaktury"), trUtf8("Faktura nie wybrana. Wybierz fakurę, do której chcesz wystawić duplikat."), trUtf8("Ok"), 0, 0, 1);
        return;
    }

    int row = ui->tableH->selectedItems()[0]->row();

    // types of invoices for which it's ok to issue a duplicate
    QStringList invTypes = QStringList();
    invTypes << "FVAT" << "FBrutto";

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

        if (dupWindow->getKAdded()) readBuyer();
        dl->checkAllSymbInFiles();
        allSymbols = dl->getAllSymbols();
        delete dupWindow;
        dupWindow = NULL;
        ui->tableH->setSortingEnabled(true);

    } else {

        QMessageBox::information(this, "QFaktury",
                trUtf8("Do faktury typu ") + ui->tableH->item(row, 3)->text()
                + (" nie wystawiamy duplikatów."), QMessageBox::Ok);
    }

}

/** Slot used to add goods
 */

void MainWindow::goodsAdd() {

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

    delete goodsWindow;
    goodsWindow = NULL;
}

/** Slot used to delete goods
 */
void MainWindow::goodsDel() {

    if (ui->tableT->selectedItems().count() <= 0) {

        QMessageBox::information(this, trUtf8("QFaktury"), trUtf8("Towar nie wybrany. Nie mozna usuwac."), trUtf8("Ok"), 0, 0, 1);
        return;
    }

    int row = ui->tableT->currentRow();

    if (QMessageBox::warning(this, trUtf8("QFaktury"), trUtf8("Czy napewno chcesz usunąć towar ") + ui->tableT->item(row, 0)->text()
            + "/" + ui->tableT->item(row, 1)->text() + "?", trUtf8("Tak"), trUtf8("Nie"), 0, 0, 1)
            == 0) {

            dl->productsDeleteData(ui->tableT->item(row, 0)->text());
            ui->tableT->removeRow(row);
        }
}

/** Slot used for editing goods
 */

void MainWindow::goodsEdit() {

    if (ui->tableT->selectedItems().count() <= 0) {

        QMessageBox::information(this, trUtf8("QFaktury"), trUtf8("Towar nie wybrany. Nie można edytować."), trUtf8("Ok"), 0, 0, 1);
        return;
    }

    int row = ui->tableT->selectedItems()[0]->row();

    Goods *goodsWindow = new Goods(this, 1, dl);
    goodsWindow->selectData(ui->tableT->item(row, 0)->text(),
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

    delete goodsWindow;
    goodsWindow = NULL;
}


void MainWindow::noteDownTask(const QDate& taskDate) {


    windowTask = new QWidget;

    addTaskBtn = new QPushButton;
    addTaskBtn->setObjectName("addTaskButton");

    QPushButton* addNextTask = new QPushButton;
    addNextTask->setText(trUtf8("Dodaj kolejne"));

    QPushButton* delTasks = new QPushButton;
    delTasks->setText(trUtf8("Usuń zadania"));

    QString planDir = QDir::homePath() + "/.local/share/data/elinux/plans/" + taskDate.toString() + ".txt";
    QFile filename (planDir);

    if (filename.exists()) addTaskBtn->setText(trUtf8("Zastąp zadanie"));
    else addTaskBtn->setText(trUtf8("Dodaj zadanie"));

    cancelTaskBtn = new QPushButton;
    cancelTaskBtn->setText(trUtf8("Anuluj zadanie"));


    QHBoxLayout *buttons = new QHBoxLayout;
    buttons->addWidget(addTaskBtn);
    if (filename.exists()) buttons->addWidget(addNextTask);
    buttons->addWidget(cancelTaskBtn);
    if (filename.exists()) buttons->addWidget(delTasks);

    QTextEdit* taskDescription = new QTextEdit;

    if (filename.exists()) {

        if(!filename.open(QIODevice::ReadOnly  | QIODevice::Text)) {
            QMessageBox::information(0, "error", filename.errorString());
        }

        QTextStream in(&filename);

        while(!in.atEnd()) {

            QString line = in.readLine();

            if (line.isNull()) {
                taskDescription->insertPlainText ("\n");
            }

            taskDescription->insertPlainText (line);
            taskDescription->insertPlainText ("\n");
            taskDescription->moveCursor (QTextCursor::End);
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

    windowTask->hide();

    foreach (QWidget * w, windowTask->findChildren<QWidget*>())
      if (! w->windowFlags() & Qt::Window) delete w;

    if (windowTask != 0) windowTask = 0;
    delete windowTask;
}


void MainWindow::delTasksFromDay() {

    QFile file(QDir::homePath() + "/.local/share/data/elinux/plans/" + markedDate.toString() + ".txt");
    bool removed = false;

    if (file.exists()) removed = file.remove();

    if (removed) {

        QMessageBox::information(this, trUtf8("Usuwanie zadań"), trUtf8("Zadania z wybranego dnia zostały pomyślnie usunięte"),
                QMessageBox::Ok);

        cancelTaskWidget();

        checkTodayTask("remove");


    } else {

        QMessageBox::critical(this, trUtf8("Usuwanie zadań"), trUtf8("Zadania z wybranego dnia nie mogły zostać pomyślnie usunięte. Zrestartuj program, by wyeliminować ewentualny brak aktualnych danych o plikach."),
                QMessageBox::Ok);
    }
}


void MainWindow::addTaskToList() {


    QString planDir = QDir::homePath() + "/.local/share/data/elinux/plans";

    QDir mainPath(planDir);

    if (!mainPath.exists()) {

        mainPath.mkdir(planDir);
    }


    QString filename = planDir + "/" + markedDate.toString(Qt::TextDate) + ".txt";

    QTextEdit* button = windowTask->findChild<QTextEdit*>();

    QFile file( filename );

    if ( file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text) )
    {
        QTextStream stream( &file );
        stream << button->toPlainText() << endl;

        if (stream.status() == QTextStream::Ok) {

            QMessageBox::information(this, trUtf8("Dodawanie zadania"), trUtf8("Zadanie zostało pomyślnie stworzone"),
                    QMessageBox::Ok);

            cancelTaskWidget();

            checkTodayTask(QString("insert"));


        } else {

            QMessageBox::critical(this, trUtf8("Dodawanie zadania"), trUtf8("Zadanie nie mogło zostac dodane. Sprawdź, czy istnieje ścieżka: ") + planDir + trUtf8(" . Jeśli istnieje to sprawdź, czy masz uprawnienia do zapisu i odczytu w podanej ścieżce."),
                    QMessageBox::Ok);

        }
    }
}


void MainWindow::addNextTask() {

    QString planDir = QDir::homePath() + "/.local/share/data/elinux/plans";

    QString filename = planDir + "/" + markedDate.toString(Qt::TextDate) + ".txt";

    QTextEdit* button = windowTask->findChild<QTextEdit*>();

    QFile file( filename );
    if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {

        QTextStream stream( &file );
        stream << "\n" << endl;
        stream << button->toPlainText() << endl;

        if (stream.status() == QTextStream::Ok) {

            QMessageBox::information(this, trUtf8("Dopisywanie kolejnego zadania"), trUtf8("Dodatkowe zadanie zostało pomyślnie dodane."),
                    QMessageBox::Ok);

            cancelTaskWidget();

            checkTodayTask();

        } else {

            QMessageBox::critical(this, trUtf8("Dopisywanie kolejnego zadania"), trUtf8("Dodatkowe zadanie nie mogło zostac dodane. Sprawdź, czy istnieje ścieżka: ") + planDir + trUtf8(" . Jeśli istnieje to sprawdź, czy masz uprawnienia do zapisu i odczytu w podanej ścieżce."),
                    QMessageBox::Ok);


        }
    }
}


void MainWindow::openHideOrganizer() {

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

	if (QMessageBox::question(this, trUtf8("Potwierdź"),
	trUtf8("Czy chcesz wyjść z programu?"), QMessageBox::Yes | QMessageBox::No,
			QMessageBox::Yes) == QMessageBox::Yes) {

		saveAllSett();
		return QMainWindow::close();

	} else {

		return false;
	}
}

/** Slot help
 */

void MainWindow::help() {

    QDesktopServices::openUrl(QUrl("https://github.com/juliagoda/qfaktury"));
}

/** Slot reportBug
 */

void MainWindow::reportBug() {

    QDesktopServices::openUrl(QUrl("https://github.com/juliagoda/qfaktury/issues"));
}

// ----------------------------------------  SLOTS ---------------------------------//
