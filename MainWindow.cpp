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
#include "MainWindow.moc"
#include <qtextcodec.h>
#include <qdir.h>
#include <qmessagebox.h>
#include <qsettings.h>
#include <qapplication.h>
#include <qevent.h>
#include <qprocess.h>
#include <Qt/qdom.h>
#include <QTextStream>
#include <QtDebug>

#include "Podglad.h"
#include "Ustawienia.h"
#include "Uzytkownik.h"
#include "Towary.h"
#include "Faktura.h"
#include "Korekta.h"
#include "Kontrahenci.h"


QString pdGlob;

void MainWindow::init ()
{
  QTextCodec::setCodecForCStrings (QTextCodec::codecForName ("ISO8859-2"));
  QTextCodec::setCodecForLocale (QTextCodec::codecForName ("ISO8859-2"));    
 //  create local user directory for store xml files
  // works only on Linux -> see also licence Qt 3
  QDir tmp;
  QString progDir = tmp.homePath () + "/elinux";
  pdGlob = progDir;
  // qDebug(progDir);
  if (!tmp.exists (progDir))
    {
      tmp.mkdir (progDir);
      tmp.mkdir (progDir + "/faktury");
    }


  if (!tmp.exists (progDir + "/faktury"))
    {
      tmp.mkdir (progDir + "/faktury");
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



bool MainWindow::firstRun ()
{
  qDebug (__FUNCTION__);
  QSettings settings;
  bool ok;
  ok = settings.value("elinux/faktury/firstrun").toBool();
  if (ok == 0)
    {
      return true;
    }
  else
    return false;
}

void MainWindow::tableClear (QTableWidget * tab)
{
    tab->clear();
}

void MainWindow::tabChanged (QWidget * aaa)
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

void MainWindow::readHist (QString progDir)
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
  QStringList filters;
  filters<<"h*.xml";
  allFiles.setNameFilters (filters);
  QStringList pliczki = allFiles.entryList ();
  int i, max = pliczki.count ();
  for (i = 0; i < max; ++i)
    {
      // qDebug(pliczki[i]);
      tableH->insertRow(tableH->rowCount ());
      text = pliczki[i];
      tableH->item(tableH->rowCount () - 1, 0)->setText(text);

      QFile file (progDir + "/faktury/" + pliczki[i]);

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
	      // qDebug ("can not set content ");
	      // qDebug( file.name() );
	      file.close ();
	      // return;
	    }
	}

      root = doc.documentElement ();
      tableH->item (tableH->rowCount () - 1, 1)->setText(
		       root.attribute ("nr", "NULL"));
      tableH->item (tableH->rowCount () - 1, 2)->setText(
		       root.attribute ("data.sprzed", "NULL"));
      tableH->item (tableH->rowCount () - 1, 3)->setText(
  		       root.attribute ("type", "NULL"));
      QDomNode nab;
      nab = root.firstChild();
      nab = nab.toElement().nextSibling();
      tableH->item (tableH->rowCount () - 1, 4)->setText(
		       nab.toElement().attribute ("nazwa", "NULL"));
      tableH->item (tableH->rowCount () - 1, 5)->setText(
		       nab.toElement().attribute ("nip", "NULL"));
    }

}

void MainWindow::aboutQt ()
{
  QMessageBox::aboutQt (this, "QFaktury");
}

void MainWindow::oProg ()
{
  QMessageBox::about (this, "QFaktury v0.0.1 beta",
        "Program do wystawiania faktur. \n Koordynator projektu: \n\tGrzegorz R�kawek www.e-linux.pl \n Programista:\n\tTomasz 'moux' Pielech \nGrafika:\n\tDariusz Arciszewski \n\nSupport: info@e-linux.pl");		  
}

