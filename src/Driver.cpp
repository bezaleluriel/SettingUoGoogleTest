#include "Driver.h"

Driver::Driver() {}


Driver::Driver(int driverId, int driverAge, char status, int experience, int cabVehicleId) {
    id = driverId;
    age = driverAge;
    yearsOfExperience = experience;
    vehicleId = cabVehicleId;
    switch (status) {
        case 'S' :
            maritalStatus = Single;
            break;
        case 'M' :
            maritalStatus = Married;
            break;
        case 'W' :
            maritalStatus = Widowed;
            break;
        case 'D' :
            maritalStatus = Divorced;
            break;
        default :
            break;
    }
    available = true;
    averageSatisfaction = 0;
    numberOfCustomers = 0;
    taxiCab = NULL;
    tripInformation = NULL;
}

int Driver::getId() {
    return id;
}

int Driver::getAge() {
    return age;
}

void Driver::setAge(int driverAge) {
    age = driverAge;
}

int Driver::getYearsOfExperience() {
    return yearsOfExperience;
}

void Driver::setYearsOfExperience(int years) {
    yearsOfExperience = years;
}

double Driver::getAverageSatisfaction() {
    return averageSatisfaction;
}

void Driver::setAverageSatisfaction(double average) {
    averageSatisfaction = average;
}

bool Driver::getAvailable() {
    return available;
}

void Driver::setAvailable(bool b) {
    available = b;
}

BaseCab* Driver::getTaxiCab() {
    return taxiCab;
}

void Driver::setTaxiCab(BaseCab *taxi) {
    taxiCab = taxi;
}

MaritalStatus Driver::getMaritalStatus() {
    return maritalStatus;
}

void Driver::setMaritalStatus(MaritalStatus driverMaritalStatus) {
    maritalStatus = driverMaritalStatus;
}

int Driver::getNumberOfCustomers() {
    return numberOfCustomers;
}

void Driver::setNumberOfCustomers(int numOfCustomers) {
    numberOfCustomers = numOfCustomers;
}

GridNode *Driver::getLocation() {
    return taxiCab->getLocation();
}

int Driver::getVehicleId() {
    return vehicleId;
}

void Driver::setVehicleId(int id) {
    vehicleId = id;
}

TripInformation *Driver::getTripInformation() {
    return tripInformation;
}

void Driver::setTripInformation(TripInformation *tripInformation) {
    Driver::tripInformation = tripInformation;
}
