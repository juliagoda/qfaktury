#pragma once

#include "ProductData.h"
#include "ui_GoodsList.h"

class GoodsList : public QDialog, public Ui::GoodsList
{
	Q_OBJECT

public:
	GoodsList(QWidget *parent);
	~GoodsList();

	static GoodsList *instance();
	QString getRetVal() const;
	QMap<QString, int> getVatsVal() const;
	QString getSelItem() const;
	QString getGoodsId() const;

public slots:
	virtual void doAccept();
	virtual void calcNet();
	void readGoods();
	void comboBox1Changed(int x);
	void displayData(int x);
	void lv1selChanged();
	void displayNet(QString index);
	void spinChanged(int a);

protected:
	void init();
	typedef QHash<QString, ProductData> ProductDataList;
	ProductDataList goodsList2;
	ProductDataList servicesList2;
	QString trimZeros(QString in);

private:
	QString ret;
	QString selectedItem;
	QString id;
	QMap<QString, QString> nets;
	QMap<QString, int> vats;
	static GoodsList *m_instance;
};
