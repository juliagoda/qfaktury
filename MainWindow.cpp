#include "MainWindow.moc"
#include <qtextcodec.h>
#include <qdir.h>
#include <qmessagebox.h>
#include <qapplication.h>
#include <qevent.h>
#include <qprocess.h>
#include <Qt/qdom.h>
#include <QTextStream>
#include <QtDebug>

#include "Podglad.h"
#include "Ustawienia.h"
#include "Uzytkownik.h"
#include "Towary.h"
#include "Faktura.h"
#include "Korekta.h"
#include "Kontrahenci.h"
#include "config.h"


QString pdGlob;


/** Constructor
 */
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {
    setupUi(this);
    init();
}

/**
 * init() method
 */
void MainWindow::init() {
	// working direcroty
	QDir tmp;
	QString progDir = tmp.homePath() + "/elinux"; // move to settings
	pdGlob = progDir;

	if (!tmp.exists(progDir)) {
		tmp.mkdir(progDir);
		tmp.mkdir(progDir + "/faktury");
	}

	if (!tmp.exists(progDir + "/faktury")) {
		tmp.mkdir(progDir + "/faktury");
	}

	// first run
	if (firstRun()) {
		// towary/uslugi - wymiary
		tableT->setColumnWidth(0, 50);
		tableT->setColumnWidth(1, 140);
		tableT->setColumnWidth(3, 40);
		tableT->setColumnWidth(4, 60);
		tableT->setColumnWidth(5, 50);
		tableT->setColumnWidth(6, 55); // netto1
		tableT->setColumnWidth(7, 55); // netto2
		tableT->setColumnWidth(8, 55); // netto3
		tableT->setColumnWidth(9, 55); // netto4
		tableT->setColumnWidth(10, 55);

		// qDebug("firstRun");
		saveAllSettAsDefault();
	} else {
		// qDebug() << settings.getValueAsDate("filtrStart")
		//		<< settings.getValueAsDate("filtrEnd");

		filtrStart->setDisplayFormat(settings.getDateFormat());
		filtrStart->setDate(settings.getValueAsDate("filtrStart"));
		filtrEnd->setDisplayFormat(settings.getDateFormat());
		filtrEnd->setDate(settings.getValueAsDate("filtrEnd"));
	}

	// towary/uslugi - wymiary
	tableT->setColumnWidth(0, settings.value("towCol0", QVariant(50)) .toInt());
	tableT->setColumnWidth(1, settings.value("towCol1", QVariant(140)) .toInt());
	tableT->setColumnWidth(3, settings.value("towCol2", QVariant(40)) .toInt());
	tableT->setColumnWidth(4, settings.value("towCol3", QVariant(60)) .toInt());
	tableT->setColumnWidth(5, settings.value("towCol4", QVariant(50)) .toInt());
	tableT->setColumnWidth(6, settings.value("towCol5", QVariant(55)) .toInt()); // netto1
	tableT->setColumnWidth(7, settings.value("towCol6", QVariant(55)) .toInt()); // netto2
	tableT->setColumnWidth(8, settings.value("towCol7", QVariant(55)) .toInt()); // netto3
	tableT->setColumnWidth(9, settings.value("towCol8", QVariant(55)) .toInt());; // netto4
	tableT->setColumnWidth(10, settings.value("towCol9", QVariant(55)) .toInt());

	tableH->setColumnWidth(0, settings.value("histCol0", QVariant(0)) .toInt());
	tableH->setColumnWidth(1, settings.value("histCol1", QVariant(40)) .toInt());
	tableH->setColumnWidth(3, settings.value("histCol2", QVariant(40)) .toInt());
	tableH->setColumnWidth(4, settings.value("histCol3", QVariant(140)) .toInt());
	tableH->setColumnWidth(5, settings.value("histCol4", QVariant(50)) .toInt());

	tableK->setColumnWidth(0, settings.value("custCol0", QVariant(50)) .toInt());
	tableK->setColumnWidth(1, settings.value("custCol1", QVariant(140)) .toInt());
	tableK->setColumnWidth(3, settings.value("custCol2", QVariant(40)) .toInt());
	tableK->setColumnWidth(4, settings.value("custCol3", QVariant(60)) .toInt());
	tableK->setColumnWidth(5, settings.value("custCol4", QVariant(50)) .toInt());

	// add Icon
	QIcon icon;
	icon.addPixmap(QPixmap(":/res/share/qfaktury/icons/qfaktury_48.png"),
			QIcon::Normal, QIcon::Off);
	this->setWindowIcon(icon);
	this->setWindowTitle(qAppName() + " - " + UTF8("Wersja ") + STRING(QFAKTURY_VERSION));

	// connect slots
	connect(actionForum, SIGNAL (activated ()), this, SLOT(forum()));
	connect(applyFiltrBtn, SIGNAL (clicked()), this, SLOT(rereadHist()));
	connect(plikDane_firmyAction, SIGNAL(activated()), this, SLOT(daneFirmyClick()));
	connect(plikKoniecAction, SIGNAL(activated()), this, SLOT(close()));
	connect(kontrahenciDodajAction, SIGNAL(activated()), this, SLOT(kontrClick()));
	connect(kontrahenciUsunAction, SIGNAL(activated()), this, SLOT(kontrDel()));
	connect(kontrahenciEdycjaAction, SIGNAL(activated()), this, SLOT(kontrEd()));
	connect(fakturyDodajAction, SIGNAL(activated()), this, SLOT(newFra()));
	connect(fakturyUsunAction, SIGNAL(activated()), this, SLOT(delFHist()));
	connect(fakturyEdAction, SIGNAL(activated()), this, SLOT(editFHist()));
	connect(pomocO_QtAction, SIGNAL(activated()), this, SLOT(aboutQt()));
	connect(pomocO_programieAction, SIGNAL(activated()), this, SLOT(oProg()));
	connect(plikUstawieniaAction, SIGNAL(activated()), this, SLOT(settClick()));
	connect(tabWidget2, SIGNAL(currentChanged(QWidget*)), this, SLOT(tabChanged(QWidget*)));
	connect(pomocPomocAction, SIGNAL(activated()), this, SLOT(pomoc()));
	connect(towaryDodajAction, SIGNAL(activated()), this, SLOT(towaryDodaj()));
	connect(towaryEdycjaAction, SIGNAL(activated()), this, SLOT(towaryEdycja()));
	connect(towaryUsunAction, SIGNAL(activated()), this, SLOT(towaryUsun()));
	connect(fakturyKorektaAction, SIGNAL(activated()), this, SLOT(newKor()));
	connect(fakturyPFormaAction, SIGNAL(activated()), this, SLOT(newPForm()));
	connect(prevPageAction, SIGNAL(activated()), this, SLOT(prevPage()));
	connect(nextPageAction, SIGNAL(activated()), this, SLOT(nextPage()));
	connect(tableH, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(editFHist()));
	connect(tableK, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(kontrEd()));
	connect(tableT, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(towaryEdycja()));

	tabChanged(tabWidget2);

	readKontr(progDir);
	readHist(progDir);
	readTw(progDir);
}

