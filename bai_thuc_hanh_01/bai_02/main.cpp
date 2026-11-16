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
    int id;
    do {
        id = rand() % 9000 + 1000;   // 1000..9999
    } while (isParkIDExists(id) || isVehicleIDExists(id));
    return id;
}

int SystemInterface::readInt(const string& prompt, int lo, int hi) const {
    int x;
    while (true) {
        cout << prompt;
        cin >> x;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  [Loi] Vui long nhap mot so nguyen!\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (x < lo || x > hi) {
            cout << "  [Loi] Gia tri phai trong khoang " << lo << " - " << hi << "!\n";
            continue;
        }
        return x;
    }
}

char SystemInterface::readSize(const string& prompt) const {
    char c;
    while (true) {
        cout << prompt;
        cin >> c;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        c = (char)toupper(c);
        if (c == 'S' || c == 'M' || c == 'L') return c;
        cout << "  [Loi] Chi nhap S, M hoac L!\n";
    }
}

string SystemInterface::readType(const string& prompt) const {
    string s;
    while (true) {
        cout << prompt;
        cin >> s;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (s == "Car" || s == "Motorcycle" || s == "Bicycle") return s;
        cout << "  [Loi] Chi nhap Car, Motorcycle hoac Bicycle!\n";
    }
}


void SystemInterface::createLot() {
    if (currentLotCount >= MAX_LOTS) {
        cout << "He thong da dat toi da " << MAX_LOTS << " bai do!\n";
        return;
    }
    int id = readInt("Ma bai: ", 1, 999999);
    if (isParkIDExists(id)) {
        id = generateRandomID();
        cout << "  [Canh bao] ID bai do bi trung! Tu dong gan ID moi: " << id << "\n";
    }
    char sz = readSize("Kich thuoc (S/M/L): ");
    parkingLots[currentLotCount] = ParkingLot(id, sz);
    ++currentLotCount;
    cout << "Da tao bai " << id << "\n";
}
void SystemInterface::addVehicleToLot() {
    if (currentLotCount == 0) {
        cout << "Chua co bai do nao! Hay tao bai truoc.\n";
        return;
    }
    int id = readInt("Ma xe: ", 1, 999999);
    if (isVehicleIDExists(id)) {
        id = generateRandomID();
        cout << "  [Canh bao] ID xe bi trung! Tu dong gan ID moi: " << id << "\n";
    }
    string type = readType("Loai (Car/Motorcycle/Bicycle): ");
    int entry = readInt("Gio vao (0-23): ", 0, 23);
    int dur = readInt("Thoi luong (1-23): ", 1, 23);

    Vehicle v(id, type, entry, dur);
for (int i = 0; i < currentLotCount; ++i) {
        if (!parkingLots[i].isFull()) {
            parkingLots[i].addVehicle(v);
            cout << "Da them xe " << id << " vao bai " << parkingLots[i].getParkID()
                 << " | Phi: $" << fixed << setprecision(2) << v.getParkingFee() << "\n";
            return;
        }
    }
    cout << "Tat ca cac bai do da day!\n";
}


void SystemInterface::deleteLot() {
    int id = readInt("Ma bai can xoa: ", 1, 999999);
    int idx = findLotIndex(id);
    if (idx == -1) {
        cout << "Khong tim thay bai " << id << "\n";
        return;
    }
    for (int i = idx; i < currentLotCount - 1; ++i)
        parkingLots[i] = parkingLots[i + 1];
    --currentLotCount;
    cout << "Da xoa bai " << id << "\n";
}


void SystemInterface::takeVehicleOut() {
    int id = readInt("Ma xe can lay ra: ", 1, 999999);
    for (int i = 0; i < currentLotCount; ++i) {
        if (parkingLots[i].removeVehicle(id)) {
            cout << "Da lay xe " << id << " ra khoi bai " << parkingLots[i].getParkID() << "\n";
            return;
        }
    }
    cout << "Khong tim thay xe\n";
}


