#include <KAboutData>
#include <KLocalizedString>
#include <QApplication>
#include <QCommandLineParser>
#include <QDesktopWidget>
#include <QResource>
#include <QSplashScreen>
#include <QStyle>
#include <QTimer>

#include "MainWindow.h"
#include "Settings.h"

int main(int argc, char **argv) {
  QApplication a(argc, argv);

  KLocalizedString::setApplicationDomain("mainwindow_ui");

  KAboutData aboutData(
      // The program name used internally. (componentName)
      QStringLiteral("mainwindow_ui"),
      // A displayable program name string. (displayName)
      QString("QFaktury"),
      // The program version string. (version)
      sett().getVersion(qAppName()),
      // Short description of what the app does. (shortDescription)
      QString("Aplikacja do zarządzania fakturami"),
      // The license this code is released under
      KAboutLicense::GPL,
      // Copyright Statement (copyrightStatement = QString())
      QString("(c) 2017"),
      // Optional text shown in the About box.
      // Can contain any information desired. (otherText)
      QString("QFaktury to darmowy system fakturujący, pracujący w systemach "
              "Linux. Umożliwia on drukowanie faktur, faktur pro forma, "
              "rachunków, korekt i duplikatów. Umożliwia zarządzanie bazą "
              "faktur, towarów i kontrahentów."),
      // The program homepage string. (homePageAddress = QString())
      QString("https://github.com/juliagoda/qfaktury"),
      // The bug report email address
      // (bugsEmailAddress = QLatin1String("submit@bugs.kde.org")
      QString("https://github.com/juliagoda/qfaktury/issues"));
  aboutData.addAuthor(
      QString("Jagoda \"juliagoda\" Górska"), QString("Programista"),
      QStringLiteral("juliagoda.de@gmail.com"),
      QStringLiteral("https://github.com/juliagoda"), QStringLiteral(""));
  aboutData.addAuthor(QString("Piotr \"sir_lucjan\" Górski"),
                      QString("Tester w środowisku Arch Linux"),
                      QStringLiteral("lucjan.lucjanov@gmail.com"),
                      QStringLiteral("https://github.com/sirlucjan"),
                      QStringLiteral(""));
  aboutData.addAuthor(QString("Paweł \"pavbaranov\" Baranowski"),
                      QString("Tester w środowisku Arch Linux"),
                      QStringLiteral(""),
                      QStringLiteral("http://linux-pavbaranov.blogspot.in"),
                      QStringLiteral(""));
  KAboutData::setApplicationData(aboutData);

  QCommandLineParser parser;
  parser.addHelpOption();
  parser.addVersionOption();
  aboutData.setupCommandLine(&parser);
  parser.process(a);
  aboutData.processCommandLine(&parser);

  // sets language from file chosen in "translations" directory
  a.installTranslator(sett().getTranslation());

  QResource::registerResource(
      "qfaktury.rcc"); // using the rcc file so it's more portable
  // Q_INIT_RESOURCE(qfaktury);

  // gets geometry of the screen
  QRect screen = QApplication::desktop()->screenGeometry();

  // sets start window during application load
  QSplashScreen splash(QPixmap(":/res/icons/splash.png"));

  // creates instance of main window and move it in according to the screen
  // geometry
  MainWindow *w = new MainWindow;
  w->move(screen.center() - QPoint(w->width() / 2, w->height() / 2));

  // if argument for app in commandd line is --nosplash, uses no start window
  if (a.arguments().contains("--nosplash")) {
    w->show();
  } else {

    // else uses start window
    splash.show();

    a.processEvents();

    // when start window should to start
    QTimer *showSplash = new QTimer();
    a.connect(showSplash, SIGNAL(timeout()), w, SLOT(show()));

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
  icon.addPixmap(QPixmap(":/res/icons/qfaktury_48.png"), QIcon::Normal,
                 QIcon::Off);
  a.setWindowIcon(icon);
  a.setApplicationName("QFaktury");
  a.setOrganizationName("https://github.com/juliagoda/qfaktury");
  a.setApplicationVersion(sett().getVersion(qAppName()));
  a.setStyle(sett().getStyle());

  int ret = a.exec();

  if (w != 0)
    w = 0;
  delete w;

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
