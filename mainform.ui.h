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

#include <qtextcodec.h>
#include <qdir.h>
#include <qmessagebox.h>
#include <qsettings.h>
#include <qapplication.h>
#include <qevent.h>
#include <qprocess.h>
#include <qdom.h>

#include "kontr.h"
#include "kreator.h"
#include "mainform.h"
#include "preview.h"
#include "sett.h"
#include "user.h"
#include "towary.h"
#include "fraform.h"
#include "korform.h"


QString pdGlob;

void
Form1::init ()
{
  QTextCodec::setCodecForCStrings (QTextCodec::codecForName ("ISO8859-2"));
  QTextCodec::setCodecForLocale (QTextCodec::codecForName ("ISO8859-2"));    
 //  create local user directory for store xml files
  // works only on Linux -> see also licence Qt 3
  QDir tmp;
  QString progDir = tmp.homeDirPath () + "/elinux";
  pdGlob = progDir;
  // qDebug(progDir);
  if (!tmp.exists (progDir))
    {
      tmp.mkdir (progDir, TRUE);
      tmp.mkdir (progDir + "/faktury", TRUE);
    }


  if (!tmp.exists (progDir + "/faktury"))
    {
      tmp.mkdir (progDir + "/faktury", TRUE);
    }

  // first run
  if (firstRun ())  saveAllSett();
  // first run

  readKontr (progDir);
  readHist (progDir);
  readTw (progDir);

  // towary/.uslugi - wymiary
  tableT->setColumnWidth (0, 50);
  tableT->setColumnWidth (1, 140);
  tableT->setColumnWidth (3, 40);
  tableT->setColumnWidth (4, 60);
  tableT->setColumnWidth (5, 50);
  // tableT->setColumnWidth(5, 50);
  tableT->setColumnWidth (6, 55);	// netto1
  tableT->setColumnWidth (7, 55);	// netto2
  tableT->setColumnWidth (8, 55);	// netto3
  tableT->setColumnWidth (9, 55);	// netto4
  tableT->setColumnWidth (10, 55);
}



bool
Form1::firstRun ()
{
  qDebug (__FUNCTION__);
  QSettings settings;
  bool ok;
  settings.readEntry ("elinux/faktury/firstrun", "", &ok);
  if (ok == 0)
    {
      return true;
    }
  else
    return false;
}

void
Form1::tableClear (QTable * tab)
{
  int x = tab->numRows ();
  for (int i = x; i >= 0; --i)
    tab->removeRow (i);
}

void
Form1::tabChanged (QWidget * aaa)
{
  if (tabWidget2->indexOf (aaa) == 0)
    {
      kontrahenciDodajAction->setEnabled (false);
      kontrahenciEdycjaAction->setEnabled (false);
      kontrahenciUsunAction->setEnabled (false);
      towaryDodajAction->setEnabled (false);
      towaryEdycjaAction->setEnabled (false);
      towaryUsunAction->setEnabled (false);
      fakturyEdAction->setEnabled (true);
      fakturyUsunAction->setEnabled (true);
// qDebug("Historia");
    }
  if (tabWidget2->indexOf (aaa) == 1)
    {
      kontrahenciDodajAction->setEnabled (true);
      kontrahenciEdycjaAction->setEnabled (true);
      kontrahenciUsunAction->setEnabled (true);
      towaryDodajAction->setEnabled (false);
      towaryEdycjaAction->setEnabled (false);
      towaryUsunAction->setEnabled (false);
      fakturyEdAction->setEnabled (false);
      fakturyUsunAction->setEnabled (false);
    }
  if (tabWidget2->indexOf (aaa) == 2)
    {
      kontrahenciDodajAction->setEnabled (false);
      kontrahenciEdycjaAction->setEnabled (false);
      kontrahenciUsunAction->setEnabled (false);
      towaryDodajAction->setEnabled (true);
      towaryEdycjaAction->setEnabled (true);
      towaryUsunAction->setEnabled (true);
      fakturyEdAction->setEnabled (false);
      fakturyUsunAction->setEnabled (false);
    }

}

