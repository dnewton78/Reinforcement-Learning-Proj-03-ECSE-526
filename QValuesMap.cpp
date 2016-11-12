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
    
}

QValuesMap::~QValuesMap()
{
    //delete 2Darray
    for(int i = 0; i<stateNum; i++)
    {
        delete [] QValueArray[i];
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
    for(int i = 1; i<actionNum; i++)
    {
        if(QValueArray[state][i]>QValueArray[state][indexOfMax])
        {
            indexOfMax = i;
        }
    }
    return indexOfMax;
}

void QValuesMap::storeQValue(int state, int action, double qVal)
{
    QValueArray[state][action] = qVal;
}
