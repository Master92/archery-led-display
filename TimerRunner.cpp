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
#include <stdlib.h>
#include <unistd.h>

TimerRunner::TimerRunner() {
}

TimerRunner::TimerRunner(const TimerRunner& orig) {
}

TimerRunner::~TimerRunner() {
}

void TimerRunner::next() {
    countDown = false;
}

void TimerRunner::shootIn(Canvas* canvas, int maxEnds, bool indoor) {
    Font fontMisc, fontTimer;
    fontMisc.LoadFont("matrix/fonts/5x8.bdf");
    fontTimer.LoadFont("matrix/fonts/10x20.bdf");
    
    displayView display;
    
    display.reset();
    display.setMaxEnds(maxEnds);
    display.toggleGroup(canvas, fontMisc);
    
    for(int end = 0; end < maxEnds; end++) {
        display.colorSign(canvas, Color(255,0,0));
        display.nextEnd(canvas, fontMisc);
        
        for(int group = 0; group < 2; group++) {
            countDown = true;
            
            if(group == 1)
                display.toggleGroup(canvas, fontMisc);
            
            for(int i = 10; i > 0; i--) {
                
                display.colorSign(canvas, Color(255,0,0));
                display.remainingTime(canvas, fontTimer, i);
                
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            
            for(int i = (indoor) ? 120 : 240; i > 0 && countDown; i--) {
                Color c = (i > 30) ? Color(0,255,0) : Color(255,255,0);
                
                display.colorSign(canvas, c);
                display.remainingTime(canvas, fontTimer, i);
                
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }
        
        display.remainingTime(canvas, fontTimer, 0);
        countDown = true;
        
        idle(canvas, display);
    }
}


void TimerRunner::WAIndoor(Canvas* canvas) {
    Font fontMisc, fontBig, fontTimer;
    fontMisc.LoadFont("matrix/fonts/5x8.bdf");
    fontBig.LoadFont("matrix/fonts/10x20.bdf");
    fontTimer.LoadFont("matrix/fonts/10x20.bdf");
    
    displayView display;
    
    display.reset();
    display.setMaxEnds(10);
    display.toggleGroup(canvas, fontBig);
//    display.UpdateEnd(canvas, fontMisc, 0);
    for(int end = 0; end < 10; end++) {
        display.colorSign(canvas, Color(255,0,0));
        display.nextEnd(canvas, fontMisc);
        
        for(int group = 0; group < 2; group++) {
            countDown = true;
            
            if (group == 1)
                display.toggleGroup(canvas, fontBig);
            
            honk(2);
            for(int i = 10; i > 0; i--) {
                display.colorSign(canvas, Color(255,0,0));
                display.remainingTime(canvas, fontTimer, i);
                
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            
            honk(1);
            for(int i = 120; i > 0 && countDown; i--) {
                Color c = (i > 30) ? Color(0,255,0) : Color(255,255,0);
                display.colorSign(canvas, c);
                display.remainingTime(canvas, fontTimer, i);
                
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }
        
        honk(3);
        display.remainingTime(canvas, fontTimer, 0);
        countDown = true;
        
        idle(canvas, display);
    }
}

void TimerRunner::idle(Canvas* canvas, displayView display) {
    bool red = true;
    while (countDown) {
//        if(red) {
//            display.colorSign(canvas, Color(255,0,0));
//            red = false;
//        } else {
//            display.colorSign(canvas, Color(0,0,0));
//            red = true;
//        }
//        
//        std::this_thread::sleep_for(std::chrono::seconds(1));
        for(int i = 255; i >= 0 && countDown; i--) {
            display.colorSign(canvas, Color(i,0,0));
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
        
        for(int i = 0; i < 256 && countDown; i++) {
            display.colorSign(canvas, Color(i,0,0));
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
    }
}

void TimerRunner::honk(int n) {
    char* s;
    switch(n) {
        case 1:
            s = "aplay res/sounds/horn001.wav &";
            break;
            
        case 2:
            s = "aplay res/sounds/horn002.wav &";
            break;
            
        default:
            s = "aplay res/sounds/horn003.wav &";
            break;
    }
    
    system(s);
}


