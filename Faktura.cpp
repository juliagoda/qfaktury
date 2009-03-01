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
	settings.beginGroup("fakturaForm");
	tableTow->setColumnWidth(0, settings.value("towCol0", QVariant(0)).toInt()); //index
	tableTow->setColumnWidth(1, settings.value("towCol1", QVariant(90)).toInt()); // nazwa
	tableTow->setColumnWidth(2, settings.value("towCol2", QVariant(35)).toInt()); // kod
	tableTow->setColumnWidth(3, settings.value("towCol3", QVariant(35)).toInt()); // kod
	tableTow->setColumnWidth(4, settings.value("towCol4", QVariant(40)).toInt()); // ilosc
	tableTow->setColumnWidth(5, settings.value("towCol5", QVariant(30)).toInt()); // jm
	tableTow->setColumnWidth(6, settings.value("towCol6", QVariant(30)).toInt()); // rabat
	tableTow->setColumnWidth(7, settings.value("towCol7", QVariant(60)).toInt()); // cena jedn.
	tableTow->setColumnWidth(8, settings.value("towCol8", QVariant(60)).toInt()); // netto
	tableTow->setColumnWidth(9, settings.value("towCol9", QVariant(30)).toInt()); // vat
	tableTow->setColumnWidth(10,
			settings.value("towCol10", QVariant(50)).toInt()); // netto *  (wzor vat)
	settings.endGroup();

	// set all the dates to todays date -> could be logical date :)
	sellingDate->setDate(QDate::currentDate());
	productDate->setDate(QDate::currentDate());
	liabDate->setDate(QDate::currentDate());

	// connects
	connect(addTw, SIGNAL(clicked()), this, SLOT(addTow()));
	connect(kListGet, SIGNAL(clicked()), this, SLOT(getCustomer()));
	connect(rabatValue, SIGNAL(valueChanged(int)), this, SLOT(discountChange()));
	connect(rmTow, SIGNAL(clicked()), this, SLOT(delTowar()));
	connect(tableTow, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(editTowar()));
	connect(editTw, SIGNAL(clicked()), this, SLOT(editTowar()));
	connect(backBtn, SIGNAL(clicked()), this, SLOT(backBtnClick()));
	connect(cancelbtn, SIGNAL(clicked()), this, SLOT(canCancel()));
    connect(printBtn, SIGNAL(clicked()), this, SLOT(makeData()));

	// Calulcate next number of the invoice
	QString tmp;
	if (windowTitle().right(3) == "VAT") {
		tmp = settings.value("fvat").toString();
	} else {
		tmp = settings.value("fpro").toString();
	}

	QStringList one1 = tmp.split("/");
	int nr = one1[0].toInt() + 1;
	qDebug() << tmp << one1 << nr;
	lastInvoice = QString::number(nr) + "/" + QDate::currentDate().toString(
			"MM/yyyy");
	frNr->setText(lastInvoice);


	/*
	 settings.beginGroup ("elinux/formatki");
	 this->setGeometry(settings.value ("formfra_left").toInt(),
	 settings.value ("formfra_top").toInt(),
	 settings.value ("formfra_width").toInt(),
	 settings.value ("formfra_height").toInt());
	 settings.endGroup();
	 */

	// load payments method and currencies
	platCombo->insertItems(0, settings.value("payments").toString().split("|"));
	currCombo->insertItems(0, settings.value("waluty").toString().split("|"));

	if (settings.value ("addText").toString().compare("") == 0 )
		additEdit->setText(settings.value("addText").toString());

	backBtnClick();

	// set window icon
	QIcon icon;
	icon.addPixmap(QPixmap(":/res/share/qfaktury/icons/nowa_faktura.png"),
			QIcon::Normal, QIcon::Off);
	this->setWindowIcon(icon);
}


// --- SLOTS START ----
/** Slot getCustomer
 *  Opens window with the list of the customers
 */
void Faktura::getCustomer ()
{
  KontrahenciLista *klWindow =
    new KontrahenciLista(this);
  if (klWindow->exec () == QDialog::Accepted)
    {
      kontrName->setText (klWindow->ret);
      kontrName->setCursorPosition (1);
    }
}

/** Slot discountChange
 *  Used to recalculate discount when spinBox arrows are pressed.
 */
