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

#include "InetServer.h"
#include "aipprotocol.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <thread>
#include <iostream>


InetServer::InetServer(Canvas* c, TimerRunner* tr, displayView* d) {
    canvas = c;
    timer = tr;
    display = d;
    
    struct sockaddr_in serv_addr;
    
    servsock = socket(AF_INET, SOCK_STREAM, 0);
    if(servsock < 0)
        std::cout << "Error on opening socket\n";
    bzero(&serv_addr, sizeof(sockaddr_in));
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(aip::PORT);
    
    if(bind(servsock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0)
        std::cout << "Error on binding\n";
    listen(servsock, 1);
    
}

void InetServer::acceptThread() {
    struct sockaddr_in cli_addr;
    socklen_t clilen = sizeof(cli_addr);
    clisock = accept(servsock, (struct sockaddr *) &cli_addr, &clilen);
    timer->setClisock(clisock);
    if(clisock < 0)
        std::cout << "Error on accept";
}

InetServer::InetServer(const InetServer& orig) {
}

InetServer::~InetServer() {
    if(!(clisock < 0)) {
        close(clisock);
    }
    
    close(servsock);
}

void InetServer::handleEverything() {
    char buffer[129], b2[129];
    bool readOn = true;
    
    while(readOn) {
        if(recv(clisock, buffer, 1, MSG_PEEK) == 0)
            readOn = false;
        
        read(clisock, buffer, buffer[0]);
        
        strcpy(b2, buffer);

        std::thread t (&InetServer::callDisplayThread, this, b2);
        t.detach();
        
        bzero(buffer, 129);
    }
    
    close(clisock);
}

void InetServer::callDisplayThread(char* buffer) {
    int command = int(buffer[1]);
    int ends = int(buffer[2]);
    int preparation = int(buffer[3]);
    int duration = int(buffer[4]) * 10 + int(buffer[5]);
    bool groups = (buffer[6] == '0') ? false : true;
    char text[127];
    
    switch(command) {
        case aip::NEXT:
            std::cout << "Skipping to next\n";
            timer->next();
            break;
            
        case aip::SHOOT_IN:
            std::cout << "Starting shoot in programme with " << ends << " ends\n";
            timer->round(canvas, 10, 120, ends, true);
            break;

        case aip::WAINDOOR:
            std::cout << "Starting WA indoor programme\n";
            timer->round(canvas, 10, 120, 10, true);
            break;
            
        case aip::WAOUTDOOR:
            std::cout << "Starting WA outdoor programme\n";
            timer->round(canvas, 10, 240, 6, true);
            break;
            
        case aip::FINALE:
            std::cout << "Starting finale programme with " << ends << " ends\n";
            timer->round(canvas, 10, 120, ends, false);
            break;
            
        case aip::NEW_ROUND:
            std::cout << "New round" << std::endl;
            timer->round(canvas, preparation, duration, ends, groups);
            break;
            
        case aip::RUNTEXT:
            for(int i = 0; i < int(buffer[0]-2); i++) {
                text[i] = buffer[i+2];
            }
            text[buffer[1]] = '\0';
            std::cout << "Received runtext" << std::endl;
            
            timer->runtext(canvas, text);
            break;
            
        case aip::TIMER:
            timer->timer(canvas, buffer[2], buffer[3], buffer[4]);
            break;
            
        case aip::TIME:
            timer->showClock(canvas);
            break;
            
        case aip::SYNC:
            char time[19];
            for(int i = 0; i < 4; i++) {
                time[i] = buffer[i+2];
            }
            time[4] = '-';
            time[5] = buffer[7];
            time[6] = buffer[8];
            time[7] = '-';
            time[8] = buffer[9];
            time[9] = buffer[10];
            time[10] = ' ';
            time[11] = buffer[11];
            time[12] = buffer[12];
            time[13] = ':';
            time[14] = buffer[13];
            time[15] = buffer[14];
            time[16] = ':';
            time[17] = buffer[15];
            time[18] = buffer[16];
            std::string command = "date -s \"";
            command += time;
            command += "\"";
            
            std::cout << command << std::endl;
            //system(command.c_str());
            break;
    }
    
    bzero(buffer, sizeof(buffer));
}
