#include "detector.h"
#if _pragma_once_support
#pragma once
#endif
#ifndef USER_H
#define USER_H

#include "ui_User.h"

// class for creating, saving and updating user account with GUI
class User : public QDialog, public Ui::User {

  Q_OBJECT

public:
  User(QWidget *parent);

public slots:

  void init();
  void okClick();
  bool checkAll();

private slots:

  void on_nextSeller_clicked();
  void delcurrSel();
  void on_addAcc_clicked();
  void on_remAcc_clicked();
  void on_accountsCombo_currentTextChanged(const QString &arg1);
  void on_addTel_clicked();
  void on_remTel_clicked();
  void on_telsCombo_currentTextChanged(const QString &arg1);
  void on_addFax_clicked();
  void on_remFax_clicked();
  void on_faxesCombo_currentTextChanged(const QString &arg1);
  void on_addEmail_clicked();
  void on_remEmail_clicked();
  void on_emailsCombo_currentTextChanged(const QString &arg1);

private:
  QList<QWidget *> sellersWidgets;

  bool cameFromOldVersion();
  void prepareFor_0_7_1(bool cameFromOlder);
};
#endif
