#include "slownie.h"
#include "Settings.h"

//     slownieLbl->setText ( slownie(kwotaEdit->text ()) );

QString slownie(QString input, QString waluta)
{
    QString in = input;

    QString tmp = in.remove (in.indexOf(UTF8(",")), 3);

    QString setki = tmp.right (3);
    QString tysiace;
    switch (tmp.length ())
    {
    case 4:
	tysiace = tmp.left (1);
	break;
    case 5:
	tysiace = tmp.left (2);
	break;
    case 6:
	tysiace = tmp.left (3);
	break;
    default:
	tysiace = UTF8("");
	break;
    }

    QString out;

    QStringList jedynki;

    jedynki << UTF8("jeden") << UTF8("dwa")  << UTF8("trzy") << UTF8("cztery") <<
	    UTF8("pięć") << UTF8("sześć") << UTF8("siedem") << UTF8("osiem") <<
	    UTF8("dziewięć");

/*
    jedynki << UTF8("jeden złotych") << UTF8("dwa złote")  << UTF8("trzy złote") << UTF8("cztery złote") <<
	    UTF8("pięć złotych") << UTF8("sześć złotych") << UTF8("siedem złotych") << UTF8("osiem złotych") <<
	    UTF8("dziewięć złotych");
    */

    QStringList jedynki1;
    jedynki1 << UTF8("jeden") << UTF8("dwa")  << UTF8("trzy") << UTF8("cztery") <<
	    UTF8("pięć") << UTF8("sześć") << UTF8("siedem") << UTF8("osiem") <<
	    UTF8("dziewięć");


    QStringList nascie;
    nascie << UTF8("jedenaście") << UTF8("dwanaście") << UTF8("trzynaście") <<
	    UTF8("czternaście") << UTF8("piętnaście") << UTF8("szesnaście") <<
	    UTF8("siedemnaście") << UTF8("osiemnaście") << UTF8("dziewiętnaście") <<
	    UTF8("dziesięć");
    /*
    nascie << UTF8("jedenaście złotych") << UTF8("dwanaście złotych") << UTF8("trzynaście złotych") <<
	    UTF8("czternaście złotych") << UTF8("piętnaście złotych") << UTF8("szesnaście złotych") <<
	    UTF8("siedemnaście złotych") << UTF8("osiemnaście złotych") << UTF8("dziewiętnaście złotych") <<
	    UTF8("dziesięć złotych");

      */

    QStringList nascie1;
    nascie1<< UTF8("jedenaście") << UTF8("dwanaście") << UTF8("trzynaście") <<
	    UTF8("czternaście") << UTF8("piętnaście") << UTF8("szesnaście") <<
	    UTF8("siedemnaście") << UTF8("osiemnaście") << UTF8("dziewiętnaście") <<
	    UTF8("dziesięć");


    QStringList escia;
    escia << UTF8("dwadziescia") << UTF8("trzydziesci") << UTF8("czterdzieści") <<
	    UTF8("piędziesiąt") << UTF8("sześdziesiąt") << UTF8("siedemdziesiąt") <<
	    UTF8("osiemdziesiąt") << UTF8("dziewięćdziesiąt");

    QStringList sta;
    sta << UTF8("sto") << UTF8("dwieście") << UTF8("trzysta") << UTF8("czterysta")
	    << UTF8("pięćset") << UTF8("sześćset") << UTF8("siedemset") <<
	    UTF8("osiemset") << UTF8("dziewięćset");


    // ******************************************************************
    while (tysiace.length () < 3) tysiace = UTF8("0") + tysiace;

    switch (tysiace.left (1).toInt ())
    {
    case 1:
	out += UTF8(" ") + sta[0];
	break;
    case 2:
	out += UTF8(" ") + sta[1];
	break;
    case 3:
	out += UTF8(" ") + sta[2];
	break;
    case 4:
	out += UTF8(" ") + sta[3];
	break;
    case 5:
	out += UTF8(" ") + sta[4];
	break;
    case 6:
	out += UTF8(" ") + sta[5];
	break;
    case 7:
	out += UTF8(" ") + sta[6];
	break;
    case 8:
	out += UTF8(" ") + sta[7];
	break;
    case 9:
	out += UTF8(" ") + sta[8];
	break;
    case 0:
	out += UTF8("");
	break;
    }

    if (tysiace.mid (1, 1).toInt () == 1)
    {
	switch (tysiace.right(1).toInt ())
	{
	case 1:
	    out += UTF8(" ")  + nascie1[0];
	    break;
	case 2:
	    out += UTF8(" ") + nascie1[1];
	    break;
	case 3:
	    out += UTF8(" ") + nascie1[2];
	    break;
	case 4:
	    out += UTF8(" ") + nascie1[3];
	    break;
	case 5:
	    out += UTF8(" ") + nascie1[4];
	    break;
	case 6:
	    out += UTF8(" ") + nascie1[5];
	    break;
	case 7:
	    out += UTF8(" ") + nascie1[6];
	    break;
	case 8:
	    out += UTF8(" ") + nascie1[7];
	    break;
	case 9:
	    out += UTF8(" ") + nascie1[8];
	    break;
	case 0:
	    out += UTF8(" ") + nascie1[9];
	    break;
	}
    } else {
	switch (tysiace.mid (1, 1).toInt ())
	{
	    //    case 1: out += nascie[0];
	    // break;
	case 2:
	    out += UTF8(" ") + escia[0];
	    break;
	case 3:
	    out += UTF8(" ") + escia[1];
	    break;
	case 4:
	    out += UTF8(" ") + escia[2];
	    break;
	case 5:
	    out += UTF8(" ") + escia[3];
	    break;
	case 6:
	    out += UTF8(" ") + escia[4];
	    break;
	case 7:
	    out += UTF8(" ") + escia[5];
	    break;
	case 8:
	    out += UTF8(" ") + escia[6];
	    break;
	case 9:
	    out += UTF8(" ") + escia[7];
	    break;
	case 0:
	    out += UTF8("");
	    break;
	}
	switch (tysiace.right (1).toInt ())
	{
	case 1:
	    out += UTF8(" ") + jedynki1[0];
	    break;
	case 2:
	    out += UTF8(" ") + jedynki1[1];
	    break;
	case 3:
	    out += UTF8(" ") + jedynki1[2];
	    break;
	case 4:
	    out += UTF8(" ") + jedynki1[3];
	    break;
	case 5:
	    out += UTF8(" ") + jedynki1[4];
	    break;
	case 6:
	    out += UTF8(" ") + jedynki1[5];
	    break;
	case 7:
	    out += UTF8(" ") + jedynki1[6];
	    break;
	case 8:
	    out += UTF8(" ") + jedynki1[7];
	    break;
	case 9:
	    out += UTF8(" ") + jedynki1[8];
	    break;
	case 0:
	    out += UTF8("");
	    break;
	}
    }


    if (out.length () > 2)
	out += UTF8(" tys.");


    //***************************************************************
    while (setki.length () < 3)
	setki = UTF8("0") + setki;

    switch (setki.left (1).toInt ())
    {
    case 1:
	out += UTF8(" ") + sta[0];
	break;
    case 2:
	out += UTF8(" ") + sta[1];
	break;
    case 3:
	out += UTF8(" ") + sta[2];
	break;
    case 4:
	out += UTF8(" ") + sta[3];
	break;
    case 5:
	out += UTF8(" ") + sta[4];
	break;
    case 6:
	out += UTF8(" ") + sta[5];
	break;
    case 7:
	out += UTF8(" ") + sta[6];
	break;
    case 8:
	out += UTF8(" ") + sta[7];
	break;
    case 9:
	out += UTF8(" ") + sta[8];
	break;
    case 0:
	out += UTF8("");
	break;
    }

    switch (setki.mid (1, 1).toInt ())
    {
	//    case 1: out += nascie[0];
	// break;
    case 2:
	out += UTF8(" ") + escia[0];
	break;
    case 3:
	out += UTF8(" ") + escia[1];
	break;
    case 4:
	out += UTF8(" ") + escia[2];
	break;
    case 5:
	out += UTF8(" ") + escia[3];
	break;
    case 6:
	out += UTF8(" ") + escia[4];
	break;
    case 7:
	out += UTF8(" ") + escia[5];
	break;
    case 8:
	out += UTF8(" ") + escia[6];
	break;
    case 9:
	out += UTF8(" ") + escia[7];
	break;
    case 0:
	out += UTF8("");
	break;
    }


    if (setki.mid (1, 1).toInt () == 1)
    {
	switch (setki.right (1).toInt ())
	{
	case 1:
	    out += UTF8(" ") + nascie[0];
	    break;
	case 2:
	    out += UTF8(" ") + nascie[1];
	    break;
	case 3:
	    out += UTF8(" ") + nascie[2];
	    break;
	case 4:
	    out += UTF8(" ") + nascie[3];
	    break;
	case 5:
	    out += UTF8(" ") + nascie[4];
	    break;
	case 6:
	    out += UTF8(" ") + nascie[5];
	    break;
	case 7:
	    out += UTF8(" ") + nascie[6];
	    break;
	case 8:
	    out += UTF8(" ") + nascie[7];
	    break;
	case 9:
	    out += UTF8(" ") + nascie[8];
	    break;
	case 0:
	    out +=  UTF8(" ")+ nascie[9];
	    break;
	}
    }
    else
    {
	switch (setki.right (1).toInt ())
	{
	case 1:
	    out += UTF8(" ") + jedynki[0];
	    break;
	case 2:
	    out += UTF8(" ") + jedynki[1];
	    break;
	case 3:
	    out += UTF8(" ") + jedynki[2];
	    break;
	case 4:
	    out += UTF8(" ") + jedynki[3];
	    break;
	case 5:
	    out += UTF8(" ") + jedynki[4];
	    break;
	case 6:
	    out += UTF8(" ") + jedynki[5];
	    break;
	case 7:
	    out += UTF8(" ") + jedynki[6];
	    break;
	case 8:
	    out += UTF8(" ") + jedynki[7];
	    break;
	case 9:
	    out += UTF8(" ") + jedynki[8];
	    break;
	case 0:
	    out += UTF8(" zero"); // waluta; // UTF8(" złotych");
	    break;
	}

    }

    in = input;
    QString grosze =
	    in.remove (0, in.indexOf(UTF8(",")) + 1);
    return out + UTF8(" ") + grosze + UTF8("/100 ") + waluta;
}
