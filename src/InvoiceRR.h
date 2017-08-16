#pragma once

#include "Invoice.h"

class InvoiceRR : public Invoice
{
public:
	InvoiceRR(QWidget *parent, IDataLayer *dl, QString in_form = QString());
	~InvoiceRR();

public slots:
	void invoiceRRInit();
	void makeInvoice() override;

protected:
	QString getInvoiceTypeAndSaveNr() override;
	void getData(InvoiceData invData) override;
	void setData(InvoiceData &invData) override;

private:
	QCheckBox *ifpaysVAT;
};
