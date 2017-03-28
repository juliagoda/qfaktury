#ifndef USER_H
#define USER_H

#include "ui_User.h"


class User: public QDialog, public Ui::User {

Q_OBJECT

public:

    User(QWidget *parent);


public slots:

	void init();
	void okClick();
    bool checkAll();

};
#endif
