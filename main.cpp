/**
 * This file defines a quick test program for finding sets in a Set hand.
  (http://www.setgame.com/set)
 * Provide a file path on the command line to initialize a hand and find the sets in it.
  See "usage" below for detail.
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

#include <iostream>
#include "hand.h"

using namespace std;

int main(int argc, char* argv[]) {
    if( argc != 2 ) {
        cerr << "Usage:" << endl << "sets <input hand file path>" << endl;
        return -1;
    }
    Hand hand(argv[1]);
    hand.print_sets();
    return 0;
}
