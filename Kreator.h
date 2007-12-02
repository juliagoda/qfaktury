#ifndef Kreator_H
#define Kreator_H
#include <QDialog>
#include "ui_Kreator.h"
class Kreator: public QDialog, public Ui::Kreator {
    Q_OBJECT
    public:
    Kreator(QWidget *parent);
    public slots:
void init ();
void fillEdits ();
void kwotaKeyDown ();
void slownie ();
void hideSlownie (bool ok);
void getFirmList ();
void getOdbData ();
void makeWplata ();
void nextFunc ();
QString rozstrzel (QString in);
int getXSett (QString in);
int getYSett (QString in);
void readSettings ();
void saveXML ();
QPixmap getPrzelew ();
void print ();
};
#endif
