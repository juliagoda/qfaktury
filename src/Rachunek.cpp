/*
 * Rachunek.cpp
 *
 *  Created on: Apr 2, 2009
 *      Author: moux
 */

#include "moc_Rachunek.cpp"
#include "Rachunek.h"
#include "Const.h"

// constructor
Rachunek::Rachunek(QWidget *parent, IDataLayer *dl, QString in_form): Faktura(parent, dl, in_form) {

}

void Rachunek::rachunekInit() {
	invoiceType = s_BILL;
}


QString Rachunek::getInvoiceTypeAndSaveNr() {

	QString rachunek = "rachunek";
	sett().setValue("fvat", frNr->text());
	return rachunek;
}
