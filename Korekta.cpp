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

#include "Korekta.moc"
#include <qdatetime.h>
#include <qdir.h>
#include <qprocess.h>
#include <qapplication.h>
#include <qsettings.h>
#include <Qt/qdom.h>
#include <qmessagebox.h>
#include <qtextcodec.h>
#include <QTextStream>
#include <QtDebug>


#include "KontrahenciLista.h"
#include "TowaryLista.h"
#include "ZmienIlosc.h"

#include "Rounding.h"
#include "slownie.h"


// QDate liabDate;
int citem;


void Korekta::init ()
{
  QTextCodec::setCodecForCStrings (QTextCodec::codecForName ("ISO8859-2"));
  QTextCodec::setCodecForLocale (QTextCodec::codecForName ("ISO8859-2"));    
  // invoice fra1;
  // dodac do settingsow!!
	
  tableTow->setColumnWidth (0, 30);	//index
  tableTow->setColumnWidth (1, 90);	// nazwa
  tableTow->setColumnWidth (2, 35);	// kod
  tableTow->setColumnWidth (3, 35);	// kod
  tableTow->setColumnWidth (4, 40);	// ilosc
  tableTow->setColumnWidth (5, 30);	// jm
  tableTow->setColumnWidth (6, 60);	// cena jedn.
  tableTow->setColumnWidth (7, 60);	// netto
  tableTow->setColumnWidth (8, 30);	// vat
  tableTow->setColumnWidth (9, 50);	// netto *  (wzor vat)
  // tableTow->setColumnWidth(5, 90);
  // sellingDate->setDate (QDate::currentDate ());
  sellingDate2->setDate (QDate::currentDate ());
  liabDate->setDate( QDate::currentDate() );


  QDir abs (qApp->argv ()[0]);
  if (QString (qApp->argv ()[0]).left (2) == "./")
    templDir = abs.absolutePath ();
  else
    templDir = "/usr/bin/qfaktury";
  //absPath();
  templDir = templDir.replace ("bin", "share");
  templDir = templDir + "/templates/";

//  QString tmp;
  QSettings settings;
/*
   tmp = settings.value ("elinux/faktury/korNr");

  QStringList one1 = QStringList::split ("/", tmp);
  int nr = one1[0].toInt () + 1;
  lastInvoice =
    QString::number (nr) + "/" + QDate::currentDate ().toString ("MM/yyyy");
  korNr->setText (lastInvoice);
  */
  
 platCombo->addItems( settings.value("elinux/faktury/payments").toString().split("|")); 

// currCombo->insertStringList( QStringList::split("|", settings.value("elinux/faktury/waluty")), -1); 
 // reasonCombo->clear();
 reasonCombo->addItems(settings.value("elinux/faktury/pkorekty").toString().split("|")); 
  
}


void Korekta::readData(QString fraFile)
{
  backBtn->setEnabled(false); // do this another way
  korNr->setEnabled(false);
  setWindowTitle ("Edytuje korektê");
  fName = fraFile;
  
  // here we would read all data from one xml file to the this window
  QDomDocument doc ("faktury");
  QDomElement root;
  QDomElement nabywca;
  QDomElement towary;
  QDomElement towaryOld;
  
  fName = fraFile;
  QFile file (progDir2 + "/faktury/" + fraFile);
  // qDebug( file.name() );
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
	  file.close ();
	  // return;
	}
    }

  root = doc.documentElement ();
  frNr->setText (root.attribute ("nr"));
  sellingDate->
    setDate (QDate::fromString (root.attribute ("data.sprzed"), Qt::ISODate));
  sellingDate2->
    setDate (QDate::fromString (root.attribute ("data.korekty"), Qt::ISODate));

  QDomNode tmp;
  tmp = root.firstChild ();
  tmp = tmp.toElement ().nextSibling ();	// nabywca
  nabywca = tmp.toElement ();
  kontrName->setText (nabywca.attribute ("nazwa") + "," +
		      nabywca.attribute ("miasto") + "," +
		      nabywca.attribute ("ulica") + ", " +
		      nabywca.attribute ("nip"));
  kontrName->setCursorPosition (1);

  tmp = tmp.toElement ().nextSibling ();	// towary
  towary = tmp.toElement ();
  rabatValue->setValue (towary.attribute ("goods::rabat").toInt ());
  int towCount = towary.attribute ("goods::count").toInt ();
  int i = 0;
  QDomElement towar;
  towar = towary.firstChild ().toElement ();
  // qDebug( towar.attribute("Nazwa")  );
  tableTow->setRowCount(towCount);
  tableTow->setColumnCount(10);
  const char *towarColumns[] = {
      "",
"Nazwa",
"Kod",
"PKWiU",
"Ilosc",
"Jm.",
"Cena_jdn.",
"Wartosc_Netto",
"Stawka_VAT",
"Wartosc_Brutto",
  };
  for (i = 0; i < towCount; ++i)
    {
        for (int j = 0; j < sizeof(towarColumns)/sizeof(*towarColumns); j++) {
            tableTow->setItem(i, j, new QTableWidgetItem(towar.attribute(towarColumns[j])));
        }
      towar = towar.nextSibling ().toElement ();
    }
  
 tmp = tmp.toElement ().nextSibling ();
towaryOld = tmp.toElement ();
// qDebug(  towaryOld.tagName() ); 
  QString tmp1;
  towCount = towaryOld.attribute ("goods::count").toInt ();
  // qDebug( towaryOld.attribute ("goods::count") );
  i = 0;
  towary = towaryOld.firstChild ().toElement ();
  
  oldNetto = 0;
  oldVat = 0;
  oldBrutto = 0;
  
  for (i = 0; i < towCount; ++i)
    {
      tmp1 = QString::number(i);
      tmp1 += "|" + towary.attribute ("Nazwa");
      tmp1 += "|" + towary.attribute ("Kod");
      tmp1 += "|" + towary.attribute ("PKWiU");
      tmp1 += "|" + towary.attribute ("Ilosc");
      tmp1 += "|" + towary.attribute ("Jm.");
      tmp1 += "|" + towary.attribute ("Cena_jdn.");
      tmp1 += "|" + towary.attribute ("Wartosc_Netto");
      oldNetto += towary.attribute ("Wartosc_Netto").replace(",", ".").toDouble();
      tmp1 += "|" + towary.attribute ("Stawka_VAT");
      oldVat += towary.attribute ("Stawka_VAT").replace(",", ".").toDouble();
      tmp1 += "|" + towary.attribute ("Kwota_Vat");
      tmp1 += "|" + towary.attribute ("Wartosc_Brutto");
      oldBrutto += towary.attribute ("Wartosc_Brutto").replace(",", ".").toDouble();
      towary = towary.nextSibling ().toElement ();
      towaryPKor[i] = tmp1;
    }
  
  
  tmp = tmp.toElement ().nextSibling ();
  QDomElement additional = tmp.toElement ();
  additEdit->setText (additional.attribute ("text"));
  
  platCombo->setCurrentIndex(additional.attribute ("forma.plat").toInt ());
  
  reasonCombo->setCurrentIndex(additional.attribute ("przyczyna").toInt ());
//  addinfo.setAttribute ("przyczyna",
//			QString::number (reasonCombo->currentItem ()));
  
