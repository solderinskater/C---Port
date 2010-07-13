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

#ifndef ENTERNAMESCREEN_H
#define ENTERNAMESCREEN_H

#include <QFrame>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <buttons.h>

class EnterNameScreen : public QFrame
{
    Q_OBJECT
public:
    explicit EnterNameScreen(QWidget *parent = 0);

signals:
    void nameEntered(QString);

protected slots:
    void commitName();

private:
    QHBoxLayout *layout, *hbox1, *hbox2;
    QVBoxLayout *entryLayout;
    QLineEdit* edit;
    ShinyButton *buttonOk;

};

#endif // ENTERNAMESCREEN_H


/*


class HighscoreScreen(QtGui.QFrame):
  def __init__(self, parent):
    QtGui.QFrame.__init__(self, parent)
    self.setStyleSheet("QFrame {background-image: url(./images/highscorescreen.png);\
      background-repeat: no-repeat; background-position: top left;\
      background-color: black;}")

    self.layout = QtGui.QHBoxLayout()
    self.setLayout(self.layout)

    self.buttonBack = ShinyButton("back", "small", "width:178;")
    self.vbox1 = QtGui.QVBoxLayout()
    self.vbox1.addWidget(self.buttonBack)
    self.vbox1.addItem(QtGui.QSpacerItem(0,0,QtGui.QSizePolicy.Minimum,QtGui.QSizePolicy.Expanding))
    self.layout.addLayout(self.vbox1)

    self.heroes = []
    self.heroes = readHeroesFromFile()
    labeltext = ""
    for h in self.heroes:
      labeltext += h.to_string_pretty() + "\n"
    self.highscorelabel = SkateLabel(labeltext.rstrip(),"font-size: 35px;margin-right: 3px;")
    self.layout.addItem(QtGui.QSpacerItem(0,0,QtGui.QSizePolicy.Expanding,QtGui.QSizePolicy.Minimum))
    self.layout.addWidget(self.highscorelabel)
    */
