/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TimerRunner.cpp
 * Author: nils
 * 
 * Created on 4. März 2016, 16:28
 */

#include "TimerRunner.h"
#include "displayView.h"
#include <thread>
#include <chrono>
#include <iostream>

TimerRunner::TimerRunner() {
}

TimerRunner::TimerRunner(const TimerRunner& orig) {
}

TimerRunner::~TimerRunner() {
}

void TimerRunner::Abort() {
    countDown = false;
}

void TimerRunner::WAIndoor(Canvas* canvas) {
    Font fontMisc, fontTimer;
    fontMisc.LoadFont("matrix/fonts/5x8.bdf");
    fontTimer.LoadFont("matrix/fonts/10x20.bdf");
    
    displayView display;
    
    display.ToggleGroup(canvas, fontMisc);
    display.UpdateEnd(canvas, fontMisc, 0);
    for(int end = 0; end < 10; end++) {
        display.ColorSign(canvas, Color(255,0,0));
        display.nextEnd(canvas, fontMisc);
        
        for(int group = 0; group < 2; group++) {
            countDown = true;
            
            if (group == 1)
                display.ToggleGroup(canvas, fontMisc);
            
            for(int i = 10; i > 0; i--) {
                display.ColorSign(canvas, Color(255,0,0));
                display.RemainingTime(canvas, fontTimer, i);
                
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            
            for(int i = 120; i > 0 && countDown; i--) {
                Color c = (i > 30) ? Color(0,255,0) : Color(255,255,0);
                display.ColorSign(canvas, c);
                display.RemainingTime(canvas, fontTimer, i);
                
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }
        display.ColorSign(canvas, Color(255,0,0));
        display.RemainingTime(canvas, fontTimer, 0);
        
        std::cout << "Press any key to continue. . .\n";
        getchar();
    }
    
}
