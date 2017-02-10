#ifndef INVOICE_H
#define INVOICE_H

#include <QDialog>
#include <QDomElement>
#include <QDomDocument>
#include <QPrinter>
#include <QMap>
#include <QWebEnginePage>
#include <QComboBox>

#include "ConvertAmount.h"

#include "CustomPaymData.h"

#include "IDataLayer.h"
#include "InvoiceData.h"
#include "ui_Invoice.h"

enum InvoiceType {FVat, FPro, EFVat, EFPro, KBR, BILL, DUP};

class Invoice: public QDialog, public Ui::Invoice {

Q_OBJECT

public:

    Invoice(QWidget *parent, IDataLayer *dl, QString Inv = QString());
    virtual ~Invoice();
    static Invoice * instance();
	void init();
    void readData(QString fraFile);
    QString const getRet() const;
    QString const getfName() const;
    QString const getInvForm() const;
    bool const getKAdded() const;
    void setfName(QString text);
    bool convWarn();

    virtual void setIsEditAllowed(bool isAllowed);
	void keyPressEvent(QKeyEvent * event);
    void connectedWebsite(const QUrl&);
    QMap<QString,double> getActualCurList();
    QMap<QString,double> tableOfValues();
    virtual void calcAll(const double&);
    void templateCurr(const QString&);
    bool ifUpdated();
    QString checkInvCurr();
	virtual void calculateOneDiscount(int a);
    QString pressedTxt() const;
    void convertMoneyFunc(QString );
    inline void setTextDurRate(QString,QString,QString);
    void whatTypeFromTitle(QString title, bool ifForm, bool kadded, InvoiceType invTyp, int numbType);


public slots:

	void getCustomer();
    virtual void addGoods();
	virtual void discountChange();
    void delGoods();
    void editGoods();
	void tableActivated ( QTableWidgetItem * item );
	void textChanged(QString someStr);
    virtual void payTextChanged(QString someStr);
	void dateChanged (QDate someDate);
	virtual void discountConstChange(); // Overwritten in FakturaBrutto
	// to be overwritten in child class
	virtual void backBtnClick();
	virtual void canQuit();
	virtual bool saveInvoice();
	virtual void makeInvoice();
	void printSlot(QPrinter*);
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
    QComboBox *ratesCombo;
    QLabel *labelRate;
    QLabel *rateLabel;
    QLabel *restLabel;
    QLabel *sendKind;
    QLabel *rateLabelInfo;
    QLabel *restLabelInfo;
    QLabel *sendKindInfo;
	IDataLayer *dataLayer;
	QString lastInvoice, invoiceType;
	double discountTotal, nettTotal, grossTotal;
	bool canClose;
	bool saveFailed;
	CustomPaymData *custPaymData;
    QStringList invStrList;
	QString numbersCount(int in, int x);
	int type;
    bool rComboWasChanged;
    bool goodsEdited;
    double am1, am2;

	virtual void calculateDiscount();
	virtual void calculateSum();
	QString getGroupedSums();
	void saveColumnsWidth();
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

	void makeInvoiceFooter();

	virtual QString getInvoiceTypeAndSaveNr();
	bool validateForm();


private:

    static Invoice * m_instance;
    QNetworkAccessManager *manager;
    QFile file;
    QNetworkReply *reply;
    QString pressedText;
    QDomDocument doc;
    QString fName, ret, inv_form;
    bool pforma, kAdded, ifCSS;

};
#endif
