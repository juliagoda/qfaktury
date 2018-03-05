#include "detector.h"
#if _pragma_once_support
#pragma once
#endif
#ifndef SAFTFILEOUTPUT_H
#define SAFTFILEOUTPUT_H

#include "saftfile.h"
#include <QWidget>
#include <QXmlSchema>
#include <QXmlStreamWriter>
#include <QPointer>

class QPlainTextEdit;
class QPushButton;
class MessageHandler;


class SaftfileOutput : public Saftfile
{
    Q_OBJECT

public:
    explicit SaftfileOutput(QVector<InvoiceData> invoicesList, QHash<QString, QString> data);
    ~SaftfileOutput();
    QXmlSchema getXsdSchemaFromWebsite(QString fileArt);
    bool jpkDirExist();
    void createJpkDir(bool existsDir);
    QString prepareSchema(QString fileArt);
    QStringList getSortedVats(QVector<InvoiceData> inv);
    const QString getStreetName(QString fullAddress);
    const QString getHouseNumer(QString fullAddress);
    const QString getDoorNumer(QString fullAddress);

    enum JPKType { JPK_VAT, JPK_FA };
    Q_ENUM(JPKType)

public slots:

protected:
    QString checkCurrenciesInList(QVector<InvoiceData> inv);
    QString prepareTns(QString fileArt);
    QString prepareSchemaVersion(QString fileArt);
    QString prepareAppPurposeNr(QString fileArt, QString filePurpose);
    QString prepareFileVarriant(QString fileArtWithVersion);
    const QString getInvTypeForJPKFA(QString abbrInv, QString paymentType, QChar beginFilename);
    const QString getContentFromFileJPK(QString filepath);
    void findErrors(QString fileArt, const QString content);

private slots:
    void overwriteFile();
    void textChanged();

private:
   QVector<InvoiceData> invoices;
   QHash<QString, QString> allData;
   QPointer<QPlainTextEdit> jpkContent;
   QPointer<QPushButton> overwriteBtn;
   QPointer<QLabel> statusText;

   void createNoteJPKWindow(MessageHandler* messageHandler = 0);
   void saveXmlFile();
   void saveXmlFileJKP_VAT(QXmlStreamWriter& xmlWriter);
   void saveXmlFileJKP_FA(QXmlStreamWriter& xmlWriter);
   void saveErrors(MessageHandler* messageHandler);
   void moveCursor(int line, int column);
   void inputTextFile(const QString content);
   void putOptIfNotEmpty(QXmlStreamWriter& writer, QString node, QString value);

};

#endif // SAFTFILEOUTPUT_H
