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
#include "Towary.moc"
#include <qtextcodec.h>
#include <qdir.h>
#include <Qt/qdom.h>
#include <qprocess.h>
#include "Settings.h"
#include <qmessagebox.h>
#include <QtDebug>


/*
idxEdit
nameEdit
skrotEdit
typeCombo
jednCombo
nettoEdit
vatEdit
*/




void Towary::readData (QString idx, QString type)
{
  qDebug (__FUNCTION__);
  if (idx == "")
    {
      netto.append ("0,00");
      netto.append ("0,00");
      netto.append ("0,00");
      netto.append ("0,00");
      nettoEdit->setText ("0,00");
    }
  else
    {
      setWindowTitle ("Edytuj towar/us³ugê");
    }

  lastId = 1;
  idxEdit->setText (idx);
  qDebug ()<<idx << "   " << type;
  QDomDocument doc ("towary");
  QDomElement root;
  QDomElement towar;
  QDomElement usluga;

  QFile file (progDir + "/towary.xml");
  if (!file.open (QIODevice::ReadOnly))
    {
      qDebug ("file doesn't exists");
      return;
    }
  else
    {
      QTextStream stream (&file);
      if (!doc.setContent (stream.readAll ()))
	{
	  qDebug ("can not set content ");
	  file.close ();
	  return;
	}
      else
	{
	  root = doc.documentElement ();
	  lastId = root.attribute ("last", "1").toInt ();
	  towar = root.firstChild ().toElement ();
	  usluga = root.lastChild ().toElement ();
	}
      QString text;

      if (type.compare ("towar") == 0)
	{
	  for (QDomNode n = towar.firstChild (); !n.isNull ();
	       n = n.nextSibling ())
	    {
	      text = n.toElement ().attribute ("idx");
	      if (text.compare (idx) == 0)
		{
		  idxEdit->setText (text);
		  nameEdit->setText (n.toElement ().attribute ("name"));
		  kodEdit->setText (n.toElement ().attribute ("code"));
		  skrotEdit->setText (n.toElement ().attribute ("desc"));
		  pkwiuEdit->setText (n.toElement ().attribute ("pkwiu"));
		  typeCombo->setCurrentIndex(0);
		  jednCombo->setCurrentIndex(0);//Text (n.toElement ().
					     //X attribute ("curr"));
		  nettoEdit->setText (n.toElement ().attribute ("netto1"));
		  netto[0] = n.toElement ().attribute ("netto1");
		  netto[1] = n.toElement ().attribute ("netto2");
		  netto[2] = n.toElement ().attribute ("netto3");
		  netto[3] = n.toElement ().attribute ("netto4");
		  qDebug ()<<n.toElement ().attribute ("netto4");
		  cbVat->setCurrentIndex(0); //X Text (n.toElement ().attribute ("vat"));
		  // vatEdit->setText (n.toElement ().attribute ("vat"));
		}
	    }
	}
      else
	{
	  for (QDomNode n = usluga.firstChild (); !n.isNull ();
	       n = n.nextSibling ())
	    {
	      text = n.toElement ().attribute ("idx");
	      if (text.compare (idx) == 0)
		{
		  idxEdit->setText (text);
		  nameEdit->setText (n.toElement ().attribute ("name"));
		  kodEdit->setText (n.toElement ().attribute ("code"));
		  pkwiuEdit->setText (n.toElement ().attribute ("pkwiu"));
		  skrotEdit->setText (n.toElement ().attribute ("desc"));
		  typeCombo->setCurrentIndex(0); //X Text ("us³uga");
		  jednCombo->setCurrentIndex(0); //X Text (n.toElement ().
					     //attribute ("curr"));
		  nettoEdit->setText (n.toElement ().attribute ("netto1"));
		  netto[0] = n.toElement ().attribute ("netto1");
		  netto[1] = n.toElement ().attribute ("netto2");
		  netto[2] = n.toElement ().attribute ("netto3");
		  netto[3] = n.toElement ().attribute ("netto4");
		  qDebug ()<<n.toElement ().attribute ("netto4");
		  cbVat->setCurrentIndex(0); //X Text (n.toElement ().attribute ("vat"));
		  // spinBoxVat->setValue( n.toElement ().attribute ("vat").toInt() );
		  // vatEdit->setText (n.toElement ().attribute ("vat"));
		}
	    }
	}
    }

}

