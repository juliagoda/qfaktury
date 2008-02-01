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
#include "Kontrahenci.moc"
#include <qmessagebox.h>
#include <qtextcodec.h>
#include <qdir.h>
#include <Qt/qdom.h>
#include <QtDebug>


QString progDir;
QString nazwaEdit;

void Kontrahenci::readData (QString name, QString type)
{
  nazwaEdit = name;
  qDebug ()<<name<< "   " <<type;
  QDomDocument doc ("kontrahenci");
  QDomElement root;
  QDomElement urzad;
  QDomElement firma;

  QFile file (progDir + "/kontrah.xml");
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
	  urzad = root.firstChild ().toElement ();
	  firma = root.lastChild ().toElement ();
	}
      QString text;

      if (type.compare ("firma") == 0)
	{
	  for (QDomNode n = firma.firstChild (); !n.isNull ();
	       n = n.nextSibling ())
	    {
	      text = n.toElement ().attribute ("name");
	      if (text.compare (name) == 0)
		{
		  nameEdit->setText (text);
		  placeEdit->setText (n.toElement ().attribute ("place"));
		  codeEdit->setText (n.toElement ().attribute ("code"));
		  addressEdit->setText (n.toElement ().attribute ("address"));
		  nipEdit->setText (n.toElement ().attribute ("nip"));
		  accountEdit->setText (n.toElement ().attribute ("account"));
		  telefonEdit->setText (n.toElement ().attribute ("telefon"));
		  emailEdit->setText (n.toElement ().attribute ("email"));
		  wwwEdit->setText (n.toElement ().attribute ("www"));
          typeCombo->setCurrentIndex(0);
		  // typeCombo->setCurrentText ("firma");
		}
	    }
	}
      else
	{
	  for (QDomNode n = urzad.firstChild (); !n.isNull ();
	       n = n.nextSibling ())
	    {
	      text = n.toElement ().attribute ("name");
	      if (text.compare (name) == 0)
		{
		  nameEdit->setText (text);
		  placeEdit->setText (n.toElement ().attribute ("place"));
		  codeEdit->setText (n.toElement ().attribute ("code"));
		  addressEdit->setText (n.toElement ().attribute ("address"));
		  nipEdit->setText (n.toElement ().attribute ("nip"));
		  telefonEdit->setText (n.toElement ().attribute ("telefon"));
		  accountEdit->setText (n.toElement ().attribute ("account"));
		  emailEdit->setText (n.toElement ().attribute ("email"));
		  wwwEdit->setText (n.toElement ().attribute ("www"));
          typeCombo->setCurrentIndex(1);
		  //typeCombo->setCurrentText ("Urz±d");
		}
	    }
	}
    }
  setWindowTitle ("Edytuj kontrahenta");
}

void Kontrahenci::getFirmList ()
{
  qDebug (__FUNCTION__);
  QString progDir2 = QDir::homePath () + "/elinux";

  QDomDocument doc ("kontrahenci");
  QDomElement root;
  QDomElement urzad;
  QDomElement firma;

  QFile file (progDir2 + "/kontrah.xml");
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
	  urzad = root.firstChild ().toElement ();
	  firma = root.lastChild ().toElement ();
	}
      QString text;


      for (QDomNode n = firma.firstChild (); !n.isNull ();
	   n = n.nextSibling ())
	{
	  text = n.toElement ().attribute ("name");
	  allNames << text;
	}

      for (QDomNode n = urzad.firstChild (); !n.isNull ();
	   n = n.nextSibling ())
	{
	  text = n.toElement ().attribute ("name");
	  allNames << text;
	}

    }

}


void Kontrahenci::init ()
{
  progDir = QDir::homePath () + "/elinux";
}


bool Kontrahenci::saveAll ()
{
  qDebug (__FUNCTION__);

  getFirmList ();
  if (allNames.indexOf(QRegExp(nameEdit->text(), Qt::CaseSensitive, QRegExp::FixedString)) != -1 )
    {
      QMessageBox::critical (0, "Faktury",
			     "Kontrahent nie moze zostaæ dodany poniewa¿ istnieje ju¿ kontrahent o tej nazwie.");
      return false;
    }

  QDomDocument doc ("kontrahenci");
  QDomElement root;
  QDomElement urzad;
  QDomElement firma;

  QFile file (progDir + "/kontrah.xml");
  if (!file.open (QIODevice::ReadOnly))
    {
      qDebug ("can not open ");
      root = doc.createElement ("kontrahenci");
      doc.appendChild (root);
      urzad = doc.createElement ("urzedy");
      root.appendChild (urzad);
      firma = doc.createElement ("firmy");
      root.appendChild (firma);
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
	  urzad = root.firstChild ().toElement ();
	  firma = root.lastChild ().toElement ();
	}
    }

  root.lastChild ();

  // firma = 0; urzad = 1;
  if (typeCombo->currentIndex () == 0)
    {
      QDomElement elem = doc.createElement ("firma");
      elem.setAttribute ("name", nameEdit->text ());
      elem.setAttribute ("place", placeEdit->text ());
      elem.setAttribute ("code", codeEdit->text ());
      elem.setAttribute ("address", addressEdit->text ());
      elem.setAttribute ("nip", nipEdit->text ());
      elem.setAttribute ("account", accountEdit->text ());
      elem.setAttribute ("telefon", telefonEdit->text ());
      elem.setAttribute ("email", emailEdit->text ());
      elem.setAttribute ("www", wwwEdit->text ());
      firma.appendChild (elem);
      qDebug ("dodano firme");
    }

  if (typeCombo->currentIndex () == 1)
    {
      QDomElement elem = doc.createElement ("urzad");
      elem.setAttribute ("name", nameEdit->text ());
      elem.setAttribute ("place", placeEdit->text ());
      elem.setAttribute ("code", codeEdit->text ());
      elem.setAttribute ("address", addressEdit->text ());
      elem.setAttribute ("nip", nipEdit->text ());
      elem.setAttribute ("account", accountEdit->text ());
      elem.setAttribute ("telefon", telefonEdit->text ());
      elem.setAttribute ("email", emailEdit->text ());
      elem.setAttribute ("www", wwwEdit->text ());
      urzad.appendChild (elem);
      qDebug ("dodano urzad");
    }


  QString xml = doc.toString ();

  file.close ();
  file.open (QIODevice::WriteOnly);
  QTextStream ts (&file);
  ts << xml;
  file.close ();

  return true;
}