void
Form1::readHist (QString progDir)
{
  /*!
   * step one: get list of files from directory
   */
  QDir allFiles;
  QString text;

  QDomDocument doc ("faktury");
  QDomElement root;
  QDomElement nadawca;
  QDomElement odbiorca;

  allFiles.setPath (progDir + "/faktury/");
  allFiles.setFilter (QDir::Files);
  allFiles.setNameFilter ("h*.xml");
  QStringList pliczki = allFiles.entryList ();
  int i, max = pliczki.count ();
  for (i = 0; i < max; ++i)
    {
      // qDebug(pliczki[i]);
      tableH->insertRows (tableH->numRows (), 1);
      text = pliczki[i];
      tableH->setText (tableH->numRows () - 1, 0, text);

      QFile file (progDir + "/faktury/" + pliczki[i]);

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
	      // qDebug ("can not set content ");
	      // qDebug( file.name() );
	      file.close ();
	      // return;
	    }
	}

      root = doc.documentElement ();
      tableH->setText (tableH->numRows () - 1, 1,
		       root.attribute ("nr", "NULL"));
      tableH->setText (tableH->numRows () - 1, 2,
		       root.attribute ("data.sprzed", "NULL"));
      tableH->setText (tableH->numRows () - 1, 3,
  		       root.attribute ("type", "NULL"));
      QDomNode nab;
      nab = root.firstChild();
      nab = nab.toElement().nextSibling();
      tableH->setText (tableH->numRows () - 1, 4,
		       nab.toElement().attribute ("nazwa", "NULL"));
      tableH->setText (tableH->numRows () - 1, 5,
		       nab.toElement().attribute ("nip", "NULL"));
    }

}

void
Form1::aboutQt ()
{
  QMessageBox::aboutQt (this, "QFaktury");
}

void
Form1::oProg ()
{
  QMessageBox::about (this, "QFaktury v0.0.1 beta",
        "Program do wystawiania faktur. \n Koordynator projektu: \n\tGrzegorz Rêkawek www.e-linux.pl \n Programista:\n\tTomasz 'moux' Pielech \nGrafika:\n\tDariusz Arciszewski \n\nSupport: info@e-linux.pl");		  
}

void
Form1::editFHist ()
{
  qDebug( __FUNCTION__ );
  
  QSettings settings;
  
  int row, max = tableH->numRows ();
  for (row = 0; row < max; ++row)
    {
      if (tableH->isRowSelected (row))
	break;
    }
    // qDebug (__FUNCTION__);

  if (tableH->text(row, 3) == "korekta"){
      // QMessageBox::information( this, "QFaktury", "Jeszcze nie ma", QMessageBox::Ok );
	korForm *korWindow = new korForm;
	korWindow->progDir2 = pdGlob;
	korWindow->readData (tableH->text (row, 0));
	if (korWindow->exec () == QDialog::Accepted)
	{
	    QStringList rowTxt = QStringList::split ("|", korWindow->ret);
	    tableH->setText (row, 0, rowTxt[0]);	// file name
	    tableH->setText (row, 1, rowTxt[1]);	// symbol
	    tableH->setText (row, 2, rowTxt[2]);	// date
	    tableH->setText (row, 3, rowTxt[3]);	// type
	    tableH->setText (row, 4, rowTxt[4]);	// nabywca
	    tableH->setText (row, 5, rowTxt[5]);	// NIP
	}
    }
      
  
  if ((tableH->text(row, 3) == "FVAT")
      || (tableH->text(row, 3) == "FPro"))
    {
      // qDebug ("%s %s:%d", __FUNCTION__, __FILE__, __LINE__);
      FormFra *fraWindow = new FormFra;
      fraWindow->progDir2 = pdGlob;
      qDebug( pdGlob );
      int co = 0;
      if (tableH->text (row, 3) == "FVAT")
	co = 0;
      else
	co = 1;
      fraWindow->readData (tableH->text (row, 0), co);
      if (fraWindow->exec () == QDialog::Accepted)
	{
	  // tableH->insertRows (tableH->numRows (), 1);
	     QStringList rowTxt = QStringList::split( "|",  fraWindow->ret );
	     tableH->setText (row, 0, rowTxt[0]); // file name
	     tableH->setText (row, 1, rowTxt[1]); // symbol
	     tableH->setText (row, 2, rowTxt[2]); // date
	     tableH->setText (row, 3, rowTxt[3]); // type
	     tableH->setText (row, 4, rowTxt[4]); // nabywca
	     tableH->setText (row, 5, rowTxt[5]); // NIP
	}
    }
}


