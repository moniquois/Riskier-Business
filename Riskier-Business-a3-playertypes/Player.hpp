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
#include "PlayerType.hpp"

class Map;
class Dice;
class PlayerType;
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
    void aggressivereinforce();// method for aggresive player
    void aggresiveattack();// method for aggresive player
    void aggresivefortify();// method for aggresive player
    void beneloventreinforce(); // reinforces it's weakest country
    void beneloventattack();//method will be empty
    void beneloventfortify();//fortifies weakest country
    void computerdefend(int i);//defending country as a computer
    void humandefend(int i);//user defends country
    void reinforcebonus();//gives you the bonuses for countries&continents NEW CODE
    void sortdice();
    //Need to create a defending helper method depending on the player that is playing..
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
    Dice* gettheirdice(){return theirdice;}
    Hand* gettheirhand(){return theirhand;}
    deck* getDeck(){return mainDeck;}
    void setStrategy(PlayerType* p){strategy =p;}
    PlayerType* getStrategy(){return strategy;}
    void addArmies(int i){armies+=i;}
    
private:
    int player_id;
    int number_of_countries;
    std::vector <Country*> theircountries;
    int armies;
    Hand* theirhand;
    Dice* theirdice;
    deck* mainDeck;
    Map* mainMap;
    PlayerType* strategy;
    
};

#endif /* Player_hpp */
