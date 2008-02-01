/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you want to add, delete, or rename functions or slots, use
** Qt Designer to update this file, preserving your code.
**
** You should not define a constructor or destructor in this file.
** Instead, write your code in functions called init() and destroy().
** These will automatically be called by the form's constructor and
** destructor.
*****************************************************************************/
#include "Ustawienia.moc"
#include <qtextcodec.h>
#include "Settings.h"
#include <qfiledialog.h>


#include <qprinter.h>
#include <qpainter.h>
#include <qimage.h>
#include <qpicture.h>

#include <qdatetime.h>
#include <qdir.h>
#include <Qt/qdom.h>
#include <qfont.h>

#include <qmessagebox.h>
#include <qapplication.h>

// #include "preview.h"



void Ustawienia::init ()
{
  tablePos->setColumnWidth(0, 300);
  readSettings ();
}

void Ustawienia::apply ()
{
  saveSettings ();
  zastButton->setEnabled(false);
}

void Ustawienia::okButtonClick ()
{
  saveSettings ();
  accept ();
}

QString Ustawienia::getAll(QListWidget *lb)
{
    QString tmp;
  int selNr, posCount = lb->count ();
  for (selNr = 0; selNr < posCount; ++selNr)
    {
	  tmp += lb->item(selNr)->text();
	  tmp += "|";
    }
 return  tmp;
}

void Ustawienia::saveSettings ()
{
  Settings settings;
  settings.beginGroup ("elinux/faktury");
  settings.setValue("firstrun", "nie");
  settings.setValue ("logo", logoEdit->text());  
  settings.setValue ("jednostki",   getAll(currlBox) );
  settings.setValue ("stawki",   getAll(vatlBox).remove("%") );
  settings.setValue ("waluty",   getAll(currencylBox) );
  settings.setValue ("pkorekty",   getAll(korlBox) );
  settings.setValue ("payments",   getAll(paymlBox) ); // uwaga!! get first
  settings.setValue ("paym1",   paymlBox->item(0)->text() ); 
  
  settings.setValue ("prefix",  prefixEdit->text() ); 
  settings.setValue ("day",  cbDay->isChecked() ); 
  settings.setValue ("month",  cbMonth->isChecked() ); 
  settings.setValue ("year",  cbYear->isChecked() ); 
  settings.setValue ("edit",  cbEdit->isChecked() ); 
  settings.setValue ("editSymbol",  cbSmbEdit->isChecked() ); 
  settings.setValue ("shortYear",  shortYear->isChecked() ); 
  settings.setValue ("chars_in_symbol",  spbNumb->value() ); 
  
  settings.endGroup ();
  

  //X
//  settings.beginGroup ("elinux/faktury_pozycje");
//  QCheckTableItem  *cb;
//  cb = static_cast<QCheckTableItem *>( tablePos->item( 0, 0) );
//  settings.setValue ("Lp",   cb->isChecked());
//  cb = static_cast<QCheckTableItem *>( tablePos->item( 1, 0) );
//  settings.setValue ("Nazwa",   cb->isChecked());
//  cb = static_cast<QCheckTableItem *>( tablePos->item( 2, 0) );
//  settings.setValue ("Kod",   cb->isChecked());
//  cb = static_cast<QCheckTableItem *>( tablePos->item( 3, 0) );
//  settings.setValue ("pkwiu",   cb->isChecked());
//  cb = static_cast<QCheckTableItem *>( tablePos->item( 4, 0) );
//  settings.setValue ("ilosc",   cb->isChecked());
//  cb = static_cast<QCheckTableItem *>( tablePos->item( 5, 0) );
//  settings.setValue ("jm",   cb->isChecked());
//  cb = static_cast<QCheckTableItem *>( tablePos->item( 6, 0) );
//  settings.setValue ("cenajedn",   cb->isChecked());
//  cb = static_cast<QCheckTableItem *>( tablePos->item( 7, 0) );
//  settings.setValue ("wartnetto",   cb->isChecked());
//  cb = static_cast<QCheckTableItem *>( tablePos->item( 8, 0) );
//  settings.setValue ("rabatperc",   cb->isChecked());
//  cb = static_cast<QCheckTableItem *>( tablePos->item( 9, 0) );
//  settings.setValue ("rabatval",   cb->isChecked());
//  cb = static_cast<QCheckTableItem *>( tablePos->item( 10, 0) );
//  settings.setValue ("nettoafter",   cb->isChecked());
//  cb = static_cast<QCheckTableItem *>( tablePos->item( 11, 0) );
//  settings.setValue ("vatval",   cb->isChecked());
//  cb = static_cast<QCheckTableItem *>( tablePos->item( 12, 0) );
//  settings.setValue ("vatprice",   cb->isChecked());
//  cb = static_cast<QCheckTableItem *>( tablePos->item( 13, 0) );
//  settings.setValue ("bruttoval",   cb->isChecked());
//  settings.endGroup ();
}

