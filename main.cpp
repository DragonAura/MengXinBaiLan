#include "total.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameStart start;
    start.show();
    start.exec();
    if (start.ok == true)
    {
        BaiLan w;
        w.show();
        return a.exec();
    }
    else
    {
        return 0;
    }
}
