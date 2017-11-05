//
//  Continent.h
//  Tester101
//
//  Created by Monique Richard on 2017-09-26.
//  Copyright © 2017 Monique Richard. All rights reserved.
//

#ifndef CONTINENT_H_
#define CONTINENT_H_

#include "Country.h"
#include <iostream>
using namespace std;

class Continent {
public:
    Continent(); //default Constructor
    Continent(string name); //Constructor that takes name of Continent
    Continent(string name,  int bon);
    Continent(string name, vector<Country*> contain);
    ~Continent(); // deconstructor
    string get_continent_name();//Gets Continent name
    void set_continent_name(); //sets continent name
  
    void set_Countries_Contained(vector<Country*> all); //Sets Countries Contained
    void print_allContinentCountries(); //prints all COntained Countries
    vector<Country*> gets_Countries_Contained();//Gets vector of Countries Contained
    void addCountryContained(Country* c);
    int getBonus(){return bonus;}
    
private:
    string continent_name; //Name of Continent Object
    vector<Country*> allCountriesContained; //Vector with all Countries contained in Continent
    int bonus;
};

#endif /* CONTINENT_H_ */
