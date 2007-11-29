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
#include <qprinter.h>
#include <qpainter.h>
#include <qpaintdevicemetrics.h>
#include <qsimplerichtext.h>
#include <qimage.h>

#include <qpicture.h>

#include <qdatetime.h>
#include <qdir.h>
#include <qdom.h>
#include <qfont.h>

#include <qapplication.h>


#include "preview.h"

QStringList uWx;
QStringList uPx;
// QString fileName;

void
pUS::readData ()
{
  qDebug ("%s %s:%d", __FUNCTION__, __FILE__, __LINE__);
  QDomDocument doc ("przelewy");
  QDomElement root;
  QDomElement nadawca;
  QDomElement odbiorca;

  QFile file (progDir2 + "/" + fileName);

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
  qDebug ("fileName " + fileName);
  root = doc.documentElement ();
  // root.attribute("date", "");
  if (root.attribute ("typ", "") == "USPrzelew")
    comboBox1->setCurrentText ("Przelew");
  if (root.attribute ("typ", "").left (4) == "USWp")
    comboBox1->setCurrentText ("Wp³ata");

  kwotaEdit->setText (root.attribute ("kwota", ""));
//    lineEdit17->setText( root.attribute("title", ""));

  nadawca = root.firstChild ().toElement ();
  odbiorca = root.lastChild ().toElement ();
  // nadawca.attribute("name", "NULL"));

  cbNazwa->setCurrentText (odbiorca.attribute ("name", ""));
  codeEdit2->setText (odbiorca.attribute ("code", ""));
  placeEdit2->setText (odbiorca.attribute ("place", ""));
  addressEdit2->setText (odbiorca.attribute ("address", ""));
  accountEdit2->setText (odbiorca.attribute ("account", ""));

  nameEdit->setText (nadawca.attribute ("name", ""));
  codeEdit->setText (nadawca.attribute ("code", ""));
  placeEdit->setText (nadawca.attribute ("place", ""));
  addressEdit->setText (nadawca.attribute ("address", ""));
  accountEdit->setText (nadawca.attribute ("account", ""));

  nipEdit->setText (nadawca.attribute ("nip"));	// nazwa odb1.
  // aaaaaaaaa
  if (nadawca.attribute ("drugiIdT") == "N")
    secIdType->setCurrentItem (0);
  if (nadawca.attribute ("drugiIdT") == "R")
    secIdType->setCurrentItem (1);
  if (nadawca.attribute ("drugiIdT") == "P")
    secIdType->setCurrentItem (2);
  if (nadawca.attribute ("drugiIdT") == "1")
    secIdType->setCurrentItem (3);
  if (nadawca.attribute ("drugiIdT") == "2")
    secIdType->setCurrentItem (4);



  nrdek->setText (nadawca.attribute ("nrdek"));
  dek->setText (nadawca.attribute ("dek"));
  nrdec->setText (nadawca.attribute ("nrdec"));

  qDebug ("fileName " + fileName);
}


void
pUS::init ()
{
  QTextCodec::setCodecForCStrings (QTextCodec::codecForName ("ISO8859-2"));
  QTextCodec::setCodecForTr (QTextCodec::codecForName ("ISO8859-2"));
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

  // wczytaj liste urzedow

  progDir2 = QDir::homeDirPath () + "/przelewy";

  QDomDocument doc ("kontrahenci");
  QDomElement root;
  QDomElement urzad;
  QDomElement firma;

  QFile file (progDir2 + "/kontrah.xml");
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


      for (QDomNode n = urzad.firstChild (); !n.isNull ();
	   n = n.nextSibling ())
	{
	  text = n.toElement ().attribute ("name");
	  cbNazwa->insertItem (text, -1);
	}
    }

}

