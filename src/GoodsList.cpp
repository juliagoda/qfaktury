
#include <QtXml/qdom.h>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QList>

#include "GoodsList.h"
#include "Settings.h"

/** Constructor
 */

GoodsList *GoodsList::m_instance = nullptr;

GoodsList::GoodsList(QWidget *parent) : QDialog(parent) {

    qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

    setupUi(this);
  if (parent->objectName() == "GoodsIssuedNotes") ifGoodIssueNote = true;
  else ifGoodIssueNote = false;
  if (parent->objectName() == "DeliveryNote") lockWidgetsDelNotes();
  amounts.clear();
  init();
}

GoodsList::~GoodsList() {

    qDebug() << __FILE__ << __LINE__ << __FUNCTION__;
    
    if (ifGoodIssueNote) {

        disconnect(amountOut, SIGNAL(valueChanged(const QString &)), this,
                               SLOT(calcNet()));

     lab1->deleteLater();
     lab2->deleteLater();
     amountWant->deleteLater();
     amountOut->deleteLater();

     textLabel3_4->show();
     grossLabel->show();
     textLabel1_8->show();
     discountSpin->show();
    }

    if (this->parent()->objectName() == "DeliveryNote") unlockWidgetsDelNotes();
    
    m_instance = nullptr; }

/** Init
 */

void GoodsList::init() {

    qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

    if (ifGoodIssueNote) {

        lab1 = new QLabel;
        lab1->setText("Ilość żądana*:");
        amountWant = new QSpinBox;
        lab2 = new QLabel;
        lab2->setText("Ilość wydana*:");
        amountOut = new QSpinBox;
        _14->addWidget(lab1);
        _14->addWidget(lab2);
        verticalLayout->addWidget(amountWant);
        verticalLayout->addWidget(amountOut);

        textLabel3_4->hide();
        grossLabel->hide();
        textLabel1_8->hide();
        discountSpin->hide();
        
    }

  m_instance = this;
  ret = "";

  // clear all the lists
  goodsList2.clear();
  servicesList2.clear();
  listWidget->clear();

  // load data
  readGoods();
  displayData(0);

  if (sett().value("editName").toBool())
    nameEdit->setEnabled(true);
  else
    nameEdit->setEnabled(false);

  // connects
  connect(okBtn, SIGNAL(clicked()), this, SLOT(doAccept()));
  connect(cancelBtn, SIGNAL(clicked()), this, SLOT(close()));

  /** Slot
   *  ComboBox changed reload the list.
   */

  connect(comboBox1,
          static_cast<void (QComboBox::*)(int)>(&QComboBox::activated),
          [this](int x) { displayData(x); });

  connect(listWidget, SIGNAL(itemSelectionChanged()), this,
          SLOT(lv1selChanged()));
  connect(spinBox2, SIGNAL(valueChanged(int)), this, SLOT(spinChanged(int)));
  connect(discountSpin, SIGNAL(valueChanged(int)), this, SLOT(calcNet()));

  if (ifGoodIssueNote)
        connect(amountOut, SIGNAL(valueChanged(const QString &)), this,
                               SLOT(calcNet()));
  else
        connect(countSpinBox, SIGNAL(valueChanged(const QString &)), this,
          SLOT(calcNet()));
}

GoodsList *GoodsList::instance() { qDebug() << __FILE__ << __LINE__ << __FUNCTION__; return m_instance; }

const QString GoodsList::getGoodsId() { qDebug() << __FILE__ << __LINE__ << __FUNCTION__; return id; }

const QString GoodsList::getSelItem() { qDebug() << __FILE__ << __LINE__ << __FUNCTION__; return selectedItem; }

const QMap<QString, int> GoodsList::getVatsVal() { qDebug() << __FILE__ << __LINE__ << __FUNCTION__; return vats; }

const QString GoodsList::getRetVal() { qDebug() << __FILE__ << __LINE__ << __FUNCTION__; return ret; }

// ***************************** SLOTS START
// *****************************************

/** Slot
 *  spinBox netto numbers changed
 */

void GoodsList::spinChanged(int a) {

  qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

  if (listWidget->selectedItems().size() == 1) {

    priceBoxEdit->setValue(nets[listWidget->selectedItems().at(0)->text()]
                               .split("|")[a - 1]
                               .toDouble());
    calcNet();
  }
}

/** Slot
 *  Accept and close
 */
