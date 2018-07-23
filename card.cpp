/**
 * \class Card
 *
 *
 * This class defines a card for the game Set (http://www.setgame.com/set)
 * The card has four properties that can each be one of three values.
 *
 * \author (last to touch it) $Author: Jameson Hyde $
 *
 * \date $Date: 2014/01/18 $
 *
 * Contact: jameson.hyde@ieee.com
 *
 * Created on: 2014/01/18
 *
 */

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

#include "card.h"

using namespace std;

#undef KEY_DEF
#define KEY_DEF( identifier, id, name )  (name)

static string const number_strings[] =    { NUMBERS_DEF };
static string const colour_strings[] =    { COLOURS_DEF };
static string const shade_strings[] =     { SHADES_DEF };
static string const symbol_strings[] =    { SYMBOLS_DEF };

const uint32_t NUM_PROPERTIES = MAX_NUM;

Card::Card(number_t number, colour_t colour, shade_t shade, symbol_t symbol)
{
    this->number = number;
    this->colour = colour;
    this->shade = shade;
    this->symbol = symbol;
}

number_t Card::get_number()
{
    return this->number;
}

colour_t Card::get_colour()
{
    return this->colour;
}

shade_t Card::get_shade()
{
    return this->shade;
}

symbol_t Card::get_symbol()
{
    return this->symbol;
}

//effectively create a ternary number representing a unique card index
//only 81 possible values can result
int Card::get_index()
{
    return ((int)number +
            (int)colour * MAX_NUM +
            (int)shade * MAX_NUM * NUM_COLOURS +
            (int)symbol * MAX_NUM * NUM_COLOURS * NUM_SHADES);
}

ostream& operator<<(ostream& out, Card& card)
{
    out << number_strings[card.number] << ' '
        << colour_strings[card.colour] << ' ' 
        << shade_strings[card.shade] << ' ' 
        << symbol_strings[card.symbol];
    if(card.number > ONE) {
        out << 's';
    }
    return out;
}

Card* ParseCardString(string card_string)
{
    string number_str, colour_str, shade_str, symbol_str;
    number_t number;
    colour_t colour;
    shade_t shade;
    symbol_t symbol;
    uint32_t i;
    istringstream ss(card_string);

    ss >> number_str;
    ss >> colour_str;
    ss >> shade_str;
    ss >> symbol_str;

    //parse number
    for(i = 0; i < number_str.length(); i++) {
        number_str[i] = tolower(number_str[i]);
    }

    //allow for integers ("1", "2", or "3")
    if(isdigit(number_str[0]) && atoi(number_str.c_str()) <= MAX_NUM && atoi(number_str.c_str()) > 0) {
        number = (number_t)(atoi(number_str.c_str())-1);
    }
    //otherwise check strings ("one", "two", or "three")
    else {
        for(i = 0; i < MAX_NUM; i++) {
            if(0 == number_str.compare(number_strings[i])) {
                number = (number_t)i;
                break;
            }
        }
        if(i >= MAX_NUM) {
            cerr << "Failed to parse number from string ('" << number_str << "')" << endl;
            return NULL;
        }
    }

    //parse colour
    for(i = 0; i < colour_str.length(); i++) {
        colour_str[i] = tolower(colour_str[i]);
    }

    for(i = 0; i < NUM_COLOURS; i++) {
        if(0 == colour_str.compare(colour_strings[i])) {
            colour = (colour_t)i;
            break;
        }
    }
    if(i >= NUM_COLOURS) {
        cerr << "Failed to parse colour from string ('" << colour_str << "')" << endl;
        return NULL;
    }

    //parse shade
    for(i = 0; i < shade_str.length(); i++) {
        shade_str[i] = tolower(shade_str[i]);
    }

    for(i = 0; i < NUM_SHADES; i++) {
        if(0 == shade_str.compare(shade_strings[i])) {
            shade = (shade_t)i;
            break;
        }
    }
    if(i >= NUM_SHADES) {
        cerr << "Failed to parse shade from string " << shade_str << "')" << endl;
        return NULL;
    }

    //parse symbol
    for(i = 0; i < symbol_str.length(); i++) {
        symbol_str[i] = tolower(symbol_str[i]);
    }

    //drop pluralization
    if(symbol_str[symbol_str.length()-1] == 's') {
        symbol_str.resize(symbol_str.length()-1);
    }

    for(i = 0; i < NUM_SYMBOLS; i++) {
        if(0 == symbol_str.compare(symbol_strings[i])) {
            symbol = (symbol_t)i;
            break;
        }
    }
    if(i >= NUM_SYMBOLS) {
        cerr << "Failed to parse symbol from string ('" << symbol_str << "')" << endl;
        return NULL;
    }

    return new Card(number, colour, shade, symbol);
}

