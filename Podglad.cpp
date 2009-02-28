#include "Podglad.moc"
#include <QPainter>
#include <QPixmap>
#include <QLabel>
#include <QDebug>
#include <QToolBar>

/** Default constructor
 */
Podglad::Podglad(QWidget *parent): QDialog(parent) {
    setupUi(this);
    init();
}


/** Init method
 */
void Podglad::init() {

	scale = 1;
	makePdf = false;

	margTop = settings.value("margTopPrinter").toInt() * 4;
	margLeft = settings.value("margLeftPrinter").toInt() * 4;
	margRight = settings.value("margRightPrinter").toInt() * 4;
	margDown = settings.value("margDownPrinter").toInt() * 4;
	pageMargTop = static_cast<double> (settings.value("margTopPrinter").toInt() * 4);
	pageMargLeft
			= static_cast<double> (settings.value("margLeftPrinter").toInt() * 4);
	pageMargRight
			= static_cast<double> (settings.value("margRightPrinter").toInt() * 4);
	pageMargDown
			= static_cast<double> (settings.value("margDownPrinter").toInt() * 4);

	label = new QLabel("", NULL);
	view->setWidget(label);
	label->setGeometry(0, 0, 840, 1188); // why 00 840 1188


    // signals and slots connections
    connect( savepdfbtn, SIGNAL( clicked() ), this, SLOT( exportPdf() ) );
    // connect( pagespinbox, SIGNAL( valueChanged(int) ), this, SLOT( scroolChanged(int) ) );
    connect( cnlBtn, SIGNAL( clicked() ), this, SLOT( close() ) );
    // connect( htmlBtn, SIGNAL( clicked() ), this, SLOT( exportHtml() ) );
    connect( prnBtn, SIGNAL( clicked() ), this, SLOT( printPages() ) );
    connect( jpgBtn, SIGNAL( clicked() ), this, SLOT( exportJpg() ) );
    connect( pushButton6, SIGNAL( clicked() ), this, SLOT( printTransfer() ) );

}

/** Print all the pages
 */
