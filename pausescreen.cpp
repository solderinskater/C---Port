#include "pausescreen.h"

PauseScreen::PauseScreen(QWidget *parent) :
    QFrame(parent)
{
    qDebug("Build pause window");
    setStyleSheet("PauseScreen {background-image: url(:/images/pauseScreenBackground.png);"
      "background-color: transparent; background-position: top left;}");

    layout = new QVBoxLayout();
    setLayout(layout);

    hbox = new QHBoxLayout();
    buttonResume = new ShinyButton("resume","pause_resume", "width:286;");
    buttonEndGame = new ShinyButton("end game","pause_resume", "width:286;");
    hbox->addWidget(buttonResume);
    hbox->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
    hbox->addWidget(buttonEndGame);
    layout->addLayout(hbox);
    hbox2 = new QHBoxLayout();
    QList<int> intervals; intervals << 2000 << 700 << 200 << 100 << 100 << 100 << 100;
    timeLine = new TimeLine(intervals);
    timeLine->setFrameRange(1,7);
    rauchmonster = new AnimatedButton("", "rauchmonster", timeLine, "margin-left: 20px; width: 332px; height: 354px;");
    hbox2->addWidget(rauchmonster);
    hbox2->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
    vbox = new QVBoxLayout();
    vbox->addItem(new QSpacerItem(0, 130, QSizePolicy::Minimum, QSizePolicy::Minimum));
    vbox->addWidget(new SkateLabel("pause","font-size: 48px;margin-right: 30px;"));
    vbox->addItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));
    hbox2->addLayout(vbox);
    layout->addLayout(hbox2);

    connect(buttonResume, SIGNAL(clicked()), this, SIGNAL(resumePressed()));
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
