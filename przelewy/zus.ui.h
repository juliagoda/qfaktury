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

QStringList zWx;
QStringList zPx;
// QString fileName;

void
pZUS::readData ()
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
  if (root.attribute ("typ", "") == "ZUSPrzelew")
    comboBox1->setCurrentText ("Przelew");
  if (root.attribute ("typ", "").left (5) == "ZUSWp")
    comboBox1->setCurrentText ("Wp³ata");

  zusType->setCurrentText (root.attribute ("typZ", ""));
  kwotaEdit->setText (root.attribute ("kwota", ""));
//    lineEdit17->setText( root.attribute("title", ""));

  nadawca = root.firstChild ().toElement ();
  odbiorca = root.lastChild ().toElement ();
  // nadawca.attribute("name", "NULL"));

//  nameEdit2->setText( nadawca.attribute("name", "") );
//    codeEdit2->setText( nadawca.attribute("code", "")  );
//    placeEdit2->setText( nadawca.attribute("place", "") );
//    addressEdit2->setText( nadawca.attribute("address", "") );
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

  regonEdit->setText (nadawca.attribute ("drugiId"));

  typwp->setCurrentText (nadawca.attribute ("typWp"));


  nrdek->setText (nadawca.attribute ("nrdek"));
  dek->setText (nadawca.attribute ("dek"));
  nrdec->setText (nadawca.attribute ("nrdec"));

  qDebug ("fileName " + fileName);
}


void
pZUS::init ()
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
  regonEdit->setText (settings.readEntry ("przelewy/user/regon"));
  progDir2 = QDir::homeDirPath () + "/przelewy";
}

void
pZUS::slownie ()
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
pZUS::rozstrzel (QString in)
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
pZUS::kwotaKeyDown ()
{
  if (comboBox1->currentItem () == 1)
    slownie ();
}

void
pZUS::makeWplata ()
{
  slownie ();
//    nameEdit2->setText( nameEdit->text() );
//    codeEdit2->setText( codeEdit->text()  );
//    placeEdit2->setText( placeEdit->text() );
//    addressEdit2->setText( addressEdit->text() );
//    accountEdit2->setText( accountEdit->text()  );
}

int
pZUS::getXSett (QString in)
{
  int x = in.find (',');
  // int y = in.length();
  // qDebug( in.left(x) );
  // qDebug( in.right(y - (x + 1)) );
  return in.left (x).toInt ();
}

int
pZUS::getYSett (QString in)
{
  int x = in.find (',');
  int y = in.length ();
  // qDebug( in.left(x) );
  // qDebug( in.right(y - (x + 1)) );
  return in.right (y - (x + 1)).toInt ();
}

void
pZUS::readSettings ()
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

  z_dek = QStringList::split (";", settings.readEntry ("przelewy/z_dek"));
  zWx = QStringList::split (";", settings.readEntry ("przelewy/z_wx"));
  zPx = QStringList::split (";", settings.readEntry ("przelewy/z_px"));
  z_id = QStringList::split (";", settings.readEntry ("przelewy/z_id"));
  z_konto = QStringList::split (";", settings.readEntry ("przelewy/z_konto"));
  z_ksw = QStringList::split (";", settings.readEntry ("przelewy/z_ksw"));
  z_kwota = QStringList::split (";", settings.readEntry ("przelewy/z_kwota"));
  z_nazwa1 =
    QStringList::split (";", settings.readEntry ("przelewy/z_nazwa1"));
  z_nazwa2 =
    QStringList::split (";", settings.readEntry ("przelewy/z_nazwa2"));
  z_nip = QStringList::split (";", settings.readEntry ("przelewy/z_nip"));
  z_nrdec = QStringList::split (";", settings.readEntry ("przelewy/z_nrdec"));
  z_nrdek = QStringList::split (";", settings.readEntry ("przelewy/z_nrdek"));
  z_typid = QStringList::split (";", settings.readEntry ("przelewy/z_typid"));
  z_typwp = QStringList::split (";", settings.readEntry ("przelewy/z_typwp"));

  pages = settings.readEntry ("przelewy/zus_strony").toInt ();
  if (settings.readEntry ("przelewy/zus_widok").compare ("poziomy") == 0)
    poziom = true;
  else
    poziom = false;

  if (settings.readEntry ("przelewy/zus_wbud").compare ("true") == 0)
    own = false;
  else
    own = true;

  /*
     // loop for zus
     z1->setText(  settings.readEntry( "przelewy/z_konto") );
     z2->setText(   settings.readEntry( "przelewy/z_kwota") );
     z3->setText(   settings.readEntry( "przelewy/z_ksw") );
     z4->setText(   settings.readEntry( "przelewy/z_nazwa1") );
     z5->setText(   settings.readEntry( "przelewy/z_nazwa2") );
     z6->setText(   settings.readEntry( "przelewy/z_nip") );
     z7->setText(   settings.readEntry( "przelewy/z_typid") );
     z8->setText(   settings.readEntry( "przelewy/z_id") );
     z9->setText(   settings.readEntry( "przelewy/z_typwp") );
     z10->setText(   settings.readEntry( "przelewy/z_nrdek") );
     z11->setText(   settings.readEntry( "przelewy/z_dek") );
     z12->setText(   settings.readEntry( "przelewy/z_nrdec") );

     // loop for us
     u1->setText( settings.readEntry( "przelewy/u_nazwa1") );
     u2->setText(  settings.readEntry( "przelewy/u_nazwa2") );
     u3->setText(  settings.readEntry( "przelewy/u_nrrach") );
     u4->setText(  settings.readEntry( "przelewy/u_kwota") );
     u5->setText(  settings.readEntry( "przelewy/u_ksw") );
     u6->setText(  settings.readEntry( "przelewy/u_zlec1") );
     u7->setText(  settings.readEntry( "przelewy/u_zlec2") );
     u8->setText(  settings.readEntry( "przelewy/u_nip") );
     u9->setText(  settings.readEntry( "przelewy/u_id") );
     u10->setText(  settings.readEntry( "przelewy/u_okres") );
     u11->setText(  settings.readEntry( "przelewy/u_symbol") );
     u12->setText(  settings.readEntry( "przelewy/u_idzob") ); 
   */
