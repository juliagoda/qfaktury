
#include <QDateTime>
#include <QDir>
#include <QProcess>
#include <QApplication>
#include <QMessageBox>
#include <QTextCodec>
#include <QTextStream>
#include <QSpinBox>
#include <QDebug>
#include <QDateEdit>
#include <QPrinter>
#include <QPrintPreviewDialog>
#include <QPrintDialog>
#include <QTextDocument>
#include <QWebEnginePage>
#include <QWebEngineView>
#include <QStringListIterator>
#include <QMutableStringListIterator>
#include <QUrl>
#include <QLineEdit>
#include <QToolTip>
#include <QPushButton>
#include <QTextEdit>
#include <QComboBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include "Faktura.h"
#include "KontrahenciLista.h"
#include "TowaryLista.h"
#include "ZmienIlosc.h"
#include "CustomPayment.h"
#include "MainWindow.h"
#include "Kontrahenci.h"
#include "IDataLayer.h"
#include "Settings.h"

#include "Const.h"


short invType;
Faktura* Faktura::m_instance = nullptr;


/** Constructor
 */

Faktura::Faktura(QWidget *parent, IDataLayer *dl, QString Inv) :
    QDialog(parent), inv_form(Inv) {
    setupUi(this);

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;
    m_instance = this;
	dataLayer = dl;
    pforma = false;
	kAdded = false;
    konvEUR->setToolTip(trUtf8("Zamienia wartości liczbowe na fakturze na zaznaczone według aktualnego kursu walut, o ile się różni wyboru waluty z listy obok."));
    konvPLN->setToolTip(trUtf8("Zamienia wartości liczbowe na fakturze na zaznaczone według aktualnego kursu walut, o ile się różni wyboru waluty z listy obok."));
    konvUSD->setToolTip(trUtf8("Zamienia wartości liczbowe na fakturze na zaznaczone według aktualnego kursu walut, o ile się różni wyboru waluty z listy obok."));
    konvCHF->setToolTip(trUtf8("Zamienia wartości liczbowe na fakturze na zaznaczone według aktualnego kursu walut, o ile się różni wyboru waluty z listy obok."));
    konvGBP->setToolTip(trUtf8("Zamienia wartości liczbowe na fakturze na zaznaczone według aktualnego kursu walut, o ile się różni wyboru waluty z listy obok."));
    konvRUB->setToolTip(trUtf8("Zamienia wartości liczbowe na fakturze na zaznaczone według aktualnego kursu walut, o ile się różni wyboru waluty z listy obok."));

	init();
}

/** Destructor
 */

Faktura::~Faktura() {

    m_instance = nullptr;
    delete reply;
    delete manager;
    if (ratesCombo != 0) ratesCombo = 0;
    delete ratesCombo;
    if (labelRate != 0) labelRate = 0;
    delete labelRate;
    if (rateLabel != 0) rateLabel = 0;
    delete rateLabel;
    if (restLabel != 0) restLabel = 0;
    delete restLabel;
    if (sendKind != 0) sendKind = 0;
    delete sendKind;
    if (rateLabelInfo != 0) rateLabelInfo = 0;
    delete rateLabelInfo;
    if (restLabelInfo != 0) restLabelInfo = 0;
    delete restLabelInfo;
    if (sendKindInfo != 0) sendKindInfo = 0;
    delete sendKindInfo;

}

Faktura* Faktura::instance()
{
    return m_instance;
}


QString const Faktura::getRet() const
{
    return ret;
}


QString const Faktura::getfName() const
{
    return fName;
}


void Faktura::setfName(QString text)
{
    fName = text;
}


QString const Faktura::getInvForm() const
{
    return inv_form;
}


bool const Faktura::getKAdded() const
{
    return kAdded;
}


/** Init method
 */

void Faktura::init() {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;
    reply = 0;
    manager = 0;
    ratesCombo = new QComboBox();
    labelRate = 0;
    rateLabel = 0;
    restLabel = 0;
    sendKind = 0;
    rateLabelInfo = 0;
    restLabelInfo = 0;
    sendKindInfo = 0;
    rComboWasChanged = false;
    goodsEdited = false;

    this->setWindowTitle(inv_form);
    whatTypeFromTitle(s_PROFORMA, true, false, FPro, 2);
    whatTypeFromTitle(s_WIN_PROFORMA_EDIT, true, true, FPro, 2);
    whatTypeFromTitle(s_INVOICE, false, false, FVat, 1);
    whatTypeFromTitle(s_WIN_INVOICE_EDIT, false, true, FVat, 1);
    whatTypeFromTitle(s_CORRECT_TITLE, false, true, EFVat, 3);
    whatTypeFromTitle(s_WIN_CORRECT_EDIT, false, true, EFVat, 3);
    whatTypeFromTitle(s_FBRUTTO, false, false, EFPro, 4);
    whatTypeFromTitle(s_BR_INVOICE_EDIT, false, true, EFPro, 4);
    whatTypeFromTitle(s_CORRECT_BRUTTO, false, true, KBR, 5);
    whatTypeFromTitle(s_BILL, false, false, BILL, 6);
    whatTypeFromTitle(s_BILL_EDIT, false, true, BILL, 6);
    whatTypeFromTitle(s_DUPLICATE, false, true, DUP, 7);
    whatTypeFromTitle(s_WIN_DUPLICATE_LOOK, false, true, DUP, 7);

    if (sett().value("editSymbol").toBool()) frNr->setEnabled(false);
    else frNr->setEnabled(true);

	// set width of the columns on the products list
	sett().beginGroup("fakturaForm");

    tableTow->setColumnWidth(0, 100); //index
    tableTow->setColumnWidth(1, 100); // nazwa
    tableTow->setColumnWidth(2, 100); // kod
    tableTow->setColumnWidth(3, 100); // kod
    tableTow->setColumnWidth(4, 100); // ilosc
    tableTow->setColumnWidth(5, 100); // jm
    tableTow->setColumnWidth(6, 100); // rabat
    tableTow->setColumnWidth(7, 100); // cena jedn.
    tableTow->setColumnWidth(8, 100); // netto
    tableTow->setColumnWidth(9, 100); // vat
    tableTow->setColumnWidth(10, 100); // netto *  (wzor vat)

	sett().endGroup();

	// set all the dates to todays date -> could be logical date :)
	sellingDate->setDate(QDate::currentDate());
	productDate->setDate(QDate::currentDate());
	liabDate->setDate(QDate::currentDate());

	// connects
	connect(addTwBtn, SIGNAL(clicked()), this, SLOT(addTow()));
	connect(kListGet, SIGNAL(clicked()), this, SLOT(getCustomer()));
	connect(rmTowBtn, SIGNAL(clicked()), this, SLOT(delTowar()));
	connect(editTwBtn, SIGNAL(clicked()), this, SLOT(editTowar()));
	connect(backBtn, SIGNAL(clicked()), this, SLOT(backBtnClick()));
	connect(closeBtn, SIGNAL(clicked()), this, SLOT(canQuit()));
    connect(saveBtn, SIGNAL(clicked()), this, SLOT(saveInvoice()));
    connect(printBtn, SIGNAL(clicked()), this, SLOT(makeInvoice()));
	connect(tableTow, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(editTowar()));
    connect(tableTow, SIGNAL(itemActivated(QTableWidgetItem *)), this, SLOT(tableActivated(QTableWidgetItem *)));
    connect(tableTow, SIGNAL(itemClicked(QTableWidgetItem *)), this, SLOT(tableActivated(QTableWidgetItem *)));
    connect(additEdit, SIGNAL(textChanged(QString)), this, SLOT(textChanged(QString)));
    connect(platCombo, SIGNAL(currentIndexChanged (QString)), this, SLOT(payTextChanged(QString)));
    connect(currCombo, SIGNAL(currentIndexChanged (QString)), this, SLOT(textChanged(QString)));
    connect(sellingDate, SIGNAL(dateChanged (QDate)), this, SLOT(dateChanged (QDate)));
    connect(productDate, SIGNAL(dateChanged (QDate)), this, SLOT(dateChanged (QDate)));
    connect(liabDate, SIGNAL(dateChanged (QDate)), this, SLOT(dateChanged (QDate)));
	connect(rabatValue, SIGNAL(valueChanged(int)), this, SLOT(discountChange()));
	connect(constRab, SIGNAL(stateChanged(int)), this, SLOT(discountConstChange()));
	connect(addKButton, SIGNAL(clicked()), this, SLOT(kontrClick()));
    connect(konvUSD, SIGNAL(clicked()), this, SLOT(changeToUSD()));
    connect(konvEUR, SIGNAL(clicked()), this, SLOT(changeToEUR()));
    connect(konvPLN, SIGNAL(clicked()), this, SLOT(changeToPLN()));
    connect(konvCHF, SIGNAL(clicked()), this, SLOT(changeToCHF()));
    connect(konvGBP, SIGNAL(clicked()), this, SLOT(changeToGBP()));
    connect(konvRUB, SIGNAL(clicked()), this, SLOT(changeToRUB()));
    connect(ratesCombo, SIGNAL(currentIndexChanged (QString)), this, SLOT(rateDateChanged(QString)));


	// Calulcate next number of the invoice
	QString tmp;
	if (pforma) {
		tmp = sett().value("fpro").toString();
		invoiceType = s_PROFORMA;
	} else {
		tmp = sett().value("fvat").toString();
		invoiceType = s_INVOICE;
	}

	// load payments method and currencies
	platCombo->insertItems(0, sett().value("payments").toString().split("|"));
	currCombo->insertItems(0, sett().value("waluty").toString().split("|"));

	if (sett().value ("addText").toString().compare("") != 0 )
		additEdit->setText(sett().value("addText").toString());

	backBtnClick();

	// set window icon
	QIcon icon;
	icon.addPixmap(QPixmap(":/res/icons/nowa_faktura.png"),
			QIcon::Normal, QIcon::Off);
	this->setWindowIcon(icon);

	rmTowBtn->setEnabled(false);
	editTwBtn->setEnabled(false);
	liabDate->setEnabled(false);
	rabatValue->setEnabled(false);

	canClose = true;
}


void Faktura::whatTypeFromTitle(QString title, bool ifForm, bool kadded, InvoiceType invTyp, int numbType)
{
    if (inv_form == title) {

        pforma = ifForm;
        kAdded = kadded;
        invType = invTyp;
        type = numbType;
    }
}

/**
 *  Return invoice type
 */

QString Faktura::getInvoiceTypeAndSaveNr() {

         qDebug() << __FUNCTION__ << __LINE__ << __FILE__;

        ret = QString();

        if (inv_form == s_INVOICE) {
                ret = "FVAT";
                sett().setValue("fvat", frNr->text());
        } else if (inv_form == s_PROFORMA) {
                ret = "FPro";
                sett().setValue("fpro", frNr->text());
        } else if (inv_form == s_CORRECT_TITLE) {
                ret = trUtf8("korekta");
                sett().setValue("pkorekty", frNr->text());
        } else if (inv_form == s_DUPLICATE) {
                ret = trUtf8("duplikat");
                sett().setValue("dup", frNr->text());
        }

        return ret;
}

