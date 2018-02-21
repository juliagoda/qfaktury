#ifndef SAFTFILEOUTPUT_H
#define SAFTFILEOUTPUT_H

#include "saftfile.h"
#include <QWidget>

class SaftfileOutput : public Saftfile
{
    Q_OBJECT
public:
    explicit SaftfileOutput(QVector<InvoiceData> invoicesList);
    ~SaftfileOutput();

public slots:

private slots:

private:
   QVector<InvoiceData> invoices;

};

#endif // SAFTFILEOUTPUT_H
