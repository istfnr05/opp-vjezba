#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>
#include <string>

using namespace std;


class Animal {
protected:
    string name;
    int age;
    double weight;

    Animal(const string& name, int age, double weight) {
        if (name.empty())
            throw invalid_argument("Ime ne smije biti prazno");
        if (age < 0)
            throw invalid_argument("Godine ne mogu biti negativne");
        if (weight <= 0)
            throw invalid_argument("Tezina mora biti veca od 0");

        this->name = name;
        this->age = age;
        this->weight = weight;
    }

public:
    virtual ~Animal() {}

    virtual string getSpecies() const = 0;
    virtual double getDailyFood() const = 0;
    string getName() const {
        return name;
    }
};

class Mammal : virtual public Animal {
protected:
    bool hasFur;

    Mammal(const string& name, int age, double weight, bool hasFur)
        : Animal(name, age, weight), hasFur(hasFur) {
        if (hasFur)
            cout << "Stvoren sisavac s dlakom" << endl;
        else
            cout << "Stvoren sisavac s malo dlake" << endl;
    }
};

class Aquatic : virtual public Animal {
protected:
    double maxDiveDepth;

    Aquatic(const string& name, int age, double weight, double maxDiveDepth)
        : Animal(name, age, weight), maxDiveDepth(maxDiveDepth) {
        cout << "Stvorena vodena zivotinja koja roni do "
            << maxDiveDepth << "m" << endl;
    }
};

class Lion : public Mammal {
public:
    Lion(const string& name, int age, double weight)
        : Animal(name, age, weight),
        Mammal(name, age, weight, true) {
    }

    string getSpecies() const override {
        return "Lion";
    }

    double getDailyFood() const override {
        double food = weight * 0.06;
        if (food == 0)
            throw logic_error("Kolicina hrane je 0");
        return food;
    }
};

class Elephant : public Mammal {
public:
    Elephant(const string& name, int age, double weight)
        : Animal(name, age, weight),
        Mammal(name, age, weight, false) {
    }

    string getSpecies() const override {
        return "Elephant";
    }

    double getDailyFood() const override {
        double food = weight * 0.04;
        if (food == 0)
            throw logic_error("Kolicina hrane je 0");
        return food;
    }
};

class Dolphin : public Mammal, public Aquatic {
public:
    Dolphin(const string& name, int age, double weight)
        : Animal(name, age, weight),
        Mammal(name, age, weight, true),
        Aquatic(name, age, weight, 300.0) {
    }

    string getSpecies() const override {
        return "Dolphin";
    }

    double getDailyFood() const override {
        double food = weight * 0.05;
        if (food == 0)
            throw logic_error("Kolicina hrane je 0");
        return food;
    }
};

class SeaTurtle : public Aquatic {
public:
    SeaTurtle(const string& name, int age, double weight)
        : Animal(name, age, weight),
        Aquatic(name, age, weight, 200.0) {
    }

    string getSpecies() const override {
        return "Sea Turtle";
    }

    double getDailyFood() const override {
        double food = weight * 0.03;
        if (food == 0)
            throw logic_error("Kolicina hrane je 0");
        return food;
    }
};


template <typename T>
class ZooSection {
private:
    vector<unique_ptr<T>> animals;

public:
    void addAnimal(unique_ptr<T> animal) {
        if (!animal)
            throw runtime_error("Pokusaj dodavanja nullptr-a");
        animals.push_back(move(animal));
    }

    double totalFood() const {
        double sum = 0;
        for (const auto& a : animals)
            sum += a->getDailyFood();
        return sum;
    }

    size_t size() const {
        return animals.size();
    }

    T* getAnimal(size_t index) const {
        return animals.at(index).get();
    }
};

class ZooKeeper {
private:
    static int totalAnimalsServed;

public:
    void processAnimal(Animal* animal) {
        if (!animal) return;

        cout << "Species: " << animal->getSpecies()
            << ", Name: " << animal->getName()
            << ", Food: " << animal->getDailyFood() << "kg" << endl;

        totalAnimalsServed++;
    }

    static int getTotalAnimalsServed() {
        return totalAnimalsServed;
    }
};

int ZooKeeper::totalAnimalsServed = 0;

int main() {
    try {
        ZooSection<Animal> zoo;
        ZooKeeper keeper;

        zoo.addAnimal(make_unique<Lion>("Simba", 5, 190));
        zoo.addAnimal(make_unique<Elephant>("Dumbo", 10, 5400));
        zoo.addAnimal(make_unique<Dolphin>("Flipper", 8, 300));
        zoo.addAnimal(make_unique<SeaTurtle>("Leonardo", 50, 150));

        for (size_t i = 0; i < zoo.size(); i++) {
            keeper.processAnimal(zoo.getAnimal(i));
        }

        cout << endl;
        cout << "Ukupna dnevna kolicina hrane: "
            << zoo.totalFood() << "kg" << endl;
        cout << "Ukupno nahranjenih zivotinja: "
            << ZooKeeper::getTotalAnimalsServed() << endl;
    }
    catch (const exception& e) {
        cout << "Greska: " << e.what() << endl;
    }

    return 0;
}
