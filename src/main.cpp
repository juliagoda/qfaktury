#include "MainWindow.h"
#include "Settings.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QResource>
#include <QSplashScreen>
#include <QStyle>
#include <QTimer>

int main(int argc, char **argv) {

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  QApplication *a = new QApplication(argc, argv);

  // sets language from file chosen in "translations" directory
  a->installTranslator(sett().getTranslation());

  QResource::registerResource(
      "qfaktury.rcc"); // using the rcc file so it's more portable
  // Q_INIT_RESOURCE(qfaktury);

  // gets geometry of the screen
  QRect screen = QApplication::desktop()->screenGeometry();

  // sets start window during application load
  QSplashScreen splash(QPixmap(":/res/icons/splash.png"));

  // creates instance of main window and move it in according to the screen
  // geometry
  MainWindow *w = new MainWindow();
  w->move(screen.center() - QPoint(w->width() / 2, w->height() / 2));

  QTimer *showSplash = new QTimer();
  QTimer *closeSplash = new QTimer();

  // if argument for app in commandd line is --nosplash, uses no start window
  if (a->arguments().contains("--nosplash")) {
    w->show();
  } else {

    // else uses start window
    splash.show();

    a->processEvents();

    // when start window should to start
    a->connect(showSplash, SIGNAL(timeout()), w, SLOT(show()));

    // when start window should to be closed
    a->connect(closeSplash, SIGNAL(timeout()), &splash, SLOT(close()));

    // start of signals
    showSplash->start(5000);
    closeSplash->start(4960);
  }

  // if last window is close, closes down application
  a->connect(a, SIGNAL(lastWindowClosed()), a, SLOT(quit()));

  // sets icon, application name, organization name and style for app
  QIcon icon;
  icon.addPixmap(QPixmap(":/res/icons/qfaktury_48.png"), QIcon::Normal,
                 QIcon::Off);
  a->setWindowIcon(icon);
  a->setApplicationName("QFaktury");
  a->setOrganizationName("https://github.com/juliagoda/qfaktury");
  a->setApplicationVersion(sett().getVersion(qAppName()));
  a->setStyle(sett().getStyle());

  int ret = a->exec();

  delete w;
  delete a;
  delete showSplash;
  delete closeSplash;

  return ret;
}

#ifdef WIN32
#if CMAKE_BUILD_TYPE == Release
#include <windows.h>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) {
  main(0, 0);
}
#endif
#endif
