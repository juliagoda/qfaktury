/*
 * IDataLayer.h
 *
 *  Created on: Apr 18, 2009
 *      Author: moux
 */

#ifndef IDATALAYER_H_
#define IDATALAYER_H_

#include "KontrData.h"
#include "ProductData.h"

class IDataLayer {
public:
	IDataLayer() {};
	virtual ~IDataLayer() {};
	virtual void saveInvoiceData() {};
	virtual void readInvoiceData() {};

	virtual KontrData kontrahenciSelectData(QString, int) { return KontrData(); };
	virtual bool kontrahenciInsertData(KontrData&, int) { return true; };
	virtual bool kontrahenciUpdateData(KontrData&, int, QString) { return true; };
	virtual bool kontrahenciDeleteData(QString ) { return true; };
	virtual QStringList kontrahenciGetFirmList() { return QStringList(); };

	virtual ProductData productsSelectData(QString, int) { return ProductData(); };
	virtual QVector<ProductData> productsSelectAllData() { QVector<ProductData> a; return a; };
	virtual bool productsInsertData(ProductData&, int) { return true; };
	virtual bool productsUpdateData(ProductData&, int, QString) { return true; };
	virtual bool productsDeleteData(QString) { return true; };


};

#endif /* IDATALAYER_H_ */
