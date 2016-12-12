#ifndef KONTRAHENCI_H
#define KONTRAHENCI_H
#include <QDialog>
#include <QtXml/qdom.h>

#include "ui_Kontrahenci.h"

#include "IDataLayer.h"

class Kontrahenci: public QDialog, public Ui::Kontrahenci {
Q_OBJECT
public:
	QString ret;
	QStringList allNames;
	Kontrahenci(QWidget *parent, int mode, IDataLayer *dl);
	void selectData(QString name, int type); // 0 - company, 1 - office
	bool insertData();
	bool updateData();
public slots:
	void okClick();
private:
	IDataLayer *dataLayer;
	int workingMode; // 0 = new
	void init();
	QString isEmpty(QString in);

	void getData(KontrData kontrData);
	void setData(KontrData &kontrData);

	bool validate();
    bool validateUpdated();
};
#endif
