#ifndef SEND_H
#define SEND_H

#include <QVariant>
#include <QLayout>
#include <QLineEdit>
#include <QCheckBox>
#include <QRadioButton>
#include <QLabel>
#include <QGroupBox>
#include <QFile>
#include <QMessageBox>
#include <QRegularExpression>
#include <QWizard>
#include <QWizardPage>
#include <QTableWidget>
#include <QTextEdit>

#include "Buyers.h"


class Send : public QWizard
{
    Q_OBJECT

public:
    Send(QVector<BuyerData>, QVector<InvoiceData>, QWidget *parent = 0);

    void accept() override;

private:

    QVector<BuyerData> bList;
    QVector<InvoiceData> iList;
};

class IntroPage : public QWizardPage
{
    Q_OBJECT

public:
    IntroPage(QWidget *parent = 0);

private:
    QLabel *label;
};

class ClassInvoicePage : public QWizardPage
{
    Q_OBJECT

public:
    ClassInvoicePage(QVector<BuyerData>, QVector<InvoiceData>, QWidget *parent = 0);

protected:
    bool validatePage() override;
    QString transformType(QString);

private:
    QVector<BuyerData> bList;
    QVector<InvoiceData> iList;
    QTableWidget* invoicesList;

};

class EmailPage : public QWizardPage
{
    Q_OBJECT

public:
    EmailPage(QWidget *parent = 0);

protected:
    void initializePage() override;


private slots:
    void getTemplateOne(bool);
    void getTemplateTwo(bool);
    void getTemplateThree(bool);

private:
    QLineEdit *emailLine;
    QLineEdit *copyLine;
    QLineEdit *titleLine;
    QTextEdit *message;
    QGroupBox *groupBox;
};

class ConclusionPage : public QWizardPage
{
    Q_OBJECT

public:
    ConclusionPage(QWidget *parent = 0);

protected:
    void initializePage() override;

private:
    QLabel *label;
};

#endif // SEND_H
