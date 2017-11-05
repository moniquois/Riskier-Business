//
//  Country.cpp
//  Tester101
//
//  Created by Monique Richard on 2017-09-26.
//  Copyright © 2017 Monique Richard. All rights reserved.
//

#include <stdio.h>
#include "Country.h"
#include "Continent.h"
#include "Player.hpp"
#include <iostream>
#include <vector>
class Continent;

Country::Country() {
    // TODO Auto-generated constructor stub
    owned = false;
    num_of_armies = 0;
  continent = NULL;
    cout<<"New Country Created";
}
Country::Country(string name, Continent* be){
    country_name=name;
    owned = false;
    num_of_armies = 0;
    continent = be;
    cout<< name <<" :New Country Created" << endl;
}

Country::Country(string name){
    country_name= name;
    owned = false;
    num_of_armies = 0;
    continent = NULL;
    cout<< name <<" :New Country Created"<<endl;
    
}

Country::Country(string name, vector<Country*> c, Continent* be){
    country_name = name;
    adj_countries = c;
    continent = be;
    continent->addCountryContained(this);
    cout<<name <<" :New Country Created"<<endl;
}

string Country:: get_country_name(){
    return country_name;
}

void Country:: set_country_name(string name){
    country_name=name;
}

bool Country::is_owned(){
    return owned;
}

void Country::set_owned(bool e){
    owned = e;
}

int Country::armiesnum(){
    return num_of_armies;
}

void Country::set_armies(int num){
    num_of_armies=num;
}

void Country::PrintallAdjCountries(){ //itterates through vector & prints names of Countries
    for(int i=0; i< adj_countries.size() ;i++){
        cout << adj_countries[i]->country_name << endl;    }
}
vector<Country*> Country::getAdjCountries(){
    return adj_countries;
}
void Country::setAdjCOuntries(vector<Country*> d){
    adj_countries = d;
}
void Country::addAdjCountry(Country* c){
    adj_countries.push_back(c);
}

void Country::setContinent(Continent* c){
    continent = c;
}

Continent* Country::getContinent(){
    return continent;
}


Country::~Country() {
    // TODO Auto-generated destructor stub
}
