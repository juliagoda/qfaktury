#if _pragma_once_support
#pragma once
#endif
#ifndef WAREHOUSEDATA_H
#define WAREHOUSE_H

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
  bool ifInvForDelNote;

  QString custStreet;
  QString custTic;
  QString custCity;
  QString custName;
  QDate issueDate;
  int invoiceType; // 1 - FVAT, 2 - FPro, 3 - corr, 4 - FBrutto

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