void Faktura::connectedWebsite(const QUrl& webExchRate) {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

    manager = new QNetworkAccessManager(this);

       // get url
       QUrl url = QUrl::fromEncoded(webExchRate.toEncoded());

       QFileInfo fileInfo(url.path());
       QString fileName = fileInfo.fileName();

       if (fileName.isEmpty())
           fileName = sett().getInvoicesDir() + "bureau.xml";

       if (file.exists()) {
           qDebug("Plik istnieje");
           if (QFile::remove(fileName)) qDebug("Plik usunięto");
       }

       file.setFileName(fileName);


       if (!file.open(QIODevice::WriteOnly)) {
           QMessageBox::information(this, tr("HTTP"),
                         tr("Unable to save the file %1: %2.")
                         .arg(fileName).arg(file.errorString()));
           return;
       }


       reply = manager->get(QNetworkRequest(url));

       connect(reply, SIGNAL(readyRead()),
                   this, SLOT(httpReadyRead()));

       connect(reply, SIGNAL(finished()),
                   this, SLOT(tellFinished()));

}

void Faktura::httpReadyRead()
{
    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

    if (file.exists()) {
        file.write(reply->readAll());
    }

}

void Faktura::tellFinished()
{
    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

    if (file.open(QIODevice::ReadOnly)) {

        if (!doc.setContent(&file)) {

          qDebug("You can't set content to correction xml");

        }
        sett().setValue("lastUpdateCur", doc.elementsByTagName(QString("lastBuildDate")).at(0).toElement().text());

    }


        qDebug("Finished");

        QMap<QString, double> list;
        QMap<QString, double> table;

         list = getActualCurList();
         table = tableOfValues();


         if (checkInvCurr() != pressedTxt()) {

             QMap<QString, double>::const_iterator i = table.constBegin();
             while (i != table.constEnd()) {

                 QString first = i.key().split("/").at(0);
                 QString second = i.key().split("/").at(1);

                 if (first == currCombo->currentText() && second == pressedText) {
                     calcAll(i.value());
                     break;
                 }

                 ++i;
             }


         } else {

             QMessageBox::information(this,trUtf8("Wartości walut"),trUtf8("Wartości konwertowane nie mogą być sobie równe. Ustaw różne nazwy walut."));
         }

         currCombo->setCurrentText(pressedTxt());

         file.close();

}


QMap<QString,double> Faktura::getActualCurList() {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

    QMap<QString,double> currencies;

   if (file.open(QIODevice::ReadOnly)) {

       if (!doc.setContent(&file)) {

         qDebug("You can't set content to correction xml");

       }

       QDomNodeList items = doc.elementsByTagName(QString("item"));
       qDebug() << "Ile itemów w pliku: " << items.count();

       for (int i = 0; i < items.size(); i++) {

                QDomElement titleNode = items.at(i).firstChild().toElement();
                qDebug() << "Pierwsze dziecko itemów w pliku: " << titleNode.text();
                QString titleText = titleNode.text().simplified();
                QString noSpaces = titleText.replace(" ","");
                QStringList splitted = noSpaces.remove(0,1).split("-");
                QString val_one = splitted.at(0);
                val_one = val_one.remove( QRegExp("[0-9]*") );
                qDebug() << "Wartości pierwsze tytułów: " << val_one;
                QString val_two = splitted.at(1);
                qDebug() << "Wartości drugie tytułów: " << val_two;
                double val_two_fl = val_two.toDouble();
                if (!currencies.contains(val_one))
                currencies.insert(val_one, val_two_fl);

         }
        }

    if (currencies.isEmpty()) currencies.insert("nothing",0.0);

    file.close();
    return currencies;

}


QMap<QString,double> Faktura::tableOfValues() {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

    QMap<QString,double> currencies;

    if (currencies.isEmpty()) {

        double eurToPln = getActualCurList().value("EUR");
        double usdToPln = getActualCurList().value("USD");
        double chfToPln = getActualCurList().value("CHF");
        double gbpToPln = getActualCurList().value("GBP");
        double rubToPln = getActualCurList().value("RUB");

        double plnToEur = 1/eurToPln;
        double plnToChf = 1/chfToPln;
        double plnToGbp = 1/gbpToPln;
        double plnToRub = 1/rubToPln;
        double plnToUsd = 1/usdToPln;

        double eurToUsd = eurToPln/usdToPln;
        double eurToChf = eurToPln/chfToPln;
        double eurToGbp = eurToPln/gbpToPln;
        double eurToRub = eurToPln/rubToPln;

        double usdToEur = usdToPln/eurToPln;
        double usdToChf = usdToPln/chfToPln;
        double usdToGbp = usdToPln/gbpToPln;
        double usdToRub = usdToPln/rubToPln;

        double chfToEur = chfToPln/eurToPln;
        double chfToUsd = chfToPln/usdToPln;
        double chfToGbp = chfToPln/gbpToPln;
        double chfToRub = chfToPln/rubToPln;

        double gbpToEur = gbpToPln/eurToPln;
        double gbpToUsd = gbpToPln/usdToPln;
        double gbpToChf = gbpToPln/chfToPln;
        double gbpToRub = gbpToPln/rubToPln;

        double rubToEur = rubToPln/eurToPln;
        double rubToUsd = rubToPln/usdToPln;
        double rubToGbp = rubToPln/gbpToPln;
        double rubToChf = rubToPln/chfToPln;


        currencies.insert("EUR/PLN",eurToPln);
        currencies.insert("USD/PLN",usdToPln);
        currencies.insert("CHF/PLN",chfToPln);
        currencies.insert("GBP/PLN",gbpToPln);
        currencies.insert("RUB/PLN",rubToPln);

        currencies.insert("PLN/EUR",plnToEur);
        currencies.insert("PLN/USD",plnToUsd);
        currencies.insert("PLN/CHF",plnToChf);
        currencies.insert("PLN/GBP",plnToGbp);
        currencies.insert("PLN/RUB",plnToRub);

        currencies.insert("EUR/USD",eurToUsd);
        currencies.insert("EUR/CHF",eurToChf);
        currencies.insert("EUR/GBP",eurToGbp);
        currencies.insert("EUR/RUB",eurToRub);

        currencies.insert("USD/EUR",usdToEur);
        currencies.insert("USD/CHF",usdToChf);
        currencies.insert("USD/GBP",usdToGbp);
        currencies.insert("USD/RUB",usdToRub);

        currencies.insert("CHF/EUR",chfToEur);
        currencies.insert("CHF/USD",chfToUsd);
        currencies.insert("CHF/GBP",chfToGbp);
        currencies.insert("CHF/RUB",chfToRub);

        currencies.insert("GBP/EUR",gbpToEur);
        currencies.insert("GBP/USD",gbpToUsd);
        currencies.insert("GBP/CHF",gbpToChf);
        currencies.insert("GBP/RUB",gbpToRub);

        currencies.insert("RUB/EUR",rubToEur);
        currencies.insert("RUB/USD",rubToUsd);
        currencies.insert("RUB/CHF",rubToChf);
        currencies.insert("RUB/GBP",rubToGbp);

    }

    return currencies;

}

bool Faktura::ifUpdated()
{
    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

   if (!file.open(QIODevice::ReadOnly)) {

        qDebug("file doesn't exist");
        return false;

    } else {

           if (!doc.setContent(&file)) {

             qDebug("You can't set content to correction xml");
             return true;

           }

           QMap<QString,int> helpMonths;
           helpMonths.insert("Jan",1);
           helpMonths.insert("Feb",2);
           helpMonths.insert("Mar",3);
           helpMonths.insert("Apr",4);
           helpMonths.insert("May",5);
           helpMonths.insert("Jun",6);
           helpMonths.insert("Jul",7);
           helpMonths.insert("Aug",8);
           helpMonths.insert("Sep",9);
           helpMonths.insert("Oct",10);
           helpMonths.insert("Nov",11);
           helpMonths.insert("Dec",12);


        QDomNodeList lastUpdate = doc.elementsByTagName(QString("lastBuildDate"));
        QStringList dateElements = lastUpdate.at(0).toElement().text().replace(","," ").split(" ");
        dateElements.removeLast();
        QString hours = dateElements.last();
        QStringList hms = hours.split(":");
        QDateTime dateNow = QDateTime::currentDateTime();

        QString year = dateElements.at(3);
        qDebug() << "Rok: " << year;
        QString day = dateElements.at(1);
        qDebug() << "Miesiąc: " << helpMonths.value(dateElements.at(2));
        qDebug() << "Dzień: " << day;
        QString hour = hms.at(0);
        qDebug() << "Godz: " << hour;
        QString min = hms.at(1);
        qDebug() << "Min: " << min;
        QString sec = hms.at(2);
        qDebug() << "Sec: " << sec;

        // Wed,30 Nov 2016 16:51:40

        QDateTime dateOfFile(QDate(year.toInt(), helpMonths.value(dateElements.at(2)), day.toInt()), QTime(hour.toInt(), min.toInt(), sec.toInt()));

        qDebug() << "data pliku: " << dateOfFile.toString();
        qDebug() << "data obecna: " << dateNow.toString();
        qDebug() << "Minęło: " << dateOfFile.secsTo(dateNow);

        if (dateOfFile.secsTo(dateNow) > 1800)
            return true;
        else
            return false;

    }

   file.close();

}


QString Faktura::checkInvCurr() {

    return currCombo->currentText().trimmed();
}


// ---- SLOTS START  --//////////////////////////////////////////////////////////////////////////////////

void Faktura::changeToEUR() {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

    file.setFileName(sett().getInvoicesDir() + "bureau.xml");
    pressedText = konvEUR->text().trimmed();


   if (!file.exists()) {

       QUrl web = QUrl::fromEncoded("http://waluty.com.pl/rss/?mode=kursy");
       connectedWebsite(web);

   } else {

       if (ifUpdated()) {

           QUrl web = QUrl::fromEncoded("http://waluty.com.pl/rss/?mode=kursy");
           connectedWebsite(web);

       } else {


           QMap<QString, double> list;
           QMap<QString, double> table;

            list = getActualCurList();
            table = tableOfValues();


            if (checkInvCurr() != pressedTxt()) {

                QMap<QString, double>::const_iterator i = table.constBegin();
                while (i != table.constEnd()) {

                    QString first = i.key().split("/").at(0);
                    QString second = i.key().split("/").at(1);
                    if (first == currCombo->currentText() && second == pressedText) {
                        calcAll(i.value());
                        break;
                    }

                    ++i;
                }
       } else {

                QMessageBox::information(this,trUtf8("Wartości walut"),trUtf8("Wartości konwertowane nie mogą być sobie równe. Ustaw różne nazwy walut."));
            }

            currCombo->setCurrentText(pressedTxt());
        }
    }

   QApplication::restoreOverrideCursor();
}

void Faktura::changeToUSD() {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

   file.setFileName(sett().getInvoicesDir() + "bureau.xml");
    pressedText = konvUSD->text().trimmed();
    qDebug() << "Konwertowane na " << pressedText;
    qDebug() << "Konwertowane na " << pressedTxt();

   if (!file.exists()) {

       QUrl web = QUrl::fromEncoded("http://waluty.com.pl/rss/?mode=kursy");
       connectedWebsite(web);

   } else {

       if (ifUpdated()) {

           QUrl web = QUrl::fromEncoded("http://waluty.com.pl/rss/?mode=kursy");
           connectedWebsite(web);

       } else {

           QMap<QString, double> list;
           QMap<QString, double> table;

            list = getActualCurList();
            table = tableOfValues();


            if (checkInvCurr() != pressedTxt()) {

                QMap<QString, double>::const_iterator i = table.constBegin();
                while (i != table.constEnd()) {

                    QString first = i.key().split("/").at(0);
                    QString second = i.key().split("/").at(1);

                    if (first == currCombo->currentText() && second == pressedTxt()) {
                        calcAll(i.value());
                        break;
                    }

                    ++i;
                }
       } else {

                QMessageBox::information(this,trUtf8("Wartości walut"),trUtf8("Wartości konwertowane nie mogą być sobie równe. Ustaw różne nazwy walut."));
            }

            currCombo->setCurrentText(pressedTxt());
        }
    }

   QApplication::restoreOverrideCursor();
}

