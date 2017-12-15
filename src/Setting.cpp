#include "Setting.h"
#include "Settings.h"

#include <QFileDialog>
#include <QRadioButton>
#include <QSignalMapper>

Setting::Setting(QWidget *parent) : QDialog(parent) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  setupUi(this);
  init();
}

Setting::~Setting() {
  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;
}

void Setting::init() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  QList<QAbstractButton *> settBoxes =
      QList<QAbstractButton *>()
      << cbMonth << cbYear << shortYear << cbEdit << cbSmbEdit << cbSmbEdit_2
      << cbValOn << userinfoswift << userinfobank << userinfowww
      << userinfoadress << userinfocity << userinfonip << userinfomail
      << buyerinfowww << buyerinfocity << buyerinfoaddress << buyerinfoaccount
      << buyerinfomail << buyerinfotel << buyerinfotic << buyerinfoname
      << userinfotel << userinfoaccount << userinfoname << userinfofax
      << userinfokrs << cb1 << cb2 << cb3 << cb4 << cb5 << cb6 << cb7 << cb8
      << cb9 << cb10 << cb11 << cb12 << cb13 << cb14 << cbDay << exportGoodsBtn
      << exportBuyersBtn << exportInvBtn << exportWareBtn << noAskCSVPath
      << noAskBackupPath << regularBackupBtn << backupEveryTimeBtn
      << backupOnceDay << backupOnceWeek << backupOnceMonth << backupEveryHour
      << backupEveryMin << CSVUSAFormat << CSVEURFormat;

  QList<QRadioButton *> settBackupRadios = QList<QRadioButton *>()
                                           << backupOnceDay << backupOnceWeek
                                           << backupOnceMonth << backupEveryHour
                                           << backupEveryMin;

  // static_cast<void (QSignalMapper::*)(int)>(&QSignalMapper::mapped),
  QSignalMapper *signalMapper = new QSignalMapper(this);
  connect(signalMapper,
          static_cast<void (QSignalMapper::*)(int)>(&QSignalMapper::mapped),
          [this](int) { saveButton->setEnabled(true); });

  QSignalMapper *signalMapperRadios = new QSignalMapper(this);
  connect(signalMapperRadios, SIGNAL(mapped(bool)), this,
          SIGNAL(checkOnlyOneInterval(bool)));

  int j = 0;
  QList<QAbstractButton *>::iterator i;
  for (i = settBoxes.begin(); i != settBoxes.end(); ++i) {
    signalMapper->setMapping((*i), j);
    connect((*i), SIGNAL(toggled(bool)), signalMapper, SLOT(map()));
    j++;
  }

  j = 0;

  int x = 0;
  QList<QRadioButton *>::iterator k;
  for (k = settBackupRadios.begin(); k != settBackupRadios.end(); ++k) {
    signalMapperRadios->setMapping((*k), x);
    connect((*k), SIGNAL(toggled(bool)), signalMapperRadios, SLOT(map()));
    j++;
  }

  x = 0;

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
  connect(cssList, SIGNAL(currentIndexChanged(int)), this,
          SLOT(saveBtnEnable()));
  connect(stylesList, SIGNAL(currentIndexChanged(int)), this,
          SLOT(saveBtnEnable()));
  connect(codecList, SIGNAL(currentIndexChanged(int)), this,
          SLOT(saveBtnEnable()));
  connect(logoEdit, SIGNAL(textChanged(const QString &)), this,
          SLOT(saveBtnEnable()));
  connect(stempEdit, SIGNAL(textChanged(const QString &)), this,
          SLOT(saveBtnEnable()));
  connect(workingDirEdit, SIGNAL(textChanged(const QString &)), this,
          SLOT(saveBtnEnable()));
  connect(prefixEdit, SIGNAL(textChanged(const QString &)), this,
          SLOT(saveBtnEnable()));
  connect(sufixEdit, SIGNAL(textChanged(const QString &)), this,
          SLOT(saveBtnEnable()));
  connect(spbNumb, SIGNAL(valueChanged(const QString &)), this,
          SLOT(saveBtnEnable()));
  connect(spbNumCopies, SIGNAL(valueChanged(const QString &)), this,
          SLOT(saveBtnEnable()));
  connect(csvLinePath, SIGNAL(textChanged(const QString &)), this,
          SLOT(saveBtnEnable()));
  connect(backupLinePath, SIGNAL(textChanged(const QString &)), this,
          SLOT(saveBtnEnable()));
  connect(CSVUSAFormat, SIGNAL(toggled(bool)), this,
          SLOT(checkCurrCsvFormat(bool)));
  connect(CSVEURFormat, SIGNAL(toggled(bool)), this,
          SLOT(checkCurrCsvFormat(bool)));
  connect(noAskCSVPath, SIGNAL(stateChanged(int)), this,
          SLOT(blockCsvCheckboxPath(int)));
  connect(noAskBackupPath, SIGNAL(stateChanged(int)), this,
          SLOT(blockBackupCheckboxPath(int)));
  connect(regularBackupBtn, SIGNAL(stateChanged(int)), this,
          SLOT(blockBackupCheckbox(int)));
  connect(setCSVPathBtn, SIGNAL(clicked(bool)), this, SLOT(fillPath(bool)));
  connect(setBackupPathBtn, SIGNAL(clicked(bool)), this, SLOT(fillPath(bool)));

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

