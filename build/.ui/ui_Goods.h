/********************************************************************************
** Form generated from reading UI file 'Goods.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GOODS_H
#define UI_GOODS_H

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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Goods
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *hboxLayout;
    QVBoxLayout *vboxLayout;
    QLabel *textLabel1;
    QLabel *textLabel3;
    QLabel *textLabel4;
    QLabel *textLabel1_2;
    QVBoxLayout *vboxLayout1;
    QLineEdit *idxEdit;
    QLineEdit *nameEdit;
    QLineEdit *shortcutEdit;
    QLineEdit *codeEdit;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *vboxLayout2;
    QLabel *textLabel1_2_2;
    QLabel *textLabel2;
    QLabel *textLabel5;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *hboxLayout1;
    QLineEdit *pkwiuEdit;
    QToolButton *pkwiuBtn;
    QHBoxLayout *hboxLayout2;
    QComboBox *typeCombo;
    QHBoxLayout *hboxLayout3;
    QLabel *textLabel2_2;
    QComboBox *jednCombo;
    QHBoxLayout *horizontalLayout;
    QSpinBox *spinBox2;
    QDoubleSpinBox *netEdit;
    QHBoxLayout *hboxLayout4;
    QLabel *textLabel6;
    QComboBox *cbVat;
    QFrame *line3;
    QHBoxLayout *hboxLayout5;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *Goods)
    {
        if (Goods->objectName().isEmpty())
            Goods->setObjectName(QStringLiteral("Goods"));
        Goods->resize(379, 319);
        Goods->setContextMenuPolicy(Qt::DefaultContextMenu);
        gridLayout = new QGridLayout(Goods);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
        vboxLayout = new QVBoxLayout();
        vboxLayout->setSpacing(6);
        vboxLayout->setObjectName(QStringLiteral("vboxLayout"));
        textLabel1 = new QLabel(Goods);
        textLabel1->setObjectName(QStringLiteral("textLabel1"));
        textLabel1->setWordWrap(false);

        vboxLayout->addWidget(textLabel1);

        textLabel3 = new QLabel(Goods);
        textLabel3->setObjectName(QStringLiteral("textLabel3"));
        textLabel3->setWordWrap(false);

        vboxLayout->addWidget(textLabel3);

        textLabel4 = new QLabel(Goods);
        textLabel4->setObjectName(QStringLiteral("textLabel4"));
        textLabel4->setWordWrap(false);

        vboxLayout->addWidget(textLabel4);

        textLabel1_2 = new QLabel(Goods);
        textLabel1_2->setObjectName(QStringLiteral("textLabel1_2"));
        textLabel1_2->setWordWrap(false);

        vboxLayout->addWidget(textLabel1_2);


        hboxLayout->addLayout(vboxLayout);

        vboxLayout1 = new QVBoxLayout();
        vboxLayout1->setSpacing(6);
        vboxLayout1->setObjectName(QStringLiteral("vboxLayout1"));
        idxEdit = new QLineEdit(Goods);
        idxEdit->setObjectName(QStringLiteral("idxEdit"));
        idxEdit->setEnabled(false);
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        idxEdit->setFont(font);
        idxEdit->setReadOnly(true);

        vboxLayout1->addWidget(idxEdit);

        nameEdit = new QLineEdit(Goods);
        nameEdit->setObjectName(QStringLiteral("nameEdit"));
        nameEdit->setMaxLength(75);

        vboxLayout1->addWidget(nameEdit);

        shortcutEdit = new QLineEdit(Goods);
        shortcutEdit->setObjectName(QStringLiteral("shortcutEdit"));
        shortcutEdit->setMaxLength(25);

        vboxLayout1->addWidget(shortcutEdit);

        codeEdit = new QLineEdit(Goods);
        codeEdit->setObjectName(QStringLiteral("codeEdit"));
        codeEdit->setMaxLength(20);

        vboxLayout1->addWidget(codeEdit);


        hboxLayout->addLayout(vboxLayout1);


        gridLayout->addLayout(hboxLayout, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        vboxLayout2 = new QVBoxLayout();
        vboxLayout2->setSpacing(6);
        vboxLayout2->setObjectName(QStringLiteral("vboxLayout2"));
        textLabel1_2_2 = new QLabel(Goods);
        textLabel1_2_2->setObjectName(QStringLiteral("textLabel1_2_2"));
        textLabel1_2_2->setWordWrap(false);

        vboxLayout2->addWidget(textLabel1_2_2);

        textLabel2 = new QLabel(Goods);
        textLabel2->setObjectName(QStringLiteral("textLabel2"));
        textLabel2->setWordWrap(false);

        vboxLayout2->addWidget(textLabel2);

        textLabel5 = new QLabel(Goods);
        textLabel5->setObjectName(QStringLiteral("textLabel5"));
        textLabel5->setWordWrap(false);

        vboxLayout2->addWidget(textLabel5);


        horizontalLayout_2->addLayout(vboxLayout2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setObjectName(QStringLiteral("hboxLayout1"));
        pkwiuEdit = new QLineEdit(Goods);
        pkwiuEdit->setObjectName(QStringLiteral("pkwiuEdit"));
        pkwiuEdit->setMaxLength(20);

        hboxLayout1->addWidget(pkwiuEdit);

        pkwiuBtn = new QToolButton(Goods);
        pkwiuBtn->setObjectName(QStringLiteral("pkwiuBtn"));
        pkwiuBtn->setCursor(QCursor(Qt::PointingHandCursor));

        hboxLayout1->addWidget(pkwiuBtn);


        verticalLayout->addLayout(hboxLayout1);

        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setSpacing(6);
        hboxLayout2->setObjectName(QStringLiteral("hboxLayout2"));
        typeCombo = new QComboBox(Goods);
        typeCombo->setObjectName(QStringLiteral("typeCombo"));

        hboxLayout2->addWidget(typeCombo);

        hboxLayout3 = new QHBoxLayout();
        hboxLayout3->setSpacing(6);
        hboxLayout3->setObjectName(QStringLiteral("hboxLayout3"));
        textLabel2_2 = new QLabel(Goods);
        textLabel2_2->setObjectName(QStringLiteral("textLabel2_2"));
        textLabel2_2->setWordWrap(false);

        hboxLayout3->addWidget(textLabel2_2);

        jednCombo = new QComboBox(Goods);
        jednCombo->setObjectName(QStringLiteral("jednCombo"));

        hboxLayout3->addWidget(jednCombo);


        hboxLayout2->addLayout(hboxLayout3);


        verticalLayout->addLayout(hboxLayout2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        spinBox2 = new QSpinBox(Goods);
        spinBox2->setObjectName(QStringLiteral("spinBox2"));
        spinBox2->setMinimumSize(QSize(60, 0));
        spinBox2->setMinimum(1);
        spinBox2->setMaximum(4);

        horizontalLayout->addWidget(spinBox2);

        netEdit = new QDoubleSpinBox(Goods);
        netEdit->setObjectName(QStringLiteral("netEdit"));
        netEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        netEdit->setButtonSymbols(QAbstractSpinBox::NoButtons);
        netEdit->setMaximum(100000);

        horizontalLayout->addWidget(netEdit);

        hboxLayout4 = new QHBoxLayout();
        hboxLayout4->setSpacing(6);
        hboxLayout4->setObjectName(QStringLiteral("hboxLayout4"));
        textLabel6 = new QLabel(Goods);
        textLabel6->setObjectName(QStringLiteral("textLabel6"));
        textLabel6->setWordWrap(false);

        hboxLayout4->addWidget(textLabel6);

        cbVat = new QComboBox(Goods);
        cbVat->setObjectName(QStringLiteral("cbVat"));

        hboxLayout4->addWidget(cbVat);


        horizontalLayout->addLayout(hboxLayout4);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_2->addLayout(verticalLayout);


        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        line3 = new QFrame(Goods);
        line3->setObjectName(QStringLiteral("line3"));
        line3->setFrameShape(QFrame::HLine);
        line3->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line3, 2, 0, 1, 1);

        hboxLayout5 = new QHBoxLayout();
        hboxLayout5->setSpacing(6);
        hboxLayout5->setObjectName(QStringLiteral("hboxLayout5"));
        spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout5->addItem(spacerItem);

        okButton = new QPushButton(Goods);
        okButton->setObjectName(QStringLiteral("okButton"));
        okButton->setCursor(QCursor(Qt::PointingHandCursor));

        hboxLayout5->addWidget(okButton);

        cancelButton = new QPushButton(Goods);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));
        cancelButton->setCursor(QCursor(Qt::PointingHandCursor));

        hboxLayout5->addWidget(cancelButton);


        gridLayout->addLayout(hboxLayout5, 3, 0, 1, 1);


        retranslateUi(Goods);

        QMetaObject::connectSlotsByName(Goods);
    } // setupUi

    void retranslateUi(QDialog *Goods)
    {
        Goods->setWindowTitle(QApplication::translate("Goods", "Dodaj towar", Q_NULLPTR));
        textLabel1->setText(QApplication::translate("Goods", "Index:", Q_NULLPTR));
        textLabel3->setText(QApplication::translate("Goods", "Nazwa*:", Q_NULLPTR));
        textLabel4->setText(QApplication::translate("Goods", "Skr\303\263t:", Q_NULLPTR));
        textLabel1_2->setText(QApplication::translate("Goods", "Kod:", Q_NULLPTR));
        shortcutEdit->setText(QString());
        textLabel1_2_2->setText(QApplication::translate("Goods", "PKWiU:", Q_NULLPTR));
        textLabel2->setText(QApplication::translate("Goods", "Typ:", Q_NULLPTR));
        textLabel5->setText(QApplication::translate("Goods", "Cena:", Q_NULLPTR));
        pkwiuBtn->setText(QApplication::translate("Goods", "Z&najd\305\272", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        pkwiuBtn->setShortcut(QApplication::translate("Goods", "Alt+N", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        typeCombo->clear();
        typeCombo->insertItems(0, QStringList()
         << QApplication::translate("Goods", "Towar", Q_NULLPTR)
         << QApplication::translate("Goods", "Us\305\202uga", Q_NULLPTR)
        );
        textLabel2_2->setText(QApplication::translate("Goods", "Jedn.:", Q_NULLPTR));
        textLabel6->setText(QApplication::translate("Goods", "Vat:", Q_NULLPTR));
        okButton->setText(QApplication::translate("Goods", "O&K", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        okButton->setShortcut(QApplication::translate("Goods", "Alt+K", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        cancelButton->setText(QApplication::translate("Goods", "Can&cel", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        cancelButton->setShortcut(QApplication::translate("Goods", "Alt+C", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
    } // retranslateUi

};

namespace Ui {
    class Goods: public Ui_Goods {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GOODS_H
