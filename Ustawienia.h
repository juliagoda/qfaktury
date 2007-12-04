#ifndef Ustawienia_H
#define Ustawienia_H
#include <QDialog>
#include "ui_Ustawienia.h"
#include <QListWidget>
class Ustawienia: public QDialog, public Ui::Ustawienia {
    Q_OBJECT
QString getAll(QListWidget *lb);
void init ();
    public:
    Ustawienia(QWidget *parent);
    public slots:
void apply ();
void okButtonClick ();
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
