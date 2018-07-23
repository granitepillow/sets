/**
 * \class Hand
 *
 *
 * This class defines a hand of cards for the game Set (http://www.setgame.com/set)
 * The hand can have an indefinite number of cards.
 *
 * \author $Author: Jameson Hyde $
 *
 * \date $Date: 2014/01/18 $
 *
 * Contact: jameson.hyde@ieee.com
 *
 * Created on: 2014/01/18
 *
 */

#ifndef _HAND_H_
#define _HAND_H_

#include <vector>
#include <string>
#include <stdint.h>

#include "card.h"

using namespace std;

class Hand
{
    private:
        ///Hand itself is represented as a vector of Cards
        vector<Card> hand;

        ///List of all 81 possible cards and an indication of whether they are in the hand or not
        int32_t map[MAX_COMBINATIONS];
        
        ///Each pair of cards has exactly one possible card that makes a set.
        //This member function accepts two hand element indices and returns the index of matching set card in the hand,
        //or -1 if it isn't present.
        int32_t pair_has_set(uint32_t, uint32_t);

        ///Returns the missing value for a given property to complete a set.
        //For every card property, a set requires that the three candidate cards are unique or all the same.
        int32_t get_missing_property(uint32_t, uint32_t);
        
        ///initialization function for the card map.
        void init_hand();
    public:
        ///Empty constructor.
        Hand();

        ///Constructor that accepts an input file of a specified hand in appropriate format to be parsed
        Hand(char*);
        
        ///Constructor that accepts a vector of Cards to initialize the hand.
        Hand(vector<Card>);
        
        ///Add a desigated card to the end of the hand and increase the hand size,
        void add_card(Card*);
        
        ///Get the card vector representing the hand.
        vector<Card> get_hand();
        
        ///Output all sets within the hand to stdout.
        void print_sets();
};

#endif //_HAND_H_
