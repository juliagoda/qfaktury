#ifndef FORM1_H
#define FORM1_H
#include <QMainWindow>
#include <ui_mainform.h>
class Form1: public QMainWindow, public Ui::Form1 {
    Q_OBJECT
    public slots:

    Form1(QWidget *parent);
    
    void init();
    bool firstRun();
    void tableClear(QTable * tab);
    void tabChanged(QWidget * aaa);
    void readHist(QString progDir);
    void aboutQt();
    void oProg();
    void editFHist();
    void delFHist();
    void readKontr(QString progDir);
    void readTw(QString progDir);
    void daneFirmyClick();
    void settClick();
    void kretorClick();
    void kontrClick();
    void kontrDel();
    void kontrEd();
    void newFra();
    void newPForm();
    void newKor();
    void closeEvent(QCloseEvent * e);
    void pomoc();
    void towaryDodaj();
    void towaryUsun();
    void towaryEdycja();
    void saveAllSett();
    void nextPage();
    void prevPage();
};

#endif
