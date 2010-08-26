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

#include "dialog.h"

Dialog::Dialog(QString title, QWidget *parent) :
    QDialog(parent)
{
    l = new QGridLayout;

    bar = new QProgressBar;
    bar->setRange(0,0);
    l->addWidget(bar, 1,0,1,4,Qt::AlignCenter);

    okBtn = new QPushButton("Ok");
    okBtn->setDefault(true);

    cancelBtn = new QPushButton("Cancel");
    label = new QLabel(title);
    label->setAlignment(Qt::AlignCenter);
    l->addWidget(label, 0,0,1,4,Qt::AlignCenter);

    showOkButton(true);
    showCancelButton(true);

    resize(320,240);
}

Dialog::~Dialog()
{
    delete bar;
    delete label;
    delete okBtn;
    delete cancelBtn;
    delete l;
}

void Dialog::showOkButton(bool s)
{
    if(s)
        l->addWidget(okBtn,2,0,1,2,Qt::AlignCenter);
    else
        l->removeWidget(okBtn);
}

void Dialog::showCancelButton(bool s)
{
    if(s)
        l->addWidget(cancelBtn,2,2,1,2,Qt::AlignCenter);
    else
        l->removeWidget(cancelBtn);
}

void Dialog::setOkButtonText(const QString& text)
{
    okBtn->setText(text);
}

void Dialog::setCancelButtonText(const QString& text)
{
    cancelBtn->setText(text);
}

