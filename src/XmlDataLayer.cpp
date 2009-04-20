/*
 * XmlDataLayer.cpp
 *
 *  Created on: Apr 18, 2009
 *      Author: moux
 */

#include "XmlDataLayer.h"
#include "IDataLayer.h"


XmlDataLayer::XmlDataLayer():IDataLayer() {
	// TODO Auto-generated constructor stub

}

XmlDataLayer::~XmlDataLayer() {
	// TODO Auto-generated destructor stub
}

// ************ KONTRAHENCI START *****************
// helper method
void XmlDataLayer::kontrahenciElemToData(KontrData &o_kontrData, QDomElement i_element) {
	o_kontrData.name 	= i_element.attribute("name");
	o_kontrData.place 	= i_element.attribute("place");
	o_kontrData.code 	= i_element.attribute("code");
	o_kontrData.address	= i_element.attribute("address");
	o_kontrData.tic		= i_element.attribute("tic");
	o_kontrData.account	= i_element.attribute("account");
	o_kontrData.phone	= i_element.attribute("phone");
	o_kontrData.email	= i_element.attribute("email");
	o_kontrData.www		= i_element.attribute("www");
}

// helper method
void XmlDataLayer::kontrahenciDataToElem(KontrData &i_kontrData, QDomElement &o_element) {
	o_element.setAttribute("name", i_kontrData.name);
	o_element.setAttribute("place", i_kontrData.place);
	o_element.setAttribute("code", i_kontrData.code);
	o_element.setAttribute("address", i_kontrData.address);
	o_element.setAttribute("tic", i_kontrData.tic);
	o_element.setAttribute("account", i_kontrData.account);
	o_element.setAttribute("phone", i_kontrData.phone);
	o_element.setAttribute("email", i_kontrData.email);
	o_element.setAttribute("www", i_kontrData.www);
}


KontrData XmlDataLayer::kontrahenciSelectData(QString name, int type) {
	KontrData o_kontrData;

	QDomDocument doc(sett().getCustomersDocName());
	QDomElement root;
	QDomElement office;
	QDomElement company;

	QFile file(sett().getCustomersXml());
	if (!file.open(QIODevice::ReadOnly)) {
		qDebug() << "File" << file.fileName() << "doesn't exists";
		return o_kontrData;
	} else {
		QTextStream stream(&file);
		if (!doc.setContent(stream.readAll())) {
			qDebug("can not set content ");
			file.close();
			return o_kontrData;
		} else {
			root = doc.documentElement();
			office = root.firstChild().toElement();
			company = root.lastChild().toElement();
		}

		if (type == 0) {
			for (QDomNode n = company.firstChild(); !n.isNull(); n = n.nextSibling()) {
				if (n.toElement().attribute("name").compare(name) == 0) {
					kontrahenciElemToData(o_kontrData, n.toElement());
				}
			}
		} else {
			for (QDomNode n = office.firstChild(); !n.isNull(); n = n.nextSibling()) {
				if (n.toElement().attribute("name").compare(name) == 0) {
					kontrahenciElemToData(o_kontrData, n.toElement());
				}
			}
		}
	}
	return o_kontrData;
}


