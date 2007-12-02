#ifndef Uzytkownik_H
#define Uzytkownik_H
#include <QDialog>
#include "ui_Uzytkownik.h"
class Uzytkownik: public QDialog, public Ui::Uzytkownik {
    Q_OBJECT
    public:
    Uzytkownik(QWidget *parent);
    public slots:
void init ();
void okClick ();
};
#endif
