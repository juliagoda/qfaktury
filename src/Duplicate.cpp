/*
 * Duplicate.cpp
 *
 *  Created on: Mar 31, 2009, improved on Dec 2016
 *      Author: moux, juliagoda
 */

#include "Duplicate.h"

// constructor
Duplicate::Duplicate(QWidget *parent, IDataLayer *dl, QString in_form, bool ifEdited)
	: Invoice(parent, dl, in_form)
	, editMode(ifEdited)
{
}

Duplicate::~Duplicate()
{
	if (labelDupDate != 0)
		labelDupDate = 0;
	delete labelDupDate;

	if (duplicateDate != 0)
		duplicateDate = 0;
	delete duplicateDate;
}

void Duplicate::duplicateInit()
{
	labelDupDate = new QLabel(this);
	labelDupDate->setText(trUtf8("Data duplikatu:"));
	labelDupDate->setAlignment(Qt::AlignRight);
	addDataLabels->addWidget(labelDupDate);

	duplicateDate = new QDateEdit(this);
	duplicateDate->setObjectName(QString::fromUtf8("duplicateDate"));
	duplicateDate->setCalendarPopup(true);
	duplicateDate->setDisplayFormat(sett().getDateFormat());

	if (!editMode)
	{
		duplicateDate->setDate(QDate::currentDate());
	}
	else
	{
		duplicateDate->setDate(dupDate);
		duplicateDate->setEnabled(false);
	}

	addData->addWidget(duplicateDate);

	setIsEditAllowed(false); // since it's a duplicate
	saveBtn->setEnabled(true);

	connect(closeBtn, SIGNAL(clicked()), this, SLOT(cancelDupl()));
}

void Duplicate::setData(InvoiceData &invData)
{
	invData.id = getfName();
	invData.customer = buyerName->text();
	invData.invNr = invNr->text();
	invData.sellingDate = sellingDate->date();
	invData.issueDate = productDate->date();

	if (constRab->isChecked())
		invData.discount = discountVal->value();
	else
		invData.discount = 0;

	// lp, name, code, pkwiu, amount, unit, discount, unit price, net, vat, gross
	for (int i = 0; i < tableGoods->rowCount(); ++i)
	{
		ProductData product; //  = new ProductData();

		product.setId(tableGoods->item(i, 0)->text());
		product.setName(tableGoods->item(i, 1)->text());
		product.setCode(tableGoods->item(i, 2)->text());
		product.setPkwiu(tableGoods->item(i, 3)->text());
		product.setQuantity(tableGoods->item(i, 4)->text());
		product.setQuanType(tableGoods->item(i, 5)->text());
		product.setDiscount(tableGoods->item(i, 6)->text());
		double help = tableGoods->item(i, 7)->text().toDouble();
		product.setPrice(sett().numberToString(help, 'f', 2));
		product.setNett(tableGoods->item(i, 8)->text());
		product.setVat(tableGoods->item(i, 9)->text());
		product.setGross(tableGoods->item(i, 10)->text());
		invData.products[i] = product;
	}

	invData.additText = additEdit->text();
	invData.paymentType = paysCombo->currentText();

	if (invData.paymentType == trUtf8("zaliczka"))
	{
		if (rComboWasChanged)
		{
			invData.custPaym.payment1 = custPaymData->payment1;
			invData.custPaym.date1 = custPaymData->date1;
			invData.custPaym.amount1 = custPaymData->amount1;

			invData.custPaym.payment2 = custPaymData->payment2;
			invData.custPaym.date2 = custPaymData->date2;
			invData.custPaym.amount2 = custPaymData->amount2;
		}
		else
		{
			QLocale locale;

			ratesCombo->setCurrentIndex(0);

			invData.custPaym.payment1 = sendKindInfo->text();
			invData.custPaym.date1 = locale.toDate(ratesCombo->itemText(0), sett().getDateFormat());
			invData.custPaym.amount1 = sett().stringToDouble(rateLabelInfo->text());
			invData.custPaym.date2 = locale.toDate(ratesCombo->itemText(1), sett().getDateFormat());

			invData.custPaym.amount2 = sett().stringToDouble(restLabelInfo->text());

			ratesCombo->setCurrentIndex(1);
			invData.custPaym.payment2 = sendKindInfo->text();
		}
	}

	invData.liabDate = liabDate->date();
	invData.currencyType = currCombo->currentText();

	invData.duplDate = duplicateDate->date();
}

/** Adds duplicate requirements
 */

void Duplicate::makeInvoiceHeadar(bool sellDate, bool breakPage, bool original)
{
	QString breakPageStr = "class=\"page_break\"";

	if (breakPage == false)
		breakPageStr = "";

	invStrList +=
		"<table comment=\"headar table\" width=\"100%\" border=\"0\"" + breakPageStr + ">";
	invStrList += "<tr>";
	invStrList += "<td width=\"60%\" align=\"center\" valign=\"bottom\">";
	invStrList += "<span class=\"stamp\">";

	QString logo = sett().value("logo").toString();

	if (logo != "")
		invStrList += "<img src=\"" + logo + "\" width=\"100\" " + " height=\"100\"+ >";
	else
		invStrList += trUtf8("Pieczęć wystawcy");

	invStrList += "</span>";
	invStrList += "</td>";
	invStrList += "<td align=\"right\">";
	invStrList += "<span style=\"font-size:12pt; font-weight:600\">";
	invStrList += invoiceType + "<br/>";
	invStrList += trUtf8("Nr: ") + invNr->text() + "<br></span>";
	invStrList += "<span style=\"font-size:11pt; font-weight:600\">";
	invStrList += trUtf8("Duplikat z dnia: ") + "<b>"
		+ duplicateDate->date().toString(sett().getDateFormat()) + "</b></span><br>";
	invStrList += "<span class=\"dates\">" + trUtf8("Data wystawienia: ")
		+ productDate->date().toString(sett().getDateFormat()) + "<br>";

	if (sellDate)
		invStrList += trUtf8("Data sprzedaży: ")
			+ sellingDate->date().toString(sett().getDateFormat()) + "<br>";

	invStrList += "</span>";
	invStrList += "</td><td width=\"3%\">&nbsp;</td>";
	invStrList += "</tr>";
	invStrList += "<tr>";
	invStrList += "<td colspan=\"2\" align=\"right\" valign=\"top\"><br>";

	if (original)
		invStrList += trUtf8("ORYGINAŁ");
	else
		invStrList += trUtf8("KOPIA");

	invStrList += "<br></td><td width=\"3%\">&nbsp;</td>";
	invStrList += "</tr>";
	invStrList += "</table>";
	invStrList += "<hr>";
	invStrList += "</td></tr>";
}

/** Slot
 *  canQuit slot
 */

void Duplicate::canQuit()
{
	if (canClose)
	{
		qDebug("if canClose true");
		accept();
	}
	else
	{
		if (QMessageBox::warning(
				this,
				"QFaktury",
				trUtf8("Dane zostały zmienione czy chcesz zapisać?"),
				trUtf8("Tak"),
				trUtf8("Nie"),
				0,
				0,
				1)
			== 1)
		{
			saveColumnsWidth();
			reject();
		}
		else
		{
			saveInvoice();

			if (saveFailed)
			{
				return;
			}

			saveColumnsWidth();
			accept();
		}
	}
}

void Duplicate::cancelDupl()
{
	reject();
}
