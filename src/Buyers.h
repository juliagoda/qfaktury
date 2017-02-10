#ifndef BUYERS_H
#define BUYERS_H
#include <QDialog>
#include <QtXml/qdom.h>

#include "ui_Buyers.h"

#include "IDataLayer.h"

class Buyers: public QDialog, public Ui::Buyers {

Q_OBJECT

public:

    Buyers(QWidget *parent, int mode, IDataLayer *dl);
    void selectData(QString name, int type); // 0 - company, 1 - department
	bool insertData();
	bool updateData();
    QString const getRetBuyer() const;


public slots:

	void okClick();


private:

    QStringList allNames;
    QString ret;
	IDataLayer *dataLayer;
	int workingMode; // 0 = new
	void init();
	QString isEmpty(QString in);
    void getData(BuyerData buyerData);
    void setData(BuyerData &buyerData);
	bool validate();
    bool validateUpdated();

};
#endif
