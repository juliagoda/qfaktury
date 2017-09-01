#include "detector.h"
#if _pragma_once_support
#pragma once
#endif
#ifndef GOODS_H
#define GOODS_H


#include "IDataLayer.h"
#include "ProductData.h"
#include "ui_Goods.h"


class Goods: public QDialog, public Ui::Goods {

Q_OBJECT

public:

    Goods(QWidget *parent, int mode, IDataLayer *dl);
    void selectData(QString idx, int type); // called from MainWindow
    const QString getRetGoods();


public slots:

	void okClick();


private:

	IDataLayer* dataLayer;
    QString ret;
    QStringList net;
    int workMode; // Working mode - 0 = new; 1 = edit

	void init();
    void getData(ProductData prodData);
	void setData(ProductData &prodData);
	bool updateData();
	bool insertData();
    QString isEmpty(QString in);

};
#endif
