//
//  Player.cpp
//  Tester101
//
//  Created by Monique Richard on 2017-10-21.
//  Copyright © 2017 Monique Richard. All rights reserved.
//

#include "Player.hpp"

#include <iostream>
using namespace std;
Player::Player()
{
    player_id = 0;
    theirdice = new Dice();
    theirhand = new Hand();
    theirhand->setDeck(mainDeck);
    armies = 0;
}

Player::Player(int id) {
    using namespace std;
    cout <<" Player " << id << " created." << endl;
    player_id = id;
    armies=0;
    number_of_countries = 0;
    theirdice = new Dice();
    theirhand = new Hand();
    
}
//player chooses how many dice it wants to roll
void Player::humandefend(int i){
    int num;
    cout<<"Human Player";
    cout<<"Player " << player_id << " is now defending.. ";
    cout << "Please input the numbers of dice you want to roll (1-" << 2 << ")" << endl;
    cin >> num;
    cout << "user input: " << num << endl;
    
    while (!(1 <= num && num <= 2) && (num <= i)) {
        cout << "Invalid number of dice, Please try again (1-2)" << endl;
        cin >> num;
    }
    
    theirdice->setNumberOfDice(num);
    theirdice->DiceRoll();
    sortdice();
    
}

//automatically defends
void Player::computerdefend(int i){

    cout<< "Player " << player_id << " is now defending.."<<endl;
    
    if(i > 1 )
    theirdice->setNumberOfDice(2);
    else
        theirdice->setNumberOfDice(1);
    
    theirdice->DiceRoll();
    sortdice();
}


//helper method for every kind of player
void Player::reinforcebonus(){
    if(theircountries.size() > 2)
        armies += theircountries.size()/3;
    
    //contient control bonus
    vector<int>Counter(mainMap->getContinents().size());//keeps count of similar countries of player and Continent vector, same then increment
    int numberofContinents = mainMap->getNumofCountinents();//number of continents
    int extraArmiesFromContinentBonus = 0;
    
    
    //number of countries owned by player
    cout<<"Number of player countries owned: "<<theircountries.size()<<endl;
    
    cout<<"Now printing the country inventory of player: " << get_player_id() << " \n"<<endl;
    for(int i=0;i<theircountries.size();i++)
        cout<<"\t"<<theircountries[i]->get_country_name()<<endl;
    cout<<"\n||||||||||||||||||||||||||||||||||||||||||||||||||"<<endl;
    
    
    for(int i=0; i<numberofContinents; i++)//loops through the continent
    {
        cout<<"\n!Continent currently being evaluated: "<<mainMap->getContinents()[i]->get_continent_name()<<endl;
        
        for(int j=0; j< mainMap->getContinents()[i]->gets_Countries_Contained().size();j++)//loops through the different countries of said continent
        {
            
            string currentCountryEvaluation = mainMap->getContinents()[i]->gets_Countries_Contained()[j]->get_country_name();//assigning country we wish to compare to a string variable
            //cout<<"\nCurrent Country being tested from map: "<<currentCountryEvaluation<<endl;
            
            for(int k=0;k<theircountries.size();k++)//loops through player country vector
            {
                
                if(currentCountryEvaluation==theircountries[k]->get_country_name())//if values are identical increment counter array at position for certain continents
                {
                    cout<<"Match has been found! "<< theircountries[k]->get_country_name()<<endl;
                    Counter[i]++;
                    
                }
                
            }
            
            if(Counter[i]==mainMap->getContinents()[i]->gets_Countries_Contained().size())
            {
                cout<<"\nBonuses are ready at your command, CAPTAIN!"<<endl;
                
                string continentNameBonus=mainMap->getContinents()[i]->get_continent_name();
                cout<<"A COMPLETE set - Continent targetted: "<<mainMap->getContinents()[i]->get_continent_name()<<endl;
                
                
                
                
                cout<<"You get: "<<mainMap->getContinents()[i]->getBonus()<<" extra soldiers!";
                extraArmiesFromContinentBonus+=mainMap->getContinents()[i]->getBonus();
                cout<<endl;
            }
            
        }
        
        
        
    }
    armies+=extraArmiesFromContinentBonus;
    
}


void Player::sortdice(){
    vector<int> DiceOut = theirdice->getdiceoutcome();
    if (!(DiceOut.empty())) {
        
        cout << "Before sorting the values are:" << endl;
        for (int i = 0; i < DiceOut.size(); i++) {
            cout << DiceOut[i] << endl;
        }
        cout << "The size is " << DiceOut.size() << endl;
        for (int i = 0; i < DiceOut.size() - 1; i++) {
            
            for (int j = 0; j < DiceOut.size() - 1; j++) {
                
                if (DiceOut[j] <= DiceOut[j + 1]) {
                    int temp = DiceOut[j];
                    DiceOut[j] = DiceOut[j + 1];
                    DiceOut[j + 1] = temp;
                }
            }
        }
        cout << "After sorting the values are:" << endl;
        for (int i = 0; i < DiceOut.size(); i++) {
            cout << DiceOut[i] << endl;
        }
    }
    
}


void Player::playerTurn() {
    cout<<"------------------------------------------------"<<endl;
    cout<<"STARTING PLAYER "<< get_player_id() <<"'s TURN" <<endl;
    cout<<"------------------------------------------------"<<endl;
    strategy->reinforce(this);
    strategy->attack(this);
    strategy->fortify(this);
}

int Player::get_player_id() {
    return player_id;
}

void Player::addCountry(Country* c){
    theircountries.push_back(c);
    c->setPlayer(this);
    number_of_countries ++;
}
void Player::setDeck(deck *d){
    mainDeck = d;
    gettheirhand()->setDeck(mainDeck);
}
void Player::setDice(Dice *d){
    theirdice = d;
}
void Player::setHand(Hand *h){
    theirhand = h;
}

void Player::removeCountry(Country* country) {
    //An arbitrary value to be used to indicate whether the country was found in the player's countries_owned vector.
    int index = -1;
    
    int countries_owned = theircountries.size();
    for(int i=0; i<countries_owned; i++) {
        if(theircountries.at(i) == country) {
            index = i;
        }
    }
    if(index == -1) {
        std::cout << "You do not own that country" << std::endl;
    }
    //remove country
    else {
        theircountries.erase(theircountries.begin()+index);
        number_of_countries--;
     //   std::cout << "Country was erased." << std::endl;
        
    }
}