void Towary::getStuffList ()
{
  qDebug (__FUNCTION__);
  QString progDir2 = QDir::homePath () + "/elinux";

  QDomDocument doc ("towary");
  QDomElement root;
  QDomElement towar;
  QDomElement usluga;

  QFile file (progDir2 + "/towary.xml");
  if (!file.open (QIODevice::ReadOnly))
    {
      qDebug ("file doesn't exists");
      return;

    }
  else
    {
      QTextStream stream (&file);
      if (!doc.setContent (stream.readAll ()))
	{
	  qDebug ("can not set content ");
	  file.close ();
	  return;
	}
      else
	{
	  root = doc.documentElement ();
	  towar = root.firstChild ().toElement ();
	  usluga = root.lastChild ().toElement ();
	}
      QString text;


      for (QDomNode n = towar.firstChild (); !n.isNull ();
	   n = n.nextSibling ())
	{
	  text = n.toElement ().attribute ("idx");
	  allNames << text;
	}

      for (QDomNode n = usluga.firstChild (); !n.isNull ();
	   n = n.nextSibling ())
	{
	  text = n.toElement ().attribute ("idx");
	  allNames << text;
	}

    }

}

void Towary::init ()
{
  qDebug (__FUNCTION__);
  QTextCodec::setCodecForCStrings (QTextCodec::codecForName ("ISO8859-2"));
  QTextCodec::setCodecForLocale (QTextCodec::codecForName ("ISO8859-2"));

  progDir = QDir::homePath () + "/elinux";
  readData ("", "");
  idxEdit->setText (QString::number (lastId));
  // cbVat->setCurrentText ("22");
  
  Settings settings;
  
  //  settings.writeEntry ("firstrun", "nie");
  // logoEdit->setText( settings.readEntry("elinux/faktury/logo") );
 jednCombo->addItems( settings.value("elinux/faktury/jednostki").toString().split("|")); 
 cbVat->addItems( settings.value("elinux/faktury/stawki").toString().split("|")); 
  
}

bool Towary::saveAll ()
{
  qDebug (__FUNCTION__);
  nettoChanged ();

  // getStuffList ();
  /*
     // nie robimy sprawdzania nazwy
     QStringList::iterator it = allNames.find (nameEdit->text ());
     if ((*it) == nameEdit->text ())
     {
     QMessageBox::critical (0, "Faktury",
     "Towar nie moze zostaæ dodany poniewa¿ istnieje ju¿ kontrahent o tej nazwie.");
     return false;
     }
   */

  QDomDocument doc ("towary");
  QDomElement root;
  QDomElement towary;
  QDomElement uslugi;

  QFile file (progDir + "/towary.xml");
  if (!file.open (QIODevice::ReadOnly))
    {
      qDebug ("can not open ");
      root = doc.createElement ("towary");
      lastId++;
      root.setAttribute ("last", QString::number (lastId));
      doc.appendChild (root);
      towary = doc.createElement ("towar");
      root.appendChild (towary);
      uslugi = doc.createElement ("usluga");
      root.appendChild (uslugi);
    }
  else
    {
      QTextStream stream (&file);
      if (!doc.setContent (stream.readAll ()))

	{
	  qDebug ("can not set content ");
	  file.close ();
	  // return;¦
	}
      else
	{
	  root = doc.documentElement ();
	  lastId++;
	  root.setAttribute ("last", QString::number (lastId));
	  towary = root.firstChild ().toElement ();
	  uslugi = root.lastChild ().toElement ();
	}
    }

  root.lastChild ();



  // firma = 0; urzad = 1;
  if (typeCombo->currentIndex () == 0)
    {
      QDomElement elem = doc.createElement ("towar");
      elem.setAttribute ("idx", idxEdit->text ());
      elem.setAttribute ("code", kodEdit->text ());
      elem.setAttribute ("name", nameEdit->text ());
      elem.setAttribute ("desc", skrotEdit->text ());
      elem.setAttribute ("pkwiu", pkwiuEdit->text ());
      // elem.setAttribute ("type", "towar");
      elem.setAttribute ("curr", jednCombo->currentText ());
      elem.setAttribute ("netto1", netto[0]);
      elem.setAttribute ("netto2", netto[1]);
      elem.setAttribute ("netto3", netto[2]);
      elem.setAttribute ("netto4", netto[3]);
      // qDebug("1 netto4" + netto[3]);
      elem.setAttribute ("vat", cbVat->currentText ());
      towary.appendChild (elem);
      qDebug ("dodano towar");
    }

  if (typeCombo->currentIndex () == 1)
    {
      QDomElement elem = doc.createElement ("usluga");
      elem.setAttribute ("idx", idxEdit->text ());
      elem.setAttribute ("name", nameEdit->text ());
      elem.setAttribute ("code", kodEdit->text ());
      elem.setAttribute ("pkwiu", pkwiuEdit->text ());
      elem.setAttribute ("desc", skrotEdit->text ());
      // elem.setAttribute ("type", "towar");
      elem.setAttribute ("curr", jednCombo->currentText ());
      elem.setAttribute ("netto1", netto[0]);
      elem.setAttribute ("netto2", netto[1]);
      elem.setAttribute ("netto3", netto[2]);
      elem.setAttribute ("netto4", netto[3]);
      // qDebug("2 netto4" + netto[3]);
      elem.setAttribute ("vat", cbVat->currentText ());
      // elem.setAttribute ("vat", vatEdit->text ());
      uslugi.appendChild (elem);
      qDebug ("dodano usluge");
    }


  QString xml = doc.toString ();

  file.close ();
  file.open (QIODevice::WriteOnly);
  QTextStream ts (&file);
  ts.setCodec (QTextCodec::codecForName ("ISO8859-2"));
  ts << xml;
  file.close ();

  return true;
}