/**
 * firstRun setup()
 */
bool MainWindow::firstRun() {
	bool ok = settings.value("firstrun").toBool();
	if (ok) {
		settings.checkSettings();
		// set dates for filter
		filtrStart->setDate(QDate::currentDate());
		filtrEnd->setDate(QDate::currentDate());
		return true;
	} else {
		settings.checkSettings();
		return false;
	}

}

/** save settings before quit
 * save column width
 */
void MainWindow::saveColumnWidth() {
	// width of the columns in the towary "goods" tab
	settings.setValue("towCol0", tableT->columnWidth(0));
	settings.setValue("towCol1", tableT->columnWidth(1));
	settings.setValue("towCol2", tableT->columnWidth(2));
	settings.setValue("towCol3", tableT->columnWidth(3));
	settings.setValue("towCol4", tableT->columnWidth(4));
	settings.setValue("towCol5", tableT->columnWidth(5));
	settings.setValue("towCol6", tableT->columnWidth(6));
	settings.setValue("towCol7", tableT->columnWidth(7));
	settings.setValue("towCol8", tableT->columnWidth(8));
	settings.setValue("towCol9", tableT->columnWidth(9));
	settings.setValue("towCol10", tableT->columnWidth(10));
	// width of the columns in the history tab
	settings.setValue("histCol0", tableH->columnWidth(0));
	settings.setValue("histCol1", tableH->columnWidth(1));
	settings.setValue("histCol2", tableH->columnWidth(2));
	settings.setValue("histCol3", tableH->columnWidth(3));
	settings.setValue("histCol4", tableH->columnWidth(4));
	settings.setValue("histCol5", tableH->columnWidth(5));
	// width of the columns in the customers tab
	settings.setValue("custCol0", tableK->columnWidth(0));
	settings.setValue("custCol1", tableK->columnWidth(1));
	settings.setValue("custCol2", tableK->columnWidth(2));
	settings.setValue("custCol3", tableK->columnWidth(3));
	settings.setValue("custCol4", tableK->columnWidth(4));
	settings.setValue("custCol5", tableK->columnWidth(5));
}

/** Saves all settings as default - first run
 */
void MainWindow::saveAllSettAsDefault() {
	settings.resetSettings();
}


/** Saves all settings
 */
