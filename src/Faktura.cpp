#include "moc_Faktura.cpp"
#include <QDateTime>
#include <QDir>
#include <QProcess>
#include <QApplication>
#include <QMessageBox>
#include <QTextCodec>
#include <QTextStream>
#include <QDebug>
#include <QPrinter>
#include <QPrintPreviewDialog>
#include <QPrintDialog>
#include <QTextDocument>

#include "KontrahenciLista.h"
#include "TowaryLista.h"
#include "ZmienIlosc.h"
#include "CustomPayment.h"
#include "MainWindow.h"
#include "Kontrahenci.h"
#include "IDataLayer.h"

#include "Const.h"

enum InvoiceType {FVat, FPro, EFVat, EFPro};
short invType;

/** Constructor
 */
Faktura::Faktura(QWidget *parent, IDataLayer *dl) :
	QDialog(parent) {
	setupUi(this);

	dataLayer = dl;
	pforma = false;
	kAdded = false;
	init();
}

/** Destructor
 */
Faktura::~Faktura() {

}
/** Init method
 */
void Faktura::init() {
	invType = FVat;
	if (pforma)
		invType = FPro;

	// set width of the columns on the products list
	sett().beginGroup("fakturaForm");
	tableTow->setColumnWidth(0, sett().value("towCol0", QVariant(0)).toInt()); //index
	tableTow->setColumnWidth(1, sett().value("towCol1", QVariant(90)).toInt()); // nazwa
	tableTow->setColumnWidth(2, sett().value("towCol2", QVariant(35)).toInt()); // kod
	tableTow->setColumnWidth(3, sett().value("towCol3", QVariant(35)).toInt()); // kod
	tableTow->setColumnWidth(4, sett().value("towCol4", QVariant(40)).toInt()); // ilosc
	tableTow->setColumnWidth(5, sett().value("towCol5", QVariant(30)).toInt()); // jm
	tableTow->setColumnWidth(6, sett().value("towCol6", QVariant(30)).toInt()); // rabat
	tableTow->setColumnWidth(7, sett().value("towCol7", QVariant(60)).toInt()); // cena jedn.
	tableTow->setColumnWidth(8, sett().value("towCol8", QVariant(60)).toInt()); // netto
	tableTow->setColumnWidth(9, sett().value("towCol9", QVariant(30)).toInt()); // vat
	tableTow->setColumnWidth(10,
			sett().value("towCol10", QVariant(50)).toInt()); // netto *  (wzor vat)
	sett().endGroup();

	// set all the dates to todays date -> could be logical date :)
	sellingDate->setDate(QDate::currentDate());
	productDate->setDate(QDate::currentDate());
	liabDate->setDate(QDate::currentDate());

	// connects
	connect(addTwBtn, SIGNAL(clicked()), this, SLOT(addTow()));
	connect(kListGet, SIGNAL(clicked()), this, SLOT(getCustomer()));
	connect(rmTowBtn, SIGNAL(clicked()), this, SLOT(delTowar()));
	connect(editTwBtn, SIGNAL(clicked()), this, SLOT(editTowar()));
	connect(backBtn, SIGNAL(clicked()), this, SLOT(backBtnClick()));
	connect(closeBtn, SIGNAL(clicked()), this, SLOT(canQuit()));
    connect(saveBtn, SIGNAL(clicked()), this, SLOT(saveInvoice()));
    connect(printBtn, SIGNAL(clicked()), this, SLOT(makeInvoice()));
	connect(tableTow, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(editTowar()));
    connect(tableTow, SIGNAL(itemActivated(QTableWidgetItem *)), this,
				SLOT(tableActivated(QTableWidgetItem *)));
    connect(tableTow, SIGNAL(itemClicked(QTableWidgetItem *)), this,
				SLOT(tableActivated(QTableWidgetItem *)));
    connect(additEdit, SIGNAL(textChanged(QString)), this, SLOT(textChanged(QString)));
    connect(platCombo, SIGNAL(currentIndexChanged (QString)), this, SLOT(payTextChanged(QString)));
    connect(currCombo, SIGNAL(currentIndexChanged (QString)), this, SLOT(textChanged(QString)));
    connect(sellingDate, SIGNAL(dateChanged (QDate)), this, SLOT(dateChanged (QDate)));
    connect(productDate, SIGNAL(dateChanged (QDate)), this, SLOT(dateChanged (QDate)));
    connect(liabDate, SIGNAL(dateChanged (QDate)), this, SLOT(dateChanged (QDate)));
	connect(rabatValue, SIGNAL(valueChanged(int)), this, SLOT(discountChange()));
	connect(constRab, SIGNAL(stateChanged(int)), this, SLOT(discountConstChange()));
	connect(addKButton, SIGNAL(clicked()), this, SLOT(kontrClick()));



	// Calulcate next number of the invoice
	QString tmp;
	if (pforma) {
		tmp = sett().value("fpro").toString();
		invoiceType = s_PROFORMA;
	} else {
		tmp = sett().value("fvat").toString();
		invoiceType = s_INVOICE;
	}

	/*
	QStringList one1 = tmp.split("/");
	int nr = one1[0].toInt() + 1;
	lastInvoice = sett().numberToString(nr) + "/" + QDate::currentDate().toString(
			"MM/yyyy");
	frNr->setText(lastInvoice);
	*/

	// load payments method and currencies
	platCombo->insertItems(0, sett().value("payments").toString().split("|"));
	currCombo->insertItems(0, sett().value("waluty").toString().split("|"));

	if (sett().value ("addText").toString().compare("") != 0 )
		additEdit->setText(sett().value("addText").toString());

	backBtnClick();

	// set window icon
	QIcon icon;
	icon.addPixmap(QPixmap(":/res/icons/nowa_faktura.png"),
			QIcon::Normal, QIcon::Off);
	this->setWindowIcon(icon);

	rmTowBtn->setEnabled(false);
	editTwBtn->setEnabled(false);
	liabDate->setEnabled(false);
	rabatValue->setEnabled(false);
	canClose = true;
}


