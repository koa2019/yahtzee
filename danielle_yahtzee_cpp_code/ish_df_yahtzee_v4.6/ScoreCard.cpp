#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <numeric>
#include "ScoreCard.h"
#include "Dice.h"

using namespace std;


//************************************************************
//                  Default Constructor    
//************************************************************

ScoreCard::ScoreCard() {
    
    for (int i = 0; i < 13; i++) {
        scores[i] = -1;
        isSelected[i] = 0;
    }
   //printScoreCard();
}


//************************************************************
//              Set points in scores array           
//************************************************************

void ScoreCard::recordScore(int category, int score) {
    
    static int round = 0;
    
    //cout<<"\nInside recordScore()  "; get_isSelected();   
    //cout << "round = " << round << endl;
    
    if(round >= 0 && round <= 12){ scores[category-1] = score; }
  
    else if( round > 12 && (isSelected[category-1] == 0) ) {
        scores[category-1] = score;
    }
    else { scores[category-1] = -1;}
   
    round++;
}


//************************************************************
//          Add upper and lower sections of scorecard            
//************************************************************

int ScoreCard::getTotalScore() {
    
    int total = 0;    
    for (int i = 0; i < 13; i++) {        
        if (scores[i] >= 0) {
            
            // if upper section is 63 or more than add 25 pts to total
            if(i==5 && total >= 63){ total +=25; } 
            total += scores[i];
        }
    }
    return total;
}

//*****************************************************************************
//        Set player's scorecard using values from possible scorecard
//*****************************************************************************

void ScoreCard::setFinalSC(ScoreCard &scorecard, int diceArr[]){
    
    int choice = 0;
     
    cout << "\nPick a Category between 1 and 13.\n";
    
    do {
       
        cin >> choice;

        // Check if the choice is valid and not already used.
        // You need to implement the logic to store the used categories and check for valid scoring.
        while (choice < 1 || choice > 13) {
            cout << "Invalid choice. Please select a category between 1 and 13." << endl;
            cin >> choice;
        }

        // Conditional stops a set category from being overwritten
        if( (isSelected[choice-1]) != 0) { 
            cout << "Category " << choice << " has already been selected.\n"
                 << "Chose another category:  ";
        }
    } while( (isSelected[choice-1]) != 0);
    
    // Set points in player's final scoreboard
    scores[choice-1] = scorecard.scores[choice-1];     
            
    // set flag so this category, so it can't be selected anymore
    isSelected[choice-1] = true;
    scorecard.isSelected[choice-1] = true;
    
    //cout<<"\nInside setFinalSC()  "; get_isSelected();    
    //getFinalSC();
}


//************************************************************
//               Fill scorecard with possible points
//************************************************************

void ScoreCard::fillScoreCard(int diceArr[], bool clearance) {
    
    int num_dice = 5;
    vector<int> scores(13, 0);
    vector<int> counts(6, 0);    
    
    // Sort array in ascending order
    sort(diceArr, diceArr + num_dice);

    // ? Accumulating something in scores[]
    for (int i = 0; i < num_dice; i++) {
        counts[diceArr[i] - 1]++;
        scores[diceArr[i] - 1] += diceArr[i];
    }

    // ? Record scores to upper section?  
    for (int i = 0; i < 6; i++) {
        recordScore(i + 1, scores[i]);
    }

    //  Check Lower section of scorecard  starts here  
    bool three_of_a_kind = false;
    bool four_of_a_kind = false;
    bool full_house = false;
    bool small_straight = false;
    bool large_straight = false;
    bool isYahtzee = true;

    // Check for Three and four of a kind
    for (int count : counts) {
        if (count >= 3) {
            three_of_a_kind = true;
            if (count >= 4) {
                four_of_a_kind = true;
                break;
            }
        }
    }

    // if 3 or 4 of kind is true, then set pts in scores[]
    recordScore(7, three_of_a_kind ? accumulate(diceArr, diceArr + num_dice, 0) : 0);
    recordScore(8, four_of_a_kind ? accumulate(diceArr, diceArr + num_dice, 0) : 0);

    // if Full house, then set pts in scores[]
    full_house = (counts[0] == 3 && counts[1] == 2) || (counts[0] == 2 && counts[1] == 3);
    recordScore(9, full_house ? 25 : 0);

    // Check for Small and large straight
    for (int i = 0; i < 2; i++) {
        if (counts[i] && counts[i + 1] && counts[i + 2] && counts[i + 3]) {
            small_straight = true;
            if (counts[i + 4]) {
                large_straight = true;
                break;
            }
        }
    }

    // if small or large straight, then set pts in scores[]
    recordScore(10, small_straight ? 30 : 0);
    recordScore(11, large_straight ? 40 : 0);

    // if Yahtzee, then set pts in scores[]
    isYahtzee = all_of(counts.begin(), counts.end(), [&](int count) { return count == num_dice; });
    recordScore(12, isYahtzee ? 50 : 0);

    // Chance set pts in scores[]
    recordScore(13, accumulate(diceArr, diceArr + num_dice, 0));    

    //cout<<"\nPoints Possible "; printScoreCard();     
}


