//To do: selectDice(a), selectCategory(a, name, rnd), setFinalSC(), setHiScore()

// Global constants for Yahtzee Class
const MINSIZE = 2;
const MAXROLLS = 3;
const MAXRND = 13;


// Event listener for each scorecard categories' button
function catgyOnClick() {

    //console.log("Hit catgyOnClick()");       
    alert("this.value=" + this.value);
    alert("this.name=" + this.name);

    // remove the event listener so that the button becomes static
    this.removeEventListener("click", catgyOnClick);

//    const buttons = document.querySelectorAll('button'); // select all button elements
//    for (const button of buttons) {
//        button.addEventListener('click', () => {
//            button.style.backgroundColor = 'transparent'; // remove the hover effect by setting the background color to transparent
//        });
//    }
}

// Event listener for each dice button
function diceOnClick() {
    console.log("Hit diceOnClick()");
    alert("dice.value=" + this.value);
    //this.removeEventListener("click", diceOnClick);  // remove the event listener so that the button becomes static
}


//*****************************************************************
// Yahtzee Constructor. Public properties of Yahtzee class 
//*****************************************************************

function Yahtzee() {
    //console.log("Hit Yahtzee()");   
    this.setP1Winner(false);
    this.setNPlayer(MINSIZE);
    this.setIndex(0);
    this.choice = 0; // User choice made during play()
}

//*****************************************************************
//        Print nPlayers div
//*****************************************************************

Yahtzee.prototype.printNPlayrDiv = function () {

    var nPlayrDiv = document.getElementById('nPlayrDiv');
    var string = "Enter 1 or 2 players?";
    string += '<input type="text" id="nPlayrInput" name="nPlayrInput" min="1" max="4" required size="1">';
    string += '<button type="submit" id="nPlayrBtn">Enter</button>'; //onclick="choiceOnClick()"
    nPlayrDiv.innerHTML = string;
    document.getElementById("nPlayrBtn").addEventListener("click", this.nPlayrOnClick);
};


Yahtzee.prototype.nPlayrOnClick = function () {
    //console.log("Hit nPlayrOnClick()");
    var num = this.value;
    alert("nPlayrInput =" + num);
    //num = (num == null ) ? 1 : num;
    this.nPlayer = num;         //this.setNPlayer(num);
    console.log("Hit nPlayrOnClick().  num =" + num + "  this.nPlayer=" + this.nPlayer);
};

//*****************************************************************
//        Writes play() menu 
//*****************************************************************

Yahtzee.prototype.printPlayMenu = function () {
    var msgDiv = document.getElementById('msgDiv');
    var string = "<br> Options: <br>";
    string += "1: Select which dice you want to keep before rolling again.<br>";
    string += "2: Pick category and end your turn<br>";
    string += "3: Roll again.<br>";
    string += "4: Exit<br>";
    string += "Enter a number: ";
    string += '<input type="text" id="choiceInput" name="choiceInput" min="1" max="4" required size="1">';
    string += '<button type="submit" id="menuBtn">Enter</button>'; //onclick="choiceOnClick()"
    msgDiv.innerHTML = string;
    document.getElementById("menuBtn").addEventListener("click", this.choiceOnClick);
};

//*****************************************************************
//        Get and return player's choice from printPlayMenu()
//*****************************************************************

Yahtzee.prototype.choiceOnClick = function () {
    //console.log("Hit choiceOnClick()");
    var resp = 1;
    resp = document.getElementById('choiceInput').value; //cin>>resp;
    this.choice = resp;//this.setChoice(resp); //
    console.log("Hit choiceOnClick(). resp=" + resp + "  this.choice=" + this.choice);
};


//*****************************************************************
//
//*****************************************************************

Yahtzee.prototype.setChoice = function (num) {
    this.choice = num;
};


//*****************************************************************
//
//*****************************************************************

Yahtzee.prototype.getChoice = function () {
    return this.choice;
};


//*****************************************************************
//
//*****************************************************************

Yahtzee.prototype.welcomeMsg = function (name) {
    console.log("this.nPlayer=" + this.nPlayer);
    if (this.nPlayer > 1) {
        var string = name[0] + " vs " + name[1];
    } else {
        string = "Welcome " + name[0];
    }
    document.getElementById("rollDiv").innerHTML = string;
};


