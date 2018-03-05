
#include "correction.h"
#include "const.h"
#include "invoicedata.h"
#include "mainwindow.h"
#include "settings.h"

#include <QComboBox>
#include <QLabel>

// constructor
Correction::Correction(QWidget *parent, IDataLayer *dl, QString in_form,
                       bool edMode)
    : Invoice(parent, dl, in_form), editMode(edMode) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  firstRunned = true;
  origGrossBureau = 0;

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__
           << "EXIT";
}

Correction::~Correction() {

  qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

  delete invData;
  invData = NULL;
}

bool Correction::getMode() const {
  qDebug() << __FILE__ << __LINE__ << __FUNCTION__;
  return editMode;
}

bool Correction::getFirstRun() const {
  qDebug() << __FILE__ << __LINE__ << __FUNCTION__;
  return firstRunned;
}

const QString Correction::getRet() {
  qDebug() << __FILE__ << __LINE__ << __FUNCTION__;
  return ret;
}

/* Init
 */

void Correction::correctionInit(bool mode) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  labelReason1 = new QLabel();
  labelReason1->setText(trUtf8("Przyczyna korekty:"));
  labelReason1->setAlignment(Qt::AlignRight);
  addDataLabels->addWidget(labelReason1);

  reasonCombo = new QComboBox();
  reasonCombo->addItems(sett().value("corrections").toString().split("|"));
  addData->addWidget(reasonCombo);

  textLabelSum1->setText(trUtf8("Wartość korekty:"));
  textLabelSum2->setText(trUtf8("Wartość faktury:"));
  textLabelSum3->setText(trUtf8("Do zapłaty:"));

  invoiceType = trUtf8("Korekta");

  invData = NULL;      // set to null
  origGrossTotal = -1; // -1

  editMode = mode;

  constRab->setEnabled(false);
  discountVal->setEnabled(false);

  qDebug() << "Do zapłaty w korekcie: " << sett().stringToDouble(sum3->text());

  // connects
  connect(reasonCombo,
          static_cast<void (QComboBox::*)(const QString &)>(
              &QComboBox::currentIndexChanged),
          [this](const QString &) {
            saveBtn->setEnabled(true);
            canClose = false;
          });

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__
           << "EXIT";
}

//*********************************************** SLOTS START
//****************************************/

/** Slot
 *  Used populate invoice symbol
 */

void Correction::backBtnClick() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  QString tmp = sett().value("korNr").toString();
  QString prefix, suffix;

  prefix = sett().value("prefix").toString();
  QStringList one1 = tmp.split("/");
  one1[0] = one1[0].remove(prefix);

  int nr = MainWindow::instance()->getMaxSymbol() + 1;
  lastInvoice =
      prefix + numbersCount(nr, sett().value("chars_in_symbol").toInt());

  if (sett().value("day").toBool())
    lastInvoice += "/" + QDate::currentDate().toString("dd");

  if (sett().value("month").toBool())
    lastInvoice += "/" + QDate::currentDate().toString("MM");

  if (sett().value("year").toBool()) {
    if (!sett().value("shortYear").toBool())
      lastInvoice += "/" + QDate::currentDate().toString("yy");
    else
      lastInvoice += "/" + QDate::currentDate().toString("yyyy");
  }

  suffix = sett().value("sufix").toString();
  lastInvoice += suffix;
  invNr->setText(lastInvoice);
  saveBtn->setEnabled(true);

  fName = "";
  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__
           << "EXIT";
}

/** Slot
 *  Generates Correction XML
 */

