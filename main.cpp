#include "mainwindow.h"
#include "mainwindow.h"


#include <QApplication>


using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow *w = new MainWindow();
    w->show();



    return a.exec();
}
