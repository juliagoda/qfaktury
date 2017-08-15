#pragma once

#include "ui_Setting.h"

class Setting : public QDialog, public Ui::Setting
{
	Q_OBJECT

public:
	Setting(QWidget *parent);
	~Setting();

public slots:

	void apply();
	void okButtonClick();
	void addLogoBtnClick();
	void addStempBtnClick();
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
	void helpFuncAddNr(QLineEdit *lineEd, QListWidget *listWg, QString const &text);
	void helpFuncDelNr(QListWidget *listWg, QString const &text);
	void helpFuncAp(QListWidget *listWg);
	void helpFuncDown(QListWidget *listWg);
	QStringList getTemplates() const;
	QStringList getTranslations() const;
	QStringList getStyles() const;
	QString getAll(QListWidget *lb) const;
	QVector<QTextCodec *> codecs;
};
