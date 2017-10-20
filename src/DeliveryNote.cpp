#include "DeliveryNote.h"
#include "ChangeAmount.h"
#include "Const.h"
#include "GoodsList.h"
#include "MainWindow.h"
#include "XmlDataLayer.h"

#include <QCheckBox>
#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>

/** Constructor
 */

DeliveryNote::DeliveryNote(QWidget *parent, IDataLayer *dl, QString in_form)
    : Warehouse(parent, dl, in_form) {

  qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

  invoiceType = s_WZ;
  setObjectName("DeliveryNote");

  textLabelSum1->hide();
  textLabelSum2->hide();
  textLabelSum3->hide();
  sum1->hide();
  sum2->hide();
  sum3->hide();

  currCombo->setDisabled(true);
  constRab->setDisabled(true);

  konvCHF->setDisabled(true);
  konvEUR->setDisabled(true);
  konvGBP->setDisabled(true);
  konvPLN->setDisabled(true);
  konvRUB->setDisabled(true);
  konvUSD->setDisabled(true);

  liabDate->setEnabled(true);
}

/** Destructor
 */

DeliveryNote::~DeliveryNote() {

  qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

  textLabelSum1->show();
  textLabelSum2->show();
  textLabelSum3->show();
  sum1->hide();
  sum2->hide();
  sum3->hide();

  currCombo->setEnabled(true);
  constRab->setEnabled(true);

  konvCHF->setEnabled(true);
  konvEUR->setEnabled(true);
  konvGBP->setEnabled(true);
  konvPLN->setEnabled(true);
  konvRUB->setEnabled(true);
  konvUSD->setEnabled(true);
}

