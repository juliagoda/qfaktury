#include "detector.h"
#if _pragma_once_support
#pragma once
#endif
#ifndef GOODSLIST_H
#define GOODSLIST_H

#include "productdata.h"
#include "ui_GoodsList.h"

class QSpinBox;
class QLabel;

// class for choosing goods/services with GUI, when a document is created
class GoodsList : public QDialog, public Ui::GoodsList {

  Q_OBJECT

public:
  GoodsList(QWidget *parent);
  ~GoodsList();

  const QString getRetVal();
  const QMap<QString, int> getVatsVal();
  const QString getSelItem();
  const QString getGoodsId();
  static GoodsList *instance();
  void lockWidgetsDelNotes();
  void unlockWidgetsDelNotes();

public slots:

  virtual void doAccept();
  virtual void calcNet();
  void readGoods();
  void displayData(int x);
  void lv1selChanged();
  void displayNet(QString index);
  void spinChanged(int a);

protected:
  void init();
  typedef QHash<QString, ProductData *> ProductDataList;
  ProductDataList goodsList2;
  ProductDataList servicesList2;
  QString trimZeros(QString in);

private:
  QString ret;
  QString selectedItem;
  QString id;
  QMap<QString, QString> nets;
  QMap<QString, int> vats;
  QList<int> amounts;
  static GoodsList *m_instance;
  bool ifGoodIssueNote;
  QLabel* lab1;
  QLabel* lab2;
  QSpinBox* amountWant;
  QSpinBox* amountOut;
};
#endif
