#pragma once

#include <QComboBox>

#include "Invoice.h"
#include "InvoiceData.h"
#include "ui_Invoice.h"

class Correction : public Invoice
{
	Q_OBJECT

public:
	Correction(QWidget *parent, IDataLayer *dl, QString in_form = QString(), bool edMode = false);
	virtual ~Correction();
	bool getMode() const;
	bool getFirstRun() const;
	QString getRet() const;
	void schemaCalcSum();
	void correctionInit(bool mode);
	void readCorrData(QString invFile);

	void calculateOneDiscount(int i) override;
	void setIsEditAllowed(bool isAllowed) override;

public slots:
	bool saveInvoice() override;
	void backBtnClick() override;
	void makeInvoice() override;
	void canQuit() override;

protected:
	void makeInvoiceSummAll() override;
	void makeInvoiceSumm() override;
	void makeInvoceProductsTitle(short a);
	void makeBeforeCorrProducts();
	void makeBeforeCorrSumm();
	void calculateDiscount() override;
	void calculateSum() override;
	QString getInvoiceTypeAndSaveNr() override;
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
