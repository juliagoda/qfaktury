
#include "Goods.h"
#include "IDataLayer.h"
#include "Settings.h"
#include "Validations.h"

#include <QDesktopServices>
#include <QUrl>

/** Constructor
 */

Goods::Goods(QWidget *parent, int mode, IDataLayer *dl) : QDialog(parent) {
<<<<<<< HEAD
=======

  qDebug() << __FILE__ << __LINE__ << __FUNCTION__;
>>>>>>> testing

  workMode = mode;
  dataLayer = dl;

  setupUi(this);
  init();
}

/** Inits
 */

void Goods::init() {

<<<<<<< HEAD
  selectData("", 0);

  jednCombo->addItems(sett().value("units").toString().split("|"));
  cbVat->addItems(sett().value("rates").toString().split("|"));

  connect(okButton, SIGNAL(clicked()), this, SLOT(okClick()));
  connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));

=======
  qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

  selectData("", 0);

  jednCombo->addItems(sett().value("units").toString().split("|"));
  cbVat->addItems(sett().value("rates").toString().split("|"));

  connect(okButton, SIGNAL(clicked()), this, SLOT(okClick()));
  connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));

>>>>>>> testing
  /** Slot
   *  Nett value changed
   */

  connect(
<<<<<<< HEAD
      netEdit, static_cast<void (QDoubleSpinBox::*)(double)>(
                   &QDoubleSpinBox::valueChanged),
      [this](double) { net[spinBox2->value() - 1] = netEdit->cleanText(); });

  /** Slot
   *  spinBox with list of prices changed
   */

  connect(spinBox2,
          static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
          [this](int a) { netEdit->setValue(net[a - 1].toDouble()); });

  /** Slot
   *  Finds PKWIU code on the net
   */
  connect(pkwiuBtn, &QToolButton::clicked, [this]() {
    QDesktopServices::openUrl(QUrl(tr(
        "http://www.vat.pl/pkwiu/index.php?rodzajKlasyfikacji=pkwiuvat&kod")));
  });
=======
      netEdit,
      static_cast<void (QDoubleSpinBox::*)(double)>(
          &QDoubleSpinBox::valueChanged),
      [this](double) { net[spinBox2->value() - 1] = netEdit->cleanText(); });

  /** Slot
   *  spinBox with list of prices changed
   */

  connect(spinBox2,
          static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
          [this](int a) { netEdit->setValue(net[a - 1].toDouble()); });

  /** Slot
   *  Finds PKWIU code on the net
   */
  connect(pkwiuBtn, &QToolButton::clicked, [this]() {
    QDesktopServices::openUrl(QUrl(tr(
        "http://www.vat.pl/pkwiu/index.php?rodzajKlasyfikacji=pkwiuvat&kod")));
  });
}

const QString Goods::getRetGoods() {
  qDebug() << __FILE__ << __LINE__ << __FUNCTION__;
  return ret;
>>>>>>> testing
}

const QString Goods::getRetGoods() { return ret; }

/******************** SLOTS START ***************************/

/** Slot
 *  saves data to XML file and returns row for products table
 */

