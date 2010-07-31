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

#include "trickdetector.h"

TrickDetector* TrickDetector::instance()
{
    static TrickDetector* inst = 0;
    if(!inst)
        inst = new TrickDetector;
    return inst;
}

TrickDetector::TrickDetector(QObject *parent) :
        QObject(parent), W(100,1), m_isInit(false), buffer(10)
{
    bias = 4.0;
}

void TrickDetector::init(QList<double> weightVector)
{
    W.ReSize(weightVector.size(), 1);
    int i=1;
    foreach(double v, weightVector)
    {
        W(i++,1) = v;
    }
    m_isInit = true;
}

void TrickDetector::addSample(QString smp)
{
    if(!m_isInit)
    {
        qDebug("[TrickDetector] Set a weight vector first!");
        return;
    }

    QStringList s = smp.split(",");
    QList<double> d;
    foreach(QString str, s)
        d << str.toDouble();

    buffer.add(d);

    if(buffer.isFilled())
        classify();
}

void TrickDetector::classify()
{
    Matrix data = buffer.getBuffer();
    RowVector v = data.Row(1);
    double score = (W.Row(1)*data.Row(1).t()).AsScalar() + bias;
    if(score>0) {
        qDebug()<<score;
        emit trickEvent("Ollie",0);
    }
}
