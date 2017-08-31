
#include "ChangeAmount.h"

ChangeAmount *ChangeAmount::m_instance = nullptr;

ChangeAmount::ChangeAmount(QWidget *parent) : QDialog(parent) {
  setupUi(this);
  init();
}

void ChangeAmount::init() { m_instance = this; }

ChangeAmount::~ChangeAmount() { m_instance = nullptr; }

ChangeAmount *ChangeAmount::instance() { return m_instance; }
