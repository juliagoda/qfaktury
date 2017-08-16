#pragma once

/*
 *  Created on: Apr 2, 2009
 *      Author: TPIELECH
 */

#include "Invoice.h"

class InvoiceGross : public Invoice
{
	Q_OBJECT

public:
	InvoiceGross(QWidget *parent, IDataLayer *dl, QString in_form = QString());

	void calculateOneDiscount(int i) override;

public slots:
	void invoiceGrossInit();
	void addGoods() override;

protected:
	QString getInvoiceTypeAndSaveNr() override;
};
