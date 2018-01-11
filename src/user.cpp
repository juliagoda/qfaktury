#include "user.h"
#include "settings.h"
#include "validations.h"

#include <QCheckBox>
#include <QComboBox>
#include <QLineEdit>
#include <QScrollArea>


User::User(QWidget *parent) : QDialog(parent) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  setupUi(this);
  sellersWidgets.append(mainSeller);
  bool ifOld = cameFromOldVersion();
  if (ifOld)
    prepareFor_0_7_1(ifOld);
  init();
}

/*!
  * inits function, reads settings
  !*/

void User::init() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  QSettings settings("elinux", "user");
  nameEdit->setText(settings.value("name").toString());
  placeEdit->setText(settings.value("city").toString());
  codeEdit->setText(settings.value("zip").toString());
  addressEdit->setText(settings.value("address").toString());
  accountEdit->setText(settings.value("account").toString());

  if (!settings.value("secIdType").isNull()) {
    int current = secIdType->findText(settings.value("secIdType").toString());
    secIdType->setCurrentIndex(current);
  }

  nipEdit->setText(settings.value("tic").toString());
  regonEdit->setText(
      settings.value("regon").toString()); // i guess it's statistical number
  webEdit->setText(settings.value("website").toString());
  bankNameEdit->setText(settings.value("bank").toString());
  bicSwiftEdit->setText(settings.value("swift").toString());
  krsEdit->setText(settings.value("krs").toString());

  for (int i = 0; i < settings.value("accountsCount").toInt(); ++i) {
    accountsCombo->addItem(
        settings.value("account" + QString::number(i + 1)).toString());
  }

  for (int i = 0; i < settings.value("telsCount").toInt(); ++i) {
    telsCombo->addItem(
        settings.value("phone" + QString::number(i + 1)).toString());
  }

  for (int i = 0; i < settings.value("faxesCount").toInt(); ++i) {
    faxesCombo->addItem(
        settings.value("fax" + QString::number(i + 1)).toString());
  }

  for (int i = 0; i < settings.value("emailsCount").toInt(); ++i) {
    emailsCombo->addItem(
        settings.value("email" + QString::number(i + 1)).toString());
  }

  for (int i = 1; i < settings.value("sellerCount").toInt(); ++i) {

    on_nextSeller_clicked();

    // add data to QLineEdits and choose of QComboBox option for each QTab
    QSettings settings("elinux", "user");
    settings.beginGroup("seller" + QString::number(i));
    sellersWidgets.at(i)
        ->findChild<QLineEdit *>("nameEdit")
        ->setText(settings.value("name").toString()); // save String
    sellersWidgets.at(i)
        ->findChild<QLineEdit *>("placeEdit")
        ->setText(settings.value("city").toString());
    sellersWidgets.at(i)
        ->findChild<QLineEdit *>("codeEdit")
        ->setText(settings.value("zip").toString());
    sellersWidgets.at(i)
        ->findChild<QLineEdit *>("addressEdit")
        ->setText(settings.value("address").toString());
    sellersWidgets.at(i)
        ->findChild<QLineEdit *>("accountEdit")
        ->setText(settings.value("account").toString());

    if (!settings.value("secIdType").isNull()) {
      int current = sellersWidgets.at(i)
                        ->findChild<QComboBox *>("secIdType")
                        ->findText(settings.value("secIdType").toString());
      sellersWidgets.at(i)
          ->findChild<QComboBox *>("secIdType")
          ->setCurrentIndex(current);
    }

    sellersWidgets.at(i)
        ->findChild<QLineEdit *>("regonEdit")
        ->setText(settings.value("regon").toString());
    sellersWidgets.at(i)
        ->findChild<QLineEdit *>("phonEdit")
        ->setText(settings.value("phone").toString());
    sellersWidgets.at(i)
        ->findChild<QLineEdit *>("emailEdit")
        ->setText(settings.value("email").toString());
    sellersWidgets.at(i)->findChild<QLineEdit *>("webEdit")->setText(
        settings.value("website").toString());
    sellersWidgets.at(i)->findChild<QLineEdit *>("krsEdit")->setText(
        settings.value("krs").toString());
    sellersWidgets.at(i)->findChild<QLineEdit *>("faxEdit")->setText(
        settings.value("fax").toString());
    sellersWidgets.at(i)
        ->findChild<QLineEdit *>("bankNameEdit")
        ->setText(settings.value("bank").toString());
    sellersWidgets.at(i)
        ->findChild<QLineEdit *>("bicSwiftEdit")
        ->setText(settings.value("swift").toString());
    if (settings.value("ifUsed").toBool())
      sellersWidgets.at(i)->findChild<QCheckBox *>()->setChecked(true);
    else
      sellersWidgets.at(i)->findChild<QCheckBox *>()->setChecked(false);
    settings.endGroup();
  }

  accountsCombo->setMaxCount(5);
  accountsCombo->setDuplicatesEnabled(false);
  telsCombo->setMaxCount(5);
  telsCombo->setDuplicatesEnabled(false);
  faxesCombo->setMaxCount(5);
  faxesCombo->setDuplicatesEnabled(false);
  emailsCombo->setMaxCount(5);
  emailsCombo->setDuplicatesEnabled(false);
}

