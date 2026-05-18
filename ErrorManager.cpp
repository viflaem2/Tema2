#include "ErrorManager.h"

ErrorManager& ErrorManager::getInstance() {
    static ErrorManager instance;
    return instance;
}
void ErrorManager::adaugaEroare(const std::string& mesaj) {
    erori.push_back(mesaj);
}
bool ErrorManager::areErori() const {
    return !erori.empty();
}
void ErrorManager::afiseazaErori(std::ostream& os) const {
    if(erori.empty()) {
        os << "Nu au fost inregistrate erori.\n";
        return;
    }
    os << "Erori inregistrate:\n";
    for(size_t i=0; i<erori.size(); i++){
        os << i + 1 << ". " << erori[i] << '\n';
    }
}
void ErrorManager::stergeErori() {
    erori.clear();
}

