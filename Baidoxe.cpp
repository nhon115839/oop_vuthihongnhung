#include <iostream>
#include <string>
#include <cctype>
#include <limits>
#include <iomanip>
using namespace std;

// Lop 1: thong tin mot xe
class Vehicle {
private:
    int vehicleId;
    string vehicleType;
    int entryTime;
    int parkingDuration;
    double parkingFee;
    bool isOccupied;

    string toLower(string text) const {
        for (int i = 0; i < static_cast<int>(text.length()); ++i) {
            text[i] = static_cast<char>(tolower(static_cast<unsigned char>(text[i])));
        }
        return text;
    }

    bool isPeakHour(int hour) const {
        return (hour >= 6 && hour < 10) || (hour >= 15 && hour < 19);
    }

public:
    Vehicle() : vehicleId(0), vehicleType(""), entryTime(0),
                parkingDuration(0), parkingFee(0), isOccupied(false) {}

    Vehicle(int id, string type, int time, int duration)
        : vehicleId(id), vehicleType(""), entryTime(time),parkingDuration(duration), parkingFee(0), isOccupied(true) 
		{
        	setVehicleType(type);
        	calculateFee();
    	}

    int getVehicleId() const 
	{ 
		return vehicleId; 
	}
    string getVehicleType() const 
	{ 
		return vehicleType; 
	}
    int getEntryTime() const 
	{ 
		return entryTime; 	
	}
    int getParkingDuration() const 
	{ 
		return parkingDuration; 
	}
    double getParkingFee() const 
	{ 
		return parkingFee; 
	}
    bool getIsOccupied() const 
	{ 
		return isOccupied; 
	}

    void setVehicleId(int id) { vehicleId = id; }

    void setVehicleType(string type) {
        string lower = toLower(type);
        if (lower == "car") vehicleType = "Car";
        else if (lower == "motorcycle") vehicleType = "Motorcycle";
        else if (lower == "bicycle") vehicleType = "Bicycle";
        else vehicleType = "";
    }

    void setEntryTime(int time) {
        if (time >= 0 && time <= 23) entryTime = time;
    }

    void setParkingDuration(int duration) {
        if (duration >= 1 && duration <= 23) parkingDuration = duration;
    }

    void setParkingFee(double fee) 
	{ 
		parkingFee = fee; 
	}
    void setIsOccupied(bool value) { 
		isOccupied = value; 
	}

    void calculateFee() {
        double rate = 0;
        if (vehicleType == "Car") rate = 6.0;
        else if (vehicleType == "Motorcycle") rate = 4.0;
        else if (vehicleType == "Bicycle") rate = 2.0;

        double total = 0;
        for (int hour = 0; hour < parkingDuration; ++hour) {
            if (hour < 2) {
                total += rate * (isPeakHour(entryTime) ? 1.30 : 0.95);
            } else {
                total += rate * 0.90;
            }
        }
        parkingFee = total;
    }

    void display() const {
        if (!isOccupied) return;
        cout << "Ma xe: " << vehicleId
             << " | Loai xe: " << vehicleType
             << " | Gio vao: " << entryTime << ":00"
             << " | So gio do: " << parkingDuration
             << " | Phi: " << fixed << setprecision(2) << parkingFee << " VND\n";
    }
};

class ParkingLot {
private:
    int parkId;
    char size;
    Vehicle vehicle1;
    Vehicle vehicle2;
    Vehicle vehicle3;
    bool hasVehicle1;
    bool hasVehicle2;
    bool hasVehicle3;

public:
    ParkingLot() : parkId(0), size('S'), hasVehicle1(false), hasVehicle2(false), hasVehicle3(false) {}

    ParkingLot(int id, char lotSize)
        : parkId(id), size(static_cast<char>(toupper(static_cast<unsigned char>(lotSize)))),
          hasVehicle1(false), hasVehicle2(false), hasVehicle3(false) {}

