#include "TournamentGraphicScene.h"

#include "Tournament.h"
#include "MatchWidgetForm.h"
#include "GraphicsItem.h"

#include <QMap>
#include <QList>
#include <QGraphicsItem>
#include <QDebug>
#include <QGraphicsProxyWidget>
#include <QPainter>

TournamentGraphicScene::TournamentGraphicScene(Tournament *tournament)
{
    m_Tournament = tournament;
    connect(m_Tournament, &Tournament::requestUpdate, this, &TournamentGraphicScene::requestUpdate);
    init();
}

void TournamentGraphicScene::requestUpdate() { update(); }

void TournamentGraphicScene::init()
{
    auto rounds = m_Tournament->getRounds();
    if (rounds.isEmpty()) return;
    int nRounds = rounds.size();
    int tmp = rounds.first()->nMatches();
    if (tmp != 1 && tmp % 2 != 0) tmp++;

    int totalHeight = tmp * m_MatchWidgetHeight + (tmp - 1) * m_RowSpacing;

    setSceneRect(-100, -100, nRounds * m_MatchWidgetWidth + (nRounds - 1) * m_ColumnSpacing + 200, totalHeight + m_RowSpacing + 200);

    QPen pen(Qt::black);
    QBrush brush(QColor(32, 32, 32));

    QList< QGraphicsItem * > previousRoundItems;
    QMap< Match *, QGraphicsItem * > items;
    for (int i = 0; i < rounds.size(); i++)
    {
        QList< QGraphicsItem * > roundItems;
        qDebug() << "Round " << i + 1;
        auto matches = rounds[i]->getMatches();

        int x = i * (m_MatchWidgetWidth + m_ColumnSpacing);
        for (int j = 0; j < matches.size(); j++)
        {
            auto match = matches[j];

            int y = j * (m_MatchWidgetHeight + m_RowSpacing);

            auto pm1 = match->getPreviousMatch1();
            if (pm1)
            {
                auto pi0 = previousRoundItems[0];
                auto pi1 = previousRoundItems[1];
                auto y0 = pi0->mapToScene(pi0->boundingRect().bottomLeft()).y();  // Unterkante
                auto y1 = pi1->mapToScene(pi1->boundingRect().topLeft()).y();     // Oberkante

                auto dist = y1 - y0;

                auto item1 = items[pm1];
                auto bb1 = item1->boundingRect();
                auto br1 = item1->mapToScene(bb1.bottomRight());

                auto px0 = br1.x();
                auto py0 = br1.y() - m_MatchWidgetHeight * 0.5;
                auto px1 = px0 + m_ColumnSpacing * 0.5;
                auto py1 = py0;
                auto px2 = px1;
                auto py2 = br1.y() + dist * 0.5;
                auto px3 = px2 + m_ColumnSpacing * 0.5;
                auto py3 = py2;
                auto px4 = px2;
                auto py4 = py2 + (py2 - py1);
                auto px5 = px0;
                auto py5 = py4;

                y = py3 - m_MatchWidgetHeight * 0.5;

                if (py2 > totalHeight)  // In some cases the lowest widget is outbound at bottom.
                {
                    addLine(px0, py0, px1, py1, pen);
                    int tmp = m_MatchWidgetHeight + m_ColumnSpacing * 0.5;
                    py2 -= tmp;
                    py3 -= tmp;
                    y -= tmp;
                    addLine(px1, py1, px2, py2, pen);
                    addLine(px2, py2, px3, py3, pen);
                }
                else
                {
                    addLine(px0, py0, px1, py1, pen);
                    addLine(px1, py1, px2, py2, pen);
                    addLine(px2, py2, px3, py3, pen);
                }

                if (match->getPreviousMatch2())
                {
                    addLine(px5, py5, px4, py4, pen);
                    addLine(px4, py4, px2, py2, pen);
                }
            }

            //            MatchWidgetForm *mw = new MatchWidgetForm(match);
            //            mw->setFixedSize(m_MatchWidgetWidth, m_MatchWidgetHeight);
            //            auto item = addWidget(mw);
            //            item->setPos(x, y);
            //            roundItems.append(item);
            //            items.insert(match, item);


            GraphicsItem *graphicsItem = new GraphicsItem(QRectF(0, 0, m_MatchWidgetWidth, m_MatchWidgetHeight), match);
            //            auto item = addWidget(graphicsItem);
            graphicsItem->setPos(x, y);
            roundItems.append(graphicsItem);
            items.insert(match, graphicsItem);
            addItem(graphicsItem);
        }

        auto textItem = addText(rounds[i]->getName(), QFont("sans", 16, 2));
        textItem->moveBy(x - 5 + (m_MatchWidgetWidth + 10 - textItem->boundingRect().width()) * 0.5, -30);
        textItem->setZValue(1);


        QPainterPath path;
        path.addRoundedRect(x - 5, -30, m_MatchWidgetWidth + 10, totalHeight + 35, 10, 10);
        //        auto rectItem = addRect(x - 5, -30, m_MatchWidgetWidth + 10, totalHeight + 35, pen, brush);
        QGraphicsPathItem *rectItem = new QGraphicsPathItem(path);
        rectItem->setZValue(-1);
        rectItem->setOpacity(0.5);
        rectItem->setPen(pen);
        rectItem->setBrush(brush);
        addItem(rectItem);

        previousRoundItems.clear();
        previousRoundItems.append(roundItems);
    }
}


void TournamentGraphicScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    QLinearGradient linearGrad(rect.topLeft(), rect.bottomRight());
    linearGrad.setColorAt(0, QColor("#024C62"));
    linearGrad.setColorAt(0.2, QColor("#024C62"));
    linearGrad.setColorAt(0.4, QColor("#04627F"));
    linearGrad.setColorAt(0.6, QColor("#0394C0"));
    linearGrad.setColorAt(0.8, QColor("#04627F"));
    linearGrad.setColorAt(1, QColor("#024C62"));
    //    QRect rect_linear(50, 50, 200, 200);
    painter->fillRect(rect, linearGrad);
}
