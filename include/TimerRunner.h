//  Copyright (C) 2016 Nils Friedchen <nils.friedchen@googlemail.com>
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation version 2.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License along
//  with this program; if not, write to the Free Software Foundation, Inc.,
//  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA,
//  or see see <http://gnu.org/licenses/gpl-2.0.txt>

#ifndef TIMERRUNNER_H
#define TIMERRUNNER_H

#include "displayView.h"
#include "led-matrix.h"
#include "graphics.h"

using rgb_matrix::Canvas;
using rgb_matrix::Font;
using rgb_matrix::Color;


class TimerRunner {
public:
    TimerRunner();
    virtual ~TimerRunner();
    
    void next();
    void idle(Canvas*);
    void idle(Canvas*,displayView);
    void round(Canvas*,int preparation,int timer,int ends,bool groups);
    void addEnd();
    void delEnd();
    void setClisock(int);
    void runtext(Canvas*,char* text);
    void timer(Canvas*, int hours, int minutes, int seconds);
    void showClock(Canvas*);
private:
    int clisock, fEnds;
    bool doRun = false;
    bool init = true;
    bool sthNewPossible = true;
    bool roundInProgress = false;
    displayView *display;
    void honk(int);
    void sendUpdate(int timer, int color, int group, int end, int max_ends);
    void sendUpdate(int hours, int minutes, int seconds);
};

#endif /* TIMERRUNNER_H */

