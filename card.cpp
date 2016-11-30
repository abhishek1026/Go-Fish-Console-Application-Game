#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <string>

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

string Card::toString()
{

    string result;

    result = to_string(value) + " of " + suit;

    return result;
}

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

Card Deck::peek()
{
    if (a.size() > 0)
    {
        Card d = a[a.size() - 1];
        cout << d.get_value() << " of " << d.get_suit() << endl;
        return d;
    }
    else
        return Card();
}

Card Deck::pop()
{
    if (a.size() > 0)
    {
        Card d = a[a.size() - 1];
        cout << d.get_value() << " of " << d.get_suit() << endl;
        a.erase(a.begin() + (a.size() - 1));
        return d;
    }
    else
        return Card();
}

vector<Card> Deck::shuffle(vector<Card> *x)
{ //shuffle the deck
    srand(time(NULL));
    int index1, index2;
    Card temp;
    int size = x->size();
    vector<Card> a = *x;
    for (int i = 0; i < 100; i++)
    {
        index1 = rand() % size; //choose two random cards and swap them
        index2 = rand() % size;
        temp = a[index1];
        a[index1] = a[index2];
        a[index2] = temp;
    }

    return a;
}

int Deck::searchHand(int x)
{ //see if someone's hand contains a certain card
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i].get_value() == x)
            return i;
    }
    return -1; //returns index of the matching card if it exists, -1 if it does not exist
}

class Player
{
  private:
    int score;
    vector<Card> hand;
    string name;

  public:
    Player()
    {
        score = 0;
    }
    Player(string x)
    {
        set_name(x);
        score = 0;
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
};

void Player::showHand(vector<Card> *x)
{
    vector<Card> a = *x;

    for (int i = 0; i < x->size(); i++)
    {
        cout << a[i].get_value() << " of " << a[i].get_suit() << endl;
    }
}

Card Player::grabFromHand(vector<Card> *x, int index)
{
    Card result = x->at(index);
    x->erase(x->begin() + index);

    return result;
}

void Player::removePairs(vector<Card> *x)
{
    int size = x->size();

    for (int i = 0;
         i < (size - 1);
         i++)
    {
        int index = lastInd(x, x->at(i).get_value());
        if (index > i)
        {
            x->erase(x->begin() + index);
            x->erase(x->begin() + i);
            score++;
            i--;
        }
        size = x->size();
    }
}

int Player::lastInd(vector<Card> *d, int c)
{
    int start;

    for (start = d->size() - 1; start >= 0; start--)
    {
        if (d->at(start).get_value() == c)
        {
            return start;
        }
    }

    return -1;
}

/*int main()
{

    Player abhi("abhi");

    vector<Card> cards = (abhi.get_hand());

    vector<Card> *cardspointer = &cards;

    for (int i = 1; i < 11; i++)
    {
        cards.push_back(Card(i, "Spades"));
        cout << "# of cards: " << cards.size() << endl;
    }

    cout << abhi.get_name() << " has these cards in his hand before shuffling: " << endl;

    for (int i = 0; i < cards.size(); i++)
    {
        cout << cards[i].get_value() << "  " << cards[i].get_suit() << endl;
    }

    Deck d;

    cards = d.shuffle(cardspointer);

    cout << "After shuffling: " << endl;

    abhi.showHand(cardspointer);

    Player raj("raj");

    vector<Card> rajhand = raj.get_hand();

    vector<Card> *rajptr = &rajhand;

    rajhand.push_back(Card(1, "Hearts"));

    rajhand.push_back(Card(2, "Hearts"));

    cout << raj.get_name() << " has these cards in his hand before grabbing: " << endl;

    raj.showHand(rajptr);

    rajhand.push_back(raj.grabFromHand(cardspointer, abhi.lastInd(cardspointer, 1)));

    rajhand.push_back(raj.grabFromHand(cardspointer, abhi.lastInd(cardspointer, 2)));

    cout << "Cards with value 1 and 2 taken from Player 1 and given to Player 2: " << endl;

    cout << raj.get_name() << " has these cards in his hand after grabbing: " << endl;

    raj.showHand(rajptr);

    cout << abhi.get_name() << " has these cards in his hand after getting robbed: " << endl;

    abhi.showHand(cardspointer);

    raj.removePairs(rajptr);

    cout << raj.get_name() << " has a score of: " << raj.get_score() << endl;

    return 0;
}*/
