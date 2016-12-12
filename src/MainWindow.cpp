#include "moc_MainWindow.cpp"
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

#include "Ustawienia.h"
#include "Uzytkownik.h"
#include "Towary.h"
#include "Faktura.h"
#include "Korekta.h"
#include "Duplikat.h"
#include "FakturaBrutto.h"
#include "KorektaBrutto.h"
#include "Rachunek.h"
#include "Kontrahenci.h"
#include "DateWidgetItem.h"
#include "Const.h"
#include "MainWindow.h"

#include "XmlDataLayer.h"



/** Constructor
 */
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    init();
}

/** Destructor
 */
MainWindow::~MainWindow() {
	saveAllSett();
    if (timer != 0) timer = 0;
    delete timer;

    if (ui != 0) ui = 0;
    delete ui;
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
		saveAllSettAsDefault();


        QMessageBox::information(this, "QFaktury", trUtf8("Program zawiera konwersję walut w oknie edycji faktury lub podczas jej tworzenia. By jej używać, powinieneś mieć dostęp do internetu oraz poprawnie ustawiony czas systemowy."));
        QMessageBox::information(this, "QFaktury", trUtf8("W przypadku zmiany lokalizacji systemu sposób formatowania liczb może się zmienić. Efekt ten może być widoczny po restarcie programu."));


        if (QMessageBox::warning(this, "QFaktury", trUtf8("Czy chcesz skonfigurować firmę? Opcja ta przy starcie programu będzie widoczna tylko przy pierwszym uruchomieniu."), trUtf8("Tak"), trUtf8("Nie"), 0, 0,
				1) == 0) {
            daneFirmyClick();
		}

	} else {

		setupDir();

        ui->filtrStart->setDisplayFormat(sett().getDateFormat());
        ui->filtrStart->setDate(sett().getValueAsDate("filtrStart"));
        ui->filtrEnd->setDisplayFormat(sett().getDateFormat());
        ui->filtrEnd->setDate(sett().getValueAsDate("filtrEnd"));
	}

    if (ui->tableH->rowCount() != 0) {
        ui->fakturyEdAction->setEnabled(true);
        ui->fakturyUsunAction->setEnabled(true);
    } else {
        ui->fakturyEdAction->setDisabled(true);
        ui->fakturyUsunAction->setDisabled(true);
    }

    if (ui->tableK->rowCount() != 0) {
        ui->kontrahenciEdycjaAction->setEnabled(true);
        ui->kontrahenciUsunAction->setEnabled(true);
    } else {
        ui->kontrahenciEdycjaAction->setDisabled(true);
        ui->kontrahenciUsunAction->setDisabled(true);
    }

    if (ui->tableT->rowCount() != 0) {
        ui->towaryEdycjaAction->setEnabled(true);
        ui->towaryUsunAction->setEnabled(true);
    } else {
        ui->towaryEdycjaAction->setDisabled(true);
        ui->towaryUsunAction->setDisabled(true);
    }


	// choose data access mode
	dl = new XmlDataLayer();

	// towary/uslugi - wymiary
    ui->tableT->setColumnWidth(0, sett().value("towCol0", QVariant(50)) .toInt());
    ui->tableT->setColumnWidth(1, sett().value("towCol1", QVariant(140)) .toInt());
    ui->tableT->setColumnWidth(3, sett().value("towCol2", QVariant(40)) .toInt());
    ui->tableT->setColumnWidth(4, sett().value("towCol3", QVariant(60)) .toInt());
    ui->tableT->setColumnWidth(5, sett().value("towCol4", QVariant(50)) .toInt());
    ui->tableT->setColumnWidth(6, sett().value("towCol5", QVariant(55)) .toInt()); // netto1
    ui->tableT->setColumnWidth(7, sett().value("towCol6", QVariant(55)) .toInt()); // netto2
    ui->tableT->setColumnWidth(8, sett().value("towCol7", QVariant(55)) .toInt()); // netto3
    ui->tableT->setColumnWidth(9, sett().value("towCol8", QVariant(55)) .toInt());; // netto4
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


    qDebug() << "Ścieżka aplikacji: " << QStandardPaths::standardLocations(QStandardPaths::AppDataLocation).at(2);


	// connect slots
    connect(ui->actionBug, SIGNAL (triggered()), this, SLOT(reportBug()));
    connect(ui->applyFiltrBtn, SIGNAL (clicked(bool)), this, SLOT(rereadHist(bool)));
    connect(ui->plikDane_firmyAction, SIGNAL(triggered()), this, SLOT(daneFirmyClick()));
    connect(ui->plikKoniecAction, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->kontrahenciDodajAction, SIGNAL(triggered()), this, SLOT(kontrClick()));
    connect(ui->kontrahenciUsunAction, SIGNAL(triggered()), this, SLOT(kontrDel()));
    connect(ui->kontrahenciEdycjaAction, SIGNAL(triggered()), this, SLOT(kontrEd()));
    connect(ui->fakturyDodajAction, SIGNAL(triggered()), this, SLOT(newFra()));
    connect(ui->fakturyUsunAction, SIGNAL(triggered()), this, SLOT(delFHist()));
    connect(ui->fakturyEdAction, SIGNAL(triggered()), this, SLOT(editFHist()));
    connect(ui->fakturyDuplikatAction, SIGNAL(triggered()), this, SLOT(newDuplikat()));
    connect(ui->fakturyBruttoAction, SIGNAL(triggered()), this, SLOT(newFBrutto()));
    connect(ui->fakturyRachunekAction, SIGNAL(triggered()), this, SLOT(newFRachunek()));
    connect(ui->fakturyKorektaAction, SIGNAL(triggered()), this, SLOT(newKor()));
    connect(ui->fakturyPFormaAction, SIGNAL(triggered()), this, SLOT(newPForm()));
    connect(ui->towaryDodajAction, SIGNAL(triggered()), this, SLOT(towaryDodaj()));
    connect(ui->towaryEdycjaAction, SIGNAL(triggered()), this, SLOT(towaryEdycja()));
    connect(ui->towaryUsunAction, SIGNAL(triggered()), this, SLOT(towaryUsun()));
    connect(ui->pomocO_QtAction, SIGNAL(triggered()), this, SLOT(aboutQt()));
    connect(ui->pomocO_programieAction, SIGNAL(triggered()), this, SLOT(oProg()));
    connect(ui->plikUstawieniaAction, SIGNAL(triggered()), this, SLOT(settClick()));
    connect(ui->pomocPomocAction, SIGNAL(triggered()), this, SLOT(pomoc()));
    connect(ui->action_Qt, SIGNAL(triggered()), this, SLOT(aboutQt()));
    connect(ui->tableH, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(editFHist()));
    connect(ui->tableH, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showTableMenuH(QPoint)));
    connect(ui->tableK, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(kontrEd()));
    connect(ui->tableK, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showTableMenuK(QPoint)));
    connect(ui->tableT, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(towaryEdycja()));
    connect(ui->tableT, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showTableMenuT(QPoint)));

    connect(ui->tableH, SIGNAL(itemClicked(QTableWidgetItem *)), this, SLOT(mainUpdateStatus(QTableWidgetItem *)));
    connect(ui->tableK, SIGNAL(itemClicked(QTableWidgetItem *)), this, SLOT(mainUpdateStatus(QTableWidgetItem *)));
    connect(ui->tableT, SIGNAL(itemClicked(QTableWidgetItem *)), this, SLOT(mainUpdateStatus(QTableWidgetItem *)));
    connect(ui->tableK, SIGNAL (cellClicked(int, int)), this, SLOT(openWebTableK(int,int)));


	readKontr();
	readHist();
	readTw();

	loadPlugins();
}


