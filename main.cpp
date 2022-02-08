#include "total.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BaiLan w;
    w.InitGame();
    w.show();
    return a.exec();
}
