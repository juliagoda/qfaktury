#ifndef TowaryLista_H
#define TowaryLista_H
#include <QDialog>
#include "Settings.h"
#include "ProductsListData.h"

#include "ui_TowaryLista.h"

class TowaryLista: public QDialog, public Ui::TowaryLista {
Q_OBJECT
public:
	QString ret;
	TowaryLista(QWidget *parent);
public slots:
	void readTow(QString progDir);
	void doAccept();
	void comboBox1Changed(int x);
	void calcNetto();
	void displayData(int x);
	void lv1selChanged();
	void displayNetto(QString index);
	void spinChanged(int a);
private:
	void init();

	typedef QMap<QString, ProductsListData *> ProductsListDataList;
	ProductsListDataList listaTowary2;
	ProductsListDataList listaUslugi2;
	QStringList listaTowary;
	QStringList listaUslugi;
	QMap<QString, QString> nettos;
	QMap<QString, int> vats;

	QString selectedItem;
	QString progDir;
	QString id;
	QString trimZeros(QString in);
};
#endif