// ---- SLOTS START  --//////////////////////////////////////////////////////////////////////////////////

void Faktura::kontrClick() {
	Kontrahenci *kontrWindow;
	kontrWindow = new Kontrahenci(this, 0, dataLayer);
	//qDebug ("%s %s:%d", __FUNCTION__, __FILE__, __LINE__);
	if (kontrWindow->exec() == QDialog::Accepted) {
		kAdded = true;
		QStringList row = kontrWindow->ret.split("|");
		kontrName->setText (row[0] + "," + row[3] + "," + row[6] + " " + row[2] + "," +  s_TIC + row[5]);
		kontrName->setCursorPosition(0);
	}
	delete kontrWindow;
	kontrWindow = NULL;
}

void Faktura::keyPressEvent(QKeyEvent * event) {
	// qDebug() << __FUNCTION__;
	// for now not really used could be deleted
	if (event->key() == Qt::Key_Escape) {
		canQuit();
	}

}

/** Slot getCustomer
 *  Opens window with the list of the customers
 */
void Faktura::getCustomer () {
  KontrahenciLista *klWindow = new KontrahenciLista(this);
  if (klWindow->exec () == QDialog::Accepted)
    {
      kontrName->setText (klWindow->ret);
      kontrName->setCursorPosition (1);
      saveBtn->setEnabled(true);
      canClose = false;
    }
  delete klWindow;
  klWindow = NULL;
}

/** Slot
 *  Enables and disables rebatValue field
 */
void Faktura::discountConstChange(){
	if (constRab->isChecked()) {
		rabatValue->setEnabled(true);
		saveBtn->setEnabled(true);
		calculateDiscount();
		calculateSum();
	} else {
		rabatValue->setValue(0);
		rabatValue->setEnabled(false);
	}
}

/** Slot discountChange
 *  Used to recalculate discount when spinBox arrows are pressed.
 */
void Faktura::discountChange() {
	// qDebug() << __FUNCTION__;
	calculateDiscount();
	calculateSum();
	saveBtn->setEnabled(true);
	canClose = false;
}

/** Slot addTow
 *  Shows window with a list of products
 */
void Faktura::addTow() {
	TowaryLista *twWindow = new TowaryLista(this);
	if (twWindow->exec() == QDialog::Accepted) {
		MainWindow::insertRow(tableTow, tableTow->rowCount());
		// qDebug() << twWindow->ret;
		QStringList row = twWindow->ret.split("|");
		int rowNum = tableTow->rowCount() - 1;
		tableTow->item(rowNum, 0)->setText(sett().numberToString(
				tableTow->rowCount())); // id
		tableTow->item(rowNum, 1)->setText(row[0]); // name
		tableTow->item(rowNum, 2)->setText(row[1]); // code
		tableTow->item(rowNum, 3)->setText(row[2]); // pkwiu
		tableTow->item(rowNum, 4)->setText(row[3]); // quantity
		tableTow->item(rowNum, 5)->setText(row[4]); // qType
		tableTow->item(rowNum, 6)->setText(row[5]); // discount
		tableTow->item(rowNum, 7)->setText(row[6]); // price
		tableTow->item(rowNum, 8)->setText(row[7]); // nett
		tableTow->item(rowNum, 9)->setText(row[8]); // vat
		tableTow->item(rowNum, 10)->setText(row[9]); // gross
		saveBtn->setEnabled(true);
		canClose = false;
		if (constRab->isChecked())
			calculateDiscount();
		calculateSum();
	}
	delete twWindow;
	twWindow = NULL;
}

/** Slot delTowar
 *  Remove the product from the list
 */
void Faktura::delTowar() {
	tableTow->removeRow(tableTow->currentRow());
	for (int i = 0; i < tableTow->rowCount(); ++i) {
		tableTow->item(i, 0)->setText(sett().numberToString(i + 1));
	}
	calculateSum();
	saveBtn->setEnabled(true);
	canClose = false;
}

/** Slot editTowar
 *  Allows to edit selected product. Opens changeAmount window.
 */
void Faktura::editTowar() {
	// qDebug() << __FUNCTION__ << ": ENTER";
	// we can only modify quantity
	ZmienIlosc *changeQuant = new ZmienIlosc(this);
	changeQuant->nameTow->setText(
			tableTow-> item(tableTow->currentRow(), 1)->text());
	changeQuant->codeTow->setText(
			tableTow-> item(tableTow->currentRow(), 2)->text());
	changeQuant->spinAmount->setValue(tableTow-> item(tableTow->currentRow(),
			4)->text().toInt());
	if (changeQuant->exec() == QDialog::Accepted) {
		int currentRow = tableTow->currentRow();
		tableTow->item(currentRow, 4)->setText(changeQuant->spinAmount->cleanText());
		saveBtn->setEnabled(true);
		canClose = false;
		calculateOneDiscount(currentRow);
		calculateSum();
	}
	delete changeQuant;
	changeQuant = NULL;
	// qDebug() << __FUNCTION__ << ": EXIT";
}

/** Slot
 *  Used populate invoice symbol
 */
void Faktura::backBtnClick() {
	QString tmp;

	QString prefix, suffix;

	if (pforma) {
		tmp = sett().value("fpro").toString();
	} else {
		tmp = sett().value("fvat").toString();
	}
	prefix = sett().value("prefix").toString();

	QStringList one1 = tmp.split("/");
	one1[0] = one1[0].remove(prefix);

	int nr = one1[0].toInt() + 1;
	lastInvoice = prefix + numbersCount(nr,
			sett().value("chars_in_symbol").toInt());

	if (sett().value("day") .toBool())
		lastInvoice += "/" + QDate::currentDate().toString("dd");

	if (sett().value("month") .toBool())
		lastInvoice += "/" + QDate::currentDate().toString("MM");

	if (sett().value("year") .toBool()) {
		if (!sett().value("shortYear") .toBool())
			lastInvoice += "/" + QDate::currentDate().toString("yy");
		else
			lastInvoice += "/" + QDate::currentDate().toString("yyyy");
	}
	suffix = sett().value("sufix").toString();
	lastInvoice += suffix;
	frNr->setText(lastInvoice);
	saveBtn->setEnabled(true);
}

