/********************************************************************************
** Form generated from reading UI file 'ChangeAmount.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANGEAMOUNT_H
#define UI_CHANGEAMOUNT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ChangeAmount
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

    void setupUi(QDialog *ChangeAmount)
    {
        if (ChangeAmount->objectName().isEmpty())
            ChangeAmount->setObjectName(QStringLiteral("ChangeAmount"));
        ChangeAmount->resize(378, 190);
        gridLayout = new QGridLayout(ChangeAmount);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
        spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        okBtn = new QPushButton(ChangeAmount);
        okBtn->setObjectName(QStringLiteral("okBtn"));
        okBtn->setCursor(QCursor(Qt::PointingHandCursor));

        hboxLayout->addWidget(okBtn);

        spacerItem1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem1);

        cancelBtn = new QPushButton(ChangeAmount);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));
        cancelBtn->setCursor(QCursor(Qt::PointingHandCursor));

        hboxLayout->addWidget(cancelBtn);

        spacerItem2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem2);


        gridLayout->addLayout(hboxLayout, 3, 0, 1, 1);

        line2 = new QFrame(ChangeAmount);
        line2->setObjectName(QStringLiteral("line2"));
        line2->setFrameShape(QFrame::HLine);
        line2->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line2, 2, 0, 1, 1);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setObjectName(QStringLiteral("hboxLayout1"));
        vboxLayout = new QVBoxLayout();
        vboxLayout->setSpacing(6);
        vboxLayout->setObjectName(QStringLiteral("vboxLayout"));
        textLabel1 = new QLabel(ChangeAmount);
        textLabel1->setObjectName(QStringLiteral("textLabel1"));
        textLabel1->setWordWrap(false);

        vboxLayout->addWidget(textLabel1);

        textLabel1_2 = new QLabel(ChangeAmount);
        textLabel1_2->setObjectName(QStringLiteral("textLabel1_2"));
        textLabel1_2->setWordWrap(false);

        vboxLayout->addWidget(textLabel1_2);

        textLabel2 = new QLabel(ChangeAmount);
        textLabel2->setObjectName(QStringLiteral("textLabel2"));
        textLabel2->setWordWrap(false);

        vboxLayout->addWidget(textLabel2);


        hboxLayout1->addLayout(vboxLayout);

        vboxLayout1 = new QVBoxLayout();
        vboxLayout1->setSpacing(6);
        vboxLayout1->setObjectName(QStringLiteral("vboxLayout1"));
        nameTow = new QLineEdit(ChangeAmount);
        nameTow->setObjectName(QStringLiteral("nameTow"));
        nameTow->setEnabled(false);
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        nameTow->setFont(font);
        nameTow->setReadOnly(true);

        vboxLayout1->addWidget(nameTow);

        codeTow = new QLineEdit(ChangeAmount);
        codeTow->setObjectName(QStringLiteral("codeTow"));
        codeTow->setEnabled(false);
        codeTow->setFont(font);
        codeTow->setReadOnly(true);

        vboxLayout1->addWidget(codeTow);

        spinAmount = new QSpinBox(ChangeAmount);
        spinAmount->setObjectName(QStringLiteral("spinAmount"));
        spinAmount->setMinimum(1);
        spinAmount->setMaximum(999999);

        vboxLayout1->addWidget(spinAmount);


        hboxLayout1->addLayout(vboxLayout1);


        gridLayout->addLayout(hboxLayout1, 0, 0, 1, 1);

        spacerItem3 = new QSpacerItem(20, 41, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(spacerItem3, 1, 0, 1, 1);


        retranslateUi(ChangeAmount);
        QObject::connect(cancelBtn, SIGNAL(clicked()), ChangeAmount, SLOT(close()));
        QObject::connect(okBtn, SIGNAL(clicked()), ChangeAmount, SLOT(accept()));

        QMetaObject::connectSlotsByName(ChangeAmount);
    } // setupUi

    void retranslateUi(QDialog *ChangeAmount)
    {
        ChangeAmount->setWindowTitle(QApplication::translate("ChangeAmount", "Zmie\305\204 ilo\305\233\304\207", Q_NULLPTR));
        okBtn->setText(QApplication::translate("ChangeAmount", "&OK", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        okBtn->setShortcut(QApplication::translate("ChangeAmount", "Alt+O", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        cancelBtn->setText(QApplication::translate("ChangeAmount", "&Cancel", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        cancelBtn->setShortcut(QApplication::translate("ChangeAmount", "Alt+C", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        textLabel1->setText(QApplication::translate("ChangeAmount", "Nazwa towaru:", Q_NULLPTR));
        textLabel1_2->setText(QApplication::translate("ChangeAmount", "Kod:", Q_NULLPTR));
        textLabel2->setText(QApplication::translate("ChangeAmount", "Ilo\305\233\304\207:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ChangeAmount: public Ui_ChangeAmount {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANGEAMOUNT_H
