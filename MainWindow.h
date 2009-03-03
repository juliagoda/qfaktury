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
	bool close();
	void pomoc();
	void forum();
	void towaryDodaj();
	void towaryUsun();
	void towaryEdycja();
	void nextPage();
	void prevPage();
private:
	QString workingDir;
	void saveColumnWidth();
	bool applyFiltr(QString);
	void init();
	bool firstRun();
	void saveAllSett();
	void saveAllSettAsDefault();
	void readHist(QString progDir);
	void readKontr(QString progDir);
	void readTw(QString progDir);
	void setupDir();
};
#endif
