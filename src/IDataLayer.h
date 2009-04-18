/*
 * IDataLayer.h
 *
 *  Created on: Apr 18, 2009
 *      Author: moux
 */

#ifndef IDATALAYER_H_
#define IDATALAYER_H_

#include "KontrData.h"

class IDataLayer {
public:
	IDataLayer() {};
	virtual ~IDataLayer() {};
	virtual void saveInvoiceData() {};
	virtual void readInvoiceData() {};
	virtual KontrData kontrahenciReadData(QString, int) {}; // warning: @TODO solve it
	virtual QStringList kontrahenciGetFirmList() {};

};

#endif /* IDATALAYER_H_ */
