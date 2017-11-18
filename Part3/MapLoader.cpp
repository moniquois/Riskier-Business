//
//  MapLoader.cpp
//  Tester101
//
//  Created by Monique Richard on 2017-10-21.
//  Copyright © 2017 Monique Richard. All rights reserved.
//

#include "MapLoader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
using namespace std;
MapLoader::MapLoader(){

}
MapLoader::~MapLoader(){

}

bool MapLoader::is_validExt(string fn){
    //This checks if the file extension is the right one.

    if(fn.substr(fn.find_last_of(".") + 1) == "txt" //checks that it ends with .txt
       || fn.substr(fn.find_last_of(".") + 1) == "map" ) { //checks that it ends with .map
        std::cout << "Yes... This a valid file extension" << std::endl;
        return true;

    } else {
        std::cout << "This is not a valid file extension" << std::endl;
        return false; //terminate
    }
}


bool MapLoader::is_valid(string fn) {
    bool mapcom = false;
    bool terricom = false;
    bool continentscom = false;
    bool value = false;
    string line = "" ;
    ifstream infile;

    infile.open(fn.c_str());
    if( !infile.is_open())
        return false;
    if (!infile.eof())
    {
        while (!infile.eof()){
            getline(infile, line);
            if(line=="[Map]"){
                cout<<"This has MAP component"<<endl;
                mapcom =true;
            }
            if(line=="[Continents]"){
                cout<<"This has CONTINENTS component"<<endl;
                continentscom = true;
            }
            if(line=="[Territories]"){
                cout<<"This has TERRITORIES component"<<endl;
                terricom = true;
            }
        }
         infile.close();
        if (!mapcom||!continentscom||!terricom){
            cout<<"This is not a valid MAP file!"<<endl;
            value=false;
            return false;
        }
        else
            return true;

    }


    return value;
}

//main function
bool MapLoader::createMap(string fn){

    //This checks if the file extension is the right one.


    string line; //holds the line that we are at in the file


    std::vector<string> x;
    std::vector<string> y;
    std::vector<string> adjacent_territories; // temp for the real adj_territories


    std::string temp=" ";
    std::string territory=" ";
    std::string continent=" ";
    std::string corx=" ";
    std::string cory=" ";
    std::string adj_terr=" ";
    std::string bonusvalue = " ";
    fstream infile;

    string filename = fn;


    bool valid = is_valid(fn);
    bool valid2 = is_validExt(fn);

    if(valid2 == true && valid==true){
        infile.open(fn.c_str());
    }
    else{
        return false;
    }


    if (infile.is_open())
    {


        while(!infile.eof())  //while the file isn't empty
        {
            getline (infile,line);
            if(line == "[Continents]"){ //check if one of them is the start of the continents
                cout << "Getting the continents in the map.." << endl;
                if(line == "") { //if line is empty, skip
                    getline(infile,line);
                }
                while(line!="[Territories]"){ //keeps going until territory line
                    getline(infile,line);
                    stringstream str(line);
                    getline(str,temp,'=');
                    getline(str, bonusvalue, '=');

                    if(line == "") { //if line is empty, skip
                        getline(infile,line);
                    }
                    if(line == "[Territories]") {
                        break;
                    }
                    continentnames.push_back(temp);
                    int j=(std::stoi(bonusvalue));
                    bonus.push_back(j);

                }


                //end of continents


            }if(line == "[Territories]") {
                cout << "Getting the countries... " << endl;
                if(line==" ") { //if line is empty, skip
                    getline(infile,temp);
                }
                while (!infile.eof()){
                    getline(infile,line);
                    stringstream str(line);
                    getline(str,territory,',');
                    getline(str,corx,',');
                    getline(str,cory,',');
                    getline(str,continent,',');
                    while(str.good()){
                        getline(str, adj_terr,',');//change to get a vector vector of strings
                        adjacent_territories.push_back(adj_terr);

                    }

                    adj_countries.push_back(adjacent_territories);
                    adjacent_territories.clear();


                    if(line==" ") { //if line is empty, skip
                        getline(infile,temp);
                    }
                    countries.push_back(territory);
                    x.push_back(corx);
                    y.push_back(cory);
                    continentlist.push_back(continent);

                    if(infile.eof()) {
                        break;
                    }

                }



            }

        }
        cout<<endl;
        cout<< "Map has been created"<<endl;
        cout<<endl;
        cout<<endl;
        infile.close();
    }




    else cout << "Unable to open file";

    return true;
}
void MapLoader::printall(){
    cout<< "List of Countries" <<endl;

    for(int i=0; i<countries.size();i++)
        cout<<countries[i] << endl;
    cout<<"List of Countinents" << endl;
    for(int j= 0; j<continentnames.size(); j++)
        cout<< continentnames[j] << "  & bonus value = " << bonus[j] <<endl;
    for(int i=0; i<adj_countries.size();i++){
        for(int j=0;j<adj_countries[i].size();j++)
            cout<< adj_countries[i][j] << " ";
            cout<< endl;
            }
}
