#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <string>
#include <iostream>
#include <memory>
///Clasa de baza, ingredient folosit in prepararea potiunii
enum class ElementType {
    Fire,Water,Air,Ground,Light,Darkness ///Folosit in calcularea sinergiei intre ingrediente
};
///Clasa de baza pentru toate ingredientele folosite la prepararea potiunilor
class Ingredient {
private:
    static int generatorId;
    const int id;
    std::string nume;
    double potentaBaza;
    ElementType element;
    double qualityMultiplier; ///calitatea ingredient-ului
    virtual void print(std::ostream& os) const =0; ///Functie virtuala apelata prin operator<<

protected:
    Ingredient(const std::string& nume, double potentaBaza, ElementType element);
    virtual double calculValoare() const =0; ///Pentru valoarea monetara

public:
    virtual ~Ingredient() = default;
    virtual std::unique_ptr<Ingredient> clone() const =0; ///Copiere polimorfica pentru unique_ptr

    double calculeazaPretVanzare()const; ///Valoarea monetara finala in functie de indicatorul de calitate
    static int getNumarTotalIngrediente();
    int getId() const { return id; }
    std::string getNume() const { return nume; }
    ElementType getElement() const { return element; }
    double getPotentaBaza() const { return potentaBaza; }
    friend std::ostream& operator<<(std::ostream& os, const Ingredient& ing) {
        ing.print(os);
        return os;
    }
    virtual double calculSpecific(double temp, double umid, double timp) const=0; ///Calculul potentei individuale a ingredientului

};

#endif
