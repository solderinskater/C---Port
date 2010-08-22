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
#include "btcapture.h"

PlayScreen::PlayScreen(QWidget *parent)
        : QFrame(parent)
{
        qDebug() << "Building play screen...";

        setStyleSheet("PlayScreen {background-image: url(:/backgrounds/play_new.png); background-color : black; }");

        layout = new QVBoxLayout();
        setLayout(layout);

        buttonBack	= new ShinyButton("back","small","width:178;");

        hbox1		= new QHBoxLayout();
        hbox1->addWidget(buttonBack);
        hbox1->addStretch();
        layout->addLayout(hbox1);
        layout->addSpacing(20);

        hbox2 = new QHBoxLayout();
        buttonSingle = new ShinyButton("singleplayer", "singleplayer_new", "padding-top:187px; height: 255px;");
        hbox2->addWidget(buttonSingle);

        buttonMulti = new ShinyButton("multiplayer", "multiplayer_new", "padding-top:187px; height: 255px;");
        hbox2->addWidget(buttonMulti);
        layout->addLayout(hbox2);


        connect(buttonBack,     SIGNAL(clicked()), this, SIGNAL(backPressed()));
        connect(buttonSingle,   SIGNAL(clicked()), this, SIGNAL(singlePlayerPressed()));
        connect(buttonMulti,    SIGNAL(clicked()), this, SIGNAL(multiPlayerPressed()));


}

