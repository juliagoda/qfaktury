#include "Uzytkownik.moc"
#include "Settings.h"


/*!
  * init function read settings
  !*/
void Uzytkownik::init ()
{
  QSettings settings("elinux", "user");
  nameEdit->setText (settings.value ("name").toString());
  placeEdit->setText (settings.value ("city").toString());
  codeEdit->setText (settings.value ("zip").toString());
  addressEdit->setText (settings.value ("address").toString());
  accountEdit->setText (settings.value ("account").toString());
  if (!settings.value ("secIdType").isNull ())
    secIdType->setCurrentIndex (0); //X settings.
			       //value ("przelewy/user/secIdType").toString());
  nipEdit->setText (settings.value ("tic").toString());
  regonEdit->setText (settings.value ("regon").toString()); // i guess it's statistical number
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
