#include "detector.h"
#if _pragma_once_support
#pragma once
#endif
#ifndef ORGANIZER_H
#define ORGANIZER_H

#include <QWidget>
#include <QDate>
#include <QPointer>

class QTabWidget;
class QFile;
class QTextEdit;

namespace Ui {
class Organizer;
}

class Organizer : public QWidget
{
    Q_OBJECT

public:
    explicit Organizer(QTextEdit* exercisesField, const QDate& calendarD, QWidget *parent = 0);
    explicit Organizer(QTabWidget* tabWidgetOrganizer, QWidget *parent = 0);
    ~Organizer();
    void checkTodayTask();
    const QString getNoteFile(const QDate &taskDate);


public slots:


protected:
    bool ifNoteExists(QString filenameArg);
    void updateOrganizerGUI(bool fileNoteExists, bool fileNoteEmpty);
    void calendarNoteJustify(QString text);


protected slots:


private:
    void init();
    bool checkMainDirExist(QString planDir);
    void noteDownTask(const QDate &taskDate);
    void communicateAboutRemove(QFile* file,bool removed);
    void removeTodayTask();
    void delTasksFromDay(const QDate &markedDate);
    void addNextTaskFromDay(const QDate& markedDate);
    void addTaskToList(const QDate& markedDate);

    Ui::Organizer *ui;
    QDate calendarDate;
    QPointer<QTextEdit> tasksWindowToday;


private slots:
    void delTasksDay();
    void addNextTask();
    void addTaskToDir();

};

#endif // ORGANIZER_H
