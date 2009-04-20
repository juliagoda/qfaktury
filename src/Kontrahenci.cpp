#include "moc_Kontrahenci.cpp"
#include <QMessageBox>
#include <QtDebug>
#include "Settings.h"

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

	nipEdit->setInputMask(sett().value("ticMask", "999-99-999-99; ").toString());
	accountEdit->setInputMask(sett().value("accountMask", "99-9999-9999-9999-9999-9999-9999; ").toString());

	// connects
	connect(okButton, SIGNAL(clicked()), this, SLOT(okClick()));
}

// --------- SLOTS START --
/** Slot - ok & save
 */
void Kontrahenci::okClick() {
	if (workingMode == 1) {
		updateData();
		ret = isEmpty(nameEdit->text()) + "|" + typeCombo->currentText() + "|" + isEmpty(
				placeEdit->text()) + "|" + isEmpty(addressEdit->text()) + "|"
				+ isEmpty(telefonEdit->text()) + "|" + nipEdit->text() + "|"
				+ codeEdit->text();
		accept();
	} else {
		if (insertData()) {
			ret = isEmpty(nameEdit->text()) + "|" + typeCombo->currentText() + "|"
					+ isEmpty(placeEdit->text()) + "|" + isEmpty(
					addressEdit->text()) + "|" + isEmpty(telefonEdit->text())
					+ "|" + nipEdit->text() + "|" + codeEdit->text();
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
	if (validate()) {
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
bool Kontrahenci::validateForm(QString &missing) {
	if (nameEdit->text().isEmpty()) {
		missing = trUtf8("Nazwa");
		nameEdit->setFocus();
		return false;
	}

	if (placeEdit->text().isEmpty()) {
		missing = trUtf8("Miejscowość");
		placeEdit->setFocus();
		return false;
	}

	if (codeEdit->text().isEmpty()) {
		missing = trUtf8("Kod pocztowy");
		codeEdit->setFocus();
		return false;
	}


	if (addressEdit->text().isEmpty()) {
		missing = trUtf8("Adres");
		addressEdit->setFocus();
		return false;
	}

	if (nipEdit->text().isEmpty()) {
		missing = trUtf8("Nip");
		nipEdit->setFocus();
		return false;
	}

	return true;
}

/** validate()
 */
bool Kontrahenci::validate() {
	QString missing;

	if (!validateForm(missing)) {
		QMessageBox::critical(
				0,
				"QFaktury",
				trUtf8("Kontrahent nie moze zostać zapisany pownieważ brakuje wymaganych danych w polu: ") + missing);
		return false;
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

