#include "detector.h"
#if _pragma_once_support
#pragma once
#endif
#ifndef MainWindow_H
#define MainWindow_H

#include <QMainWindow>

#include "ui_MainWindow.h"

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

  void createFirstWinBackup();
  void createFirstWinCsv();
  void choosePathBackup();
  void choosePathCsv();
  void createCsvFiles();
  void createBackup();
  void loadBackup();
  void sendEmailToBuyer();
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
  void openHideOrganizer();
  void noteDownTask(const QDate &);
  void goodsAdd();
  void goodsDel();
  void goodsEdit();
  void findInvoicePdf();
  void checkDateRange(const QDate &date);
  void mainUpdateStatus(QTableWidgetItem *item);
  void showTableMenuT(QPoint p);
  void showTableMenuK(QPoint p);
  void showTableMenuH(QPoint p);
  void showTableMenuM(QPoint p);
  void pluginSlot();
  void pluginInfoSlot();
  void keyPressEvent(QKeyEvent *event);
  void openWebTableK(int, int);
  void printBuyerList();
  void printList(QPrinter *);
  void cancelTaskWidget();
  void addTaskToList();
  void addNextTask();
  void delTasksFromDay();
  QString changeIfEmpty(QString);
  bool ifpdfDirExists();
  void createPdfDir();
  void generatePdfFromList();

protected:
  virtual void loadPlugins();

private:
  IDataLayer *dl;
  Ui::MainWindow *ui;
  QWidget *windBack;
  QLineEdit *fileComboBox;
  QLineEdit *directoryComboBox;

  QVector<QAction *> plugActions;
  QHash<QString, QString> idCvsSeller;
  QHash<QString, QString> idCvsBuyer;
  QHash<QString, QString> idCvsInvoices;
  QHash<QString, QString> idCvsWarehouses;
  QHash<QString, QString> idCvsProducts;
  QString workingDir;
  QMap<int, QString> customActions;
  QTimer *timer;
  QList<int> allSymbols;
  QList<int> allSymbolsWarehouse;
  QWidget *windowTask;
  QPushButton *cancelTaskBtn;
  QPushButton *addTaskBtn;
  QDate markedDate;
  ownCalendarWidget *calendar;
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
  void checkTodayTask(QString whatToDo = QString("append"));
  void createEmergTemplate();
  bool ifEmergTemplateExists();
  bool applyFiltr(QString);
  bool firstRun();
  void createBuyersCsvFiles();
  void createProductsCsvFiles();
  void createSellersCsvFiles();
  void createInvoicesCsvFiles(QDate from, QDate to);
  void createWareCsvFiles(QDate from, QDate to);

  inline void calendarNoteJustify(QString text) {

    ui->todayExercise->append(text);

    QTextCursor cursor = ui->todayExercise->textCursor();
    QTextBlockFormat textBlockFormat = cursor.blockFormat();
    textBlockFormat.setAlignment(Qt::AlignHCenter);
    cursor.mergeBlockFormat(textBlockFormat);
    ui->todayExercise->setTextCursor(cursor);
  }
};
#endif
