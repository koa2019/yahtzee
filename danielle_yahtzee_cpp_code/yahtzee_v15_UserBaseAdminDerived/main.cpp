/* 
 * File:    main.cpp
 * Author:  Danielle F
 * Created: 03-28-23 @10 PM
 * Purpose:  yahtzee_v15_UserBaseAdminDerived
 * 
 * v15:
 * Is a copy of survey project v1.
 * Admin inherits User
 * 
 * 
 * To Do:
 * BUG! Admin findByIndx() isn't working correctly and crashes after 1 run.
 * Have it rewrite the entire record in binary reset it recSize & begnFile
 * 
 */

//System Libraries
#include <iostream>  //Input/Output Library
#include <cstdlib> // rand()
#include <ctime>   // time()
#include <string> //string
#include <cstring> //c-strings
#include <cctype> // tolower()
using namespace std;  //STD Name-space where Library is compiled

//User Libraries
#include "User.h"
#include "Admin.h"

//Global Constants not Variables
//Math/Physics/Science/Conversions/Dimensions

//Function Prototypes

//Code Begins Execution Here with function main
int main(int argc, char** argv) {
    //Set random number seed once here
    srand(static_cast<unsigned int>(time(0)));
    //rand()%90+10;//2 digit numbers
    
   // Variables    
    int choice = 0;
    
    //do {
    cout<<"\n\nMenu\n"
        <<"Press 1: Sign Up\n"
        <<"Press 2: User Login\n"
        <<"Press 3: Admin Login\n"
        <<"Press 4: ReadInputFile()\n"
        //<<"Press 5: \n"
        <<"Press 9: Logout\n";
        cin>>choice;
        cin.ignore();
        
        switch(choice){
            case 1:{ // User sign up for new account
                
                User user2("guest","guest@em.com","Gue!234");   
                user2.print1User();
                //user2.signUp();                 
                break;
            }
            case 2:{ // I WANT TO SAVE THIS ADMIN TO A USER so i can play()
             
                Admin admin;  // Create one instance of Admin class
                if(admin.isUsrLogin()){
                    
                    admin.print1User();
                    User user2(admin.getTtlRec(), admin.getID(),admin.getName(),admin.getEmail(),admin.getPwrd());
                 
                } else {cout<<"\nUnable to locate your email.\n";}
                break;
            } 
            case 3:{ // Admin login
                Admin admin2;  // Create one instance of Admin class
                admin2.adminLogin();
                break;
            } 
            case 4:{ 
                User user;    // Create one instance of User class
                user.readInputFile();
                break;
            }
            default: {
                cout<<"\nLogged Out.\n";                
                exit(0);
            }
        }

    return 0;
}

/**********  Function Definitions  **************/