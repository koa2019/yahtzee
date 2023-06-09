/* 
 * File:    main.cpp
 * Author:  Danielle F
 * Created: 3-10-2023 @ 12:36 PM
 * Purpose:  yahtzee group project-userLogin v6
 * 
 * v1:  Reads inputs from user and confirms them in main().
 *      If all inputs are valid, then it prints inputs.
 * 
 * v2:  Creates one name string, one email string, one password string.
 *      Adds functions that confirm each input meets certain criteria.
 *      Prints one name, one email, one password    
 * 
 * v3:  Writes & appends to text and binary file:
 *      size of name string, one name string,
 *      size of email string, one email string,
 *      size of password string, one password string.
 * 
 *      Reads first three strings in from binary file.
 * 
 * v4:  Reads in third record in from binary file
 *      by accumulating the size of each string.  
 *      Stops at the beginning of record 3.
 * 
 * v5:  At this point program can read in three strings and validate
 *      they meet certain requirements, saves the three variables, then
 *      it writes these 3 strings and their lengths to a text & binary file.
 *      The program opens binary file and looks for the third record in it.
 *      Once it finds the record it reads and saves the length of each string
 *      as well as the actual string. Since this is all working 
 *      I added a User class. It took a LOT of adjustments to get this working again.
 *      This version now does everything it was doing in version 4, 
 *      but now it saves the strings and their lengths inside of class.
 * 
 *      Writing and reading files runs in main(). I will them into functions 
 *      once I add a rand() to randRec.
 * 
 * v6:  Added a rand() to randRec, BUT I eventually need to figure out how many 
 *      records are in data.txt because Admin class will be the only one who has 
 *      permission to read the binary file, and they'll be looking for a specific  
 *      user rather than a random user.
 * 
 *      Added int hiScore=0 to class. Added getHiScore(), and
 *      added setHiScore(int score) that accepts a int and checks if is greater
 *      than the current hiScore.
 * 
 *      Wrote hiScore to text and binary.
 *      Confirmed hiScore is being read from binary file. 
 *      Created 1 instance of User class and saved the contents of 1 file that 
 *      was located in from the binary file. But I had to change how the 
 *      mutator member functions set the variables.
 * 
 * To do:
        * Ask how many players are going to play and create an array of users. 
        * Need to add a variable that keeps count of how many records 
          are written. We are appending the files every time the 
          program runs. Static variable doesn't work in main() or in User class.
 *      * Test setHiScore(). It'll have to rewrite the binary file 
 *        @specific location.
        * Change password minSize to 7 after testing is finished.
        * Once User profile is complete, create Admin class 
          and either copy User class or inherit User class.
          Then cut the code that reads binary from the User class 
          and only allow Admin class to read the binary file.
 *      * Put writing and reading to files in their own functions.
 *      * Create a input file to read in dummy info.
 */

//System Libraries
#include <iostream>   //Input/Output Library
#include <cstdlib>   // rand()
#include <ctime>    // time()
#include <string>   //string var
#include <fstream>
using namespace std;  //STD Name-space where Library is compiled

//Global Constants not Variables
//Math/Physics/Science/Conversions/Dimensions

// Function Prototypes


//User Libraries
class User {
    private:
        unsigned short namSiz = 0;
        string name = "";    
        unsigned short emaiSiz = 0;
        string email = "";    
        unsigned short pwrdSiz = 0;
        string password = ""; 
        int hiScore = 0;
        
       
       
    public:
        
         // Private Mutators 
        void setNamSiz(int size) { namSiz = size;}
        void setEmaiSiz(int size){ emaiSiz = size;}
        void setPwrdSiz(int size){ pwrdSiz = size;}
        void setHiScore(int s){ hiScore = s;}
        
        User();     // Default constructor
        ~User();    // Destructor
        
        // Mutators that validate user input before setting member variable
        bool setName();  
        bool setEmail();
        bool setPwrd();
                
