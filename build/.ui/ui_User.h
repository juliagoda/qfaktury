/********************************************************************************
** Form generated from reading UI file 'User.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
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
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_User
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QHBoxLayout *hboxLayout1;
    QVBoxLayout *vboxLayout;
    QLabel *textLabel1;
    QLabel *textLabel3;
    QLabel *textLabel4;
    QLabel *textLabel2;
    QLabel *textLabel5;
    QLabel *label;
    QLabel *label_2;
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
    QLineEdit *accountEdit;
    QLineEdit *bankNameEdit;
    QLineEdit *bicSwiftEdit;
    QLineEdit *nipEdit;
    QComboBox *secIdType;
    QLineEdit *regonEdit;
    QLineEdit *krsEdit;
    QLineEdit *phonEdit;
    QLineEdit *faxEdit;
    QLineEdit *emailEdit;
    QLineEdit *webEdit;

    void setupUi(QDialog *User)
    {
        if (User->objectName().isEmpty())
            User->setObjectName(QStringLiteral("User"));
        User->resize(408, 422);
        gridLayout = new QGridLayout(User);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
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

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setObjectName(QStringLiteral("hboxLayout1"));
        vboxLayout = new QVBoxLayout();
        vboxLayout->setSpacing(6);
        vboxLayout->setObjectName(QStringLiteral("vboxLayout"));
        textLabel1 = new QLabel(User);
        textLabel1->setObjectName(QStringLiteral("textLabel1"));
        textLabel1->setWordWrap(false);

        vboxLayout->addWidget(textLabel1);

        textLabel3 = new QLabel(User);
        textLabel3->setObjectName(QStringLiteral("textLabel3"));
        textLabel3->setWordWrap(false);

        vboxLayout->addWidget(textLabel3);

        textLabel4 = new QLabel(User);
        textLabel4->setObjectName(QStringLiteral("textLabel4"));
        textLabel4->setWordWrap(false);

        vboxLayout->addWidget(textLabel4);

        textLabel2 = new QLabel(User);
        textLabel2->setObjectName(QStringLiteral("textLabel2"));
        textLabel2->setWordWrap(false);

        vboxLayout->addWidget(textLabel2);

        textLabel5 = new QLabel(User);
        textLabel5->setObjectName(QStringLiteral("textLabel5"));
        textLabel5->setWordWrap(false);

        vboxLayout->addWidget(textLabel5);

        label = new QLabel(User);
        label->setObjectName(QStringLiteral("label"));

        vboxLayout->addWidget(label);

        label_2 = new QLabel(User);
        label_2->setObjectName(QStringLiteral("label_2"));

        vboxLayout->addWidget(label_2);

        textLabel2_2 = new QLabel(User);
        textLabel2_2->setObjectName(QStringLiteral("textLabel2_2"));
        textLabel2_2->setWordWrap(false);

        vboxLayout->addWidget(textLabel2_2);

        textLabel2_2_2_2 = new QLabel(User);
        textLabel2_2_2_2->setObjectName(QStringLiteral("textLabel2_2_2_2"));
        textLabel2_2_2_2->setWordWrap(false);

        vboxLayout->addWidget(textLabel2_2_2_2);

        textLabel2_2_2 = new QLabel(User);
        textLabel2_2_2->setObjectName(QStringLiteral("textLabel2_2_2"));
        textLabel2_2_2->setWordWrap(false);

        vboxLayout->addWidget(textLabel2_2_2);

        label_3 = new QLabel(User);
        label_3->setObjectName(QStringLiteral("label_3"));

        vboxLayout->addWidget(label_3);

        telLabel = new QLabel(User);
        telLabel->setObjectName(QStringLiteral("telLabel"));

        vboxLayout->addWidget(telLabel);

        label_4 = new QLabel(User);
        label_4->setObjectName(QStringLiteral("label_4"));

        vboxLayout->addWidget(label_4);

        emailLabel = new QLabel(User);
        emailLabel->setObjectName(QStringLiteral("emailLabel"));

        vboxLayout->addWidget(emailLabel);

        wwwLabel = new QLabel(User);
        wwwLabel->setObjectName(QStringLiteral("wwwLabel"));

        vboxLayout->addWidget(wwwLabel);


        hboxLayout1->addLayout(vboxLayout);

        vboxLayout1 = new QVBoxLayout();
        vboxLayout1->setSpacing(6);
        vboxLayout1->setObjectName(QStringLiteral("vboxLayout1"));
        nameEdit = new QLineEdit(User);
        nameEdit->setObjectName(QStringLiteral("nameEdit"));

        vboxLayout1->addWidget(nameEdit);

        placeEdit = new QLineEdit(User);
        placeEdit->setObjectName(QStringLiteral("placeEdit"));

        vboxLayout1->addWidget(placeEdit);

        codeEdit = new QLineEdit(User);
        codeEdit->setObjectName(QStringLiteral("codeEdit"));

        vboxLayout1->addWidget(codeEdit);

        addressEdit = new QLineEdit(User);
        addressEdit->setObjectName(QStringLiteral("addressEdit"));

        vboxLayout1->addWidget(addressEdit);

        accountEdit = new QLineEdit(User);
        accountEdit->setObjectName(QStringLiteral("accountEdit"));
        accountEdit->setMaxLength(34);

        vboxLayout1->addWidget(accountEdit);

        bankNameEdit = new QLineEdit(User);
        bankNameEdit->setObjectName(QStringLiteral("bankNameEdit"));

        vboxLayout1->addWidget(bankNameEdit);

        bicSwiftEdit = new QLineEdit(User);
        bicSwiftEdit->setObjectName(QStringLiteral("bicSwiftEdit"));

        vboxLayout1->addWidget(bicSwiftEdit);

        nipEdit = new QLineEdit(User);
        nipEdit->setObjectName(QStringLiteral("nipEdit"));
        nipEdit->setMaxLength(13);

        vboxLayout1->addWidget(nipEdit);

        secIdType = new QComboBox(User);
        secIdType->setObjectName(QStringLiteral("secIdType"));

        vboxLayout1->addWidget(secIdType);

        regonEdit = new QLineEdit(User);
        regonEdit->setObjectName(QStringLiteral("regonEdit"));

        vboxLayout1->addWidget(regonEdit);

        krsEdit = new QLineEdit(User);
        krsEdit->setObjectName(QStringLiteral("krsEdit"));

        vboxLayout1->addWidget(krsEdit);

        phonEdit = new QLineEdit(User);
        phonEdit->setObjectName(QStringLiteral("phonEdit"));

        vboxLayout1->addWidget(phonEdit);

        faxEdit = new QLineEdit(User);
        faxEdit->setObjectName(QStringLiteral("faxEdit"));

        vboxLayout1->addWidget(faxEdit);

        emailEdit = new QLineEdit(User);
        emailEdit->setObjectName(QStringLiteral("emailEdit"));

        vboxLayout1->addWidget(emailEdit);

        webEdit = new QLineEdit(User);
        webEdit->setObjectName(QStringLiteral("webEdit"));

        vboxLayout1->addWidget(webEdit);


        hboxLayout1->addLayout(vboxLayout1);


        gridLayout->addLayout(hboxLayout1, 0, 0, 1, 1);


        retranslateUi(User);
        QObject::connect(okButton, SIGNAL(clicked()), User, SLOT(okClick()));
        QObject::connect(cancelButton, SIGNAL(clicked()), User, SLOT(close()));

        QMetaObject::connectSlotsByName(User);
    } // setupUi

    void retranslateUi(QDialog *User)
    {
        User->setWindowTitle(QApplication::translate("User", "Dane firmy", Q_NULLPTR));
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
        textLabel2_2->setText(QApplication::translate("User", "NIP*:", Q_NULLPTR));
        textLabel2_2_2_2->setText(QApplication::translate("User", "Typ 2 Id:", Q_NULLPTR));
        textLabel2_2_2->setText(QApplication::translate("User", "Drugi Id:", Q_NULLPTR));
        label_3->setText(QApplication::translate("User", "Numer KRS: ", Q_NULLPTR));
        telLabel->setText(QApplication::translate("User", "Telefon:", Q_NULLPTR));
        label_4->setText(QApplication::translate("User", "Fax:", Q_NULLPTR));
        emailLabel->setText(QApplication::translate("User", "Email:", Q_NULLPTR));
        wwwLabel->setText(QApplication::translate("User", "Strona www:", Q_NULLPTR));
        accountEdit->setInputMask(QString());
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
    } // retranslateUi

};

namespace Ui {
    class User: public Ui_User {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USER_H
