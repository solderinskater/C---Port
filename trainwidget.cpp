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
    buttonDel = new ShinyButton("Del","small", "width:178;");

    listWidget->addItem("GFDFGDF");
    listWidget->addItem("GFDFGDF");
    listWidget->addItem("GFDFGDF");
    listWidget->addItem("GFDFGDF");
    listWidget->addItem("GFDFGDF");
    listWidget->addItem("GFDFGDF");

    gridLayout->addWidget(listWidget,0,0,4,1);
    gridLayout->addWidget(buttonAdd,0,1);
    gridLayout->addWidget(buttonDel,3,1);

    setLayout(gridLayout);
    show();
}
