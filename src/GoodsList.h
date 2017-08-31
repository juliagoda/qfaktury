#include "detector.h"
#if _pragma_once_support
#    pragma once
#endif
#ifndef GOODSLIST_H
#define GOODSLIST_H

#include "ui_GoodsList.h"
#include "ProductData.h"


class GoodsList: public QDialog, public Ui::GoodsList {

Q_OBJECT

public:

    GoodsList(QWidget *parent);
    ~GoodsList();

    const QString getRetVal();
    const QMap<QString, int> getVatsVal();
    const QString getSelItem();
    const QString getGoodsId();
    static GoodsList * instance();


public slots:

	virtual void doAccept();
    virtual void calcNet();
    void readGoods();
	void displayData(int x);
	void lv1selChanged();
    void displayNet(QString index);
	void spinChanged(int a);


protected:

	void init();
    typedef QHash<QString, ProductData *> ProductDataList;
    ProductDataList goodsList2;
    ProductDataList servicesList2;
    QString trimZeros(QString in);


private:

    QString ret;
    QString selectedItem;
    QString id;
    QMap<QString, QString> nets;
    QMap<QString, int> vats;
    static GoodsList * m_instance;

};
#endif
