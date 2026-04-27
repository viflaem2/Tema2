#ifndef MAGICESSENCE_H
#define MAGICESSENCE_H

#include "Ingredient.h"

class MagicEssence : public Ingredient{
private:
    double concentratie,stabilitate; ///Acestea sunt atributele specifice pentru esentele magice
    double calculSpecific(double temp, double umid, double timp) const override;
    double calculValoare() const override;
    void print(std::ostream& os) const override;

public:
    MagicEssence(const std::string& nume, double potentaBaza, ElementType element, double concentratie, double stabilitate);
    ~MagicEssence() override = default;
    std::unique_ptr<Ingredient> clone() const override;
    double getConcentratie() const { return concentratie; }
    double getStabilitate() const { return stabilitate; }
};

#endif
