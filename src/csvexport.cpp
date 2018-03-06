#include "csvexport.h"
#include "ui_csvexport.h"

#include "settings.h"
#include "xmldatalayer.h"
#include "invoicedata.h"

#include <QFileDialog>

CsvExport::CsvExport(IDataLayer* dlCsv, QWidget *parent) :
    dl(dlCsv), QWidget(parent),
    ui(new Ui::CsvExport)
{      
    ui->setupUi(this);

    qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

    putDataIntoWidgets(getPathCsv());
    prepareConnections();
    show();
}


CsvExport::~CsvExport()
{
    delete ui;
}


void CsvExport::prepareConnections() {

      qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

    connect(ui->browseButton, &QAbstractButton::clicked, this,
            &CsvExport::choosePathCsv);
    connect(ui->okButton, &QAbstractButton::clicked, this,
            &CsvExport::createCsvFiles);
    connect(ui->cancButton, &QAbstractButton::clicked, this, [=]() { close(); });

}


const QString CsvExport::getPathCsv() {

      qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

    QString path = QDir::toNativeSeparators(sett().getCSVDir());

    sett().beginGroup("csv_settings");

    bool csvPathSett = !sett().value("csv_path").toString().isEmpty() &&
                       !sett().value("csv_path").toString().isNull();

    if (csvPathSett)
       path = QDir::toNativeSeparators(sett().value("csv_path").toString());

    sett().endGroup();

    return path;

}


void CsvExport::putDataIntoWidgets(QString dirPath) {

    ui->directoryLineEdit->setText(dirPath);
}


void CsvExport::choosePathCsv() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  QString directory =
      QDir::toNativeSeparators(QFileDialog::getExistingDirectory(
          this, tr("Find Files"), sett().getCSVDir()));

  if (!directory.isEmpty()) {
    putDataIntoWidgets(directory);
  }

}


bool CsvExport::createPathCsv(const QString path) {

      qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

      QDir csvDir(path);
      if (!csvDir.exists())

      csvDir.mkpath(path);

      return true;

}


void CsvExport::splitCsvTasks(bool expBuyers, bool expGoods, bool expInvoices, bool expWarehouses) {

      qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

    sett().beginGroup("csv_settings");

    qDebug() << "directory path for csv in new window has not been empty";
    qDebug() << "If export_buyers in qfaktury.conf is set: "
             << sett().value("export_buyers").toBool();
    qDebug() << "If export_goods in qfaktury.conf is set: "
             << sett().value("export_goods").toBool();
    qDebug() << "If export_invoices in qfaktury.conf is set: "
             << sett().value("export_invoices").toBool();
    qDebug() << "If export_warehouses in qfaktury.conf is set: "
             << sett().value("export_warehouses").toBool();


    createSellersCsvFiles(sett().value("csv_format").toString());
    if (expBuyers) createBuyersCsvFiles(sett().value("csv_format").toString());
    if (expGoods) createProductsCsvFiles(sett().value("csv_format").toString());
    if (expInvoices) createInvoicesCsvFiles(sett().value("csv_format").toString(), QDate(QDate::currentDate().year(), 1, 1),
                             QDate(QDate::currentDate().year(), 12, 31));
    if (expWarehouses) createWareCsvFiles(sett().value("csv_format").toString(), QDate(QDate::currentDate().year(), 1, 1),
                         QDate(QDate::currentDate().year(), 12, 31));

    sett().endGroup();

    QMessageBox::information(this, "Zakończenie eksportu", "Eksport danych dobiegł końca. Zaleca się sprawdzenie, czy pliki faktycznie znajdują się we wskazanym miejscu");

}


