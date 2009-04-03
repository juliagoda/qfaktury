/*
 * FakrutaBrutto.cpp
 *
 *  Created on: Apr 2, 2009
 *      Author: TPIELECH
 */

#include "moc_FakturaBrutto.cpp"

// constructor
FakturaBrutto::FakturaBrutto(QWidget *parent): Faktura(parent) {

}

FakturaBrutto::~FakturaBrutto() {
}

void FakturaBrutto::fakturaBruttoInit() {

}

void FakturaBrutto::calculateDiscount() {

}

void FakturaBrutto::calculateSum() {

}

void FakturaBrutto::addTow() {
	TowaryLista *twWindow = new TowaryLista(this);
	if (twWindow->exec() == QDialog::Accepted) {
		MainWindow::insertRow(tableTow, tableTow->rowCount());
		// qDebug() << twWindow->ret;
		QStringList row = twWindow->ret.split("|");
		int rowNum = tableTow->rowCount() - 1;
		tableTow->item(rowNum, 0)->setText(sett().numberToString(
				tableTow->rowCount())); // id
		tableTow->item(rowNum, 1)->setText(row[0]); // name
		tableTow->item(rowNum, 2)->setText(row[1]); // code
		tableTow->item(rowNum, 3)->setText(row[2]); // pkwiu
		tableTow->item(rowNum, 4)->setText(row[3]); // quantity
		tableTow->item(rowNum, 5)->setText(row[4]); // qType
		tableTow->item(rowNum, 6)->setText(row[5]); // discount
		tableTow->item(rowNum, 7)->setText(row[6]); // price
		tableTow->item(rowNum, 8)->setText(row[7]); // nett
		tableTow->item(rowNum, 9)->setText(row[8]); // vat
		tableTow->item(rowNum, 10)->setText(row[9]); // gross
		saveBtn->setEnabled(true);
		canClose = false;
		if (constRab->isChecked())
			calculateDiscount();
		calculateSum();
	}
	delete twWindow;
	twWindow = NULL;
}