bool User::checkAll() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  foreach (QWidget *widg, sellersWidgets) {
    if (Validations::instance()->isEmptyField(
            widg->findChild<QLineEdit *>("nameEdit")->text(),
            textLabel1->text()))
      return false;
  }

  foreach (QWidget *widg, sellersWidgets) {
    if (Validations::instance()->isEmptyField(
            widg->findChild<QLineEdit *>("placeEdit")->text(),
            textLabel3->text()))
      return false;
  }

  foreach (QWidget *widg, sellersWidgets) {
    if (!Validations::instance()->isEmptyField(
            widg->findChild<QLineEdit *>("codeEdit")->text(),
            textLabel4->text())) {
      if (!Validations::instance()->validateZip(
              widg->findChild<QLineEdit *>("codeEdit")->text()))
        return false;
    } else {
      return false;
    }
  }

  foreach (QWidget *widg, sellersWidgets) {
    if (Validations::instance()->isEmptyField(
            widg->findChild<QLineEdit *>("addressEdit")->text(),
            textLabel2->text()))
      return false;
  }

  foreach (QWidget *widg, sellersWidgets) {
    if (!Validations::instance()->isEmptyField(
            widg->findChild<QLineEdit *>("accountEdit")->text(),
            textLabel5->text())) {
      if (!Validations::instance()->validateAccount(
              widg->findChild<QLineEdit *>("accountEdit")->text()))
        return false;
      if (!Validations::instance()->checkSumAccount(
              widg->findChild<QLineEdit *>("accountEdit")->text()))
        return false;
    } else {
      return false;
    }
  }

  if (!Validations::instance()->isEmptyField(nipEdit->text(),
                                             textLabel2_2->text())) {
    if (!Validations::instance()->validateNIP(nipEdit->text()))
      return false;
    if (!Validations::instance()->checkSumNIP(nipEdit->text()))
      return false;
  } else {
    return false;
  }

  foreach (QWidget *widg, sellersWidgets) {
    if (widg->findChild<QComboBox *>("secIdType")->currentText() !=
        trUtf8("Brak")) {
      switch (widg->findChild<QComboBox *>("secIdType")->currentIndex()) {
      case 0:

        break;

      case 1:

        if (widg->findChild<QLineEdit *>("regonEdit")->text().isEmpty()) {
          QMessageBox::warning(
              this, trUtf8("Pusty NUSP"),
              trUtf8("Pole dla numeru NUSP nie może być puste"));
          return false;
        }
        break;

      case 2:

        if (!Validations::instance()->validateRegon(
                widg->findChild<QLineEdit *>("regonEdit")->text()))
          return false;
        if (!Validations::instance()->checkSumREGON(
                widg->findChild<QLineEdit *>("regonEdit")->text()))
          return false;
        break;

      case 3:

        if (!Validations::instance()->validatePESEL(
                widg->findChild<QLineEdit *>("regonEdit")->text()))
          return false;
        if (!Validations::instance()->checkSumPESEL(
                widg->findChild<QLineEdit *>("regonEdit")->text()))
          return false;
        break;

      case 4:

        if (!Validations::instance()->validateIDCard(
                widg->findChild<QLineEdit *>("regonEdit")->text()))
          return false;
        if (!Validations::instance()->checkSumIDCard(
                widg->findChild<QLineEdit *>("regonEdit")->text()))
          return false;
        break;

      case 5:

        if (!Validations::instance()->validatePass(
                widg->findChild<QLineEdit *>("regonEdit")->text()))
          return false;
        if (!Validations::instance()->checkSumPass(
                widg->findChild<QLineEdit *>("regonEdit")->text()))
          return false;
        break;
      }
    }
  }

  foreach (QWidget *widg, sellersWidgets) {
    if (!widg->findChild<QLineEdit *>("phonEdit")->text().isEmpty()) {
      if (!Validations::instance()->validateTel(
              widg->findChild<QLineEdit *>("phonEdit")->text()))
        return false;
    }
  }

  foreach (QWidget *widg, sellersWidgets) {
    if (!widg->findChild<QLineEdit *>("emailEdit")->text().isEmpty()) {
      if (!Validations::instance()->validateEmail(
              widg->findChild<QLineEdit *>("emailEdit")->text()))
        return false;
    }
  }

  foreach (QWidget *widg, sellersWidgets) {
    if (!widg->findChild<QLineEdit *>("webEdit")->text().isEmpty()) {
      if (!Validations::instance()->validateWebsite(
              widg->findChild<QLineEdit *>("webEdit")->text()))
        return false;
    }
  }

  return true;
}

