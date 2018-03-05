#include "warehouse.h"
#include "const.h"
#include "mainwindow.h"
#include "xmldatalayer.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>

/** Constructor
 */

Warehouse::Warehouse(QWidget *parent, IDataLayer *dl, QString in_form)
    : Invoice(parent, dl, in_form) {
  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;
}

/** Destructor
 */

Warehouse::~Warehouse() {}

void Warehouse::readWarehouseData(QString invFile) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  backBtn->setEnabled(false);
  invNr->setEnabled(false);

  setWindowTitle(trUtf8("Edytuje WZ"));

  qDebug("invFile file");
  qDebug() << invFile;

  QDomDocument doc(sett().getWarehouseFullDir());
  QDomElement root;
  QDomElement buyer;
  QDomElement product;

  // fName = invFile;
  // prepayFile = invFile;

  QFile file(sett().getWarehouseFullDir() + invFile);
  QTextStream stream(&file);

  if (!file.open(QIODevice::ReadOnly) || !doc.setContent(stream.readAll())) {

    QFileInfo check_file(file.fileName());

    if (check_file.exists() && check_file.isFile()) {

      QFile(file.fileName())
          .setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner);

    } else {

      QMessageBox::warning(
          this, trUtf8("Brak dostępu"),
          trUtf8("Plik przechowujący dane o dokumencie magazynu w ścieżce ") +
              file.fileName() + trUtf8(" nie istnieje.") +
              trUtf8(" Jesteś pewien, że plik o tej nazwie nie jest "
                     "przechowywany w innym folderze?"));
      return;
    }
  }

  root = doc.documentElement();
  QLabel *messageDelNote = new QLabel;
  messageDelNote->setText("Dla tego dokumentu faktura była już wystawiana");
  if (root.attribute("invoice").toInt() == 0)
    horizontalLayout_4->addWidget(messageDelNote);
  else
    messageDelNote->deleteLater();
  this->update();
  invNr->setText(root.attribute("no"));
  sellingDate->setDate(
      QDate::fromString(root.attribute("sellingDate"), sett().getDateFormat()));
  productDate->setDate(
      QDate::fromString(root.attribute("issueDate"), sett().getDateFormat()));
  endTransactionDate->setDate(
      QDate::fromString(root.attribute("endTransDate"), sett().getDateFormat()));

  wareData = new WarehouseData();
  wareData->invNr = invNr->text();

  QDomNode tmp;
  tmp = root.firstChild();
  tmp = tmp.toElement().nextSibling(); // buyer
  buyer = tmp.toElement();
  buyerName->setText(buyer.attribute("name") + "," + buyer.attribute("city") +
                     "," + buyer.attribute("street") + "," + trUtf8("NIP: ") +
                     buyer.attribute("tic") + ", " + trUtf8("Konto: ") +
                     buyer.attribute("account") + ", " + trUtf8("Tel: ") +
                     buyer.attribute("phone") + ", " + trUtf8("Email: ") +
                     buyer.attribute("email") + ", " + trUtf8("Strona: ") +
                     buyer.attribute("website"));
  buyerName->setCursorPosition(1);

  //*********************** Load Products Vars ***************************

  int goodsCount = 0;
  int i = 0;
  QDomElement good;

  static const char *goodsColumns[] = {"id", "name", "quantity",
                                       "quantityType"};

  //*********************** Load Products After ***************************

  tmp = tmp.toElement().nextSibling(); // product after
  product = tmp.toElement();
  goodsCount = product.attribute("productsCount").toInt();
  discountVal->setValue(0);

  goodsCount = product.attribute("productsCount").toInt();
  i = 0;
  good = product.firstChild().toElement();

  tableGoods->setRowCount(goodsCount);

  for (i = 0; i < goodsCount; ++i) {

    tableGoods->setItem(i, 0,
                        new QTableWidgetItem(good.attribute(goodsColumns[0])));
    tableGoods->setItem(i, 1,
                        new QTableWidgetItem(good.attribute(goodsColumns[1])));
    tableGoods->setItem(i, 4,
                        new QTableWidgetItem(good.attribute(goodsColumns[2])));
    tableGoods->setItem(i, 5,
                        new QTableWidgetItem(good.attribute(goodsColumns[3])));

    good = good.nextSibling().toElement();
  }

  //*********************** Load Products Before ***************************

  tmp = tmp.toElement().nextSibling(); // product before
  product = tmp.toElement();
  goodsCount = product.attribute("productsCount").toInt();
  good = product.firstChild().toElement();

  wareData->customer = buyerName->text();
  wareData->sellingDate = sellingDate->date();
  wareData->productDate = productDate->date();
  wareData->endTransDate = endTransactionDate->date();

  for (i = 0; i < goodsCount; ++i) {

    ProductData product; //  = new ProductData();
    product.setId(good.attribute(goodsColumns[0]));
    product.setName(good.attribute(goodsColumns[1]));
    product.setQuantity(good.attribute(goodsColumns[3]));
    product.setQuanType(good.attribute(goodsColumns[4]));
    wareData->products[i] = product;
    good = good.nextSibling().toElement();
  }

  tmp = tmp.toElement().nextSibling();
  QDomElement additional = tmp.toElement();
  additEdit->setText(additional.attribute("text"));
  wareData->additText = additEdit->text();
  wareData->paymentType = additional.attribute("paymentType");
  paysCombo->setCurrentText(wareData->paymentType);

  liabDate->setDate(QDate::fromString(additional.attribute("liabDate"),
                                      sett().getDateFormat()));
  wareData->liabDate = liabDate->date();

  canClose = true;
  saveBtn->setEnabled(false);

  setIsEditAllowed(sett().value("edit").toBool());
  file.close();

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__
           << "EXIT";
}

