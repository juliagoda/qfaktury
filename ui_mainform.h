/********************************************************************************
** Form generated from reading ui file 'mainform.ui'
**
** Created: Thu Nov 29 01:25:38 2007
**      by: Qt User Interface Compiler version 4.3.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_MAINFORM_H
#define UI_MAINFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QTabWidget>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

class Ui_Form1
{
public:
    QAction *plikKreatorAction;
    QAction *plikDrukujAction;
    QAction *fakturyUsunAction;
    QAction *fakturyDodajAction;
    QAction *kontrahenciDodajAction;
    QAction *kontrahenciUsunAction;
    QAction *kontrahenciEdycjaAction;
    QAction *pomocO_QtAction;
    QAction *plikKoniecAction;
    QAction *fakturyEdAction;
    QAction *plikDane_firmyAction;
    QAction *przelewyDrukuj_Action;
    QAction *pomocO_programieAction;
    QAction *plikUstawieniaAction;
    QAction *przelewyZUS;
    QAction *przelewyUSAction;
    QAction *pomocPomocAction;
    QAction *separatornew_itemAction;
    QAction *towaryEdycjaAction;
    QAction *towaryUsunAction;
    QAction *towaryDodajAction;
    QAction *plikExportEDIAction;
    QAction *plikExport_pdfAction;
    QAction *plikExport_XMLAction;
    QAction *plikImport_EDIAction;
    QAction *plikImport_XMLAction;
    QAction *fakturyKorektaAction;
    QAction *fakturyPFormaAction;
    QAction *nextPageAction;
    QAction *prevPageAction;
    QWidget *widget;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget2;
    QWidget *tab1;
    QGridLayout *gridLayout1;
    QTableWidget *tableH;
    QWidget *tab2;
    QGridLayout *gridLayout2;
    QTableWidget *tableK;
    QWidget *TabPage;
    QGridLayout *gridLayout3;
    QTableWidget *tableT;
    QMenuBar *MenuBarEditor;
    QMenu *Plik;
    QMenu *Faktury;
    QMenu *Kontrahenci;
    QMenu *Towary;
    QMenu *Pomoc;

    void setupUi(QMainWindow *Form1)
    {
    if (Form1->objectName().isEmpty())
        Form1->setObjectName(QString::fromUtf8("Form1"));
    Form1->resize(711, 488);
    Form1->setWindowIcon(QIcon());
    plikKreatorAction = new QAction(Form1);
    plikKreatorAction->setObjectName(QString::fromUtf8("plikKreatorAction"));
    plikKreatorAction->setIcon(QIcon(QString::fromUtf8("image1")));
    plikKreatorAction->setVisible(false);
    plikDrukujAction = new QAction(Form1);
    plikDrukujAction->setObjectName(QString::fromUtf8("plikDrukujAction"));
    fakturyUsunAction = new QAction(Form1);
    fakturyUsunAction->setObjectName(QString::fromUtf8("fakturyUsunAction"));
    fakturyDodajAction = new QAction(Form1);
    fakturyDodajAction->setObjectName(QString::fromUtf8("fakturyDodajAction"));
    kontrahenciDodajAction = new QAction(Form1);
    kontrahenciDodajAction->setObjectName(QString::fromUtf8("kontrahenciDodajAction"));
    kontrahenciDodajAction->setIcon(QIcon(QString::fromUtf8("image2")));
    kontrahenciUsunAction = new QAction(Form1);
    kontrahenciUsunAction->setObjectName(QString::fromUtf8("kontrahenciUsunAction"));
    kontrahenciUsunAction->setIcon(QIcon(QString::fromUtf8("image3")));
    kontrahenciEdycjaAction = new QAction(Form1);
    kontrahenciEdycjaAction->setObjectName(QString::fromUtf8("kontrahenciEdycjaAction"));
    kontrahenciEdycjaAction->setIcon(QIcon(QString::fromUtf8("image4")));
    pomocO_QtAction = new QAction(Form1);
    pomocO_QtAction->setObjectName(QString::fromUtf8("pomocO_QtAction"));
    pomocO_QtAction->setIcon(QIcon(QString::fromUtf8("image5")));
    plikKoniecAction = new QAction(Form1);
    plikKoniecAction->setObjectName(QString::fromUtf8("plikKoniecAction"));
    plikKoniecAction->setIcon(QIcon(QString::fromUtf8("image6")));
    fakturyEdAction = new QAction(Form1);
    fakturyEdAction->setObjectName(QString::fromUtf8("fakturyEdAction"));
    plikDane_firmyAction = new QAction(Form1);
    plikDane_firmyAction->setObjectName(QString::fromUtf8("plikDane_firmyAction"));
    plikDane_firmyAction->setIcon(QIcon(QString::fromUtf8("image7")));
    przelewyDrukuj_Action = new QAction(Form1);
    przelewyDrukuj_Action->setObjectName(QString::fromUtf8("przelewyDrukuj_Action"));
    pomocO_programieAction = new QAction(Form1);
    pomocO_programieAction->setObjectName(QString::fromUtf8("pomocO_programieAction"));
    pomocO_programieAction->setIcon(QIcon(QString::fromUtf8("image8")));
    plikUstawieniaAction = new QAction(Form1);
    plikUstawieniaAction->setObjectName(QString::fromUtf8("plikUstawieniaAction"));
    plikUstawieniaAction->setIcon(QIcon(QString::fromUtf8("image9")));
    przelewyZUS = new QAction(Form1);
    przelewyZUS->setObjectName(QString::fromUtf8("przelewyZUS"));
    przelewyZUS->setIcon(QIcon(QString::fromUtf8("image10")));
    przelewyUSAction = new QAction(Form1);
    przelewyUSAction->setObjectName(QString::fromUtf8("przelewyUSAction"));
    przelewyUSAction->setIcon(QIcon(QString::fromUtf8("image11")));
    pomocPomocAction = new QAction(Form1);
    pomocPomocAction->setObjectName(QString::fromUtf8("pomocPomocAction"));
    separatornew_itemAction = new QAction(Form1);
    separatornew_itemAction->setObjectName(QString::fromUtf8("separatornew_itemAction"));
    towaryEdycjaAction = new QAction(Form1);
    towaryEdycjaAction->setObjectName(QString::fromUtf8("towaryEdycjaAction"));
    towaryUsunAction = new QAction(Form1);
    towaryUsunAction->setObjectName(QString::fromUtf8("towaryUsunAction"));
    towaryDodajAction = new QAction(Form1);
    towaryDodajAction->setObjectName(QString::fromUtf8("towaryDodajAction"));
    plikExportEDIAction = new QAction(Form1);
    plikExportEDIAction->setObjectName(QString::fromUtf8("plikExportEDIAction"));
    plikExportEDIAction->setVisible(false);
    plikExport_pdfAction = new QAction(Form1);
    plikExport_pdfAction->setObjectName(QString::fromUtf8("plikExport_pdfAction"));
    plikExport_pdfAction->setVisible(false);
    plikExport_XMLAction = new QAction(Form1);
    plikExport_XMLAction->setObjectName(QString::fromUtf8("plikExport_XMLAction"));
    plikExport_XMLAction->setVisible(false);
    plikImport_EDIAction = new QAction(Form1);
    plikImport_EDIAction->setObjectName(QString::fromUtf8("plikImport_EDIAction"));
    plikImport_EDIAction->setVisible(false);
    plikImport_XMLAction = new QAction(Form1);
    plikImport_XMLAction->setObjectName(QString::fromUtf8("plikImport_XMLAction"));
    plikImport_XMLAction->setVisible(false);
    fakturyKorektaAction = new QAction(Form1);
    fakturyKorektaAction->setObjectName(QString::fromUtf8("fakturyKorektaAction"));
    fakturyPFormaAction = new QAction(Form1);
    fakturyPFormaAction->setObjectName(QString::fromUtf8("fakturyPFormaAction"));
    nextPageAction = new QAction(Form1);
    nextPageAction->setObjectName(QString::fromUtf8("nextPageAction"));
    prevPageAction = new QAction(Form1);
    prevPageAction->setObjectName(QString::fromUtf8("prevPageAction"));
    widget = new QWidget(Form1);
    widget->setObjectName(QString::fromUtf8("widget"));
    gridLayout = new QGridLayout(widget);
    gridLayout->setSpacing(6);
    gridLayout->setMargin(11);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    tabWidget2 = new QTabWidget(widget);
    tabWidget2->setObjectName(QString::fromUtf8("tabWidget2"));
    tab1 = new QWidget();
    tab1->setObjectName(QString::fromUtf8("tab1"));
    gridLayout1 = new QGridLayout(tab1);
    gridLayout1->setSpacing(6);
    gridLayout1->setMargin(11);
    gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
    tableH = new QTableWidget(tab1);
    tableH->setObjectName(QString::fromUtf8("tableH"));
    tableH->setSelectionMode(QAbstractItemView::ExtendedSelection);
    tableH->setProperty("numRows", QVariant(0));
    tableH->setProperty("numCols", QVariant(6));
    tableH->setProperty("readOnly", QVariant(true));
    tableH->setProperty("sorting", QVariant(false));

    gridLayout1->addWidget(tableH, 0, 0, 1, 1);

    tabWidget2->addTab(tab1, QString());
    tab2 = new QWidget();
    tab2->setObjectName(QString::fromUtf8("tab2"));
    gridLayout2 = new QGridLayout(tab2);
    gridLayout2->setSpacing(6);
    gridLayout2->setMargin(11);
    gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
    tableK = new QTableWidget(tab2);
    tableK->setObjectName(QString::fromUtf8("tableK"));
    tableK->setSelectionMode(QAbstractItemView::ExtendedSelection);
    tableK->setProperty("numRows", QVariant(0));
    tableK->setProperty("numCols", QVariant(5));
    tableK->setProperty("readOnly", QVariant(true));
    tableK->setProperty("sorting", QVariant(false));

    gridLayout2->addWidget(tableK, 0, 0, 1, 1);

    tabWidget2->addTab(tab2, QString());
    TabPage = new QWidget();
    TabPage->setObjectName(QString::fromUtf8("TabPage"));
    gridLayout3 = new QGridLayout(TabPage);
    gridLayout3->setSpacing(6);
    gridLayout3->setMargin(11);
    gridLayout3->setObjectName(QString::fromUtf8("gridLayout3"));
    tableT = new QTableWidget(TabPage);
    tableT->setObjectName(QString::fromUtf8("tableT"));
    tableT->setSelectionMode(QAbstractItemView::ExtendedSelection);
    tableT->setProperty("numRows", QVariant(0));
    tableT->setProperty("numCols", QVariant(12));
    tableT->setProperty("readOnly", QVariant(true));
    tableT->setProperty("sorting", QVariant(false));

    gridLayout3->addWidget(tableT, 0, 0, 1, 1);

    tabWidget2->addTab(TabPage, QString());

    gridLayout->addWidget(tabWidget2, 0, 0, 1, 1);

    Form1->setCentralWidget(widget);
    MenuBarEditor = new QMenuBar(Form1);
    MenuBarEditor->setObjectName(QString::fromUtf8("MenuBarEditor"));
    MenuBarEditor->setGeometry(QRect(0, 0, 711, 25));
    Plik = new QMenu(MenuBarEditor);
    Plik->setObjectName(QString::fromUtf8("Plik"));
    Faktury = new QMenu(MenuBarEditor);
    Faktury->setObjectName(QString::fromUtf8("Faktury"));
    Kontrahenci = new QMenu(MenuBarEditor);
    Kontrahenci->setObjectName(QString::fromUtf8("Kontrahenci"));
    Towary = new QMenu(MenuBarEditor);
    Towary->setObjectName(QString::fromUtf8("Towary"));
    Pomoc = new QMenu(MenuBarEditor);
    Pomoc->setObjectName(QString::fromUtf8("Pomoc"));
    Form1->setMenuBar(MenuBarEditor);

    MenuBarEditor->addAction(Plik->menuAction());
    MenuBarEditor->addAction(Faktury->menuAction());
    MenuBarEditor->addAction(Kontrahenci->menuAction());
    MenuBarEditor->addAction(Towary->menuAction());
    MenuBarEditor->addAction(Pomoc->menuAction());
    MenuBarEditor->addSeparator();
    Plik->addAction(plikKreatorAction);
    Plik->addAction(plikDane_firmyAction);
    Plik->addAction(plikUstawieniaAction);
    Plik->addSeparator();
    Plik->addAction(plikExportEDIAction);
    Plik->addAction(plikExport_pdfAction);
    Plik->addAction(plikExport_XMLAction);
    Plik->addAction(plikImport_EDIAction);
    Plik->addAction(plikImport_XMLAction);
    Plik->addAction(plikKoniecAction);
    Faktury->addAction(fakturyDodajAction);
    Faktury->addAction(fakturyPFormaAction);
    Faktury->addAction(fakturyKorektaAction);
    Faktury->addSeparator();
    Faktury->addAction(fakturyUsunAction);
    Faktury->addAction(fakturyEdAction);
    Kontrahenci->addAction(kontrahenciDodajAction);
    Kontrahenci->addAction(kontrahenciUsunAction);
    Kontrahenci->addAction(kontrahenciEdycjaAction);
    Towary->addAction(towaryDodajAction);
    Towary->addAction(towaryUsunAction);
    Towary->addAction(towaryEdycjaAction);
    Pomoc->addAction(pomocO_programieAction);
    Pomoc->addAction(pomocPomocAction);

    retranslateUi(Form1);
    QObject::connect(plikDane_firmyAction, SIGNAL(activated()), Form1, SLOT(daneFirmyClick()));
    QObject::connect(plikKreatorAction, SIGNAL(activated()), Form1, SLOT(kretorClick()));
    QObject::connect(plikKoniecAction, SIGNAL(activated()), Form1, SLOT(close()));
    QObject::connect(kontrahenciDodajAction, SIGNAL(activated()), Form1, SLOT(kontrClick()));
    QObject::connect(kontrahenciUsunAction, SIGNAL(activated()), Form1, SLOT(kontrDel()));
    QObject::connect(kontrahenciEdycjaAction, SIGNAL(activated()), Form1, SLOT(kontrEd()));
    QObject::connect(fakturyDodajAction, SIGNAL(activated()), Form1, SLOT(newFra()));
    QObject::connect(fakturyUsunAction, SIGNAL(activated()), Form1, SLOT(delFHist()));
    QObject::connect(fakturyEdAction, SIGNAL(activated()), Form1, SLOT(editFHist()));
    QObject::connect(tableH, SIGNAL(doubleClicked(int,int,int,QPoint)), Form1, SLOT(editFHist()));
    QObject::connect(pomocO_QtAction, SIGNAL(activated()), Form1, SLOT(aboutQt()));
    QObject::connect(pomocO_programieAction, SIGNAL(activated()), Form1, SLOT(oProg()));
    QObject::connect(tableK, SIGNAL(doubleClicked(int,int,int,QPoint)), Form1, SLOT(kontrEd()));
    QObject::connect(plikUstawieniaAction, SIGNAL(activated()), Form1, SLOT(settClick()));
    QObject::connect(tabWidget2, SIGNAL(currentChanged(QWidget*)), Form1, SLOT(tabChanged(QWidget*)));
    QObject::connect(pomocPomocAction, SIGNAL(activated()), Form1, SLOT(pomoc()));
    QObject::connect(towaryDodajAction, SIGNAL(activated()), Form1, SLOT(towaryDodaj()));
    QObject::connect(towaryEdycjaAction, SIGNAL(activated()), Form1, SLOT(towaryEdycja()));
    QObject::connect(towaryUsunAction, SIGNAL(activated()), Form1, SLOT(towaryUsun()));
    QObject::connect(tableT, SIGNAL(doubleClicked(int,int,int,QPoint)), Form1, SLOT(towaryEdycja()));
    QObject::connect(fakturyKorektaAction, SIGNAL(activated()), Form1, SLOT(newKor()));
    QObject::connect(fakturyPFormaAction, SIGNAL(activated()), Form1, SLOT(newPForm()));
    QObject::connect(prevPageAction, SIGNAL(activated()), Form1, SLOT(prevPage()));
    QObject::connect(nextPageAction, SIGNAL(activated()), Form1, SLOT(nextPage()));

    tabWidget2->setCurrentIndex(0);


    QMetaObject::connectSlotsByName(Form1);
    } // setupUi

    void retranslateUi(QMainWindow *Form1)
    {
    Form1->setWindowTitle(QApplication::translate("Form1", "QFaktury", 0, QApplication::UnicodeUTF8));
    plikKreatorAction->setText(QApplication::translate("Form1", "Kreator", 0, QApplication::UnicodeUTF8));
    plikKreatorAction->setIconText(QApplication::translate("Form1", "Kreator", 0, QApplication::UnicodeUTF8));
    plikKreatorAction->setShortcut(QApplication::translate("Form1", "Ctrl+N", 0, QApplication::UnicodeUTF8));
    plikKreatorAction->setProperty("name", QVariant(QApplication::translate("Form1", "plikKreatorAction", 0, QApplication::UnicodeUTF8)));
    plikDrukujAction->setText(QApplication::translate("Form1", "Drukuj", 0, QApplication::UnicodeUTF8));
    plikDrukujAction->setIconText(QApplication::translate("Form1", "Drukuj", 0, QApplication::UnicodeUTF8));
    plikDrukujAction->setProperty("name", QVariant(QApplication::translate("Form1", "plikDrukujAction", 0, QApplication::UnicodeUTF8)));
    fakturyUsunAction->setText(QApplication::translate("Form1", "Usu\305\204", 0, QApplication::UnicodeUTF8));
    fakturyUsunAction->setIconText(QApplication::translate("Form1", "Usu\305\204", 0, QApplication::UnicodeUTF8));
    fakturyUsunAction->setShortcut(QApplication::translate("Form1", "Alt+D", 0, QApplication::UnicodeUTF8));
    fakturyUsunAction->setProperty("name", QVariant(QApplication::translate("Form1", "fakturyUsunAction", 0, QApplication::UnicodeUTF8)));
    fakturyDodajAction->setText(QApplication::translate("Form1", "Nowa faktura", 0, QApplication::UnicodeUTF8));
    fakturyDodajAction->setIconText(QApplication::translate("Form1", "Nowa faktura", 0, QApplication::UnicodeUTF8));
    fakturyDodajAction->setShortcut(QApplication::translate("Form1", "F5", 0, QApplication::UnicodeUTF8));
    fakturyDodajAction->setProperty("name", QVariant(QApplication::translate("Form1", "fakturyDodajAction", 0, QApplication::UnicodeUTF8)));
    kontrahenciDodajAction->setText(QApplication::translate("Form1", "Dodaj", 0, QApplication::UnicodeUTF8));
    kontrahenciDodajAction->setIconText(QApplication::translate("Form1", "Dodaj", 0, QApplication::UnicodeUTF8));
    kontrahenciDodajAction->setShortcut(QApplication::translate("Form1", "Ctrl+K", 0, QApplication::UnicodeUTF8));
    kontrahenciDodajAction->setProperty("name", QVariant(QApplication::translate("Form1", "kontrahenciDodajAction", 0, QApplication::UnicodeUTF8)));
    kontrahenciUsunAction->setText(QApplication::translate("Form1", "Usu\305\204", 0, QApplication::UnicodeUTF8));
    kontrahenciUsunAction->setIconText(QApplication::translate("Form1", "Usu\305\204", 0, QApplication::UnicodeUTF8));
    kontrahenciUsunAction->setShortcut(QApplication::translate("Form1", "Ctrl+D", 0, QApplication::UnicodeUTF8));
    kontrahenciUsunAction->setProperty("name", QVariant(QApplication::translate("Form1", "kontrahenciUsunAction", 0, QApplication::UnicodeUTF8)));
    kontrahenciEdycjaAction->setText(QApplication::translate("Form1", "Edycja", 0, QApplication::UnicodeUTF8));
    kontrahenciEdycjaAction->setIconText(QApplication::translate("Form1", "Edycja", 0, QApplication::UnicodeUTF8));
    kontrahenciEdycjaAction->setShortcut(QApplication::translate("Form1", "Ctrl+E", 0, QApplication::UnicodeUTF8));
    kontrahenciEdycjaAction->setProperty("name", QVariant(QApplication::translate("Form1", "kontrahenciEdycjaAction", 0, QApplication::UnicodeUTF8)));
    pomocO_QtAction->setText(QApplication::translate("Form1", "O Qt", 0, QApplication::UnicodeUTF8));
    pomocO_QtAction->setIconText(QApplication::translate("Form1", "O &Qt", 0, QApplication::UnicodeUTF8));
    pomocO_QtAction->setProperty("name", QVariant(QApplication::translate("Form1", "pomocO_QtAction", 0, QApplication::UnicodeUTF8)));
    plikKoniecAction->setText(QApplication::translate("Form1", "Koniec", 0, QApplication::UnicodeUTF8));
    plikKoniecAction->setIconText(QApplication::translate("Form1", "Koniec", 0, QApplication::UnicodeUTF8));
    plikKoniecAction->setShortcut(QApplication::translate("Form1", "Q", 0, QApplication::UnicodeUTF8));
    plikKoniecAction->setProperty("name", QVariant(QApplication::translate("Form1", "plikKoniecAction", 0, QApplication::UnicodeUTF8)));
    fakturyEdAction->setText(QApplication::translate("Form1", "Edytuj", 0, QApplication::UnicodeUTF8));
    fakturyEdAction->setIconText(QApplication::translate("Form1", "Edytuj", 0, QApplication::UnicodeUTF8));
    fakturyEdAction->setShortcut(QApplication::translate("Form1", "F8", 0, QApplication::UnicodeUTF8));
    fakturyEdAction->setProperty("name", QVariant(QApplication::translate("Form1", "fakturyEdAction", 0, QApplication::UnicodeUTF8)));
    plikDane_firmyAction->setText(QApplication::translate("Form1", "Dane firmy", 0, QApplication::UnicodeUTF8));
    plikDane_firmyAction->setIconText(QApplication::translate("Form1", "Dane firmy", 0, QApplication::UnicodeUTF8));
    plikDane_firmyAction->setShortcut(QApplication::translate("Form1", "Ctrl+I", 0, QApplication::UnicodeUTF8));
    plikDane_firmyAction->setProperty("name", QVariant(QApplication::translate("Form1", "plikDane_firmyAction", 0, QApplication::UnicodeUTF8)));
    przelewyDrukuj_Action->setText(QApplication::translate("Form1", "Drukuj ", 0, QApplication::UnicodeUTF8));
    przelewyDrukuj_Action->setIconText(QApplication::translate("Form1", "Drukuj ", 0, QApplication::UnicodeUTF8));
    przelewyDrukuj_Action->setShortcut(QApplication::translate("Form1", "F2", 0, QApplication::UnicodeUTF8));
    przelewyDrukuj_Action->setProperty("name", QVariant(QApplication::translate("Form1", "przelewyDrukuj_Action", 0, QApplication::UnicodeUTF8)));
    pomocO_programieAction->setText(QApplication::translate("Form1", "O programie", 0, QApplication::UnicodeUTF8));
    pomocO_programieAction->setIconText(QApplication::translate("Form1", "O programie", 0, QApplication::UnicodeUTF8));
    pomocO_programieAction->setProperty("name", QVariant(QApplication::translate("Form1", "pomocO_programieAction", 0, QApplication::UnicodeUTF8)));
    plikUstawieniaAction->setText(QApplication::translate("Form1", "Ustawienia", 0, QApplication::UnicodeUTF8));
    plikUstawieniaAction->setIconText(QApplication::translate("Form1", "Ustawienia", 0, QApplication::UnicodeUTF8));
    plikUstawieniaAction->setProperty("name", QVariant(QApplication::translate("Form1", "plikUstawieniaAction", 0, QApplication::UnicodeUTF8)));
    przelewyZUS->setText(QApplication::translate("Form1", "Nowy (ZUS)", 0, QApplication::UnicodeUTF8));
    przelewyZUS->setIconText(QApplication::translate("Form1", "Nowy (ZUS)", 0, QApplication::UnicodeUTF8));
    przelewyZUS->setProperty("name", QVariant(QApplication::translate("Form1", "przelewyZUS", 0, QApplication::UnicodeUTF8)));
    przelewyUSAction->setText(QApplication::translate("Form1", "Nowy (US)", 0, QApplication::UnicodeUTF8));
    przelewyUSAction->setIconText(QApplication::translate("Form1", "Nowy (US)", 0, QApplication::UnicodeUTF8));
    przelewyUSAction->setProperty("name", QVariant(QApplication::translate("Form1", "przelewyUSAction", 0, QApplication::UnicodeUTF8)));
    pomocPomocAction->setText(QApplication::translate("Form1", "Pomoc", 0, QApplication::UnicodeUTF8));
    pomocPomocAction->setIconText(QApplication::translate("Form1", "Pomoc", 0, QApplication::UnicodeUTF8));
    pomocPomocAction->setProperty("name", QVariant(QApplication::translate("Form1", "pomocPomocAction", 0, QApplication::UnicodeUTF8)));
    separatornew_itemAction->setText(QApplication::translate("Form1", "new item", 0, QApplication::UnicodeUTF8));
    separatornew_itemAction->setIconText(QApplication::translate("Form1", "new item", 0, QApplication::UnicodeUTF8));
    separatornew_itemAction->setProperty("name", QVariant(QApplication::translate("Form1", "separatornew_itemAction", 0, QApplication::UnicodeUTF8)));
    towaryEdycjaAction->setText(QApplication::translate("Form1", "Edycja", 0, QApplication::UnicodeUTF8));
    towaryEdycjaAction->setIconText(QApplication::translate("Form1", "Edycja", 0, QApplication::UnicodeUTF8));
    towaryEdycjaAction->setShortcut(QApplication::translate("Form1", "Ctrl+M", 0, QApplication::UnicodeUTF8));
    towaryEdycjaAction->setProperty("name", QVariant(QApplication::translate("Form1", "towaryEdycjaAction", 0, QApplication::UnicodeUTF8)));
    towaryUsunAction->setText(QApplication::translate("Form1", "Usu\305\204", 0, QApplication::UnicodeUTF8));
    towaryUsunAction->setIconText(QApplication::translate("Form1", "Usu\305\204", 0, QApplication::UnicodeUTF8));
    towaryUsunAction->setShortcut(QApplication::translate("Form1", "Ctrl+U", 0, QApplication::UnicodeUTF8));
    towaryUsunAction->setProperty("name", QVariant(QApplication::translate("Form1", "towaryUsunAction", 0, QApplication::UnicodeUTF8)));
    towaryDodajAction->setText(QApplication::translate("Form1", "Dodaj", 0, QApplication::UnicodeUTF8));
    towaryDodajAction->setIconText(QApplication::translate("Form1", "Dodaj", 0, QApplication::UnicodeUTF8));
    towaryDodajAction->setShortcut(QApplication::translate("Form1", "Ctrl+T", 0, QApplication::UnicodeUTF8));
    towaryDodajAction->setProperty("name", QVariant(QApplication::translate("Form1", "towaryDodajAction", 0, QApplication::UnicodeUTF8)));
    plikExportEDIAction->setText(QApplication::translate("Form1", "Export do EDI", 0, QApplication::UnicodeUTF8));
    plikExportEDIAction->setIconText(QApplication::translate("Form1", "Export do EDI", 0, QApplication::UnicodeUTF8));
    plikExportEDIAction->setProperty("name", QVariant(QApplication::translate("Form1", "plikExportEDIAction", 0, QApplication::UnicodeUTF8)));
    plikExport_pdfAction->setText(QApplication::translate("Form1", "Export do PDF", 0, QApplication::UnicodeUTF8));
    plikExport_pdfAction->setIconText(QApplication::translate("Form1", "Export do PDF", 0, QApplication::UnicodeUTF8));
    plikExport_pdfAction->setProperty("name", QVariant(QApplication::translate("Form1", "plikExport_pdfAction", 0, QApplication::UnicodeUTF8)));
    plikExport_XMLAction->setText(QApplication::translate("Form1", "Export do XML", 0, QApplication::UnicodeUTF8));
    plikExport_XMLAction->setIconText(QApplication::translate("Form1", "Export do XML", 0, QApplication::UnicodeUTF8));
    plikExport_XMLAction->setProperty("name", QVariant(QApplication::translate("Form1", "plikExport_XMLAction", 0, QApplication::UnicodeUTF8)));
    plikImport_EDIAction->setText(QApplication::translate("Form1", "Import EDI", 0, QApplication::UnicodeUTF8));
    plikImport_EDIAction->setIconText(QApplication::translate("Form1", "Import EDI", 0, QApplication::UnicodeUTF8));
    plikImport_EDIAction->setProperty("name", QVariant(QApplication::translate("Form1", "plikImport_EDIAction", 0, QApplication::UnicodeUTF8)));
    plikImport_XMLAction->setText(QApplication::translate("Form1", "Import XML", 0, QApplication::UnicodeUTF8));
    plikImport_XMLAction->setIconText(QApplication::translate("Form1", "Import XML", 0, QApplication::UnicodeUTF8));
    plikImport_XMLAction->setProperty("name", QVariant(QApplication::translate("Form1", "plikImport_XMLAction", 0, QApplication::UnicodeUTF8)));
    fakturyKorektaAction->setText(QApplication::translate("Form1", "Nowa korekta", 0, QApplication::UnicodeUTF8));
    fakturyKorektaAction->setIconText(QApplication::translate("Form1", "Nowa korekta", 0, QApplication::UnicodeUTF8));
    fakturyKorektaAction->setShortcut(QString());
    fakturyKorektaAction->setProperty("name", QVariant(QApplication::translate("Form1", "fakturyKorektaAction", 0, QApplication::UnicodeUTF8)));
    fakturyPFormaAction->setText(QApplication::translate("Form1", "Nowa pro forma", 0, QApplication::UnicodeUTF8));
    fakturyPFormaAction->setIconText(QApplication::translate("Form1", "Nowa pro forma", 0, QApplication::UnicodeUTF8));
    fakturyPFormaAction->setProperty("name", QVariant(QApplication::translate("Form1", "fakturyPFormaAction", 0, QApplication::UnicodeUTF8)));
    nextPageAction->setIconText(QApplication::translate("Form1", "Action", 0, QApplication::UnicodeUTF8));
    nextPageAction->setShortcut(QApplication::translate("Form1", "Ctrl+PgDown", 0, QApplication::UnicodeUTF8));
    nextPageAction->setProperty("name", QVariant(QApplication::translate("Form1", "nextPageAction", 0, QApplication::UnicodeUTF8)));
    prevPageAction->setIconText(QApplication::translate("Form1", "Action_2", 0, QApplication::UnicodeUTF8));
    prevPageAction->setShortcut(QApplication::translate("Form1", "Ctrl+PgUp", 0, QApplication::UnicodeUTF8));
    prevPageAction->setProperty("name", QVariant(QApplication::translate("Form1", "prevPageAction", 0, QApplication::UnicodeUTF8)));
    if (tableH->columnCount() < 6)
        tableH->setColumnCount(6);

    QTableWidgetItem *__colItem = new QTableWidgetItem();
    __colItem->setText(QApplication::translate("Form1", "Nazwa pliku", 0, QApplication::UnicodeUTF8));
    tableH->setHorizontalHeaderItem(0, __colItem);

    QTableWidgetItem *__colItem1 = new QTableWidgetItem();
    __colItem1->setText(QApplication::translate("Form1", "Symbol", 0, QApplication::UnicodeUTF8));
    tableH->setHorizontalHeaderItem(1, __colItem1);

    QTableWidgetItem *__colItem2 = new QTableWidgetItem();
    __colItem2->setText(QApplication::translate("Form1", "Data", 0, QApplication::UnicodeUTF8));
    tableH->setHorizontalHeaderItem(2, __colItem2);

    QTableWidgetItem *__colItem3 = new QTableWidgetItem();
    __colItem3->setText(QApplication::translate("Form1", "Typ", 0, QApplication::UnicodeUTF8));
    tableH->setHorizontalHeaderItem(3, __colItem3);

    QTableWidgetItem *__colItem4 = new QTableWidgetItem();
    __colItem4->setText(QApplication::translate("Form1", "Nabywca", 0, QApplication::UnicodeUTF8));
    tableH->setHorizontalHeaderItem(4, __colItem4);

    QTableWidgetItem *__colItem5 = new QTableWidgetItem();
    __colItem5->setText(QApplication::translate("Form1", "NIP", 0, QApplication::UnicodeUTF8));
    tableH->setHorizontalHeaderItem(5, __colItem5);
    tabWidget2->setTabText(tabWidget2->indexOf(tab1), QApplication::translate("Form1", "Historia", 0, QApplication::UnicodeUTF8));
    if (tableK->columnCount() < 5)
        tableK->setColumnCount(5);

    QTableWidgetItem *__colItem6 = new QTableWidgetItem();
    __colItem6->setText(QApplication::translate("Form1", "Nazwa", 0, QApplication::UnicodeUTF8));
    tableK->setHorizontalHeaderItem(0, __colItem6);

    QTableWidgetItem *__colItem7 = new QTableWidgetItem();
    __colItem7->setText(QApplication::translate("Form1", "Typ", 0, QApplication::UnicodeUTF8));
    tableK->setHorizontalHeaderItem(1, __colItem7);

    QTableWidgetItem *__colItem8 = new QTableWidgetItem();
    __colItem8->setText(QApplication::translate("Form1", "Miasto", 0, QApplication::UnicodeUTF8));
    tableK->setHorizontalHeaderItem(2, __colItem8);

    QTableWidgetItem *__colItem9 = new QTableWidgetItem();
    __colItem9->setText(QApplication::translate("Form1", "Adres", 0, QApplication::UnicodeUTF8));
    tableK->setHorizontalHeaderItem(3, __colItem9);

    QTableWidgetItem *__colItem10 = new QTableWidgetItem();
    __colItem10->setText(QApplication::translate("Form1", "Telefon", 0, QApplication::UnicodeUTF8));
    tableK->setHorizontalHeaderItem(4, __colItem10);
    tabWidget2->setTabText(tabWidget2->indexOf(tab2), QApplication::translate("Form1", "Kontrahenci", 0, QApplication::UnicodeUTF8));
    if (tableT->columnCount() < 12)
        tableT->setColumnCount(12);

    QTableWidgetItem *__colItem11 = new QTableWidgetItem();
    __colItem11->setText(QApplication::translate("Form1", "Index", 0, QApplication::UnicodeUTF8));
    tableT->setHorizontalHeaderItem(0, __colItem11);

    QTableWidgetItem *__colItem12 = new QTableWidgetItem();
    __colItem12->setText(QApplication::translate("Form1", "Nazwa", 0, QApplication::UnicodeUTF8));
    tableT->setHorizontalHeaderItem(1, __colItem12);

    QTableWidgetItem *__colItem13 = new QTableWidgetItem();
    __colItem13->setText(QApplication::translate("Form1", "Skr\303\263t", 0, QApplication::UnicodeUTF8));
    tableT->setHorizontalHeaderItem(2, __colItem13);

    QTableWidgetItem *__colItem14 = new QTableWidgetItem();
    __colItem14->setText(QApplication::translate("Form1", "Kod", 0, QApplication::UnicodeUTF8));
    tableT->setHorizontalHeaderItem(3, __colItem14);

    QTableWidgetItem *__colItem15 = new QTableWidgetItem();
    __colItem15->setText(QApplication::translate("Form1", "PKWiU", 0, QApplication::UnicodeUTF8));
    tableT->setHorizontalHeaderItem(4, __colItem15);

    QTableWidgetItem *__colItem16 = new QTableWidgetItem();
    __colItem16->setText(QApplication::translate("Form1", "Typ", 0, QApplication::UnicodeUTF8));
    tableT->setHorizontalHeaderItem(5, __colItem16);

    QTableWidgetItem *__colItem17 = new QTableWidgetItem();
    __colItem17->setText(QApplication::translate("Form1", "Jedn.", 0, QApplication::UnicodeUTF8));
    tableT->setHorizontalHeaderItem(6, __colItem17);

    QTableWidgetItem *__colItem18 = new QTableWidgetItem();
    __colItem18->setText(QApplication::translate("Form1", "Netto1", 0, QApplication::UnicodeUTF8));
    tableT->setHorizontalHeaderItem(7, __colItem18);

    QTableWidgetItem *__colItem19 = new QTableWidgetItem();
    __colItem19->setText(QApplication::translate("Form1", "Netto2", 0, QApplication::UnicodeUTF8));
    tableT->setHorizontalHeaderItem(8, __colItem19);

    QTableWidgetItem *__colItem20 = new QTableWidgetItem();
    __colItem20->setText(QApplication::translate("Form1", "Netto3", 0, QApplication::UnicodeUTF8));
    tableT->setHorizontalHeaderItem(9, __colItem20);

    QTableWidgetItem *__colItem21 = new QTableWidgetItem();
    __colItem21->setText(QApplication::translate("Form1", "Netto4", 0, QApplication::UnicodeUTF8));
    tableT->setHorizontalHeaderItem(10, __colItem21);

    QTableWidgetItem *__colItem22 = new QTableWidgetItem();
    __colItem22->setText(QApplication::translate("Form1", "Stawka VAT", 0, QApplication::UnicodeUTF8));
    tableT->setHorizontalHeaderItem(11, __colItem22);
    tabWidget2->setTabText(tabWidget2->indexOf(TabPage), QApplication::translate("Form1", "Towary/Us\305\202ugi", 0, QApplication::UnicodeUTF8));
    Plik->setTitle(QApplication::translate("Form1", "&Plik", 0, QApplication::UnicodeUTF8));
    Faktury->setTitle(QApplication::translate("Form1", "&Faktury", 0, QApplication::UnicodeUTF8));
    Kontrahenci->setTitle(QApplication::translate("Form1", "&Kontrahenci", 0, QApplication::UnicodeUTF8));
    Towary->setTitle(QApplication::translate("Form1", "&Towary", 0, QApplication::UnicodeUTF8));
    Pomoc->setTitle(QApplication::translate("Form1", "P&omoc", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Form1: public Ui_Form1 {};
} // namespace Ui

#endif // UI_MAINFORM_H
