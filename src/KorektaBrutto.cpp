/*
 * KorektaBrutto.cpp
 *
 *  Created on: Apr 3, 2009
 *      Author: moux
 */
#include "moc_KorektaBrutto.cpp"

#include "TowaryBruttoLista.h"
#include "MainWindow.h"
#include "KorektaBrutto.h"


/* Constructor
 */

KorektaBrutto::KorektaBrutto(QWidget *parent, IDataLayer *dl, QString in_form): Korekta(parent, dl, in_form) {

}

QString KorektaBrutto::getInvoiceTypeAndSaveNr() {

	sett().setValue("korNr", frNr->text());
	return "kbrutto";
}

/** Caclulate Discount
 */

void KorektaBrutto::calculateOneDiscount(int i) {

	// qDebug() << __FUNCTION__ << __LINE__ << __FILE__;
	double quantity = 0, vat = 0, gross = 0;
	double netto = 0,  price = 0;
	double discountValue = 0, discount;

	price = sett().stringToDouble(tableTow->item(i, 7)->text());

    if (constRab->isChecked()) discount = rabatValue->value() * 0.01;
    else discount = (tableTow->item(i, 6)->text()).toInt() * 0.01;

	quantity = sett().stringToDouble(tableTow->item(i, 4)->text());
	price = price * quantity;
	discountValue = price * discount;

	gross = price - discountValue;
	int vatValue = sett().stringToDouble(tableTow->item(i, 9)->text());
	vat = (gross * vatValue)/(100 + vatValue);

	netto = gross - vat;

	// qDebug() << price << quantity << netto << discount << discountValue << vat << gross;

    tableTow->item(i, 6)->setText(sett().numberToString(discount * 100, 'f', 0)); // discount
	tableTow->item(i, 8)->setText(sett().numberToString(netto)); // nett
	tableTow->item(i, 10)->setText(sett().numberToString(gross)); // gross

}

/** Slot
 *  Add new towar
 */

void KorektaBrutto::addTow() {

	TowaryBruttoLista *twWindow = new TowaryBruttoLista(this);
	if (twWindow->exec() == QDialog::Accepted) {

		MainWindow::insertRow(tableTow, tableTow->rowCount());
        QStringList row = twWindow->getRetVal().split("|");
		int rowNum = tableTow->rowCount() - 1;
		tableTow->item(rowNum, 0)->setText(sett().numberToString(
				tableTow->rowCount())); // id

        int i = 0;

        while (i < tableTow->columnCount()) {
            tableTow->item(rowNum, i+1)->setText(row[i]);
            i++;
        }

		canClose = false;

		if (constRab->isChecked())
			calculateDiscount();

		calculateSum();
	}

	delete twWindow;
    twWindow = 0;
}
