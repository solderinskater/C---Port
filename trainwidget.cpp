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

RecordWidget::RecordWidget(QWidget *parent) :
        QWidget(parent)
{
    capGrid = new QGridLayout;
    startBtn = new ShinyButton("Start","small");
    nameEdit = new QLineEdit;
    statusLabel = new QLabel("[Ready]");
    capGrid->addWidget(new QLabel("Enter Trick Name"),0,0,Qt::AlignLeft);
    capGrid->addWidget(statusLabel,0,1,Qt::AlignRight);
    capGrid->addWidget(nameEdit,1,0,1,2);
    capGrid->addWidget(startBtn,2,1,3,2);
    nameEdit->setStyleSheet("color: #86bc10; font-size:40px; font-family:Adore64; background: black;"
                        "border: 2px solid #49762c; border-radius: 10px; padding: 6px 10px;"
                        "selection-background-color: black;margin-left:42px;");
    nameEdit->setMaximumWidth(800);
    nameEdit->setMaxLength(20);
    nameEdit->grabKeyboard();
    nameEdit->setFocus();
    nameEdit->setEnabled(true);
    startBtn->hide();

    setLayout(capGrid);

    connect(startBtn,SIGNAL(clicked()), this, SLOT(startClicked()));
    connect(nameEdit,SIGNAL(textChanged(const QString&)), this, SLOT(checkInput(const QString&)));
}

void RecordWidget::showEvent(QShowEvent *event)
{
    nameEdit->grabKeyboard();
    nameEdit->setFocus();
}

void RecordWidget::checkInput(const QString &t)
{
    if(!t.isEmpty())
        startBtn->show();
    else
        startBtn->hide();

}

void RecordWidget::addData(QString smp)
{
    QStringList s = smp.split(",");
    QList<int> d;

    if(s.size()<10) {   // workaround for missing numbers. lost during transmission
        for(int i=0;i<10;i++)
            d << 300;
    }
    else {
        for(int i=0;i<10;i++) {
            int v = (int)s[i].toDouble();
            if(v>600)
                v = recordedData[recordedData.size()-1][i];
            d << v;
        }
    }
    recordedData << d;
}

void RecordWidget::startClicked()
{
    TrickSimulator* sim = TrickSimulator::instance();
    sim->setEnableClassification(false);

    if(startBtn->text()=="Start") {
        startBtn->setText("Stop");
        sim->disconnect(); // disconnect it from the actual game since we abuse it here as "data recorder" for the trick trainer
        sim->stop();
        sim->open();
        connect(sim,SIGNAL(dataCaptured(QString)), this, SLOT(addData(QString)));
        sim->start();

    }
    else {
        startBtn->setText("Start");
        startBtn->hide();
        sim->stop();
        sim->disconnect();
        if(trainTrick()) {
            emit trickTrained();
        }
        else {
            startBtn->show();
            statusLabel->setText("[Retry Trick]");
            recordedData.clear();
        }
    }
}

bool RecordWidget::trainTrick()
{
    static int trickLength = 60; // 60 samples window
    static int peakThr = 430;   // peak detection threshold

    int i=25;
    while(i<recordedData.size() && recordedData[i][1]<peakThr) { i++; }
    if(i==recordedData.size()-1 || i < trickLength*2)
        return false;

    QList<QList<int> > trick = recordedData.mid(i-25,trickLength);

    /* dirty boy*/
    QVariantList trickCh8;
    QList<int> chans;
    chans <<7<<8;
    foreach(int ch, chans) {
        for(i=0;i<trickLength;i++)
            trickCh8<<trick[i][ch];
    }

    QSettings s("SolderinSkaters", "TiltNRoll");
    s.setValue("Tricks/"+nameEdit->text(),trickCh8);
    return true;

}

TrainWidget::TrainWidget(QWidget *parent) :
    QWidget(parent)
{
    gridLayout = new QGridLayout;

    listWidget = new QListWidget;
    buttonAdd = new ShinyButton("Add","small", "width:178;");
    buttonBack = new ShinyButton("Back","small", "width:178;");
    buttonDel = new ShinyButton("Del","small", "width:178;");

    updateTrickList();

    gridLayout->addWidget(new QLabel("Known Tricks"), 0,0,1,2);
    gridLayout->addWidget(listWidget,1,0,5,1);
    gridLayout->addWidget(buttonAdd,4,1);
    gridLayout->addWidget(buttonBack,1,1);
    gridLayout->addWidget(buttonDel,5,1);

    setLayout(gridLayout);

    connect(buttonBack,SIGNAL(clicked()), this, SIGNAL(backPressed()));
    connect(buttonAdd,SIGNAL(clicked()), this, SIGNAL(startCapture()));
    connect(buttonDel,SIGNAL(clicked()), this, SLOT(deleteTrick()));

    show();
}


void TrainWidget::updateTrickList()
{
    listWidget->clear();
    QSettings s("SolderinSkaters", "TiltNRoll");
    s.beginGroup("Tricks");
    QStringList tricks = s.childKeys();

    foreach(QString s, tricks)
        listWidget->addItem(s);
}

void TrainWidget::deleteTrick()
{
    QListWidgetItem* item = listWidget->currentItem();
    QSettings s("SolderinSkaters", "TiltNRoll");
    s.remove("Tricks/"+item->text());
    updateTrickList();
}
