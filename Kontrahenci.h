#ifndef KONTRAHENCI_H
#define KONTRAHENCI_H
#include <QDialog>
#include "ui_Kontrahenci.h"
class Kontrahenci: public QDialog, public Ui::Kontrahenci {
Q_OBJECT
public:
	QString ret;
	QStringList allNames;
	Kontrahenci(QWidget *parent);
	void readData(QString name, QString type);
public slots:
	void okClick();
private:
	QString progDir;
	QString nazwaEdit;
	void init();
	QString isEmpty(QString in);
	void getFirmList();
	bool saveAll();
	void modifyOnly();
};
#endif
