#ifndef MainWindow_H
#define MainWindow_H
#include <QMainWindow>
#include "Settings.h"
#include "ui_MainWindow.h"

class MainWindow: public QMainWindow, public Ui::MainWindow {

Q_OBJECT
public:
	MainWindow(QWidget *parent);
	static void insertRow(QTableWidget *t, int row);
	~MainWindow();
public slots:
	void tableClear(QTableWidget * tab);
	void tabChanged(QWidget * aaa);
	void rereadHist();
	void aboutQt();
	void oProg();
	void editFHist();
	void delFHist();
	void daneFirmyClick();
	void settClick();
	void kontrClick();
	void kontrDel();
	void kontrEd();
	void newFra();
	void newPForm();
	void newKor();
	void newDuplikat();
	bool close();
	void pomoc();
	void reportBug();
	void towaryDodaj();
	void towaryUsun();
	void towaryEdycja();
	void mainUpdateStatus(QTableWidgetItem *item);
	void showTableMenuT(QPoint p);
	void showTableMenuK(QPoint p);
	void showTableMenuH(QPoint p);
	void pluginSlot(int i);
	void pluginInfoSlot();
private:
	QString workingDir; // should be deprecated
	QMap<int, QString> plugins;
	void saveColumnWidth();
	bool applyFiltr(QString);
	void init();
	bool firstRun();
	void saveAllSett();
	void saveAllSettAsDefault();
	void readHist();
	void readKontr();
	void readTw();
	void setupDir();
	virtual void loadPlugins();
};
#endif
