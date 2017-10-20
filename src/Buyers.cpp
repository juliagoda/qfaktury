
#include "Buyers.h"
#include "IDataLayer.h"
#include "Validations.h"
<<<<<<< HEAD
=======

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMovie>

#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
>>>>>>> testing

/** Constructor
 */

Buyers::Buyers(QWidget *parent, int mode, IDataLayer *dl) : QDialog(parent) {
<<<<<<< HEAD

    qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

=======

  qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

>>>>>>> testing
  workingMode = mode;
  dataLayer = dl;
  setupUi(this);
  init();
}

/** init()
 */

void Buyers::init() {

<<<<<<< HEAD
    qDebug() << __FILE__ << __LINE__ << __FUNCTION__;
=======
  qDebug() << __FILE__ << __LINE__ << __FUNCTION__;
>>>>>>> testing

  allNames = dataLayer->buyersGetFirmList();

  // connects
  connect(okButton, SIGNAL(clicked()), this, SLOT(okClick()));
  connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
  connect(typeCombo, SIGNAL(currentIndexChanged(int)), this,
          SLOT(requiredTic(int)));
}

const QString Buyers::getRetBuyer() {
<<<<<<< HEAD
    qDebug() << __FILE__ << __LINE__ << __FUNCTION__;
    return ret;
=======

  qDebug() << __FILE__ << __LINE__ << __FUNCTION__;
  return ret;
>>>>>>> testing
}

// --------- SLOTS START --
/** Slot - ok & save
 */

void Buyers::okClick() {

<<<<<<< HEAD
  QStringList list = QStringList()
                     << nameEdit->text() << typeCombo->currentText()
                     << placeEdit->text() << addressEdit->text()
                     << telefonEdit->text() << nipEdit->text()
                     << codeEdit->text() << accountEdit->text()
                     << emailEdit->text() << wwwEdit->text();

=======
  qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

  QStringList list = QStringList()
                     << nameEdit->text() << typeCombo->currentText()
                     << placeEdit->text() << addressEdit->text()
                     << telefonEdit->text() << nipEdit->text()
                     << codeEdit->text() << accountEdit->text()
                     << emailEdit->text() << wwwEdit->text();

>>>>>>> testing
  if (workingMode == 1) {

    if (updateData()) {

      foreach (QString listEl, list) { ret += isEmpty(listEl) + "|"; }
<<<<<<< HEAD

      accept();
    }

  } else {

    if (insertData()) {

      foreach (QString listEl, list) { ret += isEmpty(listEl) + "|"; }

      accept();
    }
  }
}

void Buyers::requiredTic(int type) {
=======

      accept();
    }

  } else {

    if (insertData()) {

      foreach (QString listEl, list) { ret += isEmpty(listEl) + "|"; }

      accept();
    }
  }
}

void Buyers::requiredTic(int type) {

  qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

>>>>>>> testing
  if (type == 2)
    textLabel2_2->setText(trUtf8("NIP:"));
  else
    textLabel2_2->setText(trUtf8("NIP*:"));

  this->update();
}

// --------- SLOTS END --

//***** DATA access START ****
// load data modification mode

void Buyers::selectData(QString name, int type) {

<<<<<<< HEAD
=======
  qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

>>>>>>> testing
  setWindowTitle(trUtf8("Edytuj kontrahenta"));
  getData(dataLayer->buyersSelectData(name, type));
  typeCombo->setCurrentIndex(type);
  typeCombo->setEnabled(false);

  if (typeCombo->currentIndex() == 2) {
    textLabel2_2->setText(trUtf8("NIP:"));
  } else {
    textLabel2_2->setText(trUtf8("NIP*:"));
  }

  this->update();
}

// new customer insert data
bool Buyers::insertData() {

<<<<<<< HEAD
  bool result = false;
  BuyerData buyerData;

  if ((sett().value("validation").toBool() && validate()) ||
      sett().value("validation").toBool() == false) {

    setData(buyerData);
    result = dataLayer->buyersInsertData(buyerData, typeCombo->currentIndex());
  }

=======
  qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

  bool result = false;
  BuyerData buyerData;

  if ((sett().value("validation").toBool() && validate()) ||
      sett().value("validation").toBool() == false) {

    setData(buyerData);
    result = dataLayer->buyersInsertData(buyerData, typeCombo->currentIndex());
  }

>>>>>>> testing
  return result;
}

