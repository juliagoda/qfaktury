#include "detector.h"
#if _pragma_once_support
#pragma once
#endif
#ifndef PRODUCTDATA_H_
#define PRODUCTDATA_H_

#include "Settings.h"

/* Class used in the Products list
 *
 */

// class for holding data about goods/services. One instance -> one type of
// service/good
class ProductData {

public:
  ProductData() {
    id = 0;
    name = "";
    code = "";
    pkwiu = "";
    quantity = 0;
    quanType = "";
    discount = 0;
    price = 0;
    nett = 0;
    vat = 0;
    gross = 0;
    curr = "";
    requiredAmount = 0;
    givedOutAmount = 0;
  }

  ProductData(QString c1, QString c2, QString c3) {
    code = c1;
    if (code == "")
      code = "-";
    curr = c2;
    if (curr == "")
      curr = "-";
    pkwiu = c3;
    if (pkwiu == "")
      pkwiu = "-";
  }

  ProductData(int inId, QString inName, QString inCode, QString inPkwiu,
              double inQuantity, QString inQuanType, double inDiscount,
              double inPrice, double inNett, int inVat, double inGross,
              QString inCurr, int reqAmount, int givAmount) {

    id = inId;
    name = inName;
    code = inCode;
    pkwiu = inPkwiu;
    quantity = inQuantity;
    quanType = inQuanType;
    discount = inDiscount;
    price = inPrice;
    nett = inNett;
    vat = inVat;
    gross = inGross;
    curr = inCurr;
    requiredAmount = reqAmount;
    givedOutAmount = givAmount;

  }

  //*************************************************** getters
  //***************************************************
  int getId() const { return id; }

  QString getName() const { return name; }

  QString getCode() const { return code; }

  QString getPkwiu() const { return pkwiu; }

  double getQuantity() const { return quantity; }

  QString getQuantityType() const { return quanType; }

  double getDiscount() const { return discount; }

  double getPrice() const { return price; }

  double getNett() const { return nett; }

  int getVat() const { return vat; }

  double getGross() const { return gross; }

  QString getCurr() const { return curr; }

  //*************************************************** setters
  //***************************************************
  void setId(QString inId) { id = inId.toInt(); }

  void setName(QString inName) { name = inName; }

  void setCode(QString inCode) { code = inCode; }

  void setPkwiu(QString inPkwiu) { pkwiu = inPkwiu; }

  void setQuantity(QString quan) { quantity = quan.toInt(); }

  void setQuanType(QString qType) { quanType = qType; }

  void setDiscount(QString disc) { discount = disc.toInt(); }

  void setPrice(QString prc) { price = sett().stringToDouble(prc); }

  void setNett(QString net) { nett = sett().stringToDouble(net); }

  void setVat(QString vt) { vat = vt.toInt(); }

  void setGross(QString gr) {
    double decimalPointsGross = gr.right(2).toInt() * 0.01;
    gross = sett().stringToDouble(gr);
    gross += decimalPointsGross;
  }

  void setCurr(QString cr) { curr = cr; }

  void setRequiredAmount(QString reqAmount) {
    requiredAmount = reqAmount.toInt();
  }

  void setGivedOutAmount(QString givAmount) {
    givedOutAmount = givAmount.toInt();
  }

  // ********************************* All TO STRING ********************

  QString toString() {
    QString str;
    QTextStream ret(&str);
    ret << "id: " << id << "\n"
        << "name: " << name << "\n"
        << "code: " << code << "\n"
        << "pkwiu: " << pkwiu << "\n"
        << "quantity: " << quantity << "\n"
        << "quanType: " << quanType << "\n"
        << "discount: " << discount << "\n"
        << "price: " << price << "\n"
        << "nett: " << nett << "\n"
        << "vat: " << vat << "\n"
        << "gross: " << gross << "\n"
        << "curr: " << curr << "\n"
        << "requiredAmount: " << requiredAmount << "\n"
        << "givedOutAmount: " << givedOutAmount;
    return "ProductData: [" + str + "]";
  }

  int id;
  int vat;
  int lastProdId;
  QString name;
  QString code;
  QString pkwiu;
  QString quanType;
  QString curr;
  QString desc;
  QString type;
  double quantity;
  double discount;
  double price;
  double nett;
  double gross;
  QMap<int, double> prices;
  int requiredAmount;
  int givedOutAmount;
};

#endif
