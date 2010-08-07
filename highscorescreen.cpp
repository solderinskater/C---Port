#include "highscorescreen.h"
#include <iostream>

HighscoreScreen::HighscoreScreen(Highscore *highscore, QWidget *parent):
        QFrame(parent), highscore(highscore) {
    qDebug() << "Building highscore screen...";
    setStyleSheet("HighscoreScreen {background-image: url(:/backgrounds/highscore_new.png);"
      "background-repeat: no-repeat; background-position: top left;"
      "background-color: black;}");
    layout = new QHBoxLayout();
    setLayout(layout);

    buttonBack = new ShinyButton("back", "small", "width:178;");
    vbox1 = new QVBoxLayout();
    vbox1->addWidget(buttonBack);
    vbox1->addStretch();
    layout->addLayout(vbox1);

    highscorelabel = new SkateLabel(" ","font-size: 26px;margin-right: 15px;");
    layout->addStretch();
    layout->addWidget(highscorelabel);

    connect(buttonBack, SIGNAL(clicked()), this, SIGNAL(backPressed()));
}

void HighscoreScreen::showEvent(QShowEvent *e) {
    Q_UNUSED(e)
    updateLabel();
}

void HighscoreScreen::updateLabel() {
    QString text = "";
    Highscore::Hero h;
    foreach(h, highscore->getHeroes()) text += heroToString(h) + '\n';
    text.chop(1);
    highscorelabel->setText(text);
}

QString HighscoreScreen::heroToString(Highscore::Hero h) {
    return QString("%1 %2")
            .arg(h.name.mid(0,3).toUpper(),-3,QChar(' '))
            .arg(QString::number(h.points),6,QChar('0'));
}