void
pUS::slownie ()
{
  QString tmp = kwotaEdit->text ().remove (kwotaEdit->text ().find (","), 3);

  QString setki = tmp.right (3);
  QString tysiace;
  switch (tmp.length ())
    {
    case 4:
      tysiace = tmp.left (1);
      break;
    case 5:
      tysiace = tmp.left (2);
      break;
    case 6:
      tysiace = tmp.left (3);
      break;
    default:
      tysiace = "";
      break;
    }

  QString out;

  QStringList jedynki;
  jedynki << tr ("jeden") << tr ("dwa") << tr ("trzy") << tr ("cztery") <<
    tr ("piêæ") << tr ("sze¶æ") << tr ("siedem") << tr ("osiem") <<
    tr ("dziewiêæ");

  QStringList nascie;
  nascie << tr ("jedena¶cie") << tr ("dwana¶cie") << tr ("trzyna¶cie") <<
    tr ("czterna¶cie") << tr ("piêtna¶cie") << tr ("szesna¶cie") <<
    tr ("siedemna¶cie") << tr ("osiemna¶cie") << tr ("dziewiêtna¶cie");

  QStringList escia;
  escia << tr ("dwadziescia") << tr ("trzydziesci") << tr ("czterdzie¶ci") <<
    tr ("piêdziesi±t") << tr ("sze¶dziesi±t") << tr ("siedemdziesi±t") <<
    tr ("osiemdziesi±t") << tr ("dziewiêædziesi±t");

  QStringList sta;
  sta << tr ("sto") << tr ("dwie¶cie") << tr ("trzysta") << tr ("czterysta")
    << tr ("piêæset") << tr ("sze¶æset") << tr ("siedemset") <<
    tr ("osiemset") << tr ("dziewiêæset");


  // ******************************************************************
  while (tysiace.length () < 3)
    tysiace = "0" + tysiace;

  switch (tysiace.left (1).toInt ())
    {
    case 1:
      out += " " + sta[0];
      break;
    case 2:
      out += " " + sta[1];
      break;
    case 3:
      out += " " + sta[2];
      break;
    case 4:
      out += " " + sta[3];
      break;
    case 5:
      out += " " + sta[4];
      break;
    case 6:
      out += " " + sta[5];
      break;
    case 7:
      out += " " + sta[6];
      break;
    case 8:
      out += " " + sta[7];
      break;
    case 9:
      out += " " + sta[8];
      break;
    case 0:
      out += "";
      break;
    }

  switch (tysiace.mid (1, 1).toInt ())
    {
      //    case 1: out += nascie[0];
      // break;
    case 2:
      out += " " + escia[0];
      break;
    case 3:
      out += " " + escia[1];
      break;
    case 4:
      out += " " + escia[2];
      break;
    case 5:
      out += " " + escia[3];
      break;
    case 6:
      out += " " + escia[4];
      break;
    case 7:
      out += " " + escia[5];
      break;
    case 8:
      out += " " + escia[6];
      break;
    case 9:
      out += " " + escia[7];
      break;
    case 0:
      out += "";
      break;
    }


  if (tysiace.mid (1, 1).toInt () == 1)
    {
      switch (setki.right (1).toInt ())
	{
	case 1:
	  out += " " + nascie[0];
	  break;
	case 2:
	  out += " " + nascie[1];
	  break;
	case 3:
	  out += " " + nascie[2];
	  break;
	case 4:
	  out += " " + nascie[3];
	  break;
	case 5:
	  out += " " + nascie[4];
	  break;
	case 6:
	  out += " " + nascie[5];
	  break;
	case 7:
	  out += " " + nascie[6];
	  break;
	case 8:
	  out += " " + nascie[7];
	  break;
	case 9:
	  out += " " + nascie[8];
	  break;
	case 0:
	  out += "";
	  break;
	}
    }
  else
    {
      switch (tysiace.right (1).toInt ())
	{
	case 1:
	  out += " " + jedynki[0];
	  break;
	case 2:
	  out += " " + jedynki[1];
	  break;
	case 3:
	  out += " " + jedynki[2];
	  break;
	case 4:
	  out += " " + jedynki[3];
	  break;
	case 5:
	  out += " " + jedynki[4];
	  break;
	case 6:
	  out += " " + jedynki[5];
	  break;
	case 7:
	  out += " " + jedynki[6];
	  break;
	case 8:
	  out += " " + jedynki[7];
	  break;
	case 9:
	  out += " " + jedynki[8];
	  break;
	case 0:
	  out += "";
	  break;
	}

    }

  if (out.length () > 2)
    out += " tys.";

  //***************************************************************
  while (setki.length () < 3)
    setki = "0" + setki;

  switch (setki.left (1).toInt ())
    {
    case 1:
      out += " " + sta[0];
      break;
    case 2:
      out += " " + sta[1];
      break;
    case 3:
      out += " " + sta[2];
      break;
    case 4:
      out += " " + sta[3];
      break;
    case 5:
      out += " " + sta[4];
      break;
    case 6:
      out += " " + sta[5];
      break;
    case 7:
      out += " " + sta[6];
      break;
    case 8:
      out += " " + sta[7];
      break;
    case 9:
      out += " " + sta[8];
      break;
    case 0:
      out += "";
      break;
    }

  switch (setki.mid (1, 1).toInt ())
    {
      //    case 1: out += nascie[0];
      // break;
    case 2:
      out += " " + escia[0];
      break;
    case 3:
      out += " " + escia[1];
      break;
    case 4:
      out += " " + escia[2];
      break;
    case 5:
      out += " " + escia[3];
      break;
    case 6:
      out += " " + escia[4];
      break;
    case 7:
      out += " " + escia[5];
      break;
    case 8:
      out += " " + escia[6];
      break;
    case 9:
      out += " " + escia[7];
      break;
    case 0:
      out += "";
      break;
    }


  if (setki.mid (1, 1).toInt () == 1)
    {
      switch (setki.right (1).toInt ())
	{
	case 1:
	  out += " " + nascie[0];
	  break;
	case 2:
	  out += " " + nascie[1];
	  break;
	case 3:
	  out += " " + nascie[2];
	  break;
	case 4:
	  out += " " + nascie[3];
	  break;
	case 5:
	  out += " " + nascie[4];
	  break;
	case 6:
	  out += " " + nascie[5];
	  break;
	case 7:
	  out += " " + nascie[6];
	  break;
	case 8:
	  out += " " + nascie[7];
	  break;
	case 9:
	  out += " " + nascie[8];
	  break;
	case 0:
	  out += "";
	  break;
	}
    }
  else
    {
      switch (setki.right (1).toInt ())
	{
	case 1:
	  out += " " + jedynki[0];
	  break;
	case 2:
	  out += " " + jedynki[1];
	  break;
	case 3:
	  out += " " + jedynki[2];
	  break;
	case 4:
	  out += " " + jedynki[3];
	  break;
	case 5:
	  out += " " + jedynki[4];
	  break;
	case 6:
	  out += " " + jedynki[5];
	  break;
	case 7:
	  out += " " + jedynki[6];
	  break;
	case 8:
	  out += " " + jedynki[7];
	  break;
	case 9:
	  out += " " + jedynki[8];
	  break;
	case 0:
	  out += "";
	  break;
	}

    }
  QString grosze =
    kwotaEdit->text ().remove (0, kwotaEdit->text ().find (",") + 1);
  slownieLbl->setText (out + " " + grosze + "/100 groszy");
}