//   qDebug( additional.attribute ("przyczyna") );
//   qDebug( additional.attribute ("forma.plat") );
   
  paymFry->setText( platCombo->currentText() );
  liabDate->
    setDate (QDate::
	     fromString (additional.attribute ("liabDate"), Qt::ISODate));
  citem = additional.attribute ("waluta").toInt ();
  QSettings settings;
  // currCombo->setCurrentItem (additional.attribute ("waluta").toInt ());
  QStringList waluty = settings.value("elinux/faktury/waluty").toString().split("|"); 
  currency = waluty[additional.attribute ("waluta").toInt ()];
  // qDebug(currency); qFatal("dsadsa");
  fraValLbl->setText( fixStr(QString::number( oldBrutto ).replace(",", ".")) );
  
    
  lastInvoice += "/" + QDate::currentDate ().toString ("dd");
  
    if ( !settings.value/*bool*/ ("elinux/faktury/edit") .toBool())
  {
      korNr->setEnabled( FALSE );
      backBtn->setEnabled( FALSE );
      sellingDate2->setEnabled( FALSE );
tableTow->setEnabled( FALSE );
rabatValue->setEnabled( FALSE );
platCombo->setEnabled( FALSE );
liabDate->setEnabled( FALSE );
reasonCombo->setEnabled( FALSE );
additEdit->setEnabled( FALSE );
addTw->setEnabled( FALSE );
rmTow->setEnabled( FALSE );
editTw->setEnabled( FALSE );
saveBtn->setEnabled( FALSE );
  } else {
      korNr->setEnabled( TRUE );
      backBtn->setEnabled( TRUE );
      sellingDate2->setEnabled( TRUE );
tableTow->setEnabled( TRUE );
rabatValue->setEnabled( TRUE );
platCombo->setEnabled( TRUE );
liabDate->setEnabled( TRUE );
reasonCombo->setEnabled( TRUE );
additEdit->setEnabled( TRUE );
addTw->setEnabled( TRUE );
rmTow->setEnabled( TRUE );
editTw->setEnabled( TRUE );
saveBtn->setEnabled( TRUE );
  }

  
  countRabat ();
  countSum ();
  
  
}

void Korekta::readDataNewKor (QString fraFile)
{
  // here we would read all data from one xml file to the this window
  QDomDocument doc ("faktury");
  QDomElement root;
  QDomElement nabywca;
  QDomElement towary;
  
  backBtnClick();

  fName = fraFile;
  QFile file (progDir2 + "/faktury/" + fraFile);
  // qDebug( file.name() );
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
	  file.close ();
	  // return;
	}
    }

  root = doc.documentElement ();
  frNr->setText (root.attribute ("nr"));
  sellingDate->
    setDate (QDate::fromString (root.attribute ("data.sprzed"), Qt::ISODate));

  QDomNode tmp;
  tmp = root.firstChild ();
  tmp = tmp.toElement ().nextSibling ();	// nabywca
  nabywca = tmp.toElement ();
  kontrName->setText (nabywca.attribute ("nazwa") + "," +
		      nabywca.attribute ("miasto") + "," +
		      nabywca.attribute ("ulica") + ", " +
		      nabywca.attribute ("nip"));
  kontrName->setCursorPosition (1);

  tmp = tmp.toElement ().nextSibling ();	// towary
  towary = tmp.toElement ();
  rabatValue->setValue (towary.attribute ("goods::rabat").toInt ());
  int towCount = towary.attribute ("goods::count").toInt ();
  int i = 0;
  QDomElement towar;
  towar = towary.firstChild ().toElement ();
  // qDebug( towar.attribute("Nazwa")  );
  QString tmp1;
  oldNetto = 0;
  oldVat = 0;
  oldBrutto = 0;
  tableTow->setRowCount(towCount);
  tableTow->setColumnCount(10);
  for (i = 0; i < towCount; ++i)
    {
      tableTow->item (i, 0)->setText(QString::number (i));	// lp
      tmp1 = QString::number(i);
      
      tableTow->item (i, 1)->setText(towar.attribute ("Nazwa"));	// nazwa
      tmp1 += "|" + towar.attribute ("Nazwa");
      
      tableTow->item (i, 2)->setText(towar.attribute ("Kod"));	// kod
      tmp1 += "|" + towar.attribute ("Kod");
      
      tableTow->item (i, 3)->setText(towar.attribute ("PKWiU"));	// pkwiu
      tmp1 += "|" + towar.attribute ("PKWiU");
      
      tableTow->item (i, 4)->setText(towar.attribute ("Ilosc"));	// ilosc
      tmp1 += "|" + towar.attribute ("Ilosc");
      
      tableTow->item (i, 5)->setText(towar.attribute ("Jm."));	// jm
      tmp1 += "|" + towar.attribute ("Jm.");
      
      tableTow->item (i, 6)->setText(towar.attribute ("Cena_jdn.")); // cena jdn.
      tmp1 += "|" + towar.attribute ("Cena_jdn.");
      
      tableTow->item (i, 7)->setText(towar.attribute ("Wartosc_Netto")); // netto
      tmp1 += "|" + towar.attribute ("Wartosc_Netto");
      oldNetto += towar.attribute ("Wartosc_Netto").replace(",", ".").toDouble();
      
      tableTow->item (i, 8)->setText(towar.attribute ("Stawka_VAT"));	// vat
      tmp1 += "|" + towar.attribute ("Stawka_VAT");
      oldVat += towar.attribute ("Stawka_VAT").replace(",", ".").toDouble();

      
      tableTow->item (i, 9)->setText(towar.attribute ("Wartosc_Brutto")); // brutto
      tmp1 += "|" + towar.attribute ("Kwota_Vat");
      tmp1 += "|" + towar.attribute ("Wartosc_Brutto");
      oldBrutto += towar.attribute ("Wartosc_Brutto").replace(",", ".").toDouble();
      
      towar = towar.nextSibling ().toElement ();
      towaryPKor[i] = tmp1;
    }
  tmp = tmp.toElement ().nextSibling ();
  QDomElement additional = tmp.toElement ();
  additEdit->setText (additional.attribute ("text"));
  
  platCombo->setCurrentIndex(additional.attribute ("forma.plat").toInt ());
  paymFry->setText( platCombo->currentText() );
 liabDate->setDate( QDate::currentDate() );
/*
  liabDate->
    setDate (QDate::
	     fromString (additional.attribute ("liabDate"), Qt::ISODate));
  */
  citem = additional.attribute ("waluta").toInt ();
  QSettings settings;
  // currCombo->setCurrentItem (additional.attribute ("waluta").toInt ());
  QStringList waluty = settings.value("elinux/faktury/waluty").toString().split("|"); 
  currency = waluty[additional.attribute ("waluta").toInt ()];
  // qDebug(currency); qFatal("dsadsa");
  fraValLbl->setText( fixStr(QString::number( oldBrutto ).replace(",", ".")) );
  
  if ( settings.value/*bool*/ ("elinux/faktury/editSymbol") .toBool())
  {
      korNr->setEnabled( FALSE );
      backBtn->setEnabled( FALSE );
  } else {
      korNr->setEnabled( TRUE );
      backBtn->setEnabled( TRUE );
  }
  
  
  countRabat ();
  countSum ();
}

void Korekta::getKontrahent ()
{
  KontrahenciLista *klWindow =
    new KontrahenciLista(this);
  if (klWindow->exec () == QDialog::Accepted)
    {
      kontrName->setText (klWindow->ret);
      kontrName->setCursorPosition (1);
    }
}

void Korekta::addTow ()
{
  TowaryLista *twWindow =
    new TowaryLista(this);
  if (twWindow->exec () == QDialog::Accepted)
    {
      // qDebug( twWindow->ret );
      // DAR|100|0,12|22|14.64
      // twarers|21398edwa|45|szt.|15,45|22|848.205
      tableTow->insertRow (tableTow->rowCount());
      QStringList row = twWindow->ret.split("|");
      tableTow->item (tableTow->rowCount () - 1, 0)->setText(QString::number (tableTow->rowCount ()));	// lp
      tableTow->item (tableTow->rowCount () - 1, 1)->setText(row[0]);	// nazwa
      tableTow->item (tableTow->rowCount () - 1, 2)->setText(row[1]);	// kod
      tableTow->item (tableTow->rowCount () - 1, 3)->setText(row[2]);	// pkwiu
      tableTow->item (tableTow->rowCount () - 1, 4)->setText(row[3]);	// ilosc
      tableTow->item (tableTow->rowCount () - 1, 5)->setText(row[4]);	// jm
      tableTow->item (tableTow->rowCount () - 1, 6)->setText(row[5]);	// cena jdn.
      tableTow->item (tableTow->rowCount () - 1, 7)->setText(row[6]);	// netto
      tableTow->item (tableTow->rowCount () - 1, 8)->setText(row[7]);	// vat
      tableTow->item (tableTow->rowCount () - 1, 9)->setText(row[8]);	// brutto
    }
  countRabat ();
  countSum ();
}


