# Tema 2 - Alchemy Potion Game

Proiectul este o aplicație C++ în consolă care simulează prepararea unor poțiuni într-un cazan. Ideea de bază este că jucătorul combină ingrediente de tipuri diferite, iar programul calculează dacă poțiunea rezultată este validă, toxică, inutilizabilă sau dacă procesul produce o explozie.

Am încercat să păstrez logica destul de simplă, dar să folosesc conceptele OOP cerute în temă: moștenire, funcții virtuale, pointeri către clasa de bază, smart pointers, excepții proprii și copiere polimorfică.

## Descriere generală

În joc există trei tipuri de ingrediente:

- `Plant`
- `Mineral`
- `MagicEssence`

Toate derivă din clasa de bază abstractă `Ingredient`.

O poțiune validă trebuie să fie formată din exact:

- o plantă
- un mineral
- o esență magică

Ingredientele sunt puse într-un obiect de tip `Cazan`, iar apoi se apelează metoda de preparare. Dacă prepararea reușește, rezultatul este un obiect `Potiune`, care reține potența finală, valoarea monetară și ingredientele folosite.

## Generarea ingredientelor

În modul interactiv, utilizatorul introduce doar numele ingredientului. Restul atributelor sunt generate automat pe baza numelui, folosind un seed calculat din string.

Asta înseamnă că același nume va genera aceleași proprietăți de fiecare dată. De exemplu, dacă se introduce `Mandragora`, planta va avea aceleași valori generate la fiecare rulare.

Atribute generate:

- potență de bază
- element magic
- vitalitate, pentru plante
- duritate și puritate, pentru minerale
- concentrație și stabilitate, pentru esențe magice

## Reguli pentru prepararea poțiunii

Cazanul verifică mai întâi dacă are ingredientele corecte. Dacă lipsesc ingrediente sau sunt tipuri greșite, prepararea eșuează.

După aceea, fiecare ingredient contribuie la potența finală prin funcția virtuală `calculSpecific()`. Implementarea acestei funcții este diferită pentru fiecare clasă derivată.

Elementele ingredientelor pot afecta poțiunea:

- `Fire` + `Water` anulează poțiunea
- `Light` + `Darkness` anulează poțiunea
- anumite combinații reduc potența la jumătate

Dacă potența ajunge la zero, poțiunea nu este utilizabilă. Dacă potența depășește limita de toxicitate a cazanului, se aruncă o excepție de toxicitate.

Esențele magice pot produce și o explozie dacă devin prea instabile în condițiile date.

## Valoarea monetară

Fiecare ingredient are o valoare proprie, calculată diferit în funcție de tipul său. Clasa de bază `Ingredient` aplică și un `qualityMultiplier`, care modifică prețul de vânzare al ingredientului.

Valoarea monetară finală a poțiunii este calculată pe baza valorii ingredientelor și a potenței finale. În joc, aceasta este folosită ca scor.

## Moduri de rulare

Programul are două moduri:

### 1. Demo

Modul demo rulează automat mai multe cazuri, ca să fie mai ușor de verificat proiectul.

Acesta demonstrează:

- prepararea unei poțiuni valide
- cazan gol
- combinație greșită de ingrediente
- poțiune fără efect
- poțiune toxică
- explozie
- constructor de copiere
- operatorul de atribuire

### 2. Interactiv

În modul interactiv, utilizatorul poate:

- adăuga plante
- adăuga minerale
- adăuga esențe magice
- afișa conținutul cazanului
- prepara o poțiune
- afișa raftul cu poțiuni create
- vedea scorul total
- goli cazanul

## Structura proiectului

Fișiere principale:

```text
Ingredient.h / Ingredient.cpp
Plant.h / Plant.cpp
Mineral.h / Mineral.cpp
MagicEssence.h / MagicEssence.cpp
Cazan.h / Cazan.cpp
AlchemyExceptions.h
main.cpp
```

Rolul claselor:

- `Ingredient` - clasa de bază abstractă pentru toate ingredientele
- `Plant` - ingredient de tip plantă
- `Mineral` - ingredient de tip mineral
- `MagicEssence` - ingredient de tip esență magică
- `Cazan` - gestionează ingredientele și prepararea poțiunii
- `Potiune` - rezultatul unei preparări reușite
- `AlchemyException` și clasele derivate - excepții proprii pentru erorile din joc

## Elemente OOP folosite

În proiect sunt folosite:

- moștenire
- funcții virtuale pure
- suprascriere cu `override`
- clasă abstractă
- pointeri către clasa de bază
- `std::unique_ptr`
- copiere polimorfică prin `clone()`
- `dynamic_cast`
- excepții proprii
- `try` / `catch`
- membri și metode statice
- STL: `std::vector`, `std::string`, `std::unique_ptr`

## Rulare

Exemplu de rețetă validă în modul interactiv:

```text
Planta: Mandragora
Mineral: Cristal
Esenta: Salvie
Temperatura: 100
Umiditate: 0.8
Timp: 5
```