void DeliveryNote::readWarehouseData(QString invFile) {

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

  for (i = 0; i < goodsCount; ++i) {

    ProductData product; //  = new ProductData();
    product.setId(good.attribute(goodsColumns[0]));
    product.setName(good.attribute(goodsColumns[1]));
    product.setQuantity(good.attribute(goodsColumns[2]));
    product.setQuanType(good.attribute(goodsColumns[3]));
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

void DeliveryNote::makeInvoiceProductsHeadar() {

  qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

  invStrList += "<tr align=\"center\" valign=\"middle\" "
                "class=\"productsHeader\" width=\"100%\" >"; // TUTAJ

  int currentPercent = 0;
  int &sumPercents = currentPercent;

  currentPercent += 3;
  invStrList += "<td align=\"center\" width=\"" + sett().numberToString(3) +
                "%\">" + trUtf8("Lp.") + "</td>";

  int res = 100 - sumPercents;
  invStrList += "<td align=\"center\" width=\"" + sett().numberToString(res) +
                "%\">" + trUtf8("Nazwa towaru/materiału") + "</td>";

  currentPercent += 9;
  invStrList += "<td align=\"center\" width=\"" + sett().numberToString(9) +
                "%\">" + trUtf8("Ilość") + "</td>";

  currentPercent += 3;
  invStrList += "<td align=\"center\" width=\"" + sett().numberToString(3) +
                "%\">" + trUtf8("jm.") + "</td>";

  currentPercent += 8;
  invStrList += "<td align=\"center\" width=\"" + sett().numberToString(8) +
                "%\">" + trUtf8("Uwagi") + "</td>";

  invStrList += "</tr>";
}

void DeliveryNote::makeInvoiceProducts() {

  qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

  invStrList += "<tr width=\"100%\"><td width=\"100%\">";

  invStrList += "<table border=\"2\" align=\"right\" cellspacing=\"0\" "
                "cellpadding=\"5\" width=\"100%\">";

  makeInvoiceProductsHeadar();

  for (int i = 0; i < tableGoods->rowCount(); ++i) {

    invStrList += "<tr class=\"products\">";
    // no, name, code, pkwiu, amount, unit, discount, unit price, net, vat,
    // gross

    invStrList += "<td>" + sett().numberToString(i + 1) + "</td>"; // LP

    invStrList += "<td align=\"left\">" + tableGoods->item(i, 1)->text() +
                  "</td>"; // Name

    invStrList += "<td>" + tableGoods->item(i, 4)->text() + "</td>"; // AMOUNT

    invStrList += "<td>" + tableGoods->item(i, 5)->text() + "</td>"; // UNIT

    invStrList += "<td></td>"; // NOTES

    invStrList += "</tr>";
  }

  invStrList += "</table>";
  invStrList += "</td>";
  invStrList += "</tr>";
}

void DeliveryNote::makeInvoiceSumm() {
  qDebug() << __FILE__ << __LINE__ << __FUNCTION__;
  invStrList += "<br/><br/>";
}

void DeliveryNote::makeInvoiceSummAll() {

  qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

  invStrList += "<table width=\"100%\" border=\"0\">";

  invStrList += "<tr class=\"summary\">";
  invStrList += "<td width=\"3%\">&nbsp;</td>";
  invStrList += "<td width=\"48%\">";

  // <span/>???

  invStrList += "<span class=\"toPay\">";
  invStrList +=
      trUtf8("forma płatności: ") + paysCombo->currentText() + "<br/>";
  invStrList += "</span>";

  invStrList += "<span class=\"payDate\">";
  invStrList += trUtf8("termin płatności: ") +
                liabDate->date().toString(sett().getDateFormat()) + "<br/>";
  invStrList += "</span>";

  invStrList += "<br/><br/>";
  invStrList +=
      "<span class=\"additionalText\">" + additEdit->text() + "</span>";
  invStrList += "</td>";
  invStrList += "<td width=\"3%\">&nbsp;</td>";

  invStrList += "</tr>";
  invStrList += "</table>";
}

void DeliveryNote::makeInvoiceFooter() {

  qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

  invStrList += "<tr comment=\"podpis\" align=\"center\"><td>";
  invStrList += "<br><br><br><br>";
  invStrList += "<table width=\"80%\" border=\"0\">";
  invStrList += "<tr>";
  invStrList += "<td width=\"3%\">&nbsp;</td>";
  invStrList += "<td width=\"26%\" align=\"center\"> ";
  invStrList += "<hr width=\"100%\" noshade=\"noshade\" color=\"black\" />";
  invStrList += "</td>";
  invStrList += "<td width=\"6%\">&nbsp;</td>";
  invStrList += "<td width=\"3%\">&nbsp;</td>";
  invStrList += "<td width=\"26%\" align=\"center\"> ";
  invStrList += "<hr width=\"100%\" noshade=\"noshade\" color=\"black\" />";
  invStrList += "</td>";
  invStrList += "<td width=\"6%\">&nbsp;</td>";
  invStrList += "<td width=\"3%\">&nbsp;</td>";
  invStrList += "<td width=\"26%\" align=\"center\"> ";
  invStrList += "<hr width=\"100%\" noshade=\"noshade\" color=\"black\" />";
  invStrList += "</td>";
  invStrList += "</tr>";
  invStrList += "<tr class=\"signature\">";
  invStrList += "<td width=\"3%\">&nbsp;</td>";
  invStrList += "<td width=\"26%\" align=\"center\"> ";
  invStrList += trUtf8("Towar wydał");
  invStrList += "<td width=\"6%\">&nbsp;</td>";
  invStrList += "<td width=\"3%\">&nbsp;</td>";
  invStrList += "<td width=\"26%\" align=\"center\">";
  invStrList += trUtf8("Towar odebrał");
  invStrList += "</td>";
  invStrList += "<td width=\"6%\">&nbsp;</td>";
  invStrList += "<td width=\"3%\">&nbsp;</td>";
  invStrList += "<td width=\"26%\" align=\"center\">";
  invStrList += trUtf8("Zatwierdził");
  invStrList += "</td>";
  invStrList += "</tr>";
  invStrList += "</table>";
  invStrList += "</td></tr>";
  invStrList += "</table>";
}

bool DeliveryNote::saveInvoice() {

  qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << fName;

  bool result = false;
  ifcreateInv = false;
  if (!validateForm())
    return false;

  WarehouseData wareData;
  setData(wareData);

  if (this->windowTitle() != s_WIN_WZ_EDIT) {

    QMessageBox msgBox;
    msgBox.setText(trUtf8(
        "Czy chcesz od razu do tworzonego dokumentu WZ wygenerować fakturę?"));
    msgBox.setInformativeText(trUtf8("Jeśli chcesz dodać dodatkowo fakturę do "
                                     "listy faktur, wybierz - OK. Jeśli "
                                     "chcesz zapisać tylko dokument WZ, "
                                     "wybierz - Anuluj. Pamiętaj, że fakturę do"
                                     "każdego dokumentu WZ należy wystawić w "
                                     "nieprzekraczalnym terminie 7 dni"));
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret2 = msgBox.exec();

    InvoiceData invData;
    setData(invData);

    switch (ret2) {
    case QMessageBox::Ok: {

      ifcreateInv = true;

      result = dataLayer->invoiceInsertData(invData, type);
      ret = dataLayer->getRet();
      MainWindow::instance()->shouldHidden = true;
      Invoice::instance()->makeInvoice();
      MainWindow::instance()->shouldHidden = false;

      if (!result) {
        QMessageBox::warning(
            this, trUtf8("Zapis faktury"),
            trUtf8(
                "Zapis faktury zakończył się niepowodzeniem. Sprawdź, czy masz "
                "uprawnienia do zapisu lub odczytu w ścieżce ") +
                sett().getInvoicesDir() +
                trUtf8(" oraz czy ścieżka istnieje."));
      }

      result = dataLayer->warehouseInsertData(wareData, type);
      retWarehouse = dataLayer->getRetWarehouse();
      MainWindow::instance()->shouldHidden = true;
      makeInvoice();
      MainWindow::instance()->shouldHidden = false;

      if (!result) {
        QMessageBox::warning(
            this, trUtf8("Zapis dokumentu WZ"),
            trUtf8("Zapis dokumentu WZ zakończył się niepowodzeniem. Sprawdź, "
                   "czy masz "
                   "uprawnienia do zapisu lub odczytu w ścieżce ") +
                sett().getWarehouseFullDir() +
                trUtf8(" oraz czy ścieżka istnieje."));
      }

      break;
    }
    case QMessageBox::Cancel: {

      result = dataLayer->warehouseInsertData(wareData, type);
      retWarehouse = dataLayer->getRetWarehouse();
      MainWindow::instance()->shouldHidden = true;
      makeInvoice();
      MainWindow::instance()->shouldHidden = false;

      if (!result) {
        QMessageBox::warning(
            this, trUtf8("Zapis dokumentu WZ"),
            trUtf8("Zapis dokumentu WZ zakończył się niepowodzeniem. Sprawdź "
                   "czy masz "
                   "uprawnienia do zapisu lub odczytu w ścieżce ") +
                sett().getWarehouseFullDir() +
                trUtf8(" oraz czy ścieżka istnieje."));
      }

      break;
    }
    }
  } else {

    result = dataLayer->warehouseInsertData(wareData, type);
    retWarehouse = dataLayer->getRetWarehouse();
    MainWindow::instance()->shouldHidden = true;
    makeInvoice();
    MainWindow::instance()->shouldHidden = false;

    if (!result) {
      QMessageBox::warning(
          this, trUtf8("Zapis dokumentu WZ"),
          trUtf8("Zapis dokumentu WZ zakończył się niepowodzeniem. Sprawdź, "
                 "czy masz "
                 "uprawnienia do zapisu lub odczytu w ścieżce ") +
              sett().getWarehouseFullDir() +
              trUtf8(" oraz czy ścieżka istnieje."));
    }
  }

  saveBtn->setEnabled(false);
  rmGoodsBtn->setEnabled(false);
  editGoodsBtn->setEnabled(false);

  saveFailed = false;
  canClose = true;

  return result;
}

void DeliveryNote::setData(WarehouseData &invData) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  invData.id = fName;
  invData.customer = buyerName->text();
  qDebug() << "buyerName->text() in setData(InvoiceData&):"
           << buyerName->text();
  invData.invNr = invNr->text();
  invData.sellingDate = sellingDate->date();
  invData.issueDate = productDate->date();
  invData.ifInvForDelNote = ifcreateInv;

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

void DeliveryNote::setData(InvoiceData &invData) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  invData.id = fName;
  invData.customer = buyerName->text();
  qDebug() << "buyerName->text() in setData(InvoiceData&):"
           << buyerName->text();
  invData.invNr = lastInvoice;
  invData.sellingDate = sellingDate->date();
  invData.issueDate = productDate->date();

  if (constRab->isChecked())
    invData.discount = discountVal->value();
  else
    invData.discount = 0;

  // no, name, code, pkwiu, amount, unit, discount, unit price, net, vat, gross
  for (int i = 0; i < tableGoods->rowCount(); ++i) {
    ProductData product; //  = new ProductData();

    product.setId(tableGoods->item(i, 0)->text());
    product.setName(tableGoods->item(i, 1)->text());
    product.setCode(tableGoods->item(i, 2)->text());
    product.setPkwiu(tableGoods->item(i, 3)->text());
    product.setQuantity(tableGoods->item(i, 4)->text());
    product.setQuanType(tableGoods->item(i, 5)->text());
    product.setDiscount(tableGoods->item(i, 6)->text());
    double help = sett().stringToDouble(tableGoods->item(i, 7)->text());
    product.setPrice(sett().numberToString(help, 'f', 2));
    product.setNett(tableGoods->item(i, 8)->text());
    product.setVat(tableGoods->item(i, 9)->text());
    product.setGross(tableGoods->item(i, 10)->text());
    invData.products[i] = product;
  }

  invData.additText = additEdit->text();
  invData.paymentType = paysCombo->currentText();

  if (invData.paymentType == trUtf8("zaliczka")) {

    if (rComboWasChanged) {

      invData.custPaym.payment1 = custPaymData->payment1;
      invData.custPaym.date1 = custPaymData->date1;
      invData.custPaym.amount1 = custPaymData->amount1;

      invData.custPaym.payment2 = custPaymData->payment2;
      invData.custPaym.date2 = custPaymData->date2;
      invData.custPaym.amount2 = custPaymData->amount2;

    } else {

      QLocale locale;

      ratesCombo->setCurrentIndex(0);

      invData.custPaym.payment1 = sendKindInfo->text();
      invData.custPaym.date1 =
          locale.toDate(ratesCombo->itemText(0), sett().getDateFormat());
      invData.custPaym.amount1 = sett().stringToDouble(rateLabelInfo->text());
      invData.custPaym.date2 =
          locale.toDate(ratesCombo->itemText(1), sett().getDateFormat());

      invData.custPaym.amount2 = sett().stringToDouble(restLabelInfo->text());

      ratesCombo->setCurrentIndex(1);
      invData.custPaym.payment2 = sendKindInfo->text();
    }
  }

  invData.liabDate = liabDate->date();
  invData.currencyType = currCombo->currentText();

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__
           << "EXIT";
}

void DeliveryNote::readData(QString fraFile) {

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

void DeliveryNote::getData(WarehouseData invData) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  buyerName->setText(invData.customer);
  invNr->setText(invData.invNr);
  sellingDate->setDate(invData.sellingDate);
  productDate->setDate(invData.issueDate);

  if (!invData.duplDate.isNull() && invData.duplDate.isValid())
    dupDate = invData.duplDate;

  additEdit->setText(invData.additText);

  paysCombo->setCurrentText(invData.paymentType);
  liabDate->setDate(invData.liabDate);

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__
           << "EXIT";
}

void DeliveryNote::addGoods() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  GoodsList *goodslistWindow = new GoodsList(this);

  if (goodslistWindow->exec() == QDialog::Accepted) {

    MainWindow::insertRow(tableGoods, tableGoods->rowCount());
    QStringList row = goodslistWindow->getRetVal().split("|");
    int rowNum = tableGoods->rowCount() - 1;
    tableGoods->item(rowNum, 0)->setText(
        sett().numberToString(tableGoods->rowCount())); // id
    tableGoods->item(rowNum, 1)->setText(row[0]);       // name
    tableGoods->item(rowNum, 4)->setText(row[3]);       // quantity
    tableGoods->item(rowNum, 5)->setText(row[4]);       // qType

    saveBtn->setEnabled(true);
    canClose = false;
  }

  delete goodslistWindow;
  goodslistWindow = NULL;
}

