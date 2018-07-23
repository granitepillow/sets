/**
 * \class Card
 *
 *
 * This class defines a card for the game Set (http://www.setgame.com/set)
 * The card has four properties that can each be one of three values.
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

#ifndef _CARD_H_
#define _CARD_H_

#include <iostream>
#include <string>
#include <stdint.h>

using namespace std;

//this defines the four card properties as enums with corresponding string names used for I/O

//number
//the number property seems odd to enumerate, but it provides restriction to the values,
// and simplifies index calculation described below
#define NUMBERS_DEF \
    KEY_DEF( ONE,           0, "one" ),         \
    KEY_DEF( TWO,           1, "two" ),         \
    KEY_DEF( THREE,         2, "three" ),       \
    KEY_DEF( MAX_NUM,       3, "" )

#define COLOURS_DEF \
    KEY_DEF( RED,           0, "red" ),         \
    KEY_DEF( GREEN,         1, "green" ),       \
    KEY_DEF( PURPLE,        2, "purple" ),      \
    KEY_DEF( NUM_COLOURS,   3, "" )

#define SHADES_DEF \
    KEY_DEF( OUTLINED,      0, "outlined" ),    \
    KEY_DEF( STIPED,        1, "striped" ),     \
    KEY_DEF( SOLID,         2, "solid" ),       \
    KEY_DEF( NUM_SHADES,    3, "" )

#define SYMBOLS_DEF \
    KEY_DEF( OVAL,          0, "oval" ),        \
    KEY_DEF( DIAMOND,       1, "diamond" ),     \
    KEY_DEF( SQUIGGLE,      2, "squiggle" ),    \
    KEY_DEF( NUM_SYMBOLS,   3, "" )

#define KEY_DEF( identifier, id, name )  identifier=id
typedef enum { NUMBERS_DEF } number_t;
typedef enum { COLOURS_DEF } colour_t;
typedef enum { SHADES_DEF } shade_t;
typedef enum { SYMBOLS_DEF } symbol_t;

#define MAX_COMBINATIONS    (MAX_NUM * NUM_COLOURS * NUM_SHADES * NUM_SYMBOLS)

extern const uint32_t NUM_PROPERTIES;

//each card has four properties that can each take one of three values
class Card
{
    private:
        ///number property of Card
        number_t    number;
        
        ///colour property of Card
        colour_t    colour;
        
        ///shade property of Card
        shade_t     shade;
        
        ///symbol property of Card
        symbol_t    symbol;
    public:
        ///Create a card based on specified property arguments.
        Card(number_t, colour_t, shade_t, symbol_t);
        
        ///Get Card number.
        number_t get_number();
        
        ///Get Card colour.
        colour_t get_colour();
        
        ///Get Card shade.
        shade_t get_shade();
        
        ///Get Card symbol.
        symbol_t get_symbol();
        
        ///Calculate a unique index to represent Card properties.
        //Each property represents a ternary digit from number as LSD to symbol as MSD.
        int get_index();
        
    ///Output operator overload to print the Card
    //"<number> <colour> <shade> <symbol>".
    friend ostream& operator<<(ostream&, Card&);
};

///Helper function to create and return a new card object from a specified input string.
//The string format must be: "<number> <colour> <shade> <symbol>".
Card* ParseCardString(string);

#endif //_CARD_H_