bool XmlDataLayer::kontrahenciInsertData(KontrData& kontrData, int type) {
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
	if (type == 0) {
		QDomElement elem = doc.createElement(sett().getCompanyName());
		kontrahenciDataToElem(kontrData, elem);
		company.appendChild(elem);
	}

	if (type == 1) {
		QDomElement elem = doc.createElement(sett().getOfficeName());
        elem.setAttribute("name", kontrData.name);
        elem.setAttribute("place", kontrData.place);
        elem.setAttribute("code", kontrData.code);
        elem.setAttribute("address", kontrData.address);
        elem.setAttribute("tic", kontrData.tic);
        elem.setAttribute("account", kontrData.account);
        elem.setAttribute("phone", kontrData.phone);
        elem.setAttribute("email", kontrData.email);
        elem.setAttribute("www", kontrData.www);
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

QStringList XmlDataLayer::kontrahenciGetFirmList() {
	QStringList allNames;

	QDomDocument doc(sett().getCustomersDocName());
	QDomElement root;
	QDomElement office;
	QDomElement company;

	QFile file(sett().getCustomersXml());
	if (!file.open(QIODevice::ReadOnly)) {
		qDebug() << "File" << file.fileName() << "doesn't exists";
		return allNames;
	} else {
		QTextStream stream(&file);
		if (!doc.setContent(stream.readAll())) {
			qDebug("can not set content ");
			file.close();
			return allNames;
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
	return allNames;
}

bool XmlDataLayer::kontrahenciUpdateData(KontrData& kontrData, int type, QString name) {
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
			return false;
		} else {
			root = doc.documentElement();
			office = root.firstChild().toElement();
			company = root.lastChild().toElement();
		}
	}

	root.lastChild();
	QString text;

	// firma = 0; urzad = 1;
	if (type == 0) {
		QDomElement elem; // = doc.createElement ("firma");
		for (QDomNode n = company.firstChild(); !n.isNull(); n
				= n.nextSibling()) {
			if (n.toElement().attribute("name").compare(name) == 0) {
				elem = n.toElement();
				break;
			}
		}
		kontrahenciDataToElem(kontrData, elem);
		company.appendChild(elem);
	}

	if (type == 1) {
		QDomElement elem; //  = doc.createElement ("urzad");
		for (QDomNode n = office.firstChild(); !n.isNull(); n = n.nextSibling()) {
			if (n.toElement().attribute("name").compare(name) == 0) {
				elem = n.toElement();
				break;
			}
		}
		kontrahenciDataToElem(kontrData, elem);
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

bool XmlDataLayer::kontrahenciDeleteData(QString name) {
	QDomDocument doc(sett().getCustomersDocName());
	QDomElement root;
	QDomElement urzad;
	QDomElement firma;

	QFile file(sett().getCustomersXml());
	if (!file.open(QIODevice::ReadOnly)) {
		qDebug() << "File" << file.fileName() << "doesn't exists";
		return false;
	} else {
		QTextStream stream(&file);
		if (!doc.setContent(stream.readAll())) {
			qDebug("can not set content ");
			file.close();
			return false;
		} else {
			root = doc.documentElement();
			urzad = root.firstChild().toElement();
			firma = root.lastChild().toElement();
		}
		QString text;

		for (QDomNode n = firma.firstChild(); !n.isNull(); n = n.nextSibling()) {
			if (n.toElement().attribute("name"). compare(name) == 0) {
				firma.removeChild(n);
				break;
			}
		}

		for (QDomNode n = urzad.firstChild(); !n.isNull(); n = n.nextSibling()) {
			if (n.toElement().attribute("name"). compare(name) == 0) {
				urzad.removeChild(n);
				break;
			}
		}

		QString xml = doc.toString();
		file.close();
		file.open(QIODevice::WriteOnly);
		QTextStream ts(&file);
		ts << xml;

		file.close();
	}
	return true;
}
// ************ KONTRAHENCI END *****************


// ************ TOWARY START *****************
ProductData XmlDataLayer::productsSelectData(QString name, int type) {
	ProductData o_prodData;

	QDomDocument doc(sett().getProdutcsDocName());
	QDomElement root;
	QDomElement towar;
	QDomElement usluga;

	QFile file(sett().getProductsXml());
	if (!file.open(QIODevice::ReadOnly)) {
		qDebug() << "File" << file.fileName() << "doesn't exists";
		return o_prodData;
	} else {
		QTextStream stream(&file);
		if (!doc.setContent(stream.readAll())) {
			qDebug("can not set content ");
			file.close();
			return o_prodData;
		} else {
			root = doc.documentElement();
			o_prodData.lastProdId = root.attribute("last", "1").toInt();
			towar = root.firstChild().toElement();
			usluga = root.lastChild().toElement();
		}
		QString text;

		if (type == 0) {
			for (QDomNode n = towar.firstChild(); !n.isNull(); n
					= n.nextSibling()) {
				if (n.toElement().attribute("idx").compare(name) == 0) {
					// displayData(n);
					// cbVat->setCurrentIndex(type);
				}
			}
		} else {
			for (QDomNode n = usluga.firstChild(); !n.isNull(); n
					= n.nextSibling()) {
				if (n.toElement().attribute("idx").compare(name) == 0) {
					// displayData(n);
					// cbVat->setCurrentIndex(type);
				}
			}
		}

	}
}


bool XmlDataLayer::productsInsertData(ProductData& prodData, int type) {
	return true;
}

bool XmlDataLayer::productsUpdateData(ProductData& prodData, int type, QString name) {
	return true;
}

bool XmlDataLayer::productsDeleteData(QString name) {
	return true;
}

// ************ TOWARY END   *****************
