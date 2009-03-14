#ifndef Korekta_H
#define Korekta_H
#include <QDialog>

#include "ui_Faktura.h"
#include "Faktura.h"
#include "InvoiceData.h"


class Korekta: public Faktura {
Q_OBJECT
public:
	Korekta(QWidget *parent);
	~Korekta();
	bool editMode;
	virtual void korektaInit(bool mode); // called outside
public slots:
	// to be overwritten in child class
	virtual void backBtnClick();
	virtual void saveInvoice();
	virtual void makeInvoice();
	virtual void canQuit();
private:
	InvoiceData *invData;
	QComboBox *reasonCombo;
	QLabel *labelReason1;
	virtual void calculateDiscount();
	virtual void calculateSum();
	virtual QString getGroupedSums();
	virtual void makeInvoiceSummAll();
	virtual void makeInvoceProductsTitle(short a);
	virtual void makeBeforeInvoiceProducts();
	virtual void makeBeforeInvoiceSumm();
	InvoiceData *createOriginalInv();
	virtual void setIsEditAllowed(bool isAllowed);
protected:
	double origDiscTotal, origNettTotal, origGrossTotal;
	double diffTotal;
};
#endif
