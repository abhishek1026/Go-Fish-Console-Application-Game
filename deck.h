#ifndef DECK_H
#define DECK_H

using namespace std;
#include "card.h"

class Deck
{
public:
  vector<Card> a;
  Deck() {}
  ~Deck() {}
  Card pop();
  Card peek();
  void push(Card x) { a.push_back(x); }
  vector<Card> shuffle(vector<Card> *x);
  int searchHand(int v);
};

#endif