void Faktura::changeToPLN() {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

    file.setFileName(sett().getInvoicesDir() + "bureau.xml");
    pressedText = konvPLN->text().replace("&","").trimmed();

   if (!file.exists()) {

       QUrl web = QUrl::fromEncoded("http://waluty.com.pl/rss/?mode=kursy");
       connectedWebsite(web);

   } else {

       if (ifUpdated()) {

           QUrl web = QUrl::fromEncoded("http://waluty.com.pl/rss/?mode=kursy");
           connectedWebsite(web);

       } else {

           QMap<QString, double> list;
           QMap<QString, double> table;

            list = getActualCurList();
            table = tableOfValues();


            if (checkInvCurr() != pressedTxt()) {

                QMap<QString, double>::const_iterator i = table.constBegin();
                while (i != table.constEnd()) {

                    QString first = i.key().split("/").at(0);
                    QString second = i.key().split("/").at(1);

                    if (first == currCombo->currentText() && second == pressedText) {
                        qDebug() << "first: " << first << " == " << "currComboText: " << currCombo->currentText() << " && " << "second: " << second << " == " << "pressedText: " << pressedTxt();
                        calcAll(i.value());
                        break;
                    }

                    ++i;
                }
       } else {

                QMessageBox::information(this,trUtf8("Wartości walut"),trUtf8("Wartości konwertowane nie mogą być sobie równe. Ustaw różne nazwy walut."));
            }

            currCombo->setCurrentText(pressedTxt());
        }
    }

   QApplication::restoreOverrideCursor();
}


void Faktura::changeToCHF() {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

    file.setFileName(sett().getInvoicesDir() + "bureau.xml");
    pressedText = konvCHF->text().replace("&","").trimmed();

   if (!file.exists()) {

       QUrl web = QUrl::fromEncoded("http://waluty.com.pl/rss/?mode=kursy");
       connectedWebsite(web);

   } else {

       if (ifUpdated()) {

           QUrl web = QUrl::fromEncoded("http://waluty.com.pl/rss/?mode=kursy");
           connectedWebsite(web);

       } else {

           QMap<QString, double> list;
           QMap<QString, double> table;

            list = getActualCurList();
            table = tableOfValues();


            if (checkInvCurr() != pressedTxt()) {

                QMap<QString, double>::const_iterator i = table.constBegin();
                while (i != table.constEnd()) {

                    QString first = i.key().split("/").at(0);
                    QString second = i.key().split("/").at(1);

                    if (first == currCombo->currentText() && second == pressedText) {
                        qDebug() << "first: " << first << " == " << "currComboText: " << currCombo->currentText() << " && " << "second: " << second << " == " << "pressedText: " << pressedTxt();
                        calcAll(i.value());
                        break;
                    }

                    ++i;
                }
       } else {

                QMessageBox::information(this,trUtf8("Wartości walut"),trUtf8("Wartości konwertowane nie mogą być sobie równe. Ustaw różne nazwy walut."));
            }

            currCombo->setCurrentText(pressedTxt());
        }
    }

   QApplication::restoreOverrideCursor();
}


void Faktura::changeToGBP() {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

    file.setFileName(sett().getInvoicesDir() + "bureau.xml");
    pressedText = konvGBP->text().replace("&","").trimmed();

   if (!file.exists()) {

       QUrl web = QUrl::fromEncoded("http://waluty.com.pl/rss/?mode=kursy");
       connectedWebsite(web);

   } else {

       if (ifUpdated()) {

           QUrl web = QUrl::fromEncoded("http://waluty.com.pl/rss/?mode=kursy");
           connectedWebsite(web);

       } else {

           QMap<QString, double> list;
           QMap<QString, double> table;

            list = getActualCurList();
            table = tableOfValues();


            if (checkInvCurr() != pressedTxt()) {

                QMap<QString, double>::const_iterator i = table.constBegin();
                while (i != table.constEnd()) {

                    QString first = i.key().split("/").at(0);
                    QString second = i.key().split("/").at(1);

                    if (first == currCombo->currentText() && second == pressedText) {
                        qDebug() << "first: " << first << " == " << "currComboText: " << currCombo->currentText() << " && " << "second: " << second << " == " << "pressedText: " << pressedTxt();
                        calcAll(i.value());
                        break;
                    }

                    ++i;
                }
       } else {

                QMessageBox::information(this,trUtf8("Wartości walut"),trUtf8("Wartości konwertowane nie mogą być sobie równe. Ustaw różne nazwy walut."));
            }

            currCombo->setCurrentText(pressedTxt());
        }
    }

   QApplication::restoreOverrideCursor();
}


void Faktura::changeToRUB() {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

    file.setFileName(sett().getInvoicesDir() + "bureau.xml");
    pressedText = konvRUB->text().replace("&","").trimmed();

   if (!file.exists()) {

       QUrl web = QUrl::fromEncoded("http://waluty.com.pl/rss/?mode=kursy");
       connectedWebsite(web);

   } else {

       if (ifUpdated()) {

           QUrl web = QUrl::fromEncoded("http://waluty.com.pl/rss/?mode=kursy");
           connectedWebsite(web);

       } else {

           QMap<QString, double> list;
           QMap<QString, double> table;

            list = getActualCurList();
            table = tableOfValues();


            if (checkInvCurr() != pressedTxt()) {

                QMap<QString, double>::const_iterator i = table.constBegin();
                while (i != table.constEnd()) {

                    QString first = i.key().split("/").at(0);
                    QString second = i.key().split("/").at(1);

                    if (first == currCombo->currentText() && second == pressedText) {
                        qDebug() << "first: " << first << " == " << "currComboText: " << currCombo->currentText() << " && " << "second: " << second << " == " << "pressedText: " << pressedTxt();
                        calcAll(i.value());
                        break;
                    }

                    ++i;
                }
       } else {

                QMessageBox::information(this,trUtf8("Wartości walut"),trUtf8("Wartości konwertowane nie mogą być sobie równe. Ustaw różne nazwy walut."));
            }

            currCombo->setCurrentText(pressedTxt());
        }
    }

   QApplication::restoreOverrideCursor();
}

QString Faktura::pressedTxt() const
{
    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

    return pressedText;
}

void Faktura::calcAll(const double& currVal)
{
    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

    double res1 = sett().stringToDouble(sum1->text()) * currVal;
    double res2 = sett().stringToDouble(sum2->text()) * currVal;
    double res3 = sett().stringToDouble(sum3->text()) * currVal;

    sum1->setText(sett().numberToString(res1,'f',2));
    sum2->setText(sett().numberToString(res2,'f',2l));
    sum3->setText(sett().numberToString(res3,'f',2));


    if (tableTow->rowCount() != 0) {

        for (int i = 0; i < tableTow->rowCount(); i++) {

            double it2 = sett().stringToDouble(tableTow->item(i,7)->text()) * currVal;
            tableTow->item(i,7)->setText(sett().numberToString(it2,'f',2));
            double it3 = sett().stringToDouble(tableTow->item(i,8)->text()) * currVal;
            tableTow->item(i,8)->setText(sett().numberToString(it3,'f',2));
            double it4 = sett().stringToDouble(tableTow->item(i,10)->text()) * currVal;
            tableTow->item(i,10)->setText(sett().numberToString(it4,'f',2));
        }
    }

    if (platCombo->currentText() == trUtf8("zaliczka")) {
        if (ratesCombo->currentIndex() == 0) {

            double retLabInfo = sett().stringToDouble(rateLabelInfo->text()) * currVal;
            rateLabelInfo->setText(sett().numberToString(retLabInfo,'f',2));

            double resLabInfo = sett().stringToDouble(restLabelInfo->text()) * currVal;
            restLabelInfo->setText(sett().numberToString(resLabInfo,'f',2));

            am1 = retLabInfo;
            am2 = resLabInfo;

            if (rComboWasChanged) {
                custPaymData->amount1 = am1;
                custPaymData->amount2 = am2;
            }


        }

    if (ratesCombo->currentIndex() == 1) {

            double retLabInfo = sett().stringToDouble(rateLabelInfo->text()) * currVal;
            rateLabelInfo->setText(sett().numberToString(retLabInfo,'f',2));

            restLabelInfo->setText(sett().numberToString(0.0));

            am1 = sett().stringToDouble(sum3->text()) - retLabInfo;
            am2 = retLabInfo;

            if (rComboWasChanged) {
                custPaymData->amount1 = am1;
                custPaymData->amount2 = am2;
            }


        }
    }

    goodsEdited = true;
    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  << "EXIT";

}

void Faktura::kontrClick() {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

	Kontrahenci *kontrWindow;
	kontrWindow = new Kontrahenci(this, 0, dataLayer);
    qDebug ("%s %s:%d", __FUNCTION__, __FILE__, __LINE__);

    if (kontrWindow->exec() == QDialog::Accepted) {

		kAdded = true;
        QStringList row = kontrWindow->getRetKontr().split("|");
        kontrName->setText (row[0] + "," + row[3] + "," + row[6] + " " + row[2] + "," +  s_TIC + row[5] + "," + row[7] + "," + row[8] + "," + row[9] + "," + row[10]);
		kontrName->setCursorPosition(0);
    }

	delete kontrWindow;
	kontrWindow = NULL;
}

void Faktura::keyPressEvent(QKeyEvent * event) {

     qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

	if (event->key() == Qt::Key_Escape) {
		canQuit();
    }

}

/** Slot getCustomer
 *  Opens window with the list of the customers
 */

void Faktura::getCustomer () {

  qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

  KontrahenciLista *klWindow = new KontrahenciLista(this);

  if (klWindow->exec () == QDialog::Accepted)
    {
      kontrName->setText (klWindow->getRetKontrList());
      kontrName->setCursorPosition (1);
      saveBtn->setEnabled(true);
      canClose = false;
    }

  delete klWindow;
  klWindow = NULL;
}

/** Slot
 *  Enables and disables rebatValue field
 */

void Faktura::discountConstChange(){

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

    if (constRab->isChecked()) {

		rabatValue->setEnabled(true);
		saveBtn->setEnabled(true);
		calculateDiscount();
        calculateSum();

    } else {

		rabatValue->setValue(0);
		rabatValue->setEnabled(false);
	}
}

/** Slot discountChange
 *  Used to recalculate discount when spinBox arrows are pressed.
 */

void Faktura::discountChange() {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;



	calculateDiscount();

    if (platCombo->currentText() == trUtf8("zaliczka")) {

        if ((am1 + am2) != sett().stringToDouble(sum3->text())) {
            payTextChanged(trUtf8("zaliczka"));
        }

    }

	calculateSum();

	saveBtn->setEnabled(true);
	canClose = false;
}

/** Slot addTow
 *  Shows window with a list of products
 */

