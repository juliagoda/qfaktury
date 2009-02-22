#ifndef Podglad_H
#define Podglad_H
#include <QDialog>
#include <QProcess>
#include <QScrollArea>

#include "tabletemp.h"

#include "ui_Podglad.h"

class Podglad: public QDialog, public Ui::Podglad {
    Q_OBJECT
    void init ();
    public:
    Podglad(QWidget *parent);

    	std::vector<QPixmap> pixmap_pdf;
    	std::vector<QPixmap> pixmap;
    	void setTableTemp( TableTemp & t,QString progdir2,QString retrn );

    public slots:
    private:
    	bool visibleColumns[14];
    	QString ret;
    	QString progDir2;
    	QProcess *cmd3;
    	int margTop,margDown,margLeft,margRight;
    	TableTemp tabletemp;
    	bool makePdf;
    	unsigned int scale;
    	float pageMargLeft,pageMargTop,pageMargRight,pageMargDown;
    	float xrate,yrate;
    	int countPos;
    	QScrollArea *view;
    	QLabel *label;
    	int sizeColumns[14];
    	int leftColumns[15];
    	void makePixmap();
};
#endif
