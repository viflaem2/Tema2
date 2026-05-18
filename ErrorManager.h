#ifndef ERROR_MANAGER_H
#define ERROR_MANAGER_H

#include <iostream>
#include <string>
#include <vector>

class ErrorManager {
private:
    std::vector<std::string> erori;

    ErrorManager() = default;

public:
    static ErrorManager& getInstance();

    ErrorManager(const ErrorManager&) = delete;
    ErrorManager& operator=(const ErrorManager&) = delete;

    void adaugaEroare(const std::string& mesaj);
    bool areErori() const;
    void afiseazaErori(std::ostream& os = std::cout) const;
    void stergeErori();
};

#endif