/*!
  *   saves settings
  !*/

void User::okClick() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  bool ifOtherSeller = false;

  if (sett().value("validation").toBool() == false ||
      (sett().value("validation").toBool() && checkAll())) {

    int i = 0;
    foreach (QWidget *widg, sellersWidgets) {
      if (i == 0) {

        int accParts = 0;
        QString temp = accountsCombo->currentText();
        QStringList listOfAcc = temp.split(" | ");
        if (temp.contains('|'))
          accParts = listOfAcc.count();

        QSettings settings("elinux", "user");

        if (accParts > 0) {
          switch (accParts) {
          case 1:
            settings.setValue("account", listOfAcc.at(0));
            break;
          case 2:
            settings.setValue("account", listOfAcc.at(0));
            settings.setValue("bank", listOfAcc.at(1));
            break;
          case 3:
            settings.setValue("account", listOfAcc.at(0));
            settings.setValue("bank", listOfAcc.at(1));
            settings.setValue("swift", listOfAcc.at(2));
            break;
          }
        }

        settings.setValue("name", nameEdit->text()); // save String
        settings.setValue("city", placeEdit->text());
        settings.setValue("zip", codeEdit->text());
        settings.setValue("address", addressEdit->text());
        settings.setValue("tic", nipEdit->text());
        settings.setValue("secIdType", secIdType->currentText());
        settings.setValue("regon", regonEdit->text());
        settings.setValue("phone", telsCombo->currentText());
        settings.setValue("email", emailsCombo->currentText());
        settings.setValue("website", webEdit->text());
        settings.setValue("krs", krsEdit->text());
        settings.setValue("fax", faxesCombo->currentText());

        settings.setValue("accountsCount", accountsCombo->count());
        settings.setValue("telsCount", telsCombo->count());
        settings.setValue("faxesCount", faxesCombo->count());
        settings.setValue("emailsCount", emailsCombo->count());

        for (int i = 0; i < settings.value("accountsCount").toInt(); ++i) {
          settings.setValue("account" + QString::number(i + 1),
                            accountsCombo->itemText(i));
        }

        for (int i = 0; i < settings.value("telsCount").toInt(); ++i) {
          settings.setValue("phone" + QString::number(i + 1),
                            telsCombo->itemText(i));
        }

        for (int i = 0; i < settings.value("faxesCount").toInt(); ++i) {
          settings.setValue("fax" + QString::number(i + 1),
                            faxesCombo->itemText(i));
        }

        for (int i = 0; i < settings.value("emailsCount").toInt(); ++i) {
          settings.setValue("email" + QString::number(i + 1),
                            emailsCombo->itemText(i));
        }

      } else {

        QSettings settings("elinux", "user");
        settings.beginGroup("seller" + QString::number(i));
        settings.setValue(
            "name",
            widg->findChild<QLineEdit *>("nameEdit")->text()); // save String
        settings.setValue("city",
                          widg->findChild<QLineEdit *>("placeEdit")->text());
        settings.setValue("zip",
                          widg->findChild<QLineEdit *>("codeEdit")->text());
        settings.setValue("address",
                          widg->findChild<QLineEdit *>("addressEdit")->text());
        settings.setValue("account",
                          widg->findChild<QLineEdit *>("accountEdit")->text());
        settings.setValue("tic",
                          widg->findChild<QLineEdit *>("nipEdit")->text());
        settings.setValue(
            "secIdType",
            widg->findChild<QComboBox *>("secIdType")->currentText());
        settings.setValue("regon",
                          widg->findChild<QLineEdit *>("regonEdit")->text());
        settings.setValue("phone",
                          widg->findChild<QLineEdit *>("phonEdit")->text());
        settings.setValue("email",
                          widg->findChild<QLineEdit *>("emailEdit")->text());
        settings.setValue("website",
                          widg->findChild<QLineEdit *>("webEdit")->text());
        settings.setValue("krs",
                          widg->findChild<QLineEdit *>("krsEdit")->text());
        settings.setValue("fax",
                          widg->findChild<QLineEdit *>("faxEdit")->text());
        settings.setValue("bank",
                          widg->findChild<QLineEdit *>("bankNameEdit")->text());
        settings.setValue("swift",
                          widg->findChild<QLineEdit *>("bicSwiftEdit")->text());
        settings.setValue("ifUsed",
                          widg->findChild<QCheckBox *>()->isChecked());
        settings.endGroup();

        if (widg->findChild<QCheckBox *>()->isChecked()) {
          ifOtherSeller = true;

          QSettings settings("elinux", "user");

          settings.beginGroup("choosenSeller");
          settings.setValue(
              "name",
              widg->findChild<QLineEdit *>("nameEdit")->text()); // save String
          settings.setValue("city",
                            widg->findChild<QLineEdit *>("placeEdit")->text());
          settings.setValue("zip",
                            widg->findChild<QLineEdit *>("codeEdit")->text());
          settings.setValue(
              "address", widg->findChild<QLineEdit *>("addressEdit")->text());
          settings.setValue(
              "account", widg->findChild<QLineEdit *>("accountEdit")->text());
          settings.setValue("tic",
                            widg->findChild<QLineEdit *>("nipEdit")->text());
          settings.setValue(
              "secIdType",
              widg->findChild<QComboBox *>("secIdType")->currentText());
          settings.setValue("regon",
                            widg->findChild<QLineEdit *>("regonEdit")->text());
          settings.setValue("phone",
                            widg->findChild<QLineEdit *>("phonEdit")->text());
          settings.setValue("email",
                            widg->findChild<QLineEdit *>("emailEdit")->text());
          settings.setValue("website",
                            widg->findChild<QLineEdit *>("webEdit")->text());
          settings.setValue("krs",
                            widg->findChild<QLineEdit *>("krsEdit")->text());
          settings.setValue("fax",
                            widg->findChild<QLineEdit *>("faxEdit")->text());
          settings.setValue(
              "bank", widg->findChild<QLineEdit *>("bankNameEdit")->text());
          settings.setValue(
              "swift", widg->findChild<QLineEdit *>("bicSwiftEdit")->text());
          settings.endGroup();
        }
      }
      i += 1;
    }

    QSettings settings("elinux", "user");
    settings.setValue("sellerCount", QString::number(i));

    if (!ifOtherSeller) {
      QSettings settings("elinux", "user");
      QSettings setts("elinux", "user");
      setts.beginGroup("choosenSeller");
      setts.setValue("name", settings.value("name").toString()); // save String
      setts.setValue("city", settings.value("city").toString());
      setts.setValue("zip", settings.value("zip").toString());
      setts.setValue("address", settings.value("address").toString());
      setts.setValue("account", settings.value("account").toString());
      setts.setValue("tic", settings.value("tic").toString());
      setts.setValue("secIdType", settings.value("secIdType").toString());
      setts.setValue("regon", settings.value("regon").toString());
      setts.setValue("phone", settings.value("phone").toString());
      setts.setValue("email", settings.value("email").toString());
      setts.setValue("website", settings.value("website").toString());
      setts.setValue("krs", settings.value("krs").toString());
      setts.setValue("fax", settings.value("fax").toString());
      setts.setValue("bank", settings.value("bank").toString());
      setts.setValue("swift", settings.value("swift").toString());
      setts.endGroup();
    }

    close();
  }
}

