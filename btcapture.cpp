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

#include "btcapture.h"
#include "trickdetector.h"
//#define OLD_BT

BTCapture* BTCapture::instance()
{
    static BTCapture* inst = 0;

    if(!inst)
        inst = new BTCapture;
    return inst;
}

BTCapture::BTCapture(QObject *parent) : conn(false)
{
    doClassify = false;
    setObjectName("Bluetooh");
    setupWidget();
}

void BTCapture::setupWidget()
{
    mWidget = new QWidget;
    mLayout = new QGridLayout();

    okButton = new ShinyButton("Ok","small");
    cancelButton = new ShinyButton("Back","small");
    refreshButton = new ShinyButton("Refresh","small");

    connect(okButton, SIGNAL(clicked()), this, SLOT(okClicked()));
    connect(cancelButton, SIGNAL(clicked()), this, SIGNAL(backPressed()));
    connect(refreshButton,SIGNAL(clicked()), this, SLOT(startDeviceDiscovery()));

    list = new QListWidget;
    list->addItem("None");
    mLayout->addWidget(list, 0, 0, 5, 2);

    mLayout->addWidget(cancelButton,0,3);
    mLayout->addWidget(refreshButton,3,3);

    mLayout->addWidget(okButton,4,3);

    widget()->setLayout(mLayout);

    splash = new QSplashScreen(QPixmap(), Qt::WindowStaysOnTopHint);
//    QProgressBar* b = new QProgressBar;
//    b->setRange(0,0);
//    splash->layout()->addWidget(b);

    open();
}




/**** IOCapture implementation ****/

QWidget* BTCapture::widget()
{
    return mWidget;
}

void BTCapture::open()
{
    initBluetooth();
}

void BTCapture::okClicked()
{
    stop();
    //QBtDevice* dev = new QBtDevice(foundDevices[list->currentRow()]);
//    foundServices.clear();
    selectedDevice = foundDevices[list->currentRow()];
    connect(serviceDisc, SIGNAL(newServiceFound(const QBtDevice&, QBtService)),
            this, SLOT(addService(const QBtDevice&, QBtService)));
    connect(serviceDisc, SIGNAL(discoveryStopped()),
            this, SLOT(serviceDiscoveryCompleteReport()));

    //serviceDisc->startDiscovery(*dev,QBtConstants::RFCOMM);
#ifdef OLD_BT
    serviceDisc->startDiscovery(&selectedDevice);
#else
    serviceDisc->startDiscovery(selectedDevice);
#endif


    splash->show();
    splash->setPixmap(QPixmap(":/images/connect.png"));
    splash->showMessage("Establishing connection...");

}

bool BTCapture::isConnected()
{
    return conn;

}

void BTCapture::setEnableClassification(bool on)
{
    if(on)
    {
        TrickDetector* detector = TrickDetector::instance();
        if(!doClassify) {
            connect(this, SIGNAL(dataCaptured(QString)),
                    detector, SLOT(addSample(QString)));
        }
        doClassify = true;
    } else {
        TrickDetector* detector = TrickDetector::instance();
        if(doClassify)
            disconnect(detector);
        doClassify = false;
    }
}

void BTCapture::start()
{
    //QBtDevice dev = selectedDevice; foundDevices[list->currentRow()];
    qDebug() << "Start!";
    client->connect(foundDevices[list->currentRow()],foundServices.last());
    qDebug() << "Start OK!";
    conn = true;
}