void Ustawienia::readSettings ()
{
  Settings settings;
  
  //  settings.writeEntry ("firstrun", "nie");
  logoEdit->setText( settings.value("elinux/faktury/logo").toString() );
 currlBox->addItems( settings.value("elinux/faktury/jednostki").toString().split("|")); 
 vatlBox->addItems( settings.value("elinux/faktury/stawki").toString().split("|")); 
 currencylBox->addItems( settings.value("elinux/faktury/waluty").toString().split("|")); 
 paymlBox->addItems( settings.value("elinux/faktury/payments").toString().split("|")); 
 korlBox->addItems( settings.value("elinux/faktury/pkorekty").toString().split("|")); 
 
 /*  
  settings.writeEntry ("payments",   getAll(paymlBox) ); // uwaga!! get first
  settings.writeEntry ("paym1",   getAll(paymlBox)[0] );   
  */
 //X
//  QCheckTableItem *cbItem1 = new QCheckTableItem ( tablePos, "Lp." );
//    tablePos->setItem( 0, 0, cbItem1);
//    cbItem1->setChecked( settings.value/*bool*/("elinux/faktury_pozycje/Lp") .toBool());
//    
//    QCheckTableItem *cbItem2 = new QCheckTableItem ( tablePos, "Nazwa" ); 	
//    tablePos->setItem( 1, 0, cbItem2);
//    cbItem2->setChecked( settings.value/*bool*/("elinux/faktury_pozycje/Nazwa") .toBool());
//    
//    QCheckTableItem *cbItem3 = new QCheckTableItem ( tablePos, "Kod" );
//    tablePos->setItem( 2, 0, cbItem3);
//    cbItem3->setChecked( settings.value/*bool*/("elinux/faktury_pozycje/Kod") .toBool());
//    
//    QCheckTableItem *cbItem4 = new QCheckTableItem ( tablePos, "PKWiU" ); 	
//    tablePos->setItem( 3, 0, cbItem4);
//    cbItem4->setChecked( settings.value/*bool*/("elinux/faktury_pozycje/pkwiu") .toBool());
//    
//    QCheckTableItem *cbItem5 = new QCheckTableItem ( tablePos, "Ilo¶æ" ); 	
//    tablePos->setItem( 4, 0, cbItem5);
//    cbItem5->setChecked( settings.value/*bool*/("elinux/faktury_pozycje/ilosc") .toBool());
//    
//    QCheckTableItem *cbItem6 = new QCheckTableItem ( tablePos, "Jm." ); 	
//    tablePos->setItem( 5, 0, cbItem6);
//    cbItem6->setChecked( settings.value/*bool*/("elinux/faktury_pozycje/jm") .toBool());
//    
//    QCheckTableItem *cbItem7 = new QCheckTableItem ( tablePos, "Cena jdn." ); 	
//    tablePos->setItem( 6, 0, cbItem7);
//    cbItem7->setChecked( settings.value/*bool*/("elinux/faktury_pozycje/cenajedn") .toBool());
//    
//    QCheckTableItem *cbItem8 = new QCheckTableItem ( tablePos, "Warto¶æ Netto" ); 	
//    tablePos->setItem( 7, 0, cbItem8);
//    cbItem8->setChecked( settings.value/*bool*/("elinux/faktury_pozycje/wartnetto") .toBool());
//    
//    QCheckTableItem *cbItem9 = new QCheckTableItem ( tablePos, "Rabat %" ); 	
//    tablePos->setItem( 8, 0, cbItem9);
//    cbItem9->setChecked( settings.value/*bool*/("elinux/faktury_pozycje/rabatperc") .toBool());
//    
//    QCheckTableItem *cbItem10 = new QCheckTableItem ( tablePos, "Rabat Warto¶æ" );	
//    tablePos->setItem( 9, 0, cbItem10);
//    cbItem10->setChecked( settings.value/*bool*/("elinux/faktury_pozycje/rabatval") .toBool());
//    
//    QCheckTableItem *cbItem11 = new QCheckTableItem ( tablePos, "Netto po rabacie" ); 	
//    tablePos->setItem( 10, 0, cbItem11);
//    cbItem11->setChecked( settings.value/*bool*/("elinux/faktury_pozycje/nettoafter") .toBool());
//    
//    QCheckTableItem *cbItem12 = new QCheckTableItem ( tablePos, "Stawka VAT" ); 	
//    tablePos->setItem( 11, 0, cbItem12);
//    cbItem12->setChecked( settings.value/*bool*/("elinux/faktury_pozycje/vatval") .toBool());
//    
//    QCheckTableItem *cbItem13 = new QCheckTableItem ( tablePos, "Kwota Vat" ); 	
//    tablePos->setItem( 12, 0, cbItem13);
//    cbItem13->setChecked( settings.value/*bool*/("elinux/faktury_pozycje/vatprice") .toBool());
//    
//    QCheckTableItem *cbItem14 = new QCheckTableItem ( tablePos, "Warto¶æ Brutto" );
//    tablePos->setItem( 13, 0, cbItem14);
//    cbItem14->setChecked( settings.value/*bool*/("elinux/faktury_pozycje/bruttoval") .toBool());
    
  prefixEdit->setText( settings.value("elinux/faktury/prefix").toString()  );
	
  cbDay->setChecked( settings.value/*bool*/("elinux/faktury/day")  .toBool());
  cbMonth->setChecked( settings.value/*bool*/("elinux/faktury/month")  .toBool());
  cbYear->setChecked( settings.value/*bool*/("elinux/faktury/year")  .toBool());
  shortYear->setChecked( settings.value/*bool*/("elinux/faktury/shortYear")  .toBool());
  cbEdit->setChecked( settings.value/*bool*/("elinux/faktury/edit")  .toBool());
  cbSmbEdit->setChecked( settings.value/*bool*/("elinux/faktury/editSymbol")  .toBool());
  spbNumb->setValue( settings.value/*int*/("elinux/faktury/chars_in_symbol").toInt() );
}


