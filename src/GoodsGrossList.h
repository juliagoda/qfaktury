/*
 * TowaryBruttoLista.h
 *
 *  Created on: Apr 3, 2009
 *      Author: TPIELECH
 */

#ifndef GOODSGROSSLIST_H_
#define GOODSGROSSLIST_H_

#include "GoodsList.h"

class GoodsGrossList: public GoodsList {

Q_OBJECT

public:

    GoodsGrossList(QWidget *parent);
    QString const getRetValGoodsBr() const;
    ~GoodsGrossList();


public slots:

    void calcNet();
    void doAccept();
	QString getPriceOfCurrent();


private:

    QString ret;
    QString selectedItem;
};


#endif /* TOWARYBRUTTOLISTA_H_ */