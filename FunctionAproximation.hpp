//
//  FunctionAproximation.hpp
//  QLearning
//
//  Created by David Newton on 11/13/16.
//  Copyright © 2016 David Newton. All rights reserved.
//

#ifndef FunctionAproximation_hpp
#define FunctionAproximation_hpp

#include <stdio.h>
#include <vector>
#include <stdio.h>
#include <iostream>
#include <random>
#include "utilities.hpp"
using namespace std;

class FunctionAproximation
{
private:
    double getPredictedUtility(vector<Coord>& features);
    int getBestAction(vector<Coord>& features);
    default_random_engine generator;
    default_random_engine generatorA;
    
public:
    int setOfActions[5];
    double alpha;
    double rho;
    int featureNumber;
    int numberOfActions;
    vector<double> weights;
    double observedUtility;
    double predictedUtility;
    FunctionAproximation(int featureNumber, double alpha, double rho, int numberOfActions);//initialize weights
    int getAction(vector<Coord>& features);
    void update(vector<Coord>& features, double reward);
    void printContents();
    
};
#endif /* FunctionAproximation_hpp */
