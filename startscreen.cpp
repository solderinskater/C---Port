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

#include "startscreen.h"
#include <QVBoxLayout>
#include <QtGui>

StartScreen::StartScreen(QWidget *parent) :
    QFrame(parent)
{
        setStyleSheet("StartScreen {background-image: url(:/images/startscreen.jpg);}");

        QBoxLayout *layout = new QBoxLayout(QBoxLayout::TopToBottom);
        setLayout(layout);

        ShinyButton *buttonPlay     = new ShinyButton("play","big");
        ShinyButton *buttonSettings = new ShinyButton("settings", "big");
        ShinyButton *buttonQuit     = new ShinyButton("quit","big");
        ShinyButton *buttonSimul     = new ShinyButton("simulator","big");

        connect(buttonPlay,     SIGNAL(clicked()), this, SIGNAL(playPressed()));
        connect(buttonSettings, SIGNAL(clicked()), this, SIGNAL(settingsPressed()));
        connect(buttonQuit,     SIGNAL(clicked()), this, SIGNAL(quitPressed()));
        connect(buttonSimul,     SIGNAL(clicked()), this, SIGNAL(simulPressed()));

        QSpacerItem* spacer = new QSpacerItem(640, 250, QSizePolicy::Fixed, QSizePolicy::Fixed);
//        layout->addWidget(new QLabel(""));
//        layout->addWidget(new QLabel(""));
//        layout->addWidget(new QLabel(""));
        layout->insertSpacerItem(0,spacer);
        layout->addWidget(buttonPlay);
        layout->addWidget(buttonSettings);
//        layout->addWidget(buttonQuit);
        layout->addWidget(buttonSimul);
//        layout->addWidget(new QLabel(""));

}
