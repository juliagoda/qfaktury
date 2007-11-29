/********************************************************************************
** Form generated from reading ui file 'user.ui'
**
** Created: Thu Nov 29 01:25:38 2007
**      by: Qt User Interface Compiler version 4.3.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_USER_H
#define UI_USER_H

#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

class Ui_Form2
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
    QLabel *textLabel2_2;
    QLabel *textLabel2_2_2_2;
    QLabel *textLabel2_2_2;
    QVBoxLayout *vboxLayout1;
    QLineEdit *nameEdit;
    QLineEdit *placeEdit;
    QLineEdit *codeEdit;
    QLineEdit *addressEdit;
    QLineEdit *accountEdit;
    QLineEdit *nipEdit;
    QComboBox *secIdType;
    QLineEdit *regonEdit;

    void setupUi(QDialog *Form2)
    {
    if (Form2->objectName().isEmpty())
        Form2->setObjectName(QString::fromUtf8("Form2"));
    Form2->resize(413, 314);
    gridLayout = new QGridLayout(Form2);
    gridLayout->setSpacing(6);
    gridLayout->setMargin(11);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    hboxLayout = new QHBoxLayout();
    hboxLayout->setSpacing(6);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout->addItem(spacerItem);

    okButton = new QPushButton(Form2);
    okButton->setObjectName(QString::fromUtf8("okButton"));

    hboxLayout->addWidget(okButton);

    cancelButton = new QPushButton(Form2);
    cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

    hboxLayout->addWidget(cancelButton);


    gridLayout->addLayout(hboxLayout, 1, 0, 1, 1);

    hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setSpacing(6);
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    vboxLayout = new QVBoxLayout();
    vboxLayout->setSpacing(6);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    textLabel1 = new QLabel(Form2);
    textLabel1->setObjectName(QString::fromUtf8("textLabel1"));
    textLabel1->setWordWrap(false);

    vboxLayout->addWidget(textLabel1);

    textLabel3 = new QLabel(Form2);
    textLabel3->setObjectName(QString::fromUtf8("textLabel3"));
    textLabel3->setWordWrap(false);

    vboxLayout->addWidget(textLabel3);

    textLabel4 = new QLabel(Form2);
    textLabel4->setObjectName(QString::fromUtf8("textLabel4"));
    textLabel4->setWordWrap(false);

    vboxLayout->addWidget(textLabel4);

    textLabel2 = new QLabel(Form2);
    textLabel2->setObjectName(QString::fromUtf8("textLabel2"));
    textLabel2->setWordWrap(false);

    vboxLayout->addWidget(textLabel2);

    textLabel5 = new QLabel(Form2);
    textLabel5->setObjectName(QString::fromUtf8("textLabel5"));
    textLabel5->setWordWrap(false);

    vboxLayout->addWidget(textLabel5);

    textLabel2_2 = new QLabel(Form2);
    textLabel2_2->setObjectName(QString::fromUtf8("textLabel2_2"));
    textLabel2_2->setWordWrap(false);

    vboxLayout->addWidget(textLabel2_2);

    textLabel2_2_2_2 = new QLabel(Form2);
    textLabel2_2_2_2->setObjectName(QString::fromUtf8("textLabel2_2_2_2"));
    textLabel2_2_2_2->setWordWrap(false);

    vboxLayout->addWidget(textLabel2_2_2_2);

    textLabel2_2_2 = new QLabel(Form2);
    textLabel2_2_2->setObjectName(QString::fromUtf8("textLabel2_2_2"));
    textLabel2_2_2->setWordWrap(false);

    vboxLayout->addWidget(textLabel2_2_2);


    hboxLayout1->addLayout(vboxLayout);

    vboxLayout1 = new QVBoxLayout();
    vboxLayout1->setSpacing(6);
    vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
    nameEdit = new QLineEdit(Form2);
    nameEdit->setObjectName(QString::fromUtf8("nameEdit"));

    vboxLayout1->addWidget(nameEdit);

    placeEdit = new QLineEdit(Form2);
    placeEdit->setObjectName(QString::fromUtf8("placeEdit"));

    vboxLayout1->addWidget(placeEdit);

    codeEdit = new QLineEdit(Form2);
    codeEdit->setObjectName(QString::fromUtf8("codeEdit"));

    vboxLayout1->addWidget(codeEdit);

    addressEdit = new QLineEdit(Form2);
    addressEdit->setObjectName(QString::fromUtf8("addressEdit"));

    vboxLayout1->addWidget(addressEdit);

    accountEdit = new QLineEdit(Form2);
    accountEdit->setObjectName(QString::fromUtf8("accountEdit"));

    vboxLayout1->addWidget(accountEdit);

    nipEdit = new QLineEdit(Form2);
    nipEdit->setObjectName(QString::fromUtf8("nipEdit"));

    vboxLayout1->addWidget(nipEdit);

    secIdType = new QComboBox(Form2);
    secIdType->setObjectName(QString::fromUtf8("secIdType"));

    vboxLayout1->addWidget(secIdType);

    regonEdit = new QLineEdit(Form2);
    regonEdit->setObjectName(QString::fromUtf8("regonEdit"));

    vboxLayout1->addWidget(regonEdit);


    hboxLayout1->addLayout(vboxLayout1);


    gridLayout->addLayout(hboxLayout1, 0, 0, 1, 1);


    retranslateUi(Form2);
    QObject::connect(okButton, SIGNAL(clicked()), Form2, SLOT(okClick()));
    QObject::connect(cancelButton, SIGNAL(clicked()), Form2, SLOT(close()));

    QMetaObject::connectSlotsByName(Form2);
    } // setupUi

    void retranslateUi(QDialog *Form2)
    {
    Form2->setWindowTitle(QApplication::translate("Form2", "Dane firmy", 0, QApplication::UnicodeUTF8));
    okButton->setText(QApplication::translate("Form2", "O&K", 0, QApplication::UnicodeUTF8));
    okButton->setShortcut(QApplication::translate("Form2", "Alt+K", 0, QApplication::UnicodeUTF8));
    cancelButton->setText(QApplication::translate("Form2", "Can&cel", 0, QApplication::UnicodeUTF8));
    cancelButton->setShortcut(QApplication::translate("Form2", "Alt+C", 0, QApplication::UnicodeUTF8));
    textLabel1->setText(QApplication::translate("Form2", "Nazwa:", 0, QApplication::UnicodeUTF8));
    textLabel3->setText(QApplication::translate("Form2", "Miejscowo\305\233\304\207:", 0, QApplication::UnicodeUTF8));
    textLabel4->setText(QApplication::translate("Form2", "Kod:", 0, QApplication::UnicodeUTF8));
    textLabel2->setText(QApplication::translate("Form2", "Adres:", 0, QApplication::UnicodeUTF8));
    textLabel5->setText(QApplication::translate("Form2", "Nr konta:", 0, QApplication::UnicodeUTF8));
    textLabel2_2->setText(QApplication::translate("Form2", "NIP:", 0, QApplication::UnicodeUTF8));
    textLabel2_2_2_2->setText(QApplication::translate("Form2", "Typ 2 Id:", 0, QApplication::UnicodeUTF8));
    textLabel2_2_2->setText(QApplication::translate("Form2", "Drugi Id:", 0, QApplication::UnicodeUTF8));
    accountEdit->setInputMask(QApplication::translate("Form2", "99-9999-9999-9999-9999-9999-9999; ", 0, QApplication::UnicodeUTF8));
    secIdType->clear();
    secIdType->insertItems(0, QStringList()
     << QApplication::translate("Form2", "NUSP", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("Form2", "REGON", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("Form2", "PESEL", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("Form2", "Dow\303\263d osobisty", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("Form2", "Paszport", 0, QApplication::UnicodeUTF8)
    );
    Q_UNUSED(Form2);
    } // retranslateUi

};

namespace Ui {
    class Form2: public Ui_Form2 {};
} // namespace Ui

#endif // UI_USER_H
