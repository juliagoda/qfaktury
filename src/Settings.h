#ifndef SETTINGS_H
#define SETTINGS_H

#include <QStandardPaths>
#include <QSettings>
#include <QDate>
#include <QDir>
#include <QString>
#include <QVariant>
#include <QLocale>
#include <QDebug>
#include <QTextCodec>
#include <QStyleFactory>
#include <QTranslator>
#include <QMessageBox>
#include "config.h"


// #define trUtf8(x) QObject::aaa(x)
#define STRING2(x) #x
#define STRING(x) STRING2(x)

// Singleton class to store all the settings and static values

class Settings: public QSettings {
public:

#ifdef Q_OS_MAC
QString appPath = "~/Library/Application Support/qfaktury";
#endif

#ifdef Q_OS_LINUX
QString appPath = "/usr/share/qfaktury";
#endif
// Probably QStandardPaths::standardLocations(QStandardPaths::AppDataLocation).at(1) returns different values on different distributions, for me that was /usr/share/<APPNAME>

#ifdef Q_OS_WIN32
QString appPath = QDir::homePath() + "/AppData/Roaming/qfaktury";
#endif

    QString getAppDirs() {
        return appPath + "/";
    }

	// get date from settings as QDate
	QDate getValueAsDate(QString val) {
		QString date = value(val).toString();
		QLocale locale;
		return locale.toDate( date, getDateFormat());
	}

	// returns date format used for all dates
	QString getDateFormat() {
		// it's better to have a full year... so
		return dateFormat;
	}

	// returns date format used while saving the file
	QString getFnameDateFormat() {
			return fileNameDateFormat;
	}

	// returns a translator
	QTranslator* getTranslation() {

	    translator = new QTranslator();
	    QString lang = value("lang", "pl").toString();
	    // The easiest way
	    // On windows and during testing files have to be in executable dir

        if (!translator->load(QString("qfaktury_") + lang)) translator->load(QString("qfaktury_") + lang, appPath + "/translations");
        qDebug() << "Translations files are in: " << appPath + "/translations";
		return translator;
	}

	/**
	 * validate the settings and set them to default values if required.
	 */

