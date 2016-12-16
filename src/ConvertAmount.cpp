/*
 * ConvertAmount.cpp
 *
 *  Created on: Mar 16, 2009
 *      Author: tpielech
 */

#include "ConvertAmount.h"

ConvertAmount::ConvertAmount() {
	// TODO Auto-generated constructor stub

}

ConvertAmount::~ConvertAmount() {
	// TODO Auto-generated destructor stub
}

QString& ConvertAmount::descAmount(QString & countMoney, QString partMoney, QString ifOne, QString ifMore, QString ifBetween)
{
    while (partMoney.length() < 3)
        partMoney = QObject::trUtf8("0") + partMoney;

    switch (partMoney.left(1).toInt()) {
    case 1:
        countMoney += QObject::trUtf8(" ") + staList()[0];
        break;
    case 2:
        countMoney += QObject::trUtf8(" ") + staList()[1];
        break;
    case 3:
        countMoney += QObject::trUtf8(" ") + staList()[2];
        break;
    case 4:
        countMoney += QObject::trUtf8(" ") + staList()[3];
        break;
    case 5:
        countMoney += QObject::trUtf8(" ") + staList()[4];
        break;
    case 6:
        countMoney += QObject::trUtf8(" ") + staList()[5];
        break;
    case 7:
        countMoney += QObject::trUtf8(" ") + staList()[6];
        break;
    case 8:
        countMoney += QObject::trUtf8(" ") + staList()[7];
        break;
    case 9:
        countMoney += QObject::trUtf8(" ") + staList()[8];
        break;
    case 0:
        countMoney += QObject::trUtf8("");
        break;
    }

    if (partMoney.mid(1, 1).toInt() == 1) {
        switch (partMoney.right(1).toInt()) {
        case 1:
            countMoney += QObject::trUtf8(" ") + nascieList()[0];
            break;
        case 2:
            countMoney += QObject::trUtf8(" ") + nascieList()[1];
            break;
        case 3:
            countMoney += QObject::trUtf8(" ") + nascieList()[2];
            break;
        case 4:
            countMoney += QObject::trUtf8(" ") + nascieList()[3];
            break;
        case 5:
            countMoney += QObject::trUtf8(" ") + nascieList()[4];
            break;
        case 6:
            countMoney += QObject::trUtf8(" ") + nascieList()[5];
            break;
        case 7:
            countMoney += QObject::trUtf8(" ") + nascieList()[6];
            break;
        case 8:
            countMoney += QObject::trUtf8(" ") + nascieList()[7];
            break;
        case 9:
            countMoney += QObject::trUtf8(" ") + nascieList()[8];
            break;
        case 0:
            countMoney += QObject::trUtf8(" ") + nascieList()[9];
            break;
        }
    } else {
        switch (partMoney.mid(1, 1).toInt()) {
        case 2:
            countMoney += QObject::trUtf8(" ") + esciaList()[0];
            break;
        case 3:
            countMoney += QObject::trUtf8(" ") + esciaList()[1];
            break;
        case 4:
            countMoney += QObject::trUtf8(" ") + esciaList()[2];
            break;
        case 5:
            countMoney += QObject::trUtf8(" ") + esciaList()[3];
            break;
        case 6:
            countMoney += QObject::trUtf8(" ") + esciaList()[4];
            break;
        case 7:
            countMoney += QObject::trUtf8(" ") + esciaList()[5];
            break;
        case 8:
            countMoney += QObject::trUtf8(" ") + esciaList()[6];
            break;
        case 9:
            countMoney += QObject::trUtf8(" ") + esciaList()[7];
            break;
        case 0:
            countMoney += QObject::trUtf8("");
            break;
        }
        switch (partMoney.right(1).toInt()) {
        case 1:
            countMoney += QObject::trUtf8(" ") + jedynkiList()[0];
            break;
        case 2:
            countMoney += QObject::trUtf8(" ") + jedynkiList()[1];
            break;
        case 3:
            countMoney += QObject::trUtf8(" ") + jedynkiList()[2];
            break;
        case 4:
            countMoney += QObject::trUtf8(" ") + jedynkiList()[3];
            break;
        case 5:
            countMoney += QObject::trUtf8(" ") + jedynkiList()[4];
            break;
        case 6:
            countMoney += QObject::trUtf8(" ") + jedynkiList()[5];
            break;
        case 7:
            countMoney += QObject::trUtf8(" ") + jedynkiList()[6];
            break;
        case 8:
            countMoney += QObject::trUtf8(" ") + jedynkiList()[7];
            break;
        case 9:
            countMoney += QObject::trUtf8(" ") + jedynkiList()[8];
            break;
        case 0:
            countMoney += QObject::trUtf8("");
            break;
        }
    }

    if (!ifOne.isEmpty() && !ifOne.isNull()) {
    if (partMoney.toInt() > 9) {

                countMoney += ifMore;
                qDebug() << "partMoney.toInt() > 9: " << partMoney.toInt();

    } else if ((partMoney.toInt() < 10) && (partMoney.toInt() > 0)) {

            if ((partMoney.toInt() > 1) && (partMoney.toInt() < 5)) countMoney += ifBetween;
            else if (partMoney.toInt() > 4) countMoney += ifMore;
            else countMoney += ifOne;
            qDebug() << "partMoney.toInt() >= 1: " << partMoney.toInt();

    }
    }

    return countMoney;
}

