/*
 * KorektaBrutto.h
 *
 *  Created on: Apr 3, 2009
 *      Author: moux
 */

#ifndef KOREKTABRUTTO_H_
#define KOREKTABRUTTO_H_

#include "Korekta.h"

class KorektaBrutto: public Korekta {
Q_OBJECT
public:
	KorektaBrutto(QWidget *parent);
	~KorektaBrutto();
	void addTow();
};


#endif /* KOREKTABRUTTO_H_ */
