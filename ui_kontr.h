/********************************************************************************
** Form generated from reading ui file 'kontr.ui'
**
** Created: Thu Nov 29 01:25:38 2007
**      by: Qt User Interface Compiler version 4.3.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_KONTR_H
#define UI_KONTR_H

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

class Ui_Form4
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QHBoxLayout *hboxLayout1;
    QVBoxLayout *vboxLayout;
    QLabel *textLabel5_2;
    QLabel *textLabel5_2_2;
    QLabel *textLabel5_2_2_2;
    QVBoxLayout *vboxLayout1;
    QLineEdit *telefonEdit;
    QLineEdit *emailEdit;
    QLineEdit *wwwEdit;
    QHBoxLayout *hboxLayout2;
    QVBoxLayout *vboxLayout2;
    QLabel *textLabel1;
    QLabel *textLabel3;
    QLabel *textLabel4;
    QLabel *textLabel2;
    QLabel *textLabel2_2;
    QLabel *textLabel5;
    QLabel *textLabel6;
    QVBoxLayout *vboxLayout3;
    QLineEdit *nameEdit;
    QLineEdit *placeEdit;
    QLineEdit *codeEdit;
    QLineEdit *addressEdit;
    QLineEdit *nipEdit;
    QLineEdit *accountEdit;
    QComboBox *typeCombo;

    void setupUi(QDialog *Form4)
    {
    if (Form4->objectName().isEmpty())
        Form4->setObjectName(QString::fromUtf8("Form4"));
    Form4->resize(420, 384);
    gridLayout = new QGridLayout(Form4);
    gridLayout->setSpacing(6);
    gridLayout->setMargin(11);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    hboxLayout = new QHBoxLayout();
    hboxLayout->setSpacing(6);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout->addItem(spacerItem);

    okButton = new QPushButton(Form4);
    okButton->setObjectName(QString::fromUtf8("okButton"));

    hboxLayout->addWidget(okButton);

    cancelButton = new QPushButton(Form4);
    cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

    hboxLayout->addWidget(cancelButton);


    gridLayout->addLayout(hboxLayout, 2, 0, 1, 1);

    hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setSpacing(6);
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    vboxLayout = new QVBoxLayout();
    vboxLayout->setSpacing(6);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    textLabel5_2 = new QLabel(Form4);
    textLabel5_2->setObjectName(QString::fromUtf8("textLabel5_2"));
    textLabel5_2->setWordWrap(false);

    vboxLayout->addWidget(textLabel5_2);

    textLabel5_2_2 = new QLabel(Form4);
    textLabel5_2_2->setObjectName(QString::fromUtf8("textLabel5_2_2"));
    textLabel5_2_2->setWordWrap(false);

    vboxLayout->addWidget(textLabel5_2_2);

    textLabel5_2_2_2 = new QLabel(Form4);
    textLabel5_2_2_2->setObjectName(QString::fromUtf8("textLabel5_2_2_2"));
    textLabel5_2_2_2->setWordWrap(false);

    vboxLayout->addWidget(textLabel5_2_2_2);


    hboxLayout1->addLayout(vboxLayout);

    vboxLayout1 = new QVBoxLayout();
    vboxLayout1->setSpacing(6);
    vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
    telefonEdit = new QLineEdit(Form4);
    telefonEdit->setObjectName(QString::fromUtf8("telefonEdit"));

    vboxLayout1->addWidget(telefonEdit);

    emailEdit = new QLineEdit(Form4);
    emailEdit->setObjectName(QString::fromUtf8("emailEdit"));

    vboxLayout1->addWidget(emailEdit);

    wwwEdit = new QLineEdit(Form4);
    wwwEdit->setObjectName(QString::fromUtf8("wwwEdit"));

    vboxLayout1->addWidget(wwwEdit);


    hboxLayout1->addLayout(vboxLayout1);


    gridLayout->addLayout(hboxLayout1, 1, 0, 1, 1);

    hboxLayout2 = new QHBoxLayout();
    hboxLayout2->setSpacing(6);
    hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
    vboxLayout2 = new QVBoxLayout();
    vboxLayout2->setSpacing(6);
    vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
    textLabel1 = new QLabel(Form4);
    textLabel1->setObjectName(QString::fromUtf8("textLabel1"));
    textLabel1->setWordWrap(false);

    vboxLayout2->addWidget(textLabel1);

    textLabel3 = new QLabel(Form4);
    textLabel3->setObjectName(QString::fromUtf8("textLabel3"));
    textLabel3->setWordWrap(false);

    vboxLayout2->addWidget(textLabel3);

    textLabel4 = new QLabel(Form4);
    textLabel4->setObjectName(QString::fromUtf8("textLabel4"));
    textLabel4->setWordWrap(false);

    vboxLayout2->addWidget(textLabel4);

    textLabel2 = new QLabel(Form4);
    textLabel2->setObjectName(QString::fromUtf8("textLabel2"));
    textLabel2->setWordWrap(false);

    vboxLayout2->addWidget(textLabel2);

    textLabel2_2 = new QLabel(Form4);
    textLabel2_2->setObjectName(QString::fromUtf8("textLabel2_2"));
    textLabel2_2->setWordWrap(false);

    vboxLayout2->addWidget(textLabel2_2);

    textLabel5 = new QLabel(Form4);
    textLabel5->setObjectName(QString::fromUtf8("textLabel5"));
    textLabel5->setWordWrap(false);

    vboxLayout2->addWidget(textLabel5);

    textLabel6 = new QLabel(Form4);
    textLabel6->setObjectName(QString::fromUtf8("textLabel6"));
    textLabel6->setWordWrap(false);

    vboxLayout2->addWidget(textLabel6);


    hboxLayout2->addLayout(vboxLayout2);

    vboxLayout3 = new QVBoxLayout();
    vboxLayout3->setSpacing(6);
    vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
    nameEdit = new QLineEdit(Form4);
    nameEdit->setObjectName(QString::fromUtf8("nameEdit"));

    vboxLayout3->addWidget(nameEdit);

    placeEdit = new QLineEdit(Form4);
    placeEdit->setObjectName(QString::fromUtf8("placeEdit"));

    vboxLayout3->addWidget(placeEdit);

    codeEdit = new QLineEdit(Form4);
    codeEdit->setObjectName(QString::fromUtf8("codeEdit"));

    vboxLayout3->addWidget(codeEdit);

    addressEdit = new QLineEdit(Form4);
    addressEdit->setObjectName(QString::fromUtf8("addressEdit"));

    vboxLayout3->addWidget(addressEdit);

    nipEdit = new QLineEdit(Form4);
    nipEdit->setObjectName(QString::fromUtf8("nipEdit"));

    vboxLayout3->addWidget(nipEdit);

    accountEdit = new QLineEdit(Form4);
    accountEdit->setObjectName(QString::fromUtf8("accountEdit"));

    vboxLayout3->addWidget(accountEdit);

    typeCombo = new QComboBox(Form4);
    typeCombo->setObjectName(QString::fromUtf8("typeCombo"));

    vboxLayout3->addWidget(typeCombo);


    hboxLayout2->addLayout(vboxLayout3);


    gridLayout->addLayout(hboxLayout2, 0, 0, 1, 1);


    retranslateUi(Form4);
    QObject::connect(cancelButton, SIGNAL(clicked()), Form4, SLOT(close()));
    QObject::connect(okButton, SIGNAL(clicked()), Form4, SLOT(okClick()));

    QMetaObject::connectSlotsByName(Form4);
    } // setupUi

    void retranslateUi(QDialog *Form4)
    {
    Form4->setWindowTitle(QApplication::translate("Form4", "Dodaj kontrahenta", 0, QApplication::UnicodeUTF8));
    okButton->setText(QApplication::translate("Form4", "O&K", 0, QApplication::UnicodeUTF8));
    okButton->setShortcut(QApplication::translate("Form4", "Alt+K", 0, QApplication::UnicodeUTF8));
    cancelButton->setText(QApplication::translate("Form4", "Can&cel", 0, QApplication::UnicodeUTF8));
    cancelButton->setShortcut(QApplication::translate("Form4", "Alt+C", 0, QApplication::UnicodeUTF8));
    textLabel5_2->setText(QApplication::translate("Form4", "Telefon:", 0, QApplication::UnicodeUTF8));
    textLabel5_2_2->setText(QApplication::translate("Form4", "e-mail", 0, QApplication::UnicodeUTF8));
    textLabel5_2_2_2->setText(QApplication::translate("Form4", "www:", 0, QApplication::UnicodeUTF8));
    textLabel1->setText(QApplication::translate("Form4", "Nazwa:", 0, QApplication::UnicodeUTF8));
    textLabel3->setText(QApplication::translate("Form4", "Miejscowo\305\233\304\207:", 0, QApplication::UnicodeUTF8));
    textLabel4->setText(QApplication::translate("Form4", "Kod:", 0, QApplication::UnicodeUTF8));
    textLabel2->setText(QApplication::translate("Form4", "Adres:", 0, QApplication::UnicodeUTF8));
    textLabel2_2->setText(QApplication::translate("Form4", "NIP:", 0, QApplication::UnicodeUTF8));
    textLabel5->setText(QApplication::translate("Form4", "Nr konta:", 0, QApplication::UnicodeUTF8));
    textLabel6->setText(QApplication::translate("Form4", "Typ:", 0, QApplication::UnicodeUTF8));
    nipEdit->setInputMask(QApplication::translate("Form4", "999-99-999-99; ", 0, QApplication::UnicodeUTF8));
    accountEdit->setInputMask(QApplication::translate("Form4", "99-9999-9999-9999-9999-9999-9999; ", 0, QApplication::UnicodeUTF8));
    typeCombo->clear();
    typeCombo->insertItems(0, QStringList()
     << QApplication::translate("Form4", "Firma", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("Form4", "Urz\304\205d", 0, QApplication::UnicodeUTF8)
    );
    Q_UNUSED(Form4);
    } // retranslateUi

};

namespace Ui {
    class Form4: public Ui_Form4 {};
} // namespace Ui

#endif // UI_KONTR_H
