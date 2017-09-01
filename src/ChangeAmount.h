#include "detector.h"
#if _pragma_once_support
#pragma once
#endif
#ifndef CHANGEAMOUNT_H
#define CHANGEAMOUNT_H

#include "ui_ChangeAmount.h"


class ChangeAmount: public QDialog, public Ui::ChangeAmount {

Q_OBJECT

public:

    ChangeAmount(QWidget *parent);
    ~ChangeAmount();
    static ChangeAmount * instance();
    void init();

private:

    static ChangeAmount * m_instance;

};
#endif
