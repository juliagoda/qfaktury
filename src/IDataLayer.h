#pragma once

/*
 * IDataLayer.h
 *
 *  Created on: Apr 18, 2009
 *      Author: moux
 */

#include "BuyerData.h"
#include "InvoiceData.h"
#include "ProductData.h"

#include <QList>

class IDataLayer
{
public:
	IDataLayer(){};
	virtual ~IDataLayer(){};
	virtual void saveInvoiceData(){};
	virtual void readInvoiceData(){};
	virtual const QString getRet() const
	{
		return "|";
	};
	virtual void checkAllSymbInFiles(){};
	virtual const QList<int> getAllSymbols()
	{
		QList<int> a;
		a.append(0);
		return a;
	};

	virtual BuyerData buyersSelectData(QString /*unused*/, int /*unused*/)
	{
		return BuyerData();
	};
	virtual QVector<BuyerData> buyersSelectAllData()
	{
		QVector<BuyerData> a;
		return a;
	};
	virtual bool buyersInsertData(BuyerData & /*unused*/, int /*unused*/)
	{
		return true;
	};
	virtual bool buyersUpdateData(BuyerData & /*unused*/, int /*unused*/, QString /*unused*/)
	{
		return true;
	};
	virtual bool buyersDeleteData(QString /*unused*/)
	{
		return true;
	};
	virtual QStringList buyersGetFirmList()
	{
		return QStringList();
	};

	virtual ProductData productsSelectData(QString /*unused*/, int /*unused*/)
	{
		return ProductData();
	};
	virtual QVector<ProductData> productsSelectAllData()
	{
		QVector<ProductData> a;
		return a;
	};
	virtual bool productsInsertData(ProductData & /*unused*/, int /*unused*/)
	{
		return true;
	};
	virtual bool productsUpdateData(ProductData & /*unused*/, int /*unused*/, QString /*unused*/)
	{
		return true;
	};
	virtual bool productsDeleteData(QString /*unused*/)
	{
		return true;
	};

	virtual InvoiceData invoiceSelectData(QString /*unused*/, int /*unused*/)
	{
		return InvoiceData();
	};
	virtual QVector<InvoiceData> invoiceSelectAllData(QDate /*unused*/, QDate /*unused*/)
	{
		QVector<InvoiceData> a;
		return a;
	};
	virtual bool invoiceInsertData(InvoiceData & /*unused*/, int /*unused*/)
	{
		return true;
	};
	virtual bool invoiceUpdateData(InvoiceData & /*unused*/, int /*unused*/, QString /*unused*/)
	{
		return true;
	};
	virtual bool invoiceDeleteData(QString /*unused*/)
	{
		return true;
	};

	virtual bool ifThereOldInvoice()
	{
		return true;
	};
	virtual void separateOldInvoices(){};
};
