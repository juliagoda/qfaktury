#ifndef Ustawienia_H
#define Ustawienia_H
#include <QDialog>
#include <QSettings>
#include "ui_Ustawienia.h"
#include <QListWidget>
class Ustawienia: public QDialog, public Ui::Ustawienia {
Q_OBJECT
public:
	Ustawienia(QWidget *parent);
public slots:
	void apply();
	void okButtonClick();
	void addLogoBtnClick();
	void currAddBtnClick();
	void currDelBtnClick();
	void korAddBtnClick();
	void korDelBtnClick();
	void vatAddBtnClick();
	void vatDelBtnClick();
	void vatUpBtnClick();
	void vatDownBtnClick();
	void currencyAddBtnClick();
	void currencyDelBtnClick();
	void paymUpBtnClick();
	void paymDownBtnClick();
	void paymDelBtnClick();
	void zastBtnEnable();
	void paymAddBtnClick();
	void defTextBtnClick();
	void setDefaultClick();
	void maskHelpClick();
	void workingDirBtnClick();
private:
	bool read;
	void init();
	void sumSize();
	void saveSettings();
	void readSettings();
	void getEncodings();
	QStringList getTemplates();
	QStringList getTranslations();
	QString getAll(QListWidget *lb);
	QList<QTextCodec *> codecs;

};
#endif
