#include "Ustawienia.moc"
#include <qtextcodec.h>
#include "Settings.h"
#include <qfiledialog.h>


#include <qprinter.h>
#include <qpainter.h>
#include <qimage.h>
#include <qpicture.h>

#include <qdatetime.h>
#include <qdir.h>
#include <Qt/qdom.h>
#include <qfont.h>

#include <qmessagebox.h>
#include <qapplication.h>

// #include "preview.h"


Ustawienia::Ustawienia(QWidget *parent) :
	QDialog(parent) {
	setupUi(this);
	init();
}

void Ustawienia::init() {

	// connect all slots
	connect(zastButton, SIGNAL(clicked()), this, SLOT(apply()));
	connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
	connect(okButton, SIGNAL(clicked()), this, SLOT(okButtonClick()));
	connect(currAddBtn, SIGNAL(clicked()), this, SLOT(currAddBtnClick()));
	connect(currDelBtn, SIGNAL(clicked()), this, SLOT(currDelBtnClick()));
	connect(currencyAddBtn, SIGNAL(clicked()), this, SLOT(currencyAddBtnClick()));
	connect(currencyDelBtn, SIGNAL(clicked()), this, SLOT(currencyDelBtnClick()));
	connect(paymAddBtn, SIGNAL(clicked()), this, SLOT(paymAddBtnClick()));
	connect(paymDelBtn, SIGNAL(clicked()), this, SLOT(paymDelBtnClick()));
	connect(paymDownBtn, SIGNAL(clicked()), this, SLOT(paymDownBtnClick()));
	connect(paymUpBtn, SIGNAL(clicked()), this, SLOT(paymUpBtnClick()));
	connect(vatAddBtn, SIGNAL(clicked()), this, SLOT(vatAddBtnClick()));
	connect(vatDelBtn, SIGNAL(clicked()), this, SLOT(vatDelBtnClick()));
	connect(korAddBtn, SIGNAL(clicked()), this, SLOT(korAddBtnClick()));
	connect(korDelBtn, SIGNAL(clicked()), this, SLOT(korDelBtnClick()));
	connect(vatUpBtn, SIGNAL(clicked()), this, SLOT(vatUpBtnClick()));
	connect(vatDownBtn, SIGNAL(clicked()), this, SLOT(vatDownBtnClick()));
	connect(addLogoBtn, SIGNAL(clicked()), this, SLOT(addLogoBtnClick()));
	connect(pushButton, SIGNAL(clicked()), this, SLOT(setDefaultClick()));

	// QFaktury 0.6.0
    connect( logoEdit, SIGNAL( editingFinished ()), this, SLOT( zastBtnEnable() ) );
    connect( prefixEdit, SIGNAL( editingFinished () ), this, SLOT( zastBtnEnable() ) );
    connect( sufixEdit, SIGNAL( editingFinished () ), this, SLOT( zastBtnEnable() ) );
    connect( spbNumb, SIGNAL( editingFinished () ), this, SLOT( zastBtnEnable() ) );
    connect( cbDay, SIGNAL( stateChanged(int) ), this, SLOT( zastBtnEnable()) );
    connect( cbMonth, SIGNAL( stateChanged(int) ), this, SLOT( zastBtnEnable() ) );
    connect( cbYear, SIGNAL( stateChanged(int) ), this, SLOT( zastBtnEnable() ) );
    connect( shortYear, SIGNAL( stateChanged(int) ), this, SLOT( zastBtnEnable() ) );
    connect( cbEdit, SIGNAL( stateChanged(int) ), this, SLOT( zastBtnEnable() ) );
    connect( cbSmbEdit, SIGNAL( stateChanged(int) ), this, SLOT( zastBtnEnable() ) );
    connect( cbSmbEdit_2, SIGNAL( stateChanged(int) ), this, SLOT( zastBtnEnable() ) );
    connect( additText,  SIGNAL( textChanged() ), this, SLOT( zastBtnEnable() ) );
    connect( userinfonazwa, SIGNAL( stateChanged(int) ), this, SLOT( zastBtnEnable() ) );
	connect( userinfomiejscowosc, SIGNAL( stateChanged(int) ), this, SLOT( zastBtnEnable() ) );
	connect( userinfoadres, SIGNAL( stateChanged(int) ), this, SLOT( zastBtnEnable() ) );
    connect( userinfokonto, SIGNAL( stateChanged(int) ), this, SLOT( zastBtnEnable() ) );
    connect( userinfonip, SIGNAL( stateChanged(int) ), this, SLOT( zastBtnEnable() ) );
    connect( userinfotel, SIGNAL( stateChanged(int) ), this, SLOT( zastBtnEnable() ) );
    connect( userinfomail, SIGNAL( stateChanged(int) ), this, SLOT( zastBtnEnable() ) );
    connect( userinfowww, SIGNAL( stateChanged(int) ), this, SLOT( zastBtnEnable() ) );
    connect( userinfonazwa_2, SIGNAL( stateChanged(int) ), this, SLOT( zastBtnEnable() ) );
    connect( userinfomiejscowosc_2, SIGNAL( stateChanged(int) ), this, SLOT( zastBtnEnable() ) );
    connect( userinfoadres_2, SIGNAL( stateChanged(int) ), this, SLOT( zastBtnEnable() ) );
    connect( userinfokonto_2, SIGNAL( stateChanged(int) ), this, SLOT( zastBtnEnable() ) );
    connect( userinfonip_2, SIGNAL( stateChanged(int) ), this, SLOT( zastBtnEnable() ) );
    connect( userinfotel_2, SIGNAL( stateChanged(int) ), this, SLOT( zastBtnEnable() ) );
    connect( userinfomail_2, SIGNAL( stateChanged(int) ), this, SLOT( zastBtnEnable() ) );
    connect( userinfowww_2, SIGNAL( stateChanged(int) ), this, SLOT( zastBtnEnable() ) );

    getEncodings();
    readSettings();

    // disable apply button :)
    zastButton->setEnabled(false);
}

