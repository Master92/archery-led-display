/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   displayView.h
 * Author: nils
 *
 * Created on 4. März 2016, 08:28
 */

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
    displayView(const displayView& orig);
    virtual ~displayView();
    
    void clear(Canvas*);
    void colorSign(Canvas*,const Color&);
    void toggleGroup(Canvas*,const Font&);
    void remainingTime(Canvas*,const Font&,int);
    void nextEnd(Canvas*,const Font&);
    void reset();
    void setMaxEnds(int);
    //void runtext(Canvas*,const Font&,char*);
    void printText(Canvas*,const Font&,int,int,const Color&,char*);
private:
    void updateEnd(Canvas*,const Font&,int);
    void fillSquare(Canvas*,int,int,int,int,const Color&);
    void fillCircle(Canvas*,int,int,int,const Color&);
    
    int group = 1;
    int end = 0;
    int max_ends = 10;
};

#endif /* DISPLAYVIEW_H */

