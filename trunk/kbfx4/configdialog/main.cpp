#include <QApplication>
#include <QTranslator>

#include "kbfx_main.h"
//include "dlglogin.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

	QString locale = QLocale::system().name();

	QTranslator translator;
  translator.load("trans/" + QString("kbfxconf_") + locale);
  app.installTranslator(&translator);

	QCoreApplication::setOrganizationName("KBFX");
  QCoreApplication::setOrganizationDomain("kbfx.com");
  QCoreApplication::setApplicationName("KBFX Configurator");

  dlgMain *l = new dlgMain();
  l->show();

  return app.exec();
}


 
