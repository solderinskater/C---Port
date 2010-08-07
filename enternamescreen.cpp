#include "enternamescreen.h"

EnterNameScreen::EnterNameScreen(QWidget *parent) :
    QFrame(parent)
{
    qDebug() << "Building enter name screen...";
    setStyleSheet("EnterNameScreen {background-image: url(:/backgrounds/highscore_new.png);"
                  "background-color: black; background-position: top left; background-repeat: no-repeat}");

    layout = new QHBoxLayout();
    setLayout(layout);
    layout->addStretch();
    entryLayout = new QVBoxLayout();
    entryLayout->setSpacing(10);
    entryLayout->addWidget(new SkateLabel("NEW HIGHSCORE!","margin-top:20px",true));
    entryLayout->addSpacing(120);
    entryLayout->addWidget(new SkateLabel("your name:","margin-left: 30px; margin-bottom: 4px;"));
    edit = new QLineEdit();
    edit->setStyleSheet("color: #86bc10; font-size:40px; font-family:Adore64; background: black;"
                        "border: 2px solid #49762c; border-radius: 10px; padding: 6px 10px;"
                        "selection-background-color: black;margin-left:42px;");
    edit->setMaximumWidth(200);
    edit->setMaxLength(3);
    edit->grabKeyboard();

    entryLayout->addWidget(edit);
    buttonOk = new ShinyButton("ok", "small", "width:178;");
    entryLayout->addWidget(buttonOk);
    connect(buttonOk, SIGNAL(clicked()), this, SLOT(commitName()));
    connect(edit, SIGNAL(returnPressed()), this, SLOT(commitName()));
    layout->addLayout(entryLayout);
    layout->addSpacing(10);
}

void EnterNameScreen::commitName() {
    nameEntered(edit->text());
}
