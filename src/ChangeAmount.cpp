
#include "ChangeAmount.h"

<<<<<<< HEAD
=======
#include <QDebug>
>>>>>>> testing
#include <QWidget>

ChangeAmount *ChangeAmount::m_instance = nullptr;

<<<<<<< HEAD
ChangeAmount *ChangeAmount::m_instance = nullptr;

ChangeAmount::ChangeAmount(QWidget *parent) : QDialog(parent) {
  setupUi(this);
  init();
}
=======
ChangeAmount::ChangeAmount(QWidget *parent) : QDialog(parent) {

  qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

  setupUi(this);
  init();
}

void ChangeAmount::init() {

  qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

  if (m_instance == nullptr)
    m_instance = this;
>>>>>>> testing

  if (this->parent()->objectName() == "GoodsIssuedNotes") {

<<<<<<< HEAD
void ChangeAmount::init() { 
    
    if (m_instance == nullptr) m_instance = this;
    
if (this->parent()->objectName() == "GoodsIssuedNotes") {
    
   textLabel2->hide();
   spinAmount->hide();
   
   requiredAm = new QLabel;
   requiredAm->setText("Ilość żądana*: ");
   
   givedOutAm = new QLabel;
   givedOutAm-> setText("Ilość wydana*: ");
   
   labelsList->addWidget(requiredAm);
   labelsList->addWidget(givedOutAm);
   
   requiredAmBox = new QSpinBox;
   
   givedOutBox = new QSpinBox;
   
   descList->addWidget(requiredAmBox);
   descList->addWidget(givedOutBox);
    
}
}
                          

ChangeAmount::~ChangeAmount() { 
    if (this->parent()->objectName() == "GoodsIssuedNotes") {
   textLabel2->show();
   spinAmount->show();
   
   requiredAm->deleteLater();
   requiredAmBox->deleteLater();
   
   givedOutAm->deleteLater();
   givedOutAm->deleteLater();
}

if (m_instance != nullptr) m_instance = nullptr;
    
}

ChangeAmount *ChangeAmount::instance() { return m_instance; }
=======
    textLabel2->hide();
    spinAmount->hide();

    requiredAm = new QLabel;
    requiredAm->setText("Ilość żądana*: ");

    givedOutAm = new QLabel;
    givedOutAm->setText("Ilość wydana*: ");

    labelsList->addWidget(requiredAm);
    labelsList->addWidget(givedOutAm);

    requiredAmBox = new QSpinBox;

    givedOutBox = new QSpinBox;

    descList->addWidget(requiredAmBox);
    descList->addWidget(givedOutBox);
  }
}

ChangeAmount::~ChangeAmount() {

  qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

  if (this->parent()->objectName() == "GoodsIssuedNotes") {
    textLabel2->show();
    spinAmount->show();

    requiredAm->deleteLater();
    requiredAmBox->deleteLater();

    givedOutAm->deleteLater();
    givedOutAm->deleteLater();
  }

  if (m_instance != nullptr)
    m_instance = nullptr;
}

ChangeAmount *ChangeAmount::instance() {
  qDebug() << __FILE__ << __LINE__ << __FUNCTION__;
  return m_instance;
}
>>>>>>> testing
