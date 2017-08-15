
#include "Buyers.h"
#include  "Validations.h"

/** Constructor
 */

Buyers::Buyers(QWidget *parent, int mode, IDataLayer *dl) :
	QDialog(parent) {

	workingMode = mode;
	dataLayer = dl;
	setupUi(this);
	init();
}

/** init()
 */

void Buyers::init() {

    allNames = dataLayer->buyersGetFirmList();


	// connects
	connect(okButton, SIGNAL(clicked()), this, SLOT(okClick()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(typeCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(requiredTic(int)));
}


const QString Buyers::getRetBuyer()
{
    return ret;
}

// --------- SLOTS START --
/** Slot - ok & save
 */

void Buyers::okClick() {


    QStringList list = QStringList() << nameEdit->text() << typeCombo->currentText() << placeEdit->text() << addressEdit->text() << telefonEdit->text() <<
            nipEdit->text() << codeEdit->text() << accountEdit->text() << emailEdit->text() << wwwEdit->text();


	if (workingMode == 1) {

        if (updateData()) {

            foreach(QString listEl, list) {

                ret += isEmpty(listEl) + "|";
            }

            accept();
        }

	} else {

		if (insertData()) {

            foreach(QString listEl, list) {

                ret += isEmpty(listEl) + "|";
            }

			accept();
		}
	}
}


void Buyers::requiredTic(int type)
{
    if (type == 2)
        textLabel2_2->setText(trUtf8("NIP:"));
    else
        textLabel2_2->setText(trUtf8("NIP*:"));

    this->update();
}

// --------- SLOTS END --

//***** DATA access START ****
// load data modification mode

void Buyers::selectData(QString name, int type) {

	setWindowTitle(trUtf8("Edytuj kontrahenta"));
    getData(dataLayer->buyersSelectData(name, type));
	typeCombo->setCurrentIndex(type);
	typeCombo->setEnabled(false);

    if (typeCombo->currentIndex() == 2) {
        textLabel2_2->setText(trUtf8("NIP:"));
    } else {
        textLabel2_2->setText(trUtf8("NIP*:"));
    }

    this->update();
}

// new customer insert data
bool Buyers::insertData() {

	bool result = false;
    BuyerData buyerData;

    if ((sett().value("validation").toBool() && validate()) || sett().value("validation").toBool() == false) {

        setData(buyerData);
        result = dataLayer->buyersInsertData(buyerData,
                    typeCombo->currentIndex());
    }

	return result;
}

// update existing
bool Buyers::updateData() {

	bool result = false;
    BuyerData buyerData;

    if ((sett().value("validation").toBool() && validateUpdated()) || sett().value("validation").toBool() == false) {

        setData(buyerData);

        result = dataLayer->buyersUpdateData(buyerData,
                    typeCombo->currentIndex(), nameEdit->text());
    }

    if (typeCombo->currentIndex() == 2) {
        textLabel2_2->setText(trUtf8("NIP:"));
    } else {
        textLabel2_2->setText(trUtf8("NIP*:"));
    }

    this->update();

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

bool Buyers::validate() {

    if (Validations::instance()->isEmptyField(nameEdit->text(),textLabel1->text())) return false;
    if (Validations::instance()->isEmptyField(placeEdit->text(),textLabel3->text())) return false;

    if (!Validations::instance()->isEmptyField(codeEdit->text(),textLabel4->text())) {
        if (!Validations::instance()->validateZip(codeEdit->text())) return false;
   } else {
        return false;
    }

    if (Validations::instance()->isEmptyField(addressEdit->text(),textLabel2->text())) return false;

    if (typeCombo->currentIndex() == 2) {

        textLabel2_2->setText(trUtf8("NIP:"));
        this->update();

        if (!nipEdit->text().isEmpty()) {

            if (!Validations::instance()->validateNIP(nipEdit->text())) return false;
            if (!Validations::instance()->checkSumNIP(nipEdit->text())) return false;
       }

    } else {

        textLabel2_2->setText(trUtf8("NIP*:"));
        this->update();

        if (!Validations::instance()->isEmptyField(nipEdit->text(),textLabel2_2->text())) {

            if (!Validations::instance()->validateNIP(nipEdit->text())) return false;
            if (!Validations::instance()->checkSumNIP(nipEdit->text())) return false;

        } else {

            return false;
        }

    }

    if (!accountEdit->text().isEmpty()) {
        if (!Validations::instance()->validateAccount(accountEdit->text())) return false;
        if (!Validations::instance()->checkSumAccount(accountEdit->text())) return false;
   }

    if (!telefonEdit->text().isEmpty()) {
        if (!Validations::instance()->validateTel(telefonEdit->text())) return false;
   }

    if (!emailEdit->text().isEmpty()) {
        if (!Validations::instance()->validateEmail(emailEdit->text())) return false;
   }

    if (!wwwEdit->text().isEmpty()) {
        if (!Validations::instance()->validateWebsite(wwwEdit->text())) return false;
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

bool Buyers::validateUpdated()
{
    if (Validations::instance()->isEmptyField(nameEdit->text(),textLabel1->text())) return false;
    if (Validations::instance()->isEmptyField(placeEdit->text(),textLabel3->text())) return false;

    if (!Validations::instance()->isEmptyField(codeEdit->text(),textLabel4->text())) {
        if (!Validations::instance()->validateZip(codeEdit->text())) return false;
   } else {
        return false;
    }

    if (Validations::instance()->isEmptyField(addressEdit->text(),textLabel2->text())) return false;

    if (!Validations::instance()->isEmptyField(nipEdit->text(),textLabel2_2->text())) {
        if (!Validations::instance()->validateNIP(nipEdit->text())) return false;
        if (!Validations::instance()->checkSumNIP(nipEdit->text())) return false;
    } else {
        return false;
    }

    if (!accountEdit->text().isEmpty()) {
        if (!Validations::instance()->validateAccount(accountEdit->text())) return false;
        if (!Validations::instance()->checkSumAccount(accountEdit->text())) return false;
   }

    if (!telefonEdit->text().isEmpty()) {
        if (!Validations::instance()->validateTel(telefonEdit->text())) return false;
   }

    if (!emailEdit->text().isEmpty()) {
        if (!Validations::instance()->validateEmail(emailEdit->text())) return false;
   }

    if (!wwwEdit->text().isEmpty()) {
        if (!Validations::instance()->validateWebsite(wwwEdit->text())) return false;
   }

    return true;
}

//********************** VALIDATION  END ************************


//********************** DATA METHODS START *********************
/** Loads data from labels into Data object
 */

void Buyers::setData(BuyerData& buyerData) {

    buyerData.name = nameEdit->text();
    buyerData.place= placeEdit->text();
    buyerData.code = codeEdit->text();
    buyerData.address = addressEdit->text();
    buyerData.tic = nipEdit->text();
    buyerData.account = accountEdit->text();
    buyerData.phone = telefonEdit->text();
    buyerData.email = emailEdit->text();
    buyerData.www = wwwEdit->text();
}

/** Load details
 */

void Buyers::getData(BuyerData buyerData) {

    nameEdit->setText(buyerData.name);
    placeEdit->setText(buyerData.place);
    codeEdit->setText(buyerData.code);
    addressEdit->setText(buyerData.address);
    nipEdit->setText(buyerData.tic);
    accountEdit->setText(buyerData.account);
    telefonEdit->setText(buyerData.phone);
    emailEdit->setText(buyerData.email);
    wwwEdit->setText(buyerData.www);
}
//********************** DATA METHODS END *********************

// helper method which sets "-" in input forms
QString Buyers::isEmpty(QString in) {

	if (in == "") return "-";
	return in;
}

