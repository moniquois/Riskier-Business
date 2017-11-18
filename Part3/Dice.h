//
//  Dice.hpp
//  Tester101
//
//  Created by Monique Richard on 2017-10-21.
//  Copyright © 2017 Monique Richard. All rights reserved.
//

#ifndef Dice_hpp
#define Dice_hpp

#include <stdio.h>
#include <vector>
#pragma once

class Dice
{
public:
    Dice();

    int getNumberOfDice();
    void setNumberOfDice(int x);
    std::vector<int> getdiceoutcome(){return DiceOutcome;};
    int DiceRoll();
    void store();
    void Percent();
    void clearVector();

protected:
private:
    int x;
    int numberOfDice;
    int DiceCount;
    int turns;
    int DiceNumber[6]={0,0,0,0,0,0};
    std::vector<int> DiceOutcome;
};

#endif /* Dice_hpp */
