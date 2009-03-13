#include <QApplication>
#include "MainWindow.h"

// do splasha
#include <QLabel>
#include <QTimer>
#include <QResource>
#include <QDir>
#include <QDesktopWidget>
#include <QSplashScreen>
#include <QWaitCondition>

int main(int argc, char **argv) {
	QApplication a(argc, argv);

	QResource::registerResource("qfaktury.rcc"); // using the rcc file so it's more portable
	// Q_INIT_RESOURCE(qfaktury);

	QSplashScreen splash(QPixmap(":/res/icons/splash.png"));
	splash.show();

	a.processEvents();

	QRect screen = QApplication::desktop()->screenGeometry();

	MainWindow w(0);

	w.move(screen.center() - QPoint(w.width() / 2, w.height() / 2));

	QTimer *showSplash = new QTimer();
	a.connect(showSplash, SIGNAL(timeout()), &w, SLOT(show()));

	QTimer *closeSplash = new QTimer();
	a.connect(closeSplash, SIGNAL(timeout()), &splash, SLOT(close()));

	showSplash->start(5000);
	closeSplash->start(4960);

	a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));
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