/** Slot
 *  Validate close and save if requested
 */
void Faktura::canQuit() {
	// qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__ << ": canClose " << canClose;

	// canClose == false -> data changed
	if (canClose || QMessageBox::warning(this, "QFaktury", trUtf8("Dane zostały zmienione czy chcesz zapisać?"), trUtf8("Tak"), trUtf8("Nie"), 0, 0,
			1) == 1) {
		saveColumnsWidth();
		reject();
	} else {
		saveInvoice();
		if (saveFailed) {
			return;
		}
		saveColumnsWidth();
		accept();
	}
}

/** Slot tableActivated
 *  Enable/Disable buttons
 */
void Faktura::tableActivated(QTableWidgetItem * item) {
	// qDebug() << __FUNCTION__;
	if (item != NULL || !item->text().isEmpty()) {
		rmTowBtn->setEnabled(true);
		editTwBtn->setEnabled(true);
	}
}

/** Slot payTextChanged
 *  Activates buttons
 */
void Faktura::payTextChanged(QString text) {
	// qDebug() << __FUNCTION__ <<  platCombo->currentIndex();
	if (platCombo->currentIndex() > 0) {
		liabDate->setEnabled(true);
	} else {
		liabDate->setEnabled(false);
	}

	// qDebug() << platCombo->currentIndex()  <<  platCombo->count();
	if (platCombo->currentIndex() == platCombo->count() - 1) {
		if (sett().stringToDouble(sum3->text()) == 0) {
			QMessageBox::critical(this, "QFaktury", trUtf8("Taki sposób płatności nie może zostać wybrany ponieważ kwota do zapłaty wynosi 0."));
			platCombo->setCurrentIndex(0);
			return;
		}
		CustomPayment *cp = new CustomPayment(this);
		cp->setInvoiceAmount(sett().stringToDouble(sum3->text()));
		if (cp->exec() ==  QDialog::Accepted) {
			custPaymData = cp->custPaymData;
			liabDate->setEnabled(false);
		} else {
			platCombo->setCurrentIndex(0);
		}
		delete cp;
		cp = NULL;
	}

	textChanged(text);
}

/** Slot textChanged
 *  Activates buttons
 */
void Faktura::textChanged(QString ) {
	saveBtn->setEnabled(true);
	canClose = false;
}

/** Slot dateChanged
 *  Activates buttons
 */
void Faktura::dateChanged(QDate ) {
	saveBtn->setEnabled(true);
	canClose = false;
}


/** Slot saveInvoice
 *  Generates Invoice XML
 */
void Faktura::saveInvoice() {
	// qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << fName;

	if (!validateForm()) return;

	InvoiceData invData;
	setData(invData);
	result = dataLayer->invoiceInsertData(inv, invType);

	saveBtn->setEnabled(false);
	rmTowBtn->setEnabled(false);
	editTwBtn->setEnabled(false);

	saveFailed = false;
	canClose = true;
}

/** Slot makeInvoice
 *  Generate html with invoice and show Print Preview dialog
 */
void Faktura::makeInvoice() {
	if (kontrName->text() == "") {
		QMessageBox::information(this, "QFaktury", trUtf8("Wybierz kontrahenta"),
				QMessageBox::Ok);
		return;
	}

	if (tableTow->rowCount() == 0) {
		QMessageBox::information(this, "QFaktury", trUtf8("Nie ma towarów"),
		QMessageBox::Ok);
		return;
	}

	// if (fraStrList.isEmpty()) {
	// for perfomance reasons could be done... but not now TODO

	fraStrList.clear();
	makeInvoiceHeadarHTML();

	makeInvoiceHeadar(true, false, true);
	makeInvoiceBody();
	makeInvoiceProducts();
	makeInvoiceSumm();
	makeInvoiceSummAll();
	makeInvoiceFooter();

    // fraStrList +="    <h1 class=\"page_break\">&nbsp;</h1>";

	int numberOfCopies = sett().value("numberOfCopies", 2).toInt();
	for (int i = 1; i <= numberOfCopies; i++) {
		// prrint copy
		makeInvoiceHeadar(true, true, false);
		makeInvoiceBody();
		makeInvoiceProducts();
		makeInvoiceSumm();
		makeInvoiceSummAll();
		makeInvoiceFooter();
	}

	makeInvoiceFooterHtml();

	print();

	saveBtn->setFocus();
}

/** Slot print
 *  Helper slot used to display print preview
 */
void Faktura::printSlot(QPrinter *printer) {
	// qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

    QTextDocument doc(invoiceType);
    QString s;
    for (QStringList::iterator it = fraStrList.begin(); it != fraStrList.end(); ++it) {
        s+=*it+"\n";
    }
    // qDebug of the whole invoice :)

	QFile file(sett().getWorkingDir() + "/invoice.html");
	if (file.open(QIODevice::WriteOnly)) {
		QTextStream stream(&file);
		for (QStringList::Iterator it = fraStrList.begin(); it
				!= fraStrList.end(); ++it)
			stream << *it << "\n";
		file.close();
	}

    doc.setHtml(s);
    doc.print(printer);
}

/** Slot
 *  Print slot
 */