/** Slot - Apply
 */
void Ustawienia::apply ()
{
  saveSettings ();
  zastButton->setEnabled(false);
}

/** Slot - OK
 */
void Ustawienia::okButtonClick () {
  saveSettings ();
  accept ();
}

/** Slot applyBtn
 */
void Ustawienia::zastBtnEnable()
{
    zastButton->setEnabled(true);
}


/** Slot - set default text
 */
void Ustawienia::defTextBtnClick() {
	additText->setText ( trUtf8("towar odebrałem zgodnie z fakturą") );
}

/** Slot - set all to default
 */
void Ustawienia::setDefaultClick() {
	if (QMessageBox::question(this, "QFaktury GPL", trUtf8("Czy napewno chcesz przywrócic ustawienia domyślne?"),
			QMessageBox::Yes, QMessageBox::No) == QMessageBox::No)
		return;

	sett().resetSettings();
	// is this required?
	readSettings();
}


/** Slot add logo
 */
void Ustawienia::addLogoBtnClick() {
	QString ofn = QFileDialog::getOpenFileName(this, trUtf8("Wybierz plik do wstawienia jako logo"), "",
			trUtf8("Obrazki (*.jpg *.png)"));

	logoEdit->setText(ofn);
	zastButton->setEnabled(true);
}

//----------------------- List box Slots START ---
//@TODO merge into 1 function

/** Slot add currency
 */
void Ustawienia::currAddBtnClick() {
	if (currEdit->text() != "") {
		currlBox->addItem(currEdit->text());
		currEdit->clear();
	} else {
		QMessageBox::information(this, trUtf8("Uwaga!!"),trUtf8("Nie można dodać. Pole jest puste."), QMessageBox::Ok);
		return;
	}
	zastButton->setEnabled(true);
}


/** Slot del currency
 */
void Ustawienia::currDelBtnClick() {
	int selNr = currlBox->currentRow();
	if (selNr >= 0) {
		currlBox->takeItem(selNr);
	} else {
		QMessageBox::information(this, trUtf8("Uwaga!!"), trUtf8("Musisz coś zaznaczyś, żeby usuwać."),
		QMessageBox::Ok);
		return;
	}
	zastButton->setEnabled(true);
}

/** Slot korekty reason add
 */
void Ustawienia::korAddBtnClick() {
	//    qDebug( "%s, %s, %d", __FUNCTION__ , __FILE__, __LINE__);
	if (korEdit->text() != "") {
		korlBox->addItem(korEdit->text());
		korEdit->clear();
	} else {
		QMessageBox::information(this, trUtf8("Uwaga!!"), trUtf8("Nie można dodać. Pole jest puste."),
		QMessageBox::Ok);
		return;
	}
	zastButton->setEnabled(true);
}

