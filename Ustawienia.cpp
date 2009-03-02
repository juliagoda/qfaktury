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
    connect(defTextBtn, SIGNAL(clicked()), this, SLOT(defTextBtnClick()));
    connect( cb1, SIGNAL( stateChanged(int) ), this, SLOT( cb1Changed() ) );
    connect( cb2, SIGNAL( stateChanged(int) ), this, SLOT( cb2Changed() ) );
    connect( cb3, SIGNAL( stateChanged(int) ), this, SLOT( cb3Changed() ) );
    connect( cb4, SIGNAL( stateChanged(int) ), this, SLOT( cb4Changed() ) );
    connect( cb5, SIGNAL( stateChanged(int) ), this, SLOT( cb5Changed() ) );
    connect( cb6, SIGNAL( stateChanged(int) ), this, SLOT( cb6Changed() ) );
    connect( cb7, SIGNAL( stateChanged(int) ), this, SLOT( cb7Changed() ) );
    connect( cb8, SIGNAL( stateChanged(int) ), this, SLOT( cb8Changed() ) );
    connect( cb9, SIGNAL( stateChanged(int) ), this, SLOT( cb9Changed() ) );
    connect( cb10, SIGNAL( stateChanged(int) ), this, SLOT( cb10Changed() ) );
    connect( cb11, SIGNAL( stateChanged(int) ), this, SLOT( cb11Changed() ) );
    connect( cb12, SIGNAL( stateChanged(int) ), this, SLOT( cb12Changed() ) );
    connect( cb13, SIGNAL( stateChanged(int) ), this, SLOT( cb13Changed() ) );
    connect( cb14, SIGNAL( stateChanged(int) ), this, SLOT( cb14Changed() ) );

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
	additText->setText ( UTF8("towar odebrałem zgodnie z fakturą") );
}

/** Slot - set all to default
 */
void Ustawienia::setDefaultClick() {
	if (QMessageBox::question(this, "QFaktury GPL", UTF8("Czy napewno chcesz przywrócic ustawienia domyślne?"),
			QMessageBox::Yes, QMessageBox::No) == QMessageBox::No)
		return;

	Settings settings;
	settings.resetSettings();

	// is this required?
	readSettings();
}


/** Slot add logo
 */
