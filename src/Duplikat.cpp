/*
 * Duplikat.cpp
 *
 *  Created on: Mar 31, 2009
 *      Author: moux
 */
#include "moc_Duplikat.cpp"
#include <QLabel>

// constructor
Duplikat::Duplikat(QWidget *parent, IDataLayer *dl): Faktura(parent, dl) {
	// editMode = false;
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
    duplicateDate->setDate(QDate::currentDate());
	addData->addWidget(duplicateDate);

	setIsEditAllowed(false); // since it's a duplikat
	saveBtn->setEnabled(false);
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
	reject();
}

