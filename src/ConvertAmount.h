#pragma once

/*
 * ConvertAmount.h
 *
 *  Created on: Mar 16, 2009
 *      Author: tpielech
 */

#include <QString>

class ConvertAmount
{
public:
	ConvertAmount();
	~ConvertAmount();

	void convertTest();
	QString convertPL(QString input, QString currency);
	QString &descAmount(
		QString &countMoney,
		QString partMoney,
		QString ifOne = QString(),
		QString ifMore = QString(),
		QString ifBetween = QString());
	const QStringList hundsList();
	const QStringList endsHundList();
	const QStringList endsTensList();
	const QStringList simpleNumbList();
};
