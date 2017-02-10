#ifndef GOODSLIST_H
#define GOODSLIST_H

#include <QDialog>
#include "Settings.h"
#include "ProductData.h"

#include "ui_GoodsList.h"

class GoodsList: public QDialog, public Ui::GoodsList {

Q_OBJECT

public:

    QString const getRetVal() const;
    QMap<QString, int> const getVatsVal() const;
    QString const getSelItem() const;
    QString const getGoodsId() const;
    GoodsList(QWidget *parent);
    ~GoodsList();
    static GoodsList * instance();


public slots:

    void readGoods();
	virtual void doAccept();
	void comboBox1Changed(int x);
    virtual void calcNet();
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
    QMap<QString, QString> nets;
    QMap<QString, int> vats;
    QString selectedItem;
    QString id;
    static GoodsList * m_instance;

};
#endif
