#include <QCalendarWidget>
#include <QDir>
#include <QPainter>

#include "owncalendar.h"

ownCalendarWidget::ownCalendarWidget(QWidget *parent)
    : QCalendarWidget(parent) {}

ownCalendarWidget::~ownCalendarWidget() {}

void ownCalendarWidget::ourCall(QDate) {
  // here we set some conditions
  update();
}

QSize ownCalendarWidget::sizeHint() const { return QSize(); }

QSize ownCalendarWidget::minimumSizeHint() const { return QSize(); }

void ownCalendarWidget::resizeEvent(QResizeEvent *) {}

void ownCalendarWidget::mousePressEvent(QMouseEvent *) {}

void ownCalendarWidget::keyPressEvent(QKeyEvent *) {}

bool ownCalendarWidget::eventFilter(QObject *, QEvent *) { return true; }

bool ownCalendarWidget::event(QEvent *) { return true; }

void ownCalendarWidget::paintCell(QPainter *painter, const QRect &rect,
                                  const QDate &date) const {
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
    painter->drawRoundedRect(rect, 12,
                             12); // here we draw n ellipse and the day—
    painter->drawText(rect, Qt::AlignCenter, QString::number(date.day()));
    painter->restore();

  } else { // if our conditions are not matching, show the default way.
    QCalendarWidget::paintCell(painter, rect, date);
  }
}