void Faktura::discountChange() {
	countDiscount();
	countSum();
}

/** Slot addTow
 *  Shows window with a list of products
 */
void Faktura::addTow() {
	TowaryLista *twWindow = new TowaryLista(this);
	if (twWindow->exec() == QDialog::Accepted) {
		qDebug() << twWindow->ret;
		MainWindow::insertRow(tableTow, tableTow->rowCount());

		QStringList row = twWindow->ret.split("|");
		tableTow->item(tableTow->rowCount() - 1, 0)->setText(QString::number(
				tableTow->rowCount())); // id
		tableTow->item(tableTow->rowCount() - 1, 1)->setText(row[0]); // name
		tableTow->item(tableTow->rowCount() - 1, 2)->setText(row[1]); // code
		tableTow->item(tableTow->rowCount() - 1, 3)->setText(row[2]); // pkwiu
		tableTow->item(tableTow->rowCount() - 1, 4)->setText(row[3]); // quantity
		tableTow->item(tableTow->rowCount() - 1, 5)->setText(row[4]); // qType
		tableTow->item(tableTow->rowCount() - 1, 6)->setText(row[5]); // price
		tableTow->item(tableTow->rowCount() - 1, 7)->setText(row[6]); // nett
		tableTow->item(tableTow->rowCount() - 1, 8)->setText(row[7]); // vat
		tableTow->item(tableTow->rowCount() - 1, 9)->setText(row[8]); // gross
	}
	countDiscount();
	countSum();
}

/** Slot delTowar
 *  Remove the product from the list
 */
void Faktura::delTowar() {
	tableTow->removeRow(tableTow->currentRow());
	for (int i = 0; i < tableTow->rowCount(); ++i) {
		tableTow->item(i, 0)->setText(QString::number(i + 1));
	}
	countDiscount();
	countSum();
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
	}
	countDiscount();
	countSum();
}

/** Slot
 *  Used opulate invoice symbol
 */
void Faktura::backBtnClick() {
	QString tmp;
	Settings settings;
	QString prefix, suffix;

	if (windowTitle().right(3) == "VAT") {
		tmp = settings.value("fvat").toString();
	} else {
		tmp = settings.value("fpro").toString();
	}
	prefix = settings.value("prefix").toString();

	QStringList one1 = tmp.split("/");
	one1[0] = one1[0].remove(prefix);

	int nr = one1[0].toInt() + 1;
	lastInvoice = prefix + numbersCount(nr,
			settings.value("chars_in_symbol").toInt());

	if (settings.value/*bool*/("day") .toBool())
		lastInvoice += "/" + QDate::currentDate().toString("dd");

	if (settings.value/*bool*/("month") .toBool())
		lastInvoice += "/" + QDate::currentDate().toString("MM");

	if (settings.value/*bool*/("year") .toBool()) {
		if (!settings.value/*bool*/("shortYear") .toBool())
			lastInvoice += "/" + QDate::currentDate().toString("yy");
		else
			lastInvoice += "/" + QDate::currentDate().toString("yyyy");
	}
	suffix = settings.value("sufix").toString();
	lastInvoice += suffix;
	frNr->setText(lastInvoice);
}

/** Slot makeData
 *  Creates tableTemp object used by PrintPreview class.
 *  @TODO
 *  tabletemp contains content of what's gonna be displayed on the invoice
 *  it would be nice if we could move it to the a file so invoice could be
 *  printed in different language even though program is in polish
 */
