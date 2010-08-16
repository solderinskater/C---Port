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

#ifndef TRAINWIDGET_H
#define TRAINWIDGET_H

#include <QWidget>
#include <QtGui>
#include "buttons.h"
#include "trickmanager.h"

/** Provides the UI to select one trick from a list of all known tricks. Buttons
 for editing or deleting the selected trick are shown. Also a button for adding
 a new trick and a button to get back to the start screen are shown.
*/
class TrainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TrainWidget(QWidget *parent = 0);

signals:
    /// back button pressed
    void backPressed();
    /// add button pressed
    void addPressed();
    /// edit button pressed, name of selected trick will be passed
    void editPressed(QString);

public slots:
    /// reload the trick list from settings
    void updateTrickList();
    /// deletes all tricks currently selected in the list
    void deleteTrick();

private slots:
    /// helper to extract the currently selected trick
    void emitEditPressed();

private:
    QListWidget* listWidget;
    QVBoxLayout *layout, *vbox2_1;
    QHBoxLayout *hbox1, *hbox2;
    ShinyButton *buttonAdd, *buttonDel, *buttonEdit;
    ShinyButton* buttonBack;
    TrickManager *trickManager;

};

#endif // TRAINWIDGET_H