const QStringList ConvertAmount::staList() const {

    QStringList sta = QStringList();
    sta << QObject::trUtf8("sto") << QObject::trUtf8("dwieście")
            << QObject::trUtf8("trzysta") << QObject::trUtf8("czterysta")
            << QObject::trUtf8("pięćset") << QObject::trUtf8("sześćset")
            << QObject::trUtf8("siedemset") << QObject::trUtf8("osiemset")
            << QObject::trUtf8("dziewięćset");

    return sta;
}

const QStringList ConvertAmount::esciaList() const {

    QStringList escia = QStringList();
    escia << QObject::trUtf8("dwadzieścia") << QObject::trUtf8("trzydzieści")
            << QObject::trUtf8("czterdzieści")
            << QObject::trUtf8("pięćdziesiąt")
            << QObject::trUtf8("sześdziesiąt") << QObject::trUtf8(
            "siedemdziesiąt") << QObject::trUtf8("osiemdziesiąt")
            << QObject::trUtf8("dziewięćdziesiąt");

    return escia;
}

const QStringList ConvertAmount::nascieList() const {

    QStringList nascie = QStringList();
    nascie << QObject::trUtf8("jedenaście") << QObject::trUtf8("dwanaście")
            << QObject::trUtf8("trzynaście") << QObject::trUtf8("czternaście")
            << QObject::trUtf8("piętnaście") << QObject::trUtf8("szesnaście")
            << QObject::trUtf8("siedemnaście")
            << QObject::trUtf8("osiemnaście") << QObject::trUtf8(
            "dziewiętnaście") << QObject::trUtf8("dziesięć");

    return nascie;
}

const QStringList ConvertAmount::jedynkiList() const {

    QStringList jedynki = QStringList();
    jedynki << QObject::trUtf8("jeden") << QObject::trUtf8("dwa")
            << QObject::trUtf8("trzy") << QObject::trUtf8("cztery")
            << QObject::trUtf8("pięć") << QObject::trUtf8("sześć")
            << QObject::trUtf8("siedem") << QObject::trUtf8("osiem")
            << QObject::trUtf8("dziewięć");

    return jedynki;
}

QString ConvertAmount::convertPL(QString input, QString waluta) {

	QString in = input.remove(sett().getTPointStr());
    qDebug() << "in: " << in;

	QString tmp = in.remove(in.indexOf(sett().getDecimalPointStr()), 3);
    qDebug() << "temp: " << tmp;

	QString setki = tmp.right(3);
    QString tysiace = QString();
    QString miliony = QString();
    QString miliardy = QString();

	switch (tmp.length()) {
	case 4:

		tysiace = tmp.left(1);
        miliony = QObject::trUtf8("");
        miliardy = QObject::trUtf8("");
		break;

	case 5:

		tysiace = tmp.left(2);
        miliony = QObject::trUtf8("");
        miliardy = QObject::trUtf8("");
		break;

	case 6:

		tysiace = tmp.left(3);
        miliony = QObject::trUtf8("");
        miliardy = QObject::trUtf8("");
		break;

    case 7:

        miliony = tmp.left(1);
        tysiace = tmp.mid(1,3);
        miliardy = QObject::trUtf8("");
        break;

    case 8:

        miliony = tmp.left(2);
        tysiace = tmp.mid(2,3);
        miliardy = QObject::trUtf8("");
        break;

    case 9:

        miliony = tmp.left(3);
        tysiace = tmp.mid(3,3);
        miliardy = QObject::trUtf8("");
        break;

    case 10:

        miliardy = tmp.left(1);
        miliony = tmp.mid(1,3);
        tysiace = tmp.mid(4,3);
        break;

    case 11:

        miliardy = tmp.left(2);
        miliony = tmp.mid(2,3);
        tysiace = tmp.mid(5,3);
        break;

    case 12:

        miliardy = tmp.left(3);
        miliony = tmp.mid(3,3);
        tysiace = tmp.mid(6,3);
        break;

	default:

		tysiace = QObject::trUtf8("");
        miliony = QObject::trUtf8("");
        miliardy = QObject::trUtf8("");
		break;
	}

    qDebug() << "wartość miliarda: " << miliardy;
    qDebug() << "wartość miliona: " << miliony;
    qDebug() << "wartość tysiąca: " << tysiace;

    QString out = QString();

   descAmount(out, miliardy, QObject::trUtf8(" miliard"), QObject::trUtf8(" miliardów"), QObject::trUtf8(" miliardy"));
   descAmount(out, miliony, QObject::trUtf8(" milion"), QObject::trUtf8(" milionów"), QObject::trUtf8(" miliony"));
   descAmount(out, tysiace, QObject::trUtf8(" tysiąc"), QObject::trUtf8(" tysięcy"), QObject::trUtf8(" tysiące"));
   descAmount(out, setki);

	in = input;
	QString grosze = in.remove(0, in.indexOf(sett().getDecimalPointStr()) + 1);

	return out + QObject::trUtf8(" ") + grosze + QObject::trUtf8("/100 ")
			+ waluta;

}
