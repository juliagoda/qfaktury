#include "Faktura.moc"
#include <QDateTime>
#include <QDir>
#include <QProcess>
#include <QApplication>
#include <Qt/qdom.h>
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

#include "Rounding.h"
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

	// set width of the columns on the goods list
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
	connect(rabatValue, SIGNAL(valueChanged(int)), this, SLOT(discountChange()));
	connect(rmTowBtn, SIGNAL(clicked()), this, SLOT(delTowar()));
	connect(tableTow, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(editTowar()));
	connect(editTwBtn, SIGNAL(clicked()), this, SLOT(editTowar()));
	connect(backBtn, SIGNAL(clicked()), this, SLOT(backBtnClick()));

	connect(closeBtn, SIGNAL(clicked()), this, SLOT(canQuit()));
    connect(saveBtn, SIGNAL(clicked()), this, SLOT(saveInvoice()));
    connect(printBtn, SIGNAL(clicked()), this, SLOT(makeInvoice()));
    connect(tableTow, SIGNAL(itemActivated ( QTableWidgetItem * )), this,
				SLOT(tableActivated ( QTableWidgetItem * )));

    connect(additEdit, SIGNAL(textChanged(QString)), this, SLOT(textChanged(QString)));
    connect(printBtn, SIGNAL(clicked()), this, SLOT(makeInvoice()));

    connect(platCombo, SIGNAL(editTextChanged(QString)), this, SLOT(textChanged(QString)));
    connect(currCombo, SIGNAL(editTextChanged(QString)), this, SLOT(textChanged(QString)));

    connect(sellingDate, SIGNAL(dateChanged (QDate)), this, SLOT(dateChanged (QDate)));
    connect(productDate, SIGNAL(dateChanged (QDate)), this, SLOT(dateChanged (QDate)));
    connect(liabDate, SIGNAL(dateChanged (QDate)), this, SLOT(dateChanged (QDate)));

	// Calulcate next number of the invoice
	QString tmp;
	if (windowTitle().right(3) == "VAT") {
		tmp = sett().value("fvat").toString();
		invoiceType = UTF8("Faktura VAT");
	} else {
		tmp = sett().value("fpro").toString();
		invoiceType = UTF8("Faktura Pro Forma");
	}

	QStringList one1 = tmp.split("/");
	int nr = one1[0].toInt() + 1;
	lastInvoice = QString::number(nr) + "/" + QDate::currentDate().toString(
			"MM/yyyy");
	frNr->setText(lastInvoice);

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
	canClose = true;
}


// ---- SLOTS START  --//////////////////////////////////////////////////////////////////////////////////

/** Slot getCustomer
 *  Opens window with the list of the customers
 */
void Faktura::getCustomer ()
{
  KontrahenciLista *klWindow = new KontrahenciLista(this);
  if (klWindow->exec () == QDialog::Accepted)
    {
      kontrName->setText (klWindow->ret);
      kontrName->setCursorPosition (1);
      saveBtn->setEnabled(true);
      canClose = false;
    }
}

/** Slot discountChange
 *  Used to recalculate discount when spinBox arrows are pressed.
 */
void Faktura::discountChange() {
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
		QStringList row = twWindow->ret.split("|");

		int rowNum = tableTow->rowCount() - 1;
		tableTow->item(rowNum, 0)->setText(QString::number(
				tableTow->rowCount())); // id
		tableTow->item(rowNum, 1)->setText(row[0]); // name
		tableTow->item(rowNum, 2)->setText(row[1]); // code
		tableTow->item(rowNum, 3)->setText(row[2]); // pkwiu

		QStringList quan = row[3].split(",");
		QString quantity = row[3];
		if (quan[1].compare("") == 0) {
			quantity = quan[0];
		}
		tableTow->item(rowNum, 4)->setText(quantity); // quantity
		tableTow->item(rowNum, 5)->setText(row[4]); // qType
		tableTow->item(rowNum, 6)->setText(row[5]); // discount
		tableTow->item(rowNum, 7)->setText(row[6]); // price
		tableTow->item(rowNum, 8)->setText(row[7]); // nett
		tableTow->item(rowNum, 9)->setText(row[8]); // vat
		tableTow->item(rowNum, 10)->setText(row[9]); // gross
		saveBtn->setEnabled(true);
		canClose = false;
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
		tableTow->item(i, 0)->setText(QString::number(i + 1));
	}
	calculateDiscount();
	calculateSum();
	saveBtn->setEnabled(true);
	canClose = false;
}