        // For reading from binary
        void setName (string str){ name=str;}  // 
        void setEmail(string str){ email=str;}  // 
        void setPwrd (string str){ password=str;}  // 
        
        
        bool isMinSize(string , int);
        bool isStrEqual(string, string);
        bool hasSpecialChars(string);
        bool confrmEmail(string);
        bool checkHiScore(int score=0); // Checks if score is higher than current hiScore
        
        // Accessors   
        unsigned short getNamSiz() const { return namSiz;}
        unsigned short getEmaiSiz() const { return emaiSiz;}
        unsigned short getPwrdSiz() const { return pwrdSiz;}
        string getName() const  { return name;}
        string getEmail() const { return email;}
        string getPwrd() const  { return password;}
        int getHiScore() const  { return hiScore;}
        void print1User (bool,bool,bool) const; 
};

//   Default Constructor
User::User(){
    namSiz = 0;
    name = "";
    emaiSiz = 0;
    email = "";
    pwrdSiz = 0;
    password = ""; 
    hiScore = 0;
}

//   Destructor
User::~User(){
    cout<<"\nHit Destructor(). Static class, so nothing to destroy.\n";
}
       

// Accepts score from game and checks if it is higher than the current hiScore
bool User::checkHiScore(int score){
    if(score > hiScore) { 
        setHiScore(score); // Call private member function to reset hiScore
        return true;
    } 
    return false;
}


// After a user submits their info, it prints a message whether their profile
// was created or not.
void User::print1User(bool isName, bool isEmail, bool isPwrd) const {
    
    if( isName && isEmail && isPwrd){
        cout<<"\nProfile successfully created.\n"
            <<"Name: " << getName() << endl
            <<"Email: " << getEmail() << endl
            <<"Password: ";
        for(int i=0;i<(getPwrd().length()) ;i++){ // prints stars instead of actual password
            cout<< '*';
        }
        cout<<"\nHigh Score: "<<getHiScore()<<endl<<endl;
        
    }
    else { cout<<"\nOops! Profile not created.\n"; }
}


// SET NAME. Loops until a name's length is within the range
bool User::setName(){
    
    bool isLeng=true;
    string n="";
    
    // Loop until a valid name is entered
    do {
        cout<<"\nEnter your name. Must be at least 2 characters: ";
        getline(cin,n);
        
        // Set flag. Confirm name is at least 2 characters long
        isLeng = isMinSize(n,2);
       
    } while(!isLeng);
    
    if(isLeng){
        name = n;     // set variable in class    
        setNamSiz(name.size());  // set this string's length in the class
        return true;
    } else { return false; }
}


//  SET EMAIL. Loops until a email's length is within the range
//             and contains '@' and '.' 
bool User::setEmail(){
    
    bool isEmail = true, 
          isLeng = true;
    unsigned short minSize = 9;
    string em = "";
    
    // Loop until a valid email is entered
    do {
        cout<<"\nEnter your email: ";
        cin>>em;
        
        // Set flags. Confirm emails length and that it contains '@' and '.'
        isEmail = confrmEmail(em);
        isLeng = isMinSize(em, minSize);
        
    } while( !isEmail || !isLeng );
    
    if(isEmail && isLeng){
        email = em;   // set variable in class
        setEmaiSiz(email.size()); // set this string's length in the class
        return true;
        
    } else { return false; }
}


//  SET PASSWORD.  Loops until a password's length is within the range
//             and contains at least 1 digit, 1 uppercase and 1 special char
bool User::setPwrd(){
    
    bool isPwd   = true,  
         isLeng  = true,
         hasSpCh = true;
    unsigned short minSize = 4;    
    string pwd="",
           tempPwd="";
    
    
    //  Loop until password AND temp password are exactly the same
    //  and it is at least the minimum length
    do{
       
        // Loop until password is correct length 
        do{
            cout<<"\nPassword must be at least "
                <<minSize<<" characters long, and "  
                <<"\ninclude: 1 uppercase letter, 1 digit, "
                <<"and 1 special character (! $ #)."
                <<"\nEnter your password:   ";       
            cin>>pwd;
            
            // Set flag. Confirm string length is a minimum length
            isPwd = isMinSize(pwd,minSize);            
            
            // Confirm password has digit, uppercase and $,!, or # in it
            hasSpCh = hasSpecialChars(pwd);            
            
        } while(!isPwd && !hasSpCh);
        
        
        // Loop until temp password is correct length 
        do {
            cout<<"\nConfirm your password: ";
            cin>>tempPwd;
            
            // Set flag. Confirm string length is a minimum length
            isPwd = isMinSize(tempPwd,minSize); 
            
           // Confirm tempPwd has digit, uppercase and $,!, or # in it
           hasSpCh = hasSpecialChars(tempPwd);             
            
        } while(!isPwd && !hasSpCh);        
                
        //  Confirm password is the exactly the same as temp password 
       isPwd = isStrEqual(pwd,tempPwd);       
         
    } while( !isPwd );
    
    if(isPwd){
        password = pwd; // set variable in class    
        setPwrdSiz(password.size());  // set this string's length in the class
        return true;
        
    } else { return false; }
}


