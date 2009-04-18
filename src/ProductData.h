#ifndef PRODUCTDATA_H_
#define PRODUCTDATA_H_


#include <QString>
#include <QTextStream>

#include "Settings.h"

/* Class used in the Products list
 *
 */


class ProductData {
public:
	ProductData() {
		id = 0;
		name = "";
		code = "";
		pkwiu = "";
		quantity = 0;
		quanType = "";
		discount = 0;
		price = 0;
		nett = 0;
		vat = 0;
		gross = 0;
		curr = "";
	}
	ProductData(QString c1, QString c2, QString c3) {
		code = c1;
		if (code == "")
			code = "-";
		curr = c2;
		if (curr == "")
			curr = "-";
		pkwiu = c3;
		if (pkwiu == "")
			pkwiu = "-";
	}
	ProductData(int inId, QString inName, QString inCode, QString inPkwiu, double inQuantity, QString inQuanType,
			double inDiscount, double inPrice, double inNett, int inVat, double inGross, QString inCurr) {
		id = inId;
		name = inName;
		code = inCode;
		pkwiu = inPkwiu;
		quantity = inQuantity;
		quanType = inQuanType;
		discount = inDiscount;
		price = inPrice;
		nett = inNett;
		vat = inVat;
		gross = inGross;
		curr = inCurr;
	}

	//*************************************************** getters ***************************************************
	int getId() const{
		return id;
	}

	QString getName() const{
		return name;
	}

	QString getCode() const {
		return code;
	}

	QString getPkwiu() const {
		return pkwiu;
	}

	double getQuantity() const{
		return quantity;
	}

	QString getQuantityType() const {
		return quanType;
	}

	double getDiscount() const{
		return discount;
	}

	double getPrice() const{
		return price;
	}

	double getNett() const {
		return nett;
	}

	int getVat() const {
		return vat;
	}

	double getGross() const {
		return gross;
	}

	QString getCurr() const {
		return curr;
	}

	//*************************************************** setters ***************************************************
	void setId(QString inId) {
		id = inId.toInt();
	}

	void setName(QString inName) {
		name = inName;
	}

	void setCode(QString inCode)  {
		code = inCode;
	}

	void setPkwiu(QString inPkwiu)  {
		pkwiu = inPkwiu;
	}

	void setQuantity(QString quan) {
		quantity = sett().stringToDouble(quan);
	}

	void setQuanType(QString qType)  {
		quanType = qType;
	}

	void setDiscount(QString disc) {
		discount = sett().stringToDouble(disc);
	}

	void setPrice(QString prc) {
		price = sett().stringToDouble(prc);
	}

	void setNett(QString net)  {
		nett = sett().stringToDouble(net);
	}

	void setVat(QString vt)  {
		vat = vt.toInt();
	}

	void setGross(QString gr)  {
		gross = sett().stringToDouble(gr);
	}

	void setCurr(QString cr)  {
		curr = cr;
	}

	// ********************************* All TO STRING ********************
	QString  toString() {
		QString str;
		QTextStream ret(&str);
		ret << "id: " << id << "\n"
			<< "name: " << name << "\n"
			<< "code: " << code << "\n"
			<< "pkwiu: " << pkwiu<< "\n"
			<< "quantity: " << quantity << "\n"
			<< "quanType: " << quanType << "\n"
			<< "discount: " << discount<< "\n"
			<< "price: " << price<< "\n"
			<< "nett: " << nett << "\n"
			<< "vat: " << vat<< "\n"
			<< "gross: " << gross<< "\n"
			<< "curr: " << curr;
		return	"ProductData: [" + str + "]";
	}
private:
	int id;
	QString name;
	QString code;
	QString pkwiu;
	double quantity;
	QString quanType;
	double discount;
	double price;
	double nett;
	int vat;
	double gross;
	QString curr;
};


#endif
