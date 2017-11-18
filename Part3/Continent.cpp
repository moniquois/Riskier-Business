//
//  Continent.cpp
//  Tester101
//
//  Created by Monique Richard on 2017-09-26.
//  Copyright © 2017 Monique Richard. All rights reserved.
//

#include <stdio.h>
#include "Continent.h"
#include <iostream>



Continent::Continent() {
    // TODO Auto-generated constructor stub
    continent_name ="";
    std::cout <<"Continent created" <<endl;
}
Continent::~Continent(){
  
}
Continent::Continent(string name, int bon){
    continent_name = name;
    bonus = bon;
    std::cout <<"Continent created: " << name <<endl;
}

Continent::Continent(string name){
    continent_name = name;
    std::cout <<"Continent created: " << name <<endl;
}
Continent::Continent(string name, vector<Country*> contain){
    continent_name = name;
    allCountriesContained = contain;
  std::cout <<"Continent created " << name << endl;
}
string Continent::get_continent_name(){
    return continent_name;
}

void Continent::set_Countries_Contained(vector<Country*> countr){
    for (int i=0;i<countr.size();i++){
        allCountriesContained[i] = countr[i];
    }
}

//Goes through vector & prints all the countries 
void Continent::print_allContinentCountries(){
    for (int i = 0; i< allCountriesContained.size();i++){
        cout << allCountriesContained[i]->get_country_name() << endl;
    }
  
}
void Continent::addCountryContained(Country* c){
    allCountriesContained.push_back(c);
}
vector<Country*> Continent::gets_Countries_Contained(){
    return allCountriesContained;
}


