#include <QTextEdit>
#include <QObject>

#include "SmtpClient-for-Qt/src/smtpclient.h"
#include "SmtpClient-for-Qt/src/mimetext.h"
#include "Send.h"
#include "Buyers.h"
#include "IDataLayer.h"
#include "ConvertAmount.h"
#include "Invoice.h"
#include "Const.h"
#include "Correction.h"
#include "Invoice.h"
#include "Bill.h"
#include "InvoiceGross.h"
#include "Duplicate.h"
#include "InvoiceRR.h"
#include "CorrectGross.h"


Send::Send(QVector<BuyerData> buyersList, QVector<InvoiceData> invList, QWidget *parent)
    : QWizard(parent)
{
    bList = buyersList;
    iList = invList;
    addPage(new IntroPage);
    addPage(new ClassInvoicePage(bList,iList));
    addPage(new EmailPage);
    addPage(new ConclusionPage(qobject_cast<MainWindow*>(parent)));

    setWindowTitle(trUtf8("Generowanie wiadomości"));
}

void Send::accept()
{

    // -------------------

    SmtpClient smtp(field("host").toString(), field("port").toInt(), SmtpClient::SslConnection);

        // We need to set the username (your email address) and the password
        // for smtp authentification.

        smtp.setUser(field("user").toString());
        smtp.setPassword(field("password").toString());

        // Now we create a MimeMessage object. This will be the email.
        QSettings settings("elinux", "user");

        settings.beginGroup("choosenSeller");

        MimeMessage message;

        message.setSender(new EmailAddress(settings.value("email").toString(), settings.value("name").toString()));
        message.addRecipient(new EmailAddress(field("Email").toString(), field("nameData").toString()));
        message.setSubject(field("Title").toString());
        settings.endGroup();

        // Now add some text to the email.
        // First we create a MimeText object.

        MimeText text;

        text.setText(field("Message").toString());

        // Now add it to the mail

        message.addPart(&text);

        // Now we can send the mail

        if (smtp.connectToHost()) QMessageBox::information(this, "Łączenie z hostem", "Połączenie z hostem zakończyło się sukcesem");
        else QMessageBox::information(this, "Łączenie z hostem", "Połączenie z hostem nie powiodło się");
        smtp.login();
        if (smtp.sendMail(message)) QMessageBox::information(this, "Wysyłanie wiadomości", "Wiadomość została poprawnie wysłana");
        else QMessageBox::warning(this, "Wysyłanie wiadomości", "Wiadomość nie mogła zostać wysłana. Wystąpił błąd.");
        smtp.quit();


    // -------------------

    QDialog::accept();
}


IntroPage::IntroPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(trUtf8("Wprowadzenie"));

    label = new QLabel(trUtf8("Generator pomoże w kolejnych krokach wysłać"
                              " e-mail z opcją wybierania kontrahenta oraz "
                              "faktury. Istnieje możliwość dodania jednego "
                              "z kilku szablonów tekstowych jako treść wiadomości."));
    label->setWordWrap(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    setLayout(layout);
}


ClassInvoicePage::ClassInvoicePage(QVector<BuyerData> buyList, QVector<InvoiceData> invList, QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Wybieranie danych"));
    setSubTitle(tr("Wybierz jednego z kontrahentów oraz fakturę jako załącznik"));
    bList = buyList;
    iList = invList;

    QHBoxLayout* mainHLayout = new QHBoxLayout();
    QVBoxLayout* secondVLayout = new QVBoxLayout();


    QLabel* invoices = new QLabel;
    invoices->setText(trUtf8("Wybierz fakturę"));

    invoicesList = new QTableWidget();
    invoicesList->setRowCount(iList.size());
    invoicesList->setColumnCount(5);
    invoicesList->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    invoicesList->setHorizontalHeaderLabels(QStringList() << trUtf8("Symbol") << trUtf8("Data") << trUtf8("Typ") << trUtf8("Nabywca") << trUtf8("NIP"));

    for (int i = 0; i < iList.size(); ++i) {

        invoicesList->setItem(i,0,new QTableWidgetItem(iList.at(i).invNr));
        invoicesList->setItem(i,1,new QTableWidgetItem(iList.at(i).sellingDate.toString("dd/MM/yyyy")));
        invoicesList->setItem(i,2,new QTableWidgetItem(iList.at(i).type));
        invoicesList->setItem(i,3,new QTableWidgetItem(iList.at(i).custName));
        invoicesList->setItem(i,4,new QTableWidgetItem(iList.at(i).custTic));

    }

    secondVLayout->addWidget(invoices);
    secondVLayout->addWidget(invoicesList);

    mainHLayout->addLayout(secondVLayout);

    setLayout(mainHLayout);

}