//**********************************************************
//              Controls rounds
//**********************************************************
Yahtzee.prototype.startGame = function (user) {

    //console.log("Hit startGame()");
    var player = new Array(MINSIZE);
    player[0] = new User(1);  // Aggregate Array of User Class
    player[1] = new User(2);

    var scorecard = new Array(MINSIZE);
    var finalSC = new Array(MINSIZE);

    for (var i = 0; i < scorecard.length; i++) {
        scorecard[i] = new ScoreCard();  // possible scorecard points. Aggregates Array of ScoreCard class
        finalSC[i] = new ScoreCard();   // final scorecard. Aggregates Array of ScoreCard class
    }

    finalSC[0].printDice(i);           // Writes player1 dice elements to ScoreCard.html
    player[0].setName(user.getName());// Reset player 1's name with user's name
    var name = [player[0].getName(), player[1].getName()];// Create array for player's name
    this.getRules();  // Print rules    
    console.log("startGame().  this.nPlayer=" + this.nPlayer);
    this.welcomeMsg(name);          // print welcome message depending on num players
    document.getElementById("diceCol").style.visibility = "visible";//"hidden"; 
    document.getElementById("scorecardCol").style.visibility = "visible";//"hidden"; 

    // Game runs for MAXRND = 13 rounds. 1 round per category
    for (var rnd = 1; rnd <= 1; rnd++) {

        finalSC[0].setRound(rnd); // set & write round to ScoreCard.html
        //this.play(player, scorecard, finalSC, 0);

        //if there's 2 players and round is less than or equal to MAXRND
        if (this.nPlayer > 1 && (finalSC[0].getRound() <= MAXRND)) {
            //finalSC[1].setRound(rnd); // set round in final ScoreCard
            //this.play(player, scorecard, finalSC, 1);
        }
    } // ends round for(rnd < 13 )            

    //console.log("Outside of rounds loop");
//    //this.p1Winner = this.getP1Winner(player, finalSC);  // Print player's final scorecards
//    //var isTrue = this.getP1Winner(player, finalSC);  // Print player's final scorecards
//    this.getP1Winner(player, finalSC, 0);  // Print player's final scorecards
//    
//    
//    finalSC[0].setRound(finalSC.NUM_CATGRY);               // Set round to last round for each player, so it'll 
//    finalSC[1].setRound(finalSC.NUM_CATGRY);               // check if they hit upperScore bonus in printFinalSC()
//    finalSC[0].printFinalSC( player[0].getName() );// Print player 1's final scorecard 
//    
//    // if 2 players, then print player 2's final scorecard
//    if(this.nPlayer > 1) { finalSC[1].printFinalSC( player[1].getName() ); }  // Print player 2's final scorecard 
//    
//    console.log("<br/><br/>   Game Over!<br/>");
//    
//    // if nPlayer === 1, then p1 automatically winner
//    if(this.nPlayer === 1) { this.p1Winner = true; } 
//    
//    else { // If there is more than 1 player
//    
//        console.log("<br/>"+ player[0].getName() + " vs " + player[1].getName() + "<br/>");
//        console.log(player[0].getHiScore() + "     vs " + player[1].getHiScore());
//        
//        var msg = "";
//        
//        // Check is p1 is winner, tie or loser
//        if( player[0].getHiScore() > player[1].getHiScore() )
//        {
//           msg = player[0].getName() + " won!<br>"; 
//           this.p1Winner = true;
//            
//        } else if(player[0].getHiScore() === player[1].getHiScore()){
//        
//            msg ="Tie Game!\n";
//            this.p1Winner = true;
//            
//        } else { 
//            
//            this.p1Winner = false; 
//            msg = "Uh-Oh..." + player[1].getName() + " won!\n";
//        }
//        
//        console.log("<br/>"+ msg +"<br/>");        
//    }
//
//
//    if (!this.p1Winner) { // if player 1 is NOT winner
//
//        //alert("p1Winner===false"); 
//        console.log("<br/><br/>Good Game!<br/>");
//        return false;
//
//    } else {
//        return this.isNewHiScore(user, player[0].getHiScore()); // return whether or not p1 has new hiScor
//    }
//
    console.log("End of startGame()");
};


