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
#include "trickmanager.h"
#include "trickdetector.h"

TrainPage::TrainPage(QWidget *parent) :
    QWidget(parent)
{
    layout = new QStackedLayout(this);

    train = new TrainWidget;
    record = new RecordWidget;

    connect(record,SIGNAL(saveClicked()), this, SLOT(saveTrick()));
    connect(record,SIGNAL(cancelClicked()), this, SLOT(showTraining()));
    connect(train,SIGNAL(backPressed()), this, SIGNAL(backPressed()));
    connect(train,SIGNAL(addPressed()), this, SLOT(showRecording()));
    connect(train,SIGNAL(editPressed(QString)), this, SLOT(showRecording(QString)));


    layout->addWidget(train);
    layout->addWidget(record);

    layout->setCurrentWidget(train);
}

void TrainPage::showRecording() {
    record->newTrickMode();
    layout->setCurrentWidget(record);
}

void TrainPage::showRecording(QString trick_id) {
    record->editTrickMode(trick_id);
    layout->setCurrentWidget(record);
}

void TrainPage::showTraining() {
    layout->setCurrentWidget(train);
}

void TrainPage::saveTrick() {
    TrickManager *tm = TrickManager::instance();
    if (record->isNewTrick()) {
        tm->addTrick(record->getEnteredTrick());
    } else {
        tm->removeTrick(record->getOldTrickName());
        tm->addTrick(record->getEnteredTrick());
    }
    train->updateTrickList();
    TrickDetector::instance()->init();
    showTraining();
}
