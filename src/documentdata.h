#include "detector.h"
#if _pragma_once_support
#pragma once
#endif
#ifndef DOCUMENTDATA_H
#define DOCUMENTDATA_H

#include <QString>

class DocumentData {

public:
    virtual QString getCustomer(){return QString();};

protected:

private:


};

#endif // DOCUMENTDATA_H
