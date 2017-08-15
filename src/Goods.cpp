
#include "Goods.h"
#include "Settings.h"
#include "Validations.h"

#include <QDesktopServices>
#include <QUrl>

/** Constructor
 */

Goods::Goods(QWidget *parent, int mode, IDataLayer *dl)
	: QDialog(parent)
{
	workMode = mode;
	dataLayer = dl;

	setupUi(this);
	init();
}

/** Inits
 */

void Goods::init()
{
	selectData("", 0);

	jednCombo->addItems(sett().value("units").toString().split("|"));
	cbVat->addItems(sett().value("rates").toString().split("|"));

	connect(okButton, SIGNAL(clicked()), this, SLOT(okClick()));
	connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
	connect(netEdit, SIGNAL(valueChanged(double)), this, SLOT(netChanged(double)));
	connect(spinBox2, SIGNAL(valueChanged(int)), this, SLOT(spinChanged(int)));
	connect(pkwiuBtn, SIGNAL(clicked()), this, SLOT(pkwiuGet()));
}

const QString Goods::getRetGoods()
{
	return ret;
}

/******************** SLOTS START ***************************/

/** Slot
 *  saves data to XML file and returns row for products table
 */

void Goods::okClick()
{
	if (Validations::instance()->isEmptyField(nameEdit->text(), textLabel3->text()))
	{
		return;
	}

	if (!pkwiuEdit->text().isEmpty())
	{
		if (!Validations::instance()->validatePkwiu(pkwiuEdit->text()))
		{
			return;
		}
	}

	QStringList listRet;
	listRet << isEmpty(idxEdit->text()) << isEmpty(nameEdit->text())
			<< isEmpty(shortcutEdit->text()) << isEmpty(codeEdit->text())
			<< isEmpty(pkwiuEdit->text()) << isEmpty(typeCombo->currentText())
			<< isEmpty(jednCombo->currentText()) << isEmpty(net[0]) << isEmpty(net[1])
			<< isEmpty(net[2]) << isEmpty(net[3]) << isEmpty(cbVat->currentText());

	if (workMode == 1)
	{
		if (updateData())
		{
			foreach (QString listEl, listRet)
			{
				ret += listEl + "|";
			}

			accept();
		}
	}
	else
	{
		if (insertData())
		{
			foreach (QString listEl, listRet)
			{
				ret += listEl + "|";
			}

			accept();
		}
	}
}

// helper method which sets "-" in input forms
QString Goods::isEmpty(QString in)
{
	if (in == "")
	{
		return " ";
	}
	return in;
}

/** Slot
 *  spinBox with list of prices changed
 */

void Goods::spinChanged(int a)
{
	netEdit->setValue(net[a - 1].toDouble());
}

/** Slot
 *  Nett value changed
 */

void Goods::netChanged(double /*unused*/)
{
	net[spinBox2->value() - 1] = netEdit->cleanText();
}

/** Slot
 *  Finds PKWIU code on the net
 */

void Goods::pkwiuGet()
{
	QDesktopServices::openUrl(
		QUrl(tr("http://www.vat.pl/pkwiu/index.php?rodzajKlasyfikacji=pkwiuvat&kod")));
}

/******************** SLOTS END ***************************/

/** Loads data into the form
 */

void Goods::selectData(QString idx, int type)
{
	if (idx == "")
	{
		for (int i = 1; i < 5; i++)
		{
			net.append("0");
		}
		netEdit->setValue(0);
	}
	else
	{
		setWindowTitle(trUtf8("Edytuj towar/usługę"));
		typeCombo->setEnabled(false);
	}

	ProductData prodData = dataLayer->productsSelectData(idx, type);

	if (workMode == 0)
	{
		idx = QString::number(prodData.lastProdId);
		idxEdit->setText(idx);
	}
	else
	{
		getData(prodData);
	}

	typeCombo->setCurrentIndex(type);
}

/** Saves data from the form
 */

bool Goods::insertData()
{
	netChanged(0);
	ProductData prodData;
	setData(prodData);
	dataLayer->productsInsertData(prodData, typeCombo->currentIndex());
	return true;
}

/** Modifies product
 *  Searches for the right one and saves it.
 */

bool Goods::updateData()
{
	netChanged(0);
	ProductData prodData;
	setData(prodData);
	dataLayer->productsUpdateData(prodData, typeCombo->currentIndex(), idxEdit->text());
	return true;
}

/** Loads from the form to Data object
 */

void Goods::getData(ProductData prodData)
{
	idxEdit->setText(QString::number(prodData.id));
	nameEdit->setText(prodData.name);
	codeEdit->setText(prodData.code);
	shortcutEdit->setText(prodData.desc);
	pkwiuEdit->setText(prodData.pkwiu);

	int current = 0;
	current = sett().value("units").toString().split("|").indexOf(prodData.quanType);
	jednCombo->setCurrentIndex(current);
	current = sett().value("rates").toString().split("|").indexOf(QString::number(prodData.vat));
	cbVat->setCurrentIndex(current);
	netEdit->setValue(prodData.prices[0]);

	for (int i = 0; i < 4; i++)
	{
		net[i] = sett().numberToString(prodData.prices[i]);
	}
}

/** Display productData
 */

void Goods::setData(ProductData &prodData)
{
	prodData.id = idxEdit->text().toInt();
	prodData.name = nameEdit->text();
	prodData.desc = shortcutEdit->text();
	prodData.code = codeEdit->text();
	prodData.pkwiu = pkwiuEdit->text();
	prodData.quanType = jednCombo->currentText();

	for (int i = 0; i < 4; i++)
	{
		prodData.prices[i] = sett().stringToDouble(net[i]);
	}
	prodData.vat = cbVat->currentText().toInt();
}
