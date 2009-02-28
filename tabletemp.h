#ifndef TABLETEMP_H
#define TABLETEMP_H

#include <vector>
#include <qstring.h>

class TempData
{
public:
  QString title;  // title
  QString number; // number of facture
  QString sellingDate; // date of selling
  QString creatingDate;//date of creating
  QString client;
  QString sum;
  QString sumStr;
  QString netto,vat,brutto;
  QString payMode;
  QString payDate;
  bool paidCash;
  QString additText;
  QString bidsArray[4][4];
  QString bids;
};

class TableTemp
{
public:
    std::vector< std::vector<QString > > vec_temp;
    TempData data;
};

#endif




