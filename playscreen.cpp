/* 
Copyright 2010 Keywan Tonekaboni, Florian Fusco, Stefanie Schirmer, Alexander Lenhard, Erik Weitnauer <eweitnauer at gmail.com>

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

#include "playscreen.h"

PlayScreen::PlayScreen(QWidget *parent)
        : QFrame(parent)
{
        qDebug("Build play window");

        setStyleSheet("PlayScreen {background-image: url(:/images/background_playerscreen.png); background-color : transparent; }");

        layout = new QVBoxLayout();
        setLayout(layout);

        buttonBack	= new ShinyButton("back","small","width:178;");

        hbox1		= new QHBoxLayout();
        hbox1->addWidget(buttonBack);
        spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding);
        hbox1->addItem(spacer);
        layout->addLayout(hbox1);

        hbox2 = new QHBoxLayout();
        buttonSingle = new ShinyButton("singleplayer", "singleplayer", "padding-top:195px; height: 293px;");
        hbox2->addWidget(buttonSingle);

        buttonMulti = new ShinyButton("multiplayer", "multiplayer", "padding-top:195px; height: 293px;");
        hbox2->addWidget(buttonMulti);
        layout->addLayout(hbox2);


        connect(buttonBack,     SIGNAL(clicked()), this, SIGNAL(backPressed()));
        connect(buttonSingle,   SIGNAL(clicked()), this, SIGNAL(singlePlayerPressed()));
        connect(buttonMulti,    SIGNAL(clicked()), this, SIGNAL(multiPlayerPressed()));

}

