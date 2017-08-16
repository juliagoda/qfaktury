#pragma once

#include "Invoice.h"

class InvoiceRR : public Invoice
{
public:
	InvoiceRR(QWidget *parent, IDataLayer *dl, QString in_form = QString());
	~InvoiceRR();

public slots:
	void invoiceRRInit();
	void makeInvoice();

protected:
	QString getInvoiceTypeAndSaveNr();
	void getData(InvoiceData invData);
	void setData(InvoiceData &invData);

private:
	QCheckBox *ifpaysVAT;
};