    int getParkId() const 
	{ 
		return parkId; 
	}
    char getSize() const 
	{ 
		return size; 
	}
    bool getHasVehicle1() const 
	{ 
		return hasVehicle1; 
	}
    bool getHasVehicle2() const 
	{ 
		return hasVehicle2; 
	}
    bool getHasVehicle3() const 
	{ 
		return hasVehicle3; 
	}
    const Vehicle& getVehicle1() const 
	{ 
		return vehicle1; 
	}
    const Vehicle& getVehicle2() const 
	{ 
		return vehicle2; 
	}
    const Vehicle& getVehicle3() const 
	{ 
		return vehicle3; 
	}

    int getParkingSize() const {
        if (size == 'S') return 1;
        if (size == 'M') return 2;
        return 3;
    }

    int getVehicleCount() const {
        return (hasVehicle1 ? 1 : 0) + (hasVehicle2 ? 1 : 0) + (hasVehicle3 ? 1 : 0);
    }

    bool addVehicle(const Vehicle& vehicle) {
        if (hasVehicle1 && vehicle1.getVehicleId() == vehicle.getVehicleId()) return false;
        if (hasVehicle2 && vehicle2.getVehicleId() == vehicle.getVehicleId()) return false;
        if (hasVehicle3 && vehicle3.getVehicleId() == vehicle.getVehicleId()) return false;

        if (!hasVehicle1) {
            vehicle1 = vehicle;
            hasVehicle1 = true;
            return true;
        }
        if (getParkingSize() >= 2 && !hasVehicle2) {
            vehicle2 = vehicle;
            hasVehicle2 = true;
            return true;
        }
        if (getParkingSize() >= 3 && !hasVehicle3) {
            vehicle3 = vehicle;
            hasVehicle3 = true;
            return true;
        }
        return false;
    }

    bool deleteVehicle(int id) {
        if (hasVehicle1 && vehicle1.getVehicleId() == id) {
            vehicle1 = Vehicle(); hasVehicle1 = false; 
			return true;
        }
        if (hasVehicle2 && vehicle2.getVehicleId() == id) {
            vehicle2 = Vehicle(); hasVehicle2 = false; 
			return true;
        }
        if (hasVehicle3 && vehicle3.getVehicleId() == id) {
            vehicle3 = Vehicle(); hasVehicle3 = false; 
			return true;
        }
        return false;
    }

    void displayParkingLot() const {
        cout<< "Bai do " << parkId << " | Kich thuoc: " << size
             << " | So xe: " << getVehicleCount()<< "/" << getParkingSize()<< "\n";
        if (getVehicleCount() == 0) cout<< "  Bai dang trong\n";
        if (hasVehicle1) 
		{ 
			 cout << "  "; vehicle1.display(); 
		}
        if (hasVehicle2) 
		{ 
			cout<< "  "; vehicle2.display(); 
		}
        if (hasVehicle3) 
		{ 
			cout << "  "; vehicle3.display(); 
		}
    }
};

class SystemInterface {
private:
    ParkingLot parkingLot1;
    ParkingLot parkingLot2;
    ParkingLot parkingLot3;
    bool hasLot1;
    bool hasLot2;
    bool hasLot3;

    void clearInput() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    bool lotIdExists(int id) const {
        return (hasLot1 && parkingLot1.getParkId() == id) ||(hasLot2 && parkingLot2.getParkId() == id) || (hasLot3 && parkingLot3.getParkId() == id);
    }

    bool vehicleIdExistsInLot(const ParkingLot& lot, int id) const {
        return (lot.getHasVehicle1() && lot.getVehicle1().getVehicleId() == id) ||(lot.getHasVehicle2() && lot.getVehicle2().getVehicleId() == id) || (lot.getHasVehicle3() && lot.getVehicle3().getVehicleId() == id);
    }

    bool vehicleIdExists(int id) const {
        return (hasLot1 && vehicleIdExistsInLot(parkingLot1, id)) ||(hasLot2 && vehicleIdExistsInLot(parkingLot2, id)) || (hasLot3 && vehicleIdExistsInLot(parkingLot3, id));
    }