	void checkSettings() {

		if (value("browser_name").toString().compare("") == 0)
			setValue("browser_name", "");
		if (value("default_browser").toString().compare("") == 0)
			setValue("default_browser", "true");
		if (value("lang").toString().compare("") == 0)
			setValue("lang", tr("pl"));
        if (value("style").toString().compare("") == 0)
            setValue("style", QStyleFactory::keys().at(0));
        if (value("css").toString().compare("") == 0)
            setValue("css", "black.css");
		if (value("localEnc").toString().compare("") == 0)
			setValue("localEnc", tr("UTF-8"));


		if (value("addText").toString().compare("") == 0)
            setValue("addText", trUtf8("towar odebrałem zgodnie z fakturą"));
		if (value("chars_in_symbol").toString().compare("") == 0)
			setValue("chars_in_symbol", tr("0"));
		if (value("day").toString().compare("") == 0)
			setValue("day", "false");
		if (value("edit").toString().compare("") == 0)
            setValue("edit", "true");
		if (value("editName").toString().compare("") == 0)
			setValue("editName", "false");
		if (value("filtrEnd").toString().compare("") == 0)
			setValue("filtrEnd",
					QDate::currentDate().toString(Qt::ISODate));
		if (value("filtrStart").toString().compare("") == 0)
			setValue("filtrStart", QDate::currentDate().toString(
					Qt::ISODate));
		if (value("firstrun").toString().compare("") == 0)
			setValue("firstrun", false);
        if (value("units").toString().compare("") == 0)
            setValue("units", tr("szt.|kg.|g.|m|km.|godz."));
		if (value("korNr").toString().compare("") == 0)
			setValue("korNr", "1");
        if (value("invNr").toString().compare("") == 0)
            setValue("invNr", "1");
		if (value("logo").toString().compare("") == 0)
			setValue("logo", "");
		if (value("margLeftPrinter").toString().compare("") == 0)
			setValue("margLeftPrinter", "10");
		if (value("margTopPrinter").toString().compare("") == 0)
			setValue("margTopPrinter", "10");
		if (value("margDownPrinter").toString().compare("") == 0)
			setValue("margDownPrinter", "10");
		if (value("margRightPrinter").toString().compare("") == 0)
			setValue("margRightPrinter", "10");
		if (value("month").toString().compare("") == 0)
			setValue("month", "false");
		if (value("paym1").toString().compare("") == 0)
			setValue("paym1", tr("gotówka"));
		if (value("payments").toString().compare("") == 0)
			setValue("payments", tr("gotówka|przelew|zaliczka"));
		if (value("pdfQuality").toString().compare("") == 0)
			setValue("pdfQuality", "1");
        if (value("corrections").toString().compare("") == 0)
            setValue("corrections", tr("zmiana ilości|zmiana waluty|zmiana rabatu|zmiana sposobu płatności|zmiana kontrahenta|zmiana towaru/usługi|zmiana daty terminu|zmiana daty sprzedaży"));
		if (value("prefix").toString().compare("") == 0)
			setValue("prefix", "");
		if (value("renamed").toString().compare("") == 0)
			setValue("renamed", "tak");
		if (value("shortYear").toString().compare("") == 0)
			setValue("shortYear", "false");
        if (value("rates").toString().compare("") == 0)
            setValue("rates", tr("23|8|5|0|zw."));
		if (value("sufix").toString().compare("") == 0)
			setValue("sufix", "");
        if (value("currencies").toString().compare("") == 0)
            setValue("currencies", tr("PLN|EUR|USD|CHF|GBP|RUB"));
		if (value("year").toString().compare("") == 0)
			setValue("year", "false");
		if (value("numberOfCopies").toString().compare("") == 0)
			setValue("numberOfCopies", 1);


        // here we could add special code for Bill
        beginGroup("invoices_positions");
		if (value("Lp").toString().compare("") == 0)
			setValue("Lp", true);
        if (value("Name").toString().compare("") == 0)
            setValue("Name", true);
        if (value("Code").toString().compare("") == 0)
            setValue("Code", true);
		if (value("pkwiu").toString().compare("") == 0)
			setValue("pkwiu", true);
        if (value("amount").toString().compare("") == 0)
            setValue("amount", true);
        if (value("unit").toString().compare("") == 0)
            setValue("unit", true);
        if (value("unitprice").toString().compare("") == 0)
            setValue("unitprice", true);
        if (value("netvalue").toString().compare("") == 0)
            setValue("netvalue", true);
        if (value("discountperc").toString().compare("") == 0)
            setValue("discountperc", true);
        if (value("discountval").toString().compare("") == 0)
            setValue("discountval", true);
        if (value("netafter").toString().compare("") == 0)
            setValue("netafter", true);
		if (value("vatval").toString().compare("") == 0)
			setValue("vatval", true);
		if (value("vatprice").toString().compare("") == 0)
			setValue("vatprice", true);
        if (value("grossval").toString().compare("") == 0)
            setValue("grossval", true);
		endGroup();

        beginGroup("forms");
		if (value("chAmount_top").toString().compare("") == 0)
			setValue("chAmount_top", "50");
		if (value("chAmount_left").toString().compare("") == 0)
			setValue("chAmount_left", "50");
		if (value("chAmount_width").toString().compare("") == 0)
			setValue("chAmount_width", "288");
		if (value("chAmount_height").toString().compare("") == 0)
			setValue("chAmount_height", "184");
		if (value("form1_top").toString().compare("") == 0)
			setValue("form1_top", "50");
		if (value("form1_left").toString().compare("") == 0)
			setValue("form1_left", "50");
		if (value("form1_width").toString().compare("") == 0)
			setValue("form1_width", "748");
		if (value("form1_height").toString().compare("") == 0)
			setValue("form1_height", "507");
		if (value("form2_top").toString().compare("") == 0)
			setValue("form2_top", "200");
		if (value("form2_left").toString().compare("") == 0)
			setValue("form2_left", "200");
		if (value("form2_width").toString().compare("") == 0)
			setValue("form2_width", "388");
		if (value("form2_height").toString().compare("") == 0)
			setValue("form2_height", "350");
		if (value("form4_top").toString().compare("") == 0)
			setValue("form4_top", "50");
		if (value("form4_left").toString().compare("") == 0)
			setValue("form4_left", "50");
		if (value("form4_width").toString().compare("") == 0)
			setValue("form4_width", "423");
		if (value("form4_height").toString().compare("") == 0)
			setValue("form4_height", "358");
		if (value("form7_top").toString().compare("") == 0)
			setValue("form7_top", "50");
		if (value("form7_left").toString().compare("") == 0)
			setValue("form7_left", "50");
		if (value("form7_width").toString().compare("") == 0)
			setValue("form7_width", "636");
		if (value("form7_height").toString().compare("") == 0)
			setValue("form7_height", "600");
		if (value("formfra_top").toString().compare("") == 0)
			setValue("formfra_top", "50");
		if (value("formfra_left").toString().compare("") == 0)
			setValue("formfra_left", "50");
		if (value("formfra_width").toString().compare("") == 0)
			setValue("formfra_width", "546");
		if (value("formfra_height").toString().compare("") == 0)
			setValue("formfra_height", "650");
		if (value("kontlist_top").toString().compare("") == 0)
			setValue("kontlist_top", "50");
		if (value("kontlist_left").toString().compare("") == 0)
			setValue("kontlist_left", "50");
		if (value("kontlist_width").toString().compare("") == 0)
			setValue("kontlist_width", "300");
		if (value("kontlist_height").toString().compare("") == 0)
			setValue("kontlist_height", "300");
		if (value("korform_top").toString().compare("") == 0)
			setValue("korform_top", "50");
		if (value("korform_left").toString().compare("") == 0)
			setValue("korform_left", "50");
		if (value("korform_width").toString().compare("") == 0)
			setValue("korform_width", "537");
		if (value("korform_height").toString().compare("") == 0)
			setValue("korform_height", "677");
		if (value("korprintpreview_top").toString().compare("") == 0)
			setValue("korprintpreview_top", "50");
		if (value("korprintpreview_left").toString().compare("") == 0)
			setValue("korprintpreview_left", "50");
		if (value("korprintpreview_width").toString().compare("") == 0)
			setValue("korprintpreview_width", "900");
		if (value("korprintpreview_height").toString().compare("") == 0)
			setValue("korprintpreview_height", "600");
		if (value("printpreview_top").toString().compare("") == 0)
			setValue("printpreview_top", "50");
		if (value("printpreview_left").toString().compare("") == 0)
			setValue("printpreview_left", "50");
		if (value("printpreview_width").toString().compare("") == 0)
			setValue("printpreview_width", "900");
		if (value("printpreview_height").toString().compare("") == 0)
			setValue("printpreview_height", "600");
		if (value("towadd_top").toString().compare("") == 0)
			setValue("towadd_top", "50");
		if (value("towadd_left").toString().compare("") == 0)
			setValue("towadd_left", "50");
		if (value("towadd_width").toString().compare("") == 0)
			setValue("towadd_width", "334");
		if (value("towadd_height").toString().compare("") == 0)
			setValue("towadd_height", "286");
		if (value("towlist_top").toString().compare("") == 0)
			setValue("towlist_top", "50");
		if (value("towlist_left").toString().compare("") == 0)
			setValue("towlist_left", "50");
		if (value("towlist_width").toString().compare("") == 0)
			setValue("towlist_width", "300");
		if (value("towlist_height").toString().compare("") == 0)
			setValue("towlist_height", "300");
		endGroup();

		beginGroup("printpos");
        if (value("username").toString().compare("") == 0)
            setValue("username", "true");
        if (value("usercity").toString().compare("") == 0)
            setValue("usercity", "true");
        if (value("useradress").toString().compare("") == 0)
            setValue("useradress", "true");
        if (value("useraccount").toString().compare("") == 0)
            setValue("useraccount", "true");
		if (value("usernip").toString().compare("") == 0)
			setValue("usernip", "true");
		if (value("userphone").toString().compare("") == 0)
			setValue("userphone", "true");
		if (value("usermail").toString().compare("") == 0)
			setValue("usermail", "true");
		if (value("userwww").toString().compare("") == 0)
			setValue("userwww", "true");
		if (value("clientnazwa").toString().compare("") == 0)
			setValue("clientnazwa", "true");
		if (value("clientmiejscowosc").toString().compare("") == 0)
			setValue("clientmiejscowosc", "true");
		if (value("clientadres").toString().compare("") == 0)
			setValue("clientadres", "true");
		if (value("clientkonto").toString().compare("") == 0)
			setValue("clientkonto", "true");
		if (value("clientnip").toString().compare("") == 0)
			setValue("clientnip", "true");
		if (value("clientphone").toString().compare("") == 0)
			setValue("clientphone", "true");
		if (value("clientmail").toString().compare("") == 0)
			setValue("clientmail", "true");
		if (value("clientwww").toString().compare("") == 0)
			setValue("clientwww", "true");
		endGroup();

        beginGroup("printkontr");
        if (value("buyername").toString().compare("") == 0)
            setValue("buyername", "true");
        if (value("buyercity").toString().compare("") == 0)
            setValue("buyercity", "true");
        if (value("buyeraddress").toString().compare("") == 0)
            setValue("buyeraddress", "true");
        if (value("buyeraccount").toString().compare("") == 0)
            setValue("buyeraccount", "true");
        if (value("buyernip").toString().compare("") == 0)
            setValue("buyernip", "true");
        if (value("buyerphone").toString().compare("") == 0)
            setValue("buyerphone", "true");
        if (value("buyermail").toString().compare("") == 0)
            setValue("buyermail", "true");
        if (value("buyerwww").toString().compare("") == 0)
            setValue("buyerwww", "true");
        endGroup();

		beginGroup("wydruki");
		if (value("col1").toString().compare("") == 0)
			setValue("col1", "10");
		if (value("col2").toString().compare("") == 0)
			setValue("col2", "25");
		if (value("col3").toString().compare("") == 0)
			setValue("col3", "12");
		if (value("col4").toString().compare("") == 0)
			setValue("col4", "12");
		if (value("col5").toString().compare("") == 0)
			setValue("col5", "10");
		if (value("col6").toString().compare("") == 0)
			setValue("col6", "9");
		if (value("col7").toString().compare("") == 0)
			setValue("col7", "11");
		if (value("col8").toString().compare("") == 0)
			setValue("col8", "11");
		if (value("col9").toString().compare("") == 0)
			setValue("col9", "10");
		if (value("col10").toString().compare("") == 0)
			setValue("col10", "12");
		if (value("col11").toString().compare("") == 0)
			setValue("col11", "12");
		if (value("col12").toString().compare("") == 0)
			setValue("col12", "12");
		if (value("col13").toString().compare("") == 0)
			setValue("col13", "12");
		if (value("col14").toString().compare("") == 0)
			setValue("col14", "12");

		endGroup();

		sync();
	}

