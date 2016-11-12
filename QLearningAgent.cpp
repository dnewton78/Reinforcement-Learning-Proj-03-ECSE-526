//
//  QLearningAgent.cpp
//  QLearning
//
//  Created by David Newton on 11/10/16.
//  Copyright © 2016 David Newton. All rights reserved.
//

#include "QLearningAgent.hpp"

QLearningAgent::QLearningAgent(double a, double g, double r, double n, int states, int actions)
{
    alpha = a;
    gamma = g;
    rho = r;
    nu = n;
    QMap = new QValuesMap(states, actions);
}

QLearningAgent::~QLearningAgent()
{
    delete QMap;
}

int QLearningAgent::getAction(int state)
{
    return QMap->getBestAction(state);
}

//take action; get reward; get new state
void QLearningAgent::calculateQVal(int curState, int newState, int curAction, int bestAction, double reward)
{
    //Get the q of the best action from the new state: maxQ = store.getQValue(newState, store.getBestAction(newState))
    double Q = QMap->getQValue(curState, curAction);
    double QMax = QMap->getQValue(newState, bestAction);
    //Perform the q learning Q = (1 - alpha) * Q + alpha * (reward + gamma * maxQ)
    Q = (1-alpha)*Q+alpha*(reward+gamma*QMax);
    //store Q value
    QMap->storeQValue(newState, bestAction, Q);
}
