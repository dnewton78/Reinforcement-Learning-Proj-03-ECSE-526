//
//  main.cpp
//  QLearning
//
//  Created by David Newton on 11/10/16.
//  Copyright © 2016 David Newton. All rights reserved.
//

#include <iostream>
#include "QLearningAgent.hpp"
#include "GameBoard.cpp"
using namespace std;

int main(int argc, const char * argv[]) {
    
    //1.initialize game
    //create 3 x 4 grid world
    GameBoard newGame = GameBoard();
    
    //initialize Q-learning agent
    double alpha = 0.5;double gamma = 0.5; double rho = 0.3; double nu = 0; int states = 3*4; int actions = 4;
    QLearningAgent* myAgent = new QLearningAgent(alpha, gamma, rho,nu,states,actions);
   
    cout<<"|||||||||||||QMap\n";
    myAgent->printQMap();
    
    //play several games and learn
    int numberOfGames = 1000;
    int goalCounter = 0;
    double counterSum = 0;
    for (int i = 0; i<numberOfGames; i++)
    {
        int counter = 0;
        int currentAction = myAgent->getAction(newGame.getState());
        int currentState = newGame.getState();
        int newAction = 0;
        int newState = 0;
        double reward = 0;
        
        cout<<"||||||||New Game - G#"<<i<<"\n";
        
        //play one game and learn
        do
        {
            newAction = myAgent->getAction(currentState);//get action based on state
            newGame.makeMove(newAction);
            reward = newGame.getReward();
            newState = newGame.getState();
            myAgent->calculateQVal(currentState, newState, currentAction, newAction, reward);
            
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
         cout<<"|||||||||||||QMap\n";
        myAgent->printQMap();
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
    
    delete myAgent;
    return 0;
}
