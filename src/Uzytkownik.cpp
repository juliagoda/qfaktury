
#include <QLabel>
#include <QComboBox>
#include "Walidacje.h"
#include "Settings.h"
#include "Uzytkownik.h"

/*!
  * init function read settings
  !*/
void Uzytkownik::init () {

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

}


bool Uzytkownik::checkAll()
{
    if (Walidacje::instance()->isEmptyField(nameEdit->text(),textLabel1->text())) return false;
    if (Walidacje::instance()->isEmptyField(placeEdit->text(),textLabel3->text())) return false;

    if (!Walidacje::instance()->isEmptyField(codeEdit->text(),textLabel4->text())) {
        if (!Walidacje::instance()->validateZip(codeEdit->text())) return false;
       } else {
        return false;
        }

    if (Walidacje::instance()->isEmptyField(addressEdit->text(),textLabel2->text())) return false;

    if (!Walidacje::instance()->isEmptyField(accountEdit->text(),textLabel5->text())) {
        if (!Walidacje::instance()->validateAccount(accountEdit->text())) return false;
        if (!Walidacje::instance()->checkSumAccount(accountEdit->text())) return false;
        } else {
        return false;
        }

    if (!Walidacje::instance()->isEmptyField(nipEdit->text(),textLabel2_2->text())) {
        if (!Walidacje::instance()->validateNIP(nipEdit->text())) return false;
        if (!Walidacje::instance()->checkSumNIP(nipEdit->text())) return false;
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

        if (!Walidacje::instance()->validateRegon(regonEdit->text())) return false;
        if (!Walidacje::instance()->checkSumREGON(regonEdit->text())) return false;
            break;

    case 3:

        if (!Walidacje::instance()->validatePESEL(regonEdit->text())) return false;
        if (!Walidacje::instance()->checkSumPESEL(regonEdit->text())) return false;
            break;

    case 4:

        if (!Walidacje::instance()->validateIDCard(regonEdit->text())) return false;
        if (!Walidacje::instance()->checkSumIDCard(regonEdit->text())) return false;
            break;

    case 5:

        if (!Walidacje::instance()->validatePass(regonEdit->text())) return false;
        if (!Walidacje::instance()->checkSumPass(regonEdit->text())) return false;
            break;
        }
    }

    if (!phonEdit->text().isEmpty()) {
        if (!Walidacje::instance()->validateTel(phonEdit->text())) return false;
        }

    if (!emailEdit->text().isEmpty()) {
        if (!Walidacje::instance()->validateEmail(emailEdit->text())) return false;
        }

    if (!webEdit->text().isEmpty()) {
        if (!Walidacje::instance()->validateWebsite(webEdit->text())) return false;
        }

    return true;
}

/*!
  *   save settings
  !*/

void Uzytkownik::okClick ()
{
  if (checkAll()) {

  QSettings settings("elinux", "user");
  settings.setValue ("name", nameEdit->text ());	// zapis String
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


Uzytkownik::Uzytkownik(QWidget *parent): QDialog(parent) {
    setupUi(this);
    init();
}
