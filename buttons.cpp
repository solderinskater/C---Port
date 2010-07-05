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

#include "buttons.h"

SkateLabel::SkateLabel(QString caption, QString add_style, bool centered)
        : QLabel(caption)
{
    setStyleSheet("color: #86bc10; font-size:24px; font-family:Adore64; text-align:center;"+add_style);

        if(centered)
                setAlignment(Qt::AlignCenter);

}



AnimatedButton::AnimatedButton(QString caption, QString iname, QList<int> timeIntervals, QString addStyle)
        : QPushButton(caption), timeLine(timeIntervals), image_name(iname), add_style(addStyle)
{
    base_style = "margin:0px; height: 74px; color: #86bc10; background-color: transparent; font-family:Adore64;font-size:28px; background-repeat:no-repeat; background-position: center;";
    setFlat(true);
    connect(&timeLine, SIGNAL(frameChanged(int)), this, SLOT(updateImage(int)));
}

void AnimatedButton::updateImage(int frame) {
    setStyleSheet(base_style + "background-image: url(" + get_image_name(frame)
                  + ");" + add_style);
}

QString AnimatedButton::get_image_name(int num) {
    QString s = ":/anims/%1%2.png";
    return s.arg(image_name).arg(num,2,10,QChar('0'));
}

void AnimatedButton::start() {
    timeLine.start();
}

void AnimatedButton::stop() {
    timeLine.stop();
}

ShinyButton::ShinyButton(QString caption, QString image_name, QString addStyle) : QPushButton(caption)
{
    setFlat(true);
    setStyleSheet("QPushButton{color: rgba(200,200,200,128); margin:0px; height: 65px; background-color: transparent; font-family:Adore64; font-size:24px; background-repeat:no-repeat; background-position: center; background-image: url(:/buttons/"+image_name+".png);"+addStyle+"}"
                  +"QPushButton:checked{color: #86bc10;}"
                  +"QPushButton:pressed{color: #86bc10;}");

}


TogglePushButton::TogglePushButton(QString caption, bool initialState, QString image_name) : QPushButton(caption)
{
    state = initialState;
    image_name = image_name;
    setFlat(true);
    base_style = "height: 74px; background-color: transparent; font-size:28px;font-family:Adore64; color: #86bc10; background-repeat:no-repeat; background-position: center;";
    update_style();
}

void TogglePushButton::update_style()
{
        if(state)
            setStyleSheet(base_style+"background-image: url(:/buttons/"+image_name+"_on.png);color: #86bc10;");
        else
            setStyleSheet(base_style+"background-image: url(:/buttons/"+image_name+"_off.png);color: #324606;");
}

bool TogglePushButton::toggle_state()
{
        state = !state;
        update_style();
        return state;
}

bool TogglePushButton::is_active()
{
        return state;
}

void TogglePushButton::set_state(bool on)
{
        state = on;
        update_style();
}

void TogglePushButton::mousePressEvent(QMouseEvent *e)
{
        if(e->button() == Qt::LeftButton)
                toggle_state();

        QPushButton::mousePressEvent(e);
}
