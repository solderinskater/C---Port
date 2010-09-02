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

#ifndef TRICKSIMULATOR_H
#define TRICKSIMULATOR_H

//#define WANT_STREAM                  // include.h will get stream fns
//#define WANT_MATH                    // include.h will get math fns
//#include "newmat/newmatap.h"                // need matrix applications
//#include "newmat/newmatio.h"                // need matrix output routines
//#ifdef use_namespace
//using namespace NEWMAT;              // access NEWMAT namespace
//#endif
#include <QWidget>
#include <QtGui>
#include <IOCapture.h>
#include <trickdetector.h>

Q_DECLARE_METATYPE(QList<int>)

class TrickSimulator : public IOCapture
{
    Q_OBJECT
public:
    static TrickSimulator* instance();
    ~TrickSimulator();
    QWidget* widget();
    QString errorString(){return QString(""); }
    void setEnableClassification(bool yes=true) { doClassify = yes; }
    bool isConnected() { return true; }

signals:
    void backPressed();

/* implement IOCapture interface */
public slots:
    void open();    /* from IOCApture */
    void close();    /* from IOCApture */
    void start();
    void stop();

protected slots:
    void doCapture();
    void loadClicked();


protected:
    TrickSimulator(QObject *parent = 0);

private:
    QList<QList<int> > data;
    QStringList dataStr;
    QList<double> ldaW;
    QVariantList tmpl_ollie;
    QVariantList tmpl_180;
    QTimer timer;
    bool m_isOpen;
    int m_curSample;
    QWidget* m_widget;
    TrickDetector* detector;
    bool doClassify;
};

#endif // TRICKSIMULATOR_H
