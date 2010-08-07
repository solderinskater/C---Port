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
    qDebug() << "Building singleplayer screen...";
    setStyleSheet("SingleplayerScreen {background-image: url(:/backgrounds/singleplayer_new.png); background-color: black;}");

    QVBoxLayout* layout = new QVBoxLayout();
    setLayout(layout);
    layout->setSpacing(10);

    ShinyButton* buttonBack = new ShinyButton("back", "small", "width:178;");
    QHBoxLayout* hbox1 = new QHBoxLayout();
    hbox1->addWidget(buttonBack);
    hbox1->addStretch();
    layout->addLayout(hbox1);

    ShinyButton* buttonChallenge = new ShinyButton("challenge","big");
    layout->addWidget(buttonChallenge);
    ShinyButton* buttonFreestyle = new ShinyButton("freestyle","big");
    layout->addWidget(buttonFreestyle);
    ShinyButton* buttonHighscore = new ShinyButton("highscore","big");
    layout->addWidget(buttonHighscore);

    connect(buttonBack,         SIGNAL(clicked()), this, SIGNAL(backPressed()));
    connect(buttonChallenge,    SIGNAL(clicked()), this, SIGNAL(challendePressed()));
    connect(buttonFreestyle,    SIGNAL(clicked()), this, SIGNAL(freestylePressed()));
    connect(buttonHighscore,    SIGNAL(clicked()), this, SIGNAL(highscorePressed()));
}
