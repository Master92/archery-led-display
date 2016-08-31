/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TimerRunner.h
 * Author: nils
 *
 * Created on 4. März 2016, 16:28
 */

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
    TimerRunner(const TimerRunner& orig);
    virtual ~TimerRunner();
    
    void addEnd();
    void next();
    void idle(Canvas*);
    void idle(Canvas*,displayView);
    void round(Canvas*,int preparation,int timer,int ends,bool groups);
    void setClisock(int);
    void runtext(Canvas*,char* text);
    void timer(Canvas*, int hours, int minutes, int seconds);
    void showClock(Canvas*);
private:
    int clisock, fEnds;
    bool doRun = false;
    bool init = true;
    bool sthNewPossible = true;
    void honk(int);
    void sendUpdate(int timer, int color, int group, int end, int max_ends);
};

#endif /* TIMERRUNNER_H */