void CsvExport::createCsvFiles() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  createPathCsv(getPathCsv());

  if (ui->directoryLineEdit->text().isEmpty()) {

      QMessageBox::warning(this, trUtf8("Brakująca ścieżka"),
                         trUtf8("Nazwa dla archiwum oraz ścieżka dla "
                                "tworzonego archiwum nie może być pominięta"));

  } else {

      sett().beginGroup("csv_settings");
      splitCsvTasks(sett().value("export_buyers").toBool(), sett().value("export_goods").toBool(),
                    sett().value("export_invoices").toBool(), sett().value("export_warehouses").toBool());
      sett().endGroup();

  }
}


QString CsvExport::separator(QString format) {

    QString character = ",";
    if (format == "EU") character = ",";
    else character = ";";

    return character;

}


QString CsvExport::preventNull(QString elementText) {

    return (elementText != "") ? elementText : "null";
}


void CsvExport::createBuyersCsvFiles(QString format) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  if (!idCvsBuyer.isEmpty())
    idCvsBuyer.clear();

  QString checkSlashPath = ui->directoryLineEdit->text();
  if (!checkSlashPath.endsWith('/'))
    checkSlashPath += '/';
  QFile csv(checkSlashPath + "/kontrahenci_buyers.csv");
  qDebug() << "Buyers csv path: " << csv.fileName();
  csv.open(QFile::WriteOnly | QFile::Text);
  csv.resize(0);

  QTextStream in(&csv);

  QString row = "id_klient" + separator(format) + "typ" + separator(format) + "nazwa" + separator(format) +
          "ulica" + separator(format) + "miejscowosc" + separator(format) + "kod_pocztowy" + separator(format) +
          "tel" + separator(format) + "email" + separator(format) + "fax" + separator(format) +
          "NIP" + separator(format) + "nazwa_banku" + separator(format) + "nr_konta" + separator(format) +
          "bic_swift" + separator(format) + "krs" + separator(format) + "strona_www";


  in << row << endl;

  QVector<BuyerData> buyersXml = dl->buyersSelectAllData();

  for (int i = 0; i < buyersXml.size(); ++i) {

    qDebug() << "insert tic to idCvsBuyer: " << buyersXml.at(i).tic;
    QString buyTic = buyersXml.at(i).tic;
    idCvsBuyer.insert(
        buyTic.remove(QChar('-')),
        QString::number(
            i +
            1)); // according to the tic, because the number is always unique
    // invData.custTic.remove('-'), because of validation choice option. When
    // validation on data is unchecked, users can put tic into app without '-'
    // characters

      QString next_row = QString::number(i + 1) + separator(format) + preventNull(buyersXml.at(i).type) + separator(format) + preventNull(buyersXml.at(i).name) + separator(format) + preventNull(buyersXml.at(i).address)
              + separator(format) + preventNull(buyersXml.at(i).place) + separator(format) + preventNull(buyersXml.at(i).code) + separator(format) + preventNull(buyersXml.at(i).phone)  + separator(format) + preventNull(buyersXml.at(i).email)
                  + separator(format) + preventNull(buyersXml.at(i).fax) + separator(format) + preventNull(buyersXml.at(i).tic) + separator(format) + preventNull(buyersXml.at(i).bank) + separator(format) + preventNull(buyersXml.at(i).account)
                  + separator(format) + preventNull(buyersXml.at(i).swift) + separator(format) + preventNull(buyersXml.at(i).krs) + separator(format) + preventNull(buyersXml.at(i).www);

    in << next_row << endl;
  }

  csv.close();
}


