#include "moc_TowaryLista.cpp"
#include <QtXml/qdom.h>
#include <QDir>
#include <QMessageBox>
#include <QTextCodec>
#include <QTextStream>
#include <QDebug>
#include <QListWidgetItem>

#include "TowaryLista.h"

/** Constructor
 */
TowaryLista::TowaryLista(QWidget *parent): QDialog(parent) {
    setupUi(this);
    init();
}

/** Init
 */
void TowaryLista::init() {
	ret = "";
	// clear all the lists
	listaTowary2.clear();
	listaUslugi2.clear();
	listWidget->clear();

	// load data
	readTow ();
	displayData(0);

    if (sett().value("editName").toBool()) {
		nameEdit->setEnabled(true);

	} else {
		nameEdit->setEnabled(false);

	}

	// connects
	connect(okBtn, SIGNAL( clicked() ), this, SLOT( doAccept()));
	connect(cancelBtn, SIGNAL( clicked() ), this, SLOT( close()));
	connect(comboBox1, SIGNAL( activated(int) ), this, SLOT( comboBox1Changed(int)));
	connect(listWidget, SIGNAL(itemSelectionChanged()), this, SLOT(lv1selChanged()));
	connect(spinBox2, SIGNAL( valueChanged(int) ), this, SLOT( spinChanged(int) ) );
	// connect( nameEdit, SIGNAL( textChanged(const QString&) ), this, SLOT( setSelItemText() ) );
	connect(rabatSpin, SIGNAL( valueChanged(int) ), this, SLOT( calcNetto() ) );
	// connect( countSpinBox, SIGNAL( lostFocus() ), this, SLOT( calcNetto() ) );
	// connect( countSpinBox, SIGNAL( selectionChanged() ), this, SLOT( calcNetto() ) );
	connect(countSpinBox, SIGNAL( valueChanged(const QString&) ), this, SLOT( calcNetto() ) );
}

// ***************************** SLOTS START *****************************************

/** Slot
 *  spinBox netto numbers changed
 */
void TowaryLista::spinChanged(int a) {
	// qDebug () << __FUNCTION__;
	QList<QListWidgetItem *> items = listWidget->selectedItems();
	if (items.size() == 1) {
		QListWidgetItem *item = items[0];
		priceBoxEdit->setValue(nettos[item->text()].split("|")[a - 1].toDouble());
		calcNetto();
	}
}

/** Slot
 *  Accept and close
 */
void TowaryLista::doAccept() {
	if (countSpinBox->text() == "" || countSpinBox->value() < 0.001) {
		QMessageBox::information(this, "QFaktury", trUtf8("Podaj ilość"),
				QMessageBox::Ok);
		return;
	}

	selectedItem = nameEdit->text();

	if (selectedItem != "") {
		if (comboBox1->currentIndex() == 0) {
			ret = selectedItem + "|" + listaTowary2[id]->getCode() + "|"
					+ listaTowary2[id]->getPkwiu() + "|"
					+ trimZeros(countSpinBox->cleanText()) + "|"
					+ listaTowary2[id]->getQuantityType() + "|"
					+ rabatSpin->cleanText() + "|"
					+ sett().numberToString(priceBoxEdit->value()) + "|"
					+ nettoLabel->text() + "|" + sett().numberToString(listaTowary2[id]->getVat()) + "|"
					+ bruttoLabel->text();

		}
		if (comboBox1->currentIndex() == 1) {
			ret = selectedItem + "|" + listaUslugi2[id]->getCode() + "|"
					+ listaUslugi2[id]->getPkwiu() + "|"
					+ trimZeros(countSpinBox->cleanText()) + "|"
					+ listaUslugi2[id]->getQuantityType() + "|"
					+ rabatSpin->cleanText() + "|"
					+ sett().numberToString(priceBoxEdit->value()) + "|"
					+ nettoLabel->text() + "|" + sett().numberToString(listaUslugi2[id]->getVat()) + "|"
					+ bruttoLabel->text();

		}
		accept();
	} else {
		QMessageBox::information(this, "QFaktury", trUtf8("Wskaż towar"),
				QMessageBox::Ok);
	}
}

/** Slot
 *  ComboBox changed reload the list.
 */
void TowaryLista::comboBox1Changed(int x) {
	// qDebug (__FUNCTION__);
	displayData(x);
}

/** Slot
 *  Reload data in ListView
 */
