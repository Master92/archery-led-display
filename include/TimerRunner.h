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
    
    void Abort();
    void WAIndoor(Canvas*);
private:
    bool countDown = false;
};

#endif /* TIMERRUNNER_H */