// update existing
bool Buyers::updateData() {

<<<<<<< HEAD
  bool result = false;
  BuyerData buyerData;

  if ((sett().value("validation").toBool() && validateUpdated()) ||
      sett().value("validation").toBool() == false) {

    setData(buyerData);

    result = dataLayer->buyersUpdateData(buyerData, typeCombo->currentIndex(),
                                         nameEdit->text());
  }

  if (typeCombo->currentIndex() == 2) {
    textLabel2_2->setText(trUtf8("NIP:"));
  } else {
    textLabel2_2->setText(trUtf8("NIP*:"));
  }

  this->update();

=======
  qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

  bool result = false;
  BuyerData buyerData;

  if ((sett().value("validation").toBool() && validateUpdated()) ||
      sett().value("validation").toBool() == false) {

    setData(buyerData);

    result = dataLayer->buyersUpdateData(buyerData, typeCombo->currentIndex(),
                                         nameEdit->text());
  }

  if (typeCombo->currentIndex() == 2) {
    textLabel2_2->setText(trUtf8("NIP:"));
  } else {
    textLabel2_2->setText(trUtf8("NIP*:"));
  }

  this->update();

>>>>>>> testing
  return result;
}
//***** DATA access END ****

//********************** VALIDATION START ************************

/** Validate form
 *  Don't save when no
 *  "name", "city", "street", "tic"
 */

/** validate()
 */

bool Buyers::validate() {

<<<<<<< HEAD
=======
  qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

>>>>>>> testing
  if (Validations::instance()->isEmptyField(nameEdit->text(),
                                            textLabel1->text()))
    return false;
  if (Validations::instance()->isEmptyField(placeEdit->text(),
                                            textLabel3->text()))
    return false;

  if (!Validations::instance()->isEmptyField(codeEdit->text(),
                                             textLabel4->text())) {
    if (!Validations::instance()->validateZip(codeEdit->text()))
      return false;
  } else {
    return false;
  }

  if (Validations::instance()->isEmptyField(addressEdit->text(),
                                            textLabel2->text()))
    return false;

  if (typeCombo->currentIndex() == 2) {

    textLabel2_2->setText(trUtf8("NIP:"));
    this->update();

    if (!nipEdit->text().isEmpty()) {

      if (!Validations::instance()->validateNIP(nipEdit->text()))
        return false;
      if (!Validations::instance()->checkSumNIP(nipEdit->text()))
        return false;
    }

  } else {

    textLabel2_2->setText(trUtf8("NIP*:"));
    this->update();

    if (!Validations::instance()->isEmptyField(nipEdit->text(),
                                               textLabel2_2->text())) {

      if (!Validations::instance()->validateNIP(nipEdit->text()))
        return false;
      if (!Validations::instance()->checkSumNIP(nipEdit->text()))
        return false;

    } else {

      return false;
    }
  }

  if (!accountEdit->text().isEmpty()) {
    if (!Validations::instance()->validateAccount(accountEdit->text()))
      return false;
    if (!Validations::instance()->checkSumAccount(accountEdit->text()))
      return false;
  }

  if (!telefonEdit->text().isEmpty()) {
    if (!Validations::instance()->validateTel(telefonEdit->text()))
      return false;
  }

  if (!emailEdit->text().isEmpty()) {
    if (!Validations::instance()->validateEmail(emailEdit->text()))
      return false;
  }

  if (!wwwEdit->text().isEmpty()) {
    if (!Validations::instance()->validateWebsite(wwwEdit->text()))
      return false;
  }

  if (allNames.indexOf(QRegExp(nameEdit->text(), Qt::CaseSensitive,
                               QRegExp::FixedString)) != -1) {
    QMessageBox::critical(0, "QFaktury",
                          trUtf8("Kontrahent nie moze zostać dodany, ponieważ "
                                 "istnieje już kontrahent o tej nazwie."));
    return false;
  }

  return true;
}

