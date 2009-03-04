#ifndef KONTRAHENCI_H
#define KONTRAHENCI_H
#include <QDialog>
#include <Qt/qdom.h>

#include "ui_Kontrahenci.h"

class Kontrahenci: public QDialog, public Ui::Kontrahenci {
Q_OBJECT
public:
	QString ret;
	QStringList allNames;
	Kontrahenci(QWidget *parent, int mode);
	void readData(QString name, int type); // 0 - company, 1 - office
public slots:
	void okClick();
private:
	QString nazwaEdit;
	int workingMode; // 0 = new
	void init();
	QString isEmpty(QString in);
	void getFirmList();
	bool saveAll();
	void modifyOnly();
	void loadDetails(QDomNode n);
	void dataToElem(QDomElement elem);
};
#endif
