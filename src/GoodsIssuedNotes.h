#include "detector.h"
#if _pragma_once_support
#pragma once
#endif
#ifndef GOODSISSUEDNOTES_H
#define GOODSISSUEDNOTES_H

#include "Warehouse.h"
#include "warehousedata.h"

class QFormLayout;
class QLineEdit;
class QDateTimeEdit;


class GoodsIssuedNotes : public Warehouse {

public:
  GoodsIssuedNotes(QWidget *parent, IDataLayer *dl, QString in_form);
  virtual ~GoodsIssuedNotes();

  void readWarehouseData(QString fraFile);
  void setData(WarehouseData &invData);
  void getData(WarehouseData invData);
  void readData(QString fraFile);


protected:
  void makeInvoiceHeadar(bool, bool breakPage, bool original);
  void makeInvoiceBody();
  void makeInvoiceSummAll();
  void makeInvoiceSumm();
  void makeInvoiceProductsHeadar();
  void makeInvoiceProducts(); // changed invoice form to delivery note form of products table
  void makeInvoiceFooter();
  void setData(InvoiceData &invData);



private:
  QFormLayout* formLayout;
  QWidget* widgetsRW;
  QLineEdit* lineEdit1;
  QLineEdit* lineEdit2;
  QLineEdit* lineEdit3;
  QDateTimeEdit* dateTimeEdit1;
  QDateTimeEdit* dateTimeEdit2;
  WarehouseData *wareData;


private slots:


public slots:
  bool saveInvoice();


};
#endif // GOODSISSUEDNOTES_H
