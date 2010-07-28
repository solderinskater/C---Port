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

#ifndef HIGHSCORESCREEN_H
#define HIGHSCORESCREEN_H

#include <QFrame>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <buttons.h>
#include <highscore.h>

/// Screen that shows a list of the 10 best players.
/** On construction, a Highscore object pointer is passed to the HighscoreScreen
  class and each time the screen becomes visible, this data is used to build the
  highscore list. */
class HighscoreScreen : public QFrame
{
    Q_OBJECT
public:
    explicit HighscoreScreen(Highscore *highscore, QWidget *parent = 0);

signals:
    void backPressed();

protected:
    /// returns one line of the highscore list from a Hero object
    QString heroToString(Highscore::Hero h);
    /// sets the highscore list to the data the highscore member points to
    void updateLabel();
    /// calls updateLabel()
    void showEvent(QShowEvent *e);

private:
    Highscore *highscore;
    QHBoxLayout *layout;
    ShinyButton *buttonBack;
    QVBoxLayout *vbox1;
    SkateLabel *highscorelabel;

};

#endif // HIGHSCORESCREEN_H
