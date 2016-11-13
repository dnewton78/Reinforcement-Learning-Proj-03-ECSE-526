//
//  QLearningAgent.cpp
//  QLearning
//
//  Created by David Newton on 11/10/16.
//  Copyright © 2016 David Newton. All rights reserved.
//

#include "QLearningAgent.hpp"
#include <random>

QLearningAgent::QLearningAgent(double a, double g, double r, double n, int states, int actions)
{
    alpha = a;
    gamma = g;
    rho = r;
    nu = n;
    QMap = new QValuesMap(states, actions);
    currentState = 0;
}

QLearningAgent::~QLearningAgent()
{
    delete QMap;
}

int QLearningAgent::getAction(int state)
{
    int bestAction;
    //use randomness as exploration strategy to try new states
    
    std::uniform_real_distribution<double> distribution(0,1);
    
    double randomNum = distribution(generator);
    //if random number is <= rho then slect random action
    if(randomNum<=rho)
    {
        
        std::uniform_int_distribution<int> distributionA(0,QMap->actionNum-1);
        bestAction =distributionA(generatorA);
    }
    else
    {
        bestAction =QMap->getBestAction(state);
    }
    return bestAction;
}

//take action; get reward; get new state then use function

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

void QLearningAgent::printQMap()
{
    QMap->printQTable();
}