bool ClassInvoicePage::validatePage() {


    QLineEdit* QLineEmail = new QLineEdit;
    QLineEdit* QLineName = new QLineEdit;
    QLineEdit* QLineSymbol = new QLineEdit;
    QLineEdit* QLineType = new QLineEdit;
    QLineEdit* QLineCurr = new QLineEdit;
    QLineEdit* QLineShortType = new QLineEdit;
    QLineEdit* QLineFileName = new QLineEdit;


    if (invoicesList->currentRow() >= 0) {

        for (int i = 0; i < bList.size(); ++i) {

            if (invoicesList->item(invoicesList->currentRow(),3)->text() == bList.at(i).name &&
                    invoicesList->item(invoicesList->currentRow(),4)->text() == bList.at(i).tic) {


                QLineEmail->setText(bList.at(i).email);
            }

        }

        double res = 0;
        QString name = QString();


        for (int i = 0; i < iList.size(); ++i) {

            if (invoicesList->item(invoicesList->currentRow(),3)->text() == iList.at(i).custName &&
                    invoicesList->item(invoicesList->currentRow(),4)->text() == iList.at(i).custTic &&
                    invoicesList->item(invoicesList->currentRow(),0)->text() == iList.at(i).invNr) {


                name = iList.at(i).id;


                QDomDocument doc(sett().getInoiveDocName());
                QDomElement root;
                QDomElement purchaser;
                QDomElement product;
                QString fName = name;

                QFile file(sett().getInvoicesDir() + fName);
                QLineFileName->setText(file.fileName());


                if (!file.open(QIODevice::ReadOnly)) {

                    qDebug("file doesn't exist");


                } else {

                    QTextStream stream(&file);

                    if (!doc.setContent(stream.readAll())) {
                        qDebug("You can't read content from invoice");
                        file.close();

                    }
                }

                root = doc.documentElement();
                QLineSymbol->setText(root.attribute("no"));
                QDomNode tmp;
                tmp = root.firstChild();
                tmp = tmp.toElement().nextSibling(); // purchaser
                purchaser = tmp.toElement();

                tmp = tmp.toElement().nextSibling(); // product
                product = tmp.toElement();

                int goodsCount = product.childNodes().count();
                qDebug() << QString::number(goodsCount);
                int x = 0;
                QDomElement good;
                good = product.firstChild().toElement();

                static const char *goodsColumns[] = { "id", "name", "code", "PKWiU", "quantity",
                        "quantityType", "discount", "price", "nett", "vatBucket", "gross"};


                for (x = 0; x < goodsCount; ++x) {

                    double decimalPointsAmount1 = good.attribute(goodsColumns[10]).right(2).toInt() * 0.01;
                       res += sett().stringToDouble( good.attribute( goodsColumns[10] ));
                       res += decimalPointsAmount1;
                    if (good.nextSibling().toElement().tagName() == "product") good = good.nextSibling().toElement();
                    else break;
                }

                tmp = tmp.toElement().nextSibling();
                QDomElement additional = tmp.toElement();

                QLineCurr->setText(additional.attribute("currency"));


                file.close();

                QLineType->setText(transformType(iList.at(i).type));
                QLineShortType->setText(iList.at(i).type);

            }

        }

      QLineName->setText(invoicesList->item(invoicesList->currentRow(),3)->text());
      QLineSymbol->setText(invoicesList->item(invoicesList->currentRow(),0)->text());
      QLineEdit* sumD = new QLineEdit;
      sumD->setText(sett().numberToString(res));

       registerField("emailData", QLineEmail);
       registerField("nameData", QLineName);
       registerField("symbolData", QLineSymbol);
       registerField("sumData", sumD);
       registerField("invtypeData", QLineType);
       registerField("invTypeShort", QLineShortType);
       registerField("currData", QLineCurr);
       registerField("filenameData", QLineFileName);

       return true;
    }
    else {

       return false;
    }
}


