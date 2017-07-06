#include "widget.h"
#include"screen.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
 //   Screen s;
    w.show();
  //  s.show();

    return a.exec();
}
