#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "MatchWidget.h"

#include <QMainWindow>
#include <QMap>

class Tournament;

QT_BEGIN_NAMESPACE namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

  private:
    Ui::MainWindow *ui;
    MatchWidget *mw3 = Q_NULLPTR;

    QMap< Match *, MatchWidget * > matchMap;

    Tournament *t;
};
#endif  // MAINWINDOW_H