bool Correction::saveInvoice() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__
           << fName;

  QDomDocument doc(sett().getCorrDocName());
  QDomElement root;

  if (!editMode && (fName == ""))
    fName = "NULL";

  qDebug() << fName;

  QFile file;

  if (fName == "NULL") {

    fName = QDate::currentDate().toString(sett().getFnameDateFormat());

    int pNumber = 0;
    QString fname = "k" + fName + "_" + sett().numberToString(pNumber) + ".xml";
    file.setFileName(sett().getInvoicesDir() + fname);

    ret = fname + "|";
    pNumber += 1;

    while (file.exists()) {

      fname = "k" + fName + "_" + sett().numberToString(pNumber) + ".xml";
      file.setFileName(sett().getInvoicesDir() + fname);
      ret = fname + "|";
      pNumber += 1;
    }

    qDebug() << "Created new file " + file.fileName();
    fName = fname;

  } else {

    file.setFileName(sett().getInvoicesDir() + fName);
    qDebug() << "Used existing file " + file.fileName();
    ret = fName + "|";
  }

  root = doc.createElement("correction");
  root.setAttribute("no", invNr->text());
  root.setAttribute("originalInvoiceNo", invData->invNr);

  ret += invNr->text() + "|";
  root.setAttribute("issueDate",
                    QDate::currentDate().toString(sett().getDateFormat()));
  ret += QDate::currentDate().toString(sett().getDateFormat()) + "|";

  root.setAttribute("sellingDate",
                    sellingDate->date().toString(sett().getDateFormat()));

  root.setAttribute("endTransDate",
                    endTransactionDate->date().toString(sett().getDateFormat()));

  root.setAttribute("invValue", sum2->text());

  QString invType = getInvoiceTypeAndSaveNr();
  root.setAttribute("type", invType);
  ret += invType + "|";
  doc.appendChild(root);

  QDomElement seller = doc.createElement("seller");
  QSettings userSettings("elinux", "user");

  seller.setAttribute("name", userSettings.value("name").toString());
  seller.setAttribute("zip", userSettings.value("zip").toString());
  seller.setAttribute("city", userSettings.value("city").toString());
  seller.setAttribute("street", userSettings.value("address").toString());
  seller.setAttribute("tic", userSettings.value("tic").toString());
  seller.setAttribute(
      "account", userSettings.value("account").toString().replace(" ", "-"));
  seller.setAttribute("phone", userSettings.value("phone").toString());
  seller.setAttribute("email", userSettings.value("email").toString());
  seller.setAttribute("website", userSettings.value("website").toString());
  seller.setAttribute("bank", userSettings.value("bank").toString());
  seller.setAttribute("krs", userSettings.value("krs").toString());
  seller.setAttribute("fax", userSettings.value("fax").toString());
  seller.setAttribute("swift", userSettings.value("swift").toString());

  root.appendChild(seller);

  QDomElement buyer = doc.createElement("buyer");
  QStringList kht = invData->customer.split(",");

  buyer.setAttribute("name", kht[0]);
  ret += kht[0] + "|";
  buyer.setAttribute("city", kht[1]);
  buyer.setAttribute("street", kht[2]);
  buyer.setAttribute(
      "tic", kht[3].replace(" ", "").replace(QObject::trUtf8("NIP:"), ""));
  ret += kht[3].replace(" ", "").replace(trUtf8("NIP:"), "");
  buyer.setAttribute("account", kht[4].replace(" ", "").replace(
                                    QObject::trUtf8("Konto:"), ""));
  buyer.setAttribute(
      "phone", kht[5].replace(" ", "").replace(QObject::trUtf8("Tel:"), ""));
  buyer.setAttribute(
      "email", kht[6].replace(" ", "").replace(QObject::trUtf8("Email:"), ""));

  QString imprWeb =
      kht[7].replace(" ", "").replace(QObject::trUtf8("Strona:"), "");
  imprWeb = imprWeb.remove(imprWeb.indexOf("<"), imprWeb.indexOf(">") + 1);
  imprWeb = imprWeb.remove(imprWeb.indexOf("<"), imprWeb.indexOf(">"));

  buyer.setAttribute("website", imprWeb);
  root.appendChild(buyer);

  QDomElement product;
  QDomElement productsCorrected;
  productsCorrected = doc.createElement("productsCorrected");
  productsCorrected.setAttribute("discount",
                                 sett().numberToString(discountVal->value()));

  for (int i = 0; i < tableGoods->rowCount(); ++i) {

    product =
        doc.createElement("product"); //  + tableGoods->item(i, 0)->text());
    productsCorrected.setAttribute("productsCount",
                                   sett().numberToString(i + 1));
    product.setAttribute("id", tableGoods->item(i, 0)->text());
    product.setAttribute("name", tableGoods->item(i, 1)->text());
    product.setAttribute("code", tableGoods->item(i, 2)->text());
    product.setAttribute(
        "PKWiU",
        tableGoods->item(i, 3)->text()); // Polish Classification of STH
    product.setAttribute("quantity", tableGoods->item(i, 4)->text());
    product.setAttribute("quantityType", tableGoods->item(i, 5)->text());

    if (!constRab->isChecked()) {

      product.setAttribute("discount", tableGoods->item(i, 6)->text());

    } else {

      product.setAttribute(
          "discount", sett().numberToString(discountVal->value())); // rabat
    }

    product.setAttribute("price", tableGoods->item(i, 7)->text());
    product.setAttribute(
        "nett", tableGoods->item(i, 8)->text()); // netto without discount
    product.setAttribute("discountedNett", tableGoods->item(i, 7)->text());
    product.setAttribute("vatBucket", tableGoods->item(i, 9)->text());
    double vatPrice = sett().stringToDouble(tableGoods->item(i, 10)->text()) -
                      sett().stringToDouble(tableGoods->item(i, 8)->text());
    product.setAttribute("vatAmout", sett().numberToString(vatPrice, 'f', 2));
    product.setAttribute("gross", tableGoods->item(i, 10)->text());
    productsCorrected.appendChild(product);
  }

  root.appendChild(productsCorrected);

  QDomElement productsOriginal;
  productsOriginal = doc.createElement("productsOriginal");
  productsOriginal.setAttribute("discount",
                                sett().numberToString(discountVal->value()));

  for (QMap<int, ProductData>::const_iterator iter = invData->products.begin();
       iter != invData->products.end(); ++iter) {

    product =
        doc.createElement("product"); //  + tableGoods->item(i, 0)->text());
    product.setAttribute("id", QString::number(iter.value().getId()));
    product.setAttribute("name", iter.value().getName());
    product.setAttribute("code", iter.value().getCode());
    product.setAttribute(
        "PKWiU", iter.value().getPkwiu()); // Polish Classification of STH
    product.setAttribute("quantity",
                         sett().numberToString(iter.value().getQuantity()));
    product.setAttribute("quantityType", iter.value().getQuantityType());
    double discountVal = 0;

    if (!constRab->isChecked()) {

      discountVal = iter.value().getDiscount();
      product.setAttribute("discount",
                           sett().numberToString(iter.value().getDiscount()));

    } else {

      discountVal = this->discountVal->value();
      product.setAttribute(
          "discount",
          sett().numberToString(this->discountVal->value())); // rabat
    }

    product.setAttribute("price",
                         sett().numberToString(iter.value().getPrice()));
    product.setAttribute(
        "nett", sett().numberToString(iter.value().getNett())); // netto
    double discNett = (iter.value().getNett() -
                       ((discountVal * 0.01) * iter.value().getNett()));
    product.setAttribute("discountedNett", sett().numberToString(discNett));
    product.setAttribute("vatBucket",
                         sett().numberToString(iter.value().getVat()));
    double vatPrice = (iter.value().getGross() - iter.value().getNett());
    product.setAttribute("vatAmout", sett().numberToString(vatPrice, 'f', 2));

    product.setAttribute("gross",
                         sett().numberToString(iter.value().getGross()));
    productsOriginal.setAttribute("productsCount",
                                  sett().numberToString(iter.key() + 1));

    productsOriginal.appendChild(product);
    qDebug() << iter.value().getName() << productsOriginal.nodeValue();
  }

  root.appendChild(productsOriginal);

  QDomElement addinfo;
  addinfo = doc.createElement("addinfo");
  addinfo.setAttribute("text", additEdit->toPlainText());

  if (paysCombo->currentText() == trUtf8("zaliczka")) {
    if (!editMode) {
      if (rComboWasChanged) {

        addinfo.setAttribute("payment1", custPaymData->payment1);
        addinfo.setAttribute(
            "amount1", sett().numberToString(custPaymData->amount1, 'f', 2));
        addinfo.setAttribute(
            "liabDate1", custPaymData->date1.toString(sett().getDateFormat()));

        addinfo.setAttribute("payment2", custPaymData->payment2);
        addinfo.setAttribute(
            "amount2", sett().numberToString(custPaymData->amount2, 'f', 2));
        addinfo.setAttribute(
            "liabDate2", custPaymData->date2.toString(sett().getDateFormat()));

      } else {

        ratesCombo->setCurrentIndex(0);

        addinfo.setAttribute("payment1", sendKindInfo->text());
        addinfo.setAttribute("amount1", rateLabelInfo->text());
        addinfo.setAttribute("liabDate1", ratesCombo->itemText(0));

        addinfo.setAttribute("amount2", restLabelInfo->text());
        addinfo.setAttribute("liabDate2", ratesCombo->itemText(1));

        ratesCombo->setCurrentIndex(1);
        addinfo.setAttribute("payment2", sendKindInfo->text());
      }
    } else {

      ratesCombo->setCurrentIndex(0);

      addinfo.setAttribute("payment1", sendKindInfo->text());
      addinfo.setAttribute("amount1", rateLabelInfo->text());
      addinfo.setAttribute("liabDate1", ratesCombo->itemText(0));

      addinfo.setAttribute("amount2", restLabelInfo->text());
      addinfo.setAttribute("liabDate2", ratesCombo->itemText(1));

      ratesCombo->setCurrentIndex(1);
      addinfo.setAttribute("payment2", sendKindInfo->text());
    }
  }

  addinfo.setAttribute("paymentType", paysCombo->currentText());
  addinfo.setAttribute("liabDate",
                       liabDate->date().toString(sett().getDateFormat()));
  addinfo.setAttribute("currency", currCombo->currentText());
  addinfo.setAttribute("reason", reasonCombo->currentText());

  root.appendChild(addinfo);

  QString xml = doc.toString();
  file.close();

  if (!file.open(QIODevice::WriteOnly)) {

    QFileInfo check_file(file.fileName());

    if (check_file.exists() && check_file.isFile()) {

      QFile(file.fileName())
          .setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner);
    }
  }

  QTextStream ts(&file);

  qDebug() << xml;

  ts << xml;
  file.close();

  saveBtn->setEnabled(false);
  rmGoodsBtn->setEnabled(false);
  editGoodsBtn->setEnabled(false);

  saveFailed = false;
  canClose = true;

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__
           << ": canClose " << canClose;
  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__
           << "EXIT";

  return canClose;
}

