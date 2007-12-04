#ifndef Kreator_H
#define Kreator_H
#include <QDialog>
#include "ui_Kreator.h"
class Kreator: public QDialog, public Ui::Kreator {
    Q_OBJECT
void init ();
    public:
    Kreator(QWidget *parent);
    public slots:
void fillEdits ();
void kwotaKeyDown ();
void slownie ();
void hideSlownie (bool ok);
void getFirmList ();
void getOdbData ();
void makeWplata ();
void nextFunc ();
void readSettings ();
void saveXML ();
void print ();
    private:
QString rozstrzel (QString in);
int getXSett (QString in);
int getYSett (QString in);
QPixmap getPrzelew ();
    QFont font;
    bool poziom;
    int prevPage;
    QStringList pOdb1;
    QStringList pOdb2;
    QStringList pWal;
    QStringList pNrrach;
    QStringList pKwota;
    QStringList pKsw;
    QStringList pZlec1;
    QStringList pZlec2;
    QStringList pTyt1;
    QStringList pTyt2;
    int pages;
    bool own;
    QString odbNazwa;
    QString odbPlace;
    QString odbCode;
    QString odbAddress;
    QString odbAccount;
    int rozSp;
};
#endif
