/*
 * CustomPayment.h
 *
 *  Created on: Apr 4, 2009
 *      Author: moux
 */

#ifndef CUSTOMPAYMENT_H_
#define CUSTOMPAYMENT_H_
#include <QDialog>

#include "Settings.h"
#include "CustomPaymData.h"

#include "ui_CustomPaymentDialog.h"

class CustomPayment: public QDialog, public Ui::CustomPaymentDialog  {
Q_OBJECT
public:
	CustomPayment(QWidget* parent);
	virtual ~CustomPayment();
	CustomPaymData *custPaymData;
	void init();
	bool validateForm();
	void setInvoiceAmount(double a);
	double invoiceAmount;
public slots:
	void okClicked();
	void amount1Changed(double a);
	void amount2Changed(double a);
};

#endif /* CUSTOMPAYMENT_H_ */
