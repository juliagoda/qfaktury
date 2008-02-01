/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you want to add, delete, or rename functions or slots, use
** Qt Designer to update this file, preserving your code.
**
** You should not define a constructor or destructor in this file.
** Instead, write your code in functions called init() and destroy().
** These will automatically be called by the form's constructor and
** destructor.
*****************************************************************************/
#include "Uzytkownik.moc"
#include "Settings.h"
#include <qtextcodec.h>


/*!
  * init function read settings
  !*/
void Uzytkownik::init ()
{
  QTextCodec::setCodecForCStrings (QTextCodec::codecForName ("ISO8859-2"));

  Settings settings;
  nameEdit->setText (settings.value ("przelewy/user/nazwa").toString());
  placeEdit->setText (settings.value ("przelewy/user/miejscowosc").toString());
  codeEdit->setText (settings.value ("przelewy/user/kod").toString());
  addressEdit->setText (settings.value ("przelewy/user/adres").toString());
  accountEdit->setText (settings.value ("przelewy/user/konto").toString());
  if (!settings.value ("przelewy/user/secIdType").isNull ())
    secIdType->setCurrentIndex (0); //X settings.
			       //value ("przelewy/user/secIdType").toString());
  nipEdit->setText (settings.value ("przelewy/user/nip").toString());
  regonEdit->setText (settings.value ("przelewy/user/regon").toString());
}

/*!
  *   save settings
  !*/
void Uzytkownik::okClick ()
{
  Settings settings;
  settings.beginGroup ("przelewy");
  settings.setValue ("user/nazwa", nameEdit->text ());	// zapis String
  settings.setValue ("user/miejscowosc", placeEdit->text ());
  settings.setValue ("user/kod", codeEdit->text ());
  settings.setValue ("user/adres", addressEdit->text ());
  settings.setValue ("user/konto", accountEdit->text ());
  settings.setValue ("user/nip", nipEdit->text ());
  settings.setValue ("user/secIdType", secIdType->currentText ());
  settings.setValue ("user/regon", regonEdit->text ());
  settings.endGroup ();
  close ();
}
Uzytkownik::Uzytkownik(QWidget *parent): QDialog(parent) {
    setupUi(this);
    init();
}
