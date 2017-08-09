#include <QApplication>
#include <QTimer>
#include <QResource>
#include <QDesktopWidget>
#include <QSplashScreen>
#include <QTranslator>
#include <QStyle>

#include "MainWindow.h"


int main(int argc, char **argv) {
	QApplication a(argc, argv);



	QResource::registerResource("qfaktury.rcc"); // using the rcc file so it's more portable
	// Q_INIT_RESOURCE(qfaktury);

    // gets geometry of the screen
	QRect screen = QApplication::desktop()->screenGeometry();

    // sets start window during application load
    QSplashScreen splash(QPixmap(":/res/icons/splash.png"));\

    // creates instance of main window and move it in according to the screen geometry
	MainWindow w(0);
	w.move(screen.center() - QPoint(w.width() / 2, w.height() / 2));

    // if argument for app in commandd line is --nosplash, uses no start window
	if (a.arguments().contains("--nosplash")) {
		w.show();
	} else {

    // else uses start window
		splash.show();

		a.processEvents();

        // when start window should to start
		QTimer *showSplash = new QTimer();
		a.connect(showSplash, SIGNAL(timeout()), &w, SLOT(show()));

        // when start window should to be closed
		QTimer *closeSplash = new QTimer();
		a.connect(closeSplash, SIGNAL(timeout()), &splash, SLOT(close()));

        // start of signals
		showSplash->start(5000);
		closeSplash->start(4960);
	}

    // if last window is close, closes down application
	a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));

    // sets icon, application name, organization name and style for app
	QIcon icon;
	icon.addPixmap(QPixmap(":/res/icons/qfaktury_48.png"), QIcon::Normal, QIcon::Off);
	a.setWindowIcon(icon);
	a.setApplicationName("QFaktury");
    a.setOrganizationName("https://github.com/juliagoda/qfaktury");
    a.setApplicationVersion(sett().getVersion(qAppName()));
    a.setStyle(sett().getStyle());

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