/** Slot
 *  Generates invoice and shows preview
 */

void Correction::makeInvoice(bool to_print) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  invoiceType = s_CORRECTION;
  invStrList.clear();

  makeInvoiceHeadarHTML();

  makeInvoiceHeadar(false, false, true);
  makeInvoiceBody();
  makeInvoceProductsTitle(0);
  makeBeforeCorrProducts();
  makeBeforeCorrSumm();
  makeInvoceProductsTitle(1);
  makeInvoiceProducts();
  makeInvoiceSumm();
  makeInvoiceSummAll();
  makeInvoiceFooter();

  int numberOfCopies = sett().value("numberOfCopies", 2).toInt();

  for (int i = 1; i <= numberOfCopies; i++) {

    makeInvoiceHeadar(false, true, false);
    makeInvoiceBody();
    makeInvoceProductsTitle(0);
    makeBeforeCorrProducts();
    makeBeforeCorrSumm();
    makeInvoceProductsTitle(1);
    makeInvoiceProducts();
    makeInvoiceSumm();
    makeInvoiceSummAll();
    makeInvoiceFooter();
  }

  makeInvoiceFooterHtml();

  if (to_print) print();

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__
           << "EXIT";
}

/** Slot
 *  Validate close and save if requested
 */

void Correction::canQuit() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__
           << ": canClose " << canClose;

  if (canClose) {

    if (ret.isNull())
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

      if (saveFailed)
        return;

      saveColumnsWidth();
      accept();
    }
  }

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__
           << "EXIT";
}
//*********************************************** SLOTS END
//****************************************/

/** Reads correction xml
 */

