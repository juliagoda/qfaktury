#ifndef Korekta_H
#define Korekta_H
#include <QDialog>
#include "ui_Korekta.h"
class Korekta: public QDialog, public Ui::Korekta {
    public:
    Korekta(QWidget *parent);
    public slots:
void init ();
void readData(QString fraFile);
void readDataNewKor (QString fraFile);
void getKontrahent ();
void addTow ();
void countRabat ();
void countSum ();
void rabatChange ();
void delTowar ();
void editTowar ();
void makeInvoiceHeadar ();
void makeInvoiceBody ();
void makeInvoiceCorr ();
void makeInvoiceGoods2 ();
void makeInvoiceSumm2 ();
void makeInvoiceGoods ();
void makeInvoiceSumm ();
void makeInvoiceSummAll ();
getStawkami();
void makeInvoiceFooter ();
void makeInvoice ();
void saveInvoice ();
numbersCount(int in, int x);
backBtnClick();
void backBtnClick();
};
#endif
