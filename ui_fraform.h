/********************************************************************************
** Form generated from reading ui file 'fraform.ui'
**
** Created: Thu Nov 29 01:25:38 2007
**      by: Qt User Interface Compiler version 4.3.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_FRAFORM_H
#define UI_FRAFORM_H

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

class Ui_FormFra
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *hboxLayout;
    QHBoxLayout *hboxLayout1;
    QLabel *textLabel1;
    QLineEdit *kontrName;
    QToolButton *kListGet;
    QHBoxLayout *hboxLayout2;
    QHBoxLayout *hboxLayout3;
    QHBoxLayout *hboxLayout4;
    QLabel *textLabel1_3;
    QLineEdit *frNr;
    QToolButton *backBtn;
    QSpacerItem *spacerItem;
    QHBoxLayout *hboxLayout5;
    QLabel *textLabel3;
    Q3DateEdit *sellingDate;
    QVBoxLayout *vboxLayout;
    QLabel *textLabel1_2;
    Q3Table *tableTow;
    QHBoxLayout *hboxLayout6;
    QSpacerItem *spacerItem1;
    QPushButton *addTw;
    QPushButton *rmTow;
    QPushButton *editTw;
    QSpacerItem *spacerItem2;
    QHBoxLayout *hboxLayout7;
    QLabel *textLabel4;
    QSpinBox *rabatValue;
    QSpacerItem *spacerItem3;
    QHBoxLayout *hboxLayout8;
    QSpacerItem *spacerItem4;
    QPushButton *printBtn;
    QPushButton *saveBtn;
    QSpacerItem *spacerItem5;
    QPushButton *cancelbtn;
    QSpacerItem *spacerItem6;
    QFrame *line1;
    QHBoxLayout *hboxLayout9;
    QLabel *textLabel7;
    QLineEdit *additEdit;
    QVBoxLayout *vboxLayout1;
    QHBoxLayout *hboxLayout10;
    QVBoxLayout *vboxLayout2;
    QLabel *textLabel2;
    QLabel *textLabel2_2_2;
    QLabel *textLabel2_2;
    QVBoxLayout *vboxLayout3;
    QLabel *snetto;
    QLabel *sRabat;
    QLabel *sbrutto;
    QHBoxLayout *hboxLayout11;
    QVBoxLayout *vboxLayout4;
    QLabel *textLabel5;
    QLabel *textLabel6;
    QLabel *textLabel2_3;
    QVBoxLayout *vboxLayout5;
    QComboBox *platCombo;
    Q3DateEdit *liabDate;
    QComboBox *currCombo;

    void setupUi(QDialog *FormFra)
    {
    if (FormFra->objectName().isEmpty())
        FormFra->setObjectName(QString::fromUtf8("FormFra"));
    FormFra->resize(515, 494);
    gridLayout = new QGridLayout(FormFra);
    gridLayout->setSpacing(6);
    gridLayout->setMargin(11);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    hboxLayout = new QHBoxLayout();
    hboxLayout->setSpacing(6);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setSpacing(6);
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    textLabel1 = new QLabel(FormFra);
    textLabel1->setObjectName(QString::fromUtf8("textLabel1"));
    textLabel1->setWordWrap(false);

    hboxLayout1->addWidget(textLabel1);

    kontrName = new QLineEdit(FormFra);
    kontrName->setObjectName(QString::fromUtf8("kontrName"));
    kontrName->setEnabled(false);
    QFont font;
    font.setBold(true);
    font.setWeight(75);
    kontrName->setFont(font);

    hboxLayout1->addWidget(kontrName);


    hboxLayout->addLayout(hboxLayout1);

    kListGet = new QToolButton(FormFra);
    kListGet->setObjectName(QString::fromUtf8("kListGet"));

    hboxLayout->addWidget(kListGet);


    gridLayout->addLayout(hboxLayout, 1, 0, 1, 3);

    hboxLayout2 = new QHBoxLayout();
    hboxLayout2->setSpacing(6);
    hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
    hboxLayout3 = new QHBoxLayout();
    hboxLayout3->setSpacing(6);
    hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
    hboxLayout4 = new QHBoxLayout();
    hboxLayout4->setSpacing(6);
    hboxLayout4->setObjectName(QString::fromUtf8("hboxLayout4"));
    textLabel1_3 = new QLabel(FormFra);
    textLabel1_3->setObjectName(QString::fromUtf8("textLabel1_3"));
    textLabel1_3->setWordWrap(false);

    hboxLayout4->addWidget(textLabel1_3);

    frNr = new QLineEdit(FormFra);
    frNr->setObjectName(QString::fromUtf8("frNr"));
    frNr->setEnabled(true);
    frNr->setFont(font);

    hboxLayout4->addWidget(frNr);


    hboxLayout3->addLayout(hboxLayout4);

    backBtn = new QToolButton(FormFra);
    backBtn->setObjectName(QString::fromUtf8("backBtn"));

    hboxLayout3->addWidget(backBtn);


    hboxLayout2->addLayout(hboxLayout3);

    spacerItem = new QSpacerItem(31, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout2->addItem(spacerItem);

    hboxLayout5 = new QHBoxLayout();
    hboxLayout5->setSpacing(6);
    hboxLayout5->setObjectName(QString::fromUtf8("hboxLayout5"));
    textLabel3 = new QLabel(FormFra);
    textLabel3->setObjectName(QString::fromUtf8("textLabel3"));
    textLabel3->setWordWrap(false);

    hboxLayout5->addWidget(textLabel3);

    sellingDate = new Q3DateEdit(FormFra);
    sellingDate->setObjectName(QString::fromUtf8("sellingDate"));
    sellingDate->setAutoAdvance(true);

    hboxLayout5->addWidget(sellingDate);


    hboxLayout2->addLayout(hboxLayout5);


    gridLayout->addLayout(hboxLayout2, 0, 0, 1, 3);

    vboxLayout = new QVBoxLayout();
    vboxLayout->setSpacing(6);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    textLabel1_2 = new QLabel(FormFra);
    textLabel1_2->setObjectName(QString::fromUtf8("textLabel1_2"));
    textLabel1_2->setWordWrap(false);

    vboxLayout->addWidget(textLabel1_2);

    tableTow = new Q3Table(FormFra);
    tableTow->setObjectName(QString::fromUtf8("tableTow"));
    tableTow->setNumRows(0);
    tableTow->setNumCols(10);
    tableTow->setSorting(true);
    tableTow->setSelectionMode(Q3Table::Multi);

    vboxLayout->addWidget(tableTow);

    hboxLayout6 = new QHBoxLayout();
    hboxLayout6->setSpacing(6);
    hboxLayout6->setObjectName(QString::fromUtf8("hboxLayout6"));
    spacerItem1 = new QSpacerItem(30, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout6->addItem(spacerItem1);

    addTw = new QPushButton(FormFra);
    addTw->setObjectName(QString::fromUtf8("addTw"));

    hboxLayout6->addWidget(addTw);

    rmTow = new QPushButton(FormFra);
    rmTow->setObjectName(QString::fromUtf8("rmTow"));

    hboxLayout6->addWidget(rmTow);

    editTw = new QPushButton(FormFra);
    editTw->setObjectName(QString::fromUtf8("editTw"));

    hboxLayout6->addWidget(editTw);

    spacerItem2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout6->addItem(spacerItem2);

    hboxLayout7 = new QHBoxLayout();
    hboxLayout7->setSpacing(6);
    hboxLayout7->setObjectName(QString::fromUtf8("hboxLayout7"));
    textLabel4 = new QLabel(FormFra);
    textLabel4->setObjectName(QString::fromUtf8("textLabel4"));
    textLabel4->setWordWrap(false);

    hboxLayout7->addWidget(textLabel4);

    rabatValue = new QSpinBox(FormFra);
    rabatValue->setObjectName(QString::fromUtf8("rabatValue"));

    hboxLayout7->addWidget(rabatValue);


    hboxLayout6->addLayout(hboxLayout7);


    vboxLayout->addLayout(hboxLayout6);


    gridLayout->addLayout(vboxLayout, 2, 0, 1, 3);

    spacerItem3 = new QSpacerItem(16, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    gridLayout->addItem(spacerItem3, 3, 1, 1, 1);

    hboxLayout8 = new QHBoxLayout();
    hboxLayout8->setSpacing(6);
    hboxLayout8->setObjectName(QString::fromUtf8("hboxLayout8"));
    spacerItem4 = new QSpacerItem(21, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout8->addItem(spacerItem4);

    printBtn = new QPushButton(FormFra);
    printBtn->setObjectName(QString::fromUtf8("printBtn"));

    hboxLayout8->addWidget(printBtn);

    saveBtn = new QPushButton(FormFra);
    saveBtn->setObjectName(QString::fromUtf8("saveBtn"));

    hboxLayout8->addWidget(saveBtn);

    spacerItem5 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout8->addItem(spacerItem5);

    cancelbtn = new QPushButton(FormFra);
    cancelbtn->setObjectName(QString::fromUtf8("cancelbtn"));

    hboxLayout8->addWidget(cancelbtn);

    spacerItem6 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout8->addItem(spacerItem6);


    gridLayout->addLayout(hboxLayout8, 6, 0, 1, 3);

    line1 = new QFrame(FormFra);
    line1->setObjectName(QString::fromUtf8("line1"));
    line1->setFrameShape(QFrame::HLine);
    line1->setFrameShadow(QFrame::Sunken);

    gridLayout->addWidget(line1, 5, 0, 1, 3);

    hboxLayout9 = new QHBoxLayout();
    hboxLayout9->setSpacing(6);
    hboxLayout9->setObjectName(QString::fromUtf8("hboxLayout9"));
    textLabel7 = new QLabel(FormFra);
    textLabel7->setObjectName(QString::fromUtf8("textLabel7"));
    textLabel7->setWordWrap(false);

    hboxLayout9->addWidget(textLabel7);

    additEdit = new QLineEdit(FormFra);
    additEdit->setObjectName(QString::fromUtf8("additEdit"));

    hboxLayout9->addWidget(additEdit);


    gridLayout->addLayout(hboxLayout9, 4, 0, 1, 3);

    vboxLayout1 = new QVBoxLayout();
    vboxLayout1->setSpacing(6);
    vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
    hboxLayout10 = new QHBoxLayout();
    hboxLayout10->setSpacing(6);
    hboxLayout10->setObjectName(QString::fromUtf8("hboxLayout10"));
    vboxLayout2 = new QVBoxLayout();
    vboxLayout2->setSpacing(6);
    vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
    textLabel2 = new QLabel(FormFra);
    textLabel2->setObjectName(QString::fromUtf8("textLabel2"));
    textLabel2->setMinimumSize(QSize(150, 0));
    textLabel2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
    textLabel2->setWordWrap(false);

    vboxLayout2->addWidget(textLabel2);

    textLabel2_2_2 = new QLabel(FormFra);
    textLabel2_2_2->setObjectName(QString::fromUtf8("textLabel2_2_2"));
    textLabel2_2_2->setMinimumSize(QSize(150, 0));
    textLabel2_2_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
    textLabel2_2_2->setWordWrap(false);

    vboxLayout2->addWidget(textLabel2_2_2);

    textLabel2_2 = new QLabel(FormFra);
    textLabel2_2->setObjectName(QString::fromUtf8("textLabel2_2"));
    textLabel2_2->setMinimumSize(QSize(150, 0));
    textLabel2_2->setFont(font);
    textLabel2_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
    textLabel2_2->setWordWrap(false);

    vboxLayout2->addWidget(textLabel2_2);


    hboxLayout10->addLayout(vboxLayout2);

    vboxLayout3 = new QVBoxLayout();
    vboxLayout3->setSpacing(6);
    vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
    snetto = new QLabel(FormFra);
    snetto->setObjectName(QString::fromUtf8("snetto"));
    snetto->setMinimumSize(QSize(80, 0));
    snetto->setWordWrap(false);

    vboxLayout3->addWidget(snetto);

    sRabat = new QLabel(FormFra);
    sRabat->setObjectName(QString::fromUtf8("sRabat"));
    sRabat->setMinimumSize(QSize(80, 0));
    sRabat->setWordWrap(false);

    vboxLayout3->addWidget(sRabat);

    sbrutto = new QLabel(FormFra);
    sbrutto->setObjectName(QString::fromUtf8("sbrutto"));
    sbrutto->setMinimumSize(QSize(80, 0));
    sbrutto->setFont(font);
    sbrutto->setWordWrap(false);

    vboxLayout3->addWidget(sbrutto);


    hboxLayout10->addLayout(vboxLayout3);


    vboxLayout1->addLayout(hboxLayout10);


    gridLayout->addLayout(vboxLayout1, 3, 2, 1, 1);

    hboxLayout11 = new QHBoxLayout();
    hboxLayout11->setSpacing(6);
    hboxLayout11->setObjectName(QString::fromUtf8("hboxLayout11"));
    vboxLayout4 = new QVBoxLayout();
    vboxLayout4->setSpacing(6);
    vboxLayout4->setObjectName(QString::fromUtf8("vboxLayout4"));
    textLabel5 = new QLabel(FormFra);
    textLabel5->setObjectName(QString::fromUtf8("textLabel5"));
    textLabel5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
    textLabel5->setWordWrap(false);

    vboxLayout4->addWidget(textLabel5);

    textLabel6 = new QLabel(FormFra);
    textLabel6->setObjectName(QString::fromUtf8("textLabel6"));
    textLabel6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
    textLabel6->setWordWrap(true);

    vboxLayout4->addWidget(textLabel6);

    textLabel2_3 = new QLabel(FormFra);
    textLabel2_3->setObjectName(QString::fromUtf8("textLabel2_3"));
    textLabel2_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
    textLabel2_3->setWordWrap(false);

    vboxLayout4->addWidget(textLabel2_3);


    hboxLayout11->addLayout(vboxLayout4);

    vboxLayout5 = new QVBoxLayout();
    vboxLayout5->setSpacing(6);
    vboxLayout5->setObjectName(QString::fromUtf8("vboxLayout5"));
    platCombo = new QComboBox(FormFra);
    platCombo->setObjectName(QString::fromUtf8("platCombo"));

    vboxLayout5->addWidget(platCombo);

    liabDate = new Q3DateEdit(FormFra);
    liabDate->setObjectName(QString::fromUtf8("liabDate"));

    vboxLayout5->addWidget(liabDate);

    currCombo = new QComboBox(FormFra);
    currCombo->setObjectName(QString::fromUtf8("currCombo"));
    currCombo->setMinimumSize(QSize(80, 0));

    vboxLayout5->addWidget(currCombo);


    hboxLayout11->addLayout(vboxLayout5);


    gridLayout->addLayout(hboxLayout11, 3, 0, 1, 1);


    retranslateUi(FormFra);
    QObject::connect(cancelbtn, SIGNAL(clicked()), FormFra, SLOT(close()));
    QObject::connect(addTw, SIGNAL(clicked()), FormFra, SLOT(addTow()));
    QObject::connect(kListGet, SIGNAL(clicked()), FormFra, SLOT(getKontrahent()));
    QObject::connect(rabatValue, SIGNAL(valueChanged(int)), FormFra, SLOT(rabatChange()));
    QObject::connect(rmTow, SIGNAL(clicked()), FormFra, SLOT(delTowar()));
    QObject::connect(tableTow, SIGNAL(doubleClicked(int,int,int,QPoint)), FormFra, SLOT(editTowar()));
    QObject::connect(editTw, SIGNAL(clicked()), FormFra, SLOT(editTowar()));
    QObject::connect(printBtn, SIGNAL(clicked()), FormFra, SLOT(makeInvoice()));
    QObject::connect(saveBtn, SIGNAL(clicked()), FormFra, SLOT(saveInvoice()));
    QObject::connect(backBtn, SIGNAL(clicked()), FormFra, SLOT(backBtnClick()));

    QMetaObject::connectSlotsByName(FormFra);
    } // setupUi

    void retranslateUi(QDialog *FormFra)
    {
    FormFra->setWindowTitle(QApplication::translate("FormFra", "Faktura VAT", 0, QApplication::UnicodeUTF8));
    textLabel1->setText(QApplication::translate("FormFra", "Kontrahent:", 0, QApplication::UnicodeUTF8));
    kListGet->setText(QApplication::translate("FormFra", "wybier&z", 0, QApplication::UnicodeUTF8));
    kListGet->setShortcut(QApplication::translate("FormFra", "Alt+Z", 0, QApplication::UnicodeUTF8));
    textLabel1_3->setText(QApplication::translate("FormFra", "Symbol:", 0, QApplication::UnicodeUTF8));
    frNr->setText(QApplication::translate("FormFra", "1/1/2006", 0, QApplication::UnicodeUTF8));
    backBtn->setText(QApplication::translate("FormFra", "co&fnij", 0, QApplication::UnicodeUTF8));
    backBtn->setShortcut(QApplication::translate("FormFra", "Alt+F", 0, QApplication::UnicodeUTF8));
    textLabel3->setText(QApplication::translate("FormFra", "Data sprzeda\305\274y:", 0, QApplication::UnicodeUTF8));
    textLabel1_2->setText(QApplication::translate("FormFra", "Lista towar\303\263w/us\305\202ug:", 0, QApplication::UnicodeUTF8));
    tableTow->horizontalHeader()->setLabel(0, QApplication::translate("FormFra", "Lp.", 0, QApplication::UnicodeUTF8));
    tableTow->horizontalHeader()->setLabel(1, QApplication::translate("FormFra", "Nazwa", 0, QApplication::UnicodeUTF8));
    tableTow->horizontalHeader()->setLabel(2, QApplication::translate("FormFra", "Kod", 0, QApplication::UnicodeUTF8));
    tableTow->horizontalHeader()->setLabel(3, QApplication::translate("FormFra", "PKWiU", 0, QApplication::UnicodeUTF8));
    tableTow->horizontalHeader()->setLabel(4, QApplication::translate("FormFra", "Ilo\305\233\304\207", 0, QApplication::UnicodeUTF8));
    tableTow->horizontalHeader()->setLabel(5, QApplication::translate("FormFra", "Jm.", 0, QApplication::UnicodeUTF8));
    tableTow->horizontalHeader()->setLabel(6, QApplication::translate("FormFra", "Cena jn.", 0, QApplication::UnicodeUTF8));
    tableTow->horizontalHeader()->setLabel(7, QApplication::translate("FormFra", "Netto", 0, QApplication::UnicodeUTF8));
    tableTow->horizontalHeader()->setLabel(8, QApplication::translate("FormFra", "Vat", 0, QApplication::UnicodeUTF8));
    tableTow->horizontalHeader()->setLabel(9, QApplication::translate("FormFra", "Brutto", 0, QApplication::UnicodeUTF8));
    addTw->setText(QApplication::translate("FormFra", "Dodaj towar", 0, QApplication::UnicodeUTF8));
    rmTow->setText(QApplication::translate("FormFra", "Usu\305\204 towar", 0, QApplication::UnicodeUTF8));
    editTw->setText(QApplication::translate("FormFra", "Edycja", 0, QApplication::UnicodeUTF8));
    textLabel4->setText(QApplication::translate("FormFra", "Rabat:", 0, QApplication::UnicodeUTF8));
    printBtn->setText(QApplication::translate("FormFra", "Dru&kuj", 0, QApplication::UnicodeUTF8));
    printBtn->setShortcut(QApplication::translate("FormFra", "Alt+K", 0, QApplication::UnicodeUTF8));
    saveBtn->setText(QApplication::translate("FormFra", "Zapis&z", 0, QApplication::UnicodeUTF8));
    saveBtn->setShortcut(QApplication::translate("FormFra", "Alt+Z", 0, QApplication::UnicodeUTF8));
    cancelbtn->setText(QApplication::translate("FormFra", "&Anuluj", 0, QApplication::UnicodeUTF8));
    cancelbtn->setShortcut(QApplication::translate("FormFra", "Alt+A", 0, QApplication::UnicodeUTF8));
    textLabel7->setText(QApplication::translate("FormFra", "Dodatkowy tekst:", 0, QApplication::UnicodeUTF8));
    additEdit->setText(QApplication::translate("FormFra", "towar odebra\305\202em zgodnie z faktur\304\205", 0, QApplication::UnicodeUTF8));
    textLabel2->setText(QApplication::translate("FormFra", "Razem netto:", 0, QApplication::UnicodeUTF8));
    textLabel2_2_2->setText(QApplication::translate("FormFra", "Rabat:", 0, QApplication::UnicodeUTF8));
    textLabel2_2->setText(QApplication::translate("FormFra", "Do zaplaty:", 0, QApplication::UnicodeUTF8));
    snetto->setText(QApplication::translate("FormFra", "0,00", 0, QApplication::UnicodeUTF8));
    sRabat->setText(QApplication::translate("FormFra", "0,00", 0, QApplication::UnicodeUTF8));
    sbrutto->setText(QApplication::translate("FormFra", "0,00", 0, QApplication::UnicodeUTF8));
    textLabel5->setText(QApplication::translate("FormFra", "P\305\202atno\305\233\304\207:", 0, QApplication::UnicodeUTF8));
    textLabel6->setText(QApplication::translate("FormFra", "Termin:", 0, QApplication::UnicodeUTF8));
    textLabel2_3->setText(QApplication::translate("FormFra", "Waluta:", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(FormFra);
    } // retranslateUi

};

namespace Ui {
    class FormFra: public Ui_FormFra {};
} // namespace Ui

#endif // UI_FRAFORM_H
