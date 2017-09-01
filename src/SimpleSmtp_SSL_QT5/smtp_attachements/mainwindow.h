#include "../../detector.h"
#if _pragma_once_support
#pragma once
#endif
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QMessageBox>
#include <QFileDialog>

namespace Ui {
class EmailWindow;
}

class QLineEdit;
class QPlainTextEdit;
class QRadioButton;
class Smtp;

class EmailWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit EmailWindow(QWidget *parent = 0);
    ~EmailWindow();

    const QLineEdit* getServerName();
    void setServerName(QString);

    const QLineEdit* getPortNumber();
    void setPortNumber(QString);

    const QLineEdit* getUserName();
    void setUserName(QString);

    const QLineEdit* getUserPassword();
    void setUserPassword(QString);

    const QLineEdit* getRecipMail();
    void setRecipMail(QString);

    const QLineEdit* getSubject();
    void setSubject(QString);

    const QLineEdit* getFiles();
    void addNextFile(QString);
    void removeLastFile(QString);

    const QRadioButton* getTemplate_1();
    const QRadioButton* getTemplate_2();
    const QRadioButton* getTemplate_3();

    const QPlainTextEdit* getMessage();
    void setMessage(QString);

    void addFile(QString);
    void removeFile(QString);


private slots:
    void sendMail();
    void browse();
    void mailSent();
    
private:
    Ui::EmailWindow *ui;
    QStringList files;
    Smtp* smtp;

};

#endif // MAINWINDOW_H
