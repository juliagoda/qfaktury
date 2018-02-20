#include "detector.h"
#if _pragma_once_support
#pragma once
#endif
#ifndef CHANGEAMOUNT_H
#define CHANGEAMOUNT_H

#include "ui_changeamount.h"

class QLabel;
class QSpinBox;

// class for changing quantity of good/service with GUI
class ChangeAmount : public QDialog, public Ui::ChangeAmount {

  Q_OBJECT

public:
  ChangeAmount(QWidget *parent);
  ~ChangeAmount();
  static ChangeAmount *instance();
  void init();

  QLabel *requiredAm;
  QLabel *givedOutAm;
  QSpinBox *requiredAmBox;
  QSpinBox *givedOutBox;

private:
  static ChangeAmount *m_instance;
};
#endif
