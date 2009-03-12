#include "Towary.moc"
#include "Settings.h"
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include <QtDebug>

/** Constructor
 */
Towary::Towary(QWidget *parent, int mode): QDialog(parent) {
    setupUi(this);
    init();
    workMode = mode;
}

/** Init
 */
void Towary::init() {

	readData("", 0);
	idxEdit->setText(sett().numberToString(lastId));
	jednCombo->addItems(sett().value("jednostki").toString().split("|"));
	cbVat->addItems(sett().value("stawki").toString().split("|"));

	connect(okButton, SIGNAL(clicked()), this, SLOT(okClick()));
	connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
	connect(nettoEdit, SIGNAL(valueChanged(double)), this, SLOT(nettoChanged(double)));
	connect(spinBox2, SIGNAL(valueChanged(int)), this, SLOT(spinChanged(int)));
	connect(pkwiuBtn, SIGNAL(clicked()), this, SLOT(pkwiuGet()));
}

/******************** SLOTS START ***************************/

/** Slot
 *  save data to XML file and returns row for products table
 */
void Towary::okClick() {
	if (nameEdit->text() == "") {
		QMessageBox::critical(0, "QFaktury", trUtf8("Musisz podać nazwe."));
		return;
	}

	QString pkwiu = pkwiuEdit->text();
	if (pkwiu == "")
		pkwiu = " ";
	QString skrot = skrotEdit->text();
	if (skrot == "")
		skrot = " ";
	QString kod = kodEdit->text();
	if (kod == "")
		kod = " ";

	QString typ;

	if (workMode == 1) {
		modifyOnly();
		ret = idxEdit->text() + "|" + nameEdit->text() + "|" + skrot + "|"
				+ kod + "|" + pkwiu + "|" + typeCombo->currentText() + "|"
				+ jednCombo->currentText() + "|" + netto[0] + "|"
				+ netto[1] + "|" + netto[2] + "|" + netto[3] + "|"
				+ cbVat->currentText();
		accept();

	} else {
		if (saveAll()) {
			ret = idxEdit->text() + "|" + nameEdit->text() + "|" + skrot + "|"
				+ kod + "|" + pkwiu + "|" + typeCombo->currentText() + "|"
				+ jednCombo->currentText() + "|" + netto[0] + "|"
				+ netto[1] + "|" + netto[2] + "|" + netto[3] + "|"
					+ cbVat->currentText();
			accept();
		}
	}

}

/** Slot
 *  spinBox with list of prices changed
 */
void Towary::spinChanged(int a) {
	nettoEdit->setValue(netto[a - 1].toDouble());
}

/** Slot
 *  Nett value changed
 */
void Towary::nettoChanged(double a) {
	// qDebug ()<<nettoEdit->text ();
	netto[spinBox2->value() - 1] = nettoEdit->cleanText();
}

/** Slot
 *  Find PKWIU code on the net
 */
void Towary::pkwiuGet() {
	QDesktopServices::openUrl(QUrl(tr("http://www.klasyfikacje.pl/")));
}


/******************** SLOTS END ***************************/


/** Loads data from the XML into the form
 */
void Towary::readData(QString idx, int type) {

	if (idx == "") {
		netto.append("0");
		netto.append("0");
		netto.append("0");
		netto.append("0");
		nettoEdit->setValue(0);
	} else {
		setWindowTitle(trUtf8("Edytuj towar/usługę"));
		typeCombo->setEnabled(false);
	}

	lastId = 1;
	idxEdit->setText(idx);
	QDomDocument doc(sett().getProdutcsDocName());
	QDomElement root;
	QDomElement towar;
	QDomElement usluga;

	QFile file(sett().getProductsXml());
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
			lastId = root.attribute("last", "1").toInt();
			towar = root.firstChild().toElement();
			usluga = root.lastChild().toElement();
		}
		QString text;

		if (type == 0) {
			for (QDomNode n = towar.firstChild(); !n.isNull(); n
					= n.nextSibling()) {
				if (n.toElement().attribute("idx").compare(idx) == 0) {
					displayData(n);
					cbVat->setCurrentIndex(type);
				}
			}
		} else {
			for (QDomNode n = usluga.firstChild(); !n.isNull(); n
					= n.nextSibling()) {
				if (n.toElement().attribute("idx").compare(idx) == 0) {
					displayData(n);
					cbVat->setCurrentIndex(type);
				}
			}
		}
	}

}


/** Saves data from the form
 */