/** Slot editTowar
 *  Allows to edit selected product. Opens changeAmount window.
 *  @TODO
 *  if nothing is selected button should be disabled
 */
void Faktura::editTowar() {
	// we can only modify amount
	ZmienIlosc *changeAmount = new ZmienIlosc(this);
	changeAmount->nameTow->setText(
			tableTow-> item(tableTow->currentRow(), 1)->text());
	changeAmount->codeTow->setText(
			tableTow-> item(tableTow->currentRow(), 2)->text());
	changeAmount->spinAmount->setValue(tableTow-> item(tableTow->currentRow(),
			4)->text().toInt());
	if (changeAmount->exec() == QDialog::Accepted) {
		tableTow->item(tableTow->currentRow(), 4)->setText(QString::number(
				changeAmount->spinAmount-> value()));
		saveBtn->setEnabled(true);
		canClose = false;
		calculateDiscount();
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

	if (sett().value/*bool*/("day") .toBool())
		lastInvoice += "/" + QDate::currentDate().toString("dd");

	if (sett().value/*bool*/("month") .toBool())
		lastInvoice += "/" + QDate::currentDate().toString("MM");

	if (sett().value/*bool*/("year") .toBool()) {
		if (!sett().value/*bool*/("shortYear") .toBool())
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
	if (canClose || QMessageBox::warning(this, "QFaktury", UTF8("Dane zostały zmienione czy chcesz zapisać?"), "Tak", "Nie", 0, 0,
			1) == 0) {
		saveColumnsWidth();
		accept();
	} else {
		saveInvoice();
		if (saveFailed)
			this->close();
		saveColumnsWidth();
		return;
	}
}

/** Slot tableActivated
 *  Enable/Disable buttons
 */
void Faktura::tableActivated(QTableWidgetItem * item) {
	if (item != NULL) {
		rmTowBtn->setEnabled(true);
		editTwBtn->setEnabled(true);
	}
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
	if (kontrName->text() == "") {
		QMessageBox::critical(this, "QFaktury", UTF8("Nie ma kontrahenta."),
		QMessageBox::Ok);
		saveFailed = true;
		return;
	}

	if (tableTow->rowCount() == 0) {
		QMessageBox::critical(this, "QFaktury", UTF8("Nie ma towarów."),
		QMessageBox::Ok);
		saveFailed = true;
		return;
	}

	QDomDocument doc("faktury");
	QDomElement root;
	QString fileName = fName;

	QFile file;
	if (fileName == "") {
		fileName = QDate::currentDate().toString(sett().getFnameDateFormat());

		int pNumber = 0;
		file.setFileName(sett().getInvoicesDir() + "h" + fileName + "_"
				+ QString::number(pNumber) + ".xml");
		ret = "h" + fileName + "_" + QString::number(pNumber) + ".xml" + "|";
		pNumber += 1;

		while (file.exists()) {
			file.setFileName(sett().getInvoicesDir() + "h" + fileName + "_"
					+ QString::number(pNumber) + ".xml");
			ret = "h" + fileName + "_" + QString::number(pNumber) + ".xml"
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

	QDomElement sprzedawca;
	sprzedawca = doc.createElement("seller");
	QSettings userSettings("elinux", "user");
	sprzedawca.setAttribute("name", userSettings.value("name").toString());
	sprzedawca.setAttribute("zip", userSettings.value("zip").toString());
	sprzedawca.setAttribute("city", userSettings.value("city").toString());
	sprzedawca.setAttribute("street", userSettings.value("street").toString());
	// NIP = Taxing Identification Code
	sprzedawca.setAttribute("tic", userSettings.value("tic").toString());
	sprzedawca.setAttribute("account",
			userSettings.value("account").toString(). replace(" ", "-"));
	root.appendChild(sprzedawca);


	QDomElement nabywca;
	nabywca = doc.createElement("buyer");
	QStringList kht = kontrName->text().split(",");

	nabywca.setAttribute("name", kht[0]);
	ret += kht[0] + "|";
	nabywca.setAttribute("city", kht[1]);
	nabywca.setAttribute("street", kht[2]);

	nabywca.setAttribute("tic", kht[3].replace(" ", "").replace("NIP:", ""));
	ret += kht[3].replace(" ", "").replace("NIP:", "");
	root.appendChild(nabywca);

	QDomElement towary;
	QDomElement goods;
	goods = doc.createElement("products");
	goods.setAttribute("discount", QString::number(rabatValue->value()));

	for (int i = 0; i < tableTow->rowCount(); ++i) {
		towary = doc.createElement("product"); //  + tableTow->item(i, 0)->text());
		goods.setAttribute("productsCount", QString::number(i + 1));
		towary.setAttribute("id", tableTow->item(i, 0)->text());
		towary.setAttribute("name", tableTow->item(i, 1)->text());
		towary.setAttribute("code", tableTow->item(i, 2)->text());
		towary.setAttribute("PKWiU", tableTow->item(i, 3)->text()); // Polish Classification of STH
		towary.setAttribute("quantity", tableTow->item(i, 4)->text());
		towary.setAttribute("quantityType", tableTow->item(i, 5)->text());
		if (!constRab->isChecked()) {
			towary.setAttribute("discount", tableTow->item(i, 6)->text());
		} else {
			towary.setAttribute("discount",
					QString::number(rabatValue->value())); // rabat
		}
		towary.setAttribute("price", tableTow->item(i, 7)->text());
		double cenajdn =
				tableTow->item(i, 8)->text().replace(",", ".").toDouble();
		double kwota = cenajdn
				* tableTow->item(i, 4)->text().replace(",", ".").toInt();

		towary.setAttribute("nett", fixStr(QString::number(kwota))); // netto

		// towary.setAttribute ("Rabat", QString::number (rabatValue->value ()));	// rabat
		towary.setAttribute("discountedNett", tableTow->item(i, 7)->text());
		towary.setAttribute("vatBucket", tableTow->item(i, 9)->text());
		double
				vatPrice =
						tableTow->item(i, 10)->text().replace(",", ".").toDouble()
								- tableTow->item(i, 8)->text().replace(",", ".").toDouble();

		towary.setAttribute("vatAmout", fixStr(QString::number(vatPrice)));
		towary.setAttribute("gross", tableTow->item(i, 10)->text());
		goods.appendChild(towary);

	}
	root.appendChild(goods);


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
	file.open(QIODevice::WriteOnly);
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
		QMessageBox::information(this, "QFaktury", UTF8("Wybierz kontrahenta"),
				QMessageBox::Ok);
		return;
	}

	if (tableTow->rowCount() == 0) {
		QMessageBox::information(this, "QFaktury", UTF8("Nie ma towarów"),
		QMessageBox::Ok);
		return;
	}

	fraStrList.clear();

	makeInvoiceHeadar();
	makeInvoiceBody();
	makeInvoiceProducts();
	makeInvoiceSummAll();
	makeInvoiceFooter();

	//print invoice
	QPrinter printer(QPrinter::HighResolution);
	QPrintPreviewDialog preview(&printer, this);
	// preview.setWindowFlags(Qt::Window);
	preview.setWindowTitle(invoiceType);
	connect(&preview, SIGNAL(paintRequested(QPrinter *)), this, SLOT(print(QPrinter *)));
	preview.exec();

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
void Faktura::print(QPrinter *printer) {
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
			+= "<table border=\"0\" cellspacing=\"0\" cellpadding=\"0\" style=\"font-family:'Arial'\">";
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
		fraStrList += UTF8("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Pieczęć wystawcy");
	}
	// in case where we don't have a logo :(

	fraStrList += "</td>";
	fraStrList += "<td align=\"right\">";

	fraStrList += "<span style=\"font-size:12pt; font-weight:600\">";

	fraStrList += invoiceType;
	fraStrList += "<br/>";

	fraStrList += "NR: " + frNr->text() + "<br></span>";
	fraStrList
			+= "<span style=\"font-size:8pt; font-weight:600\">Data wystawienia: "
					+ QDate::currentDate().toString("yyyy-MM-dd") + "<br>";
	fraStrList += UTF8("Data sprzedaży: ") + sellingDate->date().toString("yyyy-MM-dd")
			+ "<br></span>";
	fraStrList += "</td>";
	fraStrList += "<td width=\"3%\">&nbsp;</td>";
	fraStrList += "</tr>";
	fraStrList += "<tr>";
	fraStrList += "<td colspan=\"3\" align=\"right\" valign=\"top\">";
	fraStrList += UTF8("<br>ORYGINAŁ/KOPIA<br>");
	fraStrList += "</td>";
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
			+= "<span style=\"font-size:10pt; font-weight:600;\">Sprzedawca:</span><br/>";
	QSettings userSettings("elinux", "user");
	fraStrList += "<span style=\"font-size:8pt; font-weight:600;\">"
			+ userSettings.value("name").toString() + "<br>";
	fraStrList += userSettings.value("zip").toString() + " " + userSettings.value(
			"city").toString() + "<br>";
	fraStrList += "ul. " + userSettings.value("address").toString() + "<br>";
	fraStrList += "NIP: " + userSettings.value("tic").toString() + "<br>";
	fraStrList += "Nr konta: " + userSettings.value("account").toString().replace(
			"-", " ") + "<br>";
	fraStrList += "</span>";
	fraStrList += "</td>";
	fraStrList += "<td width=\"20\">&nbsp;</td>";
	fraStrList += "<td width=\"48%\">";
	fraStrList
			+= "<span style=\"font-size:10pt; font-weight:600;\">Nabywca:</span><br/>";
	fraStrList += "<span style=\"font-size:8pt; font-weight:600;\">"
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
			+= "<table border=\"1\" cellspacing=\"0\" style=\"font-size:8pt; font-weight:400;\">";
	fraStrList += "<tr>";

	if (sett().value("faktury_pozycje/Lp").toBool())
		fraStrList += "<td width=\"3%\"  align=\"center\">Lp.</td>";
	if (sett().value("faktury_pozycje/Nazwa").toBool())
		fraStrList += "<td width=\"25%\" align=\"center\">Nazwa</td>";
	if (sett().value("faktury_pozycje/Kod").toBool())
		fraStrList += "<td width=\"7%\" align=\"center\">Kod</td>";
	if (sett().value("faktury_pozycje/pkwiu").toBool())
		fraStrList += "<td width=\"7%\" align=\"center\">PKWiU</td>";
	if (sett().value("faktury_pozycje/ilosc").toBool())
		fraStrList += UTF8("<td width=\"7%\" align=\"center\">Ilość</td>");
	if (sett().value("faktury_pozycje/jm").toBool())
		fraStrList += "<td width=\"3%\" align=\"center\">Jm.</td>";
	if (sett().value("faktury_pozycje/cenajedn").toBool())
		fraStrList += "<td width=\"7%\" align=\"center\">Cena jdn.</td>";
	if (sett().value("faktury_pozycje/wartnetto").toBool())
		fraStrList += UTF8("<td width=\"7%\" align=\"center\">Wartość Netto</td>");
	if (sett().value("faktury_pozycje/rabatperc").toBool())
		fraStrList += "<td width=\"3%\" align=\"center\">Rabat %</td>";
	if (sett().value("faktury_pozycje/rabatval").toBool())
		fraStrList += UTF8("<td width=\"3%\" align=\"center\">Rabat Wartość</td>");
	if (sett().value("faktury_pozycje/nettoafter").toBool())
		fraStrList += "<td width=\"7%\" align=\"center\">Netto po rabacie</td>";
	if (sett().value("faktury_pozycje/vatval").toBool())
		fraStrList += "<td width=\"7%\" align=\"center\">Stawka VAT</td>";
	if (sett().value("faktury_pozycje/vatprice").toBool())
		fraStrList += "<td width=\"7%\" align=\"center\">Kwota Vat</td>";
	if (sett().value("faktury_pozycje/bruttoval").toBool())
		fraStrList += UTF8("<td width=\"7%\" align=\"center\">Wartość Brutto</td>");
	fraStrList += "</tr>";

	for (int i = 0; i < tableTow->rowCount(); ++i) {
		// double vatPrice = tableTow->text(i, 9).replace(",", ".").toDouble() - tableTow->text(i, 6).replace(",", ".").toDouble();
		fraStrList += "<tr>";
		// lp, nazwa, kod, ilosc, jm, cena jm., netto, vat, brutto
		if (sett().value/*bool*/("faktury_pozycje/Lp").toBool())
			fraStrList += "<td>&nbsp;" + QString::number(i + 1) + "</td>";

		if (sett().value/*bool*/("faktury_pozycje/Nazwa") .toBool())
			fraStrList += "<td>&nbsp;" + tableTow->item(i, 1)->text() + "</td>";
		if (sett().value/*bool*/("faktury_pozycje/Kod") .toBool())
			fraStrList += "<td>&nbsp;" + tableTow->item(i, 2)->text() + "</td>";
		if (sett().value/*bool*/("faktury_pozycje/pkwiu") .toBool())
			fraStrList += "<td>&nbsp;" + tableTow->item(i, 3)->text() + "</td>";
		// pkwiu
		if (sett().value/*bool*/("faktury_pozycje/ilosc") .toBool())
			fraStrList += "<td>&nbsp;" + tableTow->item(i, 4)->text() + "</td>";
		if (sett().value/*bool*/("faktury_pozycje/jm") .toBool())
			fraStrList += "<td>&nbsp;" + tableTow->item(i, 5)->text() + "</td>";
		if (sett().value/*bool*/("faktury_pozycje/cenajedn") .toBool())
			fraStrList += "<td>&nbsp;" + tableTow->item(i, 6)->text() + "</td>";
		double cenajdn =
				tableTow->item(i, 6)->text().replace(",", ".").toDouble();
		double kwota = cenajdn
				* tableTow->item(i, 4)->text().replace(",", ".").toInt();
		if (sett().value/*bool*/("faktury_pozycje/wartnetto") .toBool())
			fraStrList += "<td>&nbsp;" + fixStr(QString::number(kwota))
					+ "</td>"; // netto
		if (sett().value/*bool*/("faktury_pozycje/rabatperc") .toBool())
			fraStrList += "<td>&nbsp;" + QString::number(rabatValue->value())
					+ "% </td>"; // rabat
		if (sett().value/*bool*/("faktury_pozycje/rabatval") .toBool())
			fraStrList += "<td>&nbsp;" + fixStr(
					QString::number(
							kwota - tableTow->item(i, 7)->text().replace(",",
									".").toDouble())) + " </td>"; // rabat value
		if (sett().value/*bool*/("faktury_pozycje/nettoafter") .toBool())
			fraStrList += "<td>&nbsp;" + tableTow->item(i, 7)->text() + "</td>"; // netto po rab
		if (sett().value/*bool*/("faktury_pozycje/vatval") .toBool())
			fraStrList += "<td>&nbsp;" + tableTow->item(i, 8)->text()
					+ "%</td>";
		double
				vatPrice =
						tableTow->item(i, 9)->text().replace(",", ".").toDouble()
								- tableTow->item(i, 7)->text().replace(",", ".").toDouble();
		if (sett().value/*bool*/("faktury_pozycje/vatprice") .toBool())
			fraStrList += "<td>&nbsp;" + fixStr(QString::number(vatPrice))
					+ "</td>";
		if (sett().value/*bool*/("faktury_pozycje/bruttoval") .toBool())
			fraStrList += "<td>&nbsp;" + tableTow->item(i, 9)->text() + "</td>";
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
	double vatPrice = sbrutto->text().replace(",", ".").toDouble()
			- snetto->text().replace(",", ".").toDouble();
	fraStrList += "<tr>";
	fraStrList
			+= "<td colspan=\"10\" width=\"420\" align=\"right\">&nbsp;</td>";
	fraStrList += "<td width=\"30\" align=\"center\">&nbsp;" + UTF8("Wartość") + "</br>" + UTF8(" Netto") + "</td>"; // netto
	fraStrList += "<td width=\"30\" >&nbsp;</td>";
	fraStrList += "<td width=\"30\" align=\"center\">&nbsp;" + UTF8("Kwota") + "</br>" + UTF8(" VAT") + "</td>";// vat
	fraStrList += "<td width=\"30\" align=\"center\">&nbsp;" + UTF8("Wartość") + "</br>" + UTF8(" Brutto") + "</td>"; // brutto
	fraStrList += "</tr>";
	fraStrList += "<tr>";
	fraStrList
			+= "<td colspan=\"10\" width=\"420\" align=\"right\">Razem:&nbsp;</td>";
	fraStrList += "<td align=\"center\">&nbsp;" + snetto->text() + "</td>"; // netto
	fraStrList += "<td>&nbsp;</td>";
	fraStrList += "<td align=\"center\">&nbsp;" + fixStr(QString::number(
			vatPrice)) + "</td>";// vat
	fraStrList += "<td align=\"center\">&nbsp;" + sbrutto->text() + "</td>"; // brutto
	fraStrList += "</tr>";
	fraStrList += "</table>";
}

void Faktura::makeInvoiceSummAll() {
	fraStrList += "<tr comment=\"podsumowanie\"><td>";
	fraStrList += "<table width=\"100%\" border=\"0\">";
	fraStrList += "<tr>";
	fraStrList += "<td width=\"3%\">&nbsp;</td>";
	fraStrList += "<td width=\"48%\"> ";
	fraStrList += UTF8("<h4>Do zapłaty: ") + sbrutto->text() + " "
			+ currCombo->currentText() + "</h4>";
	fraStrList += UTF8("<span style=\"font-size:8pt; font-weight:600;\">słownie:")
			+ slownie(sbrutto->text(), currCombo->currentText())
			+ "</span><br/>";
	fraStrList
			+= UTF8("<span style=\"font-size:8pt; font-weight:600;\">forma płatności: ")
					+ platCombo->currentText() + "<br/>";
	fraStrList += UTF8("termin płatności: ") + liabDate->date().toString("yyyy-MM-dd")
			+ "<br/>";
	QString paym1 = sett().value("paym1").toString();
	if (paym1.left(3) == platCombo->currentText().left(3))
		fraStrList += UTF8("<b>Zapłacono gotówką</b> <br/>");
	fraStrList += "</span><br/>";
	fraStrList += "<span style=\"font-size:10pt; font-weight:600;\">"
			+ additEdit->text() + "</span>";
	fraStrList += "</td>";
	fraStrList += "<td width=\"3%\">&nbsp;</td>";
	fraStrList += "<td width=\"48%\" valign=\"top\">";
	fraStrList += "<table width=\"90%\" border=\"0\">";
	fraStrList += "<tr>";
	fraStrList
			+= UTF8("<td colspan=\"4\"><span style=\"font-size:8pt; font-weight:600;\">Ogółem stawkami:</span>");
	fraStrList += "</td>"; // Ogółem stawkami:
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
	fraStrList += "<td width=\"43%\" align=\"center\"> ";
	fraStrList
			+= UTF8("<span style=\"font-size:8pt; font-weight:600;\">Imię i nazwisko osoby upoważnionej do wystawienia faktury VAT</span>");
	fraStrList += "</td>";
	fraStrList += "<td width=\"7%\">&nbsp;</td>";
	fraStrList += "<td width=\"3%\">&nbsp;</td>";
	fraStrList += "<td width=\"43%\" align=\"center\"> ";
	fraStrList
			+= UTF8("<span style=\"font-size:8pt; font-weight:600;\">Imię i nazwisko osoby upoważnionej do odbioru faktury VAT</span>");
	fraStrList += "</td>";
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
	// every currency in int value is equeal vat currncy

	int ssize = stawki.size();
	// qDebug( "%d", ssize );

	for (int i = 0; i < tableTow->rowCount(); ++i) {
		for (int y = 0; y < ssize; ++y) {
			if (stawki[y] == tableTow->item(i, 8)->text()) {
				stawkiNetto[y]
						+= tableTow->item(i, 7)->text().replace(",", ".").toDouble();
				stawkiBrutto[y] += tableTow->item(i, 9)->text().replace(",",
						".").toDouble();
				stawkiVat[y] += stawkiBrutto[y] - stawkiNetto[y];
			} else {
				stawkiNetto[y] += 0;
				stawkiBrutto[y] += 0;
				stawkiVat[y] += 0;

			}
		}
	}

	for (int y = 0; y < ssize; ++y) {
		out += "<tr>";
		out += "<td>" + fixStr(QString::number(stawkiNetto[y])) + "</td>"; // netto
		out += "<td>" + stawki[y] + "</td>"; // stawka
		out += "<td>" + fixStr(QString::number(stawkiVat[y])) + "</td>"; // podatek
		out += "<td>" + fixStr(QString::number(stawkiBrutto[y])) + "</td>"; // brutto
		out += "</tr>";

	}
	return out.join(" ");
}
// Generate Invoice HTML methods --- END ---

/** Read data
 *  Used when editInvoice is invoked. Invoked from MainWindow class.
 *  @TODO
 *  Names of the fields in the XML could be stored outside
 */
void Faktura::readData(QString fraFile, int co) {
	backBtn->setEnabled(false);
	frNr->setEnabled(false);
	if (co == 0) {
		setWindowTitle(UTF8("Edytuje Fakturę VAT"));
		type = 0;
	} else
		setWindowTitle(UTF8("Edytuje Fakturę Pro Forma"));

	// here we would read all data from one xml file to the this window
	QDomDocument doc("faktury");
	QDomElement root;
	QDomElement nabywca;
	QDomElement towary;
	fName = fraFile;

	QFile file(progDir2 + "/faktury/" + fraFile);
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
	sellingDate->setDate(QDate::fromString(root.attribute("sellingDate"),
			Qt::ISODate));
	productDate->setDate(QDate::fromString(root.attribute("issueDate"),
			Qt::ISODate));

	QDomNode tmp;
	tmp = root.firstChild();
	tmp = tmp.toElement().nextSibling(); // nabywca
	nabywca = tmp.toElement();
	kontrName->setText(nabywca.attribute("name") + ", " + nabywca.attribute(
			"city") + ", " + nabywca.attribute("street") + ", "
			+ nabywca.attribute("tic") + ", " + nabywca.attribute("account")
			+ ", " + nabywca.attribute("phone") + ", " + nabywca.attribute(
			"email") + ", " + nabywca.attribute("www"));
	kontrName->setCursorPosition(1);

	tmp = tmp.toElement().nextSibling(); // towary
	towary = tmp.toElement();

	rabatValue->setValue(towary.attribute("discount").toInt());

	int towCount = towary.attribute("productsCount").toInt();
	int i = 0;
	QDomElement towar;
	towar = towary.firstChild().toElement();

	// TR!!!
	static const char *towarColumns[] = { "", "name", "code", "PKWiU",
			"quantity", "quantityType", "discount", "price", "nett",
			"vatAmount", "gross" };

	tableTow->setRowCount(towCount);
	for (i = 0; i < towCount; ++i) {
		for (int j = 0; j < int(sizeof(towarColumns) / sizeof(*towarColumns)); j++) {
			tableTow->setItem(i, j, new QTableWidgetItem(towar.attribute(
					towarColumns[j])));
		}
		towar = towar.nextSibling().toElement();
	}

	tmp = tmp.toElement().nextSibling();
	QDomElement additional = tmp.toElement();
	additEdit->setText(additional.attribute("text"));
	platCombo->setCurrentIndex(additional.attribute("paymentType").toInt());
	liabDate-> setDate(QDate::fromString(additional.attribute("liabDate"),
			Qt::ISODate));
	currCombo->setCurrentIndex(additional.attribute("currency").toInt());
	if (!sett().value("edit").toBool()) {
		isEdit = true;
		frNr->setEnabled(FALSE);
		backBtn->setEnabled(FALSE);
		sellingDate->setEnabled(FALSE);
		productDate->setEnabled(FALSE);
		tableTow->setEnabled(FALSE);
		rabatValue->setEnabled(FALSE);
		platCombo->setEnabled(FALSE);
		liabDate->setEnabled(FALSE);
		//reasonCombo->setEnabled( FALSE );
		additEdit->setEnabled(FALSE);
		addTwBtn->setEnabled(FALSE);
		rmTowBtn->setEnabled(FALSE);
		editTwBtn->setEnabled(FALSE);
		constRab->setEnabled(FALSE);
		kListGet->setEnabled(FALSE);
		currCombo->setEnabled(FALSE);
		if (rabatValue->value() == 0) {
			constRab->setChecked(true);
		}
	} else {
		isEdit = false;
		frNr->setEnabled(TRUE);
		backBtn->setEnabled(TRUE);
		sellingDate->setEnabled(TRUE);
		productDate->setEnabled(TRUE);
		tableTow->setEnabled(TRUE);
		if (rabatValue->value() == 0) {
			constRab->setChecked(FALSE);
			rabatValue->setEnabled(FALSE);
		} else {
			constRab->setChecked(TRUE);
			rabatValue->setEnabled(TRUE);
		}
		platCombo->setEnabled(TRUE);
		liabDate->setEnabled(TRUE);
		//reasonCombo->setEnabled( TRUE );
		additEdit->setEnabled(TRUE);
		addTwBtn->setEnabled(true);
		rmTowBtn->setEnabled(false);
		editTwBtn->setEnabled(false);
		kListGet->setEnabled(TRUE);
		currCombo->setEnabled(TRUE);
		saveBtn->setEnabled(false);
	}

	calculateDiscount();
	calculateSum();
}

/** Caclulate Discount
 */
void Faktura::calculateDiscount() {
	QString rabat1 = QString::number(rabatValue->value());
	if (rabat1.length() == 1)
		rabat1 = "0.0" + rabat1;
	else
		rabat1 = "0." + rabat1;

	double kwota = 0;
	double cenajdn = 0;
	double rabat = 0;
	priceBRabN = 0;
	for (int i = 0; i < tableTow->rowCount(); ++i) {
		cenajdn = tableTow->item(i, 7)->text().replace(",", ".").toDouble();
		kwota = cenajdn
				* tableTow->item(i, 4)->text().replace(",", ".").toDouble();
		rabat = kwota * rabat1.toDouble();
		tableTow->item(i, 8)->setText(fixStr(QString::number(kwota - rabat))); // netto
		priceBRabN = priceBRabN + kwota;
	}

	double vat = 0;
	double netto = 0;
	QString vat1;
	kwota = 0;
	cenajdn = 0;
	rabat = 0;
	priceBRab = 0; // priceBRabN
	/*
	 rabat1 = QString::number( rabatValue->value());
	 if (rabat1.length() == 1) rabat1 = "1.0" + rabat1;
	 else rabat1 = "1." + rabat1;
	 */
	for (int i = 0; i < tableTow->rowCount(); ++i) {
		vat1 = tableTow->item(i, 9)->text().replace(",", ".");
		// QString::number( rabatValue->value());
		if (vat1.length() == 1)
			vat1 = "1.0" + vat1;
		else
			vat1 = "1." + vat1;

		vat = vat1.toDouble();
		if (vat == 0)
			vat = 1;
		netto = tableTow->item(i, 8)->text().replace(",", ".").toDouble(); // after rab.


		cenajdn = tableTow->item(i, 7)->text().replace(",", ".").toDouble();
		kwota = cenajdn
				* tableTow->item(i, 4)->text().replace(",", ".").toInt();
		rabat = kwota * rabat1.toDouble();
		// kwota - rabat; // jedn. netto
		priceBRab = priceBRab + (vat * (kwota));

		kwota = vat * netto;
		tableTow->item(i, 10)->setText(fixStr(QString::number(kwota)));
	}
}

/** Calculate sum
 */
void Faktura::calculateSum() {
	// count netto sum
	double kwota = 0;
	for (int i = 0; i < tableTow->rowCount(); ++i) {
		kwota += tableTow->item(i, 8)->text().replace(",", ".").toDouble();
		// qDebug(tableTow->text(i, 6).replace(",", "."));
	}
	snetto->setText(fixStr(QString::number(kwota)));

	// count brutto sum
	kwota = 0;
	for (int i = 0; i < tableTow->rowCount(); ++i) {
		kwota += tableTow->item(i, 10)->text().replace(",", ".").toDouble();
		// qDebug(tableTow->text(i, 6).replace(",", "."));
	}
	sbrutto->setText(fixStr(QString::number(kwota)));

	// count rabat
	QString rabat1 = QString::number(rabatValue->value());
	if (rabat1.length() == 1)
		rabat1 = "1.0" + rabat1;
	else
		rabat1 = "1." + rabat1;
	sRabat-> setText(fixStr(QString::number(priceBRabN
			- snetto->text().toDouble()). replace(".", ",")));
	// setting labels text
}


/** Number Counts
 *  Used while populating invoice symbol, fills zeros into invoice sybmol
 */
QString Faktura::numbersCount(int in, int x) {
	QString tmp2, tmp = QString::number(in);
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
		sett().setValue("towCol" + QString::number(i), tableTow->columnWidth(i));
	sett().endGroup();
}
