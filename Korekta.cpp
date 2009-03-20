#include "Korekta.moc"
#include <Qt/qdom.h>
#include <QMessageBox>
#include <QTextCodec>
#include <QTextStream>
#include <QtDebug>



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
		QString fname = "k" + fName + "_"	+ sett().numberToString(pNumber) + ".xml";
		file.setFileName(sett().getInvoicesDir() + fname);
		ret = fname + "|";
		pNumber += 1;

		while (file.exists()) {
			QString fname = "k" + fName + "_"	+ sett().numberToString(pNumber) + ".xml";
			file.setFileName(sett().getInvoicesDir() + fname);
			ret = fname + "|";
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
		double cenajdn = sett().stringToDouble(tableTow->item(i, 7)->text());
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
	for (QMap<int, ProductData *>::const_iterator iter =
		invData->products.begin(); iter != invData->products.end(); ++iter) {
		product = doc.createElement("product"); //  + tableTow->item(i, 0)->text());
		product.setAttribute("id", QString::number(iter.value()->getId()));
		product.setAttribute("name", iter.value()->getName());
		product.setAttribute("code",  iter.value()->getCode());
		product.setAttribute("PKWiU", iter.value()->getPkwiu()); // Polish Classification of STH
		product.setAttribute("quantity", sett().numberToString(iter.value()->getQuantity()));
		product.setAttribute("quantityType", iter.value()->getQuantityType());
		double discountVal = 0;
		if (!constRab->isChecked()) {
			discountVal = iter.value()->getDiscount();
			product.setAttribute("discount", sett().numberToString(iter.value()->getDiscount()));
		} else {
			discountVal = rabatValue->value();
			product.setAttribute("discount",
					sett().numberToString(rabatValue->value())); // rabat
		}
		product.setAttribute("price", sett().numberToString(iter.value()->getPrice()));
		double cenajdn = iter.value()->getPrice();
		// double kwota = cenajdn * iter.value()->getQuantity();
		product.setAttribute("nett", sett().numberToString(iter.value()->getNett())); // netto
		// product.setAttribute ("Rabat", QLocale::toString (rabatValue->value ()));	// rabat
		double discNett = iter.value()->getNett() -
					((discountVal * 0.01) * iter.value()->getNett());
		product.setAttribute("discountedNett", sett().numberToString(discNett));
		product.setAttribute("vatBucket", sett().numberToString(iter.value()->getVat()));
		double vatPrice = iter.value()->getGross() - iter.value()->getNett();
		product.setAttribute("vatAmout", sett().numberToString(vatPrice, 'f', 2));
		product.setAttribute("gross", sett().numberToString(iter.value()->getGross()));

		productsOriginal.setAttribute("productsCount", sett().numberToString(iter.key() + 1));
		productsOriginal.appendChild(product);
		// qDebug() << iter.value()->getName() << productsOriginal.nodeValue();
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

/** Slot
 *  Generate invoice and show preview
 */
void Korekta::makeInvoice(){
	// qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;
	invoiceType = trUtf8("Faktura VAT korygująca");
	fraStrList.clear();
	makeInvoiceHeadar(false);
	makeInvoiceBody();

	makeInvoceProductsTitle(0);
	makeBeforeCorrProducts();
	makeBeforeCorrSumm();

	makeInvoceProductsTitle(1);
	makeInvoiceProducts();
	makeInvoiceSumm();

	makeInvoiceSummAll();

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

/** Reads correction xml
 */
void Korekta::readCorrData(QString fraFile){
	backBtn->setEnabled(false);
	frNr->setEnabled(false);

	setWindowTitle(trUtf8("Edytuje korektę"));

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

	invData = new InvoiceData();
	invData->frNr = root.attribute("originalInvoiceNo");

	QDomNode tmp;
	tmp = root.firstChild();
	tmp = tmp.toElement().nextSibling(); // nabywca
	nabywca = tmp.toElement();
	kontrName->setText(nabywca.attribute("name") + "," + nabywca.attribute(
			"city") + "," + nabywca.attribute("street") + ","
			+ nabywca.attribute("tic"));
	kontrName->setCursorPosition(1);

	//*********************** Load Products Vars ***************************
	int towCount = 0;
	int i = 0;
	QDomElement towar;

	static const char *towarColumns[] = { "id", "name", "code", "PKWiU",
			"quantity", "quantityType", "discount", "price", "nett",
			"vatBucket", "gross" };

	//*********************** Load Products After ***************************
	tmp = tmp.toElement().nextSibling(); // product after
	product = tmp.toElement();
	towCount = product.attribute("productsCount").toInt();
	rabatValue->setValue(product.attribute("discount").toInt());
	// qDebug() << "product.nodeName() : "  << product.nodeName();

	towCount = product.attribute("productsCount").toInt();
	i = 0;
	towar = product.firstChild().toElement();

	tableTow->setRowCount(towCount);
	for (i = 0; i < towCount; ++i) {
		for (int j = 0; j < int(sizeof(towarColumns) / sizeof(*towarColumns)); j++) {
			tableTow->setItem(i, j, new QTableWidgetItem(towar.attribute(
					towarColumns[j])));
			// qDebug() << towarColumns[j] << towar.attribute(towarColumns[j]);
		}
		towar = towar.nextSibling().toElement();
	}

	//*********************** Load Products Before ***************************
	tmp = tmp.toElement().nextSibling(); // product before
	product = tmp.toElement();
	towCount = product.attribute("productsCount").toInt();
	// qDebug() << "product.nodeName() : "  << product.nodeName();
	towar = product.firstChild().toElement();
	/*
	// those fields are not stored in correction xml... for now
	invData->customer = kontrName->text();
	invData->liabDate = liabDate->date();
	invData->sellingDate = sellingDate->date();
	invData->productDate = productDate->date();
	invData->paymentType = platCombo->currentText();
	invData->currencyType = currCombo->currentText();
	invData->additText = additEdit->text();
	*/
	for (i = 0; i < towCount; ++i) {
		ProductData *product = new ProductData();
		product->setId(towar.attribute(towarColumns[0]));
		product->setName(towar.attribute(towarColumns[1]));
		product->setCode(towar.attribute(towarColumns[2]));
		product->setPkwiu(towar.attribute(towarColumns[3]));
		product->setQuantity(towar.attribute(towarColumns[4]));
		product->setQuanType(towar.attribute(towarColumns[5]));
		product->setDiscount(towar.attribute(towarColumns[6]));
		product->setPrice(towar.attribute(towarColumns[7]));
		product->setNett(towar.attribute(towarColumns[8]));
		product->setVat(towar.attribute(towarColumns[9]));
		product->setGross(towar.attribute(towarColumns[10]));
		// qDebug() << product->toString();
		invData->products[i] = product;
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

	int corrReason = sett().value("pkorekty").toString().split("|").indexOf(additional.attribute("reason"));
	reasonCombo->setCurrentIndex(corrReason);

	canClose = true;
	saveBtn->setEnabled(false);

	setIsEditAllowed(sett().value("edit").toBool());
	calculateDiscount();
	calculateSum();
}

/** Sets the controls into disabled/enabled state
 */
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
	if (invData == NULL)
		invData = createOriginalInv();
}

/**  Creates object with the orignal invoice
 */
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

/** Not used in this class
 */
void Korekta::calculateDiscount(){
	// qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;
}

/** Calculates the sums original invoice and the new one
 */
void Korekta::calculateSum(){
	// qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;
	double netto = 0, price = 0, quantity = 0, gross = 00;
	double discountValue = 0;

	// set to 0
	nettTotal = 0;
	discountTotal = 0;
	grossTotal = 0;
	// origGrossTotal = -1;
	origDiscTotal = 0;
	origNettTotal = 0;
	diffTotal = 0;

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

	// initially origGrossTotal is -1
	// if it's -1 will set to to 0 and go through whole calculation
	if (origGrossTotal < 0) {
		origGrossTotal = 0;
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

//*************** HTML methods START  *** *****************************
void Korekta::makeInvoceProductsTitle(short a) {
	fraStrList += "<tr align=\"center\"><td>";

	if (a==1) {
		fraStrList += trUtf8("Pozycje na fakturze po korekcie:");
	}
	if (a==0) {
		fraStrList += trUtf8("Pozycje na fakturze przed korektą:");
	}
}

void Korekta::makeBeforeCorrProducts(){

	fraStrList += "<table border=\"1\" cellspacing=\"0\" cellpadding=\"5\" width=\"100%\">";

	makeInvoiceProductsHeadar();

	for (QMap<int, ProductData *>::const_iterator iter = invData->products.begin();
			iter != invData->products.end();
			++iter) {
		// qDebug() << iter.value()->toString();
		fraStrList += "<tr valign=\"middle\" align=\"center\" class=\"products\">";
		// lp, nazwa, kod, pkwiu, ilosc, jm, rabat, cena jm., netto, vat, brutto
		if (sett().value("faktury_pozycje/Lp").toBool())
			fraStrList += "<td align=\"center\">" + sett().numberToString(iter.key() + 1) + "</td>";
		if (sett().value("faktury_pozycje/Nazwa") .toBool())
			fraStrList += "<td align=\"left\">" + iter.value()->getName() + "</td>";
		if (sett().value("faktury_pozycje/Kod") .toBool())
			fraStrList += "<td align=\"center\">" + iter.value()->getCode() + "</td>";
		if (sett().value("faktury_pozycje/pkwiu") .toBool())
			fraStrList += "<td align=\"center\">" + iter.value()->getPkwiu() + "</td>";
		if (sett().value("faktury_pozycje/ilosc") .toBool())
			fraStrList += "<td align=\"center\">" + sett().numberToString(iter.value()->getQuantity()) + "</td>";
		if (sett().value("faktury_pozycje/jm") .toBool())
			fraStrList += "<td align=\"center\">" + iter.value()->getQuantityType() + "</td>";
		if (sett().value("faktury_pozycje/cenajedn") .toBool())
			fraStrList += "<td align=\"center\">" + sett().numberToString(iter.value()->getPrice()) + "</td>";
		double discountVal = iter.value()->getNett() * (iter.value()->getDiscount() * 0.01);
		double nettMinusDisc = iter.value()->getNett() - discountVal;
		if (sett().value("faktury_pozycje/wartnetto") .toBool())
			fraStrList += "<td align=\"center\">" + sett().numberToString(iter.value()->getNett())
					+ "</td>"; // netto
		if (sett().value("faktury_pozycje/rabatperc") .toBool())
			fraStrList += "<td align=\"center\">" + sett().numberToString(iter.value()->getDiscount())
					+ "% </td>"; // rabat
		if (sett().value("faktury_pozycje/rabatval") .toBool())
			fraStrList += "<td align=\"center\">" + sett().numberToString(discountVal, 'f',  2)	+ " </td>";
		if (sett().value("faktury_pozycje/nettoafter") .toBool())
			fraStrList += "<td align=\"center\">" + sett().numberToString(nettMinusDisc, 'f', 2) + "</td>";
		if (sett().value("faktury_pozycje/vatval") .toBool())
			fraStrList += "<td align=\"center\">" + sett().numberToString(iter.value()->getVat())
					+ "%</td>";
		double vatPrice = iter.value()->getGross() - iter.value()->getNett(); // brutt-nett :)
		if (sett().value("faktury_pozycje/vatprice") .toBool())
			fraStrList += "<td align=\"center\">" + sett().numberToString(vatPrice, 'f', 2)
					+ "</td>";
		if (sett().value("faktury_pozycje/bruttoval") .toBool())
			fraStrList += "<td align=\"center\">" + sett().numberToString(iter.value()->getGross()) + "</td>";
		fraStrList += "</tr>";
	}

	fraStrList += "</table>";
}

void Korekta::makeBeforeCorrSumm(){
	// qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;
	fraStrList += "<br><table width=\"100%\" border=\"0\" cellpadding=\"5\">";
	double vatPrice = origGrossTotal - origNettTotal;
	fraStrList += "<tr class=\"productsSumHeader\" valign=\"middle\">";
		fraStrList += "<td width=\"67%\" align=\"right\">&nbsp;</td>";
		fraStrList += "<td width=\"11%\" align=\"center\">" + trUtf8("Wartość Netto") + "</td>"; // netto
		fraStrList += "<td width=\"11%\" align=\"center\">" + trUtf8("Kwota VAT") + "</td>";// vat
		fraStrList += "<td width=\"11%\" align=\"center\">" + trUtf8("Wartość Brutto") + "</td>"; // brutto
	fraStrList += "</tr>";
	fraStrList += "<tr class=\"productsSum\" valign=\"middle\">";
		fraStrList += "<td align=\"right\">" + trUtf8("Razem:") + "</td>";
		fraStrList += "<td align=\"center\">" + sett().numberToString(origNettTotal, 'f', 2) + "</td>"; // netto
		fraStrList += "<td align=\"center\">" + sett().numberToString(vatPrice, 'f', 2) + "</td>";// vat
		fraStrList += "<td align=\"center\">" + sett().numberToString(origGrossTotal, 'f', 2) + "</td>"; // brutto
	fraStrList += "</tr>";
	fraStrList += "</table>";

	fraStrList += "<hr class=\"hrdiv1\">";
	// fraStrList += "<br></td></tr>";
	// fraStrList += "</td></tr>";
}

void Korekta::makeInvoiceSumm() {
	// qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;
	fraStrList += "<br><table width=\"100%\" border=\"0\" cellpadding=\"5\">";
	double vatPrice = grossTotal - nettTotal;
	fraStrList += "<tr class=\"productsSumHeader\" valign=\"middle\">";
		fraStrList += "<td width=\"67%\" align=\"right\">&nbsp;</td>";
		fraStrList += "<td width=\"11%\" align=\"center\">" + trUtf8("Wartość Netto") + "</td>"; // netto
		fraStrList += "<td width=\"11%\" align=\"center\">" + trUtf8("Kwota VAT") + "</td>";// vat
		fraStrList += "<td width=\"11%\" align=\"center\">" + trUtf8("Wartość Brutto") + "</td>"; // brutto
	fraStrList += "</tr><tr class=\"productsSum\" valign=\"middle\">";
		fraStrList += "<td align=\"right\">" + trUtf8("Razem:") + "</td>";
		fraStrList += "<td align=\"center\">" + sett().numberToString(nettTotal, 'f', 2) + "</td>"; // netto
		fraStrList += "<td align=\"center\">" + sett().numberToString(vatPrice, 'f', 2) + "</td>";// vat
		fraStrList += "<td align=\"center\">" + sett().numberToString(grossTotal, 'f', 2) + "</td>"; // brutto
	fraStrList += "</tr>";
	fraStrList += "</table>";
	// fraStrList += "<br></td></tr>";
	// fraStrList += "</td></tr>";
}

void Korekta::makeInvoiceSummAll(){
	// qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

	// fraStrList += "<tr comment=\"podsumowanie\"><td>";
	fraStrList += "<table width=\"100%\" border=\"0\" cellpadding=\"7\">";
	fraStrList += "<tr class=\"summary\">";
		fraStrList += "<td width=\"48%\">";

		fraStrList += trUtf8("Wartość faktury: ") + sett().numberToString(origGrossTotal) + "<br>";
		fraStrList += trUtf8("Wartość korekty: ") + sett().numberToString(grossTotal) + "<br>";
		if (diffTotal > 0) {
			fraStrList += trUtf8("Do zapłaty: ");
			fraStrList += sum3->text() + " " + currCombo->currentText() + "<br>";
		} else if (diffTotal < 0) {
			fraStrList += trUtf8("Do zwrotu: ");
			fraStrList += sum3->text() + " " + currCombo->currentText()+ "<br>";
		}
		ConvertAmount* conv = new ConvertAmount();
		fraStrList += trUtf8("słownie:")
				+ conv->convertPL(sum3->text(), currCombo->currentText())
				+ "<br>";
		delete conv;

		fraStrList += trUtf8("forma płatności: ") + platCombo->currentText() + "<br>";
		QString paym1 = sett().value("paym1").toString();
		if (platCombo->currentIndex() == 0) {
			fraStrList += trUtf8("Zapłacono gotówką") + "<br>";
		} else {
			fraStrList += "<span style=\"payDate\">";
			fraStrList += trUtf8("termin płatności: ")
				+ liabDate->date().toString(sett().getDateFormat())	+ "<br>";
			fraStrList += "</span>";
		}

		fraStrList += trUtf8("przyczyna korekty: ") +  reasonCombo->currentText() + "<br>";
		fraStrList += "<span class=\"additionalText\">"	+ additEdit->text() + "</span>";

		fraStrList += "</td>";
		fraStrList += "<td width=\"4%\">&nbsp;</td>";
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

	fraStrList += "</td></tr></table>";
}
//*************** HTML methods END  *** *****************************

