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

#include <qpainter.h>
#include <qpixmap.h>

#include <qscrollview.h>
#include <qvbox.h>
#include <qlabel.h>

#include <qtoolbar.h>

void
preview::init ()
{
  QBoxLayout *l = new QHBoxLayout (this);
  l->setAutoAdd (TRUE);

  QScrollView *sv = new QScrollView (this);
  // sv->resize(size());
  QLabel *pixaaa = new QLabel (sv);
  pixaaa->setPixmap (QPixmap ("/tmp/przelew.png"));
  sv->addChild (pixaaa);
}