void Ustawienia::addLogoBtnClick()
{
 // qDebug( "%s, %s, %d", __FUNCTION__ , __FILE__, __LINE__);
 QString ofn = QFileDialog::getOpenFileName (this,"Wybierz plik do wstawienia jako logo", "",
				       "Obrazki (*.jpg *.png)"
				       );
 
 logoEdit->setText( ofn );
  zastButton->setEnabled(true);
}


void Ustawienia::currAddBtnClick()
{
  //    qDebug( "%s, %s, %d", __FUNCTION__ , __FILE__, __LINE__);
    if ( currEdit->text() != "" ) {
	currlBox->addItem(currEdit->text());
	currEdit->clear();
    } else {
      QMessageBox::information (this, "Uwaga!!", "Nie mo¿na dodaæ. Pole jest puste.",
				QMessageBox::Ok);	
    }
  zastButton->setEnabled(true);
    
}


void Ustawienia::currDelBtnClick()
{
 //  qDebug( "%s, %s, %d", __FUNCTION__ , __FILE__, __LINE__);
  if (!currlBox->selectedItems().isEmpty())
    {
      currlBox->removeItemWidget(currlBox->selectedItems()[0]);
    }
  else
    {
      QMessageBox::information (this, "Uwaga!!", "Musisz co¶ zaznaczyæ, ¿eby usuwaæ",
				QMessageBox::Ok);
    }
    zastButton->setEnabled(true);

}

