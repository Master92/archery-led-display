//  Copyright (C) 2016 Nils Friedchen <nils.friedchen@googlemail.com>
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
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
    
    while(true) {
        std::cout << "Waiting for connections\n";
        server->acceptThread();
        std::cout << "Listening\n";
        std::thread t(callListenThread, server);

        t.join();
    }
    
    return 0;
}