EmailPage::EmailPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Przygotowywanie treści"));
    setSubTitle(tr("Wybierz jeden z szablonów do wygenerowania"
                   " treści lub wprowadź własną."));


    QVBoxLayout* QVMainLayout = new QVBoxLayout();
    QHBoxLayout* QLabelsLinesLayout = new QHBoxLayout();
    QVBoxLayout* QVLabelsLayout = new QVBoxLayout();
    QVBoxLayout* QVLinesLayout = new QVBoxLayout();

    QLabel* emailLabel = new QLabel;
    emailLabel->setText(trUtf8("Do: "));

    emailLine = new QLineEdit;
    emailLabel->setBuddy(emailLine);



    QLabel* copyLabel = new QLabel;
    copyLabel->setText(trUtf8("Kopia do: "));

    copyLine = new QLineEdit;
    copyLabel->setBuddy(copyLine);



    QLabel* titleLabel = new QLabel;
    titleLabel->setText(trUtf8("Tytuł: "));

    titleLine = new QLineEdit;
    titleLabel->setBuddy(titleLine);


    //attachFile = new QCheckBox("Załącz fakturę");


    QVLabelsLayout->addWidget(emailLabel);
    QVLabelsLayout->addWidget(copyLabel);
    QVLabelsLayout->addWidget(titleLabel);
    //QVLabelsLayout->addWidget(attachFile);

    QVLinesLayout->addWidget(emailLine);
    QVLinesLayout->addWidget(copyLine);
    QVLinesLayout->addWidget(titleLine);

    QLabelsLinesLayout->addLayout(QVLabelsLayout);
    QLabelsLinesLayout->addLayout(QVLinesLayout);

    message = new QTextEdit;

    groupBox = new QGroupBox(trUtf8("&Lista szablonów"));
    QVBoxLayout *groupBoxLayout = new QVBoxLayout;


        QRadioButton *radioButton1 = new QRadioButton(trUtf8("&Szablon 1"));
        radioButton1->setCheckable(true);
        QRadioButton *radioButton2 = new QRadioButton(trUtf8("S&zablon 2"));
        radioButton2->setCheckable(true);
        QRadioButton *radioButton3 = new QRadioButton(trUtf8("&Szablon 3"));
        radioButton3->setCheckable(true);

        connect(radioButton1, &QAbstractButton::toggled,
                    this, &EmailPage::getTemplateOne);
        connect(radioButton2, &QAbstractButton::toggled,
                    this, &EmailPage::getTemplateTwo);
        connect(radioButton3, &QAbstractButton::toggled,
                    this, &EmailPage::getTemplateThree);

        groupBoxLayout->addWidget(radioButton1);
        groupBoxLayout->addWidget(radioButton2);
        groupBoxLayout->addWidget(radioButton3);


    groupBox->setLayout(groupBoxLayout);

    QVMainLayout->addLayout(QLabelsLinesLayout);
    QVMainLayout->addWidget(message);
    QVMainLayout->addWidget(groupBox);

    setLayout(QVMainLayout);

    registerField("Email",emailLine);
    registerField("CopyEmail", copyLine);
    registerField("Title", titleLine);
    registerField("Message", message, "plainText");
    //registerField("attachedFile", attachFile);
}


