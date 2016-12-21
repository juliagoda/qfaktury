#include "moc_ZmienIlosc.cpp"
#include "ZmienIlosc.h"

ZmienIlosc* ZmienIlosc::m_instance = nullptr;

ZmienIlosc::ZmienIlosc(QWidget *parent): QDialog(parent) {
    setupUi(this);
    init();
}

void ZmienIlosc::init() {
    m_instance = this;
}


ZmienIlosc::~ZmienIlosc()
{
    m_instance = nullptr;
}


ZmienIlosc* ZmienIlosc::instance()
{
    return m_instance;
}

