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
#include "Map.hpp"
#include "MapLoader.hpp"
#include "Start.hpp"
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
//creates all the players!!
    s.createPlayers();
    s.startupphase();
    cout << "entering the main game loop" <<endl;
    s.maingameloop();
    
        }




