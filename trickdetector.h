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

#ifndef TRICKDETECTOR_H
#define TRICKDETECTOR_H

#include <QtCore>
//#include <newmat/newmatap.h>
#include <DTW/dtw.h>
#include "ringbuffer.h"



/// Singleton class.
class TrickDetector : public QObject
{
    Q_OBJECT

public:
    static TrickDetector* instance();
    void init();

signals:
    void trickEvent(QString);

public slots:
    void addSample(QString);

protected:
    TrickDetector(QObject *parent = 0);
    void classify();

private:
    DTW dtw;
    RingBuffer buffer;
    double bias;
    int curSmp;
    int trickLength;
    QList<int> neutral_pattern;
};

#endif // TRICKDETECTOR_H
