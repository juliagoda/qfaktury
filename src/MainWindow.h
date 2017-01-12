#ifndef MainWindow_H
#define MainWindow_H
#include <QMainWindow>
#include <QTableWidget>
#include <QKeyEvent>
#include "Settings.h"
#include "ui_MainWindow.h"

#include "IDataLayer.h"
#include "Faktura.h"


class MainWindow: public QMainWindow {

Q_OBJECT

public:

    MainWindow(QWidget *parent=0);
	~MainWindow();
	static void insertRow(QTableWidget *t, int row);
    void newInvoice(Faktura* invoice, QString windowTitle);


public slots:

	void tableClear(QTableWidget * tab);
    void tabChanged();
    void rereadHist(bool if_clicked);
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
	void newFBrutto();
	void newFRachunek();
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
	void saveColumnWidth();
	bool applyFiltr(QString);
	void init();
	bool firstRun();
	void saveAllSett();
	void saveAllSettAsDefault();
	void setupDir();
	void readHist();
	void readKontr();
	void readTw();


protected:

	virtual void loadPlugins();
};
#endif