void DeliveryNote::editGoods() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;
  // we can only modify quantity

  goodsEdited = true;
  int cur = tableGoods->currentRow();

  if (cur >= 0) {

    ChangeAmount *changeQuant = new ChangeAmount(this);

    changeQuant->nameTow->setText(
        tableGoods->item(tableGoods->currentRow(), 1)->text());

    changeQuant->spinAmount->setValue(
        tableGoods->item(tableGoods->currentRow(), 4)->text().toInt());

    if (changeQuant->exec() == QDialog::Accepted) {

      int currentRow = tableGoods->currentRow();
      tableGoods->item(currentRow, 4)
          ->setText(changeQuant->spinAmount->cleanText());
      saveBtn->setEnabled(true);
      canClose = false;
    }

    delete changeQuant;
    changeQuant = NULL;

  } else if (tableGoods->rowCount() == 0) {

    QMessageBox msgBox;
    msgBox.setText(trUtf8("Nie ma na liście żadnych towarów, które można by "
                          "było edytować. Kliknij na przycisk \"Dodaj\" i "
                          "wybierz towar lub usługę z listy."));
    msgBox.setInformativeText(
        trUtf8("Chcesz potwierdzić, by dokonać zmiany? Czy anulować, by wyjść "
               "do głównego okna?"));
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();

    switch (ret) {
    case QMessageBox::Ok:
      addGoods();
      break;

    case QMessageBox::Cancel:
      reject();
      break;
    }

  } else {

    QMessageBox msgBox;
    msgBox.setText(trUtf8("Musisz zaznaczyć towar, który chcesz edytować, "
                          "klikając na określony rząd w tabeli."));
    msgBox.setIcon(QMessageBox::Information);
    int re = msgBox.exec();

    switch (re) {
    case QMessageBox::Ok:
      tableGoods->setCurrentCell(0, 0);
      break;

    case QMessageBox::Cancel:
      reject();
      break;
    }
  }

  qDebug() << __FUNCTION__ << ": EXIT";
}