/** Slot korekty reason delete
 */
void Ustawienia::korDelBtnClick() {
	int selNr = korlBox->currentRow();
	if (selNr >= 0) {
		korlBox->takeItem(selNr);
	} else {
		QMessageBox::information(this, trUtf8("Uwaga!!"), trUtf8("Musisz coś zaznaczyś, żeby usuwać."),
		QMessageBox::Ok);
		return;
	}
	zastButton->setEnabled(true);
}

/** Slot predefined VAT value add
 */
void Ustawienia::vatAddBtnClick() {
	//  qDebug( "%s, %s, %d", __FUNCTION__ , __FILE__, __LINE__);
	if (vatEdit->text() != "") {
		vatlBox->addItem(vatEdit->text());
		vatEdit->clear();
	} else {
		QMessageBox::information(this, trUtf8("Uwaga!!"),
				trUtf8("Nie można dodać. Pole jest puste."), QMessageBox::Ok);
		return;
	}
	zastButton->setEnabled(true);
}

/** Slot predefined VAT value delete
 */
void Ustawienia::vatDelBtnClick()
{
	int selNr = vatlBox->currentRow();
	if (selNr >= 0) {
		vatlBox->takeItem(selNr);
	} else {
		QMessageBox::information(this, trUtf8("Uwaga!!"), trUtf8("Musisz coś zaznaczyć, żeby usuwać."),
		QMessageBox::Ok);
		return;
	}
	zastButton->setEnabled(true);
}

/** Slot add currency
 */
void Ustawienia::currencyAddBtnClick()
{
    if ( currencyEdit->text() != "" ) {
	currencylBox->addItem(currencyEdit->text());
	currencyEdit->clear();
    } else {
      QMessageBox::information (this, trUtf8("Uwaga!!"), trUtf8("Nie można dodać. Pole jest puste."),
				QMessageBox::Ok);
      return;
    }
   zastButton->setEnabled(true);
}

/** Slot del currency
 */
void Ustawienia::currencyDelBtnClick() {
	int selNr = currencylBox->currentRow();
	if (selNr >= 0) {
		currencylBox->takeItem(selNr);
	} else {
		QMessageBox::information(this, trUtf8("Uwaga!!"), trUtf8("Musisz coś zaznaczyś, żeby usuwać."),
		QMessageBox::Ok);
		return;
	}
   zastButton->setEnabled(true);
}

/** Slot delete payment type click
 */
void Ustawienia::paymDelBtnClick() {
	int selNr = paymlBox->currentRow();
	if (selNr >= 0) {
		paymlBox->takeItem(selNr);
	} else {
		QMessageBox::information(this, trUtf8("Uwaga!!"), trUtf8("Musisz coś zaznaczyś, żeby usuwać."),
		QMessageBox::Ok);
		return;
	}
   zastButton->setEnabled(true);
}

/** Slot add payment type click
 */
void Ustawienia::paymAddBtnClick() {
	//  qDebug( "%s, %s, %d", __FUNCTION__ , __FILE__, __LINE__);
	if (paymEdit->text() != "") {
		paymlBox->addItem(paymEdit->text());
		paymEdit->clear();
	} else {
		QMessageBox::information(this, trUtf8("Uwaga!!"),
				trUtf8("Nie można dodać. Pole jest puste."), QMessageBox::Ok);
		return;
	}
	zastButton->setEnabled(true);
}
//----------------------- List box Slots END ---

//---------------------- UP DOWN SLOTS START----
/** Slot move VAT value up
 */
void Ustawienia::vatUpBtnClick() {
	int selNr = vatlBox->currentRow();

	if (selNr == 0) {
		QMessageBox::information(this, trUtf8("Uwaga!!"), trUtf8("Nie można przenieść w górę, już jest najwyżej."),
		QMessageBox::Ok);
		return;
	}

	if (selNr > 0) {
		QListWidgetItem *item = vatlBox->item(vatlBox->currentRow());
		vatlBox->takeItem(selNr);
		vatlBox->insertItem(selNr - 1, item);
		vatlBox->setCurrentRow(selNr - 1);
	} else {
		QMessageBox::information(this, trUtf8("Uwaga!!"), trUtf8("Musisz coś zaznaczyć, żeby przesuwać."), QMessageBox::Ok);
		return;
	}
	zastButton->setEnabled(true);
}

