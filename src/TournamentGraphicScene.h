#ifndef TOURNAMENTGRAPHICSCENE_H
#define TOURNAMENTGRAPHICSCENE_H

#include <QGraphicsScene>

class Tournament;
class Player;

class TournamentGraphicScene : public QGraphicsScene
{
  public:
    TournamentGraphicScene(Tournament *tournament);

  signals:
    void itemClicked(Player *player);

  private slots:
    void requestUpdate();

  private:
    Tournament *m_Tournament = Q_NULLPTR;
    int m_MatchWidgetWidth = 240;
    int m_MatchWidgetHeight = 120;
    int m_RowSpacing = 10;
    int m_ColumnSpacing = 150;

    void init();

    // QGraphicsScene interface
  protected:
    void drawBackground(QPainter *painter, const QRectF &rect) override;
};

#endif  // TOURNAMENTGRAPHICSCENE_H