void Podglad::printPages()
{
	/*
    QPrinter printer;
    printer.setFullPage( TRUE );
    printer.setDocName("QFaktury GPL");
    QSettings settings;
    if(printer.setup(this))
    {
     QPainter p(&printer);
     QRect rect=p.viewport();
     xrate=static_cast<float>(rect.width())/840.0;
     yrate=static_cast<float>(rect.height())/1188.0;
    QString qstringTemp = settings.readEnUTF8y ("logo");
    if (qstringTemp != "")
    {
    QPixmap pix2(static_cast<int>(200.0*xrate),static_cast<int>(100.0*yrate));
    QPainter p1;
    p1.begin(&pix2);
    QPixmap qpixm(qstringTemp);
    p1.setWindow(0,0,qpixm.width(),qpixm.height());
    p1.setViewport(0,0,static_cast<int>(200.0*xrate),static_cast<int>(100.0*yrate));
    p1.drawPixmap(0,0,qpixm);
    p1.end();
    p.drawPixmap(static_cast<int>((10.0+pageMargLeft)*xrate),static_cast<int>((5.0+pageMargTop)*yrate),pix2);
    }
    else
    {
	p.drawText(static_cast<int>((10.0+pageMargLeft)*xrate),static_cast<int>((10.0+pageMargTop)*yrate),UTF8("Piecz�� wystawcy"));
    }

    p.setFont(QFont("Times",static_cast<int>(22.0*yrate)));
    p.drawText(static_cast<int>((300.0+pageMargLeft)*xrate),static_cast<int>((50.0+pageMargTop)*yrate),tabletemp.data.Title);
    p.setFont(QFont("Times",static_cast<int>(18.0*yrate)));
    p.drawText(static_cast<int>((300.0+pageMargLeft)*xrate),static_cast<int>((80.0+pageMargTop)*yrate),tabletemp.data.Number);
    p.setFont(QFont("Times",static_cast<int>(12.0*yrate)));
    p.drawText(static_cast<int>((300.0+pageMargLeft)*xrate),static_cast<int>((100.0+pageMargTop)*yrate),tabletemp.data.sellingDate);
    p.drawText(static_cast<int>((300.0+pageMargLeft)*xrate),static_cast<int>((120.0+pageMargTop)*yrate),tabletemp.data.creatingDate);
    p.setFont(QFont("Times",static_cast<int>(22*yrate)));
    p.drawText(static_cast<int>((330.0+pageMargLeft)*xrate),static_cast<int>((160+pageMargTop)*yrate),UTF8("ORYGINA�/KOPIA"));
    p.setFont(QFont("Times",static_cast<int>(18*yrate)));
    p.drawLine(static_cast<int>((pageMargLeft)*xrate),static_cast<int>((200.0+pageMargTop)*yrate),rect.width()-static_cast<int>(pageMargRight*xrate),static_cast<int>((200.0+pageMargTop)*yrate));

    p.drawText(static_cast<int>((10.0+pageMargLeft)*xrate),static_cast<int>((250.0+pageMargTop)*yrate),UTF8("Sprzedawca:"));
    p.drawText(static_cast<int>((430.0+pageMargLeft)*xrate),static_cast<int>((250.0+pageMargTop)*yrate),UTF8("Nabywca:"));
    p.setFont(QFont("Times",static_cast<int>(10.0*yrate)));

    float temp_f=0.0;
    int temp_i1=0,temp_i2=0;

    if(settings.readBoolEnUTF8y("elinux/printpos/usernazwa") && settings.readEnUTF8y("elinux/user/nazwa").remove(" ")!="")
    {
	p.drawText(static_cast<int>((20.0+pageMargLeft)*xrate),static_cast<int>((270.0+pageMargTop+temp_f)*yrate),settings.readEnUTF8y ("elinux/user/nazwa"));
	temp_f+=20.0;
	++temp_i1;
    }
        if(settings.readBoolEnUTF8y("elinux/printpos/usermiejscowosc") && settings.readEnUTF8y("elinux/user/miejscowosc").remove(" ")!="")
    {
	    p.drawText(static_cast<int>((20.0+pageMargLeft)*xrate),static_cast<int>((270.0+pageMargTop+temp_f)*yrate),settings.readEnUTF8y ("elinux/user/miejscowosc"));
	temp_f+=20.0;
	++temp_i1;
    }
        if(settings.readBoolEnUTF8y("elinux/printpos/useradres") && settings.readEnUTF8y("elinux/user/adres").remove(" ")!="")
    {
	     p.drawText(static_cast<int>((20.0+pageMargLeft)*xrate),static_cast<int>((270.0+pageMargTop+temp_f)*yrate),settings.readEnUTF8y ("elinux/user/adres"));
	    temp_f+=20.0;
	    ++temp_i1;
    }
	if(settings.readBoolEnUTF8y("elinux/printpos/usernip") && settings.readEnUTF8y("elinux/user/nip").remove(" ").remove("-")!="")
    {
	     p.drawText(static_cast<int>((20.0+pageMargLeft)*xrate),static_cast<int>((270.0+pageMargTop+temp_f)*yrate),settings.readEnUTF8y ("elinux/user/nip"));
	    temp_f+=20.0;
  	    ++temp_i1;
    }
        if(settings.readBoolEnUTF8y("elinux/printpos/userkonto") && settings.readEnUTF8y("elinux/user/konto").remove(" ").remove("-")!="")
    {
	     p.drawText(static_cast<int>((20.0+pageMargLeft)*xrate),static_cast<int>((270.0+pageMargTop+temp_f)*yrate),settings.readEnUTF8y ("elinux/user/konto"));
	    temp_f+=20.0;
  	    ++temp_i1;
    }
        if(settings.readBoolEnUTF8y("elinux/printpos/userphone") && settings.readEnUTF8y("elinux/user/phone").remove(" ")!="")
    {
	     p.drawText(static_cast<int>((20.0+pageMargLeft)*xrate),static_cast<int>((270.0+pageMargTop+temp_f)*yrate),settings.readEnUTF8y ("elinux/user/phone"));
	    temp_f+=20.0;
	    ++temp_i1;
    }
        if(settings.readBoolEnUTF8y("elinux/printpos/usermail") && settings.readEnUTF8y("elinux/user/email").remove(" ")!="")
    {
	     p.drawText(static_cast<int>((20.0+pageMargLeft)*xrate),static_cast<int>((270.0+pageMargTop+temp_f)*yrate),settings.readEnUTF8y ("elinux/user/email"));
	    temp_f+=20.0;
	    ++temp_i1;
    }
        if(settings.readBoolEnUTF8y("elinux/printpos/userwww") && settings.readEnUTF8y("elinux/user/www").remove(" ")!="")
    {
	     p.drawText(static_cast<int>((20.0+pageMargLeft)*xrate),static_cast<int>((270.0+pageMargTop+temp_f)*yrate),settings.readEnUTF8y ("elinux/user/www"));
	    temp_f+=20.0;
	    ++temp_i1;
    }
temp_f=0.0;
    settings.beginGroup ("elinux/printpos");
    QStringList qstringlist=QStringList::split(",",tabletemp.data.client);

    if(qstringlist.size()==8)
    {
	QString temporary="  "+qstringlist[0];
	if( settings.readBoolEnUTF8y("clientnazwa") && qstringlist[0].remove(" ")!="")
	{
	    p.drawText(static_cast<int>((440.0+pageMargLeft)*xrate),static_cast<int>((270.0+temp_f+pageMargTop)*yrate),temporary);
	    temp_f+=20.0;
	    ++temp_i2;
	}
	temporary=qstringlist[1];
	if( settings.readBoolEnUTF8y("clientmiejscowosc") && qstringlist[1].remove(" ")!="")
	{
	    p.drawText(static_cast<int>((440.0+pageMargLeft)*xrate),static_cast<int>((270.0+temp_f+pageMargTop)*yrate),temporary);
	    temp_f+=20.0;
	    ++temp_i2;
	}
	temporary=qstringlist[2];
	if(settings.readBoolEnUTF8y("clientadres") && qstringlist[2].remove(" ")!="")
	{
	    p.drawText(static_cast<int>((440.0+pageMargLeft)*xrate),static_cast<int>((270.0+temp_f+pageMargTop)*yrate),temporary);
	    temp_f+=20.0;
	    ++temp_i2;
	}
	temporary=qstringlist[3];
	if(settings.readBoolEnUTF8y("clientnip") &&  qstringlist[3].remove(" ").remove("-")!="")
	{
	    p.drawText(static_cast<int>((440.0+pageMargLeft)*xrate),static_cast<int>((270.0+temp_f+pageMargTop)*yrate),UTF8("  NIP:")+temporary);
	    temp_f+=20.0;
	    ++temp_i2;
	}
	temporary=qstringlist[4];
	if( settings.readBoolEnUTF8y("clientkonto") && qstringlist[4].remove(" ").remove("-")!="")
	{
	    p.drawText(static_cast<int>((440.0+pageMargLeft)*xrate),static_cast<int>((270.0+temp_f+pageMargTop)*yrate),UTF8("  Konto:")+temporary);
	    temp_f+=20.0;
	    ++temp_i2;
	}
	temporary=qstringlist[5];
	if( settings.readBoolEnUTF8y("clientphone") && qstringlist[5].remove(" ")!="")
	{
	    p.drawText(static_cast<int>((440.0+pageMargLeft)*xrate),static_cast<int>((270.0+temp_f+pageMargTop)*yrate),UTF8("  Tel.:")+temporary);
	    temp_f+=20.0;
	    ++temp_i2;
	}
	temporary=qstringlist[6];
	if( settings.readBoolEnUTF8y("clientmail") && qstringlist[6].remove(" ")!="")
	{
	    p.drawText(static_cast<int>((440.0+pageMargLeft)*xrate),static_cast<int>((270.0+temp_f+pageMargTop)*yrate),UTF8("  E-mail:")+temporary);
	    temp_f+=20.0;
	    ++temp_i2;
	}
	temporary=qstringlist[7];
	if( settings.readBoolEnUTF8y("clientwww") && qstringlist[7].remove(" ")!="")
	{
	    p.drawText(static_cast<int>((440.0+pageMargLeft)*xrate),static_cast<int>((270.0+temp_f+pageMargTop)*yrate),UTF8("  www:")+temporary);
	    temp_f+=20.0;
	    ++temp_i2;
	}
     }
    else
    {
	qDebug("Z�a ilosc danych dla klienta!!! ");
    }
	settings.endGroup ();
	countPos= ( temp_i1>temp_i2 ? temp_i1 : temp_i2);
        p.drawLine(static_cast<int>((pageMargLeft)*xrate),static_cast<int>((290.0+static_cast<float>(countPos*20)+pageMargTop)*yrate),rect.width()-static_cast<int>(pageMargRight*xrate),static_cast<int>((290.0+static_cast<float>(countPos*20)+pageMargTop)*yrate));







    float temp_i=0.0;

    float temp_i_height=330.0+static_cast<float>(countPos*20);
    int temp_i_page=0;
    temp_i=315.0+static_cast<float>(countPos*20);


    // body

    p.setFont(QFont("Times",static_cast<int>(8.0*yrate)));
    p.drawLine(static_cast<int>((static_cast<double>(leftColumns[0]))*xrate),static_cast<int>((temp_i+pageMargTop)*yrate),static_cast<int>(static_cast<double>(leftColumns[14])*xrate),static_cast<int>((temp_i+pageMargTop)*yrate));
    if(visibleColumns[0]&&sizeColumns[0]!=0)
	p.drawText(static_cast<int>((static_cast<double>(leftColumns[0])+1)*xrate),static_cast<int>((temp_i_height+pageMargTop)*yrate),UTF8("Lp."));
    if(visibleColumns[1]&&sizeColumns[1]!=0)
	p.drawText(static_cast<int>((static_cast<double>(leftColumns[1])+1)*xrate),static_cast<int>((temp_i_height+pageMargTop)*yrate),UTF8("Nazwa"));
    if(visibleColumns[2]&&sizeColumns[2]!=0)
	p.drawText(static_cast<int>((static_cast<double>(leftColumns[2])+1)*xrate),static_cast<int>((temp_i_height+pageMargTop)*yrate),UTF8("Kod"));
    if(visibleColumns[3]&&sizeColumns[3]!=0)
	p.drawText(static_cast<int>((static_cast<double>(leftColumns[3])+1)*xrate),static_cast<int>((temp_i_height+pageMargTop)*yrate),UTF8("PKWiU"));
    if(visibleColumns[4]&&sizeColumns[4]!=0)
	p.drawText(static_cast<int>((static_cast<double>(leftColumns[4])+1)*xrate),static_cast<int>((temp_i_height+pageMargTop)*yrate),UTF8("Ilo��"));
    if(visibleColumns[5]&&sizeColumns[5]!=0)
	p.drawText(static_cast<int>((static_cast<double>(leftColumns[5]+1))*xrate),static_cast<int>((temp_i_height+pageMargTop)*yrate),UTF8("Jm."));
    if(visibleColumns[6]&&sizeColumns[6]!=0)
	p.drawText(static_cast<int>((static_cast<double>(leftColumns[6])+1)*xrate),static_cast<int>((temp_i_height+pageMargTop)*yrate),UTF8("Cena jdn."));
    if(visibleColumns[7]&&sizeColumns[7]!=0)
    {
	p.drawText(static_cast<int>((static_cast<double>(leftColumns[7])+1)*xrate),static_cast<int>((temp_i_height+pageMargTop+20.0)*yrate),UTF8("Warto��"));
	p.drawText(static_cast<int>((static_cast<double>(leftColumns[7])+1)*xrate),static_cast<int>((temp_i_height+pageMargTop)*yrate),UTF8("  Netto"));
    }
    if(visibleColumns[8]&&sizeColumns[8]!=0)
    {
	p.drawText(static_cast<int>((static_cast<double>(leftColumns[8])+1)*xrate),static_cast<int>((temp_i_height+pageMargTop)*yrate),UTF8("Rabat"));
	p.drawText(static_cast<int>((static_cast<double>(leftColumns[8])+1)*xrate),static_cast<int>((temp_i_height+pageMargTop+20.0)*yrate),UTF8(" [%]"));
    }
    if(visibleColumns[9]&&sizeColumns[9]!=0)
    {
	p.drawText(static_cast<int>((static_cast<double>(leftColumns[9])+1)*xrate),static_cast<int>((temp_i_height+pageMargTop)*yrate),UTF8(" Rabat"));
	p.drawText(static_cast<int>((static_cast<double>(leftColumns[9])+1)*xrate),static_cast<int>((temp_i_height+pageMargTop+20.0)*yrate),UTF8("Warto��"));
    }
    if(visibleColumns[10]&&sizeColumns[10]!=0)
    {
	p.drawText(static_cast<int>((static_cast<double>(leftColumns[10])+1)*xrate),static_cast<int>((temp_i_height+pageMargTop)*yrate),UTF8(" Netto"));
	p.drawText(static_cast<int>((static_cast<double>(leftColumns[10])+1)*xrate),static_cast<int>((temp_i_height+pageMargTop+20.0)*yrate),UTF8("po rabacie"));
    }
    if(visibleColumns[11]&&sizeColumns[11]!=0)
    {
	p.drawText(static_cast<int>((static_cast<double>(leftColumns[11])+1)*xrate),static_cast<int>((temp_i_height+pageMargTop)*yrate),UTF8("Stawka"));
                p.drawText(static_cast<int>((static_cast<double>(leftColumns[11])+1)*xrate),static_cast<int>((temp_i_height+pageMargTop+20.0)*yrate),UTF8("VAT[%]"));
    }
    if(visibleColumns[12]&&sizeColumns[12]!=0)
    {
	p.drawText(static_cast<int>((static_cast<double>(leftColumns[12])+1)*xrate),static_cast<int>((temp_i_height+pageMargTop)*yrate),UTF8("Kwota"));
	p.drawText(static_cast<int>((static_cast<double>(leftColumns[12])+1)*xrate),static_cast<int>((temp_i_height+pageMargTop+20.0)*yrate),UTF8(" VAT"));
    }
    if(visibleColumns[13]&&sizeColumns[13]!=0)
    {
	p.drawText(static_cast<int>((static_cast<double>(leftColumns[13])+1)*xrate),static_cast<int>((temp_i_height+pageMargTop)*yrate),UTF8("Warto��"));
                p.drawText(static_cast<int>((static_cast<double>(leftColumns[13])+1)*xrate),static_cast<int>((temp_i_height+pageMargTop+20.0)*yrate),UTF8(" brutto"));
    }

      temp_i_height+=50.0;
  for(unsigned int i=0;i<tabletemp.vec_temp.size();++i)
    {
      if(temp_i_height>(1158-static_cast<int>(pageMargDown)-static_cast<int>(pageMargTop)))
      {
          p.drawLine(static_cast<int>((static_cast<double>(leftColumns[0]))*xrate),static_cast<int>((temp_i+pageMargTop)*yrate),static_cast<int>((static_cast<double>(leftColumns[0])*xrate)),static_cast<int>((temp_i_height+pageMargTop-15.0)*yrate));
          p.drawLine(static_cast<int>((static_cast<double>(leftColumns[0]))*xrate),static_cast<int>((temp_i_height+pageMargTop-15.0)*yrate),static_cast<int>((static_cast<double>(leftColumns[14]))*xrate),static_cast<int>((temp_i_height+pageMargTop-15.0)*yrate));
    if(visibleColumns[1]&&sizeColumns[1]!=0)
	    p.drawLine(static_cast<int>((static_cast<double>(leftColumns[1]))*xrate),static_cast<int>((temp_i+pageMargTop)*yrate),static_cast<int>((static_cast<double>(leftColumns[1]))*xrate),static_cast<int>((temp_i_height+pageMargTop-15)*yrate));

    if(visibleColumns[2]&&sizeColumns[2]!=0)
	    p.drawLine(static_cast<int>((static_cast<double>(leftColumns[2]))*xrate),static_cast<int>((temp_i+pageMargTop)*yrate),static_cast<int>((static_cast<double>(leftColumns[2]))*xrate),static_cast<int>((temp_i_height+pageMargTop-15)*yrate));
;
    if(visibleColumns[3]&&sizeColumns[3]!=0)
	    p.drawLine(static_cast<int>((static_cast<double>(leftColumns[3]))*xrate),static_cast<int>((temp_i+pageMargTop)*yrate),static_cast<int>((static_cast<double>(leftColumns[3]))*xrate),static_cast<int>((temp_i_height+pageMargTop-15)*yrate));
;
    if(visibleColumns[4]&&sizeColumns[4]!=0)
	    p.drawLine(static_cast<int>((static_cast<double>(leftColumns[4]))*xrate),static_cast<int>((temp_i+pageMargTop)*yrate),static_cast<int>((static_cast<double>(leftColumns[4]))*xrate),static_cast<int>((temp_i_height+pageMargTop-15)*yrate));
;
    if(visibleColumns[5]&&sizeColumns[5]!=0)
	    p.drawLine(static_cast<int>((static_cast<double>(leftColumns[5]))*xrate),static_cast<int>((temp_i+pageMargTop)*yrate),static_cast<int>((static_cast<double>(leftColumns[5]))*xrate),static_cast<int>((temp_i_height+pageMargTop-15)*yrate));
;
    if(visibleColumns[6]&&sizeColumns[6]!=0)
	    p.drawLine(static_cast<int>((static_cast<double>(leftColumns[6]))*xrate),static_cast<int>((temp_i+pageMargTop)*yrate),static_cast<int>((static_cast<double>(leftColumns[6]))*xrate),static_cast<int>((temp_i_height+pageMargTop-15)*yrate));
;
    if(visibleColumns[7]&&sizeColumns[7]!=0)
	    p.drawLine(static_cast<int>((static_cast<double>(leftColumns[7]))*xrate),static_cast<int>((temp_i+pageMargTop)*yrate),static_cast<int>((static_cast<double>(leftColumns[7]))*xrate),static_cast<int>((temp_i_height+pageMargTop-15)*yrate));
;
    if(visibleColumns[8]&&sizeColumns[8]!=0)
	    p.drawLine(static_cast<int>((static_cast<double>(leftColumns[8]))*xrate),static_cast<int>((temp_i+pageMargTop)*yrate),static_cast<int>((static_cast<double>(leftColumns[8]))*xrate),static_cast<int>((temp_i_height+pageMargTop-15)*yrate));
;
    if(visibleColumns[9]&&sizeColumns[9]!=0)
	    p.drawLine(static_cast<int>((static_cast<double>(leftColumns[9]))*xrate),static_cast<int>((temp_i+pageMargTop)*yrate),static_cast<int>((static_cast<double>(leftColumns[9]))*xrate),static_cast<int>((temp_i_height+pageMargTop-15)*yrate));
;
    if(visibleColumns[10]&&sizeColumns[10]!=0)
	    p.drawLine(static_cast<int>((static_cast<double>(leftColumns[10]))*xrate),static_cast<int>((temp_i+pageMargTop)*yrate),static_cast<int>((static_cast<double>(leftColumns[10]))*xrate),static_cast<int>((temp_i_height+pageMargTop-15)*yrate));
;
    if(visibleColumns[11]&&sizeColumns[11]!=0)
	    p.drawLine(static_cast<int>((static_cast<double>(leftColumns[11]))*xrate),static_cast<int>((temp_i+pageMargTop)*yrate),static_cast<int>((static_cast<double>(leftColumns[11]))*xrate),static_cast<int>((temp_i_height+pageMargTop-15)*yrate));

    if(visibleColumns[12]&&sizeColumns[12]!=0)
	    p.drawLine(static_cast<int>((static_cast<double>(leftColumns[12]))*xrate),static_cast<int>((temp_i+pageMargTop)*yrate),static_cast<int>((static_cast<double>(leftColumns[12]))*xrate),static_cast<int>((temp_i_height+pageMargTop-15)*yrate));

    if(visibleColumns[13]&&sizeColumns[13]!=0)
	    p.drawLine(static_cast<int>((static_cast<double>(leftColumns[13]))*xrate),static_cast<int>((temp_i+pageMargTop)*yrate),static_cast<int>((static_cast<double>(leftColumns[13]))*xrate),static_cast<int>((temp_i_height+pageMargTop-15)*yrate));

    p.drawLine(static_cast<int>(static_cast<double>(leftColumns[14])*xrate),static_cast<int>((temp_i+pageMargTop)*yrate),static_cast<int>(static_cast<double>(leftColumns[14])*xrate),static_cast<int>((temp_i_height+pageMargTop-15.0)*yrate));

	temp_i=5.0;
	drawPrintSummary(p,temp_i_page);
	++temp_i_page;
	temp_i_height=20.0;
	printer.newPage();
      }
      p.drawLine(static_cast<int>((static_cast<double>(leftColumns[0]))*xrate),static_cast<int>((temp_i_height+pageMargTop-15.0)*yrate),static_cast<int>(static_cast<double>(leftColumns[14])*xrate),static_cast<int>((temp_i_height+pageMargTop-15.0)*yrate));

      int i_temp2=static_cast<int>((temp_i_height+pageMargTop)*yrate);
      if(visibleColumns[0]&&sizeColumns[0]!=0)
	  p.drawText(static_cast<int>(static_cast<double>(leftColumns[0])*xrate),i_temp2,tabletemp.vec_temp[i][0]);
      if(visibleColumns[1]&&sizeColumns[1]!=0)
	  p.drawText(static_cast<int>(static_cast<double>(leftColumns[1])*xrate),i_temp2,tabletemp.vec_temp[i][1]);
      if(visibleColumns[2]&&sizeColumns[2]!=0)
	  p.drawText(static_cast<int>(static_cast<double>(leftColumns[2])*xrate),i_temp2,tabletemp.vec_temp[i][2]);
      if(visibleColumns[3]&&sizeColumns[3]!=0)
	  p.drawText(static_cast<int>(static_cast<double>(leftColumns[3])*xrate),i_temp2,tabletemp.vec_temp[i][3]);
      if(visibleColumns[4]&&sizeColumns[4]!=0)
	  p.drawText(static_cast<int>(static_cast<double>(leftColumns[4])*xrate),i_temp2,tabletemp.vec_temp[i][4]);
      if(visibleColumns[5]&&sizeColumns[5]!=0)
	  p.drawText(static_cast<int>(static_cast<double>(leftColumns[5])*xrate),i_temp2,tabletemp.vec_temp[i][5]);
      if(visibleColumns[6]&&sizeColumns[6]!=0)
	  p.drawText(static_cast<int>(static_cast<double>(leftColumns[6])*xrate),i_temp2,tabletemp.vec_temp[i][6]);
      if(visibleColumns[7]&&sizeColumns[7]!=0)
	  p.drawText(static_cast<int>(static_cast<double>(leftColumns[7])*xrate),i_temp2,tabletemp.vec_temp[i][7]);
      if(visibleColumns[8]&&sizeColumns[8]!=0)
	  p.drawText(static_cast<int>(static_cast<double>(leftColumns[8])*xrate),i_temp2,tabletemp.vec_temp[i][8]);
      if(visibleColumns[9]&&sizeColumns[9]!=0)
	  p.drawText(static_cast<int>(static_cast<double>(leftColumns[9])*xrate),i_temp2,tabletemp.vec_temp[i][9]);
      if(visibleColumns[10]&&sizeColumns[10]!=0)
	  p.drawText(static_cast<int>(static_cast<double>(leftColumns[10])*xrate),i_temp2,tabletemp.vec_temp[i][10]);
      if(visibleColumns[11]&&sizeColumns[11]!=0)
	  p.drawText(static_cast<int>(static_cast<double>(leftColumns[11])*xrate),i_temp2,tabletemp.vec_temp[i][11]);
      if(visibleColumns[12]&&sizeColumns[12]!=0)
	  p.drawText(static_cast<int>(static_cast<double>(leftColumns[12])*xrate),i_temp2,tabletemp.vec_temp[i][12]);
      if(visibleColumns[13]&&sizeColumns[13]!=0)
	  p.drawText(static_cast<int>(static_cast<double>(leftColumns[13])*xrate),i_temp2,tabletemp.vec_temp[i][13]);
      temp_i_height+=20.0;
    }


          p.drawLine(static_cast<int>((static_cast<double>(leftColumns[0]))*xrate),static_cast<int>((temp_i+pageMargTop)*yrate),static_cast<int>(static_cast<double>(leftColumns[0])*xrate),static_cast<int>((temp_i_height+pageMargTop-15.0)*yrate));

    if(visibleColumns[1]&&sizeColumns[1]!=0)
	    p.drawLine(static_cast<int>((static_cast<double>(leftColumns[1]))*xrate),static_cast<int>((temp_i+pageMargTop)*yrate),static_cast<int>((static_cast<double>(leftColumns[1]))*xrate),static_cast<int>((temp_i_height+pageMargTop-15)*yrate));

    if(visibleColumns[2]&&sizeColumns[2]!=0)
	    p.drawLine(static_cast<int>((static_cast<double>(leftColumns[2]))*xrate),static_cast<int>((temp_i+pageMargTop)*yrate),static_cast<int>((static_cast<double>(leftColumns[2]))*xrate),static_cast<int>((temp_i_height+pageMargTop-15)*yrate));
;
    if(visibleColumns[3]&&sizeColumns[3]!=0)
	    p.drawLine(static_cast<int>((static_cast<double>(leftColumns[3]))*xrate),static_cast<int>((temp_i+pageMargTop)*yrate),static_cast<int>((static_cast<double>(leftColumns[3]))*xrate),static_cast<int>((temp_i_height+pageMargTop-15)*yrate));
;
    if(visibleColumns[4]&&sizeColumns[4]!=0)
	    p.drawLine(static_cast<int>((static_cast<double>(leftColumns[4]))*xrate),static_cast<int>((temp_i+pageMargTop)*yrate),static_cast<int>((static_cast<double>(leftColumns[4]))*xrate),static_cast<int>((temp_i_height+pageMargTop-15)*yrate));
;
    if(visibleColumns[5]&&sizeColumns[5]!=0)
	    p.drawLine(static_cast<int>((static_cast<double>(leftColumns[5]))*xrate),static_cast<int>((temp_i+pageMargTop)*yrate),static_cast<int>((static_cast<double>(leftColumns[5]))*xrate),static_cast<int>((temp_i_height+pageMargTop-15)*yrate));
;
    if(visibleColumns[6]&&sizeColumns[6]!=0)
	    p.drawLine(static_cast<int>((static_cast<double>(leftColumns[6]))*xrate),static_cast<int>((temp_i+pageMargTop)*yrate),static_cast<int>((static_cast<double>(leftColumns[6]))*xrate),static_cast<int>((temp_i_height+pageMargTop-15)*yrate));
;
    if(visibleColumns[7]&&sizeColumns[7]!=0)
	    p.drawLine(static_cast<int>((static_cast<double>(leftColumns[7]))*xrate),static_cast<int>((temp_i+pageMargTop)*yrate),static_cast<int>((static_cast<double>(leftColumns[7]))*xrate),static_cast<int>((temp_i_height+pageMargTop-15)*yrate));
;
    if(visibleColumns[8]&&sizeColumns[8]!=0)
	    p.drawLine(static_cast<int>((static_cast<double>(leftColumns[8]))*xrate),static_cast<int>((temp_i+pageMargTop)*yrate),static_cast<int>((static_cast<double>(leftColumns[8]))*xrate),static_cast<int>((temp_i_height+pageMargTop-15)*yrate));
;
    if(visibleColumns[9]&&sizeColumns[9]!=0)
	    p.drawLine(static_cast<int>((static_cast<double>(leftColumns[9]))*xrate),static_cast<int>((temp_i+pageMargTop)*yrate),static_cast<int>((static_cast<double>(leftColumns[9]))*xrate),static_cast<int>((temp_i_height+pageMargTop-15)*yrate));
;
    if(visibleColumns[10]&&sizeColumns[10]!=0)
	    p.drawLine(static_cast<int>((static_cast<double>(leftColumns[10]))*xrate),static_cast<int>((temp_i+pageMargTop)*yrate),static_cast<int>((static_cast<double>(leftColumns[10]))*xrate),static_cast<int>((temp_i_height+pageMargTop-15)*yrate));
;
    if(visibleColumns[11]&&sizeColumns[11]!=0)
	    p.drawLine(static_cast<int>((static_cast<double>(leftColumns[11]))*xrate),static_cast<int>((temp_i+pageMargTop)*yrate),static_cast<int>((static_cast<double>(leftColumns[11]))*xrate),static_cast<int>((temp_i_height+pageMargTop-15)*yrate));

    if(visibleColumns[12]&&sizeColumns[12]!=0)
	    p.drawLine(static_cast<int>((static_cast<double>(leftColumns[12]))*xrate),static_cast<int>((temp_i+pageMargTop)*yrate),static_cast<int>((static_cast<double>(leftColumns[12]))*xrate),static_cast<int>((temp_i_height+pageMargTop-15)*yrate));

    if(visibleColumns[13]&&sizeColumns[13]!=0)
	    p.drawLine(static_cast<int>((static_cast<double>(leftColumns[13]))*xrate),static_cast<int>((temp_i+pageMargTop)*yrate),static_cast<int>((static_cast<double>(leftColumns[13]))*xrate),static_cast<int>((temp_i_height+pageMargTop-15)*yrate));

    p.drawLine(static_cast<int>(static_cast<double>(leftColumns[14])*xrate),static_cast<int>((temp_i+pageMargTop)*yrate),static_cast<int>(static_cast<double>(leftColumns[14])*xrate),static_cast<int>((temp_i_height+pageMargTop-15.0)*yrate));

    p.drawLine(static_cast<int>((static_cast<double>(leftColumns[0]))*xrate),static_cast<int>((temp_i_height+pageMargTop-15.0)*yrate),static_cast<int>((static_cast<double>(leftColumns[14]))*xrate),static_cast<int>((temp_i_height+pageMargTop-15.0)*yrate));




      if(temp_i_height>(1058-margDown-margTop))
      {
	drawPrintSummary(p,temp_i_page);
	++temp_i_page;
	temp_i_height=20.0;
	printer.newPage();
      }

                temp_i_height+=30.0;
                p.drawText(static_cast<int>((510.0+pageMargLeft)*xrate),static_cast<int>((temp_i_height+pageMargTop-25.0)*yrate),UTF8("Razem:"));
	p.drawText(static_cast<int>((550.0+pageMargLeft)*xrate),static_cast<int>((temp_i_height+pageMargTop-25.0)*yrate),UTF8("Warto��"));
	p.drawText(static_cast<int>((550.0+pageMargLeft)*xrate),static_cast<int>((temp_i_height+pageMargTop-12.0)*yrate),UTF8("Netto"));
	p.drawText(static_cast<int>((600.0+pageMargLeft)*xrate),static_cast<int>((temp_i_height+pageMargTop-25.0)*yrate),UTF8("Kwota"));
	p.drawText(static_cast<int>((600.0+pageMargLeft)*xrate),static_cast<int>((temp_i_height+pageMargTop-12.0)*yrate),UTF8("VAT"));
	p.drawText(static_cast<int>((655.0+pageMargLeft)*xrate),static_cast<int>((temp_i_height+pageMargTop-25.0)*yrate),UTF8("Warto��"));
	p.drawText(static_cast<int>((655.0+pageMargLeft)*xrate),static_cast<int>((temp_i_height+pageMargTop-12.0)*yrate),UTF8("Brutto"));

      p.drawText(static_cast<int>((550.0+pageMargLeft)*xrate),static_cast<int>((temp_i_height+pageMargTop)*yrate),tabletemp.data.netto);
      p.drawText(static_cast<int>((600.0+pageMargLeft)*xrate),static_cast<int>((temp_i_height+pageMargTop)*yrate),tabletemp.data.vat);
      p.drawText(static_cast<int>((655.0+pageMargLeft)*xrate),static_cast<int>((temp_i_height+pageMargTop)*yrate),tabletemp.data.brutto);
      temp_i_height+=50.0;

      if((temp_i_height+120)>(1058-margDown-margTop))
      {
	drawPrintSummary(p,temp_i_page);
	++temp_i_page;
	temp_i_height=20.0;
	printer.newPage();
    }
      p.setFont(QFont("Times",static_cast<int>(14.0*yrate),75));
      p.drawText(static_cast<int>((20.0+pageMargLeft)*xrate),static_cast<int>((temp_i_height+pageMargTop)*yrate),UTF8("Do zap�aty: ")+tabletemp.data.sum);
      p.setFont(QFont("Times",static_cast<int>(8.0*yrate),50));
      p.drawText(static_cast<int>((20.0+pageMargLeft)*xrate),static_cast<int>((temp_i_height+pageMargTop+20.0)*yrate),UTF8("Kwota s�ownie: ")+tabletemp.data.sumSUTF8);
      p.drawText(static_cast<int>((20.0+pageMargLeft)*xrate),static_cast<int>((temp_i_height+pageMargTop+40.0)*yrate),UTF8("Forma p�atno�ci: ")+tabletemp.data.payMode);
      p.drawText(static_cast<int>((20.0+pageMargLeft)*xrate),static_cast<int>((temp_i_height+pageMargTop+60)*yrate),UTF8("Termin p�atno�ci: ")+tabletemp.data.payDate);
      if(tabletemp.data.paidCash==true)
      {
         p.drawText(static_cast<int>((20.0+pageMargLeft)*xrate),static_cast<int>((temp_i_height+pageMargTop+80)*yrate),UTF8("Zap�acono got�wk�"));
      }
      else
      {
        p.drawText(static_cast<int>((20.0+pageMargLeft)*xrate),static_cast<int>((temp_i_height+pageMargTop+80)*yrate),UTF8("Zap�ata przelewem"));
      }
      p.setFont(QFont("Times",static_cast<int>(14.0*yrate),75));
      p.drawText(static_cast<int>((20.0+pageMargLeft)*xrate),static_cast<int>((temp_i_height+pageMargTop+100)*yrate),tabletemp.data.additText);

      p.drawText(static_cast<int>((380.0+pageMargLeft)*xrate),static_cast<int>((temp_i_height+pageMargTop-20)*yrate),UTF8("Og�lnie stawkami"));
      p.setFont(QFont("Times",static_cast<int>(8.0*yrate),50));

      p.drawText(static_cast<int>((400.0+pageMargLeft)*xrate),static_cast<int>((temp_i_height+pageMargTop)*yrate),UTF8("Netto"));
      p.drawText(static_cast<int>((450.0+pageMargLeft)*xrate),static_cast<int>((temp_i_height+pageMargTop)*yrate),UTF8("Stawka"));
      p.drawText(static_cast<int>((500.0+pageMargLeft)*xrate),static_cast<int>((temp_i_height+pageMargTop)*yrate),UTF8("Podatek"));
      p.drawText(static_cast<int>((550.0+pageMargLeft)*xrate),static_cast<int>((temp_i_height+pageMargTop)*yrate),UTF8("Brutto"));
      QStringList bidsList=QStringList::split(";",tabletemp.data.Bids);
      temp_i_height+=20.0;
      QStringList::Iterator it = bidsList.begin();
      for(int i=0;i<4;++i)
	  for(int j=0;j<4;++j)
	  {
	      p.drawText(static_cast<int>((400.0+pageMargLeft+static_cast<float>(j)*50.0)*xrate),static_cast<int>((temp_i_height+pageMargTop+static_cast<float>(i)*20)*yrate),*it);
	      ++it;
	  }
      temp_i_height+=130.0;

      if((temp_i_height+100)>(1058-margDown-margTop))
      {
	drawPrintSummary(p,temp_i_page);
	++temp_i_page;
	temp_i_height=20.0;
	printer.newPage();
      }
      temp_i_height+=50.0;
      p.drawLine(static_cast<int>((pageMargLeft+50.0)*xrate),static_cast<int>((temp_i_height+pageMargTop)*yrate),static_cast<int>((pageMargLeft+300.0)*xrate),static_cast<int>((temp_i_height+pageMargTop)*yrate));

      p.drawLine(static_cast<int>((pageMargLeft+400.0)*xrate),static_cast<int>((temp_i_height+pageMargTop)*yrate),static_cast<int>((pageMargLeft+650.0)*xrate),static_cast<int>((temp_i_height+pageMargTop)*yrate));
      p.setFont(QFont("Times",static_cast<int>(6.0*yrate),50));

#ifdef QF_base__
      //qDebug("aaa");
      p.drawText(static_cast<int>((pageMargLeft+80.0)*xrate),static_cast<int>((temp_i_height+pageMargTop+10.0)*yrate),UTF8("Imi� i nazwisko osoby upowa�nionej do wystawienia faktury VAT"));
      p.drawText(static_cast<int>((pageMargLeft+440.0)*xrate),static_cast<int>((temp_i_height+pageMargTop+10.0)*yrate),UTF8("Imi� i nazwisko osoby upowa�nionej do odbioru faktury VAT"));
#endif

#ifdef QF_vatmp__
      p.drawText(static_cast<int>((pageMargLeft+80.0)*xrate),static_cast<int>((temp_i_height+pageMargTop+10.0)*yrate),UTF8("Imi� i nazwisko osoby upowa�nionej do wystawienia faktury VAT"));
      p.drawText(static_cast<int>((pageMargLeft+440.0)*xrate),static_cast<int>((temp_i_height+pageMargTop+10.0)*yrate),UTF8("Imi� i nazwisko osoby upowa�nionej do odbioru faktury VAT"));

#endif

#ifdef QF_noVAT__
      p.drawText(static_cast<int>((pageMargLeft+80.0)*xrate),static_cast<int>((temp_i_height+pageMargTop+10.0)*yrate),UTF8("Imi� i nazwisko osoby upowa�nionej do wystawienia rachunku"));
      p.drawText(static_cast<int>((pageMargLeft+440.0)*xrate),static_cast<int>((temp_i_height+pageMargTop+10.0)*yrate),UTF8("Imi� i nazwisko osoby upowa�nionej do odbioru rachunku"));
#endif
  drawPrintSummary(p,temp_i_page);
  p.end();
   }
   */
}

