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
#include "trickmanager.h"

TrickDetector* TrickDetector::instance()
{
    static TrickDetector* inst = 0;
    if(!inst)
        inst = new TrickDetector;
    return inst;
}

TrickDetector::TrickDetector(QObject *parent) :
        QObject(parent), buffer(40),  bias(0), curSmp(0), trickLength(40)
{
    /* this is the no-trick template */
    QVector<int> tmp(trickLength);
    tmp.fill(380);
    neutral_pattern = tmp.toList();
}


void TrickDetector::addSample(QString smp) {
    QStringList s = smp.split(",");
    QList<int> d;
    if(s.size()<10) {   // workaround for missing numbers. lost during transmission
        for(int i=0;i<10;i++)
            d << 300;
    }
    else {
        for(int i=0;i<10;i++)
            d << (int)s[i].toDouble();
    }
    curSmp++;
    buffer.add(d);

    qDebug("ADD SAMPLE DETECTOR");

    if(buffer.isFilled())
        classify();
}

void TrickDetector::classify()
{
    static unsigned int refrac = 140;
    refrac++;
    QTime t;
    t.start();

    QList<int> chans;
    chans << 6<<7;
    QList<int> window;
    foreach(int ch, chans) {
        window.append(buffer.getChannel(ch));
    }
    QList<int> window2 = buffer.getChannel(1);

    /* performance tweak. only classify if we see a peak in channel 2 */
    QList<int> subwindow = window2.mid(0,15);
//    qSort(subwindow.begin(),subwindow.end());
    qDebug("CLassify PRE");
    if(subwindow.last()<430)
        return;
    qDebug("CLassify POST");


    DTWResult res = dtw.classify(neutral_pattern, window);
    int bestScore = (int)res.distance;
    QString bestMatch("");
    QList<int> scores;
    scores << bestScore;

    /* classify all trained tricks */
    TrickManager *tm = TrickManager::instance();
    foreach(QString name, tm->getTrickNames()) {
        res = dtw.classify(tm->getPattern(name), window);
        scores << (int)res.distance;
        if(res.distance<bestScore) {
            bestMatch = name;
            bestScore = (int)res.distance;
        }
    }


    if(refrac > 200) {
        if(!bestMatch.isEmpty() && bestScore < 100000) {
            emit trickEvent(bestMatch);
            qDebug() << "Trick: " << bestMatch << scores << curSmp-trickLength;
            refrac = 0;
        }
    }

//    qDebug() << "TIME: " << t.elapsed();
}

