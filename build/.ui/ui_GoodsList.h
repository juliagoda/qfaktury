/********************************************************************************
** Form generated from reading UI file 'GoodsList.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GOODSLIST_H
#define UI_GOODSLIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_GoodsList
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *_12;
    QLabel *textLabel1;
    QComboBox *comboBox1;
    QListWidget *listWidget;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *_14;
    QLabel *textLabel1_6;
    QLabel *textLabel4_2;
    QLabel *textLabel1_7;
    QLabel *textLabel1_8;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *nameEdit;
    QHBoxLayout *horizontalLayout;
    QSpinBox *spinBox2;
    QDoubleSpinBox *priceBoxEdit;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QDoubleSpinBox *countSpinBox;
    QSpinBox *discountSpin;
    QHBoxLayout *_19;
    QVBoxLayout *_20;
    QLabel *textLabel3_3;
    QLabel *textLabel3_4;
    QVBoxLayout *_21;
    QLabel *netLabel;
    QLabel *grossLabel;
    QFrame *line;
    QHBoxLayout *_22;
    QSpacerItem *spacer3;
    QPushButton *okBtn;
    QSpacerItem *spacer1;
    QPushButton *cancelBtn;
    QSpacerItem *spacer2;

    void setupUi(QDialog *GoodsList)
    {
        if (GoodsList->objectName().isEmpty())
            GoodsList->setObjectName(QStringLiteral("GoodsList"));
        GoodsList->resize(324, 315);
        gridLayout = new QGridLayout(GoodsList);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        _12 = new QHBoxLayout();
        _12->setSpacing(6);
        _12->setObjectName(QStringLiteral("_12"));
        textLabel1 = new QLabel(GoodsList);
        textLabel1->setObjectName(QStringLiteral("textLabel1"));
        textLabel1->setMaximumSize(QSize(50, 32767));
        textLabel1->setWordWrap(false);

        _12->addWidget(textLabel1);

        comboBox1 = new QComboBox(GoodsList);
        comboBox1->setObjectName(QStringLiteral("comboBox1"));

        _12->addWidget(comboBox1);


        gridLayout->addLayout(_12, 0, 0, 1, 1);

        listWidget = new QListWidget(GoodsList);
        listWidget->setObjectName(QStringLiteral("listWidget"));

        gridLayout->addWidget(listWidget, 1, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        _14 = new QVBoxLayout();
        _14->setSpacing(6);
        _14->setObjectName(QStringLiteral("_14"));
        textLabel1_6 = new QLabel(GoodsList);
        textLabel1_6->setObjectName(QStringLiteral("textLabel1_6"));
        textLabel1_6->setWordWrap(false);

        _14->addWidget(textLabel1_6);

        textLabel4_2 = new QLabel(GoodsList);
        textLabel4_2->setObjectName(QStringLiteral("textLabel4_2"));
        textLabel4_2->setWordWrap(false);

        _14->addWidget(textLabel4_2);

        textLabel1_7 = new QLabel(GoodsList);
        textLabel1_7->setObjectName(QStringLiteral("textLabel1_7"));
        textLabel1_7->setWordWrap(false);

        _14->addWidget(textLabel1_7);

        textLabel1_8 = new QLabel(GoodsList);
        textLabel1_8->setObjectName(QStringLiteral("textLabel1_8"));
        textLabel1_8->setWordWrap(false);

        _14->addWidget(textLabel1_8);


        horizontalLayout_3->addLayout(_14);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        nameEdit = new QLineEdit(GoodsList);
        nameEdit->setObjectName(QStringLiteral("nameEdit"));
        nameEdit->setEnabled(true);
        nameEdit->setFocusPolicy(Qt::StrongFocus);
        nameEdit->setStyleSheet(QStringLiteral(""));
        nameEdit->setReadOnly(false);

        verticalLayout_2->addWidget(nameEdit);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        spinBox2 = new QSpinBox(GoodsList);
        spinBox2->setObjectName(QStringLiteral("spinBox2"));
        spinBox2->setMaximumSize(QSize(55, 16777215));
        spinBox2->setFocusPolicy(Qt::NoFocus);
        spinBox2->setMinimum(1);
        spinBox2->setMaximum(4);

        horizontalLayout->addWidget(spinBox2);

        priceBoxEdit = new QDoubleSpinBox(GoodsList);
        priceBoxEdit->setObjectName(QStringLiteral("priceBoxEdit"));
        priceBoxEdit->setCursor(QCursor(Qt::IBeamCursor));
        priceBoxEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        priceBoxEdit->setButtonSymbols(QAbstractSpinBox::NoButtons);
        priceBoxEdit->setMaximum(100000);

        horizontalLayout->addWidget(priceBoxEdit);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        countSpinBox = new QDoubleSpinBox(GoodsList);
        countSpinBox->setObjectName(QStringLiteral("countSpinBox"));
        countSpinBox->setCursor(QCursor(Qt::IBeamCursor));
        countSpinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        countSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        countSpinBox->setDecimals(3);
        countSpinBox->setMaximum(9999.99);

        verticalLayout->addWidget(countSpinBox);

        discountSpin = new QSpinBox(GoodsList);
        discountSpin->setObjectName(QStringLiteral("discountSpin"));

        verticalLayout->addWidget(discountSpin);


        horizontalLayout_2->addLayout(verticalLayout);

        _19 = new QHBoxLayout();
        _19->setSpacing(6);
        _19->setObjectName(QStringLiteral("_19"));
        _20 = new QVBoxLayout();
        _20->setSpacing(6);
        _20->setObjectName(QStringLiteral("_20"));
        textLabel3_3 = new QLabel(GoodsList);
        textLabel3_3->setObjectName(QStringLiteral("textLabel3_3"));
        textLabel3_3->setWordWrap(false);

        _20->addWidget(textLabel3_3);

        textLabel3_4 = new QLabel(GoodsList);
        textLabel3_4->setObjectName(QStringLiteral("textLabel3_4"));
        textLabel3_4->setWordWrap(false);

        _20->addWidget(textLabel3_4);


        _19->addLayout(_20);

        _21 = new QVBoxLayout();
        _21->setSpacing(6);
        _21->setObjectName(QStringLiteral("_21"));
        netLabel = new QLabel(GoodsList);
        netLabel->setObjectName(QStringLiteral("netLabel"));
        netLabel->setMinimumSize(QSize(80, 0));
        netLabel->setWordWrap(false);

        _21->addWidget(netLabel);

        grossLabel = new QLabel(GoodsList);
        grossLabel->setObjectName(QStringLiteral("grossLabel"));
        grossLabel->setMinimumSize(QSize(80, 0));
        grossLabel->setWordWrap(false);

        _21->addWidget(grossLabel);


        _19->addLayout(_21);


        horizontalLayout_2->addLayout(_19);


        verticalLayout_2->addLayout(horizontalLayout_2);


        horizontalLayout_3->addLayout(verticalLayout_2);


        gridLayout->addLayout(horizontalLayout_3, 2, 0, 1, 1);

        line = new QFrame(GoodsList);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 3, 0, 1, 1);

        _22 = new QHBoxLayout();
        _22->setSpacing(6);
        _22->setObjectName(QStringLiteral("_22"));
        spacer3 = new QSpacerItem(43, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        _22->addItem(spacer3);

        okBtn = new QPushButton(GoodsList);
        okBtn->setObjectName(QStringLiteral("okBtn"));
        okBtn->setCursor(QCursor(Qt::PointingHandCursor));

        _22->addWidget(okBtn);

        spacer1 = new QSpacerItem(43, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        _22->addItem(spacer1);

        cancelBtn = new QPushButton(GoodsList);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));
        cancelBtn->setCursor(QCursor(Qt::PointingHandCursor));

        _22->addWidget(cancelBtn);

        spacer2 = new QSpacerItem(43, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        _22->addItem(spacer2);


        gridLayout->addLayout(_22, 4, 0, 1, 1);

        QWidget::setTabOrder(listWidget, priceBoxEdit);
        QWidget::setTabOrder(priceBoxEdit, countSpinBox);
        QWidget::setTabOrder(countSpinBox, discountSpin);
        QWidget::setTabOrder(discountSpin, okBtn);
        QWidget::setTabOrder(okBtn, cancelBtn);
        QWidget::setTabOrder(cancelBtn, comboBox1);

        retranslateUi(GoodsList);

        QMetaObject::connectSlotsByName(GoodsList);
    } // setupUi

    void retranslateUi(QDialog *GoodsList)
    {
        GoodsList->setWindowTitle(QApplication::translate("GoodsList", "Wybierz towar z listy", Q_NULLPTR));
        textLabel1->setText(QApplication::translate("GoodsList", "Typ:", Q_NULLPTR));
        comboBox1->clear();
        comboBox1->insertItems(0, QStringList()
         << QApplication::translate("GoodsList", "Towar", Q_NULLPTR)
         << QApplication::translate("GoodsList", "Us\305\202uga", Q_NULLPTR)
        );
        textLabel1_6->setText(QApplication::translate("GoodsList", "Nazwa*:", Q_NULLPTR));
        textLabel4_2->setText(QApplication::translate("GoodsList", "Cena:", Q_NULLPTR));
        textLabel1_7->setText(QApplication::translate("GoodsList", "Ilo\305\233\304\207*:", Q_NULLPTR));
        textLabel1_8->setText(QApplication::translate("GoodsList", "Rabat:", Q_NULLPTR));
        textLabel3_3->setText(QApplication::translate("GoodsList", "Netto:", Q_NULLPTR));
        textLabel3_4->setText(QApplication::translate("GoodsList", "Brutto:", Q_NULLPTR));
        netLabel->setText(QApplication::translate("GoodsList", "0,00", Q_NULLPTR));
        grossLabel->setText(QApplication::translate("GoodsList", "0,00", Q_NULLPTR));
        okBtn->setText(QApplication::translate("GoodsList", "O&K", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        okBtn->setShortcut(QApplication::translate("GoodsList", "Alt+K", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        cancelBtn->setText(QApplication::translate("GoodsList", "&Anuluj", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        cancelBtn->setShortcut(QApplication::translate("GoodsList", "Alt+C", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
    } // retranslateUi

};

namespace Ui {
    class GoodsList: public Ui_GoodsList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GOODSLIST_H
