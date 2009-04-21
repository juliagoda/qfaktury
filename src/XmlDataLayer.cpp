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

QVector<KontrData> XmlDataLayer::XmlDataLayer::kontrahenciSelectAllData() {
	QVector<KontrData> kontrVec;

	QDomDocument doc(sett().getCustomersDocName());
	QDomElement root;
	QDomElement office;
	QDomElement company;

	QFile file(sett().getCustomersXml());
	if (!file.open(QIODevice::ReadOnly)) {
		qDebug() << "File" << file.fileName() << "doesn't exists";
		return kontrVec;
	} else {
		QTextStream stream(&file);
		if (!doc.setContent(stream.readAll())) {
			qDebug("can not set content ");
			file.close();
			return kontrVec;
		} else {
			root = doc.documentElement();
			office = root.firstChild().toElement();
			company = root.lastChild().toElement();
		}

		for (QDomNode n = company.firstChild(); !n.isNull(); n = n.nextSibling()) {
			KontrData kontrData;
			kontrahenciElemToData(kontrData, n.toElement());
			kontrData.type = QObject::trUtf8("Firma");
			kontrVec.push_front(kontrData);
		}

		for (QDomNode n = office.firstChild(); !n.isNull(); n = n.nextSibling()) {
			KontrData kontrData;
			kontrahenciElemToData(kontrData, n.toElement());
			kontrData.type = QObject::trUtf8("Urząd");
			kontrVec.push_front(kontrData);
		}
	}

	return kontrVec;
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
// helper method
void XmlDataLayer::productsElemToData(ProductData& o_prodData, QDomElement i_element) {
	o_prodData.id 		= i_element.attribute("idx").toInt();
	o_prodData.name 	= i_element.attribute("name");
	o_prodData.desc 	= i_element.attribute("desc");
	o_prodData.code 	= i_element.attribute("code");
	o_prodData.pkwiu 	= i_element.attribute("pkwiu");
	o_prodData.quanType = i_element.attribute("quanType");
	o_prodData.prices[0] = sett().stringToDouble(i_element.attribute("netto1"));
	o_prodData.prices[1] = sett().stringToDouble(i_element.attribute("netto2"));
	o_prodData.prices[2] = sett().stringToDouble(i_element.attribute("netto3"));
	o_prodData.prices[3] = sett().stringToDouble(i_element.attribute("netto4"));
	o_prodData.vat 		= i_element.attribute("vat").toInt();
}

// helper method
void XmlDataLayer::productsDataToElem(ProductData& i_prodData, QDomElement &o_element) {
	o_element.setAttribute("idx", i_prodData.id);
	o_element.setAttribute("name", i_prodData.name);
	o_element.setAttribute("desc", i_prodData.desc);
	o_element.setAttribute("code", i_prodData.code);
	o_element.setAttribute("pkwiu", i_prodData.pkwiu);
	o_element.setAttribute("quanType", i_prodData.quanType);
	o_element.setAttribute("netto1", i_prodData.prices[0]);
	o_element.setAttribute("netto2", i_prodData.prices[0]);
	o_element.setAttribute("netto3", i_prodData.prices[0]);
	o_element.setAttribute("netto4", i_prodData.prices[0]);
	o_element.setAttribute("vat", i_prodData.vat);
}

QVector<ProductData> XmlDataLayer::productsSelectAllData() {
	QVector<ProductData> prodVec;

	QDomDocument doc(sett().getProdutcsDocName());
	QDomElement root;
	QDomElement products;
	QDomElement services;

	QFile file(sett().getProductsXml());
	if (!file.open(QIODevice::ReadOnly)) {
		qDebug() << "File" << file.fileName() << "doesn't exists";
		return prodVec;
	} else {
		QTextStream stream(&file);
		if (!doc.setContent(stream.readAll())) {
			qDebug("can't set content ");
			file.close();
			return prodVec;
		} else {
			root = doc.documentElement();
			products = root.firstChild().toElement();
			services = root.lastChild().toElement();
		}

		for (QDomNode n = products.firstChild(); !n.isNull(); n = n.nextSibling()) {
			ProductData prodData;
			productsElemToData(prodData, n.toElement());
			prodData.type = QObject::trUtf8("Towar");
			prodVec.push_front(prodData);
		}

		for (QDomNode n = services.firstChild(); !n.isNull(); n = n.nextSibling()) {
			ProductData prodData;
			productsElemToData(prodData, n.toElement());
			prodData.type = QObject::trUtf8("Usługa");
			prodVec.push_front(prodData);
		}
	}

	return prodVec;
}

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

		if (type == 0) {
			for (QDomNode n = towar.firstChild(); !n.isNull(); n
					= n.nextSibling()) {
				if (n.toElement().attribute("idx").compare(name) == 0) {
					productsElemToData(o_prodData, n.toElement());
				}
			}
		} else {
			for (QDomNode n = usluga.firstChild(); !n.isNull(); n
					= n.nextSibling()) {
				if (n.toElement().attribute("idx").compare(name) == 0) {
					productsElemToData(o_prodData, n.toElement());
				}
			}
		}
	}

	return o_prodData;
}


