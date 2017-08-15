#include <QtXml/qdom.h>

#include "GoodsList.h"
#include "Settings.h"

/** Constructor
 */

GoodsList::GoodsList(QWidget *parent)
	: QDialog(parent)
{
	setupUi(this);
	init();
}

/** Init
 */

void GoodsList::init()
{
	ret = "";

	// clear all the lists
	goodsList2.clear();
	servicesList2.clear();
	listWidget->clear();

	// load data
	readGoods();
	displayData(0);

	if (sett().value("editName").toBool())
	{
		nameEdit->setEnabled(true);
	}
	else
	{
		nameEdit->setEnabled(false);
	}

	// connects
	connect(okBtn, SIGNAL(clicked()), this, SLOT(doAccept()));
	connect(cancelBtn, SIGNAL(clicked()), this, SLOT(close()));
	connect(comboBox1, SIGNAL(activated(int)), this, SLOT(comboBox1Changed(int)));
	connect(listWidget, SIGNAL(itemSelectionChanged()), this, SLOT(lv1selChanged()));
	connect(spinBox2, SIGNAL(valueChanged(int)), this, SLOT(spinChanged(int)));
	connect(discountSpin, SIGNAL(valueChanged(int)), this, SLOT(calcNet()));
	connect(countSpinBox, SIGNAL(valueChanged(const QString &)), this, SLOT(calcNet()));
}

QString GoodsList::getGoodsId() const
{
	return id;
}

QString GoodsList::getSelItem() const
{
	return selectedItem;
}

QMap<QString, int> GoodsList::getVatsVal() const
{
	return vats;
}

QString GoodsList::getRetVal() const
{
	return ret;
}

// ***************************** SLOTS START *****************************************

/** Slot
 *  spinBox netto numbers changed
 */

void GoodsList::spinChanged(int a)
{
	// qDebug () << __FUNCTION__;

	if (listWidget->selectedItems().size() == 1)
	{
		priceBoxEdit->setValue(
			nets[listWidget->selectedItems().at(0)->text()].split("|")[a - 1].toDouble());
		calcNet();
	}
}

/** Slot
 *  Accept and close
 */
void GoodsList::doAccept()
{
	if (countSpinBox->text() == "" || countSpinBox->value() < 0.001)
	{
		QMessageBox::information(this, "QFaktury", trUtf8("Podaj ilość"), QMessageBox::Ok);
		return;
	}

	selectedItem = nameEdit->text();

	QVector<ProductDataList *> listProducts;
	listProducts.append(std::addressof(goodsList2));
	listProducts.append(std::addressof(servicesList2));

	qDebug() << "listProducts[0]" << listProducts[0];
	qDebug() << "listProducts[1]" << listProducts[1];

	if (selectedItem != "")
	{
		for (int i = 0; i < 2; i++)
		{
			if (comboBox1->currentIndex() == i)
			{
				const auto &currentList = (*listProducts[i]);
				const auto &currentProduct = currentList[id];

				QStringList listRest;
				listRest << selectedItem << currentProduct.getCode() << currentProduct.getPkwiu()
						 << trimZeros(countSpinBox->cleanText()) << currentProduct.getQuantityType()
						 << discountSpin->cleanText()
						 << sett().numberToString(priceBoxEdit->value()) << netLabel->text()
						 << sett().numberToString(currentProduct.getVat()) << grossLabel->text();

				for (int j = 0; j < listRest.count(); j++)
				{
					ret += listRest[j] + "|";
				}
			}
		}

		accept();
	}
	else
	{
		QMessageBox::information(this, "QFaktury", trUtf8("Wskaż towar"), QMessageBox::Ok);
	}
}

/** Slot
 *  ComboBox changed reload the list.
 */

void GoodsList::comboBox1Changed(int x)
{
	// qDebug (__FUNCTION__);
	displayData(x);
}

/** Slot
 *  Reload data in ListView
 */

void GoodsList::lv1selChanged()
{
	if (listWidget->selectedItems().size() == 1)
	{
		QListWidgetItem *item = listWidget->selectedItems().at(0);
		nameEdit->setText(item->text());
		displayNet(item->text());
		id = item->text();
		selectedItem = item->text();
		calcNet();
	}
}

