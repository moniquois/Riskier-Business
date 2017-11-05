//
//  Player.hpp
//  Tester101
//
//  Created by Monique Richard on 2017-10-21.
//  Copyright © 2017 Monique Richard. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp
#include "Dice.hpp"
#include "deck.hpp"
#include "Hand.hpp"
#include "Country.h"
#include "Continent.h"
#include "Map.hpp"

class Map;
class Dice;

#include <stdio.h>
class Player
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
