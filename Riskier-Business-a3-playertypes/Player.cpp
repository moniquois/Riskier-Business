//
//  Player.cpp
//  Tester101
//
//  Created by Monique Richard on 2017-10-21.
//  Copyright © 2017 Monique Richard. All rights reserved.
//

#include "Player.hpp"

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
//what happens when you can't fortify.. like there is no adjacent country.
//void Player::aggresivefortify(){
//    cout<<"Fortifying stage"<<endl;
//    Country* strongest = theircountries[0];
//
//
//    for(int i=0;i<theircountries.size();i++){
//        if(theircountries[i]->armiesnum()>strongest->armiesnum())
//            strongest = theircountries[i];
//    }
//    for(int i=0;i<strongest->getAdjCountries().size();i++){
//        if(strongest->getAdjCountries()[i]->getPlayer()==this&&strongest->getAdjCountries()[i]->armiesnum()>1){
//            cout<<"Moving armies from " << strongest->getAdjCountries()[i]->get_country_name() << endl;
//            strongest->addarmies((strongest->getAdjCountries()[i]->armiesnum()-1));
//            cout<<strongest->get_country_name()<< " now has "<< strongest->armiesnum()<< " armies." <<endl;
//            break;
//        }
//
//    }
//
//
//}
//could also find way to find the weakest country with also adjacent countries just in case..
//void Player::beneloventfortify(){
//
//    cout<<"Fortifying stage"<<endl;
//    Country* weakest = theircountries[0];
//
//
//    for(int i=0;i<theircountries.size();i++){
//        if(theircountries[i]->armiesnum()<weakest->armiesnum())
//           weakest = theircountries[i];
//    }
//    for(int i=0;i<weakest->getAdjCountries().size();i++){
//        if(weakest->getAdjCountries()[i]->getPlayer()==this&&weakest->getAdjCountries()[i]->armiesnum()>1){
//            cout<<"Moving armies from " << weakest->getAdjCountries()[i]->get_country_name() << endl;
//            weakest->addarmies((weakest->getAdjCountries()[i]->armiesnum()-1));
//            cout<<weakest->get_country_name()<< " now has "<< weakest->armiesnum()<< " armies." <<endl;
//            break;
//        }
//
//    }
//
//
//}
void Player::humandefend(int i){
    int num;
    cout<<"Human Player";
    cout<<"Player " << player_id << " is now defending.. ";
    cout << "Please input the numbers of dice you want to roll (1-" << 2 << ")" << endl;
    cin >> num;
    cout << "user input: " << num << endl;
    
    while (!(1 <= num && num <= 2) && (num <= i)) {
        cout << "Invalid number of dice, Please try again (1-2)" << endl;
        cin >> num;
    }
    
    theirdice->setNumberOfDice(num);
    theirdice->DiceRoll();
    sortdice();
    
}
void Player::computerdefend(int i){
    cout<<"Computer player";
    cout<< "Player " << player_id << " is now defending.."<<endl;
    
    if(i > 1 )
    theirdice->setNumberOfDice(2);
    else
        theirdice->setNumberOfDice(1);
    
    theirdice->DiceRoll();
    sortdice();
}
//aggresive reinforce
//void Player::aggressivereinforce(){
//    cout<<"Reinforcing stage for aggresive player"<<endl;
//    reinforcebonus();
//    armies+=theirhand->computerexchange(); //exchanges as many times as possible.. only for attacker
//    Country* c = theircountries[0];
//    for(int i = 1; i < theircountries.size();i++){
//        if(theircountries[i]->armiesnum()>c->armiesnum())
//            c = theircountries[i];
//    }
//    cout<<"Adding " << armies <<" armies to " << c->get_country_name() <<endl;
//    c->addarmies(armies);
//    armies =0;
//}

//benelovent reinforce
//void Player::beneloventreinforce(){
//    cout<<"reforcing stage for benelovent player" <<endl;
//    reinforcebonus();
//    while(armies>0){
//    Country* c = theircountries[0];
//    for(int i = 1; i < theircountries.size();i++){
//        if(theircountries[i]->armiesnum()< c->armiesnum())
//            c = theircountries[i];
//    }
//    c->incrementArmies();
//    armies--;
//
//    }
//}