void Faktura::print() {
	// qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;
	//print invoice
	QPrinter printer(QPrinter::HighResolution);
	QPrintPreviewDialog preview(&printer, this);
	preview.setWindowFlags(Qt::Window);
	// preview.setZoomMode(QPrintPreviewWidget::FitToWidth);
	preview.setWindowTitle(invoiceType + s_WIN_PRINTPREVIEW);

	connect(&preview, SIGNAL(paintRequested(QPrinter *)), this, SLOT(printSlot(QPrinter *)));
	if (preview.exec() == 1) {
	}
}

// ---- SLOTS END --//////////////////////////////////////////////////////////////////////////////////
// ******************************** XML Helpers START **********************************************
/** Check if data on the form is correct
 */
bool Faktura::validateForm() {
	if (kontrName->text() == "") {
		QMessageBox::critical(this, "QFaktury", trUtf8("Nie ma kontrahenta."),
				QMessageBox::Ok);
		saveFailed = true;
		return false;
	}

	if (tableTow->rowCount() == 0) {
		QMessageBox::critical(this, "QFaktury", trUtf8("Nie ma towarów."),
				QMessageBox::Ok);
		saveFailed = true;
		return false;
	}
	return true;
}

// ******************************** XML Helpers END **********************************************

// Generate Invoice HTML methods --- START ---

void Faktura::makeInvoiceHeadarHTML() {
	fraStrList += "<html><head>";
	fraStrList += "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />"; //@TODO
	fraStrList += "<meta name=\"creator\" value=\"http://www.e-linux.pl\" />";
	//fraStrList += "<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\" />";
	fraStrList += "</head>";

	if (windowTitle().right(3) == "VAT") {
		fraStrList += "<title>"+ invoiceType  +"</title>";
	} else {
		fraStrList += "<title>" + invoiceType + "</title>";
	}

	fraStrList += "<style type=\"text/css\"> ";
	QFile file(sett().getTemplate());
	if (file.open(QIODevice::ReadOnly)) {
		QTextStream stream(&file);
		QString line;
		while (!stream.atEnd()) {
			line = stream.readLine();
			fraStrList += line;
		}
		file.close();
	} else {
		qWarning() << "Could not open CSS file: " << file.fileName();
	}
	fraStrList += "</style>";


	fraStrList += "<body>";
}


void Faktura::makeInvoiceHeadar(bool sellDate, bool breakPage, bool original) {

	QString breakPageStr = "class=\"page_break\"";
	if (breakPage == false) breakPageStr = "";

	fraStrList += "<table comment=\"headar table\" width=\"100%\" border=\"0\"" + breakPageStr + ">";
	fraStrList += "<tr>";
		fraStrList += "<td width=\"60%\" align=\"center\" valign=\"bottom\">";
		fraStrList += "<span class=\"stamp\">";
		QString logo = sett().value("logo").toString();
		if (logo != "") {
			fraStrList += "<img src=\"" + logo + "\" width=\"100\" " + " height=\"100\"+ >";
		} else {
			fraStrList += trUtf8("Pieczęć wystawcy");
		}
		fraStrList += "</span>";
		fraStrList += "</td>";

		fraStrList += "<td align=\"right\">";
		fraStrList += "<span style=\"font-size:12pt; font-weight:600\">";
		fraStrList += invoiceType + "<br/>";
		fraStrList += trUtf8("Nr: ") + frNr->text() + "<br></span>";
		fraStrList += "<span class=\"dates\">" + trUtf8("Data wystawienia: ")
				    + productDate->date().toString(sett().getDateFormat()) + "<br>";

		if (sellDate)
			fraStrList += trUtf8("Data sprzedaży: ")
				+ sellingDate->date().toString(sett().getDateFormat())
				+ "<br>";
		fraStrList += "</span></td><td width=\"3%\">&nbsp;</td>";
	fraStrList += "</tr>";
	fraStrList += "<tr>";
		fraStrList += "<td colspan=\"2\" align=\"right\" valign=\"top\"><br>";
		if (original) {
		fraStrList += trUtf8("ORYGINAŁ");
		} else {
		fraStrList += trUtf8("KOPIA");
		}
		fraStrList += "<br></td><td width=\"3%\">&nbsp;</td>";
	fraStrList += "</tr>";
	fraStrList += "</table>";
	fraStrList += "<hr>";
	fraStrList += "</td></tr>";
}


void Faktura::makeInvoiceBody() {
	fraStrList += "<tr><td>";

	fraStrList += "<table width=\"100%\" border=\"0\">";
	fraStrList += "<tr class=\"persons\">";
		fraStrList += "<td width=\"20\">&nbsp;</td>";
		fraStrList += "<td width=\"48%\"> ";
		fraStrList += trUtf8("Sprzedawca:")+"<br>";
		QSettings userSettings("elinux", "user");

		sett().beginGroup("printpos");
		if (sett().value("usernazwa").toBool())
			fraStrList += userSettings.value("name").toString() + "<br>";
		if (sett().value("useradres").toBool())
			fraStrList += userSettings.value("address").toString() + "<br>"; // trUtf8("Ul. ") +
		if (sett().value("usermiejscowosc").toBool())
			fraStrList += userSettings.value("zip").toString() + " ";
		if (sett().value("usermiejscowosc").toBool())
			fraStrList += userSettings.value("city").toString() + "<br>";
		if (sett().value("usernip").toBool())
			fraStrList += trUtf8("NIP: ") + userSettings.value("tic").toString() + "<br>";
		if (sett().value("userkonto").toBool())
			fraStrList += trUtf8("Nr konta: ")
				+ userSettings.value("account").toString().replace("-", " ") + "<br>";
		sett().endGroup();

		fraStrList += "</td>";
		fraStrList += "<td width=\"20\">&nbsp;</td>";
		fraStrList += "<td width=\"48%\">";
		fraStrList += trUtf8("Nabywca:") + "<br>" + kontrName->text().replace(",", "<br>") + "<br>";
		fraStrList += "</td>";
	fraStrList += "</tr>";
	fraStrList += "</table>";

	fraStrList += "<hr>";
	fraStrList += "</td></tr>";
}

