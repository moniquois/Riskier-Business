//
//  Map.hpp
//  Tester101
//
//  Created by Monique Richard on 2017-10-05.
//  Copyright © 2017 Monique Richard. All rights reserved.
//

#ifndef Map_hpp
#define Map_hpp
#include <iostream>
using namespace std;
#include <vector>
#include <stdio.h>
class Continent;
class Country;

class Map{
public:
    Map();
    ~Map();
    void createContinent(vector<string> continnames, vector<int> idnums);
    void createCountries(vector<string> countrynam, vector<string> continentlist);
    void setAdjCountries(vector <vector <string>> adjCount);
    void PrintAllCountries();
    void PrintAllContinents();

    bool connected();
    int getNumofCountries(){return countries.size();}
    int getNumofCountinents(){return numOfContinents;}
    std::vector<Country*> getCountries(){return countries;}
    std::vector<Continent*> getContinents(){return continents;}


private:
    vector<Country*> countries;
    vector<Continent*> continents;
    int numOfContinents;
    int numOfCountries;

};
#endif /* Map_hpp */
