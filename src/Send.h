#pragma once

#include "Buyers.h"
#include "SimpleSmtp_SSL_QT5/smtp_attachements/mainwindow.h"

#include <QCheckBox>
#include <QFile>
#include <QGroupBox>
#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QRadioButton>
#include <QRegularExpression>
#include <QTableWidget>
#include <QTextEdit>
#include <QVariant>
#include <QWizard>
#include <QWizardPage>

class Send : public QWizard
{
	Q_OBJECT

public:
	Send(QVector<BuyerData>, QVector<InvoiceData>, QWidget *parent = nullptr);

	void accept() override;

private:
	QVector<BuyerData> bList;
	QVector<InvoiceData> iList;
};

class IntroPage : public QWizardPage
{
	Q_OBJECT

public:
	IntroPage(QWidget *parent = nullptr);

private:
	QLabel *label;
};

class ClassInvoicePage : public QWizardPage
{
	Q_OBJECT

public:
	ClassInvoicePage(QVector<BuyerData>, QVector<InvoiceData>, QWidget *parent = nullptr);

protected:
	bool validatePage() override;
	QString transformType(QString text) const;

private:
	QVector<BuyerData> bList;
	QVector<InvoiceData> iList;
	QTableWidget *invoicesList;
};

class EmailPage : public QWizardPage
{
	Q_OBJECT

public:
	EmailPage(QWidget *parent = nullptr);
	void setHostPort(QString, QString);

protected:
	void initializePage() override;

private slots:
	void setSSL(bool);
	void setTCP(bool);
	void setTLS(bool);
	void setGmail(bool);
	void seto2(bool);
	void setYahoo(bool);
	void setInteria(bool);
	void setOnet(bool);
	void setWP(bool);
	void setHotMail(bool);
	void setGazeta(bool);
	void setAol(bool);
	void setFoxMail(bool);
	void setOutlook(bool);

private:
	QLabel *label;
	QGroupBox *groupBox;
	bool checkedMailButton;
	bool checkedPortButton;
	QString protocol;
	QString checkedMail;
	QLineEdit *edit1;
	QLineEdit *edit2;
};

class ConclusionPage : public QWizardPage
{
	Q_OBJECT

public:
	ConclusionPage(QWidget *parent = nullptr);

protected:
	void initializePage() override;

private slots:
	void getTemplateOne(bool);
	void getTemplateTwo(bool);
	void getTemplateThree(bool);

private:
	EmailWindow *emailWindow;
};
