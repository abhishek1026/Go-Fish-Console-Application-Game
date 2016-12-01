#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <string>
#include <unistd.h>

#include "card.cpp"

using namespace std;

void displayRules();
int displayMenu();
void startNewGame();

unsigned int tt = 500000;

int main()
{
    int menuChoice;
    cout << "Welcome to Go Fish \n"
         << endl;
    usleep(tt);
    menuChoice = displayMenu();

    while (menuChoice != 3)
    {
        switch (menuChoice)
        {
        case 1:
        {
            usleep(tt);
            startNewGame();
            menuChoice = displayMenu();
            usleep(tt);
            break;
        }
        case 2:
        {
            usleep(tt);
            displayRules();
            menuChoice = displayMenu();
            usleep(tt);
            break;
        }
        default:
            usleep(tt);
            cout << "Sorry that is not a valid choice. Please choose another option." << endl;
            usleep(tt);
            menuChoice = displayMenu();
            usleep(tt);
        }
    }
    cout << "Thanks for playing!\n";
    return 0;
}

//Displays a menu to the user that allows them to start a game or
//view the rules.
int displayMenu()
{
    int result;
    cout << "1. Start a new game" << endl;
    cout << "2. View Rules" << endl;
    cout << "3. Exit" << endl;
    cin >> result;
    return result;
}

void displayRules()
{

    cout << "Setup:" << endl;
    cout << "Each player (1 user/3 AI) is dealt seven cards." << endl;

    cout << "Goal:" << endl;
    cout << "The purpose of the game is to make pairs of cards of the same rank." << endl;

    cout << "Game Play:" << endl;
    cout << "Moving clockwise, players take turns asking a specific player for a"
            " given rank of card. If someone asks you for a rank that you have, the\n"
            " card is taken from your hand. if you do not have any cards of that rank,\n"
            " your opponent must go fish, taking one new card from the deck. "
         << endl;
    cout << "If a player succesfully finds a match from another player, the player's turn continues, as he or she can keep asking other players(clockwise) until the player is forced to go fish." << endl;

    cout << "Ending The Game:" << endl;
    cout << "Play continues until 3 players' hands are empty.\n"
            " The winner is the player with the most pairs/points at the end of the game."
         << endl;

    return;
}