void Correction::readCorrData(QString invFile) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  backBtn->setEnabled(false);
  invNr->setEnabled(false);

  setWindowTitle(trUtf8("Edytuje korektę"));

  qDebug("invFile file");
  qDebug() << invFile;

  QDomDocument doc(sett().getInvoicesDir());
  QDomElement root;
  QDomElement buyer;
  QDomElement product;

  fName = invFile;
  prepayFile = invFile;

  QFile file(sett().getInvoicesDir() + invFile);
  QTextStream stream(&file);

  if (!file.open(QIODevice::ReadOnly) || !doc.setContent(stream.readAll())) {

    QFileInfo check_file(file.fileName());

    if (check_file.exists() && check_file.isFile()) {

      QFile(file.fileName())
          .setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner);

    } else {

      QMessageBox::warning(
          this, trUtf8("Brak dostępu"),
          trUtf8("Plik przechowujący dane o fakturze korygującej w ścieżce ") +
              file.fileName() + trUtf8(" nie istnieje.") +
              trUtf8(" Jesteś pewien, że plik o tej nazwie nie jest "
                     "przechowywany w innym folderze?"));
      return;
    }
  }

  root = doc.documentElement();
  invNr->setText(root.attribute("no"));

  sellingDate->setDate(
      QDate::fromString(root.attribute("sellingDate"), sett().getDateFormat()));
  productDate->setDate(
      QDate::fromString(root.attribute("issueDate"), sett().getDateFormat()));
  endTransactionDate->setDate(
      QDate::fromString(root.attribute("endTransDate"), sett().getDateFormat()));
  origGrossBureau = sett().stringToDouble(root.attribute("invValue"));

  invData = new InvoiceData();
  invData->invNr = root.attribute("originalInvoiceNo");
  invData->type = root.attribute("type");

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

  static const char *goodsColumns[] = {
      "id",       "name",  "code", "PKWiU",     "quantity", "quantityType",
      "discount", "price", "nett", "vatBucket", "gross"};

  //*********************** Load Products After ***************************

  tmp = tmp.toElement().nextSibling(); // product after
  product = tmp.toElement();
  goodsCount = product.attribute("productsCount").toInt();
  discountVal->setValue(product.attribute("discount").toInt());

  goodsCount = product.attribute("productsCount").toInt();
  i = 0;
  good = product.firstChild().toElement();

  tableGoods->setRowCount(goodsCount);

  for (i = 0; i < goodsCount; ++i) {
    for (int j = 0; j < int(sizeof(goodsColumns) / sizeof(*goodsColumns));
         j++) {

      tableGoods->setItem(
          i, j, new QTableWidgetItem(good.attribute(goodsColumns[j])));
    }

    good = good.nextSibling().toElement();
  }

  //*********************** Load Products Before ***************************

  tmp = tmp.toElement().nextSibling(); // product before
  product = tmp.toElement();
  goodsCount = product.attribute("productsCount").toInt();
  good = product.firstChild().toElement();

  invData->customer = buyerName->text();
  invData->sellingDate = sellingDate->date();
  invData->productDate = productDate->date();
  invData->endTransDate = endTransactionDate->date();

  for (i = 0; i < goodsCount; ++i) {

    ProductData product; //  = new ProductData();
    product.setId(good.attribute(goodsColumns[0]));
    product.setName(good.attribute(goodsColumns[1]));
    product.setCode(good.attribute(goodsColumns[2]));
    product.setPkwiu(good.attribute(goodsColumns[3]));
    product.setQuantity(good.attribute(goodsColumns[4]));
    product.setQuanType(good.attribute(goodsColumns[5]));
    product.setDiscount(good.attribute(goodsColumns[6]));
    product.setPrice(good.attribute(goodsColumns[7]));
    product.setNett(good.attribute(goodsColumns[8]));
    product.setVat(good.attribute(goodsColumns[9]));
    product.setGross(good.attribute(goodsColumns[10]));
    qDebug() << "Gross of this product: " << good.attribute(goodsColumns[10]);
    invData->products[i] = product;
    good = good.nextSibling().toElement();
  }

  tmp = tmp.toElement().nextSibling();
  QDomElement additional = tmp.toElement();
  additEdit->setText(additional.attribute("text"));
  invData->additText = additEdit->toPlainText();
  invData->paymentType = additional.attribute("paymentType");

  if (invData->paymentType == trUtf8("zaliczka")) {

    disconnect(paysCombo, SIGNAL(currentIndexChanged(QString)), this,
               SLOT(payTextChanged(QString)));

    paysCombo->setCurrentText(invData->paymentType);

    labelRate = new QLabel();
    labelRate->setText(trUtf8("Termin raty:"));
    labelRate->setAlignment(Qt::AlignRight);
    addDataLabels->addWidget(labelRate);

    if (ratesCombo == 0)
      ratesCombo = new QComboBox();
    disconnect(ratesCombo, SIGNAL(currentIndexChanged(QString)), this,
               SLOT(rateDateChanged(QString)));

    ratesCombo->addItem(additional.attribute("liabDate1"));
    ratesCombo->addItem(additional.attribute("liabDate2"));
    addData->addWidget(ratesCombo);

    rateLabel = new QLabel();
    rateLabel->setText(trUtf8("Rata:"));
    rateLabel->setAlignment(Qt::AlignRight);
    descPayments->addWidget(rateLabel);

    sendKind = new QLabel();
    sendKind->setText(trUtf8("Rodzaj zapłaty:"));
    sendKind->setAlignment(Qt::AlignRight);
    descPayments->addWidget(sendKind);

    restLabel = new QLabel();
    restLabel->setText(trUtf8("Pozostało do spłaty:"));
    restLabel->setAlignment(Qt::AlignRight);
    descPayments->addWidget(restLabel);

    rateLabelInfo = new QLabel();
    rateLabelInfo->setText(additional.attribute("amount1"));
    dataPayments->addWidget(rateLabelInfo);

    sendKindInfo = new QLabel();
    sendKindInfo->setText(additional.attribute("payment1"));
    dataPayments->addWidget(sendKindInfo);

    restLabelInfo = new QLabel();
    restLabelInfo->setText(additional.attribute("amount2"));
    dataPayments->addWidget(restLabelInfo);

    custPaymData = new CustomPaymData();
    custPaymData->payment1 = additional.attribute("payment1");

    double decimalPointsAmount1 =
        additional.attribute("amount1").right(2).toInt() * 0.01;
    qDebug() << "decimalPointsAmount1 << " << decimalPointsAmount1;
    double decimalPointsAmount2 =
        additional.attribute("amount2").right(2).toInt() * 0.01;
    qDebug() << "decimalPointsAmount2 << " << decimalPointsAmount2;

    custPaymData->amount1 =
        sett().stringToDouble(additional.attribute("amount1"));
    custPaymData->amount1 += decimalPointsAmount1;
    custPaymData->date1 = QDate::fromString(additional.attribute("liabDate1"),
                                            sett().getDateFormat());
    custPaymData->payment2 = additional.attribute("payment2");
    custPaymData->amount2 =
        sett().stringToDouble(additional.attribute("amount2"));
    custPaymData->amount2 += decimalPointsAmount2;
    custPaymData->date2 = QDate::fromString(additional.attribute("liabDate2"),
                                            sett().getDateFormat());

    if (editMode) {

      am1 = custPaymData->amount1;
      am2 = custPaymData->amount2;
    }

  } else {

    paysCombo->setCurrentText(invData->paymentType);
  }

  liabDate->setDate(QDate::fromString(additional.attribute("liabDate"),
                                      sett().getDateFormat()));
  invData->liabDate = liabDate->date();
  int curCurrency = sett()
                        .value("currencies")
                        .toString()
                        .split("|")
                        .indexOf(additional.attribute("currency"));
  currCombo->setCurrentIndex(curCurrency);
  invData->currencyType = currCombo->currentText();

  int corrReason = sett()
                       .value("corrections")
                       .toString()
                       .split("|")
                       .indexOf(additional.attribute("reason"));
  reasonCombo->setCurrentIndex(corrReason);

  if (invData->paymentType == trUtf8("zaliczka")) {

    connect(paysCombo, SIGNAL(currentIndexChanged(QString)), this,
            SLOT(payTextChanged(QString)));
    connect(ratesCombo, SIGNAL(currentIndexChanged(QString)), this,
            SLOT(rateDateChanged(QString)));
  }

  canClose = true;
  saveBtn->setEnabled(false);

  setIsEditAllowed(sett().value("edit").toBool());
  calculateDiscount();
  calculateSum();
  file.close();

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__
           << "EXIT";
}

