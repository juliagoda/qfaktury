#include "detector.h"
#if _pragma_once_support
#pragma once
#endif
#ifndef SETTING_H
#define SETTING_H

#include "ui_setting.h"

class QTextCodec;

// class for creating window with settings with GUI
class Setting : public QDialog, public Ui::Setting {

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
  void checkCurrCsvFormat(bool);
  void blockCsvCheckboxPath(int);
  void blockBackupCheckboxPath(int);
  void blockBackupCheckbox(int);
  void checkOnlyOneInterval(bool);
  void fillPath(bool);

private:
  bool read;
  void init();
  void sumSize();
  void saveSettings();
  void readSettings();
  void getEncodings();
  void helpFuncAddNr(QLineEdit *, QListWidget *, QString const &);
  void helpFuncDelNr(QListWidget *, QString const &);
  void helpFuncAp(QListWidget *);
  void helpFuncDown(QListWidget *);
  QStringList getTemplates();
  QStringList getTranslations();
  QStringList getStyles();
  QString getAll(QListWidget *lb);
  QVector<QTextCodec *> codecs;

  inline QString settWriteBackup ()
  {
     if (backupOnceDay->isChecked()) return "1D";
     else if (backupOnceWeek->isChecked()) return "1W";
     else if (backupOnceMonth->isChecked()) return "1M";
     else if (backupEveryHour->isChecked()) return QString::number(howManyHours->value()) + "h";
     else if (backupEveryMin->isChecked()) return QString::number(howManyMin->value()) + "m";
     else return "none";
  }

  inline void settReadBackup (QString settValue)
  {
      if (settValue != "none") {
          if (settValue == "1D") backupOnceDay->setChecked(true);
          else if (settValue == "1W") backupOnceWeek->setChecked(true);
          else if (settValue == "1M") backupOnceMonth->setChecked(true);
          else if (settValue.back() == 'h') { backupEveryHour->setChecked(true); settValue.chop(1); howManyHours->setValue(settValue.toInt()); }
          else if (settValue.back() == 'm') { backupEveryMin->setChecked(true); settValue.chop(1); howManyMin->setValue(settValue.toInt()); }
      }
  }

  inline void uncheckRadio (QRadioButton* btn)
  {
      btn->setAutoExclusive(false);
      btn->setChecked(false);
      btn->setAutoExclusive(true);
      btn->setEnabled(false);
  }
};
#endif
