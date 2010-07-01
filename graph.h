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

#ifndef GRAPH_H
#define GRAPH_H

#include <QtGui>


class Graph : public QWidget {
    Q_OBJECT

public:
    explicit Graph(QWidget * parent);
    ~Graph();

    void setYMinMax(qreal ymin, qreal ymax);
    void setXRange(qreal xrange);

    qreal xRange() const  { return m_xrange; }
    qreal yRange() const  { return m_ymax - m_ymin; }
    qreal yMin() const    { return m_ymin; }
    qreal yMax() const    { return m_ymax; }

    void setRenderHints(QPainter::RenderHints hints);

public Q_SLOTS:
    virtual void addPoint(const QPointF &data);
    virtual void clear();

protected:
    virtual void paintEvent(QPaintEvent *e);

private:
    void drawValues(QPainter * painter);

    qreal m_ymin;
    qreal m_ymax;
    qreal m_xrange;
    qreal m_scroll_error;

    QPainter::RenderHints m_render_hints;

    QList<QPointF> m_values;
};


#endif // GRAPH_H