/** Sets the controls into disabled/enabled state
 */

void Correction::setIsEditAllowed(bool isAllowed) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  if (editMode == false) {

    isAllowed = true;
    canClose = false;
  }

  if (!sett().value("editSymbol").toBool()) {

    invNr->setEnabled(isAllowed);
  }

  backBtn->setEnabled(isAllowed);
  sellingDate->setEnabled(isAllowed);
  productDate->setEnabled(isAllowed);
  endTransactionDate->setEnabled(isAllowed);
  tableGoods->setEnabled(isAllowed);
  discountVal->setEnabled(false);   // don't allow for now
  discountLabel->setEnabled(false); // don't allow for now
  paysCombo->setEnabled(isAllowed);
  liabDate->setEnabled(isAllowed);
  additEdit->setEnabled(isAllowed);
  addGoodsBtn->setEnabled(isAllowed);
  rmGoodsBtn->setEnabled(isAllowed);
  editGoodsBtn->setEnabled(isAllowed);
  constRab->setEnabled(false);     // don't allow for now
  buyerListGet->setEnabled(false); // don't allow to change kontrahent
  currCombo->setEnabled(isAllowed);
  saveBtn->setEnabled(isAllowed);

  if (!isAllowed && discountVal->value() == 0) {

    constRab->setChecked(false);
    discountVal->setEnabled(false);

  } else {

    constRab->setChecked(true);
    discountVal->setEnabled(true);
  }

  if (isAllowed && (paysCombo->currentText() != trUtf8("zaliczka")))
    liabDate->setEnabled(true);
  else
    liabDate->setEnabled(false);

  reasonCombo->setEnabled(isAllowed);

  if (invData == NULL)
    invData = createOriginalInv();

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__
           << "EXIT";
}

/**  Creates object with the orignal invoice
 */

InvoiceData *Correction::createOriginalInv() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  invData = new InvoiceData();
  invData->customer = buyerName->text();
  qDebug() << "Ile jest wierszy: ";

  for (int i = 0; i < tableGoods->rowCount(); ++i) {

    ProductData product; //  = new ProductData();
    product.setId(tableGoods->item(i, 0)->text());
    product.setName(tableGoods->item(i, 1)->text());
    product.setCode(tableGoods->item(i, 2)->text());
    product.setPkwiu(tableGoods->item(i, 3)->text());
    product.setQuantity(tableGoods->item(i, 4)->text());
    product.setQuanType(tableGoods->item(i, 5)->text());
    product.setDiscount(tableGoods->item(i, 6)->text());
    product.setPrice(tableGoods->item(i, 7)->text());
    product.setNett(tableGoods->item(i, 8)->text());
    product.setVat(tableGoods->item(i, 9)->text());
    product.setGross(tableGoods->item(i, 10)->text());
    qDebug() << "Gross w funkcji createOriginalInv " << i << ": "
             << tableGoods->item(i, 10)->text();
    invData->products[i] = product;
  }

  invData->liabDate = liabDate->date();
  invData->sellingDate = sellingDate->date();
  invData->productDate = productDate->date();
  invData->endTransDate = endTransactionDate->date();
  invData->invNr = invNr->text();
  invData->paymentType = paysCombo->currentText();
  invData->currencyType = currCombo->currentText();
  invData->additText = additEdit->toPlainText();

  backBtnClick(); // populate correct correction symbol
  return invData;
  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__
           << "EXIT";
}

