
#include <QtXml/qdom.h>
#include <QMessageBox>
#include <QTextCodec>
#include <QTextStream>
#include <QLabel>
#include <QtDebug>
#include <QComboBox>
#include <QPushButton>
#include <QLineEdit>
#include "Korekta.h"
#include "Faktura.h"
#include "CustomPayment.h"
#include "Settings.h"
#include "TowaryLista.h"
#include "ZmienIlosc.h"
#include "Const.h"


// constructor
Korekta::Korekta(QWidget *parent, IDataLayer *dl, QString in_form, bool edMode): Faktura(parent, dl, in_form), editMode(edMode) {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

    firstRunned = true;
    origGrossBureau = 0;

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  << "EXIT";

}

Korekta::~Korekta() {

	delete invData;
	invData = NULL;

}


bool const Korekta::getMode() const
{
    return editMode;
}


bool const Korekta::getFirstRun() const
{
    return firstRunned;
}


QString const Korekta::getRet() const
{
    return ret;
}

/* Init
 */

void Korekta::korektaInit (bool mode){

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

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

    constRab->setEnabled(false);
    rabatValue->setEnabled(false);

    qDebug() << "Do zapłaty w korekcie: " << sett().stringToDouble(sum3->text());

	// connects
    connect(reasonCombo, SIGNAL(currentIndexChanged (QString)), this, SLOT(textChanged(QString)));
    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  << "EXIT";

}

//*********************************************** SLOTS START ****************************************/

/** Slot
 *  Used populate invoice symbol
 */

void Korekta::backBtnClick(){

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

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

	fName = "";
    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  << "EXIT";

}

/** Slot
 *  Generate Correction XML
 */

