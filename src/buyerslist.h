
#include "detector.h"
#if _pragma_once_support
#pragma once
#endif
#ifndef BUYERSLIST_H
#define BUYERSLIST_H

#include "ui_buyerslist.h"

#include <QtXml/qdom.h>

// class for choosing buyer with GUI, when a document is created
class BuyersList : public QDialog, public Ui::BuyersList {

  Q_OBJECT

public:
  BuyersList(QWidget *parent);
  const QString getRetBuyerList();

public slots:

  void readBuyer();
  void doAccept();
  void comboBox1Changed();
  void updateDetails(QListWidgetItem *);

private:
  QStringList companiesList;
  QStringList officesList;
  QStringList personsList;
  QString ret;

  void init();
  void displayDetails(QStringList custDetails);
  void clearDetails();
  QString xmlDataToString(QDomNode n);
  QString detailsToString();
};
#endif
