#ifndef KONTRAHENCI_H
#define KONTRAHENCI_H
#include <QDialog>
#include <QtXml/qdom.h>

#include "ui_Kontrahenci.h"

#include "IDataLayer.h"

class Kontrahenci: public QDialog, public Ui::Kontrahenci {

Q_OBJECT

public:

	Kontrahenci(QWidget *parent, int mode, IDataLayer *dl);
	void selectData(QString name, int type); // 0 - company, 1 - office
	bool insertData();
	bool updateData();
    QString getRetKontr() const;


public slots:

	void okClick();


private:

    QStringList allNames;
    QString ret;
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
