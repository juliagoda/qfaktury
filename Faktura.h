#ifndef Faktura_H
#define Faktura_H
#include <QDialog>
#include "Settings.h"
#include "tabletemp.h"
#include "Podglad.h"



#include "ui_Faktura.h"
class Faktura: public QDialog, public Ui::Faktura {
Q_OBJECT
public:
	Faktura(QWidget *parent);
	void init();
	void readData(QString fraFile, int co);
	QString fName, progDir2, ret, vatAll, templDir;
	double priceBRabN, priceBRab;
	bool pforma;
public slots:
	void getKontrahent();
	void addTow();
	void rabatChange();
	void delTowar();
	void editTowar();
	void backBtnClick();
	void makeData();
	void canCancel();
private:
	Settings settings;
	int type;
	QString lastInvoice;
	bool isEdit;
	TableTemp tabletemp;
	void countRabat();
	void countSum();
	void makeInvoiceHeadar();
	void makeInvoiceBody();
	void makeInvoiceGoods();
	void makeInvoiceSumm();
	void makeInvoiceSummAll();
	void makeInvoice();
	void saveInvoice();
	void makeInvoiceFooter();
	QString getStawkami();
	QString numbersCount(int in, int x);
};
#endif
