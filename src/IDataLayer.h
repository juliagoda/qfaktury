/*
 * IDataLayer.h
 *
 *  Created on: Apr 18, 2009
 *      Author: moux
 */

#ifndef IDATALAYER_H_
#define IDATALAYER_H_

#include "Settings.h"

#include "KontrData.h"
#include "ProductData.h"
#include "InvoiceData.h"

class IDataLayer {
public:
	IDataLayer() {};
	virtual ~IDataLayer() {};
	virtual void saveInvoiceData() {};
	virtual void readInvoiceData() {};

	virtual KontrData kontrahenciSelectData(QString, int) { return KontrData(); };
	virtual QVector<KontrData > kontrahenciSelectAllData() { QVector<KontrData > a; return a; };
	virtual bool kontrahenciInsertData(KontrData&, int) { return true; };
	virtual bool kontrahenciUpdateData(KontrData&, int, QString) { return true; };
	virtual bool kontrahenciDeleteData(QString ) { return true; };
	virtual QStringList kontrahenciGetFirmList() { return QStringList(); };

	virtual ProductData productsSelectData(QString, int) { return ProductData(); };
	virtual QVector<ProductData> productsSelectAllData() { QVector<ProductData> a; return a; };
	virtual bool productsInsertData(ProductData&, int) { return true; };
	virtual bool productsUpdateData(ProductData&, int, QString) { return true; };
	virtual bool productsDeleteData(QString) { return true; };

	virtual InvoiceData invoiceSelectData(QString, int) { return InvoiceData(); };
	virtual QVector<InvoiceData> invoiceSelectAllData(QDate, QDate) { QVector<InvoiceData> a; return a; };
	virtual bool invoiceInsertData(InvoiceData&, int) { return true; };
	virtual bool invoiceUpdateData(InvoiceData&, int, QString) { return true; };
	virtual bool invoiceDeleteData(QString) { return true; };

};

#endif /* IDATALAYER_H_ */
