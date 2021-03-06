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

#ifndef IOCAPTURE_H
#define IOCAPTURE_H

#include <QtGui>

class IOCapture : public QObject
{

    Q_OBJECT

public:

    virtual QString errorString() =0;
    virtual QWidget* widget() = 0;
    virtual bool isConnected() = 0;

public slots:
    virtual void start() =0;
    virtual void stop() =0;
    virtual void open() =0;
    virtual void close() =0;


signals:
    void dataCaptured(QString);


};

#endif // IOCAPTURE_H
