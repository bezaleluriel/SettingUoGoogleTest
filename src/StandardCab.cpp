#include "StandardCab.h"
#include <boost/serialization/export.hpp>

StandardCab::StandardCab() {

}

StandardCab::StandardCab(int cabId, int taxiType, char manufacturer, char color, Structure* map)
:BaseCab(cabId, taxiType, manufacturer, color, map){
    coEfficient = 1;
}

void StandardCab::move(Point p) {
    location = map->getNode(p);
}


