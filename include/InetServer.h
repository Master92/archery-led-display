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

