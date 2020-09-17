#ifndef GRAPHICSITEM_H
#define GRAPHICSITEM_H

#include <QObject>
#include <QGraphicsItem>

class Match;
class Player;

class GraphicsItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
  public:
    GraphicsItem(const QRectF pos, Match *match, QGraphicsItem *parent = nullptr);

  private:
    int m_PointsPlayer1 = 0;
    int m_PointsPlayer2 = 0;
    QString m_Player1 = "---";
    QString m_Player2 = "---";
    QRectF m_Pos;
    Match *m_Match = Q_NULLPTR;
    QRectF upperHalf;
    QRectF lowerHalf;

  signals:
    void clicked(Player *player);

  private slots:
    void requestUpdate();

    // QGraphicsItem interface
  public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // QGraphicsItem interface
  protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    // QGraphicsItem interface
  protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif  // GRAPHICSITEM_H
