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

KontrData XmlDataLayer::kontrahenciReadData(QString name, int type) {
	KontrData o_kontrData;

	QDomDocument doc(sett().getCustomersDocName());
	QDomElement root;
	QDomElement office;
	QDomElement company;

	QFile file(sett().getCustomersXml());
	if (!file.open(QIODevice::ReadOnly)) {
		qDebug() << "File" << file.fileName() << "doesn't exists";
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
					kontrahenciLoadDetails(o_kontrData, n);
				}
			}
		} else {
			for (QDomNode n = office.firstChild(); !n.isNull(); n = n.nextSibling()) {
				if (n.toElement().attribute("name").compare(name) == 0) {
					kontrahenciLoadDetails(o_kontrData, n);
				}
			}
		}
	}
	return o_kontrData;
}

void XmlDataLayer::kontrahenciLoadDetails(KontrData &o_kontrData, QDomNode n) {
	o_kontrData.name = n.toElement().attribute("name");
	o_kontrData.place =  n.toElement().attribute("place");
	o_kontrData.code =  n.toElement().attribute("code");
	o_kontrData.address  = n.toElement().attribute("address");
	o_kontrData.tic =  n.toElement().attribute("tic");
	o_kontrData.account  = n.toElement().attribute("account");
	o_kontrData.phone =  n.toElement().attribute("phone");
	o_kontrData.email =  n.toElement().attribute("email");
	o_kontrData.www =  n.toElement().attribute("www");
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
