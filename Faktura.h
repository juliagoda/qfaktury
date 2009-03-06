#ifndef Faktura_H
#define Faktura_H
#include <QDialog>
#include "Settings.h"

#include "ui_Faktura.h"

class Faktura: public QDialog, public Ui::Faktura {
Q_OBJECT
public:
	Faktura(QWidget *parent);
	void init();
	void readData(QString fraFile, int co);
	QString fName, ret;
	bool pforma;
public slots:
	void getCustomer();
	void addTow();
	void discountChange();
	void delTowar();
	void editTowar();
	void backBtnClick();
	void canQuit();
	void saveInvoice();
	void makeInvoice();
	void print(QPrinter*);
	void tableActivated ( QTableWidgetItem * item );
	void textChanged(QString someStr);
	void payTextChanged(QString someStr);
	void dateChanged (QDate someDate);
	void discountConstChange();
private:
	QStringList fraStrList;

	int type;
	QString lastInvoice, invoiceType;
	bool isEdit;
	bool canClose;
	bool saveFailed;
	void calculateDiscount();
	void calculateSum();
	QString getGroupedSums();
	void saveColumnsWidth();

	void makeInvoiceHeadar();
	void makeInvoiceBody();
	void makeInvoiceProducts();
	void makeInvoiceSumm();
	void makeInvoiceSummAll();
	void makeInvoiceFooter();

	QString numbersCount(int in, int x);
	void calculateOneDiscount(int a);
};
#endif
