#pragma once

#include "ConvertAmount.h"
#include "CustomPaymData.h"
#include "IDataLayer.h"
#include "ui_Invoice.h"

#include <QDomDocument>
#include <QDomElement>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPrinter>

enum InvoiceType
{
	FVat,
	FPro,
	EFVat,
	EFPro,
	KBR,
	BILL,
	DUP,
	RR
};

class Invoice : public QDialog, public Ui::Invoice
{
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
	void whatTypeFromTitle(
		QString title,
		bool ifForm,
		bool kadded,
		InvoiceType invTyp,
		int numbType);
	QString getRet() const;
	QString getfName() const;
	QString getInvForm() const;
	QString pressedTxt() const;
	bool getKAdded() const;
	bool convWarn();
	bool ifUpdated();
	virtual void setIsEditAllowed(bool isAllowed);
	void calcAll(double);
	virtual void calculateOneDiscount(int i);
	void setTextDurRate(QString, QString, QString);
	QMap<QString, double> getActualCurList();
	QMap<QString, double> tableOfValues();
	QString checkInvCurr();

public slots:
	virtual void addGoods();
	void discountChange();
	virtual void backBtnClick();
	virtual void canQuit();
	virtual bool saveInvoice();
	virtual void makeInvoice();
	void payTextChanged(QString text);
	void discountConstChange();
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
	void changeToUSD();
	void changeToEUR();
	void changeToPLN();
	void changeToCHF();
	void changeToGBP();
	void changeToRUB();
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
	virtual void makeInvoiceHeadar(bool sellDate, bool breakPage, bool original);
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
	bool pforma, kAdded;
};