void Kontrahenci::modifyOnly ()
{
  qDebug (__FUNCTION__);

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
  QDomDocument doc ("kontrahenci");
  QDomElement root;
  QDomElement urzad;
  QDomElement firma;

  QFile file (progDir + "/kontrah.xml");
  if (!file.open (QIODevice::ReadOnly))
    {
      qDebug ("can not open ");
      root = doc.createElement ("kontrahenci");
      doc.appendChild (root);
      urzad = doc.createElement ("urzedy");
      root.appendChild (urzad);
      firma = doc.createElement ("firmy");
      root.appendChild (firma);
    }
  else
    {
      QTextStream stream (&file);
      if (!doc.setContent (stream.readAll ()))

	{
	  qDebug ("can not set content ");
	  file.close ();
	  // return;
	}
      else
	{
	  root = doc.documentElement ();
	  urzad = root.firstChild ().toElement ();
	  firma = root.lastChild ().toElement ();
	}
    }

  root.lastChild ();
  QString text;

  // firma = 0; urzad = 1;
  if (typeCombo->currentIndex () == 0)
    {
      QDomElement elem;		// = doc.createElement ("firma");
      for (QDomNode n = firma.firstChild (); !n.isNull ();
	   n = n.nextSibling ())
	{
	  text = n.toElement ().attribute ("name");
	  if (text.compare (nazwaEdit) == 0)
	    {
	      elem = n.toElement ();
	      break;
	    }
	}

      elem.setAttribute ("name", nameEdit->text ());
      elem.setAttribute ("place", placeEdit->text ());
      elem.setAttribute ("code", codeEdit->text ());
      elem.setAttribute ("nip", nipEdit->text ());
      elem.setAttribute ("address", addressEdit->text ());
      elem.setAttribute ("account", accountEdit->text ());
      elem.setAttribute ("telefon", telefonEdit->text ());
      elem.setAttribute ("email", emailEdit->text ());
      elem.setAttribute ("www", wwwEdit->text ());
      firma.appendChild (elem);
      qDebug ("modyfikacja firme");
    }

  if (typeCombo->currentIndex () == 1)
    {
      QDomElement elem;		//  = doc.createElement ("urzad");
      for (QDomNode n = urzad.firstChild (); !n.isNull ();
	   n = n.nextSibling ())
	{
	  text = n.toElement ().attribute ("name");
	  if (text.compare (nazwaEdit) == 0)
	    {
	      elem = n.toElement ();
	      break;
	    }
	}
      elem.setAttribute ("name", nameEdit->text ());
      elem.setAttribute ("place", placeEdit->text ());
      elem.setAttribute ("code", codeEdit->text ());
      elem.setAttribute ("address", addressEdit->text ());
      elem.setAttribute ("nip", nipEdit->text ());
      elem.setAttribute ("account", accountEdit->text ());
      elem.setAttribute ("telefon", telefonEdit->text ());
      elem.setAttribute ("email", emailEdit->text ());
      elem.setAttribute ("www", wwwEdit->text ());
      urzad.appendChild (elem);
      qDebug ("modyfikacja urzad");
    }


  QString xml = doc.toString ();

  file.close ();
  file.open (QIODevice::WriteOnly);
  QTextStream ts (&file);
  ts << xml;
  file.close ();

}

QString Kontrahenci::isEmpty (QString in)
{
  if (in == "")
    return "-";
  return in;
}

 /*!
  *  save data to XML file
  !*/
void Kontrahenci::okClick ()
{
  /* TODO
   * validation account must have 26 chars
   */
  if (windowTitle() == "Edytuj kontrahenta")
    {
      modifyOnly ();
      QString typ;
      if (typeCombo->currentIndex () == 1)
	{
	  typ = "urzad";
	}
      else
	typ = "firma";
      ret =
	isEmpty (nameEdit->text ()) + "|" + isEmpty (typ) + "|" +
	isEmpty (placeEdit->text ()) + "|" + isEmpty (addressEdit->text ()) +
	"|" + isEmpty (telefonEdit->text ());
      accept ();
    }
  else
    {
      if (saveAll ())
	{
	  QString typ;
	  if (typeCombo->currentIndex() == 1)
	    {
	      typ = "urzad";
	    }
	  else
	    typ = "firma";
	  ret =
	    isEmpty (nameEdit->text ()) + "|" + isEmpty (typ) + "|" +
	    isEmpty (placeEdit->text ()) + "|" +
	    isEmpty (addressEdit->text ()) + "|" +
	    isEmpty (telefonEdit->text ());
	  accept ();
	}
    }

}


void Kontrahenci::newFunction ()
{

}
Kontrahenci::Kontrahenci(QWidget *parent): QDialog(parent) {
    setupUi(this);
    init();
}
