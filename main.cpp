#include <iostream>
#include <vector>
#include <memory>
#include <cstdlib>
#include <string>
#include <exception>
#include <utility>

#include "Cazan.h"
#include "AlchemyExceptions.h"
#include "IngredientFactory.h"
#include "ErrorManager.h"
#include "Raft.h"


void afiseazaPotiune(const Potiune& p) {
    std::cout<<"Potenta: "<<p.potenta<<'\n';
    std::cout<<"Valoare monetara: "<<p.valoareMonetara<<'\n';
    std::cout<<"Ingrediente folosite:\n";
    if(p.planta) std::cout<<"-"<<*p.planta;
    if(p.mineral) std::cout<<"-"<<*p.mineral;
    if(p.esenta) std::cout<<"-"<<*p.esenta;
}

void afiseazaRaft(const Raft<Potiune>& raft) {
    if(raft.esteGol()) {
        std::cout<<"Raftul este gol.\n";
        return;
    }
    for(size_t i=0; i<raft.dimensiune(); i++) {
        std::cout<<"Potiunea "<<i+1<<":\n";
        afiseazaPotiune(raft[i]);
        std::cout<<'\n';
    }
} ///Raftul cu potiuni

double scorTotal(const Raft<Potiune>& raft) {
    return totalizeaza(raft, [](const Potiune& p) {
        return p.valoareMonetara;
    });
}

void incearca(Cazan& c, Raft<Potiune>& raft, double temp, double umid, double timp) { ///Incercam sa facem o potiune si prindem erori daca apar
    try {
        Potiune p=c.preparaPotiune(temp,umid,timp);
        std::cout<<"Potiunea a fost creata.\n";
        afiseazaPotiune(p);
        raft.adauga(std::move(p));
    }
    catch(const AlchemyExplosionException& e) {
        ErrorManager::getInstance().adaugaEroare(e.what());
        std::cout<<e.what()<<'\n';
        c.golesteCazan();
        std::cout<<"Cazanul a fost golit dupa esec.\n";
    }
    catch(const ToxicSludgeException& e) {
        ErrorManager::getInstance().adaugaEroare(e.what());
        std::cout<<e.what()<<'\n';
        c.golesteCazan();
        std::cout<<"Cazanul a fost golit dupa esec.\n";
    }
    catch(const PotionFailureException& e) {
        ErrorManager::getInstance().adaugaEroare(e.what());
        std::cout<<e.what()<<'\n';
        c.golesteCazan();
        std::cout<<"Cazanul a fost golit dupa esec.\n";
    }
    catch(const std::exception& e) {
        ErrorManager::getInstance().adaugaEroare(e.what());
        std::cout<<e.what()<<'\n';
        c.golesteCazan();
        std::cout<<"Cazanul a fost golit dupa esec.\n";
    }
}

void adaugaRetetaDemo(Cazan& c) {
    c.adaugaIngredient(IngredientFactory::creeazaPlanta("Mandragora"));
    c.adaugaIngredient(IngredientFactory::creeazaMineral("Cristal"));
    c.adaugaIngredient(IngredientFactory::creeazaEsenta("Salvie"));
}