//************************************************************
//               Print bool isSelected array
//************************************************************

void ScoreCard::get_isSelected() const {
    cout<<"\n isSelected[]";
    for(int i=0; i<13;i++){
        cout << isSelected[i] << " ";
    }
}


//************************************************************
//              Print scorecard and total points           
//************************************************************

void ScoreCard::getFinalSC(){
    cout << "\n\t\tScorecard\n";
    printScoreCard();
    cout << setw(31) << "Total Score: " << setw(3) << getTotalScore() << "\n";
}



//************************************************************
//                  Print scorecard        
//************************************************************

void ScoreCard::printScoreCard() const {
    cout << setw(5) << " "  << "-------------------------------\n";
    cout << setw(5) << " "  << "| Category          | Score   |\n";
    cout << setw(5) << " "  << "-------------------------------\n";
    cout << setw(5) << " "  << left << setw(20) << "| 1. Ones" << " | " << right << setw(6) << (scores[0] >= 0 ? to_string(scores[0]) : "-") << " |\n";
    cout << setw(5) << " "  << left << setw(20) << "| 2. Twos" << " | " << right << setw(6) << (scores[1] >= 0 ? to_string(scores[1]) : "-") << " |\n";
    cout << setw(5) << " "  << left << setw(20) << "| 3. Threes" << " | " << right << setw(6) << (scores[2] >= 0 ? to_string(scores[2]) : "-") << " |\n";
    cout << setw(5) << " "  << left << setw(20) << "| 4. Fours" << " | " << right << setw(6) << (scores[3] >= 0 ? to_string(scores[3]) : "-") << " |\n";
    cout << setw(5) << " "  << left << setw(20) << "| 5. Fives" << " | " << right << setw(6) << (scores[4] >= 0 ? to_string(scores[4]) : "-") << " |\n";
    cout << setw(5) << " "  << left << setw(20) << "| 6. Sixes" << " | " << right << setw(6) << (scores[5] >= 0 ? to_string(scores[5]) : "-") << " |\n";
    cout << setw(5) << " "  << "-------------------------------\n";
    cout << setw(5) << " "  << left << setw(20) << "| 7. Three of a Kind" << " | " << right << setw(6) << (scores[6] >= 0 ? to_string(scores[6]) : "-") << " |\n";
    cout << setw(5) << " "  << left << setw(20) << "| 8. Four of a Kind" << " | " << right << setw(6) << (scores[7] >= 0 ? to_string(scores[7]) : "-") << " |\n";
    cout << setw(5) << " "  << left << setw(20) << "| 9. Full House" << " | " << right << setw(6) << (scores[8] >= 0 ? to_string(scores[8]) : "-") << " |\n";
    cout << setw(5) << " "  << left << setw(20) << "| 10. Small Straight" << " | " << right << setw(6) << (scores[9] >= 0 ? to_string(scores[9]) : "-") << " |\n";
    cout << setw(5) << " "  << left << setw(20) << "| 11. Large Straight" << " | " << right << setw(6) << (scores[10] >= 0 ? to_string(scores[10]) : "-") << " |\n";
    cout << setw(5) << " "  << left << setw(20) << "| 12. Yahtzee" << " | " << right << setw(6) << (scores[11] >= 0 ? to_string(scores[11]) : "-") << " |\n";
    cout << setw(5) << " "  << left << setw(20) << "| 13. Chance" << " | " << right << setw(6) << (scores[12] >= 0 ? to_string(scores[12]) : "-") << " |\n";
    cout << setw(5) << " "  << "-------------------------------\n";
}