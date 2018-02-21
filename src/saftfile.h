#ifndef SAFTFILE_H
#define SAFTFILE_H

#include "invoicedata.h"

#include <QWidget>

class IDataLayer;
class QTableWidget;
class QButtonGroup;

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
    void prepareNextStep();

protected:
    QVector<InvoiceData> getInvFromRange();

    const QString getFromDateJPK();
    const QString getToDateJPK();
    const QString getApplicationPurpose();
    const QString getJpkFileArt();

private:
    IDataLayer* dlSaftfile;
    QButtonGroup* groupAppPurp;
    QButtonGroup* groupArtFiles;
    QVector<InvoiceData> invs;
    Ui::Saftfile *ui;

    bool toDateisLower();
    void putIntoTable(QVector<InvoiceData> invoices);
    void insertRowToTable(QTableWidget *t, int row);
    void putBtnToGroup();
    void showConnections();
    QVector<InvoiceData> addSAFTFieldsToList(QVector<InvoiceData> invoices);
};

#endif // SAFTFILE_H
