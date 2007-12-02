#ifndef Korekta_H
#define Korekta_H
#include <QDialog>
#include "ui_Korekta.h"
class Korekta: public QDialog, public Ui::Korekta {
    Q_OBJECT
void init ();
QString getStawkami();
QString numbersCount(int in, int x);
    public:
    Korekta(QWidget *parent);
    public slots:
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
void makeInvoiceFooter ();
void makeInvoice ();
void saveInvoice ();
void backBtnClick();
    private:
    double priceBRabN, priceBRab;
    public:
    double oldBrutto;
    double oldVat;
    double oldNetto;
    QMap<int, QString> towaryPKor;
    QStringList fraStrList;
    QString lastInvoice;
    int type;
    QString fName;
    QString progDir2;
    QString ret;
    QString templDir;
    QString snetto;
    QString sbrutto;
    QString sRabat;
    QString currency;

};
#endif
