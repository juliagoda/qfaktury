/*
 * KorektaBrutto.h
 *
 *  Created on: Apr 3, 2009
 *      Author: moux
 */

#ifndef CORRECTGROSS_H_
#define CORRECTGROSS_H_

#include "Correction.h"

class CorrectGross: public Correction {

Q_OBJECT

public:

    CorrectGross(QWidget *parent, IDataLayer *dl, QString in_form = QString(), bool edMode = false);
    void addGoods();


protected:

	void calculateOneDiscount(int i);
	QString getInvoiceTypeAndSaveNr();

};


#endif /* CorrectGross_H_ */
