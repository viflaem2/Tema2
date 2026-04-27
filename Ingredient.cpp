#include "Ingredient.h"
#include <cstdlib>

int Ingredient::generatorId=0;

Ingredient::Ingredient(const std::string& nume, double potentaBaza, ElementType element):
    id(generatorId++),nume(nume),potentaBaza(potentaBaza),element(element){
    qualityMultiplier=0.5+((double)rand()/RAND_MAX);
}

double Ingredient::calculeazaPretVanzare() const {
    return calculValoare()*qualityMultiplier;
}

int Ingredient::getNumarTotalIngrediente() {
    return Ingredient::generatorId;
}
