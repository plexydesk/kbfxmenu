#include <QApplication>

#include "kbfx_main.h"
//include "dlglogin.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);


  dlgMain *l = new dlgMain();
  l->show();

  return app.exec();
}
