/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   InetServer.cpp
 * Author: nils
 * 
 * Created on 6. März 2016, 08:47
 */

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
    char buffer[256], b2[256];
    std::string s;
    bool readOn = true;
    
    while(readOn) {
//        if(read(clisock, buffer, 255) == 0)
//            readOn = false;
        
        if(recv(clisock, buffer, 2, MSG_WAITALL) == 0)
            readOn = false;
        
        strcpy(b2, buffer);
        
        std::cout << b2;
        std::thread t (&InetServer::callDisplayThread, this, b2);
        t.detach();
        
//        CallDisplayThread(command);
        
        bzero(buffer, 256);
    }
    
    close(clisock);
}

void InetServer::callDisplayThread(char* buffer) {
    int command = int(buffer[0]);
    int ends = int(buffer[1]);
    bzero(buffer, sizeof(buffer));
    
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
    }
}