void
Form1::delFHist ()
{
  if (QMessageBox::
      warning (this, "QFaktury",
	       "Czy napewno chcesz usun±æ t± fakturê z historii?", "Tak",
	       "Nie", 0, 0, 1) == 0)
    {

      int row, max = tableH->numRows ();
      for (row = 0; row < max; ++row)
	{
	  if (tableH->isRowSelected (row))
	    break;
	}
      qDebug (tableH->text (row, 0));

      QFile file (pdGlob + "/faktury/" + tableH->text (row, 0));
      if (file.exists ())
	file.remove ();
      tableH->removeRow (row);
    }

}

void
Form1::readKontr (QString progDir)
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
	  tableK->insertRows (tableK->numRows (), 1);
	  text = n.toElement ().attribute ("name");
	  tableK->setText (tableK->numRows () - 1, 0, text);
	  text = "firma";
	  tableK->setText (tableK->numRows () - 1, 1, text);
	  text = n.toElement ().attribute ("place");
	  tableK->setText (tableK->numRows () - 1, 2, text);
	  text = n.toElement ().attribute ("address");
	  tableK->setText (tableK->numRows () - 1, 3, text);
	  text = n.toElement ().attribute ("telefon");
	  tableK->setText (tableK->numRows () - 1, 4, text);
	}

      for (QDomNode n = urzad.firstChild (); !n.isNull ();
	   n = n.nextSibling ())
	{
	  tableK->insertRows (tableK->numRows (), 1);
	  text = n.toElement ().attribute ("name");
	  tableK->setText (tableK->numRows () - 1, 0, text);
	  text = "urzad";
	  tableK->setText (tableK->numRows () - 1, 1, text);
	  text = n.toElement ().attribute ("place");
	  tableK->setText (tableK->numRows () - 1, 2, text);
	  text = n.toElement ().attribute ("address");
	  tableK->setText (tableK->numRows () - 1, 3, text);
	  text = n.toElement ().attribute ("telefon");
	  tableK->setText (tableK->numRows () - 1, 4, text);
	}
    }
}

