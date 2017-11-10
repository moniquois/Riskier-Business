//
//  Dice.cpp
//  Tester101
//
//  Created by Monique Richard on 2017-10-21.
//  Copyright © 2017 Monique Richard. All rights reserved.
//

#include "Dice.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

//constructor
Dice::Dice()
{
    numberOfDice = 0;
}
//setters
void Dice::setNumberOfDice(int x)
{
    numberOfDice=x;
}
//getters
int Dice::getNumberOfDice()
{
    return numberOfDice;
}

int Dice::DiceRoll()
{
    //increment the number of turns the player played
    turns++;
    //loop through the number of dice the user want to roll to generate the amount of random numbers the player want
    for (int i = 0; i < getNumberOfDice(); i++)
    {
        //generate random numbers
        int random = rand() % 6 + 1;
        cout << "player rolled a  " << random << endl;
        cout << endl;
        //storing the random number generated into an array which will overwrite itself everytime a new dice object is created
        DiceOutcome[i]=random;
        //dice counter, keep track the number of dice rolled
        DiceCount++;
    }

    
    return 0;
}

//storing the number of 1-6 rolled in an array
void Dice::store()
{
    //looping through the amount the user input, check the random number generated and increment each corresponding array
    for(int i=0;i<getNumberOfDice();i++)
    {
        //switch statement to check through the outcome of dice rolled
        switch(DiceOutcome[i])
        {
                //increment array at index 0 if outcome of dice is 1
            case 1:
                DiceNumber[0]++;
                break;
                //increment array at index 1 if outcome of dice is 2
            case 2:
                DiceNumber[1]++;
                break;
                //increment array at index 2 if outcome of dice is 3
            case 3:
                DiceNumber[2]++;
                break;
                //increment array at index 3 if outcome of dice is 4
            case 4:
                DiceNumber[3]++;
                break;
                //increment array at index 4 if outcome of dice is 5
            case 5:
                DiceNumber[4]++;
                break;
                //increment array at index 5 if outcome of dice is 6
            case 6:
                DiceNumber[5]++;
                break;
        }
    }
    //printing numbers of times rolled
    cout << "The amount of one rolled is: " << DiceNumber[0] << endl;
    cout << "The amount of two rolled is: " << DiceNumber[1] << endl;
    cout << "The amount of three rolled is: " << DiceNumber[2] << endl;
    cout << "The amount of four rolled is: " << DiceNumber[3] << endl;
    cout << "The amount of five rolled is: " << DiceNumber[4] << endl;
    cout << "The amount of six rolled is: " << DiceNumber[5] << endl;
    
    
}

//Calculating the percentage
void Dice::Percent()
{
    cout << "===================================================="<<endl;
    for(int i = 0; i<6;i++)
    {
        cout.setf(ios::fixed);
        cout.setf(ios::showpoint);
        cout.precision(2);
        
        double percentage = (double) DiceNumber[i]/DiceCount* 100;
        
        cout <<"The percentage of "<<(i+1)<<" being rolled is: "<<percentage<<" %"<<endl;
    }
    cout << "====================End of turn=====================" << endl;
}