void EmailPage::initializePage()
{

    emailLine->setText(field("emailData").toString());
    QSettings settings("elinux", "user");

    settings.beginGroup("choosenSeller");

    copyLine->setText(settings.value("email").toString());
    settings.endGroup();

}


QString ClassInvoicePage::transformType(QString text)
{
    if (text == "FVAT") return s_INVOICE;
    if (text == "FPro") return s_PROFORMA;
    if (text == "korekta") return s_CORRECTION;
    if (text == "FBrutto") return s_FBRUTTO;
    if (text == "kbrutto") return s_FBRUTTO;
    if (text == "rachunek") return s_BILL;
    if (text == "duplikat") return s_DUPLICATE;
    if (text == "RR") return s_RR;
}


void EmailPage::getTemplateOne(bool checked)
{
    QSettings settings("elinux", "user");
    QMessageBox::warning(this, "Załączniki", "Chwilowo załączenie faktury nie jest jeszcze wdrożone. Proszę poczekać na implementację lub wysłać zwyklą wiadomość");

    settings.beginGroup("choosenSeller");
    titleLine->setText("Faktura od " + settings.value("name").toString() + " nr " + field("symbolData").toString());
    //attachFile->setChecked(true);

    message->setText("Szanowni Państwo, \n \tFirma " + settings.value("name").toString() + " przesyła Państwu dokument w formie elektronicznej: \n"
                      + field("invtypeData").toString() + " Nr. " + field("symbolData").toString() + " na kwotę: " + field("sumData").toString() + " " + field("currData").toString() + "\n\n"
                     "Dokument został wysłany jako załącznik do tej wiadomości. \n\n"
                     "Pozdrawiamy, \n" +
                     settings.value("name").toString());
    settings.endGroup();
}


void EmailPage::getTemplateTwo(bool checked)
{
    titleLine->setText("Przypomnienie o terminie zapłaty");
    //attachFile->setChecked(false);

    QSettings settings("elinux", "user");

    settings.beginGroup("choosenSeller");
    message->setText("Szanowni Państwo, \n \tUprzejmie informujemy, iż do dnia dzisiejszego nie otrzymaliśmy zapłaty należności wynikających z następujących faktur: \n"
                     + field("invtypeData").toString() + " Nr. " + field("symbolData").toString() + " na kwotę " + field("sumData").toString() + " " + field("currData").toString() + " \n\n"
                     "W związku z tym prosimy o uregulowanie w terminie 14 od dnia otrzymania niniejszego pisma wyżej wymienionych kwot wraz z odsetkami za opóźnienie w płatności każdej z faktur.\n\n"
                     "Wpłaty prosimy dokonać na podany niżej rachunek bankowy:\n\n"
                     + settings.value("account").toString() + "\n\n"
                     "Pozdrawiamy, \n" +
                     settings.value("name").toString());
    settings.endGroup();
}


void EmailPage::getTemplateThree(bool checked)
{
    titleLine->setText("Ostateczne wezwanie do zapłaty");
    //attachFile->setChecked(false);

    QSettings settings("elinux", "user");
    ConvertAmount* conv = new ConvertAmount;

    settings.beginGroup("choosenSeller");
    message->setText("Szanowni Państwo, \n \tNiniejszym wzywamy Państwa do zapłaty w terminie 14 dni od dnia doręczenia wezwania "
                     "kwoty " + field("sumData").toString() + " (słownie: " + conv->convertPL(field("sumData").toString(), field("currData").toString()) + " ) wraz z odsetkami za opóźnienie w płatnościach. \n"
                     "Powyższa należność wynika z następujących faktur: \n\n"
                     + field("invtypeData").toString() + " Nr. " + field("symbolData").toString() + "\n\n"
                     "Podaną wyżej kwotę prosimy wpłacić na podany niżej rachunek bankowy:\n\n"
                     + settings.value("bank").toString() + "\n"
                     + settings.value("account").toString() + "\n\n"
                     "Prosimy traktować niniejsze pismo jako ostateczne wezwanie przedprocesowe.\n\n"
                     "Pozdrawiamy, \n" +
                     settings.value("name").toString());
    settings.endGroup();
}


