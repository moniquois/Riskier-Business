//
//  Player.hpp
//  Tester101
//
//  Created by Monique Richard on 2017-10-21.
//  Copyright © 2017 Monique Richard. All rights reserved.
//

#ifndef Player_h
#define Player_h
#include "Dice.h"
#include "deck.h"
#include "Hand.h"
#include "Country.h"
#include "Continent.h"
#include "Map.h"
#include "Subject.h"


class Map;
class Dice;

#include <stdio.h>
class Player: public Subject
{
public:
    Player();
    Player(int);
    std::vector <Country*> getCountries() { return theircountries; }
    int get_player_id();
    void reinforce();
    void attack();
    void fortify();

    void playerTurn();
    void addCountry(Country* c);
    int get_number_of_countries() {return number_of_countries; }
    void setDeck(deck* d);
    void setHand(Hand* h);
    void setDice(Dice* d);
    void setArmies(int a){ armies = a;}
    void decreaseArmies(){armies--;}
    int getArmies(){ return armies;}
    void removeCountry(Country* country);
    void setMap(Map* m){mainMap = m;}

private:
    int player_id;
    int number_of_countries;
    std::vector <Country*> theircountries;
    int armies;
    Hand* theirhand;
    Dice* theirdice;
    deck* mainDeck;
    Map* mainMap;
};

#endif /* Player_hpp */
