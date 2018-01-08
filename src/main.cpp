#include "MainWindow.h"
#include "Settings.h"

#include <QApplication>
#include <QResource>
#include <QSplashScreen>
#include <QStyle>
#include <QCommandLineParser>

int main(int argc, char **argv) {

  QT_REQUIRE_VERSION(argc, argv, "5.10.0");

  qDebug() << "[" << __FILE__ << ": " << __LINE__ << "] " << __FUNCTION__;

  QApplication a(argc, argv);

  // sets language from file chosen in "translations" directory
  a.installTranslator(sett().getTranslation());

  // creates instance of main window and move it in according to the screen
  // geometry
  MainWindow w;
  w.setWindowState(Qt::WindowMaximized);

  QCommandLineParser* parser = new QCommandLineParser;
  parser->addHelpOption();
  parser->addVersionOption();
  parser->setApplicationDescription("QFaktury");
  QCommandLineOption noSplashOption("nosplash", QCoreApplication::translate("nosplash", "Blokuje widok splash przy starcie programu"));
  parser->addOptions({
                        noSplashOption
          });

  parser->process( a );


  // if argument for app in commandd line is --nosplash, uses no start window
  if (!parser->isSet(noSplashOption)) {

      // sets start window during application load
      QSplashScreen splash(QPixmap(":/res/icons/splash.png"));

    // else uses start window
    splash.show();

    if (!splash.isVisible()) qDebug() << "QSplash hadn't been visible";
    if (splash.isHidden()) splash.show();

    a.processEvents();

    splash.showMessage("Ładowanie danych", Qt::AlignBaseline, Qt::white);

    bool registered = QResource::registerResource(
    "qfaktury.rcc");

    if (!registered) {
        QResource resource("qfaktury.rcc");
        if (!resource.isValid()) qDebug() << "resources file " << resource.fileName() << " is not valid";
        if (resource.size() == 0) qDebug() << "resources file " << resource.fileName() << " is empty";
    }

    splash.showMessage("Ładowanie zasobów", Qt::AlignBaseline, Qt::white);

    splash.finish(&w);

    w.show();
    if (w.isActiveWindow()) a.setActiveWindow(&w);
    if (!w.hasFocus()) w.setFocus();

    a.alert(&w,0);

  }

  // if last window is close, closes down application
  a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));
  w.connect(&w, &MainWindow::destroyed, &a, &QApplication::closeAllWindows);
  // sets icon, application name, organization name and style for app
  QIcon icon;
  icon.addPixmap(QPixmap(":/res/icons/qfaktury_48.png"), QIcon::Normal,
                 QIcon::Off);
  a.setWindowIcon(icon);
  a.setApplicationName("QFaktury");
  a.setOrganizationName("https://github.com/juliagoda/qfaktury");
  a.setApplicationVersion(sett().getVersion(qAppName()));
  a.setStyle(sett().getStyle());

  if( parser->isSet("lang") ) {
      QLocale::setDefault( QLocale( parser->value("lang") ) );
  }

  return a.exec();
}
