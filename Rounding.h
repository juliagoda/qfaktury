#ifndef Rounding_H
#define Rounding_H

#include <qstring.h>
#include <qstringlist.h>
#include <math.h>

QString doRound (QString in);
QString fixStr (QString in);
float getPrice (QString count, QString netto, QString vat);
float getPrice2 (QString count, QString netto);
QString addZeros (QString in);

#endif
