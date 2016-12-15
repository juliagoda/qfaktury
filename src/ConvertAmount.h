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
    QStringList staList() const;
    QStringList esciaList() const;
    QStringList nascieList() const;
    QStringList jedynkiList() const;

};

#endif /* CONVERTAMOUNT_H_ */
