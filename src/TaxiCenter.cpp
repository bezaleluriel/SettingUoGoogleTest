#include "TaxiCenter.h"
#include "StandardCab.h"
#include "LuxuryCab.h"
TaxiCenter::TaxiCenter() {
}
TaxiCenter::TaxiCenter(Structure* structure) {
    map = structure;
}

TaxiCenter::~TaxiCenter() {
    while(driversList.size() > 0){
        delete[] driversList.front();
        driversList.pop_front();
    }
    while(tripInformationList.size() > 0){
        delete[] tripInformationList.front();
        tripInformationList.pop_front();
    }
    while(taxiCabsList.size() > 0){
        delete[] taxiCabsList.front();
        taxiCabsList.pop_front();
    }
}

void TaxiCenter::addDriver(int id, int age, MaritalStatus status, int experience, int vehicleId) {
    char c;
    if(status == MaritalStatus::Divorced){c = 'D';}
    if(status == MaritalStatus::Married){c = 'M';}
    if(status == MaritalStatus::Single){c = 'S';}
    if(status == MaritalStatus::Widowed){c = 'W';}
    Driver* driver = new Driver(id, age, c, experience, vehicleId);
    driversList.push_back(driver);
    std::list<BaseCab*>::iterator taxiIt = taxiCabsList.begin();
    //matches the driver with his taxi(the taxi that has the same vehicle id) and sets the taxi as his.
    while(taxiIt != taxiCabsList.end()){
        if(driver->getVehicleId() == (*(taxiIt))->getCabId()){
            driver->setTaxiCab((*(taxiIt)));
            break;
        }
        else{
            taxiIt++;
        }
    }
}

void TaxiCenter::addTaxiCab(int cabId, int taxiType, char manufacturer, char color) {
    //in case the taxi type is standard cab:
    if(taxiType == 1){
        BaseCab* standardCab = new StandardCab(cabId, taxiType, manufacturer, color, map);
        standardCab->setLocation(map->getNode(Point(0,0)));
        taxiCabsList.push_back(standardCab);
    }
    //in case the taxi type is luxury cab:
    if(taxiType == 2){
        BaseCab* luxuryCab = new LuxuryCab(cabId, taxiType, manufacturer, color, map);
        luxuryCab->setLocation(map->getNode(Point(0,0)));
        taxiCabsList.push_back(luxuryCab);
    }
}

void TaxiCenter::addRide(int id, int startX, int startY, int endX, int endY, int numOfPassengers, double tariff){
    TripInformation* tripInformation = new TripInformation(id,startX, startY, endX, endY, numOfPassengers, tariff);
    tripInformationList.push_back(tripInformation);
}

std::list<Driver *> *TaxiCenter::getDriverList() {
    return &driversList;
}

std::list<BaseCab *> *TaxiCenter::getTaxiList() {
    return &taxiCabsList;
}

std::list<TripInformation *> *TaxiCenter::getTripInfoList(){
    return &tripInformationList;
}

void TaxiCenter::assignDrivers() {
    std::list<Driver*>::iterator driverIt = driversList.begin();
    std::list<TripInformation*>::iterator tripIt = tripInformationList.begin();
    while((driverIt != driversList.end()) && (tripIt != tripInformationList.end())){
        //setting the driver id of first trip to be the first driver.
        if((*(driverIt))->getLocation()->getPoint().compare((*(tripIt))->getStart())){
            (*(tripIt))->setDriverId((*driverIt)->getId());
            //setting the driver of that trip as unavailable.
            (*(driverIt))->setAvailable(false);
            //setting the trip info of this trip as a member in the driver.
            (*(driverIt))->setTripInformation((*(tripIt)));
            //setting the has driver field in trip info as true.
            (*(tripIt))->setHasDriver(true);
            driverIt++;
            tripIt++;
        }
        else{
            driverIt++;
        }
    }
}

void TaxiCenter::getTo() {
    std::list<Driver*>::iterator driverIt = driversList.begin();
    //going through drivers list telling the unavailable ones to get to end point of their trip info.
    while(driverIt != driversList.end()){
        if(!((*(driverIt))->getAvailable())){
            (*(driverIt))->getTaxiCab()->move((*(driverIt))->getTripInformation()->getEnd());
        }
        driverIt++;
    }
}

void TaxiCenter::completeTrip() {
    assignDrivers();
    getTo();
    //marking all drivers as available again after finishing their rides.
    std::list<Driver*>::iterator driverIt = driversList.begin();
    while(driverIt != driversList.end()){
        (*(driverIt))->setAvailable(true);
        driverIt++;
    }
    //deleting all info trips that are over.
    std::list<TripInformation*>::iterator tripIt = tripInformationList.begin();
    while(tripInformationList.size()>0){
        if(tripInformationList.front()->getHasDriver()){
            delete[] tripInformationList.front();
            tripInformationList.pop_front();
        }
    }
}
void TaxiCenter::printDriverLocation(int id) {
    std::list<Driver*>::iterator driverIt = driversList.begin();
    while(driverIt != driversList.end()){
        if((*(driverIt))->getId() == id){
            Point p = (*(driverIt))->getLocation()->getPoint();
            std::cout << p << std::endl;
            break;
        }
        else{
            driverIt++;
        }
    }
}