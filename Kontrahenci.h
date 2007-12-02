#ifndef Kontrahenci_H
#define Kontrahenci_H
#include <QDialog>
#include <ui_Kontrahenci.h>
class Kontrahenci: public QDialog, public Ui::Kontrahenci {
    Q_OBJECT

    public:
    Kontrahenci(QWidget *parent);

    public slots:
    void init();
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
    void makeInvoiceFooter ();
    void makeInvoice ();
    void saveInvoice ();
    QString numbersCount(int in, int x);
    void backBtnClick();
};

#endif
