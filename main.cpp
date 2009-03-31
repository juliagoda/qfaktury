#include <QApplication>
#include <QTimer>
#include <QResource>
#include <QDesktopWidget>
#include <QSplashScreen>
#include <QTranslator>
#include <QWaitCondition>

#include "MainWindow.h"
#include "Settings.h"

// do splasha

int main(int argc, char **argv) {
	QApplication a(argc, argv);


	// multilangage
    a.installTranslator(sett().getTranslation());


	QResource::registerResource("qfaktury.rcc"); // using the rcc file so it's more portable
	// Q_INIT_RESOURCE(qfaktury);


	QRect screen = QApplication::desktop()->screenGeometry();

	QSplashScreen splash(QPixmap(":/res/icons/splash.png"));

	MainWindow w(0);
	w.move(screen.center() - QPoint(w.width() / 2, w.height() / 2));


	if (a.arguments().contains("--nosplash")) {
		w.show();
	} else {
		splash.show();

		a.processEvents();

		QTimer *showSplash = new QTimer();
		a.connect(showSplash, SIGNAL(timeout()), &w, SLOT(show()));

		QTimer *closeSplash = new QTimer();
		a.connect(closeSplash, SIGNAL(timeout()), &splash, SLOT(close()));

		showSplash->start(5000);
		closeSplash->start(4960);
	}

	a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));

	QIcon icon;
	icon.addPixmap(QPixmap(":/res/icons/qfaktury_48.png"), QIcon::Normal, QIcon::Off);
	a.setWindowIcon(icon);
	a.setApplicationName("QFaktury");
	a.setOrganizationName("www.e-linux.pl");
	return a.exec();
}

#ifdef WIN32
#if CMAKE_BUILD_TYPE == Release
#include <windows.h>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
		LPSTR lpCmdLine, int nCmdShow) {
	main(0,0);
}
#endif
#endif

