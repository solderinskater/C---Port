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

#ifndef DATAPAGE_H
#define DATAPAGE_H

#include <QWidget>
#include <QtGui>
#include "buttons.h"

/** Shows some stats about the data received from the skateboard. User has to
  press the record button to record some data and press it again to stop recording
  and show the stats.
*/
class DataPage : public QWidget
{
    Q_OBJECT
public:
    explicit DataPage(QWidget *parent = 0);

signals:
    /// back button pressed
    void backPressed();

public slots:

private slots:
    void dataReceived(QString);
    /// record button pressed, press again to stop recording
    void recordPressed();

protected:
    void analyze();
    QList<int> parseData(QString data);

private:
    QListWidget* listWidget;
    QHBoxLayout *layout;
    QVBoxLayout *vbox;
    ShinyButton *buttonRecord;
    ShinyButton* buttonBack;

    QStringList data;
    bool recording;
    QTime time;
};

#endif // DATAPAGE_H
