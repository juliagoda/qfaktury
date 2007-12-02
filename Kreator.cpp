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
#include "Kreator.moc"
#include <qsettings.h>
#include <qtextcodec.h>
#include <qdom.h>
#include <qdir.h>
#include <qfile.h>
#include <qprinter.h>
#include <qpainter.h>
#include <qpaintdevicemetrics.h>
// #include <qsimplerichtext.h>
#include <qimage.h>

#include <qpicture.h>

#include <qdatetime.h>
#include <qfont.h>

#include <qapplication.h>


QStringList pPx;
QStringList pWx;

void Kreator::init ()
{
  QTextCodec::setCodecForCStrings (QTextCodec::codecForName ("ISO8859-2"));
  QTextCodec::setCodecForTr (QTextCodec::codecForName ("ISO8859-2"));

  setFinishEnabled (page (3), TRUE);
  prevPage = 0;
  QDir abs (qApp->argv ()[0]);
  QString graphDir;
  if (QString (qApp->argv ()[0]).left (2) == "./")
    graphDir = abs.absPath ();
  else
    graphDir = "/usr/bin/eprzelewy";

  //  QString graphDir = abs.absPath();
  graphDir = graphDir.replace ("bin/eprzelewy", "share/eprzelewy/icons");
  pixmapLabel1->setPixmap (QPixmap (graphDir + "/k2.png"));
  pixmapLabel1_2->setPixmap (QPixmap (graphDir + "/k2.png"));
  pixmapLabel1_2_2->setPixmap (QPixmap (graphDir + "/k2.png"));
  pixmapLabel1_2_3->setPixmap (QPixmap (graphDir + "/k2.png"));
}

void Kreator::fillEdits ()
{
  QSettings settings;
  nameEdit->setText (settings.readEntry ("przelewy/user/nazwa"));
  placeEdit->setText (settings.readEntry ("przelewy/user/miejscowosc"));
  codeEdit->setText (settings.readEntry ("przelewy/user/kod"));
  addressEdit->setText (settings.readEntry ("przelewy/user/adres"));
  accountEdit->setText (settings.readEntry ("przelewy/user/konto"));
}

void Kreator::kwotaKeyDown ()
{
  if (radioButton3->isChecked ())
    slownie ();
}

void Kreator::slownie ()
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


void Kreator::hideSlownie (bool ok)
{
  if (!ok)
    {
      textLabel4_3->hide ();
      slownieLbl->hide ();
    }
  else
    {
      textLabel4_3->show ();
      slownieLbl->show ();
    }
}

void Kreator::getFirmList ()
{
  qDebug (__FUNCTION__);
  QString progDir2 = QDir::homeDirPath () + "/przelewy";

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
	  text = n.toElement ().attribute ("name");
	  listBox1->insertItem (text, -1);
	}
    }

}

void Kreator::getOdbData ()
{

  qDebug (__FUNCTION__);
  QString progDir2 = QDir::homeDirPath () + "/przelewy";

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
      QString text = listBox1->currentText ();
      QString textXml;
      for (QDomNode n = firma.firstChild (); !n.isNull ();
	   n = n.nextSibling ())
	{
	  textXml = n.toElement ().attribute ("name");
// qDebug(textXml + " " + text);
// qDebug( QString::number(textXml.compare(text)) );
	  if (textXml.compare (text) == 0)
	    {
	      odbNazwa = n.toElement ().attribute ("name");
	      odbAccount = n.toElement ().attribute ("account");
	      odbPlace = n.toElement ().attribute ("place");
	      odbCode = n.toElement ().attribute ("code");
	      odbAddress = n.toElement ().attribute ("address");

	    }
	}
    }
}

void Kreator::makeWplata ()
{
  qDebug (__FUNCTION__);
  slownie ();
  /*
     odbNazwa = nameEdit->text ();
     odbCode = codeEdit->text ();
     odbPlace = placeEdit->text ();
     odbAddress = addressEdit->text ();
     odbAccount = accountEdit->text ();
   */
}


void Kreator::nextFunc ()
{
  if ((radioButton3->isChecked ()) && (indexOf (currentPage ()) == 2)
      && (prevPage == 1))
    {
      // showPage (page (3));
      hideSlownie (TRUE);
    }
  else
    {
      hideSlownie (FALSE);
    }

  if ((radioButton3->isChecked ()) && (indexOf (currentPage ()) == 2)
      && (prevPage == 3))
    {
      // showPage (page (1));
    }

  if (indexOf (currentPage ()) == 1)
    fillEdits ();
  if (indexOf (currentPage ()) == 2)
    {
      listBox1->clear ();
      getFirmList ();
    }

  prevPage = indexOf (currentPage ());
}