bool Warehouse::saveInvoice() {

  qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << fName;

  bool result = false;
  if (!validateForm())
    return false;

  WarehouseData wareData;
  setData(wareData);

  result = dataLayer->warehouseInsertData(wareData, type);
  retWarehouse = dataLayer->getRetWarehouse();
  MainWindow::instance()->shouldHidden = true;
  makeInvoice(false);
  MainWindow::instance()->shouldHidden = false;

  if (!result) {
    QMessageBox::warning(
        this, trUtf8("Zapis dokumentu WZ"),
        trUtf8("Zapis dokumentu WZ zakończył się niepowodzeniem. Sprawdź, czy "
               "masz "
               "uprawnienia do zapisu lub odczytu w ścieżce ") +
            sett().getWarehouseFullDir() +
            trUtf8(" oraz czy ścieżka istnieje."));
  }

  saveBtn->setEnabled(false);
  rmGoodsBtn->setEnabled(false);
  editGoodsBtn->setEnabled(false);

  saveFailed = false;
  canClose = true;

  return result;
}

void Warehouse::setData(WarehouseData &invData) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  invData.id = fName;
  invData.customer = buyerName->text();
  qDebug() << "buyerName->text() in setData(InvoiceData&):"
           << buyerName->text();
  invData.invNr = invNr->text();
  invData.sellingDate = sellingDate->date();
  invData.issueDate = productDate->date();
  invData.endTransDate = endTransactionDate->date();

  // no, name, code, pkwiu, amount, unit, discount, unit price, net, vat, gross
  for (int i = 0; i < tableGoods->rowCount(); ++i) {
    ProductData product; //  = new ProductData();

    product.setId(tableGoods->item(i, 0)->text());
    product.setName(tableGoods->item(i, 1)->text());
    product.setQuantity(tableGoods->item(i, 4)->text());
    product.setQuanType(tableGoods->item(i, 5)->text());
    invData.products[i] = product;
  }

  invData.additText = additEdit->text();
  invData.paymentType = paysCombo->currentText();

  invData.liabDate = liabDate->date();

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__
           << "EXIT";
}

void Warehouse::backBtnClick() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  QString prefix, suffix;
  prefix = sett().value("prefix").toString();
  int nr = MainWindow::instance()->getMaxSymbolWarehouse() + 1;

  qDebug() << "nr: " << nr;

  lastWarehouse =
      prefix + numbersCount(nr, sett().value("chars_in_symbol").toInt());

  qDebug() << "Begin of lastWarehouse : " << lastWarehouse;

  if (sett().value("day").toBool())
    lastWarehouse += "/" + QDate::currentDate().toString("dd");

  if (sett().value("month").toBool())
    lastWarehouse += "/" + QDate::currentDate().toString("MM");

  if (sett().value("year").toBool()) {
    if (!sett().value("shortYear").toBool())
      lastWarehouse += "/" + QDate::currentDate().toString("yy");
    else
      lastWarehouse += "/" + QDate::currentDate().toString("yyyy");

    suffix = sett().value("sufix").toString();
    lastWarehouse += suffix;
  }

  Invoice::instance()->invNr->setText(lastWarehouse);

  qDebug() << "QLineEdit invNr: " << invNr->text();

  saveBtn->setEnabled(true);
}

void Warehouse::canQuit() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__
           << ": canClose " << canClose;

  if (canClose) {

    if (retWarehouse.isNull())
      reject();
    else
      accept();

  } else {

    if (QMessageBox::warning(
            this, "QFaktury",
            trUtf8("Dane zostały zmienione. Czy chcesz zapisać?"),
            trUtf8("Tak"), trUtf8("Nie"), 0, 0, 1) == 1) {
      saveColumnsWidth();
      reject();

    } else {

      saveInvoice();
      if (saveFailed) {
        return;
      }
      saveColumnsWidth();
      accept();
    }
  }
}

void Warehouse::readData(QString fraFile) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;
  prepayFile = fraFile;
  qDebug() << "prepayFile w readData: " << prepayFile;
  backBtn->setEnabled(false);
  invNr->setEnabled(false);

  getData(dataLayer->warehouseSelectData(fraFile, type));

  canClose = true;
  saveBtn->setEnabled(false);

  setIsEditAllowed(sett().value("edit").toBool());

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__
           << "EXIT";
}

void Warehouse::getData(WarehouseData invData) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  buyerName->setText(invData.customer);
  invNr->setText(invData.invNr);
  sellingDate->setDate(invData.sellingDate);
  productDate->setDate(invData.issueDate);
  endTransactionDate->setDate(invData.endTransDate);

  if (!invData.duplDate.isNull() && invData.duplDate.isValid())
    dupDate = invData.duplDate;

  additEdit->setText(invData.additText);

  paysCombo->setCurrentText(invData.paymentType);
  liabDate->setDate(invData.liabDate);

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__
           << "EXIT";
}