void Faktura::addTow() {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

    TowaryLista *twWindow = new TowaryLista(this);
    if (twWindow->exec() == QDialog::Accepted) {

		MainWindow::insertRow(tableTow, tableTow->rowCount());
        QStringList row = twWindow->getRetVal().split("|");
        int rowNum = tableTow->rowCount() - 1;
        tableTow->item(rowNum, 0)->setText(sett().numberToString(
                tableTow->rowCount())); // id
        tableTow->item(rowNum, 1)->setText(row[0]); // name
        tableTow->item(rowNum, 2)->setText(row[1]); // code
        tableTow->item(rowNum, 3)->setText(row[2]); // pkwiu
        tableTow->item(rowNum, 4)->setText(row[3]); // quantity
        tableTow->item(rowNum, 5)->setText(row[4]); // qType
        tableTow->item(rowNum, 6)->setText(row[5]); // discount
        tableTow->item(rowNum, 7)->setText(row[6]); // price
        tableTow->item(rowNum, 8)->setText(row[7]); // nett
        tableTow->item(rowNum, 9)->setText(row[8]); // vat
        tableTow->item(rowNum, 10)->setText(row[9]); // gross

		saveBtn->setEnabled(true);
        canClose = false;
        if (constRab->isChecked())
            calculateDiscount();

        calculateSum();
    }

	delete twWindow;
	twWindow = NULL;

    if (platCombo->currentText() == trUtf8("zaliczka")) {

        if ((am1 + am2) != sett().stringToDouble(sum3->text())) {
            payTextChanged(trUtf8("zaliczka"));
        }

    }
}

/** Slot delTowar
 *  Remove the product from the list
 */
void Faktura::delTowar() {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;
    tableTow->removeRow(tableTow->currentRow());
    for (int i = 0; i < tableTow->rowCount(); ++i) {
        tableTow->item(i, 0)->setText(sett().numberToString(i + 1));
    }

    if (tableTow->rowCount() == 0) {
    platCombo->setCurrentIndex(0);
    }

	calculateSum();
	saveBtn->setEnabled(true);
	canClose = false;
}

/** Slot editTowar
 *  Allows to edit selected product. Opens changeAmount window.
 */
void Faktura::editTowar() {
     qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;
	// we can only modify quantity

    goodsEdited = true;
    int cur = tableTow->currentRow();
    if (cur >= 0) {
    ZmienIlosc *changeQuant = new ZmienIlosc(this);

    changeQuant->nameTow->setText(
            tableTow-> item(tableTow->currentRow(), 1)->text());

    changeQuant->codeTow->setText(
            tableTow-> item(tableTow->currentRow(), 2)->text());
    changeQuant->spinAmount->setValue(tableTow-> item(tableTow->currentRow(),
            4)->text().toInt());

    if (changeQuant->exec() == QDialog::Accepted) {
        int currentRow = tableTow->currentRow();
        tableTow->item(currentRow, 4)->setText(changeQuant->spinAmount->cleanText());


        saveBtn->setEnabled(true);
        canClose = false;
        calculateOneDiscount(currentRow);
        calculateSum();
    }

    delete changeQuant;
    changeQuant = NULL;

    } else if (tableTow->rowCount() == 0) {

        QMessageBox msgBox;
        msgBox.setText(trUtf8("Nie ma na liście żadnych towarów, które można by było edytować. Kliknij na przycisk \"Dodaj\" i wybierz towar lub usługę z listy"));
        msgBox.setInformativeText(trUtf8("Chcesz potwierdzić by dokonać zmiany, czy anulować, by wyjść do głównego okna?"));
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Ok);
        int ret = msgBox.exec();

        switch (ret) {
          case QMessageBox::Ok:

              break;

          case QMessageBox::Cancel:
              reject();
              break;
        }

    } else {

        QMessageBox msgBox;
        msgBox.setText(trUtf8("Musisz zaznaczyć towar, który chcesz edytować, klikając na określony rząd w tabeli"));
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();

    }

    if (platCombo->currentText() == trUtf8("zaliczka")) {

        if ((am1 + am2) != sett().stringToDouble(sum3->text())) {
            payTextChanged(trUtf8("zaliczka"));
        }

    }
     qDebug() << __FUNCTION__ << ": EXIT";
}

/** Slot
 *  Used populate invoice symbol
 */
void Faktura::backBtnClick() {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;
    QString tmp;

    QString prefix, suffix;

    if (pforma) {

        tmp = sett().value("fpro").toString();
    } else {
        tmp = sett().value("fvat").toString();
    }
	prefix = sett().value("prefix").toString();

	QStringList one1 = tmp.split("/");
	one1[0] = one1[0].remove(prefix);

	int nr = one1[0].toInt() + 1;
	lastInvoice = prefix + numbersCount(nr,
			sett().value("chars_in_symbol").toInt());

    if (sett().value("day") .toBool())
		lastInvoice += "/" + QDate::currentDate().toString("dd");

    if (sett().value("month") .toBool())
		lastInvoice += "/" + QDate::currentDate().toString("MM");

    if (sett().value("year") .toBool()) {
        if (!sett().value("shortYear") .toBool())
            lastInvoice += "/" + QDate::currentDate().toString("yy");
        else
            lastInvoice += "/" + QDate::currentDate().toString("yyyy");
    }
	suffix = sett().value("sufix").toString();
	lastInvoice += suffix;
	frNr->setText(lastInvoice);
	saveBtn->setEnabled(true);
}

/** Slot
 *  Validate close and save if requested
 */
void Faktura::canQuit() {
     qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__ << ": canClose " << canClose;

    if (canClose) {

        if (ret.isNull()) reject();
        else accept();

    } else {

        if (QMessageBox::warning(this, "QFaktury", trUtf8("Dane zostały zmienione czy chcesz zapisać?"),
                    trUtf8("Tak"), trUtf8("Nie"), 0, 0,	1) == 1) {
            saveColumnsWidth();
            reject();

        } else {

            saveInvoice();
            if (saveFailed) {
                return;
            }
            saveColumnsWidth();
            accept();
        }
    }
}

/** Slot tableActivated
 *  Enable/Disable buttons
 */
void Faktura::tableActivated(QTableWidgetItem * item) {
     qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;
    if (item != NULL || !item->text().isEmpty()) {
		rmTowBtn->setEnabled(true);
		editTwBtn->setEnabled(true);
	}
}

/** Slot payTextChanged
 *  Activates buttons
 */
void Faktura::payTextChanged(QString text) {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;
     qDebug() << __FUNCTION__ <<  platCombo->currentIndex();


    if (text != trUtf8("zaliczka"))
    {
        if (restLabel != 0 && rateLabelInfo != 0) {

            rComboWasChanged = false;
            disconnect(ratesCombo, SIGNAL(currentIndexChanged (QString)), this, SLOT(rateDateChanged(QString)));

            ratesCombo->deleteLater();
            ratesCombo = 0;
            labelRate->deleteLater();
            labelRate = 0;

            rateLabel->deleteLater();
            rateLabel = 0;
            restLabel->deleteLater();
            restLabel = 0;
            sendKind->deleteLater();
            sendKind = 0;

            rateLabelInfo->deleteLater();
            rateLabelInfo = 0;
            restLabelInfo->deleteLater();
            restLabelInfo = 0;
            sendKindInfo->deleteLater();
            sendKindInfo = 0;

        }

        if (text == trUtf8("gotówka")) {

            liabDate->setEnabled(false);
        }

        if (text == trUtf8("przelew")) {

            liabDate->setEnabled(true);
        }

    } else {

        CustomPayment *cp = new CustomPayment(this);
        double decimalPointsAmount = sum3->text().right(2).toInt() * 0.01;

        cp->setInvoiceAmount(sett().stringToDouble(sum3->text()) + decimalPointsAmount);
        if (cp->exec() ==  QDialog::Accepted) {

            custPaymData = 0;
            custPaymData = cp->custPaymData;

            rComboWasChanged = true;
            disconnect(ratesCombo, SIGNAL(currentIndexChanged (QString)), this, SLOT(rateDateChanged(QString)));


            if (ratesCombo == 0) ratesCombo = new QComboBox();

            if (labelRate == 0) labelRate = new QLabel();
            labelRate->setText(trUtf8("Termin raty:"));
            labelRate->setAlignment(Qt::AlignRight);
            addDataLabels->addWidget(labelRate);

            ratesCombo->addItem(custPaymData->date1.toString(sett().getDateFormat()));
            ratesCombo->addItem(custPaymData->date2.toString(sett().getDateFormat()));
            ratesCombo->setCurrentText(custPaymData->date1.toString(sett().getDateFormat()));
            addData->addWidget(ratesCombo);

            if (rateLabel == 0) rateLabel = new QLabel();
            rateLabel->setText(trUtf8("Rata:"));
            rateLabel->setAlignment(Qt::AlignRight);
            descPayments->addWidget(rateLabel);

            if (sendKind == 0) sendKind = new QLabel();
            sendKind->setText(trUtf8("Rodzaj zapłaty:"));
            sendKind->setAlignment(Qt::AlignRight);
            descPayments->addWidget(sendKind);

            if (restLabel == 0) restLabel = new QLabel();
            restLabel->setText(trUtf8("Pozostało do spłaty:"));
            restLabel->setAlignment(Qt::AlignRight);
            descPayments->addWidget(restLabel);

            if (rateLabelInfo == 0) rateLabelInfo = new QLabel();
            rateLabelInfo->setText(sett().numberToString(custPaymData->amount1,'f',2));
            dataPayments->addWidget(rateLabelInfo);

            if (sendKindInfo == 0) sendKindInfo = new QLabel();
            sendKindInfo->setText(custPaymData->payment1);
            dataPayments->addWidget(sendKindInfo);

            if (restLabelInfo == 0) restLabelInfo = new QLabel();
            restLabelInfo->setText(sett().numberToString(custPaymData->amount2,'f',2));
            dataPayments->addWidget(restLabelInfo);

            am1 = custPaymData->amount1;
            am2 = custPaymData->amount2;

            connect(ratesCombo, SIGNAL(currentIndexChanged (QString)), this, SLOT(rateDateChanged(QString)));

            liabDate->setEnabled(false);

        } else {

            platCombo->setCurrentIndex(0);
        }

        delete cp;
        cp = NULL;

    }

    textChanged(text);
    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  << "EXIT";

}

/** Slot textChanged
 *  Activates buttons
 */

void Faktura::textChanged(QString) {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;
    saveBtn->setEnabled(true);
	canClose = false;

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  << "EXIT";

}

/** Slot dateChanged
 *  Activates buttons
 */

void Faktura::dateChanged(QDate) {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

    if (productDate->date() < sellingDate->date()) {

        QMessageBox::information(this,trUtf8("Błędne ustawienie daty"), trUtf8("Data wystawienia faktury nie może być wcześniejsza od daty sprzedaży towaru lub wykonania usługi"));
        productDate->setDate(sellingDate->date());

    } else {

        saveBtn->setEnabled(true);
        canClose = false;
    }

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  << "EXIT";

}


