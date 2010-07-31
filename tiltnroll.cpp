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
#include "pausescreen.h"
#include "enternamescreen.h"
#include "highscorescreen.h"
#include "highscore.h"
#include <simulator/tricksimulator.h>

TiltNRoll::TiltNRoll(QWidget *parent)
        : QStackedWidget(parent), m_channel(0), m_embedded(true)
{
    // start screen (tab 0)
    StartScreen *s0 = new StartScreen();
    addWidget(s0);
    connect(s0, SIGNAL(playPressed()), this, SLOT(onPlay()));
    connect(s0, SIGNAL(settingsPressed()), this, SLOT(onSettings()));
    connect(s0, SIGNAL(quitPressed()), this, SLOT(onQuit()));
    connect(s0, SIGNAL(simulPressed()), this, SLOT(onSimul()));

    // play screen (tab 1)
    PlayScreen *s1 = new PlayScreen();
    connect(s1, SIGNAL(backPressed()), this, SLOT(onStart()));
    connect(s1, SIGNAL(singlePlayerPressed()), this, SLOT(onSingleplayer()));
    addWidget(s1);

    // settings screen (tab 2)
    SettingsScreen *s2 = new SettingsScreen();
    connect(s2, SIGNAL(backPressed()), this, SLOT(onStart()));
    addWidget(s2);

    // DEBUG
    //addWidget(createGraph());

    // single player screen (tab 3)
    SingleplayerScreen *s3 = new SingleplayerScreen();
    connect(s3, SIGNAL(backPressed()), this, SLOT(onPlay()));
    connect(s3, SIGNAL(freestylePressed()), this, SLOT(onFreestyle()));
    connect(s3, SIGNAL(highscorePressed()), this, SLOT(onHighscore()));
    addWidget(s3);

    // freestyle screen (tab 4)
    freestyle_screen = new FreestyleScreen();
    connect(freestyle_screen, SIGNAL(showPauseScreen()), this, SLOT(onPause()));
    addWidget(freestyle_screen);

    // pause screen (tab 5)
    PauseScreen *s5 = new PauseScreen();
    qDebug("added!");
    connect(s5, SIGNAL(resumePressed()), this, SLOT(onFreestyle()));
    connect(s5, SIGNAL(endGamePressed()), this, SLOT(checkHighscore()));
    addWidget(s5);

    // enter name screen (tab 6)
    EnterNameScreen *s6 = new EnterNameScreen();
    qDebug("added!");
    connect(s6, SIGNAL(nameEntered(QString)), this, SLOT(addToHighscore(QString)));
    addWidget(s6);

    // highscore screen (tab 7)
    HighscoreScreen *s7 = new HighscoreScreen(&hs);
    connect(s7, SIGNAL(backPressed()), this, SLOT(onStart()));
    addWidget(s7);

    // TrickSimulator (tab 8)
    TrickSimulator* sim = TrickSimulator::instance();
    connect(sim, SIGNAL(backPressed()), this, SLOT(onStart()));
    addWidget(sim->widget());

    QSize s(640,360);
    resize(s);
    setMinimumSize(s);
    setMaximumSize(s);
   //setStyle(new QPlastiqueStyle());
    qApp->setOverrideCursor(Qt::BlankCursor);
    setWindowState(Qt::WindowFullScreen);
    onStart();
}

TiltNRoll::~TiltNRoll()
{

}

QWidget* TiltNRoll::createGraph()
{
    QWidget *page = new QWidget();
    QVBoxLayout *toplay = new QVBoxLayout(page);

    QWidget *group = new QGroupBox(tr("Realtime Data"), page);
    QGridLayout *grid = new QGridLayout(group);

    toplay->addWidget(group);

    // create sinus graph and model
    m_graph = new Graph(group);
    m_graph->setStyle(new QWindowsStyle());
    m_graph->setProperty("isEmbedded", m_embedded);
    m_graph->setFocusPolicy(Qt::NoFocus);
    if (!m_embedded)
        m_graph->setRenderHints(QPainter::Antialiasing);

    grid->addWidget(m_graph, 0, 0, 1, 4);

    QLabel *label = new QLabel(tr("Choose channel"), group);
    grid->addWidget(label, 1, 1, Qt::AlignRight);
    QComboBox *chooser = new QComboBox(group);
    chooser->addItems(QStringList() << tr("Accel X") << tr("Accel Y") << tr("Accel Z"));
    connect(chooser, SIGNAL(currentIndexChanged(int)), this, SLOT(showGraph(int)));
    grid->addWidget(chooser, 1, 2);


    m_graphTimer = new QTimer();
    connect(m_graphTimer, SIGNAL(timeout()), this, SLOT(getData()));
    showGraph(0);
    return page;

}

void TiltNRoll::showGraph(int idx)
{
    m_graph->setXRange(200);
    m_graph->setYMinMax(-5, 10);
    m_graphTimer->stop();
    m_channel = idx;
    m_graph->clear();
    m_tick = 0;
    m_graphTimer->start(33);
}

void TiltNRoll::getData()
{
    ++m_tick;
    m_graph->addPoint(QPointF(m_tick, m_channel + (qrand()%10)*0.1));
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
void TiltNRoll::onPause()
{
    setCurrentIndex(5);
}
void TiltNRoll::onEnterName() {
    setCurrentIndex(6);
}
void TiltNRoll::onHighscore() {
    qDebug("onHighscore()");
    setCurrentIndex(7);
}
void TiltNRoll::onSimul()
{
    qDebug("onSimul()");
    setCurrentIndex(8);
}

void TiltNRoll::onChallenge()
{
    setCurrentIndex(9);
}

void TiltNRoll::checkHighscore() {
    int points = freestyle_screen->getPoints();
    if (hs.isHighscore(points)) onEnterName();
    else onHighscore();
}

void TiltNRoll::addToHighscore(QString name) {
    int points = freestyle_screen->getPoints();
    int level = freestyle_screen->getLevel();
    hs.addToHighscore(Highscore::Hero(name, points, level));
    hs.save();
    onHighscore();
}