void DeliveryNote::delGoods() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  tableGoods->removeRow(tableGoods->currentRow());

  for (int i = 0; i < tableGoods->rowCount(); ++i) {
    tableGoods->item(i, 0)->setText(sett().numberToString(i + 1));
  }

  if (tableGoods->rowCount() == 0) {
    paysCombo->setCurrentIndex(0);
  }

  saveBtn->setEnabled(true);
  canClose = false;
}

/** Sets the editability
 */
void DeliveryNote::setIsEditAllowed(bool isAllowed) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  if (!sett().value("editSymbol").toBool())
    invNr->setEnabled(isAllowed);

  backBtn->setEnabled(isAllowed);
  sellingDate->setEnabled(isAllowed);
  productDate->setEnabled(isAllowed);
  textLabelSum1->hide();
  textLabelSum2->hide();
  textLabelSum3->hide();
  sum1->hide();
  sum2->hide();
  sum3->hide();

  currCombo->setDisabled(true);
  konvCHF->setDisabled(true);
  konvEUR->setDisabled(true);
  konvGBP->setDisabled(true);
  konvPLN->setDisabled(true);
  konvRUB->setDisabled(true);
  konvUSD->setDisabled(true);

  liabDate->setEnabled(true);

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__
           << "EXIT";
}
