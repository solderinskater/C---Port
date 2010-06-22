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

#include "singleplayerscreen.h"
#include "buttons.h"

SingleplayerScreen::SingleplayerScreen(QWidget *parent) :
    QFrame(parent)
{
    qDebug("Build singleplayer window");
    setStyleSheet("SingleplayerScreen {background-image: url(:/images/background_playmodes.png);}");

    QVBoxLayout* layout = new QVBoxLayout();
    setLayout(layout);
    ShinyButton* buttonBack = new ShinyButton("back", "small", "width:178;");
    QHBoxLayout* hbox1 = new QHBoxLayout();
    hbox1->addWidget(buttonBack);
    hbox1->addItem(new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Minimum));
    layout->addLayout(hbox1);

    layout->addWidget(new QLabel(""));
    ShinyButton* buttonChallenge = new ShinyButton("challenge","big");
    layout->addWidget(buttonChallenge);
    ShinyButton* buttonFreestyle = new ShinyButton("freestyle","big");
    layout->addWidget(buttonFreestyle);
    ShinyButton* buttonHighscore = new ShinyButton("highscore","big");
    layout->addWidget(buttonHighscore);
    layout->addWidget(new QLabel(""));
    layout->addWidget(new QLabel(""));

    connect(buttonBack,         SIGNAL(clicked()), this, SIGNAL(backPressed()));
    connect(buttonChallenge,    SIGNAL(clicked()), this, SIGNAL(challendePressed()));
    connect(buttonFreestyle,    SIGNAL(clicked()), this, SIGNAL(freestylePressed()));
    connect(buttonHighscore,    SIGNAL(clicked()), this, SIGNAL(highscorePressed()));

}