bool Korekta::saveInvoice(){

     qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  << fName;

	QDomDocument doc(sett().getCorrDocName());
	QDomElement root;

    if (!editMode && (fName == "")) fName = "NULL";

     qDebug() << fName;

	QFile file;

	if (fName == "NULL") {
		fName = QDate::currentDate().toString(sett().getFnameDateFormat());

        int pNumber = 0;
		QString fname = "k" + fName + "_"	+ sett().numberToString(pNumber) + ".xml";
		file.setFileName(sett().getInvoicesDir() + fname);
		ret = fname + "|";
		pNumber += 1;

		while (file.exists()) {
			fname = "k" + fName + "_"	+ sett().numberToString(pNumber) + ".xml";
			file.setFileName(sett().getInvoicesDir() + fname);
			ret = fname + "|";
			pNumber += 1;
        }

        qDebug() << "Create new file " + file.fileName();
		fName = fname;

	} else {

		file.setFileName(sett().getInvoicesDir() + fName);
        qDebug() << "Use existing file " + file.fileName();
		ret = fName + "|";
	}

	root = doc.createElement("correction");
	root.setAttribute("no", frNr->text());
	root.setAttribute("originalInvoiceNo", invData->frNr);
	ret += frNr->text() + "|";
	root.setAttribute("issueDate", QDate::currentDate().toString(
			sett().getDateFormat()));
	ret += QDate::currentDate().toString(sett().getDateFormat()) + "|";
	root.setAttribute("sellingDate", sellingDate->date().toString(
			sett().getDateFormat()));


    root.setAttribute("invValue", sum2->text());


	QString invType = getInvoiceTypeAndSaveNr();
	root.setAttribute("type", invType);
	ret += invType + "|";
	doc.appendChild(root);

    QDomElement sprzedawca = doc.createElement("seller");
    QSettings userSettings("elinux", "user");

    sprzedawca.setAttribute("name", userSettings.value("name").toString());
    sprzedawca.setAttribute("zip", userSettings.value("zip").toString());
    sprzedawca.setAttribute("city", userSettings.value("city").toString());
    sprzedawca.setAttribute("street", userSettings.value("street").toString());
    sprzedawca.setAttribute("tic", userSettings.value("tic").toString());
    sprzedawca.setAttribute("account", userSettings.value("account").toString(). replace(" ", "-"));
    sprzedawca.setAttribute("phone", userSettings.value("phone").toString());
    sprzedawca.setAttribute("email", userSettings.value("email").toString());
    sprzedawca.setAttribute("website", userSettings.value("website").toString());

    root.appendChild(sprzedawca);

    QDomElement nabywca = doc.createElement("buyer");
    QStringList kht = invData->customer.split(",");

    nabywca.setAttribute("name", kht[0]);
    ret += kht[0] + "|";
    nabywca.setAttribute("city", kht[1]);
    nabywca.setAttribute("street", kht[2]);
    nabywca.setAttribute("tic", kht[3].replace(" ", "").replace(QObject::trUtf8("NIP:"),     ""));
    ret += kht[3].replace(" ", "").replace(trUtf8("NIP:"), "");
    nabywca.setAttribute("account", kht[4].replace(" ", "").replace(QObject::trUtf8("Konto:"), ""));
    nabywca.setAttribute("phone", kht[5].replace(" ", "").replace(QObject::trUtf8("Tel:"), ""));
    nabywca.setAttribute("email", kht[6].replace(" ", "").replace(QObject::trUtf8("Email:"), ""));

    QString imprWeb = kht[7].replace(" ", "").replace(QObject::trUtf8("Strona:"), "");
    imprWeb = imprWeb.remove(imprWeb.indexOf("<"),imprWeb.indexOf(">") + 1);
    imprWeb = imprWeb.remove(imprWeb.indexOf("<"),imprWeb.indexOf(">"));

    nabywca.setAttribute("website", imprWeb);
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

            product.setAttribute("discount", sett().numberToString(rabatValue->value())); // rabat
		}

		product.setAttribute("price", tableTow->item(i, 7)->text());
		product.setAttribute("nett", tableTow->item(i, 8)->text()); // netto without discount
        product.setAttribute("discountedNett", tableTow->item(i, 7)->text());
		product.setAttribute("vatBucket", tableTow->item(i, 9)->text());
		double vatPrice = sett().stringToDouble(tableTow->item(i, 10)->text()) -
				sett().stringToDouble(tableTow->item(i, 8)->text());
		product.setAttribute("vatAmout", sett().numberToString(vatPrice, 'f', 2));
		product.setAttribute("gross", tableTow->item(i, 10)->text());
		productsCorrected.appendChild(product);

	}

	root.appendChild(productsCorrected);

	QDomElement productsOriginal;
	productsOriginal = doc.createElement("productsOriginal");
	productsOriginal.setAttribute("discount", sett().numberToString(rabatValue->value()));


    for (QMap<int, ProductData>::const_iterator iter =
		invData->products.begin(); iter != invData->products.end(); ++iter) {

        product = doc.createElement("product"); //  + tableTow->item(i, 0)->text());
        product.setAttribute("id", QString::number(iter.value().getId()));
        product.setAttribute("name", iter.value().getName());
        product.setAttribute("code",  iter.value().getCode());
        product.setAttribute("PKWiU", iter.value().getPkwiu()); // Polish Classification of STH
        product.setAttribute("quantity", sett().numberToString(iter.value().getQuantity()));
        product.setAttribute("quantityType", iter.value().getQuantityType());
		double discountVal = 0;

        if (!constRab->isChecked()) {

            discountVal = iter.value().getDiscount();
            product.setAttribute("discount", sett().numberToString(iter.value().getDiscount()));

        } else {

			discountVal = rabatValue->value();
			product.setAttribute("discount",
					sett().numberToString(rabatValue->value())); // rabat
		}

            product.setAttribute("price", sett().numberToString(iter.value().getPrice()));
            product.setAttribute("nett", sett().numberToString(iter.value().getNett())); // netto
            double discNett = (iter.value().getNett() -
                    ((discountVal * 0.01) * iter.value().getNett()));
            product.setAttribute("discountedNett", sett().numberToString(discNett));
            product.setAttribute("vatBucket", sett().numberToString(iter.value().getVat()));
            double vatPrice = (iter.value().getGross() - iter.value().getNett());
            product.setAttribute("vatAmout", sett().numberToString(vatPrice, 'f', 2));

            product.setAttribute("gross", sett().numberToString(iter.value().getGross()));
            productsOriginal.setAttribute("productsCount", sett().numberToString(iter.key() + 1));



		productsOriginal.appendChild(product);
        qDebug() << iter.value().getName() << productsOriginal.nodeValue();

	}

	root.appendChild(productsOriginal);

	QDomElement addinfo;
	addinfo = doc.createElement("addinfo");
	addinfo.setAttribute("text", additEdit->text());


    if (platCombo->currentText() == trUtf8("zaliczka")) {
        if (!editMode) {
            if (rComboWasChanged) {

                addinfo.setAttribute("payment1", custPaymData->payment1);
                addinfo.setAttribute("amount1", sett().numberToString(custPaymData->amount1, 'f', 2));
                addinfo.setAttribute("liabDate1", custPaymData->date1.toString(
                    sett().getDateFormat()));

                addinfo.setAttribute("payment2", custPaymData->payment2);
                addinfo.setAttribute("amount2", sett().numberToString(custPaymData->amount2, 'f', 2));
                addinfo.setAttribute("liabDate2", custPaymData->date2.toString(
                    sett().getDateFormat()));

            } else {

                ratesCombo->setCurrentIndex(0);

                addinfo.setAttribute("payment1", sendKindInfo->text());
                addinfo.setAttribute("amount1", rateLabelInfo->text());
                addinfo.setAttribute("liabDate1", ratesCombo->itemText(0));

                addinfo.setAttribute("amount2", restLabelInfo->text());
                addinfo.setAttribute("liabDate2", ratesCombo->itemText(1));

                ratesCombo->setCurrentIndex(1);
                addinfo.setAttribute("payment2", sendKindInfo->text());

            }
        } else {

            ratesCombo->setCurrentIndex(0);

            addinfo.setAttribute("payment1", sendKindInfo->text());
            addinfo.setAttribute("amount1", rateLabelInfo->text());
            addinfo.setAttribute("liabDate1", ratesCombo->itemText(0));

            addinfo.setAttribute("amount2", restLabelInfo->text());
            addinfo.setAttribute("liabDate2", ratesCombo->itemText(1));

            ratesCombo->setCurrentIndex(1);
            addinfo.setAttribute("payment2", sendKindInfo->text());
        }
    }

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
    }

	QTextStream ts(&file);
    qDebug() << xml;
	ts << xml;
	file.close();

	saveBtn->setEnabled(false);
	rmTowBtn->setEnabled(false);
	editTwBtn->setEnabled(false);

	saveFailed = false;
	canClose = true;

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  << ": canClose " << canClose;
    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  << "EXIT";

    return canClose;

}

