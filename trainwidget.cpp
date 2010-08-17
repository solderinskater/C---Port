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

#include "trainwidget.h"
#include "simulator/tricksimulator.h"

TrainWidget::TrainWidget(QWidget *parent) :
        QWidget(parent), trickManager(TrickManager::instance())
{
    layout = new QVBoxLayout();

    buttonBack = new ShinyButton("Back","small", "width:178;");
    listWidget = new QListWidget;
    buttonAdd = new ShinyButton("Add","small", "width:178;");
    buttonEdit = new ShinyButton("Edit","small", "width:178;");
    buttonDel = new ShinyButton("Del","small", "width:178;");

    updateTrickList();

    hbox1 = new QHBoxLayout();
    hbox1->addWidget(buttonBack);
    hbox1->addStretch();
    hbox1->addWidget(new SkateLabel("Trick Data", "font-size:30px"));
    hbox1->addStretch();
    layout->addLayout(hbox1);
    layout->addSpacing(10);

    hbox2 = new QHBoxLayout();
    hbox2->addWidget(listWidget);
    vbox2_1 = new QVBoxLayout();
    vbox2_1->addWidget(buttonAdd);
    vbox2_1->addWidget(buttonEdit);
    vbox2_1->addWidget(buttonDel);
    hbox2->addLayout(vbox2_1);
    layout->addLayout(hbox2);

    setLayout(layout);

    connect(buttonBack,SIGNAL(clicked()), this, SIGNAL(backPressed()));
    connect(buttonAdd,SIGNAL(clicked()), this, SIGNAL(addPressed()));
    connect(buttonEdit,SIGNAL(clicked()), this, SLOT(emitEditPressed()));
    connect(buttonDel,SIGNAL(clicked()), this, SLOT(deleteTrick()));

    show();
}

void TrainWidget::emitEditPressed() {
    if (listWidget->selectedItems().size() != 1) return;
    QString trick = listWidget->selectedItems().first()->data(32).toString();
    qDebug() << "the selected trick is " << trick;
    emit editPressed(trick);
}


QString TrainWidget::prettyPrintTrick(TrickManager::Trick trick) {
    QString s("%1P%2 %3");
    s = s.arg(trick.name,-15,QChar(' '))
         .arg(QString::number(trick.points),-4,QChar(' '));
    if (trick.pattern.isEmpty()) s = s.arg("XX");
    else s = s.arg("OK");
    return s;
}

void TrainWidget::updateTrickList()
{
    listWidget->clear();
    foreach(QString s, trickManager->getTrickNames()) {
        QString status = prettyPrintTrick(trickManager->getTrick(s));
        QListWidgetItem *item = new QListWidgetItem(status, listWidget);
        item->setTextAlignment(Qt::AlignLeft);
        item->setData(32,s);
    }
}

void TrainWidget::deleteTrick() {
    foreach (QListWidgetItem* item,  listWidget->selectedItems()) {
        trickManager->removeTrick(item->data(32).toString());
    }
    updateTrickList();
}
