/*
 * FakturaBrutto.h
 *
 *  Created on: Apr 2, 2009
 *      Author: TPIELECH
 */
#include "detector.h"
#if _pragma_once_support
#pragma once
#endif
#ifndef INVOICEGROSS_H_
#define INVOICEGROSS_H_

#include "Invoice.h"

class InvoiceGross : public Invoice {

  Q_OBJECT

public:
  InvoiceGross(QWidget *parent, IDataLayer *dl, QString in_form = QString());

public slots:

  void invoiceGrossInit();
  void addGoods();

protected:
  void calculateOneDiscount(int i);
  QString getInvoiceTypeAndSaveNr();
};

#endif /* FAKTURABRUTTO_H_ */
