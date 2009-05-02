#include "moc_Uzytkownik.cpp"
#include "Settings.h"


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

  nipEdit->setInputMask(sett().value("ticMask", "999-99-999-99; ").toString());
  accountEdit->setInputMask(sett().value("accountMask", "99-9999-9999-9999-9999-9999-9999; ").toString());
}

/*!
  *   save settings
  !*/
void Uzytkownik::okClick ()
{
  QSettings settings("elinux", "user");
  settings.setValue ("name", nameEdit->text ());	// zapis String
  settings.setValue ("city", placeEdit->text ());
  settings.setValue ("zip", codeEdit->text ());
  settings.setValue ("address", addressEdit->text ());
  settings.setValue ("account", accountEdit->text ());
  settings.setValue ("tic", nipEdit->text ());
  settings.setValue ("secIdType", secIdType->currentText ());
  settings.setValue ("regon", regonEdit->text ());
  close ();
}

Uzytkownik::Uzytkownik(QWidget *parent): QDialog(parent) {
    setupUi(this);
    init();
}
