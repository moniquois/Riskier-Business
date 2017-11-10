//
//  PlayerType.hpp
//  Tester101
//
//  Created by Monique Richard on 2017-11-07.
//  Copyright © 2017 Monique Richard. All rights reserved.
//

#ifndef PlayerType_hpp
#define PlayerType_hpp

#include <stdio.h>
#include "Player.hpp"
class PlayerType
{
public:
    
    virtual void reinforce(Player* x) = 0;
    virtual void attack(Player* x) = 0;
    virtual void fortify(Player* x)  = 0;
    
    
protected:
    
private:
};

class AggressivePlayer: public PlayerType
{
    
public:
    AggressivePlayer();
    ~AggressivePlayer();
    void reinforce(Player* x);
    void attack(Player* x);
    void fortify(Player* x);
};

class BenevolantPlayer: public PlayerType
{
    
public:
    BenevolantPlayer();
    ~BenevolantPlayer();
     void reinforce(Player* x);
     void attack(Player* x);
    void fortify(Player* x);
};

class HumanPlayer: public PlayerType
{
    
public:
    HumanPlayer();
    ~HumanPlayer();
     void reinforce(Player* x);
     void attack(Player* x);
     void fortify(Player* x);
};
#endif /* PlayerType_hpp */
