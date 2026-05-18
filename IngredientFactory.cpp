#include "IngredientFactory.h"

#include <cstdlib>
#include <iostream>

#include "Plant.h"
#include "Mineral.h"
#include "MagicEssence.h"

int IngredientFactory::seedDinNume(const std::string& nume) {
    int seed = 0;
    for(char c : nume) {
        seed = seed * 31 + c;
    }
    if(seed < 0) seed = -seed;
    return seed;
}

double IngredientFactory::randomDouble(double st, double dr) {
    return st + (double)rand() / RAND_MAX * (dr - st);
}

ElementType IngredientFactory::randomElement() {
    int x = rand() % 6;
    switch(x) {
        case 0: return ElementType::Fire;
        case 1: return ElementType::Water;
        case 2: return ElementType::Air;
        case 3: return ElementType::Ground;
        case 4: return ElementType::Light;
        default: return ElementType::Darkness;
    }
}

std::unique_ptr<Ingredient> IngredientFactory::creeazaPlanta(std::string nume) {
    if(nume == "") {
        std::cout << "Nume planta: ";
        std::cin >> nume;
    }
    srand(seedDinNume(nume));
    double potenta = randomDouble(5.0, 25.0);
    ElementType element = randomElement();
    double vitalitate = randomDouble(1.0, 10.0);
    double timpMax = randomDouble(5.0, 30.0);
    return std::make_unique<Plant>(nume, potenta, element, vitalitate, timpMax);
}

std::unique_ptr<Ingredient> IngredientFactory::creeazaMineral(std::string nume) {
    if(nume == "") {
        std::cout << "Nume mineral: ";
        std::cin >> nume;
    }
    srand(seedDinNume(nume));
    double potenta = randomDouble(5.0, 25.0);
    ElementType element = randomElement();
    double duritate = randomDouble(1.0, 10.0);
    double puritate = randomDouble(0.4, 1.0);
    return std::make_unique<Mineral>(nume, potenta, element, duritate, puritate);
}

std::unique_ptr<Ingredient> IngredientFactory::creeazaEsenta(std::string nume) {
    if(nume == "") {
        std::cout << "Nume esenta: ";
        std::cin >> nume;
    }
    srand(seedDinNume(nume));
    double potenta = randomDouble(5.0, 25.0);
    ElementType element = randomElement();
    double concentratie = randomDouble(0.2, 1.0);
    double stabilitate = randomDouble(10.0, 100.0);
    return std::make_unique<MagicEssence>(nume, potenta, element, concentratie, stabilitate);
}

