//
//  Start.hpp
//  Tester101
//
//  Created by Monique Richard on 2017-10-21.
//  Copyright © 2017 Monique Richard. All rights reserved.
//

#ifndef Start_hpp
#define Start_hpp
#include "Player.hpp"
#include "Map.hpp"
#include "MapLoader.hpp"
#include "deck.hpp"
#include "Hand.hpp"
#include "Dice.hpp"


#include <stdio.h>
class Start{
public:
    Start();
    ~Start();
    void setMap();
    void createPlayers();
    void startupphase();
    void maingameloop();
private:
    std::vector<Player*> thePlayers;
    MapLoader* mapfile;
    Map* loaded;
    deck* theDeck;
    
};
#endif /* Start_hpp */
