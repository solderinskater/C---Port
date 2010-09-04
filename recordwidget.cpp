#include "recordwidget.h"
#include "simulator/tricksimulator.h"
#include "btcapture.h"

RecordWidget::RecordWidget(QWidget *parent) :
        QWidget(parent), trickManager(TrickManager::instance())
{
    // main VBox layout holding title, inputs and buttons
    titleLabel = new SkateLabel("enter trick data","font-size:30px;padding-top:10px",true);
    vbox = new QVBoxLayout();
    vbox->addWidget(titleLabel);
    vbox->addStretch();

    // inputs in grid layout
    nameErrorLabel = new SkateLabel("","color: red; font-size:14px; text-align: right;");
    pointsErrorLabel = new SkateLabel("","color: red; font-size:14px; text-align: right;");
    patternStatusLabel = new SkateLabel("no data");
    patternErrorLabel = new SkateLabel("","color: red; font-size:14px; text-align: right;");
    nameEdit = new QLineEdit;
    QString edit_style =
            "color: #86bc10; font-size:24px; font-family:Adore64; background: black;"
            "border: 2px solid #49762c; border-radius: 8px; padding: 6px 10px;"
            "selection-background-color: black;";
    nameEdit->setStyleSheet(edit_style);
    nameEdit->setMaxLength(14);
    nameEdit->setFocus();
    nameEdit->setEnabled(true);
    nameEdit->setMaximumWidth(365);
    pointsEdit = new QLineEdit;
    pointsEdit->setMaximumWidth(130);
    pointsEdit->setStyleSheet(edit_style);
    pointsEdit->setMaxLength(4);
    pointsEdit->setValidator(new QIntValidator(0, 9999, this));

    capGrid = new QGridLayout;
    capGrid->setHorizontalSpacing(20);
    capGrid->setVerticalSpacing(30);
    capGrid->setMargin(10);

    capGrid->addWidget(new SkateLabel(" name:"), 0, 0);
    capGrid->addWidget(nameEdit,0,1);
    capGrid->addWidget(nameErrorLabel,0,2);
    capGrid->addWidget(new SkateLabel(" pnts:"), 1, 0);
    capGrid->addWidget(pointsEdit,1,1);
    capGrid->addWidget(pointsErrorLabel,1,2);
    capGrid->addWidget(new SkateLabel(" patt:"), 2, 0);
    capGrid->addWidget(patternStatusLabel,2,1);
    capGrid->addWidget(patternErrorLabel,2,2);
    capGrid->setColumnStretch(2,1);
    vbox->addLayout(capGrid);
    vbox->addStretch();

    // buttons in HBox
    saveBtn = new ShinyButton("save","small","width:178;");
    trainBtn = new ShinyButton("train","small","width:178;");
    cancelBtn = new ShinyButton("cancel","small","width:178;");

    hbox = new QHBoxLayout();
    hbox->addWidget(cancelBtn);
    hbox->addWidget(trainBtn);
    hbox->addWidget(saveBtn);
    vbox->addLayout(hbox);

    setLayout(vbox);

    connect(trainBtn,SIGNAL(clicked()), this, SLOT(recordClicked()));
    connect(nameEdit,SIGNAL(textChanged(const QString&)),
            this, SLOT(checkInputs()));
    connect(pointsEdit,SIGNAL(textChanged(const QString&)),
            this, SLOT(checkInputs()));
    connect(saveBtn, SIGNAL(clicked()), this, SIGNAL(saveClicked()));
    connect(cancelBtn, SIGNAL(clicked()), this, SIGNAL(cancelClicked()));
}

void RecordWidget::newTrickMode() {
    new_trick_mode = true;
    titleLabel->setText("enter new trick");
    old_trick_name = "";
    nameEdit->setText("Tricky");
    pointsEdit->setText("200");
    pattern.clear();
}