//**********************************************************
//              This player's turn
//              a = player's index
//**********************************************************
Yahtzee.prototype.play = function (player, scorecard, finalSC, pIndx) {

    console.log("Hit play()");
    var numRolls = 0,
            rnd = finalSC[pIndx].getRound(),
            name = player[pIndx].getName();

    /**********************  START THIS PLAYER'S TURN  *************************/

    numRolls = 1; // Reset for each player's turn   

    // loop as long as numRolls does NOT equal 3
    while (!(numRolls === MAXROLLS)) {

        var string = name + "s turn. Roll " + numRolls;
        console.log(string);
        document.getElementById("rollDiv").innerHTML = string;//.append(string);
        //this.pause('r');          //replace with addEventListener to mimic rolling dice
        //scorecard[pIndx].setDice();   // Re-Roll dice   
        //numRolls++;                  // increment numRolls every time dice are rolled       


        // Set & print scorecard with possible points based on dice values
        scorecard[pIndx].fillScoreCard();

        // if it is last roll, force switch case 2 to run
        if (numRolls === MAXROLLS) {
            this.choice = 2;

        } else { //BUG! WON'T WRITE DICE WITH menuPrompt() and PlayMenu() onclick not working
            //this.menuPrompt(); 
            //this.printPlayMenu();//
            //this.checkChoice();
        }
        console.log(" play()  this.choice = " + this.getChoice());


        switch (this.choice) { // choose dice to keep, pick a category, re-roll or exit game

            case '1':  // Select dice you want to keep in between rolls
            {
                //console.log("hit switch case 1");
                this.selectDice(scorecard, pIndx);
                numRolls++;                  // increment numRolls every time dice are rolled   
                break;
            }
            case '2': // Keep points from 1 category and end their turn
            {
                console.log("hit switch case 2");
                numRolls = MAXROLLS; // reassign it, so while(numRolls<maxRolls) stops


                // Ask player to pick category & set player's final scorecard's points each time they choose a category         
                finalSC[pIndx].setFinalSC(scorecard[pIndx]); //selectCategory(a, name, rnd); 


                // reset player's hiScore each time finalSC is changed
                finalSC[pIndx].setUpLowSums();
                player[pIndx].setHiScore(finalSC[pIndx].getTotalScore());
                //console.log("<br/>" + name + "'s hiScore = " + player[pIndx].getHiScore() + "<br/>");


                // if it is NOT the last round, then print player's final scorecard
                if (!(rnd === MAXRND)) {
                    finalSC[pIndx].printFinalSC(name);

                } else { // If it IS the last round AND there are 2 players,
                    // AND it's player 1's turn, then print their final scorecard

                    if ((this.nPlayer > 1) && (pIndx === 0)) {
                        finalSC[pIndx].printFinalSC(name);

                    } else {
                        console.log("<br/>  Tallying final score...<br/>");
                        this.pause();
                    }
                }
                break;
            }
            case '3':  // Roll dice again by breaking out of switch()
            {
                console.log("hit switch case 3");
                numRolls++; // increment numRolls every time dice are rolled                   
                break;
            }
            default: // if they exit early, then reset values to break out of 
            {        // all the loops & print final scorecards

                //alert("Hit switch default...<Leaving program>");
                console.log("Hit switch default...Leaving program");
                finalSC[0].setRound(finalSC.NUM_CATGRY); // set round in final ScoreCard to end game
                numRolls = MAXROLLS;
                return;
            }
        } // ends switch(this.choice)  
    } // ends while(!(numRoll == MAXROLLS))    
};


// display options for User to choose.
Yahtzee.prototype.checkChoice = function () {

    this.menuPrompt();
    //this.printPlayMenu();
    //document.getElementById("msgDiv").style.visibility = "visible";
    //this.choice = 1;
    //console.log("checkNRolls() else{} this.choice = " + this.choice);
    console.log("checkChoice() this.choice = " + this.getChoice());
};



//*****************************************************************
//              Select dice player wants to keep
//*****************************************************************
Yahtzee.prototype.selectDice = function (scorecard, pIndx) {

    //console.log("Hit selectDice()");    
    pIndx = (pIndx < 0) ? 0 : pIndx;
    var ans = 0;
    var string = "Enter the dice numbers (1-5) to keep, separated by spaces, or -1 to stop:";

    // Push the dice they WANT OR DON'T into vector? 
    do {
        ans = prompt(string); //cin >> choice; 
        //console.log("  selectDice().  ans="+ans); 
        scorecard[pIndx].pushThisDice(ans - 1);
        console.log("In selectDice().  Keeping Dice" + ans + ": " + scorecard[pIndx].getDice(ans - 1));
    } while ((ans === '1') || (ans === '2') || (ans === '3') || (ans === '4') || (ans === '5'));
};


//*****************************************************************
//              Set p1Winner true/false
//*****************************************************************
Yahtzee.prototype.setP1Winner = function (bool) {
    this.p1Winner = bool;
};

//*****************************************************************
//              Set number of players
//*****************************************************************
Yahtzee.prototype.setNPlayer = function (num) {
    this.nPlayer = num;
};

//*****************************************************************
//          Set index for which player it is in player array
//*****************************************************************
Yahtzee.prototype.setIndex = function (i) {
    this.index = i;
};

//*****************************************************************
//              Get p1Winner true/false
//*****************************************************************
Yahtzee.prototype.getP1Winner = function () {
    return this.p1Winner;
};

//*****************************************************************
//              Get number of players
//*****************************************************************
Yahtzee.prototype.getNPlayer = function () {
    return this.nPlayer;
};


//*****************************************************************
//      Get index for which player it is in player array
//*****************************************************************
Yahtzee.prototype.getIndex = function () {
    return this.index;
};


//******************************************
//      pause screen before continuing
//******************************************
Yahtzee.prototype.pause = function (ch) {

    console.log("Hit pause()");
    var msg = (ch === 'r') ? "roll." : "continue.";
    var msg2 = "Press enter to " + msg;
    if (confirm(msg2) === true) { //cin.get(); // captures enter from keyboard
        return true;
    }
    return false;
};


//******************************************
//          Print Yahtzee rules
//******************************************
Yahtzee.prototype.getRules = function () {
    var string = "WELCOME TO YAHTZEE!! <br><br>";
    string += "RULES: <br><br>";
    string += "Yahtzee is a game played with five dice, where the objective is to score as many points as possible in 13 rounds. <br>";
    string += "Each player takes turns rolling the dice up to three times per turn, trying to achieve certain combinations. <br>";
    string += "After each turn, the player must choose a category to score their points in, and that category cannot be used again. <br><br><br><br>";
    //confirm(string);
    document.getElementById("msgDiv").innerHTML = string;
};