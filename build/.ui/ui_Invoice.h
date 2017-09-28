/********************************************************************************
** Form generated from reading UI file 'Invoice.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INVOICE_H
#define UI_INVOICE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Invoice
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *hboxLayout;
    QHBoxLayout *hboxLayout1;
    QHBoxLayout *hboxLayout2;
    QLabel *textLabel1_3;
    QLineEdit *invNr;
    QPushButton *backBtn;
    QSpacerItem *spacerItem;
    QHBoxLayout *hboxLayout3;
    QLabel *textLabel3;
    QDateEdit *sellingDate;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *spacer8_3;
    QLabel *textLabel3_2;
    QDateEdit *productDate;
    QHBoxLayout *horizontalLayout_6;
    QLabel *textLabel1;
    QLineEdit *buyerName;
    QPushButton *buyerListGet;
    QPushButton *addBuyerBtn;
    QLabel *textLabel1_2;
    QTableWidget *tableGoods;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *spacerItem1;
    QPushButton *addGoodsBtn;
    QPushButton *rmGoodsBtn;
    QPushButton *editGoodsBtn;
    QSpacerItem *spacerItem2;
    QCheckBox *constRab;
    QLabel *discountLabel;
    QSpinBox *discountVal;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *konverters;
    QLabel *label;
    QPushButton *konvEUR;
    QPushButton *konvUSD;
    QPushButton *konvPLN;
    QPushButton *konvCHF;
    QPushButton *konvGBP;
    QPushButton *konvRUB;
    QHBoxLayout *hboxLayout4;
    QVBoxLayout *addDataLabels;
    QLabel *textLabel5;
    QLabel *textLabel6;
    QLabel *textLabel2_3;
    QVBoxLayout *addData;
    QComboBox *paysCombo;
    QDateEdit *liabDate;
    QComboBox *currCombo;
    QSpacerItem *spacerItem3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *descPayments;
    QLabel *textLabelSum1;
    QLabel *textLabelSum2;
    QLabel *textLabelSum3;
    QVBoxLayout *dataPayments;
    QLabel *sum1;
    QLabel *sum2;
    QLabel *sum3;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *hboxLayout5;
    QLabel *textLabel7;
    QLineEdit *additEdit;
    QFrame *line;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *spacer6;
    QPushButton *closeBtn;
    QSpacerItem *spacer4;
    QPushButton *saveBtn;
    QSpacerItem *spacer5_2;
    QPushButton *printBtn;
    QSpacerItem *spacer5;

    void setupUi(QDialog *Invoice)
    {
        if (Invoice->objectName().isEmpty())
            Invoice->setObjectName(QStringLiteral("Invoice"));
        Invoice->setWindowModality(Qt::NonModal);
        Invoice->resize(555, 674);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Invoice->sizePolicy().hasHeightForWidth());
        Invoice->setSizePolicy(sizePolicy);
        Invoice->setMinimumSize(QSize(403, 500));
        verticalLayout_2 = new QVBoxLayout(Invoice);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetMinAndMaxSize);
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setObjectName(QStringLiteral("hboxLayout1"));
        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setSpacing(6);
        hboxLayout2->setObjectName(QStringLiteral("hboxLayout2"));
        textLabel1_3 = new QLabel(Invoice);
        textLabel1_3->setObjectName(QStringLiteral("textLabel1_3"));
        textLabel1_3->setWordWrap(false);

        hboxLayout2->addWidget(textLabel1_3);

        invNr = new QLineEdit(Invoice);
        invNr->setObjectName(QStringLiteral("invNr"));
        invNr->setEnabled(false);
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        invNr->setFont(font);
        invNr->setFocusPolicy(Qt::ClickFocus);

        hboxLayout2->addWidget(invNr);


        hboxLayout1->addLayout(hboxLayout2);

        backBtn = new QPushButton(Invoice);
        backBtn->setObjectName(QStringLiteral("backBtn"));
        backBtn->setCursor(QCursor(Qt::PointingHandCursor));
        backBtn->setFocusPolicy(Qt::NoFocus);
        backBtn->setFlat(false);

        hboxLayout1->addWidget(backBtn);


        hboxLayout->addLayout(hboxLayout1);

        spacerItem = new QSpacerItem(31, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        hboxLayout3 = new QHBoxLayout();
        hboxLayout3->setSpacing(6);
        hboxLayout3->setObjectName(QStringLiteral("hboxLayout3"));
        textLabel3 = new QLabel(Invoice);
        textLabel3->setObjectName(QStringLiteral("textLabel3"));
        textLabel3->setWordWrap(false);

        hboxLayout3->addWidget(textLabel3);

        sellingDate = new QDateEdit(Invoice);
        sellingDate->setObjectName(QStringLiteral("sellingDate"));
        sellingDate->setCursor(QCursor(Qt::UpArrowCursor));
        sellingDate->setFocusPolicy(Qt::NoFocus);
        sellingDate->setCalendarPopup(true);

        hboxLayout3->addWidget(sellingDate);


        hboxLayout->addLayout(hboxLayout3);


        verticalLayout_2->addLayout(hboxLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        spacer8_3 = new QSpacerItem(468, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(spacer8_3);

        textLabel3_2 = new QLabel(Invoice);
        textLabel3_2->setObjectName(QStringLiteral("textLabel3_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(textLabel3_2->sizePolicy().hasHeightForWidth());
        textLabel3_2->setSizePolicy(sizePolicy1);
        textLabel3_2->setWordWrap(false);

        horizontalLayout->addWidget(textLabel3_2);

        productDate = new QDateEdit(Invoice);
        productDate->setObjectName(QStringLiteral("productDate"));
        productDate->setCursor(QCursor(Qt::UpArrowCursor));
        productDate->setFocusPolicy(Qt::NoFocus);
        productDate->setCalendarPopup(true);

        horizontalLayout->addWidget(productDate);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        textLabel1 = new QLabel(Invoice);
        textLabel1->setObjectName(QStringLiteral("textLabel1"));
        textLabel1->setWordWrap(false);

        horizontalLayout_6->addWidget(textLabel1);

        buyerName = new QLineEdit(Invoice);
        buyerName->setObjectName(QStringLiteral("buyerName"));
        buyerName->setEnabled(false);
        buyerName->setFont(font);
        buyerName->setCursor(QCursor(Qt::BlankCursor));
        buyerName->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_6->addWidget(buyerName);

        buyerListGet = new QPushButton(Invoice);
        buyerListGet->setObjectName(QStringLiteral("buyerListGet"));
        buyerListGet->setCursor(QCursor(Qt::PointingHandCursor));
        buyerListGet->setFocusPolicy(Qt::StrongFocus);

        horizontalLayout_6->addWidget(buyerListGet);

        addBuyerBtn = new QPushButton(Invoice);
        addBuyerBtn->setObjectName(QStringLiteral("addBuyerBtn"));
        addBuyerBtn->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_6->addWidget(addBuyerBtn);


        verticalLayout_2->addLayout(horizontalLayout_6);

        textLabel1_2 = new QLabel(Invoice);
        textLabel1_2->setObjectName(QStringLiteral("textLabel1_2"));
        textLabel1_2->setWordWrap(false);

        verticalLayout_2->addWidget(textLabel1_2);

        tableGoods = new QTableWidget(Invoice);
        if (tableGoods->columnCount() < 11)
            tableGoods->setColumnCount(11);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableGoods->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableGoods->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableGoods->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableGoods->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableGoods->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableGoods->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableGoods->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableGoods->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableGoods->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableGoods->setHorizontalHeaderItem(9, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableGoods->setHorizontalHeaderItem(10, __qtablewidgetitem10);
        tableGoods->setObjectName(QStringLiteral("tableGoods"));
        tableGoods->setEnabled(true);
        tableGoods->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableGoods->setSelectionMode(QAbstractItemView::SingleSelection);
        tableGoods->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableGoods->setShowGrid(true);
        tableGoods->setRowCount(0);
        tableGoods->setColumnCount(11);

        verticalLayout_2->addWidget(tableGoods);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        spacerItem1 = new QSpacerItem(30, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(spacerItem1);

        addGoodsBtn = new QPushButton(Invoice);
        addGoodsBtn->setObjectName(QStringLiteral("addGoodsBtn"));
        addGoodsBtn->setCursor(QCursor(Qt::PointingHandCursor));
        addGoodsBtn->setFocusPolicy(Qt::StrongFocus);
        addGoodsBtn->setAutoDefault(true);

        horizontalLayout_2->addWidget(addGoodsBtn);

        rmGoodsBtn = new QPushButton(Invoice);
        rmGoodsBtn->setObjectName(QStringLiteral("rmGoodsBtn"));
        rmGoodsBtn->setCursor(QCursor(Qt::PointingHandCursor));
        rmGoodsBtn->setAutoDefault(true);

        horizontalLayout_2->addWidget(rmGoodsBtn);

        editGoodsBtn = new QPushButton(Invoice);
        editGoodsBtn->setObjectName(QStringLiteral("editGoodsBtn"));
        editGoodsBtn->setCursor(QCursor(Qt::PointingHandCursor));
        editGoodsBtn->setAutoDefault(true);

        horizontalLayout_2->addWidget(editGoodsBtn);

        spacerItem2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(spacerItem2);

        constRab = new QCheckBox(Invoice);
        constRab->setObjectName(QStringLiteral("constRab"));
        constRab->setMinimumSize(QSize(0, 27));
        constRab->setCursor(QCursor(Qt::PointingHandCursor));
        constRab->setIconSize(QSize(16, 16));

        horizontalLayout_2->addWidget(constRab);

        discountLabel = new QLabel(Invoice);
        discountLabel->setObjectName(QStringLiteral("discountLabel"));
        discountLabel->setWordWrap(false);

        horizontalLayout_2->addWidget(discountLabel);

        discountVal = new QSpinBox(Invoice);
        discountVal->setObjectName(QStringLiteral("discountVal"));

        horizontalLayout_2->addWidget(discountVal);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        konverters = new QVBoxLayout();
        konverters->setSpacing(6);
        konverters->setObjectName(QStringLiteral("konverters"));
        label = new QLabel(Invoice);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignCenter);
        label->setMargin(5);

        konverters->addWidget(label);

        konvEUR = new QPushButton(Invoice);
        konvEUR->setObjectName(QStringLiteral("konvEUR"));
        konvEUR->setCursor(QCursor(Qt::PointingHandCursor));

        konverters->addWidget(konvEUR);

        konvUSD = new QPushButton(Invoice);
        konvUSD->setObjectName(QStringLiteral("konvUSD"));
        konvUSD->setCursor(QCursor(Qt::PointingHandCursor));

        konverters->addWidget(konvUSD);

        konvPLN = new QPushButton(Invoice);
        konvPLN->setObjectName(QStringLiteral("konvPLN"));
        konvPLN->setCursor(QCursor(Qt::PointingHandCursor));

        konverters->addWidget(konvPLN);

        konvCHF = new QPushButton(Invoice);
        konvCHF->setObjectName(QStringLiteral("konvCHF"));
        konvCHF->setCursor(QCursor(Qt::PointingHandCursor));

        konverters->addWidget(konvCHF);

        konvGBP = new QPushButton(Invoice);
        konvGBP->setObjectName(QStringLiteral("konvGBP"));
        konvGBP->setCursor(QCursor(Qt::PointingHandCursor));

        konverters->addWidget(konvGBP);

        konvRUB = new QPushButton(Invoice);
        konvRUB->setObjectName(QStringLiteral("konvRUB"));
        konvRUB->setCursor(QCursor(Qt::PointingHandCursor));

        konverters->addWidget(konvRUB);


        horizontalLayout_5->addLayout(konverters);

        hboxLayout4 = new QHBoxLayout();
        hboxLayout4->setSpacing(6);
        hboxLayout4->setObjectName(QStringLiteral("hboxLayout4"));
        addDataLabels = new QVBoxLayout();
        addDataLabels->setSpacing(6);
        addDataLabels->setObjectName(QStringLiteral("addDataLabels"));
        textLabel5 = new QLabel(Invoice);
        textLabel5->setObjectName(QStringLiteral("textLabel5"));
        textLabel5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel5->setWordWrap(false);

        addDataLabels->addWidget(textLabel5);

        textLabel6 = new QLabel(Invoice);
        textLabel6->setObjectName(QStringLiteral("textLabel6"));
        textLabel6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel6->setWordWrap(true);

        addDataLabels->addWidget(textLabel6);

        textLabel2_3 = new QLabel(Invoice);
        textLabel2_3->setObjectName(QStringLiteral("textLabel2_3"));
        textLabel2_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel2_3->setWordWrap(false);

        addDataLabels->addWidget(textLabel2_3);


        hboxLayout4->addLayout(addDataLabels);

        addData = new QVBoxLayout();
        addData->setSpacing(6);
        addData->setObjectName(QStringLiteral("addData"));
        paysCombo = new QComboBox(Invoice);
        paysCombo->setObjectName(QStringLiteral("paysCombo"));
        paysCombo->setCursor(QCursor(Qt::PointingHandCursor));

        addData->addWidget(paysCombo);

        liabDate = new QDateEdit(Invoice);
        liabDate->setObjectName(QStringLiteral("liabDate"));
        liabDate->setCursor(QCursor(Qt::UpArrowCursor));
        liabDate->setCalendarPopup(true);

        addData->addWidget(liabDate);

        currCombo = new QComboBox(Invoice);
        currCombo->setObjectName(QStringLiteral("currCombo"));
        currCombo->setMinimumSize(QSize(80, 0));
        currCombo->setCursor(QCursor(Qt::PointingHandCursor));

        addData->addWidget(currCombo);


        hboxLayout4->addLayout(addData);


        horizontalLayout_5->addLayout(hboxLayout4);

        spacerItem3 = new QSpacerItem(100, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(spacerItem3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        descPayments = new QVBoxLayout();
        descPayments->setSpacing(6);
        descPayments->setObjectName(QStringLiteral("descPayments"));
        textLabelSum1 = new QLabel(Invoice);
        textLabelSum1->setObjectName(QStringLiteral("textLabelSum1"));
        textLabelSum1->setMinimumSize(QSize(150, 0));
        textLabelSum1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabelSum1->setWordWrap(false);

        descPayments->addWidget(textLabelSum1);

        textLabelSum2 = new QLabel(Invoice);
        textLabelSum2->setObjectName(QStringLiteral("textLabelSum2"));
        textLabelSum2->setMinimumSize(QSize(150, 0));
        textLabelSum2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabelSum2->setWordWrap(false);

        descPayments->addWidget(textLabelSum2);

        textLabelSum3 = new QLabel(Invoice);
        textLabelSum3->setObjectName(QStringLiteral("textLabelSum3"));
        textLabelSum3->setMinimumSize(QSize(150, 0));
        textLabelSum3->setFont(font);
        textLabelSum3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabelSum3->setWordWrap(false);

        descPayments->addWidget(textLabelSum3);


        horizontalLayout_3->addLayout(descPayments);

        dataPayments = new QVBoxLayout();
        dataPayments->setSpacing(6);
        dataPayments->setObjectName(QStringLiteral("dataPayments"));
        sum1 = new QLabel(Invoice);
        sum1->setObjectName(QStringLiteral("sum1"));
        sum1->setMinimumSize(QSize(80, 0));
        sum1->setWordWrap(false);

        dataPayments->addWidget(sum1);

        sum2 = new QLabel(Invoice);
        sum2->setObjectName(QStringLiteral("sum2"));
        sum2->setMinimumSize(QSize(80, 0));
        sum2->setWordWrap(false);

        dataPayments->addWidget(sum2);

        sum3 = new QLabel(Invoice);
        sum3->setObjectName(QStringLiteral("sum3"));
        sum3->setMinimumSize(QSize(80, 0));
        sum3->setFont(font);
        sum3->setWordWrap(false);

        dataPayments->addWidget(sum3);


        horizontalLayout_3->addLayout(dataPayments);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout_5->addLayout(verticalLayout);


        verticalLayout_2->addLayout(horizontalLayout_5);

        hboxLayout5 = new QHBoxLayout();
        hboxLayout5->setSpacing(6);
        hboxLayout5->setObjectName(QStringLiteral("hboxLayout5"));
        textLabel7 = new QLabel(Invoice);
        textLabel7->setObjectName(QStringLiteral("textLabel7"));
        textLabel7->setWordWrap(false);

        hboxLayout5->addWidget(textLabel7);

        additEdit = new QLineEdit(Invoice);
        additEdit->setObjectName(QStringLiteral("additEdit"));

        hboxLayout5->addWidget(additEdit);


        verticalLayout_2->addLayout(hboxLayout5);

        line = new QFrame(Invoice);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        spacer6 = new QSpacerItem(37, 23, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(spacer6);

        closeBtn = new QPushButton(Invoice);
        closeBtn->setObjectName(QStringLiteral("closeBtn"));
        closeBtn->setAutoDefault(true);

        horizontalLayout_4->addWidget(closeBtn);

        spacer4 = new QSpacerItem(228, 23, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(spacer4);

        saveBtn = new QPushButton(Invoice);
        saveBtn->setObjectName(QStringLiteral("saveBtn"));
        saveBtn->setAutoDefault(true);

        horizontalLayout_4->addWidget(saveBtn);

        spacer5_2 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(spacer5_2);

        printBtn = new QPushButton(Invoice);
        printBtn->setObjectName(QStringLiteral("printBtn"));
        printBtn->setAutoDefault(true);

        horizontalLayout_4->addWidget(printBtn);

        spacer5 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(spacer5);


        verticalLayout_2->addLayout(horizontalLayout_4);

        QWidget::setTabOrder(buyerListGet, addGoodsBtn);
        QWidget::setTabOrder(addGoodsBtn, constRab);
        QWidget::setTabOrder(constRab, discountVal);
        QWidget::setTabOrder(discountVal, paysCombo);
        QWidget::setTabOrder(paysCombo, liabDate);
        QWidget::setTabOrder(liabDate, currCombo);
        QWidget::setTabOrder(currCombo, additEdit);
        QWidget::setTabOrder(additEdit, saveBtn);
        QWidget::setTabOrder(saveBtn, printBtn);
        QWidget::setTabOrder(printBtn, closeBtn);
        QWidget::setTabOrder(closeBtn, rmGoodsBtn);
        QWidget::setTabOrder(rmGoodsBtn, editGoodsBtn);
        QWidget::setTabOrder(editGoodsBtn, invNr);
        QWidget::setTabOrder(invNr, addBuyerBtn);
        QWidget::setTabOrder(addBuyerBtn, tableGoods);

        retranslateUi(Invoice);

        QMetaObject::connectSlotsByName(Invoice);
    } // setupUi

    void retranslateUi(QDialog *Invoice)
    {
        Invoice->setWindowTitle(QApplication::translate("Invoice", "Faktura VAT", Q_NULLPTR));
        textLabel1_3->setText(QApplication::translate("Invoice", "Symbol:", Q_NULLPTR));
        invNr->setText(QApplication::translate("Invoice", "1/1/2006", Q_NULLPTR));
        backBtn->setText(QApplication::translate("Invoice", "co&fnij", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        backBtn->setShortcut(QApplication::translate("Invoice", "Alt+F", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        textLabel3->setText(QApplication::translate("Invoice", "Data sprzeda\305\274y:", Q_NULLPTR));
        sellingDate->setDisplayFormat(QApplication::translate("Invoice", "dd/MM/yyyy", Q_NULLPTR));
        textLabel3_2->setText(QApplication::translate("Invoice", "Data wystawienia:", Q_NULLPTR));
        productDate->setDisplayFormat(QApplication::translate("Invoice", "dd/MM/yyyy", Q_NULLPTR));
        textLabel1->setText(QApplication::translate("Invoice", "Kontrahent:", Q_NULLPTR));
        buyerListGet->setText(QApplication::translate("Invoice", "wybier&z", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        buyerListGet->setShortcut(QApplication::translate("Invoice", "Ctrl+K", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        addBuyerBtn->setText(QApplication::translate("Invoice", "do&daj", Q_NULLPTR));
        textLabel1_2->setText(QApplication::translate("Invoice", "Lista towar\303\263w/us\305\202ug:", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tableGoods->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("Invoice", "Lp.", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tableGoods->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("Invoice", "Nazwa", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = tableGoods->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("Invoice", "Kod", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = tableGoods->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("Invoice", "PKWiU", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = tableGoods->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("Invoice", "Ilo\305\233\304\207", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem5 = tableGoods->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("Invoice", "Jm.", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem6 = tableGoods->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("Invoice", "Rabat", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem7 = tableGoods->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QApplication::translate("Invoice", "Cena jn.", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem8 = tableGoods->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QApplication::translate("Invoice", "Netto", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem9 = tableGoods->horizontalHeaderItem(9);
        ___qtablewidgetitem9->setText(QApplication::translate("Invoice", "Vat", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem10 = tableGoods->horizontalHeaderItem(10);
        ___qtablewidgetitem10->setText(QApplication::translate("Invoice", "Brutto", Q_NULLPTR));
        addGoodsBtn->setText(QApplication::translate("Invoice", "Dodaj", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        addGoodsBtn->setShortcut(QApplication::translate("Invoice", "Ctrl+T", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        rmGoodsBtn->setText(QApplication::translate("Invoice", "Usu\305\204", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        rmGoodsBtn->setShortcut(QApplication::translate("Invoice", "Ctrl+U", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        editGoodsBtn->setText(QApplication::translate("Invoice", "Edycja", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        editGoodsBtn->setShortcut(QApplication::translate("Invoice", "Ctrl+E", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        constRab->setText(QApplication::translate("Invoice", "Sta\305\202y", Q_NULLPTR));
        discountLabel->setText(QApplication::translate("Invoice", "Rabat:", Q_NULLPTR));
        label->setText(QApplication::translate("Invoice", "Konwerter", Q_NULLPTR));
        konvEUR->setText(QApplication::translate("Invoice", "EUR", Q_NULLPTR));
        konvUSD->setText(QApplication::translate("Invoice", "USD", Q_NULLPTR));
        konvPLN->setText(QApplication::translate("Invoice", "PLN", Q_NULLPTR));
        konvCHF->setText(QApplication::translate("Invoice", "CHF", Q_NULLPTR));
        konvGBP->setText(QApplication::translate("Invoice", "GBP", Q_NULLPTR));
        konvRUB->setText(QApplication::translate("Invoice", "RUB", Q_NULLPTR));
        textLabel5->setText(QApplication::translate("Invoice", "P\305\202atno\305\233\304\207:", Q_NULLPTR));
        textLabel6->setText(QApplication::translate("Invoice", "Termin:", Q_NULLPTR));
        textLabel2_3->setText(QApplication::translate("Invoice", "Waluta:", Q_NULLPTR));
        liabDate->setDisplayFormat(QApplication::translate("Invoice", "dd/MM/yyyy", Q_NULLPTR));
        textLabelSum1->setText(QApplication::translate("Invoice", "Razem netto:", Q_NULLPTR));
        textLabelSum2->setText(QApplication::translate("Invoice", "Rabat:", Q_NULLPTR));
        textLabelSum3->setText(QApplication::translate("Invoice", "Do zaplaty:", Q_NULLPTR));
        sum1->setText(QApplication::translate("Invoice", "0.00", Q_NULLPTR));
        sum2->setText(QApplication::translate("Invoice", "0.00", Q_NULLPTR));
        sum3->setText(QApplication::translate("Invoice", "0.00", Q_NULLPTR));
        textLabel7->setText(QApplication::translate("Invoice", "Dodatkowy tekst:", Q_NULLPTR));
        additEdit->setText(QApplication::translate("Invoice", "towar odebra\305\202em zgodnie z faktur\304\205", Q_NULLPTR));
        closeBtn->setText(QApplication::translate("Invoice", "&Zamknij", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        closeBtn->setShortcut(QApplication::translate("Invoice", "Ctrl+X", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        saveBtn->setText(QApplication::translate("Invoice", "Zapisz", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        saveBtn->setShortcut(QApplication::translate("Invoice", "Ctrl+S", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        printBtn->setText(QApplication::translate("Invoice", "Drukuj", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        printBtn->setShortcut(QApplication::translate("Invoice", "Ctrl+P", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
    } // retranslateUi

};

namespace Ui {
    class Invoice: public Ui_Invoice {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INVOICE_H
