#ifndef Faktura_H
#define Faktura_H
#include <QDialog>
#include "ui_Faktura.h"
class Faktura: public QDialog, public Ui::Faktura {
    Q_OBJECT
    public:
    Faktura(QWidget *parent);
    public slots:
void init ();
void readData (QString fraFile, int co);
void getKontrahent ();
void addTow ();
void countRabat ();
void countSum ();
void rabatChange ();
void delTowar ();
void editTowar ();
void makeInvoiceHeadar ();
void makeInvoiceBody ();
void makeInvoiceGoods ();
void makeInvoiceSumm ();
void makeInvoiceSummAll ();
QString getStawkami();
void makeInvoice ();
void saveInvoice ();
QString numbersCount(int in, int x);
void backBtnClick();
};
#endif
