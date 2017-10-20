/*
 * CustomPayment.cpp
 *
 *  Created on: Apr 4, 2009
 *      Author: moux
 */

#include "CustomPayment.h"
#include "CustomPaymData.h"
#include "Settings.h"

CustomPayment::CustomPayment(QWidget *parent) : QDialog(parent) {

<<<<<<< HEAD
=======
  qDebug() << __FILE__ << __LINE__ << __FUNCTION__;
>>>>>>> testing
  setupUi(this);
  // TODO Auto-generated constructor stub
  init();
}

CustomPayment::~CustomPayment() {

<<<<<<< HEAD
=======
  qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

>>>>>>> testing
  if (custPaymData != 0)
    custPaymData = 0;
  delete custPaymData;
}

void CustomPayment::init() {

<<<<<<< HEAD
  connect(okButton, SIGNAL(clicked()), this, SLOT(okClicked()));
  connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
  connect(amount1, SIGNAL(valueChanged(double)), this,
          SLOT(amount1Changed(double)));
  connect(amount2, SIGNAL(valueChanged(double)), this,
          SLOT(amount2Changed(double)));

  paymCombo1->insertItems(0, sett().value("payments").toString().split("|"));
  int removeLast = paymCombo1->count() - 1;
  paymCombo1->removeItem(removeLast);

  paymCombo2->insertItems(0, sett().value("payments").toString().split("|"));
  paymCombo2->removeItem(removeLast);

=======
  qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

  connect(okButton, SIGNAL(clicked()), this, SLOT(okClicked()));
  connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
  connect(amount1, SIGNAL(valueChanged(double)), this,
          SLOT(amount1Changed(double)));
  connect(amount2, SIGNAL(valueChanged(double)), this,
          SLOT(amount2Changed(double)));

  paymCombo1->insertItems(0, sett().value("payments").toString().split("|"));
  int removeLast = paymCombo1->count() - 1;
  paymCombo1->removeItem(removeLast);

  paymCombo2->insertItems(0, sett().value("payments").toString().split("|"));
  paymCombo2->removeItem(removeLast);

>>>>>>> testing
  liabDate1->setDate(QDate::currentDate());
  liabDate2->setDate(QDate::currentDate());
}

void CustomPayment::setInvoiceAmount(double a) {

<<<<<<< HEAD
=======
  qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

>>>>>>> testing
  invoiceAmount = a;
  amount1->setValue(invoiceAmount);
  amount1->setMaximum(invoiceAmount);
  amount2->setValue(0);
  amount2->setMaximum(invoiceAmount);
}

bool CustomPayment::validateForm() {

<<<<<<< HEAD
  if ((amount1->value() == 0) || (amount2->value() == 0)) {

    QMessageBox::information(
        0, "QFaktury", trUtf8("Jedna z kwot do zapłaty jest równa 0. Wybierz "
                              "inny sposób płatności lub zmień kwoty."));
    return false;
  }

  if (liabDate2->date() <= liabDate1->date()) {

    QMessageBox::information(0, "QFaktury",
                             trUtf8("Ostatnia data spłaty nie powinna być "
                                    "mniejsza lub równa dacie zaliczki."));
    return false;
  }

=======
  qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

  if ((amount1->value() == 0) || (amount2->value() == 0)) {

    QMessageBox::information(
        0, "QFaktury",
        trUtf8("Jedna z kwot do zapłaty jest równa 0. Wybierz "
               "inny sposób płatności lub zmień kwoty."));
    return false;
  }

  if (liabDate2->date() <= liabDate1->date()) {

    QMessageBox::information(0, "QFaktury",
                             trUtf8("Ostatnia data spłaty nie powinna być "
                                    "mniejsza lub równa dacie zaliczki."));
    return false;
  }

>>>>>>> testing
  return true;
}

// ---------- SLOT START ------------

void CustomPayment::amount1Changed(double) {
<<<<<<< HEAD

  qDebug() << __FUNCTION__;
=======

  qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

>>>>>>> testing
  disconnect(amount2, SIGNAL(valueChanged(double)), this,
             SLOT(amount2Changed(double)));
  amount2->setValue(invoiceAmount - amount1->value());
  connect(amount2, SIGNAL(valueChanged(double)), this,
          SLOT(amount2Changed(double)));
}

void CustomPayment::amount2Changed(double) {

<<<<<<< HEAD
  qDebug() << __FUNCTION__;
=======
  qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

>>>>>>> testing
  disconnect(amount1, SIGNAL(valueChanged(double)), this,
             SLOT(amount1Changed(double)));
  amount1->setValue(invoiceAmount - amount2->value());
  connect(amount1, SIGNAL(valueChanged(double)), this,
          SLOT(amount1Changed(double)));
}

void CustomPayment::okClicked() {

<<<<<<< HEAD
=======
  qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

>>>>>>> testing
  if (validateForm()) {

    custPaymData = new CustomPaymData();
    custPaymData->payment1 = paymCombo1->currentText();
    custPaymData->date1 = liabDate1->date();
    custPaymData->amount1 = amount1->value();

    custPaymData->payment2 = paymCombo2->currentText();
    custPaymData->date2 = liabDate2->date();
    custPaymData->amount2 = amount2->value();

    accept();
  }
}

// ---------- SLOT END ------------