void Podglad::setTableTemp( TableTemp & t,QString progdir2,QString reUTF8n )
{
	tabletemp=t;
 makePixmap();
 this->setWindowTitle(tabletemp.data.title);

 progDir2=progdir2;
 ret=reUTF8n;
 if(tabletemp.data.paidCash==false)
     pushButton6->setEnabled(true);
  label->setPixmap(pixmap[0]);

  pixmap[0].save("/tmp/a");
}

void Podglad::makePixmap() {
	setVisibleColumn();
	if (makePdf) {
		if (pixmap_pdf.size() == 0) {
			pixmap_pdf.push_back(QPixmap(840 * scale, 1188 * scale));
			pixmap_pdf[0].fill();
			QPainter p(&pixmap_pdf[0]);
			drawHeader(p);
			p.end();
			drawBody();
			drawPageSummary();
		}
	} else {
		pixmap.push_back(QPixmap(840, 1188));
		pixmap[0].fill();
		QPainter p(&pixmap[0]);
		// p.begin(pixmap[0]);
		drawHeader(p);
		p.end();
		drawBody();
		drawPageSummary();
		pagespinbox->setMaximum(pixmap.size());
	}
}


void Podglad::drawHeader(QPainter &p) {
	Settings settings;
	QString qstringTemp = settings.value("logo", "").toString();
	if (!qstringTemp.isEmpty() && !qstringTemp.isNull() && qstringTemp != "") {
		QPixmap qpixm(qstringTemp);
		QRect rect((10 + margLeft) * scale, (10 + margTop) * scale, 200
				* scale, 100 * scale);
		p.drawPixmap(rect, qpixm);
	} else {
		p.drawText((10 + margLeft) * scale, (10 + margTop) * scale, UTF8(
				"Pieczęć wystawcy"));
	}

	p.setFont(QFont("Times", 22 * scale));
	p.drawText((300 + margLeft) * scale, (50 + margTop) * scale,
			tabletemp.data.title);
	p.setFont(QFont("Times", 18 * scale));
	p.drawText((300 + margLeft) * scale, (80 + margTop) * scale,
			tabletemp.data.number);
	p.setFont(QFont("Times", 12 * scale));
	p.drawText((300 + margLeft) * scale, (100 + margTop) * scale,
			tabletemp.data.sellingDate);
	p.drawText((300 + margLeft) * scale, (120 + margTop) * scale,
			tabletemp.data.creatingDate);
	p.setFont(QFont("Times", 22 * scale));
	p.drawText((330 + margLeft) * scale, (160 + margTop) * scale, UTF8(
			"ORYGINA�/KOPIA"));
	p.setFont(QFont("Times", 18 * scale));
	p.drawLine((margLeft) * scale, (200 + margTop) * scale, (pixmap[0].width()
			- margRight) * scale, (200 + margTop) * scale);

	p.drawText((10 + margLeft) * scale, (250 + margTop) * scale, UTF8(
			"Sprzedawca:"));
	p.drawText((430 + margLeft) * scale, (250 + margTop) * scale,
			UTF8("Nabywca:"));
	p.setFont(QFont("Times", 10 * scale));

	int temp_i = 0, temp_i1 = 0, temp_i2 = 0;

	if (settings.value("elinux/printpos/usernazwa").toBool() && settings.value(
			"elinux/user/nazwa").toString().remove(" ") != "") {
		p.drawText((20 + margLeft) * scale, (270 + margTop + temp_i) * scale,
				settings.value("elinux/user/nazwa").toString());
		temp_i += 20;
		++temp_i1;
	}
	if (settings.value("elinux/printpos/usermiejscowosc").toBool()
			&& settings.value("elinux/user/miejscowosc").toString().remove(" ")
					!= "") {
		p.drawText((20 + margLeft) * scale, (270 + margTop + temp_i) * scale,
				settings.value("elinux/user/kod").toString() + " "
						+ settings.value("elinux/user/miejscowosc").toString());
		temp_i += 20;
		++temp_i1;
	}
	if (settings.value("elinux/printpos/useradres").toBool() && settings.value(
			"elinux/user/adres").toString().remove(" ") != "") {
		p.drawText((20 + margLeft) * scale, (270 + margTop + temp_i) * scale,
				settings.value("elinux/user/adres").toString());
		temp_i += 20;
		++temp_i1;
	}
	if (settings.value("elinux/printpos/usernip").toBool() && settings.value(
			"elinux/user/nip").toString().remove(" ").remove("-") != "") {
		p.drawText((20 + margLeft) * scale, (270 + margTop + temp_i) * scale,
				UTF8("NIP: ") + settings.value("elinux/user/nip").toString());
		temp_i += 20;
		++temp_i1;
	}
	if (settings.value("elinux/printpos/userkonto").toBool() && settings.value(
			"elinux/user/konto").toString().remove(" ").remove("-") != "") {
		p.drawText((20 + margLeft) * scale, (270 + margTop + temp_i) * scale,
				UTF8("Nr konta: ")
						+ settings.value("elinux/user/konto").toString());
		temp_i += 20;
		++temp_i1;
	}
	if (settings.value("elinux/printpos/userphone").toBool() && settings.value(
			"elinux/user/phone").toString().remove(" ") != "") {
		p.drawText((20 + margLeft) * scale, (270 + margTop + temp_i) * scale,
				UTF8("Telefon: ")
						+ settings.value("elinux/user/phone").toString());
		temp_i += 20;
		++temp_i1;
	}
	if (settings.value("elinux/printpos/usermail").toBool() && settings.value(
			"elinux/user/email").toString().remove(" ") != "") {
		p.drawText((20 + margLeft) * scale, (270 + margTop + temp_i) * scale,
				UTF8("E-mail: ") + settings.value("elinux/user/email").toString());
		temp_i += 20;
		++temp_i1;
	}
	if (settings.value("elinux/printpos/userwww").toBool() && settings.value(
			"elinux/user/www").toString().remove(" ") != "") {
		p.drawText((20 + margLeft) * scale, (270 + margTop + temp_i) * scale,
				UTF8("WWW: ") + settings.value("elinux/user/www").toString());
		temp_i += 20;
		++temp_i1;
	}
	temp_i = 0;
	settings.beginGroup("elinux/printpos");
	QStringList qstringlist = tabletemp.data.client.split(",");

	if (qstringlist.size() == 8) {
		QString temporary = "  " + qstringlist[0];
		if (settings.value("clientnazwa").toBool()
				&& qstringlist[0].remove(" ") != "") {
			p.drawText((440 + margLeft) * scale, (270 + temp_i + margTop)
					* scale, temporary);
			temp_i += 20;
			++temp_i2;
		}
		temporary = qstringlist[1];
		if (settings.value("clientmiejscowosc").toBool()
				&& qstringlist[1].remove(" ") != "") {
			p.drawText((440 + margLeft) * scale, (270 + temp_i + margTop)
					* scale, temporary);
			temp_i += 20;
			++temp_i2;
		}
		temporary = qstringlist[2];
		if (settings.value("clientadres").toBool()
				&& qstringlist[2].remove(" ") != "") {
			p.drawText((440 + margLeft) * scale, (270 + temp_i + margTop)
					* scale, temporary);
			temp_i += 20;
			++temp_i2;
		}
		temporary = qstringlist[3];
		if (settings.value("clientnip").toBool()
				&& qstringlist[3].remove(" ").remove("-") != "") {
			p.drawText((440 + margLeft) * scale, (270 + temp_i + margTop)
					* scale, UTF8("  NIP: ") + temporary);
			temp_i += 20;
			++temp_i2;
		}
		temporary = qstringlist[4];
		if (settings.value("clientkonto").toBool()
				&& qstringlist[4].remove(" ").remove("-") != "") {
			p.drawText((440 + margLeft) * scale, (270 + temp_i + margTop)
					* scale, UTF8("  Nr konta: ") + temporary);
			temp_i += 20;
			++temp_i2;
		}
		temporary = qstringlist[5];
		if (settings.value("clientphone").toBool()
				&& qstringlist[5].remove(" ") != "") {
			p.drawText((440 + margLeft) * scale, (270 + temp_i + margTop)
					* scale, UTF8("  Telefon: ") + temporary);
			temp_i += 20;
			++temp_i2;
		}
		temporary = qstringlist[6];
		if (settings.value("clientmail").toBool() && qstringlist[6].remove(" ")
				!= "") {
			p.drawText((440 + margLeft) * scale, (270 + temp_i + margTop)
					* scale, UTF8("  E-mail: ") + temporary);
			temp_i += 20;
			++temp_i2;
		}
		temporary = qstringlist[7];
		if (settings.value("clientwww").toBool() && qstringlist[7].remove(" ")
				!= "") {
			p.drawText((440 + margLeft) * scale, (270 + temp_i + margTop)
					* scale, UTF8("  WWW: ") + temporary);
			temp_i += 20;
			++temp_i2;
		}
	} else {
		//	qDebug("Z�a ilo�� danych!!!: "+QString::number(qstringlist.size()));
		//	qDebug(tabletemp.data.client);
		//	for (QStringList::Iterator it = qstringlist.begin() ; it != qstringlist.end(); ++it)
		//	    qDebug(*it);
	}
	settings.endGroup();
	countPos = (temp_i1 > temp_i2 ? temp_i1 : temp_i2);
	p.drawLine(margLeft * scale, (290 + countPos * 20 + margTop) * scale,
			(pixmap[0].width() - margRight) * scale, (290 + countPos * 20
					+ margTop) * scale);
}



