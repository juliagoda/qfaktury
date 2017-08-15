/*
 * KorektaBrutto.cpp
 *
 *  Created on: Apr 3, 2009
 *      Author: moux
 */

#include "CorrectGross.h"
#include "GoodsGrossList.h"
#include "MainWindow.h"

/* Constructor
 */

CorrectGross::CorrectGross(QWidget *parent, IDataLayer *dl, QString in_form, bool edMode)
	: Correction(parent, dl, in_form, edMode)
{
}

QString CorrectGross::getInvoiceTypeAndSaveNr()
{
	sett().setValue("korNr", invNr->text());
	return "kbrutto";
}

/** Caclulate Discount
 */

void CorrectGross::calculateOneDiscount(int i)
{
	// qDebug() << __FUNCTION__ << __LINE__ << __FILE__;
	double quantity = 0, vat = 0, gross = 0;
	double net = 0, price = 0;
	double discountValue = 0, discount;

	price = sett().stringToDouble(tableGoods->item(i, 7)->text());

	if (constRab->isChecked())
		discount = discountVal->value() * 0.01;
	else
		discount = (tableGoods->item(i, 6)->text()).toInt() * 0.01;

	quantity = sett().stringToDouble(tableGoods->item(i, 4)->text());
	price = price * quantity;
	discountValue = price * discount;

	gross = price - discountValue;
	int vatValue = sett().stringToDouble(tableGoods->item(i, 9)->text());
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

void CorrectGross::addGoods()
{
	GoodsGrossList *goodsWindow = new GoodsGrossList(this);

	if (goodsWindow->exec() == QDialog::Accepted)
	{
		MainWindow::insertRow(tableGoods, tableGoods->rowCount());
		QStringList row = goodsWindow->getRetVal().split("|");
		int rowNum = tableGoods->rowCount() - 1;

		tableGoods->item(rowNum, 0)->setText(sett().numberToString(tableGoods->rowCount())); // id

		int i = 0;

		while (i < tableGoods->columnCount())
		{
			tableGoods->item(rowNum, i + 1)->setText(row[i]);
			i++;
		}

		canClose = false;

		if (constRab->isChecked())
			calculateDiscount();

		calculateSum();
	}

	delete goodsWindow;
	goodsWindow = 0;
}