bool Towary::saveAll() {
	nettoChanged(0);

	QDomDocument doc(sett().getProdutcsDocName());
	QDomElement root;
	QDomElement products, services;

	QFile file(sett().getProductsXml());
	if (!file.open(QIODevice::ReadOnly)) {
		root = doc.createElement(sett().getProdutcsDocName());
		lastId++;
		root.setAttribute("last", sett().numberToString(lastId));
		doc.appendChild(root);
		products = doc.createElement(sett().getNameWithData(sett().getProductName()));
		root.appendChild(products);
		services = doc.createElement(sett().getNameWithData(sett().getServiceName()));
		root.appendChild(services);
	} else {
		QTextStream stream(&file);
		if (!doc.setContent(stream.readAll())) {
			qDebug("can not set content ");
			file.close();
			return false;
		} else {
			root = doc.documentElement();
			lastId++;
			root.setAttribute("last", sett().numberToString(lastId));
			products = root.firstChild().toElement();
			services = root.lastChild().toElement();
		}
	}

	root.lastChild();

	if (typeCombo->currentIndex() == 0) {
		QDomElement elem = doc.createElement(sett().getProductName());
		fillElem(elem);
		products.appendChild(elem);
	}

	if (typeCombo->currentIndex() == 1) {
		QDomElement elem = doc.createElement(sett().getServiceName());
		fillElem(elem);
		services.appendChild(elem);
	}

	QString xml = doc.toString();

	file.close();
	file.open(QIODevice::WriteOnly);
	QTextStream ts(&file);
	ts.setCodec(QTextCodec::codecForName(sett().getCodecName()));
	ts << xml;
	file.close();

	return true;
}

/** Modify product
 *  Searches for the right one and saves it.
 */
void Towary::modifyOnly() {
	nettoChanged(0);

	QDomDocument doc(sett().getProdutcsDocName());
	QDomElement root;
	QDomElement towary;
	QDomElement uslugi;

	QFile file(sett().getProductsXml());
	if (!file.open(QIODevice::ReadOnly)) {
		root = doc.createElement(sett().getProdutcsDocName());
		doc.appendChild(root);
		towary = doc.createElement(sett().getProductName());
		root.appendChild(towary);
		uslugi = doc.createElement(sett().getServiceName());
		root.appendChild(uslugi);
	} else {
		QTextStream stream(&file);
		if (!doc.setContent(stream.readAll()))
		{
			qDebug("can not set content ");
			file.close();
			return;
		} else {
			root = doc.documentElement();
			towary = root.firstChild().toElement();
			uslugi = root.lastChild().toElement();
		}
	}

	root.lastChild();

	if (typeCombo->currentIndex() == 0) {
		QDomElement elem;
		for (QDomNode n = towary.firstChild(); !n.isNull(); n = n.nextSibling()) {
			if (n.toElement().attribute("idx").compare(idxEdit->text()) == 0) {
				elem = n.toElement();
				break;
			}
		}
		fillElem(elem);
		towary.appendChild(elem);
	}

	if (typeCombo->currentIndex() == 1) {
		QDomElement elem;
		for (QDomNode n = uslugi.firstChild(); !n.isNull(); n = n.nextSibling()) {
			if (n.toElement().attribute("idx").compare(idxEdit->text()) == 0) {
				elem = n.toElement();
				break;
			}
		}
		fillElem(elem);
		uslugi.appendChild(elem);
	}

	QString xml = doc.toString();

	file.close();
	file.open(QIODevice::WriteOnly);
	QTextStream ts(&file);
	ts.setCodec(QTextCodec::codecForName(sett().getCodecName()));
	ts << xml;
	file.close();
}

/** Load data from XML unto the labels;
 */
void Towary::displayData(QDomNode n) {
	idxEdit->setText(n.toElement().attribute("idx"));
	nameEdit->setText(n.toElement().attribute("name"));
	kodEdit->setText(n.toElement().attribute("code"));
	skrotEdit->setText(n.toElement().attribute("desc"));
	pkwiuEdit->setText(n.toElement().attribute("pkwiu"));
	typeCombo->setCurrentIndex(0);
	jednCombo->setCurrentIndex(0);
	nettoEdit->setValue(n.toElement().attribute("netto1").toDouble());
	netto[0] = n.toElement().attribute("netto1");
	netto[1] = n.toElement().attribute("netto2");
	netto[2] = n.toElement().attribute("netto3");
	netto[3] = n.toElement().attribute("netto4");

}

/** Fill XML element
 */
void Towary::fillElem(QDomElement elem) {
	elem.setAttribute("idx", idxEdit->text());
	elem.setAttribute("name", nameEdit->text());
	elem.setAttribute("desc", skrotEdit->text());
	elem.setAttribute("code", kodEdit->text());
	elem.setAttribute("pkwiu", pkwiuEdit->text());
	elem.setAttribute("quanType", jednCombo->currentText());
	elem.setAttribute("netto1", netto[0]);
	elem.setAttribute("netto2", netto[1]);
	elem.setAttribute("netto3", netto[2]);
	elem.setAttribute("netto4", netto[3]);
	elem.setAttribute("vat", cbVat->currentText());
}

