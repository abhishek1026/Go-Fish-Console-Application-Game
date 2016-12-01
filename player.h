#ifndef PLAYER_H
#define PLAYER_H

using namespace std;
#include "card.h"

class Player
{
  private:
    int score;
    vector<Card> hand;
    string name;

  public:
    bool isOut;
    Player()
    {
        isOut = false;
        score = 0;
    }
    Player(string x)
    {
        set_name(x);
        score = 0;
        isOut = false;
    }
    ~Player() {}
    void set_name(string x) { name = x; }
    string get_name() { return name; }
    int get_score() { return score; }
    vector<Card> get_hand() { return hand; }
    void showHand(vector<Card> *);
    Card grabFromHand(vector<Card> *, int);
    void removePairs(vector<Card> *);
    int lastInd(vector<Card> *, int);
    int searchHand(int r, vector<Card> *);
};

#endif