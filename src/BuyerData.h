/*
 * BuyerData.h
 *
 *  Created on: Apr 18, 2009
 *      Author: moux
 */

#ifndef BUYERDATA_H
#define BUYERDATA_H_

#include <QString>

class BuyerData {

public:

    BuyerData();
    virtual ~BuyerData();
	QString name;
	QString place;
	QString code;
	QString address;
	QString tic;
	QString account;
	QString phone;
	QString email;
	QString www;
    QString fax;
    QString krs;
    QString bank;
    QString swift;
	QString type;

};

#endif /* BUYERDATA_H_ */