/** Slot
 *  Generate invoice and show preview
 */

void Korekta::makeInvoice() {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

    invoiceType = s_CORRECTION;
	fraStrList.clear();

	makeInvoiceHeadarHTML();

	makeInvoiceHeadar(false, false, true);
	makeInvoiceBody();
	makeInvoceProductsTitle(0);
	makeBeforeCorrProducts();
	makeBeforeCorrSumm();
	makeInvoceProductsTitle(1);
	makeInvoiceProducts();
	makeInvoiceSumm();
	makeInvoiceSummAll();
	makeInvoiceFooter();

	int numberOfCopies = sett().value("numberOfCopies", 2).toInt();

	for (int i = 1; i <= numberOfCopies; i++) {

		makeInvoiceHeadar(false, true, false);
		makeInvoiceBody();
		makeInvoceProductsTitle(0);
		makeBeforeCorrProducts();
		makeBeforeCorrSumm();
		makeInvoceProductsTitle(1);
		makeInvoiceProducts();
		makeInvoiceSumm();
		makeInvoiceSummAll();
		makeInvoiceFooter();
	}

	makeInvoiceFooterHtml();

	print();

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  << "EXIT";

}

/** Slot
 *  Validate close and save if requested
 */

void Korekta::canQuit() {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__ << ": canClose " << canClose;

    if (canClose) {

        if (ret.isNull()) reject();
        else accept();

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

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  << "EXIT";

}
//*********************************************** SLOTS END ****************************************/

/** Reads correction xml
 */

void Korekta::readCorrData(QString fraFile) {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

    backBtn->setEnabled(false);
	frNr->setEnabled(false);

    setWindowTitle(trUtf8("Edytuje korektę"));
    qDebug("Plik fraFile");
    qDebug() << fraFile;
    QDomDocument doc(sett().getInvoicesDir());
	QDomElement root;
	QDomElement nabywca;
	QDomElement product;
	fName = fraFile;
    prepayFile = fraFile;

	QFile file(sett().getInvoicesDir() + fraFile);
	if (!file.open(QIODevice::ReadOnly)) {

		qDebug("file doesn't exist");
		return;

	} else {

		QTextStream stream(&file);
		if (!doc.setContent(stream.readAll())) {

            qDebug("You can't set content to correction xml");
			file.close();
			return;
		}
	}

	root = doc.documentElement();
	frNr->setText(root.attribute("no"));
	sellingDate->setDate(QDate::fromString(root.attribute("sellingDate"), sett().getDateFormat()));
	productDate->setDate(QDate::fromString(root.attribute("issueDate"),	sett().getDateFormat()));
    origGrossBureau = sett().stringToDouble(root.attribute("invValue"));

	invData = new InvoiceData();
	invData->frNr = root.attribute("originalInvoiceNo");

	QDomNode tmp;
	tmp = root.firstChild();
	tmp = tmp.toElement().nextSibling(); // nabywca
	nabywca = tmp.toElement();
	kontrName->setText(nabywca.attribute("name") + "," + nabywca.attribute(
			"city") + "," + nabywca.attribute("street") + "," + trUtf8("NIP: ")
            + nabywca.attribute("tic")
            + ", " + trUtf8("Konto: ")
            + nabywca.attribute("account")
                       + ", " + trUtf8("Tel: ")
                       + nabywca.attribute("phone") + ", " + trUtf8("Email: ")
                       + nabywca.attribute(
                       "email") + ", " + trUtf8("Strona: ")
                       + nabywca.attribute("website"));
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

	towCount = product.attribute("productsCount").toInt();
	i = 0;
	towar = product.firstChild().toElement();

	tableTow->setRowCount(towCount);

	for (i = 0; i < towCount; ++i) {
		for (int j = 0; j < int(sizeof(towarColumns) / sizeof(*towarColumns)); j++) {

            tableTow->setItem(i, j, new QTableWidgetItem(towar.attribute(
					towarColumns[j])));
		}

		towar = towar.nextSibling().toElement();
	}

	//*********************** Load Products Before ***************************

	tmp = tmp.toElement().nextSibling(); // product before
	product = tmp.toElement();
	towCount = product.attribute("productsCount").toInt();
	towar = product.firstChild().toElement();

    invData->customer = kontrName->text();
	invData->sellingDate = sellingDate->date();
	invData->productDate = productDate->date();


	for (i = 0; i < towCount; ++i) {

		ProductData product; //  = new ProductData();
		product.setId(towar.attribute(towarColumns[0]));
		product.setName(towar.attribute(towarColumns[1]));
		product.setCode(towar.attribute(towarColumns[2]));
		product.setPkwiu(towar.attribute(towarColumns[3]));
		product.setQuantity(towar.attribute(towarColumns[4]));
		product.setQuanType(towar.attribute(towarColumns[5]));
		product.setDiscount(towar.attribute(towarColumns[6]));
		product.setPrice(towar.attribute(towarColumns[7]));
		product.setNett(towar.attribute(towarColumns[8]));
		product.setVat(towar.attribute(towarColumns[9]));
		product.setGross(towar.attribute(towarColumns[10]));
        qDebug() << "Gross of this product: " << towar.attribute(towarColumns[10]);
		invData->products[i] = product;
		towar = towar.nextSibling().toElement();
	}

	tmp = tmp.toElement().nextSibling();
	QDomElement additional = tmp.toElement();
	additEdit->setText(additional.attribute("text"));
    invData->additText = additEdit->text();
    invData->paymentType = additional.attribute("paymentType");

    if (invData->paymentType == trUtf8("zaliczka")) {

        disconnect(platCombo, SIGNAL(currentIndexChanged (QString)), this, SLOT(payTextChanged(QString)));

        platCombo->setCurrentText(invData->paymentType);

        labelRate = new QLabel();
        labelRate->setText(trUtf8("Termin raty:"));
        labelRate->setAlignment(Qt::AlignRight);
        addDataLabels->addWidget(labelRate);

        if (ratesCombo == 0) ratesCombo = new QComboBox();
        disconnect(ratesCombo, SIGNAL(currentIndexChanged (QString)), this, SLOT(rateDateChanged(QString)));

        ratesCombo->addItem(additional.attribute("liabDate1"));
        ratesCombo->addItem(additional.attribute("liabDate2"));
        addData->addWidget(ratesCombo);

        rateLabel = new QLabel();
        rateLabel->setText(trUtf8("Rata:"));
        rateLabel->setAlignment(Qt::AlignRight);
        descPayments->addWidget(rateLabel);

        sendKind = new QLabel();
        sendKind->setText(trUtf8("Rodzaj zapłaty:"));
        sendKind->setAlignment(Qt::AlignRight);
        descPayments->addWidget(sendKind);

        restLabel = new QLabel();
        restLabel->setText(trUtf8("Pozostało do spłaty:"));
        restLabel->setAlignment(Qt::AlignRight);
        descPayments->addWidget(restLabel);

        rateLabelInfo = new QLabel();
        rateLabelInfo->setText(additional.attribute("amount1"));
        dataPayments->addWidget(rateLabelInfo);

        sendKindInfo = new QLabel();
        sendKindInfo->setText(additional.attribute("payment1"));
        dataPayments->addWidget(sendKindInfo);

        restLabelInfo = new QLabel();
        restLabelInfo->setText(additional.attribute("amount2"));
        dataPayments->addWidget(restLabelInfo);


		custPaymData = new CustomPaymData();
		custPaymData->payment1 = additional.attribute("payment1");

        double decimalPointsAmount1 = additional.attribute("amount1").right(2).toInt() * 0.01;
        qDebug() << "decimalPointsAmount1 << " << decimalPointsAmount1;
        double decimalPointsAmount2 = additional.attribute("amount2").right(2).toInt() * 0.01;
        qDebug() << "decimalPointsAmount2 << " << decimalPointsAmount2;

        custPaymData->amount1  = sett().stringToDouble(additional.attribute("amount1"));
        custPaymData->amount1 += decimalPointsAmount1;
		custPaymData->date1    = QDate::fromString(additional.attribute("liabDate1"), sett().getDateFormat());
		custPaymData->payment2 = additional.attribute("payment2");
        custPaymData->amount2  = sett().stringToDouble(additional.attribute("amount2"));
        custPaymData->amount2 += decimalPointsAmount2;
        custPaymData->date2    = QDate::fromString(additional.attribute("liabDate2"), sett().getDateFormat());

        if (editMode) {

            am1 = custPaymData->amount1;
            am2 = custPaymData->amount2;
        }

	} else {

        platCombo->setCurrentText(invData->paymentType);

	}


	liabDate-> setDate(QDate::fromString(additional.attribute("liabDate"), sett().getDateFormat()));
    invData->liabDate = liabDate->date();
    int curCurrency = sett().value("waluty").toString().split("|").indexOf(additional.attribute("currency"));
	currCombo->setCurrentIndex(curCurrency);
    invData->currencyType = currCombo->currentText();

	int corrReason = sett().value("pkorekty").toString().split("|").indexOf(additional.attribute("reason"));
	reasonCombo->setCurrentIndex(corrReason);

    if (invData->paymentType == trUtf8("zaliczka")) {

        connect(platCombo, SIGNAL(currentIndexChanged (QString)), this, SLOT(payTextChanged(QString)));
        connect(ratesCombo, SIGNAL(currentIndexChanged (QString)), this, SLOT(rateDateChanged(QString)));

    }

	canClose = true;
	saveBtn->setEnabled(false);

	setIsEditAllowed(sett().value("edit").toBool());
	calculateDiscount();
	calculateSum();
    file.close();

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  << "EXIT";
}

/** Sets the controls into disabled/enabled state
 */

void Korekta::setIsEditAllowed(bool isAllowed){

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

    if (editMode == false) {

		isAllowed = true;
		canClose = false;
	}

    if (!sett().value("editSymbol").toBool()) {

        frNr->setEnabled(isAllowed);
    }

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

	if (!isAllowed && rabatValue->value() == 0) {

		constRab->setChecked(false);
		rabatValue->setEnabled(false);

	} else {

		constRab->setChecked(true);
		rabatValue->setEnabled(true);
	}

    if (isAllowed && (platCombo->currentText() != trUtf8("zaliczka")))
		liabDate->setEnabled(true);
    else
		liabDate->setEnabled(false);

	reasonCombo->setEnabled(isAllowed);

	if (invData == NULL)
		invData = createOriginalInv();

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  << "EXIT";

}

/**  Creates object with the orignal invoice
 */

InvoiceData* Korekta::createOriginalInv() {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

    invData = new InvoiceData();
	invData->customer = kontrName->text();
    qDebug() << "Ile jest wierszy: ";

    for (int i = 0; i < tableTow->rowCount(); ++i) {

		ProductData product; //  = new ProductData();
		product.setId(tableTow->item(i, 0)->text());
		product.setName(tableTow->item(i, 1)->text());
		product.setCode(tableTow->item(i, 2)->text());
		product.setPkwiu(tableTow->item(i, 3)->text());
		product.setQuantity(tableTow->item(i, 4)->text());
		product.setQuanType(tableTow->item(i, 5)->text());
		product.setDiscount(tableTow->item(i, 6)->text());
		product.setPrice(tableTow->item(i, 7)->text());
		product.setNett(tableTow->item(i, 8)->text());
		product.setVat(tableTow->item(i, 9)->text());
		product.setGross(tableTow->item(i, 10)->text());
        qDebug() << "Gross w funkcji createOriginalInv " << i << ": " << tableTow->item(i, 10)->text();
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
    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  << "EXIT";

}

/** Not used in this class
 */

void Korekta::calculateDiscount(){

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;
}


void Korekta::schemaCalcSum()
{
    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;
    double netto = 0, price = 0, quantity = 0, gross = 00;
    double discountValue = 0;

    qDebug() << "platCombo->currentText(): " << platCombo->currentText();
    qDebug() << "origGrossTotal na początku funkcji: " << origGrossTotal;

    // set to 0
    nettTotal = 0;
    discountTotal = 0;
    grossTotal = 0;
    if (firstRunned) {
        if (platCombo->currentText() == trUtf8("zaliczka")) {
            if (!editMode) {
                rateLabelInfo->setText(sett().numberToString(0));
                restLabelInfo->setText(sett().numberToString(0));
                am1 = 0;
                am2 = 0;
            }
        }
        if (origGrossTotal != -1) origGrossTotal = -1;
    }

    qDebug() << "origGrossTotal na początku funkcji 2: " << origGrossTotal;

    // origGrossTotal = -1;
    origDiscTotal = 0;
    origNettTotal = 0;
    diffTotal = 0;

    // sum of after correction invoice
    for (int i = 0; i < tableTow->rowCount(); ++i) {
        price = sett().stringToDouble(tableTow->item(i, 7)->text());
        quantity = tableTow->item(i, 4)->text().toInt();
        netto = sett().stringToDouble(tableTow->item(i, 8)->text());
        double decimalPointsNetto = tableTow->item(i, 8)->text().right(2).toInt() * 0.01;
        qDebug() << "decimalPointsNetto << " << decimalPointsNetto;
        double decimalPointsGross = tableTow->item(i, 10)->text().right(2).toInt() * 0.01;
        qDebug() << "decimalPointsGross << " << decimalPointsGross;
        netto += decimalPointsNetto;
        gross = sett().stringToDouble(tableTow->item(i, 10)->text());
        gross += decimalPointsGross;
        discountValue += (price * quantity) - netto;
        nettTotal += netto;
        grossTotal += gross;
    }

    discountTotal = (discountValue * nettTotal)/100;

    // initially origGrossTotal is -1
    // if it's -1 will set to to 0 and go through whole calculation
    if (origGrossTotal < 0) {
        origGrossTotal = 0;
        qDebug() << "origGrossTotal mniejsze od zera: " << origGrossTotal;

        goodsEdited = true;

        if (invData == NULL) {
            invData = createOriginalInv();
        } else {
            if (invData->products.count() == 0) {
                origGrossTotal = -1;
            }
        }

        qDebug() << "produktów jest przed pętlą: " << invData->products.count();

        for (QMap<int, ProductData>::const_iterator iter =
                invData->products.begin(); iter != invData->products.end(); ++iter) {
            // qDebug() << iter.value()->toString();
            if (origGrossBureau == 0) {
                origGrossTotal += iter.value().getGross();
            }

            origDiscTotal += iter.value().getDiscount();
            origNettTotal += iter.value().getNett();

        }

        if (origGrossBureau != 0) {
            origGrossTotal = origGrossBureau;
        }

        qDebug() << "origGrossTotal w pętli QMap: " << origGrossTotal;
    }

    diffTotal = grossTotal - origGrossTotal;


    qDebug() << "diffTotal = grossTotal - origGrossTotal" << diffTotal << " = " << grossTotal << " - " << origGrossTotal;
    sum1->setText(sett().numberToString(grossTotal, 'f', 2));
    qDebug() << "grossTotal: " << grossTotal;
    sum2->setText(sett().numberToString(origGrossTotal, 'f', 2));
    qDebug() << "origGrossTotal: " << origGrossTotal;
    sum3->setText(sett().numberToString(diffTotal, 'f', 2));
    qDebug() << "diffTotal: " << diffTotal;


    if (diffTotal < 0) {
        textLabelSum3->setText(trUtf8("Do zwrotu:"));
    } else if (diffTotal > 0) {
        textLabelSum3->setText(trUtf8("Do zapłaty:"));
    } else {
        textLabelSum3->setText("");
    }


    if (firstRunned) firstRunned = false;

}

/** Calculates the sums original invoice and the new one
 */

void Korekta::calculateSum(){

    if (editMode) {
        if ((invData != NULL) && (invData->products.count() > 0)) {

            schemaCalcSum();

        }

    } else {

        schemaCalcSum();

    }
}


void Korekta::calculateOneDiscount(int i) {

    qDebug() << __FUNCTION__ << __LINE__ << __FILE__;

	double quantity = 0, vat = 0, gross = 0;
	double netto = 0,  price = 0;
	double discountValue = 0, discount;

	price = sett().stringToDouble(tableTow->item(i, 7)->text());

	if (constRab->isChecked()) {
        discount = rabatValue->value() * 0.01;
	} else {
        discount = (tableTow->item(i, 6)->text()).toInt() * 0.01;
	}

    quantity = tableTow->item(i, 4)->text().toInt();
	netto = (price * quantity);
	discountValue = netto * discount;
	netto -= discountValue;
    vat = tableTow->item(i, 9)->text().toInt();
	gross = netto * ((vat * 0.01) + 1);

	// qDebug() << price << quantity << netto << discount << discountValue << vat << gross;

    tableTow->item(i, 6)->setText(sett().numberToString(discount * 100, 'f', 0)); // discount
	tableTow->item(i, 8)->setText(sett().numberToString(netto)); // nett
	tableTow->item(i, 10)->setText(sett().numberToString(gross)); // gross

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  << "EXIT";

}


QString Korekta::getInvoiceTypeAndSaveNr() {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;
	sett().setValue("korNr", frNr->text());
    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  << "EXIT";

	return "korekta";
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

	for (QMap<int, ProductData>::const_iterator iter = invData->products.begin();
			iter != invData->products.end();
			++iter) {

		// qDebug() << iter.value()->toString();
		fraStrList += "<tr valign=\"middle\" align=\"center\" class=\"products\">";
		// lp, nazwa, kod, pkwiu, ilosc, jm, rabat, cena jm., netto, vat, brutto
		if (sett().value("faktury_pozycje/Lp").toBool())
			fraStrList += "<td align=\"center\">" + sett().numberToString(iter.key() + 1) + "</td>";

        if (sett().value("faktury_pozycje/Nazwa") .toBool())
            fraStrList += "<td align=\"left\">" + iter.value().getName() + "</td>";

        if (sett().value("faktury_pozycje/Kod") .toBool())
            fraStrList += "<td align=\"center\">" + iter.value().getCode() + "</td>";

        if (sett().value("faktury_pozycje/pkwiu") .toBool())
            fraStrList += "<td align=\"center\">" + iter.value().getPkwiu() + "</td>";

        if (sett().value("faktury_pozycje/ilosc") .toBool())
            fraStrList += "<td align=\"center\">" + sett().numberToString(iter.value().getQuantity()) + "</td>";

        if (sett().value("faktury_pozycje/jm") .toBool())
            fraStrList += "<td align=\"center\">" + iter.value().getQuantityType() + "</td>";

        if (sett().value("faktury_pozycje/cenajedn") .toBool())
            fraStrList += "<td align=\"center\">" + sett().numberToString(iter.value().getPrice()) + "</td>";

        double discountVal = iter.value().getNett() * (iter.value().getDiscount() * 0.01);
        double nettMinusDisc = iter.value().getNett() - discountVal;

        if (sett().value("faktury_pozycje/wartnetto") .toBool())
            fraStrList += "<td align=\"center\">" + sett().numberToString(iter.value().getNett())
					+ "</td>"; // netto

        if (sett().value("faktury_pozycje/rabatperc") .toBool())
            fraStrList += "<td align=\"center\">" + sett().numberToString(iter.value().getDiscount())
					+ "% </td>"; // rabat

        if (sett().value("faktury_pozycje/rabatval") .toBool())
			fraStrList += "<td align=\"center\">" + sett().numberToString(discountVal, 'f',  2)	+ " </td>";

        if (sett().value("faktury_pozycje/nettoafter") .toBool())
			fraStrList += "<td align=\"center\">" + sett().numberToString(nettMinusDisc, 'f', 2) + "</td>";

        if (sett().value("faktury_pozycje/vatval") .toBool())
            fraStrList += "<td align=\"center\">" + sett().numberToString(iter.value().getVat())
					+ "%</td>";
        double vatPrice = iter.value().getGross() - iter.value().getNett(); // brutt-nett :)

        if (sett().value("faktury_pozycje/vatprice") .toBool())
			fraStrList += "<td align=\"center\">" + sett().numberToString(vatPrice, 'f', 2)
					+ "</td>";

        if (sett().value("faktury_pozycje/bruttoval") .toBool())
            fraStrList += "<td align=\"center\">" + sett().numberToString(iter.value().getGross()) + "</td>";

        fraStrList += "</tr>";

	}

	fraStrList += "</table>";
}

void Korekta::makeBeforeCorrSumm(){

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;
    fraStrList += "<br/><table width=\"100%\" border=\"0\" cellpadding=\"5\">";
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

}


void Korekta::makeInvoiceSumm() {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;
    fraStrList += "<br/><table width=\"100%\" border=\"0\" cellpadding=\"5\">";
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

}


void Korekta::makeInvoiceSummAll(){

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

	fraStrList += "<table width=\"100%\" border=\"0\" cellpadding=\"7\">";
	fraStrList += "<tr class=\"summary\">";
    fraStrList += "<td width=\"48%\">";
    fraStrList += trUtf8("Wartość faktury: ") + sett().numberToString(origGrossTotal) + "<br/>";
    fraStrList += trUtf8("Wartość korekty: ") + sett().numberToString(grossTotal) + "<br/>";

    if (diffTotal > 0) {

        fraStrList += trUtf8("Do zapłaty: ");
        fraStrList += sum3->text() + " " + currCombo->currentText() + "<br/>";

    } else if (diffTotal < 0) {

        fraStrList += trUtf8("Do zwrotu: ");
        fraStrList += sum3->text() + " " + currCombo->currentText()+ "<br/>";
    }

		ConvertAmount* conv = new ConvertAmount();
		fraStrList += trUtf8("słownie:")
				+ conv->convertPL(sum3->text(), currCombo->currentText())
                + "<br/>";
		delete conv;

        if (platCombo->currentText() == trUtf8("gotówka")) {

            fraStrList += trUtf8("forma płatności: ") + platCombo->currentText() + "<br><b>";
            fraStrList += trUtf8("Zapłacono gotówką") + "<br>";

        } else if (platCombo->currentText() == trUtf8("zaliczka")) {

            fraStrList += "<span style=\"toPay\">";

            ratesCombo->setCurrentIndex(0);
            QString whatMethod_one = QString();
            if (sendKindInfo->text() == trUtf8("gotówka")) whatMethod_one = trUtf8("gotówką");
            else whatMethod_one = trUtf8("przelewem");

            ratesCombo->setCurrentIndex(1);
            QString whatMethod_two = QString();
            if (sendKindInfo->text() == trUtf8("gotówka")) whatMethod_two = trUtf8("gotówką");
            else whatMethod_two = trUtf8("przelewem");

            ratesCombo->setCurrentIndex(0);

            fraStrList += QString(trUtf8("Zapłacono ") + whatMethod_one + ": "
                    +  rateLabelInfo->text() + " " + currCombo->currentText() + " "
                    + ratesCombo->itemText(0) + "<br>");
            fraStrList += QString(trUtf8("Zaległości ") + whatMethod_two + ": "
                    +  restLabelInfo->text() + " " + currCombo->currentText() + " "
                    + ratesCombo->itemText(1));
            fraStrList += "</span>";

        }  else if (platCombo->currentText() == trUtf8("przelew")) {

            fraStrList += trUtf8("forma płatności: ") + platCombo->currentText() + "<br><b>";
            fraStrList += trUtf8("Zapłacono przelewem") + "<br>";
            fraStrList += "<span style=\"payDate\">";
            fraStrList += trUtf8("termin płatności: ")
                + liabDate->date().toString(sett().getDateFormat())	+ "<br>";
            fraStrList += "</span>";

        } else {

            fraStrList += trUtf8("forma płatności: ") + platCombo->currentText() + "<br><b>";
            fraStrList += "<span style=\"payDate\">";
            fraStrList += trUtf8("termin płatności: ")
                + liabDate->date().toString(sett().getDateFormat())	+ "<br>";
            fraStrList += "</span>";
        }

        fraStrList += trUtf8("przyczyna korekty: ") +  reasonCombo->currentText() + "<br/>";
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

