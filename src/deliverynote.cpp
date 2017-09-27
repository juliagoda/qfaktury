#include "deliverynote.h"
#include "MainWindow.h"
#include "XmlDataLayer.h"

/** Constructor
 */

DeliveryNote::DeliveryNote(QWidget *parent, IDataLayer *dl, QString in_form)
    : Invoice(parent, dl, in_form) {

}

/** Destructor
 */

DeliveryNote::~DeliveryNote() {

}


void DeliveryNote::makeInvoiceProductsHeadar() {

    invStrList += "<tr align=\"center\" valign=\"middle\" "
                  "class=\"productsHeader\" width=\"100%\" >"; // TUTAJ

    int currentPercent = 0;
    int &sumPercents = currentPercent;


      currentPercent += 3;
      invStrList += "<td align=\"center\" width=\"" + sett().numberToString(3) +
                    "%\">" + trUtf8("Lp.") + "</td>";


      int res = 100 - sumPercents;
      invStrList += "<td align=\"center\" width=\"" + sett().numberToString(res) +
                    "%\">" + trUtf8("Nazwa towaru/usługi") + "</td>";


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

    invStrList += "<tr width=\"100%\"><td width=\"100%\">";

    invStrList += "<table border=\"2\" align=\"right\" cellspacing=\"0\" "
                  "cellpadding=\"5\" width=\"100%\">";

    makeInvoiceProductsHeadar();

    for (int i = 0; i < tableGoods->rowCount(); ++i) {

      invStrList += "<tr class=\"products\">";
      // no, name, code, pkwiu, amount, unit, discount, unit price, net, vat,
      // gross

      sett().beginGroup("invoices_positions");

        invStrList += "<td>" + sett().numberToString(i + 1) + "</td>"; // LP

        invStrList += "<td align=\"left\">" + tableGoods->item(i, 1)->text() + "</td>"; // Name

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

    invStrList += "<br><br>";

}


void DeliveryNote::makeInvoiceSummAll() {

    invStrList += "<table width=\"100%\" border=\"0\">";

    invStrList += "<tr class=\"summary\">";
    invStrList += "<td width=\"3%\">&nbsp;</td>";
    invStrList += "<td width=\"48%\">";

    // <span/>???



      invStrList += "<span class=\"toPay\">";
      invStrList +=
          trUtf8("forma płatności: ") + paysCombo->currentText() + "<br>";
      invStrList += "</span>";

      invStrList += "<span class=\"payDate\">";
      invStrList += trUtf8("termin płatności: ") +
                    liabDate->date().toString(sett().getDateFormat()) + "<br>";
      invStrList += "</span>";


    invStrList += "<br><br>";
    invStrList +=
        "<span class=\"additionalText\">" + additEdit->text() + "</span>";
    invStrList += "</td>";
    invStrList += "<td width=\"3%\">&nbsp;</td>";

    invStrList += "</tr>";
    invStrList += "</table>";
}


void DeliveryNote::makeInvoiceFooter() {

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

    QMessageBox msgBox;
    msgBox.setText(trUtf8("Czy chcesz od razu do tworzonego dokumentu WZ wygenerować fakturę?"));
    msgBox.setInformativeText(
        trUtf8("Jeśli chcesz dodać dodatkowo fakturę do listy faktur, wciśnij - OK. Jeśli "
               "chcesz zapisać tylko dokument WZ, wciśnij - Anuluj. Pamiętaj, że fakturę do"
               "każdego dokumentu WZ należy wystawić w nieprzekraczalnym terminie 7 dni"));
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret2 = msgBox.exec();

    InvoiceData invData;
    setData(invData);

    switch (ret2) {
    case QMessageBox::Ok:
    {

        ifcreateInv = true;

        result = dataLayer->invoiceInsertData(invData, type);
        ret = dataLayer->getRet();
        MainWindow::instance()->shouldHidden = true;
        Invoice::instance()->makeInvoice();
        MainWindow::instance()->shouldHidden = false;

        if (!result) {
          QMessageBox::warning(
              this, trUtf8("Zapis faktury"),
              trUtf8("Zapis faktury zakończył się niepowodzeniem. Sprawdź czy masz "
                     "uprawnienia do zapisu lub odczytu w ścieżce ") +
                  sett().getInvoicesDir() + trUtf8(" oraz czy ścieżka istnieje."));
        }

        result = dataLayer->delivNoteInsertData(invData, type);
        retWarehouse = dataLayer->getRetWarehouse();
        MainWindow::instance()->shouldHidden = true;
        makeInvoice();
        MainWindow::instance()->shouldHidden = false;

        if (!result) {
          QMessageBox::warning(
              this, trUtf8("Zapis dokumentu WZ"),
              trUtf8("Zapis dokumentu WZ zakończył się niepowodzeniem. Sprawdź czy masz "
                     "uprawnienia do zapisu lub odczytu w ścieżce ") +
                  sett().getWarehouseFullDir() + trUtf8(" oraz czy ścieżka istnieje."));
        }

    break;
    }
    case QMessageBox::Cancel:
    {

        result = dataLayer->delivNoteInsertData(invData, type);
        retWarehouse = dataLayer->getRetWarehouse();
        MainWindow::instance()->shouldHidden = true;
        makeInvoice();
        MainWindow::instance()->shouldHidden = false;

        if (!result) {
          QMessageBox::warning(
              this, trUtf8("Zapis dokumentu WZ"),
              trUtf8("Zapis dokumentu WZ zakończył się niepowodzeniem. Sprawdź czy masz "
                     "uprawnienia do zapisu lub odczytu w ścieżce ") +
                  sett().getWarehouseFullDir() + trUtf8(" oraz czy ścieżka istnieje."));
        }

    break;
    }
    }

    saveBtn->setEnabled(false);
    rmGoodsBtn->setEnabled(false);
    editGoodsBtn->setEnabled(false);

    saveFailed = false;
    canClose = true;

    return result;
}


void DeliveryNote::setData(InvoiceData &invData) {

    qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

    invData.id = fName;
    invData.customer = buyerName->text();
    qDebug() << "buyerName->text() in setData(InvoiceData&):"
             << buyerName->text();
    invData.invNr = invNr->text();
    invData.sellingDate = sellingDate->date();
    invData.issueDate = productDate->date();
    invData.ifInvForDelNote = ifcreateInv;

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
