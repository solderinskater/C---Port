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

#include "settingspage.h"
#include "btcapture.h"
#include "datapage.h"

SettingsPage::SettingsPage()
{
    trainWidget = new TrainPage();
    dataWidget = new DataPage();
    captureWidget = BTCapture::instance()->widget();

    addTab(captureWidget,QIcon(":/images/bluetooth-active.png"),"Bluetooth");
    addTab(dataWidget,"Data");
    addTab(trainWidget,QIcon(":/images/trace.png"),"Tricks");

    connect(BTCapture::instance(), SIGNAL(backPressed()), this, SIGNAL(backPressed()));
    connect(trainWidget, SIGNAL(backPressed()), this, SIGNAL(backPressed()));
    connect(dataWidget, SIGNAL(backPressed()), this, SIGNAL(backPressed()));
    connect(this, SIGNAL(backPressed()), this, SLOT(saveChanges()));
}

void SettingsPage::saveChanges() {
    TrickManager::instance()->save();
}
