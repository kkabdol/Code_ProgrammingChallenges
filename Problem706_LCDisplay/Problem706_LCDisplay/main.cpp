//
//  main.cpp
//  Problem706_LCDisplay
//
//  Created by Seonghyeon Choe on 12/9/12.
//  Copyright (c) 2012 Seonghyeon Choe. All rights reserved.
//
//  Dec.9.2012 Accepted

#include <iostream>
#include <string>

using namespace std;

typedef enum {
    kTop,
    kUpperSpace,
    kMiddle,
    kLowerSpace,
    kBottom,
    
    kPartMax,
} Part;

typedef enum {
    kEmpty,
    kBar,
    kLeftWall,
    kRightWall,
    kLeftRightWalls,
    
    kShapeMax,
} Shape;
const Shape g_NumShape[10][kPartMax]  = {
    { kBar, kLeftRightWalls, kEmpty, kLeftRightWalls, kBar }, //0
    { kEmpty, kRightWall, kEmpty, kRightWall, kEmpty}, //1
    { kBar, kRightWall, kBar, kLeftWall, kBar}, //2
    { kBar, kRightWall, kBar, kRightWall, kBar}, //3
    { kEmpty, kLeftRightWalls, kBar, kRightWall, kEmpty}, //4
    
    { kBar, kLeftWall, kBar, kRightWall, kBar}, //5
    { kBar, kLeftWall, kBar, kLeftRightWalls, kBar}, //6
    { kBar, kRightWall, kEmpty, kRightWall, kEmpty}, //7
    { kBar, kLeftRightWalls, kBar, kLeftRightWalls, kBar}, //8
    { kBar, kLeftRightWalls, kBar, kRightWall, kBar}, //9
    
};


static void print(const string &str, int s);
static void drawShape(Shape shape, int s);



int main(int argc, const char * argv[])
{
    int s;
    string str;
    
    while (cin >> s && cin >> str) {
        
        if (s == 0 && str == "0") {
            break;
        } else {
            print(str, s);
            cout << endl;
        }
        
    }
    
    
    
    return 0;
}

static void print(const string &str, int s) {
    const int maxRow = 2*s + 3;
    for (int i=0; i<maxRow; ++i) {
        for (int j=0; j<str.length(); ++j) {
            const int num = str[j]-'0';
            
            Part part = kTop;
            if (i > 0 && i <= s) {
                part = kUpperSpace;
            } else if (i == s+1) {
                part = kMiddle;
            } else if (i > s+1 && i <= s*2+1) {
                part = kLowerSpace;
            } else if (i == s*2+2) {
                part = kBottom;
            }
            
            Shape shape = g_NumShape[num][part];
            
            drawShape(shape, s);
            
            if (j+1 != str.length()) {
                cout << " ";
            }
        }
        cout << endl;
    }
}

static void drawShape(Shape shape, int s) {
    switch (shape) {
        case kEmpty: {
            for (int i=0; i<s+2; ++i) {
                cout << " ";
            }
        }
            break;
            
        case kBar: {
            cout << " ";
            for (int i=1; i<s+1; ++i) {
                cout << "-";
            }
            cout << " ";
        }
            break;
            
        case kLeftWall: {
            cout << "|";
            for (int i=1; i<s+2; ++i) {
                cout << " ";
            }
        }
            break;
            
        case kRightWall: {
            for (int i=0; i<s+1; ++i) {
                cout << " ";
            }
            cout << "|";
        }
            break;
            
        case kLeftRightWalls: {
            cout << "|";
            for (int i=1; i<s+1; ++i) {
                cout << " ";
            }
            cout << "|";
        }
            break;
            
        default:
            break;
    }
}