void Faktura::makeInvoiceProductsHeadar() {
	int currentPercent = 0;
	fraStrList += "<tr align=\"center\" valign=\"middle\" class=\"productsHeader\" >";

	if (sett().value("faktury_pozycje/Lp").toBool()) {
		currentPercent = 3;
		fraStrList += "<td align=\"center\" width=\""+ sett().numberToString(currentPercent) + "%\">" + trUtf8("Lp.") + "</td>";
		currentPercent = 0;
	} else {
		currentPercent += 3;
	}
	if (sett().value("faktury_pozycje/Nazwa").toBool()) {
		currentPercent += 25;
		fraStrList += "<td align=\"center\" width=\""+ sett().numberToString(currentPercent) + "%\">" + trUtf8("Nazwa") + "</td>";
		currentPercent = 0;
	} else {
		currentPercent += 25;
	}
	if (sett().value("faktury_pozycje/Kod").toBool()) {
		currentPercent += 7;
		fraStrList += "<td align=\"center\" width=\""+ sett().numberToString(currentPercent) + "%\">" + trUtf8("Kod") + "</td>";
		currentPercent = 0;
	} else {
		currentPercent += 7;
	}
	if (sett().value("faktury_pozycje/pkwiu").toBool()) {
		currentPercent += 7;
		fraStrList += "<td align=\"center\" width=\""+ sett().numberToString(currentPercent) + "%\">" + trUtf8("PKWiU") + "</td>";
		currentPercent = 0;
	} else {
		currentPercent += 7;
	}
	if (sett().value("faktury_pozycje/ilosc").toBool()) {
		// currentPercent += 7;
		fraStrList += "<td align=\"center\" width=\""+ sett().numberToString(7) + "%\">" + trUtf8("Ilość") + "</td>";
		// currentPercent = 0;
	} else {
		currentPercent += 7;
	}
	if (sett().value("faktury_pozycje/jm").toBool()) {
		// currentPercent += 3;
		fraStrList += "<td align=\"center\" width=\""+ sett().numberToString(3) + "%\">" + trUtf8("jm.") + "</td>";
		// currentPercent = 0;
	} else {
		currentPercent += 3;
	}
	if (sett().value("faktury_pozycje/cenajedn").toBool()) {
		currentPercent += 7;
		fraStrList += "<td align=\"center\" width=\""+ sett().numberToString(currentPercent) + "%\">" + trUtf8("Cena jdn.") + "</td>";
		currentPercent = 0;
	} else {
		currentPercent += 7;
	}
	if (sett().value("faktury_pozycje/wartnetto").toBool()) {
		currentPercent += 7;
		fraStrList += "<td align=\"center\" width=\""+ sett().numberToString(currentPercent) + "%\">" + trUtf8("Wartość Netto") + "</td>";
		currentPercent = 0;
	} else {
		currentPercent += 7;
	}
	if (sett().value("faktury_pozycje/rabatperc").toBool()) {
		// currentPercent += 3;
		fraStrList += "<td align=\"center\" width=\""+ sett().numberToString(3) + "%\">" + trUtf8("Rabat %") + "</td>";
		// currentPercent = 0;
	} else {
		currentPercent += 3;
	}
	if (sett().value("faktury_pozycje/rabatval").toBool()) {
		currentPercent += 3;
		fraStrList += "<td align=\"center\" width=\""+ sett().numberToString(currentPercent) + "%\">" + trUtf8("Rabat Wartość") + "</td>";
		currentPercent = 0;
	} else {
		currentPercent += 3;
	}
	if (sett().value("faktury_pozycje/nettoafter").toBool()) {
		currentPercent += 7;
		fraStrList += "<td align=\"center\" width=\""+ sett().numberToString(currentPercent) + "%\">" + trUtf8("Netto po rabacie") + "</td>";
		currentPercent = 0;
	} else {
		currentPercent += 7;
	}
	if (sett().value("faktury_pozycje/vatval").toBool()) {
		// currentPercent += 7;
		fraStrList += "<td align=\"center\" width=\""+ sett().numberToString(7) + "%\">" + trUtf8("Stawka VAT") + "</td>";
		// currentPercent = 0;
	} else {
		currentPercent += 7;
	}
	if (sett().value("faktury_pozycje/vatprice").toBool()) {
		currentPercent += 7;
		fraStrList += "<td align=\"center\" width=\""+ sett().numberToString(currentPercent) + "%\">" + trUtf8("Kwota Vat") + "</td>";
		currentPercent = 0;
	} else {
		currentPercent += 7;
	}
	if (sett().value("faktury_pozycje/bruttoval").toBool()) {
		currentPercent += 7;
		fraStrList += "<td align=\"center\" width=\""+ sett().numberToString(currentPercent) + "%\">" + trUtf8("Wartość Brutto") + "</td>";
		currentPercent = 0;
	} else {
		currentPercent += 7;
	}
	fraStrList += "</tr>";

}

