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

#include "freestylescreen.h"
#include "soundplayer.h"
#include <trickdetector.h>
#include <trickmanager.h>

FreestyleScreen::FreestyleScreen(QWidget *parent) :
    QFrame(parent) {
    levellist << 200 << 800 << 1000 << 2000 <<100000;
    tricklabelcount = 4;
    points = 100;
    level = 1;
    qDebug("Build game screen freestyle");
    setStyleSheet(QString("FreestyleScreen {background-image: url(:/backgrounds/freestyle.jpg);}")+
                  "QLabel {color: #86bc10; font-size:24px; font-family:Adore64; text-align:center; background-color: transparent;}"+
      "#timelabel {font-size: 30px;}"+
      "#levellabel {font-size: 30px;}"+
      "#pointslabel {font-size: 90px;}"+
      "#tricklabel1 {font-size: 45px;}"+
      "#tricklabel2 {font-size: 20px;}"+
      "#tricklabel3 {font-size: 15px;}"+
      "#tricklabel4 {font-size: 10px;}"+
      "#musicwidget {font-size: 24px;}");
    QVBoxLayout* layout = new QVBoxLayout();
    setLayout(layout);

    QHBoxLayout* upperbar = new QHBoxLayout();
    timewidget = new QLabel("");
    timewidget->setObjectName("timelabel");
    timewidget->setAlignment(Qt::AlignLeft);
    levelwidget = new QLabel(" ");

    updateLevel();
    levelwidget->setAlignment(Qt::AlignRight);
    levelwidget->setObjectName("levellabel");

    upperbar->addWidget(timewidget);
    upperbar->addWidget(new QLabel(""));
    upperbar->addWidget(levelwidget);
    layout->addLayout(upperbar);

    pointswidget = new QLabel(QString::number(points));
    pointswidget->setAlignment(Qt::AlignCenter);
    pointswidget->setObjectName("pointslabel");
    layout->addWidget(pointswidget);

    QVBoxLayout* tricklistlayout = new QVBoxLayout();
    for (int i=0; i<tricklabelcount;i++) {
        QLabel* label = new QLabel(" ");
        label->setObjectName("tricklabel"+QString::number(i+1));
        label->setAlignment(Qt::AlignCenter);
        if(tricksDone.size()> i)
            label->setText(tricksDone[i]);
        tricklistlayout->addWidget(label);
        tricklabels << label;
    }
    layout->addLayout(tricklistlayout);

    QLabel* musicwidget = new QLabel("Playing This Song");
    musicwidget->setAlignment(Qt::AlignCenter);
    musicwidget->setObjectName("musicwidget");
   //layout->addWidget(musicwidget);

    connect(&updateTimer, SIGNAL(timeout()), this, SLOT(updateTimeLabel()));
    connect(TrickDetector::instance(), SIGNAL(trickEvent(QString)),
            this, SLOT(trickEvent(QString)));
    updateTimeLabel();
}

void FreestyleScreen::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    if(isPaused())
        start();
    else
        pause();
}

void FreestyleScreen::updateTimeLabel()
{
    static int s=0;
    timewidget->setText(QString().sprintf("%.2d:%.2d",s/60, s%60));
    s++;
    update();
}

void FreestyleScreen::updateLevel()
{
    int old_level = level;
    int val;
    level = 1;
    foreach(val,levellist) if(points>val) level += 1;
    if(old_level != level) {
        emit levelChanged(level);
        SoundPlayer::playLevel(level);
    }
    levelwidget->setText("lvl " + QString::number(level));
}


void FreestyleScreen::updateTrickList() {
    for(int i=0; i<tricklabelcount;i++) {
        if(tricksDone.size() > i)
            tricklabels[i]->setText(tricksDone[i]);
        else
            tricklabels[i]->setText(" ");
    }
}

void FreestyleScreen::trickEvent(QString trickid)
{
    if(isPaused())
        return;

    qDebug() << "got trick " << trickid;
    points += TrickManager::instance()->getPoints(trickid);
    pointswidget->setText(QString::number(points));
    tricksDone << trickid;
    updateTrickList();
    SoundPlayer::playTrick(trickid);
    updateLevel();
}

int FreestyleScreen::getPoints() const {
    return points;
}

int FreestyleScreen::getLevel() const {
    return level;
}



void FreestyleScreen::showEvent(QShowEvent *e)
{
    Q_UNUSED(e)
    start();
}


void FreestyleScreen::hideEvent(QHideEvent *e)
{
    Q_UNUSED(e)
    updateTimer.stop();
}

void FreestyleScreen::start()
{
    updateTimer.start(1000);
}

void FreestyleScreen::pause()
{
    updateTimer.stop();
    emit showPauseScreen();
}

void FreestyleScreen::finish()
{
    updateTimer.stop();
    /*
     ... show highscores etc.
     */
}

bool FreestyleScreen::isPaused() const
{
    return !updateTimer.isActive();
}
