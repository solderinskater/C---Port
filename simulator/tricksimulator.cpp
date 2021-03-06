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

#include "tricksimulator.h"
#include <QFormLayout>
#include <QDebug>

TrickSimulator* TrickSimulator::instance()
{
    static TrickSimulator* inst = 0;

    if(!inst)
        inst = new TrickSimulator;
    return inst;
}

TrickSimulator::TrickSimulator(QObject *parent) :
        m_curSample(0), doClassify(true)
{
    m_widget = new QWidget;
    QFormLayout* la = new QFormLayout(m_widget);

    QPushButton* btn = new QPushButton("Load");
    connect(btn, SIGNAL(clicked()), this, SLOT(loadClicked()));
    la->addWidget(btn);
    QPushButton* btn2 = new QPushButton("Back");
    connect(btn2, SIGNAL(clicked()), this, SIGNAL(backPressed()));
    la->addWidget(btn2);
    connect(&timer, SIGNAL(timeout()), this, SLOT(doCapture()));
    setObjectName("Simulator");
}

TrickSimulator::~TrickSimulator()
{
    close();
    m_widget->deleteLater();
}

QWidget* TrickSimulator::widget()
{
    return m_widget;
}

void TrickSimulator::open()
{
    qDebug("loading trick data and classifier");
    QFile f(":/simulator/ollie_b.csv");
//    QFile f(":/simulator/shoveit_b.csv");
    QFile f2(":/simulator/lenny_ollie_vs_180_new.lda");
    QFile f3(":/simulator/tmpl_ollie.csv");
    QFile f4(":/simulator/tmpl_180.csv");
    QList<double> lda_w;
    if(f.open(QIODevice::ReadOnly|QIODevice::Text) &&
       f2.open(QIODevice::ReadOnly|QIODevice::Text) &&
       f3.open(QIODevice::ReadOnly|QIODevice::Text) &&
       f4.open(QIODevice::ReadOnly|QIODevice::Text)
            )
    {
        QTextStream stream(&f);
        QTextStream stream2(&f2);
        QTextStream stream3(&f3);
        QTextStream stream4(&f4);
        QString line = stream.readLine();
        while(!line.isNull())
        {
            dataStr << line;
            line = stream.readLine();
//            qDebug() << "[Line "<<cl++<<"]   "<<line;
        }

        line= stream2.readLine();
        while(!line.isNull())
        {
            lda_w << line.toDouble();
            line = stream2.readLine();
        }

        // Templates for DTW
        line= stream3.readLine();
        while(!line.isNull())
        {
            tmpl_ollie << (int)line.toDouble();
            line = stream3.readLine();
        }
        line= stream4.readLine();
        while(!line.isNull())
        {
            tmpl_180 << (int)line.toDouble();
            line = stream4.readLine();
        }

    }
    f.close();
    f2.close();
    f3.close();
    f4.close();

//    QSettings s("SolderinSkaters", "TiltNRoll");
//    s.setValue("Tricks/Ollie",tmpl_ollie);
//    s.setValue("Tricks/180",tmpl_180);

    /* Initialize trick detector */
    if(doClassify) {
        detector = TrickDetector::instance();
        connect(this, SIGNAL(dataCaptured(QString)),
                detector, SLOT(addSample(QString)));
    }
}

void TrickSimulator::loadClicked() {
    stop();
    close();
    setEnableClassification(true);
    open();
    start();
}

void TrickSimulator::close()
{
    timer.stop();
    m_curSample = 0;
}

void TrickSimulator::start()
{
    m_curSample = 0;
    timer.start(1000/70);   // 70Hz
}
void TrickSimulator::stop()
{
    timer.stop();
}

void TrickSimulator::doCapture()
{
    if(m_curSample<dataStr.size()-1)
        emit dataCaptured(dataStr[m_curSample++]);
    else {
        qDebug("End of recorded stream reached. Restarting stream.");
        m_curSample = 0;
        emit dataCaptured(dataStr[m_curSample++]);
    }
}
