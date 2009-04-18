/*
 * IDataLayer.h
 *
 *  Created on: Apr 18, 2009
 *      Author: moux
 */

#ifndef IDATALAYER_H_
#define IDATALAYER_H_

class IDataLayer {
public:
	virtual void saveInvoiceData();
	virtual void readInvoiceData();

};

#endif /* IDATALAYER_H_ */
