#include "saftfileoutput.h"

#include <QXmlSchema>
#include <QXmlStreamWriter>
#include <QRegularExpressionMatchIterator>

SaftfileOutput::SaftfileOutput(QVector<InvoiceData> invs) :
    invoices(invs)
{

}


SaftfileOutput::~SaftfileOutput() {


}


QString SaftfileOutput::prepareContent() {

}


QXmlSchema SaftfileOutput::getXsdSchemaFromWebsite(QString fileArt) {

    QUrl url;

    if (fileArt == "JPK_VAT")
    url("http://crd.gov.pl/xml/schematy/dziedzinowe/mf/2016/01/25/eD/DefinicjeTypy/StrukturyDanych_v4-0E.xsd");
    else if (fileArt == "JPK_FA")
    url("http://crd.gov.pl/xml/schematy/dziedzinowe/mf/2011/06/21/eD/DefinicjeTypy/ElementarneTypyDanych_v3-0E.xsd");

    QXmlSchema schema;
    if (schema.load(url) == true)
        qDebug() << "schema from " << url.toString() << "  is valid";
    else
        qDebug() << "schema from " << url.toString() << " is invalid";

    return schema;
}


bool SaftfileOutput::jpkDirExist() {

    const QFileInfo jpkDir(sett().getJPKDir());
    if ((!jpkDir.exists()) || (!jpkDir.isDir()) || (!jpkDir.isWritable())) {
        qWarning() << "Directory doesn't exist: "
                   << jpkDir.absoluteFilePath();
        return false;
    }

    return true;
}


void SaftfileOutput::createJpkDir(bool existsDir) {

    if (!existsDir) QDir::mkpath(sett().getJPKDir());

}