ConclusionPage::ConclusionPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(trUtf8("Zatwierdzenie"));

    QHBoxLayout* mainL = new QHBoxLayout;
    QVBoxLayout* labLay = new QVBoxLayout;
    QVBoxLayout* datLay = new QVBoxLayout;

    QLabel* lab1 = new QLabel;
    lab1->setText(trUtf8("Host: "));

    QLabel* lab2 = new QLabel;
    lab2->setText(trUtf8("Port: "));

    QLabel* lab3 = new QLabel;
    lab3->setText(trUtf8("Login: "));

    QLabel* lab4 = new QLabel;
    lab4->setText(trUtf8("Hasło: "));

    labLay->addWidget(lab1);
    labLay->addWidget(lab2);
    labLay->addWidget(lab3);
    labLay->addWidget(lab4);

    edit1 = new QLineEdit;
    lab1->setBuddy(edit1);

    edit2 = new QLineEdit;
    lab2->setBuddy(edit2);

    QLineEdit* edit3 = new QLineEdit;
    lab3->setBuddy(edit3);

    QLineEdit* edit4 = new QLineEdit;
    lab4->setBuddy(edit4);

    datLay->addWidget(edit1);
    datLay->addWidget(edit2);
    datLay->addWidget(edit3);
    datLay->addWidget(edit4);

    mainL->addLayout(labLay);
    mainL->addLayout(datLay);

    QHBoxLayout* mainLSmtp = new QHBoxLayout;
    QVBoxLayout* labLay2 = new QVBoxLayout;
    QVBoxLayout* datLay2 = new QVBoxLayout;

    groupBox = new QGroupBox(trUtf8("&Lista skrzynek pocztowych"));
    QVBoxLayout *groupBoxLayout = new QVBoxLayout;


        QRadioButton *radioButton1 = new QRadioButton(trUtf8("&Gmail"));
        radioButton1->setCheckable(true);
        QRadioButton *radioButton2 = new QRadioButton(trUtf8("o&2"));
        radioButton2->setCheckable(true);
        QRadioButton *radioButton3 = new QRadioButton(trUtf8("&Interia"));
        radioButton3->setCheckable(true);
        QRadioButton *radioButton4 = new QRadioButton(trUtf8("O&net"));
        radioButton4->setCheckable(true);
        QRadioButton *radioButton5 = new QRadioButton(trUtf8("&WP"));
        radioButton5->setCheckable(true);
        QRadioButton *radioButton6 = new QRadioButton(trUtf8("Y&ahoo"));
        radioButton6->setCheckable(true);
        QRadioButton *radioButton7 = new QRadioButton(trUtf8("&HotMail (stare serwery)"));
        radioButton7->setCheckable(true);
        QRadioButton *radioButton8 = new QRadioButton(trUtf8("G&azeta"));
        radioButton8->setCheckable(true);
        QRadioButton *radioButton9 = new QRadioButton(trUtf8("&Aol"));
        radioButton9->setCheckable(true);
        QRadioButton *radioButton10 = new QRadioButton(trUtf8("F&oxmail / QQMail"));
        radioButton10->setCheckable(true);
        QRadioButton *radioButton11 = new QRadioButton(trUtf8("&Outlook"));
        radioButton11->setCheckable(true);

        connect(radioButton1, &QAbstractButton::toggled,
                    this, &ConclusionPage::setGmail);
        connect(radioButton2, &QAbstractButton::toggled,
                    this, &ConclusionPage::seto2);
        connect(radioButton3, &QAbstractButton::toggled,
                    this, &ConclusionPage::setInteria);
        connect(radioButton4, &QAbstractButton::toggled,
                    this, &ConclusionPage::setOnet);
        connect(radioButton5, &QAbstractButton::toggled,
                    this, &ConclusionPage::setWP);
        connect(radioButton6, &QAbstractButton::toggled,
                    this, &ConclusionPage::setYahoo);
        connect(radioButton7, &QAbstractButton::toggled,
                    this, &ConclusionPage::setHotMail);
        connect(radioButton8, &QAbstractButton::toggled,
                    this, &ConclusionPage::setGazeta);
        connect(radioButton9, &QAbstractButton::toggled,
                    this, &ConclusionPage::setAol);
        connect(radioButton10, &QAbstractButton::toggled,
                    this, &ConclusionPage::setFoxMail);
        connect(radioButton11, &QAbstractButton::toggled,
                    this, &ConclusionPage::setOutlook);

        groupBoxLayout->addWidget(radioButton1);
        groupBoxLayout->addWidget(radioButton2);
        groupBoxLayout->addWidget(radioButton3);
        groupBoxLayout->addWidget(radioButton4);
        groupBoxLayout->addWidget(radioButton5);
        groupBoxLayout->addWidget(radioButton6);
        groupBoxLayout->addWidget(radioButton7);
        groupBoxLayout->addWidget(radioButton8);
        groupBoxLayout->addWidget(radioButton9);
        groupBoxLayout->addWidget(radioButton10);
        groupBoxLayout->addWidget(radioButton11);


    groupBox->setLayout(groupBoxLayout);
    labLay2->addWidget(groupBox);

    // -----------

    QGroupBox* groupBox2 = new QGroupBox(trUtf8("&Lista protokołów"));
    QVBoxLayout *groupBoxLayout2 = new QVBoxLayout;


        QRadioButton *radioButton1_1 = new QRadioButton(trUtf8("&SSL"));
        radioButton1_1->setCheckable(true);
        QRadioButton *radioButton2_2 = new QRadioButton(trUtf8("T&CP"));
        radioButton2_2->setCheckable(true);
        QRadioButton *radioButton3_3 = new QRadioButton(trUtf8("&TLS"));
        radioButton3_3->setCheckable(true);

        connect(radioButton1_1, &QAbstractButton::toggled,
                    this, &ConclusionPage::setSSL);
        connect(radioButton2_2, &QAbstractButton::toggled,
                    this, &ConclusionPage::setTCP);
        connect(radioButton3_3, &QAbstractButton::toggled,
                    this, &ConclusionPage::setTLS);

        groupBoxLayout2->addWidget(radioButton1_1);
        groupBoxLayout2->addWidget(radioButton2_2);
        groupBoxLayout2->addWidget(radioButton3_3);


    groupBox2->setLayout(groupBoxLayout2);
    datLay2->addWidget(groupBox2);

    mainLSmtp->addLayout(labLay2);
    mainLSmtp->addLayout(datLay2);


    registerField("host", edit1);
    registerField("port", edit2);
    registerField("user", edit3);
    registerField("password", edit4);


    label = new QLabel;
    label->setWordWrap(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(mainL);
    layout->addLayout(mainLSmtp);
    layout->addWidget(label);
    setLayout(layout);
}


