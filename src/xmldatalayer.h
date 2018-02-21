/*
 * XmlDataLayer.h
 *
 *  Created on: Apr 18, 2009
 *      Author: moux
 */
#include "detector.h"
#if _pragma_once_support
#pragma once
#endif
#ifndef XMLDATALAYER_H_
#define XMLDATALAYER_H_

#include <QtXml/qdom.h>

#include "idatalayer.h"
#include "documentdata.h"
#include "warehousedata.h"

// class for creating, updating and removing xml files with goods/services,
// invoices, warehouse documents and buyers informations
class XmlDataLayer : public IDataLayer {

public:
  XmlDataLayer();
  virtual ~XmlDataLayer();

  // methods used for accessing customers
  virtual BuyerData buyersSelectData(QString name, int type);
  virtual QVector<BuyerData> buyersSelectAllData();
  virtual bool buyersInsertData(BuyerData &buyerData, int type);
  virtual bool buyersUpdateData(BuyerData &buyerData, int type, QString name);
  virtual bool buyersDeleteData(QString name);
  virtual QStringList buyersGetFirmList();

  virtual ProductData productsSelectData(QString name, int type);
  virtual QVector<ProductData> productsSelectAllData();
  virtual bool productsInsertData(ProductData &prodData, int type);
  virtual bool productsUpdateData(ProductData &prodData, int type,
                                  QString name);
  virtual bool productsDeleteData(QString name);

  virtual InvoiceData invoiceSelectData(QString name, int type, bool onlyCheck = false);
  virtual WarehouseData warehouseSelectData(QString name, int type, bool onlyCheck = false);
  virtual QVector<InvoiceData> invoiceSelectAllData(QDate start, QDate end, bool onlyCheck = false);
  virtual QVector<WarehouseData> warehouseSelectAllData(QDate start, QDate end);
  virtual bool invoiceInsertData(InvoiceData &invData, int type);
  virtual bool warehouseInsertData(WarehouseData &invData, int type);
  virtual bool invoiceUpdateData(InvoiceData &invData, int type, QString name);
  virtual bool warehouseUpdateData(WarehouseData &invData, int type,
                                   QString name);
  virtual bool invoiceDeleteData(QString name);
  virtual bool warehouseDeleteData(QString name);

  virtual QString const getRet() const;
  virtual QString getRetWarehouse() const;
  virtual void checkAllSymbInFiles();
  virtual void checkAllSymbWareInFiles();
  virtual QList<int> const getAllSymbols();
  virtual QList<int> const getAllSymbolsWarehouse();
  virtual bool ifThereOldDocuments(QString docname, QString docdir, QStringList filters);
  virtual void separateOldDocuments(QString path);

  virtual void saveInvoiceData(){};
  virtual void readInvoiceData(){};

private:
  void buyersElemToData(BuyerData &o_buyerData, QDomElement i_element);
  void buyersDataToElem(BuyerData &i_buyerData, QDomElement &o_element);

  void productsElemToData(ProductData &o_prodData, QDomElement i_element);
  void productsDataToElem(ProductData &i_prodData, QDomElement &o_element);

  void invoiceSellerDataToElem(DocumentData &i_invData, QDomElement &o_element);
  void invoiceSellerElemToData(InvoiceData &o_invData, QDomElement i_element);
  void invoiceBuyerDataToElem(DocumentData &i_invData, QDomElement &o_element);
  void invoiceBuyerElemToData(InvoiceData &o_invData, QDomElement i_element);
  void invoiceProdDataToElem(const ProductData &i_prodData,
                             QDomElement &o_element, int currentRow);
  void warehouseProdDataToElem(const ProductData &i_prodData,
                               QDomElement &o_element, int type);
  void invoiceProdElemToData(InvoiceData &o_invData, QDomElement i_element);

  bool nameFilter(QString nameToCheck, QDate start, QDate end, QString docName,
                  QString path);
  bool ifPersonNodeExists(QDomElement root);
  void addSectionPerson(bool checkedRoot);

  QString ret;
  QString retWarehouse;
  QList<int> allSymbols;
  QList<int> allSymbolsWarehouse;
  QStringList yearsList;
  QMultiHash<QString, QString> categorizedFiles;
};

#endif /* XMLDATALAYER_H_ */
