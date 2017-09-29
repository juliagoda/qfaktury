#include "detector.h"
#if _pragma_once_support
#pragma once
#endif
#ifndef DELIVERYNOTE_H
#define DELIVERYNOTE_H

#include "Invoice.h"
#include "warehousedata.h"


class DeliveryNote : public Invoice {

public:
  DeliveryNote(QWidget *parent, IDataLayer *dl, QString in_form);
  virtual ~DeliveryNote();

  void readWarehouseData(QString fraFile);
  void setData(WarehouseData &invData);
  void getData(WarehouseData invData);
  void readData(QString fraFile);


protected:
  void makeInvoiceSummAll();
  void makeInvoiceSumm();
  void makeInvoiceProductsHeadar();
  void makeInvoiceProducts(); // changed invoice form to delivery note form of products table
  void makeInvoiceFooter();
  void setData(InvoiceData &invData);



private:
  bool ifcreateInv;
  WarehouseData *wareData;


private slots:


public slots:
  bool saveInvoice();
  void backBtnClick();
  void canQuit();


};

#endif // DELIVERYNOTE_H
