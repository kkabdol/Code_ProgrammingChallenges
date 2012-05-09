//
//  main.cpp
//  Problem10189
//
//  Minesweeper
//
//  Created by Seonghyeon Choe on 1/31/12.
//  Copyright (c) 2012 kkabdol@gmail.com. All rights reserved.
//

#include <iostream>
using namespace std;

void makeMineMap(int n, int m);

int main (int argc, const char * argv[])
{
    int n, m;
    int count = 0;
    
    while(cin >> n >> m) {
        if (n == 0 && m == 0) {
            break;
        }
        
        cout << "Field #" << ++count << ":" << endl;
        makeMineMap(n, m);
        cout << endl;
    }

    return 0;
}

void makeMineMap(int n, int m)
{
    
}