/*
 * Rachunek.h
 *
 *  Created on: Apr 2, 2009
 *      Author: moux
 */

#ifndef RACHUNEK_H_
#define RACHUNEK_H_

#include <QDialog>
#include "ui_Faktura.h"
#include "Faktura.h"

#include "ConvertAmount.h"
#include "Settings.h"


class Rachunek: public Faktura {

Q_OBJECT

public:

    Rachunek(QWidget *parent, IDataLayer *dl, QString in_form = QString());


public slots:

	void rachunekInit();


protected:

	QString getInvoiceTypeAndSaveNr();
};

#endif /* RACHUNEK_H_ */
