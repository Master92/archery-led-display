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
    
    void DrawSomething(Canvas*);
    void ColorSign(Canvas*,const Color&);
    void ToggleGroup(Canvas*,const Font&);
    void RemainingTime(Canvas*,const Font&,int);
    void UpdateEnd(Canvas*,const Font&,int);
    void nextEnd(Canvas*,const Font&);
private:
    void FillSquare(Canvas*,int,int,int,int,const Color&);
    void FillCircle(Canvas*,int,int,int,const Color&);
    
    int group = 1;
    int end = 0;
    int max_ends = 10;
};

#endif /* DISPLAYVIEW_H */

