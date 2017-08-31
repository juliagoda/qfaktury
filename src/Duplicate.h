/*
 * Duplicat.h
 *
 *  Created on: Mar 31, 2009
 *      Author: moux
 */
#include "detector.h"
#if _pragma_once_support
#pragma once
#endif
#ifndef DUPLICATE_H_
#define DUPLICATE_H_

#include "Invoice.h"
#include <KDateComboBox>

class Duplicate : public Invoice {

  Q_OBJECT

public:
  Duplicate(QWidget *parent, IDataLayer *dl, QString in_form, bool ifEdited);
  ~Duplicate();

  virtual void setData(InvoiceData &invData);

public slots:

  virtual void canQuit();
  void duplicateInit();

protected:
  virtual void makeInvoiceHeadar(bool sellDate, bool breakPage, bool original);

private:
  KDateComboBox *duplicateDate;
  QLabel *labelDupDate;
  bool editMode;
};
#endif /* DUPLICATE_H */
