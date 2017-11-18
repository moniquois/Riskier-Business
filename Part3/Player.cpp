//
//  Player.cpp
//  Tester101
//
//  Created by Monique Richard on 2017-10-21.
//  Copyright © 2017 Monique Richard. All rights reserved.
//

#include "Player.h"
#include <iostream>
using namespace std;
Player::Player()
{
    player_id = 0;
    theirdice = new Dice();
    theirhand = new Hand();
    theirhand->setDeck(mainDeck);
    armies = 0;
}

Player::Player(int id) {
    using namespace std;
    cout <<" Player " << id << " created." << endl;
    player_id = id;
    armies=0;
    number_of_countries = 0;
    theirdice = new Dice();
    theirhand = new Hand();

}

void Player::reinforce() {
    cout<<"You are in the reinforcing stage."<<endl;
    if(theircountries.size() > 2)
    armies += theircountries.size()/3;

    //contient control bonus
    vector<int>Counter(mainMap->getContinents().size());//keeps count of similar countries of player and Continent vector, same then increment
    int numberofContinents = mainMap->getNumofCountinents();//number of continents
    int extraArmiesFromContinentBonus = 0;


    //number of countries owned by player

    cout<<"Number of player countries owned: "<<theircountries.size()<<endl;

    cout<<"Now printing the country inventory of player: " << get_player_id() << " \n"<<endl;
    for(int i=0;i<theircountries.size();i++)
        cout<<"\t"<<theircountries[i]->get_country_name()<<endl;
    cout<<"\n||||||||||||||||||||||||||||||||||||||||||||||||||"<<endl;


    for(int i=0; i<numberofContinents; i++)//loops through the continent
    {
        cout<<"\n!Continent currently being evaluated: "<<mainMap->getContinents()[i]->get_continent_name()<<endl;

        for(int j=0; j< mainMap->getContinents()[i]->gets_Countries_Contained().size();j++)//loops through the different countries of said continent
        {

            string currentCountryEvaluation = mainMap->getContinents()[i]->gets_Countries_Contained()[j]->get_country_name();//assigning country we wish to compare to a string variable
            //cout<<"\nCurrent Country being tested from map: "<<currentCountryEvaluation<<endl;

            for(int k=0;k<theircountries.size();k++)//loops through player country vector
            {

                if(currentCountryEvaluation==theircountries[k]->get_country_name())//if values are identical increment counter array at position for certain continents
                {
                    cout<<"Match has been found! "<< theircountries[k]->get_country_name()<<endl;
                    Counter[i]++;

                }

            }

            if(Counter[i]==mainMap->getContinents()[i]->gets_Countries_Contained().size())
            {
                cout<<"\nBonuses are ready at your command, CAPTAIN!"<<endl;

                string continentNameBonus=mainMap->getContinents()[i]->get_continent_name();
                cout<<"A COMPLETE set - Continent targetted: "<<mainMap->getContinents()[i]->get_continent_name()<<endl;




                cout<<"You get: "<<mainMap->getContinents()[i]->getBonus()<<" extra soldiers!";
                extraArmiesFromContinentBonus+=mainMap->getContinents()[i]->getBonus();
                cout<<endl;
            }



        }



    }
    armies+=theirhand->exchange();

    //cout<<"No sets available, no bonus 4 u"<<endl;
    armies+= extraArmiesFromContinentBonus;
}

