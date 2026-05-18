#ifndef RAFT_H
#define RAFT_H

#include <cstddef>
#include <utility>
#include <vector>

template <typename T>
class Raft {
private:
    std::vector<T> elemente;

public:
    void adauga(T obiect) {
        elemente.push_back(std::move(obiect));
    }
    bool esteGol() const {
        return elemente.empty();
    }
    std::size_t dimensiune() const {
        return elemente.size();
    }
    T& operator[](std::size_t index) {
        return elemente[index];
    }
    const T& operator[](std::size_t index) const {
        return elemente[index];
    }
    auto begin() -> typename std::vector<T>::iterator {
        return elemente.begin();
    }
    auto end() -> typename std::vector<T>::iterator {
        return elemente.end();
    }
    auto begin() const -> typename std::vector<T>::const_iterator {
        return elemente.begin();
    }
    auto end() const -> typename std::vector<T>::const_iterator {
        return elemente.end();
    }
};
template <typename Container, typename Extractor>
double totalizeaza(const Container& container, Extractor extractor) {
    double total = 0.0;
    for(const auto& element : container) {
        total += extractor(element);
    }
    return total;
}

#endif

