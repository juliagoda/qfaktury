#include "User.h"
#include "Settings.h"
#include "Validations.h"
#include <QCheckBox>
#include <QScrollArea>

User::User(QWidget *parent)
	: QDialog(parent)
{
	setupUi(this);
	sellersWidgets.append(mainSeller);
	init();
}

/*!
  * inits function, reads settings
  !*/

void User::init()
{
	QSettings settings("elinux", "user");
	nameEdit->setText(settings.value("name").toString());
	placeEdit->setText(settings.value("city").toString());
	codeEdit->setText(settings.value("zip").toString());
	addressEdit->setText(settings.value("address").toString());
	accountEdit->setText(settings.value("account").toString());

	if (!settings.value("secIdType").isNull())
	{
		int current = secIdType->findText(settings.value("secIdType").toString());
		secIdType->setCurrentIndex(current);
	}

	nipEdit->setText(settings.value("tic").toString());
	regonEdit->setText(settings.value("regon").toString()); // i guess it's statistical number
	phonEdit->setText(settings.value("phone").toString());
	emailEdit->setText(settings.value("email").toString());
	webEdit->setText(settings.value("website").toString());
	bankNameEdit->setText(settings.value("bank").toString());
	bicSwiftEdit->setText(settings.value("swift").toString());
	krsEdit->setText(settings.value("krs").toString());
	faxEdit->setText(settings.value("fax").toString());

	for (int i = 1; i < settings.value("sellerCount").toInt(); ++i)
	{
		on_nextSeller_clicked();

		// add data to QLineEdits and choose of QComboBox option for each QTab
		QSettings settings("elinux", "user");
		settings.beginGroup("seller" + QString::number(i));
		sellersWidgets.at(i)
			->findChild<QLineEdit *>("nameEdit")
			->setText(settings.value("name").toString()); // save String
		sellersWidgets.at(i)
			->findChild<QLineEdit *>("placeEdit")
			->setText(settings.value("city").toString());
		sellersWidgets.at(i)
			->findChild<QLineEdit *>("codeEdit")
			->setText(settings.value("zip").toString());
		sellersWidgets.at(i)
			->findChild<QLineEdit *>("addressEdit")
			->setText(settings.value("address").toString());
		sellersWidgets.at(i)
			->findChild<QLineEdit *>("accountEdit")
			->setText(settings.value("account").toString());

		if (!settings.value("secIdType").isNull())
		{
			int current = sellersWidgets.at(i)
							  ->findChild<QComboBox *>("secIdType")
							  ->findText(settings.value("secIdType").toString());
			sellersWidgets.at(i)->findChild<QComboBox *>("secIdType")->setCurrentIndex(current);
		}

		sellersWidgets.at(i)
			->findChild<QLineEdit *>("regonEdit")
			->setText(settings.value("regon").toString());
		sellersWidgets.at(i)
			->findChild<QLineEdit *>("phonEdit")
			->setText(settings.value("phone").toString());
		sellersWidgets.at(i)
			->findChild<QLineEdit *>("emailEdit")
			->setText(settings.value("email").toString());
		sellersWidgets.at(i)->findChild<QLineEdit *>("webEdit")->setText(
			settings.value("website").toString());
		sellersWidgets.at(i)->findChild<QLineEdit *>("krsEdit")->setText(
			settings.value("krs").toString());
		sellersWidgets.at(i)->findChild<QLineEdit *>("faxEdit")->setText(
			settings.value("fax").toString());
		sellersWidgets.at(i)
			->findChild<QLineEdit *>("bankNameEdit")
			->setText(settings.value("bank").toString());
		sellersWidgets.at(i)
			->findChild<QLineEdit *>("bicSwiftEdit")
			->setText(settings.value("swift").toString());
		if (settings.value("ifUsed").toBool())
		{
			sellersWidgets.at(i)->findChild<QCheckBox *>()->setChecked(true);
		}
		else
		{
			sellersWidgets.at(i)->findChild<QCheckBox *>()->setChecked(false);
		}
		settings.endGroup();
	}
}

