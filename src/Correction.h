#pragma once

#include "Invoice.h"
#include "InvoiceData.h"
#include "ui_Invoice.h"

#include "alias/memory.hpp"

#include <QComboBox>
#include <QPointer>

class Correction : public Invoice
{
	Q_OBJECT

public:
	Correction(QWidget *parent, IDataLayer *dl, QString in_form = QString(), bool edMode = false);

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
	UPtr<InvoiceData> createOriginalInv() const;

private:
	bool editMode;
	bool firstRunned;
	double origDiscTotal, origNettTotal, origGrossTotal;
	double diffTotal;
	double origGrossBureau;
	UPtr<InvoiceData> invData;
	QPointer<QComboBox> reasonCombo;
	QPointer<QLabel> labelReason1;
	QString ret;
	QString fName;
};
