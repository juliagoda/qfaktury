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
	FakturaBrutto(QWidget *parent);
	virtual ~FakturaBrutto();
public slots:
	void fakturaBruttoInit();
	void addTow();
private:
	QString getInvoiceTypeAndSaveNr();
	// virtual double calcPrice(double quant, double price);
	virtual double calcVATPrice(double nett, double gross);

};


#endif /* FAKTURABRUTTO_H_ */