void Podglad::drawBody() {
	// qDebug("drawbody" + QString::number(tabletemp.vec_temp.size()));
	int temp_i_height = 330 + countPos * 20, temp_i_page = 0, temp_i = 315
			+ countPos * 20;

	QPainter p;
	if (makePdf)
		p.begin(&pixmap_pdf[0]);
	else
		p.begin(&pixmap[0]);

	p.setFont(QFont("Times", 8 * scale));
	p.drawLine(leftColumns[0] * scale, (temp_i_height + margTop - 15) * scale,
			leftColumns[14] * scale, (temp_i_height + margTop - 15) * scale);
	if (visibleColumns[0] && sizeColumns[0] != 0)
		p.drawText((leftColumns[0] + 1) * scale, (temp_i_height + margTop)
				* scale, UTF8("Lp."));
	if (visibleColumns[1] && sizeColumns[1] != 0)
		p.drawText((leftColumns[1] + 1) * scale, (temp_i_height + margTop)
				* scale, UTF8("Nazwa"));
	if (visibleColumns[2] && sizeColumns[2] != 0)
		p.drawText((leftColumns[2] + 1) * scale, (temp_i_height + margTop)
				* scale, UTF8("Kod"));
	if (visibleColumns[3] && sizeColumns[3] != 0)
		p.drawText((leftColumns[3] + 1) * scale, (temp_i_height + margTop)
				* scale, UTF8("PKWiU"));
	if (visibleColumns[4] && sizeColumns[4] != 0)
		p.drawText((leftColumns[4] + 1) * scale, (temp_i_height + margTop)
				* scale, UTF8("Ilość"));
	if (visibleColumns[5] && sizeColumns[5] != 0)
		p.drawText((leftColumns[5] + 1) * scale, (temp_i_height + margTop)
				* scale, UTF8("Jm."));
	if (visibleColumns[6] && sizeColumns[6] != 0)
		p.drawText((leftColumns[6] + 1) * scale, (temp_i_height + margTop)
				* scale, UTF8("Cena jdn."));
	if (visibleColumns[7] && sizeColumns[7] != 0) {
		p.drawText((leftColumns[7] + 1) * scale, (temp_i_height + margTop + 20)
				* scale, UTF8("Wartość"));
		p.drawText((leftColumns[7] + 1) * scale, (temp_i_height + margTop)
				* scale, UTF8("  Netto"));
	}
	if (visibleColumns[8] && sizeColumns[8] != 0) {
		p.drawText((leftColumns[8] + 1) * scale, (temp_i_height + margTop)
				* scale, UTF8("Rabat"));
		p.drawText((leftColumns[8] + 1) * scale, (temp_i_height + margTop + 20)
				* scale, UTF8(" [%]"));
	}
	if (visibleColumns[9] && sizeColumns[9] != 0) {
		p.drawText((leftColumns[9] + 1) * scale, (temp_i_height + margTop + 20)
				* scale, UTF8(" Rabat"));
		p.drawText((leftColumns[9] + 1) * scale, (temp_i_height + margTop)
				* scale, UTF8("Wartość"));
	}
	if (visibleColumns[10] && sizeColumns[10] != 0) {
		p.drawText((leftColumns[10] + 1) * scale, (temp_i_height + margTop)
				* scale, UTF8(" Netto"));
		p.drawText((leftColumns[10] + 1) * scale,
				(temp_i_height + margTop + 20) * scale, UTF8("po rabacie"));
	}
	if (visibleColumns[11] && sizeColumns[1] != 0) {
		p.drawText((leftColumns[11] + 1) * scale, (temp_i_height + margTop)
				* scale, UTF8("Stawka"));
		p.drawText((leftColumns[11] + 1) * scale,
				(temp_i_height + margTop + 20) * scale, UTF8("VAT[%]"));
	}
	if (visibleColumns[12] && sizeColumns[12] != 0) {
		p.drawText((leftColumns[12] + 1) * scale, (temp_i_height + margTop)
				* scale, UTF8("Kwota"));
		p.drawText((leftColumns[12] + 1) * scale,
				(temp_i_height + margTop + 20) * scale, UTF8(" VAT"));
	}
	if (visibleColumns[13] && sizeColumns[13] != 0) {
		p.drawText((leftColumns[13] + 1) * scale, (temp_i_height + margTop)
				* scale, UTF8("Wartość"));
		p.drawText((leftColumns[13] + 1) * scale,
				(temp_i_height + margTop + 20) * scale, UTF8(" brutto"));
	}
	temp_i_height += 50;
	for (unsigned int i = 0; i < tabletemp.vec_temp.size(); ++i) {
		if (temp_i_height > (pixmap[temp_i_page].height() - margDown - 30
				- margTop)) {
			p.drawLine((leftColumns[0]) * scale, (temp_i_height + margTop - 15)
					* scale, (leftColumns[14]) * scale, (temp_i_height
					+ margTop - 15) * scale);
			p.drawLine((leftColumns[0]) * scale, (temp_i + margTop) * scale,
					(leftColumns[0]) * scale, (temp_i_height + margTop - 15)
							* scale);
			if (visibleColumns[1] && sizeColumns[1] != 0)
				p.drawLine((leftColumns[1]) * scale,
						(temp_i + margTop) * scale, (leftColumns[1]) * scale,
						(temp_i_height + margTop - 15) * scale);
			if (visibleColumns[2] && sizeColumns[2] != 0)
				p.drawLine((leftColumns[2]) * scale,
						(temp_i + margTop) * scale, (leftColumns[2]) * scale,
						(temp_i_height + margTop - 15) * scale);
			if (visibleColumns[3] && sizeColumns[3] != 0)
				p.drawLine((leftColumns[3]) * scale,
						(temp_i + margTop) * scale, (leftColumns[3]) * scale,
						(temp_i_height + margTop - 15) * scale);
			if (visibleColumns[4] && sizeColumns[4] != 0)
				p.drawLine((leftColumns[4]) * scale,
						(temp_i + margTop) * scale, (leftColumns[4]) * scale,
						(temp_i_height + margTop - 15) * scale);
			if (visibleColumns[5] && sizeColumns[5] != 0)
				p.drawLine((leftColumns[5]) * scale,
						(temp_i + margTop) * scale, (leftColumns[5]) * scale,
						(temp_i_height + margTop - 15) * scale);
			if (visibleColumns[6] && sizeColumns[6] != 0)
				p.drawLine((leftColumns[6]) * scale,
						(temp_i + margTop) * scale, (leftColumns[6]) * scale,
						(temp_i_height + margTop - 15) * scale);
			if (visibleColumns[7] && sizeColumns[7] != 0)
				p.drawLine((leftColumns[7]) * scale,
						(temp_i + margTop) * scale, (leftColumns[7]) * scale,
						(temp_i_height + margTop - 15) * scale);
			if (visibleColumns[8] && sizeColumns[8] != 0)
				p.drawLine((leftColumns[8]) * scale,
						(temp_i + margTop) * scale, (leftColumns[8]) * scale,
						(temp_i_height + margTop - 15) * scale);
			if (visibleColumns[9] && sizeColumns[9] != 0)
				p.drawLine((leftColumns[9]) * scale,
						(temp_i + margTop) * scale, (leftColumns[9]) * scale,
						(temp_i_height + margTop - 15) * scale);
			if (visibleColumns[10] && sizeColumns[10] != 0)
				p.drawLine((leftColumns[10]) * scale, (temp_i + margTop)
						* scale, (leftColumns[10]) * scale, (temp_i_height
						+ margTop - 15) * scale);
			if (visibleColumns[11] && sizeColumns[11] != 0)
				p.drawLine((leftColumns[11]) * scale, (temp_i + margTop)
						* scale, (leftColumns[11]) * scale, (temp_i_height
						+ margTop - 15) * scale);
			if (visibleColumns[12] && sizeColumns[12] != 0)
				p.drawLine((leftColumns[12]) * scale, (temp_i + margTop)
						* scale, (leftColumns[12]) * scale, (temp_i_height
						+ margTop - 15) * scale);
			if (visibleColumns[13] && sizeColumns[13] != 0)
				p.drawLine((leftColumns[13]) * scale, (temp_i + margTop)
						* scale, (leftColumns[13]) * scale, (temp_i_height
						+ margTop - 15) * scale);
			p.drawLine((leftColumns[14]) * scale, (temp_i + margTop) * scale,
					(leftColumns[14]) * scale, (temp_i_height + margTop - 15)
							* scale);
			temp_i = 5;
			++temp_i_page;
			temp_i_height = 20;
			p.end();
			if (makePdf) {
				pixmap_pdf.push_back(QPixmap(840 * scale, 1188 * scale));
				pixmap_pdf[temp_i_page].fill();
				p.begin(&pixmap_pdf[temp_i_page]);
			} else {
				pixmap.push_back(QPixmap(840, 1188));
				pixmap[temp_i_page].fill();
				p.begin(&pixmap[temp_i_page]);

			}
		}
		p.drawLine((leftColumns[0]) * scale, (temp_i_height + margTop - 15)
				* scale, (leftColumns[14]) * scale, (temp_i_height + margTop
				- 15) * scale);
		if (visibleColumns[0] && sizeColumns[0] != 0)
			p.drawText((leftColumns[0] + 1) * scale, (temp_i_height + margTop)
					* scale, tabletemp.vec_temp[i][0]);
		if (visibleColumns[1] && sizeColumns[1] != 0)
			p.drawText((leftColumns[1] + 1) * scale, (temp_i_height + margTop)
					* scale, tabletemp.vec_temp[i][1]);
		if (visibleColumns[2] && sizeColumns[2] != 0)
			p.drawText((leftColumns[2] + 1) * scale, (temp_i_height + margTop)
					* scale, tabletemp.vec_temp[i][2]);
		if (visibleColumns[3] && sizeColumns[3] != 0)
			p.drawText((leftColumns[3] + 1) * scale, (temp_i_height + margTop)
					* scale, tabletemp.vec_temp[i][3]);
		if (visibleColumns[4] && sizeColumns[4] != 0)
			p.drawText((leftColumns[4] + 1) * scale, (temp_i_height + margTop)
					* scale, tabletemp.vec_temp[i][4]);
		if (visibleColumns[5] && sizeColumns[5] != 0)
			p.drawText((leftColumns[5] + 1) * scale, (temp_i_height + margTop)
					* scale, tabletemp.vec_temp[i][5]);
		if (visibleColumns[6] && sizeColumns[6] != 0)
			p.drawText((leftColumns[6] + 1) * scale, (temp_i_height + margTop)
					* scale, tabletemp.vec_temp[i][6]);
		if (visibleColumns[7] && sizeColumns[7] != 0)
			p.drawText((leftColumns[7] + 1) * scale, (temp_i_height + margTop)
					* scale, tabletemp.vec_temp[i][7]);
		if (visibleColumns[8] && sizeColumns[8] != 0)
			p.drawText((leftColumns[8] + 1) * scale, (temp_i_height + margTop)
					* scale, tabletemp.vec_temp[i][8]);
		if (visibleColumns[9] && sizeColumns[9] != 0)
			p.drawText((leftColumns[9] + 1) * scale, (temp_i_height + margTop)
					* scale, tabletemp.vec_temp[i][9]);
		if (visibleColumns[10] && sizeColumns[10] != 0)
			p.drawText((leftColumns[10] + 1) * scale, (temp_i_height + margTop)
					* scale, tabletemp.vec_temp[i][10]);
		if (visibleColumns[11] && sizeColumns[11] != 0)
			p.drawText((leftColumns[11] + 1) * scale, (temp_i_height + margTop)
					* scale, tabletemp.vec_temp[i][11]);
		if (visibleColumns[12] && sizeColumns[12] != 0)
			p.drawText((leftColumns[12] + 1) * scale, (temp_i_height + margTop)
					* scale, tabletemp.vec_temp[i][12]);
		if (visibleColumns[13] && sizeColumns[13] != 0)
			p.drawText((leftColumns[13] + 1) * scale, (temp_i_height + margTop)
					* scale, tabletemp.vec_temp[i][13]);
		temp_i_height += 20;
	}
	p.drawLine((leftColumns[0]) * scale, (temp_i + margTop) * scale,
			(leftColumns[0]) * scale, (temp_i_height + margTop - 15) * scale);
	p.drawLine((leftColumns[0]) * scale,
			(temp_i_height + margTop - 15) * scale, (leftColumns[14]) * scale,
			(temp_i_height + margTop - 15) * scale);
	if (visibleColumns[1] && sizeColumns[1] != 0)
		p.drawLine((leftColumns[1]) * scale, (temp_i + margTop) * scale,
				(leftColumns[1]) * scale, (temp_i_height + margTop - 15)
						* scale);
	if (visibleColumns[2] && sizeColumns[2] != 0)
		p.drawLine((leftColumns[2]) * scale, (temp_i + margTop) * scale,
				(leftColumns[2]) * scale, (temp_i_height + margTop - 15)
						* scale);
	if (visibleColumns[3] && sizeColumns[3] != 0)
		p.drawLine((leftColumns[3]) * scale, (temp_i + margTop) * scale,
				(leftColumns[3]) * scale, (temp_i_height + margTop - 15)
						* scale);
	if (visibleColumns[4] && sizeColumns[4] != 0)
		p.drawLine((leftColumns[4]) * scale, (temp_i + margTop) * scale,
				(leftColumns[4]) * scale, (temp_i_height + margTop - 15)
						* scale);
	if (visibleColumns[5] && sizeColumns[5] != 0)
		p.drawLine((leftColumns[5]) * scale, (temp_i + margTop) * scale,
				(leftColumns[5]) * scale, (temp_i_height + margTop - 15)
						* scale);
	if (visibleColumns[6] && sizeColumns[6] != 0)
		p.drawLine((leftColumns[6]) * scale, (temp_i + margTop) * scale,
				(leftColumns[6]) * scale, (temp_i_height + margTop - 15)
						* scale);
	if (visibleColumns[7] && sizeColumns[7] != 0)
		p.drawLine((leftColumns[7]) * scale, (temp_i + margTop) * scale,
				(leftColumns[7]) * scale, (temp_i_height + margTop - 15)
						* scale);
	if (visibleColumns[8] && sizeColumns[8] != 0)
		p.drawLine((leftColumns[8]) * scale, (temp_i + margTop) * scale,
				(leftColumns[8]) * scale, (temp_i_height + margTop - 15)
						* scale);
	if (visibleColumns[9] && sizeColumns[9] != 0)
		p.drawLine((leftColumns[9]) * scale, (temp_i + margTop) * scale,
				(leftColumns[9]) * scale, (temp_i_height + margTop - 15)
						* scale);
	if (visibleColumns[10] && sizeColumns[10] != 0)
		p.drawLine((leftColumns[10]) * scale, (temp_i + margTop) * scale,
				(leftColumns[10]) * scale, (temp_i_height + margTop - 15)
						* scale);
	if (visibleColumns[11] && sizeColumns[11] != 0)
		p.drawLine((leftColumns[11]) * scale, (temp_i + margTop) * scale,
				(leftColumns[11]) * scale, (temp_i_height + margTop - 15)
						* scale);
	if (visibleColumns[12] && sizeColumns[12] != 0)
		p.drawLine((leftColumns[12]) * scale, (temp_i + margTop) * scale,
				(leftColumns[12]) * scale, (temp_i_height + margTop - 15)
						* scale);
	if (visibleColumns[13] && sizeColumns[13] != 0)
		p.drawLine((leftColumns[13]) * scale, (temp_i + margTop) * scale,
				(leftColumns[13]) * scale, (temp_i_height + margTop - 15)
						* scale);

	p.drawLine((leftColumns[14]) * scale, (temp_i + margTop) * scale,
			(leftColumns[14]) * scale, (temp_i_height + margTop - 15) * scale);
	if (temp_i_height
			> (pixmap[temp_i_page].height() - margDown - 30 - margTop)) {
		++temp_i_page;
		temp_i_height = 20;
		p.end();
		if (makePdf) {
			pixmap_pdf.push_back(QPixmap(840 * scale, 1188 * scale));
			pixmap_pdf[temp_i_page].fill();
			p.begin(&pixmap_pdf[temp_i_page]);
		} else {
			pixmap.push_back(QPixmap(840, 1188));
			pixmap[temp_i_page].fill();
			p.begin(&pixmap[temp_i_page]);
		}
	}
	temp_i_height += 30;
	p.drawText((500 + margLeft) * scale,
			(temp_i_height + margTop - 25) * scale, UTF8("Razem:"));
	p.drawText((545 + margLeft) * scale,
			(temp_i_height + margTop - 25) * scale, UTF8("Wartość"));
	p.drawText((545 + margLeft) * scale,
			(temp_i_height + margTop - 12) * scale, UTF8("Netto"));
	p.drawText((600 + margLeft) * scale,
			(temp_i_height + margTop - 25) * scale, UTF8("Kwota"));
	p.drawText((600 + margLeft) * scale,
			(temp_i_height + margTop - 12) * scale, UTF8("VAT"));
	p.drawText((655 + margLeft) * scale,
			(temp_i_height + margTop - 25) * scale, UTF8("Wartość"));
	p.drawText((655 + margLeft) * scale,
			(temp_i_height + margTop - 12) * scale, UTF8("Brutto"));

	p.drawText((545 + margLeft) * scale,
			(temp_i_height + margTop + 10) * scale, tabletemp.data.netto);
	p.drawText((600 + margLeft) * scale,
			(temp_i_height + margTop + 10) * scale, tabletemp.data.vat);
	p.drawText((655 + margLeft) * scale,
			(temp_i_height + margTop + 10) * scale, tabletemp.data.brutto);
	temp_i_height += 60;
	if ((temp_i_height + 120) > (pixmap[temp_i_page].height() - margDown - 30
			- margTop)) {
		++temp_i_page;
		temp_i_height = 20;
		p.end();
		if (makePdf) {
			pixmap_pdf.push_back(QPixmap(840 * scale, 1188 * scale));
			pixmap_pdf[temp_i_page].fill();
			p.begin(&pixmap_pdf[temp_i_page]);
		} else {
			pixmap.push_back(QPixmap(840, 1188));
			pixmap[temp_i_page].fill();
			p.begin(&pixmap[temp_i_page]);
		}
	}
	p.setFont(QFont("Times", 14 * scale, 75));
	p.drawText((20 + margLeft) * scale, (temp_i_height + margTop) * scale, UTF8(
			"Do zapłaty: ") + tabletemp.data.sum);
	p.setFont(QFont("Times", 8 * scale, 50));
	p.drawText((20 + margLeft) * scale, (temp_i_height + margTop + 20) * scale,
			UTF8("Kwota słownie: ") + tabletemp.data.sumStr);
	p.drawText((20 + margLeft) * scale, (temp_i_height + margTop + 40) * scale,
			UTF8("Forma płatności: ") + tabletemp.data.payMode);
	p.drawText((20 + margLeft) * scale, (temp_i_height + margTop + 60) * scale,
			UTF8("Termin płatności: ") + tabletemp.data.payDate);
	if (tabletemp.data.paidCash == true) {
		p.drawText((20 + margLeft) * scale, (temp_i_height + margTop + 80)
				* scale, UTF8("Zapłacono gotówką"));
	} else {
		p.drawText((20 + margLeft), (temp_i_height + margTop + 80) * scale, UTF8(
				"Zapłata przelewem"));
	}
	p.setFont(QFont("Times", 14 * scale, 75));
	p.drawText((20 + margLeft) * scale,
			(temp_i_height + margTop + 100) * scale, tabletemp.data.additText);
	p.drawText((380 + margLeft) * scale,
			(temp_i_height + margTop - 20) * scale, UTF8("Ogólnie stawkami"));
	p.setFont(QFont("Times", 8 * scale, 50));
	p.drawText((400 + margLeft) * scale, (temp_i_height + margTop) * scale, UTF8(
			"Netto"));
	p.drawText((450 + margLeft) * scale, (temp_i_height + margTop) * scale, UTF8(
			"Stawka"));
	p.drawText((500 + margLeft) * scale, (temp_i_height + margTop) * scale, UTF8(
			"Podatek"));
	p.drawText((550 + margLeft) * scale, (temp_i_height + margTop) * scale, UTF8(
			"Brutto"));
	QStringList bidsList = tabletemp.data.bids.split(",");


	temp_i_height += 20;

	QStringListIterator it(bidsList);
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4, it.hasNext(); ++j) {
			p.drawText((400 + margLeft + j * 50) * scale, (temp_i_height
					+ margTop + i * 20) * scale, it.next());
			// ++it;
		}
	temp_i_height += 130;
	if ((temp_i_height + 100) > (pixmap[temp_i_page].height() - margDown - 30
			- margTop)) {
		++temp_i_page;
		temp_i_height = 20;
		p.end();
		if (makePdf) {
			pixmap_pdf.push_back(QPixmap(840 * scale, 1188 * scale));
			pixmap_pdf[temp_i_page].fill();
			p.begin(&pixmap_pdf[temp_i_page]);
		} else {
			pixmap.push_back(QPixmap(840, 1188));
			pixmap[temp_i_page].fill();
			p.begin(&pixmap[temp_i_page]);
		}
	}
	temp_i_height += 50;
	p.drawLine((margLeft + 50) * scale, (temp_i_height + margTop) * scale,
			(margLeft + 300) * scale, (temp_i_height + margTop) * scale);
	p.drawLine((margLeft + 400) * scale, (temp_i_height + margTop) * scale,
			(margLeft + 650) * scale, (temp_i_height + margTop) * scale);
	p.setFont(QFont("Times", 6 * scale, 50));

	QString invoiceType = UTF8("faktury VAT.");