void ConclusionPage::initializePage()
{
  //  bool ifattach = field("attachedFile").toBool();
    checkedMailButton = false;
    protocol = QString();
    checkedMail = QString();
    checkedPortButton = false;


  //  if (ifattach) {
//
//    }

    QString finishText = wizard()->buttonText(QWizard::FinishButton);
    finishText.remove('&');
    label->setText(trUtf8("Wybierz \"%1\", żeby wysłać wiadomość.")
                   .arg(finishText));
}


void ConclusionPage::setHostPort(QString checked, QString protocol) {

    if (checked == "Gmail")
    {
        edit1->setText("smtp.gmail.com");

        if (protocol == "SSL") edit2->setText("465");
        else if (protocol == "TCP") { this->protocol = ""; edit2->setText(""); QMessageBox::information(this, "Protokół", "Do wysłania wiadomości z tej skrzynki pocztowej wybierz protokół SSL lub TLS."); }
        else if (protocol == "TLS") edit2->setText("587");
    }
    else if (checked == "Onet")
    {
        edit1->setText("smtp.poczta.onet.pl");

        if (protocol == "SSL") edit2->setText("465");
        else if (protocol == "TCP") { this->protocol = ""; edit2->setText(""); QMessageBox::information(this, "Protokół", "Do wysłania wiadomości z tej skrzynki pocztowej wybierz protokół SSL lub TLS."); }
        else if (protocol == "TLS") edit2->setText("587");
    }
    else if (checked == "o2")
    {
        edit1->setText("poczta.o2.pl");

        if (protocol == "SSL") edit2->setText("465");
        else if (protocol == "TCP") { this->protocol = ""; edit2->setText(""); QMessageBox::information(this, "Protokół", "Do wysłania wiadomości z tej skrzynki pocztowej wybierz protokół SSL lub TLS."); }
        else if (protocol == "TLS") edit2->setText("587");
    }
    else if (checked == "Interia")
    {
        edit1->setText("poczta.interia.pl");

        if (protocol == "SSL") edit2->setText("465");
        else if (protocol == "TCP") { this->protocol = ""; edit2->setText(""); QMessageBox::information(this, "Protokół", "Do wysłania wiadomości z tej skrzynki pocztowej wybierz protokół SSL lub TLS."); }
        else if (protocol == "TLS") edit2->setText("587");
    }
    else if (checked == "WP")
    {
        edit1->setText("smtp.wp.pl");

        if (protocol == "SSL") edit2->setText("465");
        else if (protocol == "TCP") { this->protocol = ""; edit2->setText(""); QMessageBox::information(this, "Protokół", "Do wysłania wiadomości z tej skrzynki pocztowej wybierz protokół SSL lub TLS."); }
        else if (protocol == "TLS") edit2->setText("587");
    }
    else if (checked == "Yahoo")
    {
        edit1->setText("smtp.mail.yahoo.com");

        if (protocol == "SSL") edit2->setText("465");
        else if (protocol == "TCP") { this->protocol = ""; edit2->setText(""); QMessageBox::information(this, "Protokół", "Do wysłania wiadomości z tej skrzynki pocztowej wybierz protokół SSL lub TLS."); }
        else if (protocol == "TLS") edit2->setText("587");
    }
    else if (checked == "Outlook")
    {
        edit1->setText("smtp-mail.outlook.com");

        if (protocol == "SSL") { this->protocol = ""; edit2->setText(""); QMessageBox::information(this, "Protokół", "Do wysłania wiadomości z tej skrzynki pocztowej wybierz protokół TLS lub TCP."); }
        else if (protocol == "TCP") edit2->setText("25");
        else if (protocol == "TLS") edit2->setText("587");
    }
    else if (checked == "Foxmail / QQMail")
    {
        edit1->setText("smtp.qq.com");

        if (protocol == "SSL") edit2->setText("465");
        else if (protocol == "TCP") edit2->setText("25");
        else if (protocol == "TLS") edit2->setText("587");
    }
    else if (checked == "Aol")
    {
        edit1->setText("smtp.aol.com");

        if (protocol == "SSL") { this->protocol = ""; edit2->setText(""); QMessageBox::information(this, "Protokół", "Do wysłania wiadomości z tej skrzynki pocztowej wybierz protokół TLS."); }
        else if (protocol == "TCP") { this->protocol = ""; edit2->setText(""); QMessageBox::information(this, "Protokół", "Do wysłania wiadomości z tej skrzynki pocztowej wybierz protokół TLS."); }
        else if (protocol == "TLS") edit2->setText("587");
    }
    else if (checked == "Gazeta")
    {
        edit1->setText("smtp.gazeta.pl");

        if (protocol == "SSL") edit2->setText("465");
        else if (protocol == "TCP") { this->protocol = ""; edit2->setText(""); QMessageBox::information(this, "Protokół", "Do wysłania wiadomości z tej skrzynki pocztowej wybierz protokół SSL."); }
        else if (protocol == "TLS") { this->protocol = ""; edit2->setText(""); QMessageBox::information(this, "Protokół", "Do wysłania wiadomości z tej skrzynki pocztowej wybierz protokół SSL."); }
    }
    else if (checked == "HotMail (stare serwery)")
    {
        edit1->setText("smtp.live.com");

        if (protocol == "SSL") { this->protocol = ""; edit2->setText(""); QMessageBox::information(this, "Protokół", "Do wysłania wiadomości z tej skrzynki pocztowej wybierz protokół TLS."); }
        else if (protocol == "TCP") { this->protocol = ""; edit2->setText(""); QMessageBox::information(this, "Protokół", "Do wysłania wiadomości z tej skrzynki pocztowej wybierz protokół TLS."); }
        else if (protocol == "TLS") edit2->setText("587");
    }
}


