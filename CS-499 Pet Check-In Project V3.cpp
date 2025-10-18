// CS-499 Pet Check-In Project V3.cpp : This file contains the 'main' function. Program execution begins and ends there.

// Tyler Ernest, CS-499, 9/30/2025, 5-2 Milestone four

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <fstream>
using namespace std;

// Base class
class Pet {
protected:
    string name;
    int age;
    int daysStay;
public:
    Pet(string n, int a, int d) : name(n), age(a), daysStay(d) {}
    virtual ~Pet() {}

    string getName() const { return name; }
    int getAge() const { return age; }
    int getDaysStay() const { return daysStay; }

    virtual string getType() const = 0;
    virtual string getRecord() const = 0;

    virtual void displayInfo() const {
        cout << "Pet: " << name << " | Age: " << age
            << " | Days Stay: " << daysStay;
    }
};

class Dog : public Pet {
    bool grooming;
public:
    Dog(string n, int a, int d, bool g) : Pet(n, a, d), grooming(g) {}
    string getType() const override { return "Dog"; }
    string getRecord() const override {
        return getType() + "," + name + "," + to_string(age) + "," + to_string(daysStay) + "," + (grooming ? "1" : "0");
    }
    void displayInfo() const override {
        Pet::displayInfo();
        cout << " | Type: Dog"
            << " | Grooming: " << (grooming ? "Yes" : "No") << endl;
    }
};

class Cat : public Pet {
public:
    Cat(string n, int a, int d) : Pet(n, a, d) {}
    string getType() const override { return "Cat"; }
    string getRecord() const override {
        return getType() + "," + name + "," + to_string(age) + "," + to_string(daysStay) + ",0";
    }
    void displayInfo() const override {
        Pet::displayInfo();
        cout << " | Type: Cat" << endl;
    }
};

class PetHotel {
private:
    unordered_map<string, Pet*> pets;
    vector<Pet*> petList;
    const string dataFile = "pets_db.txt";

public:
    ~PetHotel() {
        for (auto& p : petList) delete p;
    }

    void checkIn(Pet* p) {
        pets[p->getName()] = p;
        petList.push_back(p);
        cout << p->getName() << " checked in successfully.\n";
    }

    void addPet() {
        string type, name;
        int age, days;
        char groomingChoice;

        cout << "\nEnter pet type (dog/cat): ";
        cin >> type;
        cout << "Enter pet name: ";
        cin >> name;
        cout << "Enter pet age: ";
        cin >> age;
        cout << "Enter days staying: ";
        cin >> days;

        if (type == "dog" || type == "Dog") {
            cout << "Does the dog need grooming? (y/n): ";
            cin >> groomingChoice;
            bool grooming = (groomingChoice == 'y' || groomingChoice == 'Y');
            checkIn(new Dog(name, age, days, grooming));
        }
        else if (type == "cat" || type == "Cat") {
            checkIn(new Cat(name, age, days));
        }
        else {
            cout << "Unknown pet type. Pet not added.\n";
        }
    }

    void findPet(string name) {
        if (pets.find(name) != pets.end()) {
            pets[name]->displayInfo();
        }
        else {
            cout << "No pet found with name: " << name << endl;
        }
    }

    void saveToFile() {
        ofstream file(dataFile);
        if (!file) {
            cout << "Error opening file for writing.\n";
            return;
        }

        for (auto& pet : petList) {
            file << pet->getRecord() << endl;
        }

        file.close();
        cout << "Pet data saved successfully to " << dataFile << ".\n";
    }

    void loadFromFile() {
        ifstream file(dataFile);
        if (!file) {
            cout << "No existing data found.\n";
            return;
        }

        string type, name, ageStr, daysStr, groomStr;
        while (getline(file, type, ',')) {
            getline(file, name, ',');
            getline(file, ageStr, ',');
            getline(file, daysStr, ',');
            getline(file, groomStr);

            int age = stoi(ageStr);
            int days = stoi(daysStr);
            bool grooming = (groomStr == "1");

            if (type == "Dog") checkIn(new Dog(name, age, days, grooming));
            else if (type == "Cat") checkIn(new Cat(name, age, days));
        }

        file.close();
        cout << "Pet data loaded successfully from " << dataFile << ".\n";
    }

    void listPets() {
        cout << "\n--- Current Pet Records ---\n";
        for (auto& p : petList) p->displayInfo();
    }
};

int main() {
    PetHotel hotel;
    hotel.loadFromFile();

    int choice;
    string searchName;

    do {
        cout << "\n--- Pet Hotel Menu ---\n";
        cout << "1. Add Pet\n";
        cout << "2. Find Pet\n";
        cout << "3. List Pets\n";
        cout << "4. Save Data\n";
        cout << "5. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
        case 1:
            hotel.addPet();
            break;
        case 2:
            cout << "Enter pet name to search: ";
            cin >> searchName;
            hotel.findPet(searchName);
            break;
        case 3:
            hotel.listPets();
            break;
        case 4:
            hotel.saveToFile();
            break;
        case 5:
            hotel.saveToFile();
            cout << "Exiting and saving data...\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 5);

    return 0;
}

