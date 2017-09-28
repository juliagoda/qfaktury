/********************************************************************************
** Form generated from reading UI file 'CustomPaymentDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUSTOMPAYMENTDIALOG_H
#define UI_CUSTOMPAYMENTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_CustomPaymentDialog
{
public:
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *textLabel5;
    QComboBox *paymCombo1;
    QHBoxLayout *horizontalLayout;
    QLabel *textLabel6;
    QDateEdit *liabDate1;
    QHBoxLayout *horizontalLayout_4;
    QLabel *textLabel7;
    QDoubleSpinBox *amount1;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QHBoxLayout *horizontalLayout_6;
    QLabel *textLabel5_2;
    QComboBox *paymCombo2;
    QHBoxLayout *horizontalLayout_7;
    QLabel *textLabel6_2;
    QDateEdit *liabDate2;
    QHBoxLayout *horizontalLayout_8;
    QLabel *textLabel7_2;
    QDoubleSpinBox *amount2;
    QFrame *line;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *CustomPaymentDialog)
    {
        if (CustomPaymentDialog->objectName().isEmpty())
            CustomPaymentDialog->setObjectName(QStringLiteral("CustomPaymentDialog"));
        CustomPaymentDialog->resize(400, 277);
        gridLayout_3 = new QGridLayout(CustomPaymentDialog);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        groupBox = new QGroupBox(CustomPaymentDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        textLabel5 = new QLabel(groupBox);
        textLabel5->setObjectName(QStringLiteral("textLabel5"));
        textLabel5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel5->setWordWrap(false);

        horizontalLayout_2->addWidget(textLabel5);

        paymCombo1 = new QComboBox(groupBox);
        paymCombo1->setObjectName(QStringLiteral("paymCombo1"));
        paymCombo1->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_2->addWidget(paymCombo1);


        horizontalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        textLabel6 = new QLabel(groupBox);
        textLabel6->setObjectName(QStringLiteral("textLabel6"));
        textLabel6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel6->setWordWrap(true);

        horizontalLayout->addWidget(textLabel6);

        liabDate1 = new QDateEdit(groupBox);
        liabDate1->setObjectName(QStringLiteral("liabDate1"));
        liabDate1->setCursor(QCursor(Qt::UpArrowCursor));
        liabDate1->setCalendarPopup(true);

        horizontalLayout->addWidget(liabDate1);


        horizontalLayout_3->addLayout(horizontalLayout);


        gridLayout->addLayout(horizontalLayout_3, 0, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        textLabel7 = new QLabel(groupBox);
        textLabel7->setObjectName(QStringLiteral("textLabel7"));
        textLabel7->setLayoutDirection(Qt::LeftToRight);
        textLabel7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel7->setWordWrap(false);

        horizontalLayout_4->addWidget(textLabel7);

        amount1 = new QDoubleSpinBox(groupBox);
        amount1->setObjectName(QStringLiteral("amount1"));
        amount1->setMaximum(100000);

        horizontalLayout_4->addWidget(amount1);


        gridLayout->addLayout(horizontalLayout_4, 1, 0, 1, 1);


        gridLayout_3->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(CustomPaymentDialog);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        textLabel5_2 = new QLabel(groupBox_2);
        textLabel5_2->setObjectName(QStringLiteral("textLabel5_2"));
        textLabel5_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel5_2->setWordWrap(false);

        horizontalLayout_6->addWidget(textLabel5_2);

        paymCombo2 = new QComboBox(groupBox_2);
        paymCombo2->setObjectName(QStringLiteral("paymCombo2"));
        paymCombo2->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_6->addWidget(paymCombo2);


        horizontalLayout_5->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        textLabel6_2 = new QLabel(groupBox_2);
        textLabel6_2->setObjectName(QStringLiteral("textLabel6_2"));
        textLabel6_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel6_2->setWordWrap(true);

        horizontalLayout_7->addWidget(textLabel6_2);

        liabDate2 = new QDateEdit(groupBox_2);
        liabDate2->setObjectName(QStringLiteral("liabDate2"));
        liabDate2->setCursor(QCursor(Qt::UpArrowCursor));
        liabDate2->setCalendarPopup(true);

        horizontalLayout_7->addWidget(liabDate2);


        horizontalLayout_5->addLayout(horizontalLayout_7);


        gridLayout_2->addLayout(horizontalLayout_5, 0, 0, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        textLabel7_2 = new QLabel(groupBox_2);
        textLabel7_2->setObjectName(QStringLiteral("textLabel7_2"));
        textLabel7_2->setLayoutDirection(Qt::LeftToRight);
        textLabel7_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel7_2->setWordWrap(false);

        horizontalLayout_8->addWidget(textLabel7_2);

        amount2 = new QDoubleSpinBox(groupBox_2);
        amount2->setObjectName(QStringLiteral("amount2"));
        amount2->setMaximum(100000);

        horizontalLayout_8->addWidget(amount2);


        gridLayout_2->addLayout(horizontalLayout_8, 1, 0, 1, 1);


        gridLayout_3->addWidget(groupBox_2, 1, 0, 1, 1);

        line = new QFrame(CustomPaymentDialog);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_3->addWidget(line, 2, 0, 1, 1);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer);

        okButton = new QPushButton(CustomPaymentDialog);
        okButton->setObjectName(QStringLiteral("okButton"));
        okButton->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_9->addWidget(okButton);

        cancelButton = new QPushButton(CustomPaymentDialog);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));
        cancelButton->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_9->addWidget(cancelButton);


        gridLayout_3->addLayout(horizontalLayout_9, 3, 0, 1, 1);

        QWidget::setTabOrder(paymCombo1, liabDate1);
        QWidget::setTabOrder(liabDate1, amount1);
        QWidget::setTabOrder(amount1, paymCombo2);
        QWidget::setTabOrder(paymCombo2, liabDate2);
        QWidget::setTabOrder(liabDate2, amount2);

        retranslateUi(CustomPaymentDialog);

        QMetaObject::connectSlotsByName(CustomPaymentDialog);
    } // setupUi

    void retranslateUi(QDialog *CustomPaymentDialog)
    {
        CustomPaymentDialog->setWindowTitle(QApplication::translate("CustomPaymentDialog", "Zaawansowane p\305\202atno\305\233ci", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("CustomPaymentDialog", "P\305\202atno\305\233\304\207 1:", Q_NULLPTR));
        textLabel5->setText(QApplication::translate("CustomPaymentDialog", "P\305\202atno\305\233\304\207:", Q_NULLPTR));
        textLabel6->setText(QApplication::translate("CustomPaymentDialog", "Termin:", Q_NULLPTR));
        liabDate1->setDisplayFormat(QApplication::translate("CustomPaymentDialog", "dd/MM/yyyy", Q_NULLPTR));
        textLabel7->setText(QApplication::translate("CustomPaymentDialog", "Kwota:", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("CustomPaymentDialog", "P\305\202atno\305\233\304\207 2:", Q_NULLPTR));
        textLabel5_2->setText(QApplication::translate("CustomPaymentDialog", "P\305\202atno\305\233\304\207:", Q_NULLPTR));
        textLabel6_2->setText(QApplication::translate("CustomPaymentDialog", "Termin:", Q_NULLPTR));
        liabDate2->setDisplayFormat(QApplication::translate("CustomPaymentDialog", "dd/MM/yyyy", Q_NULLPTR));
        textLabel7_2->setText(QApplication::translate("CustomPaymentDialog", "Kwota:", Q_NULLPTR));
        okButton->setText(QApplication::translate("CustomPaymentDialog", "&Ok", Q_NULLPTR));
        cancelButton->setText(QApplication::translate("CustomPaymentDialog", "&Anuluj", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CustomPaymentDialog: public Ui_CustomPaymentDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUSTOMPAYMENTDIALOG_H
