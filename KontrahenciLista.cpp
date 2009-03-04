#include "KontrahenciLista.moc"
#include <QMessageBox>
#include <QTextStream>

/** Constructor
 */
KontrahenciLista::KontrahenciLista(QWidget *parent): QDialog(parent) {
    setupUi(this);
    init();
}

/** Init
 */
void KontrahenciLista::init() {
	companiesList.clear();
	officesList.clear();

	// read data
	readKontr(sett().getWorkingDir());

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
    connect(listBox1, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(updateDetails(QListWidgetItem *)));
}

// *************************** SLOTS START *************************************

/** Slot
 *  Connected to accept signal
 */
void KontrahenciLista::doAccept() {
	QList<QListWidgetItem *> selected = listBox1->selectedItems();
	if (!selected.isEmpty()) {
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
void KontrahenciLista::comboBox1Changed() {
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
void KontrahenciLista::updateDetails(QListWidgetItem *item) {
	QStringList custDetails;
	QString customer;
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
void KontrahenciLista::readKontr(QString progDir) {
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
}

/** Loads data one string
 */
QString KontrahenciLista::xmlDataToString(QDomNode n) {
	QString text;
	text = n.toElement().attribute("name") + "|";
	text += n.toElement().attribute("address") + "|";
	text += n.toElement().attribute("place") + "|";
	text += n.toElement().attribute("tic") + "|";
	text += n.toElement().attribute("account") + "|";
	text += n.toElement().attribute("phone") + "|";
	text += n.toElement().attribute("email") + "|";
	text += n.toElement().attribute("www");
	return text;
}

/** Loads data to labels
 */
void KontrahenciLista::displayDetails(QStringList custDetails) {
	labelNameE->setText(custDetails[0]);
    labelAddressE->setText(custDetails[1]);
    labelCityE->setText(custDetails[2]);
    labelTicE->setText(custDetails[3]);
    labelAccountE->setText(custDetails[4]);
    labelPhoneE->setText(custDetails[5]);
    labelEmailE->setText(custDetails[6]);
    labelWWWE->setText(custDetails[7]);
}


/** Clear labels
 */
void KontrahenciLista::clearDetails() {
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
QString  KontrahenciLista::detailsToString() {
	QString ret = labelNameE->text();
	if (!labelAddressE->text().isEmpty())
		ret += ", " +  labelAddressE->text();
	if (!labelCityE->text().isEmpty())
		ret +=  ", " + labelCityE->text();
	if (!labelTicE->text().isEmpty())
		ret += ", " + trUtf8("NIP: ") + labelTicE->text();
	if (!labelAccountE->text().isEmpty())
		ret += ", " + labelAccountE->text();
	if (!labelPhoneE->text().isEmpty())
		ret += ", " + labelPhoneE->text();
	if (!labelEmailE->text().isEmpty())
		ret += ", " + labelEmailE->text();
	if (!labelWWWE->text().isEmpty())
		ret += ", " + labelWWWE->text();
    return ret;
}

