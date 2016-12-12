/*
 * Duplicat.h
 *
 *  Created on: Mar 31, 2009
 *      Author: moux
 */

#ifndef DUPLICAT_H_
#define DUPLICAT_H_

#include <QDialog>
#include <QDateEdit>

#include "ui_Faktura.h"
#include "Faktura.h"

#include "ConvertAmount.h"
#include "Settings.h"


class Duplikat: public Faktura {
Q_OBJECT
public:
    Duplikat(QWidget *parent, IDataLayer *dl, QString in_form);
    bool editMode;
    virtual void setData(InvoiceData &invData);

public slots:
	void duplikatInit();
	virtual void canQuit();
    void cancelDupl();

protected:
	virtual void makeInvoiceHeadar(bool sellDate, bool breakPage, bool original);
private:
    QDateEdit* duplicateDate;


};
#endif /* DUPLICAT_H_ */
