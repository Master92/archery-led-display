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

TimerRunner::TimerRunner() {
}

TimerRunner::TimerRunner(const TimerRunner& orig) {
}

TimerRunner::~TimerRunner() {
}

void TimerRunner::setClisock(int sock) {
    clisock = sock;
}


void TimerRunner::next() {
    countDown = false;
}

void TimerRunner::idle(Canvas* canvas, displayView display) {
    while (countDown) {
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

void TimerRunner::round(Canvas* canvas, int preparation, int timer, int ends, bool abcd) {
    Font fontMisc, fontBig, fontTimer;
    fontMisc.LoadFont("/etc/archery-led-display/fonts/5x8.bdf");
    fontBig.LoadFont("/etc/archery-led-display/fonts/10x20.bdf");
    fontTimer.LoadFont("/etc/archery-led-display/fonts/10x20.bdf");
    
    displayView display;
    
    display.clear(canvas);
    display.reset();
    display.setMaxEnds(ends);
    
    if(abcd)
        display.toggleGroup(canvas, fontBig);
    
    for(int end = 0; end < ends; end++) {
        display.colorSign(canvas, Color(255,0,0));
        display.nextEnd(canvas, fontMisc);
        
        for(int group = (abcd) ? 0 : 1; group < 2; group++) {
            countDown = true;
            
            if(abcd && group == 1)
                display.toggleGroup(canvas, fontBig);
            
            honk(2);
            for(int i = preparation; i > 0; i--) {
                sendUpdate(i, aip::COLOR_RED, group, end);
                display.colorSign(canvas, Color(255,0,0));
                display.remainingTime(canvas, fontTimer, i);
                
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            
            honk(1);
            for(int i = timer; i > 0 && countDown; i--) {
                Color c = Color(0,255,0);
                int cUpdate;
                
                if(i > 30) {
                    c = Color(0,255,0);
                    cUpdate = aip::COLOR_GREEN;
                } else {
                    c = Color(255,255,0);
                    cUpdate = aip::COLOR_YELLOW;
                }
                sendUpdate(i, cUpdate, group, end);
                
                display.colorSign(canvas, c);
                display.remainingTime(canvas, fontTimer, i);
                
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            sendUpdate(0, aip::COLOR_RED, group, end);
        }
        
        honk(3);
        display.remainingTime(canvas, fontTimer, 0);
        countDown = true;
        
        idle(canvas, display);
    }
}


void TimerRunner::honk(int n) {
    char* s;
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
    
    system(s);
}

void TimerRunner::sendUpdate(int timer, int color, int group, int end) {
    char buffer[4];
    buffer[0] = timer;
    buffer[1] = color;
    buffer[2] = group;
    buffer[3] = end;
    
    send(clisock, buffer, strlen(buffer), MSG_CONFIRM);
    std::cout << "Sent update\n";
}
