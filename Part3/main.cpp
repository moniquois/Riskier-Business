//
//  main.cpp
//  Tester101
//
//  Created by Monique Richard on 2017-09-26.
//  Copyright © 2017 Monique Richard. All rights reserved.
//

#include <iostream>
#include "Country.h"
#include "Continent.h"
#include "Map.h"
#include "MapLoader.h"
#include "Start.h"
#include "WorldDomObserver.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
class Map;
#include <vector>

int main() {

//creates objects
    Start s;

//creates map
    s.setMap();
    int blah = s.getLoaded()->getNumofCountries();

//creates all the players!!

    s.createPlayers();


    s.startupphase();
     for(int i=0;i<s.getPlayerVector().size();i++)
    {
        cout<<"\n no "<<i+1<< "Players Y'all"<<s.getPlayerVector()[i]->get_number_of_countries();

        cout<<"///////////////////////\nmankey\n//////////////////"<<endl;
    }



   WorldDomObserver *impObserverP1 = new WorldDomObserver(s.getPlayerVector()[0],blah);
    WorldDomObserver *impObserverP2 = new WorldDomObserver(s.getPlayerVector()[1], blah);


    cout<<"@@@@@@@What is going on size of player country vector: "<<s.getPlayerVector()[0]->get_number_of_countries()<<endl;

    cout<<"SOBAAAAAAAAA"<<s.getLoaded()->getNumofCountries()<<endl;



    cout << "entering the main game loop" <<endl;
    s.maingameloop();

        }




