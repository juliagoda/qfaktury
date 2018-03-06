#include "backup.h"
#include "ui_backup.h"
#include "settings.h"

#if QUAZIP_FOUND
#include "JlCompress.h"
#include "quazipdir.h"
#endif

#include <QSettings>
#include <QDir>
#include <QMessageBox>
#include <QFileDialog>


Backup::Backup(QString action, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Backup)
{
    qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

    ui->setupUi(this);

    if (QString::compare(action, "create") == 0) {

        setWindowTitle("Tworzenie kopii zapasowej");
        putDataToWidgets(getDirectoryPath(), getFilename());
        prepareConnections();
        show();

    } else if (QString::compare(action, "load") == 0) {

        hide();
        loadBackup();

    }
}


Backup::Backup(bool withGui, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Backup)
{
    qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

    ui->setupUi(this);

    if (!withGui) {

        whenAutoBackup();

    } else {

        prepareConnections();
        show();
    }
}


Backup::~Backup()
{
    delete ui;
}


void Backup::prepareConnections() {

    qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

    connect(ui->browseButton, &QAbstractButton::clicked, this,
            &Backup::choosePathBackup);
    connect(ui->okButton, &QAbstractButton::clicked, this, &Backup::createBackup);
    connect(ui->cancButton, &QAbstractButton::clicked, this, [=]() { close(); });

}


const QString Backup::getBackupPath() {

    qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

    QString backupPath = sett().getWorkingDir();
    QSettings settings("elinux", "qfaktury");

    settings.beginGroup("backup_settings");
    bool ifbackupPathSett = !settings.value("backup_path").toString().isEmpty() &&
                          !settings.value("backup_path").toString().isNull();

    if (ifbackupPathSett)
        backupPath = settings.value("backup_path").toString();


    settings.endGroup();

    return backupPath;

}

const QString Backup::getDirectoryPath() {

    qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

    QString dirPath = QString();
    QSettings settings("elinux", "qfaktury");

    settings.beginGroup("backup_settings");
    dirPath = QDir::toNativeSeparators(getBackupPath());
    settings.endGroup();

    return dirPath;
}


const QString Backup::getFilename() {

    qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

    QString checkSlashPath = getDirectoryPath();

    if (!checkSlashPath.endsWith('/'))
      checkSlashPath += '/';

    QStringRef fileName(&checkSlashPath, checkSlashPath.lastIndexOf('/') + 1,
                        checkSlashPath.lastIndexOf('.') - 1);

    return fileName.toString();
}


void Backup::putDataToWidgets(const QString dirPath, const QString filename) {

    qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

    ui->directoryLineEdit->setText(dirPath);
    ui->fileLineEdit->setText(filename);
}


void Backup::whenAutoBackup() {

    qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

    QSettings settings("elinux", "qfaktury");

    settings.beginGroup("backup_settings");
    QString timeString = settings.value("backup_interval").toString();
    timeString.chop(1);
    int timeInt = timeString.toInt();

    QChar periodTimeSymb = settings.value("backup_interval").toString().back();

    if (!settings.value("lastBackupDate").toString().isEmpty() &&
        !settings.value("lastBackupDate").toString().isEmpty()) {
      if (periodTimeSymb == 'D' && (settings.value("lastBackupDate").toInt() <
                                    QDate::currentDate().dayOfYear() - timeInt))
        createBackupWithoutGui();
      else if (periodTimeSymb == 'W' &&
               (settings.value("lastBackupDate").toInt() <
                QDate::currentDate().dayOfYear() - (timeInt * 7)))
        createBackupWithoutGui();
      else if (periodTimeSymb == 'M' &&
               settings.value("lastBackupDate").toInt() <
                   (QDate::currentDate().dayOfYear() - (timeInt * 31)))
        createBackupWithoutGui();
      else
        createBackupWithoutGui(); // It's sure that will be in minutes or hours
                                  // then from QTimer connection
    } else {
      createBackupWithoutGui(); // just create backup. Needed if user starts
                                // qfaktury first time after newly added features
    }

    settings.setValue("lastBackupDate", QDate::currentDate().dayOfYear());
    settings.endGroup();
}


void Backup::createBackupWithoutGui() {

#if QUAZIP_FOUND

    qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

    QString checkPath = (getBackupPath().endsWith('/'))
                            ? getBackupPath()
                            : getBackupPath() + "/";

    bool completed =
        (JlCompress::compressDir(checkPath + QString("backup.zip"),
                                 sett().getWorkingDir(), true, QDir::AllDirs) &&
         JlCompress::compressFiles(checkPath + QString("backup-configs.zip"),
                                   (QStringList()
                                    << sett().fileName()
                                    << sett().fileName().left(
                                           sett().fileName().lastIndexOf("/")) +
                                           "/user.conf")));



    QSettings settings("elinux", "qfaktury");

    settings.beginGroup("backup_settings");
    qDebug() << "Saved backup path is: " << settings.value("backup_path").toString();
    if (settings.value("backup_every_time").toBool()) {
      if (completed) {


        qDebug() << "Created archive with interval in " + checkPath +
                          "backup.zip and " + checkPath + "backup-configs.zip";
        checkPath.chop(1);
        QMessageBox::information(
            this, trUtf8("Tworzenie kopii zapasowej"),
            "Stworzenie kopii zapasowej zakończyło się sukcesem! Zostało stworzone w ścieżce: \"" + checkPath + "\"");

      } else {

          qDebug() << "Archive had not been created with interval in " + checkPath +
                          "backup.zip and " + checkPath + "backup-configs.zip";
        checkPath.chop(1);
        QMessageBox::warning(
            this, "Tworzenie kopii zapasowej",
            "Stworzenie kopii zapasowej zakończyło "
            "się niepowodzeniem. Sprawdź, czy masz uprawnienia "
            "do odczytu i zapisu w wybranym folderze. Upewnij się także, "
            "że ścieżka: \"" +
                checkPath + "\" istnieje.");
      }
    } else {

      if (completed)
        qDebug() << "Created archive with interval in " + checkPath +
                        "backup.zip and " + checkPath + "backup-configs.zip";
      else
        qDebug() << "Archive had not been created with interval in " + checkPath +
                        "backup.zip and " + checkPath + "backup-configs.zip";
    }

    settings.endGroup();

#endif

}


