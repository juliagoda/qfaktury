/*
 * IDataLayer.h
 *
 *  Created on: Apr 18, 2009
 *      Author: moux
 */
#include "detector.h"
#if _pragma_once_support
#pragma once
#endif
#ifndef IDATALAYER_H_
#define IDATALAYER_H_

#include "BuyerData.h"
#include "InvoiceData.h"
#include "ProductData.h"
#include "warehousedata.h"

class IDataLayer {

public:
  IDataLayer(){};
  virtual ~IDataLayer(){};
  virtual void saveInvoiceData(){};
  virtual void readInvoiceData(){};
  virtual const QString getRet() const { return "|"; };
  virtual QString getRetWarehouse() const { return "|"; };
  virtual void checkAllSymbInFiles(){};
  virtual void checkAllSymbWareInFiles() {};
  virtual const QList<int> getAllSymbols() {
    QList<int> a;
    a.append(0);
    return a;
  };
  virtual const QList<int> getAllSymbolsWarehouse() {
    QList<int> a;
    a.append(0);
    return a;
  };

  virtual BuyerData buyersSelectData(QString, int) { return BuyerData(); };
  virtual QVector<BuyerData> buyersSelectAllData() {
    QVector<BuyerData> a;
    return a;
  };
  virtual bool buyersInsertData(BuyerData &, int) { return true; };
  virtual bool buyersUpdateData(BuyerData &, int, QString) { return true; };
  virtual bool buyersDeleteData(QString) { return true; };
  virtual QStringList buyersGetFirmList() { return QStringList(); };

  virtual ProductData productsSelectData(QString, int) {
    return ProductData();
  };
  virtual QVector<ProductData> productsSelectAllData() {
    QVector<ProductData> a;
    return a;
  };
  virtual bool productsInsertData(ProductData &, int) { return true; };
  virtual bool productsUpdateData(ProductData &, int, QString) { return true; };
  virtual bool productsDeleteData(QString) { return true; };

  virtual InvoiceData invoiceSelectData(QString, int) { return InvoiceData(); };
  virtual WarehouseData warehouseSelectData(QString, int) { return WarehouseData(); };
  virtual QVector<InvoiceData> invoiceSelectAllData(QDate, QDate) {
    QVector<InvoiceData> a;
    return a;
  };
  virtual QVector<WarehouseData> warehouseSelectAllData(QDate, QDate) {
    QVector<WarehouseData> a;
    return a;
  };
  virtual bool invoiceInsertData(InvoiceData &, int) { return true; };
  virtual bool warehouseInsertData(WarehouseData &, int) { return true; };
  virtual bool invoiceUpdateData(InvoiceData &, int, QString) { return true; };
  virtual bool warehouseUpdateData(WarehouseData &, int, QString) { return true; };
  virtual bool invoiceDeleteData(QString) { return true; };
  virtual bool warehouseDeleteData(QString) { return true; };

  virtual bool ifThereOldInvoice() { return true; };
  virtual void separateOldInvoices(){};
};

#endif /* IDATALAYER_H_ */