void CsvExport::createProductsCsvFiles(QString format) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  if (!idCvsProducts.isEmpty())
    idCvsProducts.clear();

  QString checkSlashPath = ui->directoryLineEdit->text();
  if (!checkSlashPath.endsWith('/'))
    checkSlashPath += '/';
  QFile csv(checkSlashPath + "/produkty_goods.csv");
  qDebug() << "Products csv path: " << csv.fileName();
  csv.open(QFile::WriteOnly | QFile::Text);
  csv.resize(0);

  QTextStream in(&csv);

   QString row = "id_produkt" + separator(format) + "typ" + separator(format) +
           "nazwa" + separator(format) + "vat" + separator(format) +
           "opis" + separator(format) + "kod" + separator(format) +
           "pkwiu" + separator(format) + "jednostka" + separator(format) +
           "netto1" + separator(format) + "netto2" + separator(format) +
          "netto3" + separator(format) + "netto4";

  in << row << endl;

  QVector<ProductData> productsXml = dl->productsSelectAllData();

  for (int i = 0; i < productsXml.size(); ++i) {


    if (!productsXml.at(i).code.isEmpty() && !productsXml.at(i).code.isNull()) {

      idCvsProducts.insert(productsXml.at(i).code, QString::number(i + 1));
      qDebug() << "productsXml.at(i).code: " << productsXml.at(i).code;
      qDebug() << "idCvsProducts.count(): " << idCvsProducts.count();

    } else {

      idCvsProducts.insert(
          productsXml.at(i).name,
          QString::number(
              i + 1)); // sometimes there is no code given for some product
      qDebug() << "productsXml.at(i).name: " << productsXml.at(i).name;
      qDebug() << "idCvsProducts.count(): " << idCvsProducts.count();

    }

    QString next_row = QString::number(i + 1) + separator(format) + preventNull(productsXml.at(i).type) + separator(format) + preventNull(productsXml.at(i).name) + separator(format) + preventNull(QString::number(productsXml.at(i).vat))
                  + separator(format) + preventNull(productsXml.at(i).desc) + separator(format) + preventNull(productsXml.at(i).code) + separator(format) + preventNull(productsXml.at(i).pkwiu) + separator(format) + preventNull(productsXml.at(i).quanType)
                  + separator(format) + preventNull(sett().numberToString(productsXml.at(i).prices[0], 'f', 2)) + separator(format) + preventNull(sett().numberToString(productsXml.at(i).prices[1], 'f', 2)) + separator(format) + preventNull(sett().numberToString(productsXml.at(i).prices[2], 'f', 2))
                  + separator(format) + preventNull(sett().numberToString(productsXml.at(i).prices[3], 'f', 2));

    in << next_row << endl;
  }

  csv.close();
}



