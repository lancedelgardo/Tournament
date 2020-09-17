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

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Settings::instance();  // INIT

    t = new Tournament(this);
    for (int i = 0; i < 13; i++)
    {
        t->addPlayer(new Player("Spieler " + QString::number(i + 1)));
    }
    t->init();
    t->start();

    TournamentGraphicScene *tgs = new TournamentGraphicScene(t);
    connect(tgs, SIGNAL(itemClicked(Match *, Player *)), this, SLOT(onMatchFinishedPerClick(Match *, Player *)));
    GraphicsView *view = new GraphicsView(tgs, this);
    view->show();
    ui->centralwidget->layout()->addWidget(view);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::onMatchFinishedPerClick(Match *match, Player *winner) { t->getCurrentRound()->finishMatch(match, winner); }


void MainWindow::closeEvent(QCloseEvent *event) { Settings::instance()->save(); }
