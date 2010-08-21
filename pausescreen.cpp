#include "pausescreen.h"
#include "simulator/tricksimulator.h"

PauseScreen::PauseScreen(QWidget *parent) :
    QFrame(parent)
{
    qDebug() << "Building pause screen...";
    setStyleSheet("PauseScreen {background-image: url(:/backgrounds/pause_new.png);"
      "background-color: black; background-position: top left;}");

    layout = new QVBoxLayout();
    setLayout(layout);
    layout->setSpacing(10);

    hbox = new QHBoxLayout();
    hbox->setSpacing(10);
    buttonResume = new ShinyButton("resume","medium", "width:286;");
    buttonEndGame = new ShinyButton("end game","medium", "width:286;");
    hbox->addWidget(buttonResume);
    hbox->addStretch();
    hbox->addWidget(buttonEndGame);
    layout->addLayout(hbox);
    hbox2 = new QHBoxLayout();
    QList<int> intervals; intervals << 2000 << 700 << 200 << 100 << 100 << 100 << 100;
    rauchmonster = new AnimatedButton("", "rauchmonster", intervals, "margin-left: 10px; width: 234px; height: 249px;");
    rauchmonster->getTimeLine().setFrameRange(1,7);
    hbox2->addWidget(rauchmonster);
    hbox2->addStretch();
    vbox = new QVBoxLayout();
    vbox->addWidget(new SkateLabel("pause","font-size: 48px;margin-right: 75px"));
    vbox->addSpacing(20);

    hbox2->addLayout(vbox);
    layout->addLayout(hbox2);

    connect(buttonResume, SIGNAL(clicked()), this, SIGNAL(resumePressed()));
    connect(rauchmonster, SIGNAL(clicked()), this, SIGNAL(resumePressed()));
    connect(buttonEndGame, SIGNAL(clicked()), this, SIGNAL(endGamePressed()));
}

void PauseScreen::showEvent(QShowEvent *e)
{
    Q_UNUSED(e)
    rauchmonster->start();
}

void PauseScreen::hideEvent(QHideEvent *e)
{
    Q_UNUSED(e)
    rauchmonster->stop();
}
