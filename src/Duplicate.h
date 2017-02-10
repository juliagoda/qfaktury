/*
 * Duplicat.h
 *
 *  Created on: Mar 31, 2009
 *      Author: moux
 */

#ifndef DUPLICATE_H_
#define DUPLICATE_H_

#include <QDialog>
#include <QDateEdit>

#include "ui_Invoice.h"
#include "Invoice.h"

#include "ConvertAmount.h"
#include "Settings.h"


class Duplicate: public Invoice {

Q_OBJECT

public:

    Duplicate(QWidget *parent, IDataLayer *dl, QString in_form, bool ifEdited);
    ~Duplicate();
    virtual void setData(InvoiceData &invData);


public slots:

    void duplicateInit();
	virtual void canQuit();
    void cancelDupl();


protected:

	virtual void makeInvoiceHeadar(bool sellDate, bool breakPage, bool original);


private:

    QDateEdit* duplicateDate;
    QLabel* labelDupDate;
    bool editMode;

};
#endif /* DUPLICATE_H */