/*!
  *    Special Method for account display
  !*/
QString
pUS::rozstrzel (QString in)
{
  QString tmp, out;
  switch (rozSp)
    {
    case 0:
      tmp = in.replace ("-", "");
      break;
    case 1:
      tmp = in.replace ("-", " ");
      break;
    case 2:
      tmp = in.replace ("-", "  ");
      break;
    case 3:
      tmp = in.replace ("-", "   ");
      break;
    case 4:
      tmp = in.replace ("-", "    ");
      break;
    case 5:
      tmp = in.replace ("-", "     ");
      break;
    }
  int x = tmp.length ();
  for (int i = 0; i < x; ++i)
    out += tmp[i] + " ";
  return out;
}

void
pUS::kwotaKeyDown ()
{
  if (comboBox1->currentItem () == 1)
    slownie ();
}

void
pUS::makeWplata ()
{
  slownie ();
//    nameEdit2->setText( nameEdit->text() );
//    codeEdit2->setText( codeEdit->text()  );
//    placeEdit2->setText( placeEdit->text() );
//    addressEdit2->setText( addressEdit->text() );
//    accountEdit2->setText( accountEdit->text()  );
}

int
pUS::getXSett (QString in)
{
  int x = in.find (',');
  // int y = in.length();
  // qDebug( in.left(x) );
  // qDebug( in.right(y - (x + 1)) );
  return in.left (x).toInt ();
}

int
pUS::getYSett (QString in)
{
  int x = in.find (',');
  int y = in.length ();
  // qDebug( in.left(x) );
  // qDebug( in.right(y - (x + 1)) );
  return in.right (y - (x + 1)).toInt ();
}