void Setting::apply() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  bool check1 = noAskCSVPath->isChecked() && csvLinePath->text() == "";
  bool check2 = noAskBackupPath->isChecked() && backupLinePath->text() == "";
  bool check3 = backupEveryHour->isChecked() && howManyHours->value() == 0;
  bool check4 = backupEveryMin->isChecked() && howManyMin->value() == 0;

  if (check1)
    QMessageBox::warning(this, "Niezgodność dla ustawień CSV",
                         "Jeśli zaznaczasz opcję dla zapamiętania ścieżki "
                         "zapisu dla csv, nie powinieneś pozostawiać pustego "
                         "miejsca na ścieżkę");
  if (check2)
    QMessageBox::warning(this, "Niezgodność dla ustawień backup",
                         "Jeśli zaznaczasz opcję dla zapamiętania ścieżki "
                         "zapisu dla backup, nie powinieneś pozostawiać "
                         "pustego miejsca na ścieżkę");
  if (check3)
    QMessageBox::warning(this, "Niezgodność dla ustawień backup",
                         "Jeśli zaznaczasz cykl godzinowy dla tworzonej kopii "
                         "zapasowej, powinieneś obok dodać wartość wiekszą od "
                         "0");
  if (check4)
    QMessageBox::warning(this, "Niezgodność dla ustawień backup",
                         "Jeśli zaznaczasz cykl minutowy dla tworzonej kopii "
                         "zapasowej, powinieneś obok dodać wartość wiekszą od "
                         "0");

  QList<bool> checks;
  checks << check1 << check2 << check3 << check4;

  if (checks.count(true) == 0) {
    saveSettings();
    saveButton->setEnabled(false);

    QMessageBox::information(
        this, trUtf8("Zapisywanie zmian"),
        trUtf8("Zmiany zostaną wprowadzone po zrestartowaniu programu"),
        QMessageBox::Ok);
  }
}

/** Slot - OK
 */

void Setting::okButtonClick() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  saveSettings();
  accept();
}

/** Slot applyBtn
 */

void Setting::saveBtnEnable() {
  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;
  saveButton->setEnabled(true);
}

/** Slot - set default text
 */

void Setting::defTextBtnClick() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;
  additText->setText(trUtf8("towar odebrałem zgodnie z fakturą"));
}

/** Slot - set all to default
 */

void Setting::setDefaultClick() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  if (QMessageBox::question(
          this, "QFaktury GPL",
          trUtf8("Czy napewno chcesz przywrócić ustawienia domyślne?"),
          QMessageBox::Yes, QMessageBox::No) == QMessageBox::No)
    return;

  sett().resetSettings();

  readSettings();
}

/** Slot used to change location of invoiced
 */

void Setting::workingDirBtnClick() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  QString dir = QFileDialog::getExistingDirectory(
      this, tr("Open Directory"), "/home",
      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
  dir += "~/.local/share/data";
  qDebug() << "Katalog roboczy" << dir;
  workingDirEdit->setText(dir);
  saveButton->setEnabled(true);
}

