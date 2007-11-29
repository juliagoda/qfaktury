/********************************************************************************
** Form generated from reading ui file 'chamount.ui'
**
** Created: Thu Nov 29 01:25:38 2007
**      by: Qt User Interface Compiler version 4.3.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_CHAMOUNT_H
#define UI_CHAMOUNT_H

#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
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

class Ui_chAmount
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *okBtn;
    QSpacerItem *spacerItem1;
    QPushButton *cancelBtn;
    QSpacerItem *spacerItem2;
    QFrame *line2;
    QHBoxLayout *hboxLayout1;
    QVBoxLayout *vboxLayout;
    QLabel *textLabel1;
    QLabel *textLabel1_2;
    QLabel *textLabel2;
    QVBoxLayout *vboxLayout1;
    QLineEdit *nameTow;
    QLineEdit *codeTow;
    QSpinBox *spinAmount;
    QSpacerItem *spacerItem3;

    void setupUi(QDialog *chAmount)
    {
    if (chAmount->objectName().isEmpty())
        chAmount->setObjectName(QString::fromUtf8("chAmount"));
    chAmount->resize(412, 167);
    gridLayout = new QGridLayout(chAmount);
    gridLayout->setSpacing(6);
    gridLayout->setMargin(11);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    hboxLayout = new QHBoxLayout();
    hboxLayout->setSpacing(6);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout->addItem(spacerItem);

    okBtn = new QPushButton(chAmount);
    okBtn->setObjectName(QString::fromUtf8("okBtn"));

    hboxLayout->addWidget(okBtn);

    spacerItem1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout->addItem(spacerItem1);

    cancelBtn = new QPushButton(chAmount);
    cancelBtn->setObjectName(QString::fromUtf8("cancelBtn"));

    hboxLayout->addWidget(cancelBtn);

    spacerItem2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout->addItem(spacerItem2);


    gridLayout->addLayout(hboxLayout, 3, 0, 1, 1);

    line2 = new QFrame(chAmount);
    line2->setObjectName(QString::fromUtf8("line2"));
    line2->setFrameShape(QFrame::HLine);
    line2->setFrameShadow(QFrame::Sunken);

    gridLayout->addWidget(line2, 2, 0, 1, 1);

    hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setSpacing(6);
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    vboxLayout = new QVBoxLayout();
    vboxLayout->setSpacing(6);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    textLabel1 = new QLabel(chAmount);
    textLabel1->setObjectName(QString::fromUtf8("textLabel1"));
    textLabel1->setWordWrap(false);

    vboxLayout->addWidget(textLabel1);

    textLabel1_2 = new QLabel(chAmount);
    textLabel1_2->setObjectName(QString::fromUtf8("textLabel1_2"));
    textLabel1_2->setWordWrap(false);

    vboxLayout->addWidget(textLabel1_2);

    textLabel2 = new QLabel(chAmount);
    textLabel2->setObjectName(QString::fromUtf8("textLabel2"));
    textLabel2->setWordWrap(false);

    vboxLayout->addWidget(textLabel2);


    hboxLayout1->addLayout(vboxLayout);

    vboxLayout1 = new QVBoxLayout();
    vboxLayout1->setSpacing(6);
    vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
    nameTow = new QLineEdit(chAmount);
    nameTow->setObjectName(QString::fromUtf8("nameTow"));
    nameTow->setEnabled(false);
    QFont font;
    font.setBold(true);
    font.setWeight(75);
    nameTow->setFont(font);
    nameTow->setReadOnly(true);

    vboxLayout1->addWidget(nameTow);

    codeTow = new QLineEdit(chAmount);
    codeTow->setObjectName(QString::fromUtf8("codeTow"));
    codeTow->setEnabled(false);
    codeTow->setFont(font);
    codeTow->setReadOnly(true);

    vboxLayout1->addWidget(codeTow);

    spinAmount = new QSpinBox(chAmount);
    spinAmount->setObjectName(QString::fromUtf8("spinAmount"));
    spinAmount->setMaximum(999999);

    vboxLayout1->addWidget(spinAmount);


    hboxLayout1->addLayout(vboxLayout1);


    gridLayout->addLayout(hboxLayout1, 0, 0, 1, 1);

    spacerItem3 = new QSpacerItem(20, 41, QSizePolicy::Minimum, QSizePolicy::Expanding);

    gridLayout->addItem(spacerItem3, 1, 0, 1, 1);


    retranslateUi(chAmount);
    QObject::connect(cancelBtn, SIGNAL(clicked()), chAmount, SLOT(close()));
    QObject::connect(okBtn, SIGNAL(clicked()), chAmount, SLOT(accept()));

    QMetaObject::connectSlotsByName(chAmount);
    } // setupUi

    void retranslateUi(QDialog *chAmount)
    {
    chAmount->setWindowTitle(QApplication::translate("chAmount", "Zmie\305\204 ilo\305\233\304\207", 0, QApplication::UnicodeUTF8));
    okBtn->setText(QApplication::translate("chAmount", "&OK", 0, QApplication::UnicodeUTF8));
    okBtn->setShortcut(QApplication::translate("chAmount", "Alt+O", 0, QApplication::UnicodeUTF8));
    cancelBtn->setText(QApplication::translate("chAmount", "&Cancel", 0, QApplication::UnicodeUTF8));
    cancelBtn->setShortcut(QApplication::translate("chAmount", "Alt+C", 0, QApplication::UnicodeUTF8));
    textLabel1->setText(QApplication::translate("chAmount", "Nazwa towaru:", 0, QApplication::UnicodeUTF8));
    textLabel1_2->setText(QApplication::translate("chAmount", "Kod:", 0, QApplication::UnicodeUTF8));
    textLabel2->setText(QApplication::translate("chAmount", "Ilo\305\233\304\207:", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(chAmount);
    } // retranslateUi

};

namespace Ui {
    class chAmount: public Ui_chAmount {};
} // namespace Ui

#endif // UI_CHAMOUNT_H
