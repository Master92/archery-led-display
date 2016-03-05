/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   displayView.cpp
 * Author: nils
 * 
 * Created on 4. März 2016, 08:28
 */

#include "displayView.h"
#include <iostream>
#include <string.h>

using rgb_matrix::GPIO;
using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;
using rgb_matrix::Color;


displayView::displayView() {

}

displayView::displayView(const displayView& orig) {
}

displayView::~displayView() {

}

void displayView::DrawSomething(Canvas* canvas) {
    displayView::FillSquare(canvas, 0, 0, 32, 32, Color(255, 255, 255));
}

void displayView::ColorSign(Canvas* canvas, const Color& color) {
    displayView::FillSquare(canvas, 0, 0, 16, 16, color);
}

void displayView::ToggleGroup(Canvas* canvas, const Font& font) {
    group = (group) ? 0 : 1;
    const char* sgroup = (group == 1) ? "C/D" : "A/B";

    displayView::FillSquare(canvas, 16, font.baseline(), 16, font.baseline(), Color(0,0,0));
    rgb_matrix::DrawText(canvas, font, 17, font.baseline()*2, Color(255,255,255), sgroup);
}

void displayView::RemainingTime(Canvas* canvas, const Font& font, int time) {
    std::string s = std::to_string(time);
    int x = (time >= 100) ? 0 : (time >= 10) ? 5 : 10;
    displayView::FillSquare(canvas, 0, 16, 32, 16, Color(0,0,0));
    rgb_matrix::DrawText(canvas, font, x, 32 - font.baseline() + 14, Color(255,125,0), s.c_str());
}

void displayView::UpdateEnd(Canvas* canvas,const Font& font, int new_end) {
    end = new_end;
    std::string s = std::to_string(end) + "/" + std::to_string(max_ends);
    FillSquare(canvas, 16, 0, 16, font.baseline(), Color(0,0,0));
    rgb_matrix::DrawText(canvas, font, 17, font.baseline(), Color(255,0,0), s.c_str());
}

void displayView::nextEnd(Canvas* canvas, const Font& font) {
    UpdateEnd(canvas, font, end + 1);
}

void displayView::FillSquare(Canvas* canvas, int x, int y, int width, int height, const Color& color) {
    for (int i = 0; i < height; i++) {
        rgb_matrix::DrawLine(canvas, x, y + i, x + width, y + i, color);
    }
}

void displayView::FillCircle(Canvas* canvas, int x, int y, int radius, const Color& color) {
    for (int i = radius; i > 0; i--) {
        rgb_matrix::DrawCircle(canvas, x, y, i, color);
    }
}
    