/*
 * TowaryBruttoLista.cpp
 *
 *  Created on: Apr 3, 2009
 *      Author: TPIELECH
 */
#include <QList>
#include <QListWidgetItem>

#include "GoodsGrossList.h"
#include "Settings.h"


GoodsGrossList::GoodsGrossList(QWidget *parent): GoodsList(parent) {
}

GoodsGrossList::~GoodsGrossList() {
}


QString GoodsGrossList::getPriceOfCurrent() {

    double price = sett().stringToDouble(grossLabel->text()) / countSpinBox->value();
	return sett().numberToString(price, 'f', 2);
}

QString const GoodsGrossList::getRetValGoodsBr()
{
    return ret;
}

/** Slot
 *  Accepts and closes
 */

void GoodsGrossList::doAccept() {

	if (countSpinBox->text() == "" || countSpinBox->value() < 0.001) {
		QMessageBox::information(this, "QFaktury", trUtf8("Podaj ilość"),
				QMessageBox::Ok);
		return;
	}

	selectedItem = nameEdit->text();

    QVector<ProductDataList> listProducts;
    listProducts.append(goodsList2);
    listProducts.append(servicesList2);


	if (selectedItem != "") {

        for (int i = 0; i < 2; i++) {

            if (comboBox1->currentIndex() == i) {

                QStringList listRest = QStringList() << selectedItem << listProducts[i][getGoodsId()]->getCode() << listProducts[i][getGoodsId()]->getPkwiu() <<
                                                        trimZeros(countSpinBox->cleanText()) << listProducts[i][getGoodsId()]->getQuantityType() <<
                                                        discountSpin->cleanText() << getPriceOfCurrent()
                                                     << netLabel->text() << sett().numberToString(getVatsVal()[selectedItem]) <<
                                                        grossLabel->text();

                for (int j = 0; j < listRest.count(); j++) {

                    ret += listRest[j] + "|";
                }
            }
        }

		accept();

	} else {

		QMessageBox::information(this, "QFaktury", trUtf8("Wskaż towar"),
				QMessageBox::Ok);
	}
}


void GoodsGrossList::calcNet() {

    if (listWidget->selectedItems().size() == 1) {
		double price = (countSpinBox->value() * priceBoxEdit->value()); // price * quantity

        double discount = price * (discountSpin->value() * 0.01);

		double wb = price - discount;
        int sp = getVatsVal()[listWidget->selectedItems().at(0)->text()];
        double vat = (wb * sp) / (100 + sp);
        double net2 = wb - vat;

        // qDebug() << price << discount << net2 << gross2 << vat;
        grossLabel->setText(sett().numberToString(wb, 'f', 2));
        netLabel->setText(sett().numberToString(net2, 'f', 2));
	}
}