/*********  Confirms strings length is within a range  ***********/
bool User::isMinSize(string str, int minLeng){
    
    if(str.length() < minLeng || str.length() > 70){ 
        cout<<"\nError. Minimum length is: "<<minLeng<<endl;
        if(str.length()>70){ cout<<"\nError. Input is too long.\n"; }
        return false; 
    }
    return true;            
}


/*********  Confirms strings have the same exact characters  ***********/
bool User::isStrEqual(string password, string tempPwd){
    
    // confirm strings have the same exact characters
    if( password.compare(tempPwd) !=0 ){ 
        cout<<endl<<"Passwords must match!\n";
        return false; 
    }
    return true;   
}


/*********  Confirms password includes at least 1 digit, uppercase & special char  ***********/
bool User::hasSpecialChars(string password){
     
    bool isValid1=true,
         isValid2=true,
         isValid3=true;
    
    // Check if password has at least 1 digit
    for(int i=0;i<password.length();i++){        
       
        if( isdigit(password[i]) !=0 ){    
            isValid1 = true;
            break;
        } else { isValid1 = false; }
    }  
    
    // Check if password has at least 1 uppercase letter
    for(int i=0;i<password.length();i++){
        if( isupper(password[i]) !=0 ){
            isValid2 = true;
            break;
        } else { isValid2 = false; }  
    }
    
    
    // Check if password has at least 1 special character
    for(int i=0;i<password.length();i++){
        if( password[i]=='!' || password[i]=='$' || password[i]=='#'){
            isValid3 = true;
            break;            
        } else { isValid3 = false; }  
    }
    
    // Return a true/false that says if password meets all the criteria or not
    if( !(isValid1 && isValid2 && isValid3) ){
        cout<<"\nInvalid Password.\n";
        return false;
    } 
    
    return true; 
}


/********    Confirm email string has a '@' AND '.' in it   **************/
bool User::confrmEmail(string email){
    
    // Find these characters in string
    short indxAt =  email.find("@");
    short indxDot = email.find(".");
    //cout<<"indxAt "<< indxAt <<endl<<"indxDot "<< indxDot <<endl;


    // Confirm email has a  '@' AND dot in it. Check if position is -1 or not
    if(indxAt == string::npos || indxDot == string::npos){ // npos=-1 indicates that no matches were found in the string.
        cout<<"\nInvalid email.";
        return false;
    } 
    return true;
}


