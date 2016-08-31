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
#include "include/aipprotocol.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

TimerRunner::TimerRunner() {
}

TimerRunner::TimerRunner(const TimerRunner& orig) {
}

TimerRunner::~TimerRunner() {
}

void TimerRunner::setClisock(int sock) {
    clisock = sock;
}

void TimerRunner::addEnd() {
    fEnds++;
}

void TimerRunner::next() {
    doRun = (doIdle) ? true : false;
}

void TimerRunner::idle(Canvas* canvas, displayView display) {
    while (doRun) {
        for(int i = 255; i >= 0 && doRun; i--) {
            display.colorSign(canvas, Color(i,0,0));
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
        
        for(int i = 0; i < 256 && doRun; i++) {
            display.colorSign(canvas, Color(i,0,0));
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
    }
    sthNewPossible = false;
}

void TimerRunner::idle(Canvas* canvas) {
    doRun = true;
    sthNewPossible = true;
    displayView display;
    idle(canvas, display);
}

void TimerRunner::runtext(Canvas* canvas, char* text) {
//    if (doRun && !doIdle)
//        return;
//    else if (doIdle) {
//        doIdle = false;
//        std::this_thread::sleep_for(std::chrono::seconds(2));
//    }
    if(!sthNewPossible)
        return;
    else {
        doRun = false;
        if(init)
            sthNewPossible = false;
        
        while(sthNewPossible) {
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
        }
    }
    
    sthNewPossible = doRun = true;
    Font font;
    displayView display;
    font.LoadFont("/etc/archery-led-display/fonts/10x20.bdf");
    
    int width = 0;
    int length = strlen(text);
    for(int i = 0; i < length; i++) {
        char c = text[i];
        width += font.CharacterWidth(c) + 3;
    }
    
    int left = -((length * 10) + canvas->width());
    while(doRun) {
        for(int i = canvas->width(); i > left; i--) {
            display.clear(canvas);
            display.printText(canvas, font, i, canvas->height()/2 + font.baseline()/2, Color(255,255,255), text);
            std::this_thread::sleep_for(std::chrono::milliseconds(35));
        }
    }
    sthNewPossible = false;
}

void TimerRunner::timer(Canvas* canvas, int hours, int minutes, int seconds) {
//    if (doRun && !doIdle)
//        return;
//    else if (doIdle) {
//        doIdle = false;
//    }
    
    if(!sthNewPossible)
        return;
    else {
        doRun = false;
        if(init)
            sthNewPossible = false;
        
        while(sthNewPossible) {
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
        }
    }
    
    sthNewPossible = true;
    doRun = true;
    Font font;
    displayView display;
    
    font.LoadFont("/etc/archery-led-display/fonts/10x20.bdf");
    int posX = 8, posY = canvas->height()/2 + font.baseline()/2;
    char text[posX];
    text[2] = ':';
    text[5] = ':';
    
    while(doRun) {
        text[0] = (hours > 9) ? 1 : 0;
        text[1] = (hours > 9) ? hours - 10 : hours;
        text[3] = (minutes > 9) ? floor(minutes/10) : 0;
        text[4] = (minutes > 9) ? minutes - (floor(minutes/10) * 10) : minutes;
        text[6] = (seconds > 9) ? floor(seconds/10) : 0;
        text[7] = (seconds > 9) ? seconds - (floor(seconds/10) * 10) : seconds;
        
        display.clear(canvas);
        display.printText(canvas, font, posX, posY, Color(255, 255, 255), text);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        
        if(seconds == 0) {
            if(minutes == 0) {
                if(hours == 0) {
                    
                } else {
                    --hours;
                    minutes = 59;
                    seconds = 59;
                }
            } else {
                --minutes;
                seconds = 59;
            }
        } else {
            --seconds;
        }
    }
    sthNewPossible = false;
}

void TimerRunner::showClock(Canvas* canvas) {
//    if(doRun && !doIdle) {
//        return;
//    } else if(doIdle) {
//        doIdle = false;
//        doRun = false;
//        std::this_thread::sleep_for(std::chrono::seconds(2));
//    }
    if(!sthNewPossible)
        return;
    else {
        doRun = false;
        if(init)
            sthNewPossible = false;
        
        while(sthNewPossible) {
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
        }
    }
    
    sthNewPossible = true;
    doRun = true;
    displayView dp;
    Font font;
    font.LoadFont("/etc/archery-led-display/fonts/10x20.bdf");
    int posX = (96 - 8 * 10) / 2;
    int posY = canvas->height()/2 + font.baseline()/2;
    
    time_t raw_time;
    struct tm * local_time;
    char time_str[9];
    
    while(doRun) {
        time(&raw_time);
        local_time = localtime(&raw_time);
        strftime(time_str, sizeof(time_str),"%H:%M:%S", local_time);
        dp.clear(canvas);
        dp.printText(canvas, font, posX, posY, Color(255,255,255), time_str);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
    sthNewPossible = false;
}

void TimerRunner::round(Canvas* canvas, int preparation, int timer, int ends, bool abcd) {
//    if(doRun && !doIdle) {
//        return;
//    } else if(doIdle) {
//        doIdle = false;
//        doRun = false;
//    }
    
    if(!sthNewPossible)
        return;
    else {
        doRun = false;
        if(init)
            sthNewPossible = false;
        
        while(sthNewPossible) {
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
        }
    }
    
    Font fontMisc, fontBig, fontTimer;
    fontMisc.LoadFont("/etc/archery-led-display/fonts/5x8.bdf");
    fontBig.LoadFont("/etc/archery-led-display/fonts/10x20.bdf");
    fontTimer.LoadFont("/etc/archery-led-display/fonts/10x20.bdf");
    fEnds = ends;
    
    displayView display;
    
    display.clear(canvas);
    display.reset();
    display.setMaxEnds(fEnds);
    
    if(abcd)
        display.toggleGroup(canvas, fontBig);
    
    for(int end = 0; end < fEnds; end++) {
        display.colorSign(canvas, Color(255,0,0));
        display.nextEnd(canvas, fontMisc);
        
        for(int group = (abcd) ? 0 : 1; group < 2; group++) {
            doRun = true;
            
            if(abcd && group == 1)
                display.toggleGroup(canvas, fontBig);
            
            honk(2);
            for(int i = preparation; i > 0; i--) {
                sendUpdate(i, aip::COLOR_RED, group, end, fEnds);
                display.colorSign(canvas, Color(255,0,0));
                display.remainingTime(canvas, fontTimer, i);
                
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            
            honk(1);
            for(int i = timer; i > 0 && doRun; i--) {
                Color c = Color(0,255,0);
                int cUpdate;
                
                if(i > 30) {
                    c = Color(0,255,0);
                    cUpdate = aip::COLOR_GREEN;
                } else {
                    c = Color(255,255,0);
                    cUpdate = aip::COLOR_YELLOW;
                }
                sendUpdate(i, cUpdate, group, end, fEnds);
                
                display.colorSign(canvas, c);
                display.remainingTime(canvas, fontTimer, i);
                
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            sendUpdate(0, aip::COLOR_RED, group, end, fEnds);
        }
        
        honk(3);
        display.remainingTime(canvas, fontTimer, 0);
        doRun = true;
        
        if(end + 1 == fEnds) {
            sthNewPossible = true;
        }
        idle(canvas, display);
    }
}


void TimerRunner::honk(int n) {
    std::string s;
    switch(n) {
        case 1:
            s = "aplay -q /etc/archery-led-display/sounds/horn001.wav &";
            break;
            
        case 2:
            s = "aplay -q /etc/archery-led-display/sounds/horn002.wav &";
            break;
            
        default:
            s = "aplay -q /etc/archery-led-display/sounds/horn003.wav &";
            break;
    }
    const char* command = s.c_str();
    
    system(command);
}

void TimerRunner::sendUpdate(int timer, int color, int group, int end, int max_ends) {
    char buffer[7];
    buffer[0] = aip::UPDATE;
    buffer[1] = timer/10;
    buffer[2] = timer - buffer[1]*10;
    buffer[3] = color;
    buffer[4] = group;
    buffer[5] = end;
    buffer[6] = max_ends;
    
    send(clisock, buffer, strlen(buffer), MSG_CONFIRM);
}
