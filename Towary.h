#ifndef Towary_H
#define Towary_H
#include <QDialog>
#include "ui_Towary.h"

class Towary: public QDialog, public Ui::Towary {
Q_OBJECT
	void init();
	bool saveAll();
public:
	Towary(QWidget *parent, int mode);
	QString ret;
public slots:
	void readData(QString idx, QString type);
	void getStuffList();
	void modifyOnly();
	void okClick();
	void spinChanged(int a);
	void nettoChanged();
	void pkwiuGet();

private:
	QStringList netto;
	int lastId;
	QStringList allNames;
	QString nazwaEdit;

	// Working mode - 0 = new; 1 = edit
	int workMode;
};
#endif
