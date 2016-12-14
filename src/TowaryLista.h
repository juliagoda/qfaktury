#ifndef TowaryLista_H
#define TowaryLista_H
#include <QDialog>
#include "Settings.h"
#include "ProductData.h"

#include "ui_TowaryLista.h"

class TowaryLista: public QDialog, public Ui::TowaryLista {

Q_OBJECT

public:

    QString getRetVal() const;
    QMap<QString, int> getVatsVal() const;
    QString getSelItem() const;
    QString getTowId() const;
	TowaryLista(QWidget *parent);


public slots:

	void readTow();
	virtual void doAccept();
	void comboBox1Changed(int x);
	virtual void calcNetto();
	void displayData(int x);
	void lv1selChanged();
	void displayNetto(QString index);
	void spinChanged(int a);


protected:

	void init();
    typedef QHash<QString, ProductData *> ProductDataList;
    ProductDataList listaTowary2;
    ProductDataList listaUslugi2;
    QString trimZeros(QString in);


private:

    QString ret;
    QMap<QString, QString> nettos;
    QMap<QString, int> vats;
    QString selectedItem;
    QString id;

};
#endif
