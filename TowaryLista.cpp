#include "TowaryLista.moc"
#include <qdom.h>
#include <qdir.h>
#include <qmessagebox.h>
#include <qtextcodec.h>

#include "zaokr.h"

class dane
{
public:
  dane ()
  {
  }
  dane (QString c1, QString c2, QString c3)
  {
    code = c1;
    if (code == "")
      code = "-";
    curr = c2;
    if (curr == "")
      curr = "-";
    pkwiu = c3;
    if (pkwiu == "")
      pkwiu = "-";
  }
  QString codeX () const
  {
    return code;
  }
  QString currX () const
  {
    return curr;
  }
  QString pkwiuX () const
  {
    return pkwiu;
  }
private:
    QString code;
  QString curr;
  QString pkwiu;
};

typedef QMap < QString, dane > daneList;
	// EmployeeMap map;
daneList listaTowary2;
daneList listaUslugi2;

QStringList listaTowary;
QStringList listaUslugi;
QString vat;

void TowaryLista::init ()
{
  QTextCodec::setCodecForCStrings (QTextCodec::codecForName ("ISO8859-2"));
  QTextCodec::setCodecForLocale (QTextCodec::codecForName ("ISO8859-2"));    
  ret = "";
  QDir tmp;
  progDir = tmp.homeDirPath () + "/elinux";
  listaTowary.clear ();
  listaUslugi.clear ();
  listaTowary2.clear ();
  listaUslugi2.clear ();
  readTow (progDir);
  listWidget->clear ();
  fillLv (0);
}

void TowaryLista::readTow (QString progDir)
{
  QDomDocument doc ("towary");
  QDomElement root;
  QDomElement towar;
  QDomElement usluga;
  QString code, curr, pkwiu;



  QFile file (progDir + "/towary.xml");
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
	  towar = root.firstChild ().toElement ();
	  usluga = root.lastChild ().toElement ();
	}
      QString text, idx;

      for (QDomNode n = towar.firstChild (); !n.isNull ();
	   n = n.nextSibling ())
	{
	  idx = n.toElement ().attribute ("idx");
	  listaTowary.append (idx);

	  text = n.toElement ().attribute ("name");
	  listaTowary.append (text);

	  code = n.toElement ().attribute ("code");
	  curr = n.toElement ().attribute ("curr");
	  pkwiu = n.toElement ().attribute ("pkwiu");
	  listaTowary2[idx] = dane (code, curr, pkwiu);

	}

      for (QDomNode n = usluga.firstChild (); !n.isNull ();
	   n = n.nextSibling ())
	{
	  idx = n.toElement ().attribute ("idx");
	  listaUslugi.append (idx);

	  text = n.toElement ().attribute ("name");
	  listaUslugi.append (text);

	  code = n.toElement ().attribute ("code");
	  curr = n.toElement ().attribute ("curr");
	  pkwiu = n.toElement ().attribute ("pkwiu");
	  listaUslugi2[idx] = dane (code, curr, pkwiu);
	}
    }
}



void TowaryLista::doAccept ()
{
  if (countEdit->text () == "")
    {
      QMessageBox::information (this, "QFaktury", "Podaj ilo¶æ",
				QMessageBox::Ok);
      return;
    }

  if (selectedItem != "")
    {
// |Index|Nazwa|Kod|Ilo¶æ|Jm|cena jednostkowa|Kwota netto|vat|kwota brutto|
      if (comboBox1->currentItem () == 0)
	{
	  /*
	     int x = listaTowary.findIndex(selectedItem);
	     qDebug( "%d", x );
	     qDebug( selectedItem );
	     qDebug( "code" + listaTowary2[id].codeX() ); 
	     qDebug( "curr" + listaTowary2[id].currX() );
	     qDebug( "pkwiu" + listaTowary2[id].pkwiuX() );
	   */
	  ret =
	    selectedItem + "|" + listaTowary2[id].codeX () + "|" +
	    listaTowary2[id].pkwiuX () + "|" + countEdit->text () + "|" +
	    listaTowary2[id].currX () + "|" + cenaEdit->text () + "|" +
	    nettoLabel->text () + "|" + vat + "|" + bruttoLabel->text ();
	}
      if (comboBox1->currentItem () == 1)
	{
	  // int x = listaUslugi.findIndex(selectedItem);
	  // qDebug( "%d", x );
	  ret =
	    selectedItem + "|" + listaUslugi2[id].codeX () + "|" +
	    listaUslugi2[id].pkwiuX () + "|" + countEdit->text () + "|" +
	    listaUslugi2[id].currX () + "|" + cenaEdit->text () + "|" +
	    nettoLabel->text () + "|" + vat + "|" + bruttoLabel->text ();

	}
      accept ();
    }
  else
    {
      QMessageBox::information (this, "QFaktury", "Wska¿ towar",
				QMessageBox::Ok);
    }
}

