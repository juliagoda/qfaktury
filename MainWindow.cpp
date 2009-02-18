/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you want to add, delete, or rename functions or slots, use
** Qt Designer to update this file, preserving your code.
**
** You should not define a constructor or destructor in this file.
** Instead, write your code in functions called init() and destroy().
** These will automatically be called by the form's constructor and
** destructor.
*****************************************************************************/
#include "MainWindow.moc"
#include <qtextcodec.h>
#include <qdir.h>
#include <qmessagebox.h>
#include "Settings.h"
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

#define STRING2(x) #x
#define STRING(x) STRING2(x)

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

	Settings settings;

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

	filtrStart->setDate(settings.getValueAsDate("filtrStart"));
	filtrEnd->setDate(settings.getValueAsDate("filtrEnd"));


	tabChanged(tabWidget2);

	readKontr(progDir);
	readHist(progDir);
	readTw(progDir);
}

/**
 * firstRun setup()
 */
bool MainWindow::firstRun() {
	Settings settings;
	bool ok = settings.value("firstrun").toBool();
	if (ok) {
		checkSettings();
		// set dates for filter
		filtrStart->setDate(QDate::currentDate());
		filtrEnd->setDate(QDate::currentDate());
		return true;
	} else {
		checkSettings();
		return false;
	}

}

/** save settings before quit
 * save column width
 */