void
pUS::readSettings ()
{
  QSettings settings;
  /*
     nameEdit->setText( settings.readEntry( "przelewy/user/nazwa" ) );
     placeEdit->setText( settings.readEntry( "przelewy/user/miejscowosc" ) );
     codeEdit->setText( settings.readEntry( "przelewy/user/kod" ) );
     addressEdit->setText( settings.readEntry( "przelewy/user/adres" ) );
     accountEdit->setText( settings.readEntry( "przelewy/user/konto" ) );    
   */
  // 
  font.fromString (settings.readEntry ("przelewy/czcionka"));
  rozSp = settings.readEntry ("przelewy/przerwy").toInt ();

  /*
     // checkboxy
     if ( settings.readEntry( "przelewy/przelew_wbud" ) == "true" )
     checkBox1->setChecked( TRUE );
     if (  settings.readEntry( "przelewy/zus_wbud" ) == "true" )
     checkBox2->setChecked(  TRUE );
     if (   settings.readEntry( "przelewy/us_wbud" ) == "true" )
     checkBox3->setChecked( TRUE  );
   */
  // looop for przelew

  u_id = QStringList::split (";", settings.readEntry ("przelewy/u_id"));
  u_idzob = QStringList::split (";", settings.readEntry ("przelewy/u_idzob"));
  u_ksw = QStringList::split (";", settings.readEntry ("przelewy/u_ksw"));
  u_kwota = QStringList::split (";", settings.readEntry ("przelewy/u_kwota"));
  uWx = QStringList::split (";", settings.readEntry ("przelewy/u_wx"));
  uPx = QStringList::split (";", settings.readEntry ("przelewy/u_px"));
  u_nazwa1 =
    QStringList::split (";", settings.readEntry ("przelewy/u_nazwa1"));
  u_nazwa2 =
    QStringList::split (";", settings.readEntry ("przelewy/u_nazwa2"));
  u_nip = QStringList::split (";", settings.readEntry ("przelewy/u_nip"));
  u_nrrach =
    QStringList::split (";", settings.readEntry ("przelewy/u_nrrach"));
  u_okres = QStringList::split (";", settings.readEntry ("przelewy/u_okres"));
  u_symbol =
    QStringList::split (";", settings.readEntry ("przelewy/u_symbol"));
  u_zlec1 = QStringList::split (";", settings.readEntry ("przelewy/u_zlec1"));
  u_zlec2 = QStringList::split (";", settings.readEntry ("przelewy/u_zlec2"));

  pages = settings.readEntry ("przelewy/us_strony").toInt ();
  if (settings.readEntry ("przelewy/us_widok").compare ("poziomy") == 0)
    poziom = true;
  else
    poziom = false;

  if (settings.readEntry ("przelewy/us_wbud").compare ("true") == 0)
    own = false;
  else
    own = true;

}


void
pUS::saveXML ()
{

  QDomDocument doc ("przelewy");
  QDomElement root;
  QDomElement nadawca;		// urzad    
  QDomElement odbiorca;		// firma;    
  QString fileName;
  fileName = QDate::currentDate ().toString ("dd-MM-yyyy");

  qDebug (fileName);

  int pNumber = 0;
  QFile file (progDir2 + "/h" + fileName + "_" + QString::number (pNumber) +
	      ".xml");
  pNumber += 1;

  while (file.exists ())
    {
      file.setName (progDir2 + "/h" + fileName + "_" +
		    QString::number (pNumber) + ".xml");
      pNumber += 1;
    }

  if (!file.open (IO_ReadOnly))
    {
      root = doc.createElement ("przelew");
      root.setAttribute ("typ", "US" + comboBox1->currentText ());
      root.setAttribute ("typU", cbNazwa->currentText ());
      root.setAttribute ("date",
			 QDate::currentDate ().toString ("dd-MM-yyyy"));
      root.setAttribute ("kwota", kwotaEdit->text ());
//               root.setAttribute("title", lineEdit17->text());


      doc.appendChild (root);

      qDebug ("can not open ");
      nadawca = doc.createElement ("nadawca");
      nadawca.setAttribute ("name", nameEdit->text ());
      nadawca.setAttribute ("place", placeEdit->text ());
      nadawca.setAttribute ("code", codeEdit->text ());
      nadawca.setAttribute ("address", addressEdit->text ());
      nadawca.setAttribute ("account", accountEdit->text ());
      nadawca.setAttribute ("nip", nipEdit->text ());	// nazwa odb1.
      // aaaaaaaaa
      switch (secIdType->currentItem ())
	{
	case 0:
	  nadawca.setAttribute ("drugiIdT", "N");
	  break;
	case 1:
	  nadawca.setAttribute ("drugiIdT", "R");
	  break;
	case 2:
	  nadawca.setAttribute ("drugiIdT", "P");
	  break;
	case 3:
	  nadawca.setAttribute ("drugiIdT", "1");
	  break;
	case 4:
	  nadawca.setAttribute ("drugiIdT", "2");
	  break;
	}
      nadawca.setAttribute ("nrdek", nrdek->text ());
      nadawca.setAttribute ("dek", dek->text ());
      nadawca.setAttribute ("nrdec", nrdec->text ());


      root.appendChild (nadawca);

      odbiorca = doc.createElement ("odbiorca");
      odbiorca.setAttribute ("account", accountEdit2->text ());
      odbiorca.setAttribute ("place", placeEdit2->text ());
      odbiorca.setAttribute ("address", addressEdit2->text ());
      odbiorca.setAttribute ("code", codeEdit2->text ());
      odbiorca.setAttribute ("name", cbNazwa->currentText ());
      root.appendChild (odbiorca);

    }



  QString xml = doc.toString ();
  file.close ();
  file.open (IO_WriteOnly);
  QTextStream ts (&file);
  ts << xml;
  file.close ();

}

