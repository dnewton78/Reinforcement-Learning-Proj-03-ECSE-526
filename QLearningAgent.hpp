//
//  QLearningAgent.hpp
//  QLearning
//
//  Created by David Newton on 11/10/16.
//  Copyright © 2016 David Newton. All rights reserved.
//

#ifndef QLearningAgent_hpp
#define QLearningAgent_hpp

#include <stdio.h>
#include "QValuesMap.hpp"

class QLearningAgent
{
    private:
    QValuesMap* QMap;
    //current state variable?
    //next state variable?
    public:
    double alpha, gamma, rho, nu;
    QLearningAgent(double a, double g, double r, double n, int states, int actions);
    ~QLearningAgent();
    int getAction(int state);//include randomization in here for exploration
    void calculateQVal(int curState, int newState, int curAction, int bestAction, double reward);
};
#endif /* QLearningAgent_hpp */

