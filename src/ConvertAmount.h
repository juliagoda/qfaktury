/*
 * ConvertAmount.h
 *
 *  Created on: Mar 16, 2009
 *      Author: tpielech
 */

#ifndef CONVERTAMOUNT_H_
#define CONVERTAMOUNT_H_

#include <QString>
#include "Settings.h"

class ConvertAmount {

public:

	ConvertAmount();
	~ConvertAmount();
    QString convertPL(QString input, QString currency);
	void convertTest();
    QString& descAmount(QString&,QString,QString = QString(),QString = QString(),QString = QString());
    const QStringList hundsList() const;
    const QStringList endsHundList() const;
    const QStringList endsTensList() const;
    const QStringList simpleNumbList() const;

};

#endif /* CONVERTAMOUNT_H_ */
