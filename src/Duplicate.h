#pragma once

/*
 * Duplicat.h
 *
 *  Created on: Mar 31, 2009
 *      Author: moux
 */

#include "Invoice.h"

class Duplicate : public Invoice
{
	Q_OBJECT

public:
	Duplicate(QWidget *parent, IDataLayer *dl, QString in_form, bool ifEdited);
	~Duplicate();

	void setData(InvoiceData &invData) override;

public slots:
	void canQuit() override;
	void cancelDupl();
	void duplicateInit();

protected:
	void makeInvoiceHeadar(bool sellDate, bool breakPage, bool original) override;

private:
	QDateEdit *duplicateDate;
	QLabel *labelDupDate;
	bool editMode;
};
