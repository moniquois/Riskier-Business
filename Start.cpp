//
//  Start.cpp
//  Tester101
//
//  Created by Monique Richard on 2017-10-21.
//  Copyright © 2017 Monique Richard. All rights reserved.
//

#include "Start.hpp"
#include "Player.hpp"
#include "Map.hpp"
#include "MapLoader.hpp"
#include "deck.hpp"
#include "Hand.hpp"
#include "PlayerType.hpp"
#include <algorithm>
#include <random>
#include <ctime>
#include <cstdlib>
#include "Dice.hpp"
#include <vector>
#include <iostream>


Start::Start(){
    cout<<"Welcome to the game Risk!" << endl;
    loaded = new Map();
    theDeck = new deck();
    mapfile = new MapLoader();
}
Start::~Start(){
    
}
void Start::setMap(){
    string select;
    
    //User enter the map it wants to load
    //
    cout <<"Please enter the name of the map you wish to Load from the list below(Copy and paste the desired map): " << endl;
    cout <<"1./Users/Monique/Desktop/world.txt" <<endl; //real map
    cout <<"2.map.gpp" <<endl; //bad extension
    cout <<"3./Users/Monique/Desktop/Tester101/Tester101/invalidmap.txt" <<endl; //invalid map contents
    cout <<"4./Users/Monique/Desktop/Tester101/Tester101/notconnectedmap.txt"<<endl; //not a connected map
    cout <<"5./Users/Monique/Desktop/Tester101/Tester101/medival.map"<<endl; //proper map
    cout <<"6./Users/Monique/Desktop/Tester101/Tester101/lordoftherings.txt"<<endl; //real map
    cin  >> select;
    
    //checks if you can read information from the map file/ and if it's valid
    bool e = mapfile->createMap(select);
    while(!e){
        cout<<"Map invalid. Please enter a new Map file name"<< endl;
        cin >> select;
       e = mapfile->createMap(select);
    }
    //sets the map using the information it gets from the map loader to create the map object
    loaded->createContinent(mapfile->returncontinentnames(), mapfile->returnBonus());
    loaded->createCountries(mapfile->returnCountries(), mapfile->returncontinentlist());
    loaded->setAdjCountries(mapfile->returnadj_countries());
   
    //checks to see if you can traverse the map, using a function from the map class
    while(!(loaded->connected())){
        //deletes the map & mapfile objects if map is not correctly connected.
        delete loaded;
        loaded = NULL;
        loaded = new Map();
        delete mapfile;
        mapfile =new MapLoader();
        
        cout<<"Map not a connected graph. Please enter a new Map file name"<< endl;
        cin >> select;
        bool e = mapfile->createMap(select);
        while(!e){
            cout<<"Map invalid. Please enter a new Map file name"<< endl;
            cin >> select;
            e = mapfile->createMap(select);
        }
       //creates the new map that was selected
        loaded->createContinent(mapfile->returncontinentnames(), mapfile->returnBonus());
        loaded->createCountries(mapfile->returnCountries(), mapfile->returncontinentlist());
        loaded->setAdjCountries(mapfile->returnadj_countries());
    }
    cout << "Map Created & verified!"<<endl;
    cout << "Deck has been created"<<endl;
    //creates the deck object using the numofcountries in the class
    theDeck->createDeck(loaded->getNumofCountries());
}
//method to create the players in the game
void Start::createPlayers(){
    bool correct=false;
    int play;
    while(correct==false){
        //user gets to choose how many players
    cout << "Please enter number of players(2-6): ";
    cin >> play;
        if(play>=2&&play<=6)
            correct=true;
    }
    for (int i=0;i<play;i++){
        int c;
        cout<<"Creating Player "<< (i+1) <<endl;
        thePlayers.push_back(new Player(i+1));
        thePlayers[i]->setMap(loaded);
        cout<<"What type of player do you want to be..."<<endl;
        cout<<"enter 1: Human"<<endl;
        cout<<"enter 2: Benelovant Computer"<<endl;
        cout<<"enter 3: Aggressive Computer"<< endl;
        cout<<"enter 4: Random Computer" <<endl;
        cout<<"enter 5: Cheater Computer" <<endl;
        cin>>c;
        if(c==1){
            thePlayers[i]->setStrategy(new HumanPlayer);
        }
        if(c==2){
            thePlayers[i]->setStrategy(new BenevolantPlayer);
        }
        
        if(c==3){
            thePlayers[i]->setStrategy(new AggressivePlayer);
        }
        if(c==4){
            thePlayers[i]->setStrategy(new RandomPlayer);
        }
        if(c==5){
            thePlayers[i]->setStrategy(new Cheater);
        }
                

        //setting the deck to the players
        //gives player access to the deck to draw..
        thePlayers[i]->setDeck(theDeck);
        thePlayers[i]->gettheirhand()->setDeck(theDeck);
        //gives each player a dice object
        cout<<"Giving Dice to new player" <<endl;

        //Gives each player an empty hand
        cout<<"Giving empty hand to player" <<endl;
        
 
        cout<<endl;
    }
}
void Start::startupphase(){
    auto rng = std::default_random_engine {};
    
    //random generator
    std::shuffle ( thePlayers.begin(), thePlayers.end(), rng );
    
    //Need to randomize better because it stays the same
    //Printing the new order of the players
    cout<<"The new order of plays is:" << endl;
    for(int i=0; i < thePlayers.size() ; i++)
    {
        cout << "Player: " << thePlayers[i]->get_player_id() << endl;
    }
    
    std::cout << '\n';
    
    //set armies for players
    //Assign armies based on game rules depending on how many players are created
    for(int i=0; i < thePlayers.size() ; i++)
    {
        
        //switch statements to be executed depending on the number of players
        switch(thePlayers.size())
        {
            case 2:
                thePlayers[i]->setArmies(40); //40
                break;
            case 3:
                thePlayers[i]->setArmies(35); //35
                break;
            case 4:
                thePlayers[i]->setArmies(30); //30
                break;
            case 5:
                thePlayers[i]->setArmies(25); //25
                break;
            case 6:
                thePlayers[i]->setArmies(20); //20
                break;
            default:
                cout<< "Not a valid player size" << endl;
                break;
        }
        
        //print players armies
        cout << "Player: " << thePlayers[i]->get_player_id() << " armies: " << thePlayers[i]->getArmies() << endl;
}
    //randomizer
    vector<Country*> randomorder =loaded->getCountries();
    std:: shuffle ( randomorder.begin(), randomorder.end(), rng );
    
    //Need to randomize better because it stays the same
    cout<<"The new order of countries is:" << endl;
    
    for(int i=0; i < randomorder.size() ; i++)
    {
        cout << "Country: " <<  randomorder[i]->get_country_name()<< endl;
    }
    
    std::cout << '\n';
 

    cout<<"Number of countries: " << loaded->getNumofCountries() << endl;
    cout<<"Number of players: " << thePlayers.size() << endl;
    
    //Gives players countries
    for(int i = 0; i <  loaded->getNumofCountries();)
    {
        
        for(int j = 0; j < thePlayers.size(); j++)
        {
            cout<< randomorder[i]->get_country_name() << "   ";
            thePlayers[j]->addCountry(randomorder[i]);
            randomorder[i]->setPlayer(thePlayers[j]); // may cause errors test..
            i++;
            
            if(loaded->getNumofCountries() == i)
            {
                break;
            }
        }
        
    }
    //Lets Players put armies on their countries
    cout<<"Assigning armies now!" << endl;
    autoassignarmies();
   // assignarmies();
//    int temp =thePlayers[0]->getArmies();
//        // keep going until the players don't have anymore armies
//        for(int i=0; i < temp ;i++)
//        {
//            //every round a player gets to increment its armies
//            for(int j = 0; j < thePlayers.size(); j++)  //for every country in i
//            {
//                cout<<"Player "<< thePlayers[j]->get_player_id() << " turn"<< endl;
//                cout<<"Enter the index which you would like to add the army to.. " << endl;
//                for (int k= 0 ; k<thePlayers[j]->getCountries().size();k++)
//                    cout<< k << " " << thePlayers[j]->getCountries()[k]->get_country_name()<<" number of armies is: " <<thePlayers[j]->getCountries()[k]->armiesnum() <<endl;
//                int choose;
//                cin>>choose;
//                // add one army to that country
//                thePlayers[j]->getCountries()[choose]->incrementArmies();
//                thePlayers[j]->decreaseArmies(); //remove that army from the player
//
//
//            }
//
//
//        }
    
    for(int j = 0; j < thePlayers.size(); j++){
         cout<<"Player " << thePlayers[j]->get_player_id() << endl;
        for (int k= 0 ; k < thePlayers[j]->getCountries().size();k++){
            cout << thePlayers[j]->getCountries()[k]->get_country_name()<<" amount of armies: " <<thePlayers[j]->getCountries()[k]->armiesnum() <<endl;
    }
    }
}
void Start::maingameloop(){
   bool win = false;
    while(win==false){
        if(thePlayers.size()==1){
            cout<<"A player owns all the countries! Winner!" << endl;
            win= true;
        }
    while(win==false){
    for(int i=0; i<thePlayers.size();i++){
    if(thePlayers[i]->get_number_of_countries()<1){
        cout<<"----------------------------------------------------"<<endl;
        cout<<"----------------------------------------------------"<<endl;
        cout<<"----------------------------------------------------"<<endl;
        cout<<"Player "<<thePlayers[i]->get_player_id()<<" is out of the game. :("<<endl;
        cout<<"----------------------------------------------------"<<endl;
        cout<<"----------------------------------------------------"<<endl;
        cout<<"----------------------------------------------------"<<endl;
        thePlayers.erase(thePlayers.begin()+i);
            break;
        }
            
        thePlayers[i]->playerTurn();
    }
        if(thePlayers.size()==1)
            win=true;
    }
    cout<<"----------------------------------------------------"<<endl;
    cout<<"----------------------------------------------------"<<endl;
    cout<<"----------------------------------------------------"<<endl;
    cout<<"PLAYER "<<thePlayers[0]->get_player_id()<<" WON"<<endl;
    cout<<"----------------------------------------------------"<<endl;
    cout<<"----------------------------------------------------"<<endl;
    cout<<"----------------------------------------------------"<<endl;

}
}