/*
 * Generates next seller tab in QTabWidget
 */

void User::on_nextSeller_clicked() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  QWidget *nextSel = new QWidget();

  QHBoxLayout *hLayout = new QHBoxLayout();
  QVBoxLayout *vLayout1 = new QVBoxLayout();
  QVBoxLayout *vLayout2 = new QVBoxLayout();

  QStringList listNames = QStringList() << "Nazwa*:"
                                        << "Miejscowość*:"
                                        << "Kod*:"
                                        << "Adres*:"
                                        << "Nr konta*:"
                                        << "Nazwa banku:"
                                        << "Nr SWIFT/BIC:"
                                        << "NIP*:"
                                        << "Typ 2 Id:"
                                        << "Drugi Id:"
                                        << "Numer KRS:"
                                        << "Telefon:"
                                        << "Fax:"
                                        << "Email:"
                                        << "Strona www:";

  QStringList objectNames = QStringList() << "nameEdit"
                                          << "placeEdit"
                                          << "codeEdit"
                                          << "addressEdit"
                                          << "accountEdit"
                                          << "bankNameEdit"
                                          << "bicSwiftEdit"
                                          << "nipEdit"
                                          << "secIdType"
                                          << "regonEdit"
                                          << "krsEdit"
                                          << "phonEdit"
                                          << "faxEdit"
                                          << "emailEdit"
                                          << "webEdit";

  QLabel *useLabel = new QLabel;
  useLabel->setText(trUtf8("Zastosuj do faktur"));
  vLayout1->addWidget(useLabel);

  QCheckBox *useCheckBox = new QCheckBox(nextSel);
  useCheckBox->setObjectName(trUtf8("useThisSeller"));
  vLayout2->addWidget(useCheckBox);

  for (int i = 0; i < listNames.count(); i++) {
    QLabel *name = new QLabel;
    name->setText(listNames.at(i));
    vLayout1->addWidget(name);

    if (objectNames.at(i) == "secIdType") {
      QStringList listcombo = QStringList() << "Brak"
                                            << "NUSP"
                                            << "REGON"
                                            << "PESEL"
                                            << "Dowód osobisty"
                                            << "Paszport";
      QComboBox *lname = new QComboBox;
      lname->addItems(listcombo);
      lname->setObjectName(objectNames.at(i));
      vLayout2->addWidget(lname);

    } else {

      QLineEdit *lname = new QLineEdit;
      lname->setObjectName(objectNames.at(i));
      if (lname->objectName() == "nipEdit") {
        QSettings settings("elinux", "user");
        lname->setText(settings.value("tic").toString());
        lname->setDisabled(true);
      }
      vLayout2->addWidget(lname);
    }
  }

  hLayout->addLayout(vLayout1);
  hLayout->addLayout(vLayout2);

  QPushButton *removeBtn = new QPushButton("X");
  removeBtn->setFixedWidth(30);

  hLayout->addWidget(removeBtn);

  nextSel->setLayout(hLayout);
  QScrollArea *scrollArea = new QScrollArea;
  scrollArea->setWidget(nextSel);
  sellersList->addTab(scrollArea, trUtf8("Sprzedawca/Oddział"));

  connect(removeBtn, SIGNAL(clicked()), this, SLOT(delcurrSel()));

  sellersWidgets.append(nextSel);
}

