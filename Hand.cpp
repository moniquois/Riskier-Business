//
//  Hand.cpp
//  Tester101
//
//  Created by Monique Richard on 2017-10-21.
//  Copyright © 2017 Monique Richard. All rights reserved.
//

#include "Hand.hpp"
#include "deck.hpp"
class deck;
#include <vector>
#include <iostream>
using namespace std;
Hand::Hand(){
    numOfCards=0;
   
}

Hand::Hand(std::vector<char> cars){
    numOfCards = cars.size();
    cards = cars;
}
Hand::~Hand(){
    
}
void Hand::addCard(char c){
    cards.push_back(c);
    numOfCards++;
}
//New method for the aggressive player
int Hand::computerexchange(){
    int check[3]={0,0,0};
    int addedarmies = 0;
    if (cards.size()>2){ // might have to be 3!!! check for errors later!!
        for(int i=0;i<cards.size();i++){
            switch(cards[i])//prints status of card inventory
            {
                case 'I':
                    check[0]++;
                    break;
                case 'C':
                    check[1]++;
                    break;
                case 'A':
                    check[2]++;
                    break;
                    
            }
            
        }
            cout<<"Printing status of hand.. You have "<< numOfCards<<endl;
            cout <<"I: "<<(check[0])<<" ";
            cout <<"C: "<<(check[1])<<" ";
            cout <<"A: "<<(check[2])<< endl;
            
        
      
        if(check[0]>=1 && check[1]>=1 && check[2]>=1)//will tell us if you have enough cards to exchange, if so will give option to trade them in for armies
        {
         numOfCards-= 3;
            cout<<endl;
            cout<<"3 all different - you may exchange them for armies"<<endl;//trades your cards and then returns to draw and picks two remaining cards
                cout<<"You get "<<rateOfExchange()<<" armies in return for your 3 different cards"<<endl;
                D->incrementSetsReturned();
                check[0]--;
                check[1]--;
                check[2]--;
                for(int i=0;i<cards.size();i++)
                    if(cards[i]=='I'){
                        cards.erase(cards.begin()+i);
                        break;
                    }
                for(int i=0;i<cards.size();i++)
                    if(cards[i]=='C'){
                        cards.erase(cards.begin()+i);
                        break;
                    }
                for(int i=0;i<cards.size();i++)
                    if(cards[i]=='A'){
                        cards.erase(cards.begin()+i);
                        break;
                    }
            
            addedarmies+=rateOfExchange();
            
            
            if(check[0]>=3 || check[1]>=3 || check[2]>=3)//identical but in triggered if 3 cards are the same
            {
                numOfCards-= 3;
                cout<<endl;
                cout<<"3 of a kind - you may exchange them for armies"<<endl;
           
               
                    cout<<"You get "<<rateOfExchange()<<" armies in return for your 3 same cards"<<endl;
                    D->incrementSetsReturned();
                    if(check[0]==3){
                        int k=0;
                        while (k<3)
                        {
                            for(int i=0;i<cards.size();i++)
                            {
                                if(cards[i]=='I'){
                                    cards.erase(cards.begin()+i);
                                    k++;
                                }
                            }
                            
                        }
                        addedarmies+=rateOfExchange();
                       
                    }
                    if(check[1]==3){
                        int k=0;
                        while (k<3)
                        {
                            for(int i=0;i<cards.size();i++)
                            {
                                if(cards[i]=='C'){
                                    cards.erase(cards.begin()+i);
                                    k++;
                                }
                            }
                        }
                   addedarmies+=rateOfExchange();
                        
                    }
                    if(check[2]==3){
                        int k=0;
                        while (k<3)
                        {
                            for(int i=0;i<cards.size();i++)
                            {
                                if(cards[i]=='A')
                                {
                                    cards.erase(cards.begin()+i);
                                    k++;
                                }
                            }
                            
                        }
                    addedarmies+=rateOfExchange();
                    }
        }
    }
  
}
    return addedarmies;
}

