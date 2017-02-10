#ifndef BUYERSLIST_H
#define BUYERSLIST_H
#include <QDialog>
#include <QtXml/qdom.h>
#include <QKeyEvent>

#include "Settings.h"
#include "ui_BuyersList.h"

class BuyersList: public QDialog, public Ui::BuyersList {

Q_OBJECT

public:

    BuyersList(QWidget *parent);
    QString const getRetBuyerList() const;


public slots:

    void readBuyer();
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
