// Global constants for ScoreCard Class
var NUM_DICE = 5;
var NUM_CATGRY = 13; // number of scoring categories

// ScoreCard object constructor. Public properties of ScoreCard class
function ScoreCard() {
    
    //console.log("Hit ScoreCard() Constructor");
    this.setFName("");
    this.round=0; //this.setRound(0);
    this.upperScore = 0;
    this.lowerScore = 0;
    this.isCatgryPicked = [NUM_CATGRY]; // Stops categories from being overwritten or displayed twice
    this.scores = [NUM_CATGRY];     // points for each of 13 categories in scorecard
    this.dice = [NUM_DICE]; // ? Are we using this cuz we have a local one in play() or do we need to connect it with local in play()
    this.selected = [];  // Create vector for the this.dice we're keeping for final points

    // Initialize array of Dice class object
    for (var i = 0; i < NUM_DICE; i++) {
        this.dice[i] = 0;
        this.printDice(i); 
        //console.log("ScoreCard() dice["+i+"]="+this.dice[i]);
    }
    
    // Initialize arrays
    for (var c = 0; c < NUM_CATGRY; c++) {
        this.scores[c] = -1;
        this.writeAScore(c); // Writes element to ScoreCard.html
        this.isCatgryPicked[c] = false;
    }
};



//************************************************************
//      Write one scores element to ScoreCard.html
//************************************************************
ScoreCard.prototype.writeAScore = function (indx) {    
    //console.log("Hit writeAScore()");    
    document.getElementById('catgy'+indx).innerHTML = this.scores[indx]; // display the value on the button   
};



//************************************************************
//               Fill scorecard with possible points
//************************************************************
ScoreCard.prototype.fillScoreCard = function (name) {    
    
    this.setFName(name);
    var NUM_DICE_SIDES = 6;
    var temp_scores = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];   
    var counts = [0, 0, 0, 0, 0, 0];
    this.dice.sort(); // Sort array in ascending order  

    // Loops 5 times and is Accumulating how many dice are the same and their total pts
    for (var i = 0; i < NUM_DICE; i++) {
        var index = this.dice[i] - 1;
        counts[index]++;                     
        temp_scores[index] += this.dice[i]; 
        //console.log("index = " + index + "  this.dice[" + i + "] = " + this.dice[i]);
    }
    
    // Set & write possible points to scorecard's upper section
    for (var i = 0; i < NUM_DICE_SIDES; i++) {
        this.recordScore(i + 1, temp_scores[i]);
    }

    //  Set flags for checking Lower section of scorecard starts here 
    var three_of_a_kind = false;
    var four_of_a_kind = false;
    var full_house = false;
    var small_straight = false;
    var large_straight = false;
    var yahtzee = false;
    var chance = 0;
     
    // Check for Three and four of a kind
    for (var i = 0; i < NUM_DICE_SIDES; i++) {
        if (counts[i] >= 3) {
            three_of_a_kind = true;
             //console.log("three_of_a_kind = true");
            if (counts[i] >= 4) {
                four_of_a_kind = true;
                //console.log("four_of_a_kind = true");
                if (counts[i] === NUM_DICE) {
                    yahtzee = true;
                }
            }
        }
        chance += i+1 * counts[i]; // Each die contributes its face value multiplied by its count to the chance score
    }

    // 3 or 4 of kind is true, then set pts in scores[] 
    this.recordScore(7, three_of_a_kind ? chance : 0); // Assuming score categories are 1-indexed
    this.recordScore(8, four_of_a_kind ? chance : 0);
    
    // Full house, then set pts in scores[]
    if ((counts.includes(2) && counts.includes(3)) || yahtzee) {
        full_house = true;
    }
    this.recordScore(9, full_house ? 25 : 0);
    
    // Small and Large straight
    for (var i = 0; i < 3; i++) {
        if (counts[i] && counts[i+1] && counts[i+2] && counts[i+3]) {
            small_straight = true;
            if (counts[i+4]) {
                large_straight = true;
                break;
            }
        }
    }
    
    // Small or Large straight, then set pts in scores[]
    this.recordScore(10, small_straight ? 30 : 0);
    this.recordScore(11, large_straight ? 40 : 0);
    
    // Yahtzee, then set pts in scores[]
    this.recordScore(12, yahtzee ? 50 : 0);
    
    // Chance set pts in scores[]
    this.recordScore(13, chance);

   console.log("Hit fillScorecard(). Points Possible...[ "+ this.scores+" ]");   
};