QString Kreator::rozstrzel (QString in)
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

int Kreator::getXSett (QString in)
{
  int x = in.find (',');
  // int y = in.length();
  // qDebug( in.left(x) );
  // qDebug( in.right(y - (x + 1)) );
  return in.left (x).toInt ();
}

int Kreator::getYSett (QString in)
{
  int x = in.find (',');
  int y = in.length ();
  // qDebug( in.left(x) );
  // qDebug( in.right(y - (x + 1)) );
  return in.right (y - (x + 1)).toInt ();
}


void Kreator::readSettings ()
{
  QSettings settings;
  font.fromString (settings.readEntry ("przelewy/czcionka"));
  rozSp = settings.readEntry ("przelewy/przerwy").toInt ();

  pOdb1 =
    QStringList::split (";", settings.readEntry ("przelewy/p_odbiorca1"));
  pOdb2 =
    QStringList::split (";", settings.readEntry ("przelewy/p_odbiorca2"));
  pWal = QStringList::split (";", settings.readEntry ("przelewy/p_waluta"));
  pNrrach =
    QStringList::split (";", settings.readEntry ("przelewy/p_nrrach"));
  pKwota = QStringList::split (";", settings.readEntry ("przelewy/p_kwota"));
  pKsw = QStringList::split (";", settings.readEntry ("przelewy/p_ksw"));
  pWx = QStringList::split (";", settings.readEntry ("przelewy/p_wx"));
  pPx = QStringList::split (";", settings.readEntry ("przelewy/p_px"));
  pZlec1 = QStringList::split (";", settings.readEntry ("przelewy/p_zlec1"));
  pZlec2 = QStringList::split (";", settings.readEntry ("przelewy/p_zlec2"));
  pTyt1 = QStringList::split (";", settings.readEntry ("przelewy/p_tyt1"));
  pTyt2 = QStringList::split (";", settings.readEntry ("przelewy/p_tyt2"));
  pages = settings.readEntry ("przelewy/przelew_strony").toInt ();
  if (settings.readEntry ("przelewy/przelew_widok").compare ("poziomy") == 0)
    poziom = true;
  else
    poziom = false;
  if (settings.readEntry ("przelewy/przelew_wbud").compare ("true") == 0)
    own = false;
  else
    own = true;

}

void Kreator::saveXML ()
{

  QDomDocument doc ("przelewy");
  QDomElement root;
  QDomElement nadawca;		// urzad    
  QDomElement odbiorca;		// firma;    
  QString fileName;
  fileName = QDate::currentDate ().toString ("dd-MM-yyyy");
  QString progDir2 = QDir::homeDirPath () + "/przelewy";
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

  if (!file.open (QIODevice::ReadOnly))
    {
      root = doc.createElement ("przelew");
      if (radioButton2->isChecked ())
	root.setAttribute ("typ", "Przelew");
      else
	root.setAttribute ("typ", "Wp³ata");

      root.setAttribute ("date",
			 QDate::currentDate ().toString ("dd-MM-yyyy"));
      root.setAttribute ("kwota", kwotaEdit->text ());
      root.setAttribute ("title", lineEdit17->text ());


      doc.appendChild (root);

      qDebug ("can not open ");
      nadawca = doc.createElement ("nadawca");
      nadawca.setAttribute ("name", nameEdit->text ());
      nadawca.setAttribute ("place", placeEdit->text ());
      nadawca.setAttribute ("code", codeEdit->text ());
      nadawca.setAttribute ("address", addressEdit->text ());
      nadawca.setAttribute ("account", accountEdit->text ());
      if (radioButton2->isChecked ())
	{
	  nadawca.setAttribute ("przelew", "x");
	  nadawca.setAttribute ("wplata", "0");
	}
      else
	{
	  nadawca.setAttribute ("wplata", "x");
	  nadawca.setAttribute ("przelew", "0");
	}

      root.appendChild (nadawca);

      odbiorca = doc.createElement ("odbiorca");
      odbiorca.setAttribute ("name", odbNazwa);
      odbiorca.setAttribute ("place", odbPlace);
      odbiorca.setAttribute ("code", odbCode);
      odbiorca.setAttribute ("address", odbAddress);
      odbiorca.setAttribute ("account", odbAccount);
      root.appendChild (odbiorca);

    }



  QString xml = doc.toString ();
  file.close ();
  file.open (QIODevice::WriteOnly);
  QTextStream ts (&file);
  ts << xml;
  file.close ();

}