void BTCapture::stop()
{

#ifdef OLD_BT
    if(client->IsConnected()) {
        qDebug("DISCONNECTING");
#else
    if(client->isConnected()) {
        qDebug("DISCONNECTING");
#endif
        client->disconnect();
    }
    list->currentItem()->setIcon(QIcon(":/images/led_off.png"));
    conn=false;
}

void BTCapture::close()
{
    stop();
    TrickDetector* detector = TrickDetector::instance();
    if(doClassify)
        disconnect(detector);
}

void BTCapture::addService(const QBtDevice& targetDevice, QBtService service)
{
    Q_UNUSED(targetDevice);
    foundServices << service;
#ifdef OLD_BT
    qDebug() << service.GetName();
    if(service.GetProtocols().last()==QBtConstants::RFCOMM)
        qDebug() << QString("RFCOMM");
    else
        qDebug() << QString("OTHER");
#else
    qDebug() << service.getName();
#endif
}

#ifndef Q_OS_WIN32

void BTCapture::initBluetooth()
{
    // start rfcomm server
    rfcommServerServiceName = QString("Messenger Protocol ");
    // power on bluetooth
#ifdef OLD_BT
    QBtLocalDevice::AskUserTurnOnBtPower();
    rfcommServerServiceName += QBtLocalDevice::GetLocalDeviceName();
#else
    QBtLocalDevice::askUserTurnOnBtPower();
    rfcommServerServiceName += QBtLocalDevice::getLocalDeviceName();
#endif

    client = new QBtSerialPortClient(this);
    //rfcommClient->startServer(rfcommServerServiceName);

    connect(client, SIGNAL(connectedToServer()),
            this, SLOT(connectedToServerReport()));

    connect(client, SIGNAL(disconnectedFromServer()),
            this, SLOT(disconnectedFromServerReport()));

//    connect(client, SIGNAL(dataReceived(const QString)),
//            this, SIGNAL(dataCaptured(const QString)));

    connect(client, SIGNAL(dataReceived(const QString)),
            this, SLOT(preprocess(const QString)));

    connect(client, SIGNAL(error(QBtSerialPortClient::ErrorCode)),
            this, SLOT(errorReport(QBtSerialPortClient::ErrorCode)));

    //create an instance of BT device discoverer
    devDisc = new QBtDeviceDiscoverer(this);

    //service discoverer
    serviceDisc = new QBtServiceDiscoverer(this);

}

void BTCapture::preprocess(const QString s)
{
    static QString t = QString("");
    t += s;
    int n = t.count("\n");
    if(n>1) {
        QStringList splitted = t.split("\n");
        for(int i=0; i<splitted.size()-1;i++) {
            QString sp = splitted[i];
            sp.chop(2); // remove \n and last , from line
            qDebug() << sp;
//            emit dataCaptured(splitted[i]);
            emit dataCaptured(sp);
        }
        t = splitted.last();
    }
}

/***************************************************************
 *			Device discovery related functions
 ***************************************************************/

void BTCapture::startDeviceDiscovery()
{
  //  SetupMenu(true);
    if(devDisc)
    {
        list->clear();
        foundDevices.clear();
        connect(devDisc, SIGNAL(newDeviceFound(QBtDevice)),
                this, SLOT(populateDeviceList(QBtDevice)));
        connect(devDisc, SIGNAL(discoveryStopped()),
                this, SLOT(deviceDiscoveryCompleteReport()));
        devDisc->startDiscovery();

        splash->show();
        splash->activateWindow();
        splash->setPixmap(QPixmap(":/images/input-gaming.png"));
        splash->showMessage("Searching for devices...",Qt::AlignLeft,Qt::green);
    }
}

void BTCapture::populateDeviceList(QBtDevice newDevice)
{
#ifdef OLD_BT
    list->addItem(newDevice.GetName());
#else
    list->addItem(newDevice.getName());
#endif
    list->item(list->count()-1)->setIcon(QIcon(":/images/led_off.png"));

    foundDevices.append(newDevice);
}

void BTCapture::deviceDiscoveryCompleteReport()
{
    disconnect(devDisc, SIGNAL(newDeviceFound(QBtDevice)),
            this, SLOT(populateDeviceList(QBtDevice)));
    disconnect(devDisc, SIGNAL(discoveryStopped()),
            this, SLOT(deviceDiscoveryCompleteReport()));

    splash->hide();
    splash->clearMessage();

}

void BTCapture::serviceDiscoveryCompleteReport()
{
    serviceDisc->disconnect(this);

    splash->hide();
    splash->clearMessage();

    start();

    QIcon icon(":/images/led_yellow.png");
    list->currentItem()->setIcon(icon);
}

#endif


/*************************** symbian end *******************/

void BTCapture::deviceSelected()
{
    close();
    selectedDeviceName = list->currentItem()->text();
    selectedDevice = foundDevices[list->currentRow()];
}



void BTCapture::connectedToServerReport()
{
    qDebug() << "Connected!";
//    ui.textEdit->append("---Connected---");
}

void BTCapture::disconnectedFromServerReport()
{
    qDebug() << "Disconnected!";
//    ui.textEdit->append("---Disconnected---");
//	lineEdit->setEditFocus(false);
}

//void BTCapture::dataReceivedReport(const QString data)
//{
//    QString str("-> ");
//    str += data;

////    ui.textEdit->append(str);
//}

void BTCapture::errorReport(QBtSerialPortClient::ErrorCode code)
{
    QString str("--Error occurred: ");
        str += code;
    qDebug() << str;
//    ui.textEdit->append(str);
}
