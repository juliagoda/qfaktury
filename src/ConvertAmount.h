#pragma once

/*
 *  Created on: Mar 16, 2009
 *      Author: tpielech
 */

#include <QString>

class ConvertAmount final
{
public:
	QString convertPL(QString input, QString currency) const;
	QString &descAmount(
		QString &countMoney,
		QString partMoney,
		QString ifOne = QString(),
		QString ifMore = QString(),
		QString ifBetween = QString()) const;
	QStringList hundsList() const;
	QStringList endsHundList() const;
	QStringList endsTensList() const;
	QStringList simpleNumbList() const;
};
