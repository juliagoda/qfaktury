/********************************************************************************
** Form generated from reading ui file 'przelew.ui'
**
** Created: Thu Nov 29 01:25:38 2007
**      by: Qt User Interface Compiler version 4.3.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_PRZELEW_H
#define UI_PRZELEW_H

#include <Qt3Support/Q3GroupBox>
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

class Ui_Form6
{
public:
    QGridLayout *gridLayout;
    Q3GroupBox *groupBox3;
    QGridLayout *gridLayout1;
    QHBoxLayout *hboxLayout;
    QLabel *textLabel5;
    QLineEdit *accountEdit2;
    QHBoxLayout *hboxLayout1;
    QLabel *textLabel2;
    QLineEdit *addressEdit2;
    QHBoxLayout *hboxLayout2;
    QLabel *textLabel1;
    QLineEdit *nameEdit2;
    QHBoxLayout *hboxLayout3;
    QLabel *textLabel4;
    QLineEdit *codeEdit2;
    QHBoxLayout *hboxLayout4;
    QLabel *textLabel3;
    QLineEdit *placeEdit2;
    Q3GroupBox *groupBox2;
    QGridLayout *gridLayout2;
    QHBoxLayout *hboxLayout5;
    QLabel *textLabel3_2;
    QLineEdit *placeEdit;
    QHBoxLayout *hboxLayout6;
    QLabel *textLabel5_2;
    QLineEdit *accountEdit;
    QHBoxLayout *hboxLayout7;
    QLabel *textLabel2_2;
    QLineEdit *addressEdit;
    QHBoxLayout *hboxLayout8;
    QLabel *textLabel1_2;
    QLineEdit *nameEdit;
    QHBoxLayout *hboxLayout9;
    QLabel *textLabel4_2;
    QLineEdit *codeEdit;
    Q3GroupBox *groupBox1;
    QGridLayout *gridLayout3;
    QHBoxLayout *hboxLayout10;
    QLabel *textLabel7;
    QLineEdit *lineEdit17;
    QHBoxLayout *hboxLayout11;
    QLabel *textLabel3_3;
    QHBoxLayout *hboxLayout12;
    QLineEdit *kwotaEdit;
    QPushButton *slownieButton;
    QHBoxLayout *hboxLayout13;
    QLabel *textLabel6;
    QComboBox *comboBox1;
    QHBoxLayout *hboxLayout14;
    QLabel *textLabel4_3;
    QLabel *slownieLbl;
    QHBoxLayout *hboxLayout15;
    QSpacerItem *spacerItem;
    QPushButton *ppriviewButton;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *Form6)
    {
    if (Form6->objectName().isEmpty())
        Form6->setObjectName(QString::fromUtf8("Form6"));
    Form6->resize(408, 530);
    gridLayout = new QGridLayout(Form6);
    gridLayout->setSpacing(6);
    gridLayout->setMargin(11);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    groupBox3 = new Q3GroupBox(Form6);
    groupBox3->setObjectName(QString::fromUtf8("groupBox3"));
    groupBox3->setColumnLayout(0, Qt::Vertical);
    groupBox3->layout()->setSpacing(6);
    groupBox3->layout()->setMargin(11);
    gridLayout1 = new QGridLayout();
    QBoxLayout *boxlayout = qobject_cast<QBoxLayout *>(groupBox3->layout());
    if (boxlayout)
        boxlayout->addLayout(gridLayout1);
    gridLayout1->setAlignment(Qt::AlignTop);
    gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
    hboxLayout = new QHBoxLayout();
    hboxLayout->setSpacing(6);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    textLabel5 = new QLabel(groupBox3);
    textLabel5->setObjectName(QString::fromUtf8("textLabel5"));
    textLabel5->setWordWrap(false);

    hboxLayout->addWidget(textLabel5);

    accountEdit2 = new QLineEdit(groupBox3);
    accountEdit2->setObjectName(QString::fromUtf8("accountEdit2"));

    hboxLayout->addWidget(accountEdit2);


    gridLayout1->addLayout(hboxLayout, 3, 0, 1, 2);

    hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setSpacing(6);
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    textLabel2 = new QLabel(groupBox3);
    textLabel2->setObjectName(QString::fromUtf8("textLabel2"));
    textLabel2->setWordWrap(false);

    hboxLayout1->addWidget(textLabel2);

    addressEdit2 = new QLineEdit(groupBox3);
    addressEdit2->setObjectName(QString::fromUtf8("addressEdit2"));

    hboxLayout1->addWidget(addressEdit2);


    gridLayout1->addLayout(hboxLayout1, 2, 0, 1, 2);

    hboxLayout2 = new QHBoxLayout();
    hboxLayout2->setSpacing(6);
    hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
    textLabel1 = new QLabel(groupBox3);
    textLabel1->setObjectName(QString::fromUtf8("textLabel1"));
    textLabel1->setWordWrap(false);

    hboxLayout2->addWidget(textLabel1);

    nameEdit2 = new QLineEdit(groupBox3);
    nameEdit2->setObjectName(QString::fromUtf8("nameEdit2"));

    hboxLayout2->addWidget(nameEdit2);


    gridLayout1->addLayout(hboxLayout2, 0, 0, 1, 2);

    hboxLayout3 = new QHBoxLayout();
    hboxLayout3->setSpacing(6);
    hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
    textLabel4 = new QLabel(groupBox3);
    textLabel4->setObjectName(QString::fromUtf8("textLabel4"));
    textLabel4->setWordWrap(false);

    hboxLayout3->addWidget(textLabel4);

    codeEdit2 = new QLineEdit(groupBox3);
    codeEdit2->setObjectName(QString::fromUtf8("codeEdit2"));
    codeEdit2->setMaximumSize(QSize(100, 32767));

    hboxLayout3->addWidget(codeEdit2);


    gridLayout1->addLayout(hboxLayout3, 1, 1, 1, 1);

    hboxLayout4 = new QHBoxLayout();
    hboxLayout4->setSpacing(6);
    hboxLayout4->setObjectName(QString::fromUtf8("hboxLayout4"));
    textLabel3 = new QLabel(groupBox3);
    textLabel3->setObjectName(QString::fromUtf8("textLabel3"));
    textLabel3->setWordWrap(false);

    hboxLayout4->addWidget(textLabel3);

    placeEdit2 = new QLineEdit(groupBox3);
    placeEdit2->setObjectName(QString::fromUtf8("placeEdit2"));
    placeEdit2->setMinimumSize(QSize(160, 0));
    placeEdit2->setMaximumSize(QSize(160, 32767));

    hboxLayout4->addWidget(placeEdit2);


    gridLayout1->addLayout(hboxLayout4, 1, 0, 1, 1);


    gridLayout->addWidget(groupBox3, 0, 0, 1, 1);

    groupBox2 = new Q3GroupBox(Form6);
    groupBox2->setObjectName(QString::fromUtf8("groupBox2"));
    groupBox2->setColumnLayout(0, Qt::Vertical);
    groupBox2->layout()->setSpacing(6);
    groupBox2->layout()->setMargin(11);
    gridLayout2 = new QGridLayout();
    QBoxLayout *boxlayout1 = qobject_cast<QBoxLayout *>(groupBox2->layout());
    if (boxlayout1)
        boxlayout1->addLayout(gridLayout2);
    gridLayout2->setAlignment(Qt::AlignTop);
    gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
    hboxLayout5 = new QHBoxLayout();
    hboxLayout5->setSpacing(6);
    hboxLayout5->setObjectName(QString::fromUtf8("hboxLayout5"));
    textLabel3_2 = new QLabel(groupBox2);
    textLabel3_2->setObjectName(QString::fromUtf8("textLabel3_2"));
    textLabel3_2->setWordWrap(false);

    hboxLayout5->addWidget(textLabel3_2);

    placeEdit = new QLineEdit(groupBox2);
    placeEdit->setObjectName(QString::fromUtf8("placeEdit"));
    placeEdit->setMinimumSize(QSize(160, 0));

    hboxLayout5->addWidget(placeEdit);


    gridLayout2->addLayout(hboxLayout5, 1, 0, 1, 1);

    hboxLayout6 = new QHBoxLayout();
    hboxLayout6->setSpacing(6);
    hboxLayout6->setObjectName(QString::fromUtf8("hboxLayout6"));
    textLabel5_2 = new QLabel(groupBox2);
    textLabel5_2->setObjectName(QString::fromUtf8("textLabel5_2"));
    textLabel5_2->setWordWrap(false);

    hboxLayout6->addWidget(textLabel5_2);

    accountEdit = new QLineEdit(groupBox2);
    accountEdit->setObjectName(QString::fromUtf8("accountEdit"));

    hboxLayout6->addWidget(accountEdit);


    gridLayout2->addLayout(hboxLayout6, 3, 0, 1, 2);

    hboxLayout7 = new QHBoxLayout();
    hboxLayout7->setSpacing(6);
    hboxLayout7->setObjectName(QString::fromUtf8("hboxLayout7"));
    textLabel2_2 = new QLabel(groupBox2);
    textLabel2_2->setObjectName(QString::fromUtf8("textLabel2_2"));
    textLabel2_2->setWordWrap(false);

    hboxLayout7->addWidget(textLabel2_2);

    addressEdit = new QLineEdit(groupBox2);
    addressEdit->setObjectName(QString::fromUtf8("addressEdit"));

    hboxLayout7->addWidget(addressEdit);


    gridLayout2->addLayout(hboxLayout7, 2, 0, 1, 2);

    hboxLayout8 = new QHBoxLayout();
    hboxLayout8->setSpacing(6);
    hboxLayout8->setObjectName(QString::fromUtf8("hboxLayout8"));
    textLabel1_2 = new QLabel(groupBox2);
    textLabel1_2->setObjectName(QString::fromUtf8("textLabel1_2"));
    textLabel1_2->setWordWrap(false);

    hboxLayout8->addWidget(textLabel1_2);

    nameEdit = new QLineEdit(groupBox2);
    nameEdit->setObjectName(QString::fromUtf8("nameEdit"));

    hboxLayout8->addWidget(nameEdit);


    gridLayout2->addLayout(hboxLayout8, 0, 0, 1, 2);

    hboxLayout9 = new QHBoxLayout();
    hboxLayout9->setSpacing(6);
    hboxLayout9->setObjectName(QString::fromUtf8("hboxLayout9"));
    textLabel4_2 = new QLabel(groupBox2);
    textLabel4_2->setObjectName(QString::fromUtf8("textLabel4_2"));
    textLabel4_2->setWordWrap(false);

    hboxLayout9->addWidget(textLabel4_2);

    codeEdit = new QLineEdit(groupBox2);
    codeEdit->setObjectName(QString::fromUtf8("codeEdit"));
    codeEdit->setMaximumSize(QSize(100, 32767));

    hboxLayout9->addWidget(codeEdit);


    gridLayout2->addLayout(hboxLayout9, 1, 1, 1, 1);


    gridLayout->addWidget(groupBox2, 1, 0, 1, 1);

    groupBox1 = new Q3GroupBox(Form6);
    groupBox1->setObjectName(QString::fromUtf8("groupBox1"));
    groupBox1->setColumnLayout(0, Qt::Vertical);
    groupBox1->layout()->setSpacing(6);
    groupBox1->layout()->setMargin(11);
    gridLayout3 = new QGridLayout();
    QBoxLayout *boxlayout2 = qobject_cast<QBoxLayout *>(groupBox1->layout());
    if (boxlayout2)
        boxlayout2->addLayout(gridLayout3);
    gridLayout3->setAlignment(Qt::AlignTop);
    gridLayout3->setObjectName(QString::fromUtf8("gridLayout3"));
    hboxLayout10 = new QHBoxLayout();
    hboxLayout10->setSpacing(6);
    hboxLayout10->setObjectName(QString::fromUtf8("hboxLayout10"));
    textLabel7 = new QLabel(groupBox1);
    textLabel7->setObjectName(QString::fromUtf8("textLabel7"));
    textLabel7->setWordWrap(false);

    hboxLayout10->addWidget(textLabel7);

    lineEdit17 = new QLineEdit(groupBox1);
    lineEdit17->setObjectName(QString::fromUtf8("lineEdit17"));

    hboxLayout10->addWidget(lineEdit17);


    gridLayout3->addLayout(hboxLayout10, 2, 0, 1, 2);

    hboxLayout11 = new QHBoxLayout();
    hboxLayout11->setSpacing(6);
    hboxLayout11->setObjectName(QString::fromUtf8("hboxLayout11"));
    textLabel3_3 = new QLabel(groupBox1);
    textLabel3_3->setObjectName(QString::fromUtf8("textLabel3_3"));
    textLabel3_3->setWordWrap(false);

    hboxLayout11->addWidget(textLabel3_3);

    hboxLayout12 = new QHBoxLayout();
    hboxLayout12->setSpacing(6);
    hboxLayout12->setObjectName(QString::fromUtf8("hboxLayout12"));
    kwotaEdit = new QLineEdit(groupBox1);
    kwotaEdit->setObjectName(QString::fromUtf8("kwotaEdit"));
    kwotaEdit->setAlignment(Qt::AlignRight);

    hboxLayout12->addWidget(kwotaEdit);

    slownieButton = new QPushButton(groupBox1);
    slownieButton->setObjectName(QString::fromUtf8("slownieButton"));
    slownieButton->setFocusPolicy(Qt::NoFocus);

    hboxLayout12->addWidget(slownieButton);


    hboxLayout11->addLayout(hboxLayout12);


    gridLayout3->addLayout(hboxLayout11, 0, 0, 1, 1);

    hboxLayout13 = new QHBoxLayout();
    hboxLayout13->setSpacing(6);
    hboxLayout13->setObjectName(QString::fromUtf8("hboxLayout13"));
    textLabel6 = new QLabel(groupBox1);
    textLabel6->setObjectName(QString::fromUtf8("textLabel6"));
    textLabel6->setWordWrap(false);

    hboxLayout13->addWidget(textLabel6);

    comboBox1 = new QComboBox(groupBox1);
    comboBox1->setObjectName(QString::fromUtf8("comboBox1"));

    hboxLayout13->addWidget(comboBox1);


    gridLayout3->addLayout(hboxLayout13, 0, 1, 1, 1);

    hboxLayout14 = new QHBoxLayout();
    hboxLayout14->setSpacing(6);
    hboxLayout14->setObjectName(QString::fromUtf8("hboxLayout14"));
    textLabel4_3 = new QLabel(groupBox1);
    textLabel4_3->setObjectName(QString::fromUtf8("textLabel4_3"));
    textLabel4_3->setMaximumSize(QSize(60, 32767));
    textLabel4_3->setWordWrap(false);

    hboxLayout14->addWidget(textLabel4_3);

    slownieLbl = new QLabel(groupBox1);
    slownieLbl->setObjectName(QString::fromUtf8("slownieLbl"));
    slownieLbl->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
    slownieLbl->setWordWrap(false);

    hboxLayout14->addWidget(slownieLbl);


    gridLayout3->addLayout(hboxLayout14, 1, 0, 1, 2);


    gridLayout->addWidget(groupBox1, 2, 0, 1, 1);

    hboxLayout15 = new QHBoxLayout();
    hboxLayout15->setSpacing(6);
    hboxLayout15->setObjectName(QString::fromUtf8("hboxLayout15"));
    spacerItem = new QSpacerItem(108, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout15->addItem(spacerItem);

    ppriviewButton = new QPushButton(Form6);
    ppriviewButton->setObjectName(QString::fromUtf8("ppriviewButton"));

    hboxLayout15->addWidget(ppriviewButton);

    okButton = new QPushButton(Form6);
    okButton->setObjectName(QString::fromUtf8("okButton"));

    hboxLayout15->addWidget(okButton);

    cancelButton = new QPushButton(Form6);
    cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

    hboxLayout15->addWidget(cancelButton);


    gridLayout->addLayout(hboxLayout15, 3, 0, 1, 1);

    QWidget::setTabOrder(nameEdit2, placeEdit2);
    QWidget::setTabOrder(placeEdit2, codeEdit2);
    QWidget::setTabOrder(codeEdit2, addressEdit2);
    QWidget::setTabOrder(addressEdit2, accountEdit2);
    QWidget::setTabOrder(accountEdit2, nameEdit);
    QWidget::setTabOrder(nameEdit, placeEdit);
    QWidget::setTabOrder(placeEdit, codeEdit);
    QWidget::setTabOrder(codeEdit, addressEdit);
    QWidget::setTabOrder(addressEdit, accountEdit);
    QWidget::setTabOrder(accountEdit, kwotaEdit);
    QWidget::setTabOrder(kwotaEdit, comboBox1);
    QWidget::setTabOrder(comboBox1, lineEdit17);
    QWidget::setTabOrder(lineEdit17, okButton);
    QWidget::setTabOrder(okButton, cancelButton);
    QWidget::setTabOrder(cancelButton, slownieButton);

    retranslateUi(Form6);
    QObject::connect(cancelButton, SIGNAL(clicked()), Form6, SLOT(close()));
    QObject::connect(slownieButton, SIGNAL(clicked()), Form6, SLOT(slownie()));
    QObject::connect(kwotaEdit, SIGNAL(textChanged(QString)), Form6, SLOT(kwotaKeyDown()));
    QObject::connect(okButton, SIGNAL(clicked()), Form6, SLOT(print_dlg()));
    QObject::connect(comboBox1, SIGNAL(activated(int)), Form6, SLOT(makeWplata()));
    QObject::connect(ppriviewButton, SIGNAL(clicked()), Form6, SLOT(ppriview()));

    QMetaObject::connectSlotsByName(Form6);
    } // setupUi

    void retranslateUi(QDialog *Form6)
    {
    Form6->setWindowTitle(QApplication::translate("Form6", "Drukuj przelew", 0, QApplication::UnicodeUTF8));
    groupBox3->setTitle(QApplication::translate("Form6", "Dane odbiorcy: ", 0, QApplication::UnicodeUTF8));
    textLabel5->setText(QApplication::translate("Form6", "Nr konta:", 0, QApplication::UnicodeUTF8));
    accountEdit2->setInputMask(QApplication::translate("Form6", "99-9999-9999-9999-9999-9999-9999; ", 0, QApplication::UnicodeUTF8));
    textLabel2->setText(QApplication::translate("Form6", "Adres:", 0, QApplication::UnicodeUTF8));
    textLabel1->setText(QApplication::translate("Form6", "Nazwa:", 0, QApplication::UnicodeUTF8));
    textLabel4->setText(QApplication::translate("Form6", "Kod:", 0, QApplication::UnicodeUTF8));
    textLabel3->setText(QApplication::translate("Form6", "Miasto:", 0, QApplication::UnicodeUTF8));
    groupBox2->setTitle(QApplication::translate("Form6", "Dane zleceniodawcy: ", 0, QApplication::UnicodeUTF8));
    textLabel3_2->setText(QApplication::translate("Form6", "Miasto:", 0, QApplication::UnicodeUTF8));
    textLabel5_2->setText(QApplication::translate("Form6", "Nr konta:", 0, QApplication::UnicodeUTF8));
    accountEdit->setInputMask(QApplication::translate("Form6", "99-9999-9999-9999-9999-9999-9999; ", 0, QApplication::UnicodeUTF8));
    textLabel2_2->setText(QApplication::translate("Form6", "Adres:", 0, QApplication::UnicodeUTF8));
    textLabel1_2->setText(QApplication::translate("Form6", "Nazwa:", 0, QApplication::UnicodeUTF8));
    textLabel4_2->setText(QApplication::translate("Form6", "Kod:", 0, QApplication::UnicodeUTF8));
    groupBox1->setTitle(QApplication::translate("Form6", "Pozosta\305\202e dane: ", 0, QApplication::UnicodeUTF8));
    textLabel7->setText(QApplication::translate("Form6", "Tytu\305\202em:", 0, QApplication::UnicodeUTF8));
    lineEdit17->setText(QString());
    textLabel3_3->setText(QApplication::translate("Form6", "Kwota:", 0, QApplication::UnicodeUTF8));
    kwotaEdit->setInputMask(QApplication::translate("Form6", "999999,99; ", 0, QApplication::UnicodeUTF8));
    kwotaEdit->setText(QApplication::translate("Form6", ",", 0, QApplication::UnicodeUTF8));
    slownieButton->setText(QApplication::translate("Form6", "&s\305\202ownie", 0, QApplication::UnicodeUTF8));
    slownieButton->setShortcut(QApplication::translate("Form6", "Alt+S", 0, QApplication::UnicodeUTF8));
    textLabel6->setText(QApplication::translate("Form6", "Typ:", 0, QApplication::UnicodeUTF8));
    comboBox1->clear();
    comboBox1->insertItems(0, QStringList()
     << QApplication::translate("Form6", "Przelew", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("Form6", "Wp\305\202ata", 0, QApplication::UnicodeUTF8)
    );
    textLabel4_3->setText(QApplication::translate("Form6", "S\305\202ownie:", 0, QApplication::UnicodeUTF8));
    slownieLbl->setText(QString());
    ppriviewButton->setText(QApplication::translate("Form6", "Po&dgl\304\205d", 0, QApplication::UnicodeUTF8));
    ppriviewButton->setShortcut(QApplication::translate("Form6", "Alt+D", 0, QApplication::UnicodeUTF8));
    okButton->setText(QApplication::translate("Form6", "D&rukuj", 0, QApplication::UnicodeUTF8));
    okButton->setShortcut(QApplication::translate("Form6", "Alt+R", 0, QApplication::UnicodeUTF8));
    cancelButton->setText(QApplication::translate("Form6", "Can&cel", 0, QApplication::UnicodeUTF8));
    cancelButton->setShortcut(QApplication::translate("Form6", "Alt+C", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(Form6);
    } // retranslateUi

};

namespace Ui {
    class Form6: public Ui_Form6 {};
} // namespace Ui

#endif // UI_PRZELEW_H