void TowaryLista::lv1selChanged() {
	QList<QListWidgetItem *> items = listWidget->selectedItems();
	if (items.size() == 1) {
		QListWidgetItem *item = items[0];
		nameEdit->setText(item->text());
		displayNetto(item->text());
		id = item->text();
		selectedItem = item->text();
		calcNetto();
	}
}

/** Slot
 *  Calulate Netto
 */
void TowaryLista::calcNetto() {
	QList<QListWidgetItem *> items = listWidget->selectedItems();
	if (items.size() == 1) {
		QListWidgetItem *item = items[0];
		double price = (countSpinBox->value() * priceBoxEdit->value()); // price * quantity
		double discount = price * (rabatSpin->value() * 0.01);
		double netto2 = price - discount;
		int vat = vats[item->text()];
		double brutto2 = netto2 * ((vat * 0.01) + 1);
		// qDebug() << price << discount << netto2 << brutto2 << vat;
		bruttoLabel->setText(sett().numberToString(brutto2, 'f', 2));
		nettoLabel->setText(sett().numberToString(netto2, 'f', 2));
	}
}


// ***************************** SLOTS END *****************************************

/** Read the XML
 */
void TowaryLista::readTow() {
	QDomDocument doc(sett().getProdutcsDocName());
	QDomElement root;
	QDomElement towar;
	QDomElement usluga;
	QString code, curr, pkwiu;

	QFile file(sett().getProductsXml());
	if (!file.open(QIODevice::ReadOnly)) {
		qDebug("file doesn't exists");
		return;
	} else {
		QTextStream stream(&file);
		if (!doc.setContent(stream.readAll())) {
			qDebug("can not set content ");
			file.close();
			return;
		} else {
			root = doc.documentElement();
			towar = root.firstChild().toElement();
			usluga = root.lastChild().toElement();
		}
		QString text, idx;

		for (QDomNode n = towar.firstChild(); !n.isNull(); n = n.nextSibling()) {
			text = n.toElement().attribute("name");
			ProductData *product = new ProductData();
			product->setId(n.toElement().attribute("idx"));
			product->setName(text);
			product->setCode(n.toElement().attribute("code"));
			product->setVat(n.toElement().attribute("vat"));
						product->setQuanType(n.toElement().attribute("quanType"));
			product->setPkwiu(n.toElement().attribute("pkwiu"));
			vats[text] = n.toElement ().attribute ("vat").toInt();
			nettos[text] = n.toElement ().attribute ("netto1") + "|" +
						n.toElement ().attribute ("netto2") + "|" +
						n.toElement ().attribute ("netto3") + "|" +
						n.toElement ().attribute ("netto4");
			listaTowary2.insert(text, product);

		}

		for (QDomNode n = usluga.firstChild(); !n.isNull(); n = n.nextSibling()) {
			text = n.toElement().attribute("name");
			ProductData *product = new ProductData();
			product->setId(n.toElement().attribute("idx"));
			product->setName(text);
			product->setVat(n.toElement().attribute("vat"));
			product->setCode(n.toElement().attribute("code"));
			product->setQuanType(n.toElement().attribute("quanType"));
			product->setPkwiu(n.toElement().attribute("pkwiu"));
			vats[text] = n.toElement ().attribute ("vat").toInt();
			nettos[text] = n.toElement ().attribute ("netto1") + "|" +
						n.toElement ().attribute ("netto2") + "|" +
						n.toElement ().attribute ("netto3") + "|" +
						n.toElement ().attribute ("netto4");
			listaUslugi2.insert(text, product);
		}
	}
}

/** DisplatData
 */
void TowaryLista::displayData(int x) {
	listWidget->clear();

	switch (x) {
	case 0:
		for (QMap<QString, ProductData *>::iterator iter = listaTowary2.begin();
				iter != listaTowary2.end();
				++iter) {
			listWidget->addItem(iter.key());
		}
		break;
	case 1:
		for (QMap<QString, ProductData *>::iterator iter = listaUslugi2.begin();
						iter != listaUslugi2.end();
						++iter) {
			listWidget->addItem(iter.key());
		}
		break;
	}
}

/** display Nettos Data
 */
void TowaryLista::displayNetto(QString index) {
	priceBoxEdit->setValue(nettos[index].split("|")[0].toDouble());
	spinBox2->setValue(1);
}


/** Remove unnecessary zeros 1,000 = 1
 */
QString TowaryLista::trimZeros(QString in) {
	// code to remove unncessery zeros
	QStringList quan = in.split(sett().getDecimalPointStr());
	QString quantity = in;
	if (quan[1].compare("000") == 0) {
		quantity = quan[0];
	}
	return quantity;
}