//Sets up a new game
void startNewGame()
{
    string playerName;

    srand(time(NULL));

    cout << "Enter your name: ";
    cin >> playerName;

    Player user(playerName);
    Player a1("AI#1");
    Player a2("AI#2");
    Player a3("AI#3");

    vector<Card> hand = (user.get_hand());

    vector<Card> *handptr = &hand;

    vector<Card> hand1 = (a1.get_hand());

    vector<Card> *handptr1 = &hand1;

    vector<Card> hand2 = (a2.get_hand());

    vector<Card> *handptr2 = &hand2;

    vector<Card> hand3 = (a3.get_hand());

    vector<Card> *handptr3 = &hand3;

    Deck pile;

    for (int i = 1; i < 14; i++)
    {
        pile.a.push_back(Card(i, "Spades"));
    }

    for (int i = 1; i < 14; i++)
    {
        pile.a.push_back(Card(i, "Hearts"));
    }

    for (int i = 1; i < 14; i++)
    {
        pile.a.push_back(Card(i, "Diamonds"));
    }

    for (int i = 1; i < 14; i++)
    {
        pile.a.push_back(Card(i, "Clubs"));
    }

    pile.a = pile.shuffle(&pile.a);

    for (int i = 0; i < 28; i++)
    {
        int who = i % 4;

        switch (who)
        {
        case 0:
            hand.push_back(user.grabFromHand(&pile.a, pile.a.size() - 1));
            break;

        case 1:
            hand1.push_back(a1.grabFromHand(&pile.a, pile.a.size() - 1));
            break;

        case 2:
            hand2.push_back(a2.grabFromHand(&pile.a, pile.a.size() - 1));
            break;

        case 3:
            hand3.push_back(a3.grabFromHand(&pile.a, pile.a.size() - 1));
            break;
        }
    }

    user.removePairs(handptr);

    a1.removePairs(handptr1);

    a2.removePairs(handptr2);

    a3.removePairs(handptr3);

    int ctr = 0;
    int numOut = 0;
    Player *plyarr = new Player[4];
    plyarr[0] = user;
    plyarr[1] = a1;
    plyarr[2] = a2;
    plyarr[3] = a3;
    do
    {

        int whoGoes = ctr % 4;

        switch (whoGoes)
        {
        case 0:
            if (!user.isOut)
            {
                int userChoice;
                int trnctr = 1;
                do
                {
                    cout << "Your hand consists of the following: " << endl;
                    user.showHand(handptr);
                    cout << endl;
                    cout << "Pick the rank(integer(1 for Ace, 11 for Jack, 12 for Queen and 13 for King)) to ask for from the next player: ";
                    cin >> userChoice;
                    if (trnctr == whoGoes)
                        trnctr++;
                    trnctr = trnctr % 4;
                    vector<Card> *select;
                    switch (trnctr)
                    {
                    case 0:
                        select = handptr;
                        break;
                    case 1:
                        select = handptr1;
                        break;
                    case 2:
                        select = handptr2;
                        break;
                    case 3:
                        select = handptr3;
                        break;
                    }
                    if (!plyarr[trnctr].isOut)
                    {
                        if (user.searchHand(userChoice, select) != -1)
                        {
                            hand.push_back(user.grabFromHand(select, user.searchHand(userChoice, select)));
                            if (select->size() == 0)
                            {
                                cout << plyarr[trnctr].get_name() << " has run out of cards in hand!" << endl;
                                plyarr[trnctr].isOut = true;
                                numOut++;
                            }
                            user.removePairs(handptr);
                            cout << "Cool! You got the card you were looking for!" << endl;
                            if (hand.size() == 0)
                            {
                                cout << "Congrats! You have run out of cards in hand!" << endl;
                                user.isOut = true;
                                numOut++;
                                break;
                            }
                        }
                        else
                        {
                            cout << "You must go fish from the draw pile! Picking up now!" << endl;
                            if (pile.a.size() > 0)
                            {
                                Card chosen = pile.a[pile.a.size() - 1];
                                string showIfChange;
                                int dispRank = chosen.get_value();
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
                                hand.push_back(user.grabFromHand(&pile.a, pile.a.size() - 1));
                                cout << "You picked up " << display << " of " << chosen.get_suit() << endl;
                                user.removePairs(handptr);
                                if (hand.size() == 0)
                                {
                                    cout << "Congrats! You have run out of cards in hand!" << endl;
                                    user.isOut = true;
                                    numOut++;
                                }
                            }
                            else
                            {
                                cout << "Sorry! Nothing in draw pile!" << endl;
                            }
                            break;
                        }
                    }
                    trnctr++;
                } while (true);
            }
            break;

        case 1:
            if (!a1.isOut)
            {

                int trnctr1 = 2;
                do
                {
                    int randChoice = rand() % hand1.size();
                    int u1 = hand1[randChoice].get_value();
                    if (trnctr1 == whoGoes)
                        trnctr1++;
                    trnctr1 = trnctr1 % 4;
                    vector<Card> *select1;
                    switch (trnctr1)
                    {
                    case 0:
                        select1 = handptr;
                        break;
                    case 1:
                        select1 = handptr1;
                        break;
                    case 2:
                        select1 = handptr2;
                        break;
                    case 3:
                        select1 = handptr3;
                        break;
                    }
                    if (!plyarr[trnctr1].isOut)
                    {
                        if (user.searchHand(u1, select1) != -1)
                        {
                            hand1.push_back(user.grabFromHand(select1, user.searchHand(u1, select1)));
                            if (select1->size() == 0)
                            {
                                cout << plyarr[trnctr1].get_name() << " has run out of cards in hand!" << endl;
                                plyarr[trnctr1].isOut = true;
                                numOut++;
                            }
                            a1.removePairs(handptr1);
                            cout << "A1 got the card he or she was looking for!" << endl;
                            if (hand1.size() == 0)
                            {
                                cout << "A1 has run out of cards in hand!" << endl;
                                a1.isOut = true;
                                numOut++;
                                break;
                            }
                        }
                        else
                        {
                            cout << "A1 must go fish from the draw pile! Picking up now!" << endl;
                            if (pile.a.size() > 0)
                            {
                                hand1.push_back(a1.grabFromHand(&pile.a, pile.a.size() - 1));
                                cout << "A1 picked up a card from the draw pile!" << endl;
                                a1.removePairs(handptr1);
                                if (hand1.size() == 0)
                                {
                                    cout << "A1 has run out of cards in hand!" << endl;
                                    a1.isOut = true;
                                    numOut++;
                                }
                                break;
                            }
                            else
                            {
                                cout << "Nothing in draw pile!" << endl;
                                break;
                            }
                        }
                    }
                    trnctr1++;
                } while (true);
            }
            break;

        case 2:
            if (!a2.isOut)
            {
                int trnctr2 = 3;
                do
                {
                    int randChoice1 = rand() % hand2.size();
                    int u2 = hand2[randChoice1].get_value();
                    if (trnctr2 == whoGoes)
                        trnctr2++;
                    trnctr2 = trnctr2 % 4;
                    vector<Card> *select2;
                    switch (trnctr2)
                    {
                    case 0:
                        select2 = handptr;
                        break;
                    case 1:
                        select2 = handptr1;
                        break;
                    case 2:
                        select2 = handptr2;
                        break;
                    case 3:
                        select2 = handptr3;
                        break;
                    }
                    if (!plyarr[trnctr2].isOut)
                    {
                        if (user.searchHand(u2, select2) != -1)
                        {
                            hand2.push_back(user.grabFromHand(select2, user.searchHand(u2, select2)));
                            if (select2->size() == 0)
                            {
                                cout << plyarr[trnctr2].get_name() << " has run out of cards in hand!" << endl;
                                plyarr[trnctr2].isOut = true;
                                numOut++;
                            }
                            a2.removePairs(handptr2);
                            cout << "A2 got the card he or she was looking for!" << endl;
                            if (hand2.size() == 0)
                            {
                                cout << "A2 has run out of cards in hand!" << endl;
                                a2.isOut = true;
                                numOut++;
                                break;
                            }
                        }
                        else
                        {
                            cout << "A2 must go fish from the draw pile! Picking up now!" << endl;
                            if (pile.a.size() > 0)
                            {
                                hand2.push_back(a2.grabFromHand(&pile.a, pile.a.size() - 1));
                                cout << "A2 picked up a card from the draw pile!" << endl;
                                a2.removePairs(handptr2);
                                if (hand2.size() == 0)
                                {
                                    cout << "A2 has run out of cards in hand!" << endl;
                                    a2.isOut = true;
                                    numOut++;
                                }
                                break;
                            }
                            else
                            {
                                cout << "Nothing in draw pile!" << endl;
                                break;
                            }
                        }
                    }
                    trnctr2++;
                } while (true);
            }
            break;

        case 3:
            if (!a3.isOut)
            {
                int trnctr3 = 0;
                do
                {
                    int randChoice2 = rand() % hand3.size();
                    int u3 = hand3[randChoice2].get_value();
                    if (trnctr3 == whoGoes)
                        trnctr3++;
                    trnctr3 = trnctr3 % 4;
                    vector<Card> *select3;
                    switch (trnctr3)
                    {
                    case 0:
                        select3 = handptr;
                        break;
                    case 1:
                        select3 = handptr1;
                        break;
                    case 2:
                        select3 = handptr2;
                        break;
                    case 3:
                        select3 = handptr3;
                        break;
                    }
                    if (!plyarr[trnctr3].isOut)
                    {
                        if (user.searchHand(u3, select3) != -1)
                        {
                            hand3.push_back(user.grabFromHand(select3, user.searchHand(u3, select3)));
                            if (select3->size() == 0)
                            {
                                cout << plyarr[trnctr3].get_name() << "has run out of cards in hand!" << endl;
                                plyarr[trnctr3].isOut = true;
                                numOut++;
                            }
                            a3.removePairs(handptr3);
                            cout << "A3 got the card he or she was looking for!" << endl;
                            if (hand3.size() == 0)
                            {
                                cout << "A3 has run out of cards in hand!" << endl;
                                a3.isOut = true;
                                numOut++;
                                break;
                            }
                        }
                        else
                        {
                            cout << "A3 must go fish from the draw pile! Picking up now!" << endl;
                            if (pile.a.size() > 0)
                            {
                                hand3.push_back(a3.grabFromHand(&pile.a, pile.a.size() - 1));
                                cout << "A3 picked up a card from the draw pile" << endl;
                                a3.removePairs(handptr3);
                                if (hand3.size() == 0)
                                {
                                    cout << "A3 has run out of cards in hand!" << endl;
                                    a3.isOut = true;
                                    numOut++;
                                }
                                break;
                            }
                            else
                            {
                                cout << "Nothing in draw pile!" << endl;
                                break;
                            }
                        }
                    }
                    trnctr3++;
                } while (true);
            }
            break;
        }
        ctr++;
    } while (numOut < 3);

    cout << "Game has ended! Here are the final scores for each player: " << endl;

    cout << user.get_name() << ": " << user.get_score() << " points" << endl;

    cout << a1.get_name() << ": " << a1.get_score() << " points" << endl;

    cout << a2.get_name() << ": " << a2.get_score() << " points" << endl;

    cout << a3.get_name() << ": " << a3.get_score() << " points" << endl;
}