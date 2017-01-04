//
// Created by matan on 13/12/16.
//

#include <boost/serialization/export.hpp>
#include "BaseCab.h"


BaseCab::BaseCab() {}

BaseCab::BaseCab(int cabId, int taxiType, char manufacturer, char color, Structure* map) {
    numOfKmPassed = 0;
    BaseCab::cabId = cabId;
    BaseCab::taxiType = taxiType;
    BaseCab::map = map;
    switch (manufacturer) {
        case 'H' :
            BaseCab::manufacturer = Manufacturer::Honda;
            break;
        case 'S' :
            BaseCab::manufacturer = Manufacturer::Subaro;
            break;
        case 'T' :
            BaseCab::manufacturer = Manufacturer::Tesla;
            break;
        case 'F' :
            BaseCab::manufacturer = Manufacturer::Fiat;
            break;
        default :
            break;
    }
    switch (color) {
        case 'R' :
            BaseCab::color = Color ::Red;
            break;
        case 'B' :
            BaseCab::color = Color ::Blue;
            break;
        case 'G' :
            BaseCab::color = Color ::Green;
            break;
        case 'P' :
            BaseCab::color = Color ::Pink;
            break;
        case 'W' :
            BaseCab::color = Color ::White;
            break;
        default :
            break;
    }
}

int BaseCab::getCabId() {
    return cabId;
}

int BaseCab::getNumOfKmPassed() {
    return numOfKmPassed;
}

Manufacturer BaseCab::getManufacturer() {
    return manufacturer;
}

Color BaseCab::getColor() {
    return color;
}

GridNode *BaseCab::getLocation() {
    return location;
}

void BaseCab::setLocation(GridNode *location) {
    BaseCab::location = location;
}

Point BaseCab::returnLocationInPoint() {
    return getLocation()->getPoint();
}

int BaseCab::getTaxiType()  {
    return taxiType;
}

void BaseCab::navigate(Point end) {
    Gps gps = Gps(map);
    route = gps.findeShortersRoute(getLocation()->getPoint(),end);
}



