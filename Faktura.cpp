#include "Faktura.moc"
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
#include "MainWindow.h"
#include "slownie.h"
#include "Settings.h"


enum InvoiceType {FVat, FPro, EFVat, EFPro};
short invType;

/** Constructor
 */
Faktura::Faktura(QWidget *parent) :
	QDialog(parent) {
	setupUi(this);
	init();
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


	// Calulcate next number of the invoice
	QString tmp;
	if (windowTitle().right(3) == "VAT") {
		tmp = sett().value("fvat").toString();
		invoiceType = trUtf8("Faktura VAT");
	} else {
		tmp = sett().value("fpro").toString();
		invoiceType = trUtf8("Faktura Pro Forma");
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

	if (sett().value ("addText").toString().compare("") == 0 )
		additEdit->setText(sett().value("addText").toString());

	backBtnClick();

	// set window icon
	QIcon icon;
	icon.addPixmap(QPixmap(":/res/share/qfaktury/icons/nowa_faktura.png"),
			QIcon::Normal, QIcon::Off);
	this->setWindowIcon(icon);

	rmTowBtn->setEnabled(false);
	editTwBtn->setEnabled(false);
	liabDate->setEnabled(false);
	rabatValue->setEnabled(false);
	canClose = true;
}


// ---- SLOTS START  --//////////////////////////////////////////////////////////////////////////////////

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
}

/** Slot
 *  Used populate invoice symbol
 */
