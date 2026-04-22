#ifndef PLANT_H
#define PLANT_H

#include "Ingredient.h"

class Plant: public Ingredient {
private:
    double vitalitate, timpMax;
    double calculSpecific(double temp, double umid, double timp) const override;
    double calculValoare() const override;
    void print(std::ostream& os) const override;
public:
    Plant(const std::string& nume, double potenta, ElementType element, double vitalitate, double timpMax);
    ~Plant() override = default;
    std::unique_ptr<Ingredient> clone() const override;
    double getVitalitate() const { return vitalitate; }
    double getTimpMax() const { return timpMax; }
};

#endif
