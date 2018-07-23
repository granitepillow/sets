#include <iostream>
#include <fstream>
#include <string>
#include <stdint.h>

#include "card.h"
#include "hand.h"

using namespace std;

void Hand::init_hand()
{
    for(uint32_t i = 0; i < MAX_COMBINATIONS; i++ ) {
        this->map[i] = -1;
    }
}

void Hand::add_card(Card* card)
{
    hand.push_back(*card);
    map[card->get_index()] = hand.size()-1;
}

Hand::Hand()
{
    init_hand();
}

Hand::Hand(vector<Card> hand)
{
    init_hand();
    for(uint32_t i = 0; i < hand.size(); i++ ) {
        add_card(new Card(hand[i].get_number(), hand[i].get_colour(), hand[i].get_shade(), hand[i].get_symbol() ));
    }
}

Hand::Hand(char* input_file_path)
{
    string line;
    ifstream fd(input_file_path);
    init_hand();
    if(fd.is_open()) {
        while(getline(fd, line)) {
            Card* card = ParseCardString(line);
            if(card) {
                add_card(card);
            } else {
                cerr << "Unable to parse line ('" << line << "'); skipping" << endl;
                continue;
            }
        }
        fd.close();
    } else {
        cerr << "Unable to open file " << input_file_path << endl;
    }
}

vector<Card> Hand::get_hand() {
    return this->hand;
}

int32_t Hand::get_missing_property(uint32_t i, uint32_t j)
{
    if( NUM_PROPERTIES <= i || NUM_PROPERTIES <= j ) {
        return -1;
    }
    if(i == j) {
        return i;
    } else {
        //simple math to return:
        // 0 if args are 1, 2
        // 1 if args are 0, 2
        // 2 if args are 0, 1
        return -i - j + 3;
    }
}

int32_t Hand::is_set(uint32_t i, uint32_t j)
{
    number_t number;
    colour_t colour;
    shade_t shade;
    symbol_t symbol;

    number = (number_t)get_missing_property(hand[i].get_number(), hand[j].get_number());
    colour = (colour_t)get_missing_property(hand[i].get_colour(), hand[j].get_colour());
    shade = (shade_t)get_missing_property(hand[i].get_shade(), hand[j].get_shade());
    symbol = (symbol_t)get_missing_property(hand[i].get_symbol(), hand[j].get_symbol());

    Card card(number, colour, shade, symbol);
    return this->map[card.get_index()];
}

void Hand::print_sets()
{
    //find all possible pairs in hand
    //each pair has exactly one possible third card that will complete the set
    //check the map for each pair to see if the third card exists in the hand
    for(uint32_t i = 0; i < hand.size(); i++) {
        for(uint32_t j = i; j < hand.size(); j++ ) {
            int32_t k = is_set(i, j);
            // skip the set if k < j since we already found it
            if(k != -1 && k > (int32_t)j) {
                cout << hand[i] << "; " << hand[j] << "; " << hand[k] << endl;
            }
        }
    }
}
