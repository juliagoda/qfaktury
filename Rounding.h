#ifndef Rounding_H
#define Rounding_H

#include <qstring.h>
#include <qstringlist.h>
#include <math.h>

QString doRound (QString in);
QString fixStr (QString in);
float getPriceGross (QString count, QString netto, QString vat);
float getPriceNett (QString count, QString netto);
float getPriceGross2 (double netto, QString vat);
QString trimZeros(QString in);
QString addZeros(QString in);

#endif