/** Not used in this class
 */

void Correction::calculateDiscount() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;
}

void Correction::schemaCalcSum() {
  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  double net = 0;
  double price = 0;
  double quantity = 0;
  double gross = 0;
  double discountValue = 0;

  qDebug() << "paysCombo->currentText(): " << paysCombo->currentText();
  qDebug() << "origGrossTotal na początku funkcji: " << origGrossTotal;

  // set to 0
  nettTotal = 0;
  discountTotal = 0;
  grossTotal = 0;

  if (firstRunned) {

    if (paysCombo->currentText() == trUtf8("zaliczka")) {

      if (!editMode) {

        rateLabelInfo->setText(sett().numberToString(0));
        restLabelInfo->setText(sett().numberToString(0));
        am1 = 0;
        am2 = 0;
      }
    }
    if (origGrossTotal != -1)
      origGrossTotal = -1;
  }

  qDebug() << "origGrossTotal na początku funkcji 2: " << origGrossTotal;

  // origGrossTotal = -1;
  origDiscTotal = 0;
  origNettTotal = 0;
  diffTotal = 0;

  // sum of after correction invoice
  for (int i = 0; i < tableGoods->rowCount(); ++i) {

    price = sett().stringToDouble(tableGoods->item(i, 7)->text());
    quantity = tableGoods->item(i, 4)->text().toInt();
    net = sett().stringToDouble(tableGoods->item(i, 8)->text());

    double decimalPointsNetto =
        tableGoods->item(i, 8)->text().right(2).toInt() * 0.01;

    qDebug() << "decimalPointsNetto << " << decimalPointsNetto;

    double decimalPointsGross =
        tableGoods->item(i, 10)->text().right(2).toInt() * 0.01;

    qDebug() << "decimalPointsGross << " << decimalPointsGross;

    net += decimalPointsNetto;
    gross = sett().stringToDouble(tableGoods->item(i, 10)->text());
    gross += decimalPointsGross;
    discountValue += (price * quantity) - net;

    nettTotal += net;
    grossTotal += gross;
  }

  discountTotal = (discountValue * nettTotal) / 100;

  // initially origGrossTotal is -1
  // if it's -1 will set to to 0 and go through whole calculation

  if (origNettTotal == 0) origGrossTotal = -1;
  if (origGrossTotal < 0) {
    origGrossTotal = 0;
    qDebug() << "origGrossTotal less than zero: " << origGrossTotal;

    goodsEdited = true;

    if (invData == NULL) {
      invData = createOriginalInv();
    } else {
      if (invData->products.count() == 0) {
        origGrossTotal = -1;
      }
    }



    qDebug() << "products before loop: " << invData->products.count();

    for (QMap<int, ProductData>::const_iterator iter =
             invData->products.begin();
         iter != invData->products.end(); ++iter) {

      // qDebug() << iter.value()->toString();

      if (origGrossBureau == 0) {
        origGrossTotal += iter.value().getGross();
      }

      origDiscTotal += iter.value().getDiscount();
      origNettTotal += iter.value().getNett();
    }

    if (origGrossBureau != 0) {
      origGrossTotal = origGrossBureau;
    }

    qDebug() << "origGrossTotal in loop of QMap: " << origGrossTotal;
}

  diffTotal = grossTotal - origGrossTotal;

  qDebug() << "diffTotal = grossTotal - origGrossTotal" << diffTotal << " = "
           << grossTotal << " - " << origGrossTotal;

  sum1->setText(sett().numberToString(grossTotal, 'f', 2));
  qDebug() << "grossTotal: " << grossTotal;

  sum2->setText(sett().numberToString(origGrossTotal, 'f', 2));
  qDebug() << "origGrossTotal: " << origGrossTotal;

  sum3->setText(sett().numberToString(diffTotal, 'f', 2));
  qDebug() << "diffTotal: " << diffTotal;

  if (diffTotal < 0)
    textLabelSum3->setText(trUtf8("Do zwrotu:"));
  else if (diffTotal > 0)
    textLabelSum3->setText(trUtf8("Do zapłaty:"));
  else
    textLabelSum3->setText("");

  if (firstRunned)
    firstRunned = false;
}

/** Calculates the sums original invoice and the new one
 */

void Correction::calculateSum() {

  if (editMode) {
    if ((invData != NULL) && (invData->products.count() > 0)) {

      schemaCalcSum();
    }

  } else {

    schemaCalcSum();
  }
}

void Correction::calculateOneDiscount(int i) {

  qDebug() << __FUNCTION__ << __LINE__ << __FILE__;

  double quantity = 0;
  double vat = 0;
  double gross = 0;
  double net = 0;
  double price = 0;
  double discountValue = 0;
  double discount = 0;

  price = sett().stringToDouble(tableGoods->item(i, 7)->text());

  if (constRab->isChecked())
    discount = discountVal->value() * 0.01;
  else
    discount = (tableGoods->item(i, 6)->text()).toInt() * 0.01;

  quantity = tableGoods->item(i, 4)->text().toInt();
  net = (price * quantity);
  discountValue = net * discount;
  net -= discountValue;
  vat = tableGoods->item(i, 9)->text().toInt();
  gross = net * ((vat * 0.01) + 1);

  // qDebug() << price << quantity << net << discount << discountValue << vat <<
  // gross;

  tableGoods->item(i, 6)->setText(
      sett().numberToString(discount * 100, 'f', 0));             // discount
  tableGoods->item(i, 8)->setText(sett().numberToString(net));    // net
  tableGoods->item(i, 10)->setText(sett().numberToString(gross)); // gross

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__
           << "EXIT";
}

