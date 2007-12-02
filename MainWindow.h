#ifndef MainWindow_H
#define MainWindow_H
#include <QMainWindow>
#include "ui_MainWindow.h"
class MainWindow: public QMainWindow, public Ui::MainWindow {
    Q_OBJECT
    public:
    MainWindow(QWidget *parent);
    public slots:
void init ();
bool firstRun ();
void tableClear (QTable * tab);
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
void kretorClick ();
void kontrClick ();
void kontrDel ();
void kontrEd ();
void newFra ();
void newPForm ();
void newKor ();
void closeEvent (QCloseEvent * e);
void pomoc ();
void towaryDodaj ();
void towaryUsun ();
void towaryEdycja ();
void saveAllSett();
void nextPage();
void prevPage();
};
#endif