void
Form1::readTw (QString progDir)
{
  QDomDocument doc ("towary");
  QDomElement root;
  QDomElement towary;
  QDomElement uslugi;

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
	  qDebug ("can't set content ");
	  file.close ();
	  return;
	}
      else
	{
	  root = doc.documentElement ();
	  towary = root.firstChild ().toElement ();
	  uslugi = root.lastChild ().toElement ();
	}
      QString text;

      for (QDomNode n = towary.firstChild (); !n.isNull ();
	   n = n.nextSibling ())
	{

	  tableT->insertRows (tableT->numRows (), 1);
	  text = n.toElement ().attribute ("idx");
	  tableT->setText (tableT->numRows () - 1, 0, text);
	  // text = "towar";
	  text = n.toElement ().attribute ("name");
	  tableT->setText (tableT->numRows () - 1, 1, text);
	  text = n.toElement ().attribute ("desc");
	  tableT->setText (tableT->numRows () - 1, 2, text);
	  text = n.toElement ().attribute ("code");
	  tableT->setText (tableT->numRows () - 1, 3, text);
	  text = n.toElement ().attribute ("pkwiu");
	  tableT->setText (tableT->numRows () - 1, 4, text);
	  text = "towar";
	  tableT->setText (tableT->numRows () - 1, 5, text);
	  text = n.toElement ().attribute ("curr");
	  tableT->setText (tableT->numRows () - 1, 6, text);
	  text = n.toElement ().attribute ("netto1");
	  tableT->setText (tableT->numRows () - 1, 7, text);
	  text = n.toElement ().attribute ("netto2");
	  tableT->setText (tableT->numRows () - 1, 8, text);
	  text = n.toElement ().attribute ("netto3");
	  tableT->setText (tableT->numRows () - 1, 9, text);
	  text = n.toElement ().attribute ("netto4");
	  tableT->setText (tableT->numRows () - 1, 10, text);
	  text = n.toElement ().attribute ("vat");
	  tableT->setText (tableT->numRows () - 1, 11, text);
	}

      for (QDomNode n = uslugi.firstChild (); !n.isNull ();
	   n = n.nextSibling ())
	{

	  tableT->insertRows (tableT->numRows (), 1);
	  text = n.toElement ().attribute ("idx");
	  tableT->setText (tableT->numRows () - 1, 0, text);
	  // text = "towar";
	  text = n.toElement ().attribute ("name");
	  tableT->setText (tableT->numRows () - 1, 1, text);
	  text = n.toElement ().attribute ("desc");
	  tableT->setText (tableT->numRows () - 1, 2, text);
	  text = n.toElement ().attribute ("code");
	  tableT->setText (tableT->numRows () - 1, 3, text);
	  text = n.toElement ().attribute ("pkwiu");
	  tableT->setText (tableT->numRows () - 1, 4, text);
	  text = "us³uga";
	  tableT->setText (tableT->numRows () - 1, 5, text);
	  text = n.toElement ().attribute ("curr");
	  tableT->setText (tableT->numRows () - 1, 6, text);
	  text = n.toElement ().attribute ("netto1");
	  tableT->setText (tableT->numRows () - 1, 7, text);
	  text = n.toElement ().attribute ("netto2");
	  tableT->setText (tableT->numRows () - 1, 8, text);
	  text = n.toElement ().attribute ("netto3");
	  tableT->setText (tableT->numRows () - 1, 9, text);
	  text = n.toElement ().attribute ("netto4");
	  tableT->setText (tableT->numRows () - 1, 10, text);
	  text = n.toElement ().attribute ("vat");
	  tableT->setText (tableT->numRows () - 1, 11, text);
	}
    }
}


void
Form1::daneFirmyClick ()
{
  qDebug ("%s %s:%d", __FUNCTION__, __FILE__, __LINE__);
  Form2 *daneFirmyWindow = new Form2;
  daneFirmyWindow->show ();
}

void
Form1::settClick ()
{
  qDebug ("%s %s:%d", __FUNCTION__, __FILE__, __LINE__);
  Form7 *settWindow = new Form7;
  settWindow->show ();
}

void
Form1::kretorClick ()
{
  qDebug ("%s %s:%d", __FUNCTION__, __FILE__, __LINE__);
//     QMessageBox::information( this, "QFaktury", "Funkcja jeszcze nie gotowa. Uzyj menu faktury->Nowy", QMessageBox::Ok );
  Form3 *kreatorWindow = new Form3;
  if (kreatorWindow->exec () == QDialog::Accepted)
    {
      kreatorWindow->print ();
      // tableClear (tableH);
      // readHist (pdGlob);
      /*
         QStringList row = QStringList::split( "|",  kreatorWindow->ret );
         tableH->insertRows (tableH->numRows (), 1);
         tableH->setText (tableH->numRows () - 1, 0, row[0]); // nazwa pliku
         tableH->setText (tableH->numRows () - 1, 1, row[1]); 
         tableH->setText (tableH->numRows () - 1, 2, row[2]); 
         tableH->setText (tableH->numRows () - 1, 4, row[3]); 
         tableH->setText (tableH->numRows () - 1, 3, row[4]); 
       */
    }
  // delete kreatorWindow;
}

