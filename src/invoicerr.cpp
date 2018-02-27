#include "invoicerr.h"

InvoiceRR::InvoiceRR(QWidget *parent, IDataLayer *dl, QString in_form)
    : Invoice(parent, dl, in_form) {
  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;
}

InvoiceRR::~InvoiceRR() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  additEdit->clear();
  additEdit->setDisabled(false);
  ifpaysVAT->deleteLater();
  ifpaysVAT = 0;
}

void InvoiceRR::invoiceRRInit() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  additEdit->setText(trUtf8("Oświadczam, że jestem rolnikiem ryczałtowym "
                            "zwolnionym od podatku od towarów"
                            " i usług na podstawie art. 43 ust. 1 pkt 3 ustawy "
                            "o podatku od towarów i usług."));
  additEdit->setDisabled(true);

  ifpaysVAT = new QCheckBox;
  ifpaysVAT->setText(trUtf8("Jest płatnikiem VAT"));
  horizontalLayout_4->addWidget(ifpaysVAT);
}

QString InvoiceRR::getInvoiceTypeAndSaveNr() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  QString itype = "RR";
  sett().setValue("rr", invNr->text());
  return itype;
}

void InvoiceRR::makeInvoice(bool to_print) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  if (!ifpaysVAT->isChecked()) {
    QMessageBox::information(this, "QFaktury",
                             trUtf8("Zaznacz opcję \"jest płatnikiem VAT\" dla "
                                    "wybranego przedsiębiorcy"),
                             QMessageBox::Ok);
    return;
  }

  if (buyerName->text() == "") {

    QMessageBox::information(this, "QFaktury", trUtf8("Wybierz kontrahenta"),
                             QMessageBox::Ok);
    return;
  }

  if (tableGoods->rowCount() == 0) {

    QMessageBox::information(this, "QFaktury", trUtf8("Nie ma towarów"),
                             QMessageBox::Ok);
    return;
  }

  invStrList.clear();
  makeInvoiceHeadarHTML();

  if (ifCSS) {

    makeInvoiceHeadar(true, false, true);
    makeInvoiceBody();
    makeInvoiceProducts();
    makeInvoiceSumm();
    makeInvoiceSummAll();
    makeInvoiceFooter();

    int numberOfCopies = sett().value("numberOfCopies", 2).toInt();

    for (int i = 1; i <= numberOfCopies; i++) {

      makeInvoiceHeadar(true, true, false);
      makeInvoiceBody();
      makeInvoiceProducts();
      makeInvoiceSumm();
      makeInvoiceSummAll();
      makeInvoiceFooter();
    }

    makeInvoiceFooterHtml();

    if (to_print) print();

  }
}

void InvoiceRR::setData(InvoiceData &invData) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  invData.id = fName;
  invData.customer = buyerName->text();
  if (ifpaysVAT->isChecked())
    invData.ifpVAT = true;
  else
    invData.ifpVAT = false;
  qDebug() << "buyerName->text() in setData(InvoiceData&):"
           << buyerName->text();
  invData.invNr = invNr->text();
  invData.sellingDate = sellingDate->date();
  invData.issueDate = productDate->date();
  invData.endTransDate = endTransactionDate->date();

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

void InvoiceRR::getData(InvoiceData invData) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  buyerName->setText(invData.customer);
  invNr->setText(invData.invNr);
  ifpaysVAT->setChecked(invData.ifpVAT);
  sellingDate->setDate(invData.sellingDate);
  productDate->setDate(invData.issueDate);
  endTransactionDate->setDate(invData.endTransDate);

  if (!invData.duplDate.isNull() && invData.duplDate.isValid())
    dupDate = invData.duplDate;

  qDebug() << "DISCOUNT: " << invData.discount;
  if (invData.discount == 0) {

    discountVal->setValue(0);

  } else {

    constRab->setChecked(true);
    discountVal->setValue(invData.discount);
  }

  qDebug() << "DISCOUNT: " << invData.discount;
  qDebug() << "changed discountVal: " << discountVal->value();

  additEdit->setText(invData.additText);

  if (invData.paymentType == trUtf8("zaliczka")) {

    disconnect(paysCombo, SIGNAL(currentIndexChanged(QString)), this,
               SLOT(payTextChanged(QString)));
    disconnect(ratesCombo, SIGNAL(currentIndexChanged(QString)), this,
               SLOT(rateDateChanged(QString)));
    labelRate = new QLabel();
    labelRate->setText(trUtf8("Termin raty:"));
    labelRate->setAlignment(Qt::AlignRight);
    addDataLabels->addWidget(labelRate);

    ratesCombo->addItem(
        invData.custPaym.date1.toString(sett().getDateFormat()));

    qDebug() << "added date to ratesCombo: "
             << invData.custPaym.date1.toString(sett().getDateFormat());
    ratesCombo->addItem(
        invData.custPaym.date2.toString(sett().getDateFormat()));
    qDebug() << "added date to ratesCombo: "
             << invData.custPaym.date2.toString(sett().getDateFormat());
    ratesCombo->setCurrentText(
        invData.custPaym.date1.toString(sett().getDateFormat()));
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
    rateLabelInfo->setText(sett().numberToString(invData.custPaym.amount1));
    dataPayments->addWidget(rateLabelInfo);

    sendKindInfo = new QLabel();
    sendKindInfo->setText(invData.custPaym.payment1);
    dataPayments->addWidget(sendKindInfo);

    restLabelInfo = new QLabel();
    restLabelInfo->setText(sett().numberToString(invData.custPaym.amount2));
    dataPayments->addWidget(restLabelInfo);
  }

  currCombo->setCurrentText(invData.currencyType);
  paysCombo->setCurrentText(invData.paymentType);
  liabDate->setDate(invData.liabDate);

  if (invData.paymentType == trUtf8("zaliczka")) {
    connect(paysCombo, SIGNAL(currentIndexChanged(QString)), this,
            SLOT(payTextChanged(QString)));
    connect(ratesCombo, SIGNAL(currentIndexChanged(QString)), this,
            SLOT(rateDateChanged(QString)));
  }

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__
           << "EXIT";
}