void Backup::choosePathBackup() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  QString directory =
      QDir::toNativeSeparators(QFileDialog::getExistingDirectory(
          this, tr("Find Files"), sett().getWorkingDir()));

  if (!directory.isEmpty()) {
    ui->directoryLineEdit->setText(directory);
  }

}


void Backup::createBackup() {

#if QUAZIP_FOUND

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  QStringList listConf = QStringList()
                         << sett().fileName()
                         << sett().fileName().left(
                                sett().fileName().lastIndexOf("/")) +
                                "/user.conf";

  if (ui->fileLineEdit->text().isEmpty() || ui->directoryLineEdit->text().isEmpty()) {

    QMessageBox::warning(this, trUtf8("Brakująca ścieżka"),
                         trUtf8("Nazwa dla archiwum oraz ścieżka dla "
                                "tworzonego archiwum nie może być pominięta"));

  } else {

    if (JlCompress::compressDir(ui->directoryLineEdit->text() + QString("/") +
                                    ui->fileLineEdit->text() + QString(".zip"),
                                sett().getWorkingDir(), true, QDir::AllDirs) &&
        JlCompress::compressFiles(ui->directoryLineEdit->text() + QString("/") +
                                      ui->fileLineEdit->text() +
                                      QString("-configs.zip"),
                                  listConf)) {
      qDebug() << "Created archive";
      QMessageBox::information(
          this, trUtf8("Tworzenie kopii zapasowej"),
          trUtf8("Stworzenie kopii zapasowej zakończyło się sukcesem!"));

    } else {

      qDebug() << "Archive had not been created";
      QMessageBox::warning(
          this, trUtf8("Tworzenie kopii zapasowej"),
          trUtf8("Stworzenie kopii zapasowej zakończyło "
                 "się niepowodzeniem. Sprawdź, czy masz uprawnienia "
                 "do odczytu i zapisu w wybranym folderze."));
    }

    qDebug() << ui->directoryLineEdit->text() + QString("/") +
                    ui->fileLineEdit->text() + QString(".zip");

  }
#endif
}


void Backup::loadBackup() {

#if QUAZIP_FOUND

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  QMessageBox msgBox;
  msgBox.setText(
      trUtf8("Wczytywanie kopii zapasowej nadpisze obecny stan. Wpierw musisz "
             "wybrać katalog, następnie pojawi się okno z jego zawartością."));
  msgBox.setInformativeText(trUtf8("Chcesz kontynuować?"));
  msgBox.setIcon(QMessageBox::Information);
  msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
  msgBox.setDefaultButton(QMessageBox::Ok);
  int ret = msgBox.exec();

  switch (ret) {
  case QMessageBox::Ok:

      QString fileName = QFileDialog::getOpenFileName(
        this, trUtf8("Wybierz kopię zapasową"),
        QFileDialog::getExistingDirectory(this, trUtf8("Znajdź"),
                                          QDir::currentPath()),
        trUtf8("pliki archiwalne (*.zip)"));

    if (fileName.endsWith("-configs.zip")) {

        qDebug() << "Chosen Backup file ended with -configs.zip";

      QStringList configsList = QStringList() << "qfaktury.conf"
                                              << "user.conf";

      QStringList confList = JlCompress::extractFiles(
          fileName, configsList,
          sett().fileName().left(sett().fileName().lastIndexOf("/")));

      if (confList.count() > 0)

          QMessageBox::information(
            this, trUtf8("Kopia zapasowa plików konfiguracyjnych"),
            trUtf8("Wczytywanie kopii zapasowej zakończyło się sukcesem!"));
      else

          QMessageBox::warning(
            this, trUtf8("Kopia zapasowa plików konfiguracyjnych"),
            trUtf8("W archiwum brakuje plików konfiguracyjnych dla QFaktury. "
                   "Jesteś pewien, że wybrałeś plik z przyrostkiem "
                   "\"-configs.zip ?\""));

    } else {

        qDebug() << "Chosen backup file not ended with -configs.zip";

      QStringList listEl =
          JlCompress::extractDir(fileName, sett().getWorkingDir());

      qDebug() << "List of files in backup file: " << listEl;

      if (listEl.contains(sett().getWorkingDir() + "/customers.xml") && listEl.contains(sett().getWorkingDir() + "/products.xml")) {

          QMessageBox::information(
            this, trUtf8("Kopia zapasowa głównego katalogu"),
            trUtf8("Wczytywanie kopii zapasowej zakończyło się sukcesem!"));

      } else {

          QMessageBox::information(
            this, trUtf8("Kopia zapasowa głównego katalogu"),
            trUtf8("Wczytywanie kopii zapasowej zakończyło się niepowodzeniem! "
                   "Kopia zapasowa powinna zawierać co najmniej listę "
                   "produktów i kontrahentów."));
      }
    }

    break;
  }

#endif

}
