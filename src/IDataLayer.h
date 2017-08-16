#pragma once

/*
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
	virtual ~IDataLayer() = default;

	virtual void saveInvoiceData() = 0;
	virtual void readInvoiceData() = 0;
	virtual QString getRet() const = 0;
	virtual void checkAllSymbInFiles() = 0;
	virtual QList<int> getAllSymbols() const = 0;

	virtual BuyerData buyersSelectData(QString /*unused*/, int /*unused*/) = 0;
	virtual QVector<BuyerData> buyersSelectAllData() = 0;
	virtual bool buyersInsertData(BuyerData & /*unused*/, int /*unused*/) = 0;
	virtual bool buyersUpdateData(BuyerData & /*unused*/, int /*unused*/, QString /*unused*/) = 0;
	virtual bool buyersDeleteData(QString /*unused*/) = 0;
	virtual QStringList buyersGetFirmList() = 0;

	virtual ProductData productsSelectData(QString /*unused*/, int /*unused*/) = 0;
	virtual QVector<ProductData> productsSelectAllData() = 0;
	virtual bool productsInsertData(ProductData & /*unused*/, int /*unused*/) = 0;
	virtual bool productsUpdateData(ProductData & /*unused*/, int /*unused*/, QString /*unused*/) = 0;
	virtual bool productsDeleteData(QString /*unused*/) = 0;

	virtual InvoiceData invoiceSelectData(QString /*unused*/, int /*unused*/) = 0;
	virtual QVector<InvoiceData> invoiceSelectAllData(QDate /*unused*/, QDate /*unused*/) = 0;
	virtual bool invoiceInsertData(InvoiceData & /*unused*/, int /*unused*/) = 0;
	virtual bool invoiceUpdateData(InvoiceData & /*unused*/, int /*unused*/, QString /*unused*/) = 0;
	virtual bool invoiceDeleteData(QString /*unused*/) = 0;

	virtual bool ifThereOldInvoice() = 0;
	virtual void separateOldInvoices() = 0;
};
