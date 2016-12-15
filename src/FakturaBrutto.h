/*
 * FakturaBrutto.h
 *
 *  Created on: Apr 2, 2009
 *      Author: TPIELECH
 */

#ifndef FAKTURABRUTTO_H_
#define FAKTURABRUTTO_H_

#include <QDialog>
#include <QDateEdit>

#include "ui_Faktura.h"
#include "Faktura.h"

#include "ConvertAmount.h"
#include "Settings.h"


class FakturaBrutto: public Faktura {

Q_OBJECT

public:

    FakturaBrutto(QWidget *parent, IDataLayer *dl, QString in_form = QString());


public slots:

	void fakturaBruttoInit();
    void addTow();


protected:

	void calculateOneDiscount(int i);
	QString getInvoiceTypeAndSaveNr();

};


#endif /* FAKTURABRUTTO_H_ */