QString Correction::getInvoiceTypeAndSaveNr() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  sett().setValue("korNr", invNr->text());

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__
           << "EXIT";

  return "korekta";
}

//*************** HTML methods START  *** *****************************

void Correction::makeInvoceProductsTitle(short a) {

  invStrList += "<tr align=\"center\"><td>";

  if (a == 1) {
    invStrList += trUtf8("Pozycje na fakturze po korekcie:");
  }

  if (a == 0) {
    invStrList += trUtf8("Pozycje na fakturze przed korektą:");
  }

  invStrList += "<br/>";
}

void Correction::makeBeforeCorrProducts() {

  invStrList +=
      "<table border=\"1\" cellspacing=\"0\" cellpadding=\"5\" width=\"100%\">";

  makeInvoiceProductsHeadar();

  for (QMap<int, ProductData>::const_iterator iter = invData->products.begin();
       iter != invData->products.end(); ++iter) {

    double discountVal =
        iter.value().getNett() * (iter.value().getDiscount() * 0.01);
    double nettMinusDisc = iter.value().getNett() - discountVal;
    double vatPrice =
        iter.value().getGross() - iter.value().getNett(); // gross - net

    qDebug() << "discountVal correction: " << discountVal;
    qDebug() << "nettMinusDisc: " << nettMinusDisc;
    qDebug() << "vatPrice: " << vatPrice;


    sett().beginGroup("invoices_positions");


          invStrList += "<tr class=\"products\">";
          // no, name, code, pkwiu, amount, unit, discount, unit price, net, vat,
          // gross

          if (sett().value("Lp").toBool())
            invStrList += "<td>" + sett().numberToString(iter.key() + 1) + "</td>";

          if (sett().value("Name").toBool())
            invStrList +=
                "<td align=\"left\">" + iter.value().getName() + "</td>";

          if (sett().value("Code").toBool())
            invStrList += "<td>" + iter.value().getCode() + "</td>";

          if (sett().value("pkwiu").toBool())
            invStrList += "<td>" + iter.value().getPkwiu() + "</td>";

          if (sett().value("amount").toBool())
            invStrList += "<td>" + sett().numberToString(iter.value().getQuantity(),'f',0) + "</td>";

          if (sett().value("unit").toBool())
            invStrList += "<td>" + iter.value().getQuantityType() + "</td>";

          if (sett().value("unitprice").toBool())
            invStrList += "<td>" + sett().numberToString(iter.value().getPrice()) + "</td>";

          if (sett().value("netvalue").toBool())
            invStrList += "<td>" + sett().numberToString(iter.value().getNett()) + "</td>"; // net

          if (sett().value("discountperc").toBool())
            invStrList += "<td>" + sett().numberToString(iter.value().getDiscount(),'f',0) + "%</td>"; // discount

          if (sett().value("discountval").toBool())
            invStrList += "<td align=\"center\" >" +
                          sett().numberToString(discountVal, 'f', 2) + "</td>";

          if (sett().value("netafter").toBool())
            invStrList +=
                "<td>" + sett().numberToString(nettMinusDisc, 'f', 2) + "</td>";

          if (sett().value("vatval").toBool())
            invStrList += "<td>" + sett().numberToString(iter.value().getVat()) + "%</td>";

          if (sett().value("vatprice").toBool())
            invStrList += "<td>" + sett().numberToString(vatPrice, 'f', 2) + "</td>";

          if (sett().value("grossval").toBool())
            invStrList += "<td>" + sett().numberToString(iter.value().getGross()) + "</td>";


    invStrList += "</tr>";


    sett().endGroup();
  }

  invStrList += "</table>";
}

void Correction::makeBeforeCorrSumm() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;
  invStrList += "<table width=\"100%\" border=\"0\" cellpadding=\"5\">";

  double vatPrice = origGrossTotal - origNettTotal;

  invStrList += "<tr class=\"productsSumHeader\" valign=\"middle\">";
  invStrList += "<br/>";
  invStrList += "<td width=\"67%\" align=\"right\">&nbsp;</td>";
  invStrList += "<td width=\"11%\" align=\"center\">" +
                trUtf8("Wartość Netto") + "</td>"; // net
  invStrList += "<td width=\"11%\" align=\"center\">" + trUtf8("Kwota VAT") +
                "</td>"; // vat
  invStrList += "<td width=\"11%\" align=\"center\">" +
                trUtf8("Wartość Brutto") + "</td>"; // gross
  invStrList += "</tr>";
  invStrList += "<tr class=\"productsSum\" valign=\"middle\">";
  invStrList += "<td align=\"right\">" + trUtf8("Razem:") + "</td>";
  invStrList += "<td align=\"center\">" +
                sett().numberToString(origNettTotal, 'f', 2) + "</td>"; // net
  invStrList += "<td align=\"center\">" +
                sett().numberToString(vatPrice, 'f', 2) + "</td>"; // vat
  invStrList += "<td align=\"center\">" +
                sett().numberToString(origGrossTotal, 'f', 2) +
                "</td>"; // gross
  invStrList += "</tr>";
  invStrList += "</table>";
  invStrList += "<hr class=\"hrdiv1\" />";
}

