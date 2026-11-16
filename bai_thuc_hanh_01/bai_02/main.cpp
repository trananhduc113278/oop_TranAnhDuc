#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <cstdlib>
#include <ctime>
using namespace std;

class Vehicle {
private:
    int vehicleID;
    string vehicleType;
    int entryTime;
    int parkingDuration;
    double parkingFee;

public:
    Vehicle();
    Vehicle(int id, string type, int entry, int duration);

    int getVehicleID() const;
    string getVehicleType() const;
    int getEntryTime() const;
    int getParkingDuration() const;
    double getParkingFee() const;

    void setVehicleID(int id);
    void setVehicleType(string type);
    void setEntryTime(int entry);
    void setParkingDuration(int duration);

    double calculateFee();
    void display() const;
};

Vehicle::Vehicle()
    : vehicleID(0), vehicleType(""), entryTime(0), parkingDuration(0), parkingFee(0) {}

Vehicle::Vehicle(int id, string type, int entry, int duration)
    : vehicleID(id), vehicleType(type), entryTime(entry), parkingDuration(duration), parkingFee(0) {
    calculateFee();
}

int Vehicle::getVehicleID() const { return vehicleID; }
string Vehicle::getVehicleType() const { return vehicleType; }
int Vehicle::getEntryTime() const { return entryTime; }
int Vehicle::getParkingDuration() const { return parkingDuration; }
double Vehicle::getParkingFee() const { return parkingFee; }

void Vehicle::setVehicleID(int id) { vehicleID = id; }
void Vehicle::setVehicleType(string type) { vehicleType = type; calculateFee(); }
void Vehicle::setEntryTime(int entry) { entryTime = entry; calculateFee(); }
void Vehicle::setParkingDuration(int duration) { parkingDuration = duration; calculateFee(); }

double Vehicle::calculateFee() {
    double rate = (vehicleType == "Car") ? 6.0 : (vehicleType == "Motorcycle") ? 4.0 : 2.0;
    bool peak = (entryTime >= 6 && entryTime <= 9) || (entryTime >= 15 && entryTime <= 18);
    double total = 0;
    for (int h = 0; h < parkingDuration; ++h) {
        if (h < 2) total += rate * (peak ? 1.30 : 0.95);
        else       total += rate * 0.90;
    }
    parkingFee = total;
    return parkingFee;
}

void Vehicle::display() const {
    cout << "    ID: " << vehicleID << " | " << vehicleType
         << " | " << entryTime << "h | " << parkingDuration << "h"
         << " | Phi: $" << fixed << setprecision(2) << parkingFee << "\n";
}


class ParkingLot {
private:
    int parkID;
    char size;
    static const int MAX_VEHICLES = 3;
    Vehicle vehicles[MAX_VEHICLES];
    int currentVehicleCount;

    int capacity() const;   // suc chua theo size (S=1, M=2, L=3)

public:
    ParkingLot();
    ParkingLot(int id, char sz);

    int getParkID() const;
    char getSize() const;
    int getCurrentVehicleCount() const;
    const Vehicle& getVehicleAt(int index) const;

    bool isFull() const;
    bool addVehicle(const Vehicle& v);
    bool removeVehicle(int vID);