void Faktura::rateDateChanged(QString date)
{
    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

    if (!rComboWasChanged) {

    qDebug() << "Zaznaczona data raty: " << date;
    QDomDocument doc(sett().getInoiveDocName());
    QDomElement root;
    qDebug() << "prepayFile w rateDateChanged: " << prepayFile;
    QFile file(sett().getInvoicesDir() + prepayFile);

    if (!file.open(QIODevice::ReadOnly)) {

        qDebug() << "file doesn't exist: " << file.fileName();

    } else {

        QTextStream stream(&file);
        if (!doc.setContent(stream.readAll())) {
            qDebug("You can't read content from invoice");
            file.close();

        }
    }

    root = doc.documentElement();
    QDomElement addinfo;
    addinfo = root.lastChild().toElement();

    qDebug() << "root.lastChild(): " << addinfo.tagName();
    qDebug() << "if date == addinfo.attribute(\"date1\"): " << date << " == " << addinfo.attribute("date1");
    qDebug() << "else if date == addinfo.attribute(\"date2\"): " << date << " == " << addinfo.attribute("date2");

    if (date == addinfo.attribute("liabDate1")) {

        if (!goodsEdited) {

            rateLabelInfo->setText(addinfo.attribute("amount1"));
            sendKindInfo->setText(addinfo.attribute("payment1"));
            restLabelInfo->setText(addinfo.attribute("amount2"));

        } else {

            rateLabelInfo->setText(sett().numberToString(am1,'f',2));
            sendKindInfo->setText(addinfo.attribute("payment1"));
            restLabelInfo->setText(sett().numberToString(am2,'f',2));

        }

    } else if (date == addinfo.attribute("liabDate2")) {

        if (!goodsEdited) {

            rateLabelInfo->setText(addinfo.attribute("amount2"));
            sendKindInfo->setText(addinfo.attribute("payment2"));
            restLabelInfo->setText(sett().numberToString(0.00));

        } else {

            rateLabelInfo->setText(sett().numberToString(am2,'f',2));
            sendKindInfo->setText(addinfo.attribute("payment2"));
            restLabelInfo->setText(sett().numberToString(0.00));

        }

    } else {

        // zrób coś bardziej pożytecznego prócz qmessagebox
        QMessageBox::information(this,"Brak danych","Rata o takiej dacie nie istnieje w bazie");
    }
    } else {

        if (date == custPaymData->date1.toString(sett().getDateFormat())) {

            if (!goodsEdited) {

                rateLabelInfo->setText(sett().numberToString(custPaymData->amount1,'f',2));
                sendKindInfo->setText(custPaymData->payment1);
                restLabelInfo->setText(sett().numberToString(custPaymData->amount2,'f',2));

            } else {

                rateLabelInfo->setText(sett().numberToString(am1,'f',2));
                sendKindInfo->setText(custPaymData->payment1);
                restLabelInfo->setText(sett().numberToString(am2,'f',2));

            }

        } else if (date == custPaymData->date2.toString(sett().getDateFormat())) {

            if (!goodsEdited) {

                rateLabelInfo->setText(sett().numberToString(custPaymData->amount2,'f',2));
                sendKindInfo->setText(custPaymData->payment2);
                restLabelInfo->setText(sett().numberToString(0.00,'f',2));

            } else {

                rateLabelInfo->setText(sett().numberToString(am2,'f',2));
                sendKindInfo->setText(custPaymData->payment2);
                restLabelInfo->setText(sett().numberToString(0.00,'f',2));

            }

        } else {

            // zrób coś bardziej pożytecznego prócz qmessagebox
            QMessageBox::information(this,"Brak danych","Rata o takiej dacie nie istnieje w bazie");
        }
     }

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  << "EXIT";

}

/** Copy data from the screen to the object
 */

void Faktura::setData(InvoiceData &invData) {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

    invData.id = fName;
	invData.customer = kontrName->text();
	invData.frNr = frNr->text();
	invData.sellingDate = sellingDate->date();
    invData.issueDate = productDate->date();

    if (constRab->isChecked())
        invData.discount = rabatValue->value();
    else
        invData.discount = 0;

    // lp, nazwa, kod, pkwiu, ilosc, jm, rabat, cena jm., netto, vat, brutto
    for (int i = 0; i < tableTow->rowCount(); ++i) {
        ProductData product; //  = new ProductData();

        product.setId(tableTow->item(i, 0)->text());
        product.setName(tableTow->item(i, 1)->text());
        product.setCode(tableTow->item(i, 2)->text());
        product.setPkwiu(tableTow->item(i, 3)->text());
        product.setQuantity(tableTow->item(i, 4)->text());
        product.setQuanType(tableTow->item(i, 5)->text());
        product.setDiscount(tableTow->item(i, 6)->text());
        double help = sett().stringToDouble(tableTow->item(i, 7)->text());
        qDebug() << "zapisz price w saveInvoice: " << help;
        product.setPrice(sett().numberToString(help,'f',2));
        product.setNett(tableTow->item(i, 8)->text());
        product.setVat(tableTow->item(i, 9)->text());
        product.setGross(tableTow->item(i, 10)->text());
        invData.products[i] = product;
    }

    invData.additText = additEdit->text();
    invData.paymentType = platCombo->currentText();

    if (invData.paymentType == trUtf8("zaliczka")) {

        if (rComboWasChanged) {

            invData.custPaym.payment1 = custPaymData->payment1;
            invData.custPaym.date1 = custPaymData->date1;
            invData.custPaym.amount1 = custPaymData->amount1;

            invData.custPaym.payment2 = custPaymData->payment2;
            invData.custPaym.date2 = custPaymData->date2;
            invData.custPaym.amount2 = custPaymData->amount2;

        } else {

            QLocale locale;

            ratesCombo->setCurrentIndex(0);

            invData.custPaym.payment1 = sendKindInfo->text();
            invData.custPaym.date1 = locale.toDate( ratesCombo->itemText(0), sett().getDateFormat());
            invData.custPaym.amount1 = sett().stringToDouble(rateLabelInfo->text());
            invData.custPaym.date2 = locale.toDate( ratesCombo->itemText(1), sett().getDateFormat());

            invData.custPaym.amount2 = sett().stringToDouble(restLabelInfo->text());

            ratesCombo->setCurrentIndex(1);
            invData.custPaym.payment2 = sendKindInfo->text();
        }
    }

    invData.liabDate = liabDate->date();
    invData.currencyType = currCombo->currentText();

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  << "EXIT";

}

/** Copy data from the object to the form
 */

void Faktura::getData(InvoiceData invData) {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;
    kontrName->setText(invData.customer);
	frNr->setText(invData.frNr);
    sellingDate->setDate(invData.sellingDate );
	productDate->setDate(invData.issueDate);

    if (!invData.duplDate.isNull() && invData.duplDate.isValid()) dupDate = invData.duplDate;

    qDebug() << "DISCOUNT: " << invData.discount;
	if (invData.discount == 0) {

        rabatValue->setValue(0);

	} else {

		constRab->setChecked(true);
		rabatValue->setValue(invData.discount);
	}

    qDebug() << "RABAT: " << invData.discount;
    qDebug() << "ustawiony rabatValue po wczytaniu: " << rabatValue->value();


    additEdit->setText(invData.additText);

    if (invData.paymentType == trUtf8("zaliczka")) {

        disconnect(platCombo, SIGNAL(currentIndexChanged (QString)), this, SLOT(payTextChanged(QString)));
        disconnect(ratesCombo, SIGNAL(currentIndexChanged (QString)), this, SLOT(rateDateChanged(QString)));
        labelRate = new QLabel();
        labelRate->setText(trUtf8("Termin raty:"));
        labelRate->setAlignment(Qt::AlignRight);
        addDataLabels->addWidget(labelRate);

        ratesCombo->addItem(invData.custPaym.date1.toString(sett().getDateFormat()));

        qDebug() << "added date to ratesCombo: " << invData.custPaym.date1.toString(sett().getDateFormat());
        ratesCombo->addItem(invData.custPaym.date2.toString(sett().getDateFormat()));
        qDebug() << "added date to ratesCombo: " << invData.custPaym.date2.toString(sett().getDateFormat());
        ratesCombo->setCurrentText(invData.custPaym.date1.toString(sett().getDateFormat()));
        addData->addWidget(ratesCombo);


        rateLabel = new QLabel();
        rateLabel->setText(trUtf8("Rata:"));
        rateLabel->setAlignment(Qt::AlignRight);
        descPayments->addWidget(rateLabel);

        sendKind = new QLabel();
        sendKind->setText(trUtf8("Rodzaj zapłaty:"));
        sendKind->setAlignment(Qt::AlignRight);
        descPayments->addWidget(sendKind);

        restLabel = new QLabel();
        restLabel->setText(trUtf8("Pozostało do spłaty:"));
        restLabel->setAlignment(Qt::AlignRight);
        descPayments->addWidget(restLabel);

        rateLabelInfo = new QLabel();
        rateLabelInfo->setText(sett().numberToString(invData.custPaym.amount1));
        dataPayments->addWidget(rateLabelInfo);

        sendKindInfo = new QLabel();
        sendKindInfo->setText(invData.custPaym.payment1);
        dataPayments->addWidget(sendKindInfo);

        restLabelInfo = new QLabel();
        restLabelInfo->setText(sett().numberToString(invData.custPaym.amount2));
        dataPayments->addWidget(restLabelInfo);

    }


    currCombo->setCurrentText(invData.currencyType);
    platCombo->setCurrentText(invData.paymentType);
    liabDate->setDate(invData.liabDate);


    if (invData.paymentType == trUtf8("zaliczka")) {
        connect(platCombo, SIGNAL(currentIndexChanged (QString)), this, SLOT(payTextChanged(QString)));
        connect(ratesCombo, SIGNAL(currentIndexChanged (QString)), this, SLOT(rateDateChanged(QString)));

    }

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  << "EXIT";

}

/** Slot saveInvoice
 *  Generates Invoice XML
 */

bool Faktura::saveInvoice() {

     qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << fName;

	bool result = false;
	if (!validateForm()) return false;

	InvoiceData invData;
    setData(invData);


    result = dataLayer->invoiceInsertData(invData, type);
    ret = dataLayer->getRet();


    if (result) {
        //getInvoiceTypeAndSaveNr();
    }

    saveBtn->setEnabled(false);
    rmTowBtn->setEnabled(false);
    editTwBtn->setEnabled(false);

    saveFailed = false;
    canClose = true;
	return result;
}

/** Slot makeInvoice
 *  Generate html with invoice and show Print Preview dialog
 */

void Faktura::makeInvoice() {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

    if (kontrName->text() == "") {

		QMessageBox::information(this, "QFaktury", trUtf8("Wybierz kontrahenta"),
				QMessageBox::Ok);
		return;
	}

	if (tableTow->rowCount() == 0) {

		QMessageBox::information(this, "QFaktury", trUtf8("Nie ma towarów"),
		QMessageBox::Ok);
		return;
	}

	fraStrList.clear();
	makeInvoiceHeadarHTML();

    if (ifCSS) {

        makeInvoiceHeadar(true, false, true);
        makeInvoiceBody();
        makeInvoiceProducts();
        makeInvoiceSumm();
        makeInvoiceSummAll();
        makeInvoiceFooter();

        int numberOfCopies = sett().value("numberOfCopies", 2).toInt();

        for (int i = 1; i <= numberOfCopies; i++) {

            makeInvoiceHeadar(true, true, false);
            makeInvoiceBody();
            makeInvoiceProducts();
            makeInvoiceSumm();
            makeInvoiceSummAll();
            makeInvoiceFooter();
        }

        makeInvoiceFooterHtml();

        print();

        saveBtn->setFocus();
    }
}

/** Slot print
 *  Helper slot used to display print preview
 */

void Faktura::printSlot(QPrinter *printer) {

     qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

    QTextDocument doc(invoiceType);
    QString s;

    for (QStringList::iterator it = fraStrList.begin(); it != fraStrList.end(); ++it) {
        s+=*it+"\n";
    }
    // qDebug of the whole invoice :)

	QFile file(sett().getWorkingDir() + "/invoice.html");

	if (file.open(QIODevice::WriteOnly)) {

		QTextStream stream(&file);
		for (QStringList::Iterator it = fraStrList.begin(); it
				!= fraStrList.end(); ++it)
			stream << *it << "\n";
		file.close();
	}

    doc.setHtml(s);
    doc.print(printer);
}

/** Slot
 *  Print slot
 */