void MainWindow::saveColumnWidth() {
	Settings settings;
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

/** Saves all settings as default
 */
void MainWindow::saveAllSettAsDefault() {

	Settings settings;

	// should i change those settings names?
	settings.setValue("firstrun", false);
	settings.setValue("logo", "");
	settings.setValue("jednostki", tr("szt.|kg.|g.|m|km.|godz."));
	settings.setValue("stawki", tr("22|7|0|zw."));
	settings.setValue("waluty", tr("PLN|EUR|USD"));
	settings.setValue("payments", UTF8("gotówka|przelew")); // uwaga!! get first
	settings.setValue("paym1", UTF8("gotówka"));
	settings.setValue("pkorekty", UTF8("zmiana ilości"));
	settings.setValue("addText", UTF8("towar odebrałem zgodnie z fakturą"));
	settings.setValue("margLeftPrinter", "10");
	settings.setValue("margTopPrinter", "10");
	settings.setValue("margDownPrinter", "10");
	settings.setValue("margRightPrinter", "10");
	settings.setValue("editName", false);

	// here we could add special code for Rachunek
	settings.beginGroup("faktury_pozycje");
	settings.setValue("Lp", true);
	settings.setValue("Nazwa", true);
	settings.setValue("Kod", true);
	settings.setValue("pkwiu", true);
	settings.setValue("ilosc", true);
	settings.setValue("jm", true);
	settings.setValue("cenajedn", true);
	settings.setValue("wartnetto", true);
	settings.setValue("rabatperc", true);
	settings.setValue("rabatval", true);
	settings.setValue("nettoafter", true);
	settings.setValue("vatval", true);
	settings.setValue("vatprice", true);
	settings.setValue("bruttoval", true);
	settings.endGroup();

	settings.beginGroup("formatki");
	settings.setValue("form1_top", "50");
	settings.setValue("form1_left", "50");
	settings.setValue("form1_width", "740");
	settings.setValue("form1_height", "540");
	settings.setValue("form2_top", "200");
	settings.setValue("form2_left", "200");
	settings.setValue("form2_width", "500");
	settings.setValue("form2_height", "350");
	settings.setValue("form7_top", "50");
	settings.setValue("form7_left", "50");
	settings.setValue("form7_width", "700");
	settings.setValue("form7_height", "600");
	settings.setValue("chAmount_top", "50");
	settings.setValue("chAmount_left", "50");
	settings.setValue("chAmount_width", "300");
	settings.setValue("chAmount_height", "200");
	settings.setValue("form4_top", "50");
	settings.setValue("form4_left", "50");
	settings.setValue("form4_width", "400");
	settings.setValue("form4_height", "300");
	settings.setValue("formfra_top", "50");
	settings.setValue("formfra_left", "50");
	settings.setValue("formfra_width", "700");
	settings.setValue("formfra_height", "600");
	settings.setValue("kontlist_top", "50");
	settings.setValue("kontlist_left", "50");
	settings.setValue("kontlist_width", "300");
	settings.setValue("kontlist_height", "300");
	settings.setValue("korform_top", "50");
	settings.setValue("korform_left", "50");
	settings.setValue("korform_width", "700");
	settings.setValue("korform_height", "600");
	settings.setValue("korprintpreview_top", "50");
	settings.setValue("korprintpreview_left", "50");
	settings.setValue("korprintpreview_width", "900");
	settings.setValue("korprintpreview_height", "600");
	settings.setValue("printpreview_top", "50");
	settings.setValue("printpreview_left", "50");
	settings.setValue("printpreview_width", "900");
	settings.setValue("printpreview_height", "600");
	settings.setValue("towlist_top", "50");
	settings.setValue("towlist_left", "50");
	settings.setValue("towlist_width", "300");
	settings.setValue("towlist_height", "300");
	settings.setValue("towadd_top", "50");
	settings.setValue("towadd_left", "50");
	settings.setValue("towadd_width", "300");
	settings.setValue("towadd_height", "300");
	settings.endGroup();

	settings.beginGroup("wydruki");
	settings.setValue("col1", "10");
	settings.setValue("col2", "25");
	settings.setValue("col3", "12");
	settings.setValue("col4", "12");
	settings.setValue("col5", "12");
	settings.setValue("col6", "9");
	settings.setValue("col7", "11");
	settings.setValue("col8", "11");
	settings.setValue("col9", "10");
	settings.setValue("col10", "12");
	settings.setValue("col11", "12");
	settings.setValue("col12", "12");
	settings.setValue("col13", "12");
	settings.setValue("col14", "12");
	settings.endGroup();
}


/** Saves all settings
 */
void MainWindow::saveAllSett() {
	Settings settings;

	// save filtr
	settings.setValue("filtrStart", filtrStart->text());
	settings.setValue("filtrEnd", filtrEnd->text());

	saveColumnWidth();

	// save unsaved
	settings.sync();
}

/**
 * validate the settings and set them to default values if required.
 */
void MainWindow::checkSettings() {
	Settings settings;

	settings.beginGroup("general");
	if (settings.value("browser_name").toString().compare("") == 0)
		settings.setValue("browser_name", "");
	if (settings.value("default_browser").toString().compare("") == 0)
		settings.setValue("default_browser", "true");
	if (settings.value("lang").toString().compare("") == 0)
		settings.setValue("lang", tr("polski"));
	if (settings.value("localEnc").toString().compare("") == 0)
		settings.setValue("waluty", tr("ISO-8859-2"));
	settings.endGroup();


	if (settings.value("addText").toString().compare("") == 0)
		settings.setValue("addText",
				tr("towar odebrałem zgodnie z fakturą"));
	if (settings.value("chars_in_symbol").toString().compare("") == 0)
		settings.setValue("chars_in_symbol", tr("0"));
	if (settings.value("day").toString().compare("") == 0)
		settings.setValue("day", "false");
	if (settings.value("edit").toString().compare("") == 0)
		settings.setValue("edit", "false");
	if (settings.value("editName").toString().compare("") == 0)
		settings.setValue("editName", "false");
	if (settings.value("editSymbol").toString().compare("") == 0)
		settings.setValue("editSymbol", "false");
	if (settings.value("editSymbol").toString().compare("") == 0)
		settings.setValue("editSymbol", "false");
	if (settings.value("editSymbol").toString().compare("") == 0)
		settings.setValue("editSymbol", "false");
	if (settings.value("filtrEnd").toString().compare("") == 0)
		settings.setValue("filtrEnd",
				QDate::currentDate().toString(Qt::ISODate));
	if (settings.value("filtrStart").toString().compare("") == 0)
		settings.setValue("filtrStart", QDate::currentDate().toString(
				Qt::ISODate));
	if (settings.value("firstrun").toString().compare("") == 0)
		settings.setValue("firstrun", false);
	if (settings.value("jednostki").toString().compare("") == 0)
		settings.setValue("jednostki", tr("szt.|kg.|g.|m|km.|godz."));
	if (settings.value("korNr").toString().compare("") == 0)
		settings.setValue("korNr", "1");
	if (settings.value("logo").toString().compare("") == 0)
		settings.setValue("logo", "");
	if (settings.value("margLeftPrinter").toString().compare("") == 0)
		settings.setValue("margLeftPrinter", "10");
	if (settings.value("margTopPrinter").toString().compare("") == 0)
		settings.setValue("margTopPrinter", "10");
	if (settings.value("margDownPrinter").toString().compare("") == 0)
		settings.setValue("margDownPrinter", "10");
	if (settings.value("margRightPrinter").toString().compare("") == 0)
		settings.setValue("margRightPrinter", "10");
	if (settings.value("month").toString().compare("") == 0)
		settings.setValue("month", "false");
	if (settings.value("paym1").toString().compare("") == 0)
		settings.setValue("paym1", tr("gotówka"));
	if (settings.value("payments").toString().compare("") == 0)
		settings.setValue("payments", tr("gotówka|przelew"));
	if (settings.value("pdfQuality").toString().compare("") == 0)
		settings.setValue("pdfQuality", "1");
	if (settings.value("pkorekty").toString().compare("") == 0)
		settings.setValue("pkorekty", tr("zmiana ilości"));
	if (settings.value("prefix").toString().compare("") == 0)
		settings.setValue("prefix", "");
	if (settings.value("renamed").toString().compare("") == 0)
		settings.setValue("renamed", "tak");
	if (settings.value("shortYear").toString().compare("") == 0)
		settings.setValue("shortYear", "false");
	if (settings.value("stawki").toString().compare("") == 0)
		settings.setValue("stawki", tr("22|7|0|zw."));
	if (settings.value("sufix").toString().compare("") == 0)
		settings.setValue("sufix", "");
	if (settings.value("waluty").toString().compare("") == 0)
		settings.setValue("waluty", tr("PLN|EUR|USD"));
	if (settings.value("year").toString().compare("") == 0)
		settings.setValue("year", "false");

	// here we could add special code for Rachunek
	settings.beginGroup("faktury_pozycje");
	if (settings.value("Lp").toString().compare("") == 0)
		settings.setValue("Lp", true);
	if (settings.value("Nazwa").toString().compare("") == 0)
		settings.setValue("Nazwa", true);
	if (settings.value("Kod").toString().compare("") == 0)
		settings.setValue("Kod", true);
	if (settings.value("pkwiu").toString().compare("") == 0)
		settings.setValue("pkwiu", true);
	if (settings.value("ilosc").toString().compare("") == 0)
		settings.setValue("ilosc", true);
	if (settings.value("jm").toString().compare("") == 0)
		settings.setValue("jm", true);
	if (settings.value("cenajedn").toString().compare("") == 0)
		settings.setValue("cenajedn", true);
	if (settings.value("wartnetto").toString().compare("") == 0)
		settings.setValue("wartnetto", true);
	if (settings.value("rabatperc").toString().compare("") == 0)
		settings.setValue("rabatperc", true);
	if (settings.value("rabatval").toString().compare("") == 0)
		settings.setValue("rabatval", true);
	if (settings.value("nettoafter").toString().compare("") == 0)
		settings.setValue("nettoafter", true);
	if (settings.value("vatval").toString().compare("") == 0)
		settings.setValue("vatval", true);
	if (settings.value("vatprice").toString().compare("") == 0)
		settings.setValue("vatprice", true);
	if (settings.value("bruttoval").toString().compare("") == 0)
		settings.setValue("bruttoval", true);
	settings.endGroup();

	settings.beginGroup("formatki");
	if (settings.value("chAmount_top").toString().compare("") == 0)
		settings.setValue("chAmount_top", "50");
	if (settings.value("chAmount_left").toString().compare("") == 0)
		settings.setValue("chAmount_left", "50");
	if (settings.value("chAmount_width").toString().compare("") == 0)
		settings.setValue("chAmount_width", "288");
	if (settings.value("chAmount_height").toString().compare("") == 0)
		settings.setValue("chAmount_height", "184");
	if (settings.value("form1_top").toString().compare("") == 0)
		settings.setValue("form1_top", "50");
	if (settings.value("form1_left").toString().compare("") == 0)
		settings.setValue("form1_left", "50");
	if (settings.value("form1_width").toString().compare("") == 0)
		settings.setValue("form1_width", "748");
	if (settings.value("form1_height").toString().compare("") == 0)
		settings.setValue("form1_height", "507");
	if (settings.value("form2_top").toString().compare("") == 0)
		settings.setValue("form2_top", "200");
	if (settings.value("form2_left").toString().compare("") == 0)
		settings.setValue("form2_left", "200");
	if (settings.value("form2_width").toString().compare("") == 0)
		settings.setValue("form2_width", "388");
	if (settings.value("form2_height").toString().compare("") == 0)
		settings.setValue("form2_height", "350");
	if (settings.value("form4_top").toString().compare("") == 0)
		settings.setValue("form4_top", "50");
	if (settings.value("form4_left").toString().compare("") == 0)
		settings.setValue("form4_left", "50");
	if (settings.value("form4_width").toString().compare("") == 0)
		settings.setValue("form4_width", "423");
	if (settings.value("form4_height").toString().compare("") == 0)
		settings.setValue("form4_height", "358");
	if (settings.value("form7_top").toString().compare("") == 0)
		settings.setValue("form7_top", "50");
	if (settings.value("form7_left").toString().compare("") == 0)
		settings.setValue("form7_left", "50");
	if (settings.value("form7_width").toString().compare("") == 0)
		settings.setValue("form7_width", "636");
	if (settings.value("form7_height").toString().compare("") == 0)
		settings.setValue("form7_height", "600");
	if (settings.value("formfra_top").toString().compare("") == 0)
		settings.setValue("formfra_top", "50");
	if (settings.value("formfra_left").toString().compare("") == 0)
		settings.setValue("formfra_left", "50");
	if (settings.value("formfra_width").toString().compare("") == 0)
		settings.setValue("formfra_width", "546");
	if (settings.value("formfra_height").toString().compare("") == 0)
		settings.setValue("formfra_height", "650");
	if (settings.value("kontlist_top").toString().compare("") == 0)
		settings.setValue("kontlist_top", "50");
	if (settings.value("kontlist_left").toString().compare("") == 0)
		settings.setValue("kontlist_left", "50");
	if (settings.value("kontlist_width").toString().compare("") == 0)
		settings.setValue("kontlist_width", "300");
	if (settings.value("kontlist_height").toString().compare("") == 0)
		settings.setValue("kontlist_height", "300");
	if (settings.value("korform_top").toString().compare("") == 0)
		settings.setValue("korform_top", "50");
	if (settings.value("korform_left").toString().compare("") == 0)
		settings.setValue("korform_left", "50");
	if (settings.value("korform_width").toString().compare("") == 0)
		settings.setValue("korform_width", "537");
	if (settings.value("korform_height").toString().compare("") == 0)
		settings.setValue("korform_height", "677");
	if (settings.value("korprintpreview_top").toString().compare("") == 0)
		settings.setValue("korprintpreview_top", "50");
	if (settings.value("korprintpreview_left").toString().compare("") == 0)
		settings.setValue("korprintpreview_left", "50");
	if (settings.value("korprintpreview_width").toString().compare("") == 0)
		settings.setValue("korprintpreview_width", "900");
	if (settings.value("korprintpreview_height").toString().compare("") == 0)
		settings.setValue("korprintpreview_height", "600");
	if (settings.value("printpreview_top").toString().compare("") == 0)
		settings.setValue("printpreview_top", "50");
	if (settings.value("printpreview_left").toString().compare("") == 0)
		settings.setValue("printpreview_left", "50");
	if (settings.value("printpreview_width").toString().compare("") == 0)
		settings.setValue("printpreview_width", "900");
	if (settings.value("printpreview_height").toString().compare("") == 0)
		settings.setValue("printpreview_height", "600");
	if (settings.value("towadd_top").toString().compare("") == 0)
		settings.setValue("towadd_top", "50");
	if (settings.value("towadd_left").toString().compare("") == 0)
		settings.setValue("towadd_left", "50");
	if (settings.value("towadd_width").toString().compare("") == 0)
		settings.setValue("towadd_width", "334");
	if (settings.value("towadd_height").toString().compare("") == 0)
		settings.setValue("towadd_height", "286");
	if (settings.value("towlist_top").toString().compare("") == 0)
		settings.setValue("towlist_top", "50");
	if (settings.value("towlist_left").toString().compare("") == 0)
		settings.setValue("towlist_left", "50");
	if (settings.value("towlist_width").toString().compare("") == 0)
		settings.setValue("towlist_width", "300");
	if (settings.value("towlist_height").toString().compare("") == 0)
		settings.setValue("towlist_height", "300");
	settings.endGroup();

	settings.beginGroup("printpos");
	if (settings.value("usernazwa").toString().compare("") == 0)
		settings.setValue("usernazwa", "true");
	if (settings.value("usermiejscowosc").toString().compare("") == 0)
		settings.setValue("usermiejscowosc", "true");
	if (settings.value("useradres").toString().compare("") == 0)
		settings.setValue("useradres", "true");
	if (settings.value("userkonto").toString().compare("") == 0)
		settings.setValue("userkonto", "true");
	if (settings.value("usernip").toString().compare("") == 0)
		settings.setValue("usernip", "true");
	if (settings.value("userphone").toString().compare("") == 0)
		settings.setValue("userphone", "true");
	if (settings.value("usermail").toString().compare("") == 0)
		settings.setValue("usermail", "true");
	if (settings.value("userwww").toString().compare("") == 0)
		settings.setValue("userwww", "true");
	if (settings.value("clientnazwa").toString().compare("") == 0)
		settings.setValue("clientnazwa", "true");
	if (settings.value("clientmiejscowosc").toString().compare("") == 0)
		settings.setValue("clientmiejscowosc", "true");
	if (settings.value("clientadres").toString().compare("") == 0)
		settings.setValue("clientadres", "true");
	if (settings.value("clientkonto").toString().compare("") == 0)
		settings.setValue("clientkonto", "true");
	if (settings.value("clientnip").toString().compare("") == 0)
		settings.setValue("clientnip", "true");
	if (settings.value("clientphone").toString().compare("") == 0)
		settings.setValue("clientphone", "true");
	if (settings.value("clientmail").toString().compare("") == 0)
		settings.setValue("clientmail", "true");
	if (settings.value("clientwww").toString().compare("") == 0)
		settings.setValue("clientwww", "true");
	settings.endGroup();

	settings.beginGroup("wydruki");
	if (settings.value("col1").toString().compare("") == 0)
		settings.setValue("col1", "10");
	if (settings.value("col2").toString().compare("") == 0)
		settings.setValue("col2", "25");
	if (settings.value("col3").toString().compare("") == 0)
		settings.setValue("col3", "12");
	if (settings.value("col4").toString().compare("") == 0)
		settings.setValue("col4", "12");
	if (settings.value("col5").toString().compare("") == 0)
		settings.setValue("col5", "10");
	if (settings.value("col6").toString().compare("") == 0)
		settings.setValue("col6", "9");
	if (settings.value("col7").toString().compare("") == 0)
		settings.setValue("col7", "11");
	if (settings.value("col8").toString().compare("") == 0)
		settings.setValue("col8", "11");
	if (settings.value("col9").toString().compare("") == 0)
		settings.setValue("col9", "10");
	if (settings.value("col10").toString().compare("") == 0)
		settings.setValue("col10", "12");
	if (settings.value("col11").toString().compare("") == 0)
		settings.setValue("col11", "12");
	if (settings.value("col12").toString().compare("") == 0)
		settings.setValue("col12", "12");
	if (settings.value("col13").toString().compare("") == 0)
		settings.setValue("col13", "12");
	if (settings.value("col14").toString().compare("") == 0)
		settings.setValue("col14", "12");

	settings.endGroup();

	settings.sync();
}

/** Clears content of the QTableWidget passed in the input
 *  @param QTableWidget
 */
void MainWindow::tableClear (QTableWidget * tab)
{
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

	int year = tmp.left(4).toInt();
	tmp = tmp.remove(0, 4);
	int month = tmp.left(2).toInt();
	tmp = tmp.remove(0, 2);
	int day = tmp.toInt();
	QDate tmpDate(year, month, day);

	// if debugOn()
	// qDebug() << __FUNCTION__ << __LINE__ << nameToCheck
	//		<< filtrStart->date().toString() << tmpDate.toString()
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
	QStringList pliczki = allFiles.entryList();
	int i, max = pliczki.count();
	for (i = 0; i < max; ++i) {
		if (applyFiltr(pliczki[i])) {
			// qDebug(pliczki[i]);
			insertRow(tableH, tableH->rowCount());
			text = pliczki[i];
			tableH->item(tableH->rowCount() - 1, 0)->setText(text);

			QFile file(progDir + "/faktury/" + pliczki[i]);

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
					"nr", "NULL"));
			tableH->item(tableH->rowCount() - 1, 2)->setText(root.attribute(
					"data.sprzed", "NULL"));
			tableH->item(tableH->rowCount() - 1, 3)->setText(root.attribute(
					"type", "NULL"));
			QDomNode nab;
			nab = root.firstChild();
			nab = nab.toElement().nextSibling();
			tableH->item(tableH->rowCount() - 1, 4)->setText(
					nab.toElement().attribute("nazwa", "NULL"));
			tableH->item(tableH->rowCount() - 1, 5)->setText(
					nab.toElement().attribute("nip", "NULL"));
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
		QTableWidgetItem *i = tableH->selectedItems()[0];
		QString name = i->text();

		// qDebug() << name;

		QFile file(pdGlob + "/faktury/" + name);
		if (file.exists())
			file.remove();
		tableH->removeRow(i->row());
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
  qDebug ("%s %s:%d", __FUNCTION__, __FILE__, __LINE__);
  int row = tableK->selectedItems()[0]->row();
  qDebug ()<<tableK->item(row, 0)->text();

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



