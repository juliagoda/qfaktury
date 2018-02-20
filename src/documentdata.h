#include "detector.h"
#if _pragma_once_support
#pragma once
#endif
#ifndef DOCUMENTDATA_H
#define DOCUMENTDATA_H

#include <QString>

// parent class for two inherited classes: InvoiceData and WarehouseData
class DocumentData {

public:
  virtual QString getCustomer() {
    return QString();
  }; // use method for inherited classes, because variable cannot be virtual

protected:
private:
};

#endif // DOCUMENTDATA_H