void Faktura::print() {

     qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

	QPrinter printer(QPrinter::HighResolution);
	QPrintPreviewDialog preview(&printer, this);
	preview.setWindowFlags(Qt::Window);
	preview.setWindowTitle(invoiceType + s_WIN_PRINTPREVIEW);

	connect(&preview, SIGNAL(paintRequested(QPrinter *)), this, SLOT(printSlot(QPrinter *)));
    if (preview.exec() == 1) {
    }
}

// ---- SLOTS END --//////////////////////////////////////////////////////////////////////////////////
// ******************************** XML Helpers START **********************************************
/** Check if data on the form is correct
 */

bool Faktura::validateForm() {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

    if (kontrName->text() == "") {

		QMessageBox::critical(this, "QFaktury", trUtf8("Nie ma kontrahenta."),
				QMessageBox::Ok);
		saveFailed = true;
		return false;
	}

	if (tableTow->rowCount() == 0) {

		QMessageBox::critical(this, "QFaktury", trUtf8("Nie ma towarów."),
				QMessageBox::Ok);
		saveFailed = true;
		return false;
    }
	return true;
}

// ******************************** XML Helpers END **********************************************

// Generate Invoice HTML methods --- START ---

void Faktura::makeInvoiceHeadarHTML() {

	fraStrList += "<html><head>";
	fraStrList += "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />"; //@TODO
    fraStrList += "<meta name=\"creator\" value=\"https://github.com/juliagoda/qfaktury\" />";
    fraStrList += "</head>";
    fraStrList += "<title>"+ invoiceType  +"</title>";
    fraStrList += "<style type=\"text/css\"> ";

	QFile file(sett().getTemplate());

    if (file.open(QIODevice::ReadOnly)) {

		QTextStream stream(&file);
        QString line;
        while (!stream.atEnd()) {
			line = stream.readLine();
			fraStrList += line;
        }
		file.close();
        ifCSS = true;

    } else {

        QMessageBox::warning(this, "Brak szablonu", trUtf8("Brakuje pliku css, który wymagany jest do ustawienia wyglądu drukowania"));
        ifCSS = false;
        qDebug() << "Could not open CSS file: " << file.fileName();

    }

	fraStrList += "</style>";
    fraStrList += "<body>";
}


void Faktura::makeInvoiceHeadar(bool sellDate, bool breakPage, bool original) {

	QString breakPageStr = "class=\"page_break\"";
	if (breakPage == false) breakPageStr = "";

    fraStrList += "<table comment=\"headar table\" width=\"100%\" " + breakPageStr + ">";
	fraStrList += "<tr>";
    fraStrList += "<td width=\"60%\" align=\"center\" valign=\"bottom\">";
    fraStrList += "<span class=\"stamp\">";
    QString logo = sett().value("logo").toString();

    if (logo != "") {
            fraStrList += "<img src=\"" + logo + "\" width=\"100\" " + " height=\"100\"+ >";
    } else {
            fraStrList += trUtf8("Pieczęć wystawcy");
    }

    fraStrList += "</span>";
    fraStrList += "</td>";
    if (sett().value("css").toString() == "tables.css") {

        fraStrList += "<td id=\"invoiceInfo\" width=\"35%\" align=\"right\">";
        if (sett().value("css").toString() == "tables.css") {
            fraStrList += "<table id=\"rightInvTable\" width=\"100%\" border=\"1\" cellspacing=\"0\" cellpadding=\"5\" >";

        } else {
            fraStrList += "<table id=\"rightInvTable\" width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"5\" >";

        }

        fraStrList += "<tr>";
        fraStrList += "<td id=\"invFirstLine\" style=\"font-size:12pt; font-weight:600\">";
        fraStrList += invoiceType + "<br/>";
        fraStrList += trUtf8("Nr: ") + frNr->text() + "</td>";
        fraStrList += "</tr>";
        fraStrList += "<tr>";
        fraStrList += "<td class=\"dates\">" + trUtf8("Data wystawienia: ")
                        + productDate->date().toString(sett().getDateFormat()) + "</td>";

        fraStrList += "</tr>";
        fraStrList += "<tr><td>";
        if (sellDate)
        fraStrList += trUtf8("Data sprzedaży: ")
                + sellingDate->date().toString(sett().getDateFormat())
                + "</td>";
        fraStrList += "</tr>";

        fraStrList += "</table></td><td width=\"3%\">&nbsp;</td>";
    } else {
    fraStrList += "<td id=\"invoiceInfo\" align=\"right\">";
    fraStrList += "<span id=\"invFirstLine\" style=\"font-size:12pt; font-weight:600\">";
    fraStrList += invoiceType + "<br/>";
    fraStrList += trUtf8("Nr: ") + frNr->text() + "<br></span>";
    fraStrList += "<span class=\"dates\">" + trUtf8("Data wystawienia: ")
				    + productDate->date().toString(sett().getDateFormat()) + "<br>";

    if (sellDate)
    fraStrList += trUtf8("Data sprzedaży: ")
            + sellingDate->date().toString(sett().getDateFormat())
            + "<br>";

    fraStrList += "</span></td><td width=\"3%\">&nbsp;</td>";
    }
	fraStrList += "</tr>";
	fraStrList += "<tr>";
    fraStrList += "<td class=\"origcopy\" colspan=\"2\" align=\"right\" valign=\"top\"><br>";

    if (original) {
        fraStrList += trUtf8("ORYGINAŁ");
    } else {
        fraStrList += trUtf8("KOPIA");
    }

        fraStrList += "<hr/><br/>";


    fraStrList += "<br></td><td width=\"3%\">&nbsp;</td>";
	fraStrList += "</tr>";
	fraStrList += "</table>";
    fraStrList += "</td></tr>";

}


void Faktura::makeInvoiceBody() {

	fraStrList += "<tr><td>";
	fraStrList += "<table width=\"100%\" border=\"0\">";
	fraStrList += "<tr class=\"persons\">";
    fraStrList += "<td width=\"20\">&nbsp;</td>";
    fraStrList += "<td class=\"buyerSeller\" width=\"48%\"> ";
    fraStrList += "<p id=\"seller\">" + trUtf8("Sprzedawca:") + "</p><br/>";

    QSettings userSettings("elinux", "user");

    sett().beginGroup("printpos");

        if (sett().value("usernazwa").toBool() && (!userSettings.value("name").toString().trimmed().isEmpty()))
            fraStrList += userSettings.value("name").toString() + "<br/>";

        if (sett().value("useradres").toBool() && (!userSettings.value("address").toString().trimmed().isEmpty()))
            fraStrList += userSettings.value("address").toString() + "<br/>";

        if (sett().value("usermiejscowosc").toBool() && (!userSettings.value("zip").toString().trimmed().isEmpty()))
			fraStrList += userSettings.value("zip").toString() + " ";

        if (sett().value("usermiejscowosc").toBool() && (!userSettings.value("city").toString().trimmed().isEmpty()))
            fraStrList += userSettings.value("city").toString() + "<br/>";

        if (sett().value("usernip").toBool() && (!userSettings.value("tic").toString().trimmed().isEmpty()))
            fraStrList += trUtf8("NIP: ") + userSettings.value("tic").toString() + "<br/>";

        if (sett().value("userkonto").toBool() && (!userSettings.value("account").toString().trimmed().isEmpty()))
            fraStrList += trUtf8("Nr konta: ") + userSettings.value("account").toString().replace("-", " ") + "<br/>";

        if (sett().value("userphone").toBool() && (!userSettings.value("phone").toString().trimmed().isEmpty()))
            fraStrList += trUtf8("Telefon: ") + userSettings.value("phone").toString() + "<br/>";

        if (sett().value("usermail").toBool() && (!userSettings.value("email").toString().trimmed().isEmpty()))
            fraStrList += trUtf8("Email: ") + userSettings.value("email").toString() + "<br/>";

        if (sett().value("userwww").toBool() && (!userSettings.value("website").toString().trimmed().isEmpty()))
            fraStrList += trUtf8("Strona www: ") + userSettings.value("website").toString() + "<br/>";

    sett().endGroup();

        fraStrList += "</td>";
        fraStrList += "<td width=\"20\">&nbsp;</td>";
        fraStrList += "<td class=\"buyerSeller\" width=\"48%\">";
        fraStrList += "<p id=\"seller\">" + trUtf8("Nabywca:") + "</p><br/>"; //+ kontrName->text().replace(",", "<br>") + "<br>";

        QStringList lista = kontrName->text().split(",");


    sett().beginGroup("printkontr");

        QString el1 = lista.at(0);
        if (sett().value("kontrnazwa").toBool() && (el1.trimmed() != "-"))
            fraStrList += el1 + "<br>";

        QString el2 = lista.at(1);
        if (sett().value("kontrmiejscowosc").toBool() && (el2.trimmed() != "-"))
            fraStrList += el2 + "<br>";

        QString el3 = lista.at(2);
        if (sett().value("kontradres").toBool() && (el3.trimmed() != "-"))
            fraStrList += el3 + "<br>";

        QString el4 = lista.at(3);
        if (sett().value("kontrnip").toBool() && (el4.replace(" ", "").replace(QObject::trUtf8("NIP:"),     "") != "-"))
            fraStrList += trUtf8("NIP: ") + el4 + "<br>";

        QString el5 = lista.at(4);
        if (sett().value("kontrkonto").toBool() && (el5.replace(" ", "").replace(QObject::trUtf8("Konto:"), "") != "-"))
            fraStrList += trUtf8("Nr konta: ") + el5 + "<br>";

        QString el6 = lista.at(5);
        if (sett().value("kontrphone").toBool() && (el6.replace(" ", "").replace(QObject::trUtf8("Tel:"), "") != "-"))
            fraStrList += trUtf8("Telefon: ") + el6 + "<br>";

        QString el7 = lista.at(6);
        if (sett().value("kontrmail").toBool() && (el7.replace(" ", "").replace(QObject::trUtf8("Email:"), "") != "-"))
            fraStrList += trUtf8("Email: ") + el7 + "<br>";

        QString el8 = lista.at(7);
        if (sett().value("kontrwww").toBool() && (el8.replace(" ", "").replace(QObject::trUtf8("Strona www:"), "") != "-"))
            fraStrList += trUtf8("Strona www: ") + el8 + "<br>";

    sett().endGroup();


    fraStrList += "</td>";
	fraStrList += "</tr>";
    fraStrList += "</table>";
    fraStrList += "<hr/>";
    fraStrList += "</td></tr>";

}