void ConclusionPage::setSSL(bool) {

    if (!checkedMailButton) QMessageBox::warning(this, "Zaznaczenie skrzynki pocztowej", "Zaznacz jeszcze jedną ze skrzynek pocztowych po lewej stronie.");
    checkedPortButton = true;
    protocol = "SSL";
    if (checkedMailButton) setHostPort(checkedMail, protocol);
}


void ConclusionPage::setTCP(bool) {

    if (!checkedMailButton) QMessageBox::warning(this, "Zaznaczenie skrzynki pocztowej", "Zaznacz jeszcze jedną ze skrzynek pocztowych po lewej stronie.");
    checkedPortButton = true;
    protocol = "TCP";
    if (checkedMailButton) setHostPort(checkedMail, protocol);
}


void ConclusionPage::setTLS(bool) {

    if (!checkedMailButton) QMessageBox::warning(this, "Zaznaczenie skrzynki pocztowej", "Zaznacz jeszcze jedną ze skrzynek pocztowych po lewej stronie.");
    checkedPortButton = true;
    protocol = "TLS";
    if (checkedMailButton) setHostPort(checkedMail, protocol);
}


void ConclusionPage::setGmail(bool) {

    checkedMailButton = true;
    checkedMail = "Gmail";
    if (checkedPortButton) setHostPort(checkedMail, protocol);
}


