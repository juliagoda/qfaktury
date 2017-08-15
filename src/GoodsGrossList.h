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
	const QString getRetValGoodsBr();

public slots:

	void calcNet();
	void doAccept();
	QString getPriceOfCurrent();

private:
	QString ret;
	QString selectedItem;
};
