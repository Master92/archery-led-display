/* 
 * File:   main.cpp
 * Author: nils
 *
 * Created on 3. März 2016, 11:58
 */

#include <stdlib.h>
#include <chrono>
#include <thread>
#include <iostream>

#include "led-matrix.h"
#include "graphics.h"
#include "displayView.h"
#include "TimerRunner.h"

using namespace std;
using rgb_matrix::GPIO;
using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;
using rgb_matrix::Font;

const int MODE_INDOOR_WA = 0;
const int MODE_OUTDOOR_WA = 1;
const int MODE_LIGA = 2;

void callDisplayThread(Canvas* canvas, TimerRunner* timer, const int mode) {
    switch(mode) {
        case MODE_INDOOR_WA:
            timer->WAIndoor(canvas);
            break;
        
        default:
            break;
    }
}
/*
 * 
 */
int main(int argc, char** argv) {
    displayView dp;
    GPIO io;
    if(!io.Init())
        return 1;
    
    int rows = 16;
    int chain = 1;
    int parallel = 2;
    
    Canvas *canvas = new RGBMatrix(&io, rows, chain, parallel);
    
    TimerRunner timer;
//    timer.WAIndoor(canvas);
    
    std::thread t1(callDisplayThread, canvas, &timer, MODE_INDOOR_WA);
    
    getchar();
    timer.Abort();
    t1.join();
    
    return 0;
}

