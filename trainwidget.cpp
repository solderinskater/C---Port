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

#include "trainwidget.h"

TrainWidget::TrainWidget(QWidget *parent) :
    QWidget(parent)
{
    gridLayout = new QGridLayout;

    listWidget = new QListWidget;
    buttonAdd = new ShinyButton("Add","small", "width:178;");
    buttonBack = new ShinyButton("Back","small", "width:178;");
    buttonDel = new ShinyButton("Del","small", "width:178;");

    connect(buttonBack,SIGNAL(clicked()), this, SIGNAL(backPressed()));

    QSettings s("SolderinSkaters", "TiltNRoll");
    s.beginGroup("Tricks");
    QStringList tricks = s.childKeys();

    foreach(QString s, tricks)
        listWidget->addItem(s);

    gridLayout->addWidget(new QLabel("Known Tricks"), 0,0,1,2);
    gridLayout->addWidget(listWidget,1,0,5,1);
    gridLayout->addWidget(buttonAdd,4,1);
    gridLayout->addWidget(buttonBack,1,1);
    gridLayout->addWidget(buttonDel,5,1);

    setLayout(gridLayout);
    show();
}
