//
//  deck.hpp
//  Tester101
//
//  Created by Monique Richard on 2017-10-21.
//  Copyright © 2017 Monique Richard. All rights reserved.
//

#ifndef deck_hpp
#define deck_hpp

#include <vector>


class deck
{
public:
    deck();
    deck(int numcards);
    void setCardNo(int nO);
    int getCardNo();
    void createDeck(int amount);//will create the deck obj
    char Draw();//will draw from deck and will put them in the hand obj
    void incrementSetsReturned();
    int getSetsReturned(){return setsReturned;};
   
    std::vector<char> gettheDeck();
private:
    
    int setsReturned;
    int noCards;
    int noReinforcement;
   
    std::vector<char> theDeck;

    
    
};

#endif /* deck_hpp */
