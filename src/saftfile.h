#ifndef SAFTFILE_H
#define SAFTFILE_H

#include <QWidget>

namespace Ui {
class Saftfile;
}

class Saftfile : public QWidget
{
    Q_OBJECT

public:
    explicit Saftfile(QWidget *parent = 0);
    ~Saftfile();

private:
    Ui::Saftfile *ui;
};

#endif // SAFTFILE_H