void MainWindow::saveAllSett() {
	// save filtr
	settings.setValue("filtrStart", filtrStart->text());
	settings.setValue("filtrEnd", filtrEnd->text());

	saveColumnWidth();

	// save unsaved
	settings.sync();
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

/** Used while loading history, returns true if XML with the invoice should be read or not.
 *  Only files which names are in between the dates from filer on the UI should be read.
 *  @param QString - name of the file.
 */
bool MainWindow::applyFiltr(QString nameToCheck) {
	QString tmp = nameToCheck;
	tmp = tmp.remove("h");
	tmp = tmp.left(10);
	tmp = tmp.remove("-");

	// not very flexible
	// assumption is that date comes as yyyymmdd
	// if its otherwise order of remove methods has to be changed
	int year = tmp.left(4).toInt();
	tmp = tmp.remove(0, 4);
	int month = tmp.left(2).toInt();
	tmp = tmp.remove(0, 2);
	int day = tmp.left(2).toInt();
	tmp = tmp.remove(0, 2);
	QDate tmpDate(year, month, day);

	// if debugOn()
	// qDebug() << __FUNCTION__ << __LINE__ << nameToCheck
	//		<< filtrStart->date().toString()
	//		<< year << month << day
	//		<< tmpDate.toString()
	//		<< filtrEnd->date().toString();

	if (tmpDate < filtrStart->date()) {
		return false;
	}

	if (tmpDate > filtrEnd->date()) {
		return false;
	}

	// default true?
	return true;
}

/** Reads the invoices from the directory passed in the input.
 *  @param QString - directory from where the invoices should be read
 */
void MainWindow::readHist(QString progDir) {
	/*!
	 * step one: get list of files from directory
	 */
	QDir allFiles;
	QString text;

	QDomDocument doc("faktury");
	QDomElement root;
	QDomElement nadawca;
	QDomElement odbiorca;

	allFiles.setPath(progDir + "/faktury/");
	allFiles.setFilter(QDir::Files);
	QStringList filters;
	filters << "h*.xml";
	allFiles.setNameFilters(filters);
	QStringList files = allFiles.entryList();
	int i, max = files.count();
	for (i = 0; i < max; ++i) {
		if (applyFiltr(files[i])) {
			// qDebug() << files[i];
			insertRow(tableH, tableH->rowCount());
			text = files[i];
			tableH->item(tableH->rowCount() - 1, 0)->setText(text);

			QFile file(progDir + "/faktury/" + files[i]);

			if (!file.open(QIODevice::ReadOnly)) {
				qDebug("file doesn't exists");
				return;
			} else {
				QTextStream stream(&file);

				if (!doc.setContent(stream.readAll())) {
					// qDebug ("can not set content ");
					// qDebug( file.name() );
					file.close();
					// return;
				}
			}

			root = doc.documentElement();
			tableH->item(tableH->rowCount() - 1, 1)->setText(root.attribute(
					"no", "NULL"));
			tableH->item(tableH->rowCount() - 1, 2)->setText(root.attribute(
					"sellingDate", "NULL"));
			tableH->item(tableH->rowCount() - 1, 3)->setText(root.attribute(
					"type", "NULL"));
			QDomNode nab;
			nab = root.firstChild();
			nab = nab.toElement().nextSibling();
			tableH->item(tableH->rowCount() - 1, 4)->setText(
					nab.toElement().attribute("name", "NULL"));
			tableH->item(tableH->rowCount() - 1, 5)->setText(
					nab.toElement().attribute("tic", "NULL"));
		}
	}
}

/** Reads customers from the XML
 */
void MainWindow::readKontr(QString progDir) {
	QDomDocument doc("kontrahenci");
	QDomElement root;
	QDomElement urzad;
	QDomElement firma;

	QFile file(progDir + "/kontrah.xml");
	if (!file.open(QIODevice::ReadOnly)) {
		qDebug("file doesn't exists");
		return;

	} else {
		QTextStream stream(&file);
		if (!doc.setContent(stream.readAll())) {
			qDebug("can not set content ");
			file.close();
			return;
		} else {
			root = doc.documentElement();
			urzad = root.firstChild().toElement();
			firma = root.lastChild().toElement();
		}
		QString text;

		for (QDomNode n = firma.firstChild(); !n.isNull(); n = n.nextSibling()) {
			insertRow(tableK, tableK->rowCount());
			text = n.toElement().attribute("name");
			tableK->item(tableK->rowCount() - 1, 0)->setText(text);
			text = "firma";
			tableK->item(tableK->rowCount() - 1, 1)->setText(text);
			text = n.toElement().attribute("place");
			tableK->item(tableK->rowCount() - 1, 2)->setText(text);
			text = n.toElement().attribute("address");
			tableK->item(tableK->rowCount() - 1, 3)->setText(text);
			text = n.toElement().attribute("telefon");
			tableK->item(tableK->rowCount() - 1, 4)->setText(text);
		}

		for (QDomNode n = urzad.firstChild(); !n.isNull(); n = n.nextSibling()) {
			insertRow(tableK, tableK->rowCount());
			text = n.toElement().attribute("name");
			tableK->item(tableK->rowCount() - 1, 0)->setText(text);
			text = "urzad";
			tableK->item(tableK->rowCount() - 1, 1)->setText(text);
			text = n.toElement().attribute("place");
			tableK->item(tableK->rowCount() - 1, 2)->setText(text);
			text = n.toElement().attribute("address");
			tableK->item(tableK->rowCount() - 1, 3)->setText(text);
			text = n.toElement().attribute("telefon");
			tableK->item(tableK->rowCount() - 1, 4)->setText(text);
		}
	}
}

/** Reads goods from the XML
 */
void MainWindow::readTw(QString progDir) {
	QDomDocument doc("towary");
	QDomElement root;
	QDomElement towary;
	QDomElement uslugi;

	QFile file(progDir + "/towary.xml");
	if (!file.open(QIODevice::ReadOnly)) {
		qDebug("file doesn't exists");
		return;
	} else {
		QTextStream stream(&file);
		if (!doc.setContent(stream.readAll())) {
			qDebug("can't set content ");
			file.close();
			return;
		} else {
			root = doc.documentElement();
			towary = root.firstChild().toElement();
			uslugi = root.lastChild().toElement();
		}
		QString text;

		for (QDomNode n = towary.firstChild(); !n.isNull(); n = n.nextSibling()) {

			insertRow(tableT, tableT->rowCount());
			text = n.toElement().attribute("idx");
			tableT->item(tableT->rowCount() - 1, 0)->setText(text);
			// text = "towar";
			text = n.toElement().attribute("name");
			tableT->item(tableT->rowCount() - 1, 1)->setText(text);
			text = n.toElement().attribute("desc");
			tableT->item(tableT->rowCount() - 1, 2)->setText(text);
			text = n.toElement().attribute("code");
			tableT->item(tableT->rowCount() - 1, 3)->setText(text);
			text = n.toElement().attribute("pkwiu");
			tableT->item(tableT->rowCount() - 1, 4)->setText(text);
			text = "towar";
			tableT->item(tableT->rowCount() - 1, 5)->setText(text);
			text = n.toElement().attribute("curr");
			tableT->item(tableT->rowCount() - 1, 6)->setText(text);
			text = n.toElement().attribute("netto1");
			tableT->item(tableT->rowCount() - 1, 7)->setText(text);
			text = n.toElement().attribute("netto2");
			tableT->item(tableT->rowCount() - 1, 8)->setText(text);
			text = n.toElement().attribute("netto3");
			tableT->item(tableT->rowCount() - 1, 9)->setText(text);
			text = n.toElement().attribute("netto4");
			tableT->item(tableT->rowCount() - 1, 10)->setText(text);
			text = n.toElement().attribute("vat");
			tableT->item(tableT->rowCount() - 1, 11)->setText(text);
		}

		for (QDomNode n = uslugi.firstChild(); !n.isNull(); n = n.nextSibling()) {
			insertRow(tableT, tableT->rowCount());
			text = n.toElement().attribute("idx");
			tableT->item(tableT->rowCount() - 1, 0)->setText(text);
			// text = "towar";
			text = n.toElement().attribute("name");
			tableT->item(tableT->rowCount() - 1, 1)->setText(text);
			text = n.toElement().attribute("desc");
			tableT->item(tableT->rowCount() - 1, 2)->setText(text);
			text = n.toElement().attribute("code");
			tableT->item(tableT->rowCount() - 1, 3)->setText(text);
			text = n.toElement().attribute("pkwiu");
			tableT->item(tableT->rowCount() - 1, 4)->setText(text);
			text = "usÅ‚uga";
			tableT->item(tableT->rowCount() - 1, 5)->setText(text);
			text = n.toElement().attribute("curr");
			tableT->item(tableT->rowCount() - 1, 6)->setText(text);
			text = n.toElement().attribute("netto1");
			tableT->item(tableT->rowCount() - 1, 7)->setText(text);
			text = n.toElement().attribute("netto2");
			tableT->item(tableT->rowCount() - 1, 8)->setText(text);
			text = n.toElement().attribute("netto3");
			tableT->item(tableT->rowCount() - 1, 9)->setText(text);
			text = n.toElement().attribute("netto4");
			tableT->item(tableT->rowCount() - 1, 10)->setText(text);
			text = n.toElement().attribute("vat");
			tableT->item(tableT->rowCount() - 1, 11)->setText(text);
		}
	}
}

// ----------------------------------------  SLOTS ---------------------------------//

/** Slot which enables/disables menu. It's possible to add/remove goods/customers
 *  only if this is the current tab.
 */
void MainWindow::tabChanged(QWidget * qwdt) {

	int tabNo = tabWidget2->indexOf(qwdt);

	switch (tabNo) {
	case 0: {
		// historia
		kontrahenciDodajAction->setEnabled(false);
		kontrahenciEdycjaAction->setEnabled(false);
		kontrahenciUsunAction->setEnabled(false);
		towaryDodajAction->setEnabled(false);
		towaryEdycjaAction->setEnabled(false);
		towaryUsunAction->setEnabled(false);
		fakturyEdAction->setEnabled(true);
		fakturyUsunAction->setEnabled(true);
		break;
	}
	case 1: {
		// kontrahenci
		kontrahenciDodajAction->setEnabled(true);
		kontrahenciEdycjaAction->setEnabled(true);
		kontrahenciUsunAction->setEnabled(true);
		towaryDodajAction->setEnabled(false);
		towaryEdycjaAction->setEnabled(false);
		towaryUsunAction->setEnabled(false);
		fakturyEdAction->setEnabled(false);
		fakturyUsunAction->setEnabled(false);
		break;
	}
	case 2: {
		// towary
		kontrahenciDodajAction->setEnabled(false);
		kontrahenciEdycjaAction->setEnabled(false);
		kontrahenciUsunAction->setEnabled(false);
		towaryDodajAction->setEnabled(true);
		towaryEdycjaAction->setEnabled(true);
		towaryUsunAction->setEnabled(true);
		fakturyEdAction->setEnabled(false);
		fakturyUsunAction->setEnabled(false);
		break;
	}
	default: {
		// historia
		kontrahenciDodajAction->setEnabled(false);
		kontrahenciEdycjaAction->setEnabled(false);
		kontrahenciUsunAction->setEnabled(false);
		towaryDodajAction->setEnabled(false);
		towaryEdycjaAction->setEnabled(false);
		towaryUsunAction->setEnabled(false);
		fakturyEdAction->setEnabled(true);
		fakturyUsunAction->setEnabled(true);
		break;
	}
	}
}

/** Slot used to read the invoices, calls readHist.
 */
void MainWindow::rereadHist() {
	//  qDebug( __FUNCTION__ );
	QString progDir = QDir::homePath() + "/elinux";
	tableClear(tableH);
	readHist(progDir);
}

/** Slot used to display aboutQt informations.
 */
void MainWindow::aboutQt() {
	QMessageBox::aboutQt(this, "QFaktury");
}

/** Slot used to display information about QFaktury
 */
void MainWindow::oProg() {
	QMessageBox::about(
			this,
			"O programie",
			UTF8("Program do wystawiania faktur.\nWersja " STRING(QFAKTURY_VERSION) " \n\nProgramista:\n\tRafał‚ Rusin (rafal.rusin@gmail.com)\n\nSupport: rafal.rusin@gmail.com\n\nPoprzednio pracowali:\nKoordynator projektu: \n\tGrzegorz Rękawek www.e-linux.pl\nProgramista:\n\tTomasz 'moux' Pielech\nGrafika:\n\tDariusz Arciszewski"));
}

/** Slot used to edit the invoice from list of invoices.
 */
void MainWindow::editFHist() {
	// qDebug() <<  __FUNCTION__;

	int row;
	QList<QTableWidgetItem *> selected = tableH->selectedItems();
	row = selected[0]->row();

	if (tableH->item(row, 3)->text() == "korekta") {
		// QMessageBox::information( this, "QFaktury", "Jeszcze nie ma", QMessageBox::Ok );
		Korekta *korWindow = new Korekta(this);
		korWindow->progDir2 = pdGlob;
		korWindow->readData(tableH->item(row, 0)->text());
		if (korWindow->exec() == QDialog::Accepted) {
			QStringList rowTxt = korWindow->ret.split("|");
			tableH->item(row, 0)->setText(rowTxt[0]); // file name
			tableH->item(row, 1)->setText(rowTxt[1]); // symbol
			tableH->item(row, 2)->setText(rowTxt[2]); // date
			tableH->item(row, 3)->setText(rowTxt[3]); // type
			tableH->item(row, 4)->setText(rowTxt[4]); // nabywca
			tableH->item(row, 5)->setText(rowTxt[5]); // NIP
		}
	}

	if ((tableH->item(row, 3)->text() == "FVAT")
			|| (tableH->item(row, 3)->text() == "FPro")) {
		// qDebug ("%s %s:%d", __FUNCTION__, __FILE__, __LINE__);
		Faktura *fraWindow = new Faktura(this);
		fraWindow->progDir2 = pdGlob;
		qDebug() << pdGlob;
		int co = 0;
		if (tableH->item(row, 3)->text() == "FVAT")
			co = 0;
		else
			co = 1;
		fraWindow->readData(tableH->item(row, 0)->text(), co);
		if (fraWindow->exec() == QDialog::Accepted) {
			// tableH->insertRows (tableH->rowCount (), 1);
			QStringList rowTxt = fraWindow->ret.split("|");
			tableH->item(row, 0)->setText(rowTxt[0]); // file name
			tableH->item(row, 1)->setText(rowTxt[1]); // symbol
			tableH->item(row, 2)->setText(rowTxt[2]); // date
			tableH->item(row, 3)->setText(rowTxt[3]); // type
			tableH->item(row, 4)->setText(rowTxt[4]); // nabywca
			tableH->item(row, 5)->setText(rowTxt[5]); // NIP
		}
	}
}

/** Slot used to delete invoices
 */
void MainWindow::delFHist() {
	if (QMessageBox::warning(this, "QFaktury", UTF8("Czy napewno chcesz usnąć tą fakturę z historii?"), "Tak",
			"Nie", 0, 0, 1) == 0) {
		QString name = tableH->item (tableH->currentRow(), 0)->text();

		QFile file(pdGlob + "/faktury/" + name);
		if (file.exists())
			file.remove();
		tableH->removeRow(tableH->currentRow());
	}

}

/** Slot used to edit data of the current company
 */
void MainWindow::daneFirmyClick() {
	// qDebug("%s %s:%d", __FUNCTION__, __FILE__, __LINE__);
	Uzytkownik *daneFirmyWindow = new Uzytkownik(this);
	daneFirmyWindow->show();
}

/** Slot used to edit edit settings
 */
void MainWindow::settClick() {
	// qDebug ("%s %s:%d", __FUNCTION__, __FILE__, __LINE__);
	Ustawienia *settWindow = new Ustawienia(this);
	settWindow->show();
}

//void MainWindow::kretorClick ()
//{
//  qDebug ("%s %s:%d", __FUNCTION__, __FILE__, __LINE__);
////     QMessageBox::information( this, "QFaktury", "Funkcja jeszcze nie gotowa. Uzyj menu faktury->Nowy", QMessageBox::Ok );
//  Form3 *kreatorWindow = new Form3;
//  if (kreatorWindow->exec () == QDialog::Accepted)
//    {
//      kreatorWindow->print ();
//      // tableClear (tableH);
//      // readHist (pdGlob);
//      /*
//         QStringList row = QStringList::split( "|",  kreatorWindow->ret );
//         tableH->insertRows (tableH->rowCount (), 1);
//         tableH->setText (tableH->rowCount () - 1, 0, row[0]); // nazwa pliku
//         tableH->setText (tableH->rowCount () - 1, 1, row[1]);
//         tableH->setText (tableH->rowCount () - 1, 2, row[2]);
//         tableH->setText (tableH->rowCount () - 1, 4, row[3]);
//         tableH->setText (tableH->rowCount () - 1, 3, row[4]);
//       */
//    }
//  // delete kreatorWindow;
//}

/** Slot used to add new customer
 */
void MainWindow::kontrClick() {
	Kontrahenci *kontrWindow;
	kontrWindow = new Kontrahenci(this);
	//qDebug ("%s %s:%d", __FUNCTION__, __FILE__, __LINE__);
	if (kontrWindow->exec() == QDialog::Accepted) {
		// tableClear (tableK);
		QDir tmp;
		QString progDir = tmp.homePath() + "/elinux";
		// qDebug() << progDir;
		tmp.mkdir(progDir);

		// readKontr (progDir);
		insertRow(tableK, tableK->rowCount());
		QStringList row = kontrWindow->ret.split("|");
		tableK->item(tableK->rowCount() - 1, 0)->setText(row[0]); // name
		tableK->item(tableK->rowCount() - 1, 1)->setText(row[1]); // type
		tableK->item(tableK->rowCount() - 1, 2)->setText(row[2]); // place
		tableK->item(tableK->rowCount() - 1, 3)->setText(row[3]); // address
		tableK->item(tableK->rowCount() - 1, 4)->setText(row[4]); // telefon
	}
}

/** Slot used to delete current customer
 */
void MainWindow::kontrDel() {
	if (QMessageBox::warning(this, "QFaktury", UTF8("Czy napewno chcesz usunąć kontrahenta: ") + tableK->item(tableK->currentRow(), 0)->text() + UTF8(" ?"), "Tak", "Nie", 0, 0, 1) == 0) {
		QDomDocument doc("kontrahenci");
		QDomElement root;
		QDomElement urzad;
		QDomElement firma;
		int row = tableK->currentRow();

		QFile file(pdGlob + "/kontrah.xml");
		if (!file.open(QIODevice::ReadOnly)) {
			qDebug("file doesn't exists");
			return;

		} else {
			QTextStream stream(&file);
			if (!doc.setContent(stream.readAll())) {
				qDebug("can not set content ");
				file.close();
				return;
			} else {
				root = doc.documentElement();
				urzad = root.firstChild().toElement();
				firma = root.lastChild().toElement();
			}
			QString text;

			for (QDomNode n = firma.firstChild(); !n.isNull(); n
					= n.nextSibling()) {
				if (n.toElement().attribute("name"). compare(tableK->item(row,
						0)->text()) == 0) {
					firma.removeChild(n);
					break;
				}
			}

			for (QDomNode n = urzad.firstChild(); !n.isNull(); n
					= n.nextSibling()) {
				// qDebug("aaa");
				if (n.toElement().attribute("name"). compare(tableK->item(row,
						0)->text()) == 0) {
					urzad.removeChild(n);
					break;
				}
			}

			QString xml = doc.toString();
			file.close();
			file.open(QIODevice::WriteOnly);
			QTextStream ts(&file);
			ts << xml;

			file.close();
			tableK->removeRow(row);
		}

	}
}

/** Slot used to edit customer
 */
void MainWindow::kontrEd ()
{
  int row = tableK->selectedItems()[0]->row();
  // qDebug ()<<tableK->item(row, 0)->text();

  Kontrahenci *kontrWindow = new Kontrahenci(this);
  kontrWindow->readData (tableK->item(row, 0)->text(), tableK->item(row, 1)->text());
  if (kontrWindow->exec () == QDialog::Accepted)
    {
      QStringList rowTxt = kontrWindow->ret.split("|");
      tableK->item (row, 0)->setText(rowTxt[0]);	// name
      tableK->item (row, 1)->setText(rowTxt[1]);	// type
      tableK->item (row, 2)->setText(rowTxt[2]);	// place
      tableK->item (row, 3)->setText(rowTxt[3]);	// address
      tableK->item (row, 4)->setText(rowTxt[4]);	// telefon
    }
}

/** Slot used for creating new invoices
 */
void MainWindow::newFra() {
	Faktura *fraWindow = new Faktura(this);
	fraWindow->progDir2 = pdGlob;
	fraWindow->pforma = false;
	if (fraWindow->exec() == QDialog::Accepted) {
		insertRow(tableH, tableH->rowCount());
		QStringList row = fraWindow->ret.split("|");
		tableH->item(tableH->rowCount() - 1, 0)->setText(row[0]); // file name
		tableH->item(tableH->rowCount() - 1, 1)->setText(row[1]); // symbol
		tableH->item(tableH->rowCount() - 1, 2)->setText(row[2]); // date
		tableH->item(tableH->rowCount() - 1, 3)->setText(row[3]); // type
		tableH->item(tableH->rowCount() - 1, 4)->setText(row[4]); // nabywca
		tableH->item(tableH->rowCount() - 1, 5)->setText(row[5]); // NIP
	}
}

/** Slot used to create new ProForma Invoice
 */
void MainWindow::newPForm() {
	Faktura *fraWindow = new Faktura(this);
	fraWindow->progDir2 = pdGlob;
	fraWindow->pforma = true;
	fraWindow->setWindowTitle("Faktura Pro Forma");
	fraWindow->backBtnClick();
	if (fraWindow->exec() == QDialog::Accepted) {
		insertRow(tableH, tableH->rowCount());
		QStringList row = fraWindow->ret.split("|");
		tableH->item(tableH->rowCount() - 1, 0)->setText(row[0]); // file name
		tableH->item(tableH->rowCount() - 1, 1)->setText(row[1]); // symbol
		tableH->item(tableH->rowCount() - 1, 2)->setText(row[2]); // date
		tableH->item(tableH->rowCount() - 1, 3)->setText(row[3]); // type
		tableH->item(tableH->rowCount() - 1, 4)->setText(row[4]); // nabywca
		tableH->item(tableH->rowCount() - 1, 5)->setText(row[5]); // NIP
	}
}

/** Slot used to create new Korkta
 */
void MainWindow::newKor() {
	int row = tableH->selectedItems()[0]->row();

	if ((tableH->item(row, 3)->text() == "FVAT")) {
		Korekta *korWindow = new Korekta(this);
		// qDebug( pdGlob );
		korWindow->progDir2 = pdGlob;
		korWindow->readDataNewKor(tableH->item(row, 0)->text());
		if (korWindow->exec() == QDialog::Accepted) {
			insertRow(tableH, tableH->rowCount());
			QStringList row = korWindow->ret.split("|");
			tableH->item(tableH->rowCount() - 1, 0)->setText(row[0]); // file name
			tableH->item(tableH->rowCount() - 1, 1)->setText(row[1]); // symbol
			tableH->item(tableH->rowCount() - 1, 2)->setText(row[2]); // date
			tableH->item(tableH->rowCount() - 1, 3)->setText(row[3]); // type
			tableH->item(tableH->rowCount() - 1, 4)->setText(row[4]); // nabywca
			tableH->item(tableH->rowCount() - 1, 5)->setText(row[5]); // NIP
		}
	}
	// no UTF8??
	if ((tableH->item(row, 3)->text() == "korekta")) {
		QMessageBox::information(this, "QFaktury",
				"Do korekt nie wystawiamy korekt", QMessageBox::Ok);
	}
	if ((tableH->item(row, 3)->text() == "FPro")) {
		QMessageBox::information(this, "QFaktury",
				"Do faktur Pro Forma nie wystawiamy korekt", QMessageBox::Ok);
	}
}

/** Slot used to add goods
 */
void MainWindow::towaryDodaj() {
	Towary *towWindow = new Towary(this);
	if (towWindow->exec() == QDialog::Accepted) {
		insertRow(tableT, tableT->rowCount());
		QStringList row = towWindow->ret.split("|");
		tableT->item(tableT->rowCount() - 1, 0)->setText(row[0]);
		tableT->item(tableT->rowCount() - 1, 1)->setText(row[1]);
		tableT->item(tableT->rowCount() - 1, 2)->setText(row[2]);
		tableT->item(tableT->rowCount() - 1, 3)->setText(row[3]);
		tableT->item(tableT->rowCount() - 1, 4)->setText(row[4]);
		tableT->item(tableT->rowCount() - 1, 5)->setText(row[5]);
		tableT->item(tableT->rowCount() - 1, 6)->setText(row[6]);
		tableT->item(tableT->rowCount() - 1, 7)->setText(row[7]);
		tableT->item(tableT->rowCount() - 1, 8)->setText(row[8]);
		tableT->item(tableT->rowCount() - 1, 9)->setText(row[9]);
		tableT->item(tableT->rowCount() - 1, 10)->setText(row[10]);
		tableT->item(tableT->rowCount() - 1, 11)->setText(row[11]);
	}
}

/** Slot used to delete goods
 */
void MainWindow::towaryUsun() {
	int row = tableT->currentRow();

	if (QMessageBox::warning(this, "QFaktury", UTF8("Czy napewno chcesz usunąć towar ") + tableT->item(row, 0)->text()
			+ "/" + tableT->item(row, 1)->text() + "?", "Tak", "Nie", 0, 0, 1)
			== 0) {

		QDomDocument doc("towary");
		QDomElement root;
		QDomElement towary;
		QDomElement uslugi;

		QFile file(pdGlob + "/towary.xml");
		if (!file.open(QIODevice::ReadOnly)) {
			qDebug("file doesn't exists");
			return;

		} else {
			QTextStream stream(&file);
			if (!doc.setContent(stream.readAll())) {
				qDebug("can not set content ");
				file.close();
				return;
			} else {
				root = doc.documentElement();
				towary = root.firstChild().toElement();
				uslugi = root.lastChild().toElement();
			}
			QString text;

			for (QDomNode n = uslugi.firstChild(); !n.isNull(); n
					= n.nextSibling()) {
				// qDebug("aaa");
				if (n.toElement().attribute("idx"). compare(
						tableT->item(row, 0)->text()) == 0) {
					uslugi.removeChild(n);
					break;
				}
			}

			for (QDomNode n = towary.firstChild(); !n.isNull(); n
					= n.nextSibling()) {
				// qDebug("aaa");
				if (n.toElement().attribute("idx"). compare(
						tableT->item(row, 0)->text()) == 0) {
					towary.removeChild(n);
					break;
				}
			}

			QString xml = doc.toString();
			file.close();
			file.open(QIODevice::WriteOnly);
			QTextStream ts(&file);
			ts << xml;

			file.close();
			tableT->removeRow(row);
		}

	}

}

/** Slot used for editing goods
 */
void MainWindow::towaryEdycja() {
	int row = tableT->selectedItems()[0]->row();

	// qDebug() << tableT->item(row, 0)->text();

	Towary *towWindow = new Towary(this);
	towWindow->readData(tableT->item(row, 0)->text(),
			tableT->item(row, 5)->text());
	if (towWindow->exec() == QDialog::Accepted) {
		QStringList rowTxt = towWindow->ret.split("|");
		tableT->item(row, 0)->setText(rowTxt[0]);
		tableT->item(row, 1)->setText(rowTxt[1]);
		tableT->item(row, 2)->setText(rowTxt[2]);
		tableT->item(row, 3)->setText(rowTxt[3]);
		tableT->item(row, 4)->setText(rowTxt[4]);
		tableT->item(row, 5)->setText(rowTxt[5]);
		tableT->item(row, 6)->setText(rowTxt[6]);
		tableT->item(row, 7)->setText(rowTxt[7]);
		tableT->item(row, 8)->setText(rowTxt[8]);
		tableT->item(row, 9)->setText(rowTxt[9]);
		tableT->item(row, 10)->setText(rowTxt[10]);
		tableT->item(row, 11)->setText(rowTxt[11]);
	}

}

/** Slot close
 */
bool MainWindow::close() {
	if (QMessageBox::question(this, UTF8("Potwierdź"),
	UTF8("Czy chcesz wyjść z programu?"), QMessageBox::Yes | QMessageBox::No,
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

	QStringList args;
	QString program;
	QProcess *process = new QProcess(this);

#if defined Q_OS_UNIX
	// move to Xlib
	/*
	program = "kfmclient";
	args << "exec";
	args << "http://www.e-linux.pl/modules/qfaktury/index.php";
	*/
#endif


#if defined Q_WS_WIN
	qDebug() << "Start WWW";
	// it may need to be changed to something more universal
	program = "c:\\Program Files\\Internet Explorer\\iexplore.exe";
	args << "http://www.e-linux.pl/modules/qfaktury/index.php";
	process->start(program, args);
#endif

}

/** Slot forum
 */
void MainWindow::forum() {
	QMessageBox::information(this, tr("Forum e-linux.pl"), tr(
			"http://forum.e-linux.pl"));
	QString program = "kfmclient";
	QStringList arguments;
	QProcess *myProcess = new QProcess(this);

#if defined Q_OS_UNIX
	arguments << "exec" << "http://forum.e-linux.pl/";
	// add ifdef for windows
	myProcess->start(program, arguments);
#endif

#if defined Q_WS_WIN
	// it may need to be changed to something more universal
	program = "c:\\Program Files\\Internet Explorer\\iexplore.exe";
	arguments << "http://forum.e-linux.pl";
	myProcess->start(program, arguments);
#endif
}

//-------------------- not used >??? ------------------------------------------
void MainWindow::nextPage()
{
 if ( tabWidget2->count() != tabWidget2->currentIndex() )
 tabWidget2->setCurrentIndex( tabWidget2->currentIndex() + 1 );
}


void MainWindow::prevPage()
{
 if ( tabWidget2->currentIndex() !=  0 )
 tabWidget2->setCurrentIndex( tabWidget2->currentIndex() - 1 );
}



