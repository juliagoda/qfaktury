/*
 * TowaryBruttoLista.h
 *
 *  Created on: Apr 3, 2009
 *      Author: TPIELECH
 */

#ifndef TOWARYBRUTTOLISTA_H_
#define TOWARYBRUTTOLISTA_H_

#include "TowaryLista.h"

class TowaryBruttoLista: public TowaryLista {

Q_OBJECT

public:

	TowaryBruttoLista(QWidget *parent);
    QString const getRetValTowBr() const;
	~TowaryBruttoLista();


public slots:

    void calcNetto();
    void doAccept();
	QString getPriceOfCurrent();


private:

    QString ret;
    QString selectedItem;
};


#endif /* TOWARYBRUTTOLISTA_H_ */
