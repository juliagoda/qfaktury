#include "detector.h"
#if _pragma_once_support
#pragma once
#endif
#ifndef CORRECTION_H
#define CORRECTION_H

#include "invoice.h"
#include "ui_Invoice.h"

class QComboBox;
class InvoiceData;
class QLabel;

// class for creation correction document with GUI, using invoice class as
// parent
class Correction : public Invoice {

  Q_OBJECT

public:
  Correction(QWidget *parent, IDataLayer *dl, QString in_form = QString(),
             bool edMode = false);
  virtual ~Correction();
  bool getMode() const;
  bool getFirstRun() const;
  QString const getRet();
  void schemaCalcSum();
  virtual void correctionInit(bool mode);
  virtual void readCorrData(QString fraFile);

public slots:

  // have to be overwritten in child class
  virtual bool saveInvoice();
  virtual void backBtnClick();
  virtual void makeInvoice(bool to_print = true);
  virtual void canQuit();

protected:
  virtual void makeInvoiceSummAll();
  virtual void makeInvoiceSumm();
  virtual void makeInvoceProductsTitle(short a);
  virtual void makeBeforeCorrProducts();
  virtual void makeBeforeCorrSumm();
  virtual void setIsEditAllowed(bool isAllowed);
  virtual void calculateDiscount();
  virtual void calculateSum();
  virtual void calculateOneDiscount(int i);
  virtual QString getInvoiceTypeAndSaveNr();
  InvoiceData *createOriginalInv();

private:
  bool editMode;
  bool firstRunned;
  double origDiscTotal, origNettTotal, origGrossTotal;
  double diffTotal;
  double origGrossBureau;
  InvoiceData *invData;
  QComboBox *reasonCombo;
  QLabel *labelReason1;
  QString ret, fName;
};
#endif
