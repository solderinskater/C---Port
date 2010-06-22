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

#include "settingsscreen.h"
#include <QSettings>

SettingsScreen::SettingsScreen(QWidget *parent)
        : QFrame(parent)
{
        qDebug("Build settings window");

        setStyleSheet("SettingsScreen {background-image: url(:/images/background_settings.png); background-color : transparent }"+
                      QString("QLabel {color: #86bc10;font-size:24px; font-family:Adore64;}"));

        QVBoxLayout* layout = new QVBoxLayout();
        setLayout(layout);
        buttonBack = new ShinyButton("back","small","width:178;");
        connect(buttonBack, SIGNAL(clicked()), this, SIGNAL(backPressed()));
        connect(buttonBack, SIGNAL(clicked()), this, SLOT(saveSettings()));

        hbox1 = new QHBoxLayout();
        hbox1->addWidget(buttonBack);
        hbox1->addItem(new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Minimum));
        QLabel* caption = new QLabel("settings");
        caption->setStyleSheet("font-size:35px; padding: 0px; margin: 0px 53px 21px 0px;");
        hbox1->addWidget(caption);
        layout->addLayout(hbox1);


        QLabel* music = new QLabel("Music Style");
        music->setStyleSheet("font-size:30px; margin-left:30px");
        layout->addWidget(music);


        QHBoxLayout* genres = new QHBoxLayout();
        QButtonGroup* btnGroup = new QButtonGroup;
        buttonElectro = new ShinyButton("electro","small");
        buttonGuitars = new ShinyButton("guitars", "small");
        buttonHipHop = new ShinyButton("hip hop", "small");
        btnGroup->addButton(buttonElectro);
        btnGroup->addButton(buttonGuitars);
        btnGroup->addButton(buttonHipHop);
        btnGroup->setExclusive(true);

        buttonElectro->setCheckable(true);
        buttonGuitars->setCheckable(true);
        buttonHipHop->setCheckable(true);

        genres->addWidget(buttonElectro);
        genres->addWidget(buttonGuitars);
        genres->addWidget(buttonHipHop);
        layout->addLayout(genres);

        QLabel* stancelabel = new QLabel("Stance");
        stancelabel->setStyleSheet("font-size:30px; margin-left:40px");
        layout->addWidget(stancelabel);
        QHBoxLayout* stance = new QHBoxLayout();
        buttonRegular  = new ShinyButton("regular", "small");
        buttonGoofy = new ShinyButton("goofy", "small");
        buttonRegular->setCheckable(true);
        buttonGoofy->setCheckable(true);
        QButtonGroup* btnGroup2 = new QButtonGroup;
        btnGroup2->addButton(buttonRegular);
        btnGroup2->addButton(buttonGoofy);
        btnGroup2->setExclusive(true);

        stance->addWidget(buttonRegular);
        stance->addWidget(buttonGoofy);
        layout->addLayout(stance);

//        connect(buttonRegular, SIGNAL("clicked()"), buttonGoofy.toggle_state);
//        connect(buttonGoofy, SIGNAL("clicked()"), buttonRegular.toggle_state);

//        networklabel = QLabel("Social Networks");
//        networklabel->setStyleSheet("font-size:30px; margin-left:40px");
//        layout->addWidget(networklabel);
//        networks = QHBoxLayout();
//        buttonTwitter  = TogglePushButton("share on twitter", parent->Twitter, "shareOnTwitter");

//        networks->addWidget(buttonTwitter);
//        layout->addLayout(networks);

//        layout->addWidget(QLabel(""));

    loadSettings();
}


void SettingsScreen::saveSettings()
{
    QSettings s("SolderinSkaters", "TiltNRoll");
    s.setValue("Music/Electro",buttonElectro->isChecked());
    s.setValue("Music/Guitars",buttonGuitars->isChecked());
    s.setValue("Music/HipHop",buttonHipHop->isChecked());

    s.setValue("Stance/Regular",buttonRegular->isChecked());
    s.setValue("Stance/Goofy",buttonGoofy->isChecked());
    qDebug("SAVED SETTINGS!");
}

void SettingsScreen::loadSettings()
{
    QSettings s("SolderinSkaters", "TiltNRoll");
    buttonElectro->setChecked(s.value("Music/Electro",true).toBool());
    buttonGuitars->setChecked(s.value("Music/Guitars",false).toBool());
    buttonHipHop->setChecked(s.value("Music/HipHop",false).toBool());

    buttonRegular->setChecked(s.value("Stance/Regular",true).toBool());
    buttonGoofy->setChecked(s.value("Stance/Goofy",false).toBool());

}
