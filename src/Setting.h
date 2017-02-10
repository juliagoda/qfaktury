#ifndef SETTING_H
#define SETTING_H

#include <QDialog>
#include <QSettings>
#include "ui_Setting.h"
#include <QListWidget>

class Setting: public QDialog, public Ui::Setting {

Q_OBJECT

public:

    Setting(QWidget *parent);


public slots:

	void apply();
	void okButtonClick();
	void addLogoBtnClick();
	void currAddBtnClick();
	void currDelBtnClick();
    void corAddBtnClick();
    void corDelBtnClick();
	void vatAddBtnClick();
	void vatDelBtnClick();
	void vatUpBtnClick();
	void vatDownBtnClick();
	void currencyAddBtnClick();
	void currencyDelBtnClick();
	void paymUpBtnClick();
	void paymDownBtnClick();
	void paymDelBtnClick();
    void saveBtnEnable();
	void paymAddBtnClick();
	void defTextBtnClick();
	void setDefaultClick();
	void workingDirBtnClick();


private:

	bool read;
	void init();
	void sumSize();
	void saveSettings();
	void readSettings();
	void getEncodings();
    void helpFuncAddNr(QLineEdit*, QListWidget* , QString const&);
    void helpFuncDelNr(QListWidget* , QString const&);
    void helpFuncAp(QListWidget*);
    void helpFuncDown(QListWidget*);
	QStringList getTemplates();
	QStringList getTranslations();
    QStringList getStyles();
	QString getAll(QListWidget *lb);
    QVector<QTextCodec *> codecs;

};
#endif
