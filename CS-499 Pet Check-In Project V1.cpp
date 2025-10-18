// CS-499 Pet Check-In Project.cpp : This file contains the 'main' function. Program execution begins and ends there.

// Tyler Ernest, CS-499, 9/17/2025

#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

// =====================
// Pet Base Class
// =====================
class Pet {
protected:
    string petType;
    string petName;
    int petAge;
    int daysStay;
    double amountDue;

public:
    Pet(string type, string name, int age, int stay)
        : petType(type), petName(name), petAge(age), daysStay(stay), amountDue(0.0) {}

    virtual ~Pet() {}

    virtual void calculateBill() = 0; // Each pet type will define billing

    // Accessors
    string getName() const { return petName; }
    string getType() const { return petType; }
    int getAge() const { return petAge; }
    int getStay() const { return daysStay; }
    double getBill() const { return amountDue; }

protected:
    void setBill(double bill) { amountDue = bill; }
};

// =====================
// Dog Class
// =====================
class Dog : public Pet {
    bool grooming;

public:
    Dog(string name, int age, int stay, bool groom)
        : Pet("Dog", name, age, stay), grooming(groom) {}

    void calculateBill() override {
        double dailyRate = 30.0; // per day
        double groomingFee = grooming ? 25.0 : 0.0;
        setBill((getStay() * dailyRate) + groomingFee);
    }
};

// =====================
// Cat Class
// =====================
class Cat : public Pet {
public:
    Cat(string name, int age, int stay)
        : Pet("Cat", name, age, stay) {}

    void calculateBill() override {
        double dailyRate = 20.0; // per day
        setBill(getStay() * dailyRate);
    }
};

// =====================
// Pet Hotel Management
// =====================
class PetHotel {
    int dogSpaces;
    int catSpaces;
    vector<shared_ptr<Pet>> pets;

public:
    PetHotel(int dSpaces, int cSpaces) : dogSpaces(dSpaces), catSpaces(cSpaces) {}

    bool checkInPet(shared_ptr<Pet> pet) {
        if (pet->getType() == "Dog") {
            if (dogSpaces > 0) {
                pets.push_back(pet);
                dogSpaces--;
                return true;
            }
        }
        else if (pet->getType() == "Cat") {
            if (catSpaces > 0) {
                pets.push_back(pet);
                catSpaces--;
                return true;
            }
        }
        return false;
    }

    void printAllBills() {
        for (auto& pet : pets) {
            pet->calculateBill();
            cout << pet->getType() << " " << pet->getName()
                << " | Stay: " << pet->getStay()
                << " days | Bill: $" << pet->getBill() << "\n";
        }
    }
};

// =====================
// Main Driver
// =====================
int main() {
    PetHotel hotel(2, 2);  // hotel has space for 2 dogs and 2 cats

    char morePets = 'y';
    while (morePets == 'y' || morePets == 'Y') {
        string type, name;
        int age, stay;
        char groomingChoice;
        bool grooming = false;

        cout << "\nEnter pet type (Dog/Cat): ";
        cin >> type;

        cout << "Enter pet name: ";
        cin >> name;

        cout << "Enter pet age: ";
        cin >> age;

        cout << "Enter length of stay (days): ";
        cin >> stay;

        shared_ptr<Pet> newPet = nullptr;

        if (type == "Dog" || type == "dog") {
            cout << "Grooming? (y/n): ";
            cin >> groomingChoice;
            grooming = (groomingChoice == 'y' || groomingChoice == 'Y');
            newPet = make_shared<Dog>(name, age, stay, grooming);
        }
        else if (type == "Cat" || type == "cat") {
            newPet = make_shared<Cat>(name, age, stay);
        }
        else {
            cout << "Invalid pet type entered.\n";
        }

        if (newPet != nullptr) {
            if (hotel.checkInPet(newPet)) {
                cout << newPet->getName() << " checked in successfully.\n";
            }
            else {
                cout << "No space available for " << newPet->getName() << ".\n";
            }
        }

        cout << "\nAdd another pet? (y/n): ";
        cin >> morePets;
    }

    cout << "\n--- Bills ---\n";
    hotel.printAllBills();

    return 0;
}

