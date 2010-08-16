#ifndef RECORDWIDGET_H
#define RECORDWIDGET_H

#include <QWidget>
#include <QtGui>
#include "buttons.h"
#include "trickmanager.h"

class RecordWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RecordWidget(QWidget *parent = 0);

    void clearTrickData() {}
    void loadTrickData(QString trickid) {}

signals:
    void trickTrained();

public slots:
    void startClicked();

protected slots:
    void checkInput(const QString&);
    void addData(QString);

protected:
    bool trainTrick();
    void showEvent ( QShowEvent * event );
    void extractTrick();

private:
    QGridLayout* capGrid;
    ShinyButton* startBtn;
    QLineEdit* nameEdit;
    QList<QList<int> > recordedData;
    QLabel* statusLabel;
};

#endif // RECORDWIDGET_H
