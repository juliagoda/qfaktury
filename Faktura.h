#ifndef Faktura_H
#define Faktura_H
#include <QDialog>
#include <QDomElement>
#include <QDomDocument>

#include "ConvertAmount.h"
#include "Settings.h"


#include "ui_Faktura.h"

class Faktura: public QDialog, public Ui::Faktura {
Q_OBJECT
public:
	Faktura(QWidget *parent);
	virtual ~Faktura();
	void init();
	void readData(QString fraFile, int co);
	QString fName, ret;
	bool pforma;
	virtual void setIsEditAllowed(bool isAllowed);
public slots:
	void getCustomer();
	void addTow();
	virtual void discountChange();
	void delTowar();
	void editTowar();
	void tableActivated ( QTableWidgetItem * item );
	void textChanged(QString someStr);
	void payTextChanged(QString someStr);
	void dateChanged (QDate someDate);
	virtual void discountConstChange(); // Overwritten in FakturaBrutto
	// to be overwritten in child class
	virtual void backBtnClick();
	virtual void canQuit();
	virtual void saveInvoice();
	virtual void makeInvoice();
	void printSlot(QPrinter*);
protected:
	QString lastInvoice, invoiceType;
	double discountTotal, nettTotal, grossTotal;
	bool isEdit;
	bool canClose;
	bool saveFailed;
	QStringList fraStrList;
	QString numbersCount(int in, int x);
	int type;
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
	void makeInvoiceFooter();
	virtual void calculateOneDiscount(int a);
	QDomElement createSellerElement(QDomDocument doc);
	QDomElement createBuyerElement(QDomDocument doc);
	bool validateForm();
};
#endif