void Faktura::backBtnClick() {
	QString tmp;

	QString prefix, suffix;

	if (windowTitle().right(3) == "VAT") {
		tmp = sett().value("fvat").toString();
	} else {
		tmp = sett().value("fpro").toString();
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

	textChanged(text);
}

/** Slot textChanged
 *  Activates buttons
 */
void Faktura::textChanged(QString text) {
	saveBtn->setEnabled(true);
	canClose = false;
}

/** Slot dateChanged
 *  Activates buttons
 */
void Faktura::dateChanged(QDate text) {
	saveBtn->setEnabled(true);
	canClose = false;
}


/** Slot saveInvoice
 *  Generates Invoice XML
 */
void Faktura::saveInvoice() {
	if (!validateForm()) return;

	QDomDocument doc(sett().getInoiveDocName());
	QDomElement root;
	QString fileName = fName;

	QFile file;
	if (fileName == "") {
		fileName = QDate::currentDate().toString(sett().getFnameDateFormat());

		int pNumber = 0;
		file.setFileName(sett().getInvoicesDir() + "h" + fileName + "_"
				+ sett().numberToString(pNumber) + ".xml");
		ret = "h" + fileName + "_" + sett().numberToString(pNumber) + ".xml" + "|";
		pNumber += 1;

		while (file.exists()) {
			file.setFileName(sett().getInvoicesDir() + "h" + fileName + "_"
					+ sett().numberToString(pNumber) + ".xml");
			ret = "h" + fileName + "_" + sett().numberToString(pNumber) + ".xml"
					+ "|";
			pNumber += 1;
		}
	} else {
		file.setFileName(sett().getInvoicesDir() + fileName);
		ret = fileName + "|";
	}

	// if (!file.open (QIODevice::ReadOnly)) {

	root = doc.createElement("invoice");
	root.setAttribute("no", frNr->text());
	ret += frNr->text() + "|";
	root.setAttribute("issueDate", QDate::currentDate().toString(
			sett().getDateFormat()));
	ret += QDate::currentDate().toString(sett().getDateFormat()) + "|";
	root.setAttribute("sellingDate", sellingDate->date().toString(
			sett().getDateFormat()));

	if (windowTitle().right(3) == "VAT") {
		root.setAttribute("type", "FVAT");
		sett().setValue("fvat", frNr->text());
		ret += "FVAT|";
	} else {
		root.setAttribute("type", "FPro");
		sett().setValue("fpro", frNr->text());
		ret += "FPro|";
	}

	doc.appendChild(root);

	QDomElement sprzedawca = createSellerElement(doc);
	root.appendChild(sprzedawca);


	QDomElement nabywca = createBuyerElement(doc);
	root.appendChild(nabywca);

	QDomElement product;
	QDomElement products;
	products = doc.createElement("products");
	products.setAttribute("discount", sett().numberToString(rabatValue->value()));

	for (int i = 0; i < tableTow->rowCount(); ++i) {
		product = doc.createElement("product"); //  + tableTow->item(i, 0)->text());
		products.setAttribute("productsCount", sett().numberToString(i + 1));
		product.setAttribute("id", tableTow->item(i, 0)->text());
		product.setAttribute("name", tableTow->item(i, 1)->text());
		product.setAttribute("code", tableTow->item(i, 2)->text());
		product.setAttribute("PKWiU", tableTow->item(i, 3)->text()); // Polish Classification of STH
		product.setAttribute("quantity", tableTow->item(i, 4)->text());
		product.setAttribute("quantityType", tableTow->item(i, 5)->text());
		if (!constRab->isChecked()) {
			product.setAttribute("discount", tableTow->item(i, 6)->text());
		} else {
			product.setAttribute("discount",
					sett().numberToString(rabatValue->value())); // rabat
		}
		product.setAttribute("price", tableTow->item(i, 7)->text());
		double cenajdn = sett().stringToDouble(tableTow->item(i, 8)->text());
		double kwota = cenajdn
				* tableTow->item(i, 4)->text().toInt();

		product.setAttribute("nett", sett().numberToString(kwota, 'f', 2)); // netto
		// product.setAttribute ("Rabat", QLocale::toString (rabatValue->value ()));	// rabat
		product.setAttribute("discountedNett", tableTow->item(i, 7)->text());
		product.setAttribute("vatBucket", tableTow->item(i, 9)->text());
		double vatPrice = sett().stringToDouble(tableTow->item(i, 10)->text())
							- sett().stringToDouble(tableTow->item(i, 8)->text());

		product.setAttribute("vatAmout", sett().numberToString(vatPrice, 'f', 2));
		product.setAttribute("gross", tableTow->item(i, 10)->text());
		products.appendChild(product);

	}
	root.appendChild(products);


	QDomElement addinfo;
	addinfo = doc.createElement("addinfo");
	addinfo.setAttribute("text", additEdit->text());
	addinfo.setAttribute("paymentType", platCombo->currentText());
	addinfo.setAttribute("liabDate", liabDate->date().toString(
			sett().getDateFormat()));
	addinfo.setAttribute("currency", currCombo->currentText());
	root.appendChild(addinfo);

	QString xml = doc.toString();
	file.close();
	if (!file.open(QIODevice::WriteOnly)) {
		QMessageBox::critical(this, "QFaktury", trUtf8("Nie można zapisać. Sprawdź czy folder:\n") +
				sett().getInvoicesDir() + trUtf8("\nistnieje i czy masz do niego prawa zapisu."),
		QMessageBox::Ok);
		saveFailed = true;
		return;
	}
	QTextStream ts(&file);
	ts << xml;
	file.close();

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

	fraStrList.clear();
	makeInvoiceHeadar();
	makeInvoiceBody();
	makeInvoiceProducts();
	makeInvoiceSummAll();
	makeInvoiceFooter();

	//  QFile file ("/tmp/invoice.html");
	//  if (file.open (QIODevice::WriteOnly))
	//    {
	//      QTextStream stream (&file);
	//      for (QStringList::Iterator it = fraStrList.begin ();
	//	   it != fraStrList.end (); ++it)
	//	stream << *it << "\n";
	//      file.close ();
	//    }

}

/** Slot print
 *  Helper slot used to display print preview
 */
void Faktura::printSlot(QPrinter *printer) {
    QTextDocument doc(invoiceType);
    QString s;
    for (QStringList::iterator it = fraStrList.begin(); it != fraStrList.end(); ++it) {
        s+=*it+"\n";
    }
    // qDebug of the whole invoice :)
	// qDebug() << s;
    doc.setHtml(s);
    doc.print(printer);

}
// ---- SLOTS END --//////////////////////////////////////////////////////////////////////////////////


/** Saves width of the columns
 */
void Faktura::print() {
	//print invoice
	QPrinter printer(QPrinter::HighResolution);
	QPrintPreviewDialog preview(&printer, this);
	preview.setWindowFlags(Qt::Window);
	preview.setWindowTitle(invoiceType + trUtf8(" - Podgląd wydruku"));

	connect(&preview, SIGNAL(paintRequested(QPrinter *)), this, SLOT(printSlot(QPrinter *)));
	if (preview.exec() == 1) {
	}
}

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

/** Create seller (Dane firmy)
 */
QDomElement Faktura::createSellerElement(QDomDocument doc) {
	QDomElement sprzedawca = doc.createElement("seller");
	QSettings userSettings("elinux", "user");
	sprzedawca.setAttribute("name", userSettings.value("name").toString());
	sprzedawca.setAttribute("zip", userSettings.value("zip").toString());
	sprzedawca.setAttribute("city", userSettings.value("city").toString());
	sprzedawca.setAttribute("street", userSettings.value("street").toString());
	// NIP = Taxing Identification Code
	sprzedawca.setAttribute("tic", userSettings.value("tic").toString());
	sprzedawca.setAttribute("account",
			userSettings.value("account").toString(). replace(" ", "-"));
	return sprzedawca;
}

/** Create buyer (Dane firmy)
 */
QDomElement Faktura::createBuyerElement(QDomDocument doc) {
	QDomElement nabywca = doc.createElement("buyer");
	QStringList kht = kontrName->text().split(",");
	nabywca.setAttribute("name", kht[0]);
	ret += kht[0] + "|";
	nabywca.setAttribute("city", kht[1]);
	nabywca.setAttribute("street", kht[2]);
	nabywca.setAttribute("tic", kht[3].replace(" ", "").replace(trUtf8("NIP:"),	""));
	ret += kht[3].replace(" ", "").replace(trUtf8("NIP:"), "");
	return nabywca;
}
// ******************************** XML Helpers END **********************************************

// Generate Invoice HTML methods --- START ---

void Faktura::makeInvoiceHeadar() {

	fraStrList += "<html><head>";
	fraStrList
			+= "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />";
	fraStrList += "<meta name=\"creator\" value=\"http://www.e-linux.pl\" />";
	//fraStrList += "<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\" />";
	fraStrList += "</head>";

	if (windowTitle().right(3) == "VAT") {
		fraStrList += "<title>"+ invoiceType  +"</title>";
	} else {
		fraStrList += "<title>" + invoiceType + "</title>";
	}

	//  fraStrList += "<style type=\"text/css\"><!-- ";
	//  // qDebug( templDir  );
	//
	//  QFile file (templDir + "style.css");
	//  if (file.open (QIODevice::ReadOnly))
	//    {
	//      QTextStream stream (&file);
	//      QString line;
	//      while (!stream.atEnd ())
	//	{
	//	  line = stream.readLine ();
	//	  fraStrList += line;
	//	}
	//      file.close ();
	//    }
	//
	//  fraStrList += "--></style>";
	fraStrList += "<body>";
	fraStrList
			+= "<table border=\"`0\" cellspacing=\"0\" cellpadding=\"0\" style=\"font-family:'Arial'\">";
	fraStrList += "<tr comment=\"headar\"><td>";
	fraStrList
			+= "<table comment=\"headar table\" width=\"100%\" border=\"0\">";
	fraStrList += "<tr>";
	fraStrList
			+= "<td width=\"60%\" align=\"left\" valign=\"center\" class=\"podpisy\">";
	// logo code
	// eof logo

	QString logo = sett().value("logo").toString();
	if (logo != "") {
		fraStrList += "<img src=\"" + logo + "\">";
	} else {
		fraStrList += trUtf8("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Pieczęć wystawcy");
	}
	// in case where we don't have a logo :(

	fraStrList += "</td>";
	fraStrList += "<td align=\"right\">";

	fraStrList += "<span style=\"font-size:12pt; font-weight:600\">";

	fraStrList += invoiceType;
	fraStrList += "<br/>";

	fraStrList += trUtf8("Nr: ") + frNr->text() + "<br></span>";
	fraStrList
			+= "<span style=\"font-size:8pt; font-weight:600\">" + trUtf8("Data wystawienia: ")
					+ productDate->date().toString(sett().getDateFormat()) + "<br>";
	fraStrList += trUtf8("Data sprzedaży: ") + sellingDate->date().toString(sett().getDateFormat())
			+ "<br></span>";
	fraStrList += "</td>";
	fraStrList += "<td width=\"3%\">&nbsp;</td>";
	fraStrList += "</tr>";
	fraStrList += "<tr>";
	fraStrList += "<td colspan=\"3\" align=\"right\" valign=\"top\"><br>";
	fraStrList += trUtf8("ORYGINAŁ/KOPIA");
	fraStrList += "<br></td>";
	fraStrList += "<td width=\"3%\">&nbsp;</td>";
	fraStrList += "</tr>";
	fraStrList += "</table>";
	fraStrList += "</td></tr>";
}


void Faktura::makeInvoiceBody() {
	fraStrList += "<tr><td>";
	fraStrList += "<table width=\"100%\" border=\"0\">";
	fraStrList += "<tr>";
	fraStrList += "<td width=\"20\">&nbsp;</td>";
	fraStrList += "<td width=\"48%\"> ";
	fraStrList
			+= "<span style=\"font-size:10pt; font-weight:600;\">"+trUtf8("Sprzedawca:")+"</span><br/>";
	QSettings userSettings("elinux", "user");
	fraStrList += "<span style=\"font-size:8pt; font-weight:600;\">";

	sett().beginGroup("printpos");
	if (sett().value("usernazwa").toBool())
		fraStrList += userSettings.value("name").toString() + "<br>";
	if (sett().value("usermiejscowosc").toBool())
		fraStrList += userSettings.value("zip").toString() + " ";
	if (sett().value("usermiejscowosc").toBool())
		fraStrList += userSettings.value("city").toString() + "<br>";
	if (sett().value("useradres").toBool())
		fraStrList += trUtf8("Ul. ") + userSettings.value("address").toString() + "<br>";
	if (sett().value("usernip").toBool())
		fraStrList += trUtf8("NIP: ") + userSettings.value("tic").toString() + "<br>";
	if (sett().value("userkonto").toBool())
		fraStrList += trUtf8("Nr konta: ")
				+ userSettings.value("account").toString().replace("-", " ")
				+ "<br>";
	sett().endGroup();

	fraStrList += "</span>";
	fraStrList += "</td>";
	fraStrList += "<td width=\"20\">&nbsp;</td>";
	fraStrList += "<td width=\"48%\"><span style=\"font-size:10pt; font-weight:600;\">";
	fraStrList += trUtf8("Nabywca:");
	fraStrList += "</span><br/><span style=\"font-size:8pt; font-weight:600;\">"
			+ kontrName->text().replace(",", "<br>") + "<br>";
	fraStrList += "</span>";
	fraStrList += "</td>";
	fraStrList += "</tr>";
	fraStrList += "</table>";
	fraStrList += "</td></tr>";
}

void Faktura::makeInvoiceProducts() {
	fraStrList += "<tr align=\"center\"><td>";
	fraStrList += "<br><br>";
	fraStrList
			+= "<table border=\"1\" width=\"100%\" cellspacing=\"0\" style=\"font-size:8pt; font-weight:400;\">";
	fraStrList += "<tr>";

	int currentPercent = 0;
	if (sett().value("faktury_pozycje/Lp").toBool()) {
		currentPercent = 3;
		fraStrList += "<td width=\""+ sett().numberToString(currentPercent) + "%\"  align=\"center\">" + trUtf8("Lp.") + "</td>";
		currentPercent = 0;
	} else {
		currentPercent += 3;
	}
	if (sett().value("faktury_pozycje/Nazwa").toBool()) {
		currentPercent += 25;
		fraStrList += "<td width=\""+ sett().numberToString(currentPercent) + "%\" align=\"center\">" + trUtf8("Nazwa") + "</td>";
		currentPercent = 0;
	} else {
		currentPercent += 25;
	}
	if (sett().value("faktury_pozycje/Kod").toBool()) {
		currentPercent += 7;
		fraStrList += "<td width=\""+ sett().numberToString(currentPercent) + "%\" align=\"center\">" + trUtf8("Kod") + "</td>";
		currentPercent = 0;
	} else {
		currentPercent += 7;
	}
	if (sett().value("faktury_pozycje/pkwiu").toBool()) {
		currentPercent += 7;
		fraStrList += "<td width=\""+ sett().numberToString(currentPercent) + "%\" align=\"center\">" + trUtf8("PKWiU") + "</td>";
		currentPercent = 0;
	} else {
		currentPercent += 7;
	}
	if (sett().value("faktury_pozycje/ilosc").toBool()) {
		// currentPercent += 7;
		fraStrList += "<td width=\""+ sett().numberToString(7) + "%\" align=\"center\">" + trUtf8("Ilość") + "</td>";
		// currentPercent = 0;
	} else {
		currentPercent += 7;
	}
	if (sett().value("faktury_pozycje/jm").toBool()) {
		// currentPercent += 3;
		fraStrList += "<td width=\""+ sett().numberToString(3) + "%\" align=\"center\">" + trUtf8("jm.") + "</td>";
		// currentPercent = 0;
	} else {
		currentPercent += 3;
	}
	if (sett().value("faktury_pozycje/cenajedn").toBool()) {
		currentPercent += 7;
		fraStrList += "<td width=\""+ sett().numberToString(currentPercent) + "%\" align=\"center\">" + trUtf8("Cena jdn.") + "</td>";
		currentPercent = 0;
	} else {
		currentPercent += 7;
	}
	if (sett().value("faktury_pozycje/wartnetto").toBool()) {
		currentPercent += 7;
		fraStrList += "<td width=\""+ sett().numberToString(currentPercent) + "%\" align=\"center\">" + trUtf8("Wartość Netto") + "</td>";
		currentPercent = 0;
	} else {
		currentPercent += 7;
	}
	if (sett().value("faktury_pozycje/rabatperc").toBool()) {
		// currentPercent += 3;
		fraStrList += "<td width=\""+ sett().numberToString(3) + "%\" align=\"center\">" + trUtf8("Rabat %") + "</td>";
		// currentPercent = 0;
	} else {
		currentPercent += 3;
	}
	if (sett().value("faktury_pozycje/rabatval").toBool()) {
		currentPercent += 3;
		fraStrList += "<td width=\""+ sett().numberToString(currentPercent) + "%\" align=\"center\">" + trUtf8("Rabat Wartość") + "</td>";
		currentPercent = 0;
	} else {
		currentPercent += 3;
	}
	if (sett().value("faktury_pozycje/nettoafter").toBool()) {
		currentPercent += 7;
		fraStrList += "<td width=\""+ sett().numberToString(currentPercent) + "%\" align=\"center\">" + trUtf8("Netto po rabacie") + "</td>";
		currentPercent = 0;
	} else {
		currentPercent += 7;
	}
	if (sett().value("faktury_pozycje/vatval").toBool()) {
		// currentPercent += 7;
		fraStrList += "<td width=\""+ sett().numberToString(7) + "%\" align=\"center\">" + trUtf8("Stawka VAT") + "</td>";
		// currentPercent = 0;
	} else {
		currentPercent += 7;
	}
	if (sett().value("faktury_pozycje/vatprice").toBool()) {
		currentPercent += 7;
		fraStrList += "<td width=\""+ sett().numberToString(currentPercent) + "%\" align=\"center\">" + trUtf8("Kwota Vat") + "</td>";
		currentPercent = 0;
	} else {
		currentPercent += 7;
	}
	if (sett().value("faktury_pozycje/bruttoval").toBool()) {
		currentPercent += 7;
		fraStrList += "<td width=\""+ sett().numberToString(currentPercent) + "%\" align=\"center\">" + trUtf8("Wartość Brutto") + "</td>";
		currentPercent = 0;
	} else {
		currentPercent += 7;
	}
	fraStrList += "</tr>";

	for (int i = 0; i < tableTow->rowCount(); ++i) {
		// for (int j=1; j<11;++j)
		// 	qDebug() << j << " : " << tableTow->item(i, j)->text();

		fraStrList += "<tr>";
		// lp, nazwa, kod, pkwiu, ilosc, jm, rabat, cena jm., netto, vat, brutto
		if (sett().value("faktury_pozycje/Lp").toBool())
			fraStrList += "<td align=\"center\">&nbsp;" + sett().numberToString(i + 1) + "</td>";
		if (sett().value("faktury_pozycje/Nazwa") .toBool())
			fraStrList += "<td align=\"center\">&nbsp;" + tableTow->item(i, 1)->text() + "</td>";
		if (sett().value("faktury_pozycje/Kod") .toBool())
			fraStrList += "<td align=\"center\">&nbsp;" + tableTow->item(i, 2)->text() + "</td>";
		if (sett().value("faktury_pozycje/pkwiu") .toBool())
			fraStrList += "<td align=\"center\">&nbsp;" + tableTow->item(i, 3)->text() + "</td>";
		if (sett().value("faktury_pozycje/ilosc") .toBool())
			fraStrList += "<td align=\"center\">&nbsp;" + tableTow->item(i, 4)->text() + "</td>";
		if (sett().value("faktury_pozycje/jm") .toBool())
			fraStrList += "<td align=\"center\">&nbsp;" + tableTow->item(i, 5)->text() + "</td>";
		if (sett().value("faktury_pozycje/cenajedn") .toBool())
			fraStrList += "<td align=\"center\">&nbsp;" + tableTow->item(i, 7)->text() + "</td>";
		double discountVal = sett().stringToDouble(tableTow->item(i, 8)->text()) *
								(tableTow->item(i, 6)->text().toDouble() * 0.01);
		double nettMinusDisc = sett().stringToDouble(tableTow->item(i, 8)->text()) - discountVal;
		if (sett().value("faktury_pozycje/wartnetto") .toBool())
			fraStrList += "<td align=\"center\">&nbsp;" + tableTow->item(i, 8)->text()
					+ "</td>"; // netto
		if (sett().value("faktury_pozycje/rabatperc") .toBool())
			fraStrList += "<td align=\"center\">&nbsp;" + tableTow->item(i, 6)->text()
					+ "% </td>"; // rabat
		if (sett().value("faktury_pozycje/rabatval") .toBool())
			fraStrList += "<td align=\"center\">&nbsp;" + sett().numberToString(discountVal, 'f',  2)	+ " </td>";
		if (sett().value("faktury_pozycje/nettoafter") .toBool())
			fraStrList += "<td align=\"center\">&nbsp;" + sett().numberToString(nettMinusDisc, 'f', 2) + "</td>";
		if (sett().value("faktury_pozycje/vatval") .toBool())
			fraStrList += "<td align=\"center\">&nbsp;" + tableTow->item(i, 9)->text()
					+ "%</td>";
		double vatPrice = sett().stringToDouble(tableTow->item(i, 10)->text())
								- sett().stringToDouble(tableTow->item(i, 8)->text()); // brutt-nett :)
		if (sett().value("faktury_pozycje/vatprice") .toBool())
			fraStrList += "<td align=\"center\">&nbsp;" + sett().numberToString(vatPrice, 'f', 2)
					+ "</td>";
		if (sett().value("faktury_pozycje/bruttoval") .toBool())
			fraStrList += "<td align=\"center\">&nbsp;" + tableTow->item(i, 10)->text() + "</td>";
		fraStrList += "</tr>";
	}

	fraStrList += "</table>";
	makeInvoiceSumm();
	fraStrList += "<br/></td></tr>";
}

void Faktura::makeInvoiceSumm() {
	fraStrList
			+= "</br><table border=\"0\" cellspacing=\"0\" style=\"font-size:8pt; font-weight:400;\">";
	fraStrList += "<tr>";
	double vatPrice = sett().stringToDouble(sum3->text()) - sett().stringToDouble(sum1->text());
	fraStrList += "<tr>";
	fraStrList
			+= "<td colspan=\"10\" width=\"420\" align=\"right\">&nbsp;</td>";
	fraStrList += "<td width=\"30\" align=\"center\">&nbsp;" + trUtf8("Wartość Netto") + "</td>"; // netto
	// fraStrList += "<td width=\"30\" >&nbsp;</td>";
	fraStrList += "<td width=\"30\" align=\"center\">&nbsp;" + trUtf8("Kwota VAT") + "</td>";// vat
	fraStrList += "<td width=\"30\" align=\"center\">&nbsp;" + trUtf8("Wartość Brutto") + "</td>"; // brutto
	fraStrList += "</tr>";
	fraStrList += "<tr><td colspan=\"10\" width=\"420\" align=\"right\">";
	fraStrList += "Razem:&nbsp;</td>";
	fraStrList += "<td align=\"center\">&nbsp;" + sum1->text(); // netto
	// fraStrList += "<td>&nbsp;</td>";
	fraStrList += "</td><td align=\"center\">&nbsp;" + sett().numberToString(vatPrice, 'f', 2) + "</td>";// vat
	fraStrList += "<td align=\"center\">&nbsp;" + sum3->text() + "</td>"; // brutto
	fraStrList += "</tr>";
	fraStrList += "</table>";
}

void Faktura::makeInvoiceSummAll() {
	fraStrList += "<tr comment=\"podsumowanie\"><td>";
	fraStrList += "<table width=\"100%\" border=\"0\">";
	fraStrList += "<tr>";
	fraStrList += "<td width=\"3%\">&nbsp;</td>";
	fraStrList += "<td width=\"48%\"><h4>";
	fraStrList += trUtf8("Do zapłaty: ") + sum3->text() + " "
			+ currCombo->currentText() + "</h4><span style=\"font-size:8pt; font-weight:600;\">";
	fraStrList += trUtf8("słownie:")
			+ slownie(sum3->text(), currCombo->currentText())
			+ "</span><br/><span style=\"font-size:8pt; font-weight:600;\">";
	fraStrList += trUtf8("forma płatności: ") + platCombo->currentText() + "<br/>";
	QString paym1 = sett().value("paym1").toString();
	if (platCombo->currentIndex() == 0) {
		fraStrList += "<b>" + trUtf8("Zapłacono gotówką");
	} else {
		fraStrList += trUtf8("termin płatności: ") + liabDate->date().toString(sett().getDateFormat())
				+ "<br/>";
	}
	fraStrList += "</b> <br/></span><br/>";
	fraStrList += "<span style=\"font-size:10pt; font-weight:600;\">"
			+ additEdit->text() + "</span>";
	fraStrList += "</td>";
	fraStrList += "<td width=\"3%\">&nbsp;</td>";
	fraStrList += "<td width=\"48%\" valign=\"top\">";
	fraStrList += "<table width=\"90%\" border=\"0\">";
	fraStrList += "<tr><td colspan=\"4\"><span style=\"font-size:8pt; font-weight:600;\">";
	fraStrList += trUtf8("Ogółem stawkami:");
	fraStrList += "</span></td>"; // Ogółem stawkami:
	fraStrList += "</tr>";
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
	fraStrList += "<tr class=\"podpisy\">";
	fraStrList += "<td width=\"3%\">&nbsp;</td>";
	fraStrList += "<td width=\"43%\" align=\"center\"><span style=\"font-size:8pt; font-weight:600;\"> ";
	fraStrList += trUtf8("Imię i nazwisko osoby upoważnionej do wystawienia faktury VAT");
	fraStrList += "</span></td>";
	fraStrList += "<td width=\"7%\">&nbsp;</td>";
	fraStrList += "<td width=\"3%\">&nbsp;</td>";
	fraStrList += "<td width=\"43%\" align=\"center\"><span style=\"font-size:8pt; font-weight:600;\">";
	fraStrList += trUtf8("Imię i nazwisko osoby upoważnionej do odbioru faktury VAT");
	fraStrList += "</span></td>";
	fraStrList += "</tr>";
	fraStrList += "</table>";
	fraStrList += "</td></tr>";
	fraStrList += "</table>";
	fraStrList += "<tr comment=\"comment\" align=\"left\"><td>";
	fraStrList += "</td></tr>";
	fraStrList += "</table>";
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
		out += "<tr>";
		out += "<td>" + sett().numberToString(stawkiNetto[y], 'f', 2) + "</td>"; // netto
		out += "<td>" + stawki[y] + "</td>"; // stawka
		out += "<td>" + sett().numberToString(stawkiVat[y], 'f', 2) + "</td>"; // podatek
		out += "<td>" + sett().numberToString(stawkiBrutto[y], 'f', 2) + "</td>"; // brutto
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
		setWindowTitle(trUtf8("Edytuje Fakturę VAT"));
	} else {
		setWindowTitle(trUtf8("Edytuje Fakturę Pro Forma"));
	}

	QDomDocument doc(sett().getInoiveDocName());
	QDomElement root;
	QDomElement nabywca;
	QDomElement product;
	fName = fraFile;

	QFile file(sett().getInvoicesDir() + fraFile);
	if (!file.open(QIODevice::ReadOnly)) {
		qDebug("file doesn't exist");
		return;
	} else {
		QTextStream stream(&file);
		if (!doc.setContent(stream.readAll())) {
			file.close();
			return;
		}
	}

	root = doc.documentElement();
	frNr->setText(root.attribute("no"));
	sellingDate->setDate(QDate::fromString(root.attribute("sellingDate"), sett().getDateFormat()));
	productDate->setDate(QDate::fromString(root.attribute("issueDate"),	sett().getDateFormat()));

	QDomNode tmp;
	tmp = root.firstChild();
	tmp = tmp.toElement().nextSibling(); // nabywca
	nabywca = tmp.toElement();
	kontrName->setText(nabywca.attribute("name") + "," + nabywca.attribute(
			"city") + "," + nabywca.attribute("street") + ","
			+ nabywca.attribute("tic"));
			/* not required
			+ ", " + nabywca.attribute("account")
			+ ", " + nabywca.attribute("phone") + ", " + nabywca.attribute(
			"email") + ", " + nabywca.attribute("www")) */
	kontrName->setCursorPosition(1);

	tmp = tmp.toElement().nextSibling(); // product
	product = tmp.toElement();

	rabatValue->setValue(product.attribute("discount").toInt());

	int towCount = product.attribute("productsCount").toInt();
	int i = 0;
	QDomElement towar;
	towar = product.firstChild().toElement();

	static const char *towarColumns[] = { "", "name", "code", "PKWiU",
			"quantity", "quantityType", "discount", "price", "nett",
			"vatBucket", "gross" };

	tableTow->setRowCount(towCount);
	for (i = 0; i < towCount; ++i) {
		for (int j = 0; j < int(sizeof(towarColumns) / sizeof(*towarColumns)); j++) {
			tableTow->setItem(i, j, new QTableWidgetItem(towar.attribute(
					towarColumns[j])));
			// qDebug() << towarColumns[j] << towar.attribute(towarColumns[j]);
		}
		towar = towar.nextSibling().toElement();
	}

	tmp = tmp.toElement().nextSibling();
	QDomElement additional = tmp.toElement();
	additEdit->setText(additional.attribute("text"));
	int curPayment = sett().value("payments").toString().split("|").indexOf(additional.attribute("paymentType"));
	platCombo->setCurrentIndex(curPayment);
	liabDate-> setDate(QDate::fromString(additional.attribute("liabDate"), sett().getDateFormat()));
	int curCurrency = sett().value("waluty").toString().split("|").indexOf(additional.attribute("currency"));
	currCombo->setCurrentIndex(curCurrency);

	setIsEditAllowed(sett().value("edit").toBool());
	calculateDiscount();
	calculateSum();
	canClose = true;
	saveBtn->setEnabled(false);
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
	liabDate->setEnabled(isAllowed);
	if (!isAllowed && rabatValue->value() == 0) {
		constRab->setChecked(false);
		rabatValue->setEnabled(false);
	} else {
		constRab->setChecked(true);
		rabatValue->setEnabled(true);
	}
	if (!isAllowed && platCombo->currentIndex() > 0) {
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
	double netto = 0, price = 0, quantity = 0, gross = 00;
	double discountValue = 0, discountTotal = 0, nettTotal = 0, grossTotal = 0;

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

