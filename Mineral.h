#ifndef MINERAL_H
#define MINERAL_H

#include "Ingredient.h"

class Mineral: public Ingredient{
private:
    double duritate, puritate; ///Mineralele au aceste 2 atribute specifice
    double calculSpecific(double temp, double umid, double timp) const override;
    double calculValoare() const override;
    void print(std::ostream& os) const override;
public:
    Mineral(const std::string& nume,double potenta, ElementType element, double duritate, double puritate);
    ~Mineral() override =default;
    std::unique_ptr<Ingredient> clone() const override;
    double getDuritate() const { return duritate; }
    double getPuritate() const { return puritate; }
};

#endif
