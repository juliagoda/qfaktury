#ifndef Towary_H
#define Towary_H
#include <QDialog>
#include <Qt/qdom.h>

#include "ui_Towary.h"

class Towary: public QDialog, public Ui::Towary {
Q_OBJECT
public:
	Towary(QWidget *parent, int mode);
	QString ret; // return to MainWindow
	void readData(QString idx, int type); // called from MainWindow
public slots:
	void okClick();
	void spinChanged(int a);
	void nettoChanged(int a);
	void pkwiuGet();
private:
	QStringList netto;
	int lastId;
	QString nazwaEdit;
	// Working mode - 0 = new; 1 = edit
	int workMode;
	void modifyOnly();
	void init();
	bool saveAll();
	void displayData(QDomNode n);
	void fillElem(QDomElement elem);
};
#endif
