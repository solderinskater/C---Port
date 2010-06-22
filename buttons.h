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

#ifndef BUTTONS_H
#define BUTTONS_H

#include <QtGui>

class SkateLabel : public QLabel
{
public:
  SkateLabel(QString caption, QString add_style="", bool centered=false);
};


class AnimatedButton : public QPushButton
{
        Q_OBJECT

public:
        AnimatedButton(QString caption, QString image_name, QList<int> timeList, QString addStyle="");

protected:
        void	timerEvent(QTimerEvent * ev);

        void	update_style();
        QString	get_image_name();

private:
        QList<int>	time_list;
        QString		image_name;
        QString		add_style, base_style;
        int			counter,max_count,tid;
};


class ShinyButton : public QPushButton
{
public:
        ShinyButton(QString caption, QString image_name, QString addStyle="");
};



class TogglePushButton : public QPushButton
{
public:
        TogglePushButton(QString caption, bool initialState=false, QString image_name="toggle");

        void update_style();
        bool toggle_state();
        bool is_active();
        void set_state(bool on);

protected:
        void mousePressEvent(QMouseEvent *e);

private:
        QString	image_name;
        QString	add_style, base_style;
        bool state;
};
#endif // BUTTONS_H
