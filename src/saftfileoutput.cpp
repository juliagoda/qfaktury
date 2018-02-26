#include "saftfileoutput.h"

#include <QRegularExpressionMatchIterator>
#include <QStringList>
#include <QList>


SaftfileOutput::SaftfileOutput(QVector<InvoiceData> invs) :
    invoices(invs)
{

}


SaftfileOutput::~SaftfileOutput() {


}


QString SaftfileOutput::prepareContent() {

    return QString();
}


QXmlSchema SaftfileOutput::getXsdSchemaFromWebsite(QString fileArt) {

    QUrl url(prepareSchema(fileArt));

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

    QDir JPKdir;
    if (!existsDir) JPKdir.mkpath(sett().getJPKDir());

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
    xmlWriter.writeAttribute("xsi:schemaLocation",prepareSchema(getJpkFileArt()).toString());
    xmlWriter.writeAttribute("xml:lang", "pl");
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("tns:Naglowek");
    xmlWriter.writeTextElement("tns:KodFormularza", getJpkFileArt() );
    xmlWriter.writeAttribute("kodSystemowy", getJpkFileArtWithVersion());
    xmlWriter.writeAttribute("wersjaSchemy", prepareSchemaVersion(getJpkFileArt()));
    xmlWriter.writeTextElement("tns:WariantFormularza", prepareFileVarriant(getJpkFileArtWithVersion()) );
    xmlWriter.writeTextElement("tns:CelZlozenia", prepareAppPurposeNr(getJpkFileArt(), getApplicationPurpose()) );
    xmlWriter.writeTextElement("tns:DataWytworzeniaJPK", QDateTime::currentDateTime().toString() );
    xmlWriter.writeTextElement("tns:DataOd", getFromDateJPK() );
    xmlWriter.writeTextElement("tns:DataDo", getToDateJPK() );

    switch (qRegisterMetaType<JPKType>()) {
    case 0:

        saveXmlFileJKP_VAT(xmlWriter);
        break;
    case 1:
        saveXmlFileJKP_FA(xmlWriter);
        break;
    default:

        break;
    }



    file.close();
}


