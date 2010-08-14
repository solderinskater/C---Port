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

#ifndef TRAINPAGE_H
#define TRAINPAGE_H

#include <QtGui>
#include "trainwidget.h"

class TrainPage : public QWidget
{
    Q_OBJECT
public:
    explicit TrainPage(QWidget *parent = 0);

signals:
    void backPressed();

public slots:
    void addPressed();
    void trainingDone();

private:
    TrainWidget* train;
    RecordWidget* record;
    QStackedLayout* layout;
};

#endif // TRAINPAGE_H
