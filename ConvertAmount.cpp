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
	// qDebug() << in;
	QString in = input.remove(sett().getTPointStr());

	QString tmp = in.remove(in.indexOf(sett().getDecimalPointStr()), 3);

	QString setki = tmp.right(3);
	QString tysiace;
	switch (tmp.length()) {
	case 4:
		tysiace = tmp.left(1);
		break;
	case 5:
		tysiace = tmp.left(2);
		break;
	case 6:
		tysiace = tmp.left(3);
		break;
	default:
		tysiace = QObject::trUtf8("");
		break;
	}

	QString out;

	QStringList jedynki;

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

	QStringList jedynki1;
	jedynki1 << QObject::trUtf8("jeden") << QObject::trUtf8("dwa")
			<< QObject::trUtf8("trzy") << QObject::trUtf8("cztery")
			<< QObject::trUtf8("pięć") << QObject::trUtf8("sześć")
			<< QObject::trUtf8("siedem") << QObject::trUtf8("osiem")
			<< QObject::trUtf8("dziewięć");

	QStringList nascie;
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

	QStringList nascie1;
	nascie1 << QObject::trUtf8("jedenaście") << QObject::trUtf8("dwanaście")
			<< QObject::trUtf8("trzynaście") << QObject::trUtf8("czternaście")
			<< QObject::trUtf8("piętnaście") << QObject::trUtf8("szesnaście")
			<< QObject::trUtf8("siedemnaście")
			<< QObject::trUtf8("osiemnaście") << QObject::trUtf8(
			"dziewiętnaście") << QObject::trUtf8("dziesięć");

	QStringList escia;
	escia << QObject::trUtf8("dwadziescia") << QObject::trUtf8("trzydziesci")
			<< QObject::trUtf8("czterdzieści")
			<< QObject::trUtf8("piędziesiąt")
			<< QObject::trUtf8("sześdziesiąt") << QObject::trUtf8(
			"siedemdziesiąt") << QObject::trUtf8("osiemdziesiąt")
			<< QObject::trUtf8("dziewięćdziesiąt");

	QStringList sta;
	sta << QObject::trUtf8("sto") << QObject::trUtf8("dwieście")
			<< QObject::trUtf8("trzysta") << QObject::trUtf8("czterysta")
			<< QObject::trUtf8("pięćset") << QObject::trUtf8("sześćset")
			<< QObject::trUtf8("siedemset") << QObject::trUtf8("osiemset")
			<< QObject::trUtf8("dziewięćset");

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

	if (out.length() > 2)
		out += QObject::trUtf8(" tys.");

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