void Korekta::countRabat ()
{
  QString rabat1 = QString::number (rabatValue->value ());
  if (rabat1.length () == 1)
    rabat1 = "0.0" + rabat1;
  else
    rabat1 = "0." + rabat1;

  double kwota = 0;
  double cenajdn = 0;
  double rabat = 0;
  priceBRabN = 0;
  for (int i = 0; i < tableTow->rowCount (); ++i)
    {
      cenajdn = tableTow->item(i, 6)->text().replace (",", ".").toDouble ();
      kwota = cenajdn * tableTow->item(i, 4)->text().replace (",", ".").toInt ();
      rabat = kwota * rabat1.toDouble ();
      tableTow->item(i, 7)->setText(fixStr (QString::number (kwota - rabat)));	// netto
      priceBRabN = priceBRabN + kwota;
      // qDebug(tableTow->text(i, 6).replace(",", "."));
    }

  double vat = 0;
  double netto = 0;
  QString vat1;
  kwota = 0;
  cenajdn = 0;
  rabat = 0;
  priceBRab = 0;		// priceBRabN
/*    
    rabat1 = QString::number( rabatValue->value());
    if (rabat1.length() == 1) rabat1 = "1.0" + rabat1;
     else rabat1 = "1." + rabat1;			
*/
  for (int i = 0; i < tableTow->rowCount (); ++i)
    {
      vat1 = tableTow->item(i, 8)->text().replace (",", ".");
      // QString::number( rabatValue->value());
      if (vat1.length () == 1)
	vat1 = "1.0" + vat1;
      else
	vat1 = "1." + vat1;

      vat = vat1.toDouble ();
      if ( vat == 0 ) vat = 1;
      
      netto = tableTow->item(i, 7)->text().replace (",", ".").toDouble ();	// after rab.

//************************************************************************//

      cenajdn = tableTow->item(i, 6)->text().replace (",", ".").toDouble ();
      kwota = cenajdn * tableTow->item(i, 4)->text().replace (",", ".").toInt ();
      rabat = kwota * rabat1.toDouble ();
      // kwota - rabat; // jedn. netto
      priceBRab = priceBRab + (vat * (kwota));

//************************************************************************//

      kwota = vat * netto;
      // qDebug(QString::number(kwota));
      tableTow->item(i, 9)->setText(fixStr (QString::number (kwota)));
      // fixStr(
      // qDebug(tableTow->text(i, 6).replace(",", "."));
    }

}


void Korekta::countSum ()
{
  // count netto sum
  double kwota = 0;
  for (int i = 0; i < tableTow->rowCount (); ++i)
    {
      kwota += tableTow->item(i, 7)->text().replace (",", ".").toDouble ();
      // qDebug(tableTow->text(i, 6).replace(",", "."));
    }
  snetto = fixStr (QString::number (kwota));

  // count brutto sum
  kwota = 0;
  for (int i = 0; i < tableTow->rowCount (); ++i)
    {
      kwota += tableTow->item(i, 9)->text().replace (",", ".").toDouble ();
      // qDebug(tableTow->text(i, 6).replace(",", "."));
    }
  sbrutto = fixStr (QString::number (kwota));

  // count rabat
  QString rabat1 = QString::number (rabatValue->value ());
  if (rabat1.length () == 1)
    rabat1 = "1.0" + rabat1;
  else
    rabat1 = "1." + rabat1;
  // qDebug( "rabat " +  rabat1 );
  // double rabatVal = rabat1.toDouble();
  // double rabatBr = sbrutto->text().toDouble();
  // double przedRab = rabatVal * rabatBr;
  // qDebug("przed rabatem1: " + QString::number(priceBRab));
  // qDebug("przed rabatem2: " + QString::number(przedRab));
  sRabat =fixStr (QString::number (priceBRab - sbrutto.toDouble ()).
	      replace (".", ","));
  // setting labels text
  
  fvKor->setText( sbrutto ); 
  diffLabel->setText( fixStr( QString::number( (oldBrutto - sbrutto.replace(",", ".").toDouble()) * -1 ))  );
}

void Korekta::rabatChange ()
{
  countRabat ();
  countSum ();
}

void Korekta::delTowar ()
{
  tableTow->removeRow (tableTow->currentRow ());
  for (int i = 0; i < tableTow->rowCount (); ++i)
    {
      tableTow->item(i, 0)->setText(QString::number (i + 1));
    }
  countRabat ();
  countSum ();
}

void Korekta::editTowar ()
{
  // we can only modify amount
  ZmienIlosc *changeAmount =
    new ZmienIlosc(this);
  changeAmount->nameTow->setText (tableTow->
				  item(tableTow->currentRow (), 1)->text());
  changeAmount->codeTow->setText (tableTow->
				  item (tableTow->currentRow (), 2)->text());
  changeAmount->spinAmount->setValue (tableTow->
				      item (tableTow->currentRow (),
					    4)->text().toInt ());
  if (changeAmount->exec () == QDialog::Accepted)
    {
      // kontrName->setText( klWindow->ret );
      tableTow->item(tableTow->currentRow (), 4)->setText(
			 QString::number (changeAmount->spinAmount->
					  value ()));
    }
  countRabat ();
  countSum ();
}




void Korekta::makeInvoiceHeadar ()
{

  fraStrList += "<html><head>";
  fraStrList +=
    "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-2\" />";
  fraStrList += "<meta name=\"creator\" value=\"http://www.e-linux.pl\" />";
  fraStrList += "</head>";
  fraStrList += "<title>______Korekta______</title>";
  fraStrList += "<style type=\"text/css\"><!-- ";
  // qDebug( templDir  );

  QFile file (templDir + "style.css");
  if (file.open (QIODevice::ReadOnly))
    {
      QTextStream stream (&file);
      QString line;
      while (!stream.atEnd ())
	{
	  line = stream.readLine ();
	  fraStrList += line;
	}
      file.close ();
    }

  fraStrList += "--></style>";
  fraStrList += "<body>";
  fraStrList +=
    "<table width=\"700\" border=\"0\" cellspacing=\"0\" cellpadding=\"0\">";
  //  class=\"page_break\" ------>>>> think about this
  fraStrList += "<tr comment=\"headar\"><td>";
  fraStrList +=
    "<table comment=\"headar table\" width=\"100%\" border=\"0\">";
  fraStrList += "<tr>";
  fraStrList +=
    "<td colspan=\"2\" width=\"60%\" align=\"left\" valign=\"center\" class=\"podpisy\">";
  // logo code
  // eof logo
  QSettings settings;
  QString logo = settings.value ("elinux/faktury/logo").toString();
  if ( logo != "" ) {
      fraStrList += "<img src=\"" + logo + "\"  width=\"200\" height=\"100\">";      
  } else {
      fraStrList += "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Pieczêæ wystawcy";
  }
  // in case where we don't have a logo :(

  fraStrList += "</td>";
  fraStrList += "<td>";
  fraStrList += "<h2>FAKTURA VAT<br>koryguj±ca<br>";
  fraStrList += "NR: " + korNr->text () + "<br></h2>";
  fraStrList +=
    "<h5>Data wystawienia: " + sellingDate2->date ().toString ("yyyy-MM-dd") +
    "<br>";
  // fraStrList +=
  // QDate::currentDate ().toString ("yyyy-MM-dd")
  //   "Data sprzeda¿y: " + sellingDate->date ().toString ("yyyy-MM-dd") +
  //    "<br></h5>";
  fraStrList += "</td>";
  fraStrList += "<td width=\"20\">&nbsp;</td>";
  fraStrList += "</tr>";
  fraStrList += "<tr>";
  fraStrList += "<td colspan=\"3\" align=\"right\" valign=\"top\">";
  fraStrList += "<br>ORYGINA£/KOPIA<br>";
  fraStrList += "</td>";
  fraStrList += "<td width=\"20\">&nbsp;</td>";
  fraStrList += "</tr>";
  fraStrList += "</table>";
  fraStrList += "</td></tr>";
}