void MainWindow::editFHist ()
{
  qDebug( __FUNCTION__ );
  
  QSettings settings;
  
  int row, max = tableH->rowCount ();
  QList<QTableWidgetItem *> selected = tableH->selectedItems();
  row = selected[0]->row();

  if (tableH->item(row, 3)->text() == "korekta"){
      // QMessageBox::information( this, "QFaktury", "Jeszcze nie ma", QMessageBox::Ok );
	Korekta *korWindow = new Korekta(this);
	korWindow->progDir2 = pdGlob;
	korWindow->readData (tableH->item(row, 0)->text());
	if (korWindow->exec () == QDialog::Accepted)
	{
	    QStringList rowTxt = korWindow->ret.split("|");
	    tableH->item (row, 0)->setText(rowTxt[0]);	// file name
	    tableH->item (row, 1)->setText(rowTxt[1]);	// symbol
	    tableH->item (row, 2)->setText(rowTxt[2]);	// date
	    tableH->item (row, 3)->setText(rowTxt[3]);	// type
	    tableH->item (row, 4)->setText(rowTxt[4]);	// nabywca
	    tableH->item (row, 5)->setText(rowTxt[5]);	// NIP
	}
    }
      
  
  if ((tableH->item(row, 3)->text() == "FVAT")
      || (tableH->item(row, 3)->text() == "FPro"))
    {
      // qDebug ("%s %s:%d", __FUNCTION__, __FILE__, __LINE__);
      Faktura *fraWindow = new Faktura(this);
      fraWindow->progDir2 = pdGlob;
      qDebug()<< pdGlob;
      int co = 0;
      if (tableH->item(row, 3)->text() == "FVAT")
	co = 0;
      else
	co = 1;
      fraWindow->readData (tableH->item(row, 0)->text(), co);
      if (fraWindow->exec () == QDialog::Accepted)
	{
	  // tableH->insertRows (tableH->rowCount (), 1);
	     QStringList rowTxt = fraWindow->ret.split("|");
	     tableH->item (row, 0)->setText(rowTxt[0]); // file name
	     tableH->item (row, 1)->setText(rowTxt[1]); // symbol
	     tableH->item (row, 2)->setText(rowTxt[2]); // date
	     tableH->item (row, 3)->setText(rowTxt[3]); // type
	     tableH->item (row, 4)->setText(rowTxt[4]); // nabywca
	     tableH->item (row, 5)->setText(rowTxt[5]); // NIP
	}
    }
}


void MainWindow::delFHist ()
{
  if (QMessageBox::
      warning (this, "QFaktury",
	       "Czy napewno chcesz usun�� t� faktur� z historii?", "Tak",
	       "Nie", 0, 0, 1) == 0)
    {
        QTableWidgetItem *i = tableH->selectedItems()[0];
        QString name = i->text();

      qDebug ()<<name;

      QFile file (pdGlob + "/faktury/" + name);
      if (file.exists ())
	file.remove ();
      tableH->removeRow(i->row());
    }

}

void MainWindow::readKontr (QString progDir)
{
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

      for (QDomNode n = firma.firstChild (); !n.isNull ();
	   n = n.nextSibling ())
	{
	  tableK->insertRow(tableK->rowCount ());
	  text = n.toElement ().attribute ("name");
	  tableK->item (tableK->rowCount () - 1, 0)->setText(text);
	  text = "firma";
	  tableK->item (tableK->rowCount () - 1, 1)->setText(text);
	  text = n.toElement ().attribute ("place");
	  tableK->item (tableK->rowCount () - 1, 2)->setText(text);
	  text = n.toElement ().attribute ("address");
	  tableK->item (tableK->rowCount () - 1, 3)->setText(text);
	  text = n.toElement ().attribute ("telefon");
	  tableK->item (tableK->rowCount () - 1, 4)->setText(text);
	}

      for (QDomNode n = urzad.firstChild (); !n.isNull ();
	   n = n.nextSibling ())
	{
	  tableK->insertRow (tableK->rowCount ());
	  text = n.toElement ().attribute ("name");
	  tableK->item (tableK->rowCount () - 1, 0)->setText(text);
	  text = "urzad";
	  tableK->item (tableK->rowCount () - 1, 1)->setText(text);
	  text = n.toElement ().attribute ("place");
	  tableK->item (tableK->rowCount () - 1, 2)->setText(text);
	  text = n.toElement ().attribute ("address");
	  tableK->item (tableK->rowCount () - 1, 3)->setText(text);
	  text = n.toElement ().attribute ("telefon");
	  tableK->item (tableK->rowCount () - 1, 4)->setText(text);
	}
    }
}