void TowaryLista::comboBox1Changed (int x)
{
  qDebug (__FUNCTION__);
  listWidget->clear ();
  fillLv (x);
}

void TowaryLista::calcNetto ()
{
  QString brutto1 = QString::number (getPrice (countEdit->text (),
					       cenaEdit->text (), vat));
  bruttoLabel->setText (fixStr (brutto1));

  QString netto1 = QString::number (getPrice2 (countEdit->text (),
					       cenaEdit->text ()));
  nettoLabel->setText (fixStr (netto1));
}


void TowaryLista::fillLv (int x)
{
  bool next = true;
  QListWidgetItem *tmp = NULL;
  switch (x)
    {
    case 0:
      for (uint i = 0; i < listaTowary.count (); ++i)
	{
        listWidget->addItem(listaTowary[i]);
//	  if (next)
//	    {
//	      tmp = new QListWidgetItem (listWidget, listaTowary[i]);
//	      next = false;
//	    }
//	  else
//	    {
//	      tmp->setText (1, listaTowary[i]);
//	      next = true;
//	    }

	}
      break;
    case 1:
      for (uint i = 0; i < listaUslugi.count (); ++i)
	{
        listWidget->addItem(listaUslugi[i]);
//	  if (next)
//	    {
//	      tmp = new QListWidgetItem (listWidget, listaUslugi[i]);
//	      next = false;
//	    }
//	  else
//	    {
//	      tmp->setText (1, listaUslugi[i]);
//	      next = true;
//	    }

	}
      break;

    }
}

void TowaryLista::lv1selChanged (QListWidgetItem * item)
{
  if (item->isSelected ())
    {
      readNettos (item->text (0));
      id = item->text (0);
      selectedItem = item->text (1);
      calcNetto ();
    }
}

void TowaryLista::readNettos (QString index)
{
  QDomDocument doc ("towary");
  QDomElement root;
  QDomElement towar;
  QDomElement usluga;

  QFile file (progDir + "/towary.xml");
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
	  towar = root.firstChild ().toElement ();
	  usluga = root.lastChild ().toElement ();
	}
      QString text;

      if (comboBox1->currentItem () == 0)
	{
	  for (QDomNode n = towar.firstChild (); !n.isNull ();
	       n = n.nextSibling ())
	    {

	      text = n.toElement ().attribute ("idx");
	      if (text == index)
		{
		  nettos[0] = n.toElement ().attribute ("netto1");
		  nettos[1] = n.toElement ().attribute ("netto2");
		  nettos[2] = n.toElement ().attribute ("netto3");
		  nettos[3] = n.toElement ().attribute ("netto4");
		  cenaEdit->setText (nettos[0]);
		  spinBox2->setValue (1);
		  vat = n.toElement ().attribute ("vat");
		}
	    }
	}

      if (comboBox1->currentItem () == 1)
	{

	  for (QDomNode n = usluga.firstChild (); !n.isNull ();
	       n = n.nextSibling ())
	    {
	      text = n.toElement ().attribute ("idx");
	      if (text == index)
		{
		  nettos[0] = n.toElement ().attribute ("netto1");
		  nettos[1] = n.toElement ().attribute ("netto2");
		  nettos[2] = n.toElement ().attribute ("netto3");
		  nettos[3] = n.toElement ().attribute ("netto4");
		  cenaEdit->setText (nettos[0]);
		  spinBox2->setValue (1);
		  vat = n.toElement ().attribute ("vat");
		}
	    }
	}
    }


}


void TowaryLista::spinChanged (int a)
{
  // qDebug (__FUNCTION__);
  cenaEdit->setText (nettos[a - 1]);
  calcNetto ();
}
TowaryLista::TowaryLista(QWidget *parent): QDialog(parent) {
    setupUi(this);
    init();
}
