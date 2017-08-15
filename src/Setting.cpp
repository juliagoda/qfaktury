#include <QFileDialog>

#include "Setting.h"
#include "Settings.h"

Setting::Setting(QWidget *parent)
	: QDialog(parent)
{
	setupUi(this);
	init();
}

Setting::~Setting()
{
}

void Setting::init()
{
	// connect all slots
	connect(saveButton, SIGNAL(clicked()), this, SLOT(apply()));
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
	connect(corAddBtn, SIGNAL(clicked()), this, SLOT(corAddBtnClick()));
	connect(corDelBtn, SIGNAL(clicked()), this, SLOT(corDelBtnClick()));
	connect(vatUpBtn, SIGNAL(clicked()), this, SLOT(vatUpBtnClick()));
	connect(vatDownBtn, SIGNAL(clicked()), this, SLOT(vatDownBtnClick()));
	connect(addLogoBtn, SIGNAL(clicked()), this, SLOT(addLogoBtnClick()));
	connect(addStempelBtn, SIGNAL(clicked()), this, SLOT(addStempBtnClick()));
	connect(workingDirBtn, SIGNAL(clicked()), this, SLOT(workingDirBtnClick()));
	connect(pushButton, SIGNAL(clicked()), this, SLOT(setDefaultClick()));
	connect(defTextBtn, SIGNAL(clicked()), this, SLOT(defTextBtnClick()));
	connect(cssList, SIGNAL(currentIndexChanged(int)), this, SLOT(saveBtnEnable()));
	connect(stylesList, SIGNAL(currentIndexChanged(int)), this, SLOT(saveBtnEnable()));
	connect(codecList, SIGNAL(currentIndexChanged(int)), this, SLOT(saveBtnEnable()));
	connect(logoEdit, SIGNAL(textChanged(const QString &)), this, SLOT(saveBtnEnable()));
	connect(stempEdit, SIGNAL(textChanged(const QString &)), this, SLOT(saveBtnEnable()));
	connect(workingDirEdit, SIGNAL(textChanged(const QString &)), this, SLOT(saveBtnEnable()));
	connect(prefixEdit, SIGNAL(textChanged(const QString &)), this, SLOT(saveBtnEnable()));
	connect(sufixEdit, SIGNAL(textChanged(const QString &)), this, SLOT(saveBtnEnable()));
	connect(spbNumb, SIGNAL(valueChanged(const QString &)), this, SLOT(saveBtnEnable()));
	connect(spbNumCopies, SIGNAL(valueChanged(const QString &)), this, SLOT(saveBtnEnable()));
	connect(cbDay, SIGNAL(stateChanged(int)), this, SLOT(saveBtnEnable()));
	connect(cbMonth, SIGNAL(stateChanged(int)), this, SLOT(saveBtnEnable()));
	connect(cbYear, SIGNAL(stateChanged(int)), this, SLOT(saveBtnEnable()));
	connect(shortYear, SIGNAL(stateChanged(int)), this, SLOT(saveBtnEnable()));
	connect(cbEdit, SIGNAL(stateChanged(int)), this, SLOT(saveBtnEnable()));
	connect(cbSmbEdit, SIGNAL(stateChanged(int)), this, SLOT(saveBtnEnable()));
	connect(cbSmbEdit_2, SIGNAL(stateChanged(int)), this, SLOT(saveBtnEnable()));
	connect(additText, SIGNAL(textChanged()), this, SLOT(saveBtnEnable()));
	connect(userinfoname, SIGNAL(stateChanged(int)), this, SLOT(saveBtnEnable()));
	connect(userinfocity, SIGNAL(stateChanged(int)), this, SLOT(saveBtnEnable()));
	connect(userinfoadress, SIGNAL(stateChanged(int)), this, SLOT(saveBtnEnable()));
	connect(userinfoaccount, SIGNAL(stateChanged(int)), this, SLOT(saveBtnEnable()));
	connect(userinfonip, SIGNAL(stateChanged(int)), this, SLOT(saveBtnEnable()));
	connect(userinfotel, SIGNAL(stateChanged(int)), this, SLOT(saveBtnEnable()));
	connect(userinfomail, SIGNAL(stateChanged(int)), this, SLOT(saveBtnEnable()));
	connect(userinfowww, SIGNAL(stateChanged(int)), this, SLOT(saveBtnEnable()));
	connect(userinfobank, SIGNAL(stateChanged(int)), this, SLOT(saveBtnEnable()));
	connect(userinfofax, SIGNAL(stateChanged(int)), this, SLOT(saveBtnEnable()));
	connect(userinfokrs, SIGNAL(stateChanged(int)), this, SLOT(saveBtnEnable()));
	connect(userinfoswift, SIGNAL(stateChanged(int)), this, SLOT(saveBtnEnable()));
	connect(buyerinfoname, SIGNAL(stateChanged(int)), this, SLOT(saveBtnEnable()));
	connect(buyerinfocity, SIGNAL(stateChanged(int)), this, SLOT(saveBtnEnable()));
	connect(buyerinfoaddress, SIGNAL(stateChanged(int)), this, SLOT(saveBtnEnable()));
	connect(buyerinfoaccount, SIGNAL(stateChanged(int)), this, SLOT(saveBtnEnable()));
	connect(buyerinfotic, SIGNAL(stateChanged(int)), this, SLOT(saveBtnEnable()));
	connect(buyerinfotel, SIGNAL(stateChanged(int)), this, SLOT(saveBtnEnable()));
	connect(buyerinfomail, SIGNAL(stateChanged(int)), this, SLOT(saveBtnEnable()));
	connect(buyerinfowww, SIGNAL(stateChanged(int)), this, SLOT(saveBtnEnable()));

	connect(cb1, SIGNAL(stateChanged(int)), this, SLOT(saveBtnEnable()));
	connect(cb2, SIGNAL(stateChanged(int)), this, SLOT(saveBtnEnable()));
	connect(cb3, SIGNAL(stateChanged(int)), this, SLOT(saveBtnEnable()));
	connect(cb4, SIGNAL(stateChanged(int)), this, SLOT(saveBtnEnable()));
	connect(cb5, SIGNAL(stateChanged(int)), this, SLOT(saveBtnEnable()));
	connect(cb6, SIGNAL(stateChanged(int)), this, SLOT(saveBtnEnable()));
	connect(cb7, SIGNAL(stateChanged(int)), this, SLOT(saveBtnEnable()));
	connect(cb8, SIGNAL(stateChanged(int)), this, SLOT(saveBtnEnable()));
	connect(cb9, SIGNAL(stateChanged(int)), this, SLOT(saveBtnEnable()));
	connect(cb10, SIGNAL(stateChanged(int)), this, SLOT(saveBtnEnable()));
	connect(cb11, SIGNAL(stateChanged(int)), this, SLOT(saveBtnEnable()));
	connect(cb12, SIGNAL(stateChanged(int)), this, SLOT(saveBtnEnable()));
	connect(cb13, SIGNAL(stateChanged(int)), this, SLOT(saveBtnEnable()));
	connect(cb14, SIGNAL(stateChanged(int)), this, SLOT(saveBtnEnable()));

	cssList->clear();
	cssList->insertItems(0, getTemplates());

	stylesList->clear();
	stylesList->insertItems(0, getStyles());

	stylesList->removeItem(stylesList->findText("bb10dark"));
	stylesList->removeItem(stylesList->findText("bb10bright"));

	getEncodings();
	readSettings();

	// disable apply button :)
	saveButton->setEnabled(false);
}

