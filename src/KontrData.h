/*
 * KontrData.h
 *
 *  Created on: Apr 18, 2009
 *      Author: moux
 */

#ifndef KONTRDATA_H_
#define KONTRDATA_H_
#include <QString>

class KontrData {
public:
	KontrData();
	virtual ~KontrData();

	// Getters and Setters??
	QString name;
	QString place;
	QString code;
	QString address;
	QString tic;
	QString account;
	QString phone;
	QString email;
	QString www;
};

#endif /* KONTRDATA_H_ */
