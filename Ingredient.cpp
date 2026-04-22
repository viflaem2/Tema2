#include "Ingredient.h"
#include <cstdlib>

int Ingredient::generatorId=0;

Ingredient::Ingredient(const std::string& nume, double potentaBaza, ElementType element):
    id(generatorId++),nume(nume),potentaBaza(potentaBaza),element(element){
    qualityMultiplier=0.5+((double)rand()/RAND_MAX);
}

double Ingredient::obtinePotentaFinala(double temp, double umid, double timp) const {
    if(temp<-273.15) return 0;
    return potentaBaza+calculSpecific(temp,umid,timp);
}

double Ingredient::calculeazaPretVanzare() const {
    return calculValoare()*qualityMultiplier;
}

void Ingredient::afisare(std::ostream& os) const {
    print(os);
}

int Ingredient::getNumarTotalIngrediente() {
    return Ingredient::generatorId;
}
