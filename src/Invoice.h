#include "detector.h"
#if _pragma_once_support
#pragma once
#endif
#ifndef INVOICE_H
#define INVOICE_H

#include <QDomDocument>
#include <QDomElement>

#include "ConvertAmount.h"
#include "InvoiceData.h"
#include "ui_Invoice.h"

class QPrinter;
class QNetworkAccessManager;
class QNetworkReply;
class CustomPaymData;
class QLabel;
class QComboBox;
class QKeyEvent;
class IDataLayer;

enum InvoiceType { FVat, FPro, EFVat, EFPro, KBR, BILL, DUP, RR };

class Invoice : public QDialog, public Ui::Invoice {

  Q_OBJECT

public:
  Invoice(QWidget *parent, IDataLayer *dl, QString Inv = QString());
  virtual ~Invoice();

  static Invoice *instance();
  void init();
  void readData(QString fraFile);
  void setfName(QString text);
  void keyPressEvent(QKeyEvent *event);
  void connectedWebsite(const QUrl &);
  void templateCurr(const QString &);
  void convertMoneyFunc(QString);
  void whatTypeFromTitle(const QString title, bool ifForm, bool kadded,
                         InvoiceType invTyp, int numbType);
  const QString getRet();
  const QString getfName();
  const QString getInvForm();
  const QString pressedTxt();
  const bool getKAdded();
  bool convWarn();
  bool ifUpdated();
  virtual void setIsEditAllowed(bool isAllowed);
  virtual void calcAll(const double &);
  virtual void calculateOneDiscount(int a);
  inline void setTextDurRate(QString, QString, QString);
  QMap<QString, double> getActualCurList();
  QMap<QString, double> tableOfValues();
  QString checkInvCurr();

public slots:

  virtual void addGoods();
  virtual void discountChange();
  virtual void backBtnClick();
  virtual void canQuit();
  virtual bool saveInvoice();
  virtual void makeInvoice();
  virtual void payTextChanged(QString someStr);
  virtual void discountConstChange(); // Overwritten in GrossInvoice
  void getCustomer();
  void delGoods();
  void editGoods();
  void tableActivated(QTableWidgetItem *item);
  void textChanged(QString someStr);
  void dateChanged(QDate someDate);
  void printSlot(QPrinter *);
  void buyerClick();
  void tellFinished();
  void httpReadyRead();
  void rateDateChanged(QString);

protected:
  QDate dupDate;
  QString prepayFile;
  QString lastInvoice, invoiceType;
  QComboBox *ratesCombo;
  QLabel *labelRate;
  QLabel *rateLabel;
  QLabel *restLabel;
  QLabel *sendKind;
  QLabel *rateLabelInfo;
  QLabel *restLabelInfo;
  QLabel *sendKindInfo;
  IDataLayer *dataLayer;
  double discountTotal, nettTotal, grossTotal;
  double am1, am2;
  bool canClose;
  bool saveFailed;
  bool rComboWasChanged;
  bool goodsEdited;
  CustomPaymData *custPaymData;
  QStringList invStrList;
  int type;
  QString fName;
  bool ifCSS;

  QString getGroupedSums();
  QString numbersCount(int in, int x);
  void saveColumnsWidth();
  void makeInvoiceFooter();
  virtual void calculateDiscount();
  virtual void calculateSum();
  virtual void makeInvoiceHeadar(bool sellDate, bool brakePage, bool original);
  virtual void makeInvoiceBody();
  virtual void print();
  virtual void makeInvoiceProducts();
  virtual void makeInvoiceSumm();
  virtual void makeInvoiceSummAll();
  virtual void makeInvoiceProductsHeadar();
  virtual void makeInvoiceFooterHtml();
  virtual void makeInvoiceHeadarHTML();
  virtual void setData(InvoiceData &invData);
  virtual void getData(InvoiceData invData);
  virtual QString getInvoiceTypeAndSaveNr();
  bool validateForm();

private:
  void algorithmCurrencies(QString, QStringList, QMap<QString, double> &);
  void convertCurrShort(QString);

  static Invoice *m_instance;
  QNetworkAccessManager *manager;
  QFile file;
  QNetworkReply *reply;
  QString pressedText;
  QString ret, inv_form;
  QDomDocument doc;
  bool pforma, kAdded;
};
#endif
