#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "smtp.h"

#include <QLineEdit>
#include <QPlainTextEdit>
#include <QRadioButton>
#include <QTimer>

EmailWindow::EmailWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::EmailWindow) {
  ui->setupUi(this);
  connect(ui->sendBtn, SIGNAL(clicked()), this, SLOT(sendMail()));
  connect(ui->browseBtn, SIGNAL(clicked()), this, SLOT(browse()));
}

void EmailWindow::browse() {
  files.clear();

  QFileDialog dialog(this);
  dialog.setDirectory(QDir::homePath());
  dialog.setFileMode(QFileDialog::ExistingFiles);

  if (dialog.exec())
    files = dialog.selectedFiles();

  QString fileListString;
  foreach (QString file, files)
    fileListString.append("\"" + QFileInfo(file).fileName() + "\" ");

  ui->file->setText(fileListString);
}

void EmailWindow::sendMail() {
  smtp = new Smtp(ui->uname->text(), ui->paswd->text(), ui->server->text(),
                  ui->port->text().toInt());

  if (!files.isEmpty())
    smtp->sendMail(ui->uname->text(), ui->rcpt->text(), ui->subject->text(),
                   ui->msg->toPlainText(), files);
  else
    smtp->sendMail(ui->uname->text(), ui->rcpt->text(), ui->subject->text(),
                   ui->msg->toPlainText());

  QTimer *showStatus = new QTimer();
  showStatus->setSingleShot(true);
  connect(showStatus, SIGNAL(timeout()), this, SLOT(mailSent()));
  showStatus->start(3000);

  if (showStatus != 0)
    showStatus = 0;
  delete showStatus;
}

void EmailWindow::mailSent() {
  if (smtp->getStatus() == "Message sent")
    QMessageBox::warning(new QWidget, trUtf8("Qt Simple SMTP client"),
                         trUtf8("Wiadomość została wysłana!\n\n"));
  else
    QMessageBox::warning(new QWidget, trUtf8("Qt Simple SMTP client"),
                         trUtf8("Wysłanie wiadomości nie było możliwe. Upewnij "
                                "się, że poprawnie namieściłeś dane w "
                                "rubrykach i jesteś podłączony do sieci."));
}

const QLineEdit *EmailWindow::getServerName() { return ui->server; }

void EmailWindow::setServerName(QString server) { ui->server->setText(server); }

const QLineEdit *EmailWindow::getPortNumber() { return ui->port; }

void EmailWindow::setPortNumber(QString port) { ui->port->setText(port); }

const QLineEdit *EmailWindow::getUserName() { return ui->uname; }

void EmailWindow::setUserName(QString username) {
  ui->uname->setText(username);
}

const QLineEdit *EmailWindow::getUserPassword() { return ui->paswd; }

void EmailWindow::setUserPassword(QString password) {
  ui->paswd->setText(password);
}

const QLineEdit *EmailWindow::getRecipMail() { return ui->rcpt; }

void EmailWindow::setRecipMail(QString recipMail) {
  ui->rcpt->setText(recipMail);
}

const QLineEdit *EmailWindow::getSubject() { return ui->subject; }

void EmailWindow::setSubject(QString subject) { ui->subject->setText(subject); }

const QPlainTextEdit *EmailWindow::getMessage() { return ui->msg; }

void EmailWindow::setMessage(QString message) {
  ui->msg->setPlainText(message);
}

const QLineEdit *EmailWindow::getFiles() { return ui->file; }

void EmailWindow::addNextFile(QString filename) {
  QString txt = ui->file->text();
  ui->file->clear();
  ui->file->setText(txt + " \"" + QFileInfo(filename).fileName() + "\"");
}

void EmailWindow::addFile(QString file) { files.append(file); }

void EmailWindow::removeFile(QString rFile) { files.removeOne(rFile); }

void EmailWindow::removeLastFile(QString rlFile) {
  QString txt = ui->file->text();
  txt.remove("\"" + QFileInfo(rlFile).fileName() + "\"");
  ui->file->clear();
  ui->file->setText(txt);
}

const QRadioButton *EmailWindow::getTemplate_1() { return ui->template1; }

const QRadioButton *EmailWindow::getTemplate_2() { return ui->template2; }

const QRadioButton *EmailWindow::getTemplate_3() { return ui->template3; }

EmailWindow::~EmailWindow() {
  files = QStringList();
  if (smtp != 0)
    smtp = 0;
  delete smtp;
  delete ui;
}
