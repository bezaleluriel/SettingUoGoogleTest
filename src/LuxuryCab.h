#ifndef EX1_LUXURYCAB_H
#define EX1_LUXURYCAB_H
#include "BaseCab.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/serialization/access.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/archive/tmpdir.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>

class LuxuryCab:public BaseCab     {
private:

    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & boost::serialization::base_object<BaseCab>(*this);
        ar & coEfficient;
    }


public:

    /**
     * constructor.
     */
    LuxuryCab();

    /**
     * constructor.
     * @param cabId is the cab's id.
     * @param taxiType is a number representing the taxi type - 1 standard , 2- luxury.
     * @param manufacturer is a char representing the manufacturer of the car(will be made into enum).
     * @param color is a char representing the color of the car(will be made into enum).
     */
    LuxuryCab(int cabId, int taxiType, char manufacturer, char color, Structure* map);

    /**
     * this function overrides the base class standardcab's function because it moves twice as fast then
     * the standard cab.(moves 2 blocks with every movement), unless there is one block left to destination and then
     * it will move only one.
     */
    void move(Point p);

};


#endif //EX1_LUXURYCAB_H
