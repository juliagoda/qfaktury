
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

#include "Invoice.h"
#include "BuyersList.h"
#include "GoodsList.h"
#include "ChangeAmount.h"
#include "CustomPayment.h"
#include "MainWindow.h"
#include "Buyers.h"
#include "IDataLayer.h"
#include "Settings.h"

#include "Const.h"


short invType;
Invoice* Invoice::m_instance = nullptr;


/** Constructor
 */

Invoice::Invoice(QWidget *parent, IDataLayer *dl, QString Inv) :
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

Invoice::~Invoice() {

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

Invoice* Invoice::instance()
{
    return m_instance;
}


QString const Invoice::getRet()
{
    return ret;
}


QString const Invoice::getfName()
{
    return fName;
}


void Invoice::setfName(QString text)
{
    fName = text;
}


QString const Invoice::getInvForm()
{
    return inv_form;
}


bool const Invoice::getKAdded()
{
    return kAdded;
}


/** Init method
 */

void Invoice::init() {

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

    if (sett().value("editSymbol").toBool()) invNr->setEnabled(false);
    else invNr->setEnabled(true);

	// set width of the columns on the products list
	sett().beginGroup("fakturaForm");

    tableGoods->setColumnWidth(0, 100); // index
    tableGoods->setColumnWidth(1, 100); // name
    tableGoods->setColumnWidth(2, 100); // code
    tableGoods->setColumnWidth(3, 100); // code
    tableGoods->setColumnWidth(4, 100); // amount
    tableGoods->setColumnWidth(5, 100); // unit
    tableGoods->setColumnWidth(6, 100); // discount
    tableGoods->setColumnWidth(7, 100); // unit price
    tableGoods->setColumnWidth(8, 100); // net
    tableGoods->setColumnWidth(9, 100); // vat
    tableGoods->setColumnWidth(10, 100); // net * (vat formula)

	sett().endGroup();

	// set all the dates to todays date -> could be logical date :)
	sellingDate->setDate(QDate::currentDate());
	productDate->setDate(QDate::currentDate());
	liabDate->setDate(QDate::currentDate());

	// connects
    connect(addGoodsBtn, SIGNAL(clicked()), this, SLOT(addGoods()));
    connect(buyerListGet, SIGNAL(clicked()), this, SLOT(getCustomer()));
    connect(rmGoodsBtn, SIGNAL(clicked()), this, SLOT(delGoods()));
    connect(editGoodsBtn, SIGNAL(clicked()), this, SLOT(editGoods()));
	connect(backBtn, SIGNAL(clicked()), this, SLOT(backBtnClick()));
	connect(closeBtn, SIGNAL(clicked()), this, SLOT(canQuit()));
    connect(saveBtn, SIGNAL(clicked()), this, SLOT(saveInvoice()));
    connect(printBtn, SIGNAL(clicked()), this, SLOT(makeInvoice()));
    connect(tableGoods, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(editGoods()));
    connect(tableGoods, SIGNAL(itemActivated(QTableWidgetItem *)), this, SLOT(tableActivated(QTableWidgetItem *)));
    connect(tableGoods, SIGNAL(itemClicked(QTableWidgetItem *)), this, SLOT(tableActivated(QTableWidgetItem *)));
    connect(additEdit, SIGNAL(textChanged(QString)), this, SLOT(textChanged(QString)));
    connect(paysCombo, SIGNAL(currentIndexChanged (QString)), this, SLOT(payTextChanged(QString)));
    connect(currCombo, SIGNAL(currentIndexChanged (QString)), this, SLOT(textChanged(QString)));
    connect(sellingDate, SIGNAL(dateChanged (QDate)), this, SLOT(dateChanged (QDate)));
    connect(productDate, SIGNAL(dateChanged (QDate)), this, SLOT(dateChanged (QDate)));
    connect(liabDate, SIGNAL(dateChanged (QDate)), this, SLOT(dateChanged (QDate)));
    connect(discountVal, SIGNAL(valueChanged(int)), this, SLOT(discountChange()));
	connect(constRab, SIGNAL(stateChanged(int)), this, SLOT(discountConstChange()));
    connect(addBuyerBtn, SIGNAL(clicked()), this, SLOT(buyerClick()));
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
    paysCombo->insertItems(0, sett().value("payments").toString().split("|"));
    currCombo->insertItems(0, sett().value("currencies").toString().split("|"));

	if (sett().value ("addText").toString().compare("") != 0 )
		additEdit->setText(sett().value("addText").toString());

    backBtnClick();

	// set window icon
	QIcon icon;
	icon.addPixmap(QPixmap(":/res/icons/nowa_faktura.png"),
			QIcon::Normal, QIcon::Off);
	this->setWindowIcon(icon);

    rmGoodsBtn->setEnabled(false);
    editGoodsBtn->setEnabled(false);
	liabDate->setEnabled(false);
    discountVal->setEnabled(false);

	canClose = true;
}


void Invoice::whatTypeFromTitle(QString title, bool ifForm, bool kadded, InvoiceType invTyp, int numbType)
{
    if (inv_form == title) {

        pforma = ifForm;
        kAdded = kadded;
        invType = invTyp;
        type = numbType;
    }
}

/**
 *  Returns invoice type
 */

QString Invoice::getInvoiceTypeAndSaveNr() {

         qDebug() << __FUNCTION__ << __LINE__ << __FILE__;

        ret = QString();

        if (inv_form == s_INVOICE) {
                ret = "FVAT";
                sett().setValue("fvat", invNr->text());
        } else if (inv_form == s_PROFORMA) {
                ret = "FPro";
                sett().setValue("fpro", invNr->text());
        } else if (inv_form == s_CORRECT_TITLE) {
                ret = trUtf8("korekta");
                sett().setValue("corrections", invNr->text());
        } else if (inv_form == s_DUPLICATE) {
                ret = trUtf8("duplikat");
                sett().setValue("dup", invNr->text());
        }

        return ret;
}

void Invoice::connectedWebsite(const QUrl& webExchRate) {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

    manager = new QNetworkAccessManager(this);

       // get url
       QUrl url = QUrl::fromEncoded(webExchRate.toEncoded());

       QFileInfo fileInfo(url.path());
       QString fileName = fileInfo.fileName();

       if (fileName.isEmpty())
           fileName = sett().getInvoicesDir() + "bureau.xml";


       if (file.exists()) {

           if (QFile::remove(fileName)) qDebug("Plik usunięto");
           else {

               QFile(fileName).setPermissions(QFileDevice::ReadOther | QFileDevice::WriteOther);
               if (QFile::remove(fileName)) qDebug("Plik usunięto");
           }
       }

       file.setFileName(fileName);


       if (!file.open(QIODevice::WriteOnly)) {
           file.setPermissions(QFileDevice::ReadOther | QFileDevice::WriteOther | QFileDevice::ReadUser | QFileDevice::ReadOwner | QFileDevice::WriteOwner | QFileDevice::WriteUser);
       }


       reply = manager->get(QNetworkRequest(url));

       connect(reply, SIGNAL(readyRead()),
                   this, SLOT(httpReadyRead()));

       connect(reply, SIGNAL(finished()),
                   this, SLOT(tellFinished()));

}

void Invoice::httpReadyRead()
{
    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

    if (file.exists()) {
        file.write(reply->readAll());
    }
}


void Invoice::tellFinished()
{
    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

    if (file.open(QIODevice::ReadOnly)) {

        if (!doc.setContent(&file)) {

          qDebug("You can't set content to correction xml");

        }

    } else {

        if (file.exists()) {

        file.setPermissions(QFileDevice::ReadOther | QFileDevice::WriteOther | QFileDevice::ReadUser | QFileDevice::ReadOwner | QFileDevice::WriteOwner | QFileDevice::WriteUser);

        }
    }

    sett().setValue("lastUpdateCur", doc.elementsByTagName(QString("lastBuildDate")).at(0).toElement().text());



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


QMap<QString,double> Invoice::getActualCurList() {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;


    QMap<QString,double> currencies;

    if (!file.open(QIODevice::ReadOnly)) {

        if (file.exists()) {

        file.setPermissions(QFileDevice::ReadOther | QFileDevice::ReadUser | QFileDevice::ReadOwner);

        }
    } else {

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

/*

Thanks to the algorithm it's no need to add every combination of currencies to QMap manually but only from
foreign to main currency in tableOfValues() function. List's order is not required, the most important thing
is first argument, that is the our main language

*/

void Invoice::algorithmCurrencies(QString mainEl, QStringList list, QMap<QString, double> & mappedList) {

    QStringList::const_iterator constIterator;
    QStringList::const_iterator constIteratorDepth;

        for (constIterator = list.constBegin(); constIterator != list.constEnd();
               ++constIterator) {

            for (constIteratorDepth = list.constBegin(); constIteratorDepth != list.constEnd();
                   ++constIteratorDepth) {

                if ((*constIterator).toLocal8Bit().constData() == (*constIteratorDepth).toLocal8Bit().constData()) continue;

                 QString desc = QString((*constIterator).toLocal8Bit().constData()) + "/" + QString((*constIteratorDepth).toLocal8Bit().constData());

                if (mappedList.contains(desc)) continue;


                if ((*constIterator).toLocal8Bit().constData() == mainEl) {

                    double result = 1/mappedList.value(QString((*constIteratorDepth).toLocal8Bit().constData()) + "/" + QString((*constIterator).toLocal8Bit().constData()));

                    mappedList.insert(desc, result);

                } else {

                    double result = mappedList.value(QString((*constIterator).toLocal8Bit().constData()) + "/" + mainEl) / mappedList.value(QString((*constIteratorDepth).toLocal8Bit().constData()) + "/" + mainEl);

                    mappedList.insert(desc, result);

                }
            }
        }
}


QMap<QString,double> Invoice::tableOfValues() {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

    QMap<QString,double> currencies;


    if (currencies.isEmpty()) {

        double eurToPln = getActualCurList().value("EUR");
        double usdToPln = getActualCurList().value("USD");
        double chfToPln = getActualCurList().value("CHF");
        double gbpToPln = getActualCurList().value("GBP");
        double rubToPln = getActualCurList().value("RUB");

        currencies.insert("EUR/PLN",eurToPln);
        currencies.insert("USD/PLN",usdToPln);
        currencies.insert("CHF/PLN",chfToPln);
        currencies.insert("GBP/PLN",gbpToPln);
        currencies.insert("RUB/PLN",rubToPln);

        QMap<QString,double>& r = currencies;
        QStringList langList = QStringList() << "PLN" << "EUR" << "USD" << "CHF" << "GBP" << "RUB";

        algorithmCurrencies("PLN", langList, r);
    }

    return currencies;

}

bool Invoice::ifUpdated()
{
    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;


   if (!file.open(QIODevice::ReadOnly)) {

       if (file.exists()) {

       file.setPermissions(QFileDevice::ReadOther | QFileDevice::ReadUser | QFileDevice::ReadOwner);

       }

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
        qDebug() << "Year: " << year;
        QString day = dateElements.at(1);
        qDebug() << "Month: " << helpMonths.value(dateElements.at(2));
        qDebug() << "Day: " << day;
        QString hour = hms.at(0);
        qDebug() << "Hour: " << hour;
        QString min = hms.at(1);
        qDebug() << "Min: " << min;
        QString sec = hms.at(2);
        qDebug() << "Sec: " << sec;

        QDateTime dateOfFile(QDate(year.toInt(), helpMonths.value(dateElements.at(2)), day.toInt()), QTime(hour.toInt(), min.toInt(), sec.toInt()));

        qDebug() << "file date: " << dateOfFile.toString();
        qDebug() << "now: " << dateNow.toString();
        qDebug() << "have passed: " << dateOfFile.secsTo(dateNow);

        if (dateOfFile.secsTo(dateNow) > 1800)
            return true;
        else
            return false;


    }

   file.close();

}


QString Invoice::checkInvCurr() {

    return currCombo->currentText().trimmed();
}


bool Invoice::convWarn()
{
    bool whatToDo = false;

    if (tableGoods->rowCount() == 0) {

        whatToDo = true;
        QMessageBox msgBox;
        msgBox.setText(trUtf8("Aby zmienić walutę, powinieneś dodać co najmniej jeden towar lub usługę"));
        msgBox.setInformativeText(trUtf8("Chcesz dodać towar lub usługę czy wrócić do głównego okna?"));
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Ok);
        int ret = msgBox.exec();

        switch (ret) {
            case QMessageBox::Ok:
                addGoods();
            break;

            case QMessageBox::Cancel:
                reject();
            break;
        }
    }

    return whatToDo;
}


void Invoice::convertCurrShort(QString btnText) {

    if (!convWarn()) {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

    file.setFileName(sett().getInvoicesDir() + "bureau.xml");
    pressedText = btnText;


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
}


// ---- SLOTS START  --//////////////////////////////////////////////////////////////////////////////////

void Invoice::changeToEUR() {

    convertCurrShort(konvEUR->text().trimmed());
}


void Invoice::changeToUSD() {

    convertCurrShort(konvUSD->text().trimmed());
}

void Invoice::changeToPLN() {

    convertCurrShort(konvPLN->text().replace("&","").trimmed());
}


void Invoice::changeToCHF() {

    convertCurrShort(konvCHF->text().replace("&","").trimmed());
}


void Invoice::changeToGBP() {

    convertCurrShort(konvGBP->text().replace("&","").trimmed());
}


void Invoice::changeToRUB() {

    convertCurrShort(konvRUB->text().replace("&","").trimmed());
}


const QString Invoice::pressedTxt()
{
    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

    return pressedText;
}


void Invoice::calcAll(const double& currVal)
{
    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

    double res1 = 0;
    double res2 = 0;
    double res3 = 0;

    if (sum1->text() != sett().numberToString(0,'f',2)) {
        res1 = sett().stringToDouble(sum1->text()) * currVal;
        qDebug() << "res1 for discount in calcAll(): " << res1;
    }

    if (sum2->text() != sett().numberToString(0,'f',2)) {
        res2 = sett().stringToDouble(sum2->text()) * currVal;
        qDebug() << "res2 for discount in calcAll(): " << res2;
    }

    if (sum3->text() != sett().numberToString(0,'f',2)) {
        res3 = sett().stringToDouble(sum3->text()) * currVal;
        qDebug() << "res3 for discount in calcAll(): " << res3;
    }

    sum1->setText(sett().numberToString(res1,'f',2));
    sum2->setText(sett().numberToString(res2,'f',2l));
    sum3->setText(sett().numberToString(res3,'f',2));


    if (tableGoods->rowCount() != 0) {

        for (int i = 0; i < tableGoods->rowCount(); i++) {

            double it2 = sett().stringToDouble(tableGoods->item(i,7)->text()) * currVal;
            tableGoods->item(i,7)->setText(sett().numberToString(it2,'f',2));
            double it3 = sett().stringToDouble(tableGoods->item(i,8)->text()) * currVal;
            tableGoods->item(i,8)->setText(sett().numberToString(it3,'f',2));
            double it4 = sett().stringToDouble(tableGoods->item(i,10)->text()) * currVal;
            tableGoods->item(i,10)->setText(sett().numberToString(it4,'f',2));
        }
    }

    if (paysCombo->currentText() == trUtf8("zaliczka")) {
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


void Invoice::buyerClick() {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

    Buyers *buyersWindow;
    buyersWindow = new Buyers(this, 0, dataLayer);

    if (buyersWindow->exec() == QDialog::Accepted) {

		kAdded = true;
        QStringList row = buyersWindow->getRetBuyer().split("|");
        buyerName->setText (row[0] + "," + row[3] + "," + row[6] + " " + row[2] + "," +  s_TIC + row[5] + "," + row[7] + "," + row[8] + "," + row[9] + "," + row[10]);
        buyerName->setCursorPosition(0);
    }

    delete buyersWindow;
    buyersWindow = NULL;
}


void Invoice::keyPressEvent(QKeyEvent * event) {

     qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

	if (event->key() == Qt::Key_Escape) {
		canQuit();
    }

}

/** Slot getCustomer
 *  Opens window with the list of the customers
 */

void Invoice::getCustomer () {

  qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

  BuyersList *buylistWindow = new BuyersList(this);

  if (buylistWindow->exec () == QDialog::Accepted)
    {
      buyerName->setText (buylistWindow->getRetBuyerList());
      buyerName->setCursorPosition (1);
      saveBtn->setEnabled(true);
      canClose = false;
    }

  delete buylistWindow;
  buylistWindow = NULL;
}

/** Slot
 *  Enables and disables rebatValue field
 */

void Invoice::discountConstChange(){

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

    if (constRab->isChecked()) {

        discountVal->setEnabled(true);
		saveBtn->setEnabled(true);
		calculateDiscount();
        calculateSum();

    } else {

        discountVal->setValue(0);
        discountVal->setEnabled(false);
	}
}

/** Slot discountChange
 *  Used to recalculate discount when spinBox arrows are pressed.
 */

void Invoice::discountChange() {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

	calculateDiscount();

    if (paysCombo->currentText() == trUtf8("zaliczka")) {

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

void Invoice::addGoods() {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

    GoodsList *goodslistWindow = new GoodsList(this);

    if (goodslistWindow->exec() == QDialog::Accepted) {

        MainWindow::insertRow(tableGoods, tableGoods->rowCount());
        QStringList row = goodslistWindow->getRetVal().split("|");
        int rowNum = tableGoods->rowCount() - 1;
        tableGoods->item(rowNum, 0)->setText(sett().numberToString(
                tableGoods->rowCount())); // id
        tableGoods->item(rowNum, 1)->setText(row[0]); // name
        tableGoods->item(rowNum, 2)->setText(row[1]); // code
        tableGoods->item(rowNum, 3)->setText(row[2]); // pkwiu
        tableGoods->item(rowNum, 4)->setText(row[3]); // quantity
        tableGoods->item(rowNum, 5)->setText(row[4]); // qType
        tableGoods->item(rowNum, 6)->setText(row[5]); // discount
        tableGoods->item(rowNum, 7)->setText(row[6]); // price
        tableGoods->item(rowNum, 8)->setText(row[7]); // nett
        tableGoods->item(rowNum, 9)->setText(row[8]); // vat
        tableGoods->item(rowNum, 10)->setText(row[9]); // gross

		saveBtn->setEnabled(true);
        canClose = false;

        if (constRab->isChecked()) calculateDiscount();

        calculateSum();
    }

    delete goodslistWindow;
    goodslistWindow = NULL;

    if (paysCombo->currentText() == trUtf8("zaliczka")) {

        if ((am1 + am2) != sett().stringToDouble(sum3->text())) {
            payTextChanged(trUtf8("zaliczka"));
        }

    }
}

/** Slot delTowar
 *  Remove the product from the list
 */


void Invoice::delGoods() {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

    tableGoods->removeRow(tableGoods->currentRow());

    for (int i = 0; i < tableGoods->rowCount(); ++i) {
        tableGoods->item(i, 0)->setText(sett().numberToString(i + 1));
    }

    if (tableGoods->rowCount() == 0) {
    paysCombo->setCurrentIndex(0);
    }

	calculateSum();
	saveBtn->setEnabled(true);
	canClose = false;
}

/** Slot editTowar
 *  Allows to edit selected product. Opens changeAmount window.
 */


void Invoice::editGoods() {

     qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;
	// we can only modify quantity

    goodsEdited = true;
    int cur = tableGoods->currentRow();

    if (cur >= 0) {

    ChangeAmount *changeQuant = new ChangeAmount(this);

    changeQuant->nameTow->setText(
            tableGoods-> item(tableGoods->currentRow(), 1)->text());

    changeQuant->codeTow->setText(
            tableGoods-> item(tableGoods->currentRow(), 2)->text());

    changeQuant->spinAmount->setValue(tableGoods-> item(tableGoods->currentRow(),
            4)->text().toInt());

    if (changeQuant->exec() == QDialog::Accepted) {

        int currentRow = tableGoods->currentRow();
        tableGoods->item(currentRow, 4)->setText(changeQuant->spinAmount->cleanText());
        saveBtn->setEnabled(true);
        canClose = false;
        calculateOneDiscount(currentRow);
        calculateSum();
    }

    delete changeQuant;
    changeQuant = NULL;

    } else if (tableGoods->rowCount() == 0) {

        QMessageBox msgBox;
        msgBox.setText(trUtf8("Nie ma na liście żadnych towarów, które można by było edytować. Kliknij na przycisk \"Dodaj\" i wybierz towar lub usługę z listy"));
        msgBox.setInformativeText(trUtf8("Chcesz potwierdzić by dokonać zmiany, czy anulować, by wyjść do głównego okna?"));
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Ok);
        int ret = msgBox.exec();

        switch (ret) {
          case QMessageBox::Ok:
                addGoods();
              break;

          case QMessageBox::Cancel:
              reject();
              break;
        }

    } else {

        QMessageBox msgBox;
        msgBox.setText(trUtf8("Musisz zaznaczyć towar, który chcesz edytować, klikając na określony rząd w tabeli"));
        msgBox.setIcon(QMessageBox::Information);
        int re = msgBox.exec();

        switch (re) {
          case QMessageBox::Ok:
               tableGoods->setCurrentCell(0,0);
              break;

          case QMessageBox::Cancel:
              reject();
              break;
        }

    }

    if (paysCombo->currentText() == trUtf8("zaliczka")) {

        if ((am1 + am2) != sett().stringToDouble(sum3->text())) {
            payTextChanged(trUtf8("zaliczka"));
        }

    }
     qDebug() << __FUNCTION__ << ": EXIT";
}

/** Slot
 *  Used populate invoice symbol
 */
void Invoice::backBtnClick() {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

    QString prefix, suffix;
    prefix = sett().value("prefix").toString();

    int nr = MainWindow::instance()->getMaxSymbol() + 1;
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
    invNr->setText(lastInvoice);
	saveBtn->setEnabled(true);
}

/** Slot
 *  Validate close and save if requested
 */

void Invoice::canQuit() {

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


void Invoice::tableActivated(QTableWidgetItem * item) {

     qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

    if (item != NULL || !item->text().isEmpty()) {
        rmGoodsBtn->setEnabled(true);
        editGoodsBtn->setEnabled(true);
    } else {
        rmGoodsBtn->setEnabled(false);
        editGoodsBtn->setEnabled(false);
    }
}

/** Slot payTextChanged
 *  Activates buttons
 */


void Invoice::payTextChanged(QString text) {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;
     qDebug() << __FUNCTION__ <<  paysCombo->currentIndex();


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

            paysCombo->setCurrentIndex(0);
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

void Invoice::textChanged(QString) {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;
    saveBtn->setEnabled(true);
	canClose = false;

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  << "EXIT";

}

/** Slot dateChanged
 *  Activates buttons
 */

void Invoice::dateChanged(QDate) {

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


void Invoice::rateDateChanged(QString date)
{
    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

    if (!rComboWasChanged) {

    qDebug() << "Chosen date of rate: " << date;
    QDomDocument doc(sett().getInoiveDocName());
    QDomElement root;
    QFile file(sett().getInvoicesDir() + prepayFile);

    QTextStream stream(&file);

    if (!file.open(QIODevice::ReadOnly) || !doc.setContent(stream.readAll())) {

        QFileInfo check_file(file.fileName());


        if (check_file.exists() && check_file.isFile()) {

        file.setPermissions(QFileDevice::ReadOther | QFileDevice::ReadUser | QFileDevice::ReadOwner);

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

        ratesCombo->setCurrentIndex(0);
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

            ratesCombo->setCurrentIndex(0);
        }
     }

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  << "EXIT";

}

/** Copy data from the screen to the object
 */

void Invoice::setData(InvoiceData &invData) {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

    invData.id = fName;
    invData.customer = buyerName->text();
    qDebug() << "buyerName->text() in setData(InvoiceData&):" << buyerName->text();
    invData.invNr = invNr->text();
	invData.sellingDate = sellingDate->date();
    invData.issueDate = productDate->date();

    if (constRab->isChecked())
        invData.discount = discountVal->value();
    else
        invData.discount = 0;

    // no, name, code, pkwiu, amount, unit, discount, unit price, net, vat, gross
    for (int i = 0; i < tableGoods->rowCount(); ++i) {
        ProductData product; //  = new ProductData();

        product.setId(tableGoods->item(i, 0)->text());
        product.setName(tableGoods->item(i, 1)->text());
        product.setCode(tableGoods->item(i, 2)->text());
        product.setPkwiu(tableGoods->item(i, 3)->text());
        product.setQuantity(tableGoods->item(i, 4)->text());
        product.setQuanType(tableGoods->item(i, 5)->text());
        product.setDiscount(tableGoods->item(i, 6)->text());
        double help = sett().stringToDouble(tableGoods->item(i, 7)->text());
        product.setPrice(sett().numberToString(help,'f',2));
        product.setNett(tableGoods->item(i, 8)->text());
        product.setVat(tableGoods->item(i, 9)->text());
        product.setGross(tableGoods->item(i, 10)->text());
        invData.products[i] = product;
    }

    invData.additText = additEdit->text();
    invData.paymentType = paysCombo->currentText();

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

void Invoice::getData(InvoiceData invData) {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

    buyerName->setText(invData.customer);
    invNr->setText(invData.invNr);
    sellingDate->setDate(invData.sellingDate );
	productDate->setDate(invData.issueDate);

    if (!invData.duplDate.isNull() && invData.duplDate.isValid()) dupDate = invData.duplDate;

    qDebug() << "DISCOUNT: " << invData.discount;
	if (invData.discount == 0) {

        discountVal->setValue(0);

	} else {

		constRab->setChecked(true);
        discountVal->setValue(invData.discount);
	}

    qDebug() << "DISCOUNT: " << invData.discount;
    qDebug() << "changed discountVal: " << discountVal->value();


    additEdit->setText(invData.additText);

    if (invData.paymentType == trUtf8("zaliczka")) {

        disconnect(paysCombo, SIGNAL(currentIndexChanged (QString)), this, SLOT(payTextChanged(QString)));
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
    paysCombo->setCurrentText(invData.paymentType);
    liabDate->setDate(invData.liabDate);


    if (invData.paymentType == trUtf8("zaliczka")) {
        connect(paysCombo, SIGNAL(currentIndexChanged (QString)), this, SLOT(payTextChanged(QString)));
        connect(ratesCombo, SIGNAL(currentIndexChanged (QString)), this, SLOT(rateDateChanged(QString)));

    }

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  << "EXIT";

}

/** Slot saveInvoice
 *  Generates Invoice XML
 */

bool Invoice::saveInvoice() {

     qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << fName;

	bool result = false;
	if (!validateForm()) return false;

	InvoiceData invData;
    setData(invData);


    result = dataLayer->invoiceInsertData(invData, type);
    ret = dataLayer->getRet();


    if (!result) {
        QMessageBox::warning(this,trUtf8("Zapis faktury"), trUtf8("Zapis faktury zakończył się niepowodzeniem. Sprawdź czy masz uprawnienia do zapisu lub odczytu w ścieżce ")
                                                                  + sett().getInvoicesDir() + trUtf8(" oraz czy ścieżka istnieje."));
    }

    saveBtn->setEnabled(false);
    rmGoodsBtn->setEnabled(false);
    editGoodsBtn->setEnabled(false);

    saveFailed = false;
    canClose = true;

	return result;
}

/** Slot makeInvoice
 *  Generate html with invoice and show Print Preview dialog
 */

void Invoice::makeInvoice() {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

    if (buyerName->text() == "") {

		QMessageBox::information(this, "QFaktury", trUtf8("Wybierz kontrahenta"),
				QMessageBox::Ok);
		return;
	}

    if (tableGoods->rowCount() == 0) {

		QMessageBox::information(this, "QFaktury", trUtf8("Nie ma towarów"),
		QMessageBox::Ok);
		return;
	}

	invStrList.clear();
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

void Invoice::printSlot(QPrinter *printer) {

     qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

    QTextDocument doc(invoiceType);
    QString s = QString();

    for (QStringList::iterator it = invStrList.begin(); it != invStrList.end(); ++it) {
        s += *it + "\n";
    }


    // qDebug of the whole invoice :)

	QFile file(sett().getWorkingDir() + "/invoice.html");

    if (!file.open(QIODevice::WriteOnly)) {

        QFileInfo check_file(file.fileName());

            if (check_file.exists() && check_file.isFile()) {

                QFile(file.fileName()).setPermissions(QFileDevice::WriteOwner);

            } else {

                QDir mainPath(sett().getWorkingDir());

                if (!mainPath.exists())
                    mainPath.mkpath(sett().getWorkingDir());

                file.setFileName(sett().getWorkingDir() + "/invoice.html");

                file.open(QIODevice::WriteOnly);
            }
    }

    QTextStream stream(&file);

    for (QStringList::Iterator it = invStrList.begin(); it
            != invStrList.end(); ++it)
        stream << *it << "\n";

    file.close();

    doc.setHtml(s);
    doc.print(printer);
}

/** Slot
 *  Print slot
 */

void Invoice::print() {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

	QPrinter printer(QPrinter::HighResolution);
	QPrintPreviewDialog preview(&printer, this);
	preview.setWindowFlags(Qt::Window);
	preview.setWindowTitle(invoiceType + s_WIN_PRINTPREVIEW);

	connect(&preview, SIGNAL(paintRequested(QPrinter *)), this, SLOT(printSlot(QPrinter *)));
    if (preview.exec() == 1) {

        QMessageBox::warning(this,trUtf8("Drukowanie"),trUtf8("Prawdopobnie nie masz skonfigurowanej drukarki. Wykrywana nazwa domyślnej drukarki to: ") + printer.printerName() +
                             trUtf8(". Status domyślnej drukarki (poprawny o ile drukarka ma możliwość raportowania statusu do systemu): ") + printer.printerState());
    }
}

// ---- SLOTS END --//////////////////////////////////////////////////////////////////////////////////
// ******************************** XML Helpers START **********************************************
/** Check if data on the form is correct
 */

bool Invoice::validateForm() {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

    if (buyerName->text() == "") {

        QMessageBox msgBox;
        msgBox.setText(trUtf8("Aby zapisać fakturę, powinieneś dodać co najmniej jednego kontrahenta"));
        msgBox.setInformativeText(trUtf8("Jeśli chcesz dodać kontrahenta, wciśnij - OK. Jeśli chcesz wrócić do głównego okna, wciśnij - Anuluj"));
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Ok);
        int ret = msgBox.exec();

        switch (ret) {
            case QMessageBox::Ok:
                getCustomer();
            break;

            case QMessageBox::Cancel:
                reject();
            break;
        }

		saveFailed = true;
		return false;
	}

    if (tableGoods->rowCount() == 0) {

        QMessageBox msgBox;
        msgBox.setText(trUtf8("Aby zapisać fakturę, powinieneś dodać co najmniej jeden towar lub usługę"));
        msgBox.setInformativeText(trUtf8("Jeśli chcesz dodać towar lub usługę, wciśnij - OK. Jeśli chcesz wrócić do głównego okna, wciśnij - Anuluj"));
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Ok);
        int ret = msgBox.exec();

        switch (ret) {
            case QMessageBox::Ok:
                addGoods();
            break;

            case QMessageBox::Cancel:
                reject();
            break;
        }

		saveFailed = true;
		return false;
    }
	return true;
}

// ******************************** XML Helpers END **********************************************

// Generate Invoice HTML methods --- START ---

void Invoice::makeInvoiceHeadarHTML() {


	invStrList += "<html><head>";
	invStrList += "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />"; //@TODO
    invStrList += "<meta name=\"creator\" value=\"https://github.com/juliagoda/qfaktury\" />";
    invStrList += "</head>";
    invStrList += "<title>"+ invoiceType  +"</title>";
    invStrList += "<style type=\"text/css\"> ";

	QFile file(sett().getTemplate());

    if (file.open(QIODevice::ReadOnly)) {

		QTextStream stream(&file);
        QString line = QString();

        while (!stream.atEnd()) {
			line = stream.readLine();
			invStrList += line;
        }

		file.close();
        ifCSS = true;

    } else {

        QFile file(sett().getEmergTemplate());

        qDebug() << "getting from additional black.css";

        if (file.open(QIODevice::ReadOnly)) {

            QTextStream stream(&file);
            QString line = QString();

            while (!stream.atEnd()) {
                line = stream.readLine();
                invStrList += line;
            }

            file.close();
            ifCSS = true;

        } else {


        QMessageBox::warning(this, "Brak szablonu", trUtf8("Brakuje najprawdopodobniej w twojej ścieżce uprawnień do odczytu lub ani ścieżka ") +
                                                           sett().getEmergTemplate() + trUtf8(", ani ") + sett().getTemplate() + trUtf8(" nie istnieją."));
        ifCSS = false;
        qDebug() << "Could not open CSS file: " << file.fileName();

        }
    }

	invStrList += "</style>";
    invStrList += "<body>";
}


void Invoice::makeInvoiceHeadar(bool sellDate, bool breakPage, bool original) {

	QString breakPageStr = "class=\"page_break\"";
	if (breakPage == false) breakPageStr = "";

    invStrList += "<table comment=\"headar table\" width=\"100%\" " + breakPageStr + ">";
	invStrList += "<tr>";
    invStrList += "<td width=\"60%\" align=\"center\" valign=\"bottom\">";
    invStrList += "<span class=\"stamp\">";
    QString logo = sett().value("logo").toString();

    if (logo != "") {
            invStrList += "<img src=\"" + logo + "\" width=\"100\" " + " height=\"100\"+ >";
    } else {
            invStrList += trUtf8("Pieczęć wystawcy");
    }

    invStrList += "</span>";
    invStrList += "</td>";

    if (sett().value("css").toString() == "tables.css") {

        invStrList += "<td id=\"invoiceInfo\" width=\"35%\" align=\"right\">";

        if (sett().value("css").toString() == "tables.css") {
            invStrList += "<table id=\"rightInvTable\" width=\"100%\" border=\"1\" cellspacing=\"0\" cellpadding=\"5\" >";

        } else {
            invStrList += "<table id=\"rightInvTable\" width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"5\" >";

        }

        invStrList += "<tr>";
        invStrList += "<td id=\"invFirstLine\" style=\"font-size:12pt; font-weight:600\">";
        invStrList += invoiceType + "<br/>";
        invStrList += trUtf8("Nr: ") + invNr->text() + "</td>";
        invStrList += "</tr>";
        invStrList += "<tr>";
        invStrList += "<td class=\"dates\">" + trUtf8("Data wystawienia: ")
                        + productDate->date().toString(sett().getDateFormat()) + "</td>";

        invStrList += "</tr>";
        invStrList += "<tr><td>";
        if (sellDate)
        invStrList += trUtf8("Data sprzedaży: ")
                + sellingDate->date().toString(sett().getDateFormat())
                + "</td>";
        invStrList += "</tr>";

        invStrList += "</table></td><td width=\"3%\">&nbsp;</td>";

    } else {

    invStrList += "<td id=\"invoiceInfo\" align=\"right\">";
    invStrList += "<span id=\"invFirstLine\" style=\"font-size:12pt; font-weight:600\">";
    invStrList += invoiceType + "<br/>";
    invStrList += trUtf8("Nr: ") + invNr->text() + "<br></span>";
    invStrList += "<span class=\"dates\">" + trUtf8("Data wystawienia: ")
				    + productDate->date().toString(sett().getDateFormat()) + "<br>";

    if (sellDate)
    invStrList += trUtf8("Data sprzedaży: ")
            + sellingDate->date().toString(sett().getDateFormat())
            + "<br>";

    invStrList += "</span></td><td width=\"3%\">&nbsp;</td>";
    }

	invStrList += "</tr>";
	invStrList += "<tr>";
    invStrList += "<td class=\"origcopy\" colspan=\"2\" align=\"right\" valign=\"top\"><br>";

    if (original) {
        invStrList += trUtf8("ORYGINAŁ");
    } else {
        invStrList += trUtf8("KOPIA");
    }

        invStrList += "<hr/><br/>";


    invStrList += "<br></td><td width=\"3%\">&nbsp;</td>";
	invStrList += "</tr>";
	invStrList += "</table>";
    invStrList += "</td></tr>";

}


void Invoice::makeInvoiceBody() {

	invStrList += "<tr><td>";
	invStrList += "<table width=\"100%\" border=\"0\">";
	invStrList += "<tr class=\"persons\">";
    invStrList += "<td width=\"20\">&nbsp;</td>";
    invStrList += "<td class=\"buyerSeller\" width=\"48%\"> ";
    invStrList += "<p id=\"seller\">" + trUtf8("Sprzedawca:") + "</p><br/>";

    QSettings userSettings("elinux", "user");

    sett().beginGroup("printpos");

        if (sett().value("username").toBool() && (!userSettings.value("name").toString().trimmed().isEmpty()))
            invStrList += userSettings.value("name").toString() + "<br/>";

        if (sett().value("useradress").toBool() && (!userSettings.value("address").toString().trimmed().isEmpty()))
            invStrList += userSettings.value("address").toString() + "<br/>";

        if (sett().value("usercity").toBool() && (!userSettings.value("zip").toString().trimmed().isEmpty()))
			invStrList += userSettings.value("zip").toString() + " ";

        if (sett().value("usercity").toBool() && (!userSettings.value("city").toString().trimmed().isEmpty()))
            invStrList += userSettings.value("city").toString() + "<br/>";

        if (sett().value("usernip").toBool() && (!userSettings.value("tic").toString().trimmed().isEmpty()))
            invStrList += trUtf8("NIP: ") + userSettings.value("tic").toString() + "<br/>";

        if (sett().value("useraccount").toBool() && (!userSettings.value("account").toString().trimmed().isEmpty()))
            invStrList += trUtf8("Nr konta: ") + userSettings.value("account").toString().replace("-", " ") + "<br/>";

        if (sett().value("userphone").toBool() && (!userSettings.value("phone").toString().trimmed().isEmpty()))
            invStrList += trUtf8("Telefon: ") + userSettings.value("phone").toString() + "<br/>";

        if (sett().value("usermail").toBool() && (!userSettings.value("email").toString().trimmed().isEmpty()))
            invStrList += trUtf8("Email: ") + userSettings.value("email").toString() + "<br/>";

        if (sett().value("userwww").toBool() && (!userSettings.value("website").toString().trimmed().isEmpty()))
            invStrList += trUtf8("Strona www: ") + userSettings.value("website").toString() + "<br/>";

    sett().endGroup();

        invStrList += "</td>";
        invStrList += "<td width=\"20\">&nbsp;</td>";
        invStrList += "<td class=\"buyerSeller\" width=\"48%\">";
        invStrList += "<p id=\"seller\">" + trUtf8("Nabywca:") + "</p><br/>"; //+ buyerName->text().replace(",", "<br>") + "<br>";

        QStringList lista = buyerName->text().split(",");


    sett().beginGroup("printkontr");

        QString el1 = lista.at(0);
        if (sett().value("buyername").toBool() && (el1.trimmed() != "-"))
            invStrList += el1 + "<br>";

        QString el2 = lista.at(1);
        if (sett().value("buyercity").toBool() && (el2.trimmed() != "-"))
            invStrList += el2 + "<br>";

        QString el3 = lista.at(2);
        if (sett().value("buyeraddress").toBool() && (el3.trimmed() != "-"))
            invStrList += el3 + "<br>";

        QString el4 = lista.at(3);
        if (sett().value("buyernip").toBool() && (el4.replace(" ", "").replace(QObject::trUtf8("NIP:"),     "") != "-"))
            invStrList += trUtf8("NIP: ") + el4 + "<br>";

        QString el5 = lista.at(4);
        if (sett().value("buyeraccount").toBool() && (el5.replace(" ", "").replace(QObject::trUtf8("Konto:"), "") != "-"))
            invStrList += trUtf8("Nr konta: ") + el5 + "<br>";

        QString el6 = lista.at(5);
        if (sett().value("buyerphone").toBool() && (el6.replace(" ", "").replace(QObject::trUtf8("Tel:"), "") != "-"))
            invStrList += trUtf8("Telefon: ") + el6 + "<br>";

        QString el7 = lista.at(6);
        if (sett().value("buyermail").toBool() && (el7.replace(" ", "").replace(QObject::trUtf8("Email:"), "") != "-"))
            invStrList += trUtf8("Email: ") + el7 + "<br>";

        QString el8 = lista.at(7);
        if (sett().value("buyerwww").toBool() && (el8.replace(" ", "").replace(QObject::trUtf8("Strona:"), "") != ""))
            invStrList += trUtf8("Strona www: ") + el8 + "<br>";

    sett().endGroup();


    invStrList += "</td>";
	invStrList += "</tr>";
    invStrList += "</table>";
    invStrList += "<hr/>";
    invStrList += "</td></tr>";

}


void Invoice::makeInvoiceProductsHeadar() {

    int currentPercent = 0;
	invStrList += "<tr align=\"center\" valign=\"middle\" class=\"productsHeader\" >";

    sett().beginGroup("invoices_positions");

        if (sett().value("Lp").toBool()) {
            currentPercent = 3;
            invStrList += "<td align=\"center\" width=\""+ sett().numberToString(currentPercent) + "%\">" + trUtf8("Lp.") + "</td>";
            currentPercent = 0;
        } else {
            currentPercent += 3;
        }

        if (sett().value("Name").toBool()) {
            currentPercent += 13;
            invStrList += "<td align=\"center\" width=\""+ sett().numberToString(currentPercent) + "%\">" + trUtf8("Nazwa") + "</td>";
            currentPercent = 0;
        } else {
            currentPercent += 13;
        }

        if (sett().value("Code").toBool()) {
            currentPercent += 7;
            invStrList += "<td align=\"center\" width=\""+ sett().numberToString(currentPercent) + "%\">" + trUtf8("Kod") + "</td>";
            currentPercent = 0;
        } else {
            currentPercent += 7;
        }

        if (sett().value("pkwiu").toBool()) {
            currentPercent += 7;
            invStrList += "<td align=\"center\" width=\""+ sett().numberToString(currentPercent) + "%\">" + trUtf8("PKWiU") + "</td>";
            currentPercent = 0;
        } else {
            currentPercent += 7;
        }

        if (sett().value("amount").toBool()) {
            currentPercent += 9;
            invStrList += "<td align=\"center\" width=\""+ sett().numberToString(7) + "%\">" + trUtf8("Ilość") + "</td>";
            currentPercent = 0;
        } else {
            currentPercent += 9;
        }

        if (sett().value("unit").toBool()) {
            currentPercent += 3;
            invStrList += "<td align=\"center\" width=\""+ sett().numberToString(3) + "%\">" + trUtf8("jm.") + "</td>";
            currentPercent = 0;
        } else {
            currentPercent += 3;
        }

        if (sett().value("unitprice").toBool()) {
            currentPercent += 7;
            invStrList += "<td align=\"center\" width=\""+ sett().numberToString(currentPercent) + "%\">" + trUtf8("Cena jdn.") + "</td>";
            currentPercent = 0;
        } else {
            currentPercent += 7;
        }

        if (sett().value("netvalue").toBool()) {
            currentPercent += 8;
            invStrList += "<td align=\"center\" width=\""+ sett().numberToString(currentPercent) + "%\">" + trUtf8("Wartość Netto") + "</td>";
            currentPercent = 0;
        } else {
            currentPercent += 8;
        }

        if (sett().value("discountperc").toBool()) {
            currentPercent += 3;
            invStrList += "<td align=\"center\" width=\""+ sett().numberToString(3) + "%\">" + trUtf8("Rabat %") + "</td>";
            currentPercent = 0;
        } else {
            currentPercent += 3;
        }

        if (sett().value("discountval").toBool()) {
            currentPercent += 11;
            invStrList += "<td align=\"center\" width=\""+ sett().numberToString(currentPercent) + "%\">" + trUtf8("Rabat Wartość") + "</td>";
            currentPercent = 0;
        } else {
            currentPercent += 11;
        }

        if (sett().value("netafter").toBool()) {
            currentPercent += 7;
            invStrList += "<td align=\"center\" width=\""+ sett().numberToString(currentPercent) + "%\">" + trUtf8("Netto po rabacie") + "</td>";
            currentPercent = 0;
        } else {
            currentPercent += 7;
        }

        if (sett().value("vatval").toBool()) {
            currentPercent += 7;
            invStrList += "<td align=\"center\" width=\""+ sett().numberToString(7) + "%\">" + trUtf8("Stawka VAT") + "</td>";
            currentPercent = 0;
        } else {
            currentPercent += 7;
        }

        if (sett().value("vatprice").toBool()) {
            currentPercent += 7;
            invStrList += "<td align=\"center\" width=\""+ sett().numberToString(currentPercent) + "%\">" + trUtf8("Kwota Vat") + "</td>";
            currentPercent = 0;
        } else {
            currentPercent += 7;
        }

        if (sett().value("grossval").toBool()) {
            currentPercent += 8;
            invStrList += "<td align=\"center\" width=\""+ sett().numberToString(currentPercent) + "%\">" + trUtf8("Wartość Brutto") + "</td>";
            currentPercent = 0;
        } else {
            currentPercent += 8;
        }

    sett().endGroup();
	invStrList += "</tr>";

}

void Invoice::makeInvoiceProducts() {

    invStrList += "<tr><td>";

    invStrList += "<table border=\"2\" cellspacing=\"0\" cellpadding=\"5\" width=\"100%\">";

	makeInvoiceProductsHeadar();

    for (int i = 0; i < tableGoods->rowCount(); ++i) {

        invStrList += "<tr class=\"products\" >";
        // no, name, code, pkwiu, amount, unit, discount, unit price, net, vat, gross

        sett().beginGroup("invoices_positions");

            if (sett().value("Lp").toBool())
                invStrList += "<td>" + sett().numberToString(i + 1) + "</td>";

            if (sett().value("Name") .toBool())
                invStrList += "<td align=\"left\">" + tableGoods->item(i, 1)->text() + "</td>";

            if (sett().value("Code") .toBool())
                invStrList += "<td>" + tableGoods->item(i, 2)->text() + "</td>";

            if (sett().value("pkwiu") .toBool())
                invStrList += "<td>" + tableGoods->item(i, 3)->text() + "</td>";

            if (sett().value("amount") .toBool())
                invStrList += "<td>" + tableGoods->item(i, 4)->text() + "</td>";

            if (sett().value("unit") .toBool())
                invStrList += "<td>" + tableGoods->item(i, 5)->text() + "</td>";

            if (sett().value("unitprice") .toBool())
                invStrList += "<td>" + tableGoods->item(i, 7)->text() + "</td>";

            double discountVal = sett().stringToDouble(tableGoods->item(i, 8)->text()) *
                                (sett().stringToDouble(tableGoods->item(i, 6)->text()) * 0.01);

            double nettMinusDisc = sett().stringToDouble(tableGoods->item(i, 8)->text()) - discountVal;

            if (sett().value("netvalue") .toBool())
                invStrList += "<td>" + tableGoods->item(i, 8)->text()	+ "</td>"; // netto

            if (sett().value("discountperc") .toBool())
                invStrList += "<td>" + tableGoods->item(i, 6)->text()	+ "%</td>"; // rabat

            if (sett().value("discountval") .toBool())
                invStrList += "<td align=\"center\" >" + sett().numberToString(discountVal, 'f',  2)	+ "</td>";

            if (sett().value("netafter") .toBool())
                invStrList += "<td>" + sett().numberToString(nettMinusDisc, 'f', 2) + "</td>";

            if (sett().value("vatval") .toBool())
                invStrList += "<td>" + tableGoods->item(i, 9)->text()	+ "%</td>";

            double vatPrice = sett().stringToDouble(tableGoods->item(i, 10)->text())
                                - sett().stringToDouble(tableGoods->item(i, 8)->text()); // brutt-nett :)

            if (sett().value("vatprice") .toBool())
                invStrList += "<td>" + sett().numberToString(vatPrice, 'f', 2) + "</td>";

            if (sett().value("grossval") .toBool())
                invStrList += "<td>" + tableGoods->item(i, 10)->text() + "</td>";

        sett().endGroup();
        invStrList += "</tr>";
    }

	invStrList += "</table>";
}

void Invoice::makeInvoiceSumm() {

    double vatPrice = sett().stringToDouble(sum3->text()) - sett().stringToDouble(sum1->text());
    if (sett().value("css").toString() == "tables.css") {
        invStrList += "<br><table width=\"100%\" border=\"2\" cellspacing=\"0\" cellpadding=\"5\">";

    } else {
        invStrList += "<br><table width=\"100%\" border=\"0\" cellpadding=\"5\">";

    }
	invStrList += "<tr class=\"productsSumHeader\" valign=\"middle\">";
    invStrList += "<td id=\"notNec\" width=\"67%\" align=\"center\">&nbsp;</td>";
    invStrList += "<td width=\"11%\" align=\"center\">" + trUtf8("Wartość Netto") + "</td>"; // netto
    invStrList += "<td width=\"11%\" align=\"center\">" + trUtf8("Kwota VAT") + "</td>";// vat
    invStrList += "<td width=\"11%\" align=\"center\">" + trUtf8("Wartość Brutto") + "</td>"; // brutto
	invStrList += "</tr><tr class=\"productsSum\">";
    invStrList += "<td align=\"right\">" + trUtf8("Razem:") + "</td>";
    invStrList += "<td align=\"center\">" + sum1->text() + "</td>"; // netto
    invStrList += "<td align=\"center\">" + sett().numberToString(vatPrice, 'f', 2) + "</td>";// vat
    invStrList += "<td align=\"center\">" + sum3->text() + "</td>"; // brutto
	invStrList += "</tr>";
	invStrList += "</table><br><br>";

}


void Invoice::makeInvoiceSummAll() {

	invStrList += "</td></tr>"; // closing products row
    invStrList += "<tr comment=\"podsumowanie\"><td>";
    invStrList += "<table width=\"100%\" border=\"0\">";


	invStrList += "<tr class=\"summary\">";
    invStrList += "<td width=\"3%\">&nbsp;</td>";
    invStrList += "<td width=\"48%\"><span style=\"toPay\">";
    invStrList += trUtf8("Do zapłaty: ") + sum3->text() + " "

					+ currCombo->currentText() + "</span><br>";
    ConvertAmount* conv = new ConvertAmount();
    invStrList += trUtf8("słownie:")
				+ conv->convertPL(sum3->text(), currCombo->currentText()) + "<br>";
    delete conv;

    if (paysCombo->currentText() == trUtf8("gotówka")) {

        invStrList += trUtf8("forma płatności: ") + paysCombo->currentText() + "<br><b>";
        invStrList += trUtf8("Zapłacono gotówką") + "<br>";

     } else if (paysCombo->currentText() == trUtf8("zaliczka")) {

        invStrList += "<span style=\"toPay\">";

        ratesCombo->setCurrentIndex(0);
        QString whatMethod_one = QString();
        if (sendKindInfo->text() == trUtf8("gotówka")) whatMethod_one = trUtf8("gotówką");
        else whatMethod_one = trUtf8("przelewem");

        ratesCombo->setCurrentIndex(1);
        QString whatMethod_two = QString();
        if (sendKindInfo->text() == trUtf8("gotówka")) whatMethod_two = trUtf8("gotówką");
        else whatMethod_two = trUtf8("przelewem");

        ratesCombo->setCurrentIndex(0);

        invStrList += QString(trUtf8("Zapłacono ") + whatMethod_one + ": "
                    +  rateLabelInfo->text() + " " + currCombo->currentText() + " "
                    + ratesCombo->itemText(0) + "<br>");
        invStrList += QString(trUtf8("Zaległości ") + whatMethod_two + ": "
                    +  restLabelInfo->text() + " " + currCombo->currentText() + " "
                    + ratesCombo->itemText(1));
        invStrList += "</span>";

     } else if (paysCombo->currentText() == trUtf8("przelew")) {

        invStrList += trUtf8("forma płatności: ") + paysCombo->currentText() + "<br><b>";
        invStrList += trUtf8("Zapłacono przelewem") + "<br>";
        invStrList += "<span style=\"payDate\">";
        invStrList += trUtf8("termin płatności: ")
				+ liabDate->date().toString(sett().getDateFormat())	+ "<br>";
        invStrList += "</span>";

     } else {

        invStrList += trUtf8("forma płatności: ") + paysCombo->currentText() + "<br><b>";
        invStrList += "<span style=\"payDate\">";
        invStrList += trUtf8("termin płatności: ")
                + liabDate->date().toString(sett().getDateFormat())	+ "<br>";
        invStrList += "</span>";
     }


     invStrList += "</b><br><br>";
     invStrList += "<span class=\"additionalText\">"	+ additEdit->text() + "</span>";
     invStrList += "</td>";
     invStrList += "<td width=\"3%\">&nbsp;</td>";
     invStrList += "<td width=\"48%\" valign=\"top\">";

     if (sett().value("css").toString() == "tables.css") {
         invStrList += "<table id=\"totalRatesTable\" width=\"90%\" border=\"2\" cellspacing=\"0\" cellpadding=\"5\">";

     } else {
         invStrList += "<table id=\"totalRatesTable\" width=\"90%\" border=\"0\">";

     }
     invStrList += "<tr class=\"stawkiHeader\"><td colspan=\"4\">";
     invStrList += trUtf8("Ogółem stawkami:");
     invStrList += "</td></tr>";
     invStrList += getGroupedSums();
     invStrList += "<tr>";
     invStrList += "<td>&nbsp;</td>"; // netto
     invStrList += "<td>&nbsp;</td>"; // stawka
     invStrList += "<td>&nbsp;</td>"; // podatek
     invStrList += "<td>&nbsp;</td>"; // brutto
     invStrList += "</tr>";
     invStrList += "</table>";
     invStrList += "</td>";
     invStrList += "</tr>";
     invStrList += "</table>";
     invStrList += "</td></tr>";
}


void Invoice::makeInvoiceFooter() {

	invStrList += "<tr comment=\"podpis\" align=\"center\"><td>";
    invStrList += "<br><br><br><br>";
    invStrList += "<table width=\"80%\" border=\"0\">";
    invStrList += "<tr>";
    invStrList += "<td width=\"3%\">&nbsp;</td>";
    invStrList += "<td width=\"43%\" align=\"center\"> ";
    invStrList += "<hr width=\"100%\" noshade=\"noshade\" color=\"black\" />";
    invStrList += "</td>";
    invStrList += "<td width=\"7%\">&nbsp;</td>";
    invStrList += "<td width=\"3%\">&nbsp;</td>";
    invStrList += "<td width=\"43%\" align=\"center\"> ";
    invStrList += "<hr width=\"100%\" noshade=\"noshade\" color=\"black\" />";
    invStrList += "</td>";
    invStrList += "</tr>";
    invStrList += "<tr class=\"signature\">";
    invStrList += "<td width=\"3%\">&nbsp;</td>";
    invStrList += "<td width=\"43%\" align=\"center\"> ";
    invStrList += trUtf8("Imię i nazwisko osoby upoważnionej")
					+ "<br>" + trUtf8(" do wystawienia faktury VAT");
    invStrList += "</td>";
    invStrList += "<td width=\"7%\">&nbsp;</td>";
    invStrList += "<td width=\"3%\">&nbsp;</td>";
    invStrList += "<td width=\"43%\" align=\"center\">";
    invStrList += trUtf8("Imię i nazwisko osoby upoważnionej")
					+ "<br>" + trUtf8(" do odbioru faktury VAT");
    invStrList += "</td>";
    invStrList += "</tr>";
    invStrList += "</table>";
	invStrList += "</td></tr>";
	invStrList += "</table>";

}

void Invoice::makeInvoiceFooterHtml() {

	invStrList += "</body>";
	invStrList += "</html>";
}

/** getGroupedSums
 *  Groups prices by VAT
 */

QString Invoice::getGroupedSums() {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

    QStringList out;
    QStringList rates = sett().value("rates").toString().split("|");
    QMap<int, double> netRates;
    QMap<int, double> vatRates;
    QMap<int, double> grossRates;
    int ssize = rates.size();

    // no, name, code, pkwiu, amount, unit, discount, unit price, net, vat, gross
    for (int i = 0; i < tableGoods->rowCount(); ++i) {
        for (int y = 0; y < ssize; ++y) {

            if (rates[y] == tableGoods->item(i, 9)->text()) {

                netRates[y] += sett().stringToDouble(tableGoods->item(i, 8)->text());
                grossRates[y] += sett().stringToDouble(tableGoods->item(i, 10)->text());
                vatRates[y] = grossRates[y] - netRates[y];

            } else {

                netRates[y] += 0;
                grossRates[y] += 0;
                vatRates[y] += 0;
			}
		}
	}

    for (int y = 0; y < ssize; ++y) {

		out += "<tr class=\"stawki\">";
        out += "<td width=\"30%\">" + sett().numberToString(netRates[y], 'f', 2) + "</td>"; // net
        out += "<td width=\"10%\">" + rates[y] + "</td>"; // rate
        out += "<td width=\"30%\">" + sett().numberToString(vatRates[y], 'f', 2) + "</td>"; // tax
        out += "<td width=\"30%\">" + sett().numberToString(grossRates[y], 'f', 2) + "</td>"; // gross
		out += "</tr>";

    }

	return out.join(" ");
}

// Generate Invoice HTML methods --- END ---

/** Read data
 *  Used when editInvoice is invoked. Invoked from MainWindow class.
 */

void Invoice::readData(QString fraFile) {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;
    prepayFile = fraFile;
    qDebug() << "prepayFile w readData: " << prepayFile;
	backBtn->setEnabled(false);
    invNr->setEnabled(false);

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
void Invoice::setIsEditAllowed(bool isAllowed) {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

    if (!sett().value("editSymbol").toBool()) invNr->setEnabled(isAllowed);

	backBtn->setEnabled(isAllowed);
	sellingDate->setEnabled(isAllowed);
	productDate->setEnabled(isAllowed);
    tableGoods->setEnabled(isAllowed);
    discountVal->setEnabled(isAllowed);
    discountLabel->setEnabled(isAllowed);
    paysCombo->setEnabled(isAllowed);
	liabDate->setEnabled(isAllowed);
	additEdit->setEnabled(isAllowed);
    addGoodsBtn->setEnabled(isAllowed);
    rmGoodsBtn->setEnabled(isAllowed);
    editGoodsBtn->setEnabled(isAllowed);
	constRab->setEnabled(isAllowed);
    buyerListGet->setEnabled(isAllowed);
	currCombo->setEnabled(isAllowed);
	saveBtn->setEnabled(isAllowed);
    addBuyerBtn->setEnabled(isAllowed);
	liabDate->setEnabled(isAllowed);

    if (!isAllowed || discountVal->value() == 0) {

		constRab->setChecked(false);
        discountVal->setEnabled(false);

	} else {

		constRab->setChecked(true);
        discountVal->setEnabled(true);
	}

    if (isAllowed && (paysCombo->currentText() != trUtf8("przelew"))) liabDate->setEnabled(false);
    else liabDate->setEnabled(true);

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

void Invoice::calculateDiscount() {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

    for (int i = 0; i < tableGoods->rowCount(); ++i) {
		calculateOneDiscount(i);
	}

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  << "EXIT";

}

/** Caclulate Discount
 */

void Invoice::calculateOneDiscount(int i) {

     qDebug() << __FUNCTION__ << __LINE__ << __FILE__;

	double quantity = 0, vat = 0, gross = 0;
    double net = 0,  price = 0;
	double discountValue = 0, discount;

    qDebug() << "PRICE BEFORE: " << tableGoods->item(i, 7)->text();
    price = sett().stringToDouble(tableGoods->item(i, 7)->text());
    qDebug() << "PRICE AFTER: " << price;

	if (constRab->isChecked()) {

        qDebug() << "BEFORE discountVal->value()" << discountVal->value();
        discount = discountVal->value() * 0.01;
        qDebug() << "AFTER discountVal->value()" << discount;

	} else {

        qDebug() << "BEFORE tableGoods->item(i, 6)->text()" << tableGoods->item(i, 6)->text().toInt();
        discount = (tableGoods->item(i, 6)->text()).toInt() * 0.01;
        qDebug() << "AFTER tableGoods->item(i, 6)->text()" << discount;
	}

    quantity = tableGoods->item(i, 4)->text().toInt();
    qDebug() << "LOOK QUANTITY: " << quantity;
    net = (price * quantity);
    qDebug() << "LOOK NET: " << net;
    discountValue = net * discount;
    qDebug() << "LOOK DISCOUNTVALUE: " << discountValue;
    net -= discountValue;
    qDebug() << "LOOK NET FROM DISCOUNT: " << net;
    vat = tableGoods->item(i, 9)->text().toInt();
    gross = net * ((vat * 0.01) + 1);
    qDebug() << "LOOK GROSS: " << gross;


    qDebug() << price << quantity << net << discount << discountValue << vat << gross;

    tableGoods->item(i, 6)->setText(sett().numberToString(discount * 100, 'f', 0)); // discount
    qDebug() << "discount in table: " << tableGoods->item(i, 6)->text();
    tableGoods->item(i, 8)->setText(sett().numberToString(net)); // nett
    qDebug() << "net in table: " << tableGoods->item(i, 8)->text();
    tableGoods->item(i, 10)->setText(sett().numberToString(gross)); // gross
    qDebug() << "gross in table: " << tableGoods->item(i, 10)->text();


    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  << "EXIT";

}

/** Calculate sum
 */

void Invoice::calculateSum() {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

    double net = 0, price = 0, gross = 0;
    double discountValue = 0;

	nettTotal = 0;
	discountTotal = 0;
	grossTotal = 0;

    for (int i = 0; i < tableGoods->rowCount(); ++i) {

        price = sett().stringToDouble(tableGoods->item(i, 7)->text());

        double decimalPointsNetto = tableGoods->item(i, 8)->text().right(2).toInt() * 0.01;
        qDebug() << "decimalPointsNetto << " << decimalPointsNetto;
        double decimalPointsGross = tableGoods->item(i, 10)->text().right(2).toInt() * 0.01;
        qDebug() << "decimalPointsGross << " << decimalPointsGross;

        net = sett().stringToDouble(tableGoods->item(i, 8)->text());
        net += decimalPointsNetto;
        gross = sett().stringToDouble(tableGoods->item(i, 10)->text());
        gross += decimalPointsGross;
        discountValue += tableGoods->item(i, 6)->text().toInt();

        nettTotal += net;
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

QString Invoice::numbersCount(int in, int x) {

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

void Invoice::saveColumnsWidth() {

    qDebug() << "[" << __FILE__  << ": " << __LINE__ << "] " << __FUNCTION__  ;

	sett().beginGroup("fakturaForm");

    for (int i = 0; i < 11; ++i)
        sett().setValue("towCol" + sett().numberToString(i), tableGoods->columnWidth(i));

	sett().endGroup();
}

