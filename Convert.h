/*
 * Convert.h
 *
 *  Created on: Mar 16, 2009
 *      Author: tpielech
 */

#ifndef CONVERT_H_
#define CONVERT_H_

#include <QObject>
#include "Settings.h"

class Convert {
public:
	Convert();
	virtual ~Convert();
	QString convertPL(QString input, QString waluta);
};

#endif /* CONVERT_H_ */
