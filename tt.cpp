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
#include <ale_interface.hpp>
#include "utilities.hpp"
#include "FunctionAproximation.hpp"

#ifdef __USE_SDL
  #include <SDL.h>
#endif

#define RAM_SIZE (128)
#define SKIPFRAMES (262)

using namespace std;


int main(int argc, char** argv) {
    
    //get Arguments from command line
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " rom_file" << std::endl;
        return 1;
    }

    //create ale interface
    ALEInterface ale;
    // Get & Set the desired settings
    ale.setInt("random_seed", 123);
    //The default is already 0.25, this is just an example
    ale.setFloat("repeat_action_probability", 0.25);

#ifdef __USE_SDL
    ale.setBool("display_screen", true);
    ale.setBool("sound", true);
#endif

    // Load the ROM file. (Also resets the system for new settings to
    // take effect.)
    ale.loadROM(argv[1]);

    // Get the vector of legal actions
    ActionVect legal_actions = ale.getMinimalActionSet();
    
    //load background
    Background bg;
    
    //initialize function aproximation agent variables
    double alpha = 0.1;
    double rho =0.3;
    int lengthOfFeatureVector = 5;//state param number
    int actions = legal_actions.size();
    double reward = 0;
    
    //variable for current state
    vector<int> currentState;
    //variable for new state
    vector<int> newState;
    
    //create FA agent
    FunctionAproximation myAgent = FunctionAproximation(lengthOfFeatureVector,alpha, rho,actions);
    myAgent.printContents();
    
    //play several games and learn
    int numberOfGames = 1000;
    for (int i = 0; i<numberOfGames; i++)
    {
        //get the game state and feature vectors
        currentState =
        //get action from function aproximation by passing current state
        Action currentAction = legal_actions[rand() % legal_actions.size()];//myAgent.getAction(newGame.getStateFA());
        //variable for new action
        Action newAction;
        //variable for new state
        newState;
        //set reward to 0 before each game
        reward = 0;
        
        //run game loop
        while (!ale.game_over()) {
            
            //get action based on state
            newAction = myAgent.getAction(newGame.getStateFA());
            //make move & get reward
            reward = reward + ale.act(newAction);
            //get new state vector
            newState = newGame.getStateFA();
            //update utility function
            myAgent.update(newState, reward);
            
            currentAction = newAction;
            currentState = newState;

        }
        cout << "Episode " << i << " ended with score: " << totalReward << endl;
        myAgent.printContents();
        ale.reset_game();
    }
    
    //save learned function weights

    return 0;
}
