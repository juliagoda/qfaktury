#include "saftfileoutput.h"
#include "messagehandler.h"
#include "runguard.h"

#include <QRegularExpressionMatchIterator>
#include <QClipboard>
#include <QGuiApplication>
//#include <QXmlSchemaValidator> // can be used, when class will work properly (below commented lines in source too)
#include <QPlainTextEdit>
#include <QStringList>
#include <QList>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMetaEnum>


SaftfileOutput::SaftfileOutput(QVector<InvoiceData> invs, QHash<QString, QString> data) :
    invoices(invs), allData(data)
{
    this->hide();
    createJpkDir(jpkDirExist());
    saveXmlFile();
    findErrors(allData.value("jpkFileArt"), getContentFromFileJPK(sett().getJPKDir() + "/" + QDate::currentDate().toString("yyyyMMdd") + allData.value("jpkFileArt")));
}


SaftfileOutput::~SaftfileOutput() {


}


QXmlSchema SaftfileOutput::getXsdSchemaFromWebsite(QString fileArt) {

    QFile schemaData(prepareSchema(fileArt));
    QXmlSchema schema;
    if (!schemaData.open(QIODevice::ReadOnly)) {
            qDebug() << "Cannot read file: " << schemaData.fileName();
    }

    if (schema.load(schemaData.readAll()))
        qDebug() << "schema from " << schemaData.fileName() << "  is valid: ";
    else
        qDebug() << "schema from " << schemaData.fileName() << " is invalid: ";

    schemaData.close();
    return schema;

}


bool SaftfileOutput::jpkDirExist() {

const QFileInfo jpkDir(sett().getJPKDir());
if ((!jpkDir.exists()) || (!jpkDir.isDir()) || (!jpkDir.isWritable())) {
  qWarning() << "Directory doesn't exist: " << jpkDir.absoluteFilePath();
  return false;
}

    return true;
}


void SaftfileOutput::createJpkDir(bool existsDir) {

    QDir JPKdir;
    if (!existsDir) JPKdir.mkpath(sett().getJPKDir());

}


