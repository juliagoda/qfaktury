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

	virtual void setData(InvoiceData &invData);

public slots:

	virtual void canQuit();
	void cancelDupl();
	void duplicateInit();

protected:
	virtual void makeInvoiceHeadar(bool sellDate, bool breakPage, bool original);

private:
	QDateEdit *duplicateDate;
	QLabel *labelDupDate;
	bool editMode;
};
