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

#ifndef BTCAPTURE_H
#define BTCAPTURE_H

#include <QtGui>

#ifndef Q_OS_WIN32
#include <QBluetooth.h>
#else
#include <QBluetooth_dummy.h>
#endif

#include "IOCapture.h"
#include "buttons.h"


class BTCapture : public IOCapture
{
    Q_OBJECT
public:
    static BTCapture* instance();
    virtual QString errorString(){ return QString("");}
    QWidget* widget();
    bool isConnected();

signals:
    void dataCaptured(QString);
    void backPressed();

public slots:
    virtual void start();
    virtual void stop();
    virtual void open();
    virtual void close();

protected slots:
#ifndef Q_OS_WIN32
    //device discoverer slots
    void startDeviceDiscovery();
    void populateDeviceList(QBtDevice newDevice);
    void deviceDiscoveryCompleteReport();
    void serviceDiscoveryCompleteReport();
    void addService(const QBtDevice& targetDevice, QBtService service);
    void okClicked();
    void preprocess(const QString);
#else
    void startDeviceDiscovery(){}
    void populateDeviceList(QBtDevice newDevice){}
    void deviceDiscoveryCompleteReport(){}
#endif
    /* widget related slots */
    void deviceSelected();
    void connectedToServerReport();
    void disconnectedFromServerReport();

protected:
    explicit BTCapture(QObject *parent = 0);
#ifndef Q_OS_WIN32
    void initBluetooth();
#else
    void initBluetooth(){}
#endif
    void setupWidget();

private:
    //For bluetooth operation
    QBtDeviceDiscoverer* devDisc;
    QBtServiceDiscoverer* serviceDisc;
    QBtSerialPortClient* client;
    QString rfcommServerServiceName;
    QList<QBtDevice> foundDevices;
    QList<QBtService> foundServices;
    QProgressDialog* dialog;

    /* widget related */
    QWidget*     mWidget;
    QListWidget* list;
    ShinyButton* okButton;
    ShinyButton* cancelButton;
    ShinyButton* refreshButton;
    QGridLayout*  mLayout;
    QString selectedDeviceName;

    bool conn;

};

#endif // BTCAPTURE_H