void
Form1::kontrClick ()
{
  qDebug ("%s %s:%d", __FUNCTION__, __FILE__, __LINE__);
  Form4 *kontrWindow = new Form4;
  if (kontrWindow->exec () == QDialog::Accepted)
    {
      // tableClear (tableK);
      QDir tmp;
      QString progDir = tmp.homeDirPath () + "/elinux";
      qDebug (progDir);
      tmp.mkdir (progDir, TRUE);

      // readKontr (progDir);
      tableK->insertRows (tableK->numRows (), 1);
      QStringList row = QStringList::split ("|", kontrWindow->ret);
      tableK->setText (tableK->numRows () - 1, 0, row[0]);	// name
      tableK->setText (tableK->numRows () - 1, 1, row[1]);	// type
      tableK->setText (tableK->numRows () - 1, 2, row[2]);	// place
      tableK->setText (tableK->numRows () - 1, 3, row[3]);	// address
      tableK->setText (tableK->numRows () - 1, 4, row[4]);	// telefon
    }
}

void
Form1::kontrDel ()
{
  if (QMessageBox::
      warning (this, "QFaktury",
	       "Czy napewno chcesz usun±æ tego kontrahenta?", "Tak", "Nie", 0,
	       0, 1) == 0)
    {

      QDomDocument doc ("kontrahenci");
      QDomElement root;
      QDomElement urzad;
      QDomElement firma;
      int row, max = tableK->numRows ();

      for (row = 0; row < max; ++row)
	{
	  if (tableK->isRowSelected (row))
	    break;
	}

      QFile file (pdGlob + "/kontrah.xml");
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
	      if (n.toElement ().attribute ("name").
		  compare (tableK->text (row, 0)) == 0)
		{
		  firma.removeChild (n);
		  break;
		}
	    }

	  for (QDomNode n = urzad.firstChild (); !n.isNull ();
	       n = n.nextSibling ())
	    {
	      // qDebug("aaa");
	      if (n.toElement ().attribute ("name").
		  compare (tableK->text (row, 0)) == 0)
		{
		  urzad.removeChild (n);
		  break;
		}
	    }


	  QString xml = doc.toString ();
	  file.close ();
	  file.open (IO_WriteOnly);
	  QTextStream ts (&file);
	  ts << xml;

	  file.close ();
	  tableK->removeRow (row);
	  // 
	  // tableClear (tableK);
	  // QDir tmp;
	  // QString progDir = tmp.homeDirPath () + "/elinux";
	  // qDebug (progDir);
	  // readKontr (progDir);
	}

    }
}

void
Form1::kontrEd ()
{
  qDebug ("%s %s:%d", __FUNCTION__, __FILE__, __LINE__);
  int row, max = tableK->numRows ();

  for (row = 0; row < max; ++row)
    {
      if (tableK->isRowSelected (row))
	break;
    }
  qDebug (tableK->text (row, 0));

  Form4 *kontrWindow = new Form4;
  kontrWindow->readData (tableK->text (row, 0), tableK->text (row, 1));
  if (kontrWindow->exec () == QDialog::Accepted)
    {
      /*
         tableClear (tableK);
         QDir tmp;
         QString progDir = tmp.homeDirPath () + "/elinux";
         qDebug (progDir);
         readKontr (progDir);
       */
      QStringList rowTxt = QStringList::split ("|", kontrWindow->ret);
      tableK->setText (row, 0, rowTxt[0]);	// name
      tableK->setText (row, 1, rowTxt[1]);	// type
      tableK->setText (row, 2, rowTxt[2]);	// place
      tableK->setText (row, 3, rowTxt[3]);	// address
      tableK->setText (row, 4, rowTxt[4]);	// telefon
    }
}