bool XmlDataLayer::productsInsertData(ProductData& prodData, int type) {
	QDomDocument doc(sett().getProdutcsDocName());
	QDomElement root;
	QDomElement products, services;

	QFile file(sett().getProductsXml());
	if (!file.open(QIODevice::ReadOnly)) {
		qDebug() << "New products file created";
		root = doc.createElement(sett().getProdutcsDocName());
		int lastId = root.attribute("last", "0").toInt();
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
			int lastId = root.attribute("last", "0").toInt();
			lastId++;
			root.setAttribute("last", sett().numberToString(lastId));
			products = root.firstChild().toElement();
			services = root.lastChild().toElement();
		}
	}

	root.lastChild();

	if (type == 0) {
		QDomElement elem = doc.createElement(sett().getProductName());
		productsDataToElem(prodData, elem);
		products.appendChild(elem);
	}

	if (type == 1) {
		QDomElement elem = doc.createElement(sett().getServiceName());
		productsDataToElem(prodData, elem);
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

bool XmlDataLayer::productsUpdateData(ProductData& prodData, int type, QString name) {
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
		if (!doc.setContent(stream.readAll())) {
			qDebug("can not set content ");
			file.close();
			return false;
		} else {
			root = doc.documentElement();
			towary = root.firstChild().toElement();
			uslugi = root.lastChild().toElement();
		}
	}

	root.lastChild();

	if (type == 0) {
		QDomElement elem;
		for (QDomNode n = towary.firstChild(); !n.isNull(); n = n.nextSibling()) {
			if (n.toElement().attribute("idx").compare(name) == 0) {
				elem = n.toElement();
				break;
			}
		}
		productsDataToElem(prodData, elem);
		towary.appendChild(elem);
	}

	if (type == 1) {
		QDomElement elem;
		for (QDomNode n = uslugi.firstChild(); !n.isNull(); n = n.nextSibling()) {
			if (n.toElement().attribute("idx").compare(name) == 0) {
				elem = n.toElement();
				break;
			}
		}
		productsDataToElem(prodData, elem);
		uslugi.appendChild(elem);
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

bool XmlDataLayer::productsDeleteData(QString name) {

	QDomDocument doc(sett().getProdutcsDocName());
	QDomElement root;
	QDomElement products;
	QDomElement services;

	QFile file(sett().getProductsXml());
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
			products = root.firstChild().toElement();
			services = root.lastChild().toElement();
		}
		QString text;

		for (QDomNode n = services.firstChild(); !n.isNull(); n
				= n.nextSibling()) {
			if (n.toElement().attribute("idx"). compare(name) == 0) {
				services.removeChild(n);
				break;
			}
		}

		for (QDomNode n = products.firstChild(); !n.isNull(); n
				= n.nextSibling()) {
			if (n.toElement().attribute("idx"). compare(name) == 0) {
				products.removeChild(n);
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

// ************ TOWARY END   *****************

// ************ INVOICES START *****************
bool XmlDataLayer::nameFilter(QString nameToCheck, QDate start, QDate end) {
	QString tmp = nameToCheck;
	tmp = tmp.remove("h"); // invoice
	tmp = tmp.remove("k"); // correction
	tmp = tmp.left(10);
	tmp = tmp.remove("-");

	// not very flexible
	// assumption is that date comes as yyyymmdd
	// if its otherwise order of remove methods has to be changed
	int year = tmp.left(4).toInt();
	tmp = tmp.remove(0, 4);
	int month = tmp.left(2).toInt();
	tmp = tmp.remove(0, 2);
	int day = tmp.left(2).toInt();
	tmp = tmp.remove(0, 2);
	QDate tmpDate(year, month, day);

	if (tmpDate < start) {
		return false;
	}

	if (tmpDate > end) {
		return false;
	}

	// default true?
	return true;
}


InvoiceData XmlDataLayer::invoiceSelectData(QString name, int type) {
	InvoiceData o_invData;
	return o_invData;
}

QVector<InvoiceData> XmlDataLayer::invoiceSelectAllData(QDate start, QDate end) {
	QVector<InvoiceData> o_invDataVec;

	QDir allFiles;
	QString text;

	QDomDocument doc(sett().getInoiveDocName());
	QDomElement root;
	QDomElement nadawca;
	QDomElement odbiorca;

	allFiles.setPath(sett().getInvoicesDir());
	allFiles.setFilter(QDir::Files);
	QStringList filters;
	filters << "h*.xml" << "k*.xml";
	allFiles.setNameFilters(filters);
	QStringList files = allFiles.entryList();
	int i, max = files.count();
	for (i = 0; i < max; ++i) {
		if (applyFiltr(files[i])) {
			// qDebug() << files[i];
			QFile file(sett().getInvoicesDir() + files[i]);

			if (!file.open(QIODevice::ReadOnly)) {
				qDebug() << "File" << file.fileName() << "doesn't exists";
				return o_invDataVec;
			} else {
				QTextStream stream(&file);
				if (!doc.setContent(stream.readAll())) {
					// qDebug ("can not set content ");
					file.close();
					// return o_invDataVec;
				}
			}

			root = doc.documentElement();
			tableH->item(tableH->rowCount() - 1, 1)->setText(root.attribute(
					"no", "NULL"));
			tableH->item(tableH->rowCount() - 1, 2)->setText(root.attribute(
					"sellingDate", "NULL"));
			tableH->item(tableH->rowCount() - 1, 3)->setText(root.attribute(
					"type", "NULL"));
			QDomNode nab;
			nab = root.firstChild();
			nab = nab.toElement().nextSibling();
			tableH->item(tableH->rowCount() - 1, 4)->setText(
					nab.toElement().attribute("name", "NULL"));
			tableH->item(tableH->rowCount() - 1, 5)->setText(
					nab.toElement().attribute("tic", "NULL"));
		}
	}



	return o_invDataVec;
}

bool XmlDataLayer::invoiceInsertData(InvoiceData& invData, int type) {
	return true;
}

bool XmlDataLayer::invoiceUpdateData(InvoiceData& invData, int type, QString name) {
	return true;
}

bool XmlDataLayer::invoiceDeleteData(QString name) {
	return true;
}
// ************ INVOICES END *****************