void Faktura::makeData() {
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
	Settings settings;
	if (additEdit->isEnabled()) {
		saveInvoice();
		QMessageBox::information(this, "QFaktury", UTF8("Dane zostały zapisane"),QMessageBox::Ok);
	}

	if (invType == FVat) {
		tabletemp.data.title = tr("Faktura VAT");
	} else {
		tabletemp.data.title = tr("Faktura Pro Forma");
	}

#ifdef QF_vatmp__
	if (invType == FVat)
	{
		tabletemp.data.Title=tr("Faktura VAT - MP");
	}
	else
	{
		tabletemp.data.Title=tr("Faktura VAT - MP - Pro Forma");
	}
#endif

#ifdef QF_noVAT__
	tabletemp.data.Title=tr("Rachunek");
#endif

	tabletemp.data.number = tr("Nr: ") + frNr->text();
	tabletemp.data.sellingDate = tr("Data sprzedaży: ")
			+ sellingDate->date().toString(settings.getDateFormat());
	tabletemp.data.creatingDate = tr("Data wystawienia: ")
			+ productDate->date().toString(settings.getDateFormat());
	tabletemp.data.client = kontrName->text();
	int temp_i = 0;
	if (settings.value("faktury_pozycje/Lp").toBool()) {
		++temp_i;
	}
	if (settings.value("faktury_pozycje/Nazwa").toBool()) {
		++temp_i;
	}
	if (settings.value("faktury_pozycje/Kod").toBool()) {
		++temp_i;
	}
	if (settings.value("faktury_pozycje/pkwiu").toBool()) {
		++temp_i;
	}
	if (settings.value("faktury_pozycje/ilosc").toBool()) {
		++temp_i;
	}
	if (settings.value("faktury_pozycje/jm").toBool()) {
		++temp_i;
	}

	if (settings.value("faktury_pozycje/cenajedn").toBool()) {
		++temp_i;
	}
	if (settings.value("faktury_pozycje/wartnetto").toBool()) {
		++temp_i;
	}
	if (settings.value("faktury_pozycje/rabatperc").toBool()) {
		++temp_i;
	}
	if (settings.value("faktury_pozycje/rabatval").toBool()) {
		++temp_i;
	}
	if (settings.value("faktury_pozycje/nettoafter").toBool()) {
		++temp_i;
	}
	if (settings.value("faktury_pozycje/vatval").toBool()) {
		++temp_i;
	}
	if (settings.value("faktury_pozycje/vatprice").toBool()) {
		++temp_i;
	}
	if (settings.value("faktury_pozycje/bruttoval").toBool()) {
		++temp_i;
	}

	for (int i = 0; i < tableTow->rowCount(); ++i) {

		std::vector<QString> v;
		v.push_back(tableTow->item(i, 0)->text());
		v.push_back(tableTow->item(i, 1)->text());
		v.push_back(tableTow->item(i, 2)->text());
		v.push_back(tableTow->item(i, 3)->text());
		v.push_back(tableTow->item(i, 4)->text());
		v.push_back(tableTow->item(i, 5)->text());
		v.push_back(tableTow->item(i, 7)->text());
		double kwota = tableTow->item(i, 7)->text().replace(",", ".").toDouble()
						* tableTow->item(i, 4)->text().replace(",", ".").toDouble();
		v.push_back(fixStr(QString::number(kwota)));
		v.push_back(tableTow->item(i, 6)->text());
		v.push_back(fixStr(QString::number(kwota
				- tableTow->item(i, 8)->text().replace(",", ".").toDouble())));
		v.push_back(tableTow->item(i, 8)->text());
		v.push_back(tableTow->item(i, 9)->text());
		double vatPrice = tableTow->item(i, 10)->text().replace(",", ".").toDouble()
							- tableTow->item(i, 8)->text().replace(",", ".").toDouble();
		v.push_back(fixStr(QString::number(vatPrice)));
		v.push_back(tableTow->item(i, 10)->text());
		tabletemp.vec_temp.push_back(v);
	}

	tabletemp.data.netto = snetto->text();
	double vatPrice = sbrutto->text().toDouble() - snetto->text().toDouble();
	tabletemp.data.vat = fixStr(QString::number(vatPrice));
	tabletemp.data.brutto = sbrutto->text();
	tabletemp.data.sum = sbrutto->text() + " " + currCombo->currentText();

	tabletemp.data.sumStr = slownie(sbrutto->text(), currCombo->currentText());
	tabletemp.data.payMode = platCombo->currentText();
	tabletemp.data.payDate
			= liabDate->date().toString(settings.getDateFormat());
	tabletemp.data.paidCash = (settings.value("paym1").toString().left(3)
			== platCombo->currentText().left(3));
	tabletemp.data.additText = additEdit->text();
	tabletemp.data.bids = getGroupedSums();

	Podglad fraWindow(this);
	fraWindow.setTableTemp(tabletemp, progDir2, ret);
	fraWindow.exec();
	tabletemp.vec_temp.clear();
	saveColumnsWidth();
	close();
}


/** Slot
 *  Validate cancel
 */
void Faktura::canCancel()
{
	saveColumnsWidth();
    this->close();
}