void CsvExport::createSellersCsvFiles(QString format) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  if (!idCvsSeller.isEmpty())
    idCvsSeller.clear();

  QString checkSlashPath = ui->directoryLineEdit->text();
  if (!checkSlashPath.endsWith('/'))
    checkSlashPath += '/';
  QFile csv(checkSlashPath + "/sprzedawcy_sellers.csv");
  qDebug() << "Sellers csv path: " << csv.fileName();
  csv.open(QFile::WriteOnly | QFile::Text);
  csv.resize(0);

  QSettings settings("elinux", "user");

  QTextStream in(&csv);

  QString row = "id_sprzedawca" + separator(format) + "nazwa"+ separator(format) + "adres"+ separator(format) + "miejscowosc"+ separator(format) + "kod_pocztowy"+ separator(format) + "oddzial"+ separator(format) + "NIP"+ separator(format) +
          "REGON" + separator(format) + "KRS" + separator(format) + "nazwa_banku" + separator(format) + "nr_konta" + separator(format) + "SWIFT_BIC" + separator(format) + "tel" + separator(format) + "fax" + separator(format) + "email" +
            separator(format) + "www";

  in << row << endl;

  idCvsSeller.insert(
      preventNull(settings.value("address").toString()),
      QString::number(
          1)); // address is the best choice, if there are other branches

  QString next_row = QString::number(1) + separator(format) + preventNull(settings.value("name").toString()) + separator(format) + preventNull(settings.value("address").toString()) + separator(format) + preventNull(settings.value("city").toString())
                + separator(format) + preventNull(settings.value("zip").toString()) + separator(format) + "glowny" + separator(format) + preventNull(settings.value("tic").toString()) + separator(format) + preventNull(settings.value("regon").toString())
                + separator(format) + preventNull(settings.value("krs").toString()) + separator(format) + preventNull(settings.value("bank").toString()) + separator(format) + preventNull(settings.value("account").toString())
                + separator(format) + preventNull(settings.value("swift").toString()) + separator(format) + preventNull(settings.value("phone").toString())
                + separator(format) + preventNull(settings.value("fax").toString()) + separator(format) + preventNull(settings.value("email").toString()) + separator(format) + preventNull(settings.value("website").toString());

  in << next_row << endl;

  for (int i = 1; i < settings.value("sellerCount").toInt(); ++i) {

    QSettings setts("elinux", "user");
    setts.beginGroup("seller" + QString::number(i));

    idCvsSeller.insert(preventNull(setts.value("address").toString()), QString::number(i + 1)); // address is the best
                                                         // choice, if there are
                                                         // other branches
                                                         // (unique value is
                                                         // needed)

     QString next_row = QString::number(i + 1) + separator(format) + preventNull(setts.value("name").toString()) + separator(format) + preventNull(setts.value("address").toString()) + separator(format) +
                 preventNull(setts.value("city").toString()) + separator(format) + preventNull(setts.value("zip").toString()) + separator(format) + "poboczny" + separator(format) + preventNull(setts.value("tic").toString()) + separator(format) +
                 preventNull(setts.value("regon").toString()) + separator(format) + preventNull(setts.value("krs").toString()) + separator(format) + preventNull(setts.value("bank").toString()) + separator(format) +
                 preventNull(setts.value("account").toString()) + separator(format) + preventNull(setts.value("swift").toString()) + separator(format) +
                 preventNull(setts.value("phone").toString()) + separator(format) + preventNull(setts.value("fax").toString()) + separator(format) + preventNull(setts.value("email").toString()) + separator(format) + preventNull(setts.value("website").toString());

    in << next_row << endl;
    setts.endGroup();
  }

  settings.endGroup();
  csv.close();
}


