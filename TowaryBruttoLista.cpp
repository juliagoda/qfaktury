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
	// nettoLabel->text() / ilosc
	double netto = sett().stringToDouble(nettoLabel->text()) / countSpinBox->value();
	return sett().numberToString(netto, 'f', 2);
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
			ret = selectedItem + "|" + listaTowary2[id]->getCode() + "|"
					+ listaTowary2[id]->getPkwiu() + "|"
					+ trimZeros(countSpinBox->cleanText()) + "|"
					+ listaTowary2[id]->getQuantityType() + "|"
					+ rabatSpin->cleanText() + "|"
					+ getPriceOfCurrent() + "|"
					+ nettoLabel->text() + "|" + sett().numberToString(vats[selectedItem]) + "|"
					+ bruttoLabel->text();

		}
		if (comboBox1->currentIndex() == 1) {
			ret = selectedItem + "|" + listaUslugi2[id]->getCode() + "|"
					+ listaUslugi2[id]->getPkwiu() + "|"
					+ trimZeros(countSpinBox->cleanText()) + "|"
					+ listaUslugi2[id]->getQuantityType() + "|"
					+ rabatSpin->cleanText() + "|"
					+ getPriceOfCurrent() + "|"
					+ nettoLabel->text() + "|" + sett().numberToString(vats[selectedItem]) + "|"
					+ bruttoLabel->text();

		}
		accept();
	} else {
		QMessageBox::information(this, "QFaktury", trUtf8("Wskaż towar"),
				QMessageBox::Ok);
	}
}

void TowaryBruttoLista::calcNetto(){
	QList<QListWidgetItem *> items = listWidget->selectedItems();
	if (items.size() == 1) {
		QListWidgetItem *item = items[0];
		double price = (countSpinBox->value() * priceBoxEdit->value()); // price * quantity
		double discount = price * (rabatSpin->value() * 0.01);
		double brutto2 = price - discount;
		int vat = vats[item->text()];
		double netto2 = brutto2 / ((vat * 0.01) + 1);
		// qDebug() << price << discount << netto2 << brutto2 << vat;
		bruttoLabel->setText(sett().numberToString(brutto2, 'f', 2));
		nettoLabel->setText(sett().numberToString(netto2, 'f', 2));
	}
}
