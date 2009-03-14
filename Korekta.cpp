#include "Korekta.moc"
#include <Qt/qdom.h>
#include <QMessageBox>
#include <QTextCodec>
#include <QTextStream>
#include <QtDebug>

#include "slownie.h"
#include "Settings.h"


// constructor
Korekta::Korekta(QWidget *parent): Faktura(parent) {
	// editMode = false;
}

Korekta::~Korekta() {
	delete invData;
	invData = NULL;
}

/* Init
 */
void Korekta::korektaInit (bool mode){
	// qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

	labelReason1 = new QLabel();
	labelReason1->setText(trUtf8("Przyczyna korekty:"));
	labelReason1->setAlignment(Qt::AlignRight);
	addDataLabels->addWidget(labelReason1);

	reasonCombo = new QComboBox();
    reasonCombo->addItems(sett().value("pkorekty").toString().split("|"));
	addData->addWidget(reasonCombo);

	textLabelSum1->setText(trUtf8("Wartość korekty:"));
	textLabelSum2->setText(trUtf8("Wartość faktury:"));
	textLabelSum3->setText(trUtf8("Do zapłaty:"));

	invoiceType = trUtf8("Korekta");

	invData = NULL; // set to null
	origGrossTotal = -1; // -1

	editMode = mode;
	// connects
    connect(reasonCombo, SIGNAL(currentIndexChanged (QString)), this, SLOT(textChanged(QString)));
}

//*********************************************** SLOTS START ****************************************/
/** Slot
 *  Used populate invoice symbol
 */