/** Slot move VAT value down
 */
void Ustawienia::vatDownBtnClick() {
	int selNr = vatlBox->currentRow();
	int recCount = vatlBox->count();
	qDebug() << selNr << recCount;

	if (selNr == recCount - 1) {
		QMessageBox::information(this, trUtf8("Uwaga!!"), trUtf8("Nie można przenieść w dół, już jest najniżej."),
				QMessageBox::Ok);
		return;
	}

	if (selNr >= 0) {
		QListWidgetItem *item = vatlBox->item(vatlBox->currentRow());
		vatlBox->takeItem(selNr);
		vatlBox->insertItem(selNr + 1, item);
		vatlBox->setCurrentRow(selNr + 1);
	} else {
		QMessageBox::information(this, trUtf8("Uwaga!!"), trUtf8("Musisz coś zaznaczyć, żeby przesuwać."), QMessageBox::Ok);
		return;
	}
	zastButton->setEnabled(true);
}

/** Slot move payment value up
 */
void Ustawienia::paymUpBtnClick() {
	int selNr = paymlBox->currentRow();

	if (selNr == 0) {
		QMessageBox::information(this, trUtf8("Uwaga!!"), trUtf8("Nie można przenieść w górę, już jest najwyżej."),
		QMessageBox::Ok);
		return;
	}

	if (selNr > 0) {
		QListWidgetItem *item = paymlBox->item(paymlBox->currentRow());
		paymlBox->takeItem(selNr);
		paymlBox->insertItem(selNr - 1, item);
		paymlBox->setCurrentRow(selNr - 1);
	} else {
		QMessageBox::information(this, trUtf8("Uwaga!!"), trUtf8("Musisz coś zaznaczyć, żeby przesuwać."), QMessageBox::Ok);
		return;
	}
	zastButton->setEnabled(true);
}

/** Slot move payment value down
 */
void Ustawienia::paymDownBtnClick() {
	int selNr = paymlBox->currentRow();
	int recCount = paymlBox->count();

	if (selNr == recCount - 1) {
		QMessageBox::information(this, trUtf8("Uwaga!!"), trUtf8("Nie można przenieść w dół, już jest najniżej."),
				QMessageBox::Ok);
		return;
	}

	if (selNr >= 0) {
		QListWidgetItem *item = paymlBox->item(paymlBox->currentRow());
		paymlBox->takeItem(selNr);
		paymlBox->insertItem(selNr + 1, item);
		paymlBox->setCurrentRow(selNr + 1);
	} else {
		QMessageBox::information(this, trUtf8("Uwaga!!"), trUtf8("Musisz coś zaznaczyć, żeby przesuwać."), QMessageBox::Ok);
		return;
	}
	zastButton->setEnabled(true);
}
//---------------------- UP DOWN SLOTS END----





// ------------- SLOTS for items on the invoice START ----
void Ustawienia::getEncodings() {
	QMap<QString, QTextCodec *> codecMap;
	QRegExp iso8859RegExp("ISO[- ]8859-([0-9]+).*");

	QList<QTextCodec *> codecs;

	foreach (int mib, QTextCodec::availableMibs()) {
			QTextCodec *codec = QTextCodec::codecForMib(mib);

			QString sortKey = codec->name().toUpper();
			int rank;

			if (sortKey.startsWith("UTF-8")) {
				rank = 1;
			} else if (sortKey.startsWith("UTF-16")) {
				rank = 2;
			} else if (iso8859RegExp.exactMatch(sortKey)) {
				if (iso8859RegExp.cap(1).size() == 1)
					rank = 3;
				else
					rank = 4;
			} else {
				rank = 5;
			}
			sortKey.prepend(QChar('0' + rank));

			codecMap.insert(sortKey, codec);
		}
	codecs = codecMap.values();

	codecList->clear();
	foreach (QTextCodec *codec, codecs)
			codecList->addItem(codec->name(), codec->mibEnum());
}

/** Used for parsing
 */
