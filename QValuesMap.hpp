//
//  QValuesMap.hpp
//  QLearning
//
//  Created by David Newton on 11/10/16.
//  Copyright © 2016 David Newton. All rights reserved.
//

#ifndef QValuesMap_hpp
#define QValuesMap_hpp

#include <stdio.h>

class QValuesMap
{
    private:
    //data structure for q vals
    double ** QValueArray;// ROWS(states) X COLS (actions) actions = 0_no action;1_up;2_dn;3_R;4_L
    public:
    int stateNum;
    int actionNum;
    QValuesMap (int stateNum, int actionNum);
    ~QValuesMap();
    double getQValue(int state, int action);
    int getBestAction(int state);
    void storeQValue(int state, int action, double qVal);

};
#endif /* QValuesMap_hpp */

