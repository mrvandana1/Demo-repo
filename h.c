#include<bits/stdc++.h>
using namespace std;

// Forward declarations
class RentalTransaction;
class Vehicle;
class Car;
class Truck;
class Bicycle;
class Drone;
class Customer;
class VehicleManagement;


// Base class representing a vehicle
class Vehicle {
protected:
    int vehicleId;
    string brand;
    double price;
    double rentalCost;

public:

    virtual ~Vehicle() = default;

    int getVehicleId() {
        return vehicleId;
    }

    string getBrand() {
        return brand;
    }

    double getPrice() {
        return price;
    }

    double getRentalCost() {
        return rentalCost;
    }
};

// Class representing a car, inherits from Vehicle
class Car : public Vehicle {
private:
    string type;
    string fuel;
    string transmission;

public:
    Car(int id, string b, double pr, double rental, string ty, string fu, string tr) : type(ty), fuel(fu), transmission(tr) {
        vehicleId = id;
        brand = b;
        price = pr;
        rentalCost = rental;
    }
    void displayDetails() {
        cout << "Car - ID: " << vehicleId << ", Brand: " << brand << ", Price: " << fixed << setprecision(2) << price
             << ", Rental Cost: " << static_cast<int>(rentalCost) << "/day, Type: " << type << ", Fuel: " << fuel
             << ", Transmission: " << transmission << endl;
    }
};

// Class representing a truck, inherits from Vehicle
class Truck : public Vehicle {
private:
    double cargoCapacity;
    double bedLength;
    int numAxles;
    double fuelEfficiency;

public:
    Truck(int id, string b, double pr, double rental, double ca, double bed, int num, double fuel)
        : cargoCapacity(ca), bedLength(bed), numAxles(num), fuelEfficiency(fuel) {
        vehicleId = id;
        brand = b;
        price = pr;
        rentalCost = rental;
    }

    double getCargoCapacity() {
        return cargoCapacity;
    }
    void displayDetails() {
        cout << "Truck - ID: " << vehicleId << ", Brand: " << brand << ", Price: " << fixed << setprecision(2) << price
             << ", Rental Cost: " << static_cast<int>(rentalCost)  << "/day, Cargo Capacity: " << cargoCapacity
             << " kg, Bed Length: " << bedLength << " m, Axles: " << numAxles << ", Fuel Efficiency: " << fuelEfficiency
             << " miles/gallon" << endl;
    }
};

// Class representing a bicycle, inherits from Vehicle
class Bicycle : public Vehicle {
private:
    string type;
    string frame;
    int numGears;

public:
    Bicycle(int id, string b, double pr, double rental, string ty, string fr, int num)
        : type(ty), frame(fr), numGears(num) {
        vehicleId = id;
        brand = b;
        price = pr;
        rentalCost = rental;
    }
    void displayDetails() {
        cout << "Bicycle - ID: " << vehicleId << ", Brand: " << brand << ", Price: " << fixed << setprecision(2) << price
             << ", Rental Cost: " << static_cast<int>(rentalCost) << "/day, Type: " << type << ", Frame: " << frame
             << ", Gears: " << numGears << endl;
    }
};

// Class representing a drone, inherits from Vehicle
class Drone : public Vehicle {
private:
    double maxAltitude;
    double flyingTime;
    int camResolution;

public:
    Drone(int id, string b, double pr, double rental, double max, double fly, int cam)
        : maxAltitude(max), flyingTime(fly), camResolution(cam) {
        vehicleId = id;
        brand = b;
        price = pr;
        rentalCost = rental;
    }
    void displayDetails() {
        cout << "Drone - ID: " << vehicleId << ", Brand: " << brand << ", Price: " << fixed << setprecision(2) << price
             << ", Rental Cost: " << static_cast<int>(rentalCost)  << "/day, Max Altitude: " << maxAltitude
             << " m, Flight time: " << flyingTime << " min, Camera Resolution: " << camResolution << " MP" << endl;
    }
};
// Class representing a rental transaction
class RentalTransaction {
private:
    int vehId;
    int duration;
    string brand;
    int rentalCost;

public:
    RentalTransaction(int vehId, int duration, string brand, int rentalCost) : vehId(vehId), duration(duration), brand(brand), rentalCost(rentalCost) {}

    string getBrand() {
        return brand;
    }

    int getVehId() {
        return vehId;
    }

    int getDuration() {
        return duration;
    }

    int getRentalCost() {
        return rentalCost;
    }
};


// Class representing a customer
class Customer {
private:
    int customerId;
    vector<RentalTransaction*> rentedVehicles;

public:
    Customer(int custId) : customerId(custId) {}

    int getCustomerId() {
        return customerId;
    }

    void addTransaction(RentalTransaction* transaction) {
        rentedVehicles.push_back(transaction);
    }
    // Display method to print customer addition
    void display() {
        cout << "Customer " << this->getCustomerId()<< " added" << endl;
    }

    void rentalHistory() {
        cout << "Customer " << customerId << " Rental History:" << endl;
        for (RentalTransaction* transaction : rentedVehicles) {
            cout << "- Vehicle ID: " << transaction->getVehId() << ", Brand: " << transaction->getBrand() << ", Rental Duration: " << transaction->getDuration() << " days, Rental Cost: " << transaction->getRentalCost() << endl;
        }
    }
};

// Class to manage vehicles and customers
class VehicleManagement {
private:
    vector<Vehicle*> vehicles;
    vector<Customer*> customers;

public:
    void addVehicle(Vehicle* vehicle) {
        vehicles.push_back(vehicle);
    }

