#pragma once

/*
 * Rachunek.h
 *
 *  Created on: Apr 2, 2009
 *      Author: moux
 */

#include "Invoice.h"

class IDataLayer;

class Bill : public Invoice
{
	Q_OBJECT

public:
	Bill(QWidget *parent, IDataLayer *dl, QString in_form = QString());

public slots:
	void billInit();

protected:
	QString getInvoiceTypeAndSaveNr() override;
};
