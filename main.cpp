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
#include "InetServer.h"

using namespace std;
using rgb_matrix::GPIO;
using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;
using rgb_matrix::Font;

void callListenThread(InetServer* server) {
    server->handleEverything();
}

void callAccept(InetServer* server) {
    server->acceptThread();
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
    int chain = 3;
    int parallel = 2;
    
    Canvas *canvas = new RGBMatrix(&io, rows, chain, parallel);
    
    displayView *display = new displayView();
    TimerRunner *timer = new TimerRunner();
    InetServer *server = new InetServer(canvas, timer, display);
    
    std::cout << "Waiting for connections\n";
    server->acceptThread();
    std::cout << "Listening\n";
    std::thread t(callListenThread, server);

    t.join();
    
    return 0;
}

