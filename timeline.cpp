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

#include "timeline.h"


// if the list of time intervals is empty, a single 1000 ms interval is added
TimeLine::TimeLine(const QList<int> &intervals, QObject *parent)
    : QObject(parent), time_intervals(intervals), loop_count(0), current_frame(-1),
    start_frame(0), end_frame(0), running(false), timer_id(0), current_loop(0)
{
    if (time_intervals.empty()) time_intervals << 1000;
}

bool TimeLine::isRunning() const { return running; }

int TimeLine::loopCount() const { return loop_count; }
void TimeLine::setLoopCount(int count) { loop_count = count; }

QList<int> TimeLine::timeIntervals() const { return time_intervals; }
void TimeLine::setTimeIntervals(QList<int> intervals) { time_intervals = intervals; }

int TimeLine::currentFrame() const { return current_frame; }
void TimeLine::setCurrentFrame(int frame) {
    if (current_frame != frame) {
        current_frame = frame;
        emit frameChanged(frame);
    }
};

int TimeLine::startFrame() const { return start_frame; }
void TimeLine::setStartFrame(int frame) {start_frame = frame; }

int TimeLine::endFrame() const { return end_frame; }
void TimeLine::setEndFrame(int frame) {end_frame = frame; }

// set both start and end frame
void TimeLine::setFrameRange(int start_frame, int end_frame) {
    this->start_frame = start_frame;
    this->end_frame = end_frame;
}

// reset and start the timeline
void TimeLine::start() {
    stopTimer();
    if (!running) {
        running = true;
        emit stateChanged(true);
    }
    if (current_frame != start_frame) {
        current_frame = start_frame;
        emit frameChanged(current_frame);
    }
    current_loop = 0;
    setTimer();
}

// resume the timeline
void TimeLine::resume() {
    if (!running) {
        running = true;
        emit stateChanged(true);
        setTimer();
    }
}

// stop the timeline
void TimeLine::stop() {
    if (running) {
        running = false;
        emit stateChanged(false);
        stopTimer();
    }
}

// processes a timer event, increases current_frame and evt. current_loop
// kills the old timer and might start a new one
void TimeLine::timerEvent(QTimerEvent *event) {
    if (event->timerId() == timer_id) {
        stopTimer();
        current_frame++;
        if (current_frame > end_frame) {
            current_frame = start_frame;
            current_loop++;
        }
        if (current_loop > loop_count && loop_count > 0) {
            emit finished();
            stop();
        } else {
            emit frameChanged(current_frame);
            setTimer();
        }
    }
}

// starts timer with current interval and stores its id
void TimeLine::setTimer() {
    timer_id = startTimer(time_intervals[current_frame-start_frame]);
}

// kills the old timer
void TimeLine::stopTimer() {
    if (timer_id == 0) return;
    killTimer(timer_id);
    timer_id = 0;
}
