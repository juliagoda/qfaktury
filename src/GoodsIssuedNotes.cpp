#include "GoodsIssuedNotes.h"
#include "ChangeAmount.h"
#include "Const.h"
#include "GoodsList.h"
#include "MainWindow.h"
#include "XmlDataLayer.h"

#include <QDateTimeEdit>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTableWidget>

/** Constructor
 */

GoodsIssuedNotes::GoodsIssuedNotes(QWidget *parent, IDataLayer *dl,
                                   QString in_form)
    : Warehouse(parent, dl, in_form) {

  tableGoods->setHorizontalHeaderItem(9, new QTableWidgetItem("Ilość żądana"));
  tableGoods->setHorizontalHeaderItem(10, new QTableWidgetItem("Ilość wydana"));

  invoiceType = s_RW;
  setObjectName("GoodsIssuedNotes");

  QLabel *label1 = new QLabel;
  label1->setText("Miejsce odbioru towaru: ");
  lineEdit1 = new QLineEdit;
  connect(lineEdit1, SIGNAL(textChanged(QString)), this,
          SLOT(emitChange(QString)));
  label1->setBuddy(lineEdit1);

  QLabel *label2 = new QLabel;
  label2->setText("Miejsce przekazania towaru ");
  lineEdit2 = new QLineEdit;
  label2->setBuddy(lineEdit2);

  QLabel *label3 = new QLabel;
  label3->setText("Dział/wydział dla kosztu: ");
  lineEdit3 = new QLineEdit;
  label3->setBuddy(lineEdit3);

  QLabel *label4 = new QLabel;
  label4->setText("Data wydania towaru: ");
  dateTimeEdit1 = new QDateTimeEdit;
  dateTimeEdit1->setDateTime(QDateTime::currentDateTime());
  label4->setBuddy(dateTimeEdit1);

  QLabel *label5 = new QLabel;
  label5->setText("Data przyjęcia towaru: ");
  dateTimeEdit2 = new QDateTimeEdit;
  dateTimeEdit2->setDateTime(QDateTime::currentDateTime());
  label5->setBuddy(dateTimeEdit2);

  formLayout = new QFormLayout;

  formLayout->addRow(label1, lineEdit1);
  formLayout->addRow(label2, lineEdit2);
  formLayout->addRow(label3, lineEdit3);
  formLayout->addRow(label4, dateTimeEdit1);
  formLayout->addRow(label5, dateTimeEdit2);

  widgetsRW = new QWidget;
  widgetsRW->setLayout(formLayout);
  verticalLayout->addWidget(widgetsRW);
  widgetsRW->show();

  constRab->setDisabled(true);

  textLabel3->hide();
  sellingDate->hide();

  textLabelSum1->hide();
  textLabelSum2->hide();
  textLabelSum3->hide();

  sum1->hide();
  sum2->hide();
  sum3->hide();

  paysCombo->setDisabled(true);

  connect(lineEdit2, SIGNAL(textEdited(const QString &)), this,
          SLOT(emitChange(const QString &)));
  connect(lineEdit3, SIGNAL(textEdited(const QString &)), this,
          SLOT(emitChange(const QString &)));
  connect(dateTimeEdit1, SIGNAL(dateChanged(const QDate &)), this,
          SLOT(emitChange(const QDate &)));
  connect(dateTimeEdit2, SIGNAL(dateChanged(const QDate &)), this,
          SLOT(emitChange(const QDate &)));

  this->update();
}

/** Destructor
 */

GoodsIssuedNotes::~GoodsIssuedNotes() {

  disconnect(lineEdit1, SIGNAL(textEdited(const QString &)), this,
             SLOT(emitChange(const QString &)));
  disconnect(lineEdit2, SIGNAL(textEdited(const QString &)), this,
             SLOT(emitChange(const QString &)));
  disconnect(lineEdit3, SIGNAL(textEdited(const QString &)), this,
             SLOT(emitChange(const QString &)));
  disconnect(dateTimeEdit1, SIGNAL(dateChanged(const QDate &)), this,
             SLOT(emitChange(const QDate &)));
  disconnect(dateTimeEdit2, SIGNAL(dateChanged(const QDate &)), this,
             SLOT(emitChange(const QDate &)));

  constRab->setEnabled(true);

  textLabel3->show();
  sellingDate->show();

  textLabelSum1->show();
  textLabelSum2->show();
  textLabelSum3->show();

  sum1->show();
  sum2->show();
  sum3->show();

  paysCombo->setEnabled(true);

  foreach (QWidget *w, widgetsRW->findChildren<QWidget *>()) {
    if (!w->windowFlags() && Qt::Window)
      delete w;
  }

  if (formLayout != 0)
    formLayout = 0;
  delete formLayout;
  widgetsRW->deleteLater();

  tableGoods->setHorizontalHeaderItem(9, new QTableWidgetItem("VAT"));
  tableGoods->setHorizontalHeaderItem(10, new QTableWidgetItem("Brutto"));
}

