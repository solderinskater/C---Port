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

    void newTrickMode();
    void editTrickMode(QString trick_name);

signals:
    void trickTrained();

public slots:
    void recordClicked();

protected slots:
    void checkInput(const QString&);
    void addData(QString);

protected:
    bool trainTrick();
    void showEvent ( QShowEvent * event );
    void extractTrick();

private:
    QGridLayout* capGrid;
    ShinyButton* recordBtn;
    ShinyButton* saveBtn;
    QLineEdit* nameEdit;
    QLabel *nameErrorLabel;
    QList<QList<int> > recordedData;
    QLabel* statusLabel;
    TrickManager *trickManager;

    bool new_trick_mode;
    QString old_trick_name;
};

#endif // RECORDWIDGET_H