/*
 * Removes current tab with seller in QTabWidget
 */

void User::delcurrSel() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  if (QMessageBox::warning(this, trUtf8("Usuwanie danych oddziału"),
                           trUtf8("Usunąć dane kolejnego sprzedawcy/oddziału?"),
                           trUtf8("Tak"), trUtf8("Nie"), 0, 0, 1) == 0) {
    QSettings settings("elinux", "user");
    settings.remove("seller" + QString::number(sellersList->currentIndex()));

    bool isLess = false;
    if (sellersList->currentIndex() < sellersList->count() - 1)
      isLess = true;

    int delIndex = sellersList->currentIndex();

    sellersWidgets.removeAt(sellersList->currentIndex());
    sellersList->removeTab(sellersList->currentIndex());
    sellersList->setCurrentIndex(0);

    int countedSellers = sellersList->count();
    settings.setValue("sellerCount", sellersWidgets.count());

    if (isLess) {

      for (int i = delIndex, j = delIndex + 1; j <= countedSellers; ++i, ++j) {
        settings.beginGroup("seller" + QString::number(j));
        QSettings settings2("elinux", "user");
        settings2.beginGroup("seller" + QString::number(i));

        foreach (const QString &key, settings.childKeys()) {
          settings2.setValue(key, settings.value(key).toString());
        }

        settings2.endGroup();
        settings.endGroup();
      }

      settings.remove("seller" + QString::number(sellersList->count()));
    }
  }
}