void modDemo() { ///Un demo cu valori hardcodate care arata aproximativ toate functionalitatile jocului
    Raft<Potiune> raft;
    Cazan c(100000);
    std::cout<<"Demo\n";
    std::cout<<"\nDemo potiune valida:\n";
    adaugaRetetaDemo(c);
    c.afiseazaContinut();
    incearca(c,raft,100,0.8,5);
    std::cout<<"\nDemo cazan gol:\n";
    c.golesteCazan();
    incearca(c,raft,100,0.8,5);
    std::cout<<"\nDemo ingrediente gresite:\n";
    c.golesteCazan();
    c.adaugaIngredient(IngredientFactory::creeazaPlanta("A"));
    c.adaugaIngredient(IngredientFactory::creeazaPlanta("B"));
    c.adaugaIngredient(IngredientFactory::creeazaEsenta("C"));
    c.afiseazaContinut();
    incearca(c,raft,100,0.8,5);
    std::cout<<"\nDemo mineral care nu se topeste:\n";
    c.golesteCazan();
    adaugaRetetaDemo(c);
    c.afiseazaContinut();
    incearca(c,raft,1,0.8,5);
    std::cout<<"\nDemo toxicitate:\n";
    Cazan cMic(1);
    adaugaRetetaDemo(cMic);
    cMic.afiseazaContinut();
    incearca(cMic,raft,100,0.8,5);
    std::cout<<"\nDemo explozie:\n";
    Cazan cExplozie(1000000);
    adaugaRetetaDemo(cExplozie);
    cExplozie.afiseazaContinut();
    incearca(cExplozie,raft,500,0.1,100);
    std::cout<<"\nDemo constructor copiere si operator=:\n";
    Cazan cOriginal(100000);
    adaugaRetetaDemo(cOriginal);
    Cazan cCopie=cOriginal;
    Cazan cEgal;
    cEgal=cOriginal;
    std::cout<<"Cazan original:\n";
    cOriginal.afiseazaContinut();
    std::cout<<"Cazan copiat prin constructor:\n";
    cCopie.afiseazaContinut();
    std::cout<<"Cazan copiat prin operator=:\n";
    cEgal.afiseazaContinut();
    std::cout<<"Preparare din copia facuta prin constructor:\n";
    incearca(cCopie,raft,100,0.8,5);
    std::cout<<"\nFinal demo:\n";
    std::cout<<"Scor: "<<scorTotal(raft)<<'\n';
    std::cout<<"Potiuni create: "<<Cazan::getPotiuniCreate()<<'\n';
    std::cout<<"Ingrediente create: "<<Ingredient::getNumarTotalIngrediente()<<'\n';
    std::cout<<"\nRaft:\n";
    afiseazaRaft(raft);
    Raft<std::unique_ptr<Ingredient>> mostre;
    mostre.adauga(IngredientFactory::creeazaPlanta("Lotus"));
    mostre.adauga(IngredientFactory::creeazaMineral("Obsidian"));
    std::cout<<"\nValoare mostre: "
             <<totalizeaza(mostre, [](const std::unique_ptr<Ingredient>& ing) {
                 if(!ing) return 0.0;
                 return ing->calculeazaPretVanzare();
             })<<'\n';
    std::cout<<"\nJurnal erori:\n";
    ErrorManager::getInstance().afiseazaErori();
}

void modInteractiv() {
    Cazan c(100000);
    Raft<Potiune> raft;
    int op;
    do {
        std::cout<<"1.Planta 2.Mineral 3.Esenta 4.Afisare cazan 5.Prepara 6.Raft 7.Scor 8.Goleste 0.Exit\n";
        std::cout<<"Optiune: ";
        std::cin>>op;
        if(op==1) {
            c.adaugaIngredient(IngredientFactory::creeazaPlanta());
            std::cout<<"Planta a fost adaugata.\n";
        }
        else if(op==2) {
            c.adaugaIngredient(IngredientFactory::creeazaMineral());
            std::cout<<"Mineralul a fost adaugat.\n";
        }
        else if(op==3) {
            c.adaugaIngredient(IngredientFactory::creeazaEsenta());
            std::cout<<"Esenta magica a fost adaugata.\n";
        }
        else if(op==4) {c.afiseazaContinut();}
        else if(op==5) {
            double temp,umid,timp;
            std::cout<<"Temperatura: ";
            std::cin>>temp;
            std::cout<<"Umiditate: ";
            std::cin>>umid;
            std::cout<<"Timp: ";
            std::cin>>timp;
            if(temp==0 || umid==0) {
                std::cout<<"Temperatura si umiditatea nu pot fi 0.\n";
            }
            else {
                incearca(c,raft,temp,umid,timp);
            }
        }
        else if(op==6) {afiseazaRaft(raft);}
        else if(op==7) {
            std::cout<<"Scor: "<<scorTotal(raft)<<'\n';
            std::cout<<"Potiuni create: "<<Cazan::getPotiuniCreate()<<'\n';
            std::cout<<"Ingrediente create: "<<Ingredient::getNumarTotalIngrediente()<<'\n';
        }
        else if(op==8) {
            c.golesteCazan();
            std::cout<<"Cazanul a fost golit.\n";
        }
        else if(op!=0) {std::cout<<"Optiune invalida.\n";}
        std::cout<<'\n';

    } while(op!=0);
}

int main() {
    int mod;
    std::cout<<"1.Demo 2.Interactiv\n";
    std::cout<<"Optiune: ";
    std::cin>>mod;

    if(mod==1) {modDemo();}
    else {modInteractiv();}

    return 0;
}
