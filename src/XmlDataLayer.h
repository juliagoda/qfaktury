/*
 * XmlDataLayer.h
 *
 *  Created on: Apr 18, 2009
 *      Author: moux
 */

#ifndef XMLDATALAYER_H_
#define XMLDATALAYER_H_

#include <Qt/qdom.h>

#include "Settings.h"
#include "IDataLayer.h"

#include "KontrData.h"

class XmlDataLayer: public IDataLayer {
public:
	XmlDataLayer();
	virtual ~XmlDataLayer();
	virtual KontrData kontrahenciReadData(QString name, int type);
	virtual QStringList kontrahenciGetFirmList();
	virtual void saveInvoiceData() {};
	virtual void readInvoiceData() {};
private:
	void kontrahenciLoadDetails(KontrData &o_kontrData, QDomNode n);
};

#endif /* XMLDATALAYER_H_ */
