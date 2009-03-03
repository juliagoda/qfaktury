#include "Towary.moc"
#include <qtextcodec.h>
#include <qdir.h>
#include <Qt/qdom.h>
#include <qprocess.h>
#include "Settings.h"
#include <qmessagebox.h>
#include <QtDebug>

/** Constructor
 */
Towary::Towary(QWidget *parent): QDialog(parent) {
    setupUi(this);
    init();
}


void Towary::init() {
	readData("", "");
	idxEdit->setText(QString::number(lastId));
	// cbVat->setCurrentText ("22");
	jednCombo->addItems(sett().value("jednostki").toString().split("|"));
	cbVat->addItems(sett().value("stawki").toString().split("|"));

	connect(okButton, SIGNAL(clicked()), this, SLOT(okClick()));
	connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
	connect(nettoEdit, SIGNAL(lostFocus()), this, SLOT(nettoChanged()));
	connect(spinBox2, SIGNAL(valueChanged(int)), this, SLOT(spinChanged(int)));
	connect(pkwiuBtn, SIGNAL(clicked()), this, SLOT(pkwiuGet()));
}

void Towary::readData (QString idx, QString type)
{
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
      setWindowTitle (UTF8("Edytuj towar/usługi"));
    }

  lastId = 1;
  idxEdit->setText (idx);
  QDomDocument doc ("towary");
  QDomElement root;
  QDomElement towar;
  QDomElement usluga;

  QFile file (sett().getProductsXml());
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
		  typeCombo->setCurrentIndex(0); //X Text ("us�uga");
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
  QDomDocument doc ("towary");
  QDomElement root;
  QDomElement towar;
  QDomElement usluga;

  QFile file (sett().getProductsXml());
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



bool Towary::saveAll ()
{
  nettoChanged ();

  // getStuffList ();
  /*
     // nie robimy sprawdzania nazwy
     QStringList::iterator it = allNames.find (nameEdit->text ());
     if ((*it) == nameEdit->text ())
     {
     QMessageBox::critical (0, "Faktury",
     "Towar nie moze zosta� dodany poniewa� istnieje ju� kontrahent o tej nazwie.");
     return false;
     }
   */

  QDomDocument doc ("towary");
  QDomElement root;
  QDomElement towary;
  QDomElement uslugi;

  QFile file (sett().getProductsXml());
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
	  // return;�
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
  nettoChanged ();

  QDomDocument doc ("towary");
  QDomElement root;
  QDomElement towary;
  QDomElement uslugi;

  QFile file (sett().getProductsXml());
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
	  return;
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
      QMessageBox::critical (0, "QFaktury", UTF8("Musisz podać nazwe."));
      return;
    }


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
	  typ = "us�uga";
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
	      typ = "us�uga";
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
  nettoEdit->setText (netto[a - 1]);
}


void Towary::nettoChanged ()
{
  qDebug ()<<nettoEdit->text ();
  netto[spinBox2->value () - 1] = nettoEdit->text ();
}

void Towary::pkwiuGet ()
{
  // firts we check is KDE working
  QStringList args;
  args += "kfmclient";
  args += "exec";
  args += "http://www.klasyfikacje.pl/";
  // args += "http://www.stat.gov.pl/klasyfikacje/PKWiU/pkwiu.htm";

  //X odpalenie przegl�darki
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



