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
	void cb1Changed();
	void cb2Changed();
	void cb3Changed();
	void cb4Changed();
	void cb5Changed();
	void cb6Changed();
	void cb7Changed();
	void cb8Changed();
	void cb9Changed();
	void cb10Changed();
	void cb11Changed();
	void cb12Changed();
	void cb13Changed();
	void cb14Changed();
	void mdChanged();
	void sbxChanged();
	void addBrowser();
private:
	bool read;
	QSettings settings;
	void init();
	void sumSize();
	void saveSettings();
	void readSettings();
	void getEncodings();
	QString getAll(QListWidget *lb);
};
#endif
