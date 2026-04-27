#include "Cazan.h"
#include "Mineral.h"
#include "MagicEssence.h"
#include "Plant.h"

int Cazan::potiuniCreate=0;

Cazan::Cazan(double limita) : toxicLimit(limita) {}

Cazan::Cazan(const Cazan& toCopy) : toxicLimit(toCopy.toxicLimit) {
    for (const auto& ing:toCopy.ingrediente){
        if(ing){ingrediente.push_back(ing->clone());}
    }
}  ///Ingredientele sunt copiate polimorfic, deoarece sunt tinute prin pointeri la clasa de baza

void swap(Cazan& v1, Cazan& v2) noexcept {
    using std::swap;
    std::swap(v2.toxicLimit,v1.toxicLimit);
    std::swap(v2.ingrediente,v1.ingrediente);
}  ///Mecanismul de copy swap

Cazan& Cazan::operator=(Cazan other) {
    swap(*this, other);
    return *this;

}

void Cazan::adaugaIngredient(std::unique_ptr<Ingredient> ing) {
    if(ing){ingrediente.push_back(std::move(ing));} ///Aici introducem ingrediente in cazan
}

Potiune Cazan::preparaPotiune(double temp, double umid, double timp) { ///Preparea potiunii
    if(ingrediente.empty()){
        throw PotionFailureException("Cazanul este gol."); ///Mai intai ne uitam daca cazanul este gol
    }\

    int nrPlante=0,nrMinerale=0,nrEsente=0;
    for(const auto& ing:ingrediente){
        if(dynamic_cast<Plant*>(ing.get())!=nullptr) nrPlante++;
        if(dynamic_cast<Mineral*>(ing.get())!=nullptr) nrMinerale++;
        if(dynamic_cast<MagicEssence*>(ing.get())!=nullptr) nrEsente++;
    } ///Numaram cate din fiecare tip de ingredient avem in cazan

    if(!(nrPlante==1&&nrMinerale==1&&nrEsente==1))
        {throw PotionFailureException("O potiune este formata din exact o planta, un mineral, si o esenta magica. Nu se poate crea potiunea cu ingredientele din cazan");}
    double potentaTotala=1.0;
    for (const auto& ing:ingrediente){
        potentaTotala*=ing->calculSpecific(temp,umid,timp);
    } ///calculam Potenta totala inainte de calculul de sinerige

    for(size_t i=0; i<3; i++){
        for (size_t j=i+1; j<3; j++) {
            ElementType e1 = ingrediente[i]->getElement();
            ElementType e2 = ingrediente[j]->getElement();
            if ((e1 == ElementType::Fire && e2 == ElementType::Water) || (e1 == ElementType::Water && e2 == ElementType::Fire) ||
                (e1 == ElementType::Light && e2 == ElementType::Darkness) || (e1 == ElementType::Darkness && e2 == ElementType::Light)) {
                potentaTotala = 0.0;
            } ///In aceasta situatie, elementele se anihileaza reciproc complet si se strica complet potiunea
            else if ((e1 == ElementType::Fire && e2 == ElementType::Darkness) || (e1 == ElementType::Darkness && e2 == ElementType::Fire) ||
                     (e1 == ElementType::Water && e2 == ElementType::Light) || (e1 == ElementType::Light && e2 == ElementType::Water) ||
                     (e1 == ElementType::Fire && e2 == ElementType::Air) || (e1 == ElementType::Air && e2 == ElementType::Fire)) {

                potentaTotala *= 0.5;
            } ///In aceasta situatie, elementele au sinergie proasta si potenta potiunii scade drastic
        }
    }

    if(potentaTotala<=0.0){throw PotionFailureException("Potiunea nu are niciun efect. Nu este utilizabila.");}
    if(potentaTotala>toxicLimit){throw ToxicSludgeException("Potiunea creata este atat de potenta incat a devenit toxica. Nu este utilizabila.");}
    double valoareTotala = 0.0;
    for (const auto& ing : ingrediente) {valoareTotala+=ing->calculeazaPretVanzare();}
    Potiune rezultat;
    rezultat.potenta=potentaTotala;
    rezultat.valoareMonetara = valoareTotala*potentaTotala*0.5;
    for(auto& ing:ingrediente){
        if(dynamic_cast<Plant*>(ing.get())!=nullptr) rezultat.planta=std::move(ing);
        if(dynamic_cast<Mineral*>(ing.get())!=nullptr) rezultat.mineral=std::move(ing);
        if(dynamic_cast<MagicEssence*>(ing.get())!=nullptr) rezultat.esenta=std::move(ing);
    } ///Avem nevoie de dynamic cast si pentru a salva ingredientele in potiune corect
    potiuniCreate++;
    golesteCazan(); ///Golim cazanul
    return rezultat;
}

void Cazan::golesteCazan() {
    ingrediente.clear();
}

void Cazan::afiseazaContinut() const {
    std::cout<<"In Cazan se afla "<<ingrediente.size()<<" ingrediente\n";
    for (const auto& ing:ingrediente){std::cout<<"-"<<*ing;}
    std::cout<<'\n';
}
