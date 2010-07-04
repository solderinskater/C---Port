#ifndef TIMELINE_H
#define TIMELINE_H

/*
Copyright 2010 Keywan Tonekaboni, Florian Fusco, Stefanie Schirmer, Alexander Lenhard, Erik Weitnauer <eweitnauer at gmail.com>

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

#include <QtCore>

/// Similar to QTimeLine but with unregular time intervals.
class TimeLine : public QObject {
    Q_OBJECT
public:
    explicit TimeLine(const QList<int> &intervals = QList<int>(), QObject *parent = 0);
    bool isRunning() const;

    int loopCount() const;
    void setLoopCount(int count);

    QList<int> timeIntervals() const;
    void setTimeIntervals(QList<int> intervals);

    int currentFrame() const;
    void setCurrentFrame(int frame);

    int startFrame() const;
    void setStartFrame(int frame);

    int endFrame() const;
    void setEndFrame(int frame);

    void setFrameRange(int startFrame, int endFrame);

public Q_SLOTS:
    void start();
    void resume();
    void stop();

Q_SIGNALS:
    void frameChanged(int);
    void stateChanged(bool is_running);
    void finished();

protected:
    void timerEvent(QTimerEvent *event);

private:
    void setTimer();
    void stopTimer();

    QList<int> time_intervals;
    int loop_count;
    int current_frame;
    int start_frame, end_frame;
    bool running;
    int timer_id;
    int current_loop;
};

#endif // TIMELINE_H
