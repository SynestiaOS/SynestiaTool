#include "synestiatool.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SynestiaTool w;
    w.show();
    return a.exec();
}
