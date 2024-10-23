#include "ParticleType.hpp"
#include <iostream>

const std::string ParticleType::GetfName() const {
    return fName_;
}

double ParticleType::GetfMass() const {  // questa funzione, fa si che se scriviamo, più avanti nel codice, "P.GetfMass"
                                               // ci ritorna il valore della massa dell'oggetto P.
    return fMass_;
} 

int ParticleType::GetfCharge() const {  //stessa cosa della funzione GetfMass
    return fCharge_;
}

void ParticleType::Print() const {
    std::cout << "Particle Name: " << GetfName() << '\n';
    std::cout << "Particle Mass: " << GetfMass() << '\n';
    std::cout << "Particle Charge: " << GetfCharge() << '\n';
}

double ParticleType::GetfWidth() const {return 0.;}