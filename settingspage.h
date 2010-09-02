/* 
Copyright 2010 Keywan Tonekaboni, Florian Fusco, Stefanie Schirmer, Alexander Lenhardt, Erik Weitnauer <eweitnauer at gmail.com>

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

#ifndef SETTINGSPAGE_H
#define SETTINGSPAGE_H

#include <QtGui>
#include "trainpage.h"

class SettingsPage : public QTabWidget
{
    Q_OBJECT
public:
    SettingsPage();

signals:
    void backPressed();

public slots:
    /// writes the changes made to the list of known tricks to the device
    void saveChanges();

private:
    TrainPage*  trainWidget;
    QWidget*    captureWidget;
};

#endif // SETTINGSPAGE_H
