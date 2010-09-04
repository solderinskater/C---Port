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

#ifndef FREESTYLESCREEN_H
#define FREESTYLESCREEN_H

#include <QtGui>
#include <QMap>
#include <QStringList>

class FreestyleScreen : public QFrame
{
    Q_OBJECT
public:
    explicit FreestyleScreen(QWidget *parent = 0);

    bool isPaused() const;
    int getPoints() const;
    int getLevel() const;

signals:
    void showPauseScreen();
    void levelChanged(int);

public slots:
    void trickEvent(QString trickId);
    void start();
    void pause();
    void finish();
    /// reset points, timer and tricks
    void reset();

protected slots:
    void updateTimeLabel();

protected:
    void hideEvent(QHideEvent *e);
    void showEvent(QShowEvent *e);
    void mousePressEvent(QMouseEvent *e);

    void updateLevel();
    void updateTrickList();

private:
    QList<int>          levellist;
    QList<QLabel*>      tricklabels;
    int                 tricklabelcount;
    QLabel              *pointswidget, *levelwidget, *timewidget;
    QMap<QString, int>  tricklist;
    QStringList         tricksDone;
    QTimer              updateTimer;

    int                 points, level, m_secs;

};

#endif // FREESTYLESCREEN_H