/** Slot saveInvoice
 *  Generates Invoice XML
 */
void Faktura::saveInvoice() {

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

	QDomDocument doc("faktury");
	QDomElement root;
	QString fileName = fName;

	QFile file;
	if (fileName == "") {
		fileName = QDate::currentDate().toString(settings.getFnameDateFormat());

		int pNumber = 0;
		file.setFileName(progDir2 + "/faktury/h" + fileName + "_"
				+ QString::number(pNumber) + ".xml");
		ret = "h" + fileName + "_" + QString::number(pNumber) + ".xml" + "|";
		pNumber += 1;

		while (file.exists()) {
			file.setFileName(progDir2 + "/faktury/h" + fileName + "_"
					+ QString::number(pNumber) + ".xml");
			ret = "h" + fileName + "_" + QString::number(pNumber) + ".xml"
					+ "|";
			pNumber += 1;
		}
	} else {
		file.setFileName(progDir2 + "/faktury/" + fileName);
		ret = fileName + "|";
	}

	// if (!file.open (QIODevice::ReadOnly)) {

	root = doc.createElement("invoice");
	root.setAttribute("no", frNr->text());
	ret += frNr->text() + "|";
	root.setAttribute("issueDate", QDate::currentDate().toString(
			settings.getDateFormat()));
	ret += QDate::currentDate().toString(settings.getDateFormat()) + "|";
	root.setAttribute("sellingDate", sellingDate->date().toString(
			settings.getDateFormat()));

	Settings settings1;

	if (windowTitle().right(3) == "VAT") {
		root.setAttribute("type", "FVAT");
		settings1.setValue("fvat", frNr->text());
		ret += "FVAT|";
	} else {
		root.setAttribute("type", "FPro");
		settings1.setValue("fpro", frNr->text());
		ret += "FPro|";
	}

	doc.appendChild(root);

	QDomElement sprzedawca;
	sprzedawca = doc.createElement("seller");
	QSettings userSettings("elinux", "user");
	sprzedawca.setAttribute("name", settings.value("name").toString());
	sprzedawca.setAttribute("zip", settings.value("zip").toString());
	sprzedawca.setAttribute("city", settings.value("city").toString());
	sprzedawca.setAttribute("street", settings.value("street").toString());
	// NIP = Taxing Identification Code
	sprzedawca.setAttribute("tic", settings.value("tic").toString());
	sprzedawca.setAttribute("account",
			settings.value("account").toString(). replace(" ", "-"));
	userSettings.endGroup();
	root.appendChild(sprzedawca);

	Settings settings;

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
	// }


	QDomElement addinfo;
	addinfo = doc.createElement("addinfo");
	addinfo.setAttribute("text", additEdit->text());
	addinfo.setAttribute("paymentType", platCombo->currentText());
	addinfo.setAttribute("liabDate", liabDate->date().toString(
			settings.getDateFormat()));
	addinfo.setAttribute("currency", currCombo->currentText());
	root.appendChild(addinfo);

	QString xml = doc.toString();
	file.close();
	file.open(QIODevice::WriteOnly);
	QTextStream ts(&file);
	ts << xml;
	file.close();
	accept();
}
// ---- SLOTS END --

/** Read data
 *  Used when editInvoice is invoked
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
	if (!settings.value("edit").toBool()) {
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
		addTw->setEnabled(FALSE);
		rmTow->setEnabled(FALSE);
		editTw->setEnabled(FALSE);
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
		addTw->setEnabled(TRUE);
		rmTow->setEnabled(TRUE);
		editTw->setEnabled(TRUE);
		kListGet->setEnabled(TRUE);
		currCombo->setEnabled(TRUE);
	}

	countDiscount();
	countSum();
}


/** getGroupedSums
 *  Groups prices by VAT
 */
QString Faktura::getGroupedSums() {
	QStringList out;
	Settings settings;
	QStringList stawki = settings.value("stawki").toString().split("|");
	QMap<int, double> stawkiNetto;
	QMap<int, double> stawkiVat;
	QMap<int, double> stawkiBrutto;
	// every currency in int value is equeal vat currncy

	int ssize = stawki.size();
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
		out += fixStr(QString::number(stawkiNetto[y])) + ";"; // netto
		out += stawki[y] + ";"; // stawka
		out += fixStr(QString::number(stawkiVat[y])) + ";"; // podatek
		out += fixStr(QString::number(stawkiBrutto[y])) + ";"; // brutto

	}
	return out.join(" ");
}