void Start::assignarmies(){
    cout<<"Assigning armies now!" << endl;
    int temp =thePlayers[0]->getArmies();
    // keep going until the players don't have anymore armies
    while(temp>0)
    {
        //loop needs to change depending on the size of getCountries..
        //if number is uneven loop won't work.

        for(int j=0; j < thePlayers[0]->getCountries().size();j++){
            for(int k=0;k<thePlayers.size();k++){
                cout<<"Player "<< thePlayers[k]->get_player_id() << " turn"<< endl;
                cout<<"Adding armies.. " << endl;
                thePlayers[k]->getCountries()[j]->incrementArmies();
                thePlayers[k]->decreaseArmies();
                cout<< j << " " << thePlayers[k]->getCountries()[j]->get_country_name()<<" number of armies is: " <<thePlayers[k]->getCountries()[j]->armiesnum() <<endl;
            }
            temp--;
            if(temp==0)
                break;
        }
        
   
       
    }
}
void Start::autoassignarmies(){
    //num of armies player has
    //
    for(int i=0; i<thePlayers.size();i++){
        cout<<"Player "<<thePlayers[i]->get_player_id()<< " turn"<<endl;
         cout<<"Adding armies.. " << endl;
        while(thePlayers[i]->getArmies()>0){
            for(int k=0; k<thePlayers[i]->getCountries().size();k++){
                thePlayers[i]->getCountries()[k]->incrementArmies();
                thePlayers[i]->decreaseArmies();
                cout << thePlayers[i]->getCountries()[k]->get_country_name()<<" number of armies is: " <<thePlayers[i]->getCountries()[k]->armiesnum() <<endl;
                if(thePlayers[i]->getArmies()<=0)
                    break;
            }
        }
    }
    cout<<"ARMIES HAVE BEEN ASSIGNED"<<endl;
}