/**
 *  Loads PyQt plugins
 */
void MainWindow::loadPlugins() {
	QDir allFiles;
	QString text, path;
	path = sett().getWorkingDir() + "/plugins/";
	allFiles.setPath(path);
	allFiles.setFilter(QDir::Files);
	QStringList filters;
	filters << "*.py" << "*.Py" << "*.PY" << "*.pY";
	allFiles.setNameFilters(filters);
	QStringList files = allFiles.entryList();
	int i, max = files.count();
	for (i = 0; i < max; ++i) {
		QFile skrypt(path + allFiles[i]);
		if (!skrypt.open(QIODevice::ReadOnly)) {
			// return;
		} else {
			QTextStream t(&skrypt);
			t.readLine ();
			QAction *action = new QAction(t.readLine ().remove ("# "), this);
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
		// set dates for filter
        ui->filtrStart->setDate(QDate::currentDate());
        ui->filtrEnd->setDate(QDate::currentDate());
		return ok;
	} else {
		sett().checkSettings();
		return ok;
	}

}


void MainWindow::openWebTableK(int row,int column)
{

    if (column == 6)
        {
        if (!ui->tableK->item(row,column)->text().isEmpty() && (ui->tableK->item(row,column)->text() != "-"))
            QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
            QDesktopServices::openUrl(QUrl(ui->tableK->item(row,column)->text(), QUrl::TolerantMode));
            QApplication::restoreOverrideCursor();
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
	// save filtr
    sett().setValue("filtrStart", ui->filtrStart->text());
    sett().setValue("filtrEnd", ui->filtrEnd->text());

	saveColumnWidth();

	// save unsaved
	sett().sync();
}


/** Clears content of the QTableWidget passed in the input
 *  @param QTableWidget
 */
void MainWindow::tableClear(QTableWidget * tab) {
	// should be a better method to do that
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

/** Reads the invoices from the directory passed in the input.
 *  @param QString - directory from where the invoices should be read
 */
void MainWindow::readHist() {
	QVector<InvoiceData> invoicesVec;
    invoicesVec = dl->invoiceSelectAllData(ui->filtrStart->date(), ui->filtrEnd->date());
    ui->tableH->setSortingEnabled(false);

	for (int i = 0; i < invoicesVec.size(); ++i) {
        insertRow(ui->tableH, ui->tableH->rowCount());
		QString text = invoicesVec.at(i).id;
        ui->tableH->item(ui->tableH->rowCount() - 1, 0)->setText(text);
        qDebug("Dodano id pliku");
		text = invoicesVec.at(i).frNr;
        ui->tableH->item(ui->tableH->rowCount() - 1, 1)->setText(text);
        qDebug("Dodano no pliku");
        ui->tableH -> setItem(ui->tableH->rowCount() - 1, 2, new DateWidgetItem(invoicesVec.at(i).sellingDate));
        qDebug("Dodano date pliku");
		text = invoicesVec.at(i).type;
        ui->tableH->item(ui->tableH->rowCount() - 1, 3)->setText(text);
        qDebug("Dodano typ pliku");
		text = invoicesVec.at(i).custName;
        ui->tableH->item(ui->tableH->rowCount() - 1, 4)->setText(text);
        qDebug("Dodano nazwe kontrahenta pliku");
		text = invoicesVec.at(i).custTic;
        ui->tableH->item(ui->tableH->rowCount() - 1, 5)->setText(text);
        qDebug("Dodano nip pliku");
    }
    ui->tableH->setSortingEnabled(true);
}

/** Reads customers from the XML
 */
void MainWindow::readKontr() {
    tableClear(ui->tableK);
    ui->tableK->setSortingEnabled(false);
	QVector<KontrData> kontrVec = dl->kontrahenciSelectAllData();
	for (int i = 0; i < kontrVec.size(); ++i) {
        qDebug() << "liczba kolumn: " << ui->tableK->columnCount();
        insertRow(ui->tableK, ui->tableK->rowCount());
		QString text = kontrVec.at(i).name;
        ui->tableK->item(ui->tableK->rowCount() - 1, 0)->setText(text);
		text = kontrVec.at(i).type;
        ui->tableK->item(ui->tableK->rowCount() - 1, 1)->setText(text);
		text = kontrVec.at(i).place;
        ui->tableK->item(ui->tableK->rowCount() - 1, 2)->setText(text);
		text = kontrVec.at(i).address;
        ui->tableK->item(ui->tableK->rowCount() - 1, 3)->setText(text);
		text = kontrVec.at(i).phone;
        ui->tableK->item(ui->tableK->rowCount() - 1, 4)->setText(text);
        text = kontrVec.at(i).email;
        qDebug() << "liczba kolumn: " << ui->tableK->columnCount();
        ui->tableK->item(ui->tableK->rowCount() - 1, 5)->setText(text);
        text = kontrVec.at(i).www;
        ui->tableK->item(ui->tableK->rowCount() - 1, 6)->setText(text);
        ui->tableK->item(ui->tableK->rowCount() - 1, 6)->setTextColor(QColor(30,144,255));

	}
    ui->tableK->setSortingEnabled(true);
}

/** Reads goods from the XML
 */
void MainWindow::readTw() {
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
	// qDebug() << __FUNCTION__;
	// for now not really used could be deleted
	if (event->key() == Qt::Key_F5) {
		newFra();
	}
	if (event->key() == Qt::Key_Return) {
		// int tabNo = tabWidget2-
        switch (ui->tabWidget2->currentIndex()) {
		case 0: {
			editFHist();
			break;
		}
		case 1: {
			kontrEd();
			break;
		}
		case 2: {
			towaryEdycja();
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

	QString program = "python";

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
}

/** Slot
 *  Show context menu
 */
void MainWindow::showTableMenuT(QPoint p) {
	// qDebug() << __FUNCTION__ << __LINE__;
    QMenu *menuTableT = new QMenu(ui->tableT);
    menuTableT->addAction(ui->towaryDodajAction);
    menuTableT->addAction(ui->towaryUsunAction);
    menuTableT->addAction(ui->towaryEdycjaAction);
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
    menuTable->addAction(ui->kontrahenciDodajAction);
    menuTable->addAction(ui->kontrahenciUsunAction);
    menuTable->addAction(ui->kontrahenciEdycjaAction);
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
    menuTable->addAction(ui->fakturyDodajAction);
    menuTable->addAction(ui->fakturyBruttoAction);
    menuTable->addAction(ui->fakturyRachunekAction);
	menuTable->addSeparator();
    menuTable->addAction(ui->fakturyPFormaAction);
    menuTable->addAction(ui->fakturyKorektaAction);
    menuTable->addAction(ui->fakturyDuplikatAction);
	menuTable->addSeparator();
    menuTable->addAction(ui->fakturyEdAction);
    menuTable->addAction(ui->fakturyUsunAction);
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
	QStatusBar* stat = dynamic_cast<QMainWindow *>(this)->statusBar();

	QTableWidget *table = item->tableWidget();
	QString message;
	message += table->horizontalHeaderItem(1)->text() + " : " + table->item(item->row(), 1)->text() + ", ";
	message += table->horizontalHeaderItem(2)->text() + " : " + table->item(item->row(), 2)->text() + ", ";
	message += table->horizontalHeaderItem(3)->text() + " : " + table->item(item->row(), 3)->text();

	stat->showMessage(trUtf8("Wybrana pozycja: ") + message);
}

/** Slot which enables/disables menu. It's possible to add/remove goods/customers
 *  only if this is the current tab.
 */
void MainWindow::tabChanged() {

	// disable Edit and Remove actions _ONLY_

		// historia
        if (ui->tableH->rowCount() != 0) {
            ui->fakturyEdAction->setEnabled(true);
            ui->fakturyUsunAction->setEnabled(true);
        } else {
            ui->fakturyEdAction->setDisabled(true);
            ui->fakturyUsunAction->setDisabled(true);
        }

		// kontrahenci
        if (ui->tableK->rowCount() != 0) {
        ui->kontrahenciEdycjaAction->setEnabled(true);
        ui->kontrahenciUsunAction->setEnabled(true);
        } else {
        ui->kontrahenciEdycjaAction->setDisabled(true);
        ui->kontrahenciUsunAction->setDisabled(true);
        }

		// towary
        if (ui->tableT->rowCount() != 0) {
        ui->towaryEdycjaAction->setEnabled(true);
        ui->towaryUsunAction->setEnabled(true);
        } else {
        ui->towaryEdycjaAction->setDisabled(true);
        ui->towaryUsunAction->setDisabled(true);
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
void MainWindow::oProg() {

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

    int row;
    QList<QTableWidgetItem *> selected = ui->tableH->selectedItems();
    row = selected[0]->row();

    if (ui->tableH->item(row, 3)->text() == trUtf8("korekta")) {
        // QMessageBox::information( this, trUtf8("QFaktury"), "Jeszcze nie ma", QMessageBox::Ok );
        Korekta *korWindow = new Korekta(this, dl, s_CORRECT_TITLE);
        korWindow->korektaInit(true);
        korWindow->readCorrData(ui->tableH->item(row, 0)->text());
        if (korWindow->exec() == QDialog::Accepted) {
            // edit window shouln't return anything
            rereadHist(true);
        }
        if (korWindow->kAdded) readKontr();
        delete korWindow;
        korWindow = NULL;
    }

    if (ui->tableH->item(row, 3)->text() == trUtf8("kbrutto")) {
        // QMessageBox::information( this, trUtf8("QFaktury"), "Jeszcze nie ma", QMessageBox::Ok );
        KorektaBrutto *korWindow = new KorektaBrutto(this, dl, s_CORRECT_TITLE);
        korWindow->korektaInit(true);
        korWindow->readCorrData(ui->tableH->item(row, 0)->text());
        if (korWindow->exec() == QDialog::Accepted) {
            // edit window shouln't return anything
            rereadHist(true);
        }
        if (korWindow->kAdded) readKontr();
        delete korWindow;
        korWindow = NULL;
    }


    if (ui->tableH->item(row, 3)->text() == trUtf8("rachunek")) {
        // QMessageBox::information( this, trUtf8("QFaktury"), "Jeszcze nie ma", QMessageBox::Ok );
        Rachunek *raWindow = new Rachunek(this, dl, s_BILL);
        raWindow->readData(ui->tableH->item(row, 0)->text(), 0);
        raWindow->fName = ui->tableH->item(row, 0)->text();
        raWindow->rachunekInit();
        raWindow->setWindowTitle(trUtf8("Edytuje Rachunek"));
        if (raWindow->exec() == QDialog::Accepted) {
            // edit window shouln't return anything
            //raWindow->fName = "";
            rereadHist(true);
        }
        if (raWindow->kAdded) readKontr();
        delete raWindow;
        raWindow = NULL;
    }

    if (ui->tableH->item(row, 3)->text() == trUtf8("FVAT")) {
        // qDebug ("%s %s:%d", __FUNCTION__, __FILE__, __LINE__);
        Faktura *fraWindow = new Faktura(this, dl, s_INVOICE);
        // qDebug() << pdGlob;

            int co = 0;

        fraWindow->readData(ui->tableH->item(row, 0)->text(), co);
        fraWindow->fName = ui->tableH->item(row, 0)->text();
        if (fraWindow->exec() == QDialog::Accepted) {
            //fraWindow->fName = "";
            rereadHist(true);
        }
        if (fraWindow->kAdded) readKontr();
        delete fraWindow;
        fraWindow = NULL;
    }

    if (ui->tableH->item(row, 3)->text() == trUtf8("FPro")) {
        // qDebug ("%s %s:%d", __FUNCTION__, __FILE__, __LINE__);
        Faktura *fraWindow = new Faktura(this, dl, s_PROFORMA);
        // qDebug() << pdGlob;
            int co = 1;

        fraWindow->readData(ui->tableH->item(row, 0)->text(), co);
        fraWindow->fName = ui->tableH->item(row, 0)->text();
        if (fraWindow->exec() == QDialog::Accepted) {
            //fraWindow->fName = "";
            rereadHist(true);
        }
        if (fraWindow->kAdded) readKontr();
        delete fraWindow;
        fraWindow = NULL;
    }

    if (ui->tableH->item(row, 3)->text() == trUtf8("FBrutto")) {
        // qDebug ("%s %s:%d", __FUNCTION__, __FILE__, __LINE__);
        FakturaBrutto *fraWindow = new FakturaBrutto(this, dl, s_FBRUTTO);
        // qDebug() << pdGlob;
        int co = 0;

        fraWindow->readData(ui->tableH->item(row, 0)->text(), co);
        fraWindow->fName = ui->tableH->item(row, 0)->text();
        if (fraWindow->exec() == QDialog::Accepted) {
            //fraWindow->fName = "";
            rereadHist(true);
        }
        if (fraWindow->kAdded) readKontr();
        delete fraWindow;
        fraWindow = NULL;
    }

    if (ui->tableH->item(row, 3)->text() == trUtf8("FBPro")) {
        // qDebug ("%s %s:%d", __FUNCTION__, __FILE__, __LINE__);
        FakturaBrutto *fraWindow = new FakturaBrutto(this, dl, s_FBRUTTO);
        // qDebug() << pdGlob;

            int co = 1;
        fraWindow->readData(ui->tableH->item(row, 0)->text(), co);
        fraWindow->fName = ui->tableH->item(row, 0)->text();
        if (fraWindow->exec() == QDialog::Accepted) {
            //fraWindow->fName = "";
            rereadHist(true);
        }
        if (fraWindow->kAdded) readKontr();
        delete fraWindow;
        fraWindow = NULL;
    }

    if (ui->tableH->item(row, 3)->text() == trUtf8("duplikat")) {
        // qDebug ("%s %s:%d", __FUNCTION__, __FILE__, __LINE__);
        Duplikat *dupWindow = new Duplikat(this, dl, s_DUPLICATE);
        dupWindow->editMode = true;
        // qDebug() << pdGlob;

            int co = 2;
        dupWindow->readData(ui->tableH->item(row, 0)->text(), co);
        dupWindow->duplikatInit();
        dupWindow->setIsEditAllowed(false);
        dupWindow->fName = ui->tableH->item(row, 0)->text();
        if (dupWindow->exec() == QDialog::Accepted) {
            //dupWindow->fName = "";
            rereadHist(true);
        }
        if (dupWindow->kAdded) readKontr();
        delete dupWindow;
        dupWindow = NULL;
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
	}

}

/** Slot used to edit data of the current company
 */
void MainWindow::daneFirmyClick() {


	// qDebug("%s %s:%d", __FUNCTION__, __FILE__, __LINE__);
	Uzytkownik *daneFirmyWindow = new Uzytkownik(this);
	daneFirmyWindow->exec();
	delete daneFirmyWindow;
	daneFirmyWindow = NULL;

}

/** Slot used to edit edit sett()
 */
void MainWindow::settClick() {
	// qDebug ("%s %s:%d", __FUNCTION__, __FILE__, __LINE__);
	Ustawienia *settWindow = new Ustawienia(this);
	settWindow->exec();
	delete settWindow;
	settWindow = NULL;
}

/** Slot used to add new customer
 */
void MainWindow::kontrClick() {
	Kontrahenci *kontrWindow;
	kontrWindow = new Kontrahenci(this, 0, dl);
	//qDebug ("%s %s:%d", __FUNCTION__, __FILE__, __LINE__);
	if (kontrWindow->exec() == QDialog::Accepted) {
        ui->tableK->setSortingEnabled(false);
        insertRow(ui->tableK, ui->tableK->rowCount());
		QStringList row = kontrWindow->ret.split("|");
        ui->tableK->item(ui->tableK->rowCount() - 1, 0)->setText(row[0]); // name
        ui->tableK->item(ui->tableK->rowCount() - 1, 1)->setText(row[1]); // type
        ui->tableK->item(ui->tableK->rowCount() - 1, 2)->setText(row[2]); // place
        ui->tableK->item(ui->tableK->rowCount() - 1, 3)->setText(row[3]); // address
        ui->tableK->item(ui->tableK->rowCount() - 1, 4)->setText(row[4]); // telefon
        ui->tableK->item(ui->tableK->rowCount() - 1, 5)->setText(row[5]); // email
        ui->tableK->item(ui->tableK->rowCount() - 1, 6)->setText(row[6]); // www
        ui->tableK->setSortingEnabled(true);
	}
	delete kontrWindow;
	kontrWindow = NULL;
}

/** Slot used to delete current customer
 */
void MainWindow::kontrDel() {
    if (ui->tableK->selectedItems().count() <= 0) {
		QMessageBox::information(this, trUtf8("QFaktury"), trUtf8("Kontrahent nie wybrany. Nie mozna usuwac."), trUtf8("Ok"), 0, 0, 1);
		return;
	}

	if (QMessageBox::warning(this, trUtf8("QFaktury"), trUtf8("Czy napewno chcesz usunąć kontrahenta: ") +
            ui->tableK->item(ui->tableK->currentRow(), 0)->text() + trUtf8(" ?"), trUtf8("Tak"), trUtf8("Nie"), 0, 0, 1) == 0) {
            dl->kontrahenciDeleteData(ui->tableK->item(ui->tableK->currentRow(), 0)->text());
            ui->tableK->removeRow(ui->tableK->currentRow());
	}
}

/** Slot used to edit customer
 */
void MainWindow::kontrEd() {
    if (ui->tableK->selectedItems().count() <= 0) {
		QMessageBox::information(this, trUtf8("QFaktury"), trUtf8("Kontrahent nie wybrany."), trUtf8("Ok"), 0, 0, 1);
		return;
	}

    int row = ui->tableK->selectedItems()[0]->row();

	Kontrahenci *kontrWindow = new Kontrahenci(this, 1, dl);
    kontrWindow->selectData(ui->tableK->item(row, 0)->text(),
            sett().getCustomerType(ui->tableK->item(row, 1)->text()));
	if (kontrWindow->exec() == QDialog::Accepted) {
        ui->tableK->setSortingEnabled(false);
		QStringList rowTxt = kontrWindow->ret.split("|");
        ui->tableK->item(row, 0)->setText(rowTxt[0]); // name
        ui->tableK->item(row, 1)->setText(rowTxt[1]); // type
        ui->tableK->item(row, 2)->setText(rowTxt[2]); // place
        ui->tableK->item(row, 3)->setText(rowTxt[3]); // address
        ui->tableK->item(row, 4)->setText(rowTxt[4]); // telefon
        ui->tableK->item(row, 5)->setText(rowTxt[5]); // telefon
        ui->tableK->item(row, 6)->setText(rowTxt[6]); // telefon
        ui->tableK->setSortingEnabled(true);
	}
	delete kontrWindow;
	kontrWindow = NULL;

}


/** Slot used for creating new invoices
 */
void MainWindow::newFra() {
    Faktura *fraWindow = new Faktura(this, dl, s_INVOICE);
	fraWindow->pforma = false;
	if (fraWindow->exec() == QDialog::Accepted) {
        ui->tableH->setSortingEnabled(false);
        insertRow(ui->tableH, ui->tableH->rowCount());
		QStringList row = fraWindow->ret.split("|");
        ui->tableH->item(ui->tableH->rowCount() - 1, 0)->setText(row[0]); // file name
        ui->tableH->item(ui->tableH->rowCount() - 1, 1)->setText(row[1]); // symbol
        ui->tableH->item(ui->tableH->rowCount() - 1, 2)->setText(row[2]); // date
        ui->tableH->item(ui->tableH->rowCount() - 1, 3)->setText(row[3]); // type
        ui->tableH->item(ui->tableH->rowCount() - 1, 4)->setText(row[4]); // nabywca
        ui->tableH->item(ui->tableH->rowCount() - 1, 5)->setText(row[5]); // NIP
        ui->tableH->setSortingEnabled(true);
	} else {
        rereadHist(true);
	}

	if (fraWindow->kAdded) readKontr();

	delete fraWindow;
	fraWindow = NULL;
}


/** Slot used for creating new invoices
 */
void MainWindow::newFRachunek() {
    Rachunek *fraWindow = new Rachunek(this, dl, s_BILL);
	fraWindow->pforma = false;
	fraWindow->setWindowTitle(trUtf8("Rachunek"));
	fraWindow->rachunekInit();
	if (fraWindow->exec() == QDialog::Accepted) {
        ui->tableH->setSortingEnabled(false);
        insertRow(ui->tableH, ui->tableH->rowCount());
		QStringList row = fraWindow->ret.split("|");
        ui->tableH->item(ui->tableH->rowCount() - 1, 0)->setText(row[0]); // file name
        ui->tableH->item(ui->tableH->rowCount() - 1, 1)->setText(row[1]); // symbol
        ui->tableH->item(ui->tableH->rowCount() - 1, 2)->setText(row[2]); // date
        ui->tableH->item(ui->tableH->rowCount() - 1, 3)->setText(row[3]); // type
        ui->tableH->item(ui->tableH->rowCount() - 1, 4)->setText(row[4]); // nabywca
        ui->tableH->item(ui->tableH->rowCount() - 1, 5)->setText(row[5]); // NIP
        ui->tableH->setSortingEnabled(true);
	} else {
        rereadHist(true);
	}

	if (fraWindow->kAdded) readKontr();
	delete fraWindow;
	fraWindow = NULL;
}


/** Slot used for creating new invoices
 */
void MainWindow::newFBrutto() {

    FakturaBrutto *fraWindow = new FakturaBrutto(this, dl, s_FBRUTTO);
	fraWindow->pforma = false;
	fraWindow->setWindowTitle(trUtf8("Faktura VAT Brutto"));

	if (fraWindow->exec() == QDialog::Accepted) {

        ui->tableH->setSortingEnabled(false);
        insertRow(ui->tableH, ui->tableH->rowCount());
		QStringList row = fraWindow->ret.split("|");
        ui->tableH->item(ui->tableH->rowCount() - 1, 0)->setText(row[0]); // file name
        ui->tableH->item(ui->tableH->rowCount() - 1, 1)->setText(row[1]); // symbol
        ui->tableH->item(ui->tableH->rowCount() - 1, 2)->setText(row[2]); // date
        ui->tableH->item(ui->tableH->rowCount() - 1, 3)->setText(row[3]); // type
        ui->tableH->item(ui->tableH->rowCount() - 1, 4)->setText(row[4]); // nabywca
        ui->tableH->item(ui->tableH->rowCount() - 1, 5)->setText(row[5]); // NIP
        ui->tableH->setSortingEnabled(true);

	} else {
        rereadHist(true);
	}

	if (fraWindow->kAdded) readKontr();
	delete fraWindow;
	fraWindow = NULL;
}


/** Slot used to create new ProForma Invoice
 */
void MainWindow::newPForm() {
    Faktura *fraWindow = new Faktura(this, dl, s_PROFORMA);
	fraWindow->pforma = true;
	fraWindow->setWindowTitle(trUtf8("Faktura Pro Forma"));
	fraWindow->backBtnClick();
	if (fraWindow->exec() == QDialog::Accepted) {
        ui->tableH->setSortingEnabled(false);
        insertRow(ui->tableH, ui->tableH->rowCount());
		QStringList row = fraWindow->ret.split("|");
        ui->tableH->item(ui->tableH->rowCount() - 1, 0)->setText(row[0]); // file name
        ui->tableH->item(ui->tableH->rowCount() - 1, 1)->setText(row[1]); // symbol
        ui->tableH->item(ui->tableH->rowCount() - 1, 2)->setText(row[2]); // date
        ui->tableH->item(ui->tableH->rowCount() - 1, 3)->setText(row[3]); // type
        ui->tableH->item(ui->tableH->rowCount() - 1, 4)->setText(row[4]); // nabywca
        ui->tableH->item(ui->tableH->rowCount() - 1, 5)->setText(row[5]); // NIP
        ui->tableH->setSortingEnabled(true);
	} else {
        rereadHist(true);
	}

	if (fraWindow->kAdded) readKontr();
	delete fraWindow;
	fraWindow = NULL;
}

/** Slot used to create new Korkta
 */
void MainWindow::newKor() {
    if (ui->tableH->selectedItems().count() <= 0) {
		QMessageBox::information(this, trUtf8("QFaktury"), trUtf8("Faktura nie wybrana. Wybierz fakurę, do której chcesz wystawić korektę."), trUtf8("Ok"), 0, 0, 1);
		return;
	}

    int row = ui->tableH->selectedItems()[0]->row();

	QStringList invTypes;
	invTypes << "FVAT" << "FBrutto";

    if (invTypes.contains(ui->tableH->item(row, 3)->text())) {
        ui->tableH->setSortingEnabled(false);

		Korekta *korWindow;

        if (ui->tableH->item(row, 3)->text().contains("FVAT")) {
            korWindow = new Korekta(this, dl, s_CORRECT_TITLE);
		} else  {
            korWindow = new KorektaBrutto(this, dl, s_CORRECT_BRUTTO);
		}

		korWindow->korektaInit(false);
		// qDebug( pdGlob );
        korWindow->readData(ui->tableH->item(row, 0)->text(), 3);
		korWindow->setWindowTitle(trUtf8("Nowa korekta"));
		if (korWindow->exec() == QDialog::Accepted) {
            insertRow(ui->tableH, ui->tableH->rowCount());
            // qDebug() << korWindow->ret;
			QStringList row = korWindow->ret.split("|");
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
		if (korWindow->kAdded) readKontr();
		delete korWindow;
		korWindow = NULL;
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
void MainWindow::newDuplikat() {
    if (ui->tableH->selectedItems().count() <= 0) {
		QMessageBox::information(this, trUtf8("QFaktury"), trUtf8("Faktura nie wybrana. Wybierz fakurę, do której chcesz wystawić duplikat."), trUtf8("Ok"), 0, 0, 1);
		return;
	}
    int row = ui->tableH->selectedItems()[0]->row();

	// types of invoices for which it's ok to issue a duplicate
	QStringList invTypes;
	invTypes << "FVAT" << "FBrutto";

    if (invTypes.contains(ui->tableH->item(row, 3)->text())) {
        Duplikat *dupWindow = new Duplikat(this, dl, s_DUPLICATE);

        // qDebug( pdGlob );
        dupWindow->readData(ui->tableH->item(row, 0)->text(), 2);
		dupWindow->setWindowTitle(trUtf8("Nowy duplikat"));
        dupWindow->duplikatInit();
		if (dupWindow->exec() == QDialog::Accepted) {
            insertRow(ui->tableH, ui->tableH->rowCount());
            // qDebug() << korWindow->ret;
            QStringList row = dupWindow->ret.split("|");
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

        if (dupWindow->kAdded) readKontr();
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
void MainWindow::towaryDodaj() {
	Towary *towWindow = new Towary(this, 0, dl);
	if (towWindow->exec() == QDialog::Accepted) {
        ui->tableT->setSortingEnabled(false);
        insertRow(ui->tableT, ui->tableT->rowCount());
		QStringList row = towWindow->ret.split("|");
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
	delete towWindow;
	towWindow = NULL;
}

/** Slot used to delete goods
 */
void MainWindow::towaryUsun() {
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
void MainWindow::towaryEdycja() {
    if (ui->tableT->selectedItems().count() <= 0) {
		QMessageBox::information(this, trUtf8("QFaktury"), trUtf8("Towar nie wybrany. Nie można edytować."), trUtf8("Ok"), 0, 0, 1);
		return;
	}
    int row = ui->tableT->selectedItems()[0]->row();

	Towary *towWindow = new Towary(this, 1, dl);
	// qDebug() << tableT->item(row, 5)->text() << sett().getProductType(tableT->item(row, 5)->text());
    towWindow->selectData(ui->tableT->item(row, 0)->text(),
            sett().getProductType(ui->tableT->item(row, 5)->text()));
	if (towWindow->exec() == QDialog::Accepted) {
        ui->tableT->setSortingEnabled(false);
		QStringList rowTxt = towWindow->ret.split("|");
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
	delete towWindow;
	towWindow = NULL;
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
void MainWindow::pomoc() {
    QDesktopServices::openUrl(QUrl("https://github.com/juliagoda/qfaktury"));
}

/** Slot reportBug
 */
void MainWindow::reportBug() {
    QDesktopServices::openUrl(QUrl("https://github.com/juliagoda/qfaktury/issues"));
}

// ----------------------------------------  SLOTS ---------------------------------//




