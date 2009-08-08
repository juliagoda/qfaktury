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
#include "CustomPaymData.h"


class InvoiceData {
public:
	QString customer; // kontrahent
	QMap<int, ProductData> products;
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
	int currencyTypeId;
	int discount;
	CustomPaymData custPaym;
	QDate issueDate;
	int invoiceType; // 1 - FVAT, 2 - FPro, 3 - corr, 4 - FBrutto

	/**
	 *  Return invoice type
	 */
	QString getInvoiceTypeAndSaveNr(int invoiceType) {
		QString ret = "FVAT";

		switch (invoiceType) {
		case 1: ret = QObject::trUtf8("FVAT");
				break;
		case 2: ret = QObject::trUtf8("FPro");
				break;
		case 3: ret = QObject::trUtf8("korekta");
				break;
		case 4: ret = QObject::trUtf8("FBrutto");
				break;
		case 5: ret = QObject::trUtf8("kbrutto");
				break;
		case 6: ret = QObject::trUtf8("rachunek");
				break;
		default: ret = QObject::trUtf8("FVAT");
				break;
		}

		return ret;
	}
};
#endif
