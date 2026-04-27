#ifndef ALCHEMY_EXCEPTIONS_H
#define ALCHEMY_EXCEPTIONS_H
#include <string>
#include <exception>

class AlchemyException : public std::exception { ///Base exception
private:
    std::string mesaj;
public:
    explicit AlchemyException(const std::string& msg): mesaj(msg) {}
    const char* what() const noexcept override {return mesaj.c_str();}
};

class AlchemyExplosionException : public AlchemyException { ///In caz de explozie
public:
    using AlchemyException::AlchemyException;
};

class PotionFailureException : public AlchemyException {  ///In caz de probleme generale la prepararea potiunii
public:
    using AlchemyException::AlchemyException;
};

class ToxicSludgeException : public AlchemyException { ///Daca potiunea e prea potenta, devine toxica si inutilizabila
public:
    using AlchemyException::AlchemyException;
};

#endif
