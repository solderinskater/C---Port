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

#include "trainpage.h"

TrainPage::TrainPage(QWidget *parent) :
    QWidget(parent)
{
    layout = new QStackedLayout(this);

    train = new TrainWidget;
    record = new RecordWidget;

    connect(record,SIGNAL(trickTrained()), this, SLOT(showTraining()));
    connect(record,SIGNAL(trickTrained()), train, SLOT(updateTrickList()));
    connect(train,SIGNAL(backPressed()), this, SIGNAL(backPressed()));
    connect(train,SIGNAL(addPressed()), this, SLOT(showRecording()));
    connect(train,SIGNAL(editPressed(QString)), this, SLOT(showRecording(QString)));


    layout->addWidget(train);
    layout->addWidget(record);

    layout->setCurrentWidget(train);
}

void TrainPage::showRecording() {
    record->clearTrickData();
    layout->setCurrentWidget(record);
}

void TrainPage::showRecording(QString trick_id) {
    record->loadTrickData(trick_id);
    layout->setCurrentWidget(record);
}

void TrainPage::showTraining()
{
    layout->setCurrentWidget(train);
}
