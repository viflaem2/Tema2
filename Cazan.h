#ifndef CAZAN_H
#define CAZAN_H

#include <vector>
#include <memory>
#include <iostream>
#include "Ingredient.h"
#include "AlchemyExceptions.h"

struct Potiune { ///O potiune este formata din 3 ingrediente, cate unul din fiecare, este preparata intr-un cazan si are o anume potenta si valoare monetara
    double potenta;
    double valoareMonetara;
    std::unique_ptr<Ingredient> planta;
    std::unique_ptr<Ingredient> mineral;
    std::unique_ptr<Ingredient> esenta;
};

class Cazan {
private:
    std::vector <std::unique_ptr<Ingredient>> ingrediente;
    double toxicLimit; ///Normal limita toxicitatii nu ar trebui sa fie data cazanului, dar nu am avut o idee mai buna unde sa o pun
    ///  pentru ca nu am voie sa utilizez variabile globale
    static int potiuniCreate;
public:
    explicit Cazan(double limita = 500.0);
    ~Cazan() = default;
    Cazan(const Cazan& toCopy);
    Cazan& operator=(Cazan other);
    friend void swap(Cazan&v1, Cazan &v2) noexcept; ///Functie folosita de operator= pentru copy-swap
    void adaugaIngredient(std::unique_ptr<Ingredient> ing);
    Potiune preparaPotiune(double temp, double umid, double timp);
    void golesteCazan();
    void afiseazaContinut() const;
    static int getPotiuniCreate(){return potiuniCreate;}
};

#endif