    void createLot() {
        if(hasLot1 && hasLot2 && hasLot3) {
            cout<< "He thong da co du 3 bai do\n";
            return;
        }
        int id;
        char lotSize;
        cout<< "Nhap ma bai do: ";
        if(!(cin >> id)) 
		{ 
			clearInput(); 
			cout << "Du lieu khong hop le\n"; return; 
		}
        if(lotIdExists(id)) 
		{ 
			cout<< "Ma bai do da ton tai\n"; 
			return; 
		}
        cout << "Nhap kich thuoc : ";
        if(!(cin>> lotSize)) 
		{ 
			clearInput(); 
			cout << "Du lieu khong hop le\n";
			return;
		}
        lotSize = static_cast<char>(toupper(static_cast<unsigned char>(lotSize)));
        if(lotSize != 'S' && lotSize != 'M' && lotSize != 'L') {
            cout << "Kich thuoc khong hop le\n";
            return;
        }
        if(!hasLot1) 
		{ 
			parkingLot1 = ParkingLot(id, lotSize); 
			hasLot1 = true; 
		}
        else if(!hasLot2) 
		{ 
			parkingLot2 = ParkingLot(id, lotSize); 
			hasLot2 = true; 
		}
        else 
		{ 
			parkingLot3 = ParkingLot(id, lotSize); 
			hasLot3 = true; 
		}
        cout << "Da tao bai do\n";
    }

    void addVehicle() {
        int id, entryTime, duration;
        string type;
        cout<< "Nhap ma xe: ";
        if(!(cin >> id)) 
		{ 
			clearInput(); 
			cout << "Du lieu khong hop le\n"; 
			return; 
		}
        if(vehicleIdExists(id)) 
		{ 
			cout << "Ma xe da ton tai\n"; 
			return; 
		}
        cout << "Nhap loai xe : ";
        cin>> type;
        Vehicle vh;
        vh.setVehicleType(type);
        if(vh.getVehicleType() == "") 
		{ 
			cout << "Loai xe khong hop le\n"; 
			return; 
		}

        cout << "Nhap gio vao : ";
        if(!(cin >> entryTime)) { 
			clearInput(); 
			cout << "Du lieu khong hop le\n"; 
			return; 
			}
        cout<< "Nhap thoi gian do : ";
        if(!(cin>> duration)) 
		{ 
			clearInput(); 
			cout << "Du lieu khong hop le\n"; 
			return; 
		}
        if(entryTime < 0 || entryTime > 23 || duration < 1 || duration > 23 || entryTime + duration > 24) {
            cout << "Gio vao hoac thoi gian khong hop le\n";
            return;
        }

        Vehicle vehicle(id, type, entryTime, duration);
        if(hasLot1 && parkingLot1.addVehicle(vehicle)) {
            cout << "Da them xe vao bai " << parkingLot1.getParkId() << "\n";
            return;
        }
        if(hasLot2 && parkingLot2.addVehicle(vehicle)) {
            cout << "Da them xe vao bai " << parkingLot2.getParkId() << "\n";
            return;
        }
        if(hasLot3 && parkingLot3.addVehicle(vehicle)) {
            cout << "Da them xe vao bai " << parkingLot3.getParkId() << "\n";
            return;
        }
        cout<< "Khong co bai do con cho\n";
    }

    void deleteLot() {
        int id;
        cout << "Nhap ma bai do can xoa: ";
        if(!(cin >> id)) 
		{ 
			clearInput(); 
			cout << "Du lieu khong hop le\n"; 
			return; 
		}
        if(hasLot1 && parkingLot1.getParkId() == id) 
		{ 
			parkingLot1 = ParkingLot(); 
			hasLot1 = false; 
			cout << "Da xoa bai do\n"; 
			return; 
		}
        if(hasLot2 && parkingLot2.getParkId() == id) 
		{ 
			parkingLot2 = ParkingLot(); 
			hasLot2 = false; 
			cout << "Da xoa bai do\n"; 
			return; 
		}
        if(hasLot3 && parkingLot3.getParkId() == id) 
		{ 
			parkingLot3 = ParkingLot(); 
			hasLot3 = false; 
			cout << "Da xoa bai do\n"; 
			return; 
		}
        cout << "Khong tim thay bai do\n";
    }