QPixmap
pUS::getPrzelew ()
{

  readSettings ();
  QPixmap pix;
  QPrinter printer;
  printer.setFullPage (TRUE);
  // if (printer.setup(this)) {

  QPainter a (&printer);
  if (!a.device ())
    return NULL;
  QPaintDeviceMetrics metrics1 (a.device ());
  int dpix1 = metrics1.logicalDpiX ();
  int dpiy1 = metrics1.logicalDpiY ();
  const int margin1 = 0;	// pt
  QRect
    body1 (margin1 * dpix1 / 72, margin1 * dpiy1 / 72,
	   metrics1.width () - margin1 * dpix1 / 72 * 2,
	   metrics1.height () - margin1 * dpiy1 / 72 * 2);
  pix.resize (body1.width (), body1.height ());
  //    = new QPixmap
//}

  QPainter p (&pix);
  if (!p.device ())
    return NULL;
  QPaintDeviceMetrics metrics (p.device ());
  int dpix = metrics.logicalDpiX ();
  int dpiy = metrics.logicalDpiY ();
  const int margin = 0;		// pt
  QRect
    body (margin * dpix / 72, margin * dpiy / 72,
	  metrics.width () - margin * dpix / 72 * 2,
	  metrics.height () - margin * dpiy / 72 * 2);
  QRect view (body);


  if (!own)
    {
      QDir abs (qApp->argv ()[0]);
      QString graphDir;
      if (QString (qApp->argv ()[0]).left (2) == "./")
	graphDir = abs.absPath ();
      else
	graphDir = "/usr/bin/eprzelewy";


      graphDir = graphDir.replace ("bin/eprzelewy", "share/eprzelewy");
      QImage *img = new QImage (graphDir + "/druki/us.png");
      p.drawImage (view, *img);
    }
  else
    {
      p.setBrush (QBrush (white, Qt::SolidPattern));
      p.setPen (Qt::white);
      p.drawRect (view);
      p.setPen (Qt::black);
    }


  QFont serifFont ("Arial", 12, 75);
  QFont sansFont ("Helvetica [Cronyx]", 12);
  p.setFont (font);

  if (comboBox1->currentItem () == 0)
    {
      // przelew 1
      if (poziom)
	p.rotate (-90);
      int i, j;
      for (i = 1; i <= pages; ++i)
	{
	  j = i - 1;
	  p.drawText (getXSett (u_nrrach[j]), getYSett (u_nrrach[j]),
		      rozstrzel (accountEdit2->text ()));
	  p.drawText (getXSett (uPx[j]), getYSett (uPx[j]), "X");
	  p.drawText (getXSett (u_nazwa1[j]), getYSett (u_nazwa1[j]),
		      cbNazwa->currentText ());
	  p.drawText (getXSett (u_nazwa2[j]), getYSett (u_nazwa2[j]),
		      codeEdit2->text () + " " + placeEdit2->text () + ", " +
		      addressEdit2->text ());
	  p.drawText (getXSett (u_kwota[j]), getYSett (u_kwota[j]),
		      kwotaEdit->text ());
	  p.drawText (getXSett (u_ksw[j]), getYSett (u_ksw[j]),
		      rozstrzel (accountEdit->text ()));
	  p.drawText (getXSett (u_zlec1[j]), getYSett (u_zlec1[j]),
		      nameEdit->text ());
	  p.drawText (getXSett (u_zlec2[j]), getYSett (u_zlec2[j]),
		      codeEdit->text () + " " + placeEdit->text () + ", " +
		      addressEdit->text ());
	  p.drawText (getXSett (u_nip[j]), getYSett (u_nip[j]),
		      nipEdit->text ());
	  /*
	     nusp, regon, pesel, DO, pszport
	     n, r p , 1, 2,
	   */
	  switch (secIdType->currentItem ())
	    {
	    case 0:
	      p.drawText (getXSett (u_id[j]), getYSett (u_id[j]), "N");
	      break;
	    case 1:
	      p.drawText (getXSett (u_id[j]), getYSett (u_id[j]), "R");
	      break;
	    case 2:
	      p.drawText (getXSett (u_id[j]), getYSett (u_id[j]), "P");
	      break;
	    case 3:
	      p.drawText (getXSett (u_id[j]), getYSett (u_id[j]), "1");
	      break;
	    case 4:
	      p.drawText (getXSett (u_id[j]), getYSett (u_id[j]), "2");
	      break;
	    }
//  secIdType->currentText()); // nazwa odb1.
	  /*
	     u_zlec1=160,378;160,808;
	     u_zlec2=360,378;360,808;
	   */


	  p.drawText (getXSett (u_okres[j]), getYSett (u_okres[j]),
		      nrdek->text ());
	  p.drawText (getXSett (u_symbol[j]), getYSett (u_symbol[j]),
		      dek->text ());
	  p.drawText (getXSett (u_idzob[j]), getYSett (u_idzob[j]),
		      nrdec->text ());

	}
    }

  if (comboBox1->currentItem () == 1)
    {
      makeWplata ();

      // przelew 1
      if (poziom)
	p.rotate (-90);
      int i, j;
      for (i = 1; i <= pages; ++i)
	{
	  j = i - 1;
	  p.drawText (getXSett (u_nrrach[j]), getYSett (u_nrrach[j]),
		      rozstrzel (accountEdit2->text ()));
	  p.drawText (getXSett (uWx[j]), getYSett (uWx[j]), "X");
	  p.drawText (getXSett (u_zlec1[j]), getYSett (u_zlec1[j]),
		      cbNazwa->currentText ());
	  p.drawText (getXSett (u_zlec2[j]), getYSett (u_zlec2[j]),
		      codeEdit2->text () + placeEdit2->text () + ", " +
		      addressEdit2->text ());
	  p.drawText (getXSett (u_kwota[j]), getYSett (u_kwota[j]),
		      kwotaEdit->text ());
	  p.drawText (getXSett (u_ksw[j]), getYSett (u_ksw[j]),
		      slownieLbl->text ());
	  p.drawText (getXSett (u_nazwa1[j]), getYSett (u_nazwa1[j]),
		      nameEdit->text ());
	  p.drawText (getXSett (u_nazwa2[j]), getYSett (u_nazwa2[j]),
		      codeEdit->text () + placeEdit->text () + ", " +
		      addressEdit->text ());
	  p.drawText (getXSett (u_nip[j]), getYSett (u_nip[j]),
		      nipEdit->text ());
	  /*
	     nusp, regon, pesel, DO, pszport
	     n, r p , 1, 2,
	   */
	  switch (secIdType->currentItem ())
	    {
	    case 0:
	      p.drawText (getXSett (u_id[j]), getYSett (u_id[j]), "N");
	      break;
	    case 1:
	      p.drawText (getXSett (u_id[j]), getYSett (u_id[j]), "R");
	      break;
	    case 2:
	      p.drawText (getXSett (u_id[j]), getYSett (u_id[j]), "P");
	      break;
	    case 3:
	      p.drawText (getXSett (u_id[j]), getYSett (u_id[j]), "1");
	      break;
	    case 4:
	      p.drawText (getXSett (u_id[j]), getYSett (u_id[j]), "2");
	      break;
	    }
//  secIdType->currentText()); // nazwa odb1.
	  /*
	     u_zlec1=160,378;160,808;
	     u_zlec2=360,378;360,808;
	   */


	  p.drawText (getXSett (u_okres[j]), getYSett (u_okres[j]),
		      nrdek->text ());
	  p.drawText (getXSett (u_symbol[j]), getYSett (u_symbol[j]),
		      dek->text ());
	  p.drawText (getXSett (u_idzob[j]), getYSett (u_idzob[j]),
		      nrdec->text ());

	}
    }

  p.translate (0, -body.height ());

  /* 
     QPixmap *px = new QPixmap();
     QPainter p2(px);
     p2.drawRect(100, 200, 30, 40);
     p2.drawText(100, 100, 200, 200, Qt::AlignHorizontal_Mask, "Hello world");
     p.drawPixmap(view, *px);
   */

  // view.moveBy(0, body.height());
  // p.translate(0 , -body.height());
  // printer.newPage();
  /*
     do {
     richText.draw(&p, body.left(), body.top(), view, colorGroup());
     view.moveBy(0, body.height());
     p.translate(0 , -body.height());
     p.setFont(font);
     p.drawText(view.right() - p.fontMetrics().width(QString::number(page)),
     view.bottom() + p.fontMetrics().ascent() + 5,
     QString::number(page));
     if (view.top()  >= richText.height())
     break;
     printer.newPage();
     page++;
     } while (TRUE);
   */
  //}
  p.end ();
  pix.save ("/tmp/przelew.png", "PNG");
  return pix;
}

