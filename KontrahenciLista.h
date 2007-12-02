#ifndef KontrahenciLista_H
#define KontrahenciLista_H
#include <QDialog>
#include "ui_KontrahenciLista.h"
class KontrahenciLista: public QDialog, public Ui::KontrahenciLista {
    Q_OBJECT
    public:
    KontrahenciLista(QWidget *parent);
    public slots:
void init ();
void readKontr (QString progDir);
void doAccept ();
void comboBox1Changed ();
};
#endif