QString SaftfileOutput::prepareSchemaVersion(QString fileArt) {

    if (fileArt == "JPK_VAT") return QString("1-1");
    else if (fileArt == "JPK_FA") return QString("1-0");

    return "1-1";
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

QUrl SaftfileOutput::prepareSchema(QString fileArt) {

    QString textUrl = "http://crd.gov.pl/xml/schematy/dziedzinowe/mf/2016/01/25/eD/DefinicjeTypy/StrukturyDanych_v4-0E.xsd";

    if (fileArt == "JPK_VAT")
    textUrl = "http://crd.gov.pl/xml/schematy/dziedzinowe/mf/2016/01/25/eD/DefinicjeTypy/StrukturyDanych_v4-0E.xsd";
    else if (fileArt == "JPK_FA")
    textUrl = "http://crd.gov.pl/xml/schematy/dziedzinowe/mf/2011/06/21/eD/DefinicjeTypy/ElementarneTypyDanych_v3-0E.xsd";

    QUrl url(textUrl);
    return url;
}


void SaftfileOutput::saveXmlFileJKP_VAT(QXmlStreamWriter& xmlWriter) {

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
}


void SaftfileOutput::saveXmlFileJKP_FA(QXmlStreamWriter& xmlWriter) {

    xmlWriter.writeTextElement("tns:DomyslnyKodWaluty", checkCurrenciesInList(invoices) );
    xmlWriter.writeTextElement("tns:KodUrzedu", getTaxOfficeNr() );
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("tns:Podmiot1");
        xmlWriter.writeStartElement("tns:IdentyfikatorPodmiotu");
            QSettings settings("elinux", "user");
            settings.beginGroup("choosenSeller");
            xmlWriter.writeTextElement("etd:NIP", settings.value("tic").toString().remove('-') );
            xmlWriter.writeTextElement("etd:PelnaNazwa", settings.value("name").toString() );
            xmlWriter.writeTextElement("etd:REGON", settings.value("regon").toString() );
            settings.endGroup();
        xmlWriter.writeEndElement();
        xmlWriter.writeStartElement("tns:AdresPodmiotu");
        // TODO
        // Add more places for user account
            xmlWriter.writeTextElement("etd:KodKraju", settings.value("regon").toString();
            xmlWriter.writeTextElement("etd:Wojewodztwo", settings.value("regon").toString();
            xmlWriter.writeTextElement("etd:Powiat", settings.value("regon").toString();
            xmlWriter.writeTextElement("etd:Gmina", settings.value("regon").toString();
            xmlWriter.writeTextElement("etd:Ulica", settings.value("regon").toString();
            xmlWriter.writeTextElement("etd:NrDomu", settings.value("regon").toString();
            xmlWriter.writeTextElement("etd:NrLokalu", settings.value("regon").toString();
            xmlWriter.writeTextElement("etd:Miejscowosc", settings.value("regon").toString();
            xmlWriter.writeTextElement("etd:KodPocztowy", settings.value("regon").toString();
            xmlWriter.writeTextElement("etd:Poczta", settings.value("regon").toString();
        xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();

    int sellCounts = 0;
    double invSum = 0.00;
    double gross = 0;

    for (int i = 0; i < invoices.size(); ++i) {

        sellCounts++;

        xmlWriter.writeStartElement("tns:Faktura");
        xmlWriter.writeAttribute("typ", "G");
            xmlWriter.writeTextElement("tns:P_1", );
            xmlWriter.writeTextElement("tns:P_2A", );
            xmlWriter.writeTextElement("tns:P_3A", );
            xmlWriter.writeTextElement("tns:P_3B", );
            xmlWriter.writeTextElement("tns:P_3C", );
            xmlWriter.writeTextElement("tns:P_3D", );
            xmlWriter.writeTextElement("tns:P_4B", );
            xmlWriter.writeTextElement("tns:P_5B", );
            xmlWriter.writeTextElement("tns:P_6", );
            xmlWriter.writeTextElement("tns:P_13_1", );
            xmlWriter.writeTextElement("tns:P_14_1", );


            QList<ProductData> products1 = invoices.at(i).products.values();

            for (int j = 0; j < products1.count(); j++) {
              gross += products1.at(j).gross;
            }

            invSum += gross;

            xmlWriter.writeTextElement("tns:P_15", QString("%1").arg(gross));
            xmlWriter.writeTextElement("tns:P_16", );
            xmlWriter.writeTextElement("tns:P_17", );
            xmlWriter.writeTextElement("tns:P_18", );
            xmlWriter.writeTextElement("tns:P_19", );
            xmlWriter.writeTextElement("tns:P_20", );
            xmlWriter.writeTextElement("tns:P_21", );
            xmlWriter.writeTextElement("tns:P_22", );
            xmlWriter.writeTextElement("tns:P_23", );
            xmlWriter.writeTextElement("tns:P_106E_2", );
            xmlWriter.writeTextElement("tns:P_106E_3", );
            xmlWriter.writeTextElement("tns:RodzajFaktury", );
        xmlWriter.writeEndElement();

     }

    xmlWriter.writeStartElement("tns:FakturaCtrl");
        xmlWriter.writeTextElement("tns:LiczbaFaktur", QString::number(sellCounts));
        xmlWriter.writeTextElement("tns:WartoscFaktur", QString("%1").arg(invSum));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("tns:StawkiPodatku");

    QStringList sortedVats = getSortedVats(invoices);
    int limit = sortedVats.count() > 5 ? 5 : sortedVats.count();

    for (int k = 0; k < limit; k++) {

        xmlWriter.writeTextElement(QString("tns:Stawka%1").arg(k+1), sortedVats.at(k));

        if (k == (limit-1)) {
            for (int l = (k+1); l < (5 - l); l++) {
                xmlWriter.writeTextElement(QString("tns:Stawka%1").arg(l+1), sortedVats.at(l));
            }
        }
    }

        xmlWriter.writeEndElement();

        int invProdCounts = 0;
        int nettSum = 0.00;

        for (int i = 0; i < invoices.size(); ++i) {

            QList<ProductData> products1 = invoices.at(i).products.values();

            for (int j = 0; j < products1.count(); j++) {
                  invProdCounts++;
                  xmlWriter.writeStartElement("tns:FakturaWiersz");
                  xmlWriter.writeAttribute("typ", "G");
                    xmlWriter.writeTextElement("tns:P_2B", );
                    xmlWriter.writeTextElement("tns:P_7", );
                    xmlWriter.writeTextElement("tns:P_8B", );
                    xmlWriter.writeTextElement("tns:P_9A", );
                    xmlWriter.writeTextElement("tns:P_9B", );

                    nettSum += products1.at(i).nett;
                    xmlWriter.writeTextElement("tns:P_11", QString("%1").arg(products1.at(i).nett));
                    xmlWriter.writeTextElement("tns:P_11A", );
                    xmlWriter.writeTextElement("tns:P_12", );
                  xmlWriter.writeEndElement();
            }
        }

        xmlWriter.writeStartElement("tns:FakturaWierszCtrl");
            xmlWriter.writeTextElement("tns:LiczbaWierszyFaktur", QString::number(invProdCounts));
            xmlWriter.writeTextElement("tns:WartoscWierszyFaktur", QString("%1").arg(nettSum));
        xmlWriter.writeEndElement();

}


QString SaftfileOutput::checkCurrenciesInList(QVector<InvoiceData> inv) {

    bool allTheSame = true;

    for (int x = 0; x < inv.size(); x++) {

        if (inv.at(x).currencyType != getDefaultCur()) {
            // TODO
            // get bureau sum from website
            // for this InvoiceData multiple all needed value to default sums
            // change text of this currency to default
            allTheSame = false;
        }

    }

    if (allTheSame) return getDefaultCur();

    return "PLN";
}


QStringList SaftfileOutput::getSortedVats(QVector<InvoiceData> inv) {

    QStringList vats = QStringList();

    for (int i = 0; i < inv.size(); ++i) {

            QList<ProductData> products1 = inv.at(i).products.values();

            for (int j = 0; j < products1.count(); j++) {
              QString vat = QString("%1").arg(products1.at(j).vat/100);

              if (!vats.contains(vat)) vats.append(vat);

    }
            // sorts from greater value to less
            qSort(vats.begin(), vats.end(), qGreater<QString>());

        return vats;

}