#ifdef QF_base__
	invoiceType = UTF8("faktury VAT.");
#endif

#ifdef QF_vatmp__
	invoiceType = UTF8("faktury VAT.");
#endif

#ifdef QF_noVAT__
	invoiceType = UTF8("rachunku.");
#endif

	p.drawText((margLeft+80)*scale,(temp_i_height+10+margTop)*scale,UTF8("Imię i nazwisko osoby upoważnionej do wystawienia ") + invoiceType);
	p.drawText((margLeft+430)*scale,(temp_i_height+10+margTop)*scale,UTF8("Imię i nazwisko osoby upoważnionej do odbioru ") + invoiceType);

}


void Podglad::drawPageSummary()
{
    QPainter p;
    for(unsigned int i=0;i<pixmap.size();++i)
    {
    if(makePdf)
	p.begin(&pixmap_pdf[i]);
    else
	p.begin(&pixmap[i]);
    p.drawLine((margLeft)*scale,(pixmap[0].height()-20-margDown)*scale,(pixmap[0].width()-margRight)*scale,(pixmap[0].height()-20-margDown)*scale);
    p.setFont(QFont("Times",8*scale));
    QString s(UTF8("QFaktury GPL wersja "));
    s+=STRING(QFAKTURY_VERSION);
    p.drawText((margLeft+10)*scale,(pixmap[0].height()-margDown-10)*scale,s);
    p.drawText((pixmap[0].width()-margRight-200)*scale,(pixmap[0].height()-margDown-10)*scale,UTF8("e-linux.pl"));
    p.drawText((pixmap[0].width()/2-40)*scale,(pixmap[0].height()-margDown-10)*scale,UTF8("strona ")+QString::number(i+1)+"/"+QString::number(pixmap.size()));
   p.end();
   }
}


