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

#include "DTW/dtw.h"
#include <math.h>

DTW::DTW()
{
}

DTWResult DTW::classify(QList<int> templ, QList<int> observation)
{
    DTWResult res;
    qint16 N = templ.size();
    qint16 M = observation.size();
    QVector<QVector<int> > d(N);
    QVector<QVector<int> > D(N);

    //init_int_array(D, N, M, 0);

    for(int n=0; n<N; n++) {
        d[n].resize(M);
        D[n].resize(M);
        D[n].fill(0);

        for(int m=0; m<M; m++)
            d[n][m]= (qint32)pow((long double)(templ[n] - observation[m]), 2); //(t(n)-r(m))^2;
   }

    D[0][0] = d[0][0];

    for(int n=1; n<N; n++)
        D[n][0] = d[n][0] + D[n-1][0];  // D(n,1)=d(n,1)+D(n-1,1);

    for(int m=1; m<M; m++)
        D[0][m] = d[0][m] + D[0][m-1];  // D(1,m)=d(1,m)+D(1,m-1);


    for(int n=1; n<N; n++)
        for(int m=1; m<M; m++)
            D[n][m] = d[n][m] + qMin(qMin(D[n-1][m], D[n-1][m-1]), D[n][m-1]);

    res.distance = D[N-1][M-1];
    res.D = D;
    return res;
    /* nice to have: reconstruction of path with backtracing. But so far, only distance will be used as measure */
}

