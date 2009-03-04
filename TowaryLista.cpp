#include "TowaryLista.moc"
#include <Qt/qdom.h>
#include <qdir.h>
#include <qmessagebox.h>
#include <QTextCodec>
#include <QTextStream>
#include <QDebug>

#include "Rounding.h"

/** Constructor
 */
TowaryLista::TowaryLista(QWidget *parent): QDialog(parent) {
    setupUi(this);
    init();
}

/** Init
 */
void TowaryLista::init ()
{
  ret = "";

  listaTowary.clear ();
  listaUslugi.clear ();
  listaTowary2.clear ();
  listaUslugi2.clear ();
  listWidget->clear();

  readTow (sett().getWorkingDir());
  fillLv (0);

  connect( okBtn, SIGNAL( clicked() ), this, SLOT( doAccept()));
  connect( cancelBtn, SIGNAL( clicked() ), this, SLOT( close()));
  connect( comboBox1, SIGNAL( activated(int) ), this, SLOT( comboBox1Changed(int)));
  connect( listWidget, SIGNAL(itemSelectionChanged()), this, SLOT(lv1selChanged()));
  connect( spinBox2, SIGNAL( valueChanged(int) ), this, SLOT( spinChanged(int) ) );
  // connect( nameEdit, SIGNAL( textChanged(const QString&) ), this, SLOT( setSelItemText() ) );
  connect( rabatSpin, SIGNAL( valueChanged(int) ), this, SLOT( calcNetto() ) );
  // connect( countSpinBox, SIGNAL( lostFocus() ), this, SLOT( calcNetto() ) );
  // connect( countSpinBox, SIGNAL( selectionChanged() ), this, SLOT( calcNetto() ) );
  connect( countSpinBox, SIGNAL( valueChanged(const QString&) ), this, SLOT( calcNetto() ) );

}

void TowaryLista::readTow (QString progDir)
{
  QDomDocument doc (sett().getProdutcsDocName());
  QDomElement root;
  QDomElement towar;
  QDomElement usluga;
  QString code, curr, pkwiu;

  QFile file (sett().getProductsXml());
  if (!file.open (QIODevice::ReadOnly))
    {
      qDebug ("file doesn't exists");
      return;
    }
  else
    {
      QTextStream stream (&file);
      if (!doc.setContent (stream.readAll ()))
	{
	  qDebug ("can not set content ");
	  file.close ();
	  return;
	}
      else
	{
	  root = doc.documentElement ();
	  towar = root.firstChild ().toElement ();
	  usluga = root.lastChild ().toElement ();
	}
      QString text, idx;

      for (QDomNode n = towar.firstChild (); !n.isNull ();
	   n = n.nextSibling ())
	{
	  idx = n.toElement ().attribute ("idx");
	  listaTowary.append (idx);

	  text = n.toElement ().attribute ("name");
	  listaTowary.append (text);

	  code = n.toElement ().attribute ("code");
	  curr = n.toElement ().attribute ("curr");
	  pkwiu = n.toElement ().attribute ("pkwiu");

	  // ProductsListData* tst1 = new ProductsListData (code, curr, pkwiu);
	  // listaTowary2[idx] = tst1;

	  listaTowary2.insert(text, new ProductsListData (code, curr, pkwiu));

	}

      for (QDomNode n = usluga.firstChild (); !n.isNull ();
	   n = n.nextSibling ())
	{
	  idx = n.toElement ().attribute ("idx");
	  listaUslugi.append (idx);

	  text = n.toElement ().attribute ("name");
	  listaUslugi.append (text);

	  code = n.toElement ().attribute ("code");
	  curr = n.toElement ().attribute ("curr");
	  pkwiu = n.toElement ().attribute ("pkwiu");
	  listaUslugi2[text] = new ProductsListData (code, curr, pkwiu);
	}
    }
}



void TowaryLista::doAccept ()
{
  if (countSpinBox->text () == "")
    {
      QMessageBox::information (this, "QFaktury", trUtf8("Podaj ilość"),
				QMessageBox::Ok);
      return;
    }

  if (selectedItem != "")
    {
// |Index|Nazwa|Kod|Ilość|Jm|cena jednostkowa|Kwota netto|vat|kwota brutto|
      if (comboBox1->currentIndex () == 0)
	{
	  /*
	     int x = listaTowary.findIndex(selectedItem);
	     qDebug( "%d", x );
	     qDebug( selectedItem );
	     qDebug( "code" + listaTowary2[id].codeX() );
	     qDebug( "curr" + listaTowary2[id].currX() );
	     qDebug( "pkwiu" + listaTowary2[id].pkwiuX() );
	   */
    	  ret =
    	    selectedItem + "|" + listaTowary2[id]->getCode() + "|" +
    	    listaTowary2[id]->getPkwiu() + "|" + countSpinBox->cleanText ().replace(".", ",") + "|" +
    	    listaTowary2[id]->getQuantityType() + "|" +
    	    QString::number (rabatSpin->value ()) + "|" + priceBoxEdit->cleanText ().replace(".", ",") +
    	    "|" + nettoLabel->text () + "|" + vat + "|" +
    	    bruttoLabel->text ();


	}
      if (comboBox1->currentIndex () == 1)
	{
	  // int x = listaUslugi.findIndex(selectedItem);
	  // qDebug( "%d", x );

  	    ret = selectedItem + "|" + listaUslugi2[id]->getCode() + "|" +
  	    listaUslugi2[id]->getPkwiu() + "|" + countSpinBox->cleanText ().replace(".", ",") + "|" +
  	    listaUslugi2[id]->getQuantityType() + "|" +
  	    QString::number (rabatSpin->value ()) + "|" + priceBoxEdit->cleanText ().replace(".", ",") +
  	    "|" + nettoLabel->text () + "|" + vat + "|" +
  	    bruttoLabel->text ();

	}
      accept ();
    }
  else
    {
      QMessageBox::information (this, "QFaktury", trUtf8("Wskaż towar"),
				QMessageBox::Ok);
    }
}