/** Slot add logo
 */

void Setting::addLogoBtnClick() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  QString ofn = QFileDialog::getOpenFileName(
      this, trUtf8("Wybierz plik do wstawienia jako logo"), "",
      trUtf8("Obrazki (*.jpg *.png)"));

  logoEdit->setText(ofn);
  saveButton->setEnabled(true);
}

void Setting::addStempBtnClick() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  QString ofn = QFileDialog::getOpenFileName(
      this, trUtf8("Wybierz plik do wstawienia jako pieczątka"), "",
      trUtf8("Obrazki (*.jpg *.png)"));

  stempEdit->setText(ofn);
  saveButton->setEnabled(true);
}

void Setting::helpFuncAddNr(QLineEdit *lineEd, QListWidget *listWg,
                            QString const &text) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  if (lineEd->text() != "") {

    listWg->addItem(lineEd->text());
    lineEd->clear();

  } else {

    QMessageBox::information(this, trUtf8("Uwaga!!"), text, QMessageBox::Ok);
    return;
  }

  saveButton->setEnabled(true);
}

void Setting::helpFuncDelNr(QListWidget *listWg, QString const &text) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  int selNr = listWg->currentRow();
  if (selNr >= 0) {

    listWg->takeItem(selNr);

  } else {

    QMessageBox::information(this, trUtf8("Uwaga!!"), text, QMessageBox::Ok);
    return;
  }

  saveButton->setEnabled(true);
}

//----------------------- List box Slots START ---
//@TODO merge into 1 function

/** Slot add currency
 */

void Setting::currAddBtnClick() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  helpFuncAddNr(currEdit, currlBox,
                trUtf8("Nie można dodać. Pole jest puste."));
}

/** Slot del currency
 */

void Setting::currDelBtnClick() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  helpFuncDelNr(currlBox, trUtf8("Musisz coś zaznaczyć, żeby usuwać."));
}

/** Slot korekty reason add
 */

void Setting::corAddBtnClick() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  helpFuncAddNr(corEdit, correctsBox,
                trUtf8("Nie można dodać. Pole jest puste."));
}

/** Slot korekty reason delete
 */

void Setting::corDelBtnClick() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  helpFuncDelNr(correctsBox, trUtf8("Musisz coś zaznaczyć, żeby usuwać."));
}

/** Slot predefined VAT value add
 */

void Setting::vatAddBtnClick() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  helpFuncAddNr(vatEdit, vatlBox, trUtf8("Nie można dodać. Pole jest puste."));
}

/** Slot predefined VAT value delete
 */

void Setting::vatDelBtnClick() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  helpFuncDelNr(vatlBox, trUtf8("Musisz coś zaznaczyć, żeby usuwać."));
}

/** Slot add currency
 */

void Setting::currencyAddBtnClick() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  helpFuncAddNr(currencyEdit, currencylBox,
                trUtf8("Nie można dodać. Pole jest puste."));
}

/** Slot del currency
 */
void Setting::currencyDelBtnClick() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  helpFuncDelNr(currencylBox, trUtf8("Musisz coś zaznaczyś, żeby usuwać."));
}

/** Slot delete payment type click
 */
void Setting::paymDelBtnClick() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  helpFuncDelNr(paymlBox, trUtf8("Musisz coś zaznaczyć, żeby usuwać."));
}

/** Slot add payment type click
 */
void Setting::paymAddBtnClick() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  helpFuncAddNr(paymEdit, paymlBox,
                trUtf8("Nie można dodać. Pole jest puste."));
}

void Setting::checkCurrCsvFormat(bool checked) {

  if (QObject::sender() != nullptr) {
    QRadioButton *radio = qobject_cast<QRadioButton *>(QObject::sender());

    if (checked) {
      if (radio->objectName() == "CSVEURFormat") {
        CSVUSAFormat->setAutoExclusive(false);
        CSVUSAFormat->setChecked(false);
        CSVUSAFormat->setAutoExclusive(true);
      } else {
        CSVEURFormat->setAutoExclusive(false);
        CSVEURFormat->setChecked(false);
        CSVEURFormat->setAutoExclusive(true);
      }
    }
  } else {
    if (CSVEURFormat->isChecked()) {
      CSVUSAFormat->setAutoExclusive(false);
      CSVUSAFormat->setChecked(false);
      CSVUSAFormat->setAutoExclusive(true);
    } else {
      CSVEURFormat->setAutoExclusive(false);
      CSVEURFormat->setChecked(false);
      CSVEURFormat->setAutoExclusive(true);
    }
  }
}

