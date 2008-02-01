#ifndef SETTINGS_H
#define SETTINGS_H
#include <QSettings>
class Settings: public QSettings {
    public:
    Settings():QSettings("elinux","qfaktury") {}
};
#endif