void TowaryLista::comboBox1Changed (int x)
{
  // qDebug (__FUNCTION__);
  // listWidget->clear ();
  fillLv (x);
}

void TowaryLista::calcNetto ()
{
	  QString rabat1 = QString::number (rabatSpin->value ());
	  if (rabat1.length () == 1)
	    rabat1 = "0.0" + rabat1;
	  else
	    rabat1 = "0." + rabat1;

	  double rabat2 = (countSpinBox->value () * priceBoxEdit->value ()) * rabat1.toDouble ();
	  double netto2 = (countSpinBox->value() * priceBoxEdit->value ()) - rabat2;
	  double brutto2 = getPriceGross2 (netto2, vat);
	  bruttoLabel->setText (fixStr (QString::number (brutto2)));
	  nettoLabel->setText (fixStr (QString::number (netto2)));
}


void TowaryLista::fillLv (int x)
{
  switch (x)
    {
    case 0:
      for (int i = 1; i < listaTowary.count (); i+=2)
	{
        listWidget->addItem(listaTowary[i]);
//	  if (next)
//	    {
//	      tmp = new QListWidgetItem (listWidget, listaTowary[i]);
//	      next = false;
//	    }
//	  else
//	    {
//	      tmp->setText (1, listaTowary[i]);
//	      next = true;
//	    }

	}
      break;
    case 1:
      for (int i = 1; i < listaUslugi.count (); i+=2)
	{
        listWidget->addItem(listaUslugi[i]);
//	  if (next)
//	    {
//	      tmp = new QListWidgetItem (listWidget, listaUslugi[i]);
//	      next = false;
//	    }
//	  else
//	    {
//	      tmp->setText (1, listaUslugi[i]);
//	      next = true;
//	    }

	}
      break;

    }
}

void TowaryLista::lv1selChanged ()
{
  QList<QListWidgetItem *> items = listWidget->selectedItems();
  if (items.size() == 1)
    {
      QListWidgetItem *item=items[0];
      nameEdit->setText(item->text());
      readNettos (item->text());
      id = item->text ();
      selectedItem = item->text ();
      calcNetto ();
    }

}

void TowaryLista::readNettos (QString index)
{
  QDomDocument doc (sett().getProdutcsDocName());
  QDomElement root;
  QDomElement towar;
  QDomElement usluga;

  QFile file (sett().getProductsXml());
  if (!file.open (QIODevice::ReadOnly))
    {
	qDebug() << "File" << file.fileName() << "doesn't exists";
      return;
    }
  else
    {
      QTextStream stream (&file);
      if (!doc.setContent (stream.readAll ()))
	{
	  qDebug ("can not set content ");
	  file.close ();
	  return;
	}
      else
	{
	  root = doc.documentElement ();
	  towar = root.firstChild ().toElement ();
	  usluga = root.lastChild ().toElement ();
	}
      QString text;

      if (comboBox1->currentIndex () == 0)
	{
	  for (QDomNode n = towar.firstChild (); !n.isNull ();
	       n = n.nextSibling ())
	    {

	      text = n.toElement ().attribute ("name");
	      if (text == index)
		{
		  nettos[0] = n.toElement ().attribute ("netto1");
		  nettos[1] = n.toElement ().attribute ("netto2");
		  nettos[2] = n.toElement ().attribute ("netto3");
		  nettos[3] = n.toElement ().attribute ("netto4");
		  priceBoxEdit->setValue(nettos[0].toDouble());
		  spinBox2->setValue (1);
		  vat = n.toElement ().attribute ("vat");
		}
	    }
	}

      if (comboBox1->currentIndex () == 1)
	{

	  for (QDomNode n = usluga.firstChild (); !n.isNull ();
	       n = n.nextSibling ())
	    {
	      text = n.toElement ().attribute ("name");
	      if (text == index)
		{
		  nettos[0] = n.toElement ().attribute ("netto1");
		  nettos[1] = n.toElement ().attribute ("netto2");
		  nettos[2] = n.toElement ().attribute ("netto3");
		  nettos[3] = n.toElement ().attribute ("netto4");
		  priceBoxEdit->setValue(nettos[0].toDouble());
		  spinBox2->setValue (1);
		  vat = n.toElement ().attribute ("vat");
		}
	    }
	}
    }

}


void TowaryLista::spinChanged (int a)
{
  qDebug () << __FUNCTION__;
  priceBoxEdit->setValue (nettos[a - 1].toDouble());
  calcNetto ();
}
