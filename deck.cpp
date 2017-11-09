//
//  deck.cpp
//  Tester101
//
//  Created by Monique Richard on 2017-10-21.
//  Copyright © 2017 Monique Richard. All rights reserved.
//

#include "deck.hpp"

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;



deck::deck()
{
    noCards=0;
}
deck::deck(int numcards){
    noCards = numcards;
}

void deck::setCardNo(int nO)//will set amount of cards
{
    noCards=nO;
}

int deck::getCardNo()//return amount of cards
{
    return noCards;
}
vector<char> deck::gettheDeck(){
    return theDeck;
}
void deck::createDeck(int amount)//will create vector deck
{
    setCardNo(amount);//numb cards
    getCardNo();//return cards
    vector<int> share(3);//vector that will keep count of frequency of cards
    
    
    for(int i=0;i<getCardNo();i++)
    {
        switch(i%3)//3 consecutive numbers will be changed in a I,C,A pattern
        {
            case 0:
                theDeck.push_back('I');
                
                break;
            case 1:
                theDeck.push_back('C');
                break;
            case 2:
                theDeck.push_back('A');
                break;
                
        }
        
    }
    
    for(int i=0; i<theDeck.size();i++){//prints out the content of vector theDeck
        cout << theDeck[i]<<" ";
    }
    cout<<endl;
    cout<<endl;
    
    cout<<"Size of deck vector: "<<theDeck.size()<<endl;
    
    
    for(int i=0;i<noCards;i++)
    {//will print the composition of deck withing 3 index places
        
        switch(theDeck[i])
        {
            case 'I'://increments share vector for every identical pattern
                ++share[0];
                break;
            case 'C':
                ++share[1];
                break;
            case 'A':
                ++share[2];
                break;
                
                
        }
        
        
    }
    
    for(int i=0;i!=share.size();i++)//prints proof of fair game
    {
        cout<<(i+1)<<"th type's freq: "<<share[i]<<"/"<< noCards<<endl;
        
    }
    
}





char deck::Draw(){
    
    //generate random number

    //use while loop to check if its = i c a

    // if it not i c a then re-pick with rand number till not taken
    
    cout<<"-----------------------------------------------------------------------"<<endl;
    
    srand(time(0));//changes random numbers constantly
    


        int randIndex=rand()%(noCards-1);//first random gen
        cout<<endl;
        
        
        
            cout<< "the random index chosen for this attempt is "<<randIndex <<"\nThe " <<theDeck[randIndex]<<" card was picked"<<endl;
        
        
        char temp =theDeck[randIndex];
        theDeck.erase(theDeck.begin()+randIndex);
        cout<<"============================================="<<endl;
        
        return (temp);
        

        
    }
void deck::incrementSetsReturned(){
    setsReturned++;
}

        
        
        