QString Ustawienia::getAll(QListWidget *lb)
{
  QString tmp;
  int selNr, posCount = lb->count ();
  for (selNr = 0; selNr < posCount; ++selNr)
    {
	  tmp += lb->item(selNr)->text();
	  if (selNr != posCount -1)
		  tmp += "|";
    }
 return  tmp;
}

/** Save all sett()
 */
void Ustawienia::saveSettings() {
	sett().setValue("lang", langList->currentText());
	sett().setValue("localEnc", codecList->currentText());

	sett().beginGroup("printpos");
	sett().setValue("usernazwa", userinfonazwa->isChecked());
	sett().setValue("usermiejscowosc", userinfomiejscowosc->isChecked());
	sett().setValue("useradres", userinfoadres->isChecked());
	sett().setValue("userkonto", userinfokonto->isChecked());
	sett().setValue("usernip", userinfonip->isChecked());
	sett().setValue("userphone", userinfotel->isChecked());
	sett().setValue("usermail", userinfomail->isChecked());
	sett().setValue("userwww", userinfowww->isChecked());
	sett().setValue("clientnazwa", userinfonazwa_2->isChecked());
	sett().setValue("clientmiejscowosc", userinfomiejscowosc_2->isChecked());
	sett().setValue("clientadres", userinfoadres_2->isChecked());
	sett().setValue("clientkonto", userinfokonto_2->isChecked());
	sett().setValue("clientnip", userinfonip_2->isChecked());
	sett().setValue("clientphone", userinfotel_2->isChecked());
	sett().setValue("clientmail", userinfomail_2->isChecked());
	sett().setValue("clientwww", userinfowww_2->isChecked());
	sett().endGroup();

	sett().setValue("firstrun", false);
	sett().setValue("logo", logoEdit->text());
	sett().setValue("jednostki", getAll(currlBox));
	sett().setValue("stawki", getAll(vatlBox).remove("%"));
	sett().setValue("waluty", getAll(currencylBox));
	sett().setValue("pkorekty", getAll(korlBox));
	sett().setValue("payments", getAll(paymlBox)); // uwaga!! get first
	sett().setValue("paym1", paymlBox->item(0)->text());
	sett().setValue("addText", additText->toPlainText());

	// sett().setValue ("fiskal", checkBNetto->isChecked ());
	sett().setValue("prefix", prefixEdit->text());
	sett().setValue("sufix", sufixEdit->text());
	sett().setValue("day", cbDay->isChecked());
	sett().setValue("month", cbMonth->isChecked());
	sett().setValue("year", cbYear->isChecked());
	sett().setValue("edit", cbEdit->isChecked());
	sett().setValue("editSymbol", cbSmbEdit->isChecked());
	sett().setValue("editName", cbSmbEdit_2->isChecked());
	sett().setValue("shortYear", shortYear->isChecked());
	sett().setValue("chars_in_symbol", spbNumb->value());

	sett().beginGroup("faktury_pozycje");
	sett().setValue("Lp", cb1->isChecked());
	sett().setValue("Nazwa", cb2->isChecked());
	sett().setValue("Kod", cb3->isChecked());
	sett().setValue("pkwiu", cb4->isChecked());
	sett().setValue("ilosc", cb5->isChecked());
	sett().setValue("jm", cb6->isChecked());
	sett().setValue("cenajedn", cb7->isChecked());
	sett().setValue("wartnetto", cb8->isChecked());
	sett().setValue("rabatperc", cb9->isChecked());
	sett().setValue("rabatval", cb10->isChecked());
	sett().setValue("nettoafter", cb11->isChecked());
	sett().setValue("vatval", cb12->isChecked());
	sett().setValue("vatprice", cb13->isChecked());
	sett().setValue("bruttoval", cb14->isChecked());
	sett().endGroup();

}

/** Read all sett()
 */