void Faktura::countDiscount ()
{
  QString rabat1 = QString::number (rabatValue->value ());
  if (rabat1.length () == 1)
    rabat1 = "0.0" + rabat1;
  else
    rabat1 = "0." + rabat1;

  double kwota = 0;
  double cenajdn = 0;
  double rabat = 0;
  priceBRabN = 0;
  for (int i = 0; i < tableTow->rowCount (); ++i)
    {
      cenajdn = tableTow->item(i, 6)->text().replace (",", ".").toDouble ();
      kwota = cenajdn * tableTow->item(i, 4)->text().replace (",", ".").toInt ();
      rabat = kwota * rabat1.toDouble ();
      tableTow->item(i,7)->setText(fixStr (QString::number (kwota - rabat)));	// netto
      priceBRabN = priceBRabN + kwota;
      // qDebug(tableTow->text(i, 6).replace(",", "."));
    }

  double vat = 0;
  double netto = 0;
  QString vat1;
  kwota = 0;
  cenajdn = 0;
  rabat = 0;
  priceBRab = 0;		// priceBRabN
/*
    rabat1 = QString::number( rabatValue->value());
    if (rabat1.length() == 1) rabat1 = "1.0" + rabat1;
     else rabat1 = "1." + rabat1;
*/
  for (int i = 0; i < tableTow->rowCount (); ++i)
    {
      vat1 = tableTow->item(i, 8)->text().replace (",", ".");
      // QString::number( rabatValue->value());
      if (vat1.length () == 1)
	vat1 = "1.0" + vat1;
      else
	vat1 = "1." + vat1;

      vat = vat1.toDouble ();
      if ( vat == 0 ) vat = 1;
      netto = tableTow->item(i, 7)->text().replace (",", ".").toDouble ();	// after rab.

//************************************************************************//

      cenajdn = tableTow->item(i, 6)->text().replace (",", ".").toDouble ();
      kwota = cenajdn * tableTow->item(i, 4)->text().replace (",", ".").toInt ();
      rabat = kwota * rabat1.toDouble ();
      // kwota - rabat; // jedn. netto
      priceBRab = priceBRab + (vat * (kwota));

//************************************************************************//

      kwota = vat * netto;
      // qDebug(QString::number(kwota));
      tableTow->item(i,9)->setText (fixStr (QString::number (kwota)));
      // fixStr(
      // qDebug(tableTow->text(i, 6).replace(",", "."));
    }

}


void Faktura::countSum ()
{
  // count netto sum
  double kwota = 0;
  for (int i = 0; i < tableTow->rowCount (); ++i)
    {
      kwota += tableTow->item(i, 7)->text().replace (",", ".").toDouble ();
      // qDebug(tableTow->text(i, 6).replace(",", "."));
    }
  snetto->setText (fixStr (QString::number (kwota)));

  // count brutto sum
  kwota = 0;
  for (int i = 0; i < tableTow->rowCount (); ++i)
    {
      kwota += tableTow->item(i, 9)->text().replace (",", ".").toDouble ();
      // qDebug(tableTow->text(i, 6).replace(",", "."));
    }
  sbrutto->setText (fixStr (QString::number (kwota)));

  // count rabat
  QString rabat1 = QString::number (rabatValue->value ());
  if (rabat1.length () == 1)
    rabat1 = "1.0" + rabat1;
  else
    rabat1 = "1." + rabat1;
  // qDebug( "rabat " +  rabat1 );
  // double rabatVal = rabat1.toDouble();
  // double rabatBr = sbrutto->text().toDouble();
  // double przedRab = rabatVal * rabatBr;
  // qDebug("przed rabatem1: " + QString::number(priceBRab));
  // qDebug("przed rabatem2: " + QString::number(przedRab));
  sRabat->
    setText (fixStr
	     (QString::number (priceBRabN - snetto->text ().toDouble ()).
	      replace (".", ",")));
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
	Settings settings;
	settings.beginGroup("fakturaForm");
	for (int i = 0; i <= 10; ++i)
		settings.setValue("towCol" + QString::number(i), tableTow->columnWidth(i));
	settings.endGroup();
}
