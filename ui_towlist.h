/********************************************************************************
** Form generated from reading ui file 'towlist.ui'
**
** Created: Thu Nov 29 01:25:39 2007
**      by: Qt User Interface Compiler version 4.3.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_TOWLIST_H
#define UI_TOWLIST_H

#include <Qt3Support/Q3Header>
#include <Qt3Support/Q3ListView>
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
#include <QtGui/QVBoxLayout>

class Ui_towList
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *hboxLayout;
    QLabel *textLabel1;
    QComboBox *comboBox1;
    Q3ListView *listView1;
    QHBoxLayout *hboxLayout1;
    QLabel *textLabel4;
    QSpinBox *spinBox2;
    QLineEdit *cenaEdit;
    QHBoxLayout *hboxLayout2;
    QLabel *textLabel1_2;
    QLineEdit *countEdit;
    QHBoxLayout *hboxLayout3;
    QSpacerItem *spacerItem;
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout4;
    QLabel *textLabel3_2;
    QLabel *nettoLabel;
    QHBoxLayout *hboxLayout5;
    QLabel *textLabel3;
    QLabel *bruttoLabel;
    QHBoxLayout *hboxLayout6;
    QSpacerItem *spacerItem1;
    QPushButton *okBtn;
    QSpacerItem *spacerItem2;
    QPushButton *cancelBtn;
    QSpacerItem *spacerItem3;
    QFrame *line3;

    void setupUi(QDialog *towList)
    {
    if (towList->objectName().isEmpty())
        towList->setObjectName(QString::fromUtf8("towList"));
    towList->resize(299, 352);
    gridLayout = new QGridLayout(towList);
    gridLayout->setSpacing(6);
    gridLayout->setMargin(11);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    hboxLayout = new QHBoxLayout();
    hboxLayout->setSpacing(6);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    textLabel1 = new QLabel(towList);
    textLabel1->setObjectName(QString::fromUtf8("textLabel1"));
    textLabel1->setMaximumSize(QSize(50, 32767));
    textLabel1->setWordWrap(false);

    hboxLayout->addWidget(textLabel1);

    comboBox1 = new QComboBox(towList);
    comboBox1->setObjectName(QString::fromUtf8("comboBox1"));

    hboxLayout->addWidget(comboBox1);


    gridLayout->addLayout(hboxLayout, 0, 0, 1, 1);

    listView1 = new Q3ListView(towList);
    listView1->addColumn(QApplication::translate("towList", "Index", 0, QApplication::UnicodeUTF8));
    listView1->addColumn(QApplication::translate("towList", "Nazwa", 0, QApplication::UnicodeUTF8));
    listView1->setObjectName(QString::fromUtf8("listView1"));
    listView1->setSelectionMode(Q3ListView::Single);
    listView1->setAllColumnsShowFocus(true);
    listView1->setResizeMode(Q3ListView::LastColumn);

    gridLayout->addWidget(listView1, 1, 0, 1, 1);

    hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setSpacing(6);
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    textLabel4 = new QLabel(towList);
    textLabel4->setObjectName(QString::fromUtf8("textLabel4"));
    textLabel4->setWordWrap(false);

    hboxLayout1->addWidget(textLabel4);

    spinBox2 = new QSpinBox(towList);
    spinBox2->setObjectName(QString::fromUtf8("spinBox2"));
    spinBox2->setMinimum(1);
    spinBox2->setMaximum(4);

    hboxLayout1->addWidget(spinBox2);

    cenaEdit = new QLineEdit(towList);
    cenaEdit->setObjectName(QString::fromUtf8("cenaEdit"));
    cenaEdit->setEnabled(true);
    cenaEdit->setAlignment(Qt::AlignRight);
    cenaEdit->setReadOnly(false);

    hboxLayout1->addWidget(cenaEdit);


    gridLayout->addLayout(hboxLayout1, 2, 0, 1, 1);

    hboxLayout2 = new QHBoxLayout();
    hboxLayout2->setSpacing(6);
    hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
    textLabel1_2 = new QLabel(towList);
    textLabel1_2->setObjectName(QString::fromUtf8("textLabel1_2"));
    textLabel1_2->setWordWrap(false);

    hboxLayout2->addWidget(textLabel1_2);

    countEdit = new QLineEdit(towList);
    countEdit->setObjectName(QString::fromUtf8("countEdit"));
    countEdit->setAlignment(Qt::AlignRight);

    hboxLayout2->addWidget(countEdit);


    gridLayout->addLayout(hboxLayout2, 3, 0, 1, 1);

    hboxLayout3 = new QHBoxLayout();
    hboxLayout3->setSpacing(6);
    hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
    spacerItem = new QSpacerItem(131, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout3->addItem(spacerItem);

    vboxLayout = new QVBoxLayout();
    vboxLayout->setSpacing(6);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    hboxLayout4 = new QHBoxLayout();
    hboxLayout4->setSpacing(6);
    hboxLayout4->setObjectName(QString::fromUtf8("hboxLayout4"));
    textLabel3_2 = new QLabel(towList);
    textLabel3_2->setObjectName(QString::fromUtf8("textLabel3_2"));
    textLabel3_2->setWordWrap(false);

    hboxLayout4->addWidget(textLabel3_2);

    nettoLabel = new QLabel(towList);
    nettoLabel->setObjectName(QString::fromUtf8("nettoLabel"));
    nettoLabel->setMinimumSize(QSize(80, 0));
    nettoLabel->setWordWrap(false);

    hboxLayout4->addWidget(nettoLabel);


    vboxLayout->addLayout(hboxLayout4);

    hboxLayout5 = new QHBoxLayout();
    hboxLayout5->setSpacing(6);
    hboxLayout5->setObjectName(QString::fromUtf8("hboxLayout5"));
    textLabel3 = new QLabel(towList);
    textLabel3->setObjectName(QString::fromUtf8("textLabel3"));
    textLabel3->setWordWrap(false);

    hboxLayout5->addWidget(textLabel3);

    bruttoLabel = new QLabel(towList);
    bruttoLabel->setObjectName(QString::fromUtf8("bruttoLabel"));
    bruttoLabel->setMinimumSize(QSize(80, 0));
    bruttoLabel->setWordWrap(false);

    hboxLayout5->addWidget(bruttoLabel);


    vboxLayout->addLayout(hboxLayout5);


    hboxLayout3->addLayout(vboxLayout);


    gridLayout->addLayout(hboxLayout3, 4, 0, 1, 1);

    hboxLayout6 = new QHBoxLayout();
    hboxLayout6->setSpacing(6);
    hboxLayout6->setObjectName(QString::fromUtf8("hboxLayout6"));
    spacerItem1 = new QSpacerItem(43, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout6->addItem(spacerItem1);

    okBtn = new QPushButton(towList);
    okBtn->setObjectName(QString::fromUtf8("okBtn"));

    hboxLayout6->addWidget(okBtn);

    spacerItem2 = new QSpacerItem(43, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout6->addItem(spacerItem2);

    cancelBtn = new QPushButton(towList);
    cancelBtn->setObjectName(QString::fromUtf8("cancelBtn"));

    hboxLayout6->addWidget(cancelBtn);

    spacerItem3 = new QSpacerItem(43, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout6->addItem(spacerItem3);


    gridLayout->addLayout(hboxLayout6, 6, 0, 1, 1);

    line3 = new QFrame(towList);
    line3->setObjectName(QString::fromUtf8("line3"));
    line3->setFrameShape(QFrame::HLine);
    line3->setFrameShadow(QFrame::Sunken);

    gridLayout->addWidget(line3, 5, 0, 1, 1);


    retranslateUi(towList);
    QObject::connect(okBtn, SIGNAL(clicked()), towList, SLOT(doAccept()));
    QObject::connect(cancelBtn, SIGNAL(clicked()), towList, SLOT(close()));
    QObject::connect(comboBox1, SIGNAL(activated(int)), towList, SLOT(comboBox1Changed(int)));
    QObject::connect(listView1, SIGNAL(selectionChanged(Q3ListViewItem*)), towList, SLOT(lv1selChanged(Q3ListViewItem*)));
    QObject::connect(spinBox2, SIGNAL(valueChanged(int)), towList, SLOT(spinChanged(int)));
    QObject::connect(countEdit, SIGNAL(selectionChanged()), towList, SLOT(calcNetto()));
    QObject::connect(countEdit, SIGNAL(lostFocus()), towList, SLOT(calcNetto()));
    QObject::connect(countEdit, SIGNAL(textChanged(QString)), towList, SLOT(calcNetto()));

    QMetaObject::connectSlotsByName(towList);
    } // setupUi

    void retranslateUi(QDialog *towList)
    {
    towList->setWindowTitle(QApplication::translate("towList", "Wybierz towar z listy", 0, QApplication::UnicodeUTF8));
    textLabel1->setText(QApplication::translate("towList", "Typ:", 0, QApplication::UnicodeUTF8));
    comboBox1->clear();
    comboBox1->insertItems(0, QStringList()
     << QApplication::translate("towList", "Towar", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("towList", "Us\305\202uga", 0, QApplication::UnicodeUTF8)
    );
    listView1->header()->setLabel(0, QApplication::translate("towList", "Index", 0, QApplication::UnicodeUTF8));
    listView1->header()->setLabel(1, QApplication::translate("towList", "Nazwa", 0, QApplication::UnicodeUTF8));
    textLabel4->setText(QApplication::translate("towList", "Cena jedn.:", 0, QApplication::UnicodeUTF8));
    cenaEdit->setInputMask(QApplication::translate("towList", "99999999,99; ", 0, QApplication::UnicodeUTF8));
    textLabel1_2->setText(QApplication::translate("towList", "Ilo\305\233\304\207:", 0, QApplication::UnicodeUTF8));
    countEdit->setInputMask(QApplication::translate("towList", "99999999; ", 0, QApplication::UnicodeUTF8));
    countEdit->setText(QString());
    textLabel3_2->setText(QApplication::translate("towList", "Netto:", 0, QApplication::UnicodeUTF8));
    nettoLabel->setText(QApplication::translate("towList", "0,00", 0, QApplication::UnicodeUTF8));
    textLabel3->setText(QApplication::translate("towList", "Brutto:", 0, QApplication::UnicodeUTF8));
    bruttoLabel->setText(QApplication::translate("towList", "0,00", 0, QApplication::UnicodeUTF8));
    okBtn->setText(QApplication::translate("towList", "O&K", 0, QApplication::UnicodeUTF8));
    okBtn->setShortcut(QApplication::translate("towList", "Alt+K", 0, QApplication::UnicodeUTF8));
    cancelBtn->setText(QApplication::translate("towList", "Can&cel", 0, QApplication::UnicodeUTF8));
    cancelBtn->setShortcut(QApplication::translate("towList", "Alt+C", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(towList);
    } // retranslateUi

};

namespace Ui {
    class towList: public Ui_towList {};
} // namespace Ui

#endif // UI_TOWLIST_H
