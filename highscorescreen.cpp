#include "highscorescreen.h"
#include <iostream>

HighscoreScreen::HighscoreScreen(Highscore *highscore, QWidget *parent):
        QFrame(parent), highscore(highscore) {
    setStyleSheet("HighscoreScreen {background-image: url(:/images/highscorescreen.png);"
      "background-repeat: no-repeat; background-position: top left;"
      "background-color: black;}");
    layout = new QHBoxLayout();
    setLayout(layout);

    buttonBack = new ShinyButton("back", "small", "width:178;");
    vbox1 = new QVBoxLayout();
    vbox1->addWidget(buttonBack);
    vbox1->addItem(new QSpacerItem(0,0,QSizePolicy::Minimum,QSizePolicy::Expanding));
    layout->addLayout(vbox1);

    highscorelabel = new SkateLabel(" ","font-size: 30px;margin-right: 3px;");
    layout->addItem(new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Minimum));
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