//************************************************************
//     Set scores in the possible points scorecard        
//************************************************************

ScoreCard.prototype.recordScore = function (category, score) {
    //console.log("Inside recordScore().  scorecard.round = " + this.getRound());
    
    var string1 = this.fName + "'s Possible ScoreCard ";
    document.getElementById('finalSCDiv').innerHTML = string1;  
    
    var indx = category - 1; //ScoreCard's range [0,12]
    
    // if it's not last round, then set the scores array with possible points
    if (this.getRound() >= 0 && this.getRound() <= 12) {
        this.scores[indx] = score;
        this.writeAScore(indx); // rewrite points on ScoreCard.html
    }

    // if it is last round AND this category has NOT be selected, then set scores array with possible points
    else if (this.getRound() > 12 && (this.isCatgryPicked[category - 1] === false)) {
        this.scores[indx] = score; // on the last round, it will set the unpicked category to zero instead of -1. Every category has to be picked.
        this.writeAScore(indx); // rewrite points on ScoreCard.html
        
    } else { // -1 sets this category to null value, so they can't choose it from possible scorecard
        this.scores[indx] = -1;
        this.writeAScore(indx); // rewrite points on ScoreCard.html
    } 
};



//*****************************************************************
//             Keep this dice in selected vector
//*****************************************************************
ScoreCard.prototype.pushThisDice = function (choice) {
    //choice -= 1;
    this.selected.push(choice);     
    console.log("      Hit  ScoreCard.pushThisDice().  this.selected = dice" + this.selected);
};



//*****************************************************************
//               Set Dice class array
//*****************************************************************
ScoreCard.prototype.reRoll = function () {

    console.log("Hit reRoll().  this.selected dice = " + this.selected);

    // Re-Roll Dice. loops through selected vector, and checks which this.dice # to re-roll ?
    for (var j = 0; j < NUM_DICE; j++) {

        // https://www.w3schools.com/jsref/jsref_find.asp
        // https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Array/find
        // syntax: array.find(function(currentValue, index, arr),thisValue)
        //var n = this.selected.find(this.isFound(j), j);
        //console.log("Hit reRoll()...keeping dice" + (n));
        
        
        //if(this.selected.find(this.selected.begin(), this.selected.end(), j) === this.selected.end()) {

            //console.log("...Re-Rolling Dice"+j);
            this.roll(j); // re-roll this this.dice
        //}
    }
    this.dice.sort();
    this.printDice();      // Write all dice to html
    this.consoleLogDice();
};


//************************************************************
//           Called in reRoll()
//************************************************************
ScoreCard.prototype.isFound = function (indx) {
    console.log("   Hit isFound(). dice " + indx + " is in this.isCatgryPicked[ ]");
    //var i = (indx === isCatgryPicked[indx]) ? indx : undefined;
    return indx >= 0;
};


//************************************************************
//              Roll & set a single dice
//************************************************************
ScoreCard.prototype.roll = function (i) {
    this.dice[i] = (1 + (Math.floor(Math.random() * 6)));
};



//************************************************************
//              Write 1 dice's value to html
//************************************************************
ScoreCard.prototype.writeADice = function (i) {
    //console.log("Hit writeADice()");  
    var diceBtn = document.getElementById("dice"+i);
    var val = this.getDice(i);
    diceBtn.value = val;
    diceBtn.innerHTML = val;
    //console.log("Hit writeADice().   dice["+i+"] = "+val);
};



//**********************************************************
//                  Write all dice to html
//**********************************************************
ScoreCard.prototype.printDice = function () {
    //console.log("Hit printDice()");
    for (var i = 0; i < NUM_DICE; i++) {
        this.writeADice(i);
        //console.log("Dice[" +i+ "]="+this.dice[i]);
    }
};



//**********************************************************
//          console log all dice 
//**********************************************************
ScoreCard.prototype.consoleLogDice = function () {
    console.log("Hit consoleLogDice().   Rerolled Dice[ "+this.dice+" ]");
};



//************************************************************
//          Calculate totals for upper, lower scorecard sections            
//************************************************************