// adds bank account from QLineEdit to QComboBox list in form -> "account number
// | bank name | bank swift/bic"
void User::on_addAcc_clicked() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  if (!accountEdit->text().isEmpty()) {
    if (!accountEdit->text().isEmpty() && !bankNameEdit->text().isEmpty() &&
        !bicSwiftEdit->text().isEmpty())
      accountsCombo->addItem(accountEdit->text().trimmed() + " | " +
                             bankNameEdit->text().trimmed() + " | " +
                             bicSwiftEdit->text().trimmed());
    else if (!accountEdit->text().isEmpty() && !bankNameEdit->text().isEmpty())
      accountsCombo->addItem(accountEdit->text().trimmed() + " | " +
                             bankNameEdit->text().trimmed());
    else if (!accountEdit->text().isEmpty())
      accountsCombo->addItem(accountEdit->text().trimmed());

    update();
  } else
    QMessageBox::warning(
        this, "Pusta rubryka dla konta",
        "Powinienes wprowadzic co najmniej numer konta bankowego do rubryki. ");
}

// removes current option in QComboBox for bank accounts. Changes in user.conf
// will be added automatically after "OK" pressing
void User::on_remAcc_clicked() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  if (accountsCombo->currentIndex() != -1)
    accountsCombo->removeItem(accountsCombo->currentIndex());
}

// after other account select in QComboBox, informations in QLineEdits are
// updated
void User::on_accountsCombo_currentTextChanged(const QString &arg1) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  int accParts = 0;
  QStringList listOfAcc = arg1.split(" | ");
  if (arg1.contains('|'))
    accParts = listOfAcc.count();

  if (accParts > 0) {
    switch (accParts) {
    case 1:
      accountEdit->clear();
      accountEdit->setText(listOfAcc.at(0));
      break;
    case 2:
      accountEdit->clear();
      bankNameEdit->clear();

      accountEdit->setText(listOfAcc.at(0));
      bankNameEdit->setText(listOfAcc.at(1));
      break;
    case 3:
      accountEdit->clear();
      bankNameEdit->clear();
      bicSwiftEdit->clear();

      accountEdit->setText(listOfAcc.at(0));
      bankNameEdit->setText(listOfAcc.at(1));
      bicSwiftEdit->setText(listOfAcc.at(2));
      break;
    }
  }

  // if this won't be executed, then under old index and first index has the
  // same value. Avoiding second select in QComboBox the first value, to
  // confirm, we execute "setCurrentIndex"
  int index = accountsCombo->findText(arg1);
  QString tempFirst = accountsCombo->itemText(0);
  accountsCombo->setItemText(index, tempFirst);
  accountsCombo->setItemText(0, arg1);
  accountsCombo->setCurrentIndex(0);
}

// adds phone number from QLineEdit to QComboBox list
void User::on_addTel_clicked() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  if (!phonEdit->text().isEmpty()) {
    if (telsCombo->findText(phonEdit->text().trimmed()) == -1) {
      telsCombo->addItem(phonEdit->text().trimmed());
      phonEdit->clear();
    } else
      QMessageBox::warning(this, "Istniejacy numer",
                           "Taki numer znajduje sie juz na Twojej liscie ");
  } else
    QMessageBox::warning(this, "Pusta rubryka dla numeru telefonu",
                         "Nie ma wpisanego numeru telefonu w rubryce, ktora "
                         "moglbys dodac do listy. Wprowadz wpierw numer. ");
}

// removes current option in QComboBox for phone numbers. Changes in user.conf
// will be added automatically after "OK" pressing
void User::on_remTel_clicked() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  if (telsCombo->currentIndex() != -1)
    telsCombo->removeItem(telsCombo->currentIndex());
}

// if this won't be executed, then under old index and first index has the same
// value. Avoiding second select in QComboBox the first value, to confirm, we
// execute "setCurrentIndex"
void User::on_telsCombo_currentTextChanged(const QString &arg1) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  int index = telsCombo->findText(arg1);
  QString tempFirst = telsCombo->itemText(0);
  telsCombo->setItemText(index, tempFirst);
  telsCombo->setItemText(0, arg1);
  telsCombo->setCurrentIndex(0);
}

