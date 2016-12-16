/*
 * TowaryBruttoLista.cpp
 *
 *  Created on: Apr 3, 2009
 *      Author: TPIELECH
 */
#include "moc_TowaryBruttoLista.cpp"

#include <QList>
#include <QListWidgetItem>

#include "TowaryBruttoLista.h"
#include "Settings.h"


TowaryBruttoLista::TowaryBruttoLista(QWidget *parent): TowaryLista(parent) {
}

TowaryBruttoLista::~TowaryBruttoLista() {
}


QString TowaryBruttoLista::getPriceOfCurrent() {

	double price = sett().stringToDouble(bruttoLabel->text()) / countSpinBox->value();
	return sett().numberToString(price, 'f', 2);
}

QString const TowaryBruttoLista::getRetValTowBr() const
{
    return ret;
}

/** Slot
 *  Accept and close
 */

void TowaryBruttoLista::doAccept() {

	if (countSpinBox->text() == "" || countSpinBox->value() < 0.001) {
		QMessageBox::information(this, "QFaktury", trUtf8("Podaj ilość"),
				QMessageBox::Ok);
		return;
	}

	selectedItem = nameEdit->text();

	if (selectedItem != "") {
		if (comboBox1->currentIndex() == 0) {
            ret = selectedItem + "|" + listaTowary2[getTowId()]->getCode() + "|"
                    + listaTowary2[getTowId()]->getPkwiu() + "|"
					+ trimZeros(countSpinBox->cleanText()) + "|"
                    + listaTowary2[getTowId()]->getQuantityType() + "|"
					+ rabatSpin->cleanText() + "|"
					+ getPriceOfCurrent() + "|"
                    + nettoLabel->text() + "|" + sett().numberToString(getVatsVal()[selectedItem]) + "|"
					+ bruttoLabel->text();

		}

		if (comboBox1->currentIndex() == 1) {
            ret = selectedItem + "|" + listaUslugi2[getTowId()]->getCode() + "|"
                    + listaUslugi2[getTowId()]->getPkwiu() + "|"
					+ trimZeros(countSpinBox->cleanText()) + "|"
                    + listaUslugi2[getTowId()]->getQuantityType() + "|"
					+ rabatSpin->cleanText() + "|"
					+ getPriceOfCurrent() + "|"
                    + nettoLabel->text() + "|" + sett().numberToString(getVatsVal()[selectedItem]) + "|"
					+ bruttoLabel->text();
		}

		accept();

	} else {

		QMessageBox::information(this, "QFaktury", trUtf8("Wskaż towar"),
				QMessageBox::Ok);
	}
}

void TowaryBruttoLista::calcNetto() {

    if (listWidget->selectedItems().size() == 1) {
		double price = (countSpinBox->value() * priceBoxEdit->value()); // price * quantity

		double discount = price * (rabatSpin->value() * 0.01);

		double wb = price - discount;
        int sp = getVatsVal()[listWidget->selectedItems().at(0)->text()];
        double vat = (wb * sp) / (100 + sp);
		double netto2 = wb - vat;
		// qDebug() << price << discount << netto2 << brutto2 << vat;
		bruttoLabel->setText(sett().numberToString(wb, 'f', 2));
		nettoLabel->setText(sett().numberToString(netto2, 'f', 2));
	}
}
