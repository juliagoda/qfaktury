#ifndef Podglad_H
#define Podglad_H
#include <QDialog>
#include <QProcess>
#include <QScrollArea>
#include <QVector>
#include <QFileInfo>
#include <QFileDialog>
#include <QMessageBox>

#include "tabletemp.h"
#include "Settings.h"
#include "config.h"

#include "ui_Podglad.h"

class Podglad: public QDialog, public Ui::Podglad {
    Q_OBJECT
    void init ();
    public:
    Podglad(QWidget *parent);

    	QVector<QPixmap> pixmap_pdf;
    	QVector<QPixmap> pixmap;
    	void setTableTemp( TableTemp & t,QString progdir2,QString retrn );

    public slots:
    // void scroolChanged( int );
    // void exportPdf();
    // void pdfFinished();
    void drawHeader( QPainter & p );
    void drawPageSummary();
    // void exportHtml();
    void printPages();
    // void canCel();
    void drawBody();
    // void destroy();
    void exportJpg();

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
    	// QScrollArea *view;
    	QLabel *label;
    	int sizeColumns[14];
    	int leftColumns[15];
    	void makePixmap();
    	void setVisibleColumn();
    	Settings settings;
};
#endif