	/** Reset all settings to default values
	 */

	void resetSettings() {

		beginGroup("General");
		setValue("browser_name", "");
		setValue("default_browser", "true");
		setValue("lang", tr("pl"));
        setValue("style", QStyleFactory::keys().at(0));
        setValue("css", "black.css");
        setValue("currencies", tr("PLN"));
		endGroup();

		setValue("addText", trUtf8("towar odebrałem zgodnie z fakturą"));
		setValue("chars_in_symbol", tr("0"));
		setValue("day", "false");
        setValue("edit", "true");
		setValue("editName", "false");
        setValue("editSymbol", "true");
		setValue("numberOfCopies", 1);
        setValue("filtrStart", QDate::currentDate().toString(getDateFormat()));
		setValue("firstrun", false);
        setValue("units", tr("szt.|kg.|g.|m.|km.|godz."));
		setValue("korNr", "1");
        setValue("invNr","1");
		setValue("logo", "");

		setValue("margLeftPrinter", "10");
		setValue("margTopPrinter", "10");
		setValue("margDownPrinter", "10");
		setValue("margRightPrinter", "10");
		setValue("month", "false");
		setValue("paym1", trUtf8("gotówka") );
		setValue("payments", trUtf8("gotówka|przelew|zaliczka") );
		setValue("pdfQuality", "1");
        setValue("corrections", trUtf8("zmiana ilości|zmiana waluty|zmiana rabatu|zmiana sposobu płatności|zmiana kontrahenta|zmiana towaru/usługi|zmiana daty terminu|zmiana daty sprzedaży") );
		setValue("prefix", "");
		setValue("renamed", "tak");
		setValue("shortYear", "false");
        setValue("rates", tr("23|8|5|0|zw."));
		setValue("sufix", "");
        setValue("currencies", tr("PLN|EUR|USD|CHF|GBP|RUB"));
		setValue("year", "false");

		// here we could add special code for Rachunek
        beginGroup("invoices_positions");
		setValue("Lp", true);
        setValue("Name", true);
        setValue("Code", true);
		setValue("pkwiu", true);
        setValue("amount", true);
        setValue("unit", true);
        setValue("unitprice", true);
        setValue("netvalue", true);
        setValue("discountperc", true);
        setValue("discountval", true);
        setValue("netafter", true);
		setValue("vatval", true);
		setValue("vatprice", true);
        setValue("grossval", true);
		endGroup();

        beginGroup("forms");
		setValue("chAmount_top", "50");
		setValue("chAmount_left", "50");
		setValue("chAmount_width", "288");
		setValue("chAmount_height", "184");
		setValue("form1_top", "50");
		setValue("form1_left", "50");
		setValue("form1_width", "748");
		setValue("form1_height", "507");
		setValue("form2_top", "200");
		setValue("form2_left", "200");
		setValue("form2_width", "388");
		setValue("form2_height", "350");
		setValue("form4_top", "50");
		setValue("form4_left", "50");
		setValue("form4_width", "423");
		setValue("form4_height", "358");
		setValue("form7_top", "50");
		setValue("form7_left", "50");
		setValue("form7_width", "636");
		setValue("form7_height", "600");
		setValue("formfra_top", "50");
		setValue("formfra_left", "50");
		setValue("formfra_width", "546");
		setValue("formfra_height", "650");
		setValue("kontlist_top", "50");
		setValue("kontlist_left", "50");
		setValue("kontlist_width", "300");
		setValue("kontlist_height", "300");
		setValue("korform_top", "50");
		setValue("korform_left", "50");
		setValue("korform_width", "537");
		setValue("korform_height", "677");
		setValue("korprintpreview_top", "50");
		setValue("korprintpreview_left", "50");
		setValue("korprintpreview_width", "900");
		setValue("korprintpreview_height", "600");
		setValue("printpreview_top", "50");
		setValue("printpreview_left", "50");
		setValue("printpreview_width", "900");
		setValue("printpreview_height", "600");
		setValue("towadd_top", "50");
		setValue("towadd_left", "50");
		setValue("towadd_width", "334");
		setValue("towadd_height", "286");
		setValue("towlist_top", "50");
		setValue("towlist_left", "50");
		setValue("towlist_width", "300");
		setValue("towlist_height", "300");
		endGroup();

		beginGroup("printpos");
        setValue("username", "true");
        setValue("usercity", "true");
        setValue("useradress", "true");
        setValue("useraccount", "true");
		setValue("usernip", "true");
		setValue("userphone", "true");
		setValue("usermail", "true");
		setValue("userwww", "true");
		setValue("clientnazwa", "true");
		setValue("clientmiejscowosc", "true");
		setValue("clientadres", "true");
		setValue("clientkonto", "true");
		setValue("clientnip", "true");
		setValue("clientphone", "true");
		setValue("clientmail", "true");
		setValue("clientwww", "true");
		endGroup();

        beginGroup("printkontr");
        setValue("buyername", "true");
        setValue("buyercity", "true");
        setValue("buyeraddress", "true");
        setValue("buyeraccount", "true");
        setValue("buyernip", "true");
        setValue("buyerphone", "true");
        setValue("buyermail", "true");
        setValue("buyerwww", "true");
        endGroup();

		beginGroup("wydruki");
		setValue("col1", "10");
		setValue("col2", "25");
		setValue("col3", "12");
		setValue("col4", "12");
		setValue("col5", "12");
		setValue("col6", "9");
		setValue("col7", "11");
		setValue("col8", "11");
		setValue("col9", "10");
		setValue("col10", "12");
		setValue("col11", "12");
		setValue("col12", "12");
		setValue("col13", "12");
		setValue("col14", "12");
		endGroup();
	}


