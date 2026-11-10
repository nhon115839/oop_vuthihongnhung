#include <iostream>
#include <string>
#include <cctype>
#include <limits>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

// Lop 1: thong tin mot xe
class Vehicle {
private:
    int vehicleId;
    string vehicleType;
    int entryTime;
    int parkingDuration;
    double parkingFee;

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
                parkingDuration(0), parkingFee(0) {}

    Vehicle(int id, string type, int time, int duration)
        : vehicleId(id), vehicleType(""), entryTime(time),parkingDuration(duration), parkingFee(0) 
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
    static const int MAX_VEHICLES = 3;
    Vehicle vehicles[MAX_VEHICLES];
    int currentVehicleCount;

public:
    ParkingLot() : parkId(0), size('S'), currentVehicleCount(0) {}

    ParkingLot(int id, char lotSize)
        : parkId(id), size(static_cast<char>(toupper(static_cast<unsigned char>(lotSize)))),
          currentVehicleCount(0)  {}

    int getParkId() const 
	{ 
		return parkId; 
	}
    char getSize() const 
	{ 
		return size; 
	}
    const Vehicle& getVehicle(int i) const 
	{ 
		return vehicles[i];
	}
	int getCurrentVehicleCount() const 
	{ 
		return currentVehicleCount; 
	}
	

    int getParkingSize() const {
        if (size == 'S') return 1;
        if (size == 'M') return 2;
        return 3;
    }
	bool isFull() const
	{
		return currentVehicleCount >= getParkingSize();
	}
	
	int findVehicle(int id) const
	{
		for(int i = 0; i < currentVehicleCount; i++){
			if(vehicles[i].getVehicleId() == id)
				return i;
		}
		return -1;
	}

    bool addVehicle(const Vehicle& vehicle) {
        if(isFull() || findVehicle(vehicle.getVehicleId()) != -1){
        	return false;
		}
		vehicles[currentVehicleCount] = vehicle;
		currentVehicleCount++;
		return true;
    }

    bool deleteVehicle(int id) {
        int a = findVehicle(id);
        if(a == -1) return false;
        for(int i = a; i < currentVehicleCount - 1; i++){
        	vehicles[i] = vehicles[i+1];
		}
		currentVehicleCount--;
		vehicles[currentVehicleCount] = Vehicle();
		return true;
    }

    void displayParkingLot() const {
        cout<< "Bai do " << parkId << " | Kich thuoc: " << size
             << " | So xe: " << currentVehicleCount<< "/" << getParkingSize()<< "\n";
        if (currentVehicleCount == 0) cout<< "  Bai dang trong\n";
        for(int i = 0; i < currentVehicleCount;i++){
        	cout << " ";
        	 vehicles[i].display();
		}
    }
};

class SystemInterface {
private:
    static const int MAX_LOTS = 10;
    ParkingLot parkingLots[MAX_LOTS];
    int currentLotCount;
    
    int findLotIndex(int id) const{
    	for(int i = 0; i < currentLotCount; i++){
    		if(parkingLots[i].getParkId() == id) return i;
		}
		return -1;
	}

    void createLot() {
        if(currentLotCount == MAX_LOTS) {
            cout<< "He thong da co du 10 bai do\n";
            return;
        }
        int id;
        cout<< "Nhap ma bai do: ";
        cin >> id;
        if(isParkIdExists(id)){
        	cout << "Ma bai do trung, ma moi da duoc gan";
        	id = generateRandomID();
        	cout << id << "\n";
		}
		char lotSize;
		while(true){
        cout << "Nhap kich thuoc : ";
        cin>> lotSize;
        lotSize = static_cast<char>(toupper(static_cast<unsigned char>(lotSize)));
        if(lotSize == 'S' || lotSize == 'M' || lotSize == 'L') {
			break;
        }
        cout << "Kich thuoc khong hop le\n";
    }
    	parkingLots[currentLotCount] = ParkingLot(id, lotSize);
    	currentLotCount++;
    	cout << "Da tao bai do\n";
	}

