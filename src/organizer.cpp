#include "organizer.h"
#include "ui_organizer.h"
#include "Settings.h"

#include <QTabWidget>
#include <QPushButton>
#include <QFileInfo>
#include <QTextEdit>
#include <QCalendarWidget>


Organizer::Organizer(QTextEdit* exercisesField, const QDate& calendarD, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Organizer)
{
    qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

    tasksWindowToday = exercisesField;
    calendarDate = calendarD;
    ui->setupUi(this);
    show();

    init();
}


Organizer::Organizer(QTabWidget* tabWidgetOrganizer, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Organizer)
{
    qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

    tasksWindowToday = tabWidgetOrganizer->findChild<QTextEdit *>("organizer");
    calendarDate = tabWidgetOrganizer->findChild<QCalendarWidget *>("organizer")->selectedDate();
    ui->setupUi(this);

    init();
}

// private
void Organizer::init() {

    qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

    checkMainDirExist(sett().getPlansDir());

    noteDownTask(calendarDate);

    connect(ui->addTaskBtn, SIGNAL(clicked()), this, SLOT(addTaskToDir()));
    connect(ui->addNextTask, SIGNAL(clicked()), this, SLOT(addNextTask()));
    connect(ui->delTasks, SIGNAL(clicked()), this, SLOT(delTasksDay()));
    connect(ui->cancelTaskBtn, SIGNAL(clicked()), this, SLOT(close()));
}

// private, get to template
bool Organizer::checkMainDirExist(QString planDir) {

    qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

    QDir mainPath(planDir);

    if (!mainPath.exists()) {

     return mainPath.mkdir(planDir);
    }

    return true;
}


Organizer::~Organizer()
{
    qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

    if (tasksWindowToday.isNull())
        delete tasksWindowToday;

    delete ui;

}

// protected
const QString Organizer::getNoteFile(const QDate &taskDate) {

    qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

    QString planDir = sett().getPlansDir() + "/" +
                      taskDate.toString() + ".txt";

    QFile filename(planDir);
    QFileInfo fileInfoName(filename);
    return fileInfoName.absoluteFilePath();

}

// private
bool Organizer::ifNoteExists(QString filenameArg) {

    qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;
    QFile filename(filenameArg);
    return filename.exists();

}

// protected
void Organizer::updateOrganizerGUI(bool fileNoteExists, bool fileNoteEmpty) {

    qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

    if (fileNoteExists && !fileNoteEmpty) {
        ui->addNextTask->setDisabled(false);
        ui->addTaskBtn->setText("Zastąp zadanie");
    } else {
        ui->addNextTask->setDisabled(true);
        ui->addTaskBtn->setText("Dodaj zadanie");
    }

    if (fileNoteExists)
        ui->delTasks->setDisabled(false);
    else
        ui->delTasks->setDisabled(true);

    update();
}

// private
void Organizer::noteDownTask(const QDate &taskDate) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  QString stringFileName = getNoteFile(taskDate);

  QFile filename(stringFileName);

  updateOrganizerGUI(ifNoteExists(stringFileName), filename.size() == 0);

  QFileInfo check_file(filename.fileName());

  if (check_file.exists() && check_file.isFile()) {

    if (!filename.open(QIODevice::ReadOnly | QIODevice::Text)) {

          filename.setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner);
    }

    QTextStream in(&filename);

    while (!in.atEnd()) {

      QString line = in.readLine();

      if (line.isNull()) {
        ui->taskDescription->insertPlainText("\n");
      }

      ui->taskDescription->insertPlainText(line);
      ui->taskDescription->insertPlainText("\n");
      ui->taskDescription->moveCursor(QTextCursor::End);
    }

    filename.close();
  }
}

// private
void Organizer::communicateAboutRemove(QFile* file,bool removed) {

    qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

    if (removed) {

      QMessageBox::information(
          this, "Usuwanie zadań",
          "Zadania z wybranego dnia zostały pomyślnie usunięte",
          QMessageBox::Ok);

    } else {

      file->setPermissions(QFileDevice::ReadOther | QFileDevice::WriteOther);
      removed = file->remove();

      if (removed) {

        QMessageBox::information(
            this, "Usuwanie zadań",
            "Zadania z wybranego dnia zostały pomyślnie usunięte",
            QMessageBox::Ok);

      } else {

        QMessageBox::critical(
            this, "Usuwanie zadań",
            "Zadania z wybranego dnia nie mogły zostać pomyślnie "
                   "usunięte. Zrestartuj program, by wyeliminować ewentualny "
                   "brak aktualnych danych o plikach.",
            QMessageBox::Ok);
      }
    }
}

// protected
void Organizer::delTasksFromDay(const QDate &markedDate) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  QString stringFileName = getNoteFile(markedDate);

  QFile file(stringFileName);

  bool removed{false};

  if (file.exists())
    removed = file.remove();

  communicateAboutRemove(&file, removed);

  close();

  removeTodayTask();
}

