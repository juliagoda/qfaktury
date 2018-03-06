#ifndef CSVEXPORT_H
#define CSVEXPORT_H

#include "idatalayer.h"

#include <QWidget>

namespace Ui {
class CsvExport;
}

class CsvExport : public QWidget
{
    Q_OBJECT

public:
    explicit CsvExport(IDataLayer* dlCsv, QWidget *parent = 0);
    ~CsvExport();

    const QString getPathCsv();
    bool createPathCsv(const QString path);
    QString preventNull(QString elementText);
    int getInvoiceTypeFullName(QString invoiceType);


protected:
    void createBuyersCsvFiles(QString format);
    void createProductsCsvFiles(QString format);
    void createSellersCsvFiles(QString format);
    void createInvoicesCsvFiles(QString format, QDate from, QDate to);
    void createWareCsvFiles(QString format, QDate from, QDate to);


private slots:
    void choosePathCsv();
    void createCsvFiles();


private:
    Ui::CsvExport *ui;
    IDataLayer* dl;
    QHash<QString, QString> idCvsSeller;
    QHash<QString, QString> idCvsBuyer;
    QHash<QString, QString> idCvsInvoices;
    QHash<QString, QString> idCvsWarehouses;
    QHash<QString, QString> idCvsProducts;

    QString separator(QString format);
    void prepareConnections();
    void putDataIntoWidgets(QString dirPath);
    void splitCsvTasks(bool expBuyers, bool expGoods, bool expInvoices, bool expWarehouses);
    void createBuyersCsvFiles();

};

#endif // CSVEXPORT_H