void Player:: attack() {
    int mine;
    int their;
    int key;
    bool continueattack = false;
    bool surrender = false;
    cout<<"You are in the attack stage."<<endl;


    Notify();//in subject


    cout << "Do you want to attack, press 1 to play and press any key to quit" << endl;
    cin >> key;
    if (key!=1)
        continueattack=true;
    while(!continueattack ==true ){
    for (int i = 0; i < theircountries.size(); i++) {
        cout << i << " -> " << theircountries[i]->get_country_name() << endl;
        cout << "The number of armies present in this country is " << theircountries[i]->armiesnum()<< "\n" << endl;
    }
    cout << "Please choose the country you want to attack from by index: " << endl;
    cin >> mine;
    cout << "You choose " << theircountries[mine]->get_country_name() <<" and their number of armies is " << theircountries[mine]->armiesnum() <<"\n"<< endl;

    //Choose the country you wish to attack

    for(int i =0; i < theircountries[mine]->getAdjCountries().size();i++){
        if(theircountries[mine]->getAdjCountries()[i]->getPlayer()!=this){
            cout<< "Please enter the number corresponding to the country you wish to attack" <<endl;
            cout<< i << " "<< theircountries[mine]->getAdjCountries()[i]->get_country_name() << " has " <<theircountries[mine]->getAdjCountries()[i]->armiesnum() << " armies and is owned by Player " << theircountries[mine]->getAdjCountries()[i]->getPlayer()->player_id <<endl;
        }
    }
    cin >> their;
    cout<< "You choose to attack: " << theircountries[mine]->getAdjCountries()[their]->get_country_name() << " has " <<theircountries[mine]->getAdjCountries()[their]->armiesnum() << " number of armies and is owned by Player " << theircountries[mine]->getAdjCountries()[their]->getPlayer()->player_id <<endl;



    int num;
    cout << "You have " << theircountries[mine]->armiesnum() << " armies" << endl;

        cout<< "Do you wish to continue attacking? "<<endl;
        cout<< "Please enter 1 to continue: ";
        cin >> key;
        if(key!=1){
            surrender= true;
            cout<<"Attacking player has decided to stop attacking this country";
        }

        while(!surrender==true){
    // dice can't be more than the amount of armies on the attacking country
    cout << "Please input the numbers of dice you want to roll (1-" << 3 << ")" << endl;
    cin >> num;
    cout << "user input: " << num << endl;

    while (!((num > 0) && (num <= 3) && (num<=theircountries[mine]->armiesnum()))) {
        cout << "Invalid number of dice, Please try again (1-" << 3 << ")" << endl;
        cin >> num;
        cout << num << endl;
        if (num == -1)
            break;
    }
    if (num != -1) {
        theirdice->setNumberOfDice(num);
        cout << "Dice number " << theirdice->getNumberOfDice() << endl;
        theirdice->DiceRoll();
    } //Player gets to roll their dice

    vector<int> DiceOut = theirdice->getdiceoutcome(); //attacking players dice outcome
    if (!(DiceOut.empty())) {

    cout << "Size: "<<DiceOut.size()<<endl;
        cout << "Before soting the values are:" << endl;
        for (int i = 0; i < DiceOut.size(); i++) {
            if(DiceOut[i] != 0)
            cout << DiceOut[i] << endl;
        }
        cout << "The size is " << DiceOut.size() << endl;
        for (int i = 0; i < DiceOut.size() - 1; i++) {

            for (int j = 0; j < DiceOut.size() - 1; j++) {

                if (DiceOut[j] <= DiceOut[j + 1]) {
                    int temp = DiceOut[j];
                    DiceOut[j] = DiceOut[j + 1];
                    DiceOut[j + 1] = temp;
                }
            }
        }
        cout << "After sorting the values are:" << endl;
        for (int i = 0; i < DiceOut.size(); i++) {
            if(DiceOut[i] != 0)
            cout << DiceOut[i] << endl;
        }
    }



    //defending player plays?
    int  DefendArmiesNumber =theircountries[mine]->getAdjCountries()[their]->armiesnum();
    cout << "DEFENDING PLAYER: You have " << DefendArmiesNumber << " armies" << endl;
    cout << "Please input the numbers of dice you want to roll (1-" << 2 << ")" << endl;
    cin >> num;
    cout << "user input: " << num << endl;

    while (!(1 <= num && num <= 2) || (num > DefendArmiesNumber)) {
        cout << "Invalid number of dice, Please try again (1-2)" << endl;
        cin >> num;
    }

   theircountries[mine]->getAdjCountries()[their]->getPlayer()->theirdice->setNumberOfDice(num);
    theircountries[mine]->getAdjCountries()[their]->getPlayer()->theirdice->DiceRoll();



    vector<int> Dicedefend =  theircountries[mine]->getAdjCountries()[their]->getPlayer()->theirdice->getdiceoutcome();//defending players dice outcome
    if (!(Dicedefend.empty())) {

        cout << "Before soting the values are:" << endl;
        for (int i = 0; i < Dicedefend.size(); i++) {
            if(Dicedefend[i] != 0)
            cout << Dicedefend[i] << endl;
        }
        cout << "The size is " << Dicedefend.size() << endl;
        for (int i = 0; i < Dicedefend.size() - 1; i++) {

            for (int j = 0; j < Dicedefend.size() - 1; j++) {

                if (Dicedefend[j] <= Dicedefend[j + 1]) {
                    int temp = Dicedefend[j];
                    Dicedefend[j] = Dicedefend[j + 1];
                    Dicedefend[j + 1] = temp;
                }
            }
        }
        cout << "After sorting the values are:" << endl;
        for (int i = 0; i < Dicedefend.size(); i++) {
            if(Dicedefend[i] != 0)
            cout << Dicedefend[i] << endl;
        }
    }
//    Dice.clearVector();

//actually attacking
    if (!(DiceOut.empty())) {

        for (int i = 0; i < Dicedefend.size(); i++) {
            if (DiceOut[i] < Dicedefend[i])
            {
                cout << "Comparing attack:" << DiceOut[i] << "  and defend:" << Dicedefend[i] << endl;
                theircountries[mine]->decrementArmies();//decrementarmies
                cout << "Defender win!" << endl;


                cout << "Attacker has " << theircountries[mine]->armiesnum() << " left" << endl;
            }
            else if (DiceOut[i] > Dicedefend[i])
            {
                cout << "Comparing attack:" << DiceOut[i] << " and defend:" << Dicedefend[i] << endl;
                theircountries[mine]->getAdjCountries()[their]->decrementArmies();
                cout << "Attacker win!" << endl;
                cout << "Defender has " << theircountries[mine]->getAdjCountries()[their]->armiesnum() << " left" << endl;
            }
            else if (DiceOut[i] == Dicedefend[i])
            {
                cout << "Comparing attack:" << DiceOut[i] << "and defend:" << Dicedefend[i] << endl;
                theircountries[mine]->decrementArmies();

                cout << "Defender win!" << endl;
                cout << "Attacker has " << theircountries[mine]->armiesnum() << " left" << endl;
            }
        }
        if (theircountries[mine]->armiesnum() == 0) {
            cout << "Defender won" << endl; //add country to players
            cout<< "Country was given to defending player"<<endl;
            theircountries[mine]->getAdjCountries()[their]->getPlayer()->addCountry(theircountries[mine]);
            removeCountry(theircountries[mine]);
            break;
        }
        else if (theircountries[mine]->getAdjCountries()[their]->armiesnum()== 0) {
            cout << "Attacker won" << endl;
            theircountries[mine]->getAdjCountries()[their]->getPlayer()->removeCountry(theircountries[mine]->getAdjCountries()[their]);
            cout << theircountries[mine]->getAdjCountries()[their]->get_country_name() << " was removed" << endl;
            addCountry(theircountries[mine]->getAdjCountries()[their]);
            cout << "Attacker owns " << theircountries[mine]->getAdjCountries()[their]->get_country_name() <<" now " << endl;
            cout << "You may now move armies from your attacking country onto your new one. Please select an amount enter an amount from 1 to " << theircountries[mine]->armiesnum()-1 << endl;
            int amount;
            cout << "user input:" ;
            cin >> amount;
            theircountries[mine]->getAdjCountries()[their]->addarmies(amount);
            break;
        }

        cout << "You have " << theircountries[mine]->armiesnum() << " armies" << endl;
        cout<< "Do you wish to continue attacking? "<<endl;
        cout<< "Please enter 1 to continue: ";
        cin >> key;

        }

        }

        cout << "Do you want to attack, press 1 to play and press any key to quit" << endl;
        cin >> key;
        if (key!=1)
            continueattack=true;
    }
    Notify();




}

