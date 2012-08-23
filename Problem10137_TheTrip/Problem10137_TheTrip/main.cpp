//
//  main.cpp
//  Problem10137_TheTrip
//
//  Created by Seonghyeon Choe on 7/13/12.
//  Copyright (c) 2012 Kkabdol. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cassert>
#include <cstdio>

/* inputs
3
10.00
20.00
30.00
4
15.00
15.01
3.00
3.01
0
*/



using namespace std;

int readNumberOfStudentsFromStdIn(void) {
    int num;
    cin >> num;
    
    return num;
}

float readSpentFromStdIn(void) {
    float spent;
    cin >> spent;
    return spent;
}

float getExpenseOfAverage(float total, int numOfStudents) {
    const float average = total / numOfStudents;
    const float belowCentsRemoved = ((int)(average*1000.0)/1000);

    if (average > belowCentsRemoved) {
        const float adjustedAverage = belowCentsRemoved + 0.01;
        return adjustedAverage;
    } else {
        assert(average == belowCentsRemoved);
        return belowCentsRemoved;
    }
}

int main(int argc, const char * argv[])
{
    int numberOfStudents;
    vector<float>* expenses = new vector<float>(1000);
    float totalAmount = 0;
    
    while ((numberOfStudents = readNumberOfStudentsFromStdIn()) > 0) {
        expenses->clear();
        totalAmount = 0;
        
        for (int i=0; i<numberOfStudents; i++) {
            float expense = readSpentFromStdIn();
            expenses->push_back(expense);
            totalAmount += expense;
        }
        
        float averageOfExpense = getExpenseOfAverage(totalAmount, numberOfStudents);
        float exchangedMoney = 0.0;
        
        for (int i=0; i<numberOfStudents; i++) {
            float expense = expenses->at(i);
            if (expense > averageOfExpense) {
                exchangedMoney += expense-averageOfExpense;
            }
        }
        
        printf("$%.02f\n", exchangedMoney);
    }

    delete expenses;
    
    return 0;
}