void
Form1::newFra ()
{
  qDebug ("%s %s:%d", __FUNCTION__, __FILE__, __LINE__);
  FormFra *fraWindow = new FormFra;
  fraWindow->progDir2 = pdGlob;
  fraWindow->pforma = false;
  if (fraWindow->exec () == QDialog::Accepted)
    {
      tableH->insertRows (tableH->numRows (), 1);
      QStringList row = QStringList::split ("|", fraWindow->ret);
      tableH->setText (tableH->numRows () - 1, 0, row[0]);	// file name
      tableH->setText (tableH->numRows () - 1, 1, row[1]);	// symbol
      tableH->setText (tableH->numRows () - 1, 2, row[2]);	// date
      tableH->setText (tableH->numRows () - 1, 3, row[3]);	// type
      tableH->setText (tableH->numRows () - 1, 4, row[4]);	// nabywca
      tableH->setText (tableH->numRows () - 1, 5, row[5]);	// NIP
    }
}


void
Form1::newPForm ()
{
  qDebug ("%s %s:%d", __FUNCTION__, __FILE__, __LINE__);
  FormFra *fraWindow = new FormFra;
  fraWindow->progDir2 = pdGlob;
  fraWindow->pforma = true;
  fraWindow->setCaption("Faktura Pro Forma");
  fraWindow->backBtnClick();
  if (fraWindow->exec () == QDialog::Accepted)
    {
      tableH->insertRows (tableH->numRows (), 1);
      QStringList row = QStringList::split ("|", fraWindow->ret);
      tableH->setText (tableH->numRows () - 1, 0, row[0]);	// file name
      tableH->setText (tableH->numRows () - 1, 1, row[1]);	// symbol
      tableH->setText (tableH->numRows () - 1, 2, row[2]);	// date
      tableH->setText (tableH->numRows () - 1, 3, row[3]);	// type
      tableH->setText (tableH->numRows () - 1, 4, row[4]);	// nabywca
      tableH->setText (tableH->numRows () - 1, 5, row[5]);	// NIP
    }
}


void
Form1::newKor ()
{
    qDebug ("%s %s:%d", __FUNCTION__, __FILE__, __LINE__);
    
    qDebug( __FUNCTION__ );
    int row, max = tableH->numRows ();
    for (row = 0; row < max; ++row)
    {
	if (tableH->isRowSelected (row))
	    break;
    }
    // qDebug (__FUNCTION__);
    
    if ((tableH->text(row, 3) == "FVAT"))
	{
	korForm *korWindow = new korForm;
	// qDebug( pdGlob );
	korWindow->progDir2 = pdGlob;
	korWindow->readDataNewKor (tableH->text (row, 0));
	if (korWindow->exec () == QDialog::Accepted)
	{
	    tableH->insertRows (tableH->numRows (), 1);
	    QStringList row = QStringList::split ("|", korWindow->ret);
	    tableH->setText (tableH->numRows () - 1, 0, row[0]);	// file name
	    tableH->setText (tableH->numRows () - 1, 1, row[1]);	// symbol
	    tableH->setText (tableH->numRows () - 1, 2, row[2]);	// date
	    tableH->setText (tableH->numRows () - 1, 3, row[3]);	// type
	    tableH->setText (tableH->numRows () - 1, 4, row[4]);	// nabywca
	    tableH->setText (tableH->numRows () - 1, 5, row[5]);	// NIP
	}
    }
    if ((tableH->text(row, 3) == "korekta"))
	{
	QMessageBox::information( this, "QFaktury", "Do korekt nie wystawiamy korekt", QMessageBox::Ok );
    }
    if ((tableH->text(row, 3) == "FPro"))
	{
	QMessageBox::information( this, "QFaktury", "Do faktur Pro Forma nie wystawiamy korekt", QMessageBox::Ok );
    }
}

