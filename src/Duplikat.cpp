/*
 * Duplikat.cpp
 *
 *  Created on: Mar 31, 2009
 *      Author: moux
 */
#include "moc_Duplikat.cpp"
#include "Duplikat.h"
#include <QLabel>
#include <QSpinBox>

// constructor
Duplikat::Duplikat(QWidget *parent, IDataLayer *dl, QString in_form): Faktura(parent, dl, in_form) {
    editMode = false;
}

void Duplikat::duplikatInit() {
	QLabel *labelDupDate = new QLabel(this);
	labelDupDate->setText(trUtf8("Data duplikatu:"));
	labelDupDate->setAlignment(Qt::AlignRight);
	addDataLabels->addWidget(labelDupDate);

    duplicateDate = new QDateEdit(this);
    duplicateDate->setObjectName(QString::fromUtf8("duplicateDate"));
    duplicateDate->setCalendarPopup(true);
    duplicateDate->setDisplayFormat(sett().getDateFormat());

    if (!editMode) {
        duplicateDate->setDate(QDate::currentDate());
    } else {
        duplicateDate->setDate(dupDate);
        duplicateDate->setEnabled(false);
    }

	addData->addWidget(duplicateDate);

	setIsEditAllowed(false); // since it's a duplikat
    saveBtn->setEnabled(true);

    connect(closeBtn, SIGNAL(clicked()), this, SLOT(cancelDupl()));
}


void Duplikat::setData(InvoiceData &invData) {

    invData.id = fName;
    invData.customer = kontrName->text();
    invData.frNr = frNr->text();
    invData.sellingDate = sellingDate->date();
    invData.issueDate = productDate->date();
    if (constRab->isChecked())
        invData.discount = rabatValue->value();
    else
        invData.discount = 0;

    // lp, nazwa, kod, pkwiu, ilosc, jm, rabat, cena jm., netto, vat, brutto
    for (int i = 0; i < tableTow->rowCount(); ++i) {

        ProductData product; //  = new ProductData();

        product.setId(tableTow->item(i, 0)->text());
        product.setName(tableTow->item(i, 1)->text());
        product.setCode(tableTow->item(i, 2)->text());
        product.setPkwiu(tableTow->item(i, 3)->text());
        product.setQuantity(tableTow->item(i, 4)->text());
        product.setQuanType(tableTow->item(i, 5)->text());
        product.setDiscount(tableTow->item(i, 6)->text());
        double help = tableTow->item(i, 7)->text().toDouble();
        product.setPrice(sett().numberToString(help,'f',2));
        product.setNett(tableTow->item(i, 8)->text());
        product.setVat(tableTow->item(i, 9)->text());
        product.setGross(tableTow->item(i, 10)->text());
        invData.products[i] = product;
    }

    invData.additText = additEdit->text();
    invData.paymentType = platCombo->currentText();

    if (invData.paymentType == trUtf8("zaliczka")) {
        if (rComboWasChanged) {

            invData.custPaym.payment1 = custPaymData->payment1;
            invData.custPaym.date1 = custPaymData->date1;
            invData.custPaym.amount1 = custPaymData->amount1;

            invData.custPaym.payment2 = custPaymData->payment2;
            invData.custPaym.date2 = custPaymData->date2;
            invData.custPaym.amount2 = custPaymData->amount2;

        } else {

            QLocale locale;

            ratesCombo->setCurrentIndex(0);

            invData.custPaym.payment1 = sendKindInfo->text();
            invData.custPaym.date1 = locale.toDate( ratesCombo->itemText(0), sett().getDateFormat());
            invData.custPaym.amount1 = sett().stringToDouble(rateLabelInfo->text());
            invData.custPaym.date2 = locale.toDate( ratesCombo->itemText(1), sett().getDateFormat());

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
void Duplikat::makeInvoiceHeadar(bool sellDate, bool breakPage, bool original) {

	QString breakPageStr = "class=\"page_break\"";
	if (breakPage == false) breakPageStr = "";

	fraStrList += "<table comment=\"headar table\" width=\"100%\" border=\"0\"" + breakPageStr + ">";
	fraStrList += "<tr>";
    fraStrList += "<td width=\"60%\" align=\"center\" valign=\"bottom\">";
    fraStrList += "<span class=\"stamp\">";

    QString logo = sett().value("logo").toString();

    if (logo != "") {
        fraStrList += "<img src=\"" + logo + "\" width=\"100\" " + " height=\"100\"+ >";
    } else {
        fraStrList += trUtf8("Pieczęć wystawcy");
    }

    fraStrList += "</span>";
    fraStrList += "</td>";

    fraStrList += "<td align=\"right\">";
    fraStrList += "<span style=\"font-size:12pt; font-weight:600\">";
    fraStrList += invoiceType + "<br/>";
    fraStrList += trUtf8("Nr: ") + frNr->text() + "<br></span>";
    fraStrList += "<span style=\"font-size:11pt; font-weight:600\">";
    fraStrList += trUtf8("Duplikat z dnia: ") + "<b>" +
				duplicateDate->date().toString(sett().getDateFormat()) +  "</b></span><br>";
    fraStrList += "<span class=\"dates\">" + trUtf8("Data wystawienia: ")
				    + productDate->date().toString(sett().getDateFormat()) + "<br>";

    if (sellDate)
        fraStrList += trUtf8("Data sprzedaży: ")
				+ sellingDate->date().toString(sett().getDateFormat())
				+ "<br>";

    fraStrList += "</span>";
    fraStrList += "</td><td width=\"3%\">&nbsp;</td>";
	fraStrList += "</tr>";
	fraStrList += "<tr>";
    fraStrList += "<td colspan=\"2\" align=\"right\" valign=\"top\"><br>";

    if (original) {
		fraStrList += trUtf8("ORYGINAŁ");
    } else {
		fraStrList += trUtf8("KOPIA");
    }

    fraStrList += "<br></td><td width=\"3%\">&nbsp;</td>";
	fraStrList += "</tr>";
	fraStrList += "</table>";
	fraStrList += "<hr>";
	fraStrList += "</td></tr>";

}

/** Slot
 *  canQuit slot
 */
void Duplikat::canQuit() {

    if (canClose) {

        qDebug("if canClose true");
        accept();

    } else {

        if (QMessageBox::warning(this, "QFaktury", trUtf8("Dane zostały zmienione czy chcesz zapisać?"),
                    trUtf8("Tak"), trUtf8("Nie"), 0, 0,	1) == 1) {
            saveColumnsWidth();
            reject();

        } else {

            saveInvoice();
            if (saveFailed) {
                return;
            }
            saveColumnsWidth();
            accept();
        }
    }
}


void Duplikat::cancelDupl()
{
    reject();
}

