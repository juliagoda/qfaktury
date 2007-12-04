#ifndef Podglad_H
#define Podglad_H
#include <QDialog>
#include "ui_Podglad.h"
class Podglad: public QDialog, public Ui::Podglad {
    Q_OBJECT
    void init ();
    public:
    Podglad(QWidget *parent);
    public slots:
};
#endif