ScoreCard.prototype.setUpLowSums = function () {

    //console.log("Hit setUpLowSums()");
    // Calculate upper section total points
    var total = 0;
    for (var i = 0; i < 6; i++) {

        if (this.scores[i] >= 0) { // only add values over zero
            total += this.scores[i];
        }

        if (i === 5) { // last points category in upper section of scorecard
            this.upperScore = total;
            //alert("Hit i==5. upperScore=" + this.upperScore +" total="+total);
        }
    }

    // Calculate lower section total points
    total = 0;
    for (var i = 6; i < NUM_CATGRY; i++) {

        if (this.scores[i] >= 0) { // only add values over zero
            total += this.scores[i];
        }
        if (i === 12) { // last points category in lower section of scorecard
            this.lowerScore = total;
            //alert("Hit i==12. lowerScore="+ this.lowerScore +" total="+total);
        }
    }
    //console.log("Hit setUpLowSums().  upperScore = " + this.upperScore + "  lowerScore = " + this.lowerScore);
};


//************************************************************
//          Add upper and lower sections of scorecard  
//      Check if upper section qualifies for bonus points          
//************************************************************

ScoreCard.prototype.getTotalScore = function () {

    var total = 0, bonus=25;

    // if upper section is 63 or more than add 25 pts to total
    if (this.upperScore >= 63) {
        total += bonus;
    }
    total = this.upperScore + this.lowerScore;
    return total;
};


//**********************************************************
//      Prints this player's final ScoreCard Class members
//**********************************************************
ScoreCard.prototype.printFinalSC = function (name) {

    var bonusMin = 63;
    var bonus = (this.getUpperScore() >= bonusMin) ? 25 : 0;
    var string1 = name + "'s Final ScoreCard ";
    this.writeScoreCard ();
    this.setUpLowSums();
    document.getElementById('finalSCDiv').innerHTML = string1;    
    document.getElementById('catgy13').innerHTML = this.getUpperScore();
    document.getElementById('catgy14').innerHTML = bonus;
    document.getElementById('catgy15').innerHTML = this.getLowerScore();
    document.getElementById('catgy16').innerHTML = this.getTotalScore();   
    console.log("Hit printFinalSC(). "+string1+" [ "+this.scores+" ]\n"  
                + "upperScore="+this.getUpperScore() +"  lowerScore="+this.getLowerScore()+" total="+this.getTotalScore());
};


//************************************************************
// Print scores array. Each element represents 1 points category on ScoreCard
//************************************************************
ScoreCard.prototype.writeScoreCard = function () {
    //console.log("Hit writeScoreCard(). scores[ "+ this.scores+" ]"); 
    for (var i = 0; i < NUM_CATGRY; i++) {
        this.writeAScore(i); // Writes element to ScoreCard.html
    }
};



//************************************************************
//              Set bool isCatgryPicked[13]
//************************************************************
ScoreCard.prototype.setWasPicked = function (i) {
    this.isCatgryPicked[i] = true;
    console.log("isCatgryPicked[" + i + "] = "+ this.isCatgryPicked[i]);
};



//************************************************************
//                  Set which round it is
//************************************************************
ScoreCard.prototype.setRound = function (r) {
    this.round = r;   
    //console.log("Hit setRound(). round = " + this.getRound());
    this.writeRound();
};

ScoreCard.prototype.setFName = function (name) {
    this.fName=name;
};

ScoreCard.prototype.writeRound = function() {
    //console.log("Hit writeRound(). round = " + this.getRound());
    var string = "Round " + this.getRound();
    document.getElementById("roundDiv").innerHTML = string;//.append(string);
};

//**********************************************************
//              Return one element in scores array
//**********************************************************
ScoreCard.prototype.getScoreIndex = function (i) {
    console.log("Hit getScoreIndex(). score[] = "+ this.scores[i]);
    return this.scores[i];
};

ScoreCard.prototype.getDice = function (i) {    
    return this.dice[i];
};


//************************************************************
//              Return round
//************************************************************
ScoreCard.prototype.getRound = function () {
    return this.round;
};


//************************************************************
//                  Return upperScore
//************************************************************
ScoreCard.prototype.getUpperScore = function () {
    return this.upperScore;
};

//************************************************************
//                  Return upperScore
//************************************************************
ScoreCard.prototype.getLowerScore = function () {
    return this.lowerScore;
};