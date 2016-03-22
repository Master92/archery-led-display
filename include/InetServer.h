/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   InetServer.h
 * Author: nils
 *
 * Created on 6. März 2016, 08:47
 */

#ifndef INETSERVER_H
#define INETSERVER_H

#include "displayView.h"
#include "TimerRunner.h"
#include "led-matrix.h"


class InetServer {
public:
    InetServer(Canvas*,TimerRunner*,displayView*);
    InetServer(const InetServer& orig);
    virtual ~InetServer();
    void acceptThread();
    
    void handleEverything();
    void callDisplayThread(char*);
    bool keepRunning();
private:
    int servsock, clisock;
    Canvas* canvas;
    TimerRunner* timer;
    displayView* display;
};

#endif /* INETSERVER_H */

