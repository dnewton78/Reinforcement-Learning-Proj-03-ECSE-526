/* *****************************************************************************
 * A.L.E (Arcade Learning Environment)
 * Copyright (c) 2009-2013 by Yavar Naddaf, Joel Veness, Marc G. Bellemare,
 *  Matthew Hausknecht, and the Reinforcement Learning and Artificial Intelligence 
 *  Laboratory
 * Released under the GNU General Public License; see License.txt for details. 
 *
 * Based on: Stella  --  "An Atari 2600 VCS Emulator"
 * Copyright (c) 1995-2007 by Bradford W. Mott and the Stella team
 *
 * *****************************************************************************
 *  sharedLibraryInterfaceExample.cpp 
 *
 *  Sample code for running an agent with the shared library interface. 
 **************************************************************************** */

#include <iostream>
#include <getopt.h>
#include <ale_interface.hpp>
#include "utilities.hpp"
#include "FunctionAproximation.hpp"

#ifdef __USE_SDL
  #include <SDL.h>
#endif


using namespace std;

void getArgs(int argc, char** argv, bool& rIsTest, int& rNumOfEpisodes)
{
    int option = 0;
    while ((option = getopt(argc, argv, "te:")) != -1)
    {
        if (option == -1)
        {
            break;
        }

        switch(option)
        {
            case 't':
                cout << "tst" << endl;
                rIsTest = true;
                break;
            case 'e':
                cout << "Episode" << endl;
                rNumOfEpisodes = atoi(optarg);
                break;
        }
    }
}

int main(int argc, char** argv)
{
    
    //get Arguments from command line
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " -t (test mode) -e (number of episodes) rom_file" << std::endl;
        return 1;
    }

    bool isTest = false;
    int numOfEpisodes = 10;

    getArgs(argc, argv, isTest, numOfEpisodes);

    //create ale interface & set settings
    ALEInterface ale;
    // Skip 5 frames
    ale.setInt("frame_skip", 5);
    ale.setBool("color_averaging", false);
    
#ifdef __USE_SDL
    ale.setBool("display_screen", true);
    ale.setBool("sound", true);
#endif
    
    // Load the ROM file. (Also resets the system for new settings to
    // take effect.)
    ale.loadROM(argv[1]);
    
    //define variables for feature extraction
    Feature newFeature = Feature();
    
    // Get the vector of legal actions
    ActionVect legal_actions = ale.getMinimalActionSet();
    
    //initialize function aproximation agent variables
    double alpha = 0.01;
    double rho =0.3;
    int numberOfFeatures = 5;//state param number
    int actionNumber = 5;
    
    
    //variable for current state
    vector<Coord> currentState(numberOfFeatures);
    //variable for new state
    vector<Coord> newState(numberOfFeatures);
    
    //create FA agent
    FunctionAproximation myAgent = FunctionAproximation(numberOfFeatures,alpha, rho,actionNumber);
    //set possible actions
    myAgent.setOfActions[0] = 2;//0 up
    myAgent.setOfActions[1] = 4;//1 down
    myAgent.setOfActions[2] = 3;//left 3
    myAgent.setOfActions[3] = 2;//right 4
    myAgent.setOfActions[4] = 0;//no action
    myAgent.printContents();
    
    //play several games and learn
    for (int i = 0; i<numOfEpisodes; i++)
    {
        //get the game state and feature vectors
        newFeature.extractCoord(ale.getScreen(), currentState);
        //get action from function aproximation by passing current state
        Action currentAction = legal_actions[2];//startout going left
        //variable for new action
        Action newAction;
        // Total score for each episodes
        float totalScore = 0;
        
        //run game loop
        while (!ale.game_over()) {
            
            //get action based on state
            newAction = legal_actions[myAgent.getAction(currentState)];
            //make move & get reward
            float reward = ale.act(newAction);
            totalScore += reward;
            //get new state vector
            newFeature.extractCoord(ale.getScreen(), newState);
            //update utility function
            myAgent.update(newState, reward);
            currentAction = newAction;
            currentState = newState;
        }
        cout << "Episode " << i << " ended with score: " << totalScore << endl;
        myAgent.printContents();
        ale.reset_game();
    }
    
    //save learned function weights
    
    return 0;
}
