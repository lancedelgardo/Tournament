#ifndef TOURNAMENTGRAPHICSCENE_H
#define TOURNAMENTGRAPHICSCENE_H

#include <QGraphicsScene>

class Tournament;
class Player;
class Match;

class TournamentGraphicScene : public QGraphicsScene
{
    Q_OBJECT
  public:
    TournamentGraphicScene(Tournament *tournament);

  signals:
    void itemClicked(Match *match, Player *winner);

  private slots:
    void requestUpdate();
    void onItemClicked(Match *match, Player *winner);

  private:
    Tournament *m_Tournament = Q_NULLPTR;
    int m_MatchWidgetWidth = 240;
    int m_MatchWidgetHeight = 120;
    int m_RowSpacing = 10;
    int m_ColumnSpacing = 150;

    QColor backgroundColor1 = QColor("#024C62");
    QColor backgroundColor2 = QColor("#024C62");
    QColor backgroundColor3 = QColor("#04627F");
    QColor backgroundColor4 = QColor("#0394C0");
    QColor backgroundColor5 = QColor("#04627F");
    QColor backgroundColor6 = QColor("#024C62");

    QColor roundsBorderColor = QColor(0, 0, 0);
    QColor roundsBackgroundColor = QColor(0, 0, 0);
    QColor roundsLineColor = QColor(0, 0, 0);

    void init();

    // QGraphicsScene interface
  protected:
    void drawBackground(QPainter *painter, const QRectF &rect) override;
};

#endif  // TOURNAMENTGRAPHICSCENE_H
