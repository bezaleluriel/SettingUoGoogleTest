#include "TripInformation.h"

TripInformation::TripInformation() {}

TripInformation::TripInformation(int id, int startX, int startY, int endX, int endY, int numOfPassengers,
                                 double cabTariff, int time) {
    rideId = id;
    start = Point(startX, startY);
    end = Point(endX, endY);
    numberOfPassengers = numOfPassengers;
    tariff = cabTariff;
    rideIsOver = false;
    hasDriver = false;
    startTime = time;
}

int TripInformation::getRideId() {
    return rideId;
}

void TripInformation::setRideId(int id) {
    rideId = id;
}

int TripInformation::getTotalMetersPassed() {
    return totalMetersPassed;
}

void TripInformation::setTotalMetersPassed(int metersPassed) {
    totalMetersPassed = metersPassed;
}

int TripInformation::getNumberOfPassengers() {
    return numberOfPassengers;
}

void TripInformation::setNumberOfPassengers(int numOfpassengers) {
    numberOfPassengers = numOfpassengers;
}

double TripInformation::getTariff() {
    return tariff;
}

void TripInformation::setTariff(double rideTariff) {
    tariff = rideTariff;
}

Point TripInformation::getStart() {
    return start;
}

void TripInformation::setStart(Point startPoint) {
    start = startPoint;
}

Point TripInformation::getEnd() {
    return end;
}

void TripInformation::setEnd(Point endPoint) {
    end = endPoint;
}

void TripInformation::setRideIsOver(bool b) {
    rideIsOver = b;
}

bool TripInformation::getRideIsOver() {
    return rideIsOver;
}

int TripInformation::getDriverId() {
    return driverId;
}

void TripInformation::setDriverId(int driverId) {
    TripInformation::driverId = driverId;
}

bool TripInformation::getHasDriver() {
    return hasDriver;
}

void TripInformation::setHasDriver(bool b) {
    hasDriver = b;
}

int TripInformation::getStartTime()  {
    return startTime;
}

void TripInformation::setStartTime(int startTime) {
    TripInformation::startTime = startTime;
}
