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

#include "Podglad.moc"
#include <QPainter>
#include <QPixmap>
#include <QLabel>
#include <QDebug>
#include <QToolBar>

void Podglad::init ()
{
    //X
//  QBoxLayout *l = new QHBoxLayout (this);
//  l->setAutoAdd (TRUE);
//
//  QScrollView *sv = new QScrollView (this);
//  // sv->resize(size());
//  QLabel *pixaaa = new QLabel (sv);
//  pixaaa->setPixmap (QPixmap ("/tmp/przelew.png"));
//  sv->addChild (pixaaa);
}

Podglad::Podglad(QWidget *parent): QDialog(parent) {
    setupUi(this);
    init();
}

void Podglad::setTableTemp( TableTemp & t,QString progdir2,QString retrn )
{
	qDebug() << __FUNCTION__;
 tabletemp=t;
 makePixmap();
 this->setWindowTitle(tabletemp.data.title);
/*
 progDir2=progdir2;
 ret=retrn;
 if(tabletemp.data.paidCash==false)
     pushButton6->setEnabled(true);
  label->setPixmap(pixmap[0]);
  */
}

void Podglad::makePixmap()
{
	/*
 //   qDebug("makePixmap");
    setVisibleColumn();
    if(makePdf)
    {
                if(pixmap_pdf.size()==0)
	{
	pixmap_pdf.push_back(QPixmap(840*scale,1188*scale));
	pixmap_pdf[0].fill();
	QPainter p(&pixmap_pdf[0]);
	drawHeader(p);
	p.end();
	drawBody();
	drawPageSummary();
                }
    }
    else
    {
	pixmap.push_back(QPixmap(840,1188));
	pixmap[0].fill();
	QPainter p(&pixmap[0]);
	drawHeader(p);
	p.end();
	drawBody();
	drawPageSummary();
	pagespinbox->setMaxValue(pixmap.size());
    }
	*/
}