void Ustawienia::addLogoBtnClick()
{
 QString ofn = QFileDialog::getOpenFileName (this,UTF8("Wybierz plik do wstawienia jako logo"), "",
				       UTF8("Obrazki (*.jpg *.png)")
				       );

 logoEdit->setText( ofn );
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
		QMessageBox::information(this, UTF8("Uwaga!!"),UTF8("Nie można dodać. Pole jest puste."), QMessageBox::Ok);
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
		QMessageBox::information(this, "Uwaga!!", UTF8("Musisz coś zaznaczyś, żeby usuwać."),
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
		QMessageBox::information(this, "Uwaga!!", UTF8("Nie można dodać. Pole jest puste."),
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
		QMessageBox::information(this, "Uwaga!!", UTF8("Musisz coś zaznaczyś, żeby usuwać."),
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
		QMessageBox::information(this, "Uwaga!!",
				UTF8("Nie można dodać. Pole jest puste."), QMessageBox::Ok);
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
		QMessageBox::information(this, "Uwaga!!", UTF8("Musisz coś zaznaczyś, żeby usuwać."),
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
      QMessageBox::information (this, "Uwaga!!", UTF8("Nie można dodać. Pole jest puste."),
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
		QMessageBox::information(this, "Uwaga!!", UTF8("Musisz coś zaznaczyś, żeby usuwać."),
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
		QMessageBox::information(this, "Uwaga!!", UTF8("Musisz coś zaznaczyś, żeby usuwać."),
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
		QMessageBox::information(this, "Uwaga!!",
				UTF8("Nie można dodać. Pole jest puste."), QMessageBox::Ok);
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
		QMessageBox::information(this, "Uwaga!!", UTF8("Nie można przenieść w górę, już jest najwyżej."),
		QMessageBox::Ok);
		return;
	}

	if (selNr > 0) {
		QListWidgetItem *item = vatlBox->item(vatlBox->currentRow());
		vatlBox->takeItem(selNr);
		vatlBox->insertItem(selNr - 1, item);
		vatlBox->setCurrentRow(selNr - 1);
	} else {
		QMessageBox::information(this, "Uwaga!!", UTF8("Musisz coś zaznaczyć, żeby przesuwać."), QMessageBox::Ok);
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
		QMessageBox::information(this, "Uwaga!!", UTF8("Nie można przenieść w dół, już jest najniżej."),
				QMessageBox::Ok);
		return;
	}

	if (selNr >= 0) {
		QListWidgetItem *item = vatlBox->item(vatlBox->currentRow());
		vatlBox->takeItem(selNr);
		vatlBox->insertItem(selNr + 1, item);
		vatlBox->setCurrentRow(selNr + 1);
	} else {
		QMessageBox::information(this, "Uwaga!!", UTF8("Musisz coś zaznaczyć, żeby przesuwać."), QMessageBox::Ok);
		return;
	}
	zastButton->setEnabled(true);
}

/** Slot move payment value up
 */
void Ustawienia::paymUpBtnClick() {
	int selNr = paymlBox->currentRow();

	if (selNr == 0) {
		QMessageBox::information(this, "Uwaga!!", UTF8("Nie można przenieść w górę, już jest najwyżej."),
		QMessageBox::Ok);
		return;
	}

	if (selNr > 0) {
		QListWidgetItem *item = paymlBox->item(paymlBox->currentRow());
		paymlBox->takeItem(selNr);
		paymlBox->insertItem(selNr - 1, item);
		paymlBox->setCurrentRow(selNr - 1);
	} else {
		QMessageBox::information(this, "Uwaga!!", UTF8("Musisz coś zaznaczyć, żeby przesuwać."), QMessageBox::Ok);
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
		QMessageBox::information(this, "Uwaga!!", UTF8("Nie można przenieść w dół, już jest najniżej."),
				QMessageBox::Ok);
		return;
	}

	if (selNr >= 0) {
		QListWidgetItem *item = paymlBox->item(paymlBox->currentRow());
		paymlBox->takeItem(selNr);
		paymlBox->insertItem(selNr + 1, item);
		paymlBox->setCurrentRow(selNr + 1);
	} else {
		QMessageBox::information(this, "Uwaga!!", UTF8("Musisz coś zaznaczyć, żeby przesuwać."), QMessageBox::Ok);
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

/** Save all settings
 */
void Ustawienia::saveSettings() {
	Settings settings;

	settings.setValue("lang", langList->currentText());
	settings.setValue("localEnc", codecList->currentText());

	settings.beginGroup("printpos");
	settings.setValue("usernazwa", userinfonazwa->isChecked());
	settings.setValue("usermiejscowosc", userinfomiejscowosc->isChecked());
	settings.setValue("useradres", userinfoadres->isChecked());
	settings.setValue("userkonto", userinfokonto->isChecked());
	settings.setValue("usernip", userinfonip->isChecked());
	settings.setValue("userphone", userinfotel->isChecked());
	settings.setValue("usermail", userinfomail->isChecked());
	settings.setValue("userwww", userinfowww->isChecked());
	settings.setValue("clientnazwa", userinfonazwa_2->isChecked());
	settings.setValue("clientmiejscowosc", userinfomiejscowosc_2->isChecked());
	settings.setValue("clientadres", userinfoadres_2->isChecked());
	settings.setValue("clientkonto", userinfokonto_2->isChecked());
	settings.setValue("clientnip", userinfonip_2->isChecked());
	settings.setValue("clientphone", userinfotel_2->isChecked());
	settings.setValue("clientmail", userinfomail_2->isChecked());
	settings.setValue("clientwww", userinfowww_2->isChecked());
	settings.endGroup();

	settings.setValue("firstrun", false);
	settings.setValue("logo", logoEdit->text());
	settings.setValue("jednostki", getAll(currlBox));
	settings.setValue("stawki", getAll(vatlBox).remove("%"));
	settings.setValue("waluty", getAll(currencylBox));
	settings.setValue("pkorekty", getAll(korlBox));
	settings.setValue("payments", getAll(paymlBox)); // uwaga!! get first
	settings.setValue("paym1", paymlBox->item(0)->text());
	settings.setValue("addText", additText->toPlainText());

	// settings.setValue ("fiskal", checkBNetto->isChecked ());
	settings.setValue("prefix", prefixEdit->text());
	settings.setValue("sufix", sufixEdit->text());
	settings.setValue("day", cbDay->isChecked());
	settings.setValue("month", cbMonth->isChecked());
	settings.setValue("year", cbYear->isChecked());
	settings.setValue("edit", cbEdit->isChecked());
	settings.setValue("editSymbol", cbSmbEdit->isChecked());
	settings.setValue("editName", cbSmbEdit_2->isChecked());
	settings.setValue("shortYear", shortYear->isChecked());
	settings.setValue("chars_in_symbol", spbNumb->value());

	settings.beginGroup("faktury_pozycje");
	settings.setValue("Lp", cb1->isChecked());
	settings.setValue("Nazwa", cb2->isChecked());
	settings.setValue("Kod", cb3->isChecked());
	settings.setValue("pkwiu", cb4->isChecked());
	settings.setValue("ilosc", cb5->isChecked());
	settings.setValue("jm", cb6->isChecked());
	settings.setValue("cenajedn", cb7->isChecked());
	settings.setValue("wartnetto", cb8->isChecked());
	settings.setValue("rabatperc", cb9->isChecked());
	settings.setValue("rabatval", cb10->isChecked());
	settings.setValue("nettoafter", cb11->isChecked());
	settings.setValue("vatval", cb12->isChecked());
	settings.setValue("vatprice", cb13->isChecked());
	settings.setValue("bruttoval", cb14->isChecked());

}

/** Read all settings
 */
void Ustawienia::readSettings() {
	Settings settings;

	logoEdit->setText(settings.value("logo").toString());

	currlBox->clear();
	currlBox->addItems(settings.value("jednostki").toString().split("|"));
	vatlBox->clear();
	vatlBox->addItems(settings.value("stawki").toString().split("|"));
	currencylBox->clear();
	currencylBox->addItems(settings.value("waluty").toString().split("|"));
	paymlBox->clear();
	paymlBox->addItems(settings.value("payments").toString().split("|"));
	korlBox->clear();
	korlBox->addItems(settings.value("pkorekty").toString().split("|"));


	/*
	 settings.setValue ("payments",   getAll(paymlBox) ); // uwaga!! get first
	 settings.setValue ("paym1",   getAll(paymlBox)[0] );
	 */

	settings.beginGroup("faktury_pozycje");
	cb1->setChecked(settings.value("Lp").toBool());
	cb2->setChecked(settings.value("Nazwa").toBool());
	cb3->setChecked(settings.value("Kod").toBool());
	cb4->setChecked(settings.value("pkwiu").toBool());
	cb5->setChecked(settings.value("ilosc").toBool());
	cb6->setChecked(settings.value("jm").toBool());
	cb7->setChecked(settings.value("cenajedn").toBool());
	cb8->setChecked(settings.value("wartnetto").toBool());
	cb9->setChecked(settings.value("rabatperc").toBool());
	cb10->setChecked(settings.value("rabatval").toBool());
	cb11->setChecked(settings.value("nettoafter").toBool());
	cb12->setChecked(settings.value("vatval").toBool());
	cb13->setChecked(settings.value("vatprice").toBool());
	cb14->setChecked(settings.value("bruttoval").toBool());
	settings.endGroup();

	prefixEdit->setText(settings.value("prefix").toString());
	sufixEdit->setText(settings.value("sufix").toString());

	// if (settings.value ("addText") != "" )
	additText->setText(settings.value("addText").toString());

	// checkBNetto->setChecked (settings.readBoolEntry ("fiskal"));
	cbDay->setChecked(settings.value("day").toBool());
	cbMonth->setChecked(settings.value("month").toBool());
	cbYear->setChecked(settings.value("year").toBool());
	shortYear->setChecked(settings.value("shortYear").toBool());
	cbEdit->setChecked(settings.value("edit").toBool());

	cbSmbEdit->setChecked(settings.value("editSymbol").toBool());
	cbSmbEdit_2->setChecked(settings.value("editName").toBool());

	spbNumb->setValue(settings. value("chars_in_symbol").toInt());

	codecList->setCurrentIndex(5);

	langList->clear();
	langList->insertItem(0, "polski"); //@TODO
	// langList->setCurrentIndex(0);

	settings.beginGroup("printpos");
	userinfonazwa->setChecked(settings.value("usernazwa").toBool());
	userinfomiejscowosc->setChecked(settings.value("usermiejscowosc").toBool());
	userinfoadres->setChecked(settings.value("useradres").toBool());
	userinfokonto->setChecked(settings.value("userkonto").toBool());
	userinfonip->setChecked(settings.value("usernip").toBool());
	userinfotel->setChecked(settings.value("userphone").toBool());
	userinfomail->setChecked(settings.value("usermail").toBool());
	userinfowww->setChecked(settings.value("userwww").toBool());
	userinfonazwa_2->setChecked(settings.value("clientnazwa").toBool());
	userinfomiejscowosc_2->setChecked(
			settings.value("clientmiejscowosc").toBool());
	userinfoadres_2->setChecked(settings.value("clientadres").toBool());
	userinfokonto_2->setChecked(settings.value("clientkonto").toBool());
	userinfonip_2->setChecked(settings.value("clientnip").toBool());
	userinfotel_2->setChecked(settings.value("clientphone").toBool());
	userinfomail_2->setChecked(settings.value("clientmail").toBool());
	userinfowww_2->setChecked(settings.value("clientwww").toBool());
	settings.endGroup();


	/*
	 settings.setValue ("payments",   getAll(paymlBox) ); // uwaga!! get first
	 settings.setValue ("paym1",   getAll(paymlBox)[0] );
	 */
	prefixEdit->setText(settings.value("prefix").toString());

	cbDay->setChecked(settings.value/*bool*/("day") .toBool());
	cbMonth->setChecked(settings.value/*bool*/("month") .toBool());
	cbYear->setChecked(settings.value/*bool*/("year") .toBool());
	shortYear->setChecked(settings.value/*bool*/("shortYear") .toBool());
	cbEdit->setChecked(settings.value/*bool*/("edit") .toBool());
	cbSmbEdit->setChecked(settings.value/*bool*/("editSymbol") .toBool());
	spbNumb->setValue(settings.value/*int*/("chars_in_symbol").toInt());

	read=true;
	// readTemplate();
}