    void addCustomer(Customer* customer) {
        customers.push_back(customer);
    }

    void fleetStatistics() {
        double totalValue = 0;
        double totalCargo = 0;

        for (Vehicle* vehicle : vehicles) {
            Truck* truck = dynamic_cast<Truck*>(vehicle);
            if (truck != nullptr) {
                totalCargo += truck->getCargoCapacity();
            }
            totalValue += vehicle->getPrice();
        }

        cout << "Total Value of All Vehicles: " << fixed << setprecision(2) << totalValue << endl;
        cout << "Total Cargo Capacity of Trucks: " << fixed << setprecision(2) << totalCargo << " kg" << endl;
    }

    void vehicleRental(int custId, int vehId, int duration) {
        for (Customer* customer : customers) {
            if (customer->getCustomerId() == custId) {
                for (Vehicle* vehicle : vehicles) {
                    if (vehicle->getVehicleId() == vehId) {
                        string brand = vehicle->getBrand();
                        double rentalCost = vehicle->getRentalCost();
                        rentalCost *= duration;
                        // Convert the rental cost to an integer
                        int roundedRentalCost = static_cast<int>(rentalCost);

                        RentalTransaction* transaction = new RentalTransaction(vehId, duration, brand, roundedRentalCost);
                        customer->addTransaction(transaction);
                        cout << "Vehicle " << vehId << " Rented for " << duration << " days by customer " << custId << ". Rental Cost: " << roundedRentalCost << endl;
                        break;
                    }
                }
                break;
            }
        }
    }

    void customerHistory(int id) {
        for (Customer* customer : customers) {
            if (customer->getCustomerId() == id) {
                customer->rentalHistory();
                break;
            }
        }
    }
};


// Main function for Fleet Management
int main() {
    int custId = 1;
    VehicleManagement vehicleManagement;

    while (true) {
        string input;
        getline(cin, input);
        istringstream iss(input);
        vector<string> tokens;
        string token;

        while (iss >> token) {
            tokens.push_back(token);
        }

        if (tokens[0] == "END") {
            break;
        }

        if (tokens[0] == "ADD_VEHICLE") {
            // Add vehicle code here based on input
            //if vehicle is car
            if (tokens[1] == "c") {
                int id = stoi(tokens[2]);
                string brand = tokens[3];
                double price = stod(tokens[4]);
                double rentalCost = stod(tokens[5]);
                string type = tokens[6];
                string fuel = tokens[7];
                string transmission = tokens[8];

                // Create and add a Car to the VehicleManagement
                Car* car = new Car(id, brand, price, rentalCost, type, fuel, transmission);
                vehicleManagement.addVehicle(car);
                car->displayDetails();
            } else if (tokens[1] == "t") {
                // Handle Truck addition similarly as Car addition
                int id = stoi(tokens[2]);
                string brand = tokens[3];
                double price = stod(tokens[4]);
                double rentalCost = stod(tokens[5]);
                double cargoCapacity = stod(tokens[6]);
                double bedLength = stod(tokens[7]);
                int numAxles = stoi(tokens[8]);
                double fuelEfficiency = stod(tokens[9]);

                // Create and add a Truck to the VehicleManagement
                Truck* truck = new Truck(id, brand, price, rentalCost, cargoCapacity, bedLength, numAxles, fuelEfficiency);
                vehicleManagement.addVehicle(truck);
                truck->displayDetails();
            } else if (tokens[1] == "b") {
                // Handle Bicycle 
                int id = stoi(tokens[2]);
                string brand = tokens[3];
                double price = stod(tokens[4]);
                double rentalCost = stod(tokens[5]);
                string type = tokens[6];
                string frame;
                int numGears;
                // Check the frame type and create an object accordingly
                if(tokens[7] == "Carbon"){
                    // Carbon frame with additional information
                    frame=tokens[7]+" "+tokens[8];
                    numGears=stoi(tokens[9]);
                } else {
                    // Other frame type without additional information
                    frame=tokens[7];
                    numGears=stoi(tokens[8]);
                }

                // Create and add a Bicycle to the VehicleManagement
                Bicycle* bicycle = new Bicycle(id, brand, price, rentalCost, type, frame, numGears);
                vehicleManagement.addVehicle(bicycle);
                bicycle->displayDetails();
            } else if (tokens[1] == "d") {
                // Handle Drone 
                int id = stoi(tokens[2]);
                string brand = tokens[3];
                double price = stod(tokens[4]);
                double rentalCost = stod(tokens[5]);
                double maxAltitude = stod(tokens[6]);
                double flyingTime = stod(tokens[7]);
                int camResolution = stoi(tokens[8]);

                Drone* drone = new Drone(id, brand, price, rentalCost, maxAltitude, flyingTime, camResolution);
                vehicleManagement.addVehicle(drone);
                drone->displayDetails();
            }

        } else if (tokens[0] == "FLEET_STATISTICS") {
            vehicleManagement.fleetStatistics();
        } else if (tokens[0] == "ADD_CUSTOMER") {
            Customer* customer = new Customer(custId);
            vehicleManagement.addCustomer(customer);
            customer->display();
            custId++;
        } else if (tokens[0] == "CUSTOMER_HISTORY") {
            // Fetch customer rental history
            int id = stoi(tokens[1]);
            vehicleManagement.customerHistory(id);
        } else if (tokens[0] == "RENT") {
            // Rent a vehicle for a customer
            int customerId = stoi(tokens[1]);
            int vehId = stoi(tokens[2]);
            int duration = stoi(tokens[3]);
            vehicleManagement.vehicleRental(customerId, vehId, duration);
        }
    }

    return 0;
}
