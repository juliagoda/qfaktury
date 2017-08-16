#pragma once

#include "ui_ChangeAmount.h"

class ChangeAmount : public QDialog, public Ui::ChangeAmount
{
	Q_OBJECT

public:
	ChangeAmount(QWidget *parent);
};
