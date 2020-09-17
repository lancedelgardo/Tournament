#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "Tournament.h"
#include "RoundWidget.h"
#include "GraphicsItem.h"
#include "TournamentGraphicScene.h"
#include "GraphicsView.h"
#include "Settings.h"


#include <QTimer>
#include <QDebug>

// TODO
// Fehler bei Anzahl Spieler: 3,5,7

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Settings *s = Settings::instance();

    t = new Tournament(this);
    for (int i = 0; i < 13; i++)
    {
        t->addPlayer(new Player("Spieler " + QString::number(i + 1)));
    }
    t->init();
    t->start();

    GraphicsView *view = new GraphicsView(new TournamentGraphicScene(t), this);
    view->show();
    ui->centralwidget->layout()->addWidget(view);
}

MainWindow::~MainWindow() { delete ui; }