void Korekta::makeInvoiceBody ()
{
  fraStrList += "<tr comment=\"body\"><td>";
  fraStrList += "<table width=\"100%\" border=\"0\">";
  fraStrList += "<tr>";
  fraStrList += "<td witdh=\"20\">&nbsp;</td>";
  fraStrList += "<td width=\"48%\"> ";
  fraStrList += "<h4>Sprzedawca:</h4>";
  QSettings settings;
  fraStrList += "<h5>" + settings.value ("przelewy/user/nazwa").toString() + "<br>";
  fraStrList +=
    settings.value ("przelewy/user/kod").toString() + " " +
    settings.value ("przelewy/user/miejscowosc").toString() + "<br>";
  fraStrList += "ul. " + settings.value ("przelewy/user/adres").toString() + "<br>";
  fraStrList += "NIP: " + settings.value ("przelewy/user/nip").toString() + "<br>";
  fraStrList +=
    "Nr konta: " + settings.value ("przelewy/user/konto").toString().replace ("-",
								       " ") +
    "<br>";
  fraStrList += "</h5>";
  fraStrList += "</td>";
  fraStrList += "<td witdh=\"20\">&nbsp;</td>";
  fraStrList += "<td width=\"48%\">";
  fraStrList += "<h4>Nabywca:</h4>";
  fraStrList += "<h5>" + kontrName->text ().replace (",", "<br>") + "<br>";
  fraStrList += "</h5>";
  fraStrList += "</td>";
  fraStrList += "</tr>";
  fraStrList += "</table>";
  fraStrList += "</td></tr>";
}

void Korekta::makeInvoiceCorr ()
{
  fraStrList += "<tr comment=\"corr\"><td>";
  fraStrList += "<table width=\"100%\" border=\"0\">";
  fraStrList += "<tr>";
  fraStrList += "<td witdh=\"20\">&nbsp;</td>";
  fraStrList += "<td width=\"48%\"> ";
  fraStrList += "<h5>Nr faktury VAT: " + frNr->text();
  fraStrList += "<br>Data wystawienia: " + sellingDate->date().toString ("yyyy-MM-dd"); // 
  fraStrList += "<br>Data sprzeda¿y:" + sellingDate->date().toString ("yyyy-MM-dd");
  fraStrList += "<br>Forma p³atno¶ci faktury: " + paymFry->text() + "</h5>";
  fraStrList += "</td>";
  fraStrList += "<td witdh=\"20\">&nbsp;</td>";
  fraStrList += "<td width=\"48%\" valign=\"bottom\">";
  fraStrList += "<h5>Powód korekty: " + reasonCombo->currentText() + "<br>";
  fraStrList += "Termin rozliczenia: " + liabDate->date().toString ("yyyy-MM-dd") + "<br>";
  fraStrList += "</h5>";
  fraStrList += "</td>";
  fraStrList += "</tr>";
  fraStrList += "</table>";
  fraStrList += "</td></tr>";
}


void Korekta::makeInvoiceGoods2 ()
{
  fraStrList += "<tr comment=\"goods\" align=\"center\"><td>";
  fraStrList += "<h4>Pozycje na fakturze przed korekt±: </h4>";
  fraStrList += "<table width=\"100%\" border=\"1\" class=\"goods\">";
  fraStrList += "<tr class=\"towaryN\">";
  
//  QSettings settings;
// if ( settings.value/*bool*/("elinux/faktury_pozycje/Lp") .toBool())
  fraStrList += "<td width=\"20\"  align=\"center\">Lp.</td>";
// if ( settings.value/*bool*/("elinux/faktury_pozycje/Nazwa")  .toBool())
 fraStrList += "<td width=\"120\" align=\"center\">Nazwa</td>";
// if ( settings.value/*bool*/("elinux/faktury_pozycje/Kod")  .toBool())
  fraStrList += "<td width=\"60\" align=\"center\">Kod</td>";
// if ( settings.value/*bool*/("elinux/faktury_pozycje/pkwiu")  .toBool())
  fraStrList += "<td width=\"60\" align=\"center\">PKWiU</td>";
// if ( settings.value/*bool*/("elinux/faktury_pozycje/ilosc")  .toBool())
  fraStrList += "<td width=\"60\" align=\"center\">Ilo¶æ</td>";
// if ( settings.value/*bool*/("elinux/faktury_pozycje/jm")  .toBool())
  fraStrList += "<td width=\"20\" align=\"center\">Jm.</td>";
//if ( settings.value/*bool*/("elinux/faktury_pozycje/cenajedn")  .toBool())
  fraStrList += "<td width=\"60\" align=\"center\">Cena jdn.</td>";
// if ( settings.value/*bool*/("elinux/faktury_pozycje/wartnetto")  .toBool())
//  fraStrList += "<td width=\"60\" align=\"center\">Warto¶æ Netto</td>";
// if ( settings.value/*bool*/("elinux/faktury_pozycje/rabatperc")  .toBool())
//  fraStrList += "<td width=\"20\" align=\"center\">Rabat %</td>";
// if ( settings.value/*bool*/("elinux/faktury_pozycje/rabatval")  .toBool())
//  fraStrList += "<td width=\"20\" align=\"center\">Rabat Warto¶æ</td>";
// if ( settings.value/*bool*/("elinux/faktury_pozycje/nettoafter")  .toBool())
  fraStrList += "<td width=\"60\" align=\"center\">Netto</td>";
// if ( settings.value/*bool*/("elinux/faktury_pozycje/vatval")  .toBool())
  fraStrList += "<td width=\"60\" align=\"center\">Stawka VAT</td>";
// if ( settings.value/*bool*/("elinux/faktury_pozycje/vatprice")  .toBool())
  fraStrList += "<td width=\"60\" align=\"center\">Kwota Vat</td>";
// if ( settings.value/*bool*/("elinux/faktury_pozycje/bruttoval")  .toBool())
  fraStrList += "<td width=\"60\" align=\"center\">Warto¶æ Brutto</td>";
  fraStrList += "</tr>";
 int max = towaryPKor.size();
  for (int i = 0; i < max; ++i)
    {
      // double vatPrice = tableTow->text(i, 9).replace(",", ".").toDouble() - tableTow->text(i, 6).replace(",", ".").toDouble();
    QStringList rowTxt = towaryPKor[i].split("|");

      fraStrList += "<tr class=\"towaryList\">";
// lp, nazwa, kod, ilosc, jm, cena jm., netto, vat, brutto
// if ( settings.value/*bool*/("elinux/faktury_pozycje/Lp")   .toBool())
      fraStrList += "<td>&nbsp;" + rowTxt[0] + "</td>";
 
// if ( settings.value/*bool*/("elinux/faktury_pozycje/Nazwa")  .toBool())
 fraStrList += "<td>&nbsp;" + rowTxt[1]+ "</td>";
//if ( settings.value/*bool*/("elinux/faktury_pozycje/Kod")  .toBool())
      fraStrList += "<td>&nbsp;" + rowTxt[2] + "</td>";
// if ( settings.value/*bool*/("elinux/faktury_pozycje/pkwiu")  .toBool())
      fraStrList += "<td>&nbsp;" + rowTxt[3] + "</td>";
// pkwiu
// if ( settings.value/*bool*/("elinux/faktury_pozycje/ilosc")  .toBool())
      fraStrList += "<td>&nbsp;" + rowTxt[4] + "</td>";
// if ( settings.value/*bool*/("elinux/faktury_pozycje/jm")  .toBool())
      fraStrList += "<td>&nbsp;" + rowTxt[5] + "</td>";
// if ( settings.value/*bool*/("elinux/faktury_pozycje/cenajedn")  .toBool())
      fraStrList += "<td>&nbsp;" + rowTxt[6] + "</td>";
/*   
      double cenajdn = tableTow->text (i, 6).replace (",", ".").toDouble ();
      double kwota =
	cenajdn * tableTow->text (i, 4).replace (",", ".").toInt ();
if ( settings.value("elinux/faktury_pozycje/wartnetto")  .toBool())
      fraStrList += "<td>&nbsp;" + fixStr (QString::number (kwota)) + "</td>";	// netto
if ( settings.value("elinux/faktury_pozycje/rabatperc")  .toBool())
      fraStrList += "<td>&nbsp;" + QString::number (rabatValue->value ()) + "% </td>";	// rabat
if ( settings.value("elinux/faktury_pozycje/rabatval")  .toBool())
      fraStrList += "<td>&nbsp;" + fixStr (QString::number (kwota - tableTow->text (i, 7).replace (",", ".").toDouble ())) + " </td>";	// rabat value
      */
// if ( settings.value/*bool*/("elinux/faktury_pozycje/nettoafter")  .toBool())
      fraStrList += "<td>&nbsp;" + rowTxt[7] + "</td>";	// netto po rab
// if ( settings.value/*bool*/("elinux/faktury_pozycje/vatval")  .toBool())
      fraStrList += "<td>&nbsp;" + rowTxt[8] + "%</td>";
      /*
      double vatPrice = tableTow->text (i, 9).replace (",",
						       ".").toDouble () -
	tableTow->text (i,
			7).replace (",", ".").toDouble ();
			*/
      fraStrList += "<td>&nbsp;" + rowTxt[9] + "</td>";
      /*
      if ( settings.value("elinux/faktury_pozycje/vatprice")  .toBool())
      fraStrList +=
	"<td>&nbsp;" + fixStr (QString::number (vatPrice)) + "</td>"; */
// if ( settings.value("elinux/faktury_pozycje/bruttoval")  .toBool())
      fraStrList += "<td>&nbsp;" + rowTxt[10] + "</td>";
      fraStrList += "</tr>";
    }

  fraStrList += "</table>";
  fraStrList += "</td></tr>";
}