// adds fax from QLineEdit to QComboBox list
void User::on_addFax_clicked() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  if (!faxEdit->text().isEmpty()) {
    if (faxesCombo->findText(faxEdit->text().trimmed()) == -1) {
      faxesCombo->addItem(faxEdit->text().trimmed());
      faxEdit->clear();
    } else
      QMessageBox::warning(this, "Istniejacy numer",
                           "Taki numer znajduje sie juz na Twojej liscie ");
  } else
    QMessageBox::warning(this, "Pusta rubryka dla faksu",
                         "Nie ma wpisanego faksu w rubryce, ktory moglbys "
                         "dodac do listy. Wprowadz wpierw numer. ");
}

// removes current option in QComboBox for faxes. Changes in user.conf will be
// added automatically after "OK" pressing
void User::on_remFax_clicked() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  if (faxesCombo->currentIndex() != -1)
    faxesCombo->removeItem(faxesCombo->currentIndex());
}

// if this won't be executed, then under old index and first index has the same
// value. Avoiding second select in QComboBox the first value, to confirm, we
// execute "setCurrentIndex"
void User::on_faxesCombo_currentTextChanged(const QString &arg1) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  int index = faxesCombo->findText(arg1);
  QString tempFirst = faxesCombo->itemText(0);
  faxesCombo->setItemText(index, tempFirst);
  faxesCombo->setItemText(0, arg1);
  faxesCombo->setCurrentIndex(0);
}

// adds email from QLineEdit to QComboBox list
void User::on_addEmail_clicked() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  if (!emailEdit->text().isEmpty()) {
    if (emailsCombo->findText(emailEdit->text().trimmed()) == -1) {
      emailsCombo->addItem(emailEdit->text().trimmed());
      emailEdit->clear();
    } else
      QMessageBox::warning(this, "Istniejący adres",
                           "Taki adres znajduje się już na Twojej liście ");
  } else
    QMessageBox::warning(
        this, "Pusta rubryka dla adresu email",
        "Nie ma wpisanego adresu email w rubryce, który "
        "mógłbyś dodać do listy. Wprowadż w pierwszej kolejności adres. ");
}

// removes current option in QComboBox for emails. Changes in user.conf will be
// added automatically after "OK" pressing
void User::on_remEmail_clicked() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  if (emailsCombo->currentIndex() != -1)
    emailsCombo->removeItem(emailsCombo->currentIndex());
}

// if this won't be executed, then under old index and first index has the same
// value. Avoiding second select in QComboBox the first value, to confirm, we
// execute "setCurrentIndex"
void User::on_emailsCombo_currentTextChanged(const QString &arg1) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  int index = emailsCombo->findText(arg1);
  QString tempFirst = emailsCombo->itemText(0);
  emailsCombo->setItemText(index, tempFirst);
  emailsCombo->setItemText(0, arg1);
  emailsCombo->setCurrentIndex(0);
}

// checks if in user.conf exist keys like "accountsCount" or "telsCount", which
// are needed for multiple choice
bool User::cameFromOldVersion() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  QSettings settings("elinux", "user");
  if (settings.contains("accountsCount") || settings.contains("telsCount") ||
      settings.contains("faxesCount") || settings.contains("emailsCount"))
    return false;
  else
    return true;
}

// if user.conf doesn't have needed keys in, then takes values from QLineEdits
// to QQComboBoxes and writes changes in user.conf
void User::prepareFor_0_7_1(bool cameFromOlder) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  if (cameFromOlder) {

    QSettings settings("elinux", "user");

    QString account = settings.value("account").toString();
    QString bank = settings.value("bank").toString();
    QString swift = settings.value("swift").toString();

    QString togetherAcc = QString();

    if (!account.isNull() || !account.isEmpty())
      togetherAcc = account;

    if (!bank.isNull() || !bank.isEmpty()) {
      if (account.isNull() || account.isEmpty())
        togetherAcc = QString();
      else
        togetherAcc += " | " + bank;
    }
    if (!swift.isNull() || !swift.isEmpty()) {
      if ((account.isNull() || account.isEmpty()) &&
          (bank.isNull() || bank.isEmpty()))
        togetherAcc = QString();
      else
        togetherAcc += " | " + swift;
    }

    settings.setValue("account1", togetherAcc);
    settings.setValue("accountsCount", "1");
    settings.setValue("phone1", settings.value("phone").toString());
    settings.setValue("telsCount", "1");
    settings.setValue("fax1", settings.value("fax").toString());
    settings.setValue("faxesCount", "1");
    settings.setValue("email1", settings.value("email").toString());
    settings.setValue("emailsCount", "1");
  }
}