void Setting::blockCsvCheckboxPath(int checked) {

  if (checked == 0) { // Qt::Unchecked
    csvPathLabel->setEnabled(false);
    csvLinePath->clear();
    csvLinePath->setEnabled(false);
    setCSVPathBtn->setEnabled(false);
  } else if (checked == 2) { // Qt::Checked
    csvPathLabel->setEnabled(true);
    csvLinePath->setEnabled(true);
    setCSVPathBtn->setEnabled(true);
  }
}

void Setting::blockBackupCheckboxPath(int checked) {

  if (checked == 0) { // Qt::Unchecked
    backupPathLabel->setEnabled(false);
    backupLinePath->clear();
    backupLinePath->setEnabled(false);
    setBackupPathBtn->setEnabled(false);
  } else if (checked == 2) { // Qt::Checked
    backupPathLabel->setEnabled(true);
    backupLinePath->setEnabled(true);
    setBackupPathBtn->setEnabled(true);
  }
}

void Setting::blockBackupCheckbox(int checked) {

  if (checked == 0) { // Qt::Unchecked
    backupEveryTimeBtn->setChecked(false);
    backupEveryTimeBtn->setEnabled(false);
    uncheckRadio(backupOnceDay);
    uncheckRadio(backupOnceWeek);
    uncheckRadio(backupOnceMonth);
    uncheckRadio(backupEveryHour);
    uncheckRadio(backupEveryMin);
    howManyHours->setEnabled(false);
    hoursLabel->setEnabled(false);
    howManyMin->setEnabled(false);
    minLabel->setEnabled(false);

  } else if (checked == 2) { // Qt::Checked
    backupEveryTimeBtn->setEnabled(true);
    backupOnceDay->setEnabled(true);
    backupOnceWeek->setEnabled(true);
    backupOnceMonth->setEnabled(true);
    backupEveryHour->setEnabled(true);
    backupEveryMin->setEnabled(true);
    howManyHours->setEnabled(true);
    hoursLabel->setEnabled(true);
    howManyMin->setEnabled(true);
    minLabel->setEnabled(true);
  }
}

void Setting::checkOnlyOneInterval(bool checked) {

  if (checked) {

    QList<QRadioButton *> radios;
    radios << backupOnceDay << backupOnceWeek << backupOnceMonth
           << backupEveryHour << backupEveryMin;

    if (QObject::sender() != nullptr) {
      QRadioButton *radio = qobject_cast<QRadioButton *>(QObject::sender());

      QList<QRadioButton *>::iterator i;
      for (i = radios.begin(); i != radios.end(); ++i) {
        if (radio->objectName() != (*i)->objectName()) {
          (*i)->setAutoExclusive(false);
          (*i)->setChecked(false);
          (*i)->setAutoExclusive(true);
        }
      }
    } else {

      std::map<char, std::string> helpFindRadio = {
          {'D', backupOnceDay->objectName().toStdString()},
          {'W', backupOnceWeek->objectName().toStdString()},
          {'M', backupOnceMonth->objectName().toStdString()},
          {'h', backupEveryHour->objectName().toStdString()},
          {'m', backupEveryMin->objectName().toStdString()}};

      QList<QRadioButton *>::iterator i;
      for (i = radios.begin(); i != radios.end(); ++i) {
        if (helpFindRadio[sett()
                              .value("backup_interval")
                              .toString()
                              .back()
                              .toLatin1()] !=
            (*i)->objectName().toStdString()) {
          (*i)->setAutoExclusive(false);
          (*i)->setChecked(false);
          (*i)->setAutoExclusive(true);
        }
      }
    }
  }
}

