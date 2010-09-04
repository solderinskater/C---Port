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

#ifndef DTW_H
#define DTW_H

#include <QList>
#include <QVector>

struct DTWResult
{
    float distance;
    QVector<QVector<int> > D;
};

class DTW
{
public:
    DTW();

    DTWResult classify(const QList<int> &templ, const QList<int> &observation);

    inline void init_int_array(int *a, int num_rows, int num_cols, int val)
    {
       int i;

       for( i = 0; i < num_rows * num_cols; i++)
          *(a + i) = val;
    }

};

#endif // DTW_H