void
pUS::print_dlg ()
{
  QPrinter printer;
  printer.setFullPage (TRUE);
  if (printer.setup (this))
    {
      QPainter p (&printer);
      if (!p.device ())
	return;
      QPaintDeviceMetrics metrics (p.device ());
      int dpix = metrics.logicalDpiX ();
      int dpiy = metrics.logicalDpiY ();
      const int margin = 0;	// pt
      QRect body (margin * dpix / 72, margin * dpiy / 72,
		  metrics.width () - margin * dpix / 72 * 2,
		  metrics.height () - margin * dpiy / 72 * 2);
      /*
         QFont font(textEdit1->font());
         QSimpleRichText richText(textEdit1->text(), font, 
         textEdit1->context(),
         textEdit1->styleSheet(),
         textEdit1->mimeSourceFactory(),
         body.height());
         richText.setWidth(&p, body.width());
       */
      QRect view (body);
      p.drawPixmap (view, getPrzelew ());

      // int page = 1;
      /*
         QImage *img = new QImage("druki/standard.png");
         p.drawImage(view, *img); 
       */
/* 
 QFont serifFont( "Arial", 12, 75 );
 QFont sansFont( "Helvetica [Cronyx]", 12 ); 
 p.setFont(serifFont);

 if (comboBox1->currentItem() == 0) {
 // przelew 1
 p.rotate(-90);
 p.drawText(-535, 70, nameEdit2->text()); // nazwa odb1.
 p.drawText(-535, 98, codeEdit2->text()  + placeEdit2->text() + ", " + addressEdit2->text()); // adres miasto odb1.
 p.drawText(-535, 133, rozstrzel(accountEdit2->text())); 
 p.drawText(-335, 163, "PLN");
 p.drawText(-275, 163,  kwotaEdit->text());
 p.drawText(-535, 192, rozstrzel(accountEdit->text())); // nazwa odb1.
 p.drawText(-535, 222, nameEdit->text()); // nazwa odb1.
 p.drawText(-535, 252, codeEdit->text()  + placeEdit->text() + ", " + addressEdit->text()); // nazwa odb1.
 p.drawText(-535, 282, lineEdit17->text()); // nazwa odb1.
 
// przelew2 
 p.drawText(-1030, 70, nameEdit2->text()); // nazwa odb1.
 p.drawText(-1030, 98, codeEdit2->text()  + placeEdit2->text() + ", " + addressEdit2->text()); // adres miasto odb1.
 p.drawText(-1030, 133, rozstrzel(accountEdit2->text())); 
 p.drawText(-830, 163, "PLN");
 p.drawText(-770, 163,  kwotaEdit->text());
 p.drawText(-1030, 192, rozstrzel(accountEdit->text())); // nazwa odb1.
 p.drawText(-1030, 222, nameEdit->text()); // nazwa odb1.
 p.drawText(-1030, 252, codeEdit->text()  + placeEdit->text() + ", " + addressEdit->text()); // nazwa odb1.
 p.drawText(-1030, 282, lineEdit17->text()); // nazwa odb1.
 
// przelew3
 p.drawText(-535, 423, nameEdit2->text()); // nazwa odb1.
 p.drawText(-535, 451, codeEdit2->text()  + placeEdit2->text() + ", " + addressEdit2->text()); // adres miasto odb1.
 p.drawText(-535, 488, rozstrzel(accountEdit2->text())); 
 p.drawText(-335, 516, "PLN");
 p.drawText(-275, 516,  kwotaEdit->text());
 p.drawText(-535, 547, rozstrzel(accountEdit->text())); // nazwa odb1.
 p.drawText(-535, 575, nameEdit->text()); // nazwa odb1.
 p.drawText(-535, 605, codeEdit->text()  + placeEdit->text() + ", " + addressEdit->text()); // nazwa odb1.
 p.drawText(-535, 635, lineEdit17->text()); // nazwa odb1.
 
 
 // przelew4
 p.drawText(-1030, 423, nameEdit2->text()); // nazwa odb1.
 p.drawText(-1030, 451, codeEdit2->text()  + placeEdit2->text() + ", " + addressEdit2->text()); // adres miasto odb1.
 p.drawText(-1030, 488, rozstrzel(accountEdit2->text())); 
 p.drawText(-830, 516, "PLN");
 p.drawText(-770, 516,  kwotaEdit->text());
 p.drawText(-1030, 547, rozstrzel(accountEdit->text())); // nazwa odb1.
 p.drawText(-1030, 575, nameEdit->text()); // nazwa odb1.
 p.drawText(-1030, 605, codeEdit->text()  + placeEdit->text() + ", " + addressEdit->text()); // nazwa odb1.
 p.drawText(-1030, 635, lineEdit17->text()); // nazwa odb1.
}
 
  if (comboBox1->currentItem() == 1) {
      makeWplata();
      // przelew 1
 p.rotate(-90);
 p.drawText(-535, 70, nameEdit2->text()); // nazwa odb1.
 p.drawText(-535, 98, codeEdit2->text()  + placeEdit2->text() + ", " + addressEdit2->text()); // adres miasto odb1.
 p.drawText(-535, 133, rozstrzel(accountEdit->text())); 
 p.drawText(-335, 163, "PLN");
 p.drawText(-275, 163,  kwotaEdit->text());
 
 p.drawText(-535, 192, slownieLbl->text()); // nazwa odb1.
 p.drawText(-535, 222, nameEdit->text()); // nazwa odb1.
 p.drawText(-535, 252, codeEdit->text()  + placeEdit->text() + ", " + addressEdit->text()); // nazwa odb1.
 p.drawText(-535, 282, lineEdit17->text()); // nazwa odb1.
 
// przelew2 
 p.drawText(-1030, 70, nameEdit2->text()); // nazwa odb1.
 p.drawText(-1030, 98, codeEdit2->text()  + placeEdit2->text() + ", " + addressEdit2->text()); // adres miasto odb1.
 p.drawText(-1030, 133, rozstrzel(accountEdit->text())); 
 p.drawText(-830, 163, "PLN");
 p.drawText(-770, 163,  kwotaEdit->text());
 p.drawText(-1030, 192, slownieLbl->text()); // nazwa odb1.
 p.drawText(-1030, 222, nameEdit->text()); // nazwa odb1.
 p.drawText(-1030, 252, codeEdit->text()  + placeEdit->text() + ", " + addressEdit->text()); // nazwa odb1.
 p.drawText(-1030, 282, lineEdit17->text()); // nazwa odb1.
 
// przelew3
 p.drawText(-535, 423, nameEdit2->text()); // nazwa odb1.
 p.drawText(-535, 451, codeEdit2->text()  + placeEdit2->text() + ", " + addressEdit2->text()); // adres miasto odb1.
 p.drawText(-535, 488, rozstrzel(accountEdit->text())); 
 p.drawText(-335, 516, "PLN");
 p.drawText(-275, 516,  kwotaEdit->text());
 p.drawText(-535, 547, slownieLbl->text()); // nazwa odb1.
 p.drawText(-535, 575, nameEdit->text()); // nazwa odb1.
 p.drawText(-535, 605, codeEdit->text()  + placeEdit->text() + ", " + addressEdit->text()); // nazwa odb1.
 p.drawText(-535, 635, lineEdit17->text()); // nazwa odb1.
 
 
 // przelew4
 p.drawText(-1030, 423, nameEdit2->text()); // nazwa odb1.
 p.drawText(-1030, 451, codeEdit2->text()  + placeEdit2->text() + ", " + addressEdit2->text()); // adres miasto odb1.
 p.drawText(-1030, 488, rozstrzel(accountEdit->text())); 
 p.drawText(-830, 516, "PLN");
 p.drawText(-770, 516,  kwotaEdit->text());
 p.drawText(-1030, 547, slownieLbl->text()); // nazwa odb1.
 p.drawText(-1030, 575, nameEdit->text()); // nazwa odb1.
 p.drawText(-1030, 605, codeEdit->text()  + placeEdit->text() + ", " + addressEdit->text()); // nazwa odb1.
 p.drawText(-1030, 635, lineEdit17->text()); // nazwa odb1.
  }
  
 p.translate(0 , -body.height());
*/
      /* 
         QPixmap *px = new QPixmap();
         QPainter p2(px);
         p2.drawRect(100, 200, 30, 40);
         p2.drawText(100, 100, 200, 200, Qt::AlignHorizontal_Mask, "Hello world");
         p.drawPixmap(view, *px);
       */

      // view.moveBy(0, body.height());
      // p.translate(0 , -body.height());
      // printer.newPage();
      /*
         do {
         richText.draw(&p, body.left(), body.top(), view, colorGroup());
         view.moveBy(0, body.height());
         p.translate(0 , -body.height());
         p.setFont(font);
         p.drawText(view.right() - p.fontMetrics().width(QString::number(page)),
         view.bottom() + p.fontMetrics().ascent() + 5,
         QString::number(page));
         if (view.top()  >= richText.height())
         break;
         printer.newPage();
         page++;
         } while (TRUE);
       */

    }
  saveXML ();
  accept ();
}

void
pUS::ppriview ()
{
  qDebug ("%s %s:%d", __FUNCTION__, __FILE__, __LINE__);
  getPrzelew ();
  preview *ppp = new preview ();
  ppp->exec ();
// saveXML();
// close();
}

void
pUS::usNameChange (const QString & text)
{
  QDomDocument doc ("kontrahenci");
  QDomElement root;
  QDomElement urzad;
  QDomElement firma;

  QFile file (progDir2 + "/kontrah.xml");
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
      QString textXml;
      for (QDomNode n = urzad.firstChild (); !n.isNull ();
	   n = n.nextSibling ())
	{
	  textXml = n.toElement ().attribute ("name");
// qDebug(textXml + " " + text);
// qDebug( QString::number(textXml.compare(text)) );
	  if (textXml.compare (text) == 0)
	    {
	      accountEdit2->setText (n.toElement ().attribute ("account"));
	      placeEdit2->setText (n.toElement ().attribute ("place"));
	      codeEdit2->setText (n.toElement ().attribute ("code"));
	      addressEdit2->setText (n.toElement ().attribute ("address"));
	    }
	}
    }

}
