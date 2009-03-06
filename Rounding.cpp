#include <QDebug>

#include "Rounding.h"
#include "Settings.h"

/*!
  This round digits to the 2 places after commas.
  You should never use this, see fixstr
  */
QString
doRound (QString in)
{
  QString tmp = in;
  QString reszta = tmp.remove (0, tmp.indexOf(sett().getDecimalPointStr() ) + 1);
  if (reszta.length () > 2)
    {
      tmp = in;
      QString calk = tmp.remove (tmp.indexOf(sett().getDecimalPointStr() ), reszta.length () + 1);	// liczba calk
      // int last = reszta.right(1).toInt();
      // first
      // if we  have 0,12321321321
      // the wy modify this to: 0,123
      // second
      // roud (depending on last digit >5 or < 5)
      reszta = "0" + sett().getDecimalPointStr()  + reszta;
      double dOriginal = reszta.toDouble ();
      double iTemp = 0;
      //  qDebug(sett().numberToString(last));
      // if (last < 5)
      iTemp = floor ((dOriginal + .005) * 100);
      /*
         if (last > 5)
         iTemp = floor((dOriginal - .005) * 100);
       */

      dOriginal = iTemp / 100;


      // qDebug("!!!" + reszta + " | | " + calk );
      QString out = QLocale::toString (calk.toInt () + dOriginal);
// in = in.replace(",", ".");


      return out;
    }
  else
    {
      return in;
    }
}

QString
addZeros (QString in)
{
  // ie. 0, then return 0,00
  QString sth = in;
  QString reszta = sth.remove (0, sth.indexOf(sett().getDecimalPointStr()) + 1);
  // qDebug( reszta + " " + in );
  if (reszta.length () == 1)
    {
      if (in.indexOf(sett().getDecimalPointStr() , 0) == -1)
	{
	  return in +  sett().getDecimalPointStr()  + "00";
	}
      return in + "0";
    }
  return in;
}

QString
trimZeros (QString in)
{
	// code to remove unncessery zeros
	QStringList quan = in.split(sett().getDecimalPointStr());
	QString quantity = in;
	if (quan[1].compare("000") == 0) {
		quantity = quan[0];
	}
	return quantity;
}

/*!
  This round or just add two zeros
  Use this function when need to rouind sth.
  */
QString
fixStr (QString in)
{
  QString tmp = in;
  if (tmp.indexOf(sett().getDecimalPointStr(), 0) == -1)
    {
      return tmp + sett().getDecimalPointStr()  + "00";
    }
  return addZeros (doRound (in));
}

/*!
 This calculate brutto
  */
float
getPriceGross2 (double netto, QString vat)
{
  float nt = netto;		// .replace (",", ".").toFloat ();
  float tmpVt = vat.toFloat ();
  float vt = (tmpVt / 100) + 1;
  return nt * vt;
}

/*!
 This calculate brutto
  */
float
getPriceGross (QString count, QString netto, QString vat)
{
  float cnt = count.toFloat ();
  float nt = netto.toFloat ();
  float tmpVt = vat.toFloat ();
  float vt = (tmpVt / 100) + 1;
  return (nt * vt) * cnt;
}

/*!
 This calculate netto
  */
float
getPriceNett (QString count, QString netto)
{
  float cnt = count.toFloat ();
  float nt = netto.toFloat ();
  return nt * cnt;
}