/** Slot
 *  Calulate Netto
 */

void GoodsList::calcNet()
{
	if (listWidget->selectedItems().size() == 1)
	{
		QListWidgetItem *item = listWidget->selectedItems().at(0);
		double price = (countSpinBox->value() * priceBoxEdit->value()); // price * quantity
		double discount = price * (discountSpin->value() * 0.01);
		double net2 = price - discount;
		int vat = vats[item->text()];
		double gross2 = net2 * ((vat * 0.01) + 1);

		// qDebug() << price << discount << net2 << gross2 << vat;
		grossLabel->setText(sett().numberToString(gross2, 'f', 2));
		netLabel->setText(sett().numberToString(net2, 'f', 2));
	}
}

// ***************************** SLOTS END *****************************************

/** Read the XML
 */

void GoodsList::readGoods()
{
	QDomDocument doc(sett().getProdutcsDocName());
	QDomElement root;
	QDomElement good;
	QDomElement service;

	QFile file(sett().getProductsXml());

	if (!file.open(QIODevice::ReadOnly))
	{
		qDebug("file doesn't exists");
		return;
	}

	QTextStream stream(&file);
	if (!doc.setContent(stream.readAll()))
	{
		qDebug("can not set content ");
		file.close();
		return;
	}

	root = doc.documentElement();
	good = root.firstChild().toElement();
	service = root.lastChild().toElement();

	QString text = QString();

	for (QDomNode n = good.firstChild(); !n.isNull(); n = n.nextSibling())
	{
		text = n.toElement().attribute("name");
		ProductData product;
		product.setId(n.toElement().attribute("idx"));
		product.setName(text);
		product.setCode(n.toElement().attribute("code"));
		product.setVat(n.toElement().attribute("vat"));
		product.setQuanType(n.toElement().attribute("quanType"));
		product.setPkwiu(n.toElement().attribute("pkwiu"));
		vats[text] = n.toElement().attribute("vat").toInt();
		nets[text] = n.toElement().attribute("netto1") + "|" + n.toElement().attribute("netto2")
			+ "|" + n.toElement().attribute("netto3") + "|" + n.toElement().attribute("netto4");
		goodsList2.insert(text, product);
	}

	for (QDomNode n = service.firstChild(); !n.isNull(); n = n.nextSibling())
	{
		text = n.toElement().attribute("name");
		ProductData product;
		product.setId(n.toElement().attribute("idx"));
		product.setName(text);
		product.setVat(n.toElement().attribute("vat"));
		product.setCode(n.toElement().attribute("code"));
		product.setQuanType(n.toElement().attribute("quanType"));
		product.setPkwiu(n.toElement().attribute("pkwiu"));
		vats[text] = n.toElement().attribute("vat").toInt();
		nets[text] = n.toElement().attribute("netto1") + "|" + n.toElement().attribute("netto2")
			+ "|" + n.toElement().attribute("netto3") + "|" + n.toElement().attribute("netto4");
		servicesList2.insert(text, product);
	}
}

/** DisplatData
 */

void GoodsList::displayData(int x)
{
	listWidget->clear();

	switch (x)
	{
	case 0:

		for (auto it = goodsList2.begin(); it != goodsList2.end(); ++it)
		{
			listWidget->addItem(it.key());
		}

		break;

	case 1:

		for (auto it = servicesList2.begin(); it != servicesList2.end(); ++it)
		{
			listWidget->addItem(it.key());
		}

		break;
	}
}

/** display Nettos Data
 */

void GoodsList::displayNet(QString index)
{
	priceBoxEdit->setValue(nets[index].split("|")[0].toDouble());
	spinBox2->setValue(1);
}

/** Remove unnecessary zeros 1,000 = 1
 */

QString GoodsList::trimZeros(QString in)
{
	// code to remove unncessery zeros
	QStringList quan = in.split(sett().getDecimalPointStr());
	QString quantity = in;

	if (quan[1].compare("000") == 0)
	{
		quantity = quan[0];
	}

	return quantity;
}