void Korekta::makeInvoiceSumm2 ()
{
//   double vatPrice = sbrutto.replace (",",  ".").toDouble () -  snetto.replace (",", ".").toDouble ();
  fraStrList += "<tr comment=\"razem\" align=\"center\"><td>";
  fraStrList += "<table width=\"100%\" border=\"0\">";
  fraStrList += "<tr class=\"stawki\">";

//  QSettings settings;
// if ( settings.value/*bool*/("elinux/faktury_pozycje/Lp") .toBool())
  fraStrList += "<td width=\"20\"  align=\"center\">&nbsp;</td>";
//if ( settings.value/*bool*/("elinux/faktury_pozycje/Nazwa")  .toBool())
  fraStrList += "<td width=\"120\" align=\"center\">&nbsp;</td>";
//if ( settings.value/*bool*/("elinux/faktury_pozycje/Kod")  .toBool())
  fraStrList += "<td width=\"60\" align=\"center\">&nbsp;</td>";
// if ( settings.value/*bool*/("elinux/faktury_pozycje/pkwiu")  .toBool())
  fraStrList += "<td width=\"60\" align=\"center\">&nbsp;</td>";
// if ( settings.value/*bool*/("elinux/faktury_pozycje/ilosc")  .toBool())
  fraStrList += "<td width=\"60\" align=\"center\">&nbsp;</td>";
// if ( settings.value/*bool*/("elinux/faktury_pozycje/jm")  .toBool())
  fraStrList += "<td width=\"20\" align=\"center\">&nbsp;</td>";
// if ( settings.value/*bool*/("elinux/faktury_pozycje/cenajedn")  .toBool())
  fraStrList += "<td width=\"60\" align=\"center\">&nbsp;</td>";
// if ( settings.value/*bool*/("elinux/faktury_pozycje/wartnetto")  .toBool())
  fraStrList += "<td width=\"60\" align=\"center\">&nbsp;</td>";
/*  
if ( settings.value("elinux/faktury_pozycje/rabatperc")  .toBool())
  fraStrList += "<td width=\"20\" align=\"center\">&nbsp;</td>";
if ( settings.value("elinux/faktury_pozycje/rabatval")  .toBool())
  fraStrList += "<td width=\"20\" align=\"center\">&nbsp;</td>";
*/
/*
if ( settings.value("elinux/faktury_pozycje/nettoafter")  .toBool())
if ( settings.value("elinux/faktury_pozycje/vatval")  .toBool())
if ( settings.value("elinux/faktury_pozycje/vatprice")  .toBool())
if ( settings.value("elinux/faktury_pozycje/bruttoval")  .toBool())
*/
  
  fraStrList += "<td width=\"140\">&nbsp;Razem:</td>";
  fraStrList += "<td width=\"60\">&nbsp;" + fixStr(QString::number(oldNetto)) + "</td>";	// netto
  fraStrList += "<td width=\"60\">&nbsp;</td>";
  fraStrList += "<td width=\"60\">&nbsp;" + fixStr (QString::number (oldVat)) + "</td>";// vat
  fraStrList += "<td width=\"60\">&nbsp;" + fixStr (QString::number (oldBrutto)) + "</td>";	// brutto



  fraStrList += "</tr>";
  fraStrList += "</table>";
  fraStrList += "</td></tr>";
}


void Korekta::makeInvoiceGoods ()
{
  fraStrList += "<tr comment=\"goods\" align=\"center\"><td>";
  fraStrList += "<h4>Pozycje na fakturze po korekcie: </h4>";
  fraStrList += "<table width=\"100%\" border=\"1\" class=\"goods\">";
  fraStrList += "<tr class=\"towaryN\">";
  
//  QSettings settings;
// if ( settings.value/*bool*/("elinux/faktury_pozycje/Lp") .toBool())
  fraStrList += "<td width=\"20\"  align=\"center\">Lp.</td>";
// if ( settings.value/*bool*/("elinux/faktury_pozycje/Nazwa")  .toBool())
 fraStrList += "<td width=\"120\" align=\"center\">Nazwa</td>";
// if ( settings.value/*bool*/("elinux/faktury_pozycje/Kod")  .toBool())
  fraStrList += "<td width=\"60\" align=\"center\">Kod</td>";
// if ( settings.value/*bool*/("elinux/faktury_pozycje/pkwiu")  .toBool())
  fraStrList += "<td width=\"60\" align=\"center\">PKWiU</td>";
// if ( settings.value/*bool*/("elinux/faktury_pozycje/ilosc")  .toBool())
  fraStrList += "<td width=\"60\" align=\"center\">Ilo¶æ</td>";
// if ( settings.value/*bool*/("elinux/faktury_pozycje/jm")  .toBool())
  fraStrList += "<td width=\"20\" align=\"center\">Jm.</td>";
//if ( settings.value/*bool*/("elinux/faktury_pozycje/cenajedn")  .toBool())
  fraStrList += "<td width=\"60\" align=\"center\">Cena jdn.</td>";
// if ( settings.value/*bool*/("elinux/faktury_pozycje/wartnetto")  .toBool())
//  fraStrList += "<td width=\"60\" align=\"center\">Warto¶æ Netto</td>";
// if ( settings.value/*bool*/("elinux/faktury_pozycje/rabatperc")  .toBool())
//  fraStrList += "<td width=\"20\" align=\"center\">Rabat %</td>";
// if ( settings.value/*bool*/("elinux/faktury_pozycje/rabatval")  .toBool())
//  fraStrList += "<td width=\"20\" align=\"center\">Rabat Warto¶æ</td>";
// if ( settings.value/*bool*/("elinux/faktury_pozycje/nettoafter")  .toBool())
  fraStrList += "<td width=\"60\" align=\"center\">Netto</td>";
// if ( settings.value/*bool*/("elinux/faktury_pozycje/vatval")  .toBool())
  fraStrList += "<td width=\"60\" align=\"center\">Stawka VAT</td>";
// if ( settings.value/*bool*/("elinux/faktury_pozycje/vatprice")  .toBool())
  fraStrList += "<td width=\"60\" align=\"center\">Kwota Vat</td>";
// if ( settings.value/*bool*/("elinux/faktury_pozycje/bruttoval")  .toBool())
  fraStrList += "<td width=\"60\" align=\"center\">Warto¶æ Brutto</td>";
  fraStrList += "</tr>";

  for (int i = 0; i < tableTow->rowCount (); ++i)
    {
      // double vatPrice = tableTow->text(i, 9).replace(",", ".").toDouble() - tableTow->text(i, 6).replace(",", ".").toDouble();
      fraStrList += "<tr class=\"towaryList\">";
// lp, nazwa, kod, ilosc, jm, cena jm., netto, vat, brutto
// if ( settings.value/*bool*/("elinux/faktury_pozycje/Lp")   .toBool())
      fraStrList += "<td>&nbsp;" + tableTow->item (i, 0)->text() + "</td>";
 
// if ( settings.value/*bool*/("elinux/faktury_pozycje/Nazwa")  .toBool())
 fraStrList += "<td>&nbsp;" + tableTow->item (i, 1)->text() + "</td>";
//if ( settings.value/*bool*/("elinux/faktury_pozycje/Kod")  .toBool())
      fraStrList += "<td>&nbsp;" + tableTow->item (i, 2)->text() + "</td>";
// if ( settings.value/*bool*/("elinux/faktury_pozycje/pkwiu")  .toBool())
      fraStrList += "<td>&nbsp;" + tableTow->item (i, 3)->text() + "</td>";
// pkwiu
// if ( settings.value/*bool*/("elinux/faktury_pozycje/ilosc")  .toBool())
      fraStrList += "<td>&nbsp;" + tableTow->item (i, 4)->text() + "</td>";
// if ( settings.value/*bool*/("elinux/faktury_pozycje/jm")  .toBool())
      fraStrList += "<td>&nbsp;" + tableTow->item (i, 5)->text() + "</td>";
// if ( settings.value/*bool*/("elinux/faktury_pozycje/cenajedn")  .toBool())
      fraStrList += "<td>&nbsp;" + tableTow->item (i, 6)->text() + "</td>";
/*   
      double cenajdn = tableTow->text (i, 6).replace (",", ".").toDouble ();
      double kwota =
	cenajdn * tableTow->text (i, 4).replace (",", ".").toInt ();
if ( settings.value("elinux/faktury_pozycje/wartnetto")  .toBool())
      fraStrList += "<td>&nbsp;" + fixStr (QString::number (kwota)) + "</td>";	// netto
if ( settings.value("elinux/faktury_pozycje/rabatperc")  .toBool())
      fraStrList += "<td>&nbsp;" + QString::number (rabatValue->value ()) + "% </td>";	// rabat
if ( settings.value("elinux/faktury_pozycje/rabatval")  .toBool())
      fraStrList += "<td>&nbsp;" + fixStr (QString::number (kwota - tableTow->text (i, 7).replace (",", ".").toDouble ())) + " </td>";	// rabat value
      */
// if ( settings.value("elinux/faktury_pozycje/nettoafter")  .toBool())
      fraStrList += "<td>&nbsp;" + tableTow->item(i, 7)->text() + "</td>";	// netto po rab
// if ( settings.value("elinux/faktury_pozycje/vatval")  .toBool())
      fraStrList += "<td>&nbsp;" + tableTow->item (i, 8)->text() + "%</td>";
      double vatPrice = tableTow->item(i, 9)->text().replace (",",
						       ".").toDouble () -
	tableTow->item(i,
			7)->text().replace (",", ".").toDouble ();
      fraStrList += "<td>&nbsp;" + fixStr(QString::number(vatPrice).replace( ",", "." )) + "</td>";
      /*
      if ( settings.value("elinux/faktury_pozycje/vatprice")  .toBool())
      fraStrList +=
	"<td>&nbsp;" + fixStr (QString::number (vatPrice)) + "</td>"; */
// if ( settings.value/*bool*/("elinux/faktury_pozycje/bruttoval")  .toBool())
      fraStrList += "<td>&nbsp;" + tableTow->item(i, 9)->text() + "</td>";
      fraStrList += "</tr>";
    }

  fraStrList += "</table>";
  fraStrList += "</td></tr>";
}

