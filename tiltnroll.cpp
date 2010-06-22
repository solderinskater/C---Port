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

#include "tiltnroll.h"
#include "startscreen.h"
#include "playscreen.h"
#include "settingsscreen.h"
#include "singleplayerscreen.h"
#include "freestylescreen.h"

TiltNRoll::TiltNRoll(QWidget *parent)
        : QStackedWidget(parent)
{
        StartScreen *s1 = new StartScreen();
        addWidget(s1);
        connect(s1, SIGNAL(playPressed()), this, SLOT(onPlay()));
        connect(s1, SIGNAL(settingsPressed()), this, SLOT(onSettings()));
        connect(s1, SIGNAL(quitPressed()), this, SLOT(onQuit()));

        PlayScreen *s2 = new PlayScreen();
        connect(s2, SIGNAL(backPressed()), this, SLOT(onStart()));
        connect(s2, SIGNAL(singlePlayerPressed()), this, SLOT(onSingleplayer()));
        addWidget(s2);

        SettingsScreen *s3 = new SettingsScreen();
        connect(s3, SIGNAL(backPressed()), this, SLOT(onStart()));
        addWidget(s3);

        SingleplayerScreen *s4 = new SingleplayerScreen();
        connect(s4, SIGNAL(backPressed()), this, SLOT(onPlay()));
        connect(s4, SIGNAL(freestylePressed()), this, SLOT(onFreestyle()));
        addWidget(s4);

        FreestyleScreen *s5 = new FreestyleScreen();
     //   connect(s4, SIGNAL(backPressed()), this, SLOT(onPlay()));
        addWidget(s5);

        QSize s(640,360);
        resize(s);
        setMinimumSize(s);
        setMaximumSize(s);

        onStart();
}

TiltNRoll::~TiltNRoll()
{

}

void TiltNRoll::onStart()
{
        setCurrentIndex(0);
}

void TiltNRoll::onPlay()
{
        setCurrentIndex(1);
}

void TiltNRoll::onSettings()
{
        setCurrentIndex(2);
}

void TiltNRoll::onQuit()
{
        close();
}



void TiltNRoll::onSingleplayer()
{
    setCurrentIndex(3);
}

void TiltNRoll::onMultiplayer()
{
    setCurrentIndex(4);
}
void TiltNRoll::onFreestyle()
{
    setCurrentIndex(4);
}
void TiltNRoll::onChallenge()
{
    setCurrentIndex(6);
}
void TiltNRoll::onPause()
{
    setCurrentIndex(7);
}
