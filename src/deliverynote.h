#include "detector.h"
#if _pragma_once_support
#pragma once
#endif
#ifndef DELIVERYNOTE_H
#define DELIVERYNOTE_H

#include "Invoice.h"


class DeliveryNote : public Invoice {

public:
  DeliveryNote(QWidget *parent, IDataLayer *dl, QString in_form);
  virtual ~DeliveryNote();


protected:
  void makeInvoiceSummAll();
  void makeInvoiceSumm();
  void makeInvoiceProductsHeadar();
  void makeInvoiceProducts(); // changed invoice form to delivery note form of products table
  void makeInvoiceFooter();
  void setData(InvoiceData &invData);


private:
  bool ifcreateInv;


private slots:


public slots:
  bool saveInvoice();


};

#endif // DELIVERYNOTE_H