void MainWindow::readTw (QString progDir)
{
  QDomDocument doc ("towary");
  QDomElement root;
  QDomElement towary;
  QDomElement uslugi;

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

	  tableT->insertRow (tableT->rowCount ());
	  text = n.toElement ().attribute ("idx");
	  tableT->item (tableT->rowCount () - 1, 0)->setText(text);
	  // text = "towar";
	  text = n.toElement ().attribute ("name");
	  tableT->item (tableT->rowCount () - 1, 1)->setText(text);
	  text = n.toElement ().attribute ("desc");
	  tableT->item (tableT->rowCount () - 1, 2)->setText(text);
	  text = n.toElement ().attribute ("code");
	  tableT->item (tableT->rowCount () - 1, 3)->setText(text);
	  text = n.toElement ().attribute ("pkwiu");
	  tableT->item (tableT->rowCount () - 1, 4)->setText(text);
	  text = "towar";
	  tableT->item (tableT->rowCount () - 1, 5)->setText(text);
	  text = n.toElement ().attribute ("curr");
	  tableT->item (tableT->rowCount () - 1, 6)->setText(text);
	  text = n.toElement ().attribute ("netto1");
	  tableT->item (tableT->rowCount () - 1, 7)->setText(text);
	  text = n.toElement ().attribute ("netto2");
	  tableT->item (tableT->rowCount () - 1, 8)->setText(text);
	  text = n.toElement ().attribute ("netto3");
	  tableT->item (tableT->rowCount () - 1, 9)->setText(text);
	  text = n.toElement ().attribute ("netto4");
	  tableT->item (tableT->rowCount () - 1, 10)->setText(text);
	  text = n.toElement ().attribute ("vat");
	  tableT->item (tableT->rowCount () - 1, 11)->setText(text);
	}

      for (QDomNode n = uslugi.firstChild (); !n.isNull ();
	   n = n.nextSibling ())
	{

	  tableT->insertRow (tableT->rowCount ());
	  text = n.toElement ().attribute ("idx");
	  tableT->item (tableT->rowCount () - 1, 0)->setText(text);
	  // text = "towar";
	  text = n.toElement ().attribute ("name");
	  tableT->item (tableT->rowCount () - 1, 1)->setText(text);
	  text = n.toElement ().attribute ("desc");
	  tableT->item (tableT->rowCount () - 1, 2)->setText(text);
	  text = n.toElement ().attribute ("code");
	  tableT->item (tableT->rowCount () - 1, 3)->setText(text);
	  text = n.toElement ().attribute ("pkwiu");
	  tableT->item (tableT->rowCount () - 1, 4)->setText(text);
	  text = "us�uga";
	  tableT->item (tableT->rowCount () - 1, 5)->setText(text);
	  text = n.toElement ().attribute ("curr");
	  tableT->item (tableT->rowCount () - 1, 6)->setText(text);
	  text = n.toElement ().attribute ("netto1");
	  tableT->item (tableT->rowCount () - 1, 7)->setText(text);
	  text = n.toElement ().attribute ("netto2");
	  tableT->item (tableT->rowCount () - 1, 8)->setText(text);
	  text = n.toElement ().attribute ("netto3");
	  tableT->item (tableT->rowCount () - 1, 9)->setText(text);
	  text = n.toElement ().attribute ("netto4");
	  tableT->item (tableT->rowCount () - 1, 10)->setText(text);
	  text = n.toElement ().attribute ("vat");
	  tableT->item (tableT->rowCount () - 1, 11)->setText(text);
	}
    }
}


