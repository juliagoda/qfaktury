
#include "Settings.h"
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include <QtDebug>
#include "Walidacje.h"
#include "Towary.h"

/** Constructor
 */

Towary::Towary(QWidget *parent, int mode, IDataLayer *dl): QDialog(parent) {

    workMode = mode;
    dataLayer = dl;

	setupUi(this);
    init();
}

/** Init
 */

void Towary::init() {

	selectData("", 0);

	jednCombo->addItems(sett().value("jednostki").toString().split("|"));
	cbVat->addItems(sett().value("stawki").toString().split("|"));

	connect(okButton, SIGNAL(clicked()), this, SLOT(okClick()));
	connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
	connect(nettoEdit, SIGNAL(valueChanged(double)), this, SLOT(nettoChanged(double)));
	connect(spinBox2, SIGNAL(valueChanged(int)), this, SLOT(spinChanged(int)));
	connect(pkwiuBtn, SIGNAL(clicked()), this, SLOT(pkwiuGet()));
}

QString const Towary::getRetTow() const
{
    return ret;
}

/******************** SLOTS START ***************************/

/** Slot
 *  save data to XML file and returns row for products table
 */

void Towary::okClick() {

    if (Walidacje::instance()->isEmptyField(nameEdit->text(),textLabel3->text())) return;

	QString pkwiu = pkwiuEdit->text();

	if (pkwiu == "")  pkwiu = " ";   
    else {
        if (!Walidacje::instance()->validatePkwiu(pkwiuEdit->text())) return;
    }

	QString skrot = skrotEdit->text();

	if (skrot == "")
		skrot = " ";

	QString kod = kodEdit->text();

	if (kod == "")
		kod = " ";

	if (workMode == 1) {

        if (updateData()) {

            ret = idxEdit->text() + "|" + nameEdit->text() + "|" + skrot + "|"
				+ kod + "|" + pkwiu + "|" + typeCombo->currentText() + "|"
				+ jednCombo->currentText() + "|" + netto[0] + "|"
				+ netto[1] + "|" + netto[2] + "|" + netto[3] + "|"
				+ cbVat->currentText();
            accept();
        }

	} else {

		if (insertData()) {

			ret = idxEdit->text() + "|" + nameEdit->text() + "|" + skrot + "|"
				+ kod + "|" + pkwiu + "|" + typeCombo->currentText() + "|"
				+ jednCombo->currentText() + "|" + netto[0] + "|"
				+ netto[1] + "|" + netto[2] + "|" + netto[3] + "|"
					+ cbVat->currentText();

			accept();
		}
	}
}

/** Slot
 *  spinBox with list of prices changed
 */

void Towary::spinChanged(int a) {

	nettoEdit->setValue(netto[a - 1].toDouble());
}

/** Slot
 *  Nett value changed
 */

void Towary::nettoChanged(double ) {

	netto[spinBox2->value() - 1] = nettoEdit->cleanText();
}

/** Slot
 *  Find PKWIU code on the net
 */

void Towary::pkwiuGet() {

    QDesktopServices::openUrl(QUrl(tr("http://www.vat.pl/pkwiu/index.php?rodzajKlasyfikacji=pkwiuvat&kod")));
}

/******************** SLOTS END ***************************/

/** Loads data into the form
 */

void Towary::selectData(QString idx, int type) {

	if (idx == "") {

		netto.append("0");
		netto.append("0");
		netto.append("0");
		netto.append("0");
		nettoEdit->setValue(0);

	} else {

		setWindowTitle(trUtf8("Edytuj towar/usługę"));
		typeCombo->setEnabled(false);
	}

	ProductData prodData = dataLayer->productsSelectData(idx, type);

	if (workMode==0) {

		idx = QString::number(prodData.lastProdId);
		idxEdit->setText(idx);

	} else {

		getData(prodData);
	}

	typeCombo->setCurrentIndex(type);
}


/** Saves data from the form
 */

bool Towary::insertData() {

	nettoChanged(0);
	ProductData prodData;
	setData(prodData);
	dataLayer->productsInsertData(prodData, typeCombo->currentIndex());
	return true;
}

/** Modify product
 *  Searches for the right one and saves it.
 */

bool Towary::updateData() {

	nettoChanged(0);
	ProductData prodData;
	setData(prodData);
	dataLayer->productsUpdateData(prodData, typeCombo->currentIndex(), idxEdit->text() );
	return true;

}

/** Load from the form to Data object
 */

void Towary::getData(ProductData prodData) {

	idxEdit->setText(QString::number(prodData.id));
	nameEdit->setText(prodData.name);
	kodEdit->setText(prodData.code);
	skrotEdit->setText(prodData.desc);
	pkwiuEdit->setText(prodData.pkwiu);

	int current = 0;
	current = sett().value("jednostki").toString().split("|").indexOf(prodData.quanType);
	jednCombo->setCurrentIndex(current);
	current = sett().value("stawki").toString().split("|").indexOf(QString::number(prodData.vat));
	cbVat->setCurrentIndex(current);

	nettoEdit->setValue(prodData.prices[0]);
	netto[0] = sett().numberToString( prodData.prices[0]);
	netto[1] = sett().numberToString( prodData.prices[1]);
	netto[2] = sett().numberToString( prodData.prices[2]);
	netto[3] = sett().numberToString( prodData.prices[3]);
}

/** Display productData
 */

void Towary::setData(ProductData &prodData) {

	prodData.id = idxEdit->text().toInt();
	prodData.name = nameEdit->text();
	prodData.desc = skrotEdit->text();
	prodData.code = kodEdit->text();
	prodData.pkwiu = pkwiuEdit->text();
	prodData.quanType = jednCombo->currentText();
	prodData.prices[0] = sett().stringToDouble(netto[0]);
	prodData.prices[1] = sett().stringToDouble(netto[1]);
	prodData.prices[2] = sett().stringToDouble(netto[2]);
	prodData.prices[3] = sett().stringToDouble(netto[3]);
	prodData.vat = cbVat->currentText().toInt();
}
