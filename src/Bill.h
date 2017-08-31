/*
 * Rachunek.h
 *
 *  Created on: Apr 2, 2009
 *      Author: moux
 */

#include "detector.h"
#if _pragma_once_support
#pragma once
#endif
#ifndef BILL_H_
#define BILL_H_

#include "Invoice.h"

class Bill : public Invoice {

  Q_OBJECT

public:
  Bill(QWidget *parent, IDataLayer *dl, QString in_form = QString());

public slots:

  void billInit();

protected:
  QString getInvoiceTypeAndSaveNr();
};

#endif /* BILL_H_ */
