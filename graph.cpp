/* 
Copyright 2010 Keywan Tonekaboni, Florian Fusco, Stefanie Schirmer, Alexander Lenhardt, Erik Weitnauer <eweitnauer at gmail.com>

This file is part of Soldering Skaters Nokia Push Project.

Soldering Skaters Nokia Push Project is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Soldering Skaters Nokia Push Project is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Soldering Skaters Nokia Push Project. If not, see <http://www.gnu.org/licenses/>.
*/

#include "graph.h"
#include <QtCore/QDebug>
#include <QStandardItemModel>
#include <QtGui>

#include <QDebug>


Graph::Graph(QWidget * parent)
    : QWidget(parent),
    m_ymin(-1), m_ymax(1), m_xrange(1), m_scroll_error(0), m_render_hints(0)
{
    setAttribute(Qt::WA_OpaquePaintEvent);
}

Graph::~Graph()
{
}

void Graph::setYMinMax(qreal ymin, qreal ymax)
{
    m_ymin = ymin;
    m_ymax = ymax;
    m_scroll_error = 0;
    update();
}

void Graph::setXRange(qreal xrange)
{
    m_xrange = xrange;
    m_scroll_error = 0;
    update();
}

void Graph::setRenderHints(QPainter::RenderHints hints)
{
    m_render_hints = hints;
    m_scroll_error = 0;
    update();
}


void Graph::addPoint(const QPointF &value)
{
    QPointF oldval;

    if (!m_values.isEmpty())
        oldval = m_values.last();

    if (!oldval.isNull() && value.x() < oldval.x()) {
        qWarning("Graph::addPoint(): the new point's x value is less than the last point's x value.");
        return;
    }

    m_values << value;

    if (!oldval.isNull()) {
        qreal deltaf = width() * ((value.x() - oldval.x()) / m_xrange);
        int delta = (int) deltaf;
        m_scroll_error += (deltaf - qreal(delta));

        if (m_scroll_error > qreal(1.0)) {
            m_scroll_error--;
            delta++;
        }

        if (delta < width()) {
            scroll(-delta, 0);
            update(width() - delta - 3, 0, delta + 3, height());
        } else {
            m_scroll_error = 0;
            update();
        }

        // purge old data
        qreal left = value.x() - m_xrange;

        int i;
        for (i = 0; i < m_values.size(); ++i) {
            if (m_values[i].x() > left)
                break;
        }
        i--;

        if (i > 0 && i < (m_values.size() - 1))
            m_values.erase(m_values.begin(), m_values.begin() + i);

  }
}

void Graph::clear()
{
    m_values.clear();
    m_scroll_error = 0;
    update();
}

void Graph::paintEvent(QPaintEvent *e)
{
    QPainter p(this);

    if (m_render_hints)
        p.setRenderHints(m_render_hints);

    p.fillRect(e->rect(), palette().background());

    if (m_values.size() < 2)
        return;

    p.setPen(palette().color(QPalette::Text));

    qreal scalex = qreal(width()) / m_xrange;
    qreal scaley = qreal(height()) / (m_ymax - m_ymin);

    qreal dx = qreal(3) / scalex;
    qreal dy = qreal(3) / scaley;

    QRectF bound(e->rect().x() / scalex, m_ymin + e->rect().y() / scaley, e->rect().width() / scalex, e->rect().height() / scaley);

    QPointF last = m_values.last();

    qreal tx = m_xrange - last.x();
    qreal ty = m_ymin;


    p.scale(scalex, -scaley);
    p.translate(tx, ty);

    QVarLengthArray<QLineF> lines;

    for (int i = m_values.size() - 1; i >= 0; --i) {
        QPointF pt = m_values[i];
        QRectF linerect(last, pt);
        linerect = linerect.normalized().translated(tx, 0);
        linerect.adjust(-dx, -dy, dx, dy);

        if (bound.intersects(linerect))
            lines.append(QLineF(last, pt));
        last = pt;
    }

//    if (lines.size() < (m_values.size()-1))
//        qWarning("skipped %d lines", (m_values.size()-1) -lines.size());

    p.drawLines(lines.constData(), lines.size());
}


