#ifndef KontrahenciLista_H
#define KontrahenciLista_H
#include <QDialog>
#include <QtXml/qdom.h>
#include <QKeyEvent>

#include "Settings.h"
#include "ui_KontrahenciLista.h"

class KontrahenciLista: public QDialog, public Ui::KontrahenciLista {

Q_OBJECT

public:

	KontrahenciLista(QWidget *parent);
    QString getRetKontrList() const;


public slots:

	void readKontr();
	void doAccept();
	void comboBox1Changed();
	void updateDetails(QListWidgetItem *);
	void mouseSelect();


private:

	QStringList companiesList;
	QStringList officesList;
	void init();
	QString xmlDataToString(QDomNode n);
	void displayDetails(QStringList custDetails);
	void clearDetails();
	QString detailsToString();
    QString ret;

};
#endif
