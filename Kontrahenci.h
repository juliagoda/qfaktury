#ifndef KONTRAHENCI_H
#define KONTRAHENCI_H
#include <QDialog>
#include "ui_Kontrahenci.h"
class Kontrahenci: public QDialog, public Ui::Kontrahenci {
    Q_OBJECT
    public:
    Kontrahenci(QWidget *parent);
void init ();
QString isEmpty (QString in);
    public slots:
void readData (QString name, QString type);
void getFirmList ();
bool saveAll ();
void modifyOnly ();
void okClick ();
void newFunction ();
    public:

    QString ret;
    QStringList allNames;
};
#endif