void Korekta::makeInvoiceSumm ()
{
  double vatPrice = sbrutto.replace (",",  ".").toDouble () -
    snetto.replace (",", ".").toDouble ();
  fraStrList += "<tr comment=\"razem\" align=\"center\"><td>";
  fraStrList += "<table width=\"100%\" border=\"0\">";
  fraStrList += "<tr class=\"stawki\">";

//  QSettings settings;
// if ( settings.value/*bool*/("elinux/faktury_pozycje/Lp") .toBool())
  fraStrList += "<td width=\"20\"  align=\"center\">&nbsp;</td>";
//if ( settings.value/*bool*/("elinux/faktury_pozycje/Nazwa")  .toBool())
  fraStrList += "<td width=\"120\" align=\"center\">&nbsp;</td>";
//if ( settings.value/*bool*/("elinux/faktury_pozycje/Kod")  .toBool())
  fraStrList += "<td width=\"60\" align=\"center\">&nbsp;</td>";
// if ( settings.value/*bool*/("elinux/faktury_pozycje/pkwiu")  .toBool())
  fraStrList += "<td width=\"60\" align=\"center\">&nbsp;</td>";
// if ( settings.value/*bool*/("elinux/faktury_pozycje/ilosc")  .toBool())
  fraStrList += "<td width=\"60\" align=\"center\">&nbsp;</td>";
// if ( settings.value/*bool*/("elinux/faktury_pozycje/jm")  .toBool())
  fraStrList += "<td width=\"20\" align=\"center\">&nbsp;</td>";
// if ( settings.value/*bool*/("elinux/faktury_pozycje/cenajedn")  .toBool())
  fraStrList += "<td width=\"60\" align=\"center\">&nbsp;</td>";
// if ( settings.value/*bool*/("elinux/faktury_pozycje/wartnetto")  .toBool())
  fraStrList += "<td width=\"60\" align=\"center\">&nbsp;</td>";
/*  
if ( settings.value("elinux/faktury_pozycje/rabatperc")  .toBool())
  fraStrList += "<td width=\"20\" align=\"center\">&nbsp;</td>";
if ( settings.value("elinux/faktury_pozycje/rabatval")  .toBool())
  fraStrList += "<td width=\"20\" align=\"center\">&nbsp;</td>";
*/
/*
if ( settings.value("elinux/faktury_pozycje/nettoafter")  .toBool())
if ( settings.value("elinux/faktury_pozycje/vatval")  .toBool())
if ( settings.value("elinux/faktury_pozycje/vatprice")  .toBool())
if ( settings.value("elinux/faktury_pozycje/bruttoval")  .toBool())
*/
  
  fraStrList += "<td width=\"140\">&nbsp;Razem:</td>";
  fraStrList += "<td width=\"60\">&nbsp;" + snetto + "</td>";	// netto
  fraStrList += "<td width=\"60\">&nbsp;</td>";
  fraStrList += "<td width=\"60\">&nbsp;" + fixStr (QString::number (vatPrice)) + "</td>";// vat
  fraStrList += "<td width=\"60\">&nbsp;" + sbrutto + "</td>";	// brutto



  fraStrList += "</tr>";
  fraStrList += "</table>";
  fraStrList += "</td></tr>";
}

void Korekta::makeInvoiceSummAll ()
{
    
  QSettings settings;
    
  fraStrList += "<tr comment=\"podsumowanie\"><td>";
  fraStrList += "<table width=\"100%\" border=\"0\">";
  fraStrList += "<tr>";
  fraStrList += "<td witdh=\"20\">&nbsp;</td>";
  fraStrList += "<td width=\"48%\"> ";
  double endVal = diffLabel->text().replace(",", ".").toDouble();
  
  if ( endVal > 1)
  fraStrList += "<h4>Do zap³aty: " + diffLabel->text() + " " + currency + "</h4>";
  else 
      fraStrList += "<h4>Do zwrotu: " + fixStr(QString::number(endVal * -1)) + " " + currency + "</h4>";
  
  fraStrList += "<h5>s³ownie:" + slownie (diffLabel->text(), currency) + "</h5>";
  fraStrList += "<h5>forma p³atno¶ci: " + platCombo->currentText () + "<br>";
  fraStrList +=
    "termin p³atno¶ci: " + liabDate->date().toString ("yyyy-MM-dd") + "<br>";
  
  QString paym1 = settings.value("elinux/faktury/paym1").toString();
  
  if ( paym1.left(3) == platCombo->currentText().left(3) )
  fraStrList += "<b>Zap³acono gotówk±</b> <br>";
  
  fraStrList += "</h5>";
  fraStrList += "<h4>" + additEdit->text () + "</h4>";
  
  fraStrList += "</td>";
  fraStrList += "<td witdh=\"20\">&nbsp;</td>";
  fraStrList += "<td width=\"48%\" valign=\"top\">";
  fraStrList += "<table width=\"80%\" class=\"stawki\" border=\"0\">";
  fraStrList += "<tr>";
  fraStrList +=
    "<td colspan=\"4\"><hr width=\"100%\" noshade=\"noshade\" color=\"black\" /></td>";
  fraStrList += "</tr>";
  fraStrList += "<tr>";
  fraStrList += "<td colspan=\"4\"><h5>Ogó³em stawkami:&nbsp;</h5></td>";	// Ogó³em stawkami:
  fraStrList += "</tr>";
  fraStrList += getStawkami();
  
  fraStrList += "<tr>";
  fraStrList += "<td>&nbsp;</td>"; // netto
  fraStrList += "<td>&nbsp;</td>"; // stawka
  fraStrList += "<td>&nbsp;</td>"; // podatek
  fraStrList += "<td>&nbsp;</td>"; // brutto
  fraStrList += "</tr>";

  fraStrList += "</table>";
  fraStrList += "</td>";
  fraStrList += "</tr>";
  fraStrList += "</table>";
  fraStrList += "</td></tr>";
}