int Hand::exchange(){
    
    int check[3]={0,0,0};
    if (cards.size()>2){ // might have to be 3!!! check for errors later!!
    for(int i=0;i<3;i++){
    switch(cards[i])//prints status of card inventory
    {
        case 'I':
            check[0]++;
            break;
        case 'C':
            check[1]++;
            break;
        case 'A':
            check[2]++;
            break;
            
    }
    }
        cout<<"Printing status of hand.. You have "<< numOfCards<<endl;
    cout <<"I: "<< check[0] <<" ";
    cout <<"C: "<< check[1] <<" ";
    cout <<"A: "<< check[2] << endl;
        
    }
    vector<char>::iterator it;
    if(check[0]>=1 && check[1]>=1 && check[2]>=1)//will tell us if you have enough cards to exchange, if so will give option to trade them in for armies
    {
        string agree;
        cout<<endl;
        cout<<"3 all different - you may exchange them for armies"<<endl;//trades your cards and then returns to draw and picks two remaining cards
        cout<<"To begin exchange input 'y'"<<endl;
        cin>>agree;
        if(agree=="y"||agree=="Y")
        {
            cout<<"You get "<<rateOfExchange()<<" armies in return for your 3 different cards"<<endl;
            D->incrementSetsReturned();
            check[0]=check[0]-1;
            check[1]=check[1]-1;
            check[2]=check[2]-1;
            for(int i=0;i<cards.size();i++)
                if(cards[i]=='I'){
                    cards.erase(cards.begin()+i);
                    break;
                }
            for(int i=0;i<cards.size();i++)
                if(cards[i]=='C'){
                    cards.erase(cards.begin()+i);
                    break;
                }
            for(int i=0;i<cards.size();i++)
                if(cards[i]=='A'){
                    cards.erase(cards.begin()+i);
                    break;
                }
            numOfCards-= 3;
        return rateOfExchange();
    }
    
    
    if(check[0]==3 || check[1]==3 || check[2]==3)//identical but in triggered if 3 cards are the same
    {
        string agree;
        cout<<endl;
        cout<<"3 of a kind - you may exchange them for armies"<<endl;
        cout<<"To begin exchange input 'y'"<<endl;
        cin>>agree;
        if(agree=="y"||agree=="Y")
        {
            cout<<"You get "<<rateOfExchange()<<" armies in return for your 3 same cards"<<endl;
            D->incrementSetsReturned();
            if(check[0]==3){
                int k=0;
                while (k<3)
                {
                    for(int i=0;cards.size();i++)
                    {
                        if(cards[i]=='I'){
                            cards.erase(cards.begin()+i);
                            k++;
                        }
                    }
                    
                }
                 numOfCards-= 3;
                return rateOfExchange();
            }
            if(check[1]==3){
                int k=0;
                while (k<3)
                {
                    for(int i=0;cards.size();i++)
                    {
                        if(cards[i]=='C'){
                            cards.erase(cards.begin()+i);
                            k++;
                        }
                    }
                }
                 numOfCards-= 3;
                return rateOfExchange();
            }
            if(check[2]==3){
                int k=0;
                while (k<3)
                {
                    for(int i=0;cards.size();i++)
                    {
                        if(cards[i]=='A')
                        {
                            cards.erase(cards.begin()+i);
                            k++;
                        }
                    }
                    
                }
                numOfCards-= 3;
            return rateOfExchange();
            }
            
            
        }
        
    }
    
    }
    return 0;
    }




    

int Hand::rateOfExchange(){
    if(D->getSetsReturned()==0)
        return 4;
    if(D->getSetsReturned()==1)
        return 6;
    if(D->getSetsReturned()==2)
        return 8;
    if(D->getSetsReturned()==3)
        return 10;
    if(D->getSetsReturned()==4)
        return 12;
    if(D->getSetsReturned()==5)
        return 15;
    if(D->getSetsReturned()>=6)
        return 15+(D->getSetsReturned()-5)*5;//check to make sure this number is correct ahah
    return 0;//idk man
}



