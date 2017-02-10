/*
 * Rachunek.h
 *
 *  Created on: Apr 2, 2009
 *      Author: moux
 */

#ifndef BILL_H_
#define BILL_H_

#include <QDialog>
#include "ui_Invoice.h"
#include "Invoice.h"

#include "ConvertAmount.h"
#include "Settings.h"


class Bill: public Invoice {

Q_OBJECT

public:

    Bill(QWidget *parent, IDataLayer *dl, QString in_form = QString());


public slots:

    void billInit();


protected:

	QString getInvoiceTypeAndSaveNr();
};

#endif /* BILL_H_ */