void Correction::makeInvoiceSumm() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  invStrList += "<table width=\"100%\" border=\"0\" cellpadding=\"5\">";

  double vatPrice = grossTotal - nettTotal;

  invStrList += "<tr class=\"productsSumHeader\" valign=\"middle\">";
  invStrList += "<br/>";
  invStrList += "<td width=\"67%\" align=\"right\">&nbsp;</td>";
  invStrList += "<td width=\"11%\" align=\"center\">" +
                trUtf8("Wartość Netto") + "</td>"; // net
  invStrList += "<td width=\"11%\" align=\"center\">" + trUtf8("Kwota VAT") +
                "</td>"; // vat
  invStrList += "<td width=\"11%\" align=\"center\">" +
                trUtf8("Wartość Brutto") + "</td>"; // gross
  invStrList += "</tr><tr class=\"productsSum\" valign=\"middle\">";
  invStrList += "<td align=\"right\">" + trUtf8("Razem:") + "</td>";
  invStrList += "<td align=\"center\">" +
                sett().numberToString(nettTotal, 'f', 2) + "</td>"; // net
  invStrList += "<td align=\"center\">" +
                sett().numberToString(vatPrice, 'f', 2) + "</td>"; // vat
  invStrList += "<td align=\"center\">" +
                sett().numberToString(grossTotal, 'f', 2) + "</td>"; // gross
  invStrList += "</tr>";
  invStrList += "</table>";
  invStrList += "<hr class=\"hrdiv1\" />";
}

void Correction::makeInvoiceSummAll() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  invStrList += "<table class=\"page_break\" width=\"100%\" border=\"0\" cellpadding=\"7\">";
  invStrList += "<tr class=\"summary\">";
  invStrList += "<td width=\"48%\">";
  invStrList += trUtf8("Wartość faktury: ") +
                sett().numberToString(origGrossTotal) + "<br/>";
  invStrList +=
      trUtf8("Wartość korekty: ") + sett().numberToString(grossTotal) + "<br/>";

  if (diffTotal > 0) {

    invStrList += trUtf8("Do zapłaty: ");
    invStrList += sum3->text() + " " + currCombo->currentText() + "<br/>";

  } else if (diffTotal < 0) {

    invStrList += trUtf8("Do zwrotu: ");
    invStrList +=
        sum3->text().remove(0, 1) + " " + currCombo->currentText() + "<br/>";
  }

  ConvertAmount *conv = new ConvertAmount();

  QString sumCorrected = QString();
  if(sum3->text().at(0) == '-')
  sumCorrected = conv->convertPL(sum3->text().remove(0, 1), currCombo->currentText());
  else
  sumCorrected = conv->convertPL(sum3->text(), currCombo->currentText());

  invStrList +=
      trUtf8("Słownie: ") + sumCorrected + "<br/>";

  delete conv;

  if (paysCombo->currentText() == trUtf8("gotówka")) {

    invStrList +=
        trUtf8("Sposób płatności: ") + paysCombo->currentText() + "<br/>";

  } else if (paysCombo->currentText() == trUtf8("zaliczka")) {

    invStrList += "<span style=\"toPay\">";

    ratesCombo->setCurrentIndex(0);
    QString whatMethod_one = QString();

    if (sendKindInfo->text() == trUtf8("gotówka"))
      whatMethod_one = trUtf8("gotówką");
    else
      whatMethod_one = trUtf8("przelewem");

    ratesCombo->setCurrentIndex(1);
    QString whatMethod_two = QString();

    if (sendKindInfo->text() == trUtf8("gotówka"))
      whatMethod_two = trUtf8("gotówką");
    else
      whatMethod_two = trUtf8("przelewem");

    ratesCombo->setCurrentIndex(0);

    invStrList +=
        QString(trUtf8("Zapłacono ") + whatMethod_one + ": " +
                rateLabelInfo->text() + " " + currCombo->currentText() + " " +
                ratesCombo->itemText(0) + "<br/>");

    invStrList += QString(
        trUtf8("Zaległości ") + whatMethod_two + ": " + restLabelInfo->text() +
        " " + currCombo->currentText() + " " + ratesCombo->itemText(1));

    invStrList += "</span>";

  } else if (paysCombo->currentText() == trUtf8("przelew")) {

    invStrList +=
        trUtf8("Sposób płatności: ") + paysCombo->currentText() + "<br/>";
    invStrList += "<span style=\"payDate\">";
    invStrList += trUtf8("Termin płatności: ") +
                  liabDate->date().toString(sett().getDateFormat()) + "<br/>";
    invStrList += "</span>";

  } else {

    invStrList +=
        trUtf8("Sposób płatności: ") + paysCombo->currentText() + "<br/>";
    invStrList += "<span style=\"payDate\">";
    invStrList += trUtf8("Termin płatności: ") +
                  liabDate->date().toString(sett().getDateFormat()) + "<br/>";
    invStrList += "</span>";
  }

  invStrList +=
      trUtf8("Przyczyna korekty: ") + reasonCombo->currentText() + "<br/>";
  invStrList +=
      "<span class=\"additionalText\">" + additEdit->toHtml() + "</span>";
  invStrList += "</td>";
  invStrList += "<td width=\"4%\">&nbsp;</td>";
  invStrList += "<td width=\"48%\" valign=\"top\">";
  invStrList += "<table width=\"90%\" border=\"0\">";
  invStrList +=
      "<tr><td colspan=\"4\"><span style=\"font-size:8pt; font-weight:600;\">";
  invStrList += trUtf8("Ogółem stawkami:");
  invStrList += "</span></td>"; // In total:
  invStrList += "</tr>";
  invStrList += getGroupedSums();
  invStrList += "<tr>";
  invStrList += "<td>&nbsp;</td>"; // net
  invStrList += "<td>&nbsp;</td>"; // rate
  invStrList += "<td>&nbsp;</td>"; // tax
  invStrList += "<td>&nbsp;</td>"; // gross
  invStrList += "</tr>";
  invStrList += "</table>";
  invStrList += "</td></tr></table>";
}

//*************** HTML methods END  *** *****************************
