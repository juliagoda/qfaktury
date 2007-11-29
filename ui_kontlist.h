/********************************************************************************
** Form generated from reading ui file 'kontlist.ui'
**
** Created: Thu Nov 29 01:25:38 2007
**      by: Qt User Interface Compiler version 4.3.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_KONTLIST_H
#define UI_KONTLIST_H

#include <Qt3Support/Q3ListBox>
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
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>

class Ui_kontList
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *hboxLayout;
    QLabel *textLabel1;
    QComboBox *comboBox1;
    Q3ListBox *listBox1;
    QHBoxLayout *hboxLayout1;
    QSpacerItem *spacerItem;
    QPushButton *okBtn;
    QSpacerItem *spacerItem1;
    QPushButton *cancelBtn;
    QSpacerItem *spacerItem2;
    QFrame *line4;

    void setupUi(QDialog *kontList)
    {
    if (kontList->objectName().isEmpty())
        kontList->setObjectName(QString::fromUtf8("kontList"));
    kontList->resize(285, 337);
    gridLayout = new QGridLayout(kontList);
    gridLayout->setSpacing(6);
    gridLayout->setMargin(11);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    hboxLayout = new QHBoxLayout();
    hboxLayout->setSpacing(6);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    textLabel1 = new QLabel(kontList);
    textLabel1->setObjectName(QString::fromUtf8("textLabel1"));
    textLabel1->setMaximumSize(QSize(50, 32767));
    textLabel1->setWordWrap(false);

    hboxLayout->addWidget(textLabel1);

    comboBox1 = new QComboBox(kontList);
    comboBox1->setObjectName(QString::fromUtf8("comboBox1"));

    hboxLayout->addWidget(comboBox1);


    gridLayout->addLayout(hboxLayout, 0, 0, 1, 1);

    listBox1 = new Q3ListBox(kontList);
    listBox1->setObjectName(QString::fromUtf8("listBox1"));

    gridLayout->addWidget(listBox1, 1, 0, 1, 1);

    hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setSpacing(6);
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout1->addItem(spacerItem);

    okBtn = new QPushButton(kontList);
    okBtn->setObjectName(QString::fromUtf8("okBtn"));

    hboxLayout1->addWidget(okBtn);

    spacerItem1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout1->addItem(spacerItem1);

    cancelBtn = new QPushButton(kontList);
    cancelBtn->setObjectName(QString::fromUtf8("cancelBtn"));

    hboxLayout1->addWidget(cancelBtn);

    spacerItem2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout1->addItem(spacerItem2);


    gridLayout->addLayout(hboxLayout1, 3, 0, 1, 1);

    line4 = new QFrame(kontList);
    line4->setObjectName(QString::fromUtf8("line4"));
    line4->setFrameShape(QFrame::HLine);
    line4->setFrameShadow(QFrame::Sunken);

    gridLayout->addWidget(line4, 2, 0, 1, 1);


    retranslateUi(kontList);
    QObject::connect(okBtn, SIGNAL(clicked()), kontList, SLOT(doAccept()));
    QObject::connect(cancelBtn, SIGNAL(clicked()), kontList, SLOT(close()));
    QObject::connect(comboBox1, SIGNAL(activated(int)), kontList, SLOT(comboBox1Changed()));
    QObject::connect(listBox1, SIGNAL(doubleClicked(Q3ListBoxItem*)), kontList, SLOT(doAccept()));

    QMetaObject::connectSlotsByName(kontList);
    } // setupUi

    void retranslateUi(QDialog *kontList)
    {
    kontList->setWindowTitle(QApplication::translate("kontList", "Wybierz kontrahenta z listy", 0, QApplication::UnicodeUTF8));
    textLabel1->setText(QApplication::translate("kontList", "Typ:", 0, QApplication::UnicodeUTF8));
    comboBox1->clear();
    comboBox1->insertItems(0, QStringList()
     << QApplication::translate("kontList", "Firma", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("kontList", "Urz\304\205d", 0, QApplication::UnicodeUTF8)
    );
    okBtn->setText(QApplication::translate("kontList", "O&K", 0, QApplication::UnicodeUTF8));
    okBtn->setShortcut(QApplication::translate("kontList", "Alt+K", 0, QApplication::UnicodeUTF8));
    cancelBtn->setText(QApplication::translate("kontList", "Can&cel", 0, QApplication::UnicodeUTF8));
    cancelBtn->setShortcut(QApplication::translate("kontList", "Alt+C", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(kontList);
    } // retranslateUi

};

namespace Ui {
    class kontList: public Ui_kontList {};
} // namespace Ui

#endif // UI_KONTLIST_H
