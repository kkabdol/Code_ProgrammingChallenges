//
//  main.cpp
//  Problem10267_GraphicalEditor
//
//  Created by Seonghyeon Choe on 12/26/12.
//  Copyright (c) 2012 Seonghyeon Choe. All rights reserved.
//

#include <iostream>
#include <string>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
#ifndef ONLINE_JUDGE
#include <fstream>
#endif
/*
 
 x > 0
 y > 0
 
 I 5 6
 L 2 3 A
 S one.bmp
 G 2 3 J
 F 3 3 J
 V 2 3 4 W
 H 3 4 2 Z
 S two.bmp
 X
 
 one.bmp
 OOOOO
 OOOOO
 OAOOO
 OOOOO
 OOOOO
 OOOOO
 two.bmp
 JJJJJ
 JJZZJ
 JWJJJ
 JWJJJ
 JJJJJ
 JJJJJ
 
 */

#define MAX_WIDTH 250
#define MAX_HEIGHT 250

typedef char Color;
typedef char Command;
const Color cWhite = '0';

class Point {
public:
    Point(int x=0, int y=0) { this->x = x; this->y = y; };
    ~Point() {};
    
    int getX() const {return this->x;};
    int getY() const {return this->y;};
    
private:
    int x;
    int y;
};



class Editor {
public:
    Editor();
    ~Editor();
    
    void create(int width, int height);
    void clear();
    void drawColor(int x, int y, Color c);
    void drawVLine(int x, int y1, int y2, Color c);
    void drawHLine(int x1, int x2, int y, Color c);
    void fillRect(int left, int top, int right, int bottom, Color c);
    void floodColor(int x, int y, Color c);
    void saveFile(const std::string& filename) const;
    
private:
    void init(int width, int height);
    void release();
    inline Color getColorAt(int x, int y) const;
    inline void setColorAt(int x, int y, Color c);
    void print() const;
    
    
    int width, height;
    Color pixels[MAX_WIDTH][MAX_HEIGHT];
    
};

int main(int argc, const char * argv[])
{
    std::istream in(std::cin.rdbuf());
#ifndef ONLINE_JUDGE
    std::ifstream fin("testcase.txt");  // declarations of streams fp_in and fp_out
    if (fin) {
        in.rdbuf(fin.rdbuf());
    } else {
        std::cout << "can not read testcase.txt" << std::endl;
    }
    
#endif
    
    Editor editor;
    
    Command cmd;
    Color c;

    bool isRunning = true;
    
    while (isRunning) {
        in >> cmd;
        
        switch (cmd) {
            case 'I': {
                int w, h;
                in >> w >> h;
                editor.create(w, h);
            }
                break;
            case 'C': {
                editor.clear();
            }
                break;
            case 'L': {
                int x, y;
                in >> x >> y >> c;
                editor.drawColor(x, y, c);
            }
                break;
            case 'V': {
                int x, y1, y2;
                in >> x >> y1 >> y2 >> c;
                editor.drawVLine(x, y1, y2, c);
            }
                break;
            case 'H': {
                int x1, x2, y;
                in >> x1 >> x2 >> y >> c;
                editor.drawHLine(x1, x2, y, c);
            }
                break;
            case 'K': {
                int x1, x2, y1, y2;
                in >> x1 >> x2 >> y1 >> y2 >> c;
                editor.fillRect(x1, x2, y1, y2, c);
            }
                break;
            case 'F': {
                int x, y;
                in >> x >> y >> c;
                editor.floodColor(x, y, c);
            }
                break;
            case 'S': {
                std::string filename;
                in >> filename;
                editor.saveFile(filename);
            }
                break;
            case 'X': {
                isRunning = false;
            }
                break;
                
            default:
                break;
        }
        
    };
    
#ifndef ONLINE_JUDGE
    fin.close();
#endif
    return 0;
}

Editor::Editor() {
    this->width = 0;
    this->height = 0;
}


