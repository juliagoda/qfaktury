/*
 * CustomPayment.h
 *
 *  Created on: Apr 4, 2009
 *      Author: moux
 */

#include "detector.h"
#if _pragma_once_support
#pragma once
#endif
#ifndef CUSTOMPAYMENT_H_
#define CUSTOMPAYMENT_H_

#include "ui_CustomPaymentDialog.h"

class CustomPaymData;

// class for splitting cost sum with GUI, when prepayment method is checked
class CustomPayment : public QDialog, public Ui::CustomPaymentDialog {

  Q_OBJECT

public:
  CustomPayment(QWidget *parent);
  virtual ~CustomPayment();

  bool validateForm();
  void setInvoiceAmount(double a);
  void init();

  CustomPaymData *custPaymData;

public slots:

  void okClicked();
  void amount1Changed(double a);
  void amount2Changed(double a);

private:
  double invoiceAmount;
};

#endif /* CUSTOMPAYMENT_H_ */
