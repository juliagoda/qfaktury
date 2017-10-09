#include "detector.h"
#if _pragma_once_support
#pragma once
#endif
#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include "Invoice.h"
#include "WarehouseData.h"

// base class for created/updated warehouse documents. Form is used from invoice
// class
class Warehouse : public Invoice {

public:
  Warehouse(QWidget *parent, IDataLayer *dl, QString in_form);
  virtual ~Warehouse();

  virtual void readWarehouseData(QString fraFile);
  virtual void setData(WarehouseData &invData);
  virtual void getData(WarehouseData invData);
  virtual void readData(QString fraFile);

protected:
private:
  WarehouseData *wareData;

private slots:

public slots:
  virtual bool saveInvoice();
  void backBtnClick();
  void canQuit();
};

#endif // WAREHOUSE_H
