#include "enternamescreen.h"

EnterNameScreen::EnterNameScreen(QWidget *parent) :
    QFrame(parent)
{
    qDebug("Build enter name screen");
    setStyleSheet("EnterNameScreen {background-image: url(:/images/highscorescreen.png);"
                  "background-color: black; background-position: top left; background-repeat: no-repeat}");

    layout = new QHBoxLayout();
    setLayout(layout);
    layout->addItem(new QSpacerItem(420,0,QSizePolicy::Minimum,QSizePolicy::Minimum));
    entryLayout = new QVBoxLayout();
    entryLayout->addWidget(new SkateLabel("NEW HIGHSCORE!","margin-top:20px",true));
    entryLayout->addItem(new QSpacerItem(0,120,QSizePolicy::Minimum,QSizePolicy::Minimum));
    entryLayout->addWidget(new SkateLabel("your name:","margin-left: 30px; margin-bottom: 4px;"));
    edit = new QLineEdit();
    edit->setStyleSheet("color: #86bc10; font-size:40px; font-family:Adore64; background: black;"
                        "border: 2px solid #49762c; border-radius: 10px; padding: 6px 10px;"
                        "selection-background-color: black;width:120px;margin-left:42px;");
    edit->setMaxLength(3);
    edit->grabKeyboard();

    hbox1 = new QHBoxLayout();
    hbox1->addWidget(edit);
    hbox1->addItem(new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Minimum));
    entryLayout->addLayout(hbox1);
    buttonOk = new ShinyButton("ok", "small", "width:178;");
    hbox2 = new QHBoxLayout();
    hbox2->addItem(new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Minimum));
    hbox2->addWidget(buttonOk);
    entryLayout->addItem(new QSpacerItem(0,0,QSizePolicy::Minimum,QSizePolicy::Expanding));
    entryLayout->addLayout(hbox2);
    connect(buttonOk, SIGNAL(clicked()), this, SLOT(commitName()));
    connect(edit, SIGNAL(returnPressed()), this, SLOT(commitName()));
    layout->addLayout(entryLayout);
}

void EnterNameScreen::commitName() {
    nameEntered(edit->text());
}