    void deleteVehicle() {
        int id;
        cout << "Nhap ma xe can lay: ";
        if(!(cin >> id)) 
		{ 
			clearInput(); 
			cout << "Du lieu khong hop le\n"; 
			return; 
		}
        if((hasLot1 && parkingLot1.deleteVehicle(id)) || (hasLot2 && parkingLot2.deleteVehicle(id)) || (hasLot3 && parkingLot3.deleteVehicle(id))) 
		cout << "Da lay xe ra khoi bai\n";
        else cout << "Khong tim thay xe\n";
    }

    void displayAllLots() const {
        if(!hasLot1 && !hasLot2 && !hasLot3) 
		{ 
			cout << "Chua co bai do nao\n"; 
			return; 
		}
        if(hasLot1) parkingLot1.displayParkingLot();
        if(hasLot2) parkingLot2.displayParkingLot();
        if(hasLot3) parkingLot3.displayParkingLot();
    }

    void displayLotById() {
        int id;
        cout << "Nhap ma bai do: ";
        if(!(cin >> id)) 
		{ 
			clearInput(); 
			cout << "Du lieu khong hop le\n"; 
			return; 
		}
        if(hasLot1 && parkingLot1.getParkId() == id) 
		{ 
			parkingLot1.displayParkingLot(); 
			return; 
		}
        if(hasLot2 && parkingLot2.getParkId() == id) 
		{ 
			parkingLot2.displayParkingLot(); 
			return; 
		}
        if(hasLot3 && parkingLot3.getParkId() == id) 
		{ 
			parkingLot3.displayParkingLot(); 
			return; 
		}
        cout << "Khong tim thay bai do\n";
    }

    void showVehicleType(const ParkingLot& pl, bool occupied, const Vehicle& vehicle,
                           const string& type, bool& found) const {
        if (occupied && vehicle.getVehicleType() == type) {
            cout << "Bai " << pl.getParkId() << ": ";
            vehicle.display();
            found = true;
        }
    }

    void listVehiclesByType() {
        string type;
        cout << "Nhap loai xe: ";
        cin >> type;
        Vehicle vh;
        vh.setVehicleType(type);
        type = vh.getVehicleType();
        if (type == "") 
		{ 
			cout<< "Loai xe khong hop le\n";
			return; 
		}

        bool found = false;
        if(hasLot1) {
            showVehicleType(parkingLot1, parkingLot1.getHasVehicle1(), parkingLot1.getVehicle1(), type, found);
            showVehicleType(parkingLot1, parkingLot1.getHasVehicle2(), parkingLot1.getVehicle2(), type, found);
            showVehicleType(parkingLot1, parkingLot1.getHasVehicle3(), parkingLot1.getVehicle3(), type, found);
        }
        if(hasLot2) {
            showVehicleType(parkingLot2, parkingLot2.getHasVehicle1(), parkingLot2.getVehicle1(), type, found);
            showVehicleType(parkingLot2, parkingLot2.getHasVehicle2(), parkingLot2.getVehicle2(), type, found);
            showVehicleType(parkingLot2, parkingLot2.getHasVehicle3(), parkingLot2.getVehicle3(), type, found);
        }
        if(hasLot3) {
            showVehicleType(parkingLot3, parkingLot3.getHasVehicle1(), parkingLot3.getVehicle1(), type, found);
            showVehicleType(parkingLot3, parkingLot3.getHasVehicle2(), parkingLot3.getVehicle2(), type, found);
            showVehicleType(parkingLot3, parkingLot3.getHasVehicle3(), parkingLot3.getVehicle3(), type, found);
        }
        if(!found) cout << "Khong co xe thuoc loai nay\n";
    }

