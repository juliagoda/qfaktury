/*
 * TowaryBruttoLista.h
 *
 *  Created on: Apr 3, 2009
 *      Author: TPIELECH
 */
#include "detector.h"
#if _pragma_once_support
#    pragma once
#endif
#ifndef GOODSGROSSLIST_H_
#define GOODSGROSSLIST_H_

#include "GoodsList.h"

class GoodsGrossList: public GoodsList {

Q_OBJECT

public:

    GoodsGrossList(QWidget *parent);
    const QString getRetValGoodsBr();
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
