#ifndef Towary_H
#define Towary_H
#include <QDialog>
#include "ui_Towary.h"
class Towary: public QDialog, public Ui::Towary {
    public:
    Towary(QWidget *parent);
    public slots:
void readData (QString idx, QString type);
void getStuffList ();
void init ();
bool saveAll ();
void modifyOnly ();
void okClick ();
void spinChanged (int a);
void nettoChanged ();
void pkwiuGet ();
};
#endif