    void addVehicle() {
    	if(currentLotCount == 0){
    		cout <<"Chua co bai do\n";
    		return;
		}
        int id, entryTime, duration;
        string type;
        cout<< "Nhap ma xe: ";
        cin >> id;
        if(isVehicleIdExists(id)) 
		{ 
			cout << "Ma xe da ton tai, ma xe moi duoc gan\n";
			id = generateRandomID(); 
			cout << id <<"\n";
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
        cin >> entryTime;
        cout<< "Nhap thoi gian do : ";
        cin >> duration;
        if(entryTime < 0 || entryTime > 23 || duration < 1 || duration > 23 || entryTime + duration > 24) {
            cout << "Gio vao hoac thoi gian khong hop le\n";
            return;
        }

        Vehicle vehicle(id, type, entryTime, duration);
        for(int i = 0; i < currentLotCount; i++){
        	if(!parkingLots[i].isFull() && parkingLots[i].addVehicle(vehicle)){
        		cout <<"Da them xe vao bai" << parkingLots[i].getParkId() << "\n";
        		return;
			}
		}
        cout<< "Khong co bai do con cho\n";
    }

    void deleteLot() {
        int id;
        cout << "Nhap ma bai do can xoa: ";
        cin >> id;
        int a = findLotIndex(id);
        if(a == -1) 
		{  
			cout << "Khong tim thay bai do\n"; 
			return; 
		}
        for(int i = a; i < currentLotCount - 1;i++){
        	parkingLots[i] = parkingLots[i+1];
		}
		currentLotCount--;
		parkingLots[currentLotCount] = ParkingLot();
        cout << "Da xoa bai do\n";
    }

    void deleteVehicle() {
        int id;
        cout << "Nhap ma xe can lay: ";
        cin >> id;
        for(int i = 0; i < currentLotCount;i++){
        	if(parkingLots[i].deleteVehicle(id)){
				cout << "Da lay xe ra khoi bai\n";
				return;
			}
		}
        cout << "Khong tim thay xe\n";
    }

    void displayAllLots() const {
        if (currentLotCount == 0) {
			cout << "Chua co bai do nao\n";
		}
        for (int i = 0; i < currentLotCount; i++){
			parkingLots[i].displayParkingLot();
		}
	}
		

    void displayLotById() {
        int id;
        cout << "Nhap ma bai do: ";
        cin >> id;
        int a = findLotIndex(id);
        if(a == -1){
        cout << "Khong tim thay bai do\n";
		}
		else{
			parkingLots[a].displayParkingLot();
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
        for(int i = 0; i < currentLotCount;i++){
        	for(int j = 0; j< parkingLots[i].getCurrentVehicleCount();j++){
        		if(parkingLots[i].getVehicle(j).getVehicleType() == type){
        			cout << "Bai" << parkingLots[i].getParkId() << ": ";
        			parkingLots[i].getVehicle(j).display();
        			found = true;
				}
			}
		}
        if(!found) cout << "Khong co xe thuoc loai nay\n";
    }

    void showFeeReport() const {
        double total[3] = {0,0,0};
        int count[3] = {0,0,0};
        cout << "Bao cao theo bai do:\n";
        for(int i = 0;  i < currentLotCount; i++){
        	double lotTotal = 0;
        	for(int j = 0; j < parkingLots[i].getCurrentVehicleCount();j++){
        		const Vehicle& vehicle = parkingLots[i].getVehicle(j);
        		lotTotal += vehicle.getParkingFee();
        		int type = vehicle.getVehicleType() == "Car" ? 0 : vehicle.getVehicleType() == "Motorcycle" ? 1 : 2;
                total[type] += vehicle.getParkingFee();
                count[type]++;
            }
            cout << "Bai " << parkingLots[i].getParkId() << ": "
                 << parkingLots[i].getCurrentVehicleCount() << " xe, tong phi "
                 << fixed << setprecision(2) << lotTotal << " VND\n";
        }
        cout << "Phi trung binh theo loai xe:\n";
        cout << "Car: " << (count[0] ? total[0] / count[0] : 0) << " VND\n";
        cout << "Motorcycle: " << (count[1] ? total[1] / count[1] : 0) << " VND\n";
        cout << "Bicycle: " << (count[2] ? total[2] / count[2] : 0) << " VND\n";
    }

public:
    SystemInterface() : currentLotCount(0) { srand(static_cast<unsigned int>(time(0))); }
    bool isParkIdExists(int id) const 
	{ 
		return findLotIndex(id) != -1; 
	}

    bool isVehicleIdExists(int id) const {
        for (int i = 0; i <currentLotCount; i++)
            if (parkingLots[i].findVehicle(id) != -1) return true;
        return false;
    }

    int generateRandomID() {
        int id;
        do { id = 1000 + rand() % 9000; }
        while (isParkIdExists(id) || isVehicleIdExists(id));
        return id;
    }

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
            cin >> choice;
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