bool Buyers::validateUpdated() {
<<<<<<< HEAD
=======

  qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

>>>>>>> testing
  if (Validations::instance()->isEmptyField(nameEdit->text(),
                                            textLabel1->text()))
    return false;
  if (Validations::instance()->isEmptyField(placeEdit->text(),
                                            textLabel3->text()))
    return false;

  if (!Validations::instance()->isEmptyField(codeEdit->text(),
                                             textLabel4->text())) {
    if (!Validations::instance()->validateZip(codeEdit->text()))
      return false;
  } else {
    return false;
  }

  if (Validations::instance()->isEmptyField(addressEdit->text(),
                                            textLabel2->text()))
    return false;

  if (!Validations::instance()->isEmptyField(nipEdit->text(),
                                             textLabel2_2->text())) {
    if (!Validations::instance()->validateNIP(nipEdit->text()))
      return false;
    if (!Validations::instance()->checkSumNIP(nipEdit->text()))
      return false;
  } else {
    return false;
  }

  if (!accountEdit->text().isEmpty()) {
    if (!Validations::instance()->validateAccount(accountEdit->text()))
      return false;
    if (!Validations::instance()->checkSumAccount(accountEdit->text()))
      return false;
  }

  if (!telefonEdit->text().isEmpty()) {
    if (!Validations::instance()->validateTel(telefonEdit->text()))
      return false;
  }

  if (!emailEdit->text().isEmpty()) {
    if (!Validations::instance()->validateEmail(emailEdit->text()))
      return false;
  }

  if (!wwwEdit->text().isEmpty()) {
    if (!Validations::instance()->validateWebsite(wwwEdit->text()))
      return false;
  }

  return true;
}

//********************** VALIDATION  END ************************

//********************** DATA METHODS START *********************
/** Loads data from labels into Data object
 */

void Buyers::setData(BuyerData &buyerData) {

<<<<<<< HEAD
=======
  qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

>>>>>>> testing
  buyerData.name = nameEdit->text();
  buyerData.place = placeEdit->text();
  buyerData.code = codeEdit->text();
  buyerData.address = addressEdit->text();
  buyerData.tic = nipEdit->text();
  buyerData.account = accountEdit->text();
  buyerData.phone = telefonEdit->text();
  buyerData.email = emailEdit->text();
  buyerData.www = wwwEdit->text();
}

/** Load details
 */

void Buyers::getData(BuyerData buyerData) {

<<<<<<< HEAD
=======
  qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

>>>>>>> testing
  nameEdit->setText(buyerData.name);
  placeEdit->setText(buyerData.place);
  codeEdit->setText(buyerData.code);
  addressEdit->setText(buyerData.address);
  nipEdit->setText(buyerData.tic);
  accountEdit->setText(buyerData.account);
  telefonEdit->setText(buyerData.phone);
  emailEdit->setText(buyerData.email);
  wwwEdit->setText(buyerData.www);
}

// executes shell script for preparation before connection to GUS
bool Buyers::checkGusPath() {
  qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

  const char *homedir;

  if ((homedir = getenv("HOME")) == NULL) {
    homedir = getpwuid(getuid())->pw_dir;
  }

  const char *addGusPath1 =
      "sh /usr/share/qfaktury/src/GusApi/php-dependencies.sh \"";
  const char *br = "\"";

  char *RutaFinal1 =
      new char[strlen(addGusPath1) + strlen(homedir) + strlen(br) + 1];
  strcpy(RutaFinal1, addGusPath1);
  strcat(RutaFinal1, homedir);
  strcat(RutaFinal1, br);

  printf(RutaFinal1);

  if (system(RutaFinal1) == 0)
    return true;

  return false;
}

// connects to GUS data thanks to PHP scripts, that saves result into json file
bool Buyers::connectGUS() {
  if (QFile(sett().getGUSDir() + "/result.json").exists())
    QFile::resize(sett().getGUSDir() + "/result.json", 0);

  qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

  const char *firstPart =
      "php -f /usr/share/qfaktury/src/GusApi/getFromNip.php ";
  const char *secondPart =
      nipEdit->text().remove(QChar('-')).toStdString().c_str();

  char *RutaFinal = new char[strlen(firstPart) + strlen(secondPart) + 1];
  strcpy(RutaFinal, firstPart);
  strcat(RutaFinal, secondPart);

  if (system(RutaFinal) == 0)
    return true;

  return false;
}

