/*
 * InvoiceData.h
 *
 *  Created on: Mar 12, 2009
 *      Author: moux
 */
#include "detector.h"
#if _pragma_once_support
#pragma once
#endif
#ifndef INVOICEDATA_H
#define INVOICEDATA_H

#include "custompaymdata.h"
#include "productdata.h"
#include "documentdata.h"

// class for holding data about invoices. One instance -> one invoice.
class InvoiceData : public DocumentData {

public:
    InvoiceData(){}
    virtual ~InvoiceData(){}

  QString getCustomer() { return customer; }
  QString customer; // buyer
  QMap<int, ProductData> products;
  QDate liabDate;
  QDate sellingDate;
  QDate productDate;
  QDate duplDate;
  QString invNr;
  QString paymentType;
  QString currencyType;
  QString additText;
  QString payment1;
  QDate date1;
  double amount1;

  QString payment2;
  QDate date2;
  double amount2;

  QString type;
  QString id; // in case of xml, here goes filename
  bool ifpVAT;
  bool ifInvForDelNote;

  QString custStreet;
  QString custTic;
  QString custCity;
  QString custName;
  QString sellerAddress;
  int currencyTypeId;
  int discount;
  CustomPaymData custPaym;
  QDate issueDate;
  int invoiceType; // 1 - FVAT, 2 - FPro, 3 - corr, 4 - FBrutto

  /**
   *  Return invoice type
   */

  QString getInvoiceTypeAndSaveNr(int invoiceType) {
    QString ret = "FVAT";

    switch (invoiceType) {
    case 1:
      ret = QObject::trUtf8("FVAT");
      break;
    case 2:
      ret = QObject::trUtf8("FPro");
      break;
    case 3:
      ret = QObject::trUtf8("korekta");
      break;
    case 4:
      ret = QObject::trUtf8("FBrutto");
      break;
    case 5:
      ret = QObject::trUtf8("kbrutto");
      break;
    case 6:
      ret = QObject::trUtf8("rachunek");
      break;
    case 7:
      ret = QObject::trUtf8("duplikat");
      break;
    case 8:
      ret = QObject::trUtf8("RR");
      break;
    case 9:
      ret = QObject::trUtf8("FVAT");
      break;
    case 10:
      ret = QObject::trUtf8("RW");
      break;
    default:
      ret = QObject::trUtf8("FVAT");
      break;
    }

    return ret;
  }

  int getInvoiceNameReturnType(QString invoiceType) {

    if (invoiceType == QObject::trUtf8("FVAT")) return 1;
    else if (invoiceType == QObject::trUtf8("FPro")) return 2;
    else if (invoiceType == QObject::trUtf8("korekta")) return 3;
    else if (invoiceType == QObject::trUtf8("FBrutto")) return 4;
    else if (invoiceType == QObject::trUtf8("kbrutto")) return 5;
    else if (invoiceType == QObject::trUtf8("rachunek")) return 6;
    else if (invoiceType == QObject::trUtf8("duplikat")) return 7;
    else if (invoiceType == QObject::trUtf8("RR")) return 8;
    else if (invoiceType == QObject::trUtf8("FVAT")) return 9;
    else if (invoiceType == QObject::trUtf8("RW")) return 10;
    else return 1;

    return 1;

}

};

#endif