void Setting::fillPath(bool) {

  if (QObject::sender() != nullptr) {

    QString directory =
        QDir::toNativeSeparators(QFileDialog::getExistingDirectory(
            this, tr("Find Files"), sett().getCSVDir()));

    if (QObject::sender()->objectName() == "setCSVPathBtn") {

      csvLinePath->setText(directory);

    } else if (QObject::sender()->objectName() == "setBackupPathBtn") {

      backupLinePath->setText(directory);
    }
  }
}

//----------------------- List box Slots END ---

void Setting::helpFuncAp(QListWidget *listWg) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  int selNr = listWg->currentRow();

  if (selNr == 0) {
    QMessageBox::information(
        this, trUtf8("Uwaga!!"),
        trUtf8("Element znajduje się już na pierwszym miejscu na liście."),
        QMessageBox::Ok);
    return;
  }

  if (selNr > 0) {

    QListWidgetItem *item = listWg->item(listWg->currentRow());
    listWg->takeItem(selNr);
    listWg->insertItem(selNr - 1, item);
    listWg->setCurrentRow(selNr - 1);

  } else {

    QMessageBox::information(this, trUtf8("Uwaga!!"),
                             trUtf8("Musisz coś zaznaczyć, żeby przesuwać."),
                             QMessageBox::Ok);
    return;
  }

  saveButton->setEnabled(true);
}

void Setting::helpFuncDown(QListWidget *listWg) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  int selNr = listWg->currentRow();
  int recCount = listWg->count();
  // qDebug() << selNr << recCount;

  if (selNr == recCount - 1) {

    QMessageBox::information(
        this, trUtf8("Uwaga!!"),
        trUtf8("Element znajduje się już na ostatnim miejscu na liście."),
        QMessageBox::Ok);
    return;
  }

  if (selNr >= 0) {

    QListWidgetItem *item = listWg->item(listWg->currentRow());
    listWg->takeItem(selNr);
    listWg->insertItem(selNr + 1, item);
    listWg->setCurrentRow(selNr + 1);

  } else {

    QMessageBox::information(this, trUtf8("Uwaga!!"),
                             trUtf8("Musisz coś zaznaczyć, żeby przesuwać."),
                             QMessageBox::Ok);
    return;
  }

  saveButton->setEnabled(true);
}

//---------------------- UP DOWN SLOTS START----

/** Slot move VAT value up
 */

void Setting::vatUpBtnClick() {
  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;
  helpFuncAp(vatlBox);
}

/** Slot move VAT value down
 */

void Setting::vatDownBtnClick() {
  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;
  helpFuncDown(vatlBox);
}

/** Slot move payment value up
 */
void Setting::paymUpBtnClick() {
  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;
  helpFuncAp(paymlBox);
}

/** Slot move payment value down
 */
void Setting::paymDownBtnClick() {
  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;
  helpFuncDown(paymlBox);
}

//---------------------- UP DOWN SLOTS END----

// ------------- SLOTS for items on the invoice START ----

void Setting::getEncodings() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  QHash<QString, QTextCodec *> codecMap;
  QRegExp iso8859RegExp("ISO[- ]8859-([0-9]+).*");

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

  codecs = codecMap.values().toVector();

  codecList->clear();

  foreach (QTextCodec *codec, codecs)
    codecList->addItem(codec->name(), codec->mibEnum());
}

/** Used for parsing
 */

QString Setting::getAll(QListWidget *lb) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  QString tmp = QString();
  int selNr, posCount = lb->count();

  for (selNr = 0; selNr < posCount; ++selNr) {
    tmp += lb->item(selNr)->text();

    if (selNr != posCount - 1)

      tmp += "|";
  }

  return tmp;
}

/** Save all sett()
 */

