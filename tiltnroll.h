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

#ifndef TILTNROLL_H
#define TILTNROLL_H

#include <QtGui>

class TiltNRoll : public QStackedWidget
{
        Q_OBJECT

public:
        explicit TiltNRoll(QWidget *parent = 0);
        ~TiltNRoll();

protected slots:
        void onStart();
        void onPlay();
        void onSettings();
        void onQuit();

        void onSingleplayer();
        void onMultiplayer();
        void onFreestyle();
        void onChallenge();
        void onPause();
        void onHighscore();

};

#endif // TILTNROLL_H
