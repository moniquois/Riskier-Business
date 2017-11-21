//
//  PlayerType.cpp
//  Tester101
//
//  Created by Monique Richard on 2017-11-07.
//  Copyright © 2017 Monique Richard. All rights reserved.
//

#include "PlayerType.hpp"
#include "Player.hpp"
#include "Dice.hpp"
#include "deck.hpp"
#include "Hand.hpp"
#include <stdlib.h>
using namespace std;


//Aggressive Player
AggressivePlayer::AggressivePlayer(){
    
}
AggressivePlayer::~AggressivePlayer(){
    
}
void AggressivePlayer::reinforce(Player* x)
{
    std:: cout<<"-------------"<< "Player " << x->get_player_id()<<"-------------"<<endl;
    std:: cout << "Reinforcing for aggressive player" << endl;
   
    x->reinforcebonus();
    x->addArmies(x->gettheirhand()->computerexchange());
 //   x->addArmies(x->gettheirhand()->computerexchange()); //exchanges as many times as possible.. only for attacker
    Country* c =new Country();
    //x->getCountries()[x->getCountries().size()-1];
    for(int i=0;i<x->getCountries().size();i++){
        for(int j =0;j<x->getCountries()[i]->getAdjCountries().size();j++){
            if(x->getCountries()[i]->getAdjCountries()[j]->getPlayer()!=x){//was causing error
                if(x->getCountries()[i]->armiesnum()>c->armiesnum()){
                    c = x->getCountries()[i];
                    break;
                }
            }
        }
    }
    cout<<"Adding " << x->getArmies() <<" armies to " << c->get_country_name() <<endl;
    c->addarmies(x->getArmies());
    x->setArmies(0);
}