	// Compiles version with appName ready for display
	QString getVersion(QString appName) {
		QString str = appName;
		str.truncate(2);
		return str.toUpper() + appName.right(6) + trUtf8(" - wersja ") + STRING(QFAKTURY_VERSION);
	}

	// returns working directory
	QString getWorkingDir() {
        return QString(QDir::homePath() + "/.local/share/data/elinux");
	}

    QString getStyle() {

        QString style = value("style").toString();
       // if (style.compare("") == 0) {
       //     style = QStyleFactory::keys().at(0);
       // }

        qDebug() << "Get STYLE: " << style;
        return style;
    }


	// returns templates directory
	QString getTemplate() {


        QString style = value("css").toString();
        //if (style.compare("") == 0) {
        //    style = "black.css";
        //}


        QString ret = appPath + "/templates/" + style;

		QFile f;

		f.setFileName(ret);
		if (!f.exists()) {
            ret = appPath + "/templates/" + style;
		}

		f.setFileName(ret);
		if (!f.exists()) {
            ret = appPath + "/templates/black.css";
		}

        qDebug() << "Get TEMPLATE: " << style;
		return ret;
	}


    QString getEmergTemplate() {

        return (QDir::homePath() + "/.local/share/data/elinux/template/black.css");
    }


	// return invoices dir
	QString getDataDir() {

		// Changed name of the folder to avoid overwriting the files.
		// This may require conversion script.
        return QString("/invoices");
	}