QString Korekta::getStawkami()
{
    QStringList out;
    QSettings settings;
    QStringList stawki = 
      settings.value("elinux/faktury/stawki").toString().split("|"); 
    QMap<int, double> stawkiNetto; 
    QMap<int, double> stawkiVat;     
    QMap<int, double> stawkiBrutto;     
    // every currency in int value is equeal vat currncy
    
    int ssize = stawki.size();
    // qDebug( "%d", ssize ); 
    
      for (int i = 0; i < tableTow->rowCount (); ++i)
    {
	for ( int y = 0; y < ssize; ++y )
	  {
	    if ( stawki[y] == tableTow->item(i, 8)->text() ) {
		stawkiNetto[y] += tableTow->item(i, 7)->text().replace(",", ".").toDouble();
		stawkiBrutto[y] += tableTow->item(i, 9)->text().replace(",", ".").toDouble();
		stawkiVat[y] += stawkiBrutto[y] - stawkiNetto[y];
	    } else {
		    stawkiNetto[y] += 0;
		stawkiBrutto[y] += 0;
				   		stawkiVat[y] += 0;

		}
	}
      }
      
	for ( int y = 0; y < ssize; ++y )
	  {
  out += "<tr>";
  out += "<td>" + fixStr(QString::number( stawkiNetto[y] )) + "</td>"; // netto
  out += "<td>" + stawki[y] + "</td>"; // stawka
  out += "<td>" + fixStr(QString::number( stawkiVat[y] )) + "</td>"; // podatek
  out += "<td>" + fixStr(QString::number( stawkiBrutto[y] )) + "</td>"; // brutto
  out += "</tr>";
	    
	}
	return out.join(" ");
      
}


void Korekta::makeInvoiceFooter ()
{
  fraStrList += "<tr comment=\"podpis\" align=\"center\"><td>";
  fraStrList += "<br><br><br><br>";
  fraStrList += "<table width=\"80%\" border=\"0\">";
  fraStrList += "<tr>";
  fraStrList += "<td witdh=\"20\">&nbsp;</td>";
  fraStrList += "<td witdh=\"48%\" align=\"center\"> ";
  fraStrList += "<hr width=\"100%\" noshade=\"noshade\" color=\"black\" />";
  fraStrList += "</td>";
  fraStrList += "<td witdh=\"60\">&nbsp;</td>";
  fraStrList += "<td witdh=\"20\">&nbsp;</td>";
  fraStrList += "<td witdh=\"48%\" align=\"center\"> ";
  fraStrList += "<hr width=\"100%\" noshade=\"noshade\" color=\"black\" />";
  fraStrList += "</td>";
  fraStrList += "</tr>";
  fraStrList += "<tr class=\"podpisy\">";
  fraStrList += "<td witdh=\"20\">&nbsp;</td>";
  fraStrList += "<td witdh=\"48%\" align=\"center\"> ";
  fraStrList +=
    "Imiê i nazwisko osoby upowa¿nionej do wystawienia faktury VAT";
  fraStrList += "</td>";
  fraStrList += "<td witdh=\"60\">&nbsp;</td>";
  fraStrList += "<td witdh=\"20\">&nbsp;</td>";
  fraStrList += "<td witdh=\"48%\" align=\"center\"> ";
  fraStrList += "Imiê i nazwisko osoby upowa¿nionej do odbioru faktury VAT";
  fraStrList += "</td>";
  fraStrList += "</tr>";
  fraStrList += "</table>";
  fraStrList += "</td></tr>";
  fraStrList += "</table>";
  fraStrList += "<tr comment=\"comment\" align=\"left\"><td>";
  fraStrList += "</td></tr>";
  fraStrList += "</table>";
  fraStrList += "</body>";
  fraStrList += "</html>";
}

void Korekta::makeInvoice ()
{
  if (kontrName->text () == "")
    {
      QMessageBox::information (this, "QFaktury", "Wybierz kontrahenta",
				QMessageBox::Ok);
      return;
    }

  if (tableTow->rowCount () == 0)
    {
      QMessageBox::information (this, "QFaktury", "Nie ma towarów",
				QMessageBox::Ok);
      return;
    }

  fraStrList.clear();

  makeInvoiceHeadar ();
  makeInvoiceBody ();
  makeInvoiceCorr ();
  makeInvoiceGoods2 ();
  makeInvoiceSumm2 ();
  makeInvoiceGoods ();
  makeInvoiceSumm ();
  makeInvoiceSummAll ();
  makeInvoiceFooter ();

  //X print invoice
  QFile file ("/tmp/invoice.html");
  if (file.open (QIODevice::WriteOnly))
    {
      QTextStream stream (&file);
      for (QStringList::Iterator it = fraStrList.begin ();
	   it != fraStrList.end (); ++it)
	stream << *it << "\n";
      file.close ();
    }

}


