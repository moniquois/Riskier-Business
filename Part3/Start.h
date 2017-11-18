//
//  Start.hpp
//  Tester101
//
//  Created by Monique Richard on 2017-10-21.
//  Copyright © 2017 Monique Richard. All rights reserved.
//

#ifndef Start_hpp
#define Start_hpp
#include "Player.h"
#include "Map.h"
#include "MapLoader.h"
#include "deck.h"
#include "Hand.h"
#include "Dice.h"


#include <stdio.h>
class Start{
public:
    Start();
    ~Start();
    void setMap();
    void createPlayers();
    void startupphase();
    void maingameloop();
    vector<Player*> getPlayerVector();
    int getNoPlayer(){return play;};
    Map* getLoaded(){return loaded;};
    Map* getMap(){return loaded;};
private:
    std::vector<Player*> thePlayers;//of type concrete subject
    MapLoader* mapfile;
    Map* loaded;
    deck* theDeck;
    int play;

};
#endif /* Start_hpp */