void Faktura::makeInvoiceProducts() {
	fraStrList += "<tr><td>";
	// fraStrList += "<br>";
	fraStrList += "<table border=\"1\" cellspacing=\"0\" cellpadding=\"5\" width=\"100%\">";

	makeInvoiceProductsHeadar();

	for (int i = 0; i < tableTow->rowCount(); ++i) {
		// for (int j=1; j<11;++j)
		// 	qDebug() << j << " : " << tableTow->item(i, j)->text();

		fraStrList += "<tr valign=\"middle\" align=\"center\" class=\"products\">";
		// lp, nazwa, kod, pkwiu, ilosc, jm, rabat, cena jm., netto, vat, brutto
		if (sett().value("faktury_pozycje/Lp").toBool())
			fraStrList += "<td align=\"center\" >" + sett().numberToString(i + 1) + "</td>";
		if (sett().value("faktury_pozycje/Nazwa") .toBool())
			fraStrList += "<td align=\"left\">" + tableTow->item(i, 1)->text() + "</td>";
		if (sett().value("faktury_pozycje/Kod") .toBool())
			fraStrList += "<td align=\"center\" >" + tableTow->item(i, 2)->text() + "</td>";
		if (sett().value("faktury_pozycje/pkwiu") .toBool())
			fraStrList += "<td align=\"center\" >" + tableTow->item(i, 3)->text() + "</td>";
		if (sett().value("faktury_pozycje/ilosc") .toBool())
			fraStrList += "<td align=\"center\" >" + tableTow->item(i, 4)->text() + "</td>";
		if (sett().value("faktury_pozycje/jm") .toBool())
			fraStrList += "<td align=\"center\" >" + tableTow->item(i, 5)->text() + "</td>";
		if (sett().value("faktury_pozycje/cenajedn") .toBool())
			fraStrList += "<td align=\"center\" >" + tableTow->item(i, 7)->text() + "</td>";
		double discountVal = sett().stringToDouble(tableTow->item(i, 8)->text()) *
								(tableTow->item(i, 6)->text().toDouble() * 0.01);
		double nettMinusDisc = sett().stringToDouble(tableTow->item(i, 8)->text()) - discountVal;
		if (sett().value("faktury_pozycje/wartnetto") .toBool())
			fraStrList += "<td align=\"center\" >" + tableTow->item(i, 8)->text()	+ "</td>"; // netto
		if (sett().value("faktury_pozycje/rabatperc") .toBool())
			fraStrList += "<td align=\"center\" >" + tableTow->item(i, 6)->text()	+ "%</td>"; // rabat
		if (sett().value("faktury_pozycje/rabatval") .toBool())
			fraStrList += "<td align=\"center\" >" + sett().numberToString(discountVal, 'f',  2)	+ "</td>";
		if (sett().value("faktury_pozycje/nettoafter") .toBool())
			fraStrList += "<td align=\"center\" >" + sett().numberToString(nettMinusDisc, 'f', 2) + "</td>";
		if (sett().value("faktury_pozycje/vatval") .toBool())
			fraStrList += "<td align=\"center\" >" + tableTow->item(i, 9)->text()	+ "%</td>";
		double vatPrice = sett().stringToDouble(tableTow->item(i, 10)->text())
								- sett().stringToDouble(tableTow->item(i, 8)->text()); // brutt-nett :)
		if (sett().value("faktury_pozycje/vatprice") .toBool())
			fraStrList += "<td align=\"center\" >" + sett().numberToString(vatPrice, 'f', 2) + "</td>";
		if (sett().value("faktury_pozycje/bruttoval") .toBool())
			fraStrList += "<td align=\"center\" >" + tableTow->item(i, 10)->text() + "</td>";
		fraStrList += "</tr>";
	}

	fraStrList += "</table>";
}

void Faktura::makeInvoiceSumm() {
	double vatPrice = sett().stringToDouble(sum3->text()) - sett().stringToDouble(sum1->text());
	fraStrList += "<br><table width=\"100%\" border=\"0\" cellpadding=\"5\">";
	fraStrList += "<tr class=\"productsSumHeader\" valign=\"middle\">";
		fraStrList += "<td width=\"67%\" align=\"center\">&nbsp;</td>";
		fraStrList += "<td width=\"11%\" align=\"center\">" + trUtf8("Wartość Netto") + "</td>"; // netto
		fraStrList += "<td width=\"11%\" align=\"center\">" + trUtf8("Kwota VAT") + "</td>";// vat
		fraStrList += "<td width=\"11%\" align=\"center\">" + trUtf8("Wartość Brutto") + "</td>"; // brutto
	fraStrList += "</tr><tr class=\"productsSum\">";
		fraStrList += "<td align=\"right\">" + trUtf8("Razem:") + "</td>";
		fraStrList += "<td align=\"center\">" + sum1->text() + "</td>"; // netto
		fraStrList += "<td align=\"center\">" + sett().numberToString(vatPrice, 'f', 2) + "</td>";// vat
		fraStrList += "<td align=\"center\">" + sum3->text() + "</td>"; // brutto
	fraStrList += "</tr>";
	fraStrList += "</table><br><br>";
}