void SaftfileOutput::saveXmlFile() {

    QFile file(sett().getJPKDir() + "/" + QDate::currentDate().toString("yyyyMMdd") + "JPKVAT");
    file.open(QIODevice::WriteOnly);

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.setAutoFormattingIndent(2);
    xmlWriter.writeStartDocument();

    xmlWriter.writeStartElement("tns:JPK");
    xmlWriter.writeAttribute("xmlns:etd","http://crd.gov.pl/xml/schematy/dziedzinowe/mf/2016/01/25/eD/DefinicjeTypy/");
    xmlWriter.writeAttribute("xmlns:tns","http://jpk.mf.gov.pl/wzor/2017/11/13/1113/");
    xmlWriter.writeAttribute("xmlns:xsi","http://www.w3.org/2001/XMLSchema-instance");
    xmlWriter.writeAttribute("xmlns:kck", "http://crd.gov.pl/xml/schematy/dziedzinowe/mf/2013/05/23/eD/KodyCECHKRAJOW/");
    xmlWriter.writeAttribute("xsi:schemaLocation","http://crd.gov.pl/xml/schematy/dziedzinowe/mf/2016/01/25/eD/DefinicjeTypy/StrukturyDanych_v4-0E.xsd");
    xmlWriter.writeAttribute("xml:lang", "pl");

    xmlWriter.writeStartElement("tns:Naglowek");
    xmlWriter.writeTextElement("tns:KodFormularza", getJpkFileArt() );
    xmlWriter.writeAttribute("kodSystemowy", getJpkFileArtWithVersion());
    xmlWriter.writeAttribute("wersjaSchemy", prepareSchema(getJpkFileArt()));
    xmlWriter.writeTextElement("tns:WariantFormularza", prepareFileVarriant(getJpkFileArtWithVersion() );
    xmlWriter.writeTextElement("tns:CelZlozenia", prepareAppPurposeNr(getJpkFileArt(), getApplicationPurpose()) );
    xmlWriter.writeTextElement("tns:DataWytworzeniaJPK", QDateTime::currentDateTime() );
    xmlWriter.writeTextElement("tns:DataOd", getFromDateJPK() );
    xmlWriter.writeTextElement("tns:DataDo", getToDateJPK() );
    xmlWriter.writeTextElement("tns:NazwaSystemu", "QFaktury" );
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("tns:Podmiot1");
    QSettings settings("elinux", "user");
    settings.beginGroup("choosenSeller");
    xmlWriter.writeTextElement("tns:NIP", settings.value("tic").toString().remove('-') );
    xmlWriter.writeTextElement("tns:PelnaNazwa", settings.value("name").toString() );
    xmlWriter.writeTextElement("tns:Email", settings.value("email").toString() );
    settings.endGroup();
    xmlWriter.writeEndElement();

    int sellCounts = 0;
    double vatPriceSum = 0.00;

    for (int i = 0; i < invoices.size(); ++i) {

        sellCounts++;

        xmlWriter.writeStartElement("tns:SprzedazWiersz");
        xmlWriter.writeTextElement("tns:LpSprzedazy", QString::number(i+1) );
        xmlWriter.writeTextElement("tns:NrKontrahenta", invoices.at(i).custTic.remove('-') );
        xmlWriter.writeTextElement("tns:NazwaKontrahenta", invoices.at(i).custName );
        xmlWriter.writeTextElement("tns:AdresKontrahenta", invoices.at(i).custStreet );
        xmlWriter.writeTextElement("tns:DowodSprzedazy", invoices.at(i).invNr );
        xmlWriter.writeTextElement("tns:DataWystawienia", invoices.at(i).issueDate.toString("yyyy-MM-dd") );
        xmlWriter.writeTextElement("tns:DataSprzedazy", invoices.at(i).sellingDate.toString("yyyy-MM-dd") );

        for (int j = 10; j < 40; j++) {

            switch (j) {
            case 19:

                double nett = 0;
                QList<ProductData> products1 = invoices.at(i).products.values();

                for (int j = 0; j < products1.count(); j++) {
                  nett += products1.at(j).nett;
                }

                xmlWriter.writeTextElement("tns:K_19", QString("%1").arg(nett) );

                break;
            case 20:

                double vatPrice = 0;
                QList<ProductData> products2 = invoices.at(i).products.values();

                for (int j = 0; j < products2.count(); j++) {
                  vatPrice += (products2.at(j).gross - products2.at(j).nett);
                }

                vatPriceSum += vatPrice;
                xmlWriter.writeTextElement("tns:K_20", QString("%1").arg(vatPrice) );

                break;
            default:

                xmlWriter.writeTextElement(QString("tns:K_%1").arg(j), "0.00" );
                break;
            }
        }

        xmlWriter.writeEndElement();
    }

    xmlWriter.writeStartElement("tns:SprzedazCtrl");
    xmlWriter.writeTextElement("tns:LiczbaWierszySprzedazy", QString::number(sellCounts) );
    xmlWriter.writeTextElement("tns:PodatekNalezny", sett().numberToString(vatPriceSum) );
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("tns:ZakupCtrl");
    xmlWriter.writeTextElement("tns:LiczbaWierszyZakupow", "0" );
    xmlWriter.writeTextElement("tns:PodatekNalezny", "0.00" );
    xmlWriter.writeEndElement();

        file.close();
}


QString SaftfileOutput::prepareSchema(QString fileArt) {

    if (fileArt == "JPK_VAT") return QString("1-1");
    else if (fileArt == "JPK_FA") return QString("1-0");
}


QString SaftfileOutput::prepareAppPurposeNr(QString fileArt, QString filePurpose) {

    if (fileArt == "JPK_FA" && filePurpose == "Standardowe") return "1";
    else if (fileArt == "JPK_FA" && filePurpose == "Korekta") return getCorrectionNr();
    else if (fileArt == "JPK_VAT" && filePurpose == "Standardowe") return "0";
    else if (fileArt == "JPK_VAT" && filePurpose == "Korekta") return getCorrectionNr(); // in range 1 - 9

}

QString SaftfileOutput::prepareFileVarriant(QString fileArtWithVersion) {

    QString number{"1"};
    QRegularExpression rx("[0-9]+");
    QRegularExpressionMatchIterator matches = rx.globalMatch(fileArtWithVersion);
    while (matches.hasNext()) {
        QRegularExpressionMatch match = matches.next();
        qDebug() << match.captured(0);
        number = match.captured(0);
    }

    return number;
}

