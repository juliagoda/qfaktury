#ifndef Towary_H
#define Towary_H
#include <QDialog>
#include <Qt/qdom.h>
#include "IDataLayer.h"
#include "ProductData.h"

#include "ui_Towary.h"

class Towary: public QDialog, public Ui::Towary {
Q_OBJECT
public:
	Towary(QWidget *parent, int mode, IDataLayer *dl);
	QString ret; // return to MainWindow
	void selectData(QString idx, int type); // called from MainWindow
public slots:
	void okClick();
	void spinChanged(int a);
	void nettoChanged(double a);
	void pkwiuGet();
private:
	IDataLayer* dataLayer;
	QStringList netto;
	// Working mode - 0 = new; 1 = edit
	int workMode;

	void init();

	void getData(ProductData prodData);
	void setData(ProductData &prodData);

	bool updateData();
	bool insertData();
};
#endif