// private
void Organizer::addTaskToList(const QDate& markedDate) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  QFile file(getNoteFile(markedDate));

  if (file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text)) {
    QTextStream stream(&file);

    stream << ui->taskDescription->toPlainText() << endl;

    if (stream.status() == QTextStream::Ok) {

      QMessageBox::information(this, "Dodawanie zadania",
                               "Zadanie zostało pomyślnie stworzone",
                               QMessageBox::Ok);

      close();

      checkTodayTask();

    } else {

          file.setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner);

      QMessageBox::critical(
          this, "Dodawanie zadania",
          "Zadanie nie mogło zostać dodane. Sprawdź, czy istnieje "
                 "ścieżka: " +
              sett().getPlansDir() +
              " . Jeśli istnieje to sprawdź, czy masz uprawnienia do "
                     "zapisu i odczytu w podanej ścieżce.",
          QMessageBox::Ok);
    }
  }
}

// private
void Organizer::addNextTaskFromDay(const QDate& markedDate) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  QFile file(getNoteFile(markedDate));

  if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {

    QTextStream stream(&file);
    stream << "\n" << endl;
    stream << ui->taskDescription->toPlainText() << endl;

    if (stream.status() == QTextStream::Ok) {

      QMessageBox::information(
          this, "Dopisywanie kolejnego zadania",
          "Dodatkowe zadanie zostało pomyślnie dodane.",
          QMessageBox::Ok);

      close();

      checkTodayTask();

    } else {

      QFileInfo check_file(file.fileName());

      if (check_file.exists() && check_file.isFile()) {

        QFile(file.fileName())
            .setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner);

        QTextStream stream(&file);
        stream << "\n" << endl;
        stream << ui->taskDescription->toPlainText() << endl;

        if (stream.status() == QTextStream::Ok) {

          QMessageBox::information(
              this, "Dopisywanie kolejnego zadania",
              "Dodatkowe zadanie zostało pomyślnie dodane.",
              QMessageBox::Ok);

          close();

          checkTodayTask();

        } else {

          QMessageBox::critical(
              this, "Dopisywanie kolejnego zadania",
              "Dodatkowe zadanie nie mogło zostać dodane. Sprawdź, czy "
                     "istnieje ścieżka: " +
                  sett().getPlansDir() +
                  " . Jeśli istnieje to sprawdź, czy masz uprawnienia "
                         "do zapisu i odczytu w podanej ścieżce.",
              QMessageBox::Ok);
        }
      }
    }
  }
}


// public
void Organizer::checkTodayTask() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  QString today = QDate::currentDate().toString();
  qDebug() << "TODAY IS " << today;

  QString planDir = sett().getPlansDir() + "/" + today + ".txt";

  QFile filename(planDir);

  QTextStream in(&filename);

  tasksWindowToday->setStyleSheet("QTextEdit"
                                   "{padding-left: 10px;"
                                   "padding-right: 10px;"
                                   "padding-top: 30px;"
                                   "padding-bottom: 30px;"
                                   "background-color: white;}");

  tasksWindowToday->clear();

    if (filename.exists()) {

      if (!filename.open(QIODevice::ReadOnly | QIODevice::Text)) {

        QFileInfo check_file(filename.fileName());

        if (check_file.exists() && check_file.isFile()) {

          QFile(filename.fileName())
              .setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner);
        }
      }

      while (!in.atEnd()) {

        QString line = in.readLine();

        if (line.isNull()) {
          tasksWindowToday->append("<br>");
        }

        calendarNoteJustify(line);
      }

      tasksWindowToday->setStyleSheet("QTextEdit"
                                       "{padding-left: 10px;"
                                       "padding-right: 10px;"
                                       "padding-top: 30px;"
                                       "padding-bottom: 30px;"
                                       "background-color: white;"
                                       "color: #e51919;"
                                       "font-weight: bold;}");

      filename.close();

    } else {

      calendarNoteJustify("Dziś nie masz nic do zrobienia");
    }
}

// protected
void Organizer::removeTodayTask() {

    qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

    QString today = QDate::currentDate().toString();
    qDebug() << "TODAY IS " << today;

    QString planDir = sett().getPlansDir() + "/" + today + ".txt";

    QFile filename(planDir);

    QTextStream in(&filename);

    tasksWindowToday->setStyleSheet("QTextEdit"
                                     "{padding-left: 10px;"
                                     "padding-right: 10px;"
                                     "padding-top: 30px;"
                                     "padding-bottom: 30px;"
                                     "background-color: white;}");

    tasksWindowToday->clear();

    calendarNoteJustify("Dziś nie masz nic do zrobienia");
}

// protected
void Organizer::calendarNoteJustify(QString text) {

    qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

    tasksWindowToday->append(text);

    QTextCursor cursor = tasksWindowToday->textCursor();
    QTextBlockFormat textBlockFormat = cursor.blockFormat();
    textBlockFormat.setAlignment(Qt::AlignHCenter);
    cursor.mergeBlockFormat(textBlockFormat);
    tasksWindowToday->setTextCursor(cursor);
}


// *********************** SLOTS ************************//

void Organizer::delTasksDay() {

    qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

    delTasksFromDay(calendarDate);
}

void Organizer::addNextTask() {

    qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

    addNextTaskFromDay(calendarDate);
}

void Organizer::addTaskToDir() {

    qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

    addTaskToList(calendarDate);
}
