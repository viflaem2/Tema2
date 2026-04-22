#include "MagicEssence.h"

MagicEssence::MagicEssence(const std::string& nume, double potentaBaza, ElementType element, double concentratie, double stabilitate)
    : Ingredient(nume, potentaBaza, element), concentratie(concentratie), stabilitate(stabilitate) {}

double MagicEssence::calculSpecific(double temp, double umid, double timp) const {
    if((temp/umid)*timp>stabilitate*100)
        throw std::runtime_error("Explozie! Esenta magica a devenit prea instabila si potiunea a explodat!"); ///DE UPDATAT LATER
    else if((temp/umid)*timp>stabilitate*10)
        return 0;
    return potentaBaza*concentratie*5;
}

double MagicEssence::calculValoare() const {
    return getPotentaBaza*concentratie*10;

}

void MagicEssence::print(std::ostream& os) const {
    os << "Esenta Magica " << getNume() << " are concentratia " << (concentratie * 100.0) << "% si stabilitatea " << stabilitate << '\n';
}

std::unique_ptr<Ingredient> MagicEssence::clone() const {
    return std::make_unique<MagicEssence>(*this);
}
