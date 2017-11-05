//
//  Country.h
//  Tester101
//
//  Created by Monique Richard on 2017-09-26.
//  Copyright © 2017 Monique Richard. All rights reserved.
//

#ifndef COUNTRY_H_
#define COUNTRY_H_

#include <iostream>//
using namespace std;
#include <vector>
//
class Player;
class Continent;

class Country {
public:
    
    Country();//default constructor
    Country(string name); //constructor that takes COuntry name
    Country(string name, Continent* be); //constructor with country name & pointer to Continent
    Country(string name, vector<Country*> c, Continent* be);//Constructor that takes name, adj countries& pointer of Continent it belongs too
    ~Country(); // default deconstructor
    
    string get_country_name(); //gets name of Country
    void set_country_name(string name); // sets name of Country
    //string get_continent_name(); //Gets Continent name
    //void set_continent_name(); //sets Continent name
    bool is_owned(); //Checks if it is owned by player
    void set_owned(bool e); //Sets Owned
    int armiesnum(); //Gets number of armies on that country
    void set_armies(int num); //Sets number of armies
    void addarmies(int num){num_of_armies+=num;}
    void removearmies(int num){num_of_armies-=num;}
    void PrintallAdjCountries(); //prints adj_countries array
    void setAdjCOuntries(vector<Country*> d);//sets AdjCountries with a vector
    void addAdjCountry(Country* c);
    vector<Country*> getAdjCountries();
    void setContinent(Continent* c); //sets pointer for Continent
    Continent* getContinent(); //Get's pointer to Continent
    void incrementArmies(){num_of_armies++;}//
    void decrementArmies(){num_of_armies--;}
    void setPlayer(Player* any){player = any;}
    Player* getPlayer(){return player;}
    
private:
    string country_name; //Name of Country
    //possibly don't need this?
    bool owned; //Boolean if country is owned by player
    int num_of_armies; //Number of armies on country
    vector<Country*> adj_countries; //Vector containing all Adj Countries
    Continent* continent; //Pointer to the Continent which Country belongs too
    Player* player;
};

#endif /* COUNTRY_H_ */