void MainWindow::daneFirmyClick ()
{
  qDebug ("%s %s:%d", __FUNCTION__, __FILE__, __LINE__);
  Uzytkownik *daneFirmyWindow = new Uzytkownik(this);
  daneFirmyWindow->show ();
}

void MainWindow::settClick ()
{
  qDebug ("%s %s:%d", __FUNCTION__, __FILE__, __LINE__);
  Ustawienia *settWindow = new Ustawienia(this);
  settWindow->show ();
}

//void MainWindow::kretorClick ()
//{
//  qDebug ("%s %s:%d", __FUNCTION__, __FILE__, __LINE__);
////     QMessageBox::information( this, "QFaktury", "Funkcja jeszcze nie gotowa. Uzyj menu faktury->Nowy", QMessageBox::Ok );
//  Form3 *kreatorWindow = new Form3;
//  if (kreatorWindow->exec () == QDialog::Accepted)
//    {
//      kreatorWindow->print ();
//      // tableClear (tableH);
//      // readHist (pdGlob);
//      /*
//         QStringList row = QStringList::split( "|",  kreatorWindow->ret );
//         tableH->insertRows (tableH->rowCount (), 1);
//         tableH->setText (tableH->rowCount () - 1, 0, row[0]); // nazwa pliku
//         tableH->setText (tableH->rowCount () - 1, 1, row[1]); 
//         tableH->setText (tableH->rowCount () - 1, 2, row[2]); 
//         tableH->setText (tableH->rowCount () - 1, 4, row[3]); 
//         tableH->setText (tableH->rowCount () - 1, 3, row[4]); 
//       */
//    }
//  // delete kreatorWindow;
//}

void MainWindow::kontrClick ()
{
  qDebug ("%s %s:%d", __FUNCTION__, __FILE__, __LINE__);
  Kontrahenci *kontrWindow = new Kontrahenci(this);
  if (kontrWindow->exec () == QDialog::Accepted)
    {
      // tableClear (tableK);
      QDir tmp;
      QString progDir = tmp.homePath () + "/elinux";
      qDebug (progDir);
      tmp.mkdir (progDir, TRUE);

      // readKontr (progDir);
      tableK->insertRows (tableK->rowCount (), 1);
      QStringList row = QStringList::split ("|", kontrWindow->ret);
      tableK->item (tableK->rowCount () - 1, 0)->setText(row[0]);	// name
      tableK->item (tableK->rowCount () - 1, 1)->setText(row[1]);	// type
      tableK->item (tableK->rowCount () - 1, 2)->setText(row[2]);	// place
      tableK->item (tableK->rowCount () - 1, 3)->setText(row[3]);	// address
      tableK->item (tableK->rowCount () - 1, 4)->setText(row[4]);	// telefon
    }
}

void MainWindow::kontrDel ()
{
  if (QMessageBox::
      warning (this, "QFaktury",
	       "Czy napewno chcesz usun�� tego kontrahenta?", "Tak", "Nie", 0,
	       0, 1) == 0)
    {

      QDomDocument doc ("kontrahenci");
      QDomElement root;
      QDomElement urzad;
      QDomElement firma;
      int row, max = tableK->rowCount ();

      for (row = 0; row < max; ++row)
	{
	  if (tableK->isRowSelected (row))
	    break;
	}

      QFile file (pdGlob + "/kontrah.xml");
      if (!file.open (QIODevice::ReadOnly))
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
	  file.open (QIODevice::WriteOnly);
	  QTextStream ts (&file);
	  ts << xml;

	  file.close ();
	  tableK->removeRow (row);
	  // 
	  // tableClear (tableK);
	  // QDir tmp;
	  // QString progDir = tmp.homePath () + "/elinux";
	  // qDebug (progDir);
	  // readKontr (progDir);
	}

    }
}

