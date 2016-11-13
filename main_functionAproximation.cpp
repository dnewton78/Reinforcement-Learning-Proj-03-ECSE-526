//
//  main_functionAproximation.cpp
//  QLearning
//
//  Created by David Newton on 11/13/16.
//  Copyright © 2016 David Newton. All rights reserved.
//

#include <iostream>
#include "GameBoardFA.cpp"
#include "FunctionAproximation.hpp"
using namespace std;

int main(int argc, const char * argv[]) {
    
    //1.initialize game
    //create 3 x 4 grid world
    GameBoardFA newGame = GameBoardFA();
    
    //initialize function aproximation agent
    double alpha = 0.1; double rho =0.3;
    int lengthOfFeatureVector = 2;//state param number
    int actions = 4;
    
    FunctionAproximation myAgent = FunctionAproximation(lengthOfFeatureVector,alpha, rho,actions);

    myAgent.printContents();
    
    //play several games and learn
    int numberOfGames = 1000;
    int goalCounter = 0;
    double counterSum = 0;
    for (int i = 0; i<numberOfGames; i++)
    {
        int counter = 0;
        int currentAction = myAgent.getAction(newGame.getStateFA());
        vector<int> currentState = newGame.getStateFA();
        int newAction = 0;
        vector<int> newState;
        double reward = 0;
        
        cout<<"||||||||New Game - G#"<<i<<"\n";
        
        //play one game and learn
        do
        {
            newAction = myAgent.getAction(newGame.getStateFA());//get action based on state
            newGame.makeMove(newAction);
            reward = newGame.getReward();
            newState = newGame.getStateFA();
            myAgent.update(newState, reward);
            
            currentAction = newAction;
            currentState = newState;
            
            counter++;
        }while(!newGame.checkGameOver() && counter<100);
        
        counterSum = counterSum+counter;
        cout<<"|||||||||||||Game:"<<i<<" complete; Goal reached: "<<newGame.checkGameOver()<<" counter = "<<counter<<" invalid count = "<<newGame.invalidActionCount<<"\n";
        if(newGame.checkGameOver())
            goalCounter++;
        //reset game
        newGame.resetGame();
        myAgent.printContents();
    }
    
    cout<<"|||||||||||||Percentage of times goal was reached: "<<(double)goalCounter/(double)numberOfGames*100<<"%"<<" The average number of moves per game was: "<<(double)counterSum/(double)numberOfGames<<"\n";
    
    //get list of available actions
    
    //Loop run q-learning to learn and store policy
    //get best action QMap.get best action(state)
    //carry out the action and retrieve the reward and the new state
    //get the current Q value from the store:Q = store.getQValue(state, action)
    //Get the q of the best action from the new state: maxQ = store.getQValue(newState, store.getBestAction(newState))
    //Perform the q learning Q = (1 - alpha) * Q + alpha * (reward + gamma * maxQ)
    //And update the state in the game: state = newState
    //end Loop
    
    //save policy
  
    return 0;
}
