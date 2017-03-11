#ifndef OWNCALENDAR_H
#define OWNCALENDAR_H

#include <QCalendarWidget>
#include <QPainter>
#include <QDir>

class ownCalendarWidget : public QCalendarWidget
{
    Q_OBJECT
public:
    ownCalendarWidget(QWidget* parent=0)
        : QCalendarWidget(parent)
    {
    }

    ~ownCalendarWidget()
    {
    }

    void ourCall(QDate date)
    {
        // here we set some conditions
        update();
    }

protected:
    void paintCell(QPainter *painter, const QRect &rect, const QDate &date) const
    {
        QDir allFiles;
        QList<QDate> dateList;

        allFiles.setPath(QDir::homePath() + "/.local/share/data/elinux/plans");
        allFiles.setFilter(QDir::Files);
        QStringList filters;
        filters << "*.txt";

        allFiles.setNameFilters(filters);
        QStringList files = allFiles.entryList();
        int i, max = files.count();

        for (i = 0; i < max; ++i) {

            QString dateFound = files.at(i);
            dateFound = dateFound.remove(".txt");
            dateList.append(QDate::fromString(dateFound));

        }

        if (dateList.contains(date)) { // our conditions
            // When the conditions are matched, passed QDate is drawn as we like.
            painter->save();
            painter->drawRoundedRect(rect,12,12); // here we draw n ellipse and the day—
            painter->drawText(rect, Qt::AlignCenter, QString::number(date.day()));
            painter->restore();

        } else { // if our conditions are not matching, show the default way.
            QCalendarWidget::paintCell(painter, rect, date);
        }
    }
};

#endif // OWNCALENDAR_H
