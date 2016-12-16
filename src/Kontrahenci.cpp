#include "moc_Kontrahenci.cpp"
#include "Kontrahenci.h"
#include <QMessageBox>
#include <QtDebug>
#include <QLineEdit>
#include <QRegExp>
#include <QByteArray>
#include <QChar>
#include "Settings.h"
#include  "Walidacje.h"

/** Constructor
 */

Kontrahenci::Kontrahenci(QWidget *parent, int mode, IDataLayer *dl) :
	QDialog(parent) {

	workingMode = mode;
	dataLayer = dl;
	setupUi(this);
	init();
}

/** init()
 */

void Kontrahenci::init() {

	allNames = dataLayer->kontrahenciGetFirmList();

	// connects
	connect(okButton, SIGNAL(clicked()), this, SLOT(okClick()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
}


QString const Kontrahenci::getRetKontr() const
{
    return ret;
}

// --------- SLOTS START --
/** Slot - ok & save
 */

void Kontrahenci::okClick() {

	if (workingMode == 1) {

        if (updateData()) {

            ret = isEmpty(nameEdit->text()) + "|" + isEmpty(typeCombo->currentText()) + "|" + isEmpty(
                placeEdit->text()) + "|" + isEmpty(addressEdit->text()) + "|"
                + isEmpty(telefonEdit->text()) + "|" + isEmpty(nipEdit->text()) + "|"
                + isEmpty(codeEdit->text()) + "|" + isEmpty(accountEdit->text()) + "|" + isEmpty(telefonEdit->text()) + "|"
                + isEmpty(emailEdit->text()) + "|" + isEmpty(wwwEdit->text());
            accept();
        }
	} else {

		if (insertData()) {

            ret = isEmpty(nameEdit->text()) + "|" + isEmpty(typeCombo->currentText()) + "|" + isEmpty(
                        placeEdit->text()) + "|" + isEmpty(addressEdit->text()) + "|"
                        + isEmpty(telefonEdit->text()) + "|" + isEmpty(nipEdit->text()) + "|"
                        + isEmpty(codeEdit->text()) + "|" + isEmpty(accountEdit->text()) + "|" + isEmpty(telefonEdit->text()) + "|"
                        + isEmpty(emailEdit->text()) + "|" + isEmpty(wwwEdit->text());
			accept();
		}
	}

}

// --------- SLOTS END --

//***** DATA access START ****
// load data modification mode

void Kontrahenci::selectData(QString name, int type) {

	setWindowTitle(trUtf8("Edytuj kontrahenta"));
	getData(dataLayer->kontrahenciSelectData(name, type));
	typeCombo->setCurrentIndex(type);
	typeCombo->setEnabled(false);
}

// new customer insert data
bool Kontrahenci::insertData() {

	bool result = false;

	if (validate()) {

		KontrData kontrData;
		setData(kontrData);
		result = dataLayer->kontrahenciInsertData(kontrData,
					typeCombo->currentIndex());
	}

	return result;
}

// update existing
bool Kontrahenci::updateData() {

	bool result = false;
    if (validateUpdated()) {

		KontrData kontrData;
		setData(kontrData);

		result = dataLayer->kontrahenciUpdateData(kontrData,
					typeCombo->currentIndex(), nameEdit->text());
	}

	return result;
}
//***** DATA access END ****


//********************** VALIDATION START ************************
/** Validate form
 *  Don't save when no
 *  "name", "city", "street", "tic"
 */

/** validate()
 */

bool Kontrahenci::validate() {

    if (Walidacje::instance()->isEmptyField(nameEdit->text(),textLabel1->text())) return false;
    if (Walidacje::instance()->isEmptyField(placeEdit->text(),textLabel3->text())) return false;

    if (!Walidacje::instance()->isEmptyField(codeEdit->text(),textLabel4->text())) {
        if (!Walidacje::instance()->validateZip(codeEdit->text())) return false;
   } else {
        return false;
    }

    if (Walidacje::instance()->isEmptyField(addressEdit->text(),textLabel2->text())) return false;

    if (!Walidacje::instance()->isEmptyField(nipEdit->text(),textLabel2_2->text())) {
        if (!Walidacje::instance()->validateNIP(nipEdit->text())) return false;
        if (!Walidacje::instance()->checkSumNIP(nipEdit->text())) return false;
    } else {
        return false;
    }

    if (!accountEdit->text().isEmpty()) {
        if (!Walidacje::instance()->validateAccount(accountEdit->text())) return false;
        if (!Walidacje::instance()->checkSumAccount(accountEdit->text())) return false;
   }

    if (!telefonEdit->text().isEmpty()) {
        if (!Walidacje::instance()->validateTel(telefonEdit->text())) return false;
   }

    if (!emailEdit->text().isEmpty()) {
        if (!Walidacje::instance()->validateEmail(emailEdit->text())) return false;
   }

    if (!wwwEdit->text().isEmpty()) {
        if (!Walidacje::instance()->validateWebsite(wwwEdit->text())) return false;
   }

    if (allNames.indexOf(QRegExp(nameEdit->text(), Qt::CaseSensitive,
            QRegExp::FixedString)) != -1) {
        QMessageBox::critical(
                0,
                "QFaktury",
                trUtf8("Kontrahent nie moze zostać dodany ponieważ istnieje już kontrahent o tej nazwie."));
        return false;
    }


	return true;
}

bool Kontrahenci::validateUpdated()
{
    if (Walidacje::instance()->isEmptyField(nameEdit->text(),textLabel1->text())) return false;
    if (Walidacje::instance()->isEmptyField(placeEdit->text(),textLabel3->text())) return false;

    if (!Walidacje::instance()->isEmptyField(codeEdit->text(),textLabel4->text())) {
        if (!Walidacje::instance()->validateZip(codeEdit->text())) return false;
   } else {
        return false;
    }

    if (Walidacje::instance()->isEmptyField(addressEdit->text(),textLabel2->text())) return false;

    if (!Walidacje::instance()->isEmptyField(nipEdit->text(),textLabel2_2->text())) {
        if (!Walidacje::instance()->validateNIP(nipEdit->text())) return false;
        if (!Walidacje::instance()->checkSumNIP(nipEdit->text())) return false;
    } else {
        return false;
    }

    if (!accountEdit->text().isEmpty()) {
        if (!Walidacje::instance()->validateAccount(accountEdit->text())) return false;
        if (!Walidacje::instance()->checkSumAccount(accountEdit->text())) return false;
   }

    if (!telefonEdit->text().isEmpty()) {
        if (!Walidacje::instance()->validateTel(telefonEdit->text())) return false;
   }

    if (!emailEdit->text().isEmpty()) {
        if (!Walidacje::instance()->validateEmail(emailEdit->text())) return false;
   }

    if (!wwwEdit->text().isEmpty()) {
        if (!Walidacje::instance()->validateWebsite(wwwEdit->text())) return false;
   }

    return true;
}

//********************** VALIDATION  END ************************


//********************** DATA METHODS START *********************
/** Loads data from labels into Data object
 */

void Kontrahenci::setData(KontrData& kontrData) {

	kontrData.name = nameEdit->text();
	kontrData.place= placeEdit->text();
	kontrData.code = codeEdit->text();
	kontrData.address = addressEdit->text();
	kontrData.tic = nipEdit->text();
	kontrData.account = accountEdit->text();
	kontrData.phone = telefonEdit->text();
	kontrData.email = emailEdit->text();
	kontrData.www = wwwEdit->text();
}

/** Load details
 */

void Kontrahenci::getData(KontrData kontrData) {

	nameEdit->setText(kontrData.name);
	placeEdit->setText(kontrData.place);
	codeEdit->setText(kontrData.code);
	addressEdit->setText(kontrData.address);
	nipEdit->setText(kontrData.tic);
	accountEdit->setText(kontrData.account);
	telefonEdit->setText(kontrData.phone);
	emailEdit->setText(kontrData.email);
	wwwEdit->setText(kontrData.www);
}
//********************** DATA METHODS END *********************

// helper method which sets "-" in input forms
QString Kontrahenci::isEmpty(QString in) {

	if (in == "") return "-";
	return in;
}

