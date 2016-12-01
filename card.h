#ifndef CARD_H
#define CARD_H

using namespace std;
class Card
{
private:
  int value;
  string suit;

public:
  int get_value() { return value; }
  string get_suit() { return suit; }
  Card(int valueInput, string suitInput)
  {
    value = valueInput;
    suit = suitInput;
  }
  Card() {}
  ~Card() {}
  void set_value(int x) { value = x; }
  void set_suit(string x) { suit = x; }
  string toString();
};

#endif