void
Form1::closeEvent (QCloseEvent * e)
{
  if (QMessageBox::
      warning (this, "QFaktury",
	       "Czy chcesz wyj¶æ z programu?", "Tak", "Nie", 0, 0, 1) == 0)
    {
      e->accept ();
    }
}

void
Form1::pomoc ()
{
  qDebug (__FUNCTION__);
  // firts we check is KDE working
  QStringList args;
  args += "kfmclient";
  args += "exec";
  args += "http://www.e-linux.pl/modules/qfaktury/index.php";
  QProcess cmd (args);
  if (!cmd.start ())
    {
      // if not we use GNOME2 api
      args.clear ();
      args += "gnome-open";
      args += "http://www.e-linux.pl/modules/qfaktury/index.php";
      QProcess cmd2 (args);
      cmd2.start ();
    }
}

void
Form1::towaryDodaj ()
{
// 
  qDebug ("%s %s:%d", __FUNCTION__, __FILE__, __LINE__);
  twAdd *towWindow = new twAdd;
  if (towWindow->exec () == QDialog::Accepted)
    {
      /*
         tableClear (tableT);
         QDir tmp;
         QString progDir = tmp.homeDirPath () + "/elinux";
         qDebug (progDir);
         tmp.mkdir (progDir, TRUE);
         readTw (progDir);
       */
      tableT->insertRows (tableT->numRows (), 1);
      QStringList row = QStringList::split ("|", towWindow->ret);
      tableT->setText (tableT->numRows () - 1, 0, row[0]);
      tableT->setText (tableT->numRows () - 1, 1, row[1]);
      tableT->setText (tableT->numRows () - 1, 2, row[2]);
      tableT->setText (tableT->numRows () - 1, 3, row[3]);
      tableT->setText (tableT->numRows () - 1, 4, row[4]);
      tableT->setText (tableT->numRows () - 1, 5, row[5]);
      tableT->setText (tableT->numRows () - 1, 6, row[6]);
      tableT->setText (tableT->numRows () - 1, 7, row[7]);
      tableT->setText (tableT->numRows () - 1, 8, row[8]);
      tableT->setText (tableT->numRows () - 1, 9, row[9]);
      tableT->setText (tableT->numRows () - 1, 10, row[10]);
      tableT->setText (tableT->numRows () - 1, 11, row[11]);
    }
}

void
Form1::towaryUsun ()
{

  int row, max = tableK->numRows ();

  for (row = 0; row < max; ++row)
    {
      if (tableT->isRowSelected (row))
	break;
    }


  if (QMessageBox::
      warning (this, "QFaktury",
	       "Czy napewno chcesz usun±æ towar " + tableT->text (row,
								  0) + "/" +
	       tableT->text (row, 1) + "?", "Tak", "Nie", 0, 0, 1) == 0)
    {

      QDomDocument doc ("towary");
      QDomElement root;
      QDomElement towary;
      QDomElement uslugi;

      QFile file (pdGlob + "/towary.xml");
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
	      towary = root.firstChild ().toElement ();
	      uslugi = root.lastChild ().toElement ();
	    }
	  QString text;

	  for (QDomNode n = uslugi.firstChild (); !n.isNull ();
	       n = n.nextSibling ())
	    {
	      // qDebug("aaa");
	      if (n.toElement ().attribute ("idx").
		  compare (tableT->text (row, 0)) == 0)
		{
		  uslugi.removeChild (n);
		  break;
		}
	    }

	  for (QDomNode n = towary.firstChild (); !n.isNull ();
	       n = n.nextSibling ())
	    {
	      // qDebug("aaa");
	      if (n.toElement ().attribute ("idx").
		  compare (tableT->text (row, 0)) == 0)
		{
		  towary.removeChild (n);
		  break;
		}
	    }

	  QString xml = doc.toString ();
	  file.close ();
	  file.open (IO_WriteOnly);
	  QTextStream ts (&file);
	  ts << xml;

	  file.close ();
 	  tableT->removeRow (row);
	  /*
	  tableClear (tableT);
	  QDir tmp;
	  QString progDir = tmp.homeDirPath () + "/elinux";
	  qDebug (progDir);
	  readTw (progDir);
	  */
	}

    }

}

