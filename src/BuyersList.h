#pragma once

#include <QtXml/qdom.h>

#include "ui_BuyersList.h"

class BuyersList : public QDialog, public Ui::BuyersList
{
	Q_OBJECT

public:
	BuyersList(QWidget *parent);
	const QString getRetBuyerList();

public slots:
	void readBuyer();
	void doAccept();
	void comboBox1Changed();
	void updateDetails(QListWidgetItem *item);
	void mouseSelect();

private:
	QStringList companiesList;
	QStringList officesList;
	QStringList personsList;
	QString ret;

	void init();
	void displayDetails(QStringList custDetails);
	void clearDetails();
	QString xmlDataToString(QDomNode n);
	QString detailsToString();
};
