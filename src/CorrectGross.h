#pragma once

/*
 * KorektaBrutto.h
 *
 *  Created on: Apr 3, 2009
 *      Author: moux
 */

#include "Correction.h"

class CorrectGross : public Correction
{
	Q_OBJECT

public:
	CorrectGross(QWidget *parent, IDataLayer *dl, QString in_form = QString(), bool edMode = false);

	void calculateOneDiscount(int i) override;

public slots:
	void addGoods() override;

protected:
	QString getInvoiceTypeAndSaveNr() override;
};
