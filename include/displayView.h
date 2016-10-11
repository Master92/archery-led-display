//  Copyright (C) 2016 Nils Friedchen <nils.friedchen@googlemail.com>
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation version 2.
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

#ifndef DISPLAYVIEW_H
#define DISPLAYVIEW_H

#include "led-matrix.h"
#include "graphics.h"

using rgb_matrix::Canvas;
using rgb_matrix::Color;
using rgb_matrix::Font;

class displayView {
public:
    displayView();
    virtual ~displayView();
    
    void clear(Canvas*);
    void colorSign(Canvas*,const Color&);
    void toggleGroup(Canvas*,const Font&);
    void remainingTime(Canvas*,const Font&,int);
    void nextEnd(Canvas*,const Font&);
    void reset();
    void setMaxEnds(int);
    void printText(Canvas*,const Font&,int,int,const Color&,char*);
    void clearTextClockTimer(Canvas*);
    void addEnd();
    void delEnd();
    void updateEnds(Canvas* canvas, const Font& font);
private:
    void updateEnd(Canvas*,const Font&,int);
    void fillSquare(Canvas*,int,int,int,int,const Color&);
    void fillCircle(Canvas*,int,int,int,const Color&);
    
    int group = 1;
    int end = 0;
    int max_ends = 10;
};

#endif /* DISPLAYVIEW_H */

