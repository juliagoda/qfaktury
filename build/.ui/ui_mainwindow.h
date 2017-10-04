/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EmailWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *server;
    QLabel *label_2;
    QLineEdit *port;
    QLabel *label_3;
    QLineEdit *uname;
    QLabel *label_4;
    QLineEdit *paswd;
    QLabel *label_5;
    QLineEdit *rcpt;
    QLabel *label_6;
    QLineEdit *subject;
    QLabel *label_8;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *file;
    QPushButton *browseBtn;
    QLabel *label_7;
    QPlainTextEdit *msg;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *template1;
    QRadioButton *template2;
    QRadioButton *template3;
    QLabel *label_9;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *sendBtn;
    QSpacerItem *horizontalSpacer_2;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *EmailWindow)
    {
        if (EmailWindow->objectName().isEmpty())
            EmailWindow->setObjectName(QStringLiteral("EmailWindow"));
        EmailWindow->resize(570, 490);
        centralWidget = new QWidget(EmailWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, -83, 536, 526));
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
        formLayout->setRowWrapPolicy(QFormLayout::WrapLongRows);
        formLayout->setVerticalSpacing(9);
        label = new QLabel(scrollAreaWidgetContents);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        server = new QLineEdit(scrollAreaWidgetContents);
        server->setObjectName(QStringLiteral("server"));

        formLayout->setWidget(0, QFormLayout::FieldRole, server);

        label_2 = new QLabel(scrollAreaWidgetContents);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        port = new QLineEdit(scrollAreaWidgetContents);
        port->setObjectName(QStringLiteral("port"));

        formLayout->setWidget(1, QFormLayout::FieldRole, port);

        label_3 = new QLabel(scrollAreaWidgetContents);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        uname = new QLineEdit(scrollAreaWidgetContents);
        uname->setObjectName(QStringLiteral("uname"));

        formLayout->setWidget(2, QFormLayout::FieldRole, uname);

        label_4 = new QLabel(scrollAreaWidgetContents);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

        paswd = new QLineEdit(scrollAreaWidgetContents);
        paswd->setObjectName(QStringLiteral("paswd"));
        paswd->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(3, QFormLayout::FieldRole, paswd);

        label_5 = new QLabel(scrollAreaWidgetContents);
        label_5->setObjectName(QStringLiteral("label_5"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_5);

        rcpt = new QLineEdit(scrollAreaWidgetContents);
        rcpt->setObjectName(QStringLiteral("rcpt"));

        formLayout->setWidget(4, QFormLayout::FieldRole, rcpt);

        label_6 = new QLabel(scrollAreaWidgetContents);
        label_6->setObjectName(QStringLiteral("label_6"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_6);

        subject = new QLineEdit(scrollAreaWidgetContents);
        subject->setObjectName(QStringLiteral("subject"));

        formLayout->setWidget(5, QFormLayout::FieldRole, subject);

        label_8 = new QLabel(scrollAreaWidgetContents);
        label_8->setObjectName(QStringLiteral("label_8"));

        formLayout->setWidget(6, QFormLayout::LabelRole, label_8);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        file = new QLineEdit(scrollAreaWidgetContents);
        file->setObjectName(QStringLiteral("file"));
        file->setReadOnly(true);

        horizontalLayout_3->addWidget(file);

        browseBtn = new QPushButton(scrollAreaWidgetContents);
        browseBtn->setObjectName(QStringLiteral("browseBtn"));

        horizontalLayout_3->addWidget(browseBtn);


        formLayout->setLayout(6, QFormLayout::FieldRole, horizontalLayout_3);

        label_7 = new QLabel(scrollAreaWidgetContents);
        label_7->setObjectName(QStringLiteral("label_7"));

        formLayout->setWidget(8, QFormLayout::LabelRole, label_7);

        msg = new QPlainTextEdit(scrollAreaWidgetContents);
        msg->setObjectName(QStringLiteral("msg"));

        formLayout->setWidget(8, QFormLayout::FieldRole, msg);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(20);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(1, 1, 1, 1);
        template1 = new QRadioButton(scrollAreaWidgetContents);
        template1->setObjectName(QStringLiteral("template1"));

        horizontalLayout_2->addWidget(template1);

        template2 = new QRadioButton(scrollAreaWidgetContents);
        template2->setObjectName(QStringLiteral("template2"));

        horizontalLayout_2->addWidget(template2);

        template3 = new QRadioButton(scrollAreaWidgetContents);
        template3->setObjectName(QStringLiteral("template3"));

        horizontalLayout_2->addWidget(template3);


        formLayout->setLayout(7, QFormLayout::FieldRole, horizontalLayout_2);

        label_9 = new QLabel(scrollAreaWidgetContents);
        label_9->setObjectName(QStringLiteral("label_9"));

        formLayout->setWidget(7, QFormLayout::LabelRole, label_9);


        verticalLayout_2->addLayout(formLayout);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        sendBtn = new QPushButton(centralWidget);
        sendBtn->setObjectName(QStringLiteral("sendBtn"));

        horizontalLayout->addWidget(sendBtn);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        EmailWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(EmailWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        EmailWindow->setStatusBar(statusBar);

        retranslateUi(EmailWindow);

        QMetaObject::connectSlotsByName(EmailWindow);
    } // setupUi

    void retranslateUi(QMainWindow *EmailWindow)
    {
        EmailWindow->setWindowTitle(QApplication::translate("EmailWindow", "SMTP Example", Q_NULLPTR));
        label->setText(QApplication::translate("EmailWindow", "Serwer SMTP:", Q_NULLPTR));
        server->setText(QApplication::translate("EmailWindow", "smtp.gmail.com", Q_NULLPTR));
        label_2->setText(QApplication::translate("EmailWindow", "Port serwera:", Q_NULLPTR));
        port->setText(QApplication::translate("EmailWindow", "465", Q_NULLPTR));
        label_3->setText(QApplication::translate("EmailWindow", "Uzytkownik:", Q_NULLPTR));
        label_4->setText(QApplication::translate("EmailWindow", "Has\305\202o:", Q_NULLPTR));
        paswd->setInputMask(QString());
        label_5->setText(QApplication::translate("EmailWindow", "Wy\305\233lij do:", Q_NULLPTR));
        label_6->setText(QApplication::translate("EmailWindow", "Temat:", Q_NULLPTR));
        label_8->setText(QApplication::translate("EmailWindow", "Za\305\202\304\205cznik:", Q_NULLPTR));
        browseBtn->setText(QApplication::translate("EmailWindow", "Dodaj...", Q_NULLPTR));
        label_7->setText(QApplication::translate("EmailWindow", "Tre\305\233\304\207:", Q_NULLPTR));
        template1->setText(QApplication::translate("EmailWindow", "Szablon 1", Q_NULLPTR));
        template2->setText(QApplication::translate("EmailWindow", "Szablon 2", Q_NULLPTR));
        template3->setText(QApplication::translate("EmailWindow", "Szablon2", Q_NULLPTR));
        label_9->setText(QApplication::translate("EmailWindow", "Szablony", Q_NULLPTR));
        sendBtn->setText(QApplication::translate("EmailWindow", "Wy\305\233lij", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class EmailWindow: public Ui_EmailWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
