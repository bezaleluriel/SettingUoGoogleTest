#ifndef EX1_POINT_H
#define EX1_POINT_H
#include<iostream>
#include <boost/serialization/access.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
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
using namespace std;
using namespace boost::archive;
/**
 * this class is a basic point class containing an x and y value. it holds methods that help
 * it change it's values and return them and to compare itself to another point.
 */
class Point {

private:
    int x;
    int y;

    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive &ar, const unsigned int version) {

        ar & x;
        ar & y;

    }

public:
    /**
     * default constructor.
     * @return nothing.
     */
    Point();

    /**
     * constructor.
     * @param x is the value of x for the point.
     * @param y is the value of x for the point.
     * @return nothing.
     */
    Point(int x,int y);

    /**
     * getPoint - returns a copy of the point.
     * @return a copy of the point.
     */
    Point getPoint();

    /**
     * getX - returns the x value of the point.
     * @return int - the x value of the point.
     */
    int getX();

    /**
     * getY - returns the x value of the point.
     * @return int - the y value of the point.
     */
    int getY();

    /**
     * setX - sets the x value for the point.
     * @param x is the value to be set for x.
     */
    void setX(int x);

    /**
     * setY - sets the x value for the point.
     * @param y is the value to be set for y.
     */
    void setY(int y);

    /**
     * compare - compares x and y values with another point .
     * @param p is the point we are comparing to this one.
     * @return true if they have same x and y values and false otherwise.
     */
    bool compare(Point p);

    bool isExist();

};

/**
 * operator overloading -
 * when printing out a point the system will automatically print it this way.
 * @param out isthe order on left of   <<.
 * @param point is the point we will want to print.
 */
std::ostream&operator<<(std::ostream& out,Point& point);

#endif //EX1_POINT_H