// container function for various raport types from GUS
void Buyers::RaportTypesContainer(QStringList &listJsonNodes,
                                  QJsonObject &item) {

  qDebug() << QString("QJsonObject[dane] of value ") << listJsonNodes.at(0)
           << QString(": ") << item[listJsonNodes.at(0)];
  QJsonValue name = item[listJsonNodes.at(0)];
  QString reformed = QString();

  Q_FOREACH (QString ref, name.toString().toLower().split(" ")) {
    if (ref.length() > 1) {
      ref[0] = ref.at(0).toTitleCase();
      reformed += " " + ref;
    } else
      reformed += " " + ref;
  }

  nameEdit->setText(reformed.trimmed());

  /* in case of array get array and convert into string*/
  qDebug() << QString("QJsonObject[dane] of value ") << listJsonNodes.at(1)
           << QString(": ") << item[listJsonNodes.at(1)];
  QJsonValue city = item[listJsonNodes.at(1)];
  placeEdit->setText(city.toString().trimmed());

  qDebug() << QString("QJsonObject[dane] of value ") << listJsonNodes.at(2)
           << QString(" and ") << listJsonNodes.at(3) << QString(": ")
           << item[listJsonNodes.at(2)];
  QJsonValue address = item[listJsonNodes.at(2)];
  QJsonValue companyNumber = item[listJsonNodes.at(3)];
  addressEdit->setText(address.toString().trimmed() + " " +
                       companyNumber.toString().trimmed());

  qDebug() << QString("QJsonObject[dane] of value ") << listJsonNodes.at(4)
           << QString(": ") << item[listJsonNodes.at(4)];
  QJsonValue postalCode = item[listJsonNodes.at(4)];
  codeEdit->setText(postalCode.toString().insert(2, '-').trimmed());

  qDebug() << QString("QJsonObject[dane] of value ") << listJsonNodes.at(5)
           << QString(": ") << item[listJsonNodes.at(5)];
  QJsonValue tel = item[listJsonNodes.at(5)];
  telefonEdit->setText("+48" + tel.toString().trimmed());

  qDebug() << QString("QJsonObject[dane] of value ") << listJsonNodes.at(6)
           << QString(": ") << item[listJsonNodes.at(6)];
  QJsonValue email = item[listJsonNodes.at(6)];
  emailEdit->setText(email.toString().toLower().trimmed());

  qDebug() << QString("QJsonObject[dane] of value ") << listJsonNodes.at(7)
           << QString(": ") << item[listJsonNodes.at(7)];
  QJsonValue site = item[listJsonNodes.at(7)];
  wwwEdit->setText(site.toString().toLower().trimmed());
}

// sets data into QLineEdits from JSON file, which has informations about last
// buyer taken from GUS
void Buyers::setDataFromGUS() {

  qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

  QFile file;
  file.setFileName(QDir::homePath() +
                   "/.local/share/data/elinux/gus/result.json");
  file.open(QIODevice::ReadOnly | QIODevice::Text);
  QString val = file.readAll();
  file.close();

  QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
  QJsonObject sett2 = d.object();
  QJsonValue value = sett2.value(QString("dane"));
  QJsonObject item = value.toObject();

  QStringList depNodes = QStringList() << "praw_nazwa"
                                       << "praw_adSiedzMiejscowosc_Nazwa"
                                       << "praw_adSiedzUlica_Nazwa"
                                       << "praw_adSiedzNumerNieruchomosci"
                                       << "praw_adSiedzKodPocztowy"
                                       << "praw_numerTelefonu"
                                       << "praw_adresEmail"
                                       << "praw_adresStronyinternetowej";

  QStringList persNodes = QStringList() << "fiz_nazwa"
                                        << "fiz_adSiedzMiejscowosc_Nazwa"
                                        << "fiz_adSiedzUlica_Nazwa"
                                        << "fiz_adSiedzNumerNieruchomosci"
                                        << "fiz_adSiedzKodPocztowy"
                                        << "fiz_numerTelefonu"
                                        << "fiz_adresEmail"
                                        << "fiz_adresStronyinternetowej";

  if (item["praw_nazwa"].isString()) {

    RaportTypesContainer(depNodes, item);

  } else if (item["fiz_nazwa"].isString()) {

    RaportTypesContainer(persNodes, item);

  } else {

    QMessageBox::warning(this, "Informacje z GUS",
                         "Nie było możliwe pobranie danych z Głównego Urzędu "
                         "Statystycznego. Sprawdź, czy podany numer NIP jest "
                         "poprawny.");
  }
}

