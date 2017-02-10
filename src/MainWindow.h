#ifndef MainWindow_H
#define MainWindow_H

#include <QMainWindow>
#include <QTableWidget>
#include <QKeyEvent>
#include "Settings.h"
#include "ui_MainWindow.h"

#include "IDataLayer.h"
#include "Invoice.h"


class MainWindow: public QMainWindow {

Q_OBJECT

public:

    MainWindow(QWidget *parent=0);
	~MainWindow();
	static void insertRow(QTableWidget *t, int row);
    void newInvoice(Invoice* invoice, QString windowTitle);
    int const getMaxSymbol();
    static MainWindow * instance();


public slots:

	void tableClear(QTableWidget * tab);
    void tabChanged();
    void rereadHist(bool if_clicked);
	void aboutQt();
    void aboutProg();
	void editFHist();
	void delFHist();
    void userDataClick();
	void settClick();
    void buyerClick();
    void buyerDel();
    void buyerEd();
    void newInv();
	void newPForm();
    void newCor();
    void newDuplicate();
    void newInvGross();
    void newInvBill();
	bool close();
    void help();
	void reportBug();
    void goodsAdd();
    void goodsDel();
    void goodsEdit();
	void mainUpdateStatus(QTableWidgetItem *item);
	void showTableMenuT(QPoint p);
	void showTableMenuK(QPoint p);
	void showTableMenuH(QPoint p);
	void pluginSlot();
	void pluginInfoSlot();
	void keyPressEvent(QKeyEvent * event);
    void openWebTableK(int,int);

private:

    IDataLayer *dl;
    Ui::MainWindow *ui;

    QVector<QAction*> plugActions;
    QString workingDir;
	QMap<int, QString> customActions;
    QTimer *timer;
    QList<int> allSymbols;
    static MainWindow * m_instance;
	void saveColumnWidth();
	bool applyFiltr(QString);
	void init();
	bool firstRun();
	void saveAllSett();
	void saveAllSettAsDefault();
	void setupDir();
	void readHist();
    void readBuyer();
    void readGoods();


protected:

	virtual void loadPlugins();
};
#endif
