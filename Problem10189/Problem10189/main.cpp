//
//  main.cpp
//  Problem10189
//
//  Minesweeper
//
//  Created by Seonghyeon Choe on 1/31/12.
//  Copyright (c) 2012 kkabdol@gmail.com. All rights reserved.
//

// 5.10.2012 Wrong Answer

#include <iostream>
#ifndef ONLINE_JUDGE
#include <fstream>
#endif
#include <string.h>
using namespace std;

// map indices of row and column start from 1 not zero.

#define kMaxN (100+2)
#define kMaxM (100+2)


void cleanMineMap(char *map, int size);
void makeMineMap(char *map, int n, int m);
void printMineMap(char *map, int n, int m);
void checkMineOnMap(char *map, int x, int y);

int main (int argc, const char * argv[])
{
    int n, m;
    int count = 0;

    istream in(cin.rdbuf());
#ifndef ONLINE_JUDGE
    ifstream fin("testcase.txt");  // declarations of streams fp_in and fp_out
    if (fin) {
        in.rdbuf(fin.rdbuf());
    } else {
        cout << "can not read testcase.txt" << endl;
    }
    
#endif

    
    char map[kMaxN*kMaxM];
    
    while(in >> n >> m) {
        if (n == 0 && m == 0) {
            break;
        }
        
        cleanMineMap(map, kMaxN*kMaxM);
        for (int i=1; i<=n; i++) {
            in >> (map + i*kMaxM + 1);
        }
        makeMineMap(map, n, m);

        cout << "Field #" << ++count << ":" << endl;
        printMineMap(map, n, m);
        cout << endl;
    }

#ifndef ONLINE_JUDGE
    fin.close();
#endif
    
    return 0;
}

void cleanMineMap(char *map, int size)
{
    memset(map, 0, size);
}

void makeMineMap(char *map, int n, int m)
{
    // change '.' to '0'
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=m; j++) {
            if (map[j+i*kMaxM] == '.') {
                map[j+i*kMaxM] = '0';
            } 
        }
    }

    // increase count of tile near mine.
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=m; j++) {
            if (map[j+i*kMaxM] == '*') {
                checkMineOnMap(map, j, i);
            } 
        }
    }
}

void printMineMap(char *map, int n, int m)
{
    for (int i=1; i<=n; i++) {
        cout << (map + i*kMaxM + 1) << endl;
    }    
}


void checkMineOnMap(char *map, int x, int y)
{
    
//     [1][ 2 ][3]
//     [4][x,y][6]
//     [7][ 8 ][9]
    char *tile = NULL;
    
    tile = &map[(y-1)*kMaxM + x-1];       // 1
    *tile = (*tile != '*') ? (*tile)+1 : (*tile);
    
    tile = &map[(y-1)*kMaxM + x];         // 2
    *tile = (*tile != '*') ? (*tile)+1 : (*tile);
    
    tile = &map[(y-1)*kMaxM + x+1];       // 3
    *tile = (*tile != '*') ? (*tile)+1 : (*tile);
    
    tile = &map[(y)*kMaxM + x-1];         // 4
    *tile = (*tile != '*') ? (*tile)+1 : (*tile);
    
    tile = &map[(y)*kMaxM + x+1];         // 6
    *tile = (*tile != '*') ? (*tile)+1 : (*tile);
    
    tile = &map[(y+1)*kMaxM + x-1];       // 7
    *tile = (*tile != '*') ? (*tile)+1 : (*tile);
    
    tile = &map[(y+1)*kMaxM + x];         // 8
    *tile = (*tile != '*') ? (*tile)+1 : (*tile);
    
    tile = &map[(y+1)*kMaxM + x+1];       // 9
    *tile = (*tile != '*') ? (*tile)+1 : (*tile);
    
}