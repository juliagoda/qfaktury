/********************************************************************************
** Form generated from reading ui file 'korform.ui'
**
** Created: Thu Nov 29 01:25:38 2007
**      by: Qt User Interface Compiler version 4.3.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_KORFORM_H
#define UI_KORFORM_H

#include <Qt3Support/Q3DateEdit>
#include <Qt3Support/Q3Header>
#include <Qt3Support/Q3MimeSourceFactory>
#include <Qt3Support/Q3Table>
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

class Ui_korForm
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *hboxLayout;
    QHBoxLayout *hboxLayout1;
    QLabel *textLabel1_4;
    QLineEdit *frNr;
    QHBoxLayout *hboxLayout2;
    QLabel *textLabel3_2;
    Q3DateEdit *sellingDate;
    QHBoxLayout *hboxLayout3;
    QHBoxLayout *hboxLayout4;
    QLabel *textLabel1;
    QLineEdit *kontrName;
    QHBoxLayout *hboxLayout5;
    QLabel *textLabel1_5;
    QLabel *paymFry;
    QHBoxLayout *hboxLayout6;
    QHBoxLayout *hboxLayout7;
    QHBoxLayout *hboxLayout8;
    QLabel *textLabel1_3;
    QLineEdit *korNr;
    QToolButton *backBtn;
    QSpacerItem *spacerItem;
    QHBoxLayout *hboxLayout9;
    QLabel *textLabel3;
    Q3DateEdit *sellingDate2;
    QVBoxLayout *vboxLayout;
    QLabel *textLabel1_2;
    Q3Table *tableTow;
    QHBoxLayout *hboxLayout10;
    QSpacerItem *spacerItem1;
    QPushButton *addTw;
    QPushButton *rmTow;
    QPushButton *editTw;
    QSpacerItem *spacerItem2;
    QHBoxLayout *hboxLayout11;
    QLabel *textLabel4;
    QSpinBox *rabatValue;
    QSpacerItem *spacerItem3;
    QHBoxLayout *hboxLayout12;
    QVBoxLayout *vboxLayout1;
    QLabel *textLabel5;
    QLabel *textLabel6;
    QLabel *textLabel1_6;
    QVBoxLayout *vboxLayout2;
    QComboBox *platCombo;
    Q3DateEdit *liabDate;
    QComboBox *reasonCombo;
    QHBoxLayout *hboxLayout13;
    QLabel *textLabel7;
    QLineEdit *additEdit;
    QFrame *line1;
    QHBoxLayout *hboxLayout14;
    QSpacerItem *spacerItem4;
    QPushButton *printBtn;
    QPushButton *saveBtn;
    QSpacerItem *spacerItem5;
    QPushButton *cancelbtn;
    QSpacerItem *spacerItem6;
    QHBoxLayout *hboxLayout15;
    QVBoxLayout *vboxLayout3;
    QLabel *textLabel2;
    QLabel *textLabel2_2;
    QLabel *textLabel1_7;
    QVBoxLayout *vboxLayout4;
    QLabel *fraValLbl;
    QLabel *fvKor;
    QLabel *diffLabel;

    void setupUi(QDialog *korForm)
    {
    if (korForm->objectName().isEmpty())
        korForm->setObjectName(QString::fromUtf8("korForm"));
    korForm->resize(537, 532);
    gridLayout = new QGridLayout(korForm);
    gridLayout->setSpacing(6);
    gridLayout->setMargin(11);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    hboxLayout = new QHBoxLayout();
    hboxLayout->setSpacing(6);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setSpacing(6);
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    textLabel1_4 = new QLabel(korForm);
    textLabel1_4->setObjectName(QString::fromUtf8("textLabel1_4"));
    textLabel1_4->setWordWrap(false);

    hboxLayout1->addWidget(textLabel1_4);

    frNr = new QLineEdit(korForm);
    frNr->setObjectName(QString::fromUtf8("frNr"));
    frNr->setEnabled(false);
    QFont font;
    font.setBold(true);
    font.setWeight(75);
    frNr->setFont(font);

    hboxLayout1->addWidget(frNr);


    hboxLayout->addLayout(hboxLayout1);

    hboxLayout2 = new QHBoxLayout();
    hboxLayout2->setSpacing(6);
    hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
    textLabel3_2 = new QLabel(korForm);
    textLabel3_2->setObjectName(QString::fromUtf8("textLabel3_2"));
    textLabel3_2->setWordWrap(false);

    hboxLayout2->addWidget(textLabel3_2);

    sellingDate = new Q3DateEdit(korForm);
    sellingDate->setObjectName(QString::fromUtf8("sellingDate"));
    sellingDate->setEnabled(false);
    sellingDate->setFont(font);
    sellingDate->setAutoAdvance(true);

    hboxLayout2->addWidget(sellingDate);


    hboxLayout->addLayout(hboxLayout2);


    gridLayout->addLayout(hboxLayout, 0, 0, 1, 3);

    hboxLayout3 = new QHBoxLayout();
    hboxLayout3->setSpacing(6);
    hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
    hboxLayout4 = new QHBoxLayout();
    hboxLayout4->setSpacing(6);
    hboxLayout4->setObjectName(QString::fromUtf8("hboxLayout4"));
    textLabel1 = new QLabel(korForm);
    textLabel1->setObjectName(QString::fromUtf8("textLabel1"));
    textLabel1->setWordWrap(false);

    hboxLayout4->addWidget(textLabel1);

    kontrName = new QLineEdit(korForm);
    kontrName->setObjectName(QString::fromUtf8("kontrName"));
    kontrName->setEnabled(false);
    kontrName->setFont(font);

    hboxLayout4->addWidget(kontrName);


    hboxLayout3->addLayout(hboxLayout4);

    hboxLayout5 = new QHBoxLayout();
    hboxLayout5->setSpacing(6);
    hboxLayout5->setObjectName(QString::fromUtf8("hboxLayout5"));
    textLabel1_5 = new QLabel(korForm);
    textLabel1_5->setObjectName(QString::fromUtf8("textLabel1_5"));
    textLabel1_5->setWordWrap(false);

    hboxLayout5->addWidget(textLabel1_5);

    paymFry = new QLabel(korForm);
    paymFry->setObjectName(QString::fromUtf8("paymFry"));
    paymFry->setMinimumSize(QSize(140, 0));
    paymFry->setWordWrap(false);

    hboxLayout5->addWidget(paymFry);


    hboxLayout3->addLayout(hboxLayout5);


    gridLayout->addLayout(hboxLayout3, 1, 0, 1, 3);

    hboxLayout6 = new QHBoxLayout();
    hboxLayout6->setSpacing(6);
    hboxLayout6->setObjectName(QString::fromUtf8("hboxLayout6"));
    hboxLayout7 = new QHBoxLayout();
    hboxLayout7->setSpacing(6);
    hboxLayout7->setObjectName(QString::fromUtf8("hboxLayout7"));
    hboxLayout8 = new QHBoxLayout();
    hboxLayout8->setSpacing(6);
    hboxLayout8->setObjectName(QString::fromUtf8("hboxLayout8"));
    textLabel1_3 = new QLabel(korForm);
    textLabel1_3->setObjectName(QString::fromUtf8("textLabel1_3"));
    textLabel1_3->setWordWrap(false);

    hboxLayout8->addWidget(textLabel1_3);

    korNr = new QLineEdit(korForm);
    korNr->setObjectName(QString::fromUtf8("korNr"));
    korNr->setEnabled(true);
    korNr->setFont(font);

    hboxLayout8->addWidget(korNr);


    hboxLayout7->addLayout(hboxLayout8);

    backBtn = new QToolButton(korForm);
    backBtn->setObjectName(QString::fromUtf8("backBtn"));

    hboxLayout7->addWidget(backBtn);


    hboxLayout6->addLayout(hboxLayout7);

    spacerItem = new QSpacerItem(31, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout6->addItem(spacerItem);

    hboxLayout9 = new QHBoxLayout();
    hboxLayout9->setSpacing(6);
    hboxLayout9->setObjectName(QString::fromUtf8("hboxLayout9"));
    textLabel3 = new QLabel(korForm);
    textLabel3->setObjectName(QString::fromUtf8("textLabel3"));
    textLabel3->setWordWrap(false);

    hboxLayout9->addWidget(textLabel3);

    sellingDate2 = new Q3DateEdit(korForm);
    sellingDate2->setObjectName(QString::fromUtf8("sellingDate2"));
    sellingDate2->setAutoAdvance(true);

    hboxLayout9->addWidget(sellingDate2);


    hboxLayout6->addLayout(hboxLayout9);


    gridLayout->addLayout(hboxLayout6, 2, 0, 1, 3);

    vboxLayout = new QVBoxLayout();
    vboxLayout->setSpacing(6);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    textLabel1_2 = new QLabel(korForm);
    textLabel1_2->setObjectName(QString::fromUtf8("textLabel1_2"));
    textLabel1_2->setWordWrap(false);

    vboxLayout->addWidget(textLabel1_2);

    tableTow = new Q3Table(korForm);
    tableTow->setObjectName(QString::fromUtf8("tableTow"));
    tableTow->setNumRows(0);
    tableTow->setNumCols(10);
    tableTow->setSorting(true);
    tableTow->setSelectionMode(Q3Table::Multi);

    vboxLayout->addWidget(tableTow);

    hboxLayout10 = new QHBoxLayout();
    hboxLayout10->setSpacing(6);
    hboxLayout10->setObjectName(QString::fromUtf8("hboxLayout10"));
    spacerItem1 = new QSpacerItem(30, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout10->addItem(spacerItem1);

    addTw = new QPushButton(korForm);
    addTw->setObjectName(QString::fromUtf8("addTw"));

    hboxLayout10->addWidget(addTw);

    rmTow = new QPushButton(korForm);
    rmTow->setObjectName(QString::fromUtf8("rmTow"));

    hboxLayout10->addWidget(rmTow);

    editTw = new QPushButton(korForm);
    editTw->setObjectName(QString::fromUtf8("editTw"));

    hboxLayout10->addWidget(editTw);

    spacerItem2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout10->addItem(spacerItem2);

    hboxLayout11 = new QHBoxLayout();
    hboxLayout11->setSpacing(6);
    hboxLayout11->setObjectName(QString::fromUtf8("hboxLayout11"));
    textLabel4 = new QLabel(korForm);
    textLabel4->setObjectName(QString::fromUtf8("textLabel4"));
    textLabel4->setWordWrap(false);

    hboxLayout11->addWidget(textLabel4);

    rabatValue = new QSpinBox(korForm);
    rabatValue->setObjectName(QString::fromUtf8("rabatValue"));
    rabatValue->setEnabled(true);

    hboxLayout11->addWidget(rabatValue);


    hboxLayout10->addLayout(hboxLayout11);


    vboxLayout->addLayout(hboxLayout10);


    gridLayout->addLayout(vboxLayout, 3, 0, 1, 3);

    spacerItem3 = new QSpacerItem(30, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    gridLayout->addItem(spacerItem3, 4, 1, 1, 1);

    hboxLayout12 = new QHBoxLayout();
    hboxLayout12->setSpacing(6);
    hboxLayout12->setObjectName(QString::fromUtf8("hboxLayout12"));
    vboxLayout1 = new QVBoxLayout();
    vboxLayout1->setSpacing(6);
    vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
    textLabel5 = new QLabel(korForm);
    textLabel5->setObjectName(QString::fromUtf8("textLabel5"));
    textLabel5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
    textLabel5->setWordWrap(false);

    vboxLayout1->addWidget(textLabel5);

    textLabel6 = new QLabel(korForm);
    textLabel6->setObjectName(QString::fromUtf8("textLabel6"));
    textLabel6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
    textLabel6->setWordWrap(true);

    vboxLayout1->addWidget(textLabel6);

    textLabel1_6 = new QLabel(korForm);
    textLabel1_6->setObjectName(QString::fromUtf8("textLabel1_6"));
    textLabel1_6->setWordWrap(false);

    vboxLayout1->addWidget(textLabel1_6);


    hboxLayout12->addLayout(vboxLayout1);

    vboxLayout2 = new QVBoxLayout();
    vboxLayout2->setSpacing(6);
    vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
    platCombo = new QComboBox(korForm);
    platCombo->setObjectName(QString::fromUtf8("platCombo"));

    vboxLayout2->addWidget(platCombo);

    liabDate = new Q3DateEdit(korForm);
    liabDate->setObjectName(QString::fromUtf8("liabDate"));

    vboxLayout2->addWidget(liabDate);

    reasonCombo = new QComboBox(korForm);
    reasonCombo->setObjectName(QString::fromUtf8("reasonCombo"));
    reasonCombo->setMinimumSize(QSize(168, 0));

    vboxLayout2->addWidget(reasonCombo);


    hboxLayout12->addLayout(vboxLayout2);


    gridLayout->addLayout(hboxLayout12, 4, 0, 1, 1);

    hboxLayout13 = new QHBoxLayout();
    hboxLayout13->setSpacing(6);
    hboxLayout13->setObjectName(QString::fromUtf8("hboxLayout13"));
    textLabel7 = new QLabel(korForm);
    textLabel7->setObjectName(QString::fromUtf8("textLabel7"));
    textLabel7->setWordWrap(false);

    hboxLayout13->addWidget(textLabel7);

    additEdit = new QLineEdit(korForm);
    additEdit->setObjectName(QString::fromUtf8("additEdit"));

    hboxLayout13->addWidget(additEdit);


    gridLayout->addLayout(hboxLayout13, 5, 0, 1, 3);

    line1 = new QFrame(korForm);
    line1->setObjectName(QString::fromUtf8("line1"));
    line1->setFrameShape(QFrame::HLine);
    line1->setFrameShadow(QFrame::Sunken);

    gridLayout->addWidget(line1, 6, 0, 1, 3);

    hboxLayout14 = new QHBoxLayout();
    hboxLayout14->setSpacing(6);
    hboxLayout14->setObjectName(QString::fromUtf8("hboxLayout14"));
    spacerItem4 = new QSpacerItem(21, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout14->addItem(spacerItem4);

    printBtn = new QPushButton(korForm);
    printBtn->setObjectName(QString::fromUtf8("printBtn"));

    hboxLayout14->addWidget(printBtn);

    saveBtn = new QPushButton(korForm);
    saveBtn->setObjectName(QString::fromUtf8("saveBtn"));

    hboxLayout14->addWidget(saveBtn);

    spacerItem5 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout14->addItem(spacerItem5);

    cancelbtn = new QPushButton(korForm);
    cancelbtn->setObjectName(QString::fromUtf8("cancelbtn"));

    hboxLayout14->addWidget(cancelbtn);

    spacerItem6 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout14->addItem(spacerItem6);


    gridLayout->addLayout(hboxLayout14, 7, 0, 1, 3);

    hboxLayout15 = new QHBoxLayout();
    hboxLayout15->setSpacing(6);
    hboxLayout15->setObjectName(QString::fromUtf8("hboxLayout15"));
    vboxLayout3 = new QVBoxLayout();
    vboxLayout3->setSpacing(6);
    vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
    textLabel2 = new QLabel(korForm);
    textLabel2->setObjectName(QString::fromUtf8("textLabel2"));
    textLabel2->setWordWrap(false);

    vboxLayout3->addWidget(textLabel2);

    textLabel2_2 = new QLabel(korForm);
    textLabel2_2->setObjectName(QString::fromUtf8("textLabel2_2"));
    textLabel2_2->setWordWrap(false);

    vboxLayout3->addWidget(textLabel2_2);

    textLabel1_7 = new QLabel(korForm);
    textLabel1_7->setObjectName(QString::fromUtf8("textLabel1_7"));
    textLabel1_7->setWordWrap(false);

    vboxLayout3->addWidget(textLabel1_7);


    hboxLayout15->addLayout(vboxLayout3);

    vboxLayout4 = new QVBoxLayout();
    vboxLayout4->setSpacing(6);
    vboxLayout4->setObjectName(QString::fromUtf8("vboxLayout4"));
    fraValLbl = new QLabel(korForm);
    fraValLbl->setObjectName(QString::fromUtf8("fraValLbl"));
    fraValLbl->setMinimumSize(QSize(60, 0));
    fraValLbl->setWordWrap(false);

    vboxLayout4->addWidget(fraValLbl);

    fvKor = new QLabel(korForm);
    fvKor->setObjectName(QString::fromUtf8("fvKor"));
    fvKor->setMinimumSize(QSize(60, 0));
    fvKor->setWordWrap(false);

    vboxLayout4->addWidget(fvKor);

    diffLabel = new QLabel(korForm);
    diffLabel->setObjectName(QString::fromUtf8("diffLabel"));
    diffLabel->setWordWrap(false);

    vboxLayout4->addWidget(diffLabel);


    hboxLayout15->addLayout(vboxLayout4);


    gridLayout->addLayout(hboxLayout15, 4, 2, 1, 1);


    retranslateUi(korForm);
    QObject::connect(cancelbtn, SIGNAL(clicked()), korForm, SLOT(reject()));
    QObject::connect(saveBtn, SIGNAL(clicked()), korForm, SLOT(saveInvoice()));
    QObject::connect(backBtn, SIGNAL(clicked()), korForm, SLOT(backBtnClick()));
    QObject::connect(addTw, SIGNAL(clicked()), korForm, SLOT(addTow()));
    QObject::connect(editTw, SIGNAL(clicked()), korForm, SLOT(editTowar()));
    QObject::connect(rmTow, SIGNAL(clicked()), korForm, SLOT(delTowar()));
    QObject::connect(printBtn, SIGNAL(clicked()), korForm, SLOT(makeInvoice()));
    QObject::connect(rabatValue, SIGNAL(valueChanged(QString)), korForm, SLOT(rabatChange()));
    QObject::connect(tableTow, SIGNAL(doubleClicked(int,int,int,QPoint)), korForm, SLOT(editTowar()));

    QMetaObject::connectSlotsByName(korForm);
    } // setupUi

    void retranslateUi(QDialog *korForm)
    {
    korForm->setWindowTitle(QApplication::translate("korForm", "Nowa korekta", 0, QApplication::UnicodeUTF8));
    textLabel1_4->setText(QApplication::translate("korForm", "Dotyczy faktury:", 0, QApplication::UnicodeUTF8));
    textLabel3_2->setText(QApplication::translate("korForm", "Data sprzeda\305\274y:", 0, QApplication::UnicodeUTF8));
    textLabel1->setText(QApplication::translate("korForm", "Kontrahent:", 0, QApplication::UnicodeUTF8));
    textLabel1_5->setText(QApplication::translate("korForm", "P\305\202atno\305\233\304\207:", 0, QApplication::UnicodeUTF8));
    paymFry->setText(QApplication::translate("korForm", "got\303\263wka", 0, QApplication::UnicodeUTF8));
    textLabel1_3->setText(QApplication::translate("korForm", "Symbol:", 0, QApplication::UnicodeUTF8));
    korNr->setText(QApplication::translate("korForm", "1/1/2006", 0, QApplication::UnicodeUTF8));
    backBtn->setText(QApplication::translate("korForm", "co&fnij", 0, QApplication::UnicodeUTF8));
    backBtn->setShortcut(QApplication::translate("korForm", "Alt+F", 0, QApplication::UnicodeUTF8));
    textLabel3->setText(QApplication::translate("korForm", "Data wystawienia:", 0, QApplication::UnicodeUTF8));
    textLabel1_2->setText(QApplication::translate("korForm", "Lista towar\303\263w/us\305\202ug:", 0, QApplication::UnicodeUTF8));
    tableTow->horizontalHeader()->setLabel(0, QApplication::translate("korForm", "Lp.", 0, QApplication::UnicodeUTF8));
    tableTow->horizontalHeader()->setLabel(1, QApplication::translate("korForm", "Nazwa", 0, QApplication::UnicodeUTF8));
    tableTow->horizontalHeader()->setLabel(2, QApplication::translate("korForm", "Kod", 0, QApplication::UnicodeUTF8));
    tableTow->horizontalHeader()->setLabel(3, QApplication::translate("korForm", "PKWiU", 0, QApplication::UnicodeUTF8));
    tableTow->horizontalHeader()->setLabel(4, QApplication::translate("korForm", "Ilo\305\233\304\207", 0, QApplication::UnicodeUTF8));
    tableTow->horizontalHeader()->setLabel(5, QApplication::translate("korForm", "Jm.", 0, QApplication::UnicodeUTF8));
    tableTow->horizontalHeader()->setLabel(6, QApplication::translate("korForm", "Cena jn.", 0, QApplication::UnicodeUTF8));
    tableTow->horizontalHeader()->setLabel(7, QApplication::translate("korForm", "Netto", 0, QApplication::UnicodeUTF8));
    tableTow->horizontalHeader()->setLabel(8, QApplication::translate("korForm", "Vat", 0, QApplication::UnicodeUTF8));
    tableTow->horizontalHeader()->setLabel(9, QApplication::translate("korForm", "Brutto", 0, QApplication::UnicodeUTF8));
    addTw->setText(QApplication::translate("korForm", "Dodaj towar", 0, QApplication::UnicodeUTF8));
    rmTow->setText(QApplication::translate("korForm", "Usu\305\204 towar", 0, QApplication::UnicodeUTF8));
    editTw->setText(QApplication::translate("korForm", "Edycja", 0, QApplication::UnicodeUTF8));
    textLabel4->setText(QApplication::translate("korForm", "Rabat:", 0, QApplication::UnicodeUTF8));
    textLabel5->setText(QApplication::translate("korForm", "P\305\202atno\305\233\304\207:", 0, QApplication::UnicodeUTF8));
    textLabel6->setText(QApplication::translate("korForm", "Termin:", 0, QApplication::UnicodeUTF8));
    textLabel1_6->setText(QApplication::translate("korForm", "Przyczyna:", 0, QApplication::UnicodeUTF8));
    textLabel7->setText(QApplication::translate("korForm", "Dodatkowy tekst:", 0, QApplication::UnicodeUTF8));
    printBtn->setText(QApplication::translate("korForm", "Dru&kuj", 0, QApplication::UnicodeUTF8));
    printBtn->setShortcut(QApplication::translate("korForm", "Alt+K", 0, QApplication::UnicodeUTF8));
    saveBtn->setText(QApplication::translate("korForm", "Zapis&z", 0, QApplication::UnicodeUTF8));
    saveBtn->setShortcut(QApplication::translate("korForm", "Alt+Z", 0, QApplication::UnicodeUTF8));
    cancelbtn->setText(QApplication::translate("korForm", "&Anuluj", 0, QApplication::UnicodeUTF8));
    cancelbtn->setShortcut(QApplication::translate("korForm", "Alt+A", 0, QApplication::UnicodeUTF8));
    textLabel2->setText(QApplication::translate("korForm", "Warto\305\233\304\207 faktury:", 0, QApplication::UnicodeUTF8));
    textLabel2_2->setText(QApplication::translate("korForm", "Warto\305\233\304\207 korekty:", 0, QApplication::UnicodeUTF8));
    textLabel1_7->setText(QApplication::translate("korForm", "R\303\263\305\274nica", 0, QApplication::UnicodeUTF8));
    fraValLbl->setText(QApplication::translate("korForm", "0,00", 0, QApplication::UnicodeUTF8));
    fvKor->setText(QApplication::translate("korForm", "0,00", 0, QApplication::UnicodeUTF8));
    diffLabel->setText(QApplication::translate("korForm", "0,00", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(korForm);
    } // retranslateUi

};

namespace Ui {
    class korForm: public Ui_korForm {};
} // namespace Ui

#endif // UI_KORFORM_H
