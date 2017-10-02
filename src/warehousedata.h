#if _pragma_once_support
#pragma once
#endif
#ifndef WAREHOUSEDATA_H
#define WAREHOUSEDATA_H

#include "ProductData.h"
#include "documentdata.h"

class WarehouseData : public DocumentData {

public:
  QString getCustomer() {return customer;}
  QString customer; // buyer
  QMap<int, ProductData> products;
  QDate liabDate;
  QDate sellingDate;
  QDate productDate;
  QDate duplDate;
  QString invNr;
  QString paymentType;
  QString additText;

  QString type;
  QString id; // in case of xml, here goes filename
  bool ifInvForDelNote; // for delivery note (WZ)

  QString custStreet;
  QString custTic;
  QString custCity;
  QString custName;
  QDate issueDate;
  int invoiceType; // 9 - WZ

  /**
   *  Return invoice type
   */

  QString getInvoiceTypeAndSaveNr(int invoiceType) {
    QString ret = "WZ";

    switch (invoiceType) {
    case 9:
      ret = QObject::trUtf8("WZ");
      break;
    default:
      ret = QObject::trUtf8("WZ");
      break;
    }

    return ret;
  }
};

#endif