void Goods::okClick() {

<<<<<<< HEAD
  if (Validations::instance()->isEmptyField(nameEdit->text(),
                                            textLabel3->text()))
    return;

  if (!pkwiuEdit->text().isEmpty()) {

    if (!Validations::instance()->validatePkwiu(pkwiuEdit->text()))
      return;
  }

  QStringList listRet =
      QStringList() << isEmpty(idxEdit->text()) << isEmpty(nameEdit->text())
                    << isEmpty(shortcutEdit->text())
                    << isEmpty(codeEdit->text()) << isEmpty(pkwiuEdit->text())
                    << isEmpty(typeCombo->currentText())
                    << isEmpty(jednCombo->currentText()) << isEmpty(net[0])
                    << isEmpty(net[1]) << isEmpty(net[2]) << isEmpty(net[3])
                    << isEmpty(cbVat->currentText());

  if (workMode == 1) {

    if (updateData()) {

      foreach (QString listEl, listRet) { ret += listEl + "|"; }

=======
  qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

  if (Validations::instance()->isEmptyField(nameEdit->text(),
                                            textLabel3->text()))
    return;

  if (!pkwiuEdit->text().isEmpty()) {

    if (!Validations::instance()->validatePkwiu(pkwiuEdit->text()))
      return;
  }

  QStringList listRet =
      QStringList() << isEmpty(idxEdit->text()) << isEmpty(nameEdit->text())
                    << isEmpty(shortcutEdit->text())
                    << isEmpty(codeEdit->text()) << isEmpty(pkwiuEdit->text())
                    << isEmpty(typeCombo->currentText())
                    << isEmpty(jednCombo->currentText()) << isEmpty(net[0])
                    << isEmpty(net[1]) << isEmpty(net[2]) << isEmpty(net[3])
                    << isEmpty(cbVat->currentText());

  if (workMode == 1) {

    if (updateData()) {

      foreach (QString listEl, listRet) { ret += listEl + "|"; }

>>>>>>> testing
      accept();
    }

  } else {

    if (insertData()) {

      foreach (QString listEl, listRet) { ret += listEl + "|"; }

      accept();
    }
  }
}

// helper method which sets "-" in input forms
QString Goods::isEmpty(QString in) {

<<<<<<< HEAD
=======
  qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

>>>>>>> testing
  if (in == "")
    return " ";
  return in;
}

/******************** SLOTS END ***************************/

/** Loads data into the form
 */

void Goods::selectData(QString idx, int type) {

<<<<<<< HEAD
  if (idx == "") {

    for (int i = 1; i < 5; i++)
      net.append("0");
    netEdit->setValue(0);

  } else {

    setWindowTitle(trUtf8("Edytuj towar/usługę"));
    typeCombo->setEnabled(false);
  }

  ProductData prodData = dataLayer->productsSelectData(idx, type);

  if (workMode == 0) {

    idx = QString::number(prodData.lastProdId);
    idxEdit->setText(idx);

  } else {

    getData(prodData);
  }

  typeCombo->setCurrentIndex(type);
}

=======
  qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

  if (idx == "") {

    for (int i = 1; i < 5; i++)
      net.append("0");
    netEdit->setValue(0);

  } else {

    setWindowTitle(trUtf8("Edytuj towar/usługę"));
    typeCombo->setEnabled(false);
  }

  ProductData prodData = dataLayer->productsSelectData(idx, type);

  if (workMode == 0) {

    idx = QString::number(prodData.lastProdId);
    idxEdit->setText(idx);

  } else {

    getData(prodData);
  }

  typeCombo->setCurrentIndex(type);
}

>>>>>>> testing
/** Saves data from the form
 */

bool Goods::insertData() {

<<<<<<< HEAD
=======
  qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

>>>>>>> testing
  ProductData prodData;
  setData(prodData);
  dataLayer->productsInsertData(prodData, typeCombo->currentIndex());
  return true;
}

/** Modifies product
 *  Searches for the right one and saves it.
 */

bool Goods::updateData() {

<<<<<<< HEAD
=======
  qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

>>>>>>> testing
  ProductData prodData;
  setData(prodData);
  dataLayer->productsUpdateData(prodData, typeCombo->currentIndex(),
                                idxEdit->text());
  return true;
}

/** Loads from the form to Data object
 */

void Goods::getData(ProductData prodData) {

<<<<<<< HEAD
=======
  qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

>>>>>>> testing
  idxEdit->setText(QString::number(prodData.id));
  nameEdit->setText(prodData.name);
  codeEdit->setText(prodData.code);
  shortcutEdit->setText(prodData.desc);
  pkwiuEdit->setText(prodData.pkwiu);

  int current = 0;
  current =
      sett().value("units").toString().split("|").indexOf(prodData.quanType);
  jednCombo->setCurrentIndex(current);
  current = sett().value("rates").toString().split("|").indexOf(
      QString::number(prodData.vat));
  cbVat->setCurrentIndex(current);
  netEdit->setValue(prodData.prices[0]);

  for (int i = 0; i < 4; i++)
    net[i] = sett().numberToString(prodData.prices[i]);
}

/** Display productData
 */

void Goods::setData(ProductData &prodData) {

<<<<<<< HEAD
=======
  qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

>>>>>>> testing
  prodData.id = idxEdit->text().toInt();
  prodData.name = nameEdit->text();
  prodData.desc = shortcutEdit->text();
  prodData.code = codeEdit->text();
  prodData.pkwiu = pkwiuEdit->text();
  prodData.quanType = jednCombo->currentText();

  for (int i = 0; i < 4; i++)
    prodData.prices[i] = sett().stringToDouble(net[i]);
  prodData.vat = cbVat->currentText().toInt();
}