	// return invoices dir
	QString getInvoicesDir() {
        return QString(getWorkingDir() + getDataDir() + "/");
	}

	// return customers xml
	QString getCustomersXml() {
        return QString(getWorkingDir() + "/customers.xml");
	}

	// return customers xml
	QString getProductsXml() {
        return QString(getWorkingDir() + "/products.xml");
	}

	// returns inoice doc name stored as a DOCTYPE
	QString getInoiveDocName() {
        return QString("invoice");
	}

	// returns correction doc name stored as a DOCTYPE
	QString getCorrDocName() {
        return QString("correction");
	}


	// returns customers doc name stored as a DOCTYPE
	QString getCustomersDocName() {
        return QString("customers");
	}

	// returns products doc name stored as a DOCTYPE
	QString getProdutcsDocName() {
        return QString("products");
	}

	// @TODO enforce that translation won't affect this funcionality
	// converts customer type into int value
	int getCustomerType(QString custType) {
		if (custType.compare(trUtf8("Firma")) == 0 || custType.compare(trUtf8("firma")) == 0) {
			return 0;
		} else {
			return 1;
		}
	}

	// converts product type into int value
	int getProductType(QString prodName) {
		if (prodName.compare(trUtf8("Towar")) == 0 || prodName.compare(trUtf8("towar")) == 0) {
			return 0;
		} else {
			return 1;
		}
	}

