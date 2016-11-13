//
//  GameBoard.cpp
//  QLearning
//
//  Created by David Newton on 11/12/16.
//  Copyright © 2016 David Newton. All rights reserved.
//

#include <stdio.h>
#include <iostream>
using namespace std;

class GameBoard
{
    public:
    int position[2];//state
    double GridWorld [3][4];
    bool invalidAFlag;
    int invalidActionCount;
    GameBoard()
    {
        GridWorld[2][0] = 0.812; GridWorld[2][1] = 0.868;GridWorld[2][2] = 0.918;GridWorld[2][3] = 1;
        GridWorld[1][0] = 0.762; GridWorld[1][1] = -0.1;GridWorld[1][2] = 0.660;GridWorld[1][3] = -1;
        GridWorld[0][0] = 0.705; GridWorld[0][1] = 0.655;GridWorld[0][2] = 0.611;GridWorld[0][3] = 0.388;
        
        position[0] = 0;
        position[1] = 0;
        invalidAFlag = false;
        invalidActionCount = 0;
    }
    void makeMove(int action)
    {
        invalidAFlag  = false;

        //apply action
        switch(action)
        {
            case 0: //up
                if(position[0]+1<3 && position[0]+1>=0)
                {
                    position[0] =position[0]+1;
                cout<<"Up action taken"<<" new position ["<<position[0]<<"]"<<"["<<position[1]<<"]"<<"\n";
                }else{
                    cout<<"Invalid action specified.  No action taken."<<"\n";
                    invalidAFlag  = true;invalidActionCount++;
                }
                break;
            case 1: //dn
                if(position[0]-1<3 && position[0]-1>=0)
                {
                    position[0] =position[0]-1;
                cout<<"Down action taken"<<" new position ["<<position[0]<<"]"<<"["<<position[1]<<"]"<<"\n";
                }else{
                    cout<<"Invalid action specified.  No action taken."<<"\n";
                    invalidAFlag  = true;invalidActionCount++;
                }
                break;
            case 2: //left
                if(position[1]-1<4 && position[1]-1>=0)
                {
                    position[1] =position[1]-1;
                cout<<"Left action taken"<<" new position ["<<position[0]<<"]"<<"["<<position[1]<<"]"<<"\n";
                }else{
                    cout<<"Invalid action specified.  No action taken."<<"\n";
                    invalidAFlag  = true;invalidActionCount++;
                }
                break;
            case 3: //right
                if(position[1]+1<4 && position[1]+1>=0)
                {
                    position[1] =position[1]+1;
                cout<<"Right action taken"<<" new position ["<<position[0]<<"]"<<"["<<position[1]<<"]"<<"\n";
                }else{
                    cout<<"Invalid action specified.  No action taken."<<"\n";
                    invalidAFlag  = true;invalidActionCount++;
                }
                break;
        }
    }
    
    double getReward()
    {
        double reward = 0;
        if(invalidAFlag)
        {
            reward = -1;
        }
        else
        {
            reward = GridWorld[position[0]][position[1]];
        }
        return reward;
    }
    
    bool checkGameOver()
    {
        bool gameFlag = false;
        if(position[0]==2 && position[1]==3)
            gameFlag = true;
        return gameFlag;
    }
    
    int getState()
    {
        return position[0]*4+position[1];
    }
    
    void resetGame()
    {
        position[0] = 0;
        position[1] = 0;
        invalidActionCount = 0;
    }
    
};
