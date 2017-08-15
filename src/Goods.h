#pragma once

#include "IDataLayer.h"
#include "ProductData.h"
#include "ui_Goods.h"

class Goods : public QDialog, public Ui::Goods
{
	Q_OBJECT

public:
	Goods(QWidget *parent, int mode, IDataLayer *dl);
	void selectData(QString idx, int type); // called from MainWindow
	QString getRetGoods() const;

public slots:
	void okClick();
	void spinChanged(int a);
	void netChanged(double a);
	void pkwiuGet();

private:
	IDataLayer *dataLayer;
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