void CsvExport::createInvoicesCsvFiles(QString format, QDate from, QDate to) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  if (!idCvsInvoices.isEmpty())
    idCvsInvoices.clear();

  QString checkSlashPath = ui->directoryLineEdit->text();
  if (!checkSlashPath.endsWith('/'))
    checkSlashPath += '/';
  QFile csv(checkSlashPath + "/faktury_invoices.csv");
  csv.open(QFile::WriteOnly | QFile::Text);
  csv.resize(0);

  QTextStream in(&csv);

  QString row = "id_faktura" + separator(format) + "typ,data_sprzedazy" + separator(format) + "data_duplikatu" + separator(format) + "data_wystawienia" + separator(format) + "data_zaplaty"
           + separator(format) + "id_klient" + separator(format) + "id_sprzedawca" + separator(format) + "id_produkt1"
           + separator(format) + "id_produkt2" + separator(format) + "id_produkt3" + separator(format) + "id_produkt4" + separator(format) + "ilosc1" + separator(format) + "netto1"
           + separator(format) + "brutto1" + separator(format) + "ilosc2" + separator(format) + "netto2" + separator(format) + "brutto2" + separator(format) + "ilosc3"
           + separator(format) + "netto3" + separator(format) + "brutto3" + separator(format) + "ilosc4" + separator(format) + "netto4" + separator(format) + "brutto4"
           + separator(format) + "sposob_platnosci" + separator(format) + "waluta";

  in << row << endl;

  QVector<InvoiceData> invoicesXml = dl->invoiceSelectAllData(from, to);

  for (int i = 0; i < invoicesXml.size(); ++i) {
    InvoiceData invData = dl->invoiceSelectData(
        invoicesXml.at(i).id, getInvoiceTypeFullName(invoicesXml.at(i).type),
        true);
    QString type = preventNull(invoicesXml.at(i).type);
    QString sellDate = preventNull(invData.sellingDate.toString(sett().getDateFormat()));
    QString prodDate = preventNull(invData.productDate.toString(sett().getDateFormat()));
    QString duplDate = preventNull(invData.duplDate.toString(sett().getDateFormat()));
    QString payDate = preventNull(invData.liabDate.toString(sett().getDateFormat()));
    QString id_customer = (invData.custTic.remove('-') != "")
                              ? idCvsBuyer[invData.custTic.remove('-')]
                              : "null";
    // invData.custTic.remove('-'), because of validation choice option. When
    // validation on data is unchecked, users can put tic into app without '-'
    // characters

    qDebug() << "invData.custTic: " << invData.custTic;
    qDebug() << "invData.sellerAddress: " << invData.sellerAddress;
    QString id_seller = (invData.sellerAddress != "")
                            ? idCvsSeller[invData.sellerAddress]
                            : "null";

    QStringList id_products = QStringList();

    QString quantity1 = QString();
    QString nett1 = QString();
    QString gross1 = QString();
    QString quantity2 = QString();
    QString nett2 = QString();
    QString gross2 = QString();
    QString quantity3 = QString();
    QString nett3 = QString();
    QString gross3 = QString();
    QString quantity4 = QString();
    QString nett4 = QString();
    QString gross4 = QString();

    qDebug() << "invData.products.count(): "
             << QString::number(invData.products.count());
    for (int k = 0; k < invData.products.count(); k++) {
      qDebug() << "idCvsProducts[invData.products[k].code]: "
               << idCvsProducts[invData.products[k].code];
      qDebug() << "idCvsProducts[invData.products[k].name]: "
               << idCvsProducts[invData.products[k].name];
      qDebug() << "invData.products[k].code: " << invData.products[k].code;
      qDebug() << "invData.products[k].name: " << invData.products[k].name;
      if (idCvsProducts[invData.products[k].code] != "") {
        qDebug() << "id_products for code: "
                 << idCvsProducts[invData.products[k].code];

        id_products << preventNull(idCvsProducts[invData.products[k].code]);

      } else {
        qDebug() << "id_products for name: "
                 << idCvsProducts[invData.products[k].name];

        id_products << preventNull(idCvsProducts[invData.products[k].name]);
      }

      if (k == 0) {
        quantity1 = sett().numberToString(invData.products[k].quantity, 'f', 2);
        nett1 = sett().numberToString(invData.products[k].nett, 'f', 2);
        gross1 = sett().numberToString(invData.products[k].gross, 'f', 2);
      }
      if (k == 1) {
        quantity2 = sett().numberToString(invData.products[k].quantity, 'f', 2);
        nett2 = sett().numberToString(invData.products[k].nett, 'f', 2);
        gross2 = sett().numberToString(invData.products[k].gross, 'f', 2);
      }
      if (k == 2) {
        quantity3 = sett().numberToString(invData.products[k].quantity, 'f', 2);
        nett3 = sett().numberToString(invData.products[k].nett, 'f', 2);
        gross3 = sett().numberToString(invData.products[k].gross, 'f', 2);
      }
      if (k == 3) {
        quantity4 = sett().numberToString(invData.products[k].quantity, 'f', 2);
        nett4 = sett().numberToString(invData.products[k].nett, 'f', 2);
        gross4 = sett().numberToString(invData.products[k].gross, 'f', 2);
      }

      if (k == invData.products.count() - 1) { // if we are at the end of loop
        if (k < 3) { // if number of last transaction was less than 3
          for (int j = 4 - (3 - k); j < 4;
               j++) { // we want fill values with "null", only if there aren't 4
                      // transaction until now
            id_products << "null"; // we have now empty values for values taken
                                   // from last transaction number to number 4
            qDebug() << "id_products for null: null";
          }
        }
      }
    }

    if (quantity1.isEmpty() && nett1.isEmpty() && gross1.isEmpty()) {
      quantity1 = "null";
      nett1 = "null";
      gross1 = "null";
    }
    if (quantity2.isEmpty() && nett2.isEmpty() && gross2.isEmpty()) {
      quantity2 = "null";
      nett2 = "null";
      gross2 = "null";
    }
    if (quantity3.isEmpty() && nett3.isEmpty() && gross3.isEmpty()) {
      quantity3 = "null";
      nett3 = "null";
      gross3 = "null";
    }
    if (quantity4.isEmpty() && nett4.isEmpty() && gross4.isEmpty()) {
      quantity4 = "null";
      nett4 = "null";
      gross4 = "null";
    }

    QString paymentMethod =
        (!invData.paymentType.isEmpty() && !invData.paymentType.isNull())
            ? invData.paymentType
            : "null";
    QString currency =
        (!invData.currencyType.isEmpty() && !invData.currencyType.isNull())
            ? invData.currencyType
            : "null";

    idCvsInvoices.insert(
        invoicesXml.at(i).id,
        QString::number(i + 1)); // because name of filename is always unique

    QString next_row =
          QString::number(i + 1) + separator(format) + type + separator(format) + sellDate + separator(format) +
          duplDate + separator(format) + prodDate + separator(format) + payDate + separator(format) + id_customer + separator(format) +
          id_seller + separator(format) + id_products.at(0) + separator(format) + id_products.at(1) + separator(format) +
          id_products.at(2) + separator(format) + id_products.at(3) + separator(format) + quantity1 + separator(format) +
          nett1 + separator(format) + gross1 + separator(format) + quantity2 + separator(format) + nett2 + separator(format) + gross2
           + separator(format) + quantity3 + separator(format) + nett3 + separator(format) + gross3 + separator(format) + quantity4 + separator(format) +
          nett4 + separator(format) + gross4 + separator(format) + paymentMethod + separator(format) + currency;

    in << next_row << endl;
  }

  csv.close();
}