void Podglad::exportJpg()
{

    int temp_i=0;
    bool ok=false,eXit=false;
    QString filename;
    QFileInfo filenameinfo;
    while(!ok)
    {
    while(filename=="")
	{
    	filename = QFileDialog::getSaveFileName(this, UTF8("Save File"),
    	                            QDir::homePath(),
    	                            UTF8("Images (*.png)"));


	if(filename=="")
	{
	    temp_i=QMessageBox::question(this, "QFaktury", UTF8("Czy chcesz anulowa�? "),QMessageBox::Yes ,QMessageBox::No );
	if(temp_i==QMessageBox::Yes)
	   {
	    eXit=true;
	    break;
	}
                }
               }
    filenameinfo.setFile(filename);
    if(filenameinfo.suffix().toUpper()!="PNG")
        filename+=".png";
    if(QFile::exists(filenameinfo.filePath()+"_01"+".png"))
    {
	temp_i=QMessageBox::question(this, "QFaktury", UTF8("Czy chcesz nadpisa� plik? "),QMessageBox::Yes ,QMessageBox::No );
	if(temp_i==QMessageBox::Yes)
	  {
	  ok=true;
                  }
    }
    else
    {
	ok=true;
    }
}
  if(eXit==false)
    {
      this->setWindowTitle(UTF8("Trwa eksportowanie..."));
      for(unsigned int i=0;i<pixmap.size();++i)
        {
	  if(i<9)
	  {
	      if(QFile::exists(filenameinfo.filePath()+"_0"+QString::number(i+1)+".png"))
   	        QFile::remove(filenameinfo.filePath()+"_0"+QString::number(i+1)+".png");
	      pixmap[i].save(filenameinfo.filePath()+"_0"+QString::number(i+1)+".png","PNG");
	  }
	  else

	  {
	    if(QFile::exists(filenameinfo.filePath()+"_"+QString::number(i+1)+".png"))
	      QFile::remove(filenameinfo.filePath()+"_"+QString::number(i+1)+".png");
                    pixmap[i].save(filenameinfo.filePath()+"_"+QString::number(i+1)+".png","PNG");
	  }
        }
    }
  this->setWindowTitle(tabletemp.data.title);

}


