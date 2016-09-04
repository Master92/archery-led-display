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

#include "displayView.h"
#include <iostream>
#include <string.h>

using rgb_matrix::GPIO;
using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;
using rgb_matrix::Color;


displayView::displayView() {

}

displayView::~displayView() {

}

void displayView::clear(Canvas* canvas) {
    fillSquare(canvas, 0, 0, canvas->width(), canvas->height(), Color(0,0,0));
}


void displayView::colorSign(Canvas* canvas, const Color& color) {
    displayView::fillSquare(canvas, 0, 0, 16, 16, color);
}

void displayView::toggleGroup(Canvas* canvas, const Font& font) {
    group = (group) ? 0 : 1;
    const char* sgroup = (group == 1) ? "C/D" : "A/B";

    displayView::fillSquare(canvas, 32, 0, 32, font.baseline(), Color(0,0,0));
    rgb_matrix::DrawText(canvas, font, 32, font.baseline()-2, Color(255,255,0), sgroup);
}

void displayView::remainingTime(Canvas* canvas, const Font& font, int time) {
    std::string s = std::to_string(time);
    int x = (time >= 100) ? 33 : (time >= 10) ? 38 : 43;
    displayView::fillSquare(canvas, 33, 16, 48, 16, Color(0,0,0));
    rgb_matrix::DrawText(canvas, font, x, 32 - font.baseline() + 14, Color(255,125,0), s.c_str());
}

void displayView::nextEnd(Canvas* canvas, const Font& font) {
    updateEnd(canvas, font, ++end);
}

void displayView::reset() {
    group = 1;
    end = 0;
}

void displayView::setMaxEnds(int max) {
    max_ends = max;
}

void displayView::printText(Canvas* canvas, const Font& font, int x, int y, const Color& color, char* text) {
    rgb_matrix::DrawText(canvas, font, x, y, color, text);
}

void displayView::updateEnd(Canvas* canvas,const Font& font, int new_end) {
    end = new_end;
    std::string s = std::to_string(end) + "/" + std::to_string(max_ends);
    fillSquare(canvas, 65, 0, 32, 16, Color(0,0,0));
    rgb_matrix::DrawText(canvas, font, 68, font.baseline()-1, Color(255,255,255), "Passe");
    rgb_matrix::DrawText(canvas, font, 70, font.baseline()*2, Color(0,255,0), s.c_str());
}

void displayView::fillSquare(Canvas* canvas, int x, int y, int width, int height, const Color& color) {
    for (int i = 0; i < height; i++) {
        rgb_matrix::DrawLine(canvas, x, y + i, x + width, y + i, color);
    }
}

void displayView::fillCircle(Canvas* canvas, int x, int y, int radius, const Color& color) {
    for (int i = radius; i > 0; i--) {
        rgb_matrix::DrawCircle(canvas, x, y, i, color);
    }
}
    