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
	QString convertPL(QString input, QString waluta);
	void convertTest();
    QString& descAmount(QString&,QString,QString = QString(),QString = QString(),QString = QString());
    const QStringList staList() const;
    const QStringList esciaList() const;
    const QStringList nascieList() const;
    const QStringList jedynkiList() const;

};

#endif /* CONVERTAMOUNT_H_ */
