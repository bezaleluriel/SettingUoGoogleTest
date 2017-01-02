#ifndef EX1_STRUCTURE_H
#define EX1_STRUCTURE_H
#include "Point.h"
#include "GridNode.h"
#include <boost/serialization/access.hpp>
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
/**
 * this is an abstract class that will be inherited by other classes
 * that will contain data in different forms e.g grid/tree etc'.
 */

class Structure {
    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive &ar, const unsigned int version) {

    }
public:
    virtual void createNodes()=0;
    virtual void flagNode(Point p)=0;
    virtual GridNode* getNode (Point p)=0;
    virtual void markObstacle(Point p)=0;
};

BOOST_SERIALIZATION_ASSUME_ABSTRACT(Structure)

#endif //EX1_STRUCTURE_H