/* 
 settings.writeEntry( "user/kod", codeEdit->text() );
 settings.writeEntry( "user/adres", addressEdit->text() );
 settings.writeEntry( "user/konto", accountEdit->text() );
 */
/*
pDruki->setCurrentText( settings.readEntry( "przelewy/przelew_strony") );
pUklad->setCurrentText(  settings.readEntry( "przelewy/przelew_widok") );

zDruki->setCurrentText(  settings.readEntry( "przelewy/zus_strony") );
zUklad->setCurrentText(  settings.readEntry( "przelewy/zus_widok") );
 
uDruki->setCurrentText(  settings.readEntry( "przelewy/us_strony") );
uUklad->setCurrentText(  settings.readEntry( "przelewy/us_widok") );
  */
}


void
pZUS::saveXML ()
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
      root.setAttribute ("typ", "ZUS" + comboBox1->currentText ());
      root.setAttribute ("typZ", zusType->currentText ());
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

      // accountEdit2->text(); 
// kwotaEdit->text());
// slownieLbl->text()); 
// nameEdit->text(); // nazwa odb1.
// codeEdit->text()  + 
// placeEdit->text() + ", " + 
// addressEdit->text()); // nazwa odb1.
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
      nadawca.setAttribute ("drugiId", regonEdit->text ());
      nadawca.setAttribute ("typWp", typwp->currentText ());
      nadawca.setAttribute ("nrdek", nrdek->text ());
      nadawca.setAttribute ("dek", dek->text ());
      nadawca.setAttribute ("nrdec", nrdec->text ());


      root.appendChild (nadawca);

      odbiorca = doc.createElement ("odbiorca");
// odbiorca.setAttribute( "name",  nameEdit2->text() );
// odbiorca.setAttribute( "place",  placeEdit2->text() );
// odbiorca.setAttribute( "code",  codeEdit2->text() );
// odbiorca.setAttribute( "address",  addressEdit2->text() );
      odbiorca.setAttribute ("account", accountEdit2->text ());
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
pZUS::getPrzelew ()
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
  // int page = 1;

