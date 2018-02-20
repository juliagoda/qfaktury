#include "detector.h"
#if _pragma_once_support
#pragma once
#endif
#ifndef MainWindow_H
#define MainWindow_H

#include <QMainWindow>

#include "ui_mainwindow.h"

class QKeyEvent;
class QPrinter;
class IDataLayer;
class QPushButton;
class QTableWidget;
class QLineEdit;
class ownCalendarWidget;
class QWidget;
class QTimer;
class QAction;
class Invoice;

// class for creating main window with menu, toolbar, calendar and table widget
class MainWindow : public QMainWindow {

  Q_OBJECT

public:
  MainWindow(QWidget *parent = 0);
  ~MainWindow();
  static void insertRow(QTableWidget *t, int row);
  void newInvoice(Invoice *invoice, QString windowTitle);
  int getMaxSymbol() const;
  int getMaxSymbolWarehouse() const;
  static MainWindow *instance();
  static bool shouldHidden;
  QString whichBackupPath();

private slots:


  void createFirstWinCsv();
  void choosePathCsv();
  void createCsvFiles();
  void createFirstWinBackup(); // Backup
  void choosePathBackup(); // Backup
  void createBackup(); // Backup
  void loadBackup(); // Backup
  void sendEmailToBuyer(); // Email
  void on_WZAction_triggered();
  void on_RWAction_triggered();


public slots:

  void tableClear(QTableWidget *tab);
  void tabChanged();
  void rereadHist(bool if_clicked);
  void rereadWarehouses(bool);
  void aboutProg();
  void editFHist();
  void warehouseEdit();
  void delFHist();
  void delMHist();
  void userDataClick();
  void settClick();
  void buyerClick();
  void buyerDel();
  void buyerEd();
  void newInv();
  void newInvRR();
  void newPForm();
  void newCor();
  void newDuplicate();
  void newInvGross();
  void newInvBill();
  bool close();
  void openHideOrganizer();  // Organizer
  void noteDownTask(const QDate &); // Organizer
  void goodsAdd();
  void goodsDel();
  void goodsEdit();
  void findInvoicePdf(); // Pdf
  void checkDateRange(const QDate &date); // Debug
  void mainUpdateStatus(QTableWidgetItem *item);
  void showTableMenuT(QPoint p);
  void showTableMenuK(QPoint p);
  void showTableMenuH(QPoint p);
  void showTableMenuM(QPoint p);
  void pluginSlot(); // Plugin
  void pluginInfoSlot(); // Plugin
  void keyPressEvent(QKeyEvent *event);
  void openWebTableK(int, int);
  void printBuyerList(); // ContactsList
  void printList(QPrinter *); // ContactsList
  QString changeIfEmpty(QString); // Templates
  bool ifpdfDirExists(); // Pdf
  void createPdfDir(); // Pdf
  void generatePdfFromList(); // Pdf
  void intervalBackup();

protected:
  virtual void loadPlugins(); // Plugin

private:
  IDataLayer *dl;
  Ui::MainWindow *ui;
  QHash<QString, QString> idCvsSeller;
  QHash<QString, QString> idCvsBuyer;
  QHash<QString, QString> idCvsInvoices;
  QHash<QString, QString> idCvsWarehouses;
  QHash<QString, QString> idCvsProducts;
  QTimer* backupTimerOften;
  QWidget *windBack; // Backup
  QLineEdit *fileComboBox; // Backup
  QLineEdit *directoryComboBox; // Backup

  QVector<QAction *> plugActions; // Plugin
  QString workingDir;
  QMap<int, QString> customActions; // Plugin
  QTimer *timer;
  QList<int> allSymbols;
  QList<int> allSymbolsWarehouse;
  ownCalendarWidget *calendar; // Organizer
  static MainWindow *m_instance;

  int getInvoiceTypeFullName(QString invoiceType);
  void saveColumnWidth();
  void init();
  void saveAllSett();
  void saveAllSettAsDefault();
  void setupDir();
  void readHist();
  void readWarehouses();
  void readBuyer();
  void readGoods();
  void categorizeYears();
  void createEmergTemplate();
  bool ifEmergTemplateExists();
  bool firstRun();
  void createBuyersCsvFiles();
  void createProductsCsvFiles();
  void createSellersCsvFiles();
  void createInvoicesCsvFiles(QDate from, QDate to);
  void createWareCsvFiles(QDate from, QDate to);
  void createBackupWithoutGUI();
  void checkIntervalsForBackup();
};

#endif
