#pragma once

#include "ui_BuyersList.h"

#include <QtXml/qdom.h>

class BuyersList : public QDialog, public Ui::BuyersList
{
	Q_OBJECT

public:
	BuyersList(QWidget *parent);
	QString getRetBuyerList() const;

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
