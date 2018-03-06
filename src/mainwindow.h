#include "detector.h"
#if _pragma_once_support
#pragma once
#endif
#ifndef MainWindow_H
#define MainWindow_H


#include <QMainWindow>
#include <QDir>

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

private slots:

  void openJPKGenerator();
  void exportCsv();
  void createBackupMode(); // Backup
  void loadBackupMode(); // Backup
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
  void openJPKDirectory();
  void checkDateRange(const QDate &date); // Debug
  void mainUpdateStatus(QTableWidgetItem *item);
  void showTableMenuT(QPoint p);
  void showTableMenuK(QPoint p);
  void showTableMenuH(QPoint p);
  void showTableMenuM(QPoint p);
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

private:
  IDataLayer *dl;
  Ui::MainWindow *ui;
  QTimer* backupTimerOften;

  QString workingDir;
  QTimer *timer;
  QList<int> allSymbols;
  QList<int> allSymbolsWarehouse;
  ownCalendarWidget *calendar; // Organizer
  static MainWindow *m_instance;

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
  void checkIntervalsForBackup(); // Backup

};

#endif
