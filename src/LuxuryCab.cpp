#include "LuxuryCab.h"
#include "BaseCab.h"
#include <boost/serialization/export.hpp>


LuxuryCab::LuxuryCab() {

}

LuxuryCab::LuxuryCab(int cabId, int taxiType, char manufacturer, char color, Structure* map)
        : BaseCab(cabId, taxiType, manufacturer, color, map){
    coEfficient = 2;
}

void LuxuryCab::move(Point p) {
    location = map->getNode(p);
}