//helper method for every kind of player
void Player::reinforcebonus(){
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
    armies+=extraArmiesFromContinentBonus;
    
}

//human reinforce stage
//should probably not be able to go negative haha..
//void Player::reinforce() {
//    cout<<endl;
//    cout<<endl;
//    cout<<"You are in the reinforcing stage."<<endl;
//    reinforcebonus();
//    armies+=theirhand->exchange();
//
//    //need to place armies on the countries.... THIS IS NEW CODE
//    cout<<"Reinforcing armies now!" << endl;
//    cout<<"You have " << armies << " to reinforce with."<<endl;
//    // keep going until the players don't have anymore armies
//    while(armies>0)
//    {
//            cout<<"Enter the index which you would like to add the army to.. " << endl;
//            for (int k= 0 ; k < theircountries.size();k++)
//                cout<< k << " " << theircountries[k]->get_country_name()<<" number of armies is: " <<theircountries[k]->armiesnum() <<endl;
//                int choose;
//                int num;
//            cin>>choose;
//        cout<< "Enter number of armies you wish to add to that country: ";
//        cin>>num;
//            theircountries[choose]->addarmies(num);
//            armies-=num;//remove that armies from the player
//        cout<< theircountries[choose]->get_country_name() << " has " <<theircountries[choose]->armiesnum() << " now. " <<endl;
//        cout<<"You have "<< armies << " left." <<endl;
//
//        }
//
//
//    }
//aggressive attack
//is one army automatically moved when the attacker wins 
//void Player::aggresiveattack(){
//    cout<<"Attacking phase"<<endl;
//    //finds strongest country
//    Country* strongest = theircountries[0];
//    for(int i=1; i<theircountries.size();i++){
//        if(strongest->armiesnum()<theircountries[i]->armiesnum())
//            strongest = theircountries[i];
//    }
//
//    cout<<endl;
//    cout<<strongest->get_country_name() << " chosen to attack!"<<endl;
//    cout << "Starting the ATTACK PHASE with" << strongest->armiesnum() << " armies" << endl;
//    //while strongest army still has armies
//
//
//        for(int i =0; i < strongest->getAdjCountries().size();i++){
//
//            while(strongest->getAdjCountries()[i]->getPlayer()!=this&&strongest->getAdjCountries()[i]->armiesnum()>0&&strongest->armiesnum()>1){
//               //attack things
//
//
//                cout<<"Player "<<strongest->getAdjCountries()[i]->getPlayer()->player_id<< " defending " <<strongest->getAdjCountries()[i]->get_country_name()<<endl;
//                cout << "They have " << strongest->getAdjCountries()[i]->armiesnum() << " armies." << endl;
//
//                    int rounds=0;
//                cout << "You have " << strongest->armiesnum() << " armies" << endl;
//                    if(strongest->armiesnum()>=3){
//                        theirdice->setNumberOfDice(3);
//                         rounds = 3;
//                    }
//                    else{
//                        rounds = 2;
//                        theirdice->setNumberOfDice(2);
//                    }
//                theirdice->DiceRoll();
//                vector<int> DiceOut = theirdice->getdiceoutcome(); //attacking players dice outcome
//                sortdice();
//
//                //defending player
//                    // In this case defend will be called depending on the kind of player.. temp for now
//                    cout<<"Defending Player's turn"<<endl;
//                strongest->getAdjCountries()[i]->getPlayer()->computerdefend(strongest->getAdjCountries()[i]->armiesnum());
//                vector<int> Dicedefend = strongest->getAdjCountries()[i]->getPlayer()->theirdice->getdiceoutcome();
//
//                if (strongest->armiesnum() != 1&&(strongest->getAdjCountries()[i]->armiesnum()!= 0)){
//
//                    for (int j = 0; j < rounds; j++) {
//
//                        if (DiceOut[j] < Dicedefend[j])
//                        {
//                            cout << "Comparing attack:" << DiceOut[j] << "  and defend:" << Dicedefend[j] << endl;
//                            strongest->decrementArmies();//decrementarmies
//                            cout << "Defender win!" << endl;
//
//
//                            cout << "Attacker has " << strongest->armiesnum() << " left" << endl;
//                             cout << "Defender has " << strongest->getAdjCountries()[i]->armiesnum() << " left" << endl;
//                        }
//                        else if (DiceOut[j] > Dicedefend[j])
//                        {
//                            cout << "Comparing attack:" << DiceOut[j] << " and defend:" << Dicedefend[j] << endl;
//                            strongest->getAdjCountries()[i]->decrementArmies();
//                            cout << "Attacker win!" << endl;
//                            cout << "Defender has " << strongest->getAdjCountries()[i]->armiesnum() << " left" << endl;
//                        }
//                        else if (DiceOut[j] == Dicedefend[j])
//                        {
//                            cout << "Comparing attack:" << DiceOut[j] << "and defend:" << Dicedefend[j] << endl;
//                            strongest->decrementArmies();
//
//                            cout << "Defender win!" << endl;
//                            cout << "Attacker has " <<strongest->armiesnum() << " left" << endl;
//                        }
//                        if (strongest->armiesnum() == 1||(strongest->getAdjCountries()[i]->armiesnum()== 0))
//                            break;
//
//                    } //end of for
//                    //may need to add another caution to make sure it can't go below 1..
//
//                    if (strongest->armiesnum() == 1) {
//                        cout << "!Defender won!" << endl; //can no longer attack
//                       // break;
//                    }
//                    else if (strongest->getAdjCountries()[i]->armiesnum()== 0) {
//                        cout << "!Attacker won!" << endl;
//                        strongest->getAdjCountries()[i]->getPlayer()->removeCountry(strongest->getAdjCountries()[i]);
//                        cout << strongest->getAdjCountries()[i]->get_country_name() << " was removed" << endl;
//                        addCountry(strongest->getAdjCountries()[i]);
//                        cout << "Attacker owns " << strongest->getAdjCountries()[i]->get_country_name() <<" now " << endl;
//                        this->theirhand->addCard(mainDeck->Draw());
//                        //break;
//                    }
//
//                }
//                }//end of for
//
//    }//end of while
//
//
//
//    cout<<"Attacking phase done"<<endl;
//}
//
////benelovent attack
//void Player::beneloventattack(){
//   cout<< "No attacking";
//}
//