Editor::~Editor() {
    this->release();
}



void Editor::create(int width, int height) {
    this->init(width, height);
}

void Editor::clear() {
    for (int y=1; y<=this->height; ++y) {
        drawHLine(1, this->width, y, cWhite);
    }
}
void Editor::drawColor(int x, int y, Color c) {
    this->pixels[y-1][x-1] = c;
}
void Editor::drawVLine(int x, int y1, int y2, Color c) {
    const int start = (y1 < y2) ? y1 : y2;
    const int end = start + abs(y2 - y1);
    
    for (int y=start; y<=end; ++y) {
        drawColor(x, y, c);
    }
}
void Editor::drawHLine(int x1, int x2, int y, Color c) {
    const int start = (x1 < x2) ? x1 : x2;
    const int end = start + abs(x2 - x1);
    
    memset(&(this->pixels[y-1][start-1]), c, sizeof(Color)*(end-start+1));
}
void Editor::fillRect(int left, int top, int right, int bottom, Color c) {
    for (int y=top; y<=bottom; ++y) {
        drawHLine(left, right, y, c);
    }
}

static Point g_FloodPos[MAX_HEIGHT*MAX_WIDTH];
static int g_NumOfFloods = 0;
static int g_CurFloods = 0;

void Editor::floodColor(int x, int y, Color c) {
    const Color oldC = this->getColorAt(x, y);
    
    g_NumOfFloods = 1;
    g_CurFloods = 0;
    g_FloodPos[g_CurFloods] = Point(x,y);
    
    do {
        const Point pos = g_FloodPos[g_CurFloods];
        g_CurFloods = (g_CurFloods+1) % (MAX_HEIGHT*MAX_WIDTH);

        const int x = pos.getX();
        const int y = pos.getY();
        this->drawColor(x, y, c);

        // right
        if (x+1 <= this->width && this->getColorAt(x+1, y) == oldC) {
            this->drawColor(x+1, y, c);
            g_FloodPos[g_NumOfFloods] = Point(x+1, y);
            g_NumOfFloods = (g_NumOfFloods+1) % (MAX_HEIGHT*MAX_WIDTH);
        }
        // left
        if (x-1 >= 1 && this->getColorAt(x-1, y) == oldC) {
            this->drawColor(x-1, y, c);
            g_FloodPos[g_NumOfFloods] = Point(x-1, y);
            g_NumOfFloods = (g_NumOfFloods+1) % (MAX_HEIGHT*MAX_WIDTH);
        }
        // lower
        if (y+1 <= this->height && this->getColorAt(x, y+1) == oldC) {
            this->drawColor(x, y+1, c);
            g_FloodPos[g_NumOfFloods] = Point(x, y+1);
            g_NumOfFloods = (g_NumOfFloods+1) % (MAX_HEIGHT*MAX_WIDTH);
        }
        // upper
        if (y-1 >= 1 && this->getColorAt(x, y-1) == oldC) {
            this->drawColor(x, y-1, c);
            g_FloodPos[g_NumOfFloods] = Point(x, y-1);
            g_NumOfFloods = (g_NumOfFloods+1) % (MAX_HEIGHT*MAX_WIDTH);

        }

        
    } while (g_CurFloods != g_NumOfFloods);
    
}

void Editor::saveFile(const std::string& filename) const {
    std::cout << filename << std::endl;
    
    this->print();
}


void Editor::init(int width, int height) {
    
    this->width = width;
    this->height = height;
    
    for (int y=1; y<=MAX_HEIGHT; ++y) {
        drawHLine(1, MAX_WIDTH, y, 0);
    }
    
    this->clear();
    
}
void Editor::release() {
    this->width = 0;
    this->height = 0;
}

inline Color Editor::getColorAt(int x, int y) const {
    return this->pixels[y-1][x-1];
}



void Editor::print() const {
    for (int y=1; y<=this->height; ++y) {
        std::cout << this->pixels[y-1] << std::endl;
    }    
}