void Podglad::setVisibleColumn()
{
    Settings settings;
    visibleColumns[0]=settings.value ("faktury_pozycje/Lp").toInt();
    visibleColumns[1]=settings.value ("faktury_pozycje/Nazwa").toInt();
    visibleColumns[2]=settings.value ("faktury_pozycje/Kod").toInt();
    visibleColumns[3]=settings.value ("faktury_pozycje/pkwiu").toInt();
    visibleColumns[4]=settings.value ("faktury_pozycje/ilosc").toInt();
    visibleColumns[5]=settings.value ("faktury_pozycje/jm").toInt();
    visibleColumns[6]=settings.value ("faktury_pozycje/cenajedn").toInt();
    visibleColumns[7]=settings.value ("faktury_pozycje/wartnetto").toInt();
    visibleColumns[8]=settings.value ("faktury_pozycje/rabatperc").toInt();
    visibleColumns[9]=settings.value ("faktury_pozycje/rabatval").toInt();
    visibleColumns[10]=settings.value ("faktury_pozycje/nettoafter").toInt();
    visibleColumns[11]=settings.value ("faktury_pozycje/vatval").toInt();
    visibleColumns[12]=settings.value ("faktury_pozycje/vatprice").toInt();
    visibleColumns[13]=settings.value ("faktury_pozycje/bruttoval").toInt();

    settings.beginGroup("wydruki");
    sizeColumns[0]=settings.value("col1").toInt()*4;
    sizeColumns[1]=settings.value("col2").toInt()*4;
    sizeColumns[2]=settings.value("col3").toInt()*4;
    sizeColumns[3]=settings.value("col4").toInt()*4;
    sizeColumns[4]=settings.value("col5").toInt()*4;
    sizeColumns[5]=settings.value("col6").toInt()*4;
    sizeColumns[6]=settings.value("col7").toInt()*4;
    sizeColumns[7]=settings.value("col8").toInt()*4;
    sizeColumns[8]=settings.value("col9").toInt()*4;
    sizeColumns[9]=settings.value("col10").toInt()*4;
    sizeColumns[10]=settings.value("col11").toInt()*4;
    sizeColumns[11]=settings.value("col12").toInt()*4;
    sizeColumns[12]=settings.value("col13").toInt()*4;
    sizeColumns[13]=settings.value("col14").toInt()*4;
    settings.endGroup();
  int temp=0;
  leftColumns[0]=margLeft;
  for(int i=0;i<14;++i)
  {

    if(visibleColumns[i]==true)
      {
	temp+=sizeColumns[i];
    }
    leftColumns[i+1]=temp+margLeft;
  }
  if((840-leftColumns[14]-margRight)>0)
  {
      for(int i=0;i<15;++i)
      {
	  leftColumns[i]+=((840-leftColumns[14]-margRight)/2);
      }
  }
}
