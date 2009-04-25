/*
 * XmlDataLayer.h
 *
 *  Created on: Apr 18, 2009
 *      Author: moux
 */

#ifndef XMLDATALAYER_H_
#define XMLDATALAYER_H_

#include <Qt/qdom.h>

#include "IDataLayer.h"

class XmlDataLayer: public IDataLayer {
public:
	XmlDataLayer();
	virtual ~XmlDataLayer();
	// methods used for accessing customers
	virtual KontrData kontrahenciSelectData(QString name, int type);
	virtual QVector<KontrData > kontrahenciSelectAllData();
	virtual bool kontrahenciInsertData(KontrData& kontrData, int type);
	virtual bool kontrahenciUpdateData(KontrData& kontrData, int type, QString name);
	virtual bool kontrahenciDeleteData(QString name);
	virtual QStringList kontrahenciGetFirmList();

	virtual ProductData productsSelectData(QString name, int type);
	virtual QVector<ProductData> productsSelectAllData();
	virtual bool productsInsertData(ProductData& prodData, int type);
	virtual bool productsUpdateData(ProductData& prodData, int type, QString name);
	virtual bool productsDeleteData(QString name);

	virtual InvoiceData invoiceSelectData(QString name, int type);
	virtual QVector<InvoiceData> invoiceSelectAllData(QDate start, QDate end);
	virtual bool invoiceInsertData(InvoiceData& invData, int type);
	virtual bool invoiceUpdateData(InvoiceData& invData, int type, QString name);
	virtual bool invoiceDeleteData(QString name);

	virtual void saveInvoiceData() {};
	virtual void readInvoiceData() {};
private:
	void kontrahenciElemToData(KontrData &o_kontrData, QDomElement i_element);
	void kontrahenciDataToElem(KontrData &i_kontrData, QDomElement &o_element);

	void productsElemToData(ProductData& o_prodData, QDomElement i_element);
	void productsDataToElem(ProductData& i_prodData, QDomElement &o_element);

	void invoiceProdElemToData(InvoiceData& o_invData, QDomElement i_element);
	void invoiceProdDataToElem(InvoiceData& i_invData, QDomElement &o_element);

	bool nameFilter(QString nameToCheck, QDate start, QDate end);

};

#endif /* XMLDATALAYER_H_ */
