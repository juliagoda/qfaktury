#pragma once

/*
 *  Created on: Mar 12, 2009
 *      Author: moux
 */

#include "CustomPaymData.h"
#include "ProductData.h"

class InvoiceData
{
public:
	QString customer; // buyer
	QMap<int, ProductData> products;
	QDate liabDate;
	QDate sellingDate;
	QDate productDate;
	QDate duplDate;
	QString invNr;
	QString paymentType;
	QString currencyType;
	QString additText;
	QString payment1;
	QDate date1;
	double amount1;

	QString payment2;
	QDate date2;
	double amount2;

	QString type;
	QString id; // in case of xml, here goes filename
	bool ifpVAT;

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

	QString getInvoiceTypeAndSaveNr(int invoiceType)
	{
		QString ret = "FVAT";

		switch (invoiceType)
		{
		case 1:
			ret = QObject::trUtf8("FVAT");
			break;
		case 2:
			ret = QObject::trUtf8("FPro");
			break;
		case 3:
			ret = QObject::trUtf8("korekta");
			break;
		case 4:
			ret = QObject::trUtf8("FBrutto");
			break;
		case 5:
			ret = QObject::trUtf8("kbrutto");
			break;
		case 6:
			ret = QObject::trUtf8("rachunek");
			break;
		case 7:
			ret = QObject::trUtf8("duplikat");
			break;
		case 8:
			ret = QObject::trUtf8("RR");
			break;
		default:
			ret = QObject::trUtf8("FVAT");
			break;
		}

		return ret;
	}
};
