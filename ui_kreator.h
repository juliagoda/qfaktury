/********************************************************************************
** Form generated from reading ui file 'kreator.ui'
**
** Created: Thu Nov 29 01:25:38 2007
**      by: Qt User Interface Compiler version 4.3.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_KREATOR_H
#define UI_KREATOR_H

#include <Qt3Support/Q3ButtonGroup>
#include <Qt3Support/Q3GroupBox>
#include <Qt3Support/Q3ListBox>
#include <Qt3Support/Q3MimeSourceFactory>
#include <Qt3Support/Q3TextEdit>
#include <Qt3Support/Q3Wizard>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

class Ui_Form3
{
public:
    QWidget *WizardPage1;
    QHBoxLayout *hboxLayout;
    QLabel *pixmapLabel1;
    QVBoxLayout *vboxLayout;
    QLabel *textLabel1;
    QHBoxLayout *hboxLayout1;
    QSpacerItem *spacerItem;
    Q3ButtonGroup *buttonGroup1;
    QGridLayout *gridLayout;
    QRadioButton *radioButton3;
    QRadioButton *radioButton2;
    QSpacerItem *spacerItem1;
    QSpacerItem *spacerItem2;
    QWidget *WizardPage4;
    QGridLayout *gridLayout1;
    QLabel *pixmapLabel1_2;
    QVBoxLayout *vboxLayout1;
    QLabel *textLabel2_3;
    QHBoxLayout *hboxLayout2;
    QVBoxLayout *vboxLayout2;
    QLabel *textLabel1_2;
    QLabel *textLabel3_2;
    QLabel *textLabel4_2;
    QLabel *textLabel2_2;
    QLabel *textLabel5_2;
    QVBoxLayout *vboxLayout3;
    QLineEdit *nameEdit;
    QLineEdit *placeEdit;
    QLineEdit *codeEdit;
    QLineEdit *addressEdit;
    QLineEdit *accountEdit;
    QSpacerItem *spacerItem3;
    QWidget *WizardPage3;
    QHBoxLayout *hboxLayout3;
    QLabel *pixmapLabel1_2_2;
    Q3ListBox *listBox1;
    QWidget *WizardPage2;
    QHBoxLayout *hboxLayout4;
    QLabel *pixmapLabel1_2_3;
    Q3GroupBox *groupBox1;
    QGridLayout *gridLayout2;
    QHBoxLayout *hboxLayout5;
    QLabel *textLabel4_3;
    QLabel *slownieLbl;
    QHBoxLayout *hboxLayout6;
    QLabel *textLabel3_3;
    QLineEdit *kwotaEdit;
    QHBoxLayout *hboxLayout7;
    QLabel *textLabel7;
    Q3TextEdit *lineEdit17;

    void setupUi(Q3Wizard *Form3)
    {
    if (Form3->objectName().isEmpty())
        Form3->setObjectName(QString::fromUtf8("Form3"));
    Form3->resize(539, 349);
    WizardPage1 = new QWidget(Form3);
    WizardPage1->setObjectName(QString::fromUtf8("WizardPage1"));
    hboxLayout = new QHBoxLayout(WizardPage1);
    hboxLayout->setSpacing(6);
    hboxLayout->setMargin(11);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    hboxLayout->setContentsMargins(0, 0, 0, 0);
    pixmapLabel1 = new QLabel(WizardPage1);
    pixmapLabel1->setObjectName(QString::fromUtf8("pixmapLabel1"));
    pixmapLabel1->setMinimumSize(QSize(200, 0));
    pixmapLabel1->setMaximumSize(QSize(200, 300));
    pixmapLabel1->setScaledContents(true);
    pixmapLabel1->setWordWrap(false);

    hboxLayout->addWidget(pixmapLabel1);

    vboxLayout = new QVBoxLayout();
    vboxLayout->setSpacing(6);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    textLabel1 = new QLabel(WizardPage1);
    textLabel1->setObjectName(QString::fromUtf8("textLabel1"));
    textLabel1->setWordWrap(false);

    vboxLayout->addWidget(textLabel1);

    hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setSpacing(6);
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    spacerItem = new QSpacerItem(30, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout1->addItem(spacerItem);

    buttonGroup1 = new Q3ButtonGroup(WizardPage1);
    buttonGroup1->setObjectName(QString::fromUtf8("buttonGroup1"));
    buttonGroup1->setColumnLayout(0, Qt::Vertical);
    buttonGroup1->layout()->setSpacing(6);
    buttonGroup1->layout()->setMargin(11);
    gridLayout = new QGridLayout();
    QBoxLayout *boxlayout = qobject_cast<QBoxLayout *>(buttonGroup1->layout());
    if (boxlayout)
        boxlayout->addLayout(gridLayout);
    gridLayout->setAlignment(Qt::AlignTop);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    radioButton3 = new QRadioButton(buttonGroup1);
    radioButton3->setObjectName(QString::fromUtf8("radioButton3"));

    gridLayout->addWidget(radioButton3, 1, 0, 1, 1);

    radioButton2 = new QRadioButton(buttonGroup1);
    radioButton2->setObjectName(QString::fromUtf8("radioButton2"));
    radioButton2->setChecked(true);

    gridLayout->addWidget(radioButton2, 0, 0, 1, 1);


    hboxLayout1->addWidget(buttonGroup1);

    spacerItem1 = new QSpacerItem(30, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout1->addItem(spacerItem1);


    vboxLayout->addLayout(hboxLayout1);

    spacerItem2 = new QSpacerItem(21, 106, QSizePolicy::Minimum, QSizePolicy::Expanding);

    vboxLayout->addItem(spacerItem2);


    hboxLayout->addLayout(vboxLayout);

    Form3->addPage(WizardPage1, QApplication::translate("Form3", "Page", 0, QApplication::UnicodeUTF8));
    WizardPage4 = new QWidget(Form3);
    WizardPage4->setObjectName(QString::fromUtf8("WizardPage4"));
    WizardPage4->setGeometry(QRect(0, 0, 100, 30));
    gridLayout1 = new QGridLayout(WizardPage4);
    gridLayout1->setSpacing(6);
    gridLayout1->setMargin(11);
    gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
    gridLayout1->setContentsMargins(0, 0, 0, 0);
    pixmapLabel1_2 = new QLabel(WizardPage4);
    pixmapLabel1_2->setObjectName(QString::fromUtf8("pixmapLabel1_2"));
    pixmapLabel1_2->setMinimumSize(QSize(200, 0));
    pixmapLabel1_2->setMaximumSize(QSize(200, 300));
    pixmapLabel1_2->setScaledContents(true);
    pixmapLabel1_2->setWordWrap(false);

    gridLayout1->addWidget(pixmapLabel1_2, 0, 0, 1, 1);

    vboxLayout1 = new QVBoxLayout();
    vboxLayout1->setSpacing(6);
    vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
    textLabel2_3 = new QLabel(WizardPage4);
    textLabel2_3->setObjectName(QString::fromUtf8("textLabel2_3"));
    textLabel2_3->setWordWrap(false);

    vboxLayout1->addWidget(textLabel2_3);

    hboxLayout2 = new QHBoxLayout();
    hboxLayout2->setSpacing(6);
    hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
    vboxLayout2 = new QVBoxLayout();
    vboxLayout2->setSpacing(6);
    vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
    textLabel1_2 = new QLabel(WizardPage4);
    textLabel1_2->setObjectName(QString::fromUtf8("textLabel1_2"));
    textLabel1_2->setWordWrap(false);

    vboxLayout2->addWidget(textLabel1_2);

    textLabel3_2 = new QLabel(WizardPage4);
    textLabel3_2->setObjectName(QString::fromUtf8("textLabel3_2"));
    textLabel3_2->setWordWrap(false);

    vboxLayout2->addWidget(textLabel3_2);

    textLabel4_2 = new QLabel(WizardPage4);
    textLabel4_2->setObjectName(QString::fromUtf8("textLabel4_2"));
    textLabel4_2->setWordWrap(false);

    vboxLayout2->addWidget(textLabel4_2);

    textLabel2_2 = new QLabel(WizardPage4);
    textLabel2_2->setObjectName(QString::fromUtf8("textLabel2_2"));
    textLabel2_2->setWordWrap(false);

    vboxLayout2->addWidget(textLabel2_2);

    textLabel5_2 = new QLabel(WizardPage4);
    textLabel5_2->setObjectName(QString::fromUtf8("textLabel5_2"));
    textLabel5_2->setWordWrap(false);

    vboxLayout2->addWidget(textLabel5_2);


    hboxLayout2->addLayout(vboxLayout2);

    vboxLayout3 = new QVBoxLayout();
    vboxLayout3->setSpacing(6);
    vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
    nameEdit = new QLineEdit(WizardPage4);
    nameEdit->setObjectName(QString::fromUtf8("nameEdit"));

    vboxLayout3->addWidget(nameEdit);

    placeEdit = new QLineEdit(WizardPage4);
    placeEdit->setObjectName(QString::fromUtf8("placeEdit"));

    vboxLayout3->addWidget(placeEdit);

    codeEdit = new QLineEdit(WizardPage4);
    codeEdit->setObjectName(QString::fromUtf8("codeEdit"));

    vboxLayout3->addWidget(codeEdit);

    addressEdit = new QLineEdit(WizardPage4);
    addressEdit->setObjectName(QString::fromUtf8("addressEdit"));

    vboxLayout3->addWidget(addressEdit);

    accountEdit = new QLineEdit(WizardPage4);
    accountEdit->setObjectName(QString::fromUtf8("accountEdit"));

    vboxLayout3->addWidget(accountEdit);


    hboxLayout2->addLayout(vboxLayout3);


    vboxLayout1->addLayout(hboxLayout2);

    spacerItem3 = new QSpacerItem(20, 51, QSizePolicy::Minimum, QSizePolicy::Expanding);

    vboxLayout1->addItem(spacerItem3);


    gridLayout1->addLayout(vboxLayout1, 0, 1, 1, 1);

    Form3->addPage(WizardPage4, QApplication::translate("Form3", "Page", 0, QApplication::UnicodeUTF8));
    WizardPage3 = new QWidget(Form3);
    WizardPage3->setObjectName(QString::fromUtf8("WizardPage3"));
    WizardPage3->setGeometry(QRect(0, 0, 100, 30));
    hboxLayout3 = new QHBoxLayout(WizardPage3);
    hboxLayout3->setSpacing(6);
    hboxLayout3->setMargin(11);
    hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
    hboxLayout3->setContentsMargins(0, 0, 0, 0);
    pixmapLabel1_2_2 = new QLabel(WizardPage3);
    pixmapLabel1_2_2->setObjectName(QString::fromUtf8("pixmapLabel1_2_2"));
    pixmapLabel1_2_2->setMinimumSize(QSize(200, 0));
    pixmapLabel1_2_2->setMaximumSize(QSize(200, 300));
    pixmapLabel1_2_2->setScaledContents(true);
    pixmapLabel1_2_2->setWordWrap(false);

    hboxLayout3->addWidget(pixmapLabel1_2_2);

    listBox1 = new Q3ListBox(WizardPage3);
    listBox1->setObjectName(QString::fromUtf8("listBox1"));

    hboxLayout3->addWidget(listBox1);

    Form3->addPage(WizardPage3, QApplication::translate("Form3", "Page", 0, QApplication::UnicodeUTF8));
    WizardPage2 = new QWidget(Form3);
    WizardPage2->setObjectName(QString::fromUtf8("WizardPage2"));
    WizardPage2->setGeometry(QRect(0, 0, 100, 30));
    hboxLayout4 = new QHBoxLayout(WizardPage2);
    hboxLayout4->setSpacing(6);
    hboxLayout4->setMargin(11);
    hboxLayout4->setObjectName(QString::fromUtf8("hboxLayout4"));
    hboxLayout4->setContentsMargins(0, 0, 0, 0);
    pixmapLabel1_2_3 = new QLabel(WizardPage2);
    pixmapLabel1_2_3->setObjectName(QString::fromUtf8("pixmapLabel1_2_3"));
    pixmapLabel1_2_3->setMinimumSize(QSize(200, 0));
    pixmapLabel1_2_3->setMaximumSize(QSize(200, 300));
    pixmapLabel1_2_3->setScaledContents(true);
    pixmapLabel1_2_3->setWordWrap(false);

    hboxLayout4->addWidget(pixmapLabel1_2_3);

    groupBox1 = new Q3GroupBox(WizardPage2);
    groupBox1->setObjectName(QString::fromUtf8("groupBox1"));
    groupBox1->setColumnLayout(0, Qt::Vertical);
    groupBox1->layout()->setSpacing(6);
    groupBox1->layout()->setMargin(11);
    gridLayout2 = new QGridLayout();
    QBoxLayout *boxlayout1 = qobject_cast<QBoxLayout *>(groupBox1->layout());
    if (boxlayout1)
        boxlayout1->addLayout(gridLayout2);
    gridLayout2->setAlignment(Qt::AlignTop);
    gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
    hboxLayout5 = new QHBoxLayout();
    hboxLayout5->setSpacing(6);
    hboxLayout5->setObjectName(QString::fromUtf8("hboxLayout5"));
    textLabel4_3 = new QLabel(groupBox1);
    textLabel4_3->setObjectName(QString::fromUtf8("textLabel4_3"));
    textLabel4_3->setMaximumSize(QSize(60, 32767));
    textLabel4_3->setWordWrap(false);

    hboxLayout5->addWidget(textLabel4_3);

    slownieLbl = new QLabel(groupBox1);
    slownieLbl->setObjectName(QString::fromUtf8("slownieLbl"));
    slownieLbl->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
    slownieLbl->setWordWrap(false);

    hboxLayout5->addWidget(slownieLbl);


    gridLayout2->addLayout(hboxLayout5, 1, 0, 1, 1);

    hboxLayout6 = new QHBoxLayout();
    hboxLayout6->setSpacing(6);
    hboxLayout6->setObjectName(QString::fromUtf8("hboxLayout6"));
    textLabel3_3 = new QLabel(groupBox1);
    textLabel3_3->setObjectName(QString::fromUtf8("textLabel3_3"));
    textLabel3_3->setWordWrap(false);

    hboxLayout6->addWidget(textLabel3_3);

    kwotaEdit = new QLineEdit(groupBox1);
    kwotaEdit->setObjectName(QString::fromUtf8("kwotaEdit"));
    kwotaEdit->setAlignment(Qt::AlignRight);

    hboxLayout6->addWidget(kwotaEdit);


    gridLayout2->addLayout(hboxLayout6, 0, 0, 1, 1);

    hboxLayout7 = new QHBoxLayout();
    hboxLayout7->setSpacing(6);
    hboxLayout7->setObjectName(QString::fromUtf8("hboxLayout7"));
    textLabel7 = new QLabel(groupBox1);
    textLabel7->setObjectName(QString::fromUtf8("textLabel7"));
    textLabel7->setAlignment(Qt::AlignTop);
    textLabel7->setWordWrap(false);

    hboxLayout7->addWidget(textLabel7);

    lineEdit17 = new Q3TextEdit(groupBox1);
    lineEdit17->setObjectName(QString::fromUtf8("lineEdit17"));

    hboxLayout7->addWidget(lineEdit17);


    gridLayout2->addLayout(hboxLayout7, 2, 0, 1, 1);


    hboxLayout4->addWidget(groupBox1);

    Form3->addPage(WizardPage2, QApplication::translate("Form3", "Page", 0, QApplication::UnicodeUTF8));
    QWidget::setTabOrder(radioButton2, nameEdit);
    QWidget::setTabOrder(nameEdit, placeEdit);
    QWidget::setTabOrder(placeEdit, codeEdit);
    QWidget::setTabOrder(codeEdit, addressEdit);
    QWidget::setTabOrder(addressEdit, accountEdit);
    QWidget::setTabOrder(accountEdit, listBox1);
    QWidget::setTabOrder(listBox1, kwotaEdit);

    retranslateUi(Form3);
    QObject::connect(Form3, SIGNAL(selected(QString)), Form3, SLOT(nextFunc()));
    QObject::connect(kwotaEdit, SIGNAL(textChanged(QString)), Form3, SLOT(kwotaKeyDown()));

    QMetaObject::connectSlotsByName(Form3);
    } // setupUi

    void retranslateUi(Q3Wizard *Form3)
    {
    Form3->setProperty("caption", QVariant(QApplication::translate("Form3", "Kreator", 0, QApplication::UnicodeUTF8)));
    textLabel1->setText(QApplication::translate("Form3", "<font size=\"+2\"><b>Witaj !!</b></font>", 0, QApplication::UnicodeUTF8));
    buttonGroup1->setTitle(QApplication::translate("Form3", "Co chcesz zrobic?", 0, QApplication::UnicodeUTF8));
    radioButton3->setText(QApplication::translate("Form3", "Wp\305\202ata", 0, QApplication::UnicodeUTF8));
    radioButton2->setText(QApplication::translate("Form3", "Przelew", 0, QApplication::UnicodeUTF8));
    Form3->setTitle(WizardPage1, QApplication::translate("Form3", "Page", 0, QApplication::UnicodeUTF8));
    textLabel2_3->setText(QApplication::translate("Form3", "Nazwa zleceniodawcy:", 0, QApplication::UnicodeUTF8));
    textLabel1_2->setText(QApplication::translate("Form3", "Nazwa:", 0, QApplication::UnicodeUTF8));
    textLabel3_2->setText(QApplication::translate("Form3", "Miejscowo\305\233\304\207:", 0, QApplication::UnicodeUTF8));
    textLabel4_2->setText(QApplication::translate("Form3", "Kod:", 0, QApplication::UnicodeUTF8));
    textLabel2_2->setText(QApplication::translate("Form3", "Adres:", 0, QApplication::UnicodeUTF8));
    textLabel5_2->setText(QApplication::translate("Form3", "Nr konta:", 0, QApplication::UnicodeUTF8));
    accountEdit->setInputMask(QApplication::translate("Form3", "99-9999-9999-9999-9999-9999-9999; ", 0, QApplication::UnicodeUTF8));
    Form3->setTitle(WizardPage4, QApplication::translate("Form3", "Page", 0, QApplication::UnicodeUTF8));
    Form3->setTitle(WizardPage3, QApplication::translate("Form3", "Page", 0, QApplication::UnicodeUTF8));
    groupBox1->setTitle(QApplication::translate("Form3", "Pozosta\305\202e dane: ", 0, QApplication::UnicodeUTF8));
    textLabel4_3->setText(QApplication::translate("Form3", "S\305\202ownie:", 0, QApplication::UnicodeUTF8));
    slownieLbl->setText(QString());
    textLabel3_3->setText(QApplication::translate("Form3", "Kwota:", 0, QApplication::UnicodeUTF8));
    kwotaEdit->setInputMask(QApplication::translate("Form3", "999999,99; ", 0, QApplication::UnicodeUTF8));
    kwotaEdit->setText(QApplication::translate("Form3", ",", 0, QApplication::UnicodeUTF8));
    textLabel7->setText(QApplication::translate("Form3", "Tytu\305\202em:", 0, QApplication::UnicodeUTF8));
    Form3->setTitle(WizardPage2, QApplication::translate("Form3", "Page", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(Form3);
    } // retranslateUi

};

namespace Ui {
    class Form3: public Ui_Form3 {};
} // namespace Ui

#endif // UI_KREATOR_H
