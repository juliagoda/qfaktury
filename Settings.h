#ifndef SETTINGS_H
#define SETTINGS_H
#include <QSettings>
#include <QDate>
#include <QString>
#include <QVariant>
#include <QLocale>
#define UTF8(x) QString::fromUtf8(x)
class Settings: public QSettings {
public:
	// constr
	Settings() :
		QSettings("elinux", "qfaktury") {
		// setDefaultFormat(QSettings::IniFormat);
	}

	// get date from settings as QDate
	QDate getValueAsDate(QString val) {
		QString date = value(val).toString();
		QLocale locale;
		return locale.toDate ( date, QLocale::ShortFormat );
	}

};
#endif
