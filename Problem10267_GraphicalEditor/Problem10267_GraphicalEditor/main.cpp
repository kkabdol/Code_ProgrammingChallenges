//
//  main.cpp
//  Problem10267_GraphicalEditor
//
//  Created by Seonghyeon Choe on 12/26/12.
//  Copyright (c) 2012 Seonghyeon Choe. All rights reserved.
//

#include <iostream>
#include <string>
#include <cassert>
#include <algorithm>

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


typedef char Color;
typedef char Command;
const Color cWhite = '0';


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
    void saveFile(const std::string& filename);
    
private:
    void init(int width, int height);
    void release();
    bool isInitialized();
    Color getColorAt(int x, int y);
    void setColorAt(int x, int y, Color c);
    void print();
    
    
    int width, height;
    Color *pixels;
    
};

int main(int argc, const char * argv[])
{

    Editor editor;
    
    Command cmd;
    Color c;

    bool isRunning = true;
    
    while (isRunning) {
        std::cin >> cmd;
        
        switch (cmd) {
            case 'I': {
                int w, h;
                std::cin >> w >> h;
                editor.create(w, h);
            }
                break;
            case 'C': {
                editor.clear();
            }
                break;
            case 'L': {
                int x, y;
                std::cin >> x >> y >> c;
                editor.drawColor(x, y, c);
            }
                break;
            case 'V': {
                int x, y1, y2;
                std::cin >> x >> y1 >> y2 >> c;
                editor.drawVLine(x, y1, y2, c);
            }
                break;
            case 'H': {
                int x1, x2, y;
                std::cin >> x1 >> x2 >> y >> c;
                editor.drawHLine(x1, x2, y, c);
            }
                break;
            case 'K': {
                int x1, x2, y1, y2;
                std::cin >> x1 >> x2 >> y1 >> y2 >> c;
                editor.fillRect(x1, x2, y1, y2, c);
            }
                break;
            case 'F': {
                int x, y;
                std::cin >> x >> y >> c;
                editor.floodColor(x, y, c);
            }
                break;
            case 'S': {
                std::string filename;
                std::cin >> filename;
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
    return 0;
}

Editor::Editor() {
    this->width = 0;
    this->height = 0;
    this->pixels = NULL;
}


Editor::~Editor() {
    if (this->isInitialized()) {
        this->release();
    }
}



void Editor::create(int width, int height) {
    if (this->isInitialized()) {
        this->release();
    }
    
    this->init(width, height);
}

void Editor::clear() {
    for (int y=1; y<=this->height; ++y) {
        for (int x=1; x<=this->width; ++x) {
            this->setColorAt(x, y, cWhite);
        }
        
    }
}
void Editor::drawColor(int x, int y, Color c) {
    this->setColorAt(x, y, c);
}
void Editor::drawVLine(int x, int y1, int y2, Color c) {
    const int start = (y1 < y2) ? y1 : y2;
    const int end = start + abs(y2 - y1);
    
    for (int y=start; y<=end; ++y) {
        setColorAt(x, y, c);
    }
}
void Editor::drawHLine(int x1, int x2, int y, Color c) {
    const int start = (x1 < x2) ? x1 : x2;
    const int end = start + abs(x2 - x1);
    
    for (int x=start; x<=end; ++x) {
        setColorAt(x, y, c);
    }
}
void Editor::fillRect(int left, int top, int right, int bottom, Color c) {
    for (int y=top; y<=bottom; ++y) {
        for (int x=left; x<=right; ++x) {
            this->setColorAt(x, y, c);
        }
        
    }
}
void Editor::floodColor(int x, int y, Color c) {
    const Color oldC = this->getColorAt(x, y);
    
    this->setColorAt(x, y, c);
    
    
#warning kkabdol. changed recursive to iterate
    // right
    if (x+1 <= this->width && this->getColorAt(x+1, y) == oldC) {
        this->floodColor(x+1, y, c);
    }
    // left
    if (x-1 >= 1 && this->getColorAt(x-1, y) == oldC) {
        this->floodColor(x-1, y, c);
    }
    // lower
    if (y+1 <= this->height && this->getColorAt(x, y+1) == oldC) {
        this->floodColor(x, y+1, c);
    }
    // upper
    if (y-1 >= 1 && this->getColorAt(x, y-1) == oldC) {
        this->floodColor(x, y-1, c);
    }
    
    
}


void Editor::init(int width, int height) {
    assert(!isInitialized());
    
    this->width = width;
    this->height = height;
    this->pixels = new Color[width*height];
    this->clear();
    
}
void Editor::release() {
    if (isInitialized()) {
        delete [] this->pixels;
        this->pixels = NULL;
        this->width = 0;
        this->height = 0;
    }
}

bool Editor::isInitialized() {
    if (this->pixels != NULL) {
        return true;
    } else {
        return false;
    }
}
Color Editor::getColorAt(int x, int y) {
    const int pos = this->width*(y-1) + (x-1);
    return this->pixels[pos];
}
void Editor::setColorAt(int x, int y, Color c) {
    const int pos = this->width*(y-1) + (x-1);
    this->pixels[pos] = c;
}

void Editor::saveFile(const std::string& filename) {
    std::cout << filename << std::endl;
    
    this->print();
}

void Editor::print() {
    for (int y=1; y<=this->height; ++y) {
        for (int x=1; x<=this->width; ++x) {
            std::cout << getColorAt(x, y);
        }
        std::cout << std::endl;
    }
}