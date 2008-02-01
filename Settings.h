#ifndef SETTINGS_H
#define SETTINGS_H
#include <QSettings>
#define UTF8(x) QString::fromUtf8(x)
class Settings: public QSettings {
    public:
    Settings():QSettings("elinux","qfaktury") {}
};
#endif
