#include <QApplication>
#include "objparser.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    objParser m("syz.obj");
    m.show();
    return a.exec();
}