/** Slot - Apply
 */

void Setting::apply()
{
	saveSettings();
	saveButton->setEnabled(false);
	QMessageBox::information(
		this,
		trUtf8("Zapisywanie zmian"),
		trUtf8("Zmiany zostaną wprowadzone po zrestartowaniu programu"),
		QMessageBox::Ok);
}

/** Slot - OK
 */

void Setting::okButtonClick()
{
	saveSettings();
	accept();
}

/** Slot applyBtn
 */

void Setting::saveBtnEnable()
{
	saveButton->setEnabled(true);
}

/** Slot - set default text
 */

void Setting::defTextBtnClick()
{
	additText->setText(trUtf8("towar odebrałem zgodnie z fakturą"));
}

/** Slot - set all to default
 */

void Setting::setDefaultClick()
{
	if (QMessageBox::question(
			this,
			"QFaktury GPL",
			trUtf8("Czy napewno chcesz przywrócic ustawienia domyślne?"),
			QMessageBox::Yes,
			QMessageBox::No)
		== QMessageBox::No)
	{
		return;
	}

	sett().resetSettings();

	readSettings();
}

/** Slot used to change location of invoiced
 */

void Setting::workingDirBtnClick()
{
	QString dir = QFileDialog::getExistingDirectory(
		this,
		tr("Open Directory"),
		"/home",
		QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	dir += "~/.local/share/data";
	qDebug() << "Katalog roboczy" << dir;
	workingDirEdit->setText(dir);
	saveButton->setEnabled(true);
}

/** Slot add logo
 */

void Setting::addLogoBtnClick()
{
	QString ofn = QFileDialog::getOpenFileName(
		this, trUtf8("Wybierz plik do wstawienia jako logo"), "", trUtf8("Obrazki (*.jpg *.png)"));

	logoEdit->setText(ofn);
	saveButton->setEnabled(true);
}

void Setting::addStempBtnClick()
{
	QString ofn = QFileDialog::getOpenFileName(
		this,
		trUtf8("Wybierz plik do wstawienia jako pieczątka"),
		"",
		trUtf8("Obrazki (*.jpg *.png)"));

	stempEdit->setText(ofn);
	saveButton->setEnabled(true);
}

void Setting::helpFuncAddNr(QLineEdit *lineEd, QListWidget *listWg, QString const &text)
{
	if (lineEd->text() != "")
	{
		listWg->addItem(lineEd->text());
		lineEd->clear();
	}
	else
	{
		QMessageBox::information(this, trUtf8("Uwaga!!"), text, QMessageBox::Ok);
		return;
	}

	saveButton->setEnabled(true);
}

void Setting::helpFuncDelNr(QListWidget *listWg, QString const &text)
{
	int selNr = listWg->currentRow();
	if (selNr >= 0)
	{
		listWg->takeItem(selNr);
	}
	else
	{
		QMessageBox::information(this, trUtf8("Uwaga!!"), text, QMessageBox::Ok);
		return;
	}

	saveButton->setEnabled(true);
}

//----------------------- List box Slots START ---
//@TODO merge into 1 function

/** Slot add currency
 */

void Setting::currAddBtnClick()
{
	helpFuncAddNr(currEdit, currlBox, trUtf8("Nie można dodać. Pole jest puste."));
}

/** Slot del currency
 */

void Setting::currDelBtnClick()
{
	helpFuncDelNr(currlBox, trUtf8("Musisz coś zaznaczyś, żeby usuwać."));
}

/** Slot korekty reason add
 */

void Setting::corAddBtnClick()
{
	helpFuncAddNr(corEdit, correctsBox, trUtf8("Nie można dodać. Pole jest puste."));
}

/** Slot korekty reason delete
 */

void Setting::corDelBtnClick()
{
	helpFuncDelNr(correctsBox, trUtf8("Musisz coś zaznaczyś, żeby usuwać."));
}

/** Slot predefined VAT value add
 */

void Setting::vatAddBtnClick()
{
	helpFuncAddNr(vatEdit, vatlBox, trUtf8("Nie można dodać. Pole jest puste."));
}

/** Slot predefined VAT value delete
 */

void Setting::vatDelBtnClick()
{
	helpFuncDelNr(vatlBox, trUtf8("Musisz coś zaznaczyć, żeby usuwać."));
}

/** Slot add currency
 */

void Setting::currencyAddBtnClick()
{
	helpFuncAddNr(currencyEdit, currencylBox, trUtf8("Nie można dodać. Pole jest puste."));
}

/** Slot del currency
 */
void Setting::currencyDelBtnClick()
{
	helpFuncDelNr(currencylBox, trUtf8("Musisz coś zaznaczyś, żeby usuwać."));
}

/** Slot delete payment type click
 */
void Setting::paymDelBtnClick()
{
	helpFuncDelNr(paymlBox, trUtf8("Musisz coś zaznaczyś, żeby usuwać."));
}

/** Slot add payment type click
 */
void Setting::paymAddBtnClick()
{
	helpFuncAddNr(paymEdit, paymlBox, trUtf8("Nie można dodać. Pole jest puste."));
}

//----------------------- List box Slots END ---

void Setting::helpFuncAp(QListWidget *listWg)
{
	int selNr = listWg->currentRow();

	if (selNr == 0)
	{
		QMessageBox::information(
			this,
			trUtf8("Uwaga!!"),
			trUtf8("Nie można przenieść w górę, już jest najwyżej."),
			QMessageBox::Ok);
		return;
	}

	if (selNr > 0)
	{
		QListWidgetItem *item = listWg->item(listWg->currentRow());
		listWg->takeItem(selNr);
		listWg->insertItem(selNr - 1, item);
		listWg->setCurrentRow(selNr - 1);
	}
	else
	{
		QMessageBox::information(
			this,
			trUtf8("Uwaga!!"),
			trUtf8("Musisz coś zaznaczyć, żeby przesuwać."),
			QMessageBox::Ok);
		return;
	}

	saveButton->setEnabled(true);
}

void Setting::helpFuncDown(QListWidget *listWg)
{
	int selNr = listWg->currentRow();
	int recCount = listWg->count();
	// qDebug() << selNr << recCount;

	if (selNr == recCount - 1)
	{
		QMessageBox::information(
			this,
			trUtf8("Uwaga!!"),
			trUtf8("Nie można przenieść w dół, już jest najniżej."),
			QMessageBox::Ok);
		return;
	}

	if (selNr >= 0)
	{
		QListWidgetItem *item = listWg->item(listWg->currentRow());
		listWg->takeItem(selNr);
		listWg->insertItem(selNr + 1, item);
		listWg->setCurrentRow(selNr + 1);
	}
	else
	{
		QMessageBox::information(
			this,
			trUtf8("Uwaga!!"),
			trUtf8("Musisz coś zaznaczyć, żeby przesuwać."),
			QMessageBox::Ok);
		return;
	}

	saveButton->setEnabled(true);
}

//---------------------- UP DOWN SLOTS START----

/** Slot move VAT value up
 */

void Setting::vatUpBtnClick()
{
	helpFuncAp(vatlBox);
}

/** Slot move VAT value down
 */

void Setting::vatDownBtnClick()
{
	helpFuncDown(vatlBox);
}

/** Slot move payment value up
 */
void Setting::paymUpBtnClick()
{
	helpFuncAp(paymlBox);
}

/** Slot move payment value down
 */
void Setting::paymDownBtnClick()
{
	helpFuncDown(paymlBox);
}

//---------------------- UP DOWN SLOTS END----

// ------------- SLOTS for items on the invoice START ----

void Setting::getEncodings()
{
	QHash<QString, QTextCodec *> codecMap;
	QRegExp iso8859RegExp("ISO[- ]8859-([0-9]+).*");

	foreach (int mib, QTextCodec::availableMibs())
	{
		QTextCodec *codec = QTextCodec::codecForMib(mib);

		QString sortKey = codec->name().toUpper();
		int rank;

		if (sortKey.startsWith("UTF-8"))
		{
			rank = 1;
		}
		else if (sortKey.startsWith("UTF-16"))
		{
			rank = 2;
		}
		else if (iso8859RegExp.exactMatch(sortKey))
		{
			if (iso8859RegExp.cap(1).size() == 1)
			{
				rank = 3;
			}
			else
			{
				rank = 4;
			}
		}
		else
		{
			rank = 5;
		}

		sortKey.prepend(QChar('0' + rank));

		codecMap.insert(sortKey, codec);
	}

	codecs = codecMap.values().toVector();

	codecList->clear();

	foreach (QTextCodec *codec, codecs)
		codecList->addItem(codec->name(), codec->mibEnum());
}

/** Used for parsing
 */

QString Setting::getAll(QListWidget *lb) const
{
	QString tmp = QString();
	int selNr, posCount = lb->count();

	for (selNr = 0; selNr < posCount; ++selNr)
	{
		tmp += lb->item(selNr)->text();

		if (selNr != posCount - 1)
		{
			tmp += "|";
		}
	}

	return tmp;
}

/** Save all sett()
 */

void Setting::saveSettings()
{
	sett().setValue("css", cssList->currentText());
	sett().setValue("style", stylesList->currentText());
	sett().setValue("localEnc", codecList->currentText());
	sett().setValue("working_dir", workingDirEdit->text());

	sett().beginGroup("printpos");
	sett().setValue("username", userinfoname->isChecked());
	sett().setValue("usercity", userinfocity->isChecked());
	sett().setValue("useradress", userinfoadress->isChecked());
	sett().setValue("useraccount", userinfoaccount->isChecked());
	sett().setValue("usernip", userinfonip->isChecked());
	sett().setValue("userphone", userinfotel->isChecked());
	sett().setValue("usermail", userinfomail->isChecked());
	sett().setValue("userwww", userinfowww->isChecked());
	sett().setValue("userbank", userinfobank->isChecked());
	sett().setValue("userswift", userinfoswift->isChecked());
	sett().setValue("userkrs", userinfokrs->isChecked());
	sett().setValue("userfax", userinfofax->isChecked());
	sett().endGroup();

	sett().beginGroup("printkontr");
	sett().setValue("buyername", buyerinfoname->isChecked());
	sett().setValue("buyercity", buyerinfocity->isChecked());
	sett().setValue("buyeraddress", buyerinfoaddress->isChecked());
	sett().setValue("buyeraccount", buyerinfoaccount->isChecked());
	sett().setValue("buyernip", buyerinfotic->isChecked());
	sett().setValue("buyerphone", buyerinfotel->isChecked());
	sett().setValue("buyermail", buyerinfomail->isChecked());
	sett().setValue("buyerwww", buyerinfowww->isChecked());
	sett().endGroup();

	sett().setValue("firstrun", false);
	sett().setValue("logo", logoEdit->text());
	sett().setValue("stempel", stempEdit->text());
	sett().setValue("units", getAll(currlBox));
	sett().setValue("rates", getAll(vatlBox).remove("%"));
	sett().setValue("currencies", getAll(currencylBox));
	sett().setValue("corrections", getAll(correctsBox));
	sett().setValue("payments", getAll(paymlBox)); // attention!! get first
	sett().setValue("paym1", paymlBox->item(0)->text());
	sett().setValue("addText", additText->toPlainText());

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
	sett().setValue("numberOfCopies", spbNumCopies->value());

	sett().beginGroup("invoices_positions");
	sett().setValue("Lp", cb1->isChecked());
	sett().setValue("Name", cb2->isChecked());
	sett().setValue("Code", cb3->isChecked());
	sett().setValue("pkwiu", cb4->isChecked());
	sett().setValue("amount", cb5->isChecked());
	sett().setValue("unit", cb6->isChecked());
	sett().setValue("unitprice", cb7->isChecked());
	sett().setValue("netvalue", cb8->isChecked());
	sett().setValue("discountperc", cb9->isChecked());
	sett().setValue("discountval", cb10->isChecked());
	sett().setValue("netafter", cb11->isChecked());
	sett().setValue("vatval", cb12->isChecked());
	sett().setValue("vatprice", cb13->isChecked());
	sett().setValue("grossval", cb14->isChecked());
	sett().endGroup();
}

/** Read all sett()
 */

void Setting::readSettings()
{
	int curr = 0;

	logoEdit->setText(sett().value("logo").toString());
	stempEdit->setText(sett().value("stempel").toString());
	workingDirEdit->setText(sett().value("working_dir").toString());

	currlBox->clear();
	currlBox->addItems(sett().value("units").toString().split("|"));

	vatlBox->clear();
	vatlBox->addItems(sett().value("rates").toString().split("|"));

	currencylBox->clear();
	currencylBox->addItems(sett().value("currencies").toString().split("|"));

	paymlBox->clear();
	paymlBox->addItems(sett().value("payments").toString().split("|"));

	curr = codecs.indexOf(QTextCodec::codecForName(sett().value("localEnc").toByteArray()));
	codecList->setCurrentIndex(curr);

	correctsBox->clear();
	correctsBox->addItems(sett().value("corrections").toString().split("|"));

	curr = getTemplates().indexOf(sett().value("css").toString());
	cssList->setCurrentIndex(curr);

	curr = getStyles().indexOf(sett().value("style").toString());
	stylesList->setCurrentIndex(curr);

	sett().beginGroup("invoices_positions");
	cb1->setChecked(sett().value("Lp").toBool());
	cb2->setChecked(sett().value("Name").toBool());
	cb3->setChecked(sett().value("Code").toBool());
	cb4->setChecked(sett().value("pkwiu").toBool());
	cb5->setChecked(sett().value("amount").toBool());
	cb6->setChecked(sett().value("unit").toBool());
	cb7->setChecked(sett().value("unitprice").toBool());
	cb8->setChecked(sett().value("netvalue").toBool());
	cb9->setChecked(sett().value("discountperc").toBool());
	cb10->setChecked(sett().value("discountval").toBool());
	cb11->setChecked(sett().value("netafter").toBool());
	cb12->setChecked(sett().value("vatval").toBool());
	cb13->setChecked(sett().value("vatprice").toBool());
	cb14->setChecked(sett().value("grossval").toBool());
	sett().endGroup();

	prefixEdit->setText(sett().value("prefix").toString());
	sufixEdit->setText(sett().value("sufix").toString());

	additText->setText(sett().value("addText").toString());

	cbDay->setChecked(sett().value("day").toBool());
	cbMonth->setChecked(sett().value("month").toBool());
	cbYear->setChecked(sett().value("year").toBool());
	shortYear->setChecked(sett().value("shortYear").toBool());
	cbEdit->setChecked(sett().value("edit").toBool());

	cbSmbEdit->setChecked(sett().value("editSymbol").toBool());
	cbSmbEdit_2->setChecked(sett().value("editName").toBool());

	spbNumb->setValue(sett().value("chars_in_symbol").toInt());
	spbNumCopies->setValue(sett().value("numberOfCopies").toInt());

	sett().beginGroup("printpos");
	userinfoname->setChecked(sett().value("username").toBool());
	userinfocity->setChecked(sett().value("usercity").toBool());
	userinfoadress->setChecked(sett().value("useradress").toBool());
	userinfoaccount->setChecked(sett().value("useraccount").toBool());
	userinfonip->setChecked(sett().value("usernip").toBool());
	userinfotel->setChecked(sett().value("userphone").toBool());
	userinfomail->setChecked(sett().value("usermail").toBool());
	userinfowww->setChecked(sett().value("userwww").toBool());
	userinfowww->setChecked(sett().value("userwww").toBool());
	userinfobank->setChecked(sett().value("userbank").toBool());
	userinfokrs->setChecked(sett().value("userkrs").toBool());
	userinfofax->setChecked(sett().value("userfax").toBool());
	userinfoswift->setChecked(sett().value("userswift").toBool());
	sett().endGroup();

	sett().beginGroup("printkontr");
	buyerinfoname->setChecked(sett().value("buyername").toBool());
	buyerinfocity->setChecked(sett().value("buyercity").toBool());
	buyerinfoaddress->setChecked(sett().value("buyeraddress").toBool());
	buyerinfoaccount->setChecked(sett().value("buyeraccount").toBool());
	buyerinfotic->setChecked(sett().value("buyernip").toBool());
	buyerinfotel->setChecked(sett().value("buyerphone").toBool());
	buyerinfomail->setChecked(sett().value("buyermail").toBool());
	buyerinfowww->setChecked(sett().value("buyerwww").toBool());
	sett().endGroup();

	prefixEdit->setText(sett().value("prefix").toString());

	cbDay->setChecked(sett().value("day").toBool());
	cbMonth->setChecked(sett().value("month").toBool());
	cbYear->setChecked(sett().value("year").toBool());
	shortYear->setChecked(sett().value("shortYear").toBool());
	cbEdit->setChecked(sett().value("edit").toBool());
	cbSmbEdit->setChecked(sett().value("editSymbol").toBool());
	spbNumb->setValue(sett().value("chars_in_symbol").toInt());

	read = true;
}

// returns list of translations
QStringList Setting::getTemplates() const
{
	QStringList templates;
	QString path = QDir::currentPath() + "/templates/";

	QFile f(path);

	if (!f.exists())
	{
		path = sett().getAppDirs() + "templates/";
		qDebug() << "Templates path: " << path;
	}

	QDir allFiles;
	allFiles.setPath(path);
	allFiles.setFilter(QDir::Files);
	QStringList filters{"*css"};
	allFiles.setNameFilters(filters);
	QStringList tmp = allFiles.entryList();
	templates = tmp;

	return templates;
}

QStringList Setting::getStyles() const
{
	return QStyleFactory::keys();
}

// returns list of translations
QStringList Setting::getTranslations() const
{
	QStringList translations;
	QString path = QDir::currentPath() + "/translations/";

	qDebug() << path;
	QFile f(path);

	if (!f.exists())
	{
		path = sett().getAppDirs() + "translations/";
		qDebug() << "Path translations: " << path;
	}

	qDebug() << path;
	QDir allFiles;
	allFiles.setPath(path);
	allFiles.setFilter(QDir::Files);
	QStringList filters{"*.qm"};
	allFiles.setNameFilters(filters);
	QStringList tmp = allFiles.entryList();
	tmp = tmp.replaceInStrings("qfaktury_", "");
	tmp = tmp.replaceInStrings(".qm", "");
	translations = tmp;

	return translations;
}