void Faktura::makeInvoiceSummAll() {
	fraStrList += "</td></tr>"; // closing products row
	fraStrList += "<tr comment=\"podsumowanie\"><td>";

	fraStrList += "<table width=\"100%\" border=\"0\">";
	fraStrList += "<tr class=\"summary\">";
		fraStrList += "<td width=\"3%\">&nbsp;</td>";
		fraStrList += "<td width=\"48%\"><span style=\"toPay\">";
		fraStrList += trUtf8("Do zapłaty: ") + sum3->text() + " "
					+ currCombo->currentText() + "</span><br>";
		ConvertAmount* conv = new ConvertAmount();
		fraStrList += trUtf8("słownie:")
				+ conv->convertPL(sum3->text(), currCombo->currentText()) + "<br>";
		delete conv;
		QString paym1 = sett().value("paym1").toString();
		if (platCombo->currentIndex() == 0) {
			fraStrList += trUtf8("forma płatności: ") + platCombo->currentText() + "<br><b>";
			fraStrList += trUtf8("Zapłacono gotówką") + "<br>";
		} else if ((platCombo->currentIndex() == platCombo->count() -1) && (custPaymData != NULL)) {
			fraStrList += "<span style=\"toPay\">";
			fraStrList += QString(trUtf8("Zapłacono: ") + custPaymData->payment1 + ": "
					+  sett().numberToString(custPaymData->amount1) + " " + currCombo->currentText() + " "
					+ custPaymData->date1.toString(sett().getDateFormat()) + "<br>");
			fraStrList += QString(trUtf8("Zaległości: ") + custPaymData->payment2 + ": "
					+  sett().numberToString(custPaymData->amount2) + " " + currCombo->currentText() + " "
					+ custPaymData->date2.toString(sett().getDateFormat()));
			fraStrList += "</span>";
		}  else {
			fraStrList += trUtf8("forma płatności: ") + platCombo->currentText() + "<br><b>";
			fraStrList += "<span style=\"payDate\">";
			fraStrList += trUtf8("termin płatności: ")
				+ liabDate->date().toString(sett().getDateFormat())	+ "<br>";
			fraStrList += "</span>";
		}

		fraStrList += "</b><br><br>";
		fraStrList += "<span class=\"additionalText\">"	+ additEdit->text() + "</span>";
		fraStrList += "</td>";
		fraStrList += "<td width=\"3%\">&nbsp;</td>";
		fraStrList += "<td width=\"48%\" valign=\"top\">";

			fraStrList += "<table width=\"90%\" border=\"0\">";
			fraStrList += "<tr class=\"stawkiHeader\"><td colspan=\"4\">";
					fraStrList += trUtf8("Ogółem stawkami:");
			fraStrList += "</td></tr>";
				fraStrList += getGroupedSums();
			fraStrList += "<tr>";
				fraStrList += "<td>&nbsp;</td>"; // netto
				fraStrList += "<td>&nbsp;</td>"; // stawka
				fraStrList += "<td>&nbsp;</td>"; // podatek
				fraStrList += "<td>&nbsp;</td>"; // brutto
			fraStrList += "</tr>";
			fraStrList += "</table>";

		fraStrList += "</td>";
	fraStrList += "</tr>";
	fraStrList += "</table>";

	fraStrList += "</td></tr>";
}

void Faktura::makeInvoiceFooter() {
	fraStrList += "<tr comment=\"podpis\" align=\"center\"><td>";
	fraStrList += "<br><br><br><br>";

		fraStrList += "<table width=\"80%\" border=\"0\">";
		fraStrList += "<tr>";
			fraStrList += "<td width=\"3%\">&nbsp;</td>";
			fraStrList += "<td width=\"43%\" align=\"center\"> ";
			fraStrList += "<hr width=\"100%\" noshade=\"noshade\" color=\"black\" />";
			fraStrList += "</td>";
			fraStrList += "<td width=\"7%\">&nbsp;</td>";
			fraStrList += "<td width=\"3%\">&nbsp;</td>";
			fraStrList += "<td width=\"43%\" align=\"center\"> ";
			fraStrList += "<hr width=\"100%\" noshade=\"noshade\" color=\"black\" />";
			fraStrList += "</td>";
		fraStrList += "</tr>";
		fraStrList += "<tr class=\"signature\">";
			fraStrList += "<td width=\"3%\">&nbsp;</td>";
			fraStrList += "<td width=\"43%\" align=\"center\"> ";
			fraStrList += trUtf8("Imię i nazwisko osoby upoważnionej")
					+ "<br>" + trUtf8(" do wystawienia faktury VAT");
			fraStrList += "</td>";
			fraStrList += "<td width=\"7%\">&nbsp;</td>";
			fraStrList += "<td width=\"3%\">&nbsp;</td>";
			fraStrList += "<td width=\"43%\" align=\"center\">";
			fraStrList += trUtf8("Imię i nazwisko osoby upoważnionej")
					+ "<br>" + trUtf8(" do odbioru faktury VAT");
			fraStrList += "</td>";
		fraStrList += "</tr>";
		fraStrList += "</table>";

	fraStrList += "</td></tr>";
	fraStrList += "</table>";

}

void Faktura::makeInvoiceFooterHtml() {
	fraStrList += "</body>";
	fraStrList += "</html>";
}

/** getGroupedSums
 *  Groups prices by VAT
 */
QString Faktura::getGroupedSums() {
	QStringList out;
	QStringList stawki = sett().value("stawki").toString().split("|");
	QMap<int, double> stawkiNetto;
	QMap<int, double> stawkiVat;
	QMap<int, double> stawkiBrutto;
	// every currency in int value is equal vat currency

	int ssize = stawki.size();
	// qDebug( "%d", ssize );

	// lp, nazwa, kod, pkwiu, ilosc, jm, rabat, cena jm., netto, vat, brutto
	for (int i = 0; i < tableTow->rowCount(); ++i) {
		for (int y = 0; y < ssize; ++y) {
			if (stawki[y] == tableTow->item(i, 9)->text()) {
				stawkiNetto[y] += sett().stringToDouble(tableTow->item(i, 8)->text());
				stawkiBrutto[y] += sett().stringToDouble(tableTow->item(i, 10)->text());
				// qDebug() << stawkiBrutto[y] << stawkiNetto[y] << stawkiBrutto[y] - stawkiNetto[y];
				stawkiVat[y] = stawkiBrutto[y] - stawkiNetto[y];
			} else {
				stawkiNetto[y] += 0;
				stawkiBrutto[y] += 0;
				stawkiVat[y] += 0;
			}
		}
	}

	for (int y = 0; y < ssize; ++y) {
		out += "<tr class=\"stawki\">";
		out += "<td width=\"30%\">" + sett().numberToString(stawkiNetto[y], 'f', 2) + "</td>"; // netto
		out += "<td width=\"10%\">" + stawki[y] + "</td>"; // stawka
		out += "<td width=\"30%\">" + sett().numberToString(stawkiVat[y], 'f', 2) + "</td>"; // podatek
		out += "<td width=\"30%\">" + sett().numberToString(stawkiBrutto[y], 'f', 2) + "</td>"; // brutto
		out += "</tr>";

	}
	return out.join(" ");
}
// Generate Invoice HTML methods --- END ---

/** Read data
 *  Used when editInvoice is invoked. Invoked from MainWindow class.
 */
