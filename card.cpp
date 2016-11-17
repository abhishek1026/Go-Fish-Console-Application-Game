#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <vector>

using namespace std;

class Card{
    private:
        int value;
        string suit;
    public:
        int get_value(){return value;}
        string get_suit(){return suit;}
        Card(int valueInput, string suitInput){
            value=valueInput;
            suit = suitInput;
            }
        Card(){}
        ~Card(){}
        void set_value(int x){value = x;}
        void set_suit(string x){suit = x;}
};


class Deck{
  public:
  vector<Card> a;  //vector made of cards
  Deck(){}//default constructor
  ~Deck(){}
  Card pop();
  Card peek();
  void push(Card x){a.push_back(x);}
  void shuffle();
  int searchHand(int v);
  //vector<Card> get_deck(){return a;}
  //void discard(int index, Deck* d); (we think this method should belong to the Player class)
};

class player{
    int numPairs;
    Deck* hand;
    string name;
    
    string set_name(string name);
    void easyComp();
    void hardComp();
    
};

Card Deck::peek(){ //prints the value of the top card of the deck
    if(a.size() > 0){
    cout << a[a.size()-1].get_value() << " of " << a[a.size()-1].get_suit() << endl;
    return a[a.size()-1];
    }

    return  Card(); 
}

//remove the top element of the deck
Card Deck::pop(){

  if(a.empty()){ //check to make sure the stack is not empty
    cout << "\nNo cards left\n";
    return  Card();
  }

  else{ //if there is an element to remove, return it and decrement top
    Card d = a[a.size()-1];
    cout << d.get_value() << " of "  << d.get_suit() << endl;
    return d;
  }
}

void Deck::shuffle(){ //shuffle the deck
    srand(time(NULL));
    int index1, index2;
    Card temp;
    for(int i=0; i<52; i++){
        index1 = rand() % 52; //choose two random cards and swap them
        index2 = rand() % 52;
        temp = a[index1];
        a[index1] = a[index2];
        a[index2] = temp;
    }
}

int Deck::searchHand(int x){ //see if someone's hand contains a certain card
    for(int i=0; i<a.size(); i++){
        if(a[i].get_value()==x)
            return i;
    }
    return -1; //returns index of the matching card if it exists, -1 if it does not exist
}

string player::set_Name(string name){
        name = "player1";
    }
    void player::easyComp(){
        vector<Card> a;
         srand(time(NULL));
         int num = (rand() %13) +1;
         cout << num;
    }
    void player::hardComp(){   
    }

int main(){
    string theSuit = "spades";
    Deck theDeck;

    //initialize the deck
    for(int i = 1; i<=13; i++){
        Card c(i,theSuit);
        theDeck.a.push_back(c);
        theDeck.peek();
    }
    theSuit = "clubs";
    for(int i = 1; i<=13; i++){
        Card c(i,theSuit);
        theDeck.a.push_back(c);
        theDeck.peek();
    }
    theSuit = "diamonds";
    for(int i = 1; i<=13; i++){
        Card c(i,theSuit);
        theDeck.a.push_back(c);
        theDeck.peek();
    }
    theSuit = "hearts";
    for(int i = 1; i<=13; i++){
        Card c(i,theSuit);
        theDeck.a.push_back(c);
        theDeck.peek();
    }
    cout << "\n";
    theDeck.shuffle(); //shuffle
    for(int i = 0; i<52; i++){
        cout << theDeck.a[i].get_value() << " of " << theDeck.a[i].get_suit() << "\n\n";
    }

return 0;
}
