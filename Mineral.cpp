#include "Mineral.h"
#include <cmath>

Mineral::Mineral(const std::string& nume, double potentaBaza, ElementType element, double duritate, double puritate)
    : Ingredient(nume, potentaBaza, element), duritate(duritate), puritate(puritate){}

double Mineral::calculSpecific(double temp, double umid, double timp) const {
    if(temp<duritate*10)
        return 0;
    return getPotentaBaza()*puritate;
}

double Mineral::calculValoare() const {
    return getPotentaBaza()*std::pow(puritate,10.0);
}

void Mineral::print(std::ostream& os) const {
    os << "Mineral " << getNume() << " are duritatea " << duritate << " si puritatea de " << (puritate * 100.0) << "%\n";
}

std::unique_ptr<Ingredient> Mineral::clone() const {
    return std::make_unique<Mineral>(*this);
}
