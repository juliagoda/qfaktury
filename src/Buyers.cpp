
#include "Buyers.h"
#include "IDataLayer.h"
#include "Validations.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <unistd.h>

/** Constructor
 */

Buyers::Buyers(QWidget *parent, int mode, IDataLayer *dl) : QDialog(parent) {

    qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

  workingMode = mode;
  dataLayer = dl;
  setupUi(this);
  init();
}

/** init()
 */

void Buyers::init() {

    qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

  allNames = dataLayer->buyersGetFirmList();

  // connects
  connect(okButton, SIGNAL(clicked()), this, SLOT(okClick()));
  connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
  connect(typeCombo, SIGNAL(currentIndexChanged(int)), this,
          SLOT(requiredTic(int)));
}

const QString Buyers::getRetBuyer() {

    qDebug() << __FILE__ << __LINE__ << __FUNCTION__;
    return ret;
}

// --------- SLOTS START --
/** Slot - ok & save
 */

void Buyers::okClick() {

    qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

  QStringList list = QStringList()
                     << nameEdit->text() << typeCombo->currentText()
                     << placeEdit->text() << addressEdit->text()
                     << telefonEdit->text() << nipEdit->text()
                     << codeEdit->text() << accountEdit->text()
                     << emailEdit->text() << wwwEdit->text();

  if (workingMode == 1) {

    if (updateData()) {

      foreach (QString listEl, list) { ret += isEmpty(listEl) + "|"; }

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

    qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

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

    qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

  bool result = false;
  BuyerData buyerData;

  if ((sett().value("validation").toBool() && validate()) ||
      sett().value("validation").toBool() == false) {

    setData(buyerData);
    result = dataLayer->buyersInsertData(buyerData, typeCombo->currentIndex());
  }

  return result;
}

// update existing
bool Buyers::updateData() {

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

    qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

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

    qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

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

    qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

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

    qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

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
bool Buyers::checkGusPath()
{
    qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

    const char *homedir;

    if ((homedir = getenv("HOME")) == NULL) {
        homedir = getpwuid(getuid())->pw_dir;
    }

    QDir dir;
    if (!QDir(QDir::homePath() + "/.local/share/data/elinux/gus").exists()) dir.mkpath(QDir::homePath() + "/.local/share/data/elinux/gus");

    const char* sys = "gksudo /usr/share/qfaktury/src/GusApi/dependencies.sh \"";
    const char* ss = "\"";

    char * RutaFinal = new char[strlen(sys) + strlen(homedir) + strlen(ss) + 1];
    strcpy(RutaFinal, sys);
    strcat(RutaFinal, homedir);
    strcat(RutaFinal, ss);

    printf(RutaFinal);

    if (system(RutaFinal) == 0) return true;

    return false;

}

// connects to GUS data thanks to PHP scripts, that saves result into json file
bool Buyers::connectGUS()
{

    qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

    const char* firstPart = "php -f /usr/share/qfaktury/src/GusApi/getFromNip.php ";
    const char* secondPart = nipEdit->text().remove(QChar('-')).toStdString().c_str();

    char * RutaFinal = new char[strlen(firstPart) + strlen(secondPart) + 1];
    strcpy(RutaFinal, firstPart);
    strcat(RutaFinal, secondPart);

    if (system(RutaFinal) == 0) return true;

    return false;

}

// sets data into QLineEdits from JSON file, which has informations about last buyer taken from GUS
void Buyers::setDataFromGUS() {

    qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

          QFile file;
          file.setFileName(QDir::homePath() + "/.local/share/data/elinux/gus/result.json");
          file.open(QIODevice::ReadOnly | QIODevice::Text);
          QString val = file.readAll();
          file.close();

          qWarning() << val;

          QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
          QJsonObject sett2 = d.object();
          QJsonValue value = sett2.value(QString("dane"));
          qWarning() << value;
          QJsonObject item = value.toObject();

          qWarning() << tr("QJsonObject of description: ") << item;

          /* in case of string value get value and convert into string*/
          qWarning() << tr("QJsonObject[dane] of description: ") << item["praw_nazwa"];
          QJsonValue name = item["praw_nazwa"];
          qWarning() << name.toString();
          QString reformed = QString();

          Q_FOREACH(QString ref, name.toString().toLower().split(" ")) {
              if (ref.length() > 1) {
                  ref[0] = ref.at(0).toTitleCase();
                  reformed +=  " " + ref;
              }
              else reformed += " " + ref;
          }

          nameEdit->setText(reformed.trimmed());

          /* in case of array get array and convert into string*/
          qWarning() << tr("QJsonObject[dane] of value: ") << item["praw_adSiedzMiejscowosc_Nazwa"];
          QJsonValue city = item["praw_adSiedzMiejscowosc_Nazwa"];
          qWarning() << city.toString();
          placeEdit->setText(city.toString().trimmed());

          qWarning() << tr("QJsonObject[dane] of value: ") << item["praw_adSiedzUlica_Nazwa"];
          QJsonValue address = item["praw_adSiedzUlica_Nazwa"];
          QJsonValue companyNumber = item["praw_adSiedzNumerNieruchomosci"];
          qWarning() << address.toString();
          addressEdit->setText(address.toString().trimmed() + " " + companyNumber.toString().trimmed());

          qWarning() << tr("QJsonObject[dane] of value: ") << item["praw_adSiedzKodPocztowy"];
          QJsonValue postalCode = item["praw_adSiedzKodPocztowy"];
          qWarning() << postalCode.toString();
          codeEdit->setText(postalCode.toString().insert(2,'-').trimmed());

          qWarning() << tr("QJsonObject[dane] of value: ") << item["praw_numerTelefonu"];
          QJsonValue tel = item["praw_numerTelefonu"];
          qWarning() << tel.toString();
          telefonEdit->setText("+48" + tel.toString().trimmed());

          qWarning() << tr("QJsonObject[dane] of value: ") << item["praw_adresEmail"];
          QJsonValue email = item["praw_adresEmail"];
          qWarning() << email.toString();
          emailEdit->setText(email.toString().toLower().trimmed());

          qWarning() << tr("QJsonObject[dane] of value: ") << item["praw_adresStronyinternetowej"];
          QJsonValue site = item["praw_adresStronyinternetowej"];
          qWarning() << site.toString();
          wwwEdit->setText(site.toString().toLower().trimmed());
}


//********************** DATA METHODS END *********************

// helper method which sets "-" in input forms

QString Buyers::isEmpty(QString in) {

    qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

  if (in == "")
    return "-";
  return in;
}

// signal for connection to GUS and update data in QLineEdits
void Buyers::on_gusBtn_clicked()
{

    qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

    if (nipEdit->text().isEmpty() || nipEdit->text().isNull()) QMessageBox::warning(this, "NIP", "Aby skorzystać z funkcji, powinieneś najpierw podać numer NIP");
    else {
    if (!QDir(QDir::homePath() + "/.local/share/data/elinux/gus").exists() || QDir(QDir::homePath() + "/.local/share/data/elinux/gus").isEmpty()) {
        if (checkGusPath()) {
            QFile(QDir::homePath() + "/.local/share/data/elinux/gus").setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner);
            if (connectGUS()) {
                setDataFromGUS();
            } else {
                QMessageBox::warning(this, "II etap", "Program nie mógł pobrać danych z Głównego Urzędu Statystycznego. Prawdopdobnie nie masz zainstalowanej paczki php lub brakuje plików w ścieżce /usr/share/qfaktury/src/GusApi");
            }
        } else {
            QMessageBox::warning(this, "I etap", "Program nie mógł przygotować się do skorzystania z danych Głównego Urzędu Statystycznego. Prawdopdobnie nie masz zainstalowanej paczki gksu, podałeś złe hasło autoryzacyjne lub odmówiłeś podania hasła");
        }
    }
    else {
        if (connectGUS()) {
            setDataFromGUS();
        } else {
            QMessageBox::warning(this, "II etap", "Program nie mógł pobrać danych z Głównego Urzędu Statystycznego. Prawdopdobnie nie masz zainstalowanej paczki php lub brakuje plików w ścieżce /usr/share/qfaktury/src/GusApi");
        }
    }
    }
}