	QString getCompanyName() {
        return QString("company");
	}

	QString getOfficeName() {
        return QString("office");
	}

	QString getCompanyNameTr() {
		return trUtf8("Firma");
	}

	QString getOfficeNameTr() {
		return trUtf8("Urząd");
	}

	QString getProductName() {
        return QString("product");
	}

	QString getServiceName() {
        return QString("service");
	}

	// Adds Data to input string
	QString getNameWithData(QString in) {
		return in + trUtf8("DATA");
	}


	QByteArray getCodecName() {
        return QByteArray("UTF-8");
	}

	QString getDecimalPointStr() {
		QChar decimalPoint = locale->decimalPoint ();
		return QString(decimalPoint);
	}

	QString getTPointStr() {
		QChar tPoint = locale->groupSeparator();
		return QString(tPoint);
	}

	QString numberToString(double i, char f = 'f', int prec = 2) {
			return locale->toString(i, f, prec);
		}

	QString numberToString(int i) {
			return locale->toString(i);
		}

	double stringToDouble(QString s) {

        bool ok = false;
        int countNumb = 1;

        QList<QLocale> allLocales = QLocale::matchingLocales(
                    QLocale::AnyLanguage,
                    QLocale::AnyScript,
                    QLocale::AnyCountry);

        for(const QLocale &locale : allLocales) {
            QLocale whatCountry(locale.language(),locale.country());
            if (whatCountry.toDouble(s, &ok)) {
                countNumb = whatCountry.toDouble(s, &ok);
                break;
            }
        }

        return countNumb;

		}

private:

	QString dateFormat;
	QString fileNameDateFormat;
	QLocale *locale;
    QTranslator* translator;

	// constr
	Settings() :
		QSettings("elinux", "qfaktury") {

		dateFormat = "dd/MM/yyyy";
		fileNameDateFormat = "yyyy-MM-dd";

        QTextCodec::setCodecForLocale(QTextCodec::codecForName (getCodecName()));
        QTextCodec::codecForUtfText(getCodecName());

		locale = new QLocale();

	}

	Settings(const Settings&):QSettings() {}

    friend Settings& sett() {
       static Settings sett;
       return sett;
    }
};

Settings& sett();

#endif
