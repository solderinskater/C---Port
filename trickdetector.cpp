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
#include <QtDebug>

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
    bias = 0.0;
}

void TrickDetector::init(QList<double> weightVector)
{
    W.ReSize(weightVector.size(), 1);
    buffer.resize(124);
    qDebug("W size: %d",weightVector.size());
    int i=1;
    foreach(double v, weightVector)
    {
        W(i++,1) = v;
    }
    m_isInit = true;
    curSmp = 0;
    buffer.resize(41);
}

void TrickDetector::addSample(QString smp)
{
    static RingBuffer buf(40);
    static double cnt = 0;
    if(!m_isInit)
    {
        qDebug("[TrickDetector] Set a weight vector first!");
        return;
    }

    QStringList s = smp.split(",");
    QList<int> d;

    if(s.size()<10) {   // workaround for missing numbers. lost during transmission
        for(int i=0;i<10;i++)
            d << 300;
    }
    else {
        for(int i=0;i<10;i++)
            d << s[i].toDouble();
    }
    curSmp++;
    buffer.add(d);


    if(buffer.isFilled()) {
        classify();
        Matrix m = buf.getBuffer();
        RowVector v;
        v = m.AsRow();
    }
}

void TrickDetector::classify()
{
    static unsigned int refrac = 0;
    Matrix data = buffer.getBuffer();
   // RowVector v = data.AsRow();
//    v -= v.Sum()/v.Nrows();
   // double score = DotProduct(W,v) + bias;

    QList<int> window = buffer.getChannel(8);

    QSettings s("SolderinSkaters", "TiltNRoll");
    QVariantList vtmpl = s.value("Tricks/180").toList();
    QList<int> tmpl;
    QVariantList vtmpl2 = s.value("Tricks/Ollie").toList();
    QList<int> tmpl2;
    foreach(QVariant v, vtmpl) {
        tmpl << v.toInt();
    }
    foreach(QVariant v, vtmpl2) {
        tmpl2 << v.toInt();
    }

    QVector<int> tmplNeutral(41);
    tmplNeutral.fill(370);

    DTWResult res = dtw.classify(tmpl, window);
    DTWResult res2 = dtw.classify(tmpl2, window);
    DTWResult res3 = dtw.classify(tmplNeutral.toList(), window);

    double score = res.distance;
    double ratio = (double)res.distance / res2.distance;
    double ratioInv = (double)res2.distance / res.distance;

    if(refrac > 140) {
        if(res3.distance< qMin(res.distance,res2.distance))
            ;//qDebug("N: %d / ScoreCorr: %.4f / ScoreFalse: %.4f / ScoreNeut: %.4f / Smp: %d  [Nothing]",1, res.distance,res2.distance,res3.distance,curSmp);
        else if(res.distance<res2.distance && res.distance <30000) {
            qDebug("N: %d / ScoreCorr: %.4f / ScoreFalse: %.4f / Smp: %d  [ShoveIt 180]",1, res.distance,res2.distance,curSmp);
            refrac = 0;
        }
        else if(res2.distance<res.distance && res2.distance <30000){
            qDebug("N: %d / ScoreCorr: %.4f / ScoreFalse: %.4f / Smp: %d  [Ollie]",1, res.distance,res2.distance,curSmp);
            refrac = 0;
        }

//        qDebug() << tmpl;
//        qDebug() << tmpl2;
//        qDebug() << window;
        emit trickEvent("Ollie");
    }

    refrac++;

}

