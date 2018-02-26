#ifndef SAFTFILEOUTPUT_H
#define SAFTFILEOUTPUT_H

#include "saftfile.h"
#include <QWidget>
#include <QXmlSchema>
#include <QXmlStreamWriter>


class SaftfileOutput : public Saftfile
{
    Q_OBJECT
public:
    explicit SaftfileOutput(QVector<InvoiceData> invoicesList);
    ~SaftfileOutput();
    QXmlSchema getXsdSchemaFromWebsite(QString fileArt);
    bool jpkDirExist();
    void createJpkDir(bool existsDir);
    QUrl prepareSchema(QString fileArt);
    QStringList getSortedVats(QVector<InvoiceData> inv);

    enum JPKType { JPK_VAT, JPK_FA };
    Q_ENUM(JPKType)

public slots:

protected:
    QString checkCurrenciesInList(QVector<InvoiceData> inv);
    QString prepareSchemaVersion(QString fileArt);
    QString prepareAppPurposeNr(QString fileArt, QString filePurpose);
    QString prepareFileVarriant(QString fileArtWithVersion);

private slots:

private:
   QVector<InvoiceData> invoices;

   QString prepareContent();
   void saveXmlFile();
   void saveXmlFileJKP_VAT(QXmlStreamWriter& xmlWriter);
   void saveXmlFileJKP_FA(QXmlStreamWriter& xmlWriter);

};

#endif // SAFTFILEOUTPUT_H
