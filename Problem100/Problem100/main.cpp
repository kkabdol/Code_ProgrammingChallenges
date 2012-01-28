//
//  main.cpp
//  Problem100
//
//  The 3n+1 Problem
//
//  Created by Seonghyeon Choe on 1/21/12.
//  Copyright 2012 Kkabdol. All rights reserved.
//


// Find maximum sequence cycle


#include <iostream>
#include <map>
using namespace std;

#ifndef ONLINE_JUDGE
const int cMaxTestCase = 4;
const int testCase[cMaxTestCase][2] = {
    {1, 10},
    {100, 200},
    {201, 210},
    {900, 1000}
};
#endif

map<int, int> data;     // save test case and cycle pair
int getCycle(int var);

int main (int argc, const char * argv[])
{
    int i,j;    // test cases are the number between i to j
 
    data[1] = 1;    // set default cycle;
    
#ifdef ONLINE_JUDGE
    while (cin >> i >> j) 
    {
#else
        for(int k=0; k<cMaxTestCase; k++) {
            i = testCase[k][0];
            j = testCase[k][1];
#endif
            cout << i << " " << j << " ";
            
        // Input i can be bigger than j, so I must make i bigger than j
        if (i > j) {
            int tmp = i;
            i = j;
            j = tmp;
        }
            
            int max = 0;    // maximum cycle
            
            
            
            for (int t=i; t<=j; t++) {  // t means test case
                int cycle = getCycle(t);
                
                if (max < cycle) {
                    max = cycle;
                }
            }
            
            cout << max << endl;
        }
        
        return 0;
    
}

int getCycle(int var)
{
    // check if var's cycle has been calculated already
    map<int,int>::iterator it;
    it = data.find(var);
    if (it != data.end()) {
#ifndef ONLINE_JUDGE
        cout << var << "'s cycle already calculated by " << it->second << endl;
#endif
        return it->second;
    } else {
        // calculate cycle
        int n = var;
        
        // n must be bigger than or equal to 1 
        if (n % 2 == 1) {        // odd
            n = 3*n + 1;
        } else {            // even
            n /= 2;         
        }
        
        data[var] = 1 + getCycle(n);
        return data[var];

    }
    
}
