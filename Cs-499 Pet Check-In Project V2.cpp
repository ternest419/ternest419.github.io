// Cs-499 Pet Check-In Project V2.cpp : This file contains the 'main' function. Program execution begins and ends there.


// Tyler Ernest, CS-499, 9/25/2025, Module 4-2

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
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

    virtual void displayInfo() const {
        cout << "Pet: " << name << " | Age: " << age
            << " | Days Stay: " << daysStay;
    }
};

class Dog : public Pet {
    bool grooming;
public:
    Dog(string n, int a, int d, bool g) : Pet(n, a, d), grooming(g) {}
    void displayInfo() const override {
        Pet::displayInfo();
        cout << " | Type: Dog"
            << " | Grooming: " << (grooming ? "Yes" : "No") << endl;
    }
};

class Cat : public Pet {
public:
    Cat(string n, int a, int d) : Pet(n, a, d) {}
    void displayInfo() const override {
        Pet::displayInfo();
        cout << " | Type: Cat" << endl;
    }
};

class PetHotel {
private:
    unordered_map<string, Pet*> pets; // fast lookups by name
    vector<Pet*> petList;             // for sorting
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

    void sortByAge() {
        sort(petList.begin(), petList.end(),
            [](Pet* a, Pet* b) { return a->getAge() < b->getAge(); });
        cout << "\nPets sorted by age:\n";
        for (auto& p : petList) p->displayInfo();
    }

    void sortByDaysStay() {
        sort(petList.begin(), petList.end(),
            [](Pet* a, Pet* b) { return a->getDaysStay() < b->getDaysStay(); });
        cout << "\nPets sorted by days stay:\n";
        for (auto& p : petList) p->displayInfo();
    }
};

int main() {
    PetHotel hotel;
    int choice;
    string searchName;

    do {
        cout << "\n--- Pet Hotel Menu ---\n";
        cout << "1. Add Pet\n";
        cout << "2. Find Pet\n";
        cout << "3. Sort Pets by Age\n";
        cout << "4. Sort Pets by Days Stay\n";
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
            hotel.sortByAge();
            break;
        case 4:
            hotel.sortByDaysStay();
            break;
        case 5:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 5);

    return 0;
}
