#include "recordwidget.h"
#include "simulator/tricksimulator.h"

RecordWidget::RecordWidget(QWidget *parent) :
        QWidget(parent), trickManager(TrickManager::instance())
{
    capGrid = new QGridLayout;
    recordBtn = new ShinyButton("record","small");
    saveBtn = new ShinyButton("save","small");
    nameEdit = new QLineEdit;
    statusLabel = new QLabel("[Ready]");
    nameErrorLabel = new SkateLabel(" ","color: red; font-size:14px; text-align: right;");
    capGrid->addWidget(new QLabel("Enter Trick Name"),0,0,Qt::AlignLeft);
    capGrid->addWidget(statusLabel,0,1,Qt::AlignRight);
    capGrid->addWidget(nameEdit,1,0,1,2);
    capGrid->addWidget(nameErrorLabel,2,0,1,2);
    capGrid->addWidget(recordBtn,2,1);
    capGrid->addWidget(saveBtn,3,1);

    nameEdit->setStyleSheet("color: #86bc10; font-size:40px; font-family:Adore64; background: black;"
                        "border: 2px solid #49762c; border-radius: 10px; padding: 6px 10px;"
                        "selection-background-color: black;margin-left:42px;");
    nameEdit->setMaximumWidth(800);
    nameEdit->setMaxLength(20);
    nameEdit->grabKeyboard();
    nameEdit->setFocus();
    nameEdit->setEnabled(true);

    setLayout(capGrid);

    connect(recordBtn,SIGNAL(clicked()), this, SLOT(recordClicked()));
    connect(nameEdit,SIGNAL(textChanged(const QString&)), this, SLOT(checkInput(const QString&)));
}

void RecordWidget::newTrickMode() {
    new_trick_mode = true;
}

void RecordWidget::editTrickMode(QString trick_name) {
    new_trick_mode = false;
    old_trick_name = trick_name;
}


void RecordWidget::showEvent(QShowEvent *event)
{
    nameEdit->grabKeyboard();
    nameEdit->setFocus();
    checkInput(nameEdit->text());
}

void RecordWidget::checkInput(const QString &t)
{
    if (t.isEmpty()) {
        saveBtn->setDisabled(true);
        nameErrorLabel->setText("empty name");
    } else if (new_trick_mode && trickManager->hasTrick(t)) {
        saveBtn->setDisabled(true);
        nameErrorLabel->setText("name exists");
    } else {
        saveBtn->setDisabled(false);
        nameErrorLabel->setText(" ");
    }
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

void RecordWidget::recordClicked()
{
    TrickSimulator* sim = TrickSimulator::instance();
    sim->setEnableClassification(false);

    if(recordBtn->text()=="Start") {
        recordBtn->setText("Stop");
        sim->disconnect(); // disconnect it from the actual game since we abuse it here as "data recorder" for the trick trainer
        sim->stop();
        sim->open();
        connect(sim,SIGNAL(dataCaptured(QString)), this, SLOT(addData(QString)));
        sim->start();
    } else {
        recordBtn->setText("Start");
        sim->stop();
        sim->disconnect();
        if(trainTrick()) {
            emit trickTrained();
        } else {
            recordBtn->show();
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
    QList<int> trickCh8;
    QList<int> chans;
    chans <<7<<8;
    foreach(int ch, chans) {
        for(i=0;i<trickLength;i++)
            trickCh8<<trick[i][ch];
    }

    trickManager->addTrick(nameEdit->text(), 200, trickCh8);
    return true;
}