void SaftfileOutput::saveXmlFile() {

    QFile file(sett().getJPKDir() + "/" + QDate::currentDate().toString("yyyyMMdd") + allData.value("jpkFileArt"));
    file.open(QIODevice::WriteOnly);

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.setAutoFormattingIndent(2);
    xmlWriter.writeStartDocument();

    xmlWriter.writeStartElement("tns:JPK");
    xmlWriter.writeAttribute("xmlns:etd", "http://crd.gov.pl/xml/schematy/dziedzinowe/mf/2016/01/25/eD/DefinicjeTypy/");
    xmlWriter.writeAttribute("xmlns:tns", prepareTns(allData.value("jpkFileArt")));
    xmlWriter.writeAttribute("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
    xmlWriter.writeAttribute("xmlns:kck", "http://crd.gov.pl/xml/schematy/dziedzinowe/mf/2013/05/23/eD/KodyCECHKRAJOW/");
    //xmlWriter.writeAttribute("xsi:schemaLocation", prepareSchema(allData.value("jpkFileArt")).toString());

    xmlWriter.writeStartElement("tns:Naglowek");
    xmlWriter.writeStartElement("tns:KodFormularza" );
    xmlWriter.writeAttribute("kodSystemowy", allData.value("jpkFileArtWithVersion")) ;
    xmlWriter.writeAttribute("wersjaSchemy", prepareSchemaVersion(allData.value("jpkFileArt")));
    xmlWriter.writeCharacters(allData.value("jpkFileArt"));
    xmlWriter.writeEndElement();
    xmlWriter.writeTextElement("tns:WariantFormularza", prepareFileVarriant(allData.value("jpkFileArtWithVersion")) );
    xmlWriter.writeTextElement("tns:CelZlozenia", prepareAppPurposeNr(allData.value("jpkFileArt"), allData.value("applicationPurpose")) );
    xmlWriter.writeTextElement("tns:DataWytworzeniaJPK", QDateTime::currentDateTime().toString("yyyy-MM-ddTHH:mm:ss") );
    xmlWriter.writeTextElement("tns:DataOd", allData.value("jpkFromDate") );
    xmlWriter.writeTextElement("tns:DataDo", allData.value("jpkToDate") );

    QMetaEnum metaEnum = QMetaEnum::fromType<SaftfileOutput::JPKType>();
    QString get = allData.value("jpkFileArt");
    QByteArray ba = get.toLatin1();
    const char *c_str2 = ba.data();

    qDebug() << get << " <- JPK File Art";
    qDebug() << metaEnum.keyToValue(c_str2) << " <- metaEnum Number";

    switch (metaEnum.keyToValue(c_str2)) {
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


QString SaftfileOutput::prepareTns(QString fileArt) {

    if (fileArt == "JPK_VAT") return QString("http://jpk.mf.gov.pl/wzor/2017/11/13/1113/");
    else if (fileArt == "JPK_FA") return QString("http://jpk.mf.gov.pl/wzor/2016/03/09/03095/");

    return QString("http://jpk.mf.gov.pl/wzor/2017/11/13/1113/");
}


QString SaftfileOutput::prepareSchemaVersion(QString fileArt) {

    if (fileArt == "JPK_VAT") return QString("1-1");
    else if (fileArt == "JPK_FA") return QString("1-0");

    return "1-1";
}


QString SaftfileOutput::prepareAppPurposeNr(QString fileArt, QString filePurpose) {

    if (fileArt == "JPK_FA" && filePurpose == "Standardowe") return "1";
    else if (fileArt == "JPK_FA" && filePurpose == "Korekta") return allData.value("correctionNr");
    else if (fileArt == "JPK_VAT" && filePurpose == "Standardowe") return "0";
    else if (fileArt == "JPK_VAT" && filePurpose == "Korekta") return allData.value("correctionNr"); // in range 1 - 9

    return "0";
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


QString SaftfileOutput::prepareSchema(QString fileArt) {

    QString textUrl = QString();

    if (fileArt == "JPK_VAT")
    textUrl = ":/documents/schemas/Schemat_JPK_VAT3_v1-1.xsd";
    else if (fileArt == "JPK_FA")
    textUrl = ":/documents/schemas/Schemat_JPK_FA_v1-0.xsd";

    qDebug() << "Chosen xsd file: " << textUrl;

    return textUrl;
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
        QString custTic = invoices.at(i).custTic;
        xmlWriter.writeTextElement("tns:NrKontrahenta", custTic.remove('-') );
        xmlWriter.writeTextElement("tns:NazwaKontrahenta", invoices.at(i).custName );
        xmlWriter.writeTextElement("tns:AdresKontrahenta", invoices.at(i).custStreet );
        xmlWriter.writeTextElement("tns:DowodSprzedazy", invoices.at(i).invNr );
        xmlWriter.writeTextElement("tns:DataWystawienia", invoices.at(i).productDate.toString("yyyy-MM-dd") );
        xmlWriter.writeTextElement("tns:DataSprzedazy", invoices.at(i).sellingDate.toString("yyyy-MM-dd") );

        for (int j = 10; j < 40; j++) {

            switch (j) {
            case 19: {

                double nett = 0;
                QList<ProductData> products1 = invoices.at(i).products.values();

                for (int j = 0; j < products1.count(); j++) {
                  nett += products1.at(j).nett;
                }

                xmlWriter.writeTextElement("tns:K_19", QString("%1").arg(nett) );
            }
                break;
            case 20: {

                double vatPrice = 0;
                QList<ProductData> products2 = invoices.at(i).products.values();

                for (int j = 0; j < products2.count(); j++) {
                  vatPrice += (products2.at(j).gross - products2.at(j).nett);
                }

                vatPriceSum += vatPrice;
                xmlWriter.writeTextElement("tns:K_20", QString("%1").arg(vatPrice) );
            }
                break;
            default: {

                xmlWriter.writeTextElement(QString("tns:K_%1").arg(j), "0.00" );

            }
                break;
            }
        }

        xmlWriter.writeEndElement();
    }

    xmlWriter.writeStartElement("tns:SprzedazCtrl");
    xmlWriter.writeTextElement("tns:LiczbaWierszySprzedazy", QString::number(sellCounts) );
    xmlWriter.writeTextElement("tns:PodatekNalezny", sett().numberToString(vatPriceSum).remove(',') );
    xmlWriter.writeEndElement();

    xmlWriter.writeEndElement(); // end of tns:JPK
}


void SaftfileOutput::saveXmlFileJKP_FA(QXmlStreamWriter& xmlWriter) {

 // xmlWriter.writeTextElement("tns:DomyslnyKodWaluty", checkCurrenciesInList(invoices) );
    xmlWriter.writeTextElement("tns:DomyslnyKodWaluty", allData.value("defaultCurrency") );
    xmlWriter.writeTextElement("tns:KodUrzedu", allData.value("codeTaxOffice") );
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("tns:Podmiot1");
        xmlWriter.writeStartElement("tns:IdentyfikatorPodmiotu");
            QSettings settingsf("elinux", "user");
            settingsf.beginGroup("choosenSeller");
            xmlWriter.writeTextElement("etd:NIP", settingsf.value("tic").toString().remove('-') );
            xmlWriter.writeTextElement("etd:PelnaNazwa", settingsf.value("name").toString() );
            putOptIfNotEmpty(xmlWriter, QString("etd:REGON"), settingsf.value("regon").toString());
            settingsf.endGroup();
        xmlWriter.writeEndElement();
        xmlWriter.writeStartElement("tns:AdresPodmiotu");
            QSettings settings("elinux", "user");
            settings.beginGroup("choosenSeller");
            QString addressText = settings.value("address").toString();
            xmlWriter.writeTextElement("etd:KodKraju", settings.value("codeLand").toString());
            xmlWriter.writeTextElement("etd:Wojewodztwo", settings.value("province").toString());
            xmlWriter.writeTextElement("etd:Powiat", settings.value("district").toString());
            xmlWriter.writeTextElement("etd:Gmina", settings.value("municipality").toString());
            xmlWriter.writeTextElement("etd:Ulica", getStreetName(addressText));
            xmlWriter.writeTextElement("etd:NrDomu", getHouseNumer(addressText));
            putOptIfNotEmpty(xmlWriter, QString("etd:NrLokalu"), getDoorNumer(addressText));
            xmlWriter.writeTextElement("etd:Miejscowosc", settings.value("city").toString());
            xmlWriter.writeTextElement("etd:KodPocztowy", settings.value("zip").toString());
            xmlWriter.writeTextElement("etd:Poczta", settings.value("post").toString());
            settings.endGroup();
        xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();

    int sellCounts = 0;
    double invSum = 0.00;
    double gross = 0;
    double sumBasicNet1 = 0.00;     // now is 23% or 22% VAT as basic; sum of basic net sums, which have 23 %
    double sumBasicVatPrice1 = 0.00;
    double sumBasicNet2 = 0.00;     // now is 7% or 8% VAT as basic
    double sumBasicVatPrice2 = 0.00;
    double sumBasicNet3 = 0.00;     // now is 5% VAT as basic
    double sumBasicVatPrice3 = 0.00;
    double sumBasicNet4 = 0.00;     // free place for optional VAT
    double sumBasicVatPrice4 = 0.00;
    double sumBasicNet5 = 0.00;     // free place for optional VAT
    double sumBasicVatPrice5 = 0.00;

    QStringList sortedVats = getSortedVats(invoices);

    for (int i = 0; i < invoices.size(); ++i) {

        sellCounts++;

        xmlWriter.writeStartElement("tns:Faktura");
        xmlWriter.writeAttribute("typ", "G");
            xmlWriter.writeTextElement("tns:P_1", invoices.at(i).productDate.toString("yyyy-MM-dd"));
            xmlWriter.writeTextElement("tns:P_2A", invoices.at(i).invNr);
            xmlWriter.writeTextElement("tns:P_3A", invoices.at(i).custName);
            xmlWriter.writeTextElement("tns:P_3B", invoices.at(i).custStreet);
            xmlWriter.writeTextElement("tns:P_3C", invoices.at(i).sellerName);
            xmlWriter.writeTextElement("tns:P_3D", invoices.at(i).sellerAddress);
            QString sellerTic = invoices.at(i).sellerTic;
            xmlWriter.writeTextElement("tns:P_4B", sellerTic.remove('-'));
            QString custTic = invoices.at(i).custTic;
            xmlWriter.writeTextElement("tns:P_5B", custTic.remove('-'));
            xmlWriter.writeTextElement("tns:P_6", invoices.at(i).endTransDate.toString("yyyy-MM-dd"));

            QList<ProductData> products1 = invoices.at(i).products.values();

            for (int j = 0; j < products1.count(); j++) {
              gross += products1.at(j).gross;

              if (products1.at(j).getVat() == 23) {

                  sumBasicNet1 += products1.at(j).nett;
                  sumBasicVatPrice1 += products1.at(j).nett * (static_cast<float>(products1.at(j).vat) / 100);

              } else if (products1.at(j).getVat() == 8 || products1.at(j).getVat() == 7) {

                  if ((sortedVats.contains("0.07") && !sortedVats.contains("0.08")) || sortedVats.contains("0.08")) {

                        sumBasicNet2 += products1.at(j).nett;
                        sumBasicVatPrice2 += products1.at(j).nett * (static_cast<float>(products1.at(j).vat) / 100);
                  }
              } else if (products1.at(j).getVat() == 5) {

                  sumBasicNet3 += products1.at(j).nett;
                  sumBasicVatPrice3 += products1.at(j).nett * (static_cast<float>(products1.at(j).vat) / 100);
              }

              if (products1.at(j).getVat() == 7) {

                  if (sortedVats.contains("0.07") && sortedVats.contains("0.08")) {

                        sumBasicNet4 += products1.at(j).nett;
                        sumBasicVatPrice4 += products1.at(j).nett * (static_cast<float>(products1.at(j).vat) / 100);
                }
              } else if (products1.at(j).getVat() == 4) {
                  if (sortedVats.contains("0.07") && sortedVats.contains("0.08")) {

                      sumBasicNet5 += products1.at(j).nett;
                      sumBasicVatPrice5 += products1.at(j).nett * (static_cast<float>(products1.at(j).vat) / 100);

                  } else {

                      sumBasicNet4 += products1.at(j).nett;
                      sumBasicVatPrice4 += products1.at(j).nett * (static_cast<float>(products1.at(j).vat) / 100);
                  }
              } else if (products1.at(j).getVat() == 0) {

                  if ((sortedVats.contains("0.07") && sortedVats.contains("0.08")) ^ sortedVats.contains("0.04")) {
                      sumBasicNet5 += products1.at(j).nett;
                  } else {
                      sumBasicNet4 += products1.at(j).nett;
                  }
            }

            }


            invSum += gross;
            QString invTypeJPK = getInvTypeForJPKFA(invoices.at(i).type, invoices.at(i).paymentType, invoices.at(i).id.at(0));

            xmlWriter.writeTextElement("tns:P_13_1", QString::number(sumBasicNet1,'f',2).remove(','));
            xmlWriter.writeTextElement("tns:P_14_1", QString::number(sumBasicVatPrice1, 'f', 2).remove(','));
            xmlWriter.writeTextElement("tns:P_13_2", QString::number(sumBasicNet2,'f',2).remove(','));
            xmlWriter.writeTextElement("tns:P_14_2", QString::number(sumBasicVatPrice2, 'f', 2).remove(','));
            xmlWriter.writeTextElement("tns:P_13_3", QString::number(sumBasicNet3,'f',2).remove(','));
            xmlWriter.writeTextElement("tns:P_14_3", QString::number(sumBasicVatPrice3, 'f', 2).remove(','));
            xmlWriter.writeTextElement("tns:P_13_4", QString::number(sumBasicNet4,'f',2).remove(','));
            xmlWriter.writeTextElement("tns:P_14_4", QString::number(sumBasicVatPrice4, 'f', 2).remove(','));
            xmlWriter.writeTextElement("tns:P_13_5", QString::number(sumBasicNet5,'f',2).remove(','));
            xmlWriter.writeTextElement("tns:P_14_5", QString::number(sumBasicVatPrice5, 'f', 2).remove(','));
            xmlWriter.writeTextElement("tns:P_15", QString::number(gross,'f',2).remove(','));
            xmlWriter.writeTextElement("tns:P_16", "false");
            xmlWriter.writeTextElement("tns:P_17", "false");
            xmlWriter.writeTextElement("tns:P_18", "false");
            xmlWriter.writeTextElement("tns:P_19", "false");
            xmlWriter.writeTextElement("tns:P_20", "false");
            xmlWriter.writeTextElement("tns:P_21", "false");
            xmlWriter.writeTextElement("tns:P_23", "false");
            xmlWriter.writeTextElement("tns:P_106E_2", "false");
            xmlWriter.writeTextElement("tns:P_106E_3", "false");
            xmlWriter.writeTextElement("tns:RodzajFaktury", invTypeJPK);

            if (invTypeJPK == "KOREKTA") {

                qDebug() << "PRZYCZYNA zmiennej reason " << invoices.at(i).reason;
                xmlWriter.writeTextElement("tns:PrzyczynaKorekty", invoices.at(i).reason);
                xmlWriter.writeTextElement("tns:NrFaKorygowanej", invoices.at(i).origInvNr);
                xmlWriter.writeTextElement("tns:OkresFaKorygowanej", invoices.at(i).productDate.toString("yyyy-MM-dd"));

            } else if (invTypeJPK == "ZAL") {

                double givenSum = 0.00;
                double vatSum = static_cast<float>(invoices.at(i).products.value(0).vat);
                if (invoices.at(i).custPaym.date1 < QDate::currentDate()) givenSum += invoices.at(i).custPaym.amount1;
                if (invoices.at(i).custPaym.date2 < QDate::currentDate()) givenSum += invoices.at(i).custPaym.amount2;
                xmlWriter.writeTextElement("tns:ZALZaplata", QString::number(givenSum, 'f', 2).remove(','));
                xmlWriter.writeTextElement("tns:ZALPodatek", QString::number((givenSum*vatSum)/(100+vatSum),'f',2).remove(','));
            }

        xmlWriter.writeEndElement();

     }

    xmlWriter.writeStartElement("tns:FakturaCtrl");
        xmlWriter.writeTextElement("tns:LiczbaFaktur", QString::number(sellCounts));
        xmlWriter.writeTextElement("tns:WartoscFaktur", QString("%1").arg(invSum));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("tns:StawkiPodatku");
        xmlWriter.writeTextElement(QString("tns:Stawka1"), QString("0.23"));

        if (sortedVats.contains("0.08")) xmlWriter.writeTextElement(QString("tns:Stawka2"), QString("0.08"));
        else if (sortedVats.contains("0.07")) xmlWriter.writeTextElement(QString("tns:Stawka2"), QString("0.07"));
        else xmlWriter.writeTextElement(QString("tns:Stawka2"), QString("0.08"));

        xmlWriter.writeTextElement(QString("tns:Stawka3"), QString("0.05"));

        if (sortedVats.contains("0.07") && sortedVats.contains("0.08")) xmlWriter.writeTextElement(QString("tns:Stawka4"), QString("0.07"));
        else if (sortedVats.contains("0.04")) xmlWriter.writeTextElement(QString("tns:Stawka4"), QString("0.04"));
        else xmlWriter.writeTextElement(QString("tns:Stawka4"), QString("0.00"));

        if ((sortedVats.contains("0.07") && sortedVats.contains("0.08")) && sortedVats.contains("0.04")) xmlWriter.writeTextElement(QString("tns:Stawka5"), QString("0.04"));
        else xmlWriter.writeTextElement(QString("tns:Stawka5"), QString("0.00"));
    xmlWriter.writeEndElement();

    qDebug() << sortedVats.count() << " additional sortedVats";


        int invProdCounts = 0;
        int nettSum = 0.00;

        for (int i = 0; i < invoices.size(); ++i) {

            QList<ProductData> products1 = invoices.at(i).products.values();

            for (int j = 0; j < products1.count(); j++) {
                  invProdCounts++;
                  xmlWriter.writeStartElement("tns:FakturaWiersz");
                  xmlWriter.writeAttribute("typ", "G");
                    xmlWriter.writeTextElement("tns:P_2B", invoices.at(i).invNr);
                    xmlWriter.writeTextElement("tns:P_7", products1.at(j).name);
                    xmlWriter.writeTextElement("tns:P_8B", QString("%1").arg(products1.at(j).quantity));
                    xmlWriter.writeTextElement("tns:P_9A", QString("%1").arg(products1.at(j).nett * (products1.at(j).discount / 100)));
                    xmlWriter.writeTextElement("tns:P_9B", QString("%1").arg(products1.at(j).price + (products1.at(j).price * (static_cast<float>(products1.at(j).vat) / 100))));

                    nettSum += products1.at(j).nett;
                    xmlWriter.writeTextElement("tns:P_11", QString("%1").arg(products1.at(j).nett));
                    xmlWriter.writeTextElement("tns:P_11A", QString("%1").arg(products1.at(j).gross));
                    xmlWriter.writeTextElement("tns:P_12", QString("%1").arg(products1.at(j).vat));
                  xmlWriter.writeEndElement();
            }
        }

        xmlWriter.writeStartElement("tns:FakturaWierszCtrl");
            xmlWriter.writeTextElement("tns:LiczbaWierszyFaktur", QString::number(invProdCounts));
            xmlWriter.writeTextElement("tns:WartoscWierszyFaktur", QString("%1").arg(nettSum));
        xmlWriter.writeEndElement();

    xmlWriter.writeEndElement(); // end of tns:JPK

}


QString SaftfileOutput::checkCurrenciesInList(QVector<InvoiceData> inv) {

    bool allTheSame = true;

    for (int x = 0; x < inv.size(); x++) {

        if (inv.at(x).currencyType != getDefaultCur()) {
           // inv.at(x).currencyType // convert this
           // getDefaultCur() // to this
            // TODO
            // get bureau sum from website
            // for this InvoiceData multiple all needed value to default sums
            // change text of this currency to default
            // allowed only after splitting bureau to other class from invoice
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


              QString vat = QString("%1").arg(static_cast<float>(products1.at(j).vat)/100);

              if (vat != "0.23" || vat != "0.05" ) {
                if (!vats.contains(vat)) vats.append(vat);
              }

            }
    }

    // sorts from greater value to less
    qSort(vats.begin(), vats.end(), qGreater<QString>());

return vats;


}


const QString SaftfileOutput::getStreetName(QString fullAddress) {

    int indexOfSpace = fullAddress.indexOf(QRegularExpression("\\d+"), 0) - 1;
    QString street{fullAddress.left(indexOfSpace)};
    return street;
}


const QString SaftfileOutput::getHouseNumer(QString fullAddress) {

    int indexOfFirstNum = fullAddress.indexOf(QRegularExpression("\\d+"), 0);

    if (fullAddress.contains('/')) {

        int indexOfLastNum = fullAddress.indexOf(QRegularExpression("/"), 0);
        int howManyElem = indexOfLastNum - indexOfFirstNum;

        QString house{fullAddress.mid(indexOfFirstNum,howManyElem)};

        return house;

    } else {

        QString house{fullAddress.mid(indexOfFirstNum)};
        return house;

    }
}


const QString SaftfileOutput::getDoorNumer(QString fullAddress) {

    if (fullAddress.contains('/')) {

        int indexOfFirstNumAfter = fullAddress.indexOf(QRegularExpression("/"), 0) + 1;
        QString door{fullAddress.mid(indexOfFirstNumAfter)};

        return door;

    }

    return QString();
}


const QString SaftfileOutput::getInvTypeForJPKFA(QString abbrInv, QString paymentType, QChar beginFilename) {

    qDebug() << "Abbreviation of invoice is: " << beginFilename;
    if ((abbrInv == "korekta") || (beginFilename == 'k')) return "KOREKTA";
    else if (paymentType == "zaliczka") return "ZAL";
    else if ((abbrInv == "FVAT") || (abbrInv == "FBrutto")) return "VAT";
    else return "POZ";

    return "VAT";
}


const QString SaftfileOutput::getContentFromFileJPK(QString filepath) {

    QFile file(filepath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << " Could not open the file for reading";
        return QString();
    }

    QTextStream in(&file);
    QString contentJPK = in.readAll();

    file.close();

    return contentJPK;
}


void SaftfileOutput::findErrors(QString fileArt, const QString content) {

    QFile schemaData(prepareSchema(fileArt));
    //QXmlSchema schema;
    if (!schemaData.open(QFile::ReadOnly | QFile::Text)) {
            qDebug() << "Cannot read file: " << schemaData.fileName();
    }

    QPointer<QClipboard> clipboard = QGuiApplication::clipboard();

    const QByteArray schemaContentByte = schemaData.readAll();

    // qDebug() << "Schema content: " << schemaContentByte;


     //   MessageHandler messageHandler;
     //   schema.setMessageHandler(&messageHandler);

     //   if (schema.load(schemaContent))
     //       qDebug() << "schema from " << schemaData.fileName() << "  is valid: ";
     //   else
     //       qDebug() << "schema from " << schemaData.fileName() << " is invalid: ";

       // QByteArray contentByte = content.toUtf8();

       // bool errorOccurred = false;
       // if (!schema.isValid()) {
       //     errorOccurred = true;
       // } else {
       //     QXmlSchemaValidator validator(schema);
       //     if (!validator.validate(contentByte))
        //        errorOccurred = true;
       // }

        /*    QXmlStreamReader xml(messageHandler.statusMessage());
            QString statusMessage = QString();
            while (!xml.atEnd()) {
                if ( xml.readNext() == QXmlStreamReader::Characters ) {
                    statusMessage += xml.text();
                }
            } */

        //if (errorOccurred) {
            QMessageBox msgBox;
           // msgBox.setText(QString("Napotkano błędy w generowanym pliku o treści:\n linia: %1, kolumna %2  %3").arg(messageHandler.line()).arg(messageHandler.column()).arg(statusMessage));
            msgBox.setText(QString("Dopóki błędy związane ze stosowaniem validatora plików xsd nie zostaną ostatecznie naprawione w bibliotece Qt5, walidacja w programie nie będzie ujęta. Zaleca się użycie walidatora na jednej ze stron internetowych, jak: \n https://www.freeformatter.com/xml-validator-xsd.html \n Zaleca się także dodatkowe sprawdzenie dokumentów z pomocą osób specjalizujących się w księgowości przed wysłaniem dokumentu"));
            //msgBox.setInformativeText("Co chcesz zrobić? Anulować? Zapisać plik z treścią błędów do katalogu plików JPK? Poprawić treść?");
            msgBox.setInformativeText("Co chcesz zrobić? Anulować? Skopiować treść schematu xsd do schowka? Skopiować treść pliku JPK do schowka? Poprawić treść? Wybór kopiowania nie zamyka okna.");

            QPushButton *cancelButton = msgBox.addButton(QMessageBox::Cancel);
            cancelButton->setObjectName("cancelBtn");
           // QPushButton *saveButton = msgBox.addButton(QMessageBox::Save);
            QPushButton *repairButton = msgBox.addButton(tr("Napraw"), QMessageBox::ActionRole);
            repairButton->setObjectName("repairBtn");
            QPushButton *xsdButton = msgBox.addButton(tr("Kopiuj xsd"), QMessageBox::HelpRole);
            xsdButton->setObjectName("xsdBtn");
            QPushButton *xmlButton = msgBox.addButton(tr("Kopiuj xml"), QMessageBox::HelpRole);
            xmlButton->setObjectName("xmlBtn");
            msgBox.setDefaultButton(repairButton);
            msgBox.exec();


            if (msgBox.clickedButton() == cancelButton) {

                msgBox.close();

            } else if (msgBox.clickedButton() == repairButton) {

                createNoteJPKWindow();

            } else if (msgBox.clickedButton() == xsdButton) {

                QTextCodec *codec2 = QTextCodec::codecForName("UTF-8");
                clipboard.data()->setText(codec2->toUnicode(schemaContentByte));

            } else if (msgBox.clickedButton() == xmlButton) {

                clipboard.data()->setText(content);

            }// else if (msgBox.clickedButton() == saveButton) {
             //   saveErrors(&messageHandler);
            //}




            msgBox.removeButton(cancelButton);
         //   msgBox.removeButton(saveButton);
            msgBox.removeButton(repairButton);
            msgBox.removeButton(xsdButton);
            msgBox.removeButton(xmlButton);

            delete cancelButton;
         //   delete saveButton;
            delete repairButton;
            delete xsdButton;
            delete xmlButton;
        //}

        schemaData.close();
}


void SaftfileOutput::saveErrors(MessageHandler* messageHandler) {

    QFile outfile;
    outfile.setFileName(sett().getJPKDir() + "/" + QDate::currentDate().toString("yyyyMMdd") + allData.value("jpkFileArt") + "-Errors");
    outfile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&outfile);
    out << messageHandler->statusMessage() << endl;
    outfile.close();
}


void SaftfileOutput::createNoteJPKWindow(MessageHandler* messageHandler) {

    RunGuard guard( "jpkmodification_run_protection" );
    if ( guard.tryToRun() ) {

    QPointer<QWidget> jpkWindow = new QWidget;
    jpkWindow.data()->setWindowTitle("Modyfikacja pliku JPK");
    jpkWindow.data()->setWindowModality(Qt::ApplicationModal);
    statusText = new QLabel();
    statusText.data()->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    statusText.data()->show();
    QSize size(600, 700);
    jpkWindow.data()->setMinimumSize(size);
    jpkContent = new QPlainTextEdit;
    jpkContent.data()->show();
    QPointer<QPushButton> cancelBtn = new QPushButton("Wyjdź");
    overwriteBtn = new QPushButton("Nadpisz");
    overwriteBtn.data()->show();

    QPointer<QHBoxLayout> hboxLay = new QHBoxLayout;

    hboxLay.data()->addWidget(cancelBtn.data());
    hboxLay.data()->addWidget(statusText);
    hboxLay.data()->addWidget(overwriteBtn.data());

    QPointer<QVBoxLayout> vboxLay = new QVBoxLayout;

    vboxLay.data()->addWidget(jpkContent);
    vboxLay.data()->addLayout(hboxLay.data());

    jpkWindow.data()->setLayout(vboxLay.data());

    jpkWindow.data()->show();
    jpkWindow.data()->update();

    connect(overwriteBtn.data(), SIGNAL(clicked(bool)), this, SLOT(overwriteFile()));
    connect(cancelBtn.data(), SIGNAL(clicked(bool)), jpkWindow.data(), SLOT(close()));
   // connect(jpkContent.data(), SIGNAL(textChanged()), SLOT(textChanged()));

    inputTextFile(getContentFromFileJPK(sett().getJPKDir() + "/" + QDate::currentDate().toString("yyyyMMdd") + allData.value("jpkFileArt")));
    if (messageHandler != 0) statusText.data()->setText(messageHandler->statusMessage());
    if (messageHandler != 0) moveCursor(messageHandler->line(), messageHandler->column());

    if (statusText.isNull()) {
        delete statusText;
        statusText = nullptr;
    }

    if (cancelBtn.isNull()) {
        delete cancelBtn;
        cancelBtn = nullptr;
    }

    if (overwriteBtn.isNull()) {
        delete overwriteBtn;
        overwriteBtn = nullptr;
    }

    if (jpkContent.isNull()) {
        delete jpkContent;
        jpkContent = nullptr;
    }

    if (jpkWindow.isNull())
        delete jpkWindow;

    }

}


void SaftfileOutput::inputTextFile(const QString content) {

   jpkContent.data()->setPlainText(content);

}


void SaftfileOutput::overwriteFile() {

    QFile outfile;
    outfile.setFileName(sett().getJPKDir() + "/" + QDate::currentDate().toString("yyyyMMdd") + allData.value("jpkFileArt"));
    outfile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&outfile);
    out << jpkContent->toPlainText() << endl;

    if (out.atEnd()) QMessageBox::information(this, "Nadpisywanie", "Operacja zakończona sukcesem");

    outfile.close();


}


void SaftfileOutput::textChanged()
{
    jpkContent.data()->setExtraSelections(QList<QTextEdit::ExtraSelection>());
}


void SaftfileOutput::moveCursor(int line, int column)
{
    jpkContent.data()->moveCursor(QTextCursor::Start);
    for (int i = 1; i < line; ++i)
        jpkContent.data()->moveCursor(QTextCursor::Down);

    for (int i = 1; i < column; ++i)
        jpkContent.data()->moveCursor(QTextCursor::Right);

    QList<QTextEdit::ExtraSelection> extraSelections;
    QTextEdit::ExtraSelection selection;

    const QColor lineColor = QColor(Qt::red).lighter(160);
    selection.format.setBackground(lineColor);
    selection.format.setProperty(QTextFormat::FullWidthSelection, true);
    selection.cursor = jpkContent.data()->textCursor();
    selection.cursor.clearSelection();
    extraSelections.append(selection);

    jpkContent.data()->setExtraSelections(extraSelections);

    jpkContent.data()->setFocus();
}


void SaftfileOutput::putOptIfNotEmpty(QXmlStreamWriter& writer, QString node, QString value) {

    if (!value.isEmpty() && !value.isNull())
        writer.writeTextElement(node, value);
}
