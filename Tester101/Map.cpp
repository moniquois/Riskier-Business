//
//  Map.cpp
//  Tester101
//
//  Created by Monique Richard on 2017-10-05.
//  Copyright © 2017 Monique Richard. All rights reserved.
//
#include "Continent.h"
#include "Country.h"
#include "Map.hpp"
#include <iostream>
#include <vector>
#include <queue>

Map::Map(){
     numOfContinents=0;
     numOfCountries=0;
}
//create destructor so that part works
Map::~Map(){
    
}
//creates continent objects
void Map::createContinent(vector<string> continnames, vector<int> bonus){
    for(int i=0; i < continnames.size(); i++){
        continents.push_back(new Continent(continnames[i] ,bonus[i]));
        numOfContinents++;
    }
}

//Have to create Continents first in order for this method to work
void Map::createCountries(vector<string> countrynam, vector<string> continentlist){
    for(int i=0; i < countrynam.size(); i++){
        for(int j=0; j < numOfContinents; j++){
            if(continentlist[i] == continents[j]->get_continent_name()){
                countries.push_back(new Country(countrynam[i], continents[j]));
                continents[j]->addCountryContained(countries[i]);
                numOfCountries++;
                break;
            
            }
                }
   
    }
    
}




void Map::setAdjCountries(vector <vector <string>> adjCount){
    for(int i=0; i < numOfCountries; i++){
        for(int j=0; j< adjCount[i].size();j++){
            
            for(int k=0; k < numOfCountries; k++){
                if(adjCount[i][j]==countries[k]->get_country_name()){
                    countries[i]->addAdjCountry(countries[k]);
                    break;
                }
            }
        }
        
            }
                
            
        }
void Map::PrintAllCountries(){
    for (int i =0; i <numOfCountries; i++){
        cout<< countries[i]->get_country_name() << endl;
        countries[i]->PrintallAdjCountries();
        cout << endl;
    }
}

void Map::PrintAllContinents(){
    for(int i=0; i<numOfContinents;i++)
        cout << continents[i]->get_continent_name();
}
bool Map::connected(){
    vector<Country*> adj;
    queue<Country*> q;
    bool visited[countries.size()];
    for(int i=0;i<numOfCountries;i++){
        visited[i] = 0;
    }
    q.push(countries[0]);
  
    while(!q.empty()){
    Country* c = q.front();
    for(int i=0;i<countries.size();i++){
        if(c->get_country_name()==countries[i]->get_country_name()&&visited[i]==0){
            cout<< "----------->" << c->get_country_name() <<endl;
            visited[i]=1;
            
        }
    }
    adj = c->getAdjCountries();
    for(int i=0;i<adj.size();i++){
        for(int j=0; j<numOfCountries;j++){
            if(adj[i]->get_country_name()==countries[j]->get_country_name()){
                if(visited[j]==0){
                    q.push(adj[i]);
                    
                }
            }
               
            }
    }
    q.pop();
    }
    for(int i = 0; i< numOfCountries;i++){
        if(visited[i]==0)
            return false;
    }
    cout<<"traversed the whole map!"<<endl;
    return true;
}


