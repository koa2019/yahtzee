#include <iostream>
#include <vector>
#include <iomanip>
#include <bits/stdc++.h>
#include "Yahtzee.h"
#include "Dice.h"
#include "Score_Card.h"

using namespace std;

Yahtzee::Yahtzee() {
    highscore = 0;
}


void Yahtzee::play() {
    
    const int MAXROLLS = 3;
    const int numRounds = 3;
    ScoreCard scorecard;
    ScoreCard finalSC;
    Dice dice[NUM_DICE];  // aggregate instance of Dice class. Dice array object    
    int diceArr[NUM_DICE];  // local dice int array
    int resp, 
        numRolls;
    bool categorySelected = false,
         leave,
         clearance;
  
    cout << "WELCOME TO YAHTZEE!!" << endl << endl;
    cout << "RULES: " << endl << endl << endl;
    //rules();

    // Game runs for 13 rounds. 1 round per category
    for (int i = 0; i < numRounds; i++) {

        prntRound(i);
        pause('r');
        numRolls = 0;  
        vector<int> selected;  // Create vector for the dice we're keeping for final points
        
            
        // loop as long as numRolls does NOT equal 3
        while(!(numRolls == MAXROLLS)){
                
            cout << "\n\t  Roll #" << numRolls+1;
            
            leave = false;
            clearance = false;
             
            // loops through selected vector, and checks which dice to re-roll
            for (int j = 0; j < NUM_DICE; j++) {                                
                if (find(selected.begin(), selected.end(), j) == selected.end()) {
                    dice[j].roll(); 
                }
            }
            
            numRolls++; // increment numRolls every time dice are rolled           
            
            //prntDice(dice);
            // Print Dice class object's values
            cout << "\n\tDice values:" << endl;
            for (int j = 0; j < NUM_DICE; j++) {
                cout << setw(4) << dice[j].getValue() << "  ";
            }
            cout << "\n";
            for (int j = 0; j < NUM_DICE; j++) {
                cout << "Dice" << j + 1 << " ";
            }
            cout << "\n" << string(40, '-') << endl;

            // Setting local dice array with Dice class object
            for (int i = 0; i < NUM_DICE; i++) {
                diceArr[i] = dice[i].getValue();
            }

            
            // Set scorecard with possible points based on dice values
            // Print scorecard with the categories they can choose from
            // Sending local dice array to Score_Card class
            scorecard.fillScoreCard(diceArr,clearance);
            cout<<"\nPoints Possible ";
            scorecard.printScoreCard();           
            
         
            resp = 0;
            if(numRolls == 3){ resp = 2; } // Make player choose a category
            else { displayOptions(resp); } // else offer them options to choose from

            
            // choose dice to keep, pick a category, re-roll or exit game
            switch(resp){

                case 1: // Select dice you want to keep in between rolls
                {
                    cout << "Enter the dice numbers (1-5) to keep, separated by spaces,\nor -1 to stop: ";
                    int choice;

                    while (!(cin >> choice) || (choice != -1 && (choice < 1 || choice > NUM_DICE))) {
                        cout << "Invalid choice. Please enter a number between 1 and " << NUM_DICE << ", or -1 to stop: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }


                    // Push the dice they want to keep to the selected vector
                    while (choice != -1) {
                        selected.push_back(choice - 1);
                        cout << "Keeping Dice" << choice << ": " << dice[choice - 1].getValue() << endl;
                        cin >> choice;  
                    }
                    break;
                }
                case 2: // Keep points from 1 category and end their turn
                {
                    clearance = true;
                    finalSC.setFinalSC(scorecard, diceArr,clearance);
                    numRolls = MAXROLLS; // reassign it, so while(numRolls<maxRolls) stops
                    leave = true;
                    pause();
                    break;
                }
                case 3: // Rolls dice again
                {
                    break;
                }
                default:
                {
                    cout << "<Leaving program>" << endl;
                    exit(0);
                }
                        
            } // ends switch(resp)                        
                    
                       
        } // ends while(!(numRoll == MAXROLLS))
            
    } // ends round for loop i < 13              

    
    //cout << "\n\nDo you want to play again? (Y/N) ";
    //while (!(cin >> resp1) || (toupper(resp1) != 'Y' && toupper(resp1) != 'N')) {
    //    cout << "Invalid choice. Please enter 'Y' or 'N': ";
    //    cin.clear();
    //    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    //}

} // ends play()


//*****************************************************************
//        Print player's options and return their choice
//*****************************************************************
void Yahtzee::displayOptions(int &resp) {
    
    cout << "Options:" << endl;
    cout << "1: Select which dice you want to keep\nbefore rolling again." << endl;
    cout << "2: Pick category and end your turn" << endl;
    cout << "3: Roll again." << endl;
    cout << "4: Exit" << endl;
    cout << "Enter a number: ";    
    
    while (!(cin >> resp) || resp < 1 || resp > 4) {
        cout << "Invalid choice. Please enter a number between 1 and 3: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

//******************************************
//              Print round
//******************************************
void Yahtzee::prntRound(int i){
    
    i = (i < 0 ) ? 0 : i;
    
    cout << endl << endl;
    cout << "|" << string(40, '-') << "|" << endl;
    cout << "|" << setw(20) << "Round " << i + 1 << setw(20) << "|" << endl;
    cout << "|" << string(40, '-') << "|" << endl;
}


//******************************************
//      pause screen before continuing
//******************************************
void Yahtzee::pause(char ch) {
    
    string msg = ch=='r' ? "roll" : "continue";    
    cout<<endl<<setw(10)<<' '<<"Press enter to " << msg << ".\n";   
    cin.get();
}

//******************************************
//          Print rules
//******************************************
void Yahtzee::rules(){
    cout << "Yahtzee is a game played with five dice, where the objective is to score as many points as possible in 13 rounds." << endl;
    cout << "Each player takes turns rolling the dice up to three times per turn, trying to achieve certain combinations." << endl;
    cout << "After each turn, the player must choose a category to score their points in, and that category cannot be used again." << endl << endl;
    cout << endl;
    cout << "______________________________________________________________________________________________________________________" << endl;
    cout << "The categories are as follows:" << endl;
    cout << "1. Ones: Score the sum of all dice showing the number 1." << endl;
    cout << "2. Twos: Score the sum of all dice showing the number 2." << endl;
    cout << "3. Threes: Score the sum of all dice showing the number 3." << endl;
    cout << "4. Fours: Score the sum of all dice showing the number 4." << endl;
    cout << "5. Fives: Score the sum of all dice showing the number 5." << endl;
    cout << "6. Sixes: Score the sum of all dice showing the number 6." << endl;
    cout << "7. Three of a Kind: If at least three dice show the same number, score the sum of all dice." << endl;
    cout << "8. Four of a Kind: If at least four dice show the same number, score the sum of all dice." << endl;
    cout << "9. Full House: If three dice show one number and the other two dice show another number, score 25 points." << endl;
    
    // Categories 10-13 are only available after the first six rounds:
    cout << "10. Small Straight: If the dice show any sequence of four numbers, score 30 points." << endl;
    cout << "11. Large Straight: If the dice show any sequence of five numbers, score 40 points." << endl;
    cout << "12. Yahtzee: If all five dice show the same number, score 50 points." << endl;
    cout << "13. Chance: Score the sum of all dice, regardless of category." << endl;
    cout << "______________________________________________________________________________________________________________________" << endl;
}