void Player:: fortify() {

    cout<<"You are in the fortifying stage."<<endl;
    cout<<"You may now move amries from one of your countries to a neighbours"<<endl;

    for(int i = 0; i < theircountries.size(); i++ )
        cout << i << " " << theircountries[i]->get_country_name() <<endl;
 cout<<"please enter the index of your source country: ";
int source;
cin >> source;
    for(int i = 0; i < theircountries[source]->getAdjCountries().size();i++){
        if(theircountries[source]->getAdjCountries()[i]->getPlayer()==this)
            cout << i << theircountries[source]->getAdjCountries()[i]->get_country_name() << " has " <<theircountries[source]->getAdjCountries()[i]->armiesnum() << armies<<endl;
            }
    int give;
    int move;
    cin >> give;
    cout<<"Please enter the amount of armies you wish to move between 1 - " << (theircountries[source]->armiesnum()-1) <<endl;
    cin >> move;
    cout<< "Moving "<< move << " armies from " << theircountries[source]->get_country_name() << " to " <<theircountries[source]->getAdjCountries()[give]->get_country_name()<<endl;
    theircountries[source]->getAdjCountries()[give]->addarmies(move);
    theircountries[source]->removearmies(move);


}

void Player::playerTurn() {
    reinforce();
    attack();
    fortify();
}

int Player::get_player_id() {
    return player_id;
}

void Player::addCountry(Country* c){
    theircountries.push_back(c);
    c->setPlayer(this);
    number_of_countries ++;
}
void Player::setDeck(deck *d){
    mainDeck = d;
}
void Player::setDice(Dice *d){
    theirdice = d;
}
void Player::setHand(Hand *h){
    theirhand = h;
}

void Player::removeCountry(Country* country) {
    //An arbitrary value to be used to indicate whether the country was found in the player's countries_owned vector.
    int index = -1;

    int countries_owned = theircountries.size();
    for(int i=0; i<countries_owned; i++) {
        if(theircountries.at(i) == country) {
            index = i;
        }
    }
    if(index == -1) {
        std::cout << "You do not own that country" << std::endl;
    }
    //remove country
    else {
        theircountries.erase(theircountries.begin()+index);
        number_of_countries--;
        std::cout << "Country was erased." << std::endl;

    }
}