void MainWindow::kontrEd ()
{
  qDebug ("%s %s:%d", __FUNCTION__, __FILE__, __LINE__);
  int row, max = tableK->rowCount ();

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
         QString progDir = tmp.homePath () + "/elinux";
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


void MainWindow::newFra ()
{
  qDebug ("%s %s:%d", __FUNCTION__, __FILE__, __LINE__);
  FormFra *fraWindow = new FormFra;
  fraWindow->progDir2 = pdGlob;
  fraWindow->pforma = false;
  if (fraWindow->exec () == QDialog::Accepted)
    {
      tableH->insertRows (tableH->rowCount (), 1);
      QStringList row = QStringList::split ("|", fraWindow->ret);
      tableH->setText (tableH->rowCount () - 1, 0, row[0]);	// file name
      tableH->setText (tableH->rowCount () - 1, 1, row[1]);	// symbol
      tableH->setText (tableH->rowCount () - 1, 2, row[2]);	// date
      tableH->setText (tableH->rowCount () - 1, 3, row[3]);	// type
      tableH->setText (tableH->rowCount () - 1, 4, row[4]);	// nabywca
      tableH->setText (tableH->rowCount () - 1, 5, row[5]);	// NIP
    }
}


void MainWindow::newPForm ()
{
  qDebug ("%s %s:%d", __FUNCTION__, __FILE__, __LINE__);
  FormFra *fraWindow = new FormFra;
  fraWindow->progDir2 = pdGlob;
  fraWindow->pforma = true;
  fraWindow->setWindowTitle("Faktura Pro Forma");
  fraWindow->backBtnClick();
  if (fraWindow->exec () == QDialog::Accepted)
    {
      tableH->insertRows (tableH->rowCount (), 1);
      QStringList row = QStringList::split ("|", fraWindow->ret);
      tableH->setText (tableH->rowCount () - 1, 0, row[0]);	// file name
      tableH->setText (tableH->rowCount () - 1, 1, row[1]);	// symbol
      tableH->setText (tableH->rowCount () - 1, 2, row[2]);	// date
      tableH->setText (tableH->rowCount () - 1, 3, row[3]);	// type
      tableH->setText (tableH->rowCount () - 1, 4, row[4]);	// nabywca
      tableH->setText (tableH->rowCount () - 1, 5, row[5]);	// NIP
    }
}


void MainWindow::newKor ()
{
    qDebug ("%s %s:%d", __FUNCTION__, __FILE__, __LINE__);
    
    qDebug( __FUNCTION__ );
    int row, max = tableH->rowCount ();
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
	    tableH->insertRows (tableH->rowCount (), 1);
	    QStringList row = QStringList::split ("|", korWindow->ret);
	    tableH->setText (tableH->rowCount () - 1, 0, row[0]);	// file name
	    tableH->setText (tableH->rowCount () - 1, 1, row[1]);	// symbol
	    tableH->setText (tableH->rowCount () - 1, 2, row[2]);	// date
	    tableH->setText (tableH->rowCount () - 1, 3, row[3]);	// type
	    tableH->setText (tableH->rowCount () - 1, 4, row[4]);	// nabywca
	    tableH->setText (tableH->rowCount () - 1, 5, row[5]);	// NIP
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

void MainWindow::closeEvent (QCloseEvent * e)
{
  if (QMessageBox::
      warning (this, "QFaktury",
	       "Czy chcesz wyj�� z programu?", "Tak", "Nie", 0, 0, 1) == 0)
    {
      e->accept ();
    }
}

void MainWindow::pomoc ()
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

void MainWindow::towaryDodaj ()
{
// 
  qDebug ("%s %s:%d", __FUNCTION__, __FILE__, __LINE__);
  twAdd *towWindow = new twAdd;
  if (towWindow->exec () == QDialog::Accepted)
    {
      /*
         tableClear (tableT);
         QDir tmp;
         QString progDir = tmp.homePath () + "/elinux";
         qDebug (progDir);
         tmp.mkdir (progDir, TRUE);
         readTw (progDir);
       */
      tableT->insertRows (tableT->rowCount (), 1);
      QStringList row = QStringList::split ("|", towWindow->ret);
      tableT->setText (tableT->rowCount () - 1, 0, row[0]);
      tableT->setText (tableT->rowCount () - 1, 1, row[1]);
      tableT->setText (tableT->rowCount () - 1, 2, row[2]);
      tableT->setText (tableT->rowCount () - 1, 3, row[3]);
      tableT->setText (tableT->rowCount () - 1, 4, row[4]);
      tableT->setText (tableT->rowCount () - 1, 5, row[5]);
      tableT->setText (tableT->rowCount () - 1, 6, row[6]);
      tableT->setText (tableT->rowCount () - 1, 7, row[7]);
      tableT->setText (tableT->rowCount () - 1, 8, row[8]);
      tableT->setText (tableT->rowCount () - 1, 9, row[9]);
      tableT->setText (tableT->rowCount () - 1, 10, row[10]);
      tableT->setText (tableT->rowCount () - 1, 11, row[11]);
    }
}

void MainWindow::towaryUsun ()
{

  int row, max = tableK->rowCount ();

  for (row = 0; row < max; ++row)
    {
      if (tableT->isRowSelected (row))
	break;
    }


  if (QMessageBox::
      warning (this, "QFaktury",
	       "Czy napewno chcesz usun�� towar " + tableT->text (row,
								  0) + "/" +
	       tableT->text (row, 1) + "?", "Tak", "Nie", 0, 0, 1) == 0)
    {

      QDomDocument doc ("towary");
      QDomElement root;
      QDomElement towary;
      QDomElement uslugi;

      QFile file (pdGlob + "/towary.xml");
      if (!file.open (QIODevice::ReadOnly))
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
	  file.open (QIODevice::WriteOnly);
	  QTextStream ts (&file);
	  ts << xml;

	  file.close ();
 	  tableT->removeRow (row);
	  /*
	  tableClear (tableT);
	  QDir tmp;
	  QString progDir = tmp.homePath () + "/elinux";
	  qDebug (progDir);
	  readTw (progDir);
	  */
	}

    }

}

void MainWindow::towaryEdycja ()
{
  qDebug ("%s %s:%d", __FUNCTION__, __FILE__, __LINE__);
  int row, max = tableT->rowCount ();

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
         QString progDir = tmp.homePath () + "/elinux";
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


void MainWindow::saveAllSett()
{
  QSettings settings;
  settings.beginGroup ("elinux/faktury");
  settings.writeEntry ("firstrun", "nie");
  settings.writeEntry ("logo", "");  
  settings.writeEntry ("jednostki",   "szt.|kg.|g.|m|km.|godz." );
  settings.writeEntry ("stawki",   "22|7|0|zw." );
  settings.writeEntry ("waluty",   "PLN|EUR|USD" );
  settings.writeEntry ("payments",  "got�wka|przelew" ); // uwaga!! get first
  settings.writeEntry ("paym1",   "got�wka" ); 
  settings.writeEntry ("pkorekty",   "zmiana ilo�ci" ); 
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
	



void MainWindow::nextPage()
{
 if ( tabWidget2->count() != tabWidget2->currentPageIndex() )
 tabWidget2->setCurrentPage( tabWidget2->currentPageIndex() + 1 );
}


void MainWindow::prevPage()
{
 if ( tabWidget2->currentPageIndex() !=  0 )
 tabWidget2->setCurrentPage( tabWidget2->currentPageIndex() - 1 );
}

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {
    setupUi(this);
    init();
}

