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
#include <qsettings.h>
#include <qtextcodec.h>


/*!
  * init function read settings
  !*/
void Uzytkownik::init ()
{
  QTextCodec::setCodecForCStrings (QTextCodec::codecForName ("ISO8859-2"));

  QSettings settings;
  nameEdit->setText (settings.readEntry ("przelewy/user/nazwa"));
  placeEdit->setText (settings.readEntry ("przelewy/user/miejscowosc"));
  codeEdit->setText (settings.readEntry ("przelewy/user/kod"));
  addressEdit->setText (settings.readEntry ("przelewy/user/adres"));
  accountEdit->setText (settings.readEntry ("przelewy/user/konto"));
  if (!settings.readEntry ("przelewy/user/secIdType").isNull ())
    secIdType->setCurrentText (settings.
			       readEntry ("przelewy/user/secIdType"));
  nipEdit->setText (settings.readEntry ("przelewy/user/nip"));
  regonEdit->setText (settings.readEntry ("przelewy/user/regon"));
}

/*!
  *   save settings
  !*/
void Uzytkownik::okClick ()
{
  QSettings settings;
  settings.beginGroup ("przelewy");
  settings.writeEntry ("user/nazwa", nameEdit->text ());	// zapis String
  settings.writeEntry ("user/miejscowosc", placeEdit->text ());
  settings.writeEntry ("user/kod", codeEdit->text ());
  settings.writeEntry ("user/adres", addressEdit->text ());
  settings.writeEntry ("user/konto", accountEdit->text ());
  settings.writeEntry ("user/nip", nipEdit->text ());
  settings.writeEntry ("user/secIdType", secIdType->currentText ());
  settings.writeEntry ("user/regon", regonEdit->text ());
  settings.endGroup ();
  close ();
}
Uzytkownik::Uzytkownik(QWidget *parent): QDialog(parent) {
    setupUi(this);
    init();
}