// !!!!!!!!!!!! testing testing testing testing
// p.setBrush(QBrush(white, Qt::SolidPattern));
// p.drawRect(view);
// !!!!!!!!!!!! testing testing testing testing


  if (!own)
    {
      QDir abs (qApp->argv ()[0]);
      QString graphDir;
      if (QString (qApp->argv ()[0]).left (2) == "./")
	graphDir = abs.absPath ();
      else
	graphDir = "/usr/bin/eprzelewy";

      graphDir = graphDir.replace ("bin/eprzelewy", "share/eprzelewy");
      QImage *img = new QImage (graphDir + "/druki/zus.png");
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
	  p.drawText (getXSett (z_konto[j]), getYSett (z_konto[j]),
		      rozstrzel (accountEdit2->text ()));
	  p.drawText (getXSett (zPx[j]), getYSett (zPx[j]), "X");
	  p.drawText (getXSett (z_kwota[j]), getYSett (z_kwota[j]),
		      kwotaEdit->text ());
	  p.drawText (getXSett (z_ksw[j]), getYSett (z_ksw[j]), rozstrzel (accountEdit->text ()));	// nazwa odb1.
	  p.drawText (getXSett (z_nazwa1[j]), getYSett (z_nazwa1[j]), nameEdit->text ());	// nazwa odb1.
	  p.drawText (getXSett (z_nazwa2[j]), getYSett (z_nazwa2[j]), codeEdit->text () + placeEdit->text () + ", " + addressEdit->text ());	// nazwa odb1.
	  p.drawText (getXSett (z_nip[j]), getYSett (z_nip[j]), nipEdit->text ());	// nazwa odb1.
	  /*
	     nusp, regon, pesel, DO, pszport
	     n, r p , 1, 2,
	   */
	  switch (secIdType->currentItem ())
	    {
	    case 0:
	      p.drawText (getXSett (z_typid[j]), getYSett (z_typid[j]), "N");
	      break;
	    case 1:
	      p.drawText (getXSett (z_typid[j]), getYSett (z_typid[j]), "R");
	      break;
	    case 2:
	      p.drawText (getXSett (z_typid[j]), getYSett (z_typid[j]), "P");
	      break;
	    case 3:
	      p.drawText (getXSett (z_typid[j]), getYSett (z_typid[j]), "1");
	      break;
	    case 4:
	      p.drawText (getXSett (z_typid[j]), getYSett (z_typid[j]), "2");
	      break;
	    }
//  secIdType->currentText()); // nazwa odb1.

	  p.drawText (getXSett (z_id[j]), getYSett (z_id[j]),
		      regonEdit->text ());
	  p.drawText (getXSett (z_typwp[j]), getYSett (z_typwp[j]),
		      typwp->currentText ().left (1));
	  p.drawText (getXSett (z_nrdek[j]), getYSett (z_nrdek[j]),
		      nrdek->text ());
	  p.drawText (getXSett (z_dek[j]), getYSett (z_dek[j]), dek->text ());
	  p.drawText (getXSett (z_nrdec[j]), getYSett (z_nrdec[j]),
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
	  p.drawText (getXSett (z_konto[j]), getYSett (z_konto[j]),
		      rozstrzel (accountEdit2->text ()));
	  p.drawText (getXSett (zWx[j]), getYSett (zWx[j]), "X");
	  p.drawText (getXSett (z_kwota[j]), getYSett (z_kwota[j]),
		      kwotaEdit->text ());
	  p.drawText (getXSett (z_ksw[j]), getYSett (z_ksw[j]),
		      slownieLbl->text ());
	  p.drawText (getXSett (z_nazwa1[j]), getYSett (z_nazwa1[j]), nameEdit->text ());	// nazwa odb1.
	  p.drawText (getXSett (z_nazwa2[j]), getYSett (z_nazwa2[j]), codeEdit->text () + placeEdit->text () + ", " + addressEdit->text ());	// nazwa odb1.
	  p.drawText (getXSett (z_nip[j]), getYSett (z_nip[j]), nipEdit->text ());	// nazwa odb1.
	  // aaaaaaaaa
	  switch (secIdType->currentItem ())
	    {
	    case 0:
	      p.drawText (getXSett (z_typid[j]), getYSett (z_typid[j]), "N");
	      break;
	    case 1:
	      p.drawText (getXSett (z_typid[j]), getYSett (z_typid[j]), "R");
	      break;
	    case 2:
	      p.drawText (getXSett (z_typid[j]), getYSett (z_typid[j]), "P");
	      break;
	    case 3:
	      p.drawText (getXSett (z_typid[j]), getYSett (z_typid[j]), "1");
	      break;
	    case 4:
	      p.drawText (getXSett (z_typid[j]), getYSett (z_typid[j]), "2");
	      break;
	    }
	  p.drawText (getXSett (z_id[j]), getYSett (z_id[j]),
		      regonEdit->text ());
	  p.drawText (getXSett (z_typwp[j]), getYSett (z_typwp[j]),
		      typwp->currentText ().left (1));
	  p.drawText (getXSett (z_nrdek[j]), getYSett (z_nrdek[j]),
		      nrdek->text ());
	  p.drawText (getXSett (z_dek[j]), getYSett (z_dek[j]), dek->text ());
	  p.drawText (getXSett (z_nrdec[j]), getYSett (z_nrdec[j]),
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
pZUS::print_dlg ()
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
pZUS::ppriview ()
{
  qDebug ("%s %s:%d", __FUNCTION__, __FILE__, __LINE__);
  getPrzelew ();
  preview *ppp = new preview ();
  ppp->exec ();
// saveXML();
// close();
}


void
pZUS::newFunction ()
{

}


void
pZUS::zusChanged (const QString & text)
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
	    accountEdit2->setText (n.toElement ().attribute ("account"));
	}
    }
}
