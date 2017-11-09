//
//  Hand.hpp
//  Tester101
//
//  Created by Monique Richard on 2017-10-21.
//  Copyright © 2017 Monique Richard. All rights reserved.
//

#ifndef Hand_hpp
#define Hand_hpp
#include "Hand.hpp"
#include "deck.hpp"

#include <vector>
#include <iostream>

#include <stdio.h>
class Hand{
public:
    Hand();
    Hand(std::vector<char> cars);
    ~Hand();
    
    void showHand();
    void setCards(std::vector<char> cars);
    void addCard(char c);
    int exchange();
    int computerexchange();
    int rateOfExchange();
    std::vector<char> getCards(){return cards;};
    void setDeck(deck* de){D = de;}

private:
    deck* D;
    std::vector<char> cards;
    int numOfCards;
};
#endif /* Hand_hpp */