void Korekta::backBtnClick(){
	// qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

	QString tmp = sett().value("korNr").toString();
	QString prefix, suffix;

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
 *  Generate Correction XML
 */
void Korekta::saveInvoice(){
	// qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__ ;

	QDomDocument doc(sett().getCorrDocName());
	QDomElement root;
	if (!editMode) fName = "NULL";

	QFile file;
	if (fName.compare("NULL") == 0) {
		fName = QDate::currentDate().toString(sett().getFnameDateFormat());

		int pNumber = 0;
		file.setFileName(sett().getInvoicesDir() + "k" + fName + "_"
				+ sett().numberToString(pNumber) + ".xml");
		ret = file.fileName() + "|";
		pNumber += 1;

		while (file.exists()) {
			file.setFileName(sett().getInvoicesDir() + "k" + fName + "_"
					+ sett().numberToString(pNumber) + ".xml");
			ret = file.fileName() + "|";
			pNumber += 1;
		}
		// qDebug() << "Create new file " + file.fileName();
	} else {
		file.setFileName(sett().getInvoicesDir() + fName);
		// qDebug() << "Use existing file " + file.fileName();
		ret = fName + "|";
	}

	// if (!file.open (QIODevice::ReadOnly)) {

	root = doc.createElement("correction");
	root.setAttribute("no", frNr->text());
	root.setAttribute("originalInvoiceNo", invData->frNr);
	ret += frNr->text() + "|";
	root.setAttribute("issueDate", QDate::currentDate().toString(
			sett().getDateFormat()));
	ret += QDate::currentDate().toString(sett().getDateFormat()) + "|";
	root.setAttribute("sellingDate", sellingDate->date().toString(
			sett().getDateFormat()));
	root.setAttribute("type", "korekta");
	ret += "korekta|";
	doc.appendChild(root);

	QDomElement sprzedawca = createSellerElement(doc);
	root.appendChild(sprzedawca);

	QDomElement nabywca = createBuyerElement(doc);
	root.appendChild(nabywca);

	QDomElement product;
	QDomElement productsCorrected;
	productsCorrected = doc.createElement("productsCorrected");
	productsCorrected.setAttribute("discount", sett().numberToString(rabatValue->value()));
	for (int i = 0; i < tableTow->rowCount(); ++i) {
		product = doc.createElement("product"); //  + tableTow->item(i, 0)->text());
		productsCorrected.setAttribute("productsCount", sett().numberToString(i + 1));
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
		double kwota = cenajdn * tableTow->item(i, 4)->text().toInt();
		product.setAttribute("nett", sett().numberToString(kwota, 'f', 2)); // netto
		// product.setAttribute ("Rabat", QLocale::toString (rabatValue->value ()));	// rabat
		product.setAttribute("discountedNett", tableTow->item(i, 7)->text());
		product.setAttribute("vatBucket", tableTow->item(i, 9)->text());
		double vatPrice = sett().stringToDouble(tableTow->item(i, 10)->text())
							- sett().stringToDouble(tableTow->item(i, 8)->text());
		product.setAttribute("vatAmout", sett().numberToString(vatPrice, 'f', 2));
		product.setAttribute("gross", tableTow->item(i, 10)->text());
		productsCorrected.appendChild(product);

	}
	root.appendChild(productsCorrected);

	QDomElement productsOriginal;
	productsOriginal = doc.createElement("productsOriginal");
	productsOriginal.setAttribute("discount", sett().numberToString(rabatValue->value()));
	for (int i = 0; i < tableTow->rowCount(); ++i) {
		product = doc.createElement("product"); //  + tableTow->item(i, 0)->text());
		productsOriginal.appendChild(product);
	}
	root.appendChild(productsOriginal);

	QDomElement addinfo;
	addinfo = doc.createElement("addinfo");
	addinfo.setAttribute("text", additEdit->text());
	addinfo.setAttribute("paymentType", platCombo->currentText());
	addinfo.setAttribute("liabDate", liabDate->date().toString(sett().getDateFormat()));
	addinfo.setAttribute("currency", currCombo->currentText());
	addinfo.setAttribute("reason", reasonCombo->currentText());
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
	// qDebug() << xml;
	ts << xml;
	file.close();

	sett().setValue("korNr", frNr->text());

	saveBtn->setEnabled(false);
	rmTowBtn->setEnabled(false);
	editTwBtn->setEnabled(false);

	saveFailed = false;
	canClose = true;
	// qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  << ": canClose " << canClose;
}

void Korekta::makeInvoice(){
	// qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;
	invoiceType = trUtf8("Faktura VAT korygująca");
	fraStrList.clear();
	makeInvoiceHeadar(false);
	makeInvoiceBody();

	makeInvoceProductsTitle(0);
	makeBeforeInvoiceProducts();
	makeBeforeInvoiceSumm();

	makeInvoceProductsTitle(1);
	makeInvoiceProducts();
	makeInvoiceSumm();

	makeInvoiceFooter();

	print();
}

/** Slot
 *  Validate close and save if requested
 */
void Korekta::canQuit() {
	// qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__ << ": canClose " << canClose;
	if (canClose) {
		accept();
	} else {
		if (QMessageBox::warning(this, "QFaktury", trUtf8("Dane zostały zmienione czy chcesz zapisać?"),
					trUtf8("Tak"), trUtf8("Nie"), 0, 0,	1) == 1) {
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
}
//*********************************************** SLOTS END ****************************************/

void Korekta::setIsEditAllowed(bool isAllowed){
	// qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;
	if (editMode == false) {
		isAllowed = true;
		canClose = false;
	}

	isEdit = true;
	frNr->setEnabled(isAllowed);
	backBtn->setEnabled(isAllowed);
	sellingDate->setEnabled(isAllowed);
	productDate->setEnabled(isAllowed);
	tableTow->setEnabled(isAllowed);
	rabatValue->setEnabled(false); // don't allow for now
	rabatLabel->setEnabled(false); // don't allow for now
	platCombo->setEnabled(isAllowed);
	liabDate->setEnabled(isAllowed);
	additEdit->setEnabled(isAllowed);
	addTwBtn->setEnabled(isAllowed);
	rmTowBtn->setEnabled(isAllowed);
	editTwBtn->setEnabled(isAllowed);
	constRab->setEnabled(false); // don't allow for now
	kListGet->setEnabled(false); // don't allow to change kontrahent
	currCombo->setEnabled(isAllowed);
	saveBtn->setEnabled(isAllowed);
	liabDate->setEnabled(isAllowed);
	/*
	 const discount not allowed at all at the correction level
	if (!isAllowed && rabatValue->value() == 0) {
		constRab->setChecked(false);
		rabatValue->setEnabled(false);
	} else {
		constRab->setChecked(true);
		rabatValue->setEnabled(true);
	}
	*/
	if (!isAllowed && platCombo->currentIndex() > 0) {
		liabDate->setEnabled(true);
	} else {
		liabDate->setEnabled(false);
	}
	reasonCombo->setEnabled(isAllowed);

	//@TODO move it somewhere else, needs to be called after readData
    invData = createOriginalInv();

}

InvoiceData* Korekta::createOriginalInv() {
	// qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;
	invData = new InvoiceData();

	invData->customer = kontrName->text();

	for (int i = 0; i < tableTow->rowCount(); ++i) {
		ProductData *product = new ProductData();

		product->setId(tableTow->item(i, 0)->text());
		product->setName(tableTow->item(i, 1)->text());
		product->setCode(tableTow->item(i, 2)->text());
		product->setPkwiu(tableTow->item(i, 3)->text());
		product->setQuantity(tableTow->item(i, 4)->text());
		product->setQuanType(tableTow->item(i, 5)->text());
		product->setDiscount(tableTow->item(i, 6)->text());
		product->setPrice(tableTow->item(i, 7)->text());
		product->setNett(tableTow->item(i, 8)->text());
		product->setVat(tableTow->item(i, 9)->text());
		product->setGross(tableTow->item(i, 10)->text());

		// qDebug() << product->toString();
		invData->products[i] = product;
	}

	invData->liabDate = liabDate->date();
	invData->sellingDate = sellingDate->date();
	invData->productDate = productDate->date();
	invData->frNr  = frNr->text();
	invData->paymentType = platCombo->currentText();
	invData->currencyType = currCombo->currentText();
	invData->additText = additEdit->text();

	backBtnClick(); // populate correct correction symbol
	return invData;
}

/* Not used in this class
 */
void Korekta::calculateDiscount(){
	// qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;
}

void Korekta::calculateSum(){
	// qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;


	double netto = 0, price = 0, quantity = 0, gross = 00;
	double discountValue = 0;

	// sum of after correction invoice
	for (int i = 0; i < tableTow->rowCount(); ++i) {
		price = sett().stringToDouble(tableTow->item(i, 7)->text());
		quantity = sett().stringToDouble(tableTow->item(i, 4)->text());
		netto = sett().stringToDouble(tableTow->item(i, 8)->text());
		gross = sett().stringToDouble(tableTow->item(i, 10)->text());
		discountValue = (price * quantity) - netto;

		nettTotal += netto;
		discountTotal += discountValue;
		grossTotal += gross;
	}

	if (origGrossTotal < 0) {
		if (invData == NULL)
			invData = createOriginalInv();

		for (QMap<int, ProductData *>::const_iterator iter =
				invData->products.begin(); iter != invData->products.end(); ++iter) {
			// qDebug() << iter.value()->toString();
			origGrossTotal += iter.value()->getGross();
			origDiscTotal += iter.value()->getDiscount();
			origNettTotal += iter.value()->getNett();
		}
	}

	diffTotal = grossTotal - origGrossTotal;

	sum1->setText(sett().numberToString(grossTotal, 'f', 2));
	sum2->setText(sett().numberToString(origGrossTotal, 'f', 2));
	sum3->setText(sett().numberToString(diffTotal, 'f', 2));

	if (diffTotal < 0) {
		textLabelSum3->setText(trUtf8("Do zwrotu:"));
	} else {
		textLabelSum3->setText(trUtf8("Do zapłaty:"));
	}
}

QString Korekta::getGroupedSums(){
	qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;
}

void Korekta::makeInvoceProductsTitle(short a) {
	if (a==1) {
		fraStrList += trUtf8("Pozycje na fakturze po korekcie:");
	}
	if (a==0) {
		fraStrList += trUtf8("Pozycje na fakturze przed korektą:");
	}
}

void Korekta::makeBeforeInvoiceProducts(){
	fraStrList += "<tr align=\"center\"><td>";
	fraStrList += "<br>";
	fraStrList
			+= "<table border=\"1\" width=\"100%\" cellspacing=\"0\" style=\"font-size:8pt; font-weight:400;\">";
	fraStrList += "<tr>";

	makeInvoiceProductsTitle();

	for (QMap<int, ProductData *>::const_iterator iter = invData->products.begin();
			iter != invData->products.end();
			++iter) {
		// qDebug() << iter.value()->toString();
		fraStrList += "<tr>";
		// lp, nazwa, kod, pkwiu, ilosc, jm, rabat, cena jm., netto, vat, brutto
		if (sett().value("faktury_pozycje/Lp").toBool())
			fraStrList += "<td align=\"center\">&nbsp;" + sett().numberToString(iter.key() + 1) + "</td>";
		if (sett().value("faktury_pozycje/Nazwa") .toBool())
			fraStrList += "<td align=\"center\">&nbsp;" + iter.value()->getName() + "</td>";
		if (sett().value("faktury_pozycje/Kod") .toBool())
			fraStrList += "<td align=\"center\">&nbsp;" + iter.value()->getCode() + "</td>";
		if (sett().value("faktury_pozycje/pkwiu") .toBool())
			fraStrList += "<td align=\"center\">&nbsp;" + iter.value()->getPkwiu() + "</td>";
		if (sett().value("faktury_pozycje/ilosc") .toBool())
			fraStrList += "<td align=\"center\">&nbsp;" + sett().numberToString(iter.value()->getQuantity()) + "</td>";
		if (sett().value("faktury_pozycje/jm") .toBool())
			fraStrList += "<td align=\"center\">&nbsp;" + iter.value()->getQuantityType() + "</td>";
		if (sett().value("faktury_pozycje/cenajedn") .toBool())
			fraStrList += "<td align=\"center\">&nbsp;" + sett().numberToString(iter.value()->getPrice()) + "</td>";
		double discountVal = iter.value()->getNett() * (iter.value()->getDiscount() * 0.01);
		double nettMinusDisc = iter.value()->getNett() - discountVal;
		if (sett().value("faktury_pozycje/wartnetto") .toBool())
			fraStrList += "<td align=\"center\">&nbsp;" + sett().numberToString(iter.value()->getNett())
					+ "</td>"; // netto
		if (sett().value("faktury_pozycje/rabatperc") .toBool())
			fraStrList += "<td align=\"center\">&nbsp;" + sett().numberToString(iter.value()->getDiscount())
					+ "% </td>"; // rabat
		if (sett().value("faktury_pozycje/rabatval") .toBool())
			fraStrList += "<td align=\"center\">&nbsp;" + sett().numberToString(discountVal, 'f',  2)	+ " </td>";
		if (sett().value("faktury_pozycje/nettoafter") .toBool())
			fraStrList += "<td align=\"center\">&nbsp;" + sett().numberToString(nettMinusDisc, 'f', 2) + "</td>";
		if (sett().value("faktury_pozycje/vatval") .toBool())
			fraStrList += "<td align=\"center\">&nbsp;" + sett().numberToString(iter.value()->getVat())
					+ "%</td>";
		double vatPrice = iter.value()->getGross() - iter.value()->getNett(); // brutt-nett :)
		if (sett().value("faktury_pozycje/vatprice") .toBool())
			fraStrList += "<td align=\"center\">&nbsp;" + sett().numberToString(vatPrice, 'f', 2)
					+ "</td>";
		if (sett().value("faktury_pozycje/bruttoval") .toBool())
			fraStrList += "<td align=\"center\">&nbsp;" + sett().numberToString(iter.value()->getGross()) + "</td>";
		fraStrList += "</tr>";
	}


	fraStrList += "</table><br><br>";

}

void Korekta::makeBeforeInvoiceSumm(){
	// qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;
	fraStrList
			+= "<table border=\"0\" cellspacing=\"0\" style=\"font-size:8pt; font-weight:400;\">";
	fraStrList += "<tr>";
	double vatPrice = grossTotal - nettTotal;
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
	fraStrList += "<td align=\"center\">&nbsp;" + sett().numberToString(nettTotal, 'f', 2); // netto
	// fraStrList += "<td>&nbsp;</td>";
	fraStrList += "</td><td align=\"center\">&nbsp;" + sett().numberToString(vatPrice, 'f', 2) + "</td>";// vat
	fraStrList += "<td align=\"center\">&nbsp;" + sett().numberToString(grossTotal, 'f', 2) + "</td>"; // brutto
	fraStrList += "</tr>";
	fraStrList += "</table>";
	fraStrList += "<br></td></tr>";

}


void Korekta::makeInvoiceSummAll(){
	qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;
}