void Ustawienia::korAddBtnClick()
{
  //    qDebug( "%s, %s, %d", __FUNCTION__ , __FILE__, __LINE__);
    if ( korEdit->text() != "" ) {
	korlBox->addItem(korEdit->text());
	korEdit->clear();
    } else {
      QMessageBox::information (this, "Uwaga!!", "Nie mo¿na dodaæ. Pole jest puste.",
				QMessageBox::Ok);	
    }
      zastButton->setEnabled(true);

}



void Ustawienia::korDelBtnClick()
{
 //  qDebug( "%s, %s, %d", __FUNCTION__ , __FILE__, __LINE__);
  if (!korlBox->selectedItems().isEmpty())
    {
      korlBox->removeItemWidget(korlBox->selectedItems()[0]);
    }
  else
    {
      QMessageBox::information (this, "Uwaga!!", "Musisz co¶ zaznaczyæ, ¿eby usuwaæ",
				QMessageBox::Ok);
    }
  zastButton->setEnabled(true);
  
}


void Ustawienia::vatAddBtnClick()
{
 //  qDebug( "%s, %s, %d", __FUNCTION__ , __FILE__, __LINE__);
    if ( vatEdit->text() != "" ) {
	vatlBox->addItem(vatEdit->text());
	vatEdit->clear();
    } else {
      QMessageBox::information (this, "Uwaga!!", "Nie mo¿na dodaæ. Pole jest puste.",
				QMessageBox::Ok);	
    }
  zastButton->setEnabled(true);
    
}


void Ustawienia::vatDelBtnClick()
{
 //  qDebug( "%s, %s, %d", __FUNCTION__ , __FILE__, __LINE__);
  if (!vatlBox->selectedItems().isEmpty())
    {
      vatlBox->removeItemWidget (vatlBox->selectedItems()[0]);
    }
  else
    {
      QMessageBox::information (this, "Uwaga!!", "Musisz co¶ zaznaczyæ, ¿eby usuwaæ",
				QMessageBox::Ok);
    }
   zastButton->setEnabled(true);
 
}


void Ustawienia::vatUpBtnClick()
{
    //X
//    int selNr, posCount = vatlBox->count ();
//  if (!vatlBox->selectedItems()->isEmpty())
//    {
//      QString pmitem = vatlBox->text(selNr);
//      vatlBox->removeItemWidget(selNr);
//      vatlBox->insertItem(pmitem , selNr -1);
//      vatlBox->setSelected ( selNr -1, true );
//    }
//  else
//    {
//      QMessageBox::information (this, "Uwaga!!", "Musisz co¶ zaznaczyæ, ¿eby przesuwaæ",
//				QMessageBox::Ok);
//    }
// 
//   zastButton->setEnabled(true);
 
}

void Ustawienia::vatDownBtnClick()
{
    //X
//    int selNr, posCount = vatlBox->count ();
//  bool hasSel = false;
//  for (selNr = 0; selNr < posCount; ++selNr)
//    {
//      if (vatlBox->isSelected (selNr))
//	{
//	  hasSel = true;
//	  break;
//	}
//    }
//
//  if (hasSel)
//    {
//      QString pmitem = vatlBox->text(selNr);
//      vatlBox->removeItem (selNr);
//      vatlBox->insertItem(pmitem , selNr + 1);
//      vatlBox->setSelected ( selNr + 1, true );
//    }
//  else
//    {
//      QMessageBox::information (this, "Uwaga!!", "Musisz co¶ zaznaczyæ, ¿eby przesuwaæ",
//				QMessageBox::Ok);
//    }
//   zastButton->setEnabled(true);
//    
}