QPixmap Kreator::getPrzelew ()
{
  qDebug (__FUNCTION__);
  readSettings ();
  QPixmap pix;
  QPrinter printer;
  printer.setFullPage (TRUE);
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
      QImage *img = new QImage (graphDir + "/druki/standard.png");
      p.drawImage (view, *img);
    }
  else
    {
      p.setBrush (QBrush (white, Qt::SolidPattern));
      p.setPen (Qt::white);
      p.drawRect (view);
      p.setPen (Qt::black);
    }

  p.setBrush (QBrush (white, Qt::SolidPattern));

  QFont serifFont ("Arial", 12, 75);
  QFont sansFont ("Helvetica [Cronyx]", 12);
  p.setFont (font);

  if (radioButton2->isChecked ())
    {
      getOdbData ();
      // przelew 1
      if (poziom)
	p.rotate (-90);
      int i, j;
      for (i = 1; i <= pages; ++i)
	{
	  j = i - 1;
	  p.drawText (getXSett (pOdb1[j]), getYSett (pOdb1[j]), odbNazwa);	// nazwa odb1.
	  p.drawText (getXSett (pOdb2[j]), getYSett (pOdb2[j]), odbCode + " " + odbPlace + ", " + odbAddress);	// adres miasto odb1.
	  p.drawText (getXSett (pNrrach[j]), getYSett (pNrrach[j]),
		      rozstrzel (odbAccount));

	  p.drawText (getXSett (pPx[j]), getYSett (pPx[j]), "X");

	  p.drawText (getXSett (pWal[j]), getYSett (pWal[j]), "PLN");
	  p.drawText (getXSett (pKwota[j]), getYSett (pKwota[j]),
		      kwotaEdit->text ());
	  p.drawText (getXSett (pKsw[j]), getYSett (pKsw[j]), rozstrzel (accountEdit->text ()));	// nazwa odb1.
	  p.drawText (getXSett (pZlec1[j]), getYSett (pZlec1[j]), nameEdit->text ());	// nazwa odb1.
	  p.drawText (getXSett (pZlec2[j]), getYSett (pZlec2[j]), codeEdit->text () + placeEdit->text () + ", " + addressEdit->text ());	// nazwa odb1.
	  p.drawText (getXSett (pTyt1[j]), getYSett (pTyt1[j]), lineEdit17->text ());	// nazwa odb1.
	}
    }

  if (radioButton3->isChecked ())
    {
//      makeWplata ();
      getOdbData ();
      // przelew 1
      if (poziom)
	p.rotate (-90);
      int i, j;
      for (i = 1; i <= pages; ++i)
	{
	  j = i - 1;
	  p.drawText (getXSett (pOdb1[j]), getYSett (pOdb1[j]), odbNazwa);	// nazwa odb1.
	  p.drawText (getXSett (pOdb2[j]), getYSett (pOdb2[j]), odbCode + " " + odbPlace + ", " + odbAddress);	// adres miasto odb1.
	  p.drawText (getXSett (pNrrach[j]), getYSett (pNrrach[j]),
		      rozstrzel (odbAccount));
	  p.drawText (getXSett (pWal[j]), getYSett (pWal[j]), "PLN");
	  p.drawText (getXSett (pWx[j]), getYSett (pWx[j]), "X");
	  p.drawText (getXSett (pKwota[j]), getYSett (pKwota[j]),
		      kwotaEdit->text ());
	  p.drawText (getXSett (pKsw[j]), getYSett (pKsw[j]), slownieLbl->text ());	// nazwa odb1.
	  p.drawText (getXSett (pZlec1[j]), getYSett (pZlec1[j]), nameEdit->text ());	// nazwa odb1.
	  p.drawText (getXSett (pZlec2[j]), getYSett (pZlec2[j]), codeEdit->text () + placeEdit->text () + ", " + addressEdit->text ());	// nazwa odb1.
	  p.drawText (getXSett (pTyt1[j]), getYSett (pTyt1[j]), lineEdit17->text ());	// nazwa odb1.
	}
    }

  p.translate (0, -body.height ());
  p.end ();
  pix.save ("/tmp/przelew.png", "PNG");
  return pix;
}

void Kreator::print ()
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
      QRect view (body);
      p.drawPixmap (view, getPrzelew ());
      saveXML ();
      accept ();
    }
}
Kreator::Kreator(QWidget *parent): QDialog(parent) {
    setupUi(this);
    init();
}
