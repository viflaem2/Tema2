#include "Plant.h"

Plant::Plant(const std::string& nume, double potentaBaza, ElementType element, double vitalitate, double timpMax)
    : Ingredient(nume, potentaBaza, element), vitalitate(vitalitate), timpMax(timpMax) {}

double Plant::calculSpecific(double temp, double umid, double timp) const {
    double timpRamas = timp - timpMax;
    if(0.0 > timpRamas) timpRamas = 0.0;
    double finalvitalitate = vitalitate * (100.0 / temp) * umid;
    return getPotentaBaza() + finalvitalitate - timpRamas;
}

double Plant::calculValoare() const {
    return getPotentaBaza() * vitalitate;
}

void Plant::print(std::ostream& os) const {
    os << "Planta " << getNume() << " are vitalitatea " << vitalitate << '\n';
}

std::unique_ptr<Ingredient> Plant::clone() const {
    return std::make_unique<Plant>(*this);
}
