#pragma once

/*
 *  Created on: Apr 4, 2009
 *      Author: moux
 */

#include <QDate>
#include <QString>

class CustomPaymData
{
public:
	CustomPaymData();
	virtual ~CustomPaymData();

	QString payment1;
	QString payment2;
	QDate date1;
	QDate date2;
	double amount1;
	double amount2;
};