void AggressivePlayer::attack(Player* x)
{
    std:: cout<<"-------------"<< "Player " << x->get_player_id()<<"-------------"<<endl;
    std:: cout << "Attacking for aggressive player" << endl;
    //finds strongest country[0];
    
    Country* strongest =new Country();
    //x->getCountries()
    for(int i=0; i<x->getCountries().size();i++){
        for(int j=0;j<x->getCountries()[i]->getAdjCountries().size();j++){
            if(x->getCountries()[i]->getAdjCountries()[j]->getPlayer()!=x){
                if(strongest->armiesnum()<x->getCountries()[i]->armiesnum()){
                    strongest = x->getCountries()[i];
                    break;
                }
    }
    }
    }
    cout<<endl;
    cout<<strongest->get_country_name() << " chosen to attack!"<<endl;
    cout << "Starting the ATTACK PHASE with "  << strongest->armiesnum() << " armies" << endl;
    //while strongest army still has armies
    
    
    for(int i =0; i < strongest->getAdjCountries().size();i++){
        
        while(strongest->getAdjCountries()[i]->getPlayer()!=strongest->getPlayer()&&strongest->getAdjCountries()[i]->armiesnum()>0&&strongest->armiesnum()>1){
            //attack things
            
            
            cout<<"Player "<<strongest->getAdjCountries()[i]->getPlayer()->get_player_id()<< " defending " <<strongest->getAdjCountries()[i]->get_country_name()<<endl;
            cout << "Defender has " << strongest->getAdjCountries()[i]->armiesnum() << " armies." << endl;
            
            int rounds=0;
            cout << "Attacker has " << strongest->armiesnum() << " armies" << endl;
            if(strongest->armiesnum()>=3){
                x->gettheirdice()->setNumberOfDice(3);
                rounds = 3;
            }
            else{
                rounds = 2;
                x->gettheirdice()->setNumberOfDice(2);
            }
            x->gettheirdice()->DiceRoll();
            vector<int> DiceOut = x->gettheirdice()->getdiceoutcome(); //attacking players dice outcome
            x->sortdice();
            
            //defending player
            // In this case defend will be called depending on the kind of player.. temp for now
            cout<<"Defending Player's turn"<<endl;
            strongest->getAdjCountries()[i]->getPlayer()->computerdefend(strongest->getAdjCountries()[i]->armiesnum());
            vector<int> Dicedefend = strongest->getAdjCountries()[i]->getPlayer()->gettheirdice()->getdiceoutcome();
            
            if (strongest->armiesnum() != 1&&(strongest->getAdjCountries()[i]->armiesnum()!= 0)){
                
                for (int j = 0; j < rounds; j++) {
                    
                    if (DiceOut[j] < Dicedefend[j])
                    {
                        cout << "Comparing attack:" << DiceOut[j] << "  and defend:" << Dicedefend[j] << endl;
                        strongest->decrementArmies();//decrementarmies
                        cout << "Defender win!" << endl;
                        
                        
                        cout << "Attacker has " << strongest->armiesnum() << " left" << endl;
                        cout << "Defender has " << strongest->getAdjCountries()[i]->armiesnum() << " left" << endl;
                    }
                    else if (DiceOut[j] > Dicedefend[j])
                    {
                        cout << "Comparing attack:" << DiceOut[j] << " and defend:" << Dicedefend[j] << endl;
                        strongest->getAdjCountries()[i]->decrementArmies();
                        cout << "Attacker win!" << endl;
                        cout << "Defender has " << strongest->getAdjCountries()[i]->armiesnum() << " left" << endl;
                    }
                    else if (DiceOut[j] == Dicedefend[j])
                    {
                        cout << "Comparing attack:" << DiceOut[j] << "and defend:" << Dicedefend[j] << endl;
                        strongest->decrementArmies();
                        
                        cout << "Defender win!" << endl;
                        cout << "Attacker has " <<strongest->armiesnum() << " left" << endl;
                    }
                    if (strongest->armiesnum() == 1||(strongest->getAdjCountries()[i]->armiesnum()== 0))
                        break;
                    
                } //end of for
                //clears dice vector
                x->cleardice();
                strongest->getAdjCountries()[i]->getPlayer()->cleardice();
                
                
                if (strongest->armiesnum() == 1) {
                    cout << "!Defender won!" << endl; //can no longer attack
                    // break;
                }
                else if (strongest->getAdjCountries()[i]->armiesnum()== 0) {
                    cout << "!Attacker won!" << endl;
                    strongest->getAdjCountries()[i]->addarmies(1);
                    strongest->decrementArmies();
                    strongest->getAdjCountries()[i]->getPlayer()->removeCountry(strongest->getAdjCountries()[i]);
                    cout << strongest->getAdjCountries()[i]->get_country_name() << " was removed" << endl;
                    strongest->getAdjCountries()[i]->setPlayer(x);
                   x->addCountry(strongest->getAdjCountries()[i]);
                   
                    cout << "Attacker owns " << strongest->getAdjCountries()[i]->get_country_name() <<" now " << endl;
                    if(x->getDeck()->getCardNo()>1){
                    x->gettheirhand()->addCard(x->getDeck()->Draw());
                    }
                    //break;
                }
                
            }
        }//end of for
        
    }//end of while
    
    
    cout<<"--------------------------------------"<<endl;
    cout<<"Attacking phase done"<<endl;
     cout<<"--------------------------------------"<<endl;
}

void AggressivePlayer::fortify(Player* x)
{
    std:: cout<<"-------------"<< "Player " << x->get_player_id()<<"-------------"<<endl;
    std:: cout << "Fortifying for aggressive player" << endl;

    Country* strongest =new Country(); //temp country

    
    
    for(int i=0;i<x->getCountries().size();i++){
        for(int j =0;j<x->getCountries()[i]->getAdjCountries().size();j++){
            if(x->getCountries()[i]->getAdjCountries()[j]->getPlayer()!=x){
                if(x->getCountries()[i]->armiesnum()>strongest->armiesnum()){
                    strongest = x->getCountries()[i];
                break;
                }
            }
        }
    }
    
    for(int i=0;i<strongest->getAdjCountries().size();i++){
        if(strongest->getAdjCountries()[i]->getPlayer()==x&&strongest->getAdjCountries()[i]->armiesnum()>1){
            cout<<"Moving armies from " << strongest->getAdjCountries()[i]->get_country_name() << endl;
            strongest->addarmies((strongest->getAdjCountries()[i]->armiesnum()-1));
            cout<<strongest->get_country_name()<< " now has "<< strongest->armiesnum()<< " armies." <<endl;
            break;
        }
        
    }
    
}
BenevolantPlayer::BenevolantPlayer(){
    
}
BenevolantPlayer::~BenevolantPlayer(){
    
}
//Benevolant Player
void BenevolantPlayer::reinforce(Player* x)
{
    std:: cout<<"-------------"<< "Player " << x->get_player_id()<<"-------------"<<endl;
    std:: cout << "Reinforcing for Benelovant player" << endl;

    x->reinforcebonus();
    while(x->getArmies()>0){
        Country* c = x->getCountries()[0];
        for(int i = 1; i < x->getCountries().size();i++){
            if(x->getCountries()[i]->armiesnum()< c->armiesnum())
                c = x->getCountries()[i];
        }
        cout<<"Increasing armies in " << c->get_country_name()<<endl;
        c->incrementArmies();
        x->decreaseArmies();
        
    }
}

