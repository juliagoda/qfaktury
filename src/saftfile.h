#ifndef SAFTFILE_H
#define SAFTFILE_H

#include "invoicedata.h"

#include <QWidget>

class IDataLayer;
class QTableWidget;

namespace Ui {
class Saftfile;
}

class Saftfile : public QWidget
{
    Q_OBJECT

public:
    explicit Saftfile(QWidget *parent = 0);
    Saftfile(IDataLayer* dl, QWidget* parent = 0);
    ~Saftfile();

private slots:
    void initInvoicesRange();

protected:
    QVector<InvoiceData> getInvFromRange();

private:
    IDataLayer* dlSaftfile;
    Ui::Saftfile *ui;

    bool toDateisLower();
    void putIntoTable(QVector<InvoiceData> invoices);
    void insertRowToTable(QTableWidget *t, int row);
};

#endif // SAFTFILE_H
