/*
 * CustomPaymData.h
 *
 *  Created on: Apr 4, 2009
 *      Author: moux
 */

#ifndef CUSTOMPAYMDATA_H_
#define CUSTOMPAYMDATA_H_

#include <QString>
#include <QDate>

class CustomPaymData {

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

#endif /* CUSTOMPAYMDATA_H_ */
