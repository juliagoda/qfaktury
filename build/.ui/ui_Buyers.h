/********************************************************************************
** Form generated from reading UI file 'Buyers.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUYERS_H
#define UI_BUYERS_H

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
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Buyers
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *hboxLayout;
    QVBoxLayout *vboxLayout;
    QLabel *textLabel1;
    QLabel *textLabel3;
    QLabel *textLabel4;
    QLabel *textLabel2;
    QLabel *textLabel2_2;
    QLabel *textLabel5;
    QLabel *textLabel6;
    QVBoxLayout *vboxLayout1;
    QLineEdit *nameEdit;
    QLineEdit *placeEdit;
    QLineEdit *codeEdit;
    QLineEdit *addressEdit;
    QLineEdit *nipEdit;
    QLineEdit *accountEdit;
    QComboBox *typeCombo;
    QHBoxLayout *hboxLayout1;
    QVBoxLayout *vboxLayout2;
    QLabel *textLabel5_2;
    QLabel *textLabel5_2_2;
    QLabel *textLabel5_2_2_2;
    QVBoxLayout *vboxLayout3;
    QLineEdit *telefonEdit;
    QLineEdit *emailEdit;
    QLineEdit *wwwEdit;
    QFrame *frame;
    QGridLayout *gridLayout;
    QHBoxLayout *hboxLayout2;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *Buyers)
    {
        if (Buyers->objectName().isEmpty())
            Buyers->setObjectName(QStringLiteral("Buyers"));
        Buyers->resize(447, 422);
        verticalLayout = new QVBoxLayout(Buyers);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
        vboxLayout = new QVBoxLayout();
        vboxLayout->setSpacing(6);
        vboxLayout->setObjectName(QStringLiteral("vboxLayout"));
        textLabel1 = new QLabel(Buyers);
        textLabel1->setObjectName(QStringLiteral("textLabel1"));
        textLabel1->setWordWrap(false);

        vboxLayout->addWidget(textLabel1);

        textLabel3 = new QLabel(Buyers);
        textLabel3->setObjectName(QStringLiteral("textLabel3"));
        textLabel3->setWordWrap(false);

        vboxLayout->addWidget(textLabel3);

        textLabel4 = new QLabel(Buyers);
        textLabel4->setObjectName(QStringLiteral("textLabel4"));
        textLabel4->setWordWrap(false);

        vboxLayout->addWidget(textLabel4);

        textLabel2 = new QLabel(Buyers);
        textLabel2->setObjectName(QStringLiteral("textLabel2"));
        textLabel2->setWordWrap(false);

        vboxLayout->addWidget(textLabel2);

        textLabel2_2 = new QLabel(Buyers);
        textLabel2_2->setObjectName(QStringLiteral("textLabel2_2"));
        textLabel2_2->setWordWrap(false);

        vboxLayout->addWidget(textLabel2_2);

        textLabel5 = new QLabel(Buyers);
        textLabel5->setObjectName(QStringLiteral("textLabel5"));
        textLabel5->setWordWrap(false);

        vboxLayout->addWidget(textLabel5);

        textLabel6 = new QLabel(Buyers);
        textLabel6->setObjectName(QStringLiteral("textLabel6"));
        textLabel6->setWordWrap(false);

        vboxLayout->addWidget(textLabel6);


        hboxLayout->addLayout(vboxLayout);

        vboxLayout1 = new QVBoxLayout();
        vboxLayout1->setSpacing(6);
        vboxLayout1->setObjectName(QStringLiteral("vboxLayout1"));
        nameEdit = new QLineEdit(Buyers);
        nameEdit->setObjectName(QStringLiteral("nameEdit"));

        vboxLayout1->addWidget(nameEdit);

        placeEdit = new QLineEdit(Buyers);
        placeEdit->setObjectName(QStringLiteral("placeEdit"));

        vboxLayout1->addWidget(placeEdit);

        codeEdit = new QLineEdit(Buyers);
        codeEdit->setObjectName(QStringLiteral("codeEdit"));

        vboxLayout1->addWidget(codeEdit);

        addressEdit = new QLineEdit(Buyers);
        addressEdit->setObjectName(QStringLiteral("addressEdit"));

        vboxLayout1->addWidget(addressEdit);

        nipEdit = new QLineEdit(Buyers);
        nipEdit->setObjectName(QStringLiteral("nipEdit"));
        nipEdit->setMaxLength(13);

        vboxLayout1->addWidget(nipEdit);

        accountEdit = new QLineEdit(Buyers);
        accountEdit->setObjectName(QStringLiteral("accountEdit"));

        vboxLayout1->addWidget(accountEdit);

        typeCombo = new QComboBox(Buyers);
        typeCombo->setObjectName(QStringLiteral("typeCombo"));

        vboxLayout1->addWidget(typeCombo);


        hboxLayout->addLayout(vboxLayout1);


        verticalLayout->addLayout(hboxLayout);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setObjectName(QStringLiteral("hboxLayout1"));
        vboxLayout2 = new QVBoxLayout();
        vboxLayout2->setSpacing(6);
        vboxLayout2->setObjectName(QStringLiteral("vboxLayout2"));
        textLabel5_2 = new QLabel(Buyers);
        textLabel5_2->setObjectName(QStringLiteral("textLabel5_2"));
        textLabel5_2->setWordWrap(false);

        vboxLayout2->addWidget(textLabel5_2);

        textLabel5_2_2 = new QLabel(Buyers);
        textLabel5_2_2->setObjectName(QStringLiteral("textLabel5_2_2"));
        textLabel5_2_2->setWordWrap(false);

        vboxLayout2->addWidget(textLabel5_2_2);

        textLabel5_2_2_2 = new QLabel(Buyers);
        textLabel5_2_2_2->setObjectName(QStringLiteral("textLabel5_2_2_2"));
        textLabel5_2_2_2->setWordWrap(false);

        vboxLayout2->addWidget(textLabel5_2_2_2);


        hboxLayout1->addLayout(vboxLayout2);

        vboxLayout3 = new QVBoxLayout();
        vboxLayout3->setSpacing(6);
        vboxLayout3->setObjectName(QStringLiteral("vboxLayout3"));
        telefonEdit = new QLineEdit(Buyers);
        telefonEdit->setObjectName(QStringLiteral("telefonEdit"));

        vboxLayout3->addWidget(telefonEdit);

        emailEdit = new QLineEdit(Buyers);
        emailEdit->setObjectName(QStringLiteral("emailEdit"));

        vboxLayout3->addWidget(emailEdit);

        wwwEdit = new QLineEdit(Buyers);
        wwwEdit->setObjectName(QStringLiteral("wwwEdit"));

        vboxLayout3->addWidget(wwwEdit);


        hboxLayout1->addLayout(vboxLayout3);


        verticalLayout->addLayout(hboxLayout1);

        frame = new QFrame(Buyers);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setMaximumSize(QSize(16777215, 10));
        frame->setFrameShape(QFrame::HLine);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));

        verticalLayout->addWidget(frame);

        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setSpacing(6);
        hboxLayout2->setObjectName(QStringLiteral("hboxLayout2"));
        spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout2->addItem(spacerItem);

        okButton = new QPushButton(Buyers);
        okButton->setObjectName(QStringLiteral("okButton"));

        hboxLayout2->addWidget(okButton);

        cancelButton = new QPushButton(Buyers);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        hboxLayout2->addWidget(cancelButton);


        verticalLayout->addLayout(hboxLayout2);


        retranslateUi(Buyers);
        QObject::connect(cancelButton, SIGNAL(clicked()), Buyers, SLOT(close()));

        QMetaObject::connectSlotsByName(Buyers);
    } // setupUi

    void retranslateUi(QDialog *Buyers)
    {
        Buyers->setWindowTitle(QApplication::translate("Buyers", "Dodaj kontrahenta", Q_NULLPTR));
        textLabel1->setText(QApplication::translate("Buyers", "Nazwa*:", Q_NULLPTR));
        textLabel3->setText(QApplication::translate("Buyers", "Miejscowo\305\233\304\207*:", Q_NULLPTR));
        textLabel4->setText(QApplication::translate("Buyers", "Kod*:", Q_NULLPTR));
        textLabel2->setText(QApplication::translate("Buyers", "Adres*:", Q_NULLPTR));
        textLabel2_2->setText(QApplication::translate("Buyers", "NIP*:", Q_NULLPTR));
        textLabel5->setText(QApplication::translate("Buyers", "Nr konta:", Q_NULLPTR));
        textLabel6->setText(QApplication::translate("Buyers", "Typ*:", Q_NULLPTR));
        nipEdit->setInputMask(QString());
        nipEdit->setText(QString());
        accountEdit->setInputMask(QString());
        typeCombo->clear();
        typeCombo->insertItems(0, QStringList()
         << QApplication::translate("Buyers", "Firma", Q_NULLPTR)
         << QApplication::translate("Buyers", "Urz\304\205d", Q_NULLPTR)
         << QApplication::translate("Buyers", "Osoba fizyczna", Q_NULLPTR)
        );
        textLabel5_2->setText(QApplication::translate("Buyers", "Telefon:", Q_NULLPTR));
        textLabel5_2_2->setText(QApplication::translate("Buyers", "e-mail", Q_NULLPTR));
        textLabel5_2_2_2->setText(QApplication::translate("Buyers", "www:", Q_NULLPTR));
        okButton->setText(QApplication::translate("Buyers", "O&K", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        okButton->setShortcut(QApplication::translate("Buyers", "Alt+K", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        cancelButton->setText(QApplication::translate("Buyers", "Can&cel", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        cancelButton->setShortcut(QApplication::translate("Buyers", "Alt+C", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
    } // retranslateUi

};

namespace Ui {
    class Buyers: public Ui_Buyers {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUYERS_H
