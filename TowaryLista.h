#ifndef TowaryLista_H
#define TowaryLista_H
#include <QDialog>
#include "Settings.h"
#include "ProductsListData.h"

#include "ui_TowaryLista.h"

class TowaryLista: public QDialog, public Ui::TowaryLista {
    Q_OBJECT
    public:
    	void init ();


    	typedef QMap < QString, ProductsListData > ProductsListDataList;
    	ProductsListDataList listaTowary2;
    	ProductsListDataList listaUslugi2;

    	QStringList listaTowary;
    	QStringList listaUslugi;
    	QString vat;
    TowaryLista(QWidget *parent);
    public slots:
void readTow (QString progDir);
void doAccept ();
void comboBox1Changed (int x);
void calcNetto ();
void fillLv (int x);
void lv1selChanged();
void readNettos (QString index);
void spinChanged (int a);
    public:
    QString selectedItem;
    QString progDir;
    QString ret;
    QMap<int, QString> nettos;
    QString id;
};
#endif