void Faktura::makeInvoiceProductsHeadar() {

    int currentPercent = 0;
	fraStrList += "<tr align=\"center\" valign=\"middle\" class=\"productsHeader\" >";

    sett().beginGroup("faktury_pozycje");

        if (sett().value("Lp").toBool()) {
            currentPercent = 3;
            fraStrList += "<td align=\"center\" width=\""+ sett().numberToString(currentPercent) + "%\">" + trUtf8("Lp.") + "</td>";
            currentPercent = 0;
        } else {
            currentPercent += 3;
        }

        if (sett().value("Nazwa").toBool()) {
            currentPercent += 13;
            fraStrList += "<td align=\"center\" width=\""+ sett().numberToString(currentPercent) + "%\">" + trUtf8("Nazwa") + "</td>";
            currentPercent = 0;
        } else {
            currentPercent += 13;
        }

        if (sett().value("Kod").toBool()) {
            currentPercent += 7;
            fraStrList += "<td align=\"center\" width=\""+ sett().numberToString(currentPercent) + "%\">" + trUtf8("Kod") + "</td>";
            currentPercent = 0;
        } else {
            currentPercent += 7;
        }

        if (sett().value("pkwiu").toBool()) {
            currentPercent += 7;
            fraStrList += "<td align=\"center\" width=\""+ sett().numberToString(currentPercent) + "%\">" + trUtf8("PKWiU") + "</td>";
            currentPercent = 0;
        } else {
            currentPercent += 7;
        }

        if (sett().value("ilosc").toBool()) {
            currentPercent += 9;
            fraStrList += "<td align=\"center\" width=\""+ sett().numberToString(7) + "%\">" + trUtf8("Ilość") + "</td>";
            currentPercent = 0;
        } else {
            currentPercent += 9;
        }

        if (sett().value("jm").toBool()) {
            currentPercent += 3;
            fraStrList += "<td align=\"center\" width=\""+ sett().numberToString(3) + "%\">" + trUtf8("jm.") + "</td>";
            currentPercent = 0;
        } else {
            currentPercent += 3;
        }

        if (sett().value("cenajedn").toBool()) {
            currentPercent += 7;
            fraStrList += "<td align=\"center\" width=\""+ sett().numberToString(currentPercent) + "%\">" + trUtf8("Cena jdn.") + "</td>";
            currentPercent = 0;
        } else {
            currentPercent += 7;
        }

        if (sett().value("wartnetto").toBool()) {
            currentPercent += 8;
            fraStrList += "<td align=\"center\" width=\""+ sett().numberToString(currentPercent) + "%\">" + trUtf8("Wartość Netto") + "</td>";
            currentPercent = 0;
        } else {
            currentPercent += 8;
        }

        if (sett().value("rabatperc").toBool()) {
            currentPercent += 3;
            fraStrList += "<td align=\"center\" width=\""+ sett().numberToString(3) + "%\">" + trUtf8("Rabat %") + "</td>";
            currentPercent = 0;
        } else {
            currentPercent += 3;
        }

        if (sett().value("rabatval").toBool()) {
            currentPercent += 11;
            fraStrList += "<td align=\"center\" width=\""+ sett().numberToString(currentPercent) + "%\">" + trUtf8("Rabat Wartość") + "</td>";
            currentPercent = 0;
        } else {
            currentPercent += 11;
        }

        if (sett().value("nettoafter").toBool()) {
            currentPercent += 7;
            fraStrList += "<td align=\"center\" width=\""+ sett().numberToString(currentPercent) + "%\">" + trUtf8("Netto po rabacie") + "</td>";
            currentPercent = 0;
        } else {
            currentPercent += 7;
        }

        if (sett().value("vatval").toBool()) {
            currentPercent += 7;
            fraStrList += "<td align=\"center\" width=\""+ sett().numberToString(7) + "%\">" + trUtf8("Stawka VAT") + "</td>";
            currentPercent = 0;
        } else {
            currentPercent += 7;
        }

        if (sett().value("vatprice").toBool()) {
            currentPercent += 7;
            fraStrList += "<td align=\"center\" width=\""+ sett().numberToString(currentPercent) + "%\">" + trUtf8("Kwota Vat") + "</td>";
            currentPercent = 0;
        } else {
            currentPercent += 7;
        }

        if (sett().value("bruttoval").toBool()) {
            currentPercent += 8;
            fraStrList += "<td align=\"center\" width=\""+ sett().numberToString(currentPercent) + "%\">" + trUtf8("Wartość Brutto") + "</td>";
            currentPercent = 0;
        } else {
            currentPercent += 8;
        }

    sett().endGroup();
	fraStrList += "</tr>";

}

void Faktura::makeInvoiceProducts() {

    fraStrList += "<tr><td>";

    fraStrList += "<table border=\"2\" cellspacing=\"0\" cellpadding=\"5\" width=\"100%\">";

	makeInvoiceProductsHeadar();

	for (int i = 0; i < tableTow->rowCount(); ++i) {

        fraStrList += "<tr class=\"products\" >";
        // lp, nazwa, kod, pkwiu, ilosc, jm, rabat, cena jm., netto, vat, brutto

        sett().beginGroup("faktury_pozycje");

            if (sett().value("Lp").toBool())
                fraStrList += "<td>" + sett().numberToString(i + 1) + "</td>";

            if (sett().value("Nazwa") .toBool())
                fraStrList += "<td align=\"left\">" + tableTow->item(i, 1)->text() + "</td>";

            if (sett().value("Kod") .toBool())
                fraStrList += "<td>" + tableTow->item(i, 2)->text() + "</td>";

            if (sett().value("pkwiu") .toBool())
                fraStrList += "<td>" + tableTow->item(i, 3)->text() + "</td>";

            if (sett().value("ilosc") .toBool())
                fraStrList += "<td>" + tableTow->item(i, 4)->text() + "</td>";

            if (sett().value("jm") .toBool())
                fraStrList += "<td>" + tableTow->item(i, 5)->text() + "</td>";

            if (sett().value("cenajedn") .toBool())
                fraStrList += "<td>" + tableTow->item(i, 7)->text() + "</td>";

            double discountVal = sett().stringToDouble(tableTow->item(i, 8)->text()) *
                                (sett().stringToDouble(tableTow->item(i, 6)->text()) * 0.01);

            double nettMinusDisc = sett().stringToDouble(tableTow->item(i, 8)->text()) - discountVal;

            if (sett().value("wartnetto") .toBool())
                fraStrList += "<td>" + tableTow->item(i, 8)->text()	+ "</td>"; // netto

            if (sett().value("rabatperc") .toBool())
                fraStrList += "<td>" + tableTow->item(i, 6)->text()	+ "%</td>"; // rabat

            if (sett().value("rabatval") .toBool())
                fraStrList += "<td align=\"center\" >" + sett().numberToString(discountVal, 'f',  2)	+ "</td>";

            if (sett().value("nettoafter") .toBool())
                fraStrList += "<td>" + sett().numberToString(nettMinusDisc, 'f', 2) + "</td>";

            if (sett().value("vatval") .toBool())
                fraStrList += "<td>" + tableTow->item(i, 9)->text()	+ "%</td>";

            double vatPrice = sett().stringToDouble(tableTow->item(i, 10)->text())
								- sett().stringToDouble(tableTow->item(i, 8)->text()); // brutt-nett :)

            if (sett().value("vatprice") .toBool())
                fraStrList += "<td>" + sett().numberToString(vatPrice, 'f', 2) + "</td>";

            if (sett().value("bruttoval") .toBool())
                fraStrList += "<td>" + tableTow->item(i, 10)->text() + "</td>";

        sett().endGroup();
        fraStrList += "</tr>";
    }

	fraStrList += "</table>";
}

void Faktura::makeInvoiceSumm() {

    double vatPrice = sett().stringToDouble(sum3->text()) - sett().stringToDouble(sum1->text());
    if (sett().value("css").toString() == "tables.css") {
        fraStrList += "<br><table width=\"100%\" border=\"2\" cellspacing=\"0\" cellpadding=\"5\">";

    } else {
        fraStrList += "<br><table width=\"100%\" border=\"0\" cellpadding=\"5\">";

    }
	fraStrList += "<tr class=\"productsSumHeader\" valign=\"middle\">";
    fraStrList += "<td id=\"notNec\" width=\"67%\" align=\"center\">&nbsp;</td>";
    fraStrList += "<td width=\"11%\" align=\"center\">" + trUtf8("Wartość Netto") + "</td>"; // netto
    fraStrList += "<td width=\"11%\" align=\"center\">" + trUtf8("Kwota VAT") + "</td>";// vat
    fraStrList += "<td width=\"11%\" align=\"center\">" + trUtf8("Wartość Brutto") + "</td>"; // brutto
	fraStrList += "</tr><tr class=\"productsSum\">";
    fraStrList += "<td align=\"right\">" + trUtf8("Razem:") + "</td>";
    fraStrList += "<td align=\"center\">" + sum1->text() + "</td>"; // netto
    fraStrList += "<td align=\"center\">" + sett().numberToString(vatPrice, 'f', 2) + "</td>";// vat
    fraStrList += "<td align=\"center\">" + sum3->text() + "</td>"; // brutto
	fraStrList += "</tr>";
	fraStrList += "</table><br><br>";

}


void Faktura::makeInvoiceSummAll() {

	fraStrList += "</td></tr>"; // closing products row
    fraStrList += "<tr comment=\"podsumowanie\"><td>";
    fraStrList += "<table width=\"100%\" border=\"0\">";


	fraStrList += "<tr class=\"summary\">";
    fraStrList += "<td width=\"3%\">&nbsp;</td>";
    fraStrList += "<td width=\"48%\"><span style=\"toPay\">";
    fraStrList += trUtf8("Do zapłaty: ") + sum3->text() + " "
					+ currCombo->currentText() + "</span><br>";
    ConvertAmount* conv = new ConvertAmount();
    fraStrList += trUtf8("słownie:")
				+ conv->convertPL(sum3->text(), currCombo->currentText()) + "<br>";
    delete conv;

    if (platCombo->currentText() == trUtf8("gotówka")) {

        fraStrList += trUtf8("forma płatności: ") + platCombo->currentText() + "<br><b>";
        fraStrList += trUtf8("Zapłacono gotówką") + "<br>";

     } else if (platCombo->currentText() == trUtf8("zaliczka")) {

        fraStrList += "<span style=\"toPay\">";

        ratesCombo->setCurrentIndex(0);
        QString whatMethod_one = QString();
        if (sendKindInfo->text() == trUtf8("gotówka")) whatMethod_one = trUtf8("gotówką");
        else whatMethod_one = trUtf8("przelewem");

        ratesCombo->setCurrentIndex(1);
        QString whatMethod_two = QString();
        if (sendKindInfo->text() == trUtf8("gotówka")) whatMethod_two = trUtf8("gotówką");
        else whatMethod_two = trUtf8("przelewem");

        ratesCombo->setCurrentIndex(0);

        fraStrList += QString(trUtf8("Zapłacono ") + whatMethod_one + ": "
                    +  rateLabelInfo->text() + " " + currCombo->currentText() + " "
                    + ratesCombo->itemText(0) + "<br>");
        fraStrList += QString(trUtf8("Zaległości ") + whatMethod_two + ": "
                    +  restLabelInfo->text() + " " + currCombo->currentText() + " "
                    + ratesCombo->itemText(1));
        fraStrList += "</span>";

     } else if (platCombo->currentText() == trUtf8("przelew")) {

        fraStrList += trUtf8("forma płatności: ") + platCombo->currentText() + "<br><b>";
        fraStrList += trUtf8("Zapłacono przelewem") + "<br>";
        fraStrList += "<span style=\"payDate\">";
        fraStrList += trUtf8("termin płatności: ")
				+ liabDate->date().toString(sett().getDateFormat())	+ "<br>";
        fraStrList += "</span>";

     } else {

        fraStrList += trUtf8("forma płatności: ") + platCombo->currentText() + "<br><b>";
        fraStrList += "<span style=\"payDate\">";
        fraStrList += trUtf8("termin płatności: ")
                + liabDate->date().toString(sett().getDateFormat())	+ "<br>";
        fraStrList += "</span>";
     }


     fraStrList += "</b><br><br>";
     fraStrList += "<span class=\"additionalText\">"	+ additEdit->text() + "</span>";
     fraStrList += "</td>";
     fraStrList += "<td width=\"3%\">&nbsp;</td>";
     fraStrList += "<td width=\"48%\" valign=\"top\">";
     if (sett().value("css").toString() == "tables.css") {
         fraStrList += "<table id=\"totalRatesTable\" width=\"90%\" border=\"2\" cellspacing=\"0\" cellpadding=\"5\">";

     } else {
         fraStrList += "<table id=\"totalRatesTable\" width=\"90%\" border=\"0\">";

     }
     fraStrList += "<tr class=\"stawkiHeader\"><td colspan=\"4\">";
     fraStrList += trUtf8("Ogółem stawkami:");
     fraStrList += "</td></tr>";
     fraStrList += getGroupedSums();
     fraStrList += "<tr>";
     fraStrList += "<td>&nbsp;</td>"; // netto
     fraStrList += "<td>&nbsp;</td>"; // stawka
     fraStrList += "<td>&nbsp;</td>"; // podatek
     fraStrList += "<td>&nbsp;</td>"; // brutto
     fraStrList += "</tr>";
     fraStrList += "</table>";
     fraStrList += "</td>";
     fraStrList += "</tr>";
     fraStrList += "</table>";
     fraStrList += "</td></tr>";
}


