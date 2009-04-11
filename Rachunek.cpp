/*
 * Rachunek.cpp
 *
 *  Created on: Apr 2, 2009
 *      Author: moux
 */

#include "moc_Rachunek.cpp"
#include "Const.h"

// constructor
Rachunek::Rachunek(QWidget *parent): Faktura(parent) {

}

Rachunek::~Rachunek() {

}

void Rachunek::rachunekInit() {
	invoiceType = s_BILL;
}


QString Rachunek::getInvoiceTypeAndSaveNr() {
	QString rachunek = "rachunek";
	sett().setValue("fvat", frNr->text());
	return rachunek;
}
