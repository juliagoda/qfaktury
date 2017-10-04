/********************************************************************************
** Form generated from reading UI file 'BuyersList.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUYERSLIST_H
#define UI_BUYERSLIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BuyersList
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *headarLayout;
    QLabel *textLabel1;
    QComboBox *comboBox1;
    QSplitter *splitter;
    QListWidget *listBox1;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *labelName;
    QLabel *labelNameE;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelAddress;
    QLabel *labelAddressE;
    QHBoxLayout *horizontalLayout_3;
    QLabel *labelCity;
    QLabel *labelCityE;
    QHBoxLayout *horizontalLayout_4;
    QLabel *labelTic;
    QLabel *labelTicE;
    QHBoxLayout *horizontalLayout_5;
    QLabel *labelAccount;
    QLabel *labelAccountE;
    QHBoxLayout *horizontalLayout_6;
    QLabel *labelPhone;
    QLabel *labelPhoneE;
    QHBoxLayout *horizontalLayout_7;
    QLabel *labelEmail;
    QLabel *labelEmailE;
    QHBoxLayout *horizontalLayout_8;
    QLabel *labelWWW;
    QLabel *labelWWWE;
    QFrame *line4;
    QHBoxLayout *buttonLayout;
    QSpacerItem *spacerRight;
    QPushButton *okBtn;
    QSpacerItem *spacerMiddle;
    QPushButton *cancelBtn;
    QSpacerItem *spacerLeft;

    void setupUi(QDialog *BuyersList)
    {
        if (BuyersList->objectName().isEmpty())
            BuyersList->setObjectName(QStringLiteral("BuyersList"));
        BuyersList->resize(397, 335);
        gridLayout = new QGridLayout(BuyersList);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        headarLayout = new QHBoxLayout();
        headarLayout->setSpacing(6);
        headarLayout->setObjectName(QStringLiteral("headarLayout"));
        textLabel1 = new QLabel(BuyersList);
        textLabel1->setObjectName(QStringLiteral("textLabel1"));
        textLabel1->setMaximumSize(QSize(50, 32767));
        textLabel1->setWordWrap(false);

        headarLayout->addWidget(textLabel1);

        comboBox1 = new QComboBox(BuyersList);
        comboBox1->setObjectName(QStringLiteral("comboBox1"));

        headarLayout->addWidget(comboBox1);


        verticalLayout_2->addLayout(headarLayout);

        splitter = new QSplitter(BuyersList);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        listBox1 = new QListWidget(splitter);
        listBox1->setObjectName(QStringLiteral("listBox1"));
        listBox1->setMaximumSize(QSize(200, 16777215));
        listBox1->setFocusPolicy(Qt::TabFocus);
        listBox1->setSelectionBehavior(QAbstractItemView::SelectItems);
        listBox1->setSortingEnabled(true);
        splitter->addWidget(listBox1);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        labelName = new QLabel(layoutWidget);
        labelName->setObjectName(QStringLiteral("labelName"));
        labelName->setMinimumSize(QSize(80, 0));
        labelName->setMaximumSize(QSize(80, 16777215));

        horizontalLayout->addWidget(labelName);

        labelNameE = new QLabel(layoutWidget);
        labelNameE->setObjectName(QStringLiteral("labelNameE"));
        labelNameE->setMinimumSize(QSize(200, 0));

        horizontalLayout->addWidget(labelNameE);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        labelAddress = new QLabel(layoutWidget);
        labelAddress->setObjectName(QStringLiteral("labelAddress"));
        labelAddress->setMinimumSize(QSize(80, 0));
        labelAddress->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_2->addWidget(labelAddress);

        labelAddressE = new QLabel(layoutWidget);
        labelAddressE->setObjectName(QStringLiteral("labelAddressE"));
        labelAddressE->setMinimumSize(QSize(200, 0));

        horizontalLayout_2->addWidget(labelAddressE);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        labelCity = new QLabel(layoutWidget);
        labelCity->setObjectName(QStringLiteral("labelCity"));
        labelCity->setMinimumSize(QSize(80, 0));
        labelCity->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_3->addWidget(labelCity);

        labelCityE = new QLabel(layoutWidget);
        labelCityE->setObjectName(QStringLiteral("labelCityE"));
        labelCityE->setMinimumSize(QSize(200, 0));

        horizontalLayout_3->addWidget(labelCityE);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        labelTic = new QLabel(layoutWidget);
        labelTic->setObjectName(QStringLiteral("labelTic"));
        labelTic->setMinimumSize(QSize(80, 0));
        labelTic->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_4->addWidget(labelTic);

        labelTicE = new QLabel(layoutWidget);
        labelTicE->setObjectName(QStringLiteral("labelTicE"));
        labelTicE->setMinimumSize(QSize(200, 0));

        horizontalLayout_4->addWidget(labelTicE);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        labelAccount = new QLabel(layoutWidget);
        labelAccount->setObjectName(QStringLiteral("labelAccount"));
        labelAccount->setMinimumSize(QSize(80, 0));
        labelAccount->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_5->addWidget(labelAccount);

        labelAccountE = new QLabel(layoutWidget);
        labelAccountE->setObjectName(QStringLiteral("labelAccountE"));
        labelAccountE->setMinimumSize(QSize(200, 0));

        horizontalLayout_5->addWidget(labelAccountE);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        labelPhone = new QLabel(layoutWidget);
        labelPhone->setObjectName(QStringLiteral("labelPhone"));
        labelPhone->setMinimumSize(QSize(80, 0));
        labelPhone->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_6->addWidget(labelPhone);

        labelPhoneE = new QLabel(layoutWidget);
        labelPhoneE->setObjectName(QStringLiteral("labelPhoneE"));
        labelPhoneE->setMinimumSize(QSize(200, 0));

        horizontalLayout_6->addWidget(labelPhoneE);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        labelEmail = new QLabel(layoutWidget);
        labelEmail->setObjectName(QStringLiteral("labelEmail"));
        labelEmail->setMinimumSize(QSize(80, 0));
        labelEmail->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_7->addWidget(labelEmail);

        labelEmailE = new QLabel(layoutWidget);
        labelEmailE->setObjectName(QStringLiteral("labelEmailE"));
        labelEmailE->setMinimumSize(QSize(200, 0));

        horizontalLayout_7->addWidget(labelEmailE);


        verticalLayout->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        labelWWW = new QLabel(layoutWidget);
        labelWWW->setObjectName(QStringLiteral("labelWWW"));
        labelWWW->setMinimumSize(QSize(80, 0));
        labelWWW->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_8->addWidget(labelWWW);

        labelWWWE = new QLabel(layoutWidget);
        labelWWWE->setObjectName(QStringLiteral("labelWWWE"));
        labelWWWE->setCursor(QCursor(Qt::PointingHandCursor));
        labelWWWE->setTextFormat(Qt::RichText);
        labelWWWE->setOpenExternalLinks(true);
        labelWWWE->setTextInteractionFlags(Qt::TextBrowserInteraction);

        horizontalLayout_8->addWidget(labelWWWE);


        verticalLayout->addLayout(horizontalLayout_8);

        splitter->addWidget(layoutWidget);

        verticalLayout_2->addWidget(splitter);

        line4 = new QFrame(BuyersList);
        line4->setObjectName(QStringLiteral("line4"));
        line4->setFrameShape(QFrame::HLine);
        line4->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line4);

        buttonLayout = new QHBoxLayout();
        buttonLayout->setSpacing(6);
        buttonLayout->setObjectName(QStringLiteral("buttonLayout"));
        spacerRight = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        buttonLayout->addItem(spacerRight);

        okBtn = new QPushButton(BuyersList);
        okBtn->setObjectName(QStringLiteral("okBtn"));
        okBtn->setCursor(QCursor(Qt::PointingHandCursor));

        buttonLayout->addWidget(okBtn);

        spacerMiddle = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        buttonLayout->addItem(spacerMiddle);

        cancelBtn = new QPushButton(BuyersList);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));
        cancelBtn->setCursor(QCursor(Qt::PointingHandCursor));

        buttonLayout->addWidget(cancelBtn);

        spacerLeft = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        buttonLayout->addItem(spacerLeft);


        verticalLayout_2->addLayout(buttonLayout);


        gridLayout->addLayout(verticalLayout_2, 0, 0, 1, 1);

        QWidget::setTabOrder(listBox1, okBtn);
        QWidget::setTabOrder(okBtn, cancelBtn);
        QWidget::setTabOrder(cancelBtn, comboBox1);

        retranslateUi(BuyersList);

        listBox1->setCurrentRow(-1);


        QMetaObject::connectSlotsByName(BuyersList);
    } // setupUi

    void retranslateUi(QDialog *BuyersList)
    {
        BuyersList->setWindowTitle(QApplication::translate("BuyersList", "Wybierz kontrahenta z listy", Q_NULLPTR));
        textLabel1->setText(QApplication::translate("BuyersList", "Typ:", Q_NULLPTR));
        comboBox1->clear();
        comboBox1->insertItems(0, QStringList()
         << QApplication::translate("BuyersList", "Firma", Q_NULLPTR)
         << QApplication::translate("BuyersList", "Urz\304\205d", Q_NULLPTR)
         << QApplication::translate("BuyersList", "Osoba fizyczna", Q_NULLPTR)
        );
        labelName->setText(QApplication::translate("BuyersList", "Nazwa:", Q_NULLPTR));
        labelNameE->setText(QString());
        labelAddress->setText(QApplication::translate("BuyersList", "Adress:", Q_NULLPTR));
        labelAddressE->setText(QString());
        labelCity->setText(QApplication::translate("BuyersList", "Miejscowo\305\233\304\207:", Q_NULLPTR));
        labelCityE->setText(QString());
        labelTic->setText(QApplication::translate("BuyersList", "NIP:", Q_NULLPTR));
        labelTicE->setText(QString());
        labelAccount->setText(QApplication::translate("BuyersList", "Nr konta:", Q_NULLPTR));
        labelAccountE->setText(QString());
        labelPhone->setText(QApplication::translate("BuyersList", "Telefon:", Q_NULLPTR));
        labelPhoneE->setText(QString());
        labelEmail->setText(QApplication::translate("BuyersList", "E-mail:", Q_NULLPTR));
        labelEmailE->setText(QString());
        labelWWW->setText(QApplication::translate("BuyersList", "WWW:", Q_NULLPTR));
        labelWWWE->setText(QString());
        okBtn->setText(QApplication::translate("BuyersList", "O&K", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        okBtn->setShortcut(QApplication::translate("BuyersList", "Alt+K", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        cancelBtn->setText(QApplication::translate("BuyersList", "&Anuluj", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        cancelBtn->setShortcut(QApplication::translate("BuyersList", "Alt+C", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
    } // retranslateUi

};

namespace Ui {
    class BuyersList: public Ui_BuyersList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUYERSLIST_H
