#include "linechart.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LineChart w;
    w.show();
    return a.exec();
}