void Korekta::saveInvoice ()
{
  if (kontrName->text () == "")
    {
      QMessageBox::information (this, "QFaktury", "Wybierz kontrahenta",
				QMessageBox::Ok);
      return;
    }

  if (tableTow->rowCount () == 0)
    {
      QMessageBox::information (this, "QFaktury", "Nie ma towarów",
				QMessageBox::Ok);
      return;
    }

  QDomDocument doc ("faktury");
  QDomElement root;
  QString fileName = fName;

  QFile file;
  if (fileName == "")
    {
      fileName = QDate::currentDate ().toString ("dd-MM-yyyy");
      qDebug ()<<fileName;

      int pNumber = 0;
      file.setFileName (progDir2 + "/faktury/h" + fileName + "_" +
		    QString::number (pNumber) + ".xml");
      pNumber += 1;
      ret =
	"h" + fileName + "_" + QString::number (pNumber) + ".xml" + "|";

      while (file.exists ())
	{
	  file.setFileName (progDir2 + "/faktury/h" + fileName + "_" +
			QString::number (pNumber) + ".xml");
	  ret =
	    "h" + fileName + "_" + QString::number (pNumber) + ".xml" + "|";
	  pNumber += 1;
	}
      // qDebug( "2" );
    }
  else
    {
      file.setFileName (progDir2 + "/faktury/" + fileName);
      ret = fileName + "|";
      // qDebug( "1" );
    }

  
  
  // qDebug( "adsad %s", file.name() ); 
  // if (!file.open (QIODevice::ReadOnly)) {

  root = doc.createElement ("korekta");
  root.setAttribute ("nr", korNr->text ());
  ret += korNr->text () + "|";
  root.setAttribute ("data.wyst",
		     QDate::currentDate ().toString ("yyyy-MM-dd"));
  root.setAttribute ("data.korekty",
		     sellingDate2->date ().toString ("yyyy-MM-dd"));
  ret += QDate::currentDate ().toString ("yyyy-MM-dd") + "|";
  root.setAttribute ("data.sprzed",
		     sellingDate->date ().toString ("yyyy-MM-dd"));

  QSettings settings1;
  settings1.beginGroup ("elinux");

  /*
  if (windowTitle ().right (3) == "VAT")
    {
      root.setAttribute ("type", "FVAT");
      settings1.writeEntry ("faktury/fvat", frNr->text ());
      ret += "FVAT|";
    }
  else
    {
      root.setAttribute ("type", "FPro");
      settings1.writeEntry ("faktury/fpro", frNr->text ());
      ret += "FPro|";
    }
  */
   ret += "korekta|";
  root.setAttribute ("type", "korekta");
 settings1.setValue("faktury/korNr", korNr->text ());
  
  settings1.endGroup ();

  doc.appendChild (root);

  QDomElement sprzedawca;
  sprzedawca = doc.createElement ("sprzedawca");
  QSettings settings;
  sprzedawca.setAttribute ("nazwa",
			   settings.value ("przelewy/user/nazwa").toString());
  sprzedawca.setAttribute ("kod", settings.value ("przelewy/user/kod").toString());
  sprzedawca.setAttribute ("miasto",
			   settings.value ("przelewy/user/miejscowosc").toString());
  sprzedawca.setAttribute ("ulica",
			   settings.value ("przelewy/user/adres").toString());
  sprzedawca.setAttribute ("nip", settings.value ("przelewy/user/nip").toString());
  sprzedawca.setAttribute ("konto",
			   settings.value ("przelewy/user/konto").toString().
			   replace (" ", "-"));
  root.appendChild (sprzedawca);

  QDomElement nabywca;
  nabywca = doc.createElement ("nabywca");
  QStringList kht = kontrName->text ().split(",");
  /* here can be bug, if kontrahent name would be with commas
     so what, block this
   */
  nabywca.setAttribute ("nazwa", kht[0]);
  ret += kht[0] + "|";
  nabywca.setAttribute ("miasto", kht[1]);
  nabywca.setAttribute ("ulica", kht[2]);

  nabywca.setAttribute ("nip", kht[3].replace (" ", "").replace ("NIP:", ""));
  ret += kht[3].replace (" ", "").replace ("NIP:", "");
  root.appendChild (nabywca);

// sellingDate2
  
  QDomElement towary;
  QDomElement goods;
  goods = doc.createElement ("goods");
  goods.setAttribute ("goods::rabat", QString::number (rabatValue->value ()));

  for (int i = 0; i < tableTow->rowCount (); ++i)
    {
      towary = doc.createElement ("towar:" + tableTow->item (i, 0)->text());
      goods.setAttribute ("goods::count", QString::number (i + 1));
      towary.setAttribute ("Lp.", tableTow->item (i, 0)->text());
      towary.setAttribute ("Nazwa", tableTow->item (i, 1)->text());
      towary.setAttribute ("Kod", tableTow->item (i, 2)->text());
      towary.setAttribute ("PKWiU", tableTow->item (i, 3)->text());
      towary.setAttribute ("Ilosc", tableTow->item (i, 4)->text());
      towary.setAttribute ("Jm.", tableTow->item (i, 5)->text());
      towary.setAttribute ("Cena_jdn.", tableTow->item (i, 6)->text());
      double cenajdn = tableTow->item (i, 6)->text().replace (",", ".").toDouble ();
      double kwota =
	cenajdn * tableTow->item (i, 4)->text().replace (",", ".").toInt ();

      towary.setAttribute ("Wartosc_Netto", fixStr (QString::number (kwota)));	// netto

      towary.setAttribute ("Rabat", QString::number (rabatValue->value ()));	// rabat
      towary.setAttribute ("Netto_po_rabacie", tableTow->item (i, 7)->text());
      towary.setAttribute ("Stawka_VAT", tableTow->item (i, 8)->text());
      double vatPrice = tableTow->item (i, 9)->text().replace (",",
						       ".").toDouble () -
	tableTow->item (i, 7)->text().replace (",", ".").toDouble ();

      towary.setAttribute ("Kwota_Vat", fixStr (QString::number (vatPrice)));
      towary.setAttribute ("Wartosc_Brutto", tableTow->item (i, 9)->text());
      goods.appendChild (towary);

    }
  root.appendChild (goods);
  
  QDomElement goodsRoot;
  QDomElement goodsOld;
  goodsRoot = doc.createElement ("goodsOldRoot");
  
  int y = towaryPKor.count();
  QStringList tmp;
  for (int i = 0; i < y; ++i)
    {
      tmp = towaryPKor[i].split("|");
      goodsOld = doc.createElement ("goodOld:" + tmp[0]);
      goodsRoot.setAttribute ("goods::count", QString::number (i + 1));
      goodsOld.setAttribute ("Lp.", QString::number (i + 1) );
      goodsOld.setAttribute ("Nazwa", tmp[1] );
      goodsOld.setAttribute ("Kod", tmp[2] );
      goodsOld.setAttribute ("PKWiU", tmp[3] );
      goodsOld.setAttribute ("Ilosc", tmp[4] );
      goodsOld.setAttribute ("Cena_jdn.", tmp[6] );
      
      goodsOld.setAttribute ("Jm.", tmp[5] );
      goodsOld.setAttribute ("Wartosc_Netto", tmp[7] );
      // goodsOld.setAttribute ("Rabat", tmp[7] );
      goodsOld.setAttribute ("Stawka_VAT", tmp[8] );
      goodsOld.setAttribute ("Kwota_Vat", tmp[9] );
      goodsOld.setAttribute ("Wartosc_Brutto", tmp[10] );
      goodsRoot.appendChild (goodsOld);
    }
  
  
  root.appendChild (goodsRoot);
  // }


  QDomElement addinfo;
  addinfo = doc.createElement ("addinfo");
  addinfo.setAttribute ("text", additEdit->text ());
  addinfo.setAttribute ("forma.plat",
			QString::number (platCombo->currentIndex ()));
  addinfo.setAttribute ("przyczyna",
			QString::number (reasonCombo->currentIndex ()));
//  qDebug( "moux" );
  addinfo.setAttribute ("liabDate", sellingDate->date ().toString ("yyyy-MM-dd"));

  // liabDate->date().toString ("yyyy-MM-dd")
  addinfo.setAttribute ("waluta", 
			QString::number (citem));
//			QString::number (currCombo->currentItem ()));
  root.appendChild (addinfo);

  QString xml = doc.toString ();
  file.close ();
  file.open (QIODevice::WriteOnly);
  QTextStream ts (&file);
  ts << xml;
  // qDebug ( "ret" + ret );
  file.close ();
  accept ();
}

QString Korekta::numbersCount(int in, int x)
{
    QString tmp2, tmp = QString::number(in);
    tmp2 = "";
    int incr = x - tmp.length();
    for (int i = 0; i < incr; ++i)
	tmp2 += "0";
    return tmp2 + tmp;
}

void Korekta::backBtnClick()
{
  QString tmp;
  QSettings settings;

  QString prefix;
//  int numbers;
  
   tmp = settings.value ("elinux/faktury/korNr").toString();
   prefix = settings.value ("elinux/faktury/prefix").toString();

  QStringList one1 = tmp.split("/");
  one1[0] = one1[0].remove(prefix);
  // qDebug( one1[0] );
  int nr = one1[0].toInt () + 1;
  lastInvoice = prefix + numbersCount(nr, settings.value("elinux/faktury/chars_in_symbol").toInt());
  
  if ( settings.value/*bool*/ ("elinux/faktury/day") .toBool())
     lastInvoice += "/" + QDate::currentDate ().toString ("dd");
  
  if ( settings.value/*bool*/ ("elinux/faktury/month") .toBool())
     lastInvoice += "/" + QDate::currentDate ().toString ("MM");
      
  if ( settings.value/*bool*/ ("elinux/faktury/year") .toBool()) {
  if ( !settings.value/*bool*/ ("elinux/faktury/shortYear") .toBool()) 
     lastInvoice += "/" + QDate::currentDate ().toString ("yy");
  else
     lastInvoice += "/" + QDate::currentDate ().toString ("yyyy");
 }
 
  
  korNr->setText (lastInvoice);
}


/*
void Korekta::backBtnClick()
{
  QString tmp;
  QSettings settings;

  if (windowTitle ().right (3) == "VAT")
    {
      tmp = settings.value ("elinux/faktury/fvat");
    }
  else
    {
      tmp = settings.value ("elinux/faktury/fpro");
    }
   tmp = settings.value ("elinux/faktury/korNr");

  QStringList one1 = QStringList::split ("/", tmp);
  int nr = one1[0].toInt () + 1;
  lastInvoice =
    QString::number (nr) + "/" + QDate::currentDate ().toString ("MM/yyyy");
  korNr->setText (lastInvoice);
}
*/
Korekta::Korekta(QWidget *parent): QDialog(parent) {
    setupUi(this);
    init();
}
