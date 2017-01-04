#include "LuxuryCab.h"
#include "BaseCab.h"
#include <boost/serialization/export.hpp>


LuxuryCab::LuxuryCab() {

}

LuxuryCab::LuxuryCab(int cabId, int taxiType, char manufacturer, char color, Structure* map)
        : BaseCab(cabId, taxiType, manufacturer, color, map){
    coEfficient = 2;
}

void LuxuryCab::move() {
    ///jump 2 points.
    if(route.size()>1){
        route.pop();
        setLocation(map->getNode(route.top()));
        route.pop();
    }
    ///if there is only one point left to dst, jump one point.
    if(route.size() == 1){
        setLocation(map->getNode(route.top()));
        route.pop();
    }
}



