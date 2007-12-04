#ifndef ZmienIlosc_H
#define ZmienIlosc_H
#include <QDialog>
#include "ui_ZmienIlosc.h"
class ZmienIlosc: public QDialog, public Ui::ZmienIlosc {
    Q_OBJECT
    void init();
    public:
    ZmienIlosc(QWidget *parent);
    public slots:
};
#endif
