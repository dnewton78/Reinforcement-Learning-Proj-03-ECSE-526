//
//  FunctionAproximation.cpp
//  QLearning
//
//  Created by David Newton on 11/13/16.
//  Copyright © 2016 David Newton. All rights reserved.
//

#include "FunctionAproximation.hpp"


FunctionAproximation:: FunctionAproximation(int featureNumber, double alpha, double rho, int numberOfActions)
{
    //set featurenumber and size of wieght array
    this->rho = rho;
    this->featureNumber = featureNumber*2;//multiply by two becasue there are two coordinates per feature and we want to create a weight for each coordinate
    this->weights.resize(this->featureNumber+1);//the weight vector adds one extra term in accordance with U(s) = Theta1+Theta2*feat1+theta2*feat2...etc....
    this->alpha = alpha;
    this->observedUtility = 0;
    this->predictedUtility = 0;
    this->numberOfActions = numberOfActions;
    
    uniform_real_distribution<double> distribution(0,1);

    //initialize weights randomly
    for (int i =0; i<this->featureNumber+1; i++)
    {
        weights[i] = distribution(generator);
    }
}

void FunctionAproximation:: update(vector<Coord>& features, double observedUtility)
{
    //calculate predicted utlity useing function
    this->predictedUtility = this->getPredictedUtility(features);
    this->observedUtility = observedUtility;
    //transfer coordinates to single feature vector
    vector<double> coordinateArray;
    for (int i =0; i<features.size(); i++)
    {
        coordinateArray.push_back(features[i].i);
        coordinateArray.push_back(features[i].j);
    }
    
    //use update equations to update each weight
    for (int i =0; i<featureNumber+1; i++)
    {
        //for the first weight we will calculate using a slightly different function because it has no feature multiplied by it: U(s) = Theta1+Theta2*feat1+theta2*feat2...etc....
        if(i==0)
        {
            weights[i] = weights[i]+alpha*(observedUtility-predictedUtility);
        }else
        {
            weights[i] = weights[i]+alpha*(observedUtility-predictedUtility)*coordinateArray[i-1];
        }
    }
}

double FunctionAproximation::getPredictedUtility(vector<Coord>& features)
{
    double predictedUtility = 0;
    //transfer coordinates to single feature vector
    vector<double> coordinateArray;
    for (int i =0; i<features.size(); i++)
    {
        coordinateArray.push_back(features[i].i);
        coordinateArray.push_back(features[i].j);
    }
    for (int i =0; i<featureNumber+1; i++)
    {
        if(i==0)
        {
            predictedUtility= weights[i];
        }else
        {
            predictedUtility= predictedUtility+weights[i]*coordinateArray[i-1];
        }
    }
    return predictedUtility;
}

int FunctionAproximation::getAction(vector<Coord>& features)
{
    int bestAction;
    
    //use randomness as exploration strategy to try new states
    uniform_real_distribution<double> distribution(0,1);
    double randomNum = distribution(generator);
    //if random number is <= rho then slect random action
    if(randomNum<=rho)
    {
        uniform_int_distribution<int> distributionA(0,numberOfActions-1);
        bestAction =distributionA(generatorA);
    }
    else
    {
        bestAction =this->getBestAction(features);
    }
    return bestAction;
}

//need to rewrite this for specifics of game
int FunctionAproximation::getBestAction(vector<Coord>& features)
{
    double pUtility = 0;
    double maxUtility = 0;
    vector<Coord> actionToTest(features.size());
    //copy current state vector to test different different actions
    for (int i =0 ; i<features.size(); i++)
    {
        actionToTest[i].i =features[i].i;
        actionToTest[i].j =features[i].j;
    }
    //cycle through possible actions and get predicted utility for each; assumes pacman is in the 0 slot
    //try up
    actionToTest[0].i = features[0].i;//get pacmans x coordinate
    actionToTest[0].j = features[0].j+1; //get pacmans y coordinate and add 1
    pUtility = this->getPredictedUtility(actionToTest);
    maxUtility = pUtility;
    int bestAction = 0;
    
    //try down
    actionToTest[0].i = features[0].i;//get pacmans x coordinate
    actionToTest[0].j = features[0].j-1; //get pacmans y coordinate and sub 1
    pUtility = this->getPredictedUtility(actionToTest);
    if(pUtility>maxUtility)
    {
        maxUtility = pUtility;
        bestAction = 1;
    }
    
    //try left
    actionToTest[0].i = features[0].i-1;//get pacmans x coordinate
    actionToTest[0].j = features[0].j; //get pacmans y coordinate and sub 1
    pUtility = this->getPredictedUtility(actionToTest);
    if(pUtility>maxUtility)
    {
        maxUtility = pUtility;
        bestAction = 2;
    }
    
    //try right
    actionToTest[0].i = features[0].i+1;//get pacmans x coordinate
    actionToTest[0].j = features[0].j; //get pacmans y coordinate and sub 1
    pUtility = this->getPredictedUtility(actionToTest);
    if(pUtility>maxUtility)
    {
        maxUtility = pUtility;
        bestAction = 3;
    }
    
    //try nothing
    actionToTest[0].i = features[0].i;//get pacmans x coordinate
    actionToTest[0].j = features[0].j; //get pacmans y coordinate and sub 1
    pUtility = this->getPredictedUtility(actionToTest);
    if(pUtility>maxUtility)
    {
        maxUtility = pUtility;
        bestAction = 4;
    }
    
    return bestAction;
}

void FunctionAproximation::printContents()
{
    cout<<"|||||||||||||Aproximated Function\n";
    cout <<"U = ";
    //use update equations to update each weight
    for (int i =0; i<featureNumber+1; i++)
    {
        //for the first weight we will calculate using a slightly different function because it has no feature multiplied by it: U(s) = Theta1+Theta2*feat1+theta2*feat2...etc....
        if(i==0)
        {
            cout <<weights[i]<<" + ";
        }else
        {
            cout <<weights[i]<<"*"<<"f"<<i-1;
        }
        
        if(i!=featureNumber)
            cout <<" + ";
    }
    
    cout <<"\n";
    cout<<"Observed Utility = "<<this->observedUtility<<" Predicted Utility = "<<this->predictedUtility<<"\n";
    
}
