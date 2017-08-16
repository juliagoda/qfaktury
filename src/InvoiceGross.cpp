/*
 *  Created on: Apr 2, 2009
 *      Author: TPIELECH
 */

#include "InvoiceGross.h"
#include "GoodsGrossList.h"
#include "MainWindow.h"

// constructor
InvoiceGross::InvoiceGross(QWidget *parent, IDataLayer *dl, QString in_form)
	: Invoice(parent, dl, in_form)
{
}

void InvoiceGross::invoiceGrossInit()
{
	// invoiceType = "FB"
}

QString InvoiceGross::getInvoiceTypeAndSaveNr()
{
	QString itype = "FBrutto";
	sett().setValue("fvat", invNr->text());
	return itype;
}

/** Caclulate Discount
 */

void InvoiceGross::calculateOneDiscount(int i)
{
	// qDebug() << __FUNCTION__ << __LINE__ << __FILE__;

	double quantity = 0, vat = 0, gross = 0;
	double net = 0, price = 0;
	double discountValue = 0, discount;

	price = sett().stringToDouble(tableGoods->item(i, 7)->text());

	if (constRab->isChecked())
	{
		discount = discountVal->value() * 0.01;
	}
	else
	{
		discount = (tableGoods->item(i, 6)->text()).toInt() * 0.01;
	}

	if ((tableGoods->item(i, 6)->text()) == "0")
	{
		discount = 0;
		sum2->setText("0");
	}

	quantity = tableGoods->item(i, 4)->text().toInt();
	price = price * quantity;
	discountValue = price * discount;

	gross = price - discountValue;
	int vatValue = tableGoods->item(i, 9)->text().toInt();
	vat = (gross * vatValue) / (100 + vatValue);

	net = gross - vat;

	// qDebug() << price << quantity << net << discount << discountValue << vat << gross;

	tableGoods->item(i, 6)->setText(sett().numberToString(discount * 100, 'f', 0)); // discount
	tableGoods->item(i, 8)->setText(sett().numberToString(net)); // net
	tableGoods->item(i, 10)->setText(sett().numberToString(gross)); // gross
}

/** Slot
 *  Add new towar
 */

void InvoiceGross::addGoods()
{
	GoodsGrossList *goodsWindow = new GoodsGrossList(this);

	if (goodsWindow->exec() == QDialog::Accepted)
	{
		MainWindow::insertRow(tableGoods, tableGoods->rowCount());

		QStringList row = goodsWindow->getRetValGoodsBr().split("|");
		int rowNum = tableGoods->rowCount() - 1;
		tableGoods->item(rowNum, 0)->setText(sett().numberToString(tableGoods->rowCount())); // id
		tableGoods->item(rowNum, 1)->setText(row[0]); // name
		tableGoods->item(rowNum, 2)->setText(row[1]); // code
		tableGoods->item(rowNum, 3)->setText(row[2]); // pkwiu
		tableGoods->item(rowNum, 4)->setText(row[3]); // quantity
		tableGoods->item(rowNum, 5)->setText(row[4]); // qType
		tableGoods->item(rowNum, 6)->setText(row[5]); // discount
		tableGoods->item(rowNum, 7)->setText(row[6]); // price
		tableGoods->item(rowNum, 8)->setText(row[7]); // net
		tableGoods->item(rowNum, 9)->setText(row[8]); // vat
		tableGoods->item(rowNum, 10)->setText(row[9]); // gross
		saveBtn->setEnabled(true);
		canClose = false;

		if (constRab->isChecked())
		{
			calculateDiscount();
		}

		calculateSum();
	}

	delete goodsWindow;
	goodsWindow = NULL;
}
