#include "MainWindow.h"

#include "Tournament.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    //    QList< Player * > players;
    //    Tournament t;
    //    for (int i = 0; i < 17; i++)
    //    {
    //        players.append(new Player("Spieler " + QString::number(i + 1)));
    //    }

    //    foreach (auto p, players)
    //    {
    //        t.addPlayer(p);
    //    }

    //    t.start();


    return a.exec();
}