void CsvExport::createWareCsvFiles(QString format, QDate from, QDate to) {

  if (!idCvsWarehouses.isEmpty())
    idCvsWarehouses.clear();

  QString checkSlashPath = ui->directoryLineEdit->text();
  if (!checkSlashPath.endsWith('/'))
    checkSlashPath += '/';
  QFile csv(checkSlashPath + "/magazyny_warehouses.csv");
  csv.open(QFile::WriteOnly | QFile::Text);
  csv.resize(0);

  QTextStream in(&csv);

  QString row = "id_magazyn" + separator(format) + "typ" + separator(format) + "data_sprzedazy" + separator(format) + "data_duplikatu" + separator(format) + "data_wydania_towaru"
           + separator(format) + "data_przyjecia_towaru" + separator(format) + "miejsce_odbioru_towaru" + separator(format) + "miejsce_wydania_towaru"
           + separator(format) + "dzial_kosztu" + separator(format) + "id_klient" + separator(format) + "id_sprzedawca" + separator(format) + "id_produkt1" + separator(format) + "id_produkt2" + separator(format) + "id_"
          "produkt3" + separator(format) + "id_produkt4" + separator(format) + "ilosc1" + separator(format) + "netto1" + separator(format) + "wydana_ilosc1" + separator(format) + "wymagana_ilosc1"
           + separator(format) + "ilosc2" + separator(format) + "netto2" + separator(format) + "wydana_ilosc2" + separator(format) + "wymagana_ilosc2" + separator(format) + "ilosc3" + separator(format) + "netto3" + separator(format) + "wydana_"
          "ilosc3" + separator(format) + "wymagana_ilosc3" + separator(format) + "ilosc4" + separator(format) + "netto4" + separator(format) + "wydana_ilosc4" + separator(format) + "wymagana_ilosc4"
          + separator(format) + "sposob_platnosci";

  in << row << endl;

  QVector<WarehouseData> wareXml = dl->warehouseSelectAllData(from, to);

  for (int i = 0; i < wareXml.size(); ++i) {

    WarehouseData invData = dl->warehouseSelectData(
        wareXml.at(i).id, getInvoiceTypeFullName(wareXml.at(i).type), true);
    QString type = preventNull(wareXml.at(i).type);
    QString sellDate = preventNull(invData.sellingDate.toString(sett().getDateFormat()));
    QString prodDate = preventNull(invData.productDate.toString(sett().getDateFormat()));
    QString duplDate = preventNull(invData.duplDate.toString(sett().getDateFormat()));
    QString giveDate = preventNull(invData.goodFromDate.toString(sett().getDateFormat()));
    QString takeDate = preventNull(invData.goodToDate.toString(sett().getDateFormat()));
    QString givePlace = preventNull(invData.goodFromPlace);
    QString takePlace = preventNull(invData.goodToPlace);
    QString departCost = preventNull(invData.departmentCost);
    QString id_customer = (invData.custTic.remove('-') != "")
                              ? idCvsBuyer[invData.custTic.remove('-')]
                              : "null";
    // invData.custTic.remove('-'), because of validation choice option. When
    // validation on data is unchecked, users can put tic into app without '-'
    // characters

    qDebug() << "invData.custTic: " << invData.custTic;
    qDebug() << "invData.sellerAddress: " << invData.sellerAddress;
    QString id_seller = (invData.sellerAddress != "")
                            ? idCvsSeller[invData.sellerAddress]
                            : "null";
    QStringList id_products = QStringList();

    QString quantity1 = QString();
    QString nett1 = QString();
    QString givAm1 = QString();
    QString reqAm1 = QString();
    QString quantity2 = QString();
    QString nett2 = QString();
    QString givAm2 = QString();
    QString reqAm2 = QString();
    QString quantity3 = QString();
    QString nett3 = QString();
    QString givAm3 = QString();
    QString reqAm3 = QString();
    QString quantity4 = QString();
    QString nett4 = QString();
    QString givAm4 = QString();
    QString reqAm4 = QString();

    qDebug() << "invData.products.count(): "
             << QString::number(invData.products.count());

    for (int k = 0; k < invData.products.count(); k++) {

      qDebug() << "idCvsProducts[invData.products[k].code]: "
               << idCvsProducts[invData.products[k].code];
      qDebug() << "idCvsProducts[invData.products[k].name]: "
               << idCvsProducts[invData.products[k].name];
      qDebug() << "invData.products[k].code: " << invData.products[k].code;
      qDebug() << "invData.products[k].name: " << invData.products[k].name;

      if (idCvsProducts[invData.products[k].code] != "") {

        qDebug() << "id_products for code: "
                 << idCvsProducts[invData.products[k].code];

        id_products << preventNull(idCvsProducts[invData.products[k].code]);

      } else {
        qDebug() << "id_products for name: "
                 << idCvsProducts[invData.products[k].name];

        id_products << preventNull(idCvsProducts[invData.products[k].name]);
      }

      if (k == 0) {
        quantity1 = sett().numberToString(invData.products[k].quantity, 'f', 2);
        nett1 = sett().numberToString(invData.products[k].nett, 'f', 2);
        givAm1 =
            sett().numberToString(invData.products[k].givedOutAmount, 'f', 2);
        reqAm1 =
            sett().numberToString(invData.products[k].requiredAmount, 'f', 2);
      }
      if (k == 1) {
        quantity2 = sett().numberToString(invData.products[k].quantity, 'f', 2);
        nett2 = sett().numberToString(invData.products[k].nett, 'f', 2);
        givAm2 =
            sett().numberToString(invData.products[k].givedOutAmount, 'f', 2);
        reqAm2 =
            sett().numberToString(invData.products[k].requiredAmount, 'f', 2);
      }
      if (k == 2) {
        quantity3 = sett().numberToString(invData.products[k].quantity, 'f', 2);
        nett3 = sett().numberToString(invData.products[k].nett, 'f', 2);
        givAm3 =
            sett().numberToString(invData.products[k].givedOutAmount, 'f', 2);
        reqAm3 =
            sett().numberToString(invData.products[k].requiredAmount, 'f', 2);
      }
      if (k == 3) {
        quantity4 = sett().numberToString(invData.products[k].quantity, 'f', 2);
        nett4 = sett().numberToString(invData.products[k].nett, 'f', 2);
        givAm4 =
            sett().numberToString(invData.products[k].givedOutAmount, 'f', 2);
        reqAm4 =
            sett().numberToString(invData.products[k].requiredAmount, 'f', 2);
      }

      if (k == invData.products.count() - 1) { // if we are at the end of loop
        if (k < 3) { // if number of last transaction was less than 3
          for (int j = 4 - (3 - k); j < 4;
               j++) { // we want fill values with "null", only if there aren't 4
                      // transaction until now
            id_products << "null"; // we have now empty values for values taken
                                   // from last transaction number to number 4
            qDebug() << "id_products for null: null";
          }
        }
      }
    }

    if (quantity1.isEmpty() && nett1.isEmpty() && givAm1.isEmpty() &&
        reqAm1.isEmpty()) {
      quantity1 = "null";
      nett1 = "null";
      givAm1 = "null";
      reqAm1 = "null";
    }
    if (quantity2.isEmpty() && nett2.isEmpty() && givAm2.isEmpty() &&
        reqAm2.isEmpty()) {
      quantity2 = "null";
      nett2 = "null";
      givAm2 = "null";
      reqAm2 = "null";
    }
    if (quantity3.isEmpty() && nett3.isEmpty() && givAm3.isEmpty() &&
        reqAm3.isEmpty()) {
      quantity3 = "null";
      nett3 = "null";
      givAm3 = "null";
      reqAm3 = "null";
    }
    if (quantity4.isEmpty() && nett4.isEmpty() && givAm4.isEmpty() &&
        reqAm4.isEmpty()) {
      quantity4 = "null";
      nett4 = "null";
      givAm4 = "null";
      reqAm4 = "null";
    }

    QString paymentMethod = preventNull(invData.paymentType);

    idCvsWarehouses.insert(
        wareXml.at(i).id,
        QString::number(i + 1)); // because name of filename is always unique

    QString next_row = QString::number(i + 1) + separator(format) + type + separator(format) + sellDate + separator(format) +
                 duplDate + separator(format) + prodDate + separator(format) + giveDate + separator(format) + takeDate
                  + separator(format) + givePlace + separator(format) + takePlace + separator(format) + departCost + separator(format) +
                 id_customer + separator(format) + id_seller + separator(format) + id_products.at(0) + separator(format) +
                 id_products.at(1) + separator(format) + id_products.at(2) + separator(format) +
                 id_products.at(3) + separator(format) + quantity1 + separator(format) + nett1 + separator(format) +
                 givAm1 + separator(format) + reqAm1 + separator(format) + quantity2 + separator(format) + nett2 + separator(format) +
                 givAm2 + separator(format) + reqAm2 + separator(format) + quantity3 + separator(format) + nett3 + separator(format) +
                 givAm3 + separator(format) + reqAm3 + separator(format) + quantity4 + separator(format) + nett4 + separator(format) +
                 givAm4 + separator(format) + reqAm4 + separator(format) + paymentMethod;

    in << next_row << endl;
  }

  csv.close();
}


int CsvExport::getInvoiceTypeFullName(QString invoiceType) {

  if (invoiceType == "FVAT")
    return 1;
  else if (invoiceType == "FPro")
    return 2;
  else if (invoiceType == "korekta")
    return 3;
  else if (invoiceType == "FBrutto")
    return 4;
  else if (invoiceType == "kbrutto")
    return 5;
  else if (invoiceType == "rachunek")
    return 6;
  else if (invoiceType == "duplikat")
    return 7;
  else if (invoiceType == "RR")
    return 8;
  else if (invoiceType == "RW")
    return 10;
  else
    return 1;
}