void Towary::modifyOnly ()
{
  qDebug (__FUNCTION__);
  nettoChanged ();

  /*
     getFirmList ();
     QStringList::iterator it = allNames.find (nameEdit->text ());
     if ((*it) == nameEdit->text ())
     {
     QMessageBox::critical (0, "GNU Przelewy",
     "Kontrahent nie moze zostaæ dodany poniewa¿ istnieje ju¿ kontrahent o tej nazwie.");
     return;
     }
   */
  QDomDocument doc ("towary");
  QDomElement root;
  QDomElement towary;
  QDomElement uslugi;

  QFile file (progDir + "/towary.xml");
  if (!file.open (QIODevice::ReadOnly))
    {
      qDebug ("can not open ");
      root = doc.createElement ("towary");
      doc.appendChild (root);
      towary = doc.createElement ("towar");
      root.appendChild (towary);
      uslugi = doc.createElement ("usluga");
      root.appendChild (uslugi);
    }
  else
    {
      QTextStream stream (&file);
      if (!doc.setContent (stream.readAll ()))

	{
	  qDebug ("can not set content ");
	  file.close ();
	  // return;¦
	}
      else
	{
	  root = doc.documentElement ();
	  towary = root.firstChild ().toElement ();
	  uslugi = root.lastChild ().toElement ();
	}
    }

  root.lastChild ();
  QString text;

  // towar = 0; usluga = 1;
  if (typeCombo->currentIndex () == 0)
    {
      QDomElement elem;		// = doc.createElement ("firma");
      for (QDomNode n = towary.firstChild (); !n.isNull ();
	   n = n.nextSibling ())
	{
	  text = n.toElement ().attribute ("idx");
	  if (text.compare (idxEdit->text ()) == 0)
	    {
	      elem = n.toElement ();
	      break;
	    }
	}
      elem.setAttribute ("idx", idxEdit->text ());
      elem.setAttribute ("name", nameEdit->text ());
      elem.setAttribute ("desc", skrotEdit->text ());
      elem.setAttribute ("code", kodEdit->text ());
      elem.setAttribute ("pkwiu", pkwiuEdit->text ());
      // elem.setAttribute ("type", "towar");
      elem.setAttribute ("curr", jednCombo->currentText ());
      elem.setAttribute ("netto1", netto[0]);
      elem.setAttribute ("netto2", netto[1]);
      elem.setAttribute ("netto3", netto[2]);
      elem.setAttribute ("netto4", netto[3]);
      // qDebug("2 netto4" + netto[3]);
      elem.setAttribute ("vat", cbVat->currentText ());
      towary.appendChild (elem);
      qDebug ("modyfikacja towary");
    }

  if (typeCombo->currentIndex () == 1)
    {
      QDomElement elem;		//  = doc.createElement ("urzad");
      for (QDomNode n = uslugi.firstChild (); !n.isNull ();
	   n = n.nextSibling ())
	{
	  text = n.toElement ().attribute ("idx");
	  if (text.compare (idxEdit->text ()) == 0)
	    {
	      elem = n.toElement ();
	      break;
	    }
	}
      elem.setAttribute ("idx", idxEdit->text ());
      elem.setAttribute ("name", nameEdit->text ());
      elem.setAttribute ("desc", skrotEdit->text ());
      elem.setAttribute ("code", kodEdit->text ());
      elem.setAttribute ("pkwiu", pkwiuEdit->text ());
      // elem.setAttribute ("type", "towar");
      elem.setAttribute ("curr", jednCombo->currentText ());
      elem.setAttribute ("netto1", netto[0]);
      elem.setAttribute ("netto2", netto[1]);
      elem.setAttribute ("netto3", netto[2]);
      elem.setAttribute ("netto4", netto[3]);
      // qDebug("2 netto4" + netto[3]);
      elem.setAttribute ("vat", cbVat->currentText ());
      uslugi.appendChild (elem);
      qDebug ("modyfikacja uslugi");
    }


  QString xml = doc.toString ();

  file.close ();
  file.open (QIODevice::WriteOnly);
  QTextStream ts (&file);
  ts.setCodec (QTextCodec::codecForName ("ISO8859-2"));
  ts << xml;
  file.close ();

}