void BenevolantPlayer::attack(Player* x)
{
 std:: cout<<"-------------"<< "Player " << x->get_player_id()<<"-------------"<<endl;
    std:: cout << "Player chooses not to attack"<< endl;
}

void BenevolantPlayer::fortify(Player* x)
{
    std:: cout<<"-------------"<< "Player " << x->get_player_id()<<"-------------"<<endl;
    std:: cout << "Fortifying for benevolant player" << endl;
    
    Country* weakest = x->getCountries()[0];
    
    
    for(int i=0;i<x->getCountries().size();i++){
        for(int j=0;j<x->getCountries()[i]->getAdjCountries().size();j++)
            if(x->getCountries()[i]->getAdjCountries()[j]->armiesnum()>1){
                if(x->getCountries()[i]->armiesnum()<weakest->armiesnum()){
                    weakest = x->getCountries()[i];
                break;
                }
            }
    }
    for(int i=0;i<weakest->getAdjCountries().size();i++){
        if(weakest->getAdjCountries()[i]->getPlayer()==x&&weakest->getAdjCountries()[i]->armiesnum()>1){
            cout<<"Moving armies from " << weakest->getAdjCountries()[i]->get_country_name() << endl;
            weakest->incrementArmies();
            weakest->getAdjCountries()[i]->decrementArmies();
            cout<<weakest->get_country_name()<< " now has "<< weakest->armiesnum()<< " armies." <<endl;
            break;
        }
        
    }
    
}
HumanPlayer::HumanPlayer() {
    
}
HumanPlayer::~HumanPlayer(){
    
}
//Human Player
void HumanPlayer::reinforce(Player* x)
{
    cout<<endl;
    cout<<endl;
    std:: cout<<"-------------"<< "Player " << x->get_player_id()<<"-------------"<<endl;
    cout<<"You are in the reinforcing stage."<<endl;
    x->reinforcebonus();
  // x->addArmies(x->gettheirhand()->exchange());
    
    //need to place armies on the countries.... THIS IS NEW CODE
    cout<<"Reinforcing armies now!" << endl;
    cout<<"You have " << x->getArmies() << " to reinforce with."<<endl;
    // keep going until the players don't have anymore armies
    while(x->getArmies()>0)
    {
        cout<<"Enter the index which you would like to add the army to.. " << endl;
        for (int k= 0 ; k < x->getCountries().size();k++)
            cout<< k << " " << x->getCountries()[k]->get_country_name()<<" number of armies is: " <<x->getCountries()[k]->armiesnum() <<endl;
        int choose;
        int num;
        cin>>choose;
        cout<< "Enter number of armies you wish to add to that country: ";
        cin>>num;
        x->getCountries()[choose]->addarmies(num);
        x->addArmies(-num);//remove that armies from the player
        cout<< x->getCountries()[choose]->get_country_name() << " has " <<x->getCountries()[choose]->armiesnum() << " now. " <<endl;
        cout<<"You have "<< x->getArmies()<< " left." <<endl;
        
    }
    cout<<endl;
    cout<<endl;
}