bool User::checkAll()
{
	foreach (QWidget *widg, sellersWidgets)
	{
		if (Validations::instance()->isEmptyField(
				widg->findChild<QLineEdit *>("nameEdit")->text(), textLabel1->text()))
		{
			return false;
		}
	}

	foreach (QWidget *widg, sellersWidgets)
	{
		if (Validations::instance()->isEmptyField(
				widg->findChild<QLineEdit *>("placeEdit")->text(), textLabel3->text()))
		{
			return false;
		}
	}

	foreach (QWidget *widg, sellersWidgets)
	{
		if (!Validations::instance()->isEmptyField(
				widg->findChild<QLineEdit *>("codeEdit")->text(), textLabel4->text()))
		{
			if (!Validations::instance()->validateZip(
					widg->findChild<QLineEdit *>("codeEdit")->text()))
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}

	foreach (QWidget *widg, sellersWidgets)
	{
		if (Validations::instance()->isEmptyField(
				widg->findChild<QLineEdit *>("addressEdit")->text(), textLabel2->text()))
		{
			return false;
		}
	}

	foreach (QWidget *widg, sellersWidgets)
	{
		if (!Validations::instance()->isEmptyField(
				widg->findChild<QLineEdit *>("accountEdit")->text(), textLabel5->text()))
		{
			if (!Validations::instance()->validateAccount(
					widg->findChild<QLineEdit *>("accountEdit")->text()))
			{
				return false;
			}
			if (!Validations::instance()->checkSumAccount(
					widg->findChild<QLineEdit *>("accountEdit")->text()))
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}

	if (!Validations::instance()->isEmptyField(nipEdit->text(), textLabel2_2->text()))
	{
		if (!Validations::instance()->validateNIP(nipEdit->text()))
		{
			return false;
		}
		if (!Validations::instance()->checkSumNIP(nipEdit->text()))
		{
			return false;
		}
	}
	else
	{
		return false;
	}

	foreach (QWidget *widg, sellersWidgets)
	{
		if (widg->findChild<QComboBox *>("secIdType")->currentText() != trUtf8("Brak"))
		{
			switch (widg->findChild<QComboBox *>("secIdType")->currentIndex())
			{
			case 0:

				break;

			case 1:

				if (widg->findChild<QLineEdit *>("regonEdit")->text().isEmpty())
				{
					QMessageBox::warning(
						this,
						trUtf8("Pusty NUSP"),
						trUtf8("Pole dla numeru NUSP nie może być puste"));
					return false;
				}
				break;

			case 2:

				if (!Validations::instance()->validateRegon(
						widg->findChild<QLineEdit *>("regonEdit")->text()))
				{
					return false;
				}
				if (!Validations::instance()->checkSumREGON(
						widg->findChild<QLineEdit *>("regonEdit")->text()))
				{
					return false;
				}
				break;

			case 3:

				if (!Validations::instance()->validatePESEL(
						widg->findChild<QLineEdit *>("regonEdit")->text()))
				{
					return false;
				}
				if (!Validations::instance()->checkSumPESEL(
						widg->findChild<QLineEdit *>("regonEdit")->text()))
				{
					return false;
				}
				break;

			case 4:

				if (!Validations::instance()->validateIDCard(
						widg->findChild<QLineEdit *>("regonEdit")->text()))
				{
					return false;
				}
				if (!Validations::instance()->checkSumIDCard(
						widg->findChild<QLineEdit *>("regonEdit")->text()))
				{
					return false;
				}
				break;

			case 5:

				if (!Validations::instance()->validatePass(
						widg->findChild<QLineEdit *>("regonEdit")->text()))
				{
					return false;
				}
				if (!Validations::instance()->checkSumPass(
						widg->findChild<QLineEdit *>("regonEdit")->text()))
				{
					return false;
				}
				break;
			}
		}
	}

	foreach (QWidget *widg, sellersWidgets)
	{
		if (!widg->findChild<QLineEdit *>("phonEdit")->text().isEmpty())
		{
			if (!Validations::instance()->validateTel(
					widg->findChild<QLineEdit *>("phonEdit")->text()))
			{
				return false;
			}
		}
	}

	foreach (QWidget *widg, sellersWidgets)
	{
		if (!widg->findChild<QLineEdit *>("emailEdit")->text().isEmpty())
		{
			if (!Validations::instance()->validateEmail(
					widg->findChild<QLineEdit *>("emailEdit")->text()))
			{
				return false;
			}
		}
	}

	foreach (QWidget *widg, sellersWidgets)
	{
		if (!widg->findChild<QLineEdit *>("webEdit")->text().isEmpty())
		{
			if (!Validations::instance()->validateWebsite(
					widg->findChild<QLineEdit *>("webEdit")->text()))
			{
				return false;
			}
		}
	}

	return true;
}

/*!
  *   saves settings
  !*/

void User::okClick()
{
	bool ifOtherSeller = false;

	if (sett().value("validation").toBool() == false
		|| (sett().value("validation").toBool() && checkAll()))
	{
		int i = 0;
		foreach (QWidget *widg, sellersWidgets)
		{
			if (i == 0)
			{
				QSettings settings("elinux", "user");
				settings.setValue("name", nameEdit->text()); // save String
				settings.setValue("city", placeEdit->text());
				settings.setValue("zip", codeEdit->text());
				settings.setValue("address", addressEdit->text());
				settings.setValue("account", accountEdit->text());
				settings.setValue("tic", nipEdit->text());
				settings.setValue("secIdType", secIdType->currentText());
				settings.setValue("regon", regonEdit->text());
				settings.setValue("phone", phonEdit->text());
				settings.setValue("email", emailEdit->text());
				settings.setValue("website", webEdit->text());
				settings.setValue("krs", krsEdit->text());
				settings.setValue("fax", faxEdit->text());
				settings.setValue("bank", bankNameEdit->text());
				settings.setValue("swift", bicSwiftEdit->text());
			}
			else
			{
				QSettings settings("elinux", "user");
				settings.beginGroup("seller" + QString::number(i));
				settings.setValue(
					"name", widg->findChild<QLineEdit *>("nameEdit")->text()); // save String
				settings.setValue("city", widg->findChild<QLineEdit *>("placeEdit")->text());
				settings.setValue("zip", widg->findChild<QLineEdit *>("codeEdit")->text());
				settings.setValue("address", widg->findChild<QLineEdit *>("addressEdit")->text());
				settings.setValue("account", widg->findChild<QLineEdit *>("accountEdit")->text());
				settings.setValue("tic", widg->findChild<QLineEdit *>("nipEdit")->text());
				settings.setValue(
					"secIdType", widg->findChild<QComboBox *>("secIdType")->currentText());
				settings.setValue("regon", widg->findChild<QLineEdit *>("regonEdit")->text());
				settings.setValue("phone", widg->findChild<QLineEdit *>("phonEdit")->text());
				settings.setValue("email", widg->findChild<QLineEdit *>("emailEdit")->text());
				settings.setValue("website", widg->findChild<QLineEdit *>("webEdit")->text());
				settings.setValue("krs", widg->findChild<QLineEdit *>("krsEdit")->text());
				settings.setValue("fax", widg->findChild<QLineEdit *>("faxEdit")->text());
				settings.setValue("bank", widg->findChild<QLineEdit *>("bankNameEdit")->text());
				settings.setValue("swift", widg->findChild<QLineEdit *>("bicSwiftEdit")->text());
				settings.setValue("ifUsed", widg->findChild<QCheckBox *>()->isChecked());
				settings.endGroup();

				if (widg->findChild<QCheckBox *>()->isChecked())
				{
					ifOtherSeller = true;

					QSettings settings("elinux", "user");

					settings.beginGroup("choosenSeller");
					settings.setValue(
						"name", widg->findChild<QLineEdit *>("nameEdit")->text()); // save String
					settings.setValue("city", widg->findChild<QLineEdit *>("placeEdit")->text());
					settings.setValue("zip", widg->findChild<QLineEdit *>("codeEdit")->text());
					settings.setValue(
						"address", widg->findChild<QLineEdit *>("addressEdit")->text());
					settings.setValue(
						"account", widg->findChild<QLineEdit *>("accountEdit")->text());
					settings.setValue("tic", widg->findChild<QLineEdit *>("nipEdit")->text());
					settings.setValue(
						"secIdType", widg->findChild<QComboBox *>("secIdType")->currentText());
					settings.setValue("regon", widg->findChild<QLineEdit *>("regonEdit")->text());
					settings.setValue("phone", widg->findChild<QLineEdit *>("phonEdit")->text());
					settings.setValue("email", widg->findChild<QLineEdit *>("emailEdit")->text());
					settings.setValue("website", widg->findChild<QLineEdit *>("webEdit")->text());
					settings.setValue("krs", widg->findChild<QLineEdit *>("krsEdit")->text());
					settings.setValue("fax", widg->findChild<QLineEdit *>("faxEdit")->text());
					settings.setValue("bank", widg->findChild<QLineEdit *>("bankNameEdit")->text());
					settings.setValue(
						"swift", widg->findChild<QLineEdit *>("bicSwiftEdit")->text());
					settings.endGroup();
				}
			}
			i += 1;
		}

		QSettings settings("elinux", "user");
		settings.setValue("sellerCount", QString::number(i));

		if (!ifOtherSeller)
		{
			QSettings settings("elinux", "user");

			settings.beginGroup("choosenSeller");
			settings.setValue("name", nameEdit->text()); // save String
			settings.setValue("city", placeEdit->text());
			settings.setValue("zip", codeEdit->text());
			settings.setValue("address", addressEdit->text());
			settings.setValue("account", accountEdit->text());
			settings.setValue("tic", nipEdit->text());
			settings.setValue("secIdType", secIdType->currentText());
			settings.setValue("regon", regonEdit->text());
			settings.setValue("phone", phonEdit->text());
			settings.setValue("email", emailEdit->text());
			settings.setValue("website", webEdit->text());
			settings.setValue("krs", krsEdit->text());
			settings.setValue("fax", faxEdit->text());
			settings.setValue("bank", bankNameEdit->text());
			settings.setValue("swift", bicSwiftEdit->text());
			settings.endGroup();
		}

		close();
	}
}

/*
 * Generates next seller tab in QTabWidget
 */

void User::on_nextSeller_clicked()
{
	QWidget *nextSel = new QWidget();

	QHBoxLayout *hLayout = new QHBoxLayout();
	QVBoxLayout *vLayout1 = new QVBoxLayout();
	QVBoxLayout *vLayout2 = new QVBoxLayout();

	QStringList listNames{
		"Nazwa*:",
		"Miejscowość*:",
		"Kod*:",
		"Adres*:",
		"Nr konta*:",
		"Nazwa banku:",
		"Nr SWIFT/BIC:",
		"NIP*:",
		"Typ 2 Id:",
		"Drugi Id:",
		"Numer KRS:",
		"Telefon:",
		"Fax:",
		"Email:",
		"Strona www:",
	};

	QStringList objectNames{
		"nameEdit",
		"placeEdit",
		"codeEdit",
		"addressEdit",
		"accountEdit",
		"bankNameEdit",
		"bicSwiftEdit",
		"nipEdit",
		"secIdType",
		"regonEdit",
		"krsEdit",
		"phonEdit",
		"faxEdit",
		"emailEdit",
		"webEdit",
	};

	QLabel *useLabel = new QLabel;
	useLabel->setText(trUtf8("Zastosuj do faktur"));
	vLayout1->addWidget(useLabel);

	QCheckBox *useCheckBox = new QCheckBox(nextSel);
	useCheckBox->setObjectName(trUtf8("useThisSeller"));
	vLayout2->addWidget(useCheckBox);

	for (int i = 0; i < listNames.count(); i++)
	{
		QLabel *name = new QLabel;
		name->setText(listNames.at(i));
		vLayout1->addWidget(name);

		if (objectNames.at(i) == "secIdType")
		{
			QStringList listcombo{
				"Brak", "NUSP", "REGON", "PESEL", "Dowód osobisty", "Paszport",
			};
			QComboBox *lname = new QComboBox;
			lname->addItems(listcombo);
			lname->setObjectName(objectNames.at(i));
			vLayout2->addWidget(lname);
		}
		else
		{
			QLineEdit *lname = new QLineEdit;
			lname->setObjectName(objectNames.at(i));
			if (lname->objectName() == "nipEdit")
			{
				QSettings settings("elinux", "user");
				lname->setText(settings.value("tic").toString());
				lname->setDisabled(true);
			}
			vLayout2->addWidget(lname);
		}
	}

	hLayout->addLayout(vLayout1);
	hLayout->addLayout(vLayout2);

	QPushButton *removeBtn = new QPushButton("X");
	removeBtn->setFixedWidth(30);

	hLayout->addWidget(removeBtn);

	nextSel->setLayout(hLayout);
	QScrollArea *scrollArea = new QScrollArea;
	scrollArea->setWidget(nextSel);
	sellersList->addTab(scrollArea, trUtf8("Sprzedawca/Oddział"));

	connect(removeBtn, SIGNAL(clicked()), this, SLOT(delcurrSel()));

	sellersWidgets.append(nextSel);
}

/*
* Removes current tab with seller in QTabWidget
*/

void User::delcurrSel()
{
	if (QMessageBox::warning(
			this,
			trUtf8("Usuwanie danych oddziału"),
			trUtf8("Usunąć dane kolejnego sprzedawcy/oddziału?"),
			trUtf8("Tak"),
			trUtf8("Nie"),
			nullptr,
			0,
			1)
		== 0)
	{
		QSettings settings("elinux", "user");
		settings.remove("seller" + QString::number(sellersList->currentIndex()));

		bool isLess = false;
		if (sellersList->currentIndex() < sellersList->count() - 1)
		{
			isLess = true;
		}

		sellersWidgets.removeAt(sellersList->currentIndex());
		sellersList->removeTab(sellersList->currentIndex());
		sellersList->setCurrentIndex(0);

		settings.setValue("sellerCount", sellersWidgets.count());

		if (isLess)
		{
			for (int i = sellersList->currentIndex(); i < sellersList->count(); ++i)
			{
				settings.beginGroup("seller" + QString::number(i + 1));
				QSettings settings2("elinux", "user");
				settings2.beginGroup("seller" + QString::number(i));

				foreach (const QString &key, settings.childKeys())
				{
					settings2.setValue(key, settings.value(key).toString());
				}

				settings2.endGroup();
				settings.endGroup();
			}

			settings.remove("seller" + QString::number(sellersList->count()));
		}
	}
}