void SystemInterface::showAllLots() const {
    if (currentLotCount == 0) { cout << "Chua co bai do nao.\n"; return; }
    for (int i = 0; i < currentLotCount; ++i)
        parkingLots[i].displayLotInfo();
}


void SystemInterface::showLotByID() const {
    int id = readInt("Ma bai: ", 1, 999999);
    int idx = findLotIndex(id);
    if (idx == -1) cout << "Khong tim thay bai " << id << "\n";
    else parkingLots[idx].displayLotInfo();
}


void SystemInterface::listByType() const {
    string type = readType("Loai xe (Car/Motorcycle/Bicycle): ");
    bool found = false;
    for (int i = 0; i < currentLotCount; ++i) {
        const ParkingLot& lot = parkingLots[i];
        for (int j = 0; j < lot.getCurrentVehicleCount(); ++j) {
            if (lot.getVehicleAt(j).getVehicleType() == type) {
                cout << "Bai " << lot.getParkID() << ":\n";
                lot.getVehicleAt(j).display();
                found = true;
            }
        }
    }
    if (!found) cout << "Khong co xe loai " << type << "\n";
}


void SystemInterface::averageFeeReport() const {
    const string types[3] = {"Car", "Motorcycle", "Bicycle"};
    cout << "--- Toan he thong ---\n";
    for (int t = 0; t < 3; ++t) {
        int cnt = 0; double sum = 0;
        for (int i = 0; i < currentLotCount; ++i)
            for (int j = 0; j < parkingLots[i].getCurrentVehicleCount(); ++j)
                if (parkingLots[i].getVehicleAt(j).getVehicleType() == types[t]) {
                    ++cnt; sum += parkingLots[i].getVehicleAt(j).getParkingFee();
                }
        cout << types[t] << ": ";
        if (cnt == 0) cout << "khong co xe\nelse cout << cnt << " xe | TB: $" << fixed << setprecision(2) << sum / cnt << "\n";
    }
    cout << "--- Theo tung bai ---\n";
    for (int i = 0; i < currentLotCount; ++i) {
        cout << "Bai " << parkingLots[i].getParkID() << ":\n";
        for (int t = 0; t < 3; ++t) {
            int cnt = 0; double sum = 0;
            for (int j = 0; j < parkingLots[i].getCurrentVehicleCount(); ++j)
                if (parkingLots[i].getVehicleAt(j).getVehicleType() == types[t]) {
                    ++cnt; sum += parkingLots[i].getVehicleAt(j).getParkingFee();
                }
            cout << "  " << types[t] << ": ";
            if (cnt == 0) cout << "khong co xe\n";
            else cout << cnt << " xe | TB: $" << fixed << setprecision(2) << sum / cnt << "\n";
        }
    }
}

void SystemInterface::runMenu() {
    int choice;
    do {
        cout << "\n===== QUAN LY BAI DO XE =====\n";
        cout << "1. Tao bai do\n";
        cout << "2. Them xe\n";
        cout << "3. Xoa bai do\n";
        cout << "4. Lay xe ra\n";
        cout << "5. Hien thi tat ca bai do\n";
        cout << "6. Hien thi xe theo bai\n";
        cout << "7. Liet ke xe theo loai\n";
        cout << "8. Bao cao phi trung binh\n";
        cout << "9. Thoat\n";
        choice = readInt("Chon: ", 1, 9);

        switch (choice) {
            case 1: createLot();        break;
            case 2: addVehicleToLot();  break;
            case 3: deleteLot();        break;
            case 4: takeVehicleOut();   break;
            case 5: showAllLots();      break;
            case 6: showLotByID();      break;
            case 7: listByType();       break;
            case 8: averageFeeReport(); break;
            case 9: cout << "Tam biet!\n"; break;
        }
    } while (choice != 9);
}

int main() {
    srand((unsigned)time(0));
    SystemInterface sys;
    sys.runMenu();
    return 0;
}";