void HumanPlayer::attack(Player* x)
{
    cout<<endl;
    cout<<endl;
    std:: cout<<"-------------"<< "Player " << x->get_player_id()<<"-------------"<<endl;
    std:: cout << "Attacking for Human player" << endl;
    int mine;
    int their;
    int key;
    bool continueattack = false;
    bool surrender = false;
    cout<<"You are in the attack stage."<<endl;
    cout << "Do you want to attack, press 1 to play and press any key to quit" << endl;
    cin >> key;
    if (key!=1)
        continueattack=true;
    while(!continueattack ==true ){
        for (int i = 0; i < x->getCountries().size(); i++) {
            cout << i << " -> " << x->getCountries()[i]->get_country_name() << endl;
            cout << "The number of armies present in this country is " << x->getCountries()[i]->armiesnum()<< "\n" << endl;
        }
        cout << "Please choose the country you want to attack from by index: " << endl;
        cin >> mine;
        
        while(x->getCountries()[mine]->armiesnum()<2){
            cout << "You choose " << x->getCountries()[mine]->get_country_name() <<" and their number of armies is " << x->getCountries()[mine]->armiesnum() <<"\n"<< endl;
            cout<<"However since this has less than 2 armies on it you cannot attack. Please enter new index: "<<endl;
            cin>>mine;
        }
        
        //Choose the country you wish to attack
        
        for(int i =0; i < x->getCountries()[mine]->getAdjCountries().size();i++){
            if(x->getCountries()[mine]->getAdjCountries()[i]->getPlayer()!=x){
                cout<< "Please enter the number corresponding to the country you wish to attack" <<endl;
                cout<< i << " "<< x->getCountries()[mine]->getAdjCountries()[i]->get_country_name() << " has " <<x->getCountries()[mine]->getAdjCountries()[i]->armiesnum() << " armies and is owned by Player " << x->getCountries()[mine]->getAdjCountries()[i]->getPlayer()->get_player_id() <<endl;
            }
        }
        cin >> their;
        cout<< "You choose to attack: " << x->getCountries()[mine]->getAdjCountries()[their]->get_country_name() << " has " <<x->getCountries()[mine]->getAdjCountries()[their]->armiesnum() << " number of armies and is owned by Player " << x->getCountries()[mine]->getAdjCountries()[their]->getPlayer()->get_player_id() <<endl;
        
        
        
        int num;
        cout << "You have " << x->getCountries()[mine]->armiesnum() << " armies" << endl;
        
        cout<< "Do you wish to continue attacking? "<<endl;
        cout<< "Please enter 1 to continue: ";
        cin >> key;
        if(key!=1){
            surrender= true;
            cout<<"Attacking player has decided to stop attacking this country";
        }
        
        while(!surrender==true){
            // dice can't be more than the amount of armies on the attacking country
            cout << "Please input the numbers of dice you want to roll (1-" << 3 << ") max being the number of countries you have.." << endl;
            cin >> num;
            cout << "user input: " << num << endl;
            
            while (!((num > 0) && (num <= 3) && (num<=x->getCountries()[mine]->armiesnum()))) {
                cout << "Invalid number of dice, Please try again (1-" << 3 << ")" << endl;
                cin >> num;
                cout << num << endl;
                if (num == -1)
                    break;
            }
            if (num != -1) {
                x->gettheirdice()->setNumberOfDice(num);
                cout << "Dice number " << x->gettheirdice()->getNumberOfDice() << endl;
                x->gettheirdice()->DiceRoll();
            } //Player gets to roll their dice
            
            vector<int> DiceOut = x->gettheirdice()->getdiceoutcome(); //attacking players dice outcome
            x->sortdice();
            //defending player plays?
            int  DefendArmiesNumber = x->getCountries()[mine]->getAdjCountries()[their]->armiesnum();
            cout << "DEFENDING PLAYER: You have " << DefendArmiesNumber << " armies" << endl;
            x->getCountries()[mine]->getAdjCountries()[their]->getPlayer()->computerdefend(DefendArmiesNumber);
            
            vector<int> Dicedefend =  x->getCountries()[mine]->getAdjCountries()[their]->getPlayer()->gettheirdice()->getdiceoutcome();
            //defending players dice outcome
            
            
            //actually attacking
            if (!(DiceOut.empty())) {
                
                for (int i = 0; i < Dicedefend.size(); i++) {
                    if ((x->getCountries()[mine]->armiesnum() == 1)||(x->getCountries()[mine]->getAdjCountries()[their]->armiesnum()<= 0))
                        break;
                    if (DiceOut[i] < Dicedefend[i])
                    {
                        cout << "Comparing attack:" << DiceOut[i] << "  and defend:" << Dicedefend[i] << endl;
                        x->getCountries()[mine]->decrementArmies();//decrementarmies
                        cout << "Defender win!" << endl;
                        
                        
                        cout << "Attacker has " << x->getCountries()[mine]->armiesnum() << " left" << endl;
                        cout <<"Defender has " <<x->getCountries()[mine]->getAdjCountries()[their]->armiesnum() << " left" <<endl;
                    }
                    else if (DiceOut[i] > Dicedefend[i])
                    {
                        cout << "Comparing attack:" << DiceOut[i] << " and defend:" << Dicedefend[i] << endl;
                        x->getCountries()[mine]->getAdjCountries()[their]->decrementArmies();
                        cout << "Attacker win!" << endl;
                        cout << "Attacker has " << x->getCountries()[mine]->armiesnum() << " left" << endl;
                        cout << "Defender has " << x->getCountries()[mine]->getAdjCountries()[their]->armiesnum() << " left" << endl;
                    }
                    else if (DiceOut[i] == Dicedefend[i])
                    {
                        cout << "Comparing attack:" << DiceOut[i] << "and defend:" << Dicedefend[i] << endl;
                        x->getCountries()[mine]->decrementArmies();
                        
                        cout << "Defender win!" << endl;
                        cout << "Attacker has " << x->getCountries()[mine]->armiesnum() << " left" << endl;
                        cout << "Defender has " << x->getCountries()[mine]->getAdjCountries()[their]->armiesnum() << " left" << endl;
                    }
                }
                x->cleardice();
                x->getCountries()[mine]->getAdjCountries()[their]->getPlayer()->cleardice();
                //
                //
                //
                //need to clear dice outcome after dice are compared
                //
                //
                //

                if (x->getCountries()[mine]->armiesnum() == 1) {
                    cout << "!Defender won!" << endl; //can no longer attack
                    cout <<"Player can no longer attack with their country"<<endl;
                    break;
                }
                else if (x->getCountries()[mine]->getAdjCountries()[their]->armiesnum()<= 0) {
                    cout << "Attacker won " << x->getCountries()[mine]->getAdjCountries()[their]->get_country_name()<< "!"<<endl;
                    x->getCountries()[mine]->getAdjCountries()[their]->getPlayer()->removeCountry(x->getCountries()[mine]->getAdjCountries()[their]);
                    cout << x->getCountries()[mine]->getAdjCountries()[their]->get_country_name() << " was removed" << endl;
                    x->getCountries()[mine]->getAdjCountries()[their]->setPlayer(x);
                    x->addCountry(x->getCountries()[mine]->getAdjCountries()[their]);
                    cout << "Attacker owns " << x->getCountries()[mine]->getAdjCountries()[their]->get_country_name() <<" now " << endl;
                    cout << "You may now move armies from your attacking country onto your new one. Please select an amount enter an amount from 1 to " << x->getCountries()[mine]->armiesnum()-1 << endl;
                    int amount;
                    cout << "user input:" ;
                    cin >> amount;
                    x->getCountries()[mine]->getAdjCountries()[their]->addarmies(amount);
                    if(x->getDeck()->getCardNo()>0){
                        x->gettheirhand()->addCard(x->getDeck()->Draw());
                    }
                    break;
                }
                
                cout << "You have " <<  x->getCountries()[mine]->armiesnum() << " armies" << endl;
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
    
    
    
    

}

void HumanPlayer::fortify(Player* x)
{
    std:: cout<<"-------------"<< "Player " << x->get_player_id()<<"-------------"<<endl;
    std:: cout << "Fortifying for human player" << endl;
    cout<<"You may now move armies from one of your countries to a neighbours"<<endl;
    
    for(int i = 0; i < x->getCountries().size(); i++ )
        cout << i << " " << x->getCountries()[i]->get_country_name() << " armies: " << x->getCountries()[i]->armiesnum() << endl;
    cout<<"please enter the index of your source country: ";
    int source;
    cin >> source;
    for(int i = 0; i < x->getCountries()[source]->getAdjCountries().size();i++){
        if(x->getCountries()[source]->getAdjCountries()[i]->getPlayer()==x)
            cout << i << x->getCountries()[source]->getAdjCountries()[i]->get_country_name() << " has " <<x->getCountries()[source]->getAdjCountries()[i]->armiesnum() << "armies" <<endl;
    }
    int give;
    int move;
    cin >> give;
    cout<<"Please enter the amount of armies you wish to move between 1 - " << (x->getCountries()[source]->armiesnum()-1) <<endl;
    cin >> move;
    cout<< "Moving "<< move << " armies from " << x->getCountries()[source]->get_country_name() << " to " <<x->getCountries()[source]->getAdjCountries()[give]->get_country_name()<<endl;
    x->getCountries()[source]->getAdjCountries()[give]->addarmies(move);
   x->getCountries()[source]->removearmies(move);
}
Cheater::Cheater(){
    
}
Cheater::~Cheater(){
    
}
void Cheater::reinforce(Player* x){
    std:: cout<<"-------------"<< "Player " << x->get_player_id()<<"-------------"<<endl;
    std:: cout << "Reinforcing for Cheater player" << endl;
     x->reinforcebonus();
    for(int j=0;j<x->getCountries().size();j++){
        cout<<x->getCountries()[j]->get_country_name() << " adding " << x->getCountries()[j]->armiesnum() <<  " armies. "<<endl;
        x->getCountries()[j]->set_armies(x->getCountries()[j]->armiesnum()*2);
    }
    x->setArmies(0);
    std::cout<<"REINFORCING STAGE OVER"<<endl;
}
void Cheater::attack(Player* x){
    //print out all the countries it owns?
    std:: cout<<"-------------"<< "Player " << x->get_player_id()<<"-------------"<<endl;
    std:: cout << "Attack for Cheater player" << endl;
    
    for(int k=0; k<x->getCountries().size();k++){
        
        for(int i=0;i<x->getCountries()[k]->getAdjCountries().size();i++){
            if(x->getCountries()[k]->getAdjCountries()[i]->getPlayer()!=x){
                cout<<x->getCountries()[k]->get_country_name()<< " chosen to attack!"<<endl;
                cout<<"Player chose to attack "<< x->getCountries()[k]->getAdjCountries()[i]->get_country_name()<<endl;
                cout<<"PLAYER: "<< x->getCountries()[k]->getAdjCountries()[i]->getPlayer()->get_player_id()<<" DEFENDING" << endl;
                cout << "!Attacker won!" << endl;
                x->getCountries()[k]->getAdjCountries()[i]->addarmies(1);
                x->getCountries()[k]->decrementArmies();
               x->getCountries()[k]->getAdjCountries()[i]->getPlayer()->removeCountry(x->getCountries()[k]->getAdjCountries()[i]);
                cout << x->getCountries()[k]->getAdjCountries()[i]->get_country_name() << " was removed" << endl;
                x->getCountries()[k]->getAdjCountries()[i]->setPlayer(x);
                x->addCountry(x->getCountries()[k]->getAdjCountries()[i]);
                
                cout << "Attacker owns " << x->getCountries()[k]->getAdjCountries()[i]->get_country_name() <<" now " << endl;
                if(x->getDeck()->getCardNo()>1){
                    x->gettheirhand()->addCard(x->getDeck()->Draw());
                }
                //attack and win
            }
                
            
        }
            
    }
    cout<<"ATTACKING PHASE OVER"<<endl;
}
void Cheater::fortify(Player* x){
    std:: cout<<"-------------"<< "Player " << x->get_player_id()<<"-------------"<<endl;
    std:: cout << "FORTIFYING for Cheater player" << endl;
    
    for(int i=0;i<x->getCountries().size();i++){
        for(int j=0;j<x->getCountries()[i]->getAdjCountries().size();j++){
            if(x->getCountries()[i]->getAdjCountries()[j]->getPlayer()!=x){
                cout<<"Doubling armies on "<< x->getCountries()[i]->get_country_name()<<endl;
                x->getCountries()[i]->set_armies(x->getCountries()[i]->armiesnum()*2);
                break;
            }
        }
    }
    cout<<"FORTIFYING STAGE OVER"<<endl;
}
RandomPlayer::RandomPlayer(){
    
}
RandomPlayer::~RandomPlayer(){
    
}
void RandomPlayer::reinforce(Player* x){
    std:: cout<<"-------------"<< "Player " << x->get_player_id()<<"-------------"<<endl;
    std:: cout << "Reinforcing for Random player" << endl;
    x->reinforcebonus();
    x->addArmies(x->gettheirhand()->computerexchange());
    int v = rand()% (x->get_number_of_countries());
    cout<<"Incrementing armies in "<<x->getCountries()[v]->get_country_name() << " by " << x->getArmies()<<endl;
    x->getCountries()[v]->addarmies(x->getArmies());
    x->setArmies(0);
    std:: cout<<"REINFORCING STAGE OVER "<<endl;
    
}
void RandomPlayer::attack(Player* x){
    //print out all countries..
    bool adj = false;
    std:: cout<<"-------------"<< "Player " << x->get_player_id()<<"-------------"<<endl;
    std:: cout << "Attacking for Random player" << endl;
    int v = rand()% (x->get_number_of_countries());
   // std:: cout <<x->getCountries()[v]->get_country_name()<< " chosen to attack" <<endl;
    while(adj==false){
        //check for adj countries,
        for(int i = 0 ; i < x->getCountries()[v]->getAdjCountries().size(); i++ ){
            if(x->getCountries()[v]->getAdjCountries()[i]->getPlayer()!=x){
                adj =true;
                break;
            }
        }
        if(adj==false){
            v = rand()% (x->get_number_of_countries());
//            cout<< "That country didn't have any adj countries belonging to another player. Another random index was chosen"<<endl;
           // std:: cout <<x->getCountries()[v]->get_country_name()<< " chosen to attack" <<endl;
        }
        
    }
    
    int defender = rand()%(x->getCountries()[v]->getAdjCountries().size());
    adj=false;
    //check if random adj country selected belongs to another player
    while(adj==false){
        
            if(x->getCountries()[v]->getAdjCountries()[defender]->getPlayer()!=x){
                adj = true;
            }
        else
            defender = rand()%(x->getCountries()[v]->getAdjCountries().size());
        }
     std:: cout <<x->getCountries()[v]->get_country_name()<< " chosen to attack" <<endl;
    //unsure how large this number should be..
    int  numofattacks = rand() % 10;
    int timestoattack = 0;
    cout<<"Number of times chosen to attack is " << numofattacks<<endl;
    Country* attack  = x->getCountries()[v];
    Country* defend = x->getCountries()[v]->getAdjCountries()[defender];
    //shall attack until someone wins of rounds run out
    while(timestoattack!=numofattacks&&attack->armiesnum()>1&&defend->armiesnum()>0){
        cout<<"Player "<<defend->getPlayer()->get_player_id()<< " defending " <<defend->get_country_name()<<endl;
        cout << "Defender has " << defend->armiesnum() << " armies." << endl;
        
        int rounds=0;
        
        cout << "Attacker has " << attack->armiesnum() << " armies" << endl;
        
        if(attack->armiesnum()>=3){
            x->gettheirdice()->setNumberOfDice(3);
            rounds = 3;
        }
        else{
            rounds = 2;
            x->gettheirdice()->setNumberOfDice(2);
        }
        x->gettheirdice()->DiceRoll();
        vector<int> DiceOut = x->gettheirdice()->getdiceoutcome(); //attacking players dice outcome
        x->sortdice();
        
        //defending player
        cout<<"Defending Player's turn"<<endl;
        defend->getPlayer()->computerdefend(defend->armiesnum());
        vector<int> Dicedefend = defend->getPlayer()->gettheirdice()->getdiceoutcome();
        
        //comparing the dice values
        for (int j = 0; j < rounds; j++) {
            
            if (DiceOut[j] < Dicedefend[j])
            {
                cout << "Comparing attack:" << DiceOut[j] << "  and defend:" << Dicedefend[j] << endl;
                attack->decrementArmies();//decrementarmies
                cout << "Defender win!" << endl;
                
                
                cout << "Attacker has " << attack->armiesnum() << " left" << endl;
                cout << "Defender has " << defend->armiesnum() << " left" << endl;
            }
            else if (DiceOut[j] > Dicedefend[j])
            {
                cout << "Comparing attack:" << DiceOut[j] << " and defend:" << Dicedefend[j] << endl;
                defend->decrementArmies();
                cout << "Attacker win!" << endl;
                cout << "Defender has " << defend->armiesnum() << " left" << endl;
            }
            else if (DiceOut[j] == Dicedefend[j])
            {
                cout << "Comparing attack:" << DiceOut[j] << "and defend:" << Dicedefend[j] << endl;
                attack->decrementArmies();
                
                cout << "Defender win!" << endl;
                cout << "Attacker has " <<attack->armiesnum() << " left" << endl;
            }
            if (attack->armiesnum() == 1||(defend->armiesnum()== 0))
                break;
            
        }
        timestoattack++;
        //clears dice vector
        x->cleardice();
        defend->getPlayer()->cleardice();
    }
        
        if (attack->armiesnum() == 1) {
            cout << "!Defender won!" << endl; //can no longer attack
            // break;
        }
        else if (defend->armiesnum()== 0) {
            cout << "!Attacker won!" << endl;
            defend->addarmies(1);
            attack->decrementArmies();
           defend->getPlayer()->removeCountry(defend);
            cout <<defend->get_country_name() << " was removed" << endl;
           defend->setPlayer(x);
            x->addCountry(defend);
            
            cout << "Attacker owns " << defend->get_country_name() <<" now " << endl;
            
            if(x->getDeck()->getCardNo()>1){
                x->gettheirhand()->addCard(x->getDeck()->Draw());
            }
            //break;
        }
        else if (timestoattack>=numofattacks){
            cout <<"Attacker has decided to stop attacking"<<endl;
            cout << "Defender has " << defend->armiesnum() << " armies." << endl;
            cout << "Attacker has " << attack->armiesnum() << " armies" << endl;
            
        }
        
    
    
    cout<<"END OF ATTACK PHASE"<<endl;
}
void RandomPlayer::fortify(Player* x){
    bool valid = false;
    //source country is random
    //destination country is random
    //num of countries moved is random
    std:: cout<<"-------------"<< "Player " << x->get_player_id()<<"-------------"<<endl;
    std:: cout << "Fortifying for Random player" << endl;
    //a temp vector to find
    vector<Country*> abletoFortify;
    //pick a random index from this vector, if empty cannot fortify..
    for(int i = 0; i<x->getCountries().size();i++){
        for(int j = 0; j<x->getCountries()[i]->getAdjCountries().size();j++){
            if(x->getCountries()[i]->getAdjCountries()[j]->getPlayer()==x&&x->getCountries()[i]->getAdjCountries()[j]->armiesnum()>1){
                abletoFortify.push_back(x->getCountries()[i]);
                
            }
        }
    }
    
    if(abletoFortify.size()>0){
    int fort = rand()% (abletoFortify.size());
    int des = rand()% (abletoFortify[fort]->getAdjCountries().size());
    cout<<"Fortify "<<abletoFortify[fort]->get_country_name()<<endl;
        while(valid==false){
    if(abletoFortify[fort]->getAdjCountries()[des]->armiesnum()>1&&abletoFortify[fort]->getAdjCountries()[des]->getPlayer()==x){
        cout<<"Moving countries from " <<abletoFortify[fort]->getAdjCountries()[des]->get_country_name() <<" to "<<abletoFortify[fort]->get_country_name()<<endl;
        //moving 1 to numofarmies-1
        int amount = rand() % 1+(abletoFortify[fort]->getAdjCountries()[des]->armiesnum()-1);
        cout<<"Amount moved was "<<amount<<endl;
        abletoFortify[fort]->addarmies(amount);
        abletoFortify[fort]->getAdjCountries()[des]->removearmies(amount);
        valid=true;
      //  break;
    }
            else
                des = rand()% (abletoFortify[fort]->getAdjCountries().size());;
                
    }
    }
    else
        cout<<"Unable to move because cannot find country with adj countries"<<endl;
    
    
    
}
