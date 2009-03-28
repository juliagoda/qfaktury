#include "moc_Kontrahenci.cpp"
#include <QMessageBox>
#include <QtDebug>
#include "Settings.h"

/** Constructor
 */
Kontrahenci::Kontrahenci(QWidget *parent, int mode) :
	QDialog(parent) {
	workingMode = mode;
	setupUi(this);
	init();
}

/** init()
 */
void Kontrahenci::init() {
	getFirmList();

	nipEdit->setInputMask(sett().value("ticMask", "999-99-999-99; ").toString());
	accountEdit->setInputMask(sett().value("accountMask", "99-9999-9999-9999-9999-9999-9999; ").toString());

	// connects
	connect(okButton, SIGNAL(clicked()), this, SLOT(okClick()));
}

// --------- SLOTS START --

/** Slot - ok & save
 */
void Kontrahenci::okClick() {
	/* @TODO
	 * validation - account must have 26 chars
	 */
	if (workingMode == 1) {
		modifyOnly();
		ret = isEmpty(nameEdit->text()) + "|" + typeCombo->currentText() + "|" + isEmpty(
				placeEdit->text()) + "|" + isEmpty(addressEdit->text()) + "|"
				+ isEmpty(telefonEdit->text());
		accept();
	} else {
		if (saveAll()) {
			ret = isEmpty(nameEdit->text()) + "|" + typeCombo->currentText() + "|"
					+ isEmpty(placeEdit->text()) + "|" + isEmpty(
					addressEdit->text()) + "|" + isEmpty(telefonEdit->text());
			accept();
		}
	}

}

// --------- SLOTS END --

/** Parse xml and load data for edit
 */
void Kontrahenci::readData(QString name, int type) {
	nazwaEdit = name;
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

		if (type == 0) {
			for (QDomNode n = company.firstChild(); !n.isNull(); n = n.nextSibling()) {
				if (n.toElement().attribute("name").compare(name) == 0) {
					loadDetails(n);
					typeCombo->setCurrentIndex(0);
				}
			}
		} else {
			for (QDomNode n = office.firstChild(); !n.isNull(); n = n.nextSibling()) {
				if (n.toElement().attribute("name").compare(name) == 0) {
					loadDetails(n);
					typeCombo->setCurrentIndex(1);
				}
			}
		}
		setWindowTitle(trUtf8("Edytuj kontrahenta"));
		typeCombo->setEnabled(false);
	}
}

/** Load list of the companies into allNames QStringList
 */
void Kontrahenci::getFirmList() {
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
		QString text;

		for (QDomNode n = company.firstChild(); !n.isNull(); n
				= n.nextSibling()) {
			text = n.toElement().attribute("name");
			allNames << text;
		}

		for (QDomNode n = office.firstChild(); !n.isNull(); n = n.nextSibling()) {
			text = n.toElement().attribute("name");
			allNames << text;
		}
	}
}

/** Save data used in okClick()
 */
bool Kontrahenci::saveAll() {
	if (allNames.indexOf(QRegExp(nameEdit->text(), Qt::CaseSensitive,
			QRegExp::FixedString)) != -1) {
		QMessageBox::critical(
				0,
				"QFaktury",
				trUtf8("Kontrahent nie moze zostać dodany ponieważ istnieje już kontrahent o tej nazwie."));
		return false;
	}

	QDomDocument doc(sett().getCustomersDocName());
	QDomElement root;
	QDomElement office;
	QDomElement company;

	QFile file(sett().getCustomersXml());
	if (!file.open(QIODevice::ReadOnly)) {
		qDebug("can not open ");
		root = doc.createElement(sett().getCustomersDocName());
		doc.appendChild(root);
		office = doc.createElement(sett().getOfficeName());
		root.appendChild(office);
		company = doc.createElement(sett().getCompanyName());
		root.appendChild(company);
	} else {
		QTextStream stream(&file);
		if (!doc.setContent(stream.readAll())) {
			qDebug("can not set content ");
			file.close();
			// return;
		} else {
			root = doc.documentElement();
			office = root.firstChild().toElement();
			company = root.lastChild().toElement();
		}
	}

	root.lastChild();

	// firma = 0; urzad = 1;
	if (typeCombo->currentIndex() == 0) {
		QDomElement elem = doc.createElement(sett().getCompanyName());
		dataToElem(elem);
		company.appendChild(elem);
	}

	if (typeCombo->currentIndex() == 1) {
		QDomElement elem = doc.createElement(sett().getOfficeName());
		dataToElem(elem);
		office.appendChild(elem);
	}

	QString xml = doc.toString();

	file.close();
	file.open(QIODevice::WriteOnly);
	QTextStream ts(&file);
	ts << xml;
	file.close();

	return true;
}

