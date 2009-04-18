#ifndef KONTRAHENCI_H
#define KONTRAHENCI_H
#include <QDialog>
#include <Qt/qdom.h>

#include "ui_Kontrahenci.h"

#include "IDataLayer.h"

class Kontrahenci: public QDialog, public Ui::Kontrahenci {
Q_OBJECT
public:
	QString ret;
	QStringList allNames;
	Kontrahenci(QWidget *parent, int mode, IDataLayer *dl);
	void readData(QString name, int type); // 0 - company, 1 - office
public slots:
	void okClick();
private:
	IDataLayer *dataLayer;
	QString nazwaEdit;
	int workingMode; // 0 = new
	void init();
	QString isEmpty(QString in);
	void getFirmList();
	bool saveAll();
	void modifyOnly();
	void loadDetails(KontrData kontrData);
	void dataToElem(QDomElement elem);
	bool validateForm(QString &missing);
};
#endif
