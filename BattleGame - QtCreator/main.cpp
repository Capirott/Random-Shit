#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include "mainwindow.h"
#include <QApplication>
#include "configdialog.h"

using namespace std;
int main(int argc, char *argv[])
{
//    srand(time(0));
    QApplication a(argc, argv);
    ConfigDialog w;
    w.show();
    a.exec();
    return 0;
}

