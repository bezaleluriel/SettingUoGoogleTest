#include "BeginningInfoReader.h"
#include "Point.h"
#include <iostream>

/**
 * this class reads the string symbolizing size start and end point and gives the different variables
 * their value.
 */

/**
 * constructor.
 * @return void.
 */
BeginningInfoReader::BeginningInfoReader(){}

std::vector<std::string> BeginningInfoReader::split(std::string &s) {
    std::vector<std::string> vec;
    std::string::iterator it = s.begin();
    std::string addChars;
    while(*(it) != '\0'){
        if((*(it) != ',')&&((*(it)) != ' ')){
            addChars += *(it);
            it++;
        }
        if((*(it) == ',')||(*(it) == ' ')){
            vec.push_back(addChars);
            addChars.clear();
            it++;
        }
        if(*(it) == '\0'){
            vec.push_back(addChars);
            addChars.clear();
        }
    }
    return vec;
}