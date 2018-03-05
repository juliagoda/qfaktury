#include "detector.h"
#if _pragma_once_support
#pragma once
#endif
#ifndef SEND_H
#define SEND_H

#include <QWizard>

#include "buyerdata.h"
#include "buyers.h"
#include "invoicedata.h"
#include "emailwindow.h"

class EmailWindow;
class QLabel;
class QLineEdit;
class QGroupBox;
class QTableWidget;

// class for creating wizard window, used for sending emails with invoices to
// buyers
class Send : public QWizard {
  Q_OBJECT

public:
  Send(QVector<BuyerData>, QVector<InvoiceData>, QWidget *parent = 0);

  void accept() override;

private:
  QVector<BuyerData> bList;
  QVector<InvoiceData> iList;

   Q_DISABLE_COPY( Send )
};


class IntroPage : public QWizardPage {
  Q_OBJECT

public:
  IntroPage(QWidget *parent = 0);

private:
  QLabel *label;

};


class ClassInvoicePage : public QWizardPage {
  Q_OBJECT

public:
  ClassInvoicePage(QVector<BuyerData>, QVector<InvoiceData>,
                   QWidget *parent = 0);

protected:
  bool validatePage() override;
  QString transformType(QString);

private:
  QVector<BuyerData> bList;
  QVector<InvoiceData> iList;
  QTableWidget *invoicesList;

};


class EmailPage : public QWizardPage {
  Q_OBJECT

public:
  EmailPage(QWidget *parent = 0);
  void setHostPort(QString, QString);

protected:
  void initializePage() override;

private slots:
  void setSSL(bool);
  void setTCP(bool);
  void setTLS(bool);
  void setGmail(bool);
  void seto2(bool);
  void setYahoo(bool);
  void setInteria(bool);
  void setOnet(bool);
  void setWP(bool);
  void setHotMail(bool);
  void setGazeta(bool);
  void setAol(bool);
  void setFoxMail(bool);
  void setOutlook(bool);

private:
  QLabel *label;
  QGroupBox *groupBox;
  bool checkedMailButton;
  bool checkedPortButton;
  QString protocol;
  QString checkedMail;
  QLineEdit *edit1;
  QLineEdit *edit2;

};


class ConclusionPage : public QWizardPage {
  Q_OBJECT

public:
  ConclusionPage(QWidget *parent = 0);

protected:
  void initializePage() override;

private slots:
  void getTemplateOne(bool);
  void getTemplateTwo(bool);
  void getTemplateThree(bool);

private:
  EmailWindow *emailWindow;

};

#endif // SEND_H
