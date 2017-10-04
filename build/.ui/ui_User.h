/********************************************************************************
** Form generated from reading UI file 'User.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USER_H
#define UI_USER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_User
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *hboxLayout;
    QPushButton *nextSeller;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QTabWidget *sellersList;
    QWidget *mainSeller;
    QHBoxLayout *horizontalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *usersMainLay;
    QVBoxLayout *vboxLayout;
    QLabel *textLabel1;
    QLabel *textLabel3;
    QLabel *textLabel4;
    QLabel *textLabel2;
    QLabel *textLabel5;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_5;
    QLabel *textLabel2_2;
    QLabel *textLabel2_2_2_2;
    QLabel *textLabel2_2_2;
    QLabel *label_3;
    QLabel *telLabel;
    QLabel *label_4;
    QLabel *emailLabel;
    QLabel *wwwLabel;
    QVBoxLayout *vboxLayout1;
    QLineEdit *nameEdit;
    QLineEdit *placeEdit;
    QLineEdit *codeEdit;
    QLineEdit *addressEdit;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout;
    QLineEdit *accountEdit;
    QLineEdit *bankNameEdit;
    QLineEdit *bicSwiftEdit;
    QPushButton *addAcc;
    QHBoxLayout *horizontalLayout_4;
    QComboBox *accountsCombo;
    QSpacerItem *horizontalSpacer;
    QPushButton *remAcc;
    QLineEdit *nipEdit;
    QComboBox *secIdType;
    QLineEdit *regonEdit;
    QLineEdit *krsEdit;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *addTel;
    QLineEdit *phonEdit;
    QComboBox *telsCombo;
    QPushButton *remTel;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *addFax;
    QLineEdit *faxEdit;
    QComboBox *faxesCombo;
    QPushButton *remFax;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *addEmail;
    QLineEdit *emailEdit;
    QComboBox *emailsCombo;
    QPushButton *remEmail;
    QLineEdit *webEdit;

    void setupUi(QDialog *User)
    {
        if (User->objectName().isEmpty())
            User->setObjectName(QStringLiteral("User"));
        User->resize(584, 650);
        gridLayout = new QGridLayout(User);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
        nextSeller = new QPushButton(User);
        nextSeller->setObjectName(QStringLiteral("nextSeller"));

        hboxLayout->addWidget(nextSeller);

        spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        okButton = new QPushButton(User);
        okButton->setObjectName(QStringLiteral("okButton"));
        okButton->setCursor(QCursor(Qt::PointingHandCursor));

        hboxLayout->addWidget(okButton);

        cancelButton = new QPushButton(User);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));
        cancelButton->setCursor(QCursor(Qt::PointingHandCursor));

        hboxLayout->addWidget(cancelButton);


        gridLayout->addLayout(hboxLayout, 1, 0, 1, 1);

        sellersList = new QTabWidget(User);
        sellersList->setObjectName(QStringLiteral("sellersList"));
        mainSeller = new QWidget();
        mainSeller->setObjectName(QStringLiteral("mainSeller"));
        horizontalLayout = new QHBoxLayout(mainSeller);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        scrollArea = new QScrollArea(mainSeller);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, -128, 532, 670));
        horizontalLayout_2 = new QHBoxLayout(scrollAreaWidgetContents);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        usersMainLay = new QHBoxLayout();
        usersMainLay->setSpacing(6);
        usersMainLay->setObjectName(QStringLiteral("usersMainLay"));
        vboxLayout = new QVBoxLayout();
        vboxLayout->setSpacing(6);
        vboxLayout->setObjectName(QStringLiteral("vboxLayout"));
        textLabel1 = new QLabel(scrollAreaWidgetContents);
        textLabel1->setObjectName(QStringLiteral("textLabel1"));
        textLabel1->setWordWrap(false);

        vboxLayout->addWidget(textLabel1);

        textLabel3 = new QLabel(scrollAreaWidgetContents);
        textLabel3->setObjectName(QStringLiteral("textLabel3"));
        textLabel3->setWordWrap(false);

        vboxLayout->addWidget(textLabel3);

        textLabel4 = new QLabel(scrollAreaWidgetContents);
        textLabel4->setObjectName(QStringLiteral("textLabel4"));
        textLabel4->setWordWrap(false);

        vboxLayout->addWidget(textLabel4);

        textLabel2 = new QLabel(scrollAreaWidgetContents);
        textLabel2->setObjectName(QStringLiteral("textLabel2"));
        textLabel2->setWordWrap(false);

        vboxLayout->addWidget(textLabel2);

        textLabel5 = new QLabel(scrollAreaWidgetContents);
        textLabel5->setObjectName(QStringLiteral("textLabel5"));
        textLabel5->setWordWrap(false);

        vboxLayout->addWidget(textLabel5);

        label = new QLabel(scrollAreaWidgetContents);
        label->setObjectName(QStringLiteral("label"));

        vboxLayout->addWidget(label);

        label_2 = new QLabel(scrollAreaWidgetContents);
        label_2->setObjectName(QStringLiteral("label_2"));

        vboxLayout->addWidget(label_2);

        label_5 = new QLabel(scrollAreaWidgetContents);
        label_5->setObjectName(QStringLiteral("label_5"));

        vboxLayout->addWidget(label_5);

        textLabel2_2 = new QLabel(scrollAreaWidgetContents);
        textLabel2_2->setObjectName(QStringLiteral("textLabel2_2"));
        textLabel2_2->setWordWrap(false);

        vboxLayout->addWidget(textLabel2_2);

        textLabel2_2_2_2 = new QLabel(scrollAreaWidgetContents);
        textLabel2_2_2_2->setObjectName(QStringLiteral("textLabel2_2_2_2"));
        textLabel2_2_2_2->setWordWrap(false);

        vboxLayout->addWidget(textLabel2_2_2_2);

        textLabel2_2_2 = new QLabel(scrollAreaWidgetContents);
        textLabel2_2_2->setObjectName(QStringLiteral("textLabel2_2_2"));
        textLabel2_2_2->setWordWrap(false);

        vboxLayout->addWidget(textLabel2_2_2);

        label_3 = new QLabel(scrollAreaWidgetContents);
        label_3->setObjectName(QStringLiteral("label_3"));

        vboxLayout->addWidget(label_3);

        telLabel = new QLabel(scrollAreaWidgetContents);
        telLabel->setObjectName(QStringLiteral("telLabel"));

        vboxLayout->addWidget(telLabel);

        label_4 = new QLabel(scrollAreaWidgetContents);
        label_4->setObjectName(QStringLiteral("label_4"));

        vboxLayout->addWidget(label_4);

        emailLabel = new QLabel(scrollAreaWidgetContents);
        emailLabel->setObjectName(QStringLiteral("emailLabel"));

        vboxLayout->addWidget(emailLabel);

        wwwLabel = new QLabel(scrollAreaWidgetContents);
        wwwLabel->setObjectName(QStringLiteral("wwwLabel"));

        vboxLayout->addWidget(wwwLabel);


        usersMainLay->addLayout(vboxLayout);

        vboxLayout1 = new QVBoxLayout();
        vboxLayout1->setSpacing(6);
        vboxLayout1->setObjectName(QStringLiteral("vboxLayout1"));
        nameEdit = new QLineEdit(scrollAreaWidgetContents);
        nameEdit->setObjectName(QStringLiteral("nameEdit"));

        vboxLayout1->addWidget(nameEdit);

        placeEdit = new QLineEdit(scrollAreaWidgetContents);
        placeEdit->setObjectName(QStringLiteral("placeEdit"));

        vboxLayout1->addWidget(placeEdit);

        codeEdit = new QLineEdit(scrollAreaWidgetContents);
        codeEdit->setObjectName(QStringLiteral("codeEdit"));

        vboxLayout1->addWidget(codeEdit);

        addressEdit = new QLineEdit(scrollAreaWidgetContents);
        addressEdit->setObjectName(QStringLiteral("addressEdit"));

        vboxLayout1->addWidget(addressEdit);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(5, 5, 5, 5);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(5, 5, 5, 5);
        accountEdit = new QLineEdit(scrollAreaWidgetContents);
        accountEdit->setObjectName(QStringLiteral("accountEdit"));
        accountEdit->setMaxLength(34);

        verticalLayout->addWidget(accountEdit);

        bankNameEdit = new QLineEdit(scrollAreaWidgetContents);
        bankNameEdit->setObjectName(QStringLiteral("bankNameEdit"));

        verticalLayout->addWidget(bankNameEdit);

        bicSwiftEdit = new QLineEdit(scrollAreaWidgetContents);
        bicSwiftEdit->setObjectName(QStringLiteral("bicSwiftEdit"));

        verticalLayout->addWidget(bicSwiftEdit);


        horizontalLayout_5->addLayout(verticalLayout);

        addAcc = new QPushButton(scrollAreaWidgetContents);
        addAcc->setObjectName(QStringLiteral("addAcc"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(addAcc->sizePolicy().hasHeightForWidth());
        addAcc->setSizePolicy(sizePolicy);
        addAcc->setMaximumSize(QSize(60, 60));

        horizontalLayout_5->addWidget(addAcc);


        vboxLayout1->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(5, 5, 5, 5);
        accountsCombo = new QComboBox(scrollAreaWidgetContents);
        accountsCombo->setObjectName(QStringLiteral("accountsCombo"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(accountsCombo->sizePolicy().hasHeightForWidth());
        accountsCombo->setSizePolicy(sizePolicy1);

        horizontalLayout_4->addWidget(accountsCombo);

        horizontalSpacer = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        remAcc = new QPushButton(scrollAreaWidgetContents);
        remAcc->setObjectName(QStringLiteral("remAcc"));
        sizePolicy.setHeightForWidth(remAcc->sizePolicy().hasHeightForWidth());
        remAcc->setSizePolicy(sizePolicy);
        remAcc->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_4->addWidget(remAcc);


        vboxLayout1->addLayout(horizontalLayout_4);

        nipEdit = new QLineEdit(scrollAreaWidgetContents);
        nipEdit->setObjectName(QStringLiteral("nipEdit"));
        nipEdit->setMaxLength(13);

        vboxLayout1->addWidget(nipEdit);

        secIdType = new QComboBox(scrollAreaWidgetContents);
        secIdType->setObjectName(QStringLiteral("secIdType"));

        vboxLayout1->addWidget(secIdType);

        regonEdit = new QLineEdit(scrollAreaWidgetContents);
        regonEdit->setObjectName(QStringLiteral("regonEdit"));

        vboxLayout1->addWidget(regonEdit);

        krsEdit = new QLineEdit(scrollAreaWidgetContents);
        krsEdit->setObjectName(QStringLiteral("krsEdit"));

        vboxLayout1->addWidget(krsEdit);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(5, 5, 5, 5);
        addTel = new QPushButton(scrollAreaWidgetContents);
        addTel->setObjectName(QStringLiteral("addTel"));
        sizePolicy.setHeightForWidth(addTel->sizePolicy().hasHeightForWidth());
        addTel->setSizePolicy(sizePolicy);
        addTel->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_3->addWidget(addTel);

        phonEdit = new QLineEdit(scrollAreaWidgetContents);
        phonEdit->setObjectName(QStringLiteral("phonEdit"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(phonEdit->sizePolicy().hasHeightForWidth());
        phonEdit->setSizePolicy(sizePolicy2);
        phonEdit->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_3->addWidget(phonEdit);

        telsCombo = new QComboBox(scrollAreaWidgetContents);
        telsCombo->setObjectName(QStringLiteral("telsCombo"));
        sizePolicy1.setHeightForWidth(telsCombo->sizePolicy().hasHeightForWidth());
        telsCombo->setSizePolicy(sizePolicy1);
        telsCombo->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_3->addWidget(telsCombo);

        remTel = new QPushButton(scrollAreaWidgetContents);
        remTel->setObjectName(QStringLiteral("remTel"));
        sizePolicy.setHeightForWidth(remTel->sizePolicy().hasHeightForWidth());
        remTel->setSizePolicy(sizePolicy);
        remTel->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_3->addWidget(remTel);


        vboxLayout1->addLayout(horizontalLayout_3);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(5, 5, 5, 5);
        addFax = new QPushButton(scrollAreaWidgetContents);
        addFax->setObjectName(QStringLiteral("addFax"));
        sizePolicy.setHeightForWidth(addFax->sizePolicy().hasHeightForWidth());
        addFax->setSizePolicy(sizePolicy);
        addFax->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_6->addWidget(addFax);

        faxEdit = new QLineEdit(scrollAreaWidgetContents);
        faxEdit->setObjectName(QStringLiteral("faxEdit"));
        sizePolicy2.setHeightForWidth(faxEdit->sizePolicy().hasHeightForWidth());
        faxEdit->setSizePolicy(sizePolicy2);
        faxEdit->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_6->addWidget(faxEdit);

        faxesCombo = new QComboBox(scrollAreaWidgetContents);
        faxesCombo->setObjectName(QStringLiteral("faxesCombo"));
        sizePolicy1.setHeightForWidth(faxesCombo->sizePolicy().hasHeightForWidth());
        faxesCombo->setSizePolicy(sizePolicy1);

        horizontalLayout_6->addWidget(faxesCombo);

        remFax = new QPushButton(scrollAreaWidgetContents);
        remFax->setObjectName(QStringLiteral("remFax"));
        sizePolicy.setHeightForWidth(remFax->sizePolicy().hasHeightForWidth());
        remFax->setSizePolicy(sizePolicy);
        remFax->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_6->addWidget(remFax);


        vboxLayout1->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(5, 5, 5, 5);
        addEmail = new QPushButton(scrollAreaWidgetContents);
        addEmail->setObjectName(QStringLiteral("addEmail"));
        sizePolicy.setHeightForWidth(addEmail->sizePolicy().hasHeightForWidth());
        addEmail->setSizePolicy(sizePolicy);
        addEmail->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_7->addWidget(addEmail);

        emailEdit = new QLineEdit(scrollAreaWidgetContents);
        emailEdit->setObjectName(QStringLiteral("emailEdit"));
        sizePolicy2.setHeightForWidth(emailEdit->sizePolicy().hasHeightForWidth());
        emailEdit->setSizePolicy(sizePolicy2);
        emailEdit->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_7->addWidget(emailEdit);

        emailsCombo = new QComboBox(scrollAreaWidgetContents);
        emailsCombo->setObjectName(QStringLiteral("emailsCombo"));
        sizePolicy1.setHeightForWidth(emailsCombo->sizePolicy().hasHeightForWidth());
        emailsCombo->setSizePolicy(sizePolicy1);

        horizontalLayout_7->addWidget(emailsCombo);

        remEmail = new QPushButton(scrollAreaWidgetContents);
        remEmail->setObjectName(QStringLiteral("remEmail"));
        sizePolicy.setHeightForWidth(remEmail->sizePolicy().hasHeightForWidth());
        remEmail->setSizePolicy(sizePolicy);
        remEmail->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_7->addWidget(remEmail);


        vboxLayout1->addLayout(horizontalLayout_7);

        webEdit = new QLineEdit(scrollAreaWidgetContents);
        webEdit->setObjectName(QStringLiteral("webEdit"));

        vboxLayout1->addWidget(webEdit);


        usersMainLay->addLayout(vboxLayout1);


        horizontalLayout_2->addLayout(usersMainLay);

        scrollArea->setWidget(scrollAreaWidgetContents);

        horizontalLayout->addWidget(scrollArea);

        sellersList->addTab(mainSeller, QString());

        gridLayout->addWidget(sellersList, 0, 0, 1, 1);


        retranslateUi(User);
        QObject::connect(okButton, SIGNAL(clicked()), User, SLOT(okClick()));
        QObject::connect(cancelButton, SIGNAL(clicked()), User, SLOT(close()));

        sellersList->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(User);
    } // setupUi

    void retranslateUi(QDialog *User)
    {
        User->setWindowTitle(QApplication::translate("User", "Dane firmy", Q_NULLPTR));
        nextSeller->setText(QApplication::translate("User", "Kolejny sprzedawca/odzia\305\202", Q_NULLPTR));
        okButton->setText(QApplication::translate("User", "O&K", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        okButton->setShortcut(QApplication::translate("User", "Alt+K", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        cancelButton->setText(QApplication::translate("User", "Can&cel", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        cancelButton->setShortcut(QApplication::translate("User", "Alt+C", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        textLabel1->setText(QApplication::translate("User", "Nazwa*:", Q_NULLPTR));
        textLabel3->setText(QApplication::translate("User", "Miejscowo\305\233\304\207*:", Q_NULLPTR));
        textLabel4->setText(QApplication::translate("User", "Kod*:", Q_NULLPTR));
        textLabel2->setText(QApplication::translate("User", "Adres*:", Q_NULLPTR));
        textLabel5->setText(QApplication::translate("User", "Nr konta*:", Q_NULLPTR));
        label->setText(QApplication::translate("User", "Nazwa banku:", Q_NULLPTR));
        label_2->setText(QApplication::translate("User", "Nr SWIFT/BIC:", Q_NULLPTR));
        label_5->setText(QString());
        textLabel2_2->setText(QApplication::translate("User", "NIP*:", Q_NULLPTR));
        textLabel2_2_2_2->setText(QApplication::translate("User", "Typ 2 Id:", Q_NULLPTR));
        textLabel2_2_2->setText(QApplication::translate("User", "Drugi Id:", Q_NULLPTR));
        label_3->setText(QApplication::translate("User", "Numer KRS: ", Q_NULLPTR));
        telLabel->setText(QApplication::translate("User", "Telefon:", Q_NULLPTR));
        label_4->setText(QApplication::translate("User", "Fax:", Q_NULLPTR));
        emailLabel->setText(QApplication::translate("User", "Email:", Q_NULLPTR));
        wwwLabel->setText(QApplication::translate("User", "Strona www:", Q_NULLPTR));
        accountEdit->setInputMask(QString());
        addAcc->setText(QApplication::translate("User", "Dodaj", Q_NULLPTR));
        remAcc->setText(QApplication::translate("User", "Usun", Q_NULLPTR));
        nipEdit->setInputMask(QString());
        secIdType->clear();
        secIdType->insertItems(0, QStringList()
         << QApplication::translate("User", "Brak", Q_NULLPTR)
         << QApplication::translate("User", "NUSP", Q_NULLPTR)
         << QApplication::translate("User", "REGON", Q_NULLPTR)
         << QApplication::translate("User", "PESEL", Q_NULLPTR)
         << QApplication::translate("User", "Dow\303\263d osobisty", Q_NULLPTR)
         << QApplication::translate("User", "Paszport", Q_NULLPTR)
        );
        addTel->setText(QApplication::translate("User", "Dodaj", Q_NULLPTR));
        remTel->setText(QApplication::translate("User", "Usun", Q_NULLPTR));
        addFax->setText(QApplication::translate("User", "Dodaj", Q_NULLPTR));
        remFax->setText(QApplication::translate("User", "Usun", Q_NULLPTR));
        addEmail->setText(QApplication::translate("User", "Dodaj", Q_NULLPTR));
        remEmail->setText(QApplication::translate("User", "Usun", Q_NULLPTR));
        sellersList->setTabText(sellersList->indexOf(mainSeller), QApplication::translate("User", "Dane g\305\202\303\263wne", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class User: public Ui_User {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USER_H
