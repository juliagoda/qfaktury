#pragma once

/*
 *  Created on: Apr 3, 2009
 *      Author: TPIELECH
 */

#include "GoodsList.h"

class GoodsGrossList : public GoodsList
{
	Q_OBJECT

public:
	GoodsGrossList(QWidget *parent);
	QString getRetValGoodsBr() const;

public slots:
	void calcNet();
	void doAccept();
	QString getPriceOfCurrent() const;

private:
	QString ret;
	QString selectedItem;
};
