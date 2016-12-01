#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <string>

#include "deck.h"
#include "card.h"
#include "player.h"

using namespace std;

string Card::toString()
{

    string result;

    result = to_string(value) + " of " + suit;

    return result;
}

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

void Player::showHand(vector<Card> *x)
{

    for (int i = 0; i < x->size(); i++)
    {
        string showIfChange;
        int dispRank = x->at(i).get_value();
        bool change = false;
        switch (dispRank)
        {
        case 1:
            showIfChange = "Ace";
            change = true;
            break;
        case 11:
            showIfChange = "Jack";
            change = true;
            break;
        case 12:
            showIfChange = "Queen";
            change = true;
            break;
        case 13:
            showIfChange = "King";
            change = true;
            break;
        }
        string dispRanks = to_string(dispRank);
        string display = change ? showIfChange : dispRanks;
        cout << display << " of " << x->at(i).get_suit() << endl;
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

int Player::searchHand(int r, vector<Card> *x)
{
    for (int i = 0; i < x->size(); i++)
    {
        if (x->at(i).get_value() == r)
        {
            return i;
        }
    }

    return -1;
}
