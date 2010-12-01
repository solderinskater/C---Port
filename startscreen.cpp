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
    qDebug() << "Building start screen...";
    setStyleSheet("StartScreen {background-image: url(:/backgrounds/start_new.png); background-color: black;}");

        QVBoxLayout *layout = new QVBoxLayout();
        setLayout(layout);

        ShinyButton *buttonPlay     = new ShinyButton("play","big");
        ShinyButton *buttonTraining = new ShinyButton("settings", "big");
        ShinyButton *buttonQuit     = new ShinyButton("quit","big");
        ShinyButton *buttonSimul     = new ShinyButton("simulator","big");

        connect(buttonPlay,     SIGNAL(clicked()), this, SIGNAL(playPressed()));
        connect(buttonTraining, SIGNAL(clicked()), this, SIGNAL(trainingPressed()));
        connect(buttonQuit,     SIGNAL(clicked()), this, SIGNAL(quitPressed()));
        connect(buttonSimul,     SIGNAL(clicked()), this, SIGNAL(simulPressed()));

        layout->setSpacing(0);
        layout->addSpacing(115);
        layout->addWidget(buttonPlay);
        layout->addSpacing(10);
        layout->addWidget(buttonTraining);
        layout->addSpacing(10);
//        layout->addWidget(buttonSimul);
        layout->addWidget(buttonQuit);
        layout->addSpacing(-10);

        SkateLabel *version = new SkateLabel("v 0.8.1","font-family: sans; font-size:14px; color: white;");
        layout->addWidget(version);
}
