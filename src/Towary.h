#ifndef Towary_H
#define Towary_H
#include <QDialog>
#include <Qt/qdom.h>
#include "IDataLayer.h"

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
	int lastId;
	QString nazwaEdit;
	// Working mode - 0 = new; 1 = edit
	int workMode;
	void updateData();
	void init();
	bool insertData();
	void displayData(QDomNode n);
	void fillElem(QDomElement elem);
};
#endif
