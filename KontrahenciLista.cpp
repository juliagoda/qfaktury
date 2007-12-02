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
#include "KontrahenciLista.moc"
#include <qdom.h>
#include <qdir.h>
#include <qmessagebox.h>
#include <qtextcodec.h>

QStringList listaFirmy;

QStringList listaUrzedy;

void KontrahenciLista::init ()
{
  QTextCodec::setCodecForCStrings (QTextCodec::codecForName ("ISO8859-2"));
  QTextCodec::setCodecForLocale (QTextCodec::codecForName ("ISO8859-2"));
  QTextCodec::setCodecForTr (QTextCodec::codecForName ("ISO8859-2"));
    
  QDir tmp;
  QString progDir = tmp.homeDirPath () + "/elinux";
  listaFirmy.clear ();
  listaUrzedy.clear ();
  readKontr (progDir);
  listBox1->clear ();
  listBox1->insertStringList ( (QStringList &)listaFirmy);
}

void KontrahenciLista::readKontr (QString progDir)
{
  QDomDocument doc ("kontrahenci");
  QDomElement root;
  QDomElement urzad;
  QDomElement firma;

  QFile file (progDir + "/kontrah.xml");
  if (!file.open (IO_ReadOnly))
    {
      qDebug ("file doesn't exists");
      return;

    }
  else
    {
      QTextStream stream (&file);
      if (!doc.setContent (stream.read ()))
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

	  text =  n.toElement ().attribute ("name");
	  text +=  ", " + n.toElement ().attribute ("code");
	  text +=  " " + n.toElement ().attribute ("place");
	  text +=  ", ul. " + n.toElement ().attribute ("address");
	  text +=  ", NIP: " + n.toElement ().attribute ("nip");
	  listaFirmy.append ( text );
	}

      for (QDomNode n = urzad.firstChild (); !n.isNull ();
	   n = n.nextSibling ())
	{

	  text = n.toElement ().attribute ("name") ;
	  text += ", " + n.toElement ().attribute ("code") ;
	  text += " " + n.toElement ().attribute ("place") ;
	  text += ", ul. " + n.toElement ().attribute ("address") ;
	  text += ", NIP: " + n.toElement ().attribute ("nip") ;
	  listaUrzedy.append (text);
	}
    }
}


void KontrahenciLista::doAccept ()
{
  int selNr, posCount = listBox1->count ();
  bool hasSel = false;
  for (selNr = 0; selNr < posCount; ++selNr)
    {
      if (listBox1->isSelected (selNr))
	{
	  hasSel = true;
	  break;
	}
    }

  if (hasSel)
    {
      ret = listBox1->currentText ();
      accept ();
    }
  else
    {
      QMessageBox::information (this, "QFaktury", "Wska¿ kontrahenta.",
				QMessageBox::Ok);
    }
}

void KontrahenciLista::comboBox1Changed ()
{
  qDebug (__FUNCTION__);
  listBox1->clear ();
  switch (comboBox1->currentItem ())
    {
    case 0:
      listBox1->insertStringList ((QStringList &)listaFirmy);
      break;
    case 1:
      listBox1->insertStringList ((QStringList &)listaUrzedy);
      break;
    }
}
KontrahenciLista::KontrahenciLista(QWidget *parent): QDialog(parent) {
    setupUi(this);
    init();
}
