#include "saftfile.h"
#include "ui_saftfile.h"

Saftfile::Saftfile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Saftfile)
{
    ui->setupUi(this);
    show();
}

Saftfile::~Saftfile()
{
    delete ui;
}
