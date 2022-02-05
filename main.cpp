#include "BaiLan.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BaiLan w;
    w.show();
    return a.exec();
}