void Ustawienia::readSettings() {
	logoEdit->setText(sett().value("logo").toString());
	currlBox->clear();
	currlBox->addItems(sett().value("jednostki").toString().split("|"));
	vatlBox->clear();
	vatlBox->addItems(sett().value("stawki").toString().split("|"));
	currencylBox->clear();
	currencylBox->addItems(sett().value("waluty").toString().split("|"));
	paymlBox->clear();
	paymlBox->addItems(sett().value("payments").toString().split("|"));
	korlBox->clear();
	korlBox->addItems(sett().value("pkorekty").toString().split("|"));


	/*
	 sett().setValue ("payments",   getAll(paymlBox) ); // uwaga!! get first
	 sett().setValue ("paym1",   getAll(paymlBox)[0] );
	 */

	sett().beginGroup("faktury_pozycje");
	cb1->setChecked(sett().value("Lp").toBool());
	cb2->setChecked(sett().value("Nazwa").toBool());
	cb3->setChecked(sett().value("Kod").toBool());
	cb4->setChecked(sett().value("pkwiu").toBool());
	cb5->setChecked(sett().value("ilosc").toBool());
	cb6->setChecked(sett().value("jm").toBool());
	cb7->setChecked(sett().value("cenajedn").toBool());
	cb8->setChecked(sett().value("wartnetto").toBool());
	cb9->setChecked(sett().value("rabatperc").toBool());
	cb10->setChecked(sett().value("rabatval").toBool());
	cb11->setChecked(sett().value("nettoafter").toBool());
	cb12->setChecked(sett().value("vatval").toBool());
	cb13->setChecked(sett().value("vatprice").toBool());
	cb14->setChecked(sett().value("bruttoval").toBool());
	sett().endGroup();

	prefixEdit->setText(sett().value("prefix").toString());
	sufixEdit->setText(sett().value("sufix").toString());

	// if (sett().value ("addText") != "" )
	additText->setText(sett().value("addText").toString());

	// checkBNetto->setChecked (sett().readBoolEntry ("fiskal"));
	cbDay->setChecked(sett().value("day").toBool());
	cbMonth->setChecked(sett().value("month").toBool());
	cbYear->setChecked(sett().value("year").toBool());
	shortYear->setChecked(sett().value("shortYear").toBool());
	cbEdit->setChecked(sett().value("edit").toBool());

	cbSmbEdit->setChecked(sett().value("editSymbol").toBool());
	cbSmbEdit_2->setChecked(sett().value("editName").toBool());

	spbNumb->setValue(sett(). value("chars_in_symbol").toInt());

	codecList->setCurrentIndex(5);

	langList->clear();
	langList->insertItem(0, "polski"); //@TODO
	// langList->setCurrentIndex(0);

	sett().beginGroup("printpos");
	userinfonazwa->setChecked(sett().value("usernazwa").toBool());
	userinfomiejscowosc->setChecked(sett().value("usermiejscowosc").toBool());
	userinfoadres->setChecked(sett().value("useradres").toBool());
	userinfokonto->setChecked(sett().value("userkonto").toBool());
	userinfonip->setChecked(sett().value("usernip").toBool());
	userinfotel->setChecked(sett().value("userphone").toBool());
	userinfomail->setChecked(sett().value("usermail").toBool());
	userinfowww->setChecked(sett().value("userwww").toBool());
	userinfonazwa_2->setChecked(sett().value("clientnazwa").toBool());
	userinfomiejscowosc_2->setChecked(
			sett().value("clientmiejscowosc").toBool());
	userinfoadres_2->setChecked(sett().value("clientadres").toBool());
	userinfokonto_2->setChecked(sett().value("clientkonto").toBool());
	userinfonip_2->setChecked(sett().value("clientnip").toBool());
	userinfotel_2->setChecked(sett().value("clientphone").toBool());
	userinfomail_2->setChecked(sett().value("clientmail").toBool());
	userinfowww_2->setChecked(sett().value("clientwww").toBool());
	sett().endGroup();


	/*
	 sett().setValue ("payments",   getAll(paymlBox) ); // uwaga!! get first
	 sett().setValue ("paym1",   getAll(paymlBox)[0] );
	 */
	prefixEdit->setText(sett().value("prefix").toString());

	cbDay->setChecked(sett().value/*bool*/("day") .toBool());
	cbMonth->setChecked(sett().value/*bool*/("month") .toBool());
	cbYear->setChecked(sett().value/*bool*/("year") .toBool());
	shortYear->setChecked(sett().value/*bool*/("shortYear") .toBool());
	cbEdit->setChecked(sett().value/*bool*/("edit") .toBool());
	cbSmbEdit->setChecked(sett().value/*bool*/("editSymbol") .toBool());
	spbNumb->setValue(sett().value/*int*/("chars_in_symbol").toInt());

	read=true;
	// readTemplate();
}