void GoodsList::doAccept() {

    qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

  if (countSpinBox->text() == "" || countSpinBox->value() < 0.001) {
    QMessageBox::information(this, "QFaktury", trUtf8("Podaj ilość"),
                             QMessageBox::Ok);

    return;
  }
    
    if (ifGoodIssueNote) {
        if ((amountWant->text() == "" || amountWant->value() < 0.001) && (amountOut->text() == "" || amountOut->value() < 0.001)) {
        QMessageBox::information(this, "QFaktury", trUtf8("Podaj ilość żądaną i ilość wydaną"),QMessageBox::Ok);

        return;
        }
    }


  selectedItem = nameEdit->text();

  QVector<QHash<QString, ProductData *>> listProducts;
  listProducts.append(goodsList2);
  listProducts.append(servicesList2);

  qDebug() << "listProducts[0]" << listProducts[0];
  qDebug() << "listProducts[1]" << listProducts[1];

  if (selectedItem != "") {

    for (int i = 0; i < 2; i++) {

      if (comboBox1->currentIndex() == i) {
          
          QStringList listRest;

        
                               
        if (ifGoodIssueNote) {
            
            listRest
                               << selectedItem << listProducts[i][id]->getCode()
                               << listProducts[i][id]->getPkwiu()
                               << trimZeros(countSpinBox->cleanText())
                               << listProducts[i][id]->getQuantityType()
                               << discountSpin->cleanText()
                               << sett().numberToString(priceBoxEdit->value())
                               << netLabel->text()
                               << QString::number(amountWant->value())
                               << QString::number(
                                     amountOut->value());
        } else {
            
            listRest
                               << selectedItem << listProducts[i][id]->getCode()
                               << listProducts[i][id]->getPkwiu()
                               << trimZeros(countSpinBox->cleanText())
                               << listProducts[i][id]->getQuantityType()
                               << discountSpin->cleanText()
                               << sett().numberToString(priceBoxEdit->value())
                               << netLabel->text()
                               << sett().numberToString(
                                      listProducts[i][id]->getVat())
                               << grossLabel->text();
            
        }

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

/** Slot
 *  Reload data in ListView
 */

void GoodsList::lv1selChanged() {

    qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

  if (listWidget->selectedItems().size() == 1) {

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

void GoodsList::calcNet() {

    qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

  if (listWidget->selectedItems().size() == 1) {

    double price =
        (amountOut->value() * priceBoxEdit->value()); // price * quantity

    // qDebug() << price;
    netLabel->setText(sett().numberToString(price, 'f', 2));
  }
}

// ***************************** SLOTS END
// *****************************************

/** Read the XML
 */

void GoodsList::readGoods() {

    qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

  QDomDocument doc(sett().getProdutcsDocName());
  QDomElement root;
  QDomElement good;
  QDomElement service;

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
      good = root.firstChild().toElement();
      service = root.lastChild().toElement();
    }

    QString text = QString();

    for (QDomNode n = good.firstChild(); !n.isNull(); n = n.nextSibling()) {

      text = n.toElement().attribute("name");
      ProductData *product = new ProductData();
      product->setId(n.toElement().attribute("idx"));
      product->setName(text);
      product->setCode(n.toElement().attribute("code"));
      product->setVat(n.toElement().attribute("vat"));
      product->setQuanType(n.toElement().attribute("quanType"));
      product->setPkwiu(n.toElement().attribute("pkwiu"));

      if (ifGoodIssueNote) {
       product->setRequiredAmount(n.toElement().attribute("requiredAmount"));
       product->setGivedOutAmount(n.toElement().attribute("givedOutAmount"));
       amounts.append(n.toElement().attribute("requiredAmount").toInt());
       amounts.append(n.toElement().attribute("givedOutAmount").toInt());
      }
      vats[text] = n.toElement().attribute("vat").toInt();
      nets[text] = n.toElement().attribute("netto1") + "|" +
                   n.toElement().attribute("netto2") + "|" +
                   n.toElement().attribute("netto3") + "|" +
                   n.toElement().attribute("netto4");
      goodsList2.insert(text, product);

      if (product != 0)
        product = 0;
      delete product;
    }

    for (QDomNode n = service.firstChild(); !n.isNull(); n = n.nextSibling()) {
      text = n.toElement().attribute("name");
      ProductData *product = new ProductData();
      product->setId(n.toElement().attribute("idx"));
      product->setName(text);
      product->setVat(n.toElement().attribute("vat"));
      product->setCode(n.toElement().attribute("code"));
      product->setQuanType(n.toElement().attribute("quanType"));
      product->setPkwiu(n.toElement().attribute("pkwiu"));

      if (ifGoodIssueNote) {
       product->setRequiredAmount(n.toElement().attribute("requiredAmount"));
       product->setGivedOutAmount(n.toElement().attribute("givedOutAmount"));
       amounts.append(n.toElement().attribute("requiredAmount").toInt());
       amounts.append(n.toElement().attribute("givedOutAmount").toInt());
      }
      vats[text] = n.toElement().attribute("vat").toInt();
      nets[text] = n.toElement().attribute("netto1") + "|" +
                   n.toElement().attribute("netto2") + "|" +
                   n.toElement().attribute("netto3") + "|" +
                   n.toElement().attribute("netto4");
      servicesList2.insert(text, product);

      if (product != 0)
        product = 0;
      delete product;
    }
  }
}

/** DisplatData
 */

void GoodsList::displayData(int x) {

    qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

  listWidget->clear();
  
  if (ifGoodIssueNote) {
      amountWant->setValue(amounts.at(0));
      amountOut->setValue(amounts.at(1));
  }

  switch (x) {
  case 0:

    for (QHash<QString, ProductData *>::iterator iter = goodsList2.begin();
         iter != goodsList2.end(); ++iter) {
      listWidget->addItem(iter.key());
    }

    break;
  case 1:

    for (QHash<QString, ProductData *>::iterator iter = servicesList2.begin();
         iter != servicesList2.end(); ++iter) {
      listWidget->addItem(iter.key());
    }

    break;
  }
}

/** display Nettos Data
 */

void GoodsList::displayNet(QString index) {

    qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

  priceBoxEdit->setValue(nets[index].split("|")[0].toDouble());
  spinBox2->setValue(1);
}

/** Remove unnecessary zeros 1,000 = 1
 */

QString GoodsList::trimZeros(QString in) {

    qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

  // code to remove unncessery zeros
  QStringList quan = in.split(sett().getDecimalPointStr());
  QString quantity = in;

  if (quan[1].compare("000") == 0)
    quantity = quan[0];

  return quantity;
}


void GoodsList::lockWidgetsDelNotes() {

    qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

textLabel1_8->hide();
discountSpin->hide();
textLabel3_3->hide();
textLabel3_4->hide();
netLabel->hide();
grossLabel->hide();

}

void GoodsList::unlockWidgetsDelNotes() {

    qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

textLabel1_8->show();
discountSpin->show();
textLabel3_3->show();
textLabel3_4->show();
netLabel->show();
grossLabel->show();

}
