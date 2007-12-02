#ifndef Faktura_H
#define Faktura_H
#include <QDialog>
#include "ui_Faktura.h"
class Faktura: public QDialog, public Ui::Faktura {
    Q_OBJECT
    public:
    Faktura(QWidget *parent);
void init ();
void readData (QString fraFile, int co);
QString getStawkami();
QString numbersCount(int in, int x);
    public slots:
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
void makeInvoice ();
void saveInvoice ();
void backBtnClick();
void makeInvoiceFooter ();

    public:
    QString fName, progDir2, ret, vatAll, templDir;
    int type;
    bool pforma;
    private:
    QString lastInvoice;
};
#endif
