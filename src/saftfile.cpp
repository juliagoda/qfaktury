#include "saftfile.h"
#include "ui_saftfile.h"
#include "saftfileoutput.h"

#include "idatalayer.h"
#include "xmldatalayer.h"

#include <QMessageBox>
#include <QTableWidgetItem>
#include <QComboBox>
#include <QPointer>



Saftfile::Saftfile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Saftfile)
{
    ui->setupUi(this);
    setWindowTitle("Generowanie JPK");
    setWindowModality(Qt::WindowModal);
    show();

    dlSaftfile = new XmlDataLayer;

    putBtnToGroup();
    showConnections();

    ui->labelComboCurr->hide(); // temporarily
    ui->currCombo->hide();

    ui->corrNrLabel->hide();
    ui->corrNrLabel->buddy()->hide();

}


Saftfile::Saftfile(IDataLayer* dl, QWidget* parent) :
    dlSaftfile(dl), QWidget(parent),
    ui(new Ui::Saftfile)
{
    ui->setupUi(this);
    setWindowTitle("Generowanie JPK");
    setWindowModality(Qt::WindowModal);
    show();

    putBtnToGroup();
    showConnections();

    ui->labelComboCurr->hide(); // temporarily
    ui->currCombo->hide();

    ui->corrNrLabel->hide();
    ui->corrNrLabel->buddy()->hide();

}


Saftfile::~Saftfile()
{
    if (dlSaftfile != 0) dlSaftfile = 0;
    delete dlSaftfile;

    if (groupAppPurp != 0 || groupArtFiles != 0) {
        groupAppPurp = 0;
        groupArtFiles = 0;
    }

    delete groupAppPurp;
    delete groupArtFiles;
    delete ui;
}


void Saftfile::showConnections() {

    connect(ui->showSAFTinvBtn, SIGNAL(clicked(bool)), this, SLOT(initInvoicesRange()));
    connect(ui->generationBtn, SIGNAL(clicked(bool)), this, SLOT(prepareNextStep()));
   /* connect(groupArtFiles, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonPressed),
        [=](QAbstractButton *button) {
        QString text = button->text();
        text = text.remove('&');
        qDebug() << "Text of pressed button " << text;
        fileArtVarVersion = text;
        fileArtVar = text.left(text.indexOf(' '));

    });*/

    connect(groupAppPurp, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonPressed),
        [=](QAbstractButton *button){
        QString btnText = button->text();
        btnText = btnText.remove('&');
        qDebug() << "BTNTEXT " << btnText;
        if (btnText == "Korekta") {
            ui->corrNrLabel->show();
            ui->corrNrLabel->buddy()->show();
            update();
        } else {
            ui->corrNrLabel->hide();
            ui->corrNrLabel->buddy()->hide();
            update();
        }

    });

    connect(ui->returnBtn, SIGNAL(clicked(bool)), this, SLOT(close()));

}


void Saftfile::putBtnToGroup() {

    groupAppPurp = new QButtonGroup();
    groupAppPurp->addButton(ui->correctionAppBtn);
    groupAppPurp->addButton(ui->standardAppBtn);

    groupArtFiles = new QButtonGroup();
    groupArtFiles->addButton(ui->saftJPKVATbtn);
    groupArtFiles->addButton(ui->saftJPKFAbtn);
}


const QString Saftfile::getFromDateJPK() {

    QString date = ui->jpksFromDate->date().toString("yyyy-MM-dd");
    qDebug() << date << " getFromDateJPK in Saftfile";
    return date;
}


const QString Saftfile::getToDateJPK() {

    QString date = ui->jpksToDate->date().toString("yyyy-MM-dd");
    qDebug() << date << " getToDateJPK in Saftfile";
    return date;
}


const QString Saftfile::getApplicationPurpose() {

    QString text = groupAppPurp->checkedButton()->text();
    return text.remove('&');
}


const QString Saftfile::getJpkFileArtWithVersion() {

    QString text = groupArtFiles->checkedButton()->text();
    text = text.remove('&');
    qDebug() << "Text of pressed button " << text;

    return text;
}


const QString Saftfile::getJpkFileArt() {

    QString text = groupArtFiles->checkedButton()->text();
    text = text.remove('&');
    qDebug() << "Text of pressed button " << text;

    return text.left(text.indexOf(' '));
}


const QString Saftfile::getDefaultCur() {

    QString text = ui->currCombo->currentText();
    text = text.remove('&');
    return text;
}


const QString Saftfile::getTaxOfficeNr() {

    return ui->codeTaxOffice->text();
}

const QString Saftfile::getCorrectionNr() {

    return ui->correctionJpkNr->text();
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

    if (ui->jpksFromDate->date().year() < 2018) {
        QMessageBox::information(this, "Błąd przedziału czasu", "Data początkowa nie może sięgać daty wcześniejszej niż 1 stycznia 2018 roku. Jest to spowodowane tym, że program używa generatora dla JPK_VAT w wersji 3, ważnej od 2018 roku.");
        ui->jpksFromDate->setDate(QDate(2018,1,1));
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
      jpkFields->addItem("na podstawie stawki VAT");
      ui->saftInvoicesTable->setCellWidget(ui->saftInvoicesTable->rowCount() - 1,4,jpkFields);

      ui->saftInvoicesTable->item(ui->saftInvoicesTable->rowCount() - 1,0)->setTextAlignment(Qt::AlignCenter);
      ui->saftInvoicesTable->item(ui->saftInvoicesTable->rowCount() - 1,1)->setTextAlignment(Qt::AlignCenter);
      ui->saftInvoicesTable->item(ui->saftInvoicesTable->rowCount() - 1,2)->setTextAlignment(Qt::AlignCenter);
      ui->saftInvoicesTable->item(ui->saftInvoicesTable->rowCount() - 1,3)->setTextAlignment(Qt::AlignCenter);
      ui->saftInvoicesTable->item(ui->saftInvoicesTable->rowCount() - 1,4)->setTextAlignment(Qt::AlignCenter);

    }

    ui->saftInvoicesTable->setSortingEnabled(true);

}


QVector<InvoiceData> Saftfile::addSAFTFieldsToList(QVector<InvoiceData> invoices) {

    for (int i = 0; i < invoices.size(); ++i) {

        if (invoices.at(i).invNr == ui->saftInvoicesTable->item(i, 1)->text()) {

            QString textSAFT = qobject_cast<QComboBox*>(ui->saftInvoicesTable->cellWidget(i,4))->currentText();

          //  invoices.at(i).jpkFieldText = textSAFT;
        }
    }

    return invoices;
}

// SLOTS //

void Saftfile::initInvoicesRange() {

    invs = getInvFromRange();
    putIntoTable(invs);
}


void Saftfile::prepareNextStep() {

    //is automatically set to 0 when the referenced object is destroyed
    qDebug() << getTaxOfficeNr() << " getTaxOfficeNr";
    data.insert("jpkFromDate", getFromDateJPK());
    data.insert("jpkToDate", getToDateJPK());
    data.insert("applicationPurpose", getApplicationPurpose());
    data.insert("correctionNr", getCorrectionNr());
    data.insert("jpkFileArt", getJpkFileArt());
    data.insert("jpkFileArtWithVersion", getJpkFileArtWithVersion());
    data.insert("codeTaxOffice", getTaxOfficeNr());
    data.insert("defaultCurrency", getDefaultCur());

    QPointer<SaftfileOutput> saftfileoutput = new SaftfileOutput(addSAFTFieldsToList(invs), data);

    if (saftfileoutput.isNull())
        delete saftfileoutput;
}
