/********************************************************************************
** Form generated from reading ui file 'towary.ui'
**
** Created: Thu Nov 29 01:25:39 2007
**      by: Qt User Interface Compiler version 4.3.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_TOWARY_H
#define UI_TOWARY_H

#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>

class Ui_twAdd
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *hboxLayout;
    QVBoxLayout *vboxLayout;
    QLabel *textLabel1;
    QLabel *textLabel3;
    QLabel *textLabel4;
    QLabel *textLabel1_2;
    QVBoxLayout *vboxLayout1;
    QLineEdit *idxEdit;
    QLineEdit *nameEdit;
    QLineEdit *skrotEdit;
    QLineEdit *kodEdit;
    QHBoxLayout *hboxLayout1;
    QVBoxLayout *vboxLayout2;
    QLabel *textLabel1_2_2;
    QLabel *textLabel2;
    QLabel *textLabel5;
    QVBoxLayout *vboxLayout3;
    QHBoxLayout *hboxLayout2;
    QLineEdit *pkwiuEdit;
    QToolButton *pkwiuBtn;
    QHBoxLayout *hboxLayout3;
    QComboBox *typeCombo;
    QHBoxLayout *hboxLayout4;
    QLabel *textLabel2_2;
    QComboBox *jednCombo;
    QHBoxLayout *hboxLayout5;
    QSpinBox *spinBox2;
    QLineEdit *nettoEdit;
    QHBoxLayout *hboxLayout6;
    QLabel *textLabel6;
    QComboBox *cbVat;
    QHBoxLayout *hboxLayout7;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QFrame *line3;

    void setupUi(QDialog *twAdd)
    {
    if (twAdd->objectName().isEmpty())
        twAdd->setObjectName(QString::fromUtf8("twAdd"));
    twAdd->resize(330, 303);
    gridLayout = new QGridLayout(twAdd);
    gridLayout->setSpacing(6);
    gridLayout->setMargin(11);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    hboxLayout = new QHBoxLayout();
    hboxLayout->setSpacing(6);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    vboxLayout = new QVBoxLayout();
    vboxLayout->setSpacing(6);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    textLabel1 = new QLabel(twAdd);
    textLabel1->setObjectName(QString::fromUtf8("textLabel1"));
    textLabel1->setWordWrap(false);

    vboxLayout->addWidget(textLabel1);

    textLabel3 = new QLabel(twAdd);
    textLabel3->setObjectName(QString::fromUtf8("textLabel3"));
    textLabel3->setWordWrap(false);

    vboxLayout->addWidget(textLabel3);

    textLabel4 = new QLabel(twAdd);
    textLabel4->setObjectName(QString::fromUtf8("textLabel4"));
    textLabel4->setWordWrap(false);

    vboxLayout->addWidget(textLabel4);

    textLabel1_2 = new QLabel(twAdd);
    textLabel1_2->setObjectName(QString::fromUtf8("textLabel1_2"));
    textLabel1_2->setWordWrap(false);

    vboxLayout->addWidget(textLabel1_2);


    hboxLayout->addLayout(vboxLayout);

    vboxLayout1 = new QVBoxLayout();
    vboxLayout1->setSpacing(6);
    vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
    idxEdit = new QLineEdit(twAdd);
    idxEdit->setObjectName(QString::fromUtf8("idxEdit"));
    idxEdit->setEnabled(false);
    QFont font;
    font.setBold(true);
    font.setWeight(75);
    idxEdit->setFont(font);
    idxEdit->setReadOnly(true);

    vboxLayout1->addWidget(idxEdit);

    nameEdit = new QLineEdit(twAdd);
    nameEdit->setObjectName(QString::fromUtf8("nameEdit"));
    nameEdit->setMaxLength(75);

    vboxLayout1->addWidget(nameEdit);

    skrotEdit = new QLineEdit(twAdd);
    skrotEdit->setObjectName(QString::fromUtf8("skrotEdit"));
    skrotEdit->setMaxLength(25);

    vboxLayout1->addWidget(skrotEdit);

    kodEdit = new QLineEdit(twAdd);
    kodEdit->setObjectName(QString::fromUtf8("kodEdit"));
    kodEdit->setMaxLength(20);

    vboxLayout1->addWidget(kodEdit);


    hboxLayout->addLayout(vboxLayout1);


    gridLayout->addLayout(hboxLayout, 0, 0, 1, 1);

    hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setSpacing(6);
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    vboxLayout2 = new QVBoxLayout();
    vboxLayout2->setSpacing(6);
    vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
    textLabel1_2_2 = new QLabel(twAdd);
    textLabel1_2_2->setObjectName(QString::fromUtf8("textLabel1_2_2"));
    textLabel1_2_2->setWordWrap(false);

    vboxLayout2->addWidget(textLabel1_2_2);

    textLabel2 = new QLabel(twAdd);
    textLabel2->setObjectName(QString::fromUtf8("textLabel2"));
    textLabel2->setWordWrap(false);

    vboxLayout2->addWidget(textLabel2);

    textLabel5 = new QLabel(twAdd);
    textLabel5->setObjectName(QString::fromUtf8("textLabel5"));
    textLabel5->setWordWrap(false);

    vboxLayout2->addWidget(textLabel5);


    hboxLayout1->addLayout(vboxLayout2);

    vboxLayout3 = new QVBoxLayout();
    vboxLayout3->setSpacing(6);
    vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
    hboxLayout2 = new QHBoxLayout();
    hboxLayout2->setSpacing(6);
    hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
    pkwiuEdit = new QLineEdit(twAdd);
    pkwiuEdit->setObjectName(QString::fromUtf8("pkwiuEdit"));
    pkwiuEdit->setMaxLength(20);

    hboxLayout2->addWidget(pkwiuEdit);

    pkwiuBtn = new QToolButton(twAdd);
    pkwiuBtn->setObjectName(QString::fromUtf8("pkwiuBtn"));

    hboxLayout2->addWidget(pkwiuBtn);


    vboxLayout3->addLayout(hboxLayout2);

    hboxLayout3 = new QHBoxLayout();
    hboxLayout3->setSpacing(6);
    hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
    typeCombo = new QComboBox(twAdd);
    typeCombo->setObjectName(QString::fromUtf8("typeCombo"));

    hboxLayout3->addWidget(typeCombo);

    hboxLayout4 = new QHBoxLayout();
    hboxLayout4->setSpacing(6);
    hboxLayout4->setObjectName(QString::fromUtf8("hboxLayout4"));
    textLabel2_2 = new QLabel(twAdd);
    textLabel2_2->setObjectName(QString::fromUtf8("textLabel2_2"));
    textLabel2_2->setWordWrap(false);

    hboxLayout4->addWidget(textLabel2_2);

    jednCombo = new QComboBox(twAdd);
    jednCombo->setObjectName(QString::fromUtf8("jednCombo"));

    hboxLayout4->addWidget(jednCombo);


    hboxLayout3->addLayout(hboxLayout4);


    vboxLayout3->addLayout(hboxLayout3);

    hboxLayout5 = new QHBoxLayout();
    hboxLayout5->setSpacing(6);
    hboxLayout5->setObjectName(QString::fromUtf8("hboxLayout5"));
    spinBox2 = new QSpinBox(twAdd);
    spinBox2->setObjectName(QString::fromUtf8("spinBox2"));
    spinBox2->setMinimumSize(QSize(60, 0));
    spinBox2->setMinimum(1);
    spinBox2->setMaximum(4);

    hboxLayout5->addWidget(spinBox2);

    nettoEdit = new QLineEdit(twAdd);
    nettoEdit->setObjectName(QString::fromUtf8("nettoEdit"));
    nettoEdit->setAlignment(Qt::AlignRight);

    hboxLayout5->addWidget(nettoEdit);

    hboxLayout6 = new QHBoxLayout();
    hboxLayout6->setSpacing(6);
    hboxLayout6->setObjectName(QString::fromUtf8("hboxLayout6"));
    textLabel6 = new QLabel(twAdd);
    textLabel6->setObjectName(QString::fromUtf8("textLabel6"));
    textLabel6->setWordWrap(false);

    hboxLayout6->addWidget(textLabel6);

    cbVat = new QComboBox(twAdd);
    cbVat->setObjectName(QString::fromUtf8("cbVat"));

    hboxLayout6->addWidget(cbVat);


    hboxLayout5->addLayout(hboxLayout6);


    vboxLayout3->addLayout(hboxLayout5);


    hboxLayout1->addLayout(vboxLayout3);


    gridLayout->addLayout(hboxLayout1, 1, 0, 1, 1);

    hboxLayout7 = new QHBoxLayout();
    hboxLayout7->setSpacing(6);
    hboxLayout7->setObjectName(QString::fromUtf8("hboxLayout7"));
    spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout7->addItem(spacerItem);

    okButton = new QPushButton(twAdd);
    okButton->setObjectName(QString::fromUtf8("okButton"));

    hboxLayout7->addWidget(okButton);

    cancelButton = new QPushButton(twAdd);
    cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

    hboxLayout7->addWidget(cancelButton);


    gridLayout->addLayout(hboxLayout7, 3, 0, 1, 1);

    line3 = new QFrame(twAdd);
    line3->setObjectName(QString::fromUtf8("line3"));
    line3->setFrameShape(QFrame::HLine);
    line3->setFrameShadow(QFrame::Sunken);

    gridLayout->addWidget(line3, 2, 0, 1, 1);


    retranslateUi(twAdd);
    QObject::connect(okButton, SIGNAL(clicked()), twAdd, SLOT(okClick()));
    QObject::connect(cancelButton, SIGNAL(clicked()), twAdd, SLOT(close()));
    QObject::connect(nettoEdit, SIGNAL(lostFocus()), twAdd, SLOT(nettoChanged()));
    QObject::connect(spinBox2, SIGNAL(valueChanged(int)), twAdd, SLOT(spinChanged(int)));
    QObject::connect(pkwiuBtn, SIGNAL(clicked()), twAdd, SLOT(pkwiuGet()));

    QMetaObject::connectSlotsByName(twAdd);
    } // setupUi

    void retranslateUi(QDialog *twAdd)
    {
    twAdd->setWindowTitle(QApplication::translate("twAdd", "Dodaj towar", 0, QApplication::UnicodeUTF8));
    textLabel1->setText(QApplication::translate("twAdd", "Index:", 0, QApplication::UnicodeUTF8));
    textLabel3->setText(QApplication::translate("twAdd", "Nazwa:", 0, QApplication::UnicodeUTF8));
    textLabel4->setText(QApplication::translate("twAdd", "Skr\303\263t:", 0, QApplication::UnicodeUTF8));
    textLabel1_2->setText(QApplication::translate("twAdd", "Kod:", 0, QApplication::UnicodeUTF8));
    skrotEdit->setText(QString());
    textLabel1_2_2->setText(QApplication::translate("twAdd", "PKWiU:", 0, QApplication::UnicodeUTF8));
    textLabel2->setText(QApplication::translate("twAdd", "Typ:", 0, QApplication::UnicodeUTF8));
    textLabel5->setText(QApplication::translate("twAdd", "Cena:", 0, QApplication::UnicodeUTF8));
    pkwiuBtn->setText(QApplication::translate("twAdd", "Z&najd\305\272", 0, QApplication::UnicodeUTF8));
    pkwiuBtn->setShortcut(QApplication::translate("twAdd", "Alt+N", 0, QApplication::UnicodeUTF8));
    typeCombo->clear();
    typeCombo->insertItems(0, QStringList()
     << QApplication::translate("twAdd", "towar", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("twAdd", "us\305\202uga", 0, QApplication::UnicodeUTF8)
    );
    textLabel2_2->setText(QApplication::translate("twAdd", "Jedn.:", 0, QApplication::UnicodeUTF8));
    jednCombo->clear();
    jednCombo->insertItems(0, QStringList()
     << QApplication::translate("twAdd", "szt.", 0, QApplication::UnicodeUTF8)
    );
    nettoEdit->setInputMask(QApplication::translate("twAdd", "0000000,00; ", 0, QApplication::UnicodeUTF8));
    textLabel6->setText(QApplication::translate("twAdd", "Vat:", 0, QApplication::UnicodeUTF8));
    okButton->setText(QApplication::translate("twAdd", "O&K", 0, QApplication::UnicodeUTF8));
    okButton->setShortcut(QApplication::translate("twAdd", "Alt+K", 0, QApplication::UnicodeUTF8));
    cancelButton->setText(QApplication::translate("twAdd", "Can&cel", 0, QApplication::UnicodeUTF8));
    cancelButton->setShortcut(QApplication::translate("twAdd", "Alt+C", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(twAdd);
    } // retranslateUi

};

namespace Ui {
    class twAdd: public Ui_twAdd {};
} // namespace Ui

#endif // UI_TOWARY_H
