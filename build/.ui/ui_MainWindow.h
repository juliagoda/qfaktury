/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *plikDrukujAction;
    QAction *invoiceDelAction;
    QAction *addInvoiceAction;
    QAction *addBuyersAction;
    QAction *delBuyersAction;
    QAction *editBuyersAction;
    QAction *pomocO_QtAction;
    QAction *fileEndAction;
    QAction *invoiceEdAction;
    QAction *fileData_companyAction;
    QAction *przelewyDrukuj_Action;
    QAction *helpAbout_appAction;
    QAction *fileSettingsAction;
    QAction *przelewyZUS;
    QAction *przelewyUSAction;
    QAction *helpAction;
    QAction *separatornew_itemAction;
    QAction *editGoodsAction;
    QAction *delGoodsAction;
    QAction *addGoodsAction;
    QAction *fileExportEDIAction;
    QAction *fileExport_pdfAction;
    QAction *fileExport_XMLAction;
    QAction *fileImport_EDIAction;
    QAction *fileImport_XMLAction;
    QAction *invoiceCorrAction;
    QAction *invoiceProFormaAction;
    QAction *nextPageAction;
    QAction *prevPageAction;
    QAction *actionBug;
    QAction *invoiceDuplAction;
    QAction *invoiceGrossAction;
    QAction *invoiceBillAction;
    QAction *action_Qt;
    QAction *actionPrintBuyer;
    QAction *invoiceRRAction;
    QAction *actionCreateBackup;
    QAction *actionLoadBackup;
    QAction *sendEmailAction;
    QAction *WZAction;
    QAction *warehouseEdAction;
    QAction *warehouseDelAction;
    QAction *RWAction;
    QWidget *widget;
    QGridLayout *gridLayout_2;
    QTabWidget *organizer;
    QWidget *tab;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QTextEdit *todayExercise;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *calendarLayout;
    QTabWidget *tabWidget2;
    QWidget *invoiceTab;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *textLabel1;
    QDateEdit *filtrStart;
    QLabel *textLabel2;
    QDateEdit *filtrEnd;
    QPushButton *applyFiltrBtn;
    QTableWidget *tableH;
    QWidget *warehouseTab;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QDateEdit *warehouseFromDate;
    QLabel *label_2;
    QDateEdit *warehouseToDate;
    QPushButton *findWarehouses;
    QTableWidget *tableM;
    QWidget *buyerTab;
    QGridLayout *gridLayout1;
    QTableWidget *tableK;
    QWidget *goodsTab;
    QGridLayout *gridLayout2;
    QTableWidget *tableT;
    QToolButton *hideOrganizer;
    QMenuBar *MenuBarEditor;
    QMenu *plikAct;
    QMenu *fakturyAct;
    QMenu *buyersAct;
    QMenu *goodsAct;
    QMenu *helpAct;
    QMenu *menuPlugins;
    QMenu *warehouseMenu;
    QToolBar *toolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(655, 445);
        MainWindow->setMinimumSize(QSize(600, 256));
        QIcon icon;
        icon.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        plikDrukujAction = new QAction(MainWindow);
        plikDrukujAction->setObjectName(QStringLiteral("plikDrukujAction"));
        invoiceDelAction = new QAction(MainWindow);
        invoiceDelAction->setObjectName(QStringLiteral("invoiceDelAction"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/res/icons/usun_fakture.png"), QSize(), QIcon::Normal, QIcon::Off);
        invoiceDelAction->setIcon(icon1);
        addInvoiceAction = new QAction(MainWindow);
        addInvoiceAction->setObjectName(QStringLiteral("addInvoiceAction"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/res/icons/nowa_faktura.png"), QSize(), QIcon::Normal, QIcon::Off);
        addInvoiceAction->setIcon(icon2);
        addBuyersAction = new QAction(MainWindow);
        addBuyersAction->setObjectName(QStringLiteral("addBuyersAction"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/res/icons/dodaj_kontrahentow.png"), QSize(), QIcon::Normal, QIcon::Off);
        addBuyersAction->setIcon(icon3);
        delBuyersAction = new QAction(MainWindow);
        delBuyersAction->setObjectName(QStringLiteral("delBuyersAction"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/res/icons/usun_kontrahentow.png"), QSize(), QIcon::Normal, QIcon::Off);
        delBuyersAction->setIcon(icon4);
        editBuyersAction = new QAction(MainWindow);
        editBuyersAction->setObjectName(QStringLiteral("editBuyersAction"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/res/icons/edytuj_kontrahentow.png"), QSize(), QIcon::Normal, QIcon::Off);
        editBuyersAction->setIcon(icon5);
        pomocO_QtAction = new QAction(MainWindow);
        pomocO_QtAction->setObjectName(QStringLiteral("pomocO_QtAction"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/res/icons/pomoc.png"), QSize(), QIcon::Normal, QIcon::Off);
        pomocO_QtAction->setIcon(icon6);
        fileEndAction = new QAction(MainWindow);
        fileEndAction->setObjectName(QStringLiteral("fileEndAction"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/res/icons/koniec.png"), QSize(), QIcon::Normal, QIcon::Off);
        fileEndAction->setIcon(icon7);
        invoiceEdAction = new QAction(MainWindow);
        invoiceEdAction->setObjectName(QStringLiteral("invoiceEdAction"));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/res/icons/edytuj_fakture.png"), QSize(), QIcon::Normal, QIcon::Off);
        invoiceEdAction->setIcon(icon8);
        fileData_companyAction = new QAction(MainWindow);
        fileData_companyAction->setObjectName(QStringLiteral("fileData_companyAction"));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/res/icons/dane_firmy.png"), QSize(), QIcon::Normal, QIcon::Off);
        fileData_companyAction->setIcon(icon9);
        fileData_companyAction->setIconVisibleInMenu(true);
        przelewyDrukuj_Action = new QAction(MainWindow);
        przelewyDrukuj_Action->setObjectName(QStringLiteral("przelewyDrukuj_Action"));
        helpAbout_appAction = new QAction(MainWindow);
        helpAbout_appAction->setObjectName(QStringLiteral("helpAbout_appAction"));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/res/icons/qfaktury_22.png"), QSize(), QIcon::Normal, QIcon::Off);
        helpAbout_appAction->setIcon(icon10);
        fileSettingsAction = new QAction(MainWindow);
        fileSettingsAction->setObjectName(QStringLiteral("fileSettingsAction"));
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/res/icons/ustawienia.png"), QSize(), QIcon::Normal, QIcon::Off);
        fileSettingsAction->setIcon(icon11);
        przelewyZUS = new QAction(MainWindow);
        przelewyZUS->setObjectName(QStringLiteral("przelewyZUS"));
        QIcon icon12;
        icon12.addFile(QStringLiteral("image10"), QSize(), QIcon::Normal, QIcon::Off);
        przelewyZUS->setIcon(icon12);
        przelewyUSAction = new QAction(MainWindow);
        przelewyUSAction->setObjectName(QStringLiteral("przelewyUSAction"));
        QIcon icon13;
        icon13.addFile(QStringLiteral("image11"), QSize(), QIcon::Normal, QIcon::Off);
        przelewyUSAction->setIcon(icon13);
        helpAction = new QAction(MainWindow);
        helpAction->setObjectName(QStringLiteral("helpAction"));
        QIcon icon14;
        icon14.addFile(QStringLiteral(":/res/icons/strona_github.png"), QSize(), QIcon::Normal, QIcon::Off);
        helpAction->setIcon(icon14);
        separatornew_itemAction = new QAction(MainWindow);
        separatornew_itemAction->setObjectName(QStringLiteral("separatornew_itemAction"));
        editGoodsAction = new QAction(MainWindow);
        editGoodsAction->setObjectName(QStringLiteral("editGoodsAction"));
        QIcon icon15;
        icon15.addFile(QStringLiteral(":/res/icons/edytuj_towar.png"), QSize(), QIcon::Normal, QIcon::Off);
        editGoodsAction->setIcon(icon15);
        delGoodsAction = new QAction(MainWindow);
        delGoodsAction->setObjectName(QStringLiteral("delGoodsAction"));
        QIcon icon16;
        icon16.addFile(QStringLiteral(":/res/icons/usun_towar.png"), QSize(), QIcon::Normal, QIcon::Off);
        delGoodsAction->setIcon(icon16);
        addGoodsAction = new QAction(MainWindow);
        addGoodsAction->setObjectName(QStringLiteral("addGoodsAction"));
        QIcon icon17;
        icon17.addFile(QStringLiteral(":/res/icons/dodaj_towar.png"), QSize(), QIcon::Normal, QIcon::Off);
        addGoodsAction->setIcon(icon17);
        fileExportEDIAction = new QAction(MainWindow);
        fileExportEDIAction->setObjectName(QStringLiteral("fileExportEDIAction"));
        fileExportEDIAction->setVisible(false);
        fileExport_pdfAction = new QAction(MainWindow);
        fileExport_pdfAction->setObjectName(QStringLiteral("fileExport_pdfAction"));
        fileExport_pdfAction->setVisible(false);
        fileExport_XMLAction = new QAction(MainWindow);
        fileExport_XMLAction->setObjectName(QStringLiteral("fileExport_XMLAction"));
        fileExport_XMLAction->setVisible(false);
        fileImport_EDIAction = new QAction(MainWindow);
        fileImport_EDIAction->setObjectName(QStringLiteral("fileImport_EDIAction"));
        fileImport_EDIAction->setVisible(false);
        fileImport_XMLAction = new QAction(MainWindow);
        fileImport_XMLAction->setObjectName(QStringLiteral("fileImport_XMLAction"));
        fileImport_XMLAction->setVisible(false);
        invoiceCorrAction = new QAction(MainWindow);
        invoiceCorrAction->setObjectName(QStringLiteral("invoiceCorrAction"));
        QIcon icon18;
        icon18.addFile(QStringLiteral(":/res/icons/nowa_korekta.png"), QSize(), QIcon::Normal, QIcon::Off);
        invoiceCorrAction->setIcon(icon18);
        invoiceProFormaAction = new QAction(MainWindow);
        invoiceProFormaAction->setObjectName(QStringLiteral("invoiceProFormaAction"));
        QIcon icon19;
        icon19.addFile(QStringLiteral(":/res/icons/nowa_proforma.png"), QSize(), QIcon::Normal, QIcon::Off);
        invoiceProFormaAction->setIcon(icon19);
        nextPageAction = new QAction(MainWindow);
        nextPageAction->setObjectName(QStringLiteral("nextPageAction"));
        prevPageAction = new QAction(MainWindow);
        prevPageAction->setObjectName(QStringLiteral("prevPageAction"));
        actionBug = new QAction(MainWindow);
        actionBug->setObjectName(QStringLiteral("actionBug"));
        QIcon icon20;
        icon20.addFile(QStringLiteral(":/res/icons/zglos_blad.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionBug->setIcon(icon20);
        invoiceDuplAction = new QAction(MainWindow);
        invoiceDuplAction->setObjectName(QStringLiteral("invoiceDuplAction"));
        QIcon icon21;
        icon21.addFile(QStringLiteral(":/res/icons/nowa_duplikat.png"), QSize(), QIcon::Normal, QIcon::Off);
        invoiceDuplAction->setIcon(icon21);
        invoiceGrossAction = new QAction(MainWindow);
        invoiceGrossAction->setObjectName(QStringLiteral("invoiceGrossAction"));
        QIcon icon22;
        icon22.addFile(QStringLiteral(":/res/icons/nowa_brutto.png"), QSize(), QIcon::Normal, QIcon::Off);
        invoiceGrossAction->setIcon(icon22);
        invoiceBillAction = new QAction(MainWindow);
        invoiceBillAction->setObjectName(QStringLiteral("invoiceBillAction"));
        QIcon icon23;
        icon23.addFile(QStringLiteral(":/res/icons/nowa_rachunek.png"), QSize(), QIcon::Normal, QIcon::Off);
        invoiceBillAction->setIcon(icon23);
        action_Qt = new QAction(MainWindow);
        action_Qt->setObjectName(QStringLiteral("action_Qt"));
        QIcon icon24;
        icon24.addFile(QStringLiteral(":/res/icons/o_qt.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Qt->setIcon(icon24);
        actionPrintBuyer = new QAction(MainWindow);
        actionPrintBuyer->setObjectName(QStringLiteral("actionPrintBuyer"));
        QIcon icon25;
        icon25.addFile(QStringLiteral(":/res/icons/drukuj_kontrahentow.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPrintBuyer->setIcon(icon25);
        invoiceRRAction = new QAction(MainWindow);
        invoiceRRAction->setObjectName(QStringLiteral("invoiceRRAction"));
        QIcon icon26;
        icon26.addFile(QStringLiteral(":/res/icons/nowa_RR.png"), QSize(), QIcon::Normal, QIcon::Off);
        invoiceRRAction->setIcon(icon26);
        actionCreateBackup = new QAction(MainWindow);
        actionCreateBackup->setObjectName(QStringLiteral("actionCreateBackup"));
        QIcon icon27;
        icon27.addFile(QStringLiteral(":/res/icons/importuj_qfaktury.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCreateBackup->setIcon(icon27);
        actionLoadBackup = new QAction(MainWindow);
        actionLoadBackup->setObjectName(QStringLiteral("actionLoadBackup"));
        QIcon icon28;
        icon28.addFile(QStringLiteral(":/res/icons/eksportuj_qfaktury.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLoadBackup->setIcon(icon28);
        sendEmailAction = new QAction(MainWindow);
        sendEmailAction->setObjectName(QStringLiteral("sendEmailAction"));
        QIcon icon29;
        icon29.addFile(QStringLiteral(":/res/icons/wyslij_fakture.png"), QSize(), QIcon::Normal, QIcon::Off);
        sendEmailAction->setIcon(icon29);
        WZAction = new QAction(MainWindow);
        WZAction->setObjectName(QStringLiteral("WZAction"));
        QIcon icon30;
        icon30.addFile(QStringLiteral(":/res/icons/delivery_note.png"), QSize(), QIcon::Normal, QIcon::Off);
        WZAction->setIcon(icon30);
        warehouseEdAction = new QAction(MainWindow);
        warehouseEdAction->setObjectName(QStringLiteral("warehouseEdAction"));
        QIcon icon31;
        icon31.addFile(QStringLiteral(":/res/icons/edytuj_magazyn.png"), QSize(), QIcon::Normal, QIcon::Off);
        warehouseEdAction->setIcon(icon31);
        warehouseDelAction = new QAction(MainWindow);
        warehouseDelAction->setObjectName(QStringLiteral("warehouseDelAction"));
        QIcon icon32;
        icon32.addFile(QStringLiteral(":/res/icons/usun_magazyn.png"), QSize(), QIcon::Normal, QIcon::Off);
        warehouseDelAction->setIcon(icon32);
        RWAction = new QAction(MainWindow);
        RWAction->setObjectName(QStringLiteral("RWAction"));
        QIcon icon33;
        icon33.addFile(QStringLiteral(":/res/icons/good_issue_note.png"), QSize(), QIcon::Normal, QIcon::Off);
        RWAction->setIcon(icon33);
        widget = new QWidget(MainWindow);
        widget->setObjectName(QStringLiteral("widget"));
        gridLayout_2 = new QGridLayout(widget);
        gridLayout_2->setSpacing(4);
        gridLayout_2->setContentsMargins(9, 9, 9, 9);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        organizer = new QTabWidget(widget);
        organizer->setObjectName(QStringLiteral("organizer"));
        organizer->setMinimumSize(QSize(350, 0));
        organizer->setMaximumSize(QSize(450, 1700));
        organizer->setCursor(QCursor(Qt::ArrowCursor));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        verticalLayout_2 = new QVBoxLayout(tab);
        verticalLayout_2->setSpacing(4);
        verticalLayout_2->setContentsMargins(9, 9, 9, 9);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(4);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        todayExercise = new QTextEdit(tab);
        todayExercise->setObjectName(QStringLiteral("todayExercise"));
        todayExercise->setAutoFormatting(QTextEdit::AutoAll);
        todayExercise->setOverwriteMode(true);
        todayExercise->setTextInteractionFlags(Qt::NoTextInteraction);

        verticalLayout->addWidget(todayExercise);


        verticalLayout_2->addLayout(verticalLayout);

        organizer->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        verticalLayout_4 = new QVBoxLayout(tab_2);
        verticalLayout_4->setSpacing(4);
        verticalLayout_4->setContentsMargins(9, 9, 9, 9);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        calendarLayout = new QVBoxLayout();
        calendarLayout->setSpacing(4);
        calendarLayout->setObjectName(QStringLiteral("calendarLayout"));

        verticalLayout_4->addLayout(calendarLayout);

        organizer->addTab(tab_2, QString());

        gridLayout_2->addWidget(organizer, 0, 1, 1, 1);

        tabWidget2 = new QTabWidget(widget);
        tabWidget2->setObjectName(QStringLiteral("tabWidget2"));
        tabWidget2->setTabPosition(QTabWidget::North);
        tabWidget2->setTabShape(QTabWidget::Rounded);
        invoiceTab = new QWidget();
        invoiceTab->setObjectName(QStringLiteral("invoiceTab"));
        gridLayout = new QGridLayout(invoiceTab);
        gridLayout->setSpacing(4);
        gridLayout->setContentsMargins(9, 9, 9, 9);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(4);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        textLabel1 = new QLabel(invoiceTab);
        textLabel1->setObjectName(QStringLiteral("textLabel1"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(textLabel1->sizePolicy().hasHeightForWidth());
        textLabel1->setSizePolicy(sizePolicy);
        textLabel1->setMinimumSize(QSize(85, 0));
        textLabel1->setWordWrap(false);

        horizontalLayout->addWidget(textLabel1);

        filtrStart = new QDateEdit(invoiceTab);
        filtrStart->setObjectName(QStringLiteral("filtrStart"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(filtrStart->sizePolicy().hasHeightForWidth());
        filtrStart->setSizePolicy(sizePolicy1);
        filtrStart->setCursor(QCursor(Qt::UpArrowCursor));
        filtrStart->setFocusPolicy(Qt::TabFocus);
        filtrStart->setCorrectionMode(QAbstractSpinBox::CorrectToNearestValue);
        filtrStart->setCalendarPopup(true);
        filtrStart->setDate(QDate(2009, 3, 1));

        horizontalLayout->addWidget(filtrStart);

        textLabel2 = new QLabel(invoiceTab);
        textLabel2->setObjectName(QStringLiteral("textLabel2"));
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(40);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(textLabel2->sizePolicy().hasHeightForWidth());
        textLabel2->setSizePolicy(sizePolicy2);
        textLabel2->setLayoutDirection(Qt::LeftToRight);
        textLabel2->setAlignment(Qt::AlignCenter);
        textLabel2->setWordWrap(false);

        horizontalLayout->addWidget(textLabel2);

        filtrEnd = new QDateEdit(invoiceTab);
        filtrEnd->setObjectName(QStringLiteral("filtrEnd"));
        sizePolicy1.setHeightForWidth(filtrEnd->sizePolicy().hasHeightForWidth());
        filtrEnd->setSizePolicy(sizePolicy1);
        filtrEnd->setCursor(QCursor(Qt::UpArrowCursor));
        filtrEnd->setFocusPolicy(Qt::TabFocus);
        filtrEnd->setWrapping(true);
        filtrEnd->setFrame(true);
        filtrEnd->setCalendarPopup(true);
        filtrEnd->setDate(QDate(2010, 1, 1));

        horizontalLayout->addWidget(filtrEnd);

        applyFiltrBtn = new QPushButton(invoiceTab);
        applyFiltrBtn->setObjectName(QStringLiteral("applyFiltrBtn"));
        applyFiltrBtn->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout->addWidget(applyFiltrBtn);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        tableH = new QTableWidget(invoiceTab);
        if (tableH->columnCount() < 6)
            tableH->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableH->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableH->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableH->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableH->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableH->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableH->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        tableH->setObjectName(QStringLiteral("tableH"));
        tableH->setContextMenuPolicy(Qt::CustomContextMenu);
        tableH->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableH->setSelectionMode(QAbstractItemView::SingleSelection);
        tableH->setSelectionBehavior(QAbstractItemView::SelectItems);
        tableH->setSortingEnabled(false);
        tableH->setCornerButtonEnabled(true);
        tableH->setProperty("numRows", QVariant(0));
        tableH->setProperty("numCols", QVariant(6));
        tableH->setProperty("readOnly", QVariant(true));
        tableH->setProperty("sorting", QVariant(true));

        gridLayout->addWidget(tableH, 1, 0, 1, 1);

        tabWidget2->addTab(invoiceTab, QString());
        warehouseTab = new QWidget();
        warehouseTab->setObjectName(QStringLiteral("warehouseTab"));
        verticalLayout_3 = new QVBoxLayout(warehouseTab);
        verticalLayout_3->setSpacing(4);
        verticalLayout_3->setContentsMargins(9, 9, 9, 9);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(4);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(5, 5, 5, 5);
        label = new QLabel(warehouseTab);
        label->setObjectName(QStringLiteral("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMinimumSize(QSize(85, 0));

        horizontalLayout_2->addWidget(label);

        warehouseFromDate = new QDateEdit(warehouseTab);
        warehouseFromDate->setObjectName(QStringLiteral("warehouseFromDate"));

        horizontalLayout_2->addWidget(warehouseFromDate);

        label_2 = new QLabel(warehouseTab);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        warehouseToDate = new QDateEdit(warehouseTab);
        warehouseToDate->setObjectName(QStringLiteral("warehouseToDate"));

        horizontalLayout_2->addWidget(warehouseToDate);

        findWarehouses = new QPushButton(warehouseTab);
        findWarehouses->setObjectName(QStringLiteral("findWarehouses"));

        horizontalLayout_2->addWidget(findWarehouses);


        verticalLayout_3->addLayout(horizontalLayout_2);

        tableM = new QTableWidget(warehouseTab);
        if (tableM->columnCount() < 6)
            tableM->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableM->setHorizontalHeaderItem(0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableM->setHorizontalHeaderItem(1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableM->setHorizontalHeaderItem(2, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableM->setHorizontalHeaderItem(3, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableM->setHorizontalHeaderItem(4, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableM->setHorizontalHeaderItem(5, __qtablewidgetitem11);
        tableM->setObjectName(QStringLiteral("tableM"));
        tableM->setContextMenuPolicy(Qt::CustomContextMenu);
        tableM->setEditTriggers(QAbstractItemView::NoEditTriggers);

        verticalLayout_3->addWidget(tableM);

        tabWidget2->addTab(warehouseTab, QString());
        buyerTab = new QWidget();
        buyerTab->setObjectName(QStringLiteral("buyerTab"));
        gridLayout1 = new QGridLayout(buyerTab);
        gridLayout1->setSpacing(4);
        gridLayout1->setContentsMargins(9, 9, 9, 9);
        gridLayout1->setObjectName(QStringLiteral("gridLayout1"));
        tableK = new QTableWidget(buyerTab);
        if (tableK->columnCount() < 7)
            tableK->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableK->setHorizontalHeaderItem(0, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableK->setHorizontalHeaderItem(1, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableK->setHorizontalHeaderItem(2, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableK->setHorizontalHeaderItem(3, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableK->setHorizontalHeaderItem(4, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableK->setHorizontalHeaderItem(5, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableK->setHorizontalHeaderItem(6, __qtablewidgetitem18);
        tableK->setObjectName(QStringLiteral("tableK"));
        tableK->setContextMenuPolicy(Qt::CustomContextMenu);
        tableK->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableK->setSelectionMode(QAbstractItemView::SingleSelection);
        tableK->setSelectionBehavior(QAbstractItemView::SelectItems);
        tableK->setProperty("numRows", QVariant(0));
        tableK->setProperty("numCols", QVariant(7));
        tableK->setProperty("readOnly", QVariant(true));
        tableK->setProperty("sorting", QVariant(true));

        gridLayout1->addWidget(tableK, 0, 0, 1, 1);

        tabWidget2->addTab(buyerTab, QString());
        goodsTab = new QWidget();
        goodsTab->setObjectName(QStringLiteral("goodsTab"));
        gridLayout2 = new QGridLayout(goodsTab);
        gridLayout2->setSpacing(4);
        gridLayout2->setContentsMargins(9, 9, 9, 9);
        gridLayout2->setObjectName(QStringLiteral("gridLayout2"));
        tableT = new QTableWidget(goodsTab);
        if (tableT->columnCount() < 12)
            tableT->setColumnCount(12);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableT->setHorizontalHeaderItem(0, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tableT->setHorizontalHeaderItem(1, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tableT->setHorizontalHeaderItem(2, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        tableT->setHorizontalHeaderItem(3, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        tableT->setHorizontalHeaderItem(4, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        tableT->setHorizontalHeaderItem(5, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        tableT->setHorizontalHeaderItem(6, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        tableT->setHorizontalHeaderItem(7, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        tableT->setHorizontalHeaderItem(8, __qtablewidgetitem27);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        tableT->setHorizontalHeaderItem(9, __qtablewidgetitem28);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        tableT->setHorizontalHeaderItem(10, __qtablewidgetitem29);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        tableT->setHorizontalHeaderItem(11, __qtablewidgetitem30);
        tableT->setObjectName(QStringLiteral("tableT"));
        tableT->setContextMenuPolicy(Qt::CustomContextMenu);
        tableT->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableT->setSelectionMode(QAbstractItemView::SingleSelection);
        tableT->setSelectionBehavior(QAbstractItemView::SelectItems);
        tableT->setProperty("numRows", QVariant(0));
        tableT->setProperty("numCols", QVariant(12));
        tableT->setProperty("readOnly", QVariant(true));
        tableT->setProperty("sorting", QVariant(true));

        gridLayout2->addWidget(tableT, 0, 0, 1, 1);

        tabWidget2->addTab(goodsTab, QString());

        gridLayout_2->addWidget(tabWidget2, 0, 0, 1, 1);

        hideOrganizer = new QToolButton(widget);
        hideOrganizer->setObjectName(QStringLiteral("hideOrganizer"));

        gridLayout_2->addWidget(hideOrganizer, 1, 1, 1, 1);

        MainWindow->setCentralWidget(widget);
        MenuBarEditor = new QMenuBar(MainWindow);
        MenuBarEditor->setObjectName(QStringLiteral("MenuBarEditor"));
        MenuBarEditor->setGeometry(QRect(0, 0, 655, 29));
        plikAct = new QMenu(MenuBarEditor);
        plikAct->setObjectName(QStringLiteral("plikAct"));
        plikAct->setCursor(QCursor(Qt::PointingHandCursor));
        fakturyAct = new QMenu(MenuBarEditor);
        fakturyAct->setObjectName(QStringLiteral("fakturyAct"));
        fakturyAct->setCursor(QCursor(Qt::PointingHandCursor));
        buyersAct = new QMenu(MenuBarEditor);
        buyersAct->setObjectName(QStringLiteral("buyersAct"));
        buyersAct->setCursor(QCursor(Qt::PointingHandCursor));
        goodsAct = new QMenu(MenuBarEditor);
        goodsAct->setObjectName(QStringLiteral("goodsAct"));
        goodsAct->setCursor(QCursor(Qt::PointingHandCursor));
        helpAct = new QMenu(MenuBarEditor);
        helpAct->setObjectName(QStringLiteral("helpAct"));
        helpAct->setCursor(QCursor(Qt::PointingHandCursor));
        menuPlugins = new QMenu(MenuBarEditor);
        menuPlugins->setObjectName(QStringLiteral("menuPlugins"));
        menuPlugins->setCursor(QCursor(Qt::PointingHandCursor));
        warehouseMenu = new QMenu(MenuBarEditor);
        warehouseMenu->setObjectName(QStringLiteral("warehouseMenu"));
        MainWindow->setMenuBar(MenuBarEditor);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        toolBar->setCursor(QCursor(Qt::PointingHandCursor));
        toolBar->setMovable(false);
        toolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        toolBar->setFloatable(false);
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        QWidget::setTabOrder(tabWidget2, applyFiltrBtn);
        QWidget::setTabOrder(applyFiltrBtn, tableH);
        QWidget::setTabOrder(tableH, filtrStart);
        QWidget::setTabOrder(filtrStart, filtrEnd);
        QWidget::setTabOrder(filtrEnd, tableK);
        QWidget::setTabOrder(tableK, tableT);

        MenuBarEditor->addAction(plikAct->menuAction());
        MenuBarEditor->addAction(fakturyAct->menuAction());
        MenuBarEditor->addAction(warehouseMenu->menuAction());
        MenuBarEditor->addAction(buyersAct->menuAction());
        MenuBarEditor->addAction(goodsAct->menuAction());
        MenuBarEditor->addAction(menuPlugins->menuAction());
        MenuBarEditor->addAction(helpAct->menuAction());
        MenuBarEditor->addSeparator();
        plikAct->addAction(fileData_companyAction);
        plikAct->addAction(fileSettingsAction);
        plikAct->addSeparator();
        plikAct->addAction(fileExportEDIAction);
        plikAct->addAction(fileExport_pdfAction);
        plikAct->addAction(fileExport_XMLAction);
        plikAct->addAction(fileImport_EDIAction);
        plikAct->addAction(fileImport_XMLAction);
        plikAct->addAction(actionCreateBackup);
        plikAct->addAction(actionLoadBackup);
        plikAct->addAction(fileEndAction);
        fakturyAct->addAction(addInvoiceAction);
        fakturyAct->addAction(invoiceGrossAction);
        fakturyAct->addAction(invoiceRRAction);
        fakturyAct->addAction(invoiceBillAction);
        fakturyAct->addSeparator();
        fakturyAct->addAction(invoiceProFormaAction);
        fakturyAct->addAction(invoiceCorrAction);
        fakturyAct->addAction(invoiceDuplAction);
        fakturyAct->addSeparator();
        fakturyAct->addAction(invoiceDelAction);
        fakturyAct->addAction(invoiceEdAction);
        fakturyAct->addAction(sendEmailAction);
        buyersAct->addAction(addBuyersAction);
        buyersAct->addAction(delBuyersAction);
        buyersAct->addAction(editBuyersAction);
        buyersAct->addAction(actionPrintBuyer);
        goodsAct->addAction(addGoodsAction);
        goodsAct->addAction(delGoodsAction);
        goodsAct->addAction(editGoodsAction);
        helpAct->addAction(helpAction);
        helpAct->addAction(actionBug);
        helpAct->addSeparator();
        helpAct->addAction(helpAbout_appAction);
        helpAct->addAction(action_Qt);
        warehouseMenu->addAction(WZAction);
        warehouseMenu->addAction(RWAction);
        warehouseMenu->addSeparator();
        warehouseMenu->addAction(warehouseEdAction);
        warehouseMenu->addAction(warehouseDelAction);
        toolBar->addAction(fileData_companyAction);
        toolBar->addSeparator();
        toolBar->addAction(addInvoiceAction);
        toolBar->addSeparator();
        toolBar->addAction(invoiceProFormaAction);
        toolBar->addSeparator();
        toolBar->addAction(addBuyersAction);
        toolBar->addSeparator();
        toolBar->addAction(addGoodsAction);
        toolBar->addSeparator();
        toolBar->addAction(fileSettingsAction);

        retranslateUi(MainWindow);

        organizer->setCurrentIndex(1);
        tabWidget2->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "QFaktury", Q_NULLPTR));
        plikDrukujAction->setText(QApplication::translate("MainWindow", "Drukuj", Q_NULLPTR));
        plikDrukujAction->setIconText(QApplication::translate("MainWindow", "Drukuj", Q_NULLPTR));
        plikDrukujAction->setProperty("name", QVariant(QApplication::translate("MainWindow", "plikDrukujAction", Q_NULLPTR)));
        invoiceDelAction->setText(QApplication::translate("MainWindow", "&Usu\305\204", Q_NULLPTR));
        invoiceDelAction->setIconText(QApplication::translate("MainWindow", "Usu\305\204", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        invoiceDelAction->setShortcut(QApplication::translate("MainWindow", "U", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        invoiceDelAction->setProperty("name", QVariant(QApplication::translate("MainWindow", "fakturyUsunAction", Q_NULLPTR)));
        addInvoiceAction->setText(QApplication::translate("MainWindow", "&Faktura VAT", Q_NULLPTR));
        addInvoiceAction->setIconText(QApplication::translate("MainWindow", "Nowa faktura", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        addInvoiceAction->setShortcut(QApplication::translate("MainWindow", "F", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        addInvoiceAction->setProperty("name", QVariant(QApplication::translate("MainWindow", "fakturyDodajAction", Q_NULLPTR)));
        addBuyersAction->setText(QApplication::translate("MainWindow", "&Dodaj", Q_NULLPTR));
        addBuyersAction->setIconText(QApplication::translate("MainWindow", "Konrahent", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        addBuyersAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+K", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        addBuyersAction->setProperty("name", QVariant(QApplication::translate("MainWindow", "kontrahenciDodajAction", Q_NULLPTR)));
        delBuyersAction->setText(QApplication::translate("MainWindow", "&Usu\305\204", Q_NULLPTR));
        delBuyersAction->setIconText(QApplication::translate("MainWindow", "Usu\305\204", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        delBuyersAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+D", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        delBuyersAction->setProperty("name", QVariant(QApplication::translate("MainWindow", "kontrahenciUsunAction", Q_NULLPTR)));
        editBuyersAction->setText(QApplication::translate("MainWindow", "&Edycja", Q_NULLPTR));
        editBuyersAction->setIconText(QApplication::translate("MainWindow", "Edycja", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        editBuyersAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+E", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        editBuyersAction->setProperty("name", QVariant(QApplication::translate("MainWindow", "kontrahenciEdycjaAction", Q_NULLPTR)));
        pomocO_QtAction->setText(QApplication::translate("MainWindow", "O Qt", Q_NULLPTR));
        pomocO_QtAction->setIconText(QApplication::translate("MainWindow", "O &Qt", Q_NULLPTR));
        pomocO_QtAction->setProperty("name", QVariant(QApplication::translate("MainWindow", "pomocO_QtAction", Q_NULLPTR)));
        fileEndAction->setText(QApplication::translate("MainWindow", "&Koniec", Q_NULLPTR));
        fileEndAction->setIconText(QApplication::translate("MainWindow", "Koniec", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        fileEndAction->setShortcut(QApplication::translate("MainWindow", "Q", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        fileEndAction->setProperty("name", QVariant(QApplication::translate("MainWindow", "plikKoniecAction", Q_NULLPTR)));
        invoiceEdAction->setText(QApplication::translate("MainWindow", "&Edytuj", Q_NULLPTR));
        invoiceEdAction->setIconText(QApplication::translate("MainWindow", "Edytuj", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        invoiceEdAction->setShortcut(QApplication::translate("MainWindow", "E", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        invoiceEdAction->setProperty("name", QVariant(QApplication::translate("MainWindow", "fakturyEdAction", Q_NULLPTR)));
        fileData_companyAction->setText(QApplication::translate("MainWindow", "&Dane firmy", Q_NULLPTR));
        fileData_companyAction->setIconText(QApplication::translate("MainWindow", "Firma", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        fileData_companyAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+I", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        fileData_companyAction->setProperty("name", QVariant(QApplication::translate("MainWindow", "plikDane_firmyAction", Q_NULLPTR)));
        przelewyDrukuj_Action->setText(QApplication::translate("MainWindow", "Drukuj ", Q_NULLPTR));
        przelewyDrukuj_Action->setIconText(QApplication::translate("MainWindow", "Drukuj ", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        przelewyDrukuj_Action->setShortcut(QApplication::translate("MainWindow", "F2", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        przelewyDrukuj_Action->setProperty("name", QVariant(QApplication::translate("MainWindow", "przelewyDrukuj_Action", Q_NULLPTR)));
        helpAbout_appAction->setText(QApplication::translate("MainWindow", "&O programie", Q_NULLPTR));
        helpAbout_appAction->setIconText(QApplication::translate("MainWindow", "O programie", Q_NULLPTR));
        helpAbout_appAction->setProperty("name", QVariant(QApplication::translate("MainWindow", "pomocO_programieAction", Q_NULLPTR)));
        fileSettingsAction->setText(QApplication::translate("MainWindow", "&Ustawienia", Q_NULLPTR));
        fileSettingsAction->setIconText(QApplication::translate("MainWindow", "Ustawienia", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        fileSettingsAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+U", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        fileSettingsAction->setProperty("name", QVariant(QApplication::translate("MainWindow", "plikUstawieniaAction", Q_NULLPTR)));
        przelewyZUS->setText(QApplication::translate("MainWindow", "Nowy (ZUS)", Q_NULLPTR));
        przelewyZUS->setIconText(QApplication::translate("MainWindow", "Nowy (ZUS)", Q_NULLPTR));
        przelewyZUS->setProperty("name", QVariant(QApplication::translate("MainWindow", "przelewyZUS", Q_NULLPTR)));
        przelewyUSAction->setText(QApplication::translate("MainWindow", "Nowy (US)", Q_NULLPTR));
        przelewyUSAction->setIconText(QApplication::translate("MainWindow", "Nowy (US)", Q_NULLPTR));
        przelewyUSAction->setProperty("name", QVariant(QApplication::translate("MainWindow", "przelewyUSAction", Q_NULLPTR)));
        helpAction->setText(QApplication::translate("MainWindow", "&Strona programu", Q_NULLPTR));
        helpAction->setIconText(QApplication::translate("MainWindow", "Strona programu", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        helpAction->setShortcut(QApplication::translate("MainWindow", "F1", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        helpAction->setProperty("name", QVariant(QApplication::translate("MainWindow", "pomocPomocAction", Q_NULLPTR)));
        separatornew_itemAction->setText(QApplication::translate("MainWindow", "new item", Q_NULLPTR));
        separatornew_itemAction->setIconText(QApplication::translate("MainWindow", "new item", Q_NULLPTR));
        separatornew_itemAction->setProperty("name", QVariant(QApplication::translate("MainWindow", "separatornew_itemAction", Q_NULLPTR)));
        editGoodsAction->setText(QApplication::translate("MainWindow", "&Edycja", Q_NULLPTR));
        editGoodsAction->setIconText(QApplication::translate("MainWindow", "Edycja", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        editGoodsAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+M", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        editGoodsAction->setProperty("name", QVariant(QApplication::translate("MainWindow", "towaryEdycjaAction", Q_NULLPTR)));
        delGoodsAction->setText(QApplication::translate("MainWindow", "&Usu\305\204", Q_NULLPTR));
        delGoodsAction->setIconText(QApplication::translate("MainWindow", "Usu\305\204", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        delGoodsAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+U", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        delGoodsAction->setProperty("name", QVariant(QApplication::translate("MainWindow", "towaryUsunAction", Q_NULLPTR)));
        addGoodsAction->setText(QApplication::translate("MainWindow", "&Dodaj", Q_NULLPTR));
        addGoodsAction->setIconText(QApplication::translate("MainWindow", "Towar/Us\305\202uga", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        addGoodsAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+T", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        addGoodsAction->setProperty("name", QVariant(QApplication::translate("MainWindow", "towaryDodajAction", Q_NULLPTR)));
        fileExportEDIAction->setText(QApplication::translate("MainWindow", "&Export do EDI", Q_NULLPTR));
        fileExportEDIAction->setIconText(QApplication::translate("MainWindow", "Export do EDI", Q_NULLPTR));
        fileExportEDIAction->setProperty("name", QVariant(QApplication::translate("MainWindow", "plikExportEDIAction", Q_NULLPTR)));
        fileExport_pdfAction->setText(QApplication::translate("MainWindow", "Export do &PDF", Q_NULLPTR));
        fileExport_pdfAction->setIconText(QApplication::translate("MainWindow", "Export do PDF", Q_NULLPTR));
        fileExport_pdfAction->setProperty("name", QVariant(QApplication::translate("MainWindow", "plikExport_pdfAction", Q_NULLPTR)));
        fileExport_XMLAction->setText(QApplication::translate("MainWindow", "Exp&ort do XML", Q_NULLPTR));
        fileExport_XMLAction->setIconText(QApplication::translate("MainWindow", "Export do XML", Q_NULLPTR));
        fileExport_XMLAction->setProperty("name", QVariant(QApplication::translate("MainWindow", "plikExport_XMLAction", Q_NULLPTR)));
        fileImport_EDIAction->setText(QApplication::translate("MainWindow", "&Import EDI", Q_NULLPTR));
        fileImport_EDIAction->setIconText(QApplication::translate("MainWindow", "Import EDI", Q_NULLPTR));
        fileImport_EDIAction->setProperty("name", QVariant(QApplication::translate("MainWindow", "plikImport_EDIAction", Q_NULLPTR)));
        fileImport_XMLAction->setText(QApplication::translate("MainWindow", "Import &XML", Q_NULLPTR));
        fileImport_XMLAction->setIconText(QApplication::translate("MainWindow", "Import XML", Q_NULLPTR));
        fileImport_XMLAction->setProperty("name", QVariant(QApplication::translate("MainWindow", "plikImport_XMLAction", Q_NULLPTR)));
        invoiceCorrAction->setText(QApplication::translate("MainWindow", "Faktura &koryguj\304\205ca", Q_NULLPTR));
        invoiceCorrAction->setIconText(QApplication::translate("MainWindow", "Nowa korekta", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        invoiceCorrAction->setShortcut(QApplication::translate("MainWindow", "K", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        invoiceCorrAction->setProperty("name", QVariant(QApplication::translate("MainWindow", "fakturyKorektaAction", Q_NULLPTR)));
        invoiceProFormaAction->setText(QApplication::translate("MainWindow", "Faktura &Pro Forma", Q_NULLPTR));
        invoiceProFormaAction->setIconText(QApplication::translate("MainWindow", "Pro forma", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        invoiceProFormaAction->setShortcut(QApplication::translate("MainWindow", "P", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        invoiceProFormaAction->setProperty("name", QVariant(QApplication::translate("MainWindow", "fakturyPFormaAction", Q_NULLPTR)));
        nextPageAction->setIconText(QApplication::translate("MainWindow", "Action", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        nextPageAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+PgDown", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        nextPageAction->setProperty("name", QVariant(QApplication::translate("MainWindow", "nextPageAction", Q_NULLPTR)));
        prevPageAction->setIconText(QApplication::translate("MainWindow", "Action_2", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        prevPageAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+PgUp", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        prevPageAction->setProperty("name", QVariant(QApplication::translate("MainWindow", "prevPageAction", Q_NULLPTR)));
        actionBug->setText(QApplication::translate("MainWindow", "&Zg\305\202o\305\233 b\305\202\304\205d", Q_NULLPTR));
        invoiceDuplAction->setText(QApplication::translate("MainWindow", "&Duplikat faktury", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        invoiceDuplAction->setShortcut(QApplication::translate("MainWindow", "D", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        invoiceGrossAction->setText(QApplication::translate("MainWindow", "Faktura &Brutto", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        invoiceGrossAction->setShortcut(QApplication::translate("MainWindow", "B", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        invoiceBillAction->setText(QApplication::translate("MainWindow", "&Rachunek", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        invoiceBillAction->setShortcut(QApplication::translate("MainWindow", "R", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        action_Qt->setText(QApplication::translate("MainWindow", "O &Qt", Q_NULLPTR));
        actionPrintBuyer->setText(QApplication::translate("MainWindow", "D&rukuj", Q_NULLPTR));
        invoiceRRAction->setText(QApplication::translate("MainWindow", "F&aktura RR", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        invoiceRRAction->setShortcut(QApplication::translate("MainWindow", "X", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionCreateBackup->setText(QApplication::translate("MainWindow", "&Stw\303\263rz kopi\304\231 zapasow\304\205", Q_NULLPTR));
        actionLoadBackup->setText(QApplication::translate("MainWindow", "&Wczytaj kopi\304\231 zapasow\304\205", Q_NULLPTR));
        sendEmailAction->setText(QApplication::translate("MainWindow", "&Wy\305\233lij", Q_NULLPTR));
        WZAction->setText(QApplication::translate("MainWindow", "&WZ", Q_NULLPTR));
        warehouseEdAction->setText(QApplication::translate("MainWindow", "&Edytuj", Q_NULLPTR));
        warehouseDelAction->setText(QApplication::translate("MainWindow", "&Usu\305\204", Q_NULLPTR));
        RWAction->setText(QApplication::translate("MainWindow", "RW", Q_NULLPTR));
        organizer->setTabText(organizer->indexOf(tab), QApplication::translate("MainWindow", "Tab 1", Q_NULLPTR));
        organizer->setTabText(organizer->indexOf(tab_2), QApplication::translate("MainWindow", "Tab 2", Q_NULLPTR));
        textLabel1->setText(QApplication::translate("MainWindow", "Wy\305\233wietl od:", Q_NULLPTR));
        filtrStart->setDisplayFormat(QApplication::translate("MainWindow", "dd/MM/yyyy", Q_NULLPTR));
        textLabel2->setText(QApplication::translate("MainWindow", "do:", Q_NULLPTR));
        filtrEnd->setDisplayFormat(QApplication::translate("MainWindow", "MM/dd/yyyy", Q_NULLPTR));
        applyFiltrBtn->setText(QApplication::translate("MainWindow", "Zastosuj", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tableH->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "Nazwa pliku", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tableH->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "Symbol", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = tableH->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "Data", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = tableH->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "Typ", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = tableH->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "Nabywca", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem5 = tableH->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("MainWindow", "NIP", Q_NULLPTR));
        tabWidget2->setTabText(tabWidget2->indexOf(invoiceTab), QApplication::translate("MainWindow", "Historia faktur", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Wy\305\233wietl od: ", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "do: ", Q_NULLPTR));
        findWarehouses->setText(QApplication::translate("MainWindow", "Zastosuj", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem6 = tableM->horizontalHeaderItem(0);
        ___qtablewidgetitem6->setText(QApplication::translate("MainWindow", "Nazwa pliku", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem7 = tableM->horizontalHeaderItem(1);
        ___qtablewidgetitem7->setText(QApplication::translate("MainWindow", "Symbol", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem8 = tableM->horizontalHeaderItem(2);
        ___qtablewidgetitem8->setText(QApplication::translate("MainWindow", "Data", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem9 = tableM->horizontalHeaderItem(3);
        ___qtablewidgetitem9->setText(QApplication::translate("MainWindow", "Typ", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem10 = tableM->horizontalHeaderItem(4);
        ___qtablewidgetitem10->setText(QApplication::translate("MainWindow", "Nabywca", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem11 = tableM->horizontalHeaderItem(5);
        ___qtablewidgetitem11->setText(QApplication::translate("MainWindow", "NIP", Q_NULLPTR));
        tabWidget2->setTabText(tabWidget2->indexOf(warehouseTab), QApplication::translate("MainWindow", "Historia magazynu", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem12 = tableK->horizontalHeaderItem(0);
        ___qtablewidgetitem12->setText(QApplication::translate("MainWindow", "Nazwa", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem13 = tableK->horizontalHeaderItem(1);
        ___qtablewidgetitem13->setText(QApplication::translate("MainWindow", "Typ", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem14 = tableK->horizontalHeaderItem(2);
        ___qtablewidgetitem14->setText(QApplication::translate("MainWindow", "Miasto", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem15 = tableK->horizontalHeaderItem(3);
        ___qtablewidgetitem15->setText(QApplication::translate("MainWindow", "Adres", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem16 = tableK->horizontalHeaderItem(4);
        ___qtablewidgetitem16->setText(QApplication::translate("MainWindow", "Telefon", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem17 = tableK->horizontalHeaderItem(5);
        ___qtablewidgetitem17->setText(QApplication::translate("MainWindow", "Email", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem18 = tableK->horizontalHeaderItem(6);
        ___qtablewidgetitem18->setText(QApplication::translate("MainWindow", "Strona www", Q_NULLPTR));
        tabWidget2->setTabText(tabWidget2->indexOf(buyerTab), QApplication::translate("MainWindow", "Kontrahenci", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem19 = tableT->horizontalHeaderItem(0);
        ___qtablewidgetitem19->setText(QApplication::translate("MainWindow", "Index", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem20 = tableT->horizontalHeaderItem(1);
        ___qtablewidgetitem20->setText(QApplication::translate("MainWindow", "Nazwa", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem21 = tableT->horizontalHeaderItem(2);
        ___qtablewidgetitem21->setText(QApplication::translate("MainWindow", "Skr\303\263t", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem22 = tableT->horizontalHeaderItem(3);
        ___qtablewidgetitem22->setText(QApplication::translate("MainWindow", "Kod", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem23 = tableT->horizontalHeaderItem(4);
        ___qtablewidgetitem23->setText(QApplication::translate("MainWindow", "PKWiU", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem24 = tableT->horizontalHeaderItem(5);
        ___qtablewidgetitem24->setText(QApplication::translate("MainWindow", "Typ", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem25 = tableT->horizontalHeaderItem(6);
        ___qtablewidgetitem25->setText(QApplication::translate("MainWindow", "Jedn.", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem26 = tableT->horizontalHeaderItem(7);
        ___qtablewidgetitem26->setText(QApplication::translate("MainWindow", "Netto1", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem27 = tableT->horizontalHeaderItem(8);
        ___qtablewidgetitem27->setText(QApplication::translate("MainWindow", "Netto2", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem28 = tableT->horizontalHeaderItem(9);
        ___qtablewidgetitem28->setText(QApplication::translate("MainWindow", "Netto3", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem29 = tableT->horizontalHeaderItem(10);
        ___qtablewidgetitem29->setText(QApplication::translate("MainWindow", "Netto4", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem30 = tableT->horizontalHeaderItem(11);
        ___qtablewidgetitem30->setText(QApplication::translate("MainWindow", "Stawka VAT", Q_NULLPTR));
        tabWidget2->setTabText(tabWidget2->indexOf(goodsTab), QApplication::translate("MainWindow", "Towary/Us\305\202ugi", Q_NULLPTR));
        hideOrganizer->setText(QApplication::translate("MainWindow", "<<", Q_NULLPTR));
        plikAct->setTitle(QApplication::translate("MainWindow", "P&rogram", Q_NULLPTR));
        fakturyAct->setTitle(QApplication::translate("MainWindow", "&Faktury", Q_NULLPTR));
        buyersAct->setTitle(QApplication::translate("MainWindow", "&Kontrahenci", Q_NULLPTR));
        goodsAct->setTitle(QApplication::translate("MainWindow", "&Towary", Q_NULLPTR));
        helpAct->setTitle(QApplication::translate("MainWindow", "Po&moc", Q_NULLPTR));
        menuPlugins->setTitle(QApplication::translate("MainWindow", "Dodatk&i", Q_NULLPTR));
        warehouseMenu->setTitle(QApplication::translate("MainWindow", "Ma&gazyn", Q_NULLPTR));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
