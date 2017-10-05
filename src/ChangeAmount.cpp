
#include "ChangeAmount.h"

#include <QWidget>


ChangeAmount *ChangeAmount::m_instance = nullptr;

ChangeAmount::ChangeAmount(QWidget *parent) : QDialog(parent) {
  setupUi(this);
  init();
}


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