void ConclusionPage::setOnet(bool) {

    checkedMailButton = true;
    checkedMail = "Onet";
    if (checkedPortButton) setHostPort(checkedMail, protocol);
}


void ConclusionPage::seto2(bool) {

    checkedMailButton = true;
    checkedMail = "o2";
    if (checkedPortButton) setHostPort(checkedMail, protocol);
}


void ConclusionPage::setInteria(bool) {

    checkedMailButton = true;
    checkedMail = "Interia";
    if (checkedPortButton) setHostPort(checkedMail, protocol);
}


void ConclusionPage::setWP(bool) {

    checkedMailButton = true;
    checkedMail = "WP";
    if (checkedPortButton) setHostPort(checkedMail, protocol);
}


void ConclusionPage::setYahoo(bool) {

    checkedMailButton = true;
    checkedMail = "Yahoo";
    if (checkedPortButton) setHostPort(checkedMail, protocol);
}


void ConclusionPage::setHotMail(bool) {

    checkedMailButton = true;
    checkedMail = "HotMail (stare serwery)";
    if (checkedPortButton) setHostPort(checkedMail, protocol);
}


void ConclusionPage::setGazeta(bool) {

    checkedMailButton = true;
    checkedMail = "Gazeta";
    if (checkedPortButton) setHostPort(checkedMail, protocol);
}


void ConclusionPage::setAol(bool) {

    checkedMailButton = true;
    checkedMail = "Aol";
    if (checkedPortButton) setHostPort(checkedMail, protocol);
}


void ConclusionPage::setFoxMail(bool) {

    checkedMailButton = true;
    checkedMail = "Foxmail / QQMail";
    if (checkedPortButton) setHostPort(checkedMail, protocol);
}


void ConclusionPage::setOutlook(bool) {

    checkedMailButton = true;
    checkedMail = "Outlook";
    if (checkedPortButton) setHostPort(checkedMail, protocol);
}