void Ustawienia::currencyAddBtnClick()
{
 //  qDebug( "%s, %s, %d", __FUNCTION__ , __FILE__, __LINE__);
    if ( currencyEdit->text() != "" ) {
	currencylBox->addItem(currencyEdit->text());
	currencyEdit->clear();
    } else {
      QMessageBox::information (this, "Uwaga!!", "Nie mo¿na dodaæ. Pole jest puste.",
				QMessageBox::Ok);	
    }
   zastButton->setEnabled(true);

}


void Ustawienia::currencyDelBtnClick()
{
 //  qDebug( "%s, %s, %d", __FUNCTION__ , __FILE__, __LINE__);
  if (!currencylBox->selectedItems().isEmpty())
    {
      currencylBox->removeItemWidget (currencylBox->selectedItems()[0]);
    }
  else
    {
      QMessageBox::information (this, "Uwaga!!", "Musisz co¶ zaznaczyæ, ¿eby usuwaæ",
				QMessageBox::Ok);
    }
    zastButton->setEnabled(true);

}


void Ustawienia::paymUpBtnClick()
{
    //X
// //  qDebug( "%s, %s, %d", __FUNCTION__ , __FILE__, __LINE__);
//  int selNr, posCount = paymlBox->count ();
//  bool hasSel = false;
//  for (selNr = 0; selNr < posCount; ++selNr)
//    {
//      if (paymlBox->isSelected (selNr))
//	{
//	  hasSel = true;
//	  break;
//	}
//    }
//
//  if (hasSel)
//    {
//      QString pmitem = paymlBox->text(selNr);
//      paymlBox->removeItem (selNr);
//      paymlBox->insertItem(pmitem , selNr -1);
//      paymlBox->setSelected ( selNr -1, true );
//    }
//  else
//    {
//      QMessageBox::information (this, "Uwaga!!", "Musisz co¶ zaznaczyæ, ¿eby przesuwaæ",
//				QMessageBox::Ok);
//    }
//  zastButton->setEnabled(true);
// 
}


void Ustawienia::paymDownBtnClick()
{
    //X
// //  qDebug( "%s, %s, %d", __FUNCTION__ , __FILE__, __LINE__);
//  int selNr, posCount = paymlBox->count ();
//  bool hasSel = false;
//  for (selNr = 0; selNr < posCount; ++selNr)
//    {
//      if (paymlBox->isSelected (selNr))
//	{
//	  hasSel = true;
//	  break;
//	}
//    }
//
//  if (hasSel)
//    {
//      QString pmitem = paymlBox->text(selNr);
//      paymlBox->removeItem (selNr);
//      paymlBox->insertItem(pmitem , selNr +1);
//      paymlBox->setSelected ( selNr + 1, true );
//    }
//  else
//    {
//      QMessageBox::information (this, "Uwaga!!", "Musisz co¶ zaznaczyæ, ¿eby przesuwaæ",
//				QMessageBox::Ok);
//    }
//  zastButton->setEnabled(true);
// 
}


void Ustawienia::paymDelBtnClick()
{
 //  qDebug( "%s, %s, %d", __FUNCTION__ , __FILE__, __LINE__);
  if (!paymlBox->selectedItems().isEmpty())
    {
      paymlBox->removeItemWidget (paymlBox->selectedItems()[0]);
    }
  else
    {
      QMessageBox::information (this, "Uwaga!!", "Musisz co¶ zaznaczyæ, ¿eby usuwaæ",
				QMessageBox::Ok);
    }
  zastButton->setEnabled(true);
  
}

void Ustawienia::zastBtnEnable()
{
    zastButton->setEnabled(true);
}

void Ustawienia::paymAddBtnClick()
{
 //  qDebug( "%s, %s, %d", __FUNCTION__ , __FILE__, __LINE__);
    if ( paymEdit->text() != "" ) {
	paymlBox->addItem(paymEdit->text());
	paymEdit->clear();
    } else {
      QMessageBox::information (this, "Uwaga!!", "Nie mo¿na dodaæ. Pole jest puste.",
				QMessageBox::Ok);	
    }
   
      zastButton->setEnabled(true);

 
}

Ustawienia::Ustawienia(QWidget *parent): QDialog(parent) {
    setupUi(this);
    init();
}

