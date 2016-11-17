#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <string>

#include "card.cpp"


using namespace std;

void displayRules();
void displayMenu();
void startNewGame();
/*
 * 
 */
int main() {
    //Variables
    int menuChoice;
    cout << "Welcome to Go Fish \n"<<endl;
    displayMenu();
    
    //To do, Make sure input is an integer.
    cin >> menuChoice;
    
    while(menuChoice != 3){
        switch (menuChoice){
            case 1:{
                void startNewGame();
                break;
            }
            case 2: {
                void displayRules();
                break; 
            }
            default: 
            cout <<"Sorry that is not a valid choice. Please choose another option."<<endl;
            
        }
    }
    cout <<"Thanks for playing!";
    return 0;
}

//Displays a menu to the user that allows them to start a game or 
//view the rules.
void displayMenu(){
    cout<<"1. Start a new game" << endl;
    cout<<"2. View Rules"<< endl;
    cout<<"3. Exit"<< endl;
}

void displayRules(){
    
    cout<<"Setup:"<<endl;
    cout<<"Each player is dealt seven cards."<<endl;
    
    cout<<"Goal:"<<endl;
    cout<<"The purpose the game is to make pairs of cards of the same rank."<<endl;
    
    cout<<"Game Play:"<<endl;
    cout<<"Moving clockwise, players take turns asking a specific player for a/n" 
           " given rank of card. If someone asks you for a rank that you have, the\n" 
           " cards are taken from your hand. if you do not have any cards of that rank,\n"
           " your opponent must go fish, taking one new card from the deck. "<<endl;
    cout<<"If a player runs out of cards in their hand they draw seven more from the deck."<<endl;
    
    cout<<"Ending The Game:"<<endl;
    cout<<"Play continues until all hands are empty and there are no more cards to draw from.\n" 
          " The winner is the player with the most pairs at the end of the game."<<endl;
    
    return;
}

//Sets up a new game
void startNewGame(){
    string playerName;
    int numberOfAl;
    
    //Gets player name
    cout<<"Enter your name: ";
    cin>>playerName;
    //Gets number of opponents from the user
    cout<<"\nEnter desired number of computer opponents (1-3): ";
    cin>>numberOfAl;
    
    //Initialize Player Objects
     
            //Initialize Computer
        
    
            //Initialize User
    
    //Initialize main deck
    
    //Deal hands
}
