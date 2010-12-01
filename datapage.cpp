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

#include "datapage.h"
#include "btcapture.h"

DataPage::DataPage(QWidget *parent) :
        QWidget(parent), recording(false)
{
    layout = new QHBoxLayout();

    buttonBack = new ShinyButton("Back","small", "width:178;");
    buttonRecord = new ShinyButton("Record","small", "width:178;");
    listWidget = new QListWidget;
    listWidget->setObjectName("tightList");

    vbox = new QVBoxLayout();
    vbox->addWidget(buttonBack);
    vbox->addWidget(buttonRecord);
    layout->addWidget(listWidget);
    layout->addSpacing(10);
    layout->addLayout(vbox);

    setLayout(layout);

    connect(buttonBack,SIGNAL(clicked()), this, SIGNAL(backPressed()));
    connect(buttonRecord,SIGNAL(clicked()), this, SLOT(recordPressed()));

    show();
}

void DataPage::dataReceived(QString d) {
    data.append(d);
}

QList<int> DataPage::parseData(QString data) {
    QStringList s = data.split(",");
    QList<int> d;
    if(s.size()<10) { // workaround for missing numbers. lost during transmission
        for(int i=0;i<10;i++) d << 300;
    } else {
        for(int i=0;i<s.size();i++) d << (int)s[i].toDouble();
    }
    return d;
}

void DataPage::analyze() {
    double secs = 0.001 * time.elapsed();
    listWidget->addItem(QString(
            "Recorded data for %1 seconds:").arg(secs, 0, 'g', 2));
    double dps = double(data.size())/secs;
    listWidget->addItem(QString(
            "Received %1 data packages (%2 per second)")
            .arg(data.size()).arg(dps, 0, 'g', 5 ));
    if (data.size() == 0) {
        listWidget->addItem("No data received -- there is something wrong with "
                            "the communication between skateboard and phone!");
        if (!BTCapture::instance()->isConnected()) {
            listWidget->addItem("Try connecting to the skateboard first.");
        }
        return;
    }
    listWidget->addItem("Here are the first 3 received sets of sensor data: ");
    for (int i=0; i<qMin(3,data.size()); ++i)
        listWidget->addItem("  " + data[i]);

    int channels = data[0].split(",").size();
    listWidget->addItem(QString(
            "The received data has %1 channels.").arg(channels));
    if (channels < 10) {
        listWidget->addItem(
                "There is a problem with the data. There should be at least 10 "
                "comma-separated values.");
        return;
    }

    // calc min, max and mean for each channel
    QList<double> max, min, mean;
    QList<int> d = parseData(data[0]);
    channels = d.size();
    for (int c=0; c<channels; ++c) {
        max.append(d[c]);
        min.append(d[c]);
        mean.append(d[c]);
    }
    for (int i=1; i<data.size(); ++i) {
        QList<int> d = parseData(data[i]);
        for (int c=0; c<channels; ++c) {
            min[c] = qMin(min[c], (double)d[c]);
            max[c] = qMax(max[c], (double)d[c]);
            mean[c] += d[c];
        }
    }
    listWidget->addItem("Here are (mean | max - min) values for each channel:");
    for (int c=0; c<channels; ++c) {
        mean[c] = mean[c] / data.size();
        listWidget->addItem(QString("  Channel %1: %2 | %3")
                            .arg(c).arg(mean[c]).arg(max[c]-min[c]));
    }
}

void DataPage::recordPressed() {
    BTCapture *capture = BTCapture::instance();
    if (recording) {
        // we already should have some data -- start analyzing
        buttonRecord->setText("Record");
        capture->disconnect(this);
        recording = false;
        analyze();
    } else {
        // start recording the data
        // first clear the data list
        data.clear();
        listWidget->clear();
        // now connect to the skateboard
        time.start();
        connect(capture, SIGNAL(dataCaptured(QString)), this, SLOT(dataReceived(QString)));
        buttonRecord->setText("Stop");
        recording = true;
    }
}