void Faktura::readData(QString fraFile, int co) {
	backBtn->setEnabled(false);
	frNr->setEnabled(false);
	if (co == 0) {
		setWindowTitle(s_WIN_INVOICE_EDIT);
	} else {
		setWindowTitle(s_WIN_PROFORMA_EDIT);
	}

	InvoiceData invData;
	getData(dataLayer->invoiceSelectData(inv, invType));

	canClose = true;
	saveBtn->setEnabled(false);

	setIsEditAllowed(sett().value("edit").toBool());
	// if (constRab->isChecked())
	calculateDiscount();
	calculateSum();
}

/** Sets the editability
 */
void Faktura::setIsEditAllowed(bool isAllowed) {
	isEdit = true;
	frNr->setEnabled(isAllowed);
	backBtn->setEnabled(isAllowed);
	sellingDate->setEnabled(isAllowed);
	productDate->setEnabled(isAllowed);
	tableTow->setEnabled(isAllowed);
	rabatValue->setEnabled(isAllowed);
	rabatLabel->setEnabled(isAllowed);
	platCombo->setEnabled(isAllowed);
	liabDate->setEnabled(isAllowed);
	//reasonCombo->setEnabled( FALSE );
	additEdit->setEnabled(isAllowed);
	addTwBtn->setEnabled(isAllowed);
	rmTowBtn->setEnabled(isAllowed);
	editTwBtn->setEnabled(isAllowed);
	constRab->setEnabled(isAllowed);
	kListGet->setEnabled(isAllowed);
	currCombo->setEnabled(isAllowed);
	saveBtn->setEnabled(isAllowed);
	addKButton->setEnabled(isAllowed);
	liabDate->setEnabled(isAllowed);
	if (!isAllowed || rabatValue->value() == 0) {
		constRab->setChecked(false);
		rabatValue->setEnabled(false);
	} else {
		constRab->setChecked(true);
		rabatValue->setEnabled(true);
	}
	if (isAllowed && (platCombo->currentIndex() > 0)) {
		liabDate->setEnabled(true);
	} else {
		liabDate->setEnabled(false);
	}
}

/** Caclulate Discount
 */
void Faktura::calculateDiscount() {
	for (int i = 0; i < tableTow->rowCount(); ++i) {
		calculateOneDiscount(i);
	}
}

/** Caclulate Discount
 */
void Faktura::calculateOneDiscount(int i) {
	// qDebug() << __FUNCTION__ << __LINE__ << __FILE__;

	double quantity = 0, vat = 0, gross = 0;
	double netto = 0,  price = 0;
	double discountValue = 0, discount;

	price = sett().stringToDouble(tableTow->item(i, 7)->text());
	if (constRab->isChecked()) {
		discount = rabatValue->value() * 0.01;
	} else {
		discount = sett().stringToDouble(tableTow->item(i, 6)->text()) * 0.01;
	}
	quantity = sett().stringToDouble(tableTow->item(i, 4)->text());
	netto = (price * quantity);
	discountValue = netto * discount;
	netto -= discountValue;
	vat = sett().stringToDouble(tableTow->item(i, 9)->text());
	gross = netto * ((vat * 0.01) + 1);

	// qDebug() << price << quantity << netto << discount << discountValue << vat << gross;

    tableTow->item(i, 6)->setText(sett().numberToString(discount * 100, 'f', 0)); // discount
	// tableTow->item(i, 7)->setText(price); // price
	tableTow->item(i, 8)->setText(sett().numberToString(netto)); // nett
	// tableTow->item(i, 9)->setText(sett().numberToString(gross - vat)); // vat
	tableTow->item(i, 10)->setText(sett().numberToString(gross)); // gross

}

/** Calculate sum
 */
void Faktura::calculateSum() {
	// qDebug() << __FUNCTION__;
	double netto = 0, price = 0, quantity = 0, gross = 00;
	double discountValue = 0;

	nettTotal = 0;
	discountTotal = 0;
	grossTotal = 0;

	for (int i = 0; i < tableTow->rowCount(); ++i) {
		price = sett().stringToDouble(tableTow->item(i, 7)->text());
		quantity = sett().stringToDouble(tableTow->item(i, 4)->text());
		netto = sett().stringToDouble(tableTow->item(i, 8)->text());
		gross = sett().stringToDouble(tableTow->item(i, 10)->text());
		discountValue = (price * quantity) - netto;

		nettTotal += netto;
		discountTotal += discountValue;
		grossTotal += gross;

		// qDebug() << netto << discountValue << gross << " | " << tableTow->item(i, 8)->text();
	}

	sum1->setText(sett().numberToString(nettTotal, 'f', 2));
	sum2->setText(sett().numberToString(discountTotal, 'f', 2));
	sum3->setText(sett().numberToString(grossTotal, 'f', 2));
}


/** Number Counts
 *  Used while populating invoice symbol, fills zeros into invoice symbol
 */
QString Faktura::numbersCount(int in, int x) {
	QString tmp2, tmp = sett().numberToString(in);
	tmp2 = "";
	int incr = x - tmp.length();
	for (int i = 0; i < incr; ++i)
		tmp2 += "0";
	return tmp2 + tmp;
}

/** Saves width of the columns
 */
void Faktura::saveColumnsWidth() {
	sett().beginGroup("fakturaForm");
	for (int i = 0; i <= 10; ++i)
		sett().setValue("towCol" + sett().numberToString(i), tableTow->columnWidth(i));
	sett().endGroup();
}

/**
 *  Return invoice type
 */
QString Faktura::getInvoiceTypeAndSaveNr() {
	// qDebug() << __FUNCTION__ << __LINE__ << __FILE__;

	QString ret = "FVAT";

	if (windowTitle().right(3) == "VAT") {
		sett().setValue("fvat", frNr->text());
	} else {
		ret = "FPro";
		sett().setValue("fpro", frNr->text());
	}

	return ret;
}
