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


    QStringList jedynki = QStringList();

	jedynki << QObject::trUtf8("jeden") << QObject::trUtf8("dwa")
			<< QObject::trUtf8("trzy") << QObject::trUtf8("cztery")
			<< QObject::trUtf8("pięć") << QObject::trUtf8("sześć")
			<< QObject::trUtf8("siedem") << QObject::trUtf8("osiem")
			<< QObject::trUtf8("dziewięć");

	/*
	 jedynki << QObject::trUtf8("jeden złotych") << QObject::trUtf8("dwa złote")  << QObject::trUtf8("trzy złote") << QObject::trUtf8("cztery złote") <<
	 QObject::trUtf8("pięć złotych") << QObject::trUtf8("sześć złotych") << QObject::trUtf8("siedem złotych") << QObject::trUtf8("osiem złotych") <<
	 QObject::trUtf8("dziewięć złotych");
	 */

    QStringList jedynki1 = QStringList();
	jedynki1 << QObject::trUtf8("jeden") << QObject::trUtf8("dwa")
			<< QObject::trUtf8("trzy") << QObject::trUtf8("cztery")
			<< QObject::trUtf8("pięć") << QObject::trUtf8("sześć")
			<< QObject::trUtf8("siedem") << QObject::trUtf8("osiem")
			<< QObject::trUtf8("dziewięć");

    QStringList nascie = QStringList();
	nascie << QObject::trUtf8("jedenaście") << QObject::trUtf8("dwanaście")
			<< QObject::trUtf8("trzynaście") << QObject::trUtf8("czternaście")
			<< QObject::trUtf8("piętnaście") << QObject::trUtf8("szesnaście")
			<< QObject::trUtf8("siedemnaście")
			<< QObject::trUtf8("osiemnaście") << QObject::trUtf8(
			"dziewiętnaście") << QObject::trUtf8("dziesięć");

	/*
	 nascie << QObject::trUtf8("jedenaście złotych") << QObject::trUtf8("dwanaście złotych") << QObject::trUtf8("trzynaście złotych") <<
	 QObject::trUtf8("czternaście złotych") << QObject::trUtf8("piętnaście złotych") << QObject::trUtf8("szesnaście złotych") <<
	 QObject::trUtf8("siedemnaście złotych") << QObject::trUtf8("osiemnaście złotych") << QObject::trUtf8("dziewiętnaście złotych") <<
	 QObject::trUtf8("dziesięć złotych");

	 */

    QStringList nascie1 = QStringList();
	nascie1 << QObject::trUtf8("jedenaście") << QObject::trUtf8("dwanaście")
			<< QObject::trUtf8("trzynaście") << QObject::trUtf8("czternaście")
			<< QObject::trUtf8("piętnaście") << QObject::trUtf8("szesnaście")
			<< QObject::trUtf8("siedemnaście")
			<< QObject::trUtf8("osiemnaście") << QObject::trUtf8(
			"dziewiętnaście") << QObject::trUtf8("dziesięć");

    QStringList escia = QStringList();
	escia << QObject::trUtf8("dwadzieścia") << QObject::trUtf8("trzydzieści")
			<< QObject::trUtf8("czterdzieści")
			<< QObject::trUtf8("pięćdziesiąt")
			<< QObject::trUtf8("sześdziesiąt") << QObject::trUtf8(
			"siedemdziesiąt") << QObject::trUtf8("osiemdziesiąt")
			<< QObject::trUtf8("dziewięćdziesiąt");

    QStringList sta = QStringList();
	sta << QObject::trUtf8("sto") << QObject::trUtf8("dwieście")
			<< QObject::trUtf8("trzysta") << QObject::trUtf8("czterysta")
			<< QObject::trUtf8("pięćset") << QObject::trUtf8("sześćset")
			<< QObject::trUtf8("siedemset") << QObject::trUtf8("osiemset")
			<< QObject::trUtf8("dziewięćset");


    // ******************************************************************
    while (miliardy.length() < 3)
        miliardy = QObject::trUtf8("0") + miliardy;

    switch (miliardy.left(1).toInt()) {
    case 1:
        out += QObject::trUtf8(" ") + sta[0];
        break;
    case 2:
        out += QObject::trUtf8(" ") + sta[1];
        break;
    case 3:
        out += QObject::trUtf8(" ") + sta[2];
        break;
    case 4:
        out += QObject::trUtf8(" ") + sta[3];
        break;
    case 5:
        out += QObject::trUtf8(" ") + sta[4];
        break;
    case 6:
        out += QObject::trUtf8(" ") + sta[5];
        break;
    case 7:
        out += QObject::trUtf8(" ") + sta[6];
        break;
    case 8:
        out += QObject::trUtf8(" ") + sta[7];
        break;
    case 9:
        out += QObject::trUtf8(" ") + sta[8];
        break;
    case 0:
        out += QObject::trUtf8("");
        break;
    }

    if (miliardy.mid(1, 1).toInt() == 1) {
        switch (miliardy.right(1).toInt()) {
        case 1:
            out += QObject::trUtf8(" ") + nascie1[0];
            break;
        case 2:
            out += QObject::trUtf8(" ") + nascie1[1];
            break;
        case 3:
            out += QObject::trUtf8(" ") + nascie1[2];
            break;
        case 4:
            out += QObject::trUtf8(" ") + nascie1[3];
            break;
        case 5:
            out += QObject::trUtf8(" ") + nascie1[4];
            break;
        case 6:
            out += QObject::trUtf8(" ") + nascie1[5];
            break;
        case 7:
            out += QObject::trUtf8(" ") + nascie1[6];
            break;
        case 8:
            out += QObject::trUtf8(" ") + nascie1[7];
            break;
        case 9:
            out += QObject::trUtf8(" ") + nascie1[8];
            break;
        case 0:
            out += QObject::trUtf8(" ") + nascie1[9];
            break;
        }
    } else {
        switch (miliardy.mid(1, 1).toInt()) {
        //    case 1: out += nascie[0];
        // break;
        case 2:
            out += QObject::trUtf8(" ") + escia[0];
            break;
        case 3:
            out += QObject::trUtf8(" ") + escia[1];
            break;
        case 4:
            out += QObject::trUtf8(" ") + escia[2];
            break;
        case 5:
            out += QObject::trUtf8(" ") + escia[3];
            break;
        case 6:
            out += QObject::trUtf8(" ") + escia[4];
            break;
        case 7:
            out += QObject::trUtf8(" ") + escia[5];
            break;
        case 8:
            out += QObject::trUtf8(" ") + escia[6];
            break;
        case 9:
            out += QObject::trUtf8(" ") + escia[7];
            break;
        case 0:
            out += QObject::trUtf8("");
            break;
        }
        switch (miliardy.right(1).toInt()) {
        case 1:
            out += QObject::trUtf8(" ") + jedynki1[0];
            break;
        case 2:
            out += QObject::trUtf8(" ") + jedynki1[1];
            break;
        case 3:
            out += QObject::trUtf8(" ") + jedynki1[2];
            break;
        case 4:
            out += QObject::trUtf8(" ") + jedynki1[3];
            break;
        case 5:
            out += QObject::trUtf8(" ") + jedynki1[4];
            break;
        case 6:
            out += QObject::trUtf8(" ") + jedynki1[5];
            break;
        case 7:
            out += QObject::trUtf8(" ") + jedynki1[6];
            break;
        case 8:
            out += QObject::trUtf8(" ") + jedynki1[7];
            break;
        case 9:
            out += QObject::trUtf8(" ") + jedynki1[8];
            break;
        case 0:
            out += QObject::trUtf8("");
            break;
        }
    }

    if (miliardy.toInt() > 9) {

                out += QObject::trUtf8(" miliardów");
                qDebug() << "miliardy.toInt() > 9: " << miliardy.toInt();

    } else if ((miliardy.toInt() < 10) && (miliardy.toInt() > 0)) {

            if ((miliardy.toInt() > 1) && (miliardy.toInt() < 5)) out += QObject::trUtf8(" miliardy");
            else if (miliardy.toInt() > 4) out += QObject::trUtf8(" miliardów");
            else out += QObject::trUtf8(" miliard");
            qDebug() << "miliardy.toInt() >= 1: " << miliardy.toInt();

    }

    // ******************************************************************
    while (miliony.length() < 3)
        miliony = QObject::trUtf8("0") + miliony;

    switch (miliony.left(1).toInt()) {
    case 1:
        out += QObject::trUtf8(" ") + sta[0];
        break;
    case 2:
        out += QObject::trUtf8(" ") + sta[1];
        break;
    case 3:
        out += QObject::trUtf8(" ") + sta[2];
        break;
    case 4:
        out += QObject::trUtf8(" ") + sta[3];
        break;
    case 5:
        out += QObject::trUtf8(" ") + sta[4];
        break;
    case 6:
        out += QObject::trUtf8(" ") + sta[5];
        break;
    case 7:
        out += QObject::trUtf8(" ") + sta[6];
        break;
    case 8:
        out += QObject::trUtf8(" ") + sta[7];
        break;
    case 9:
        out += QObject::trUtf8(" ") + sta[8];
        break;
    case 0:
        out += QObject::trUtf8("");
        break;
    }

    if (miliony.mid(1, 1).toInt() == 1) {
        switch (miliony.right(1).toInt()) {
        case 1:
            out += QObject::trUtf8(" ") + nascie1[0];
            break;
        case 2:
            out += QObject::trUtf8(" ") + nascie1[1];
            break;
        case 3:
            out += QObject::trUtf8(" ") + nascie1[2];
            break;
        case 4:
            out += QObject::trUtf8(" ") + nascie1[3];
            break;
        case 5:
            out += QObject::trUtf8(" ") + nascie1[4];
            break;
        case 6:
            out += QObject::trUtf8(" ") + nascie1[5];
            break;
        case 7:
            out += QObject::trUtf8(" ") + nascie1[6];
            break;
        case 8:
            out += QObject::trUtf8(" ") + nascie1[7];
            break;
        case 9:
            out += QObject::trUtf8(" ") + nascie1[8];
            break;
        case 0:
            out += QObject::trUtf8(" ") + nascie1[9];
            break;
        }
    } else {
        switch (miliony.mid(1, 1).toInt()) {
        //    case 1: out += nascie[0];
        // break;
        case 2:
            out += QObject::trUtf8(" ") + escia[0];
            break;
        case 3:
            out += QObject::trUtf8(" ") + escia[1];
            break;
        case 4:
            out += QObject::trUtf8(" ") + escia[2];
            break;
        case 5:
            out += QObject::trUtf8(" ") + escia[3];
            break;
        case 6:
            out += QObject::trUtf8(" ") + escia[4];
            break;
        case 7:
            out += QObject::trUtf8(" ") + escia[5];
            break;
        case 8:
            out += QObject::trUtf8(" ") + escia[6];
            break;
        case 9:
            out += QObject::trUtf8(" ") + escia[7];
            break;
        case 0:
            out += QObject::trUtf8("");
            break;
        }
        switch (miliony.right(1).toInt()) {
        case 1:
            out += QObject::trUtf8(" ") + jedynki1[0];
            break;
        case 2:
            out += QObject::trUtf8(" ") + jedynki1[1];
            break;
        case 3:
            out += QObject::trUtf8(" ") + jedynki1[2];
            break;
        case 4:
            out += QObject::trUtf8(" ") + jedynki1[3];
            break;
        case 5:
            out += QObject::trUtf8(" ") + jedynki1[4];
            break;
        case 6:
            out += QObject::trUtf8(" ") + jedynki1[5];
            break;
        case 7:
            out += QObject::trUtf8(" ") + jedynki1[6];
            break;
        case 8:
            out += QObject::trUtf8(" ") + jedynki1[7];
            break;
        case 9:
            out += QObject::trUtf8(" ") + jedynki1[8];
            break;
        case 0:
            out += QObject::trUtf8("");
            break;
        }
    }

    if (miliony.toInt() > 9) {

                out += QObject::trUtf8(" milionów");
                qDebug() << "miliony.toInt() > 9: " << miliony.toInt();

    } else if ((miliony.toInt() < 10) && (miliony.toInt() > 0)) {

            if ((miliony.toInt() > 1) && (miliony.toInt() < 5)) out += QObject::trUtf8(" miliony");
            else if (miliony.toInt() > 4) out += QObject::trUtf8(" milionów");
            else out += QObject::trUtf8(" milion");
            qDebug() << "miliony.toInt() >= 1: " << miliony.toInt();

    }


	// ******************************************************************
	while (tysiace.length() < 3)
		tysiace = QObject::trUtf8("0") + tysiace;

	switch (tysiace.left(1).toInt()) {
	case 1:
		out += QObject::trUtf8(" ") + sta[0];
		break;
	case 2:
		out += QObject::trUtf8(" ") + sta[1];
		break;
	case 3:
		out += QObject::trUtf8(" ") + sta[2];
		break;
	case 4:
		out += QObject::trUtf8(" ") + sta[3];
		break;
	case 5:
		out += QObject::trUtf8(" ") + sta[4];
		break;
	case 6:
		out += QObject::trUtf8(" ") + sta[5];
		break;
	case 7:
		out += QObject::trUtf8(" ") + sta[6];
		break;
	case 8:
		out += QObject::trUtf8(" ") + sta[7];
		break;
	case 9:
		out += QObject::trUtf8(" ") + sta[8];
		break;
	case 0:
		out += QObject::trUtf8("");
		break;
	}

	if (tysiace.mid(1, 1).toInt() == 1) {
		switch (tysiace.right(1).toInt()) {
		case 1:
			out += QObject::trUtf8(" ") + nascie1[0];
			break;
		case 2:
			out += QObject::trUtf8(" ") + nascie1[1];
			break;
		case 3:
			out += QObject::trUtf8(" ") + nascie1[2];
			break;
		case 4:
			out += QObject::trUtf8(" ") + nascie1[3];
			break;
		case 5:
			out += QObject::trUtf8(" ") + nascie1[4];
			break;
		case 6:
			out += QObject::trUtf8(" ") + nascie1[5];
			break;
		case 7:
			out += QObject::trUtf8(" ") + nascie1[6];
			break;
		case 8:
			out += QObject::trUtf8(" ") + nascie1[7];
			break;
		case 9:
			out += QObject::trUtf8(" ") + nascie1[8];
			break;
		case 0:
			out += QObject::trUtf8(" ") + nascie1[9];
			break;
		}
	} else {
		switch (tysiace.mid(1, 1).toInt()) {
		//    case 1: out += nascie[0];
		// break;
		case 2:
			out += QObject::trUtf8(" ") + escia[0];
			break;
		case 3:
			out += QObject::trUtf8(" ") + escia[1];
			break;
		case 4:
			out += QObject::trUtf8(" ") + escia[2];
			break;
		case 5:
			out += QObject::trUtf8(" ") + escia[3];
			break;
		case 6:
			out += QObject::trUtf8(" ") + escia[4];
			break;
		case 7:
			out += QObject::trUtf8(" ") + escia[5];
			break;
		case 8:
			out += QObject::trUtf8(" ") + escia[6];
			break;
		case 9:
			out += QObject::trUtf8(" ") + escia[7];
			break;
		case 0:
			out += QObject::trUtf8("");
			break;
		}
		switch (tysiace.right(1).toInt()) {
		case 1:
			out += QObject::trUtf8(" ") + jedynki1[0];
			break;
		case 2:
			out += QObject::trUtf8(" ") + jedynki1[1];
			break;
		case 3:
			out += QObject::trUtf8(" ") + jedynki1[2];
			break;
		case 4:
			out += QObject::trUtf8(" ") + jedynki1[3];
			break;
		case 5:
			out += QObject::trUtf8(" ") + jedynki1[4];
			break;
		case 6:
			out += QObject::trUtf8(" ") + jedynki1[5];
			break;
		case 7:
			out += QObject::trUtf8(" ") + jedynki1[6];
			break;
		case 8:
			out += QObject::trUtf8(" ") + jedynki1[7];
			break;
		case 9:
			out += QObject::trUtf8(" ") + jedynki1[8];
			break;
		case 0:
			out += QObject::trUtf8("");
			break;
		}
	}

    if (tysiace.toInt() > 9) {

                out += QObject::trUtf8(" tysięcy");

    } else if (tysiace.toInt() < 10) {

            if ((tysiace.toInt() > 1) && (tysiace.toInt() < 5)) out += QObject::trUtf8(" tysiące");
            else if (tysiace.toInt() > 4) out += QObject::trUtf8(" tysięcy");
            else out += QObject::trUtf8(" tysiąc");

    }

	//***************************************************************
	while (setki.length() < 3)
		setki = QObject::trUtf8("0") + setki;

	switch (setki.left(1).toInt()) {
	case 1:
		out += QObject::trUtf8(" ") + sta[0];
		break;
	case 2:
		out += QObject::trUtf8(" ") + sta[1];
		break;
	case 3:
		out += QObject::trUtf8(" ") + sta[2];
		break;
	case 4:
		out += QObject::trUtf8(" ") + sta[3];
		break;
	case 5:
		out += QObject::trUtf8(" ") + sta[4];
		break;
	case 6:
		out += QObject::trUtf8(" ") + sta[5];
		break;
	case 7:
		out += QObject::trUtf8(" ") + sta[6];
		break;
	case 8:
		out += QObject::trUtf8(" ") + sta[7];
		break;
	case 9:
		out += QObject::trUtf8(" ") + sta[8];
		break;
	case 0:
		out += QObject::trUtf8("");
		break;
	}

	switch (setki.mid(1, 1).toInt()) {
	//    case 1: out += nascie[0];
	// break;
	case 2:
		out += QObject::trUtf8(" ") + escia[0];
		break;
	case 3:
		out += QObject::trUtf8(" ") + escia[1];
		break;
	case 4:
		out += QObject::trUtf8(" ") + escia[2];
		break;
	case 5:
		out += QObject::trUtf8(" ") + escia[3];
		break;
	case 6:
		out += QObject::trUtf8(" ") + escia[4];
		break;
	case 7:
		out += QObject::trUtf8(" ") + escia[5];
		break;
	case 8:
		out += QObject::trUtf8(" ") + escia[6];
		break;
	case 9:
		out += QObject::trUtf8(" ") + escia[7];
		break;
	case 0:
		out += QObject::trUtf8("");
		break;
	}

	if (setki.mid(1, 1).toInt() == 1) {
		switch (setki.right(1).toInt()) {
		case 1:
			out += QObject::trUtf8(" ") + nascie[0];
			break;
		case 2:
			out += QObject::trUtf8(" ") + nascie[1];
			break;
		case 3:
			out += QObject::trUtf8(" ") + nascie[2];
			break;
		case 4:
			out += QObject::trUtf8(" ") + nascie[3];
			break;
		case 5:
			out += QObject::trUtf8(" ") + nascie[4];
			break;
		case 6:
			out += QObject::trUtf8(" ") + nascie[5];
			break;
		case 7:
			out += QObject::trUtf8(" ") + nascie[6];
			break;
		case 8:
			out += QObject::trUtf8(" ") + nascie[7];
			break;
		case 9:
			out += QObject::trUtf8(" ") + nascie[8];
			break;
		case 0:
			out += QObject::trUtf8(" ") + nascie[9];
			break;
		}
	} else {
		switch (setki.right(1).toInt()) {
		case 1:
			out += QObject::trUtf8(" ") + jedynki[0];
			break;
		case 2:
			out += QObject::trUtf8(" ") + jedynki[1];
			break;
		case 3:
			out += QObject::trUtf8(" ") + jedynki[2];
			break;
		case 4:
			out += QObject::trUtf8(" ") + jedynki[3];
			break;
		case 5:
			out += QObject::trUtf8(" ") + jedynki[4];
			break;
		case 6:
			out += QObject::trUtf8(" ") + jedynki[5];
			break;
		case 7:
			out += QObject::trUtf8(" ") + jedynki[6];
			break;
		case 8:
			out += QObject::trUtf8(" ") + jedynki[7];
			break;
		case 9:
			out += QObject::trUtf8(" ") + jedynki[8];
			break;
		case 0:
			out += QObject::trUtf8(" "); // waluta; // QObject::trUtf8(" złotych");
			break;
		}

	}

	in = input;
	QString grosze = in.remove(0, in.indexOf(sett().getDecimalPointStr()) + 1);
	return out + QObject::trUtf8(" ") + grosze + QObject::trUtf8("/100 ")
			+ waluta;
}
