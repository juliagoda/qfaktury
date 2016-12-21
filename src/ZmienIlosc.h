#ifndef ZmienIlosc_H
#define ZmienIlosc_H
#include <QDialog>
#include "ui_ZmienIlosc.h"
class ZmienIlosc: public QDialog, public Ui::ZmienIlosc {

Q_OBJECT

public:

	ZmienIlosc(QWidget *parent);
    ~ZmienIlosc();
    static ZmienIlosc * instance();
    void init();

private:

    static ZmienIlosc * m_instance;

};
#endif
