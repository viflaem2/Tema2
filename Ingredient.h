#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <string>
#include <iostream>
#include <memory>

enum class ElementType {
    Fire,Water,Air,Ground,Light,Darkness
};

class Ingredient {
private:
    static int generatorId;
    const int id;
    std::string nume;
    double potentaBaza;
    ElementType element;
    double qualityMultiplier;
    virtual double calculSpecific(double temp, double umid, double timp) const=0;
    virtual double calculValoare() const =0;
    virtual void print(std::ostream& os) const =0;

protected:
    Ingredient(const std::string& nume, double potentaBaza, ElementType element);

public:
    virtual ~Ingredient() = default;
    virtual std::unique_ptr<Ingredient> clone() const =0;
    double obtinePotentaFinala(double temp, double umid, double timp) const;
    double calculeazaPretVanzare()const;
    void afisare(std::ostream& os)const;
    static int getNumarTotalIngrediente();
    int getId() const { return id; }
    std::string getNume() const { return nume; }
    ElementType getElement() const { return element; }
    double getPotentaBaza() const { return potentaBaza; }

};

#endif
