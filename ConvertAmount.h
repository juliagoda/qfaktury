/*
 * ConvertAmount.h
 *
 *  Created on: Mar 16, 2009
 *      Author: tpielech
 */

#ifndef CONVERTAMOUNT_H_
#define CONVERTAMOUNT_H_

#include <QObject>
#include <QString>
#include "Settings.h"

class ConvertAmount {
public:
	ConvertAmount();
	~ConvertAmount();
	QString convertPL(QString input, QString waluta);
	void convertTest();
};

#endif /* CONVERTAMOUNT_H_ */