void Setting::saveSettings() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

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
  sett().setValue("firstRunGUS", false);
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
  sett().setValue("validation", cbValOn->isChecked());
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

  sett().beginGroup("csv_settings");
  sett().setValue("csv_format", CSVUSAFormat->isChecked() ? "US" : "EU");
  sett().setValue("export_goods", exportGoodsBtn->isChecked());
  sett().setValue("export_buyers", exportBuyersBtn->isChecked());
  sett().setValue("export_invoices", exportInvBtn->isChecked());
  sett().setValue("export_warehouses", exportWareBtn->isChecked());
  sett().setValue("no_ask_csv_path", noAskCSVPath->isChecked());
  sett().setValue("csv_path", csvLinePath->text());
  sett().endGroup();

  sett().beginGroup("backup_settings");
  sett().setValue("no_ask_backup_path", noAskBackupPath->isChecked());
  sett().setValue("backup_path", backupLinePath->text());
  sett().setValue("regular_backup", regularBackupBtn->isChecked());
  sett().setValue("backup_every_time", backupEveryTimeBtn->isChecked());
  sett().setValue("backup_interval", settWriteBackup());
  sett().endGroup();
}

/** Read all sett()
 */

void Setting::readSettings() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

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

  curr = codecs.indexOf(
      QTextCodec::codecForName(sett().value("localEnc").toByteArray()));
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
  cbValOn->setChecked(sett().value("validation").toBool());

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

  sett().beginGroup("csv_settings");
  if (sett().value("csv_format").toString() == "US")
    CSVUSAFormat->setChecked(true);
  else if (sett().value("csv_format").toString() == "EU")
    CSVEURFormat->setChecked(true);
  exportGoodsBtn->setChecked(sett().value("export_goods").toBool());
  exportBuyersBtn->setChecked(sett().value("export_buyers").toBool());
  exportInvBtn->setChecked(sett().value("export_invoices").toBool());
  exportWareBtn->setChecked(sett().value("export_warehouses").toBool());
  noAskCSVPath->setChecked(sett().value("no_ask_csv_path").toBool());
  csvLinePath->setText(sett().value("csv_path").toString());
  checkCurrCsvFormat(sett().value("csv_format").toString() != "none");
  blockCsvCheckboxPath(sett().value("no_ask_csv_path").toBool());
  sett().endGroup();

  sett().beginGroup("backup_settings");
  noAskBackupPath->setChecked(sett().value("no_ask_backup_path").toBool());
  backupLinePath->setText(sett().value("backup_path").toString());
  regularBackupBtn->setChecked(sett().value("regular_backup").toBool());
  backupEveryTimeBtn->setChecked(sett().value("backup_every_time").toBool());
  settReadBackup(sett().value("backup_interval").toString());
  blockBackupCheckboxPath(sett().value("no_ask_backup_path").toBool());
  blockBackupCheckbox(sett().value("regular_backup").toBool());
  checkOnlyOneInterval(sett().value("backup_interval").toString() == "1D");
  checkOnlyOneInterval(sett().value("backup_interval").toString() == "1W");
  checkOnlyOneInterval(sett().value("backup_interval").toString() == "1M");
  checkOnlyOneInterval(sett().value("backup_interval").toString().back() ==
                       'h');
  checkOnlyOneInterval(sett().value("backup_interval").toString().back() ==
                       'm');
  sett().endGroup();

  prefixEdit->setText(sett().value("prefix").toString());

  cbDay->setChecked(sett().value("day").toBool());
  cbMonth->setChecked(sett().value("month").toBool());
  cbYear->setChecked(sett().value("year").toBool());
  shortYear->setChecked(sett().value("shortYear").toBool());
  cbEdit->setChecked(sett().value("edit").toBool());
  cbSmbEdit->setChecked(sett().value("editSymbol").toBool());
  cbValOn->setChecked(sett().value("validation").toBool());
  spbNumb->setValue(sett().value("chars_in_symbol").toInt());

  read = true;
}

// returns list of translations
QStringList Setting::getTemplates() {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  QStringList templates = QStringList();
  QString path = QDir::currentPath() + "/templates/";

  QFile f(path);

  if (!f.exists()) {

    path = sett().getAppDirs() + "templates/";
    qDebug() << "Templates path: " << path;
  }

  QDir allFiles;
  allFiles.setPath(path);
  allFiles.setFilter(QDir::Files);
  QStringList filters = QStringList() << "*css";
  allFiles.setNameFilters(filters);
  QStringList tmp = allFiles.entryList();
  templates = tmp;

  return templates;
}

QStringList Setting::getStyles() {
  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;
  return QStyleFactory::keys();
}
