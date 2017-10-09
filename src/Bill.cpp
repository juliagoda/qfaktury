/*
 * Rachunek.cpp
 *
 *  Created on: Apr 2, 2009
 *      Author: moux
 */

#include "Bill.h"
#include "Const.h"

// constructor
Bill::Bill(QWidget *parent, IDataLayer *dl, QString in_form)
    : Invoice(parent, dl, in_form) {}

// destructor
Bill::~Bill() {}

// on start type of document is changed
void Bill::billInit() { invoiceType = s_BILL; }

// outputs type of document
QString Bill::getInvoiceTypeAndSaveNr() {

  QString bill = "rachunek";
  sett().setValue("fvat", invNr->text());
  return bill;
}
