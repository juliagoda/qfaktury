#ifndef MainWindow_H
#define MainWindow_H
#include <QMainWindow>
#include "ui_MainWindow.h"
class MainWindow: public QMainWindow, public Ui::MainWindow {
    Q_OBJECT
void init ();
bool firstRun ();
    public:
    MainWindow(QWidget *parent);
static void insertRow(QTableWidget *t,int row);
    public slots:
void tableClear (QTableWidget * tab);
void tabChanged (QWidget * aaa);
void readHist (QString progDir);
void aboutQt ();
void oProg ();
void editFHist ();
void delFHist ();
void readKontr (QString progDir);
void readTw (QString progDir);
void daneFirmyClick ();
void settClick ();
void kontrClick ();
void kontrDel ();
void kontrEd ();
void newFra ();
void newPForm ();
void newKor ();
bool close();
void pomoc ();
void towaryDodaj ();
void towaryUsun ();
void towaryEdycja ();
void saveAllSett();
void nextPage();
void prevPage();
    private:
};
#endif
