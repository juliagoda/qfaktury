#ifndef Towary_H
#define Towary_H
#include <QDialog>
#include <QtXml/qdom.h>
#include "IDataLayer.h"
#include "ProductData.h"

#include "ui_Towary.h"

class Towary: public QDialog, public Ui::Towary {

Q_OBJECT

public:

	Towary(QWidget *parent, int mode, IDataLayer *dl);
	void selectData(QString idx, int type); // called from MainWindow
    QString const getRetTow() const;


public slots:

	void okClick();
	void spinChanged(int a);
	void nettoChanged(double a);
	void pkwiuGet();


private:

	IDataLayer* dataLayer;
    QString ret;
    QStringList netto;
    int workMode; // Working mode - 0 = new; 1 = edit
	void init();
	void getData(ProductData prodData);
	void setData(ProductData &prodData);
	bool updateData();
	bool insertData();
};
#endif