TrickManager::Trick RecordWidget::getEnteredTrick() {
    return TrickManager::Trick(nameEdit->text(), pointsEdit->text().toInt(),
                               pattern);
}

bool RecordWidget::isNewTrick() {
    return new_trick_mode;
}

QString RecordWidget::getOldTrickName() {
    return old_trick_name;
}

void RecordWidget::editTrickMode(QString trick_name) {
    titleLabel->setText(QString("edit ") + trick_name);
    new_trick_mode = false;
    old_trick_name = trick_name;
    nameEdit->setText(trick_name);
    pointsEdit->setText(QString::number(trickManager->getPoints(trick_name)));
    pattern = trickManager->getPattern(trick_name);
}

void RecordWidget::showEvent(QShowEvent *event) {
    patternErrorLabel->setText("");
    checkInputs();
}

void RecordWidget::checkInputs() {
    bool valid = true;
    if (nameEdit->text().isEmpty()) {
        valid = false;
        nameErrorLabel->setText("empty\nname");
    } else if (trickManager->hasTrick(nameEdit->text()) &&
               !(nameEdit->text() == old_trick_name)) {
        valid = false;
        nameErrorLabel->setText("name\nexists");
    } else {
        nameErrorLabel->setText("");
    }
    if (pointsEdit->text().size() < 1) {
        valid = false;
        pointsErrorLabel->setText("enter\npoints");
    } else {
        pointsErrorLabel->setText("");
    }
    if (pattern.size() == 0) {
        if (trainBtn->text() != "train") trainBtn->setText("train");
        patternStatusLabel->setText("please train");
        if (patternErrorLabel->text().isEmpty()) patternErrorLabel->setText("no\ndata");
        valid = false;
    } else {
        if (trainBtn->text() != "retrain") trainBtn->setText("retrain");
        patternStatusLabel->setText("OK");
    }
    saveBtn->setDisabled(!valid);
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
    qDebug() << d;
    recordedData << d;
}

void RecordWidget::recordClicked()
{
    //TrickSimulator* sim = TrickSimulator::instance();
    BTCapture* sim = BTCapture::instance();


    sim->setEnableClassification(false);

    if(trainBtn->text()!="Stop") {
        trainBtn->setText("Stop");
//        sim->disconnect(this); // disconnect it from the actual game since we abuse it here as "data recorder" for the trick trainer
//        sim->stop();
//        sim->start();
//        sim->close();
//        sim->open();
        recordedData.clear();
        patternStatusLabel->setText("recording...");
        connect(sim,SIGNAL(dataCaptured(QString)), this, SLOT(addData(QString)));
    } else {
//        sim->stop();
//        sim->close();
        sim->disconnect(this);
        try {
            trainTrick();
            patternErrorLabel->setText("");
        } catch(QString& error) {
            patternErrorLabel->setText(error);
            recordedData.clear();
        }
        checkInputs();
    }
}

void RecordWidget::trainTrick() {
    static int trickLength = 40; // 60 samples window
    static int offset = 15; // start window 25 frames before peak
    static int peakThr = 430;   // peak detection threshold

    if(recordedData.size() < trickLength*2)
        throw QString("too\nshort");

    QList<int> ch2;
    for(int i=0; i<recordedData.size(); i++)
        ch2 << recordedData[i][1];

    int i=0;
    for(i=15;i<ch2.size();i++) {
        if(ch2[i]>=peakThr)
                break;
    }
    if(i==ch2.size() || ((i-offset)+trickLength)>=ch2.size())
        throw QString("no\npeak");

    qDebug("Peak CH:");
    qDebug() << ch2.mid(i-offset,trickLength);


    /* save trick */
    QList<QList<int> > trick = recordedData.mid(i-offset,trickLength);
    pattern.clear();
    QList<int> chans;
    chans <<6<<7;
    foreach(int ch, chans) {
        for(i=0;i<trickLength;i++)
            pattern<<trick[i][ch];
    }

    qDebug() << pattern;
}

