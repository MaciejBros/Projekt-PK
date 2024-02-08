#include "mainwindow.h"
#include "board.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Board GmBrd(15,15);
    qDebug() << "Utworzono obiekt board\n";
    MainWindow w(GmBrd);
    w.show();
    return a.exec();
}