void Faktura::makeInvoiceFooter() {

	fraStrList += "<tr comment=\"podpis\" align=\"center\"><td>";
    fraStrList += "<br><br><br><br>";
    fraStrList += "<table width=\"80%\" border=\"0\">";
    fraStrList += "<tr>";
    fraStrList += "<td width=\"3%\">&nbsp;</td>";
    fraStrList += "<td width=\"43%\" align=\"center\"> ";
    fraStrList += "<hr width=\"100%\" noshade=\"noshade\" color=\"black\" />";
    fraStrList += "</td>";
    fraStrList += "<td width=\"7%\">&nbsp;</td>";
    fraStrList += "<td width=\"3%\">&nbsp;</td>";
    fraStrList += "<td width=\"43%\" align=\"center\"> ";
    fraStrList += "<hr width=\"100%\" noshade=\"noshade\" color=\"black\" />";
    fraStrList += "</td>";
    fraStrList += "</tr>";
    fraStrList += "<tr class=\"signature\">";
    fraStrList += "<td width=\"3%\">&nbsp;</td>";
    fraStrList += "<td width=\"43%\" align=\"center\"> ";
    fraStrList += trUtf8("Imię i nazwisko osoby upoważnionej")
					+ "<br>" + trUtf8(" do wystawienia faktury VAT");
    fraStrList += "</td>";
    fraStrList += "<td width=\"7%\">&nbsp;</td>";
    fraStrList += "<td width=\"3%\">&nbsp;</td>";
    fraStrList += "<td width=\"43%\" align=\"center\">";
    fraStrList += trUtf8("Imię i nazwisko osoby upoważnionej")
					+ "<br>" + trUtf8(" do odbioru faktury VAT");
    fraStrList += "</td>";
    fraStrList += "</tr>";
    fraStrList += "</table>";
	fraStrList += "</td></tr>";
	fraStrList += "</table>";

}

void Faktura::makeInvoiceFooterHtml() {

	fraStrList += "</body>";
	fraStrList += "</html>";
}

/** getGroupedSums
 *  Groups prices by VAT
 */

QString Faktura::getGroupedSums() {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

    QStringList out;
	QStringList stawki = sett().value("stawki").toString().split("|");
	QMap<int, double> stawkiNetto;
	QMap<int, double> stawkiVat;
	QMap<int, double> stawkiBrutto;
    int ssize = stawki.size();

	// lp, nazwa, kod, pkwiu, ilosc, jm, rabat, cena jm., netto, vat, brutto
	for (int i = 0; i < tableTow->rowCount(); ++i) {
        for (int y = 0; y < ssize; ++y) {

            if (stawki[y] == tableTow->item(i, 9)->text()) {

				stawkiNetto[y] += sett().stringToDouble(tableTow->item(i, 8)->text());
				stawkiBrutto[y] += sett().stringToDouble(tableTow->item(i, 10)->text());
                // qDebug() << stawkiBrutto[y] << stawkiNetto[y] << stawkiBrutto[y] - stawkiNetto[y];
                stawkiVat[y] = stawkiBrutto[y] - stawkiNetto[y];

            } else {

				stawkiNetto[y] += 0;
				stawkiBrutto[y] += 0;
                stawkiVat[y] += 0;
			}
		}
	}

    for (int y = 0; y < ssize; ++y) {

		out += "<tr class=\"stawki\">";
		out += "<td width=\"30%\">" + sett().numberToString(stawkiNetto[y], 'f', 2) + "</td>"; // netto
		out += "<td width=\"10%\">" + stawki[y] + "</td>"; // stawka
		out += "<td width=\"30%\">" + sett().numberToString(stawkiVat[y], 'f', 2) + "</td>"; // podatek
		out += "<td width=\"30%\">" + sett().numberToString(stawkiBrutto[y], 'f', 2) + "</td>"; // brutto
		out += "</tr>";

    }

	return out.join(" ");
}

// Generate Invoice HTML methods --- END ---

/** Read data
 *  Used when editInvoice is invoked. Invoked from MainWindow class.
 */

void Faktura::readData(QString fraFile) {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;
    prepayFile = fraFile;
    qDebug() << "prepayFile w readData: " << prepayFile;
	backBtn->setEnabled(false);
	frNr->setEnabled(false);

    getData(dataLayer->invoiceSelectData(fraFile, type));

	canClose = true;
	saveBtn->setEnabled(false);

	setIsEditAllowed(sett().value("edit").toBool());
    //calculateDiscount();
	calculateSum();

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  << "EXIT";

}

/** Sets the editability
 */
void Faktura::setIsEditAllowed(bool isAllowed) {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

    if (!sett().value("editSymbol").toBool()) {
	frNr->setEnabled(isAllowed);
    }

	backBtn->setEnabled(isAllowed);
	sellingDate->setEnabled(isAllowed);
	productDate->setEnabled(isAllowed);
	tableTow->setEnabled(isAllowed);
    rabatValue->setEnabled(isAllowed);
	rabatLabel->setEnabled(isAllowed);
	platCombo->setEnabled(isAllowed);
	liabDate->setEnabled(isAllowed);
	additEdit->setEnabled(isAllowed);
	addTwBtn->setEnabled(isAllowed);
	rmTowBtn->setEnabled(isAllowed);
	editTwBtn->setEnabled(isAllowed);
	constRab->setEnabled(isAllowed);
	kListGet->setEnabled(isAllowed);
	currCombo->setEnabled(isAllowed);
	saveBtn->setEnabled(isAllowed);
	addKButton->setEnabled(isAllowed);
	liabDate->setEnabled(isAllowed);

	if (!isAllowed || rabatValue->value() == 0) {

		constRab->setChecked(false);
		rabatValue->setEnabled(false);

	} else {

		constRab->setChecked(true);
		rabatValue->setEnabled(true);

	}

    if (isAllowed && (platCombo->currentText() != trUtf8("przelew"))) {
        liabDate->setEnabled(false);
    } else {
        liabDate->setEnabled(true);
    }

    konvPLN->setEnabled(isAllowed);
    konvEUR->setEnabled(isAllowed);
    konvUSD->setEnabled(isAllowed);
    konvCHF->setEnabled(isAllowed);
    konvGBP->setEnabled(isAllowed);
    konvRUB->setEnabled(isAllowed);



    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  << "EXIT";

}

/** Caclulate Discount
 */

void Faktura::calculateDiscount() {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

	for (int i = 0; i < tableTow->rowCount(); ++i) {
		calculateOneDiscount(i);
	}

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  << "EXIT";

}

/** Caclulate Discount
 */

void Faktura::calculateOneDiscount(int i) {

     qDebug() << __FUNCTION__ << __LINE__ << __FILE__;

	double quantity = 0, vat = 0, gross = 0;
	double netto = 0,  price = 0;
	double discountValue = 0, discount;

    qDebug() << "PRICE PRZED: " << tableTow->item(i, 7)->text();
    price = sett().stringToDouble(tableTow->item(i, 7)->text());
    qDebug() << "PRICE PO: " << price;

	if (constRab->isChecked()) {

        qDebug() << "PRZED rabatValue->value()" << rabatValue->value();
        discount = rabatValue->value() * 0.01;
        qDebug() << "PO rabatValue->value()" << discount;

	} else {

        qDebug() << "PRZED tableTow->item(i, 6)->text()" << tableTow->item(i, 6)->text().toInt();
        discount = (tableTow->item(i, 6)->text()).toInt() * 0.01;
        qDebug() << "PO tableTow->item(i, 6)->text()" << discount;
	}

    quantity = tableTow->item(i, 4)->text().toInt();
    qDebug() << "PATRZ QUANTITY: " << quantity;
	netto = (price * quantity);
    qDebug() << "PATRZ NETTO: " << netto;
	discountValue = netto * discount;
    qDebug() << "PATRZ DISCOUNTVALUE: " << discountValue;
	netto -= discountValue;
    qDebug() << "PATRZ NETTO Z DISCOUNT: " << netto;
    vat = tableTow->item(i, 9)->text().toInt();
	gross = netto * ((vat * 0.01) + 1);
    qDebug() << "PATRZ BRUTTO: " << gross;


    qDebug() << price << quantity << netto << discount << discountValue << vat << gross;

    tableTow->item(i, 6)->setText(sett().numberToString(discount * 100, 'f', 0)); // discount
    qDebug() << "discount w tabeli: " << tableTow->item(i, 6)->text();
	tableTow->item(i, 8)->setText(sett().numberToString(netto)); // nett
    qDebug() << "netto w tabeli: " << tableTow->item(i, 8)->text();
	tableTow->item(i, 10)->setText(sett().numberToString(gross)); // gross
    qDebug() << "brutto w tabeli: " << tableTow->item(i, 10)->text();


    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  << "EXIT";

}

/** Calculate sum
 */

void Faktura::calculateSum() {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

    double netto = 0, price = 0, gross = 00;
    double discountValue = 0;

	nettTotal = 0;
	discountTotal = 0;
	grossTotal = 0;

	for (int i = 0; i < tableTow->rowCount(); ++i) {

		price = sett().stringToDouble(tableTow->item(i, 7)->text());

        double decimalPointsNetto = tableTow->item(i, 8)->text().right(2).toInt() * 0.01;
        qDebug() << "decimalPointsNetto << " << decimalPointsNetto;
        double decimalPointsGross = tableTow->item(i, 10)->text().right(2).toInt() * 0.01;
        qDebug() << "decimalPointsGross << " << decimalPointsGross;

        netto = sett().stringToDouble(tableTow->item(i, 8)->text());
        netto += decimalPointsNetto;
		gross = sett().stringToDouble(tableTow->item(i, 10)->text());
        gross += decimalPointsGross;
        discountValue += tableTow->item(i, 6)->text().toInt();

        nettTotal += netto;
		grossTotal += gross;

	}

    discountTotal = (discountValue * nettTotal)/100;

	sum1->setText(sett().numberToString(nettTotal, 'f', 2));
	sum2->setText(sett().numberToString(discountTotal, 'f', 2));
	sum3->setText(sett().numberToString(grossTotal, 'f', 2));

   qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  << "EXIT";

}

/** Number Counts
 *  Used while populating invoice symbol, fills zeros into invoice symbol
 */

QString Faktura::numbersCount(int in, int x) {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

	QString tmp2, tmp = sett().numberToString(in);
	tmp2 = "";
	int incr = x - tmp.length();

	for (int i = 0; i < incr; ++i)
		tmp2 += "0";

	return tmp2 + tmp;
}

/** Saves width of the columns
 */

void Faktura::saveColumnsWidth() {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

	sett().beginGroup("fakturaForm");

    for (int i = 0; i < 11; ++i)
		sett().setValue("towCol" + sett().numberToString(i), tableTow->columnWidth(i));

	sett().endGroup();
}

