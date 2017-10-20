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
    : Invoice(parent, dl, in_form) {
<<<<<<< HEAD
    qDebug() << __FILE__ << __LINE__ << __FUNCTION__;
}

// destructor
Bill::~Bill() {
    qDebug() << __FILE__ << __LINE__ << __FUNCTION__;
}

// on start type of document is changed
void Bill::billInit() {
    qDebug() << __FILE__ << __LINE__ << __FUNCTION__;
    invoiceType = s_BILL;
=======
  qDebug() << __FILE__ << __LINE__ << __FUNCTION__;
}

// destructor
Bill::~Bill() { qDebug() << __FILE__ << __LINE__ << __FUNCTION__; }

// on start type of document is changed
void Bill::billInit() {
  qDebug() << __FILE__ << __LINE__ << __FUNCTION__;
  invoiceType = s_BILL;
>>>>>>> testing
}

// outputs type of document
QString Bill::getInvoiceTypeAndSaveNr() {

<<<<<<< HEAD
    qDebug() << __FILE__ << __LINE__ << __FUNCTION__;
=======
  qDebug() << __FILE__ << __LINE__ << __FUNCTION__;
>>>>>>> testing

  QString bill = "rachunek";
  sett().setValue("fvat", invNr->text());
  return bill;
}
