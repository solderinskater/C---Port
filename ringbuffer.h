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

#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <QtCore>

class RingBuffer {
public:
    RingBuffer(int size=10) : buf(size)
    {
        tail = 0;
    }

    void resize(int size)
    {
        buf.resize(size);
        tail = 0;
    }

    bool isFilled() const { return tail>=buf.size(); }

    void add(QList<int> sample)
    {
        buf[tail%buf.size()] = sample;
        tail++;
    }
    void print() const
    {
        qDebug() << buf;
    }

//    Matrix getBuffer() const
//    {
//        if(!isFilled())
//            return Matrix(buf.size()*buf[0].size(),1);

//        Matrix m(buf.size()*buf[0].size(),1);
//        int c=1;
//        for(int i=0; i<buf.size(); i++)
//            for(int j=0; j<buf[0].size(); j++) {
////                int bs = buf.size();
//                int ls = buf[(i+tail)%buf.size()].size();
//                if(ls!=buf[0].size())
//                    m(c++,1) = 0;
//                else
//                    m(c++,1) = buf[(i+tail)%buf.size()][j];
//            }
//        return m;
//    }

    QList<int> getChannel(int ch) {
        QList<int> v;

        for(int i=0; i<buf.size(); i++) {
            int idx = (i+tail)%buf.size();
            int t = buf[idx][ch];
            if(t>600)
                t = buf[idx-1][ch];;
            v << t;
        }
//        for(int i=0; i<buf.size(); i++)
//            v << buf[i].at(ch+1);
        return v;
    }

private:
    int tail;
    QVector<QList<int> > buf;
    bool m_isFilled;
};
#endif // RINGBUFFER_H