//Code Begins Execution Here with function main
int main(int argc, char** argv) {
    
    //Set random number seed once here
    srand(static_cast<unsigned int>(time(0)));
    
       
    // Create 1 profile with default constructor 
    User user; 
    bool isNameGood  = user.setName();
    bool isEmailGood = user.setEmail();
    bool isPwrdGood  = user.setPwrd();
    
    // Print 1 profile
    user.print1User(isNameGood, isEmailGood, isPwrdGood);
    
        
 /********* START WRITING TO TEXT AND BINARY FILES  ********/
    
    cout<<endl<<endl;
    
    ofstream outTxt, outBin;
    outTxt.open("data.txt",ios::out | ios::app); // appends content to the current content of the file.
    if(!outTxt.is_open()){ cout<<"\nError opening outTxt.txt\n";}
    
    outBin.open("data.dat",ios::out | ios::app | ios::binary); // appends content to the current content of the file.
    if(!outBin.is_open()){ cout<<"\nError opening outBin.dat\n";}
    
    unsigned short sizeN = 0, sizeE = 0, sizeP = 0;
    sizeN = user.getNamSiz();     // get size of this string
    sizeE = user.getEmaiSiz();    // get size of this string
    sizeP = user.getPwrdSiz(); // get size of this string
    int hScore = user.getHiScore(); // get value of hiScore from class
    //cout<<"\nsizeN= "<<sizeN<<"\nsize= "<<sizeE<<"\nsizeP= "<<sizeP<<endl; 
    
    /**************   WRITE 1 RECORD TO TEXT FILE  ***************/
    
    int record = 0;
    outTxt<<"Record "<<record++<<endl;
    outTxt<<"namSiz:  "<<sizeN<<endl; // write the size of this string to text file
    outTxt<<"name:  "<<user.getName()<<endl;  // write this string to text file
    outTxt<<"emaiSiz: "<<sizeE<<endl; // write the size of this string to text file
    outTxt<<"email: "<<user.getEmail()<<endl;  // write this string to text file
    outTxt<<"pwrdSiz: "<<sizeP<<endl; // write the size of this string to text file
    outTxt<<"pwrd:  "<<user.getPwrd()<<endl;   // write this string to text file
    outTxt<<"hiScore: "<<hScore<<endl<<endl;
  
    
    /**************   WRITE 1 RECORD TO BINARY FILE  ***************/    
    
    outBin.write(reinterpret_cast<char *>(&sizeN), sizeof(sizeN) ); // write the size of this string to binary file
    outBin.write( (user.getName().c_str() ), sizeN); // write this actual string to binary file
    
   
    outBin.write(reinterpret_cast<char *>(&sizeE), sizeof(sizeE) ); // write the size of this string to binary file
    outBin.write((user.getEmail().c_str() ), sizeE); // write this actual string to binary file
    
   
    outBin.write(reinterpret_cast<char *>(&sizeP), sizeof(sizeP) ); // write the size of this string to binary file
    outBin.write( (user.getPwrd().c_str()), sizeP); // write this actual string to binary file
    
    outBin.write(reinterpret_cast<char *>(&hScore) , sizeof(int) ); // write hiScore
    
    // close files
    outTxt.close();
    outBin.close();
    
    
    
    /*********   READ BINARY FILE & Find 1 record    ********/
    int recIndx = 4; //(rand()%(0+7)); // As of now there's 8 records in data.txt
        
    ifstream inTxt;
    inTxt.open("data.txt",ios::in); // appends content to the current content of the file.
    if(!inTxt.is_open()){ cout<<"\nError opening inTxt.txt\n";}

    ifstream inBin;
    inBin.open("data.dat",ios::in | ios::binary); // appends content to the current content of the file.
    if(!inBin.is_open()){ cout<<"\nError opening inBin.dat\n";}
    
    long cursor = 0L;
    int count = 1;    // start at 1, so it stops before the randRec
    unsigned short sz = 0;
    hScore = 0;
        
      
    cout<<endl<<endl<<"Looking for record "<<recIndx<<" in binary file.\n\n";
    
    while(count<=recIndx){
                    
        inBin.seekg(cursor,ios::beg);  // set is set to the beginning of the cursor's value  
        
        // Read the value of namSiz and then use it to calculate the number of bits
        // that namSiz and name take up in memory. 
        // Add it to cursor and move on to the next variables
        inBin.read(reinterpret_cast<char *>(&sz), sizeof(sz) ); // read the size of this string to binary file       
        cursor += ( sizeof(sz) + sz*sizeof(char) );
        //cout<<"     sizeof(sz) = "<<sizeof(sz)<<"\nsz*sizeof(char) = " << sz*sizeof(char)<<endl; 
        //cout<<"this record sum = "<< (sizeof(sz) + sz*sizeof(char)) <<endl;
        //cout<<"\t   cursor = "<<cursor<<endl;
        
        
        inBin.seekg(cursor,ios::beg); // move cursor to the beginning of the next record

        // Read the value of emaiSiz and then use it calculate the number of bits
        // that emaiSiz and email take up in memory. 
        // Add it to cursor and move on to the next variables
        sz = 0;
        inBin.read(reinterpret_cast<char *>(&sz), sizeof(sz) ); // read the size of this string to binary file              
        cursor += ( sizeof(sz) + sz*sizeof(char) );
        //cout<<"     sizeof(sz) = "<<sizeof(sz)<<"\nsz*sizeof(char) = " << sz*sizeof(char)<<endl;          
        //cout<<"this record sum = "<< (sizeof(sz) + sz*sizeof(char)) <<endl;
        //cout<<"\t   cursor = "<<cursor<<endl;
        
        inBin.seekg(cursor,ios::beg); // move cursor to the beginning of the next record
        
        // Read the value of pwrdSiz and then use it calculate the number of bits
        // that pwrdSiz and password take up in memory. 
        // Add it to cursor and move on to the next variables
        sz = 0;
        inBin.read(reinterpret_cast<char *>(&sz), sizeof(sz) ); // read the size of this string to binary file      
        cursor += ( sizeof(sz) + sz*sizeof(char) );        
        //cout<<"     sizeof(sz) = "<<sizeof(sz)<<"\nsz*sizeof(char) = " << sz*sizeof(char)<<endl;    
        //cout<<"this record sum = "<< ( sizeof(sz) + sz*sizeof(char) ) <<endl;
        //cout<<"\t   cursor = "<<cursor<<endl;
        
        inBin.read(reinterpret_cast<char *>(&hScore) , sizeof(int) ); // write the size of this string to binary file
        cursor += sizeof(hScore);  // size of int hiScore  
        //cout<<sizeof(hScore)<<endl;
        //cout<<"\t   cursor = "<<cursor<<endl;
        
        count++;
    }
    
    //cout<<endl<<endl;
    //cout<<"cursor = "<<cursor<<" which means it's at the last bit before the record we're looking for.\n\n"; 
    
    cout<<"Found record "<<recIndx<<endl;
    
    string nme  = "";
    string emai = "";
    string pwd  = "";    
       
    User oneUser;
    //oneUser.print1User(true,true,true);
    
    // sets cursor at the beginning of the file we're looking for
    inBin.seekg(cursor,ios::beg);
    
    // Read & save the length of name and the name string
    sz = 0;
    inBin.read(reinterpret_cast<char *>(&sz), sizeof(sz) ); 
    oneUser.setNamSiz(sz);   
    
    nme = "";
    nme.resize(sz); 
    inBin.read(&nme[0], nme.size());     
    oneUser.setName(nme);
    
    // Read & save the length of email and the email string
    sz = 0;
    inBin.read(reinterpret_cast<char *>(&sz), sizeof(sz) ); 
    oneUser.setEmaiSiz(sz);   
    
    emai = "";
    emai.resize(sz);    
    inBin.read(&emai[0], emai.size()); // write this actual string to binary file    
    oneUser.setEmail(emai);
    
    // Read & save the length of password and the password string
    sz = 0;
    inBin.read(reinterpret_cast<char *>(&sz), sizeof(sz) ); // write the size of this string to binary file
    oneUser.setPwrdSiz(sz); // set size of password string
    
    pwd = "";
    pwd.resize(sz);   
    inBin.read(&pwd[0], pwd.size()); // write this actual string to binary file    
    oneUser.setPwrd(pwd);
    
    // Read & save hiScore
    hScore=0;
    inBin.read(reinterpret_cast<char *>(&hScore) , sizeof(int) ); // write the size of this string to binary file
    oneUser.setHiScore(hScore);
    
    oneUser.print1User(true,true,true);
    cout<<"nme = "<<nme<<endl;
    cout<<"emai = "<<emai<<endl;
    cout<<"pwd = "<<pwd<<endl;
    cout<<"hiScore = "<<hScore<<endl;
    
    inBin.close();
    inTxt.close();
    
    
    return 0;
}