void GoodsIssuedNotes::readWarehouseData(QString invFile) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  backBtn->setEnabled(false);
  invNr->setEnabled(false);

  setWindowTitle(s_WIN_RW_EDIT);

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

  invNr->setText(root.attribute("no"));
  sellingDate->setDate(
      QDate::fromString(root.attribute("sellingDate"), sett().getDateFormat()));
  productDate->setDate(
      QDate::fromString(root.attribute("issueDate"), sett().getDateFormat()));

  lineEdit1->setText(root.attribute("goodFromPlace"));
  lineEdit2->setText(root.attribute("goodToPlace"));
  lineEdit3->setText(root.attribute("departmentCost"));

  dateTimeEdit1->setDate(QDate::fromString(root.attribute("goodFromDate"),
                                           sett().getDateFormat()));
  dateTimeEdit2->setDate(
      QDate::fromString(root.attribute("goodToDate"), sett().getDateFormat()));

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

  static const char *goodsColumns[] = {
      "id",    "name", "quantity",       "quantityType",
      "price", "nett", "requiredAmount", "givedOutAmount"};

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
    tableGoods->setItem(i, 7,
                        new QTableWidgetItem(good.attribute(goodsColumns[4])));
    tableGoods->setItem(i, 8,
                        new QTableWidgetItem(good.attribute(goodsColumns[5])));
    tableGoods->setItem(i, 9,
                        new QTableWidgetItem(good.attribute(goodsColumns[6])));
    tableGoods->setItem(i, 10,
                        new QTableWidgetItem(good.attribute(goodsColumns[7])));

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

  wareData->goodFromPlace = lineEdit1->text();
  wareData->goodToPlace = lineEdit2->text();
  wareData->departmentCost = lineEdit3->text();
  wareData->goodFromDate = dateTimeEdit1->date();
  wareData->goodToDate = dateTimeEdit2->date();

  for (i = 0; i < goodsCount; ++i) {

    ProductData product; //  = new ProductData();
    product.setId(good.attribute(goodsColumns[0]));
    product.setName(good.attribute(goodsColumns[1]));
    product.setQuantity(good.attribute(goodsColumns[2]));
    product.setQuanType(good.attribute(goodsColumns[3]));
    product.setPrice(good.attribute(goodsColumns[4]));
    product.setNett(good.attribute(goodsColumns[5]));
    product.setRequiredAmount(good.attribute(goodsColumns[6]));
    product.setGivedOutAmount(good.attribute(goodsColumns[7]));
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

void GoodsIssuedNotes::makeInvoiceHeadar(bool, bool breakPage, bool original) {

  QString breakPageStr = "class=\"page_break\"";
  if (breakPage == false)
    breakPageStr = "";

  invStrList +=
      "<table comment=\"headar table\" width=\"100%\" " + breakPageStr + ">";
  invStrList += "<tr>";
  invStrList += "<td width=\"60%\" align=\"center\" valign=\"bottom\">";
  invStrList += "<span class=\"stamp\">";
  QString logo = sett().value("logo").toString();

  if (logo != "") {
    invStrList +=
        "<img src=\"" + logo + "\" width=\"100\" " + " height=\"100\"+ >";
  } else {
    invStrList += "";
  }

  invStrList += "</span>";
  invStrList += "</td>";

  if (sett().value("css").toString() == "tables.css") {

    invStrList += "<td id=\"invoiceInfo\" width=\"35%\" align=\"right\">";

    invStrList += "<table id=\"rightInvTable\" width=\"100%\" border=\"1\" "
                  "cellspacing=\"0\" cellpadding=\"5\" >";

    invStrList += "<tr>";
    invStrList += "<td id=\"invFirstLine\" style=\"font-size:12pt\">";
    invStrList += invoiceType + "<br/>";
    invStrList += trUtf8("Nr: ") + invNr->text() + "</td>";
    invStrList += "</tr>";
    invStrList += "<tr>";
    invStrList += "<td>" + trUtf8("Data wystawienia: ") +
                  productDate->date().toString(sett().getDateFormat()) +
                  "</td>";

    invStrList += "</tr>";

    invStrList += "</table></td><td width=\"3%\">&nbsp;</td>";

  } else {

    invStrList += "<td id=\"invoiceInfo\" width=\"35%\" align=\"right\">";

    invStrList += "<table id=\"rightInvTable\" width=\"100%\" border=\"0\" "
                  "cellspacing=\"0\" >";
    invStrList += "<tr>";
    invStrList += "<td id=\"invFirstLine\" style=\"font-size:12pt\">";
    invStrList += invoiceType + "<br/>";
    invStrList += trUtf8("Nr: ") + invNr->text() + "<br></td>";
    invStrList += "</tr>";
    invStrList += "<tr>";
    invStrList += "<td>" + trUtf8("Data wystawienia: ") +
                  productDate->date().toString(sett().getDateFormat());

    invStrList += "</tr>";

    invStrList += "</table></td><td width=\"3%\">&nbsp;</td>";
  }

  invStrList += "</tr>";
  invStrList += "<br/><br/>";
  invStrList += "<tr>";
  invStrList += "<td class=\"origcopy\" colspan=\"2\" align=\"right\" "
                "valign=\"top\"><br>";

  if (original) {
    invStrList += trUtf8("ORYGINAŁ");
  } else {
    invStrList += trUtf8("KOPIA");
  }

  invStrList += "<hr/><br/>";

  invStrList += "</td><td width=\"3%\">&nbsp;</td>";
  invStrList += "</tr>";
  invStrList += "</table>";
  invStrList += "</td></tr>";
}

void GoodsIssuedNotes::makeInvoiceBody() {

  invStrList += "<tr width=\"100%\"><td width=\"100%\">";
  invStrList += "<table width=\"100%\" border=\"0\">";
  invStrList += "<tr class=\"persons\" width=\"100%\">";
  invStrList += "<td width=\"20\">&nbsp;</td>";
  invStrList += "<td class=\"buyerSeller\" width=\"48%\"> ";
  invStrList += "<p id=\"seller\"></p><br/>";

  QSettings userSettings("elinux", "user");

  sett().beginGroup("printpos");
  userSettings.beginGroup("choosenSeller");

  if (sett().value("username").toBool() &&
      (!userSettings.value("name").toString().trimmed().isEmpty()))
    invStrList += userSettings.value("name").toString() + "<br/>";

  if (sett().value("useradress").toBool() &&
      (!userSettings.value("address").toString().trimmed().isEmpty()))
    invStrList += userSettings.value("address").toString() + "<br/>";

  if (sett().value("usercity").toBool() &&
      (!userSettings.value("zip").toString().trimmed().isEmpty()))
    invStrList += userSettings.value("zip").toString() + " ";

  if (sett().value("usercity").toBool() &&
      (!userSettings.value("city").toString().trimmed().isEmpty()))
    invStrList += userSettings.value("city").toString() + "<br/>";

  if (sett().value("usernip").toBool() &&
      (!userSettings.value("tic").toString().trimmed().isEmpty()))
    invStrList +=
        trUtf8("NIP: ") + userSettings.value("tic").toString() + "<br/>";

  if (sett().value("userbank").toBool() &&
      (!userSettings.value("bank").toString().trimmed().isEmpty()))
    invStrList += trUtf8("Nazwa banku: ") +
                  userSettings.value("bank").toString() + "<br/>";

  if (sett().value("useraccount").toBool() &&
      (!userSettings.value("account").toString().trimmed().isEmpty()))
    invStrList += trUtf8("Nr konta: ") +
                  userSettings.value("account").toString().replace("-", " ") +
                  "<br/>";

  if (sett().value("userswift").toBool() &&
      (!userSettings.value("swift").toString().trimmed().isEmpty()))
    invStrList += trUtf8("SWIFT/BIC: ") +
                  userSettings.value("swift").toString() + "<br/>";

  if (sett().value("userkrs").toBool() &&
      (!userSettings.value("krs").toString().trimmed().isEmpty()))
    invStrList +=
        trUtf8("KRS: ") + userSettings.value("krs").toString() + "<br/>";

  if (sett().value("userphone").toBool() &&
      (!userSettings.value("phone").toString().trimmed().isEmpty()))
    invStrList +=
        trUtf8("Telefon: ") + userSettings.value("phone").toString() + "<br/>";

  if (sett().value("userfax").toBool() &&
      (!userSettings.value("fax").toString().trimmed().isEmpty()))
    invStrList +=
        trUtf8("Fax: ") + userSettings.value("fax").toString() + "<br/>";

  if (sett().value("usermail").toBool() &&
      (!userSettings.value("email").toString().trimmed().isEmpty()))
    invStrList +=
        trUtf8("Email: ") + userSettings.value("email").toString() + "<br/>";

  if (sett().value("userwww").toBool() &&
      (!userSettings.value("website").toString().trimmed().isEmpty()))
    invStrList += trUtf8("Strona www: ") +
                  userSettings.value("website").toString() + "<br/>";

  userSettings.endGroup();
  sett().endGroup();

  invStrList += "</td>";
  invStrList += "</tr>";
  invStrList += "</table>";
  invStrList += "<hr/>";
  invStrList += "</td></tr>";
}

void GoodsIssuedNotes::makeInvoiceProductsHeadar() {

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
                "%\">" + trUtf8("Ilość żądana") + "</td>";

  currentPercent += 9;
  invStrList += "<td align=\"center\" width=\"" + sett().numberToString(9) +
                "%\">" + trUtf8("Ilość wydana") + "</td>";

  currentPercent += 3;
  invStrList += "<td align=\"center\" width=\"" + sett().numberToString(3) +
                "%\">" + trUtf8("Cena jn.") + "</td>";

  currentPercent += 8;
  invStrList += "<td align=\"center\" width=\"" + sett().numberToString(8) +
                "%\">" + trUtf8("Jm.") + "</td>";

  invStrList += "</tr>";
}

void GoodsIssuedNotes::makeInvoiceProducts() {

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

    invStrList +=
        "<td>" + tableGoods->item(i, 9)->text() + "</td>"; // REQUIRED AMOUNT

    invStrList +=
        "<td>" + tableGoods->item(i, 10)->text() + "</td>"; // GIVED OUT AMOUNT

    invStrList +=
        "<td>" + tableGoods->item(i, 7)->text() + "</td>"; // UNIT PRICE

    invStrList += "<td>" + tableGoods->item(i, 5)->text() + "</td>"; // UNIT

    invStrList += "</tr>";
  }

  invStrList += "</table>";
  invStrList += "</td>";
  invStrList += "</tr>";
}

void GoodsIssuedNotes::makeInvoiceSumm() {

  invStrList += "<tr width=\"100%\"><td width=\"100%\">";
  if (sett().value("css").toString() == "tables.css") {
    invStrList += "<br/><table align=\"right\" width=\"100%\" border=\"2\" "
                  "cellspacing=\"0\" cellpadding=\"5\">";

  } else {
    invStrList += "<br/><table align=\"right\" width=\"100%\" border=\"0\" "
                  "cellpadding=\"5\">";
  }
  invStrList +=
      "<tr class=\"productsSumHeader\" valign=\"middle\" width=\"100%\">";
  invStrList +=
      "<td id=\"notNec\" width=\"10%\" align=\"center\">&nbsp;</td>"; // TUTAJ
  invStrList +=
      "<td width=\"21%\" align=\"center\">" + trUtf8("Skąd") + "</td>"; // net
  invStrList +=
      "<td width=\"21%\" align=\"center\">" + trUtf8("Dokąd") + "</td>"; // vat
  invStrList += "<td width=\"31%\" align=\"center\">" +
                trUtf8("Wydział/Dział") + "</td>"; // brutto
  invStrList += "</tr><tr width=\"100%\" class=\"productsSum\">";
  invStrList += "<td align=\"center\"></td>";
  invStrList += "<td align=\"center\">" + lineEdit1->text() + "</td>"; // net
  invStrList += "<td align=\"center\">" + lineEdit2->text() + "</td>"; // vat
  invStrList += "<td align=\"center\">" + lineEdit3->text() + "</td>"; // brutto
  invStrList += "</tr>";
  invStrList += "</table></tr><br/><br/><br/>";
  invStrList += "<tr><table align=\"right\" width=\"100%\" border=\"0\" "
                "cellspacing=\"0\" cellpadding=\"5\">";
  invStrList +=
      "<tr class=\"productsSumHeader\" valign=\"middle\" width=\"100%\">";
  invStrList +=
      "<td id=\"notNec\" width=\"10%\" align=\"center\">&nbsp;</td>"; // TUTAJ
  invStrList += "<td width=\"11%\" align=\"center\">" +
                trUtf8("Razem netto: ") + "</td>"; // net

  double sumNet = 0;
  for (int i = 0; i < tableGoods->rowCount(); i++) {

    sumNet += sett().stringToDouble(tableGoods->item(i, 8)->text());
  }

  invStrList += "<td width=\"11%\" align=\"center\">" +
                sett().numberToString(sumNet, 'f', 2) + "</td>"; // vat
  invStrList += "</tr>";
  invStrList += "</table></tr><br/>";
}

void GoodsIssuedNotes::makeInvoiceSummAll() {

  invStrList += "<table width=\"100%\" border=\"0\">";

  invStrList += "<tr class=\"summary\">";
  invStrList += "<td width=\"3%\">&nbsp;</td>";
  invStrList += "<td width=\"48%\">";

  invStrList += "<span>";
  invStrList += trUtf8("Data wydania towaru: ") +
                dateTimeEdit1->date().toString(sett().getDateFormat()) +
                "<br/>";
  invStrList += "</span>";

  invStrList += "<span>";
  invStrList += trUtf8("Data przyjęcia towaru: ") +
                dateTimeEdit2->date().toString(sett().getDateFormat()) +
                "<br/>";
  invStrList += "</span>";

  invStrList += "<br/><br/>";
  invStrList +=
      "<span class=\"additionalText\">" + additEdit->text() + "</span>";
  invStrList += "</td>";
  invStrList += "<td width=\"3%\">&nbsp;</td>";

  invStrList += "</tr>";
  invStrList += "</table>";
}

void GoodsIssuedNotes::makeInvoiceFooter() {

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

bool GoodsIssuedNotes::saveInvoice() {

  qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << fName;

  bool result = false;
  if (!validateForm())
    return false;

  WarehouseData wareData;
  setData(wareData);

  result = dataLayer->warehouseInsertData(wareData, type);
  retWarehouse = dataLayer->getRetWarehouse();
  MainWindow::instance()->shouldHidden = true;
  makeInvoice();
  MainWindow::instance()->shouldHidden = false;

  if (!result) {
    QMessageBox::warning(
        this, trUtf8("Zapis dokumentu RW"),
        trUtf8("Zapis dokumentu RW zakończył się niepowodzeniem. Sprawdź, czy "
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

void GoodsIssuedNotes::setData(WarehouseData &invData) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  invData.id = fName;
  invData.customer = buyerName->text();
  qDebug() << "buyerName->text() in setData(InvoiceData&):"
           << buyerName->text();
  invData.invNr = invNr->text();
  invData.sellingDate = sellingDate->date();
  invData.issueDate = productDate->date();

  invData.goodFromPlace = lineEdit1->text();
  invData.goodToPlace = lineEdit2->text();
  invData.departmentCost = lineEdit3->text();
  invData.goodFromDate = dateTimeEdit1->date();
  invData.goodToDate = dateTimeEdit2->date();

  // no, name, code, pkwiu, amount, unit, discount, unit price, net, vat, gross
  for (int i = 0; i < tableGoods->rowCount(); ++i) {
    ProductData product; //  = new ProductData();

    product.setId(tableGoods->item(i, 0)->text());
    product.setName(tableGoods->item(i, 1)->text());
    product.setQuantity(tableGoods->item(i, 4)->text());
    product.setQuanType(tableGoods->item(i, 5)->text());
    product.setPrice(tableGoods->item(i, 7)->text());
    product.setNett(tableGoods->item(i, 8)->text());
    product.setRequiredAmount(tableGoods->item(i, 9)->text());
    product.setGivedOutAmount(tableGoods->item(i, 10)->text());
    invData.products[i] = product;
  }

  invData.additText = additEdit->text();
  invData.paymentType = paysCombo->currentText();

  invData.liabDate = liabDate->date();

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__
           << "EXIT";
}

void GoodsIssuedNotes::setData(InvoiceData &invData) {

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

void GoodsIssuedNotes::readData(QString fraFile) {

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

void GoodsIssuedNotes::getData(WarehouseData invData) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  buyerName->setText(invData.customer);
  invNr->setText(invData.invNr);
  sellingDate->setDate(invData.sellingDate);
  productDate->setDate(invData.issueDate);
  lineEdit1->setText(invData.goodFromPlace);
  lineEdit2->setText(invData.goodToPlace);
  lineEdit3->setText(invData.departmentCost);
  dateTimeEdit1->setDate(invData.goodFromDate);
  dateTimeEdit2->setDate(invData.goodToDate);

  if (!invData.duplDate.isNull() && invData.duplDate.isValid())
    dupDate = invData.duplDate;

  additEdit->setText(invData.additText);

  paysCombo->setCurrentText(invData.paymentType);
  liabDate->setDate(invData.liabDate);

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__
           << "EXIT";
}

void GoodsIssuedNotes::addGoods() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  GoodsList *goodslistWindow = new GoodsList(this);

  if (goodslistWindow->exec() == QDialog::Accepted) {

    MainWindow::insertRow(tableGoods, tableGoods->rowCount());
    QStringList row = goodslistWindow->getRetVal().split("|");
    int rowNum = tableGoods->rowCount() - 1;
    tableGoods->item(rowNum, 0)->setText(
        sett().numberToString(tableGoods->rowCount())); // id
    tableGoods->item(rowNum, 1)->setText(row[0]);       // name
    tableGoods->item(rowNum, 2)->setText(row[1]);       // code
    tableGoods->item(rowNum, 3)->setText(row[2]);       // pkwiu
    tableGoods->item(rowNum, 4)->setText(row[3]);       // quantity
    tableGoods->item(rowNum, 5)->setText(row[4]);       // qType
    tableGoods->item(rowNum, 6)->setText(row[5]);       // discount
    tableGoods->item(rowNum, 7)->setText(row[6]);       // price
    tableGoods->item(rowNum, 8)->setText(row[7]);       // net
    tableGoods->item(rowNum, 9)->setText(row[8]);       // required amount
    tableGoods->item(rowNum, 10)->setText(row[9]);      // gived out amount

    saveBtn->setEnabled(true);
    canClose = false;
  }

  delete goodslistWindow;
  goodslistWindow = NULL;
}

void GoodsIssuedNotes::editGoods() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;
  // we can only modify quantity

  goodsEdited = true;
  int cur = tableGoods->currentRow();

  if (cur >= 0) {

    ChangeAmount *changeQuant = new ChangeAmount(this);

    changeQuant->nameTow->setText(
        tableGoods->item(tableGoods->currentRow(), 1)->text());

    changeQuant->requiredAmBox->setValue(
        tableGoods->item(tableGoods->currentRow(), 9)->text().toInt());

    changeQuant->givedOutBox->setValue(
        tableGoods->item(tableGoods->currentRow(), 10)->text().toInt());

    if (changeQuant->exec() == QDialog::Accepted) {

      int currentRow = tableGoods->currentRow();
      tableGoods->item(currentRow, 9)
          ->setText(changeQuant->requiredAmBox->cleanText());
      tableGoods->item(currentRow, 10)
          ->setText(changeQuant->givedOutBox->cleanText());

      double changedNet =
          sett().stringToDouble(tableGoods->item(currentRow, 7)->text()) *
          sett().stringToDouble(tableGoods->item(currentRow, 10)->text());
      tableGoods->item(currentRow, 8)
          ->setText(sett().numberToString(changedNet, 'f', 2));

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

void GoodsIssuedNotes::delGoods() {

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

void GoodsIssuedNotes::emitChange(QString &) { saveBtn->setEnabled(true); }

void GoodsIssuedNotes::emitChange(const QDate &) { saveBtn->setEnabled(true); }

/** Sets the editability
 */
void GoodsIssuedNotes::setIsEditAllowed(bool isAllowed) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  if (!sett().value("editSymbol").toBool())
    invNr->setEnabled(isAllowed);

  backBtn->setEnabled(isAllowed);
  productDate->setEnabled(isAllowed);

  textLabelSum1->hide();
  textLabelSum2->hide();
  textLabelSum3->hide();

  sum1->hide();
  sum2->hide();
  sum3->hide();

  paysCombo->setDisabled(true);
  currCombo->setEnabled(true);
  constRab->setDisabled(true);

  liabDate->setDisabled(true);

  lineEdit1->setEnabled(true);
  lineEdit2->setEnabled(true);
  lineEdit3->setEnabled(true);
  dateTimeEdit1->setEnabled(true);
  dateTimeEdit2->setEnabled(true);

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__
           << "EXIT";
}
