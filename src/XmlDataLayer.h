#pragma once

/*
 *  Created on: Apr 18, 2009
 *      Author: moux
 */

#include <QtXml/qdom.h>

#include "IDataLayer.h"

class XmlDataLayer : public IDataLayer
{
public:
	XmlDataLayer();
	virtual ~XmlDataLayer();

	// methods used for accessing customers
	BuyerData buyersSelectData(QString name, int type) override;
	QVector<BuyerData> buyersSelectAllData() override;
	bool buyersInsertData(BuyerData &buyerData, int type) override;
	bool buyersUpdateData(BuyerData &buyerData, int type, QString name) override;
	bool buyersDeleteData(QString name) override;
	QStringList buyersGetFirmList() override;

	ProductData productsSelectData(QString name, int type) override;
	QVector<ProductData> productsSelectAllData() override;
	bool productsInsertData(ProductData &prodData, int type) override;
	bool productsUpdateData(ProductData &prodData, int type, QString name) override;
	bool productsDeleteData(QString name) override;

	InvoiceData invoiceSelectData(QString name, int type) override;
	QVector<InvoiceData> invoiceSelectAllData(QDate start, QDate end) override;
	bool invoiceInsertData(InvoiceData &oi_invData, int type) override;
	bool invoiceUpdateData(InvoiceData &invData, int type, QString name) override;
	bool invoiceDeleteData(QString name) override;

	QString getRet() const override;
	void checkAllSymbInFiles() override;
	QList<int> getAllSymbols() const override;
	bool ifThereOldInvoice() override;
	void separateOldInvoices() override;

	void saveInvoiceData() override
	{
	}
	void readInvoiceData() override
	{
	}

private:
	void buyersElemToData(BuyerData &o_buyerData, QDomElement i_element) const;
	void buyersDataToElem(BuyerData &i_buyerData, QDomElement &o_element) const;

	void productsElemToData(ProductData &o_prodData, QDomElement i_element) const;
	void productsDataToElem(ProductData &i_prodData, QDomElement &o_element) const;

	void invoiceSellerDataToElem(InvoiceData &i_invData, QDomElement &o_element) const;
	void invoiceSellerElemToData(InvoiceData &o_invData, QDomElement i_element) const;
	void invoiceBuyerDataToElem(InvoiceData &i_invData, QDomElement &o_element);
	void invoiceBuyerElemToData(InvoiceData &o_invData, QDomElement i_element) const;
	void invoiceProdDataToElem(
		const ProductData &i_prodData,
		QDomElement &o_element,
		int currentRow) const;
	void invoiceProdElemToData(InvoiceData &o_invData, QDomElement i_element) const;
	bool ifPersonNodeExists(QDomElement root) const;
	void addSectionPerson(bool checkedRoot);

	bool nameFilter(QString nameToCheck, QDate start, QDate end);

	QString ret;
	QList<int> allSymbols;
	QStringList yearsList;
	QMultiHash<QString, QString> categorizedFiles;
};
