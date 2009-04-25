/*
 * InvoiceData.h
 *
 *  Created on: Mar 12, 2009
 *      Author: moux
 */

#ifndef InvoiceData_H
#define InvoiceData_H

#include <QString>
#include <QDate>
#include <QMap>
#include "ProductData.h"

class InvoiceData {
public:
	QString customer; // kontrahent
	QMap<int, ProductData*> products;
	QDate liabDate;
	QDate sellingDate;
	QDate productDate;
	QString frNr;
	QString paymentType;
	QString currencyType;
	QString additText;

	QString type;
	QString id; // in case of xml, here goes filename

	QString custStreet;
	QString custTic;
	QString custCity;
	QString custName;
};
#endif
