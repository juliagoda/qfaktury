#include "saftfile.h"
#include "ui_saftfile.h"

#include "idatalayer.h"
#include "xmldatalayer.h"

#include <QMessageBox>
#include <QTableWidgetItem>
#include <QComboBox>


Saftfile::Saftfile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Saftfile)
{
    ui->setupUi(this);
    setWindowTitle("Generowanie JPK");
    show();

    dlSaftfile = new XmlDataLayer;
    connect(ui->showSAFTinvBtn, SIGNAL(clicked(bool)), this, SLOT(initInvoicesRange()));
}


Saftfile::Saftfile(IDataLayer* dl, QWidget* parent) :
    dlSaftfile(dl), QWidget(parent),
    ui(new Ui::Saftfile)
{
    ui->setupUi(this);
    setWindowTitle("Generowanie JPK");
    show();

    connect(ui->showSAFTinvBtn, SIGNAL(clicked(bool)), this, SLOT(initInvoicesRange()));
}


Saftfile::~Saftfile()
{
    if (dlSaftfile != 0) dlSaftfile = 0;
    delete dlSaftfile;
    delete ui;
}


bool Saftfile::toDateisLower() {

    if (ui->jpksToDate->date() < ui->jpksFromDate->date())
        return true;

    return false;
}


QVector<InvoiceData> Saftfile::getInvFromRange() {

    if (toDateisLower()) {
        QMessageBox::information(this, "Błąd przedziału czasu", "Data końcowa nie może być wcześniejsza od daty początkowej");
        ui->jpksToDate->setDate(ui->jpksFromDate->date());
    }

    QVector<InvoiceData> invoicesVec;

    invoicesVec =
        dlSaftfile->invoiceSelectAllData(ui->jpksFromDate->date(), ui->jpksToDate->date(),true);

    return invoicesVec;

}


void Saftfile::insertRowToTable(QTableWidget *t, int row) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  t->insertRow(row);

  for (int i = 0; i < t->columnCount(); i++) {

    t->setItem(row, i, new QTableWidgetItem());
  }
}


void Saftfile::putIntoTable(QVector<InvoiceData> invoices) {

    ui->saftInvoicesTable->setRowCount(0);

    if (invoices.isEmpty()) {
        QMessageBox::information(this,"brak faktur","Brakuje jakiejkolwiek faktury z tego okresu");
        return;
    }

  for (int i = 0; i < invoices.size(); ++i) {

      double gross = 0;
      QList<ProductData> products = invoices.at(i).products.values();

      for (int j = 0; j < products.count(); j++) {
        gross += products.at(j).gross;
      }

      insertRowToTable(ui->saftInvoicesTable, ui->saftInvoicesTable->rowCount());
      ui->saftInvoicesTable->item(ui->saftInvoicesTable->rowCount() - 1, 0)->setText(QString::number(i+1));
      ui->saftInvoicesTable->item(ui->saftInvoicesTable->rowCount() - 1, 1)->setText(invoices.at(i).invNr);
      ui->saftInvoicesTable->item(ui->saftInvoicesTable->rowCount() - 1, 2)->setText(QString::number(gross));
      ui->saftInvoicesTable->item(ui->saftInvoicesTable->rowCount() - 1, 3)->setText(invoices.at(i).sellingDate.toString(sett().getDateFormat()));
      QComboBox* jpkFields = new QComboBox();
      jpkFields->addItem("według stawki VAT");
      ui->saftInvoicesTable->setCellWidget(ui->saftInvoicesTable->rowCount() - 1,4,jpkFields);

      ui->saftInvoicesTable->item(ui->saftInvoicesTable->rowCount() - 1,0)->setTextAlignment(Qt::AlignCenter);
      ui->saftInvoicesTable->item(ui->saftInvoicesTable->rowCount() - 1,1)->setTextAlignment(Qt::AlignCenter);
      ui->saftInvoicesTable->item(ui->saftInvoicesTable->rowCount() - 1,2)->setTextAlignment(Qt::AlignCenter);
      ui->saftInvoicesTable->item(ui->saftInvoicesTable->rowCount() - 1,3)->setTextAlignment(Qt::AlignCenter);
      ui->saftInvoicesTable->item(ui->saftInvoicesTable->rowCount() - 1,4)->setTextAlignment(Qt::AlignCenter);

    }

    ui->saftInvoicesTable->setSortingEnabled(true);

}

// SLOTS //

void Saftfile::initInvoicesRange() {

    putIntoTable(getInvFromRange());
}
