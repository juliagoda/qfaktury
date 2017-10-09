#include "detector.h"
#if _pragma_once_support
#pragma once
#endif
#ifndef INVOICERR_H
#define INVOICERR_H

#include "Invoice.h"

// class for creating and updating Invoice VAT RR
class InvoiceRR : public Invoice {
public:
  InvoiceRR(QWidget *parent, IDataLayer *dl, QString in_form = QString());
  ~InvoiceRR();

public slots:
  void invoiceRRInit();
  void makeInvoice();

protected:
  QString getInvoiceTypeAndSaveNr();
  void getData(InvoiceData invData);
  void setData(InvoiceData &invData);

private:
  QCheckBox *ifpaysVAT;
};

#endif // INVOICERR_H
