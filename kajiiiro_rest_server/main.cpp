#include <QtGui/QApplication>
#include "kajiiiro_rest_server.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    kajiiiro_rest_server w;
    w.show();
    
    return a.exec();
}