void
Form1::towaryEdycja ()
{
  qDebug ("%s %s:%d", __FUNCTION__, __FILE__, __LINE__);
  int row, max = tableT->numRows ();

  for (row = 0; row < max; ++row)
    {
      if (tableT->isRowSelected (row))
	break;
    }
  qDebug (tableT->text (row, 0));

  twAdd *towWindow = new twAdd;
  towWindow->readData (tableT->text (row, 0), tableT->text (row, 5));
  if (towWindow->exec () == QDialog::Accepted)
    {
      /*
         tableClear (tableT);
         QDir tmp;
         QString progDir = tmp.homeDirPath () + "/elinux";
         qDebug (progDir);
         readTw(progDir);
       */
      QStringList rowTxt = QStringList::split ("|", towWindow->ret);
      tableT->setText (row, 0, rowTxt[0]);
      tableT->setText (row, 1, rowTxt[1]);
      tableT->setText (row, 2, rowTxt[2]);
      tableT->setText (row, 3, rowTxt[3]);
      tableT->setText (row, 4, rowTxt[4]);
      tableT->setText (row, 5, rowTxt[5]);
      tableT->setText (row, 6, rowTxt[6]);
      tableT->setText (row, 7, rowTxt[7]);
      tableT->setText (row, 8, rowTxt[8]);
      tableT->setText (row, 9, rowTxt[9]);
      tableT->setText (row, 10, rowTxt[10]);
      tableT->setText (row, 11, rowTxt[11]);
    }

}


void
Form1::saveAllSett()
{
  QSettings settings;
  settings.beginGroup ("elinux/faktury");
  settings.writeEntry ("firstrun", "nie");
  settings.writeEntry ("logo", "");  
  settings.writeEntry ("jednostki",   "szt.|kg.|g.|m|km.|godz." );
  settings.writeEntry ("stawki",   "22|7|0|zw." );
  settings.writeEntry ("waluty",   "PLN|EUR|USD" );
  settings.writeEntry ("payments",  "gotówka|przelew" ); // uwaga!! get first
  settings.writeEntry ("paym1",   "gotówka" ); 
  settings.writeEntry ("pkorekty",   "zmiana ilo¶ci" ); 
  settings.endGroup ();
  
  settings.beginGroup ("elinux/faktury_pozycje");
  settings.writeEntry ("Lp",   true );
  settings.writeEntry ("Nazwa",   true );
  settings.writeEntry ("Kod",   true );
  settings.writeEntry ("pkwiu",   true );
  settings.writeEntry ("ilosc",   true );
  settings.writeEntry ("jm",   true );
  settings.writeEntry ("cenajedn",   true );
  settings.writeEntry ("wartnetto",   true );
  settings.writeEntry ("rabatperc",   true );
  settings.writeEntry ("rabatval",   true );
  settings.writeEntry ("nettoafter",   true );
  settings.writeEntry ("vatval",   true );
  settings.writeEntry ("vatprice",   true );
  settings.writeEntry ("bruttoval",   true );
  settings.endGroup ();
    
}
	



void Form1::nextPage()
{
 if ( tabWidget2->count() != tabWidget2->currentPageIndex() )
 tabWidget2->setCurrentPage( tabWidget2->currentPageIndex() + 1 );
}


void Form1::prevPage()
{
 if ( tabWidget2->currentPageIndex() !=  0 )
 tabWidget2->setCurrentPage( tabWidget2->currentPageIndex() - 1 );
}
