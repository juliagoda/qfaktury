/*
 * CustomPayment.cpp
 *
 *  Created on: Apr 4, 2009
 *      Author: moux
 */

#include "CustomPayment.h"


/*
	Kwota do zapłaty  : 554.90 zł
	Zapłacono gotówką : 254,90 zł dnia {Data bieżąca}
	Kwota zaległośći  : 300 zł 7 dni Przelew {Data Zapłaty}
*/


CustomPayment::CustomPayment(QWidget *parent): QDialog(parent) {
	setupUi(this);
	// TODO Auto-generated constructor stub

}

CustomPayment::~CustomPayment() {
	// TODO Auto-generated destructor stub
}