//human attacker DEFENDER???
//armies shouldn't be able to go under 0 or 1... do a boolean chea
//void Player:: attack() {
//    int mine;
//    int their;
//    int key;
//    bool continueattack = false;
//    bool surrender = false;
//    cout<<"You are in the attack stage."<<endl;
//    cout << "Do you want to attack, press 1 to play and press any key to quit" << endl;
//    cin >> key;
//    if (key!=1)
//        continueattack=true;
//    while(!continueattack ==true ){
//    for (int i = 0; i < theircountries.size(); i++) {
//        cout << i << " -> " << theircountries[i]->get_country_name() << endl;
//        cout << "The number of armies present in this country is " << theircountries[i]->armiesnum()<< "\n" << endl;
//    }
//    cout << "Please choose the country you want to attack from by index: " << endl;
//    cin >> mine;
//
//        while(theircountries[mine]->armiesnum()<2){
//    cout << "You choose " << theircountries[mine]->get_country_name() <<" and their number of armies is " << theircountries[mine]->armiesnum() <<"\n"<< endl;
//            cout<<"However since this has less than 2 armies on it you cannot attack. Please enter new index: "<<endl;
//            cin>>mine;
//        }
//
//    //Choose the country you wish to attack
//
//    for(int i =0; i < theircountries[mine]->getAdjCountries().size();i++){
//        if(theircountries[mine]->getAdjCountries()[i]->getPlayer()!=this){
//            cout<< "Please enter the number corresponding to the country you wish to attack" <<endl;
//            cout<< i << " "<< theircountries[mine]->getAdjCountries()[i]->get_country_name() << " has " <<theircountries[mine]->getAdjCountries()[i]->armiesnum() << " armies and is owned by Player " << theircountries[mine]->getAdjCountries()[i]->getPlayer()->player_id <<endl;
//        }
//    }
//    cin >> their;
//    cout<< "You choose to attack: " << theircountries[mine]->getAdjCountries()[their]->get_country_name() << " has " <<theircountries[mine]->getAdjCountries()[their]->armiesnum() << " number of armies and is owned by Player " << theircountries[mine]->getAdjCountries()[their]->getPlayer()->player_id <<endl;
//
//
//
//    int num;
//    cout << "You have " << theircountries[mine]->armiesnum() << " armies" << endl;
//
//        cout<< "Do you wish to continue attacking? "<<endl;
//        cout<< "Please enter 1 to continue: ";
//        cin >> key;
//        if(key!=1){
//            surrender= true;
//            cout<<"Attacking player has decided to stop attacking this country";
//        }
//
//        while(!surrender==true){
//    // dice can't be more than the amount of armies on the attacking country
//    cout << "Please input the numbers of dice you want to roll (1-" << 3 << ") max being the number of countries you have.." << endl;
//    cin >> num;
//    cout << "user input: " << num << endl;
//
//    while (!((num > 0) && (num <= 3) && (num<=theircountries[mine]->armiesnum()))) {
//        cout << "Invalid number of dice, Please try again (1-" << 3 << ")" << endl;
//        cin >> num;
//        cout << num << endl;
//        if (num == -1)
//            break;
//    }
//    if (num != -1) {
//        theirdice->setNumberOfDice(num);
//        cout << "Dice number " << theirdice->getNumberOfDice() << endl;
//        theirdice->DiceRoll();
//    } //Player gets to roll their dice
//
//    vector<int> DiceOut = theirdice->getdiceoutcome(); //attacking players dice outcome
//            sortdice();
//    //defending player plays?
//    int  DefendArmiesNumber =theircountries[mine]->getAdjCountries()[their]->armiesnum();
//    cout << "DEFENDING PLAYER: You have " << DefendArmiesNumber << " armies" << endl;
//            theircountries[mine]->getAdjCountries()[their]->getPlayer()->computerdefend(DefendArmiesNumber);
//
//    vector<int> Dicedefend =  theircountries[mine]->getAdjCountries()[their]->getPlayer()->theirdice->getdiceoutcome();//defending players dice outcome
//
//
////actually attacking
//    if (!(DiceOut.empty())) {
//
//        for (int i = 0; i < Dicedefend.size(); i++) {
//            if ((theircountries[mine]->armiesnum() == 1)||(theircountries[mine]->getAdjCountries()[their]->armiesnum()<= 0))
//                break;
//            if (DiceOut[i] < Dicedefend[i])
//            {
//                cout << "Comparing attack:" << DiceOut[i] << "  and defend:" << Dicedefend[i] << endl;
//                theircountries[mine]->decrementArmies();//decrementarmies
//                cout << "Defender win!" << endl;
//
//
//                cout << "Attacker has " << theircountries[mine]->armiesnum() << " left" << endl;
//                cout <<"Defender has " <<theircountries[mine]->getAdjCountries()[their]->armiesnum() << " left" <<endl;
//            }
//            else if (DiceOut[i] > Dicedefend[i])
//            {
//                cout << "Comparing attack:" << DiceOut[i] << " and defend:" << Dicedefend[i] << endl;
//                theircountries[mine]->getAdjCountries()[their]->decrementArmies();
//                cout << "Attacker win!" << endl;
//                cout << "Attacker has " << theircountries[mine]->armiesnum() << " left" << endl;
//                cout << "Defender has " << theircountries[mine]->getAdjCountries()[their]->armiesnum() << " left" << endl;
//            }
//            else if (DiceOut[i] == Dicedefend[i])
//            {
//                cout << "Comparing attack:" << DiceOut[i] << "and defend:" << Dicedefend[i] << endl;
//                theircountries[mine]->decrementArmies();
//
//                cout << "Defender win!" << endl;
//                cout << "Attacker has " << theircountries[mine]->armiesnum() << " left" << endl;
//                 cout << "Defender has " << theircountries[mine]->getAdjCountries()[their]->armiesnum() << " left" << endl;
//            }
//        }
//        //may need to add another caution to make sure it can't go below 1..
//        if (theircountries[mine]->armiesnum() == 1) {
//            cout << "!Defender won!" << endl; //can no longer attack
//            cout <<"Player can no longer attack with their country"<<endl;
//            break;
//        }
//        else if (theircountries[mine]->getAdjCountries()[their]->armiesnum()<= 0) {
//            cout << "Attacker won " << theircountries[mine]->getAdjCountries()[their]->get_country_name()<< "!"<<endl;
//            theircountries[mine]->getAdjCountries()[their]->getPlayer()->removeCountry(theircountries[mine]->getAdjCountries()[their]);
//            cout << theircountries[mine]->getAdjCountries()[their]->get_country_name() << " was removed" << endl;
//            addCountry(theircountries[mine]->getAdjCountries()[their]);
//            cout << "Attacker owns " << theircountries[mine]->getAdjCountries()[their]->get_country_name() <<" now " << endl;
//            cout << "You may now move armies from your attacking country onto your new one. Please select an amount enter an amount from 1 to " << theircountries[mine]->armiesnum()-1 << endl;
//            int amount;
//            cout << "user input:" ;
//            cin >> amount;
//            theircountries[mine]->getAdjCountries()[their]->addarmies(amount);
//            this->theirhand->addCard(mainDeck->Draw());
//            break;
//        }
//
//        cout << "You have " << theircountries[mine]->armiesnum() << " armies" << endl;
//        cout<< "Do you wish to continue attacking? "<<endl;
//        cout<< "Please enter 1 to continue: ";
//        cin >> key;
//
//        }
//
//        }
//
//        cout << "Do you want to attack, press 1 to play and press any key to quit" << endl;
//        cin >> key;
//        if (key!=1)
//            continueattack=true;
//    }
//
//
//
//
//}
void Player::sortdice(){
    vector<int> DiceOut = theirdice->getdiceoutcome();
    if (!(DiceOut.empty())) {
        
        cout << "Before soting the values are:" << endl;
        for (int i = 0; i < DiceOut.size(); i++) {
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
            cout << DiceOut[i] << endl;
        }
    }
    
}
//human fortify..
//void Player:: fortify() {
//
//    cout<<"You are in the fortifying stage."<<endl;
//    cout<<"You may now move amries from one of your countries to a neighbours"<<endl;
//
//    for(int i = 0; i < theircountries.size(); i++ )
//        cout << i << " " << theircountries[i]->get_country_name() << " armies: " << theircountries[i]->armiesnum() << endl;
//    cout<<"please enter the index of your source country: ";
//    int source;
//    cin >> source;
//    for(int i = 0; i < theircountries[source]->getAdjCountries().size();i++){
//        if(theircountries[source]->getAdjCountries()[i]->getPlayer()==this)
//            cout << i << theircountries[source]->getAdjCountries()[i]->get_country_name() << " has " <<theircountries[source]->getAdjCountries()[i]->armiesnum() << "armies" <<endl;
//            }
//    int give;
//    int move;
//    cin >> give;
//    cout<<"Please enter the amount of armies you wish to move between 1 - " << (theircountries[source]->armiesnum()-1) <<endl;
//    cin >> move;
//    cout<< "Moving "<< move << " armies from " << theircountries[source]->get_country_name() << " to " <<theircountries[source]->getAdjCountries()[give]->get_country_name()<<endl;
//    theircountries[source]->getAdjCountries()[give]->addarmies(move);
//    theircountries[source]->removearmies(move);
//    //need condition so you can't move what you don't have.. negative numbers..
//
//}

void Player::playerTurn() {
    strategy->reinforce(this);
    strategy->attack(this);
    strategy->fortify(this);
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
