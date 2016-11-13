//
//  QValuesMap.cpp
//  QLearning
//
//  Created by David Newton on 11/10/16.
//  Copyright © 2016 David Newton. All rights reserved.
//

#include "QValuesMap.hpp"


QValuesMap::QValuesMap(int stateNum, int actionNum)
{
    this->stateNum = stateNum;
    this->actionNum = actionNum;
    
    //create 2Darray
    this->QValueArray = new double* [stateNum];
    for(int i = 0; i<stateNum; i++)
    {
        QValueArray[i] = new double [actionNum];
    }
    
    //initialize array to zero
    for(int i = 0; i<stateNum; i++)
    {
        for (int j=0; j<actionNum; j++) {
            QValueArray[i][j] = 0;
        }
    }
    
}

QValuesMap::~QValuesMap()
{
    //delete 2Darray
    for(int i = 0; i<stateNum; i++)
    {
        //delete [] QValueArray[i];
    }
    delete [] QValueArray;
}

double QValuesMap::getQValue(int state, int action)
{
    return QValueArray[state][action];
}

int QValuesMap::getBestAction(int state)
{
    //loop through actions for a specific state and find action with highest Q-value
    int indexOfMax = 0;
    double sumOfQVals = 0;
    for(int i = 0; i<actionNum; i++)
    {
        sumOfQVals = fabs(QValueArray[state][i]+sumOfQVals);
        double currentI =QValueArray[state][i];
        double maxI = QValueArray[state][indexOfMax];
        if(currentI>maxI)
        {
            indexOfMax = i;
        }
    }
    
    //if all qvalues all equal zero then pick a random action
    if(sumOfQVals==0)
    {
        std::uniform_int_distribution<int> distribution(0,actionNum);
        std::default_random_engine generator;
        indexOfMax =distribution(generator);
    }
    
    return indexOfMax;
}

void QValuesMap::storeQValue(int state, int action, double qVal)
{
    QValueArray[state][action] = qVal;
}

void QValuesMap::printQTable()
{
    for(int i = 0; i<stateNum; i++)
    {
        int row = i/4;
        int col = i-row*4;
        cout <<"["<<row<<"]"<<"["<<col<<"] = ";
        for(int j = 0; j<actionNum; j++)
        {
            cout << QValueArray[i][j]<<" ";
        }
        cout <<"\n";
    }
}
