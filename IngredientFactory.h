#ifndef INGREDIENT_FACTORY_H
#define INGREDIENT_FACTORY_H

#include <iostream>
#include <memory>
#include <string>
#include "Ingredient.h"

class IngredientFactory {
private:
    static int seedDinNume(const std::string& nume);
    static double randomDouble(double st, double dr);
    static ElementType randomElement();

public:
    static std::unique_ptr<Ingredient> creeazaPlanta(std::string nume = "");
    static std::unique_ptr<Ingredient> creeazaMineral(std::string nume = "");
    static std::unique_ptr<Ingredient> creeazaEsenta(std::string nume = "");
};

#endif

