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
#include <ale_interface.hpp>
using namespace std;

class FunctionAproximation
{
private:
    double getPredictedUtility(vector<int>& features);
    int getBestAction(vector<int>& features);
    default_random_engine generator;
    default_random_engine generatorA;
public:
    double alpha;
    double rho;
    int featureNumber;
    int numberOfActions;
    vector<double> weights;
    double observedUtility;
    double predictedUtility;
    FunctionAproximation(int featureNumber, double alpha, double rho, int numberOfActions);//initialize weights
    int getAction(vector<int>& features);
    void update(vector<int>& features, double reward);
    void printContents();
    
};
#endif /* FunctionAproximation_hpp */