// creates file in json format for php composer, because copying from app path
// changes permission of place to root
void Buyers::createComposerJson(QString path, QString filename) {

  QJsonObject recordObject;
  recordObject.insert("name", QJsonValue::fromVariant("gusapi/gusapi"));
  recordObject.insert("description",
                      QJsonValue::fromVariant("Gus Api Library for PHP"));
  recordObject.insert("type", QJsonValue::fromVariant("library"));
  recordObject.insert("license", QJsonValue::fromVariant("LGPL-2.1"));

  QJsonArray keywordsArray;
  keywordsArray.push_back("nip");
  keywordsArray.push_back("regon");
  keywordsArray.push_back("krs");
  keywordsArray.push_back("api");
  keywordsArray.push_back("soap");
  keywordsArray.push_back("library");
  keywordsArray.push_back("GUS");
  keywordsArray.push_back("CEGID");
  recordObject.insert("keywords", keywordsArray);

  QJsonArray authorsArray;
  QJsonObject recordObject2;
  recordObject2.insert("name", "Janusz Żukowicz");
  recordObject2.insert("email", "john_zuk@wp.pl");
  authorsArray.push_back(recordObject2);
  recordObject.insert("authors", authorsArray);

  QJsonObject recordObject3;
  recordObject3.insert("php", ">=5.4");
  recordObject.insert("require", recordObject3);

  QJsonObject recordObject4;
  recordObject4.insert("phpunit/phpunit", "4.6.6");
  recordObject.insert("require-dev", recordObject4);

  QJsonObject gusapi;
  gusapi.insert("GusApi\\", "/usr/share/qfaktury/src/GusApi/src/GusApi/");
  QJsonObject psr;
  psr.insert("psr-4", gusapi);

  recordObject.insert("autoload", psr);

  QJsonDocument doc(recordObject);
  //  qDebug() << doc.toJson();

  QFile composerFile(path + "/" + filename);
  composerFile.open(QFile::WriteOnly);
  composerFile.write(doc.toJson());
}

//********************** DATA METHODS END *********************

// helper method which sets "-" in input forms

QString Buyers::isEmpty(QString in) {

<<<<<<< HEAD
=======
  qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

>>>>>>> testing
  if (in == "")
    return "-";
  return in;
}
<<<<<<< HEAD
=======

// signal for connection to GUS and update data in QLineEdits
void Buyers::on_gusBtn_clicked() {

  qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

  QLabel *lbl = new QLabel;
  QMovie *movie = new QMovie(":/res/icons/waitForResp.gif");
  lbl->setMovie(movie);
  lbl->resize(300, 30);
  lbl->show();
  movie->start();
  gusLayout->addWidget(lbl);


  if (nipEdit->text().isEmpty() || nipEdit->text().isNull())
    QMessageBox::warning(
        this, "NIP",
        "Aby skorzystać z funkcji, powinieneś najpierw podać numer NIP");
  else {

    bool firstRunGUS = false;

    if (!QDir(sett().getGUSDir()).exists()) {
      QDir dir;
      dir.mkpath(sett().getGUSDir());
      firstRunGUS = true;
      QMessageBox::information(
          this, "Przygotowanie",
          "Poczekaj chwilę, aż program pobierze i "
          "przygotuje zależności dla korzystania z danych "
          "GUS po raz pierwszy. Może to potrwać do minuty");
    }

    if (!QFile(QDir::homePath() + "/.local/share/data/elinux/gus/composer.json")
             .exists()) {
      createComposerJson(sett().getGUSDir(), QString("composer.json"));
    }

    if (firstRunGUS) {
      if (QMessageBox::warning(this, "Konfiguracja PHP",
                               trUtf8("Czy chcesz przygotować plik php.ini do "
                                      "korzystania z klienta SOAP, aby łączyć "
                                      "się z Głównym Urzędem Statystycznym? "
                                      "Jeśli tego nie zrobisz, powinieneś "
                                      "znaleźć plik php.ini, znaleźć wiersz "
                                      ";extension=soap.so i usunąć średnik. "),
                               trUtf8("Tak"), trUtf8("Nie"), 0, 0, 1) == 0) {

        system("gksudo sh /usr/share/qfaktury/src/GusApi/soap-php.sh");
      }
    }



    if (!QDir(sett().getGUSDir() + "/vendor").exists() ||
        QDir(sett().getGUSDir() + "/vendor").isEmpty())

      if (!checkGusPath()) {
        QMessageBox::warning(this, "I etap",
                             "Program nie mógł przygotować się do skorzystania "
                             "z danych Głównego Urzędu Statystycznego. "
                             "Prawdopdobnie nie masz zainstalowanej paczki "
                             "gksu, podałeś złe hasło autoryzacyjne lub "
                             "odmówiłeś podania hasła dla konfiguracji PHP");
      }

    if (connectGUS()) {
      setDataFromGUS();
    } else {
      QMessageBox::warning(this, "II etap",
                           "Program nie mógł pobrać danych z Głównego "
                           "Urzędu Statystycznego. Prawdopdobnie nie masz "
                           "zainstalowanej paczki php lub brakuje plików w "
                           "ścieżce /usr/share/qfaktury/src/GusApi");
    }

    movie->stop();
    movie->deleteLater();
    lbl->deleteLater();
  }
}
>>>>>>> testing
