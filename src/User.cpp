
#include "Validations.h"
#include "Settings.h"
#include "User.h"


User::User(QWidget *parent): QDialog(parent) {
    setupUi(this);
    init();
}

/*!
  * inits function, reads settings
  !*/

void User::init () {

  QSettings settings("elinux", "user");
  nameEdit->setText (settings.value ("name").toString());
  placeEdit->setText (settings.value ("city").toString());
  codeEdit->setText (settings.value ("zip").toString());
  addressEdit->setText (settings.value ("address").toString());
  accountEdit->setText (settings.value ("account").toString());

  if (!settings.value ("secIdType").isNull ()) {
	 int current = secIdType->findText(settings.value ("secIdType").toString());
	 secIdType->setCurrentIndex (current);
  }

  nipEdit->setText (settings.value ("tic").toString());
  regonEdit->setText (settings.value ("regon").toString()); // i guess it's statistical number
  phonEdit->setText (settings.value ("phone").toString());
  emailEdit->setText (settings.value ("email").toString());
  webEdit->setText (settings.value ("website").toString());
  bankNameEdit->setText (settings.value ("bank").toString());
  bicSwiftEdit->setText (settings.value ("swift").toString());
  krsEdit->setText (settings.value ("krs").toString());
  faxEdit->setText (settings.value ("fax").toString());

}


bool User::checkAll()
{
    if (Validations::instance()->isEmptyField(nameEdit->text(),textLabel1->text())) return false;
    if (Validations::instance()->isEmptyField(placeEdit->text(),textLabel3->text())) return false;

    if (!Validations::instance()->isEmptyField(codeEdit->text(),textLabel4->text())) {
        if (!Validations::instance()->validateZip(codeEdit->text())) return false;
       } else {
        return false;
        }

    if (Validations::instance()->isEmptyField(addressEdit->text(),textLabel2->text())) return false;

    if (!Validations::instance()->isEmptyField(accountEdit->text(),textLabel5->text())) {
        if (!Validations::instance()->validateAccount(accountEdit->text())) return false;
        if (!Validations::instance()->checkSumAccount(accountEdit->text())) return false;
        } else {
        return false;
        }

    if (!Validations::instance()->isEmptyField(nipEdit->text(),textLabel2_2->text())) {
        if (!Validations::instance()->validateNIP(nipEdit->text())) return false;
        if (!Validations::instance()->checkSumNIP(nipEdit->text())) return false;
        } else {
        return false;
        }


    if (secIdType->currentText() != trUtf8("Brak")) {
    switch (secIdType->currentIndex()) {
    case 0:

            break;

    case 1:

            if (regonEdit->text().isEmpty()) {
                QMessageBox::warning(this, trUtf8("Pusty NUSP"), trUtf8("Pole dla numeru NUSP nie może być puste"));
                return false;
            }
            break;

    case 2:

        if (!Validations::instance()->validateRegon(regonEdit->text())) return false;
        if (!Validations::instance()->checkSumREGON(regonEdit->text())) return false;
            break;

    case 3:

        if (!Validations::instance()->validatePESEL(regonEdit->text())) return false;
        if (!Validations::instance()->checkSumPESEL(regonEdit->text())) return false;
            break;

    case 4:

        if (!Validations::instance()->validateIDCard(regonEdit->text())) return false;
        if (!Validations::instance()->checkSumIDCard(regonEdit->text())) return false;
            break;

    case 5:

        if (!Validations::instance()->validatePass(regonEdit->text())) return false;
        if (!Validations::instance()->checkSumPass(regonEdit->text())) return false;
            break;
        }
    }

    if (!phonEdit->text().isEmpty()) {
        if (!Validations::instance()->validateTel(phonEdit->text())) return false;
        }

    if (!emailEdit->text().isEmpty()) {
        if (!Validations::instance()->validateEmail(emailEdit->text())) return false;
        }

    if (!webEdit->text().isEmpty()) {
        if (!Validations::instance()->validateWebsite(webEdit->text())) return false;
        }

    return true;
}

/*!
  *   saves settings
  !*/

void User::okClick ()
{
  if (checkAll()) {

  QSettings settings("elinux", "user");
  settings.setValue ("name", nameEdit->text ());	// save String
  settings.setValue ("city", placeEdit->text ());
  settings.setValue ("zip", codeEdit->text ());
  settings.setValue ("address", addressEdit->text ());
  settings.setValue ("account", accountEdit->text ());
  settings.setValue ("tic", nipEdit->text ());
  settings.setValue ("secIdType", secIdType->currentText ());
  settings.setValue ("regon", regonEdit->text ());
  settings.setValue ("phone", phonEdit->text ());
  settings.setValue ("email", emailEdit->text ());
  settings.setValue ("website", webEdit->text ());

  close ();

  }
}