/** Saves when modfied
 */
void Kontrahenci::modifyOnly() {
	QDomDocument doc(sett().getCustomersDocName());
	QDomElement root;
	QDomElement office;
	QDomElement company;

	QFile file(sett().getCustomersXml());
	if (!file.open(QIODevice::ReadOnly)) {
		qDebug() << "File" << file.fileName() << "doesn't exists";
		root = doc.createElement(sett().getCustomersDocName());
		doc.appendChild(root);
		office = doc.createElement(sett().getOfficeName());
		root.appendChild(office);
		company = doc.createElement(sett().getCompanyName());
		root.appendChild(company);
	} else {
		QTextStream stream(&file);
		if (!doc.setContent(stream.readAll())) {
			qDebug("can not set content ");
			file.close();
			// return;
		} else {
			root = doc.documentElement();
			office = root.firstChild().toElement();
			company = root.lastChild().toElement();
		}
	}

	root.lastChild();
	QString text;

	// firma = 0; urzad = 1;
	if (typeCombo->currentIndex() == 0) {
		QDomElement elem; // = doc.createElement ("firma");
		for (QDomNode n = company.firstChild(); !n.isNull(); n
				= n.nextSibling()) {
			if (n.toElement().attribute("name").compare(nazwaEdit) == 0) {
				elem = n.toElement();
				break;
			}
		}
		dataToElem(elem);
		company.appendChild(elem);
	}

	if (typeCombo->currentIndex() == 1) {
		QDomElement elem; //  = doc.createElement ("urzad");
		for (QDomNode n = office.firstChild(); !n.isNull(); n = n.nextSibling()) {
			if (n.toElement().attribute("name").compare(nazwaEdit) == 0) {
				elem = n.toElement();
				break;
			}
		}
		dataToElem(elem);
		office.appendChild(elem);
	}

	QString xml = doc.toString();

	file.close();
	file.open(QIODevice::WriteOnly);
	QTextStream ts(&file);
	ts << xml;
	file.close();

}

/** Loads data from labels into DOM object
 */
void Kontrahenci::dataToElem(QDomElement elem) {
	elem.setAttribute("name", nameEdit->text());
	elem.setAttribute("place", placeEdit->text());
	elem.setAttribute("code", codeEdit->text());
	elem.setAttribute("address", addressEdit->text());
	elem.setAttribute("tic", nipEdit->text());
	elem.setAttribute("account", accountEdit->text());
	elem.setAttribute("phone", telefonEdit->text());
	elem.setAttribute("email", emailEdit->text());
	elem.setAttribute("www", wwwEdit->text());
}

/** Load details
 */
void Kontrahenci::loadDetails(QDomNode n) {
	nameEdit->setText(n.toElement().attribute("name"));
	placeEdit->setText(n.toElement().attribute("place"));
	codeEdit->setText(n.toElement().attribute("code"));
	addressEdit->setText(n.toElement().attribute("address"));
	nipEdit->setText(n.toElement().attribute("tic"));
	accountEdit->setText(n.toElement().attribute("account"));
	telefonEdit->setText(n.toElement().attribute("phone"));
	emailEdit->setText(n.toElement().attribute("email"));
	wwwEdit->setText(n.toElement().attribute("www"));
}

QString Kontrahenci::isEmpty(QString in) {
	if (in == "")
		return "-";
	return in;
}

