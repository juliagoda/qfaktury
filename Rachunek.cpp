/*
 * Rachunek.cpp
 *
 *  Created on: Apr 2, 2009
 *      Author: moux
 */

#include "moc_Rachunek.cpp"

// constructor
Rachunek::Rachunek(QWidget *parent): Faktura(parent) {

}

Rachunek::~Rachunek() {

}

void Rachunek::rachunekInit() {
	invoiceType = "Rachunek";
}


QString Rachunek::getInvoiceTypeAndSaveNr() {
	QString rachunek = "rachunek";
	sett().setValue("fvat", frNr->text());
	return rachunek;
}