/*!
  *  save data to XML file
  !*/
void Towary::okClick ()
{

  if (nameEdit->text () == "")
    {
      QMessageBox::critical (0, "QFaktury", "Musisz podaæ chocia¿ nazwe.");
      return;
    }

  qDebug (__FUNCTION__);
  qDebug ()<<this->windowTitle ().left (4);

  QString pkwiu = pkwiuEdit->text ();
  if (pkwiu == "")
    pkwiu = " ";
  QString skrot = skrotEdit->text ();
  if (skrot == "")
    skrot = " ";
  QString kod = kodEdit->text ();
  if (kod == "")
    kod = " ";

  if (this->windowTitle ().left (4) == "Edyt")
    {
      modifyOnly ();
      QString typ;
      if (typeCombo->currentIndex () == 1)
	{
	  typ = "us³uga";
	}
      else
	typ = "towar";
      ret = idxEdit->text () + "|" + nameEdit->text () + "|" + skrot +
	"|" + kod + "|" + pkwiu + "|" + typ + "|" +
	jednCombo->currentText () + "|" + netto[0] + "|" + netto[1] +
	"|" + netto[2] + "|" + netto[3] + "|" + cbVat->currentText ();
      accept ();
    }
  else
    {
      if (saveAll ())
	{
	  QString typ;
	  if (typeCombo->currentIndex () == 1)
	    {
	      typ = "us³uga";
	    }
	  else
	    typ = "towar";
	  ret = idxEdit->text () + "|" + nameEdit->text () + "|" + skrot +
	    "|" + kod + "|" + pkwiu + "|" + typ + "|" +
	    jednCombo->currentText () + "|" + netto[0] + "|" + netto[1] +
	    "|" + netto[2] + "|" + netto[3] + "|" + cbVat->currentText ();
	  accept ();
	}
    }

}

void Towary::spinChanged (int a)
{
  qDebug (__FUNCTION__);
  nettoEdit->setText (netto[a - 1]);
}


void Towary::nettoChanged ()
{
  qDebug (__FUNCTION__);
  qDebug ()<<nettoEdit->text ();
  netto[spinBox2->value () - 1] = nettoEdit->text ();
}

void Towary::pkwiuGet ()
{
  qDebug (__FUNCTION__);
  // firts we check is KDE working
  QStringList args;
  args += "kfmclient";
  args += "exec";
  args += "http://www.klasyfikacje.pl/";
  // args += "http://www.stat.gov.pl/klasyfikacje/PKWiU/pkwiu.htm";
  
  //X odpalenie przegl¿darki
//  QProcess cmd (args);
//  if (!cmd.start ())
//    {
//      // if not we use GNOME2 api
//      args.clear ();
//      args += "gnome-open";
//      args += "http://www.klasyfikacje.pl/";
//      // args += "http://www.stat.gov.pl/klasyfikacje/PKWiU/pkwiu.htm";
//      QProcess cmd2 (args);
//      cmd2.start ();
//    }
}

Towary::Towary(QWidget *parent): QDialog(parent) {
    setupUi(this);
    init();
}


