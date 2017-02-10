
#include <QMessageBox>
#include <QTextStream>
#include <QDesktopServices>
#include <QUrl>
#include <QListWidgetItem>

#include "BuyersList.h"

/** Constructor
 */
BuyersList::BuyersList(QWidget *parent): QDialog(parent) {
    setupUi(this);
    init();
}

/** Init
 */

void BuyersList::init() {

	// qDebug () << __FUNCTION__;

	companiesList.clear();
	officesList.clear();

	// read data
    readBuyer();

	// load data
	QString customer;
	listBox1->clear();
	foreach (customer, companiesList)
		listBox1->addItem(customer.split("|")[0]);

	// connects
    connect(okBtn, SIGNAL(clicked()), this, SLOT(doAccept()));
    connect(cancelBtn, SIGNAL(clicked()), this, SLOT(close()));
    connect(comboBox1, SIGNAL(activated(int)), this, SLOT(comboBox1Changed()));
    connect(listBox1, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(doAccept()));
    connect(listBox1, SIGNAL(itemSelectionChanged ()), this, SLOT(mouseSelect()));
    connect(listBox1, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(updateDetails(QListWidgetItem *)));
}


QString const BuyersList::getRetBuyerList() const
{
    return ret;
}

// *************************** SLOTS START *************************************

void BuyersList::mouseSelect() {

	// qDebug() << __FILE__ << __LINE__ << __FUNCTION__;
	updateDetails(listBox1->currentItem());
}

/** Slot
 *  Connected to accept signal
 */

void BuyersList::doAccept() {

    if (!listBox1->selectedItems().isEmpty()) {
		ret = detailsToString();
		accept();
	} else {
		QMessageBox::information(this, "QFaktury", trUtf8("Wskaż kontrahenta."),
				QMessageBox::Ok);
	}
}

/** Slot
 *  comboBox1 changed
 */

void BuyersList::comboBox1Changed() {

	// qDebug (__FUNCTION__);
	listBox1->clear();
	clearDetails();
	QString customer;

	switch (comboBox1->currentIndex()) {
	case 0:

		foreach (customer, companiesList)
			listBox1->addItem(customer.split("|")[0]);
		break;

	case 1:

		foreach (customer, officesList)
			listBox1->addItem(customer.split("|")[0]);
		break;

	}
}

/** Slot
 *  Update details when user selected
 */

void BuyersList::updateDetails(QListWidgetItem *item) {

    QStringList custDetails = QStringList();
    QString customer = QString();

	switch (comboBox1->currentIndex()) {
	case 0:

		foreach (customer, companiesList) {
			custDetails = customer.split("|");
			if (item->text().compare(custDetails[0]) == 0) {
				displayDetails(custDetails);
			}
		}
		break;

	case 1:

		foreach (customer, officesList) {
			custDetails = customer.split("|");
			if (item->text().compare(custDetails[0]) == 0) {
				displayDetails(custDetails);
			}
		}
		break;
	}
}

// *************************** SLOTS END *************************************

/** Load selected customer data
 */
void BuyersList::readBuyer() {

	QDomDocument doc(sett().getCustomersDocName());
	QDomElement root;
	QDomElement office;
	QDomElement company;

	QFile file(sett().getCustomersXml());

	if (!file.open(QIODevice::ReadOnly)) {
		qDebug() << "File" << file.fileName() << "doesn't exists";
		return;

	} else {

		QTextStream stream(&file);

		if (!doc.setContent(stream.readAll())) {
			qDebug("can not set content ");
			file.close();
			return;

		} else {

			root = doc.documentElement();
			office = root.firstChild().toElement();
			company = root.lastChild().toElement();
		}

		for (QDomNode n = company.firstChild(); !n.isNull(); n = n.nextSibling()) {

			companiesList.append(xmlDataToString(n));
		}

		for (QDomNode n = office.firstChild(); !n.isNull(); n = n.nextSibling()) {

			officesList.append(xmlDataToString(n));
		}
	}

    file.close();
}

/** Loads data one string
 */

QString BuyersList::xmlDataToString(QDomNode n) {

    QString text = QString();
	text = n.toElement().attribute("name") + "|";
	text += n.toElement().attribute("address") + "|";
	text += n.toElement().attribute("code") + " " + n.toElement().attribute("place") + "|";
	text += n.toElement().attribute("tic") + "|";
	text += n.toElement().attribute("account") + "|";
	text += n.toElement().attribute("phone") + "|";
	text += n.toElement().attribute("email") + "|";
	text += n.toElement().attribute("www");
	return text;
}

/** Loads data to labels
 */

void BuyersList::displayDetails(QStringList custDetails) {

	labelNameE->setText(custDetails[0]);
    labelAddressE->setText(custDetails[1]);
    labelCityE->setText(custDetails[2]);
    labelTicE->setText(custDetails[3]);
    labelAccountE->setText(custDetails[4]);
    labelPhoneE->setText(custDetails[5]);
    labelEmailE->setText(custDetails[6]);
    labelWWWE->setText("<a href=" + custDetails[7] + ">" + custDetails[7] + "</a>");
    labelWWWE->setStyleSheet("color: #1E90FF");
}

/** Clear labels
 */

void BuyersList::clearDetails() {

	labelNameE->setText("");
    labelAddressE->setText("");
    labelCityE->setText("");
    labelTicE->setText("");
    labelAccountE->setText("");
    labelPhoneE->setText("");
    labelEmailE->setText("");
    labelWWWE->setText("");
}

/** Labels to string
 */

QString BuyersList::detailsToString() {

	QString ret = labelNameE->text();

    if (!labelAddressE->text().isEmpty()) ret += "," +  labelAddressE->text();
    else ret += ",-";

    if (!labelCityE->text().isEmpty()) ret +=  "," + labelCityE->text();
    else ret += ",-";

    if (!labelTicE->text().isEmpty()) ret += "," + trUtf8("NIP: ") + labelTicE->text();
    else ret += "," + trUtf8("NIP: ") + "-";

    if (!labelAccountE->text().isEmpty()) ret += ", " + trUtf8("Konto: ") + labelAccountE->text();
    else ret += "," + trUtf8("Konto: ") + "-";

    if (!labelPhoneE->text().isEmpty()) ret += ", " + trUtf8("Tel: ") + labelPhoneE->text();
    else ret += "," + trUtf8("Tel: ") + "-";

    if (!labelEmailE->text().isEmpty()) ret += ", " + trUtf8("Email: ") + labelEmailE->text();
    else ret += "," + trUtf8("Email: ") + "-";

    if (!labelWWWE->text().isEmpty()) ret += ", " + trUtf8("Strona: ") + labelWWWE->text();
    else ret += "," + trUtf8("Strona: ") + "-";

    return ret;
}