    void addFeeToReport(bool occupied, const Vehicle& vehicle,  double& lotTotal, int& lotCount, double& carTotal, int& carCount, double& motorcycleTotal, int& motorcycleCount,
                        double& bicycleTotal, int& bicycleCount) const {
        if(!occupied) return;
        double fee = vehicle.getParkingFee();
        lotTotal += fee;
        ++lotCount;
        if (vehicle.getVehicleType() == "Car") 
		{ 
			carTotal += fee; ++carCount; 
		}
        else if (vehicle.getVehicleType() == "Motorcycle") 
		{ 
			motorcycleTotal += fee; ++motorcycleCount; 
		}
        else if (vehicle.getVehicleType() == "Bicycle") 
		{ 
			bicycleTotal += fee; ++bicycleCount; 
		}
    }

    void showOneLotReport(const ParkingLot& lot, double& carTotal, int& carCount, double& motorcycleTotal, int& motorcycleCount, double& bicycleTotal, int& bicycleCount) const {
        double lotTotal = 0;
        int lotCount = 0;
        addFeeToReport(lot.getHasVehicle1(), lot.getVehicle1(), lotTotal, lotCount, carTotal, carCount, motorcycleTotal, motorcycleCount, bicycleTotal, bicycleCount);
        addFeeToReport(lot.getHasVehicle2(), lot.getVehicle2(), lotTotal, lotCount, carTotal, carCount, motorcycleTotal, motorcycleCount, bicycleTotal, bicycleCount);
        addFeeToReport(lot.getHasVehicle3(), lot.getVehicle3(), lotTotal, lotCount, carTotal, carCount, motorcycleTotal, motorcycleCount, bicycleTotal, bicycleCount);
        cout<< "Bai " << lot.getParkId() << ": " << lotCount<< " xe, tong phi "<< fixed<< setprecision(2)<< lotTotal << " VND\n";
    }

    void showFeeReport() const {
        double carTotal = 0, motorcycleTotal = 0, bicycleTotal = 0;
        int carCount = 0, motorcycleCount = 0, bicycleCount = 0;
        cout << "Bao cao theo bai do:\n";
        if(hasLot1) showOneLotReport(parkingLot1, carTotal, carCount, motorcycleTotal, motorcycleCount, bicycleTotal, bicycleCount);
        if(hasLot2) showOneLotReport(parkingLot2, carTotal, carCount, motorcycleTotal, motorcycleCount, bicycleTotal, bicycleCount);
        if(hasLot3) showOneLotReport(parkingLot3, carTotal, carCount, motorcycleTotal, motorcycleCount, bicycleTotal, bicycleCount);
        cout << "Phi trung binh theo loai xe:\n";
        cout << "Car: "<<(carCount ? carTotal / carCount : 0)<< " VND\n";
        cout << "Motorcycle: "<<(motorcycleCount ? motorcycleTotal / motorcycleCount : 0) << " VND\n";
        cout << "Bicycle: "<< (bicycleCount ? bicycleTotal / bicycleCount : 0)<< " VND\n";
    }

public:
    SystemInterface() : hasLot1(false), hasLot2(false), hasLot3(false) {}

    void Run() {
        int choice = 0;
        do{
            cout << "\n QUAN LY BAI DO XE  \n"
                 << "1. Tao bai do moi\n"
                 << "2. Them xe vao bai do\n"
                 << "3. Xoa bai do\n"
                 << "4. Lay xe ra khoi bai\n"
                 << "5. Hien thi tat ca bai do\n"
                 << "6. Hien thi xe theo bai do\n"
                 << "7. Liet ke xe theo loai\n"
                 << "8. Bao cao phi do xe\n"
                 << "9. Thoat\nChon: ";
            if(!(cin >> choice)) {
                clearInput();
                cout << "Vui long nhap tu 1 den 9\n";
                continue;
            }
            switch(choice) {
                case 1: createLot(); break;
                case 2: addVehicle(); break;
                case 3: deleteLot(); break;
                case 4: deleteVehicle(); break;
                case 5: displayAllLots(); break;
                case 6: displayLotById(); break;
                case 7: listVehiclesByType(); break;
                case 8: showFeeReport(); break;
                case 9: cout << "Da thoat chuong trinh\n"; break;
                default: cout << "Lua chon khong hop le\n";
            }
        } while(choice != 9);
    }
};

int main() {
    SystemInterface s;
    s.Run();
    return 0;
}
