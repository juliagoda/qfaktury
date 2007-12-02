#ifndef Ustawienia_H
#define Ustawienia_H
#include <QDialog>
#include "ui_Ustawienia.h"
class Ustawienia: public QDialog, public Ui::Ustawienia {
    public:
    Ustawienia(QWidget *parent);
    public slots:
void init ();
void apply ();
void okButtonClick ();
QString getAll(QListBox *lb);
void saveSettings ();
void readSettings ();
void addLogoBtnClick();
void currAddBtnClick();
void currDelBtnClick();
void korAddBtnClick();
void korDelBtnClick();
void vatAddBtnClick();
void vatDelBtnClick();
void vatUpBtnClick();
void vatDownBtnClick();
void currencyAddBtnClick();
void currencyDelBtnClick();
void paymUpBtnClick();
void paymDownBtnClick();
void paymDelBtnClick();
void zastBtnEnable();
void paymAddBtnClick();
};
#endif
