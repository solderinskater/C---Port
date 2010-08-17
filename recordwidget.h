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

    /// Can be called after the save() signal to get the trick data which was entered.
    TrickManager::Trick getEnteredTrick();
    /// Returns true if a new trick was created and false if an existing trick was modified.
    bool isNewTrick();
    /// Returns the name of the trick that was edited. "" if trick was newly created.
    QString getOldTrickName();

signals:
    /// save button was pressed
    void saveClicked();
    /// cancel button was pressed
    void cancelClicked();

public slots:
    void recordClicked();

protected slots:
    /// checks all input data, shows error messages and enables/disables the save button.
    void checkInputs();
    void addData(QString);

protected:
    bool trainTrick();
    void showEvent ( QShowEvent * event );
    void extractTrick();

private:
    QGridLayout *capGrid;
    QVBoxLayout *vbox;
    QHBoxLayout *hbox;
    ShinyButton *saveBtn, *cancelBtn;
    QPushButton *trainBtn;
    QLineEdit *nameEdit, *pointsEdit;
    SkateLabel *titleLabel, *patternStatusLabel;
    SkateLabel *nameErrorLabel, *pointsErrorLabel;

    QList<QList<int> > recordedData;
    TrickManager *trickManager;

    bool new_trick_mode;
    QString old_trick_name;
    QList<int> pattern;
};

#endif // RECORDWIDGET_H
