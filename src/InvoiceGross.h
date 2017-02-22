/*
 * FakturaBrutto.h
 *
 *  Created on: Apr 2, 2009
 *      Author: TPIELECH
 */

#ifndef INVOICEGROSS_H_
#define INVOICEGROSS_H_

#include <QDialog>
#include <QDateEdit>

#include "ui_Invoice.h"
#include "Invoice.h"

#include "ConvertAmount.h"
#include "Settings.h"


class InvoiceGross: public Invoice {

Q_OBJECT

public:

    InvoiceGross(QWidget *parent, IDataLayer *dl, QString in_form = QString());


public slots:

    void invoiceGrossInit();
    void addGoods();


protected:

	void calculateOneDiscount(int i);
	QString getInvoiceTypeAndSaveNr();

};


#endif /* FAKTURABRUTTO_H_ */