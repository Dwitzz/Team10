#include "ParticleType.hpp"
#include <iostream>

ParticleType::ParticleType(char* fName, double fMass, int fCharge) : fName_(fName), fMass_(fMass), fCharge_(fCharge) {}

const char* ParticleType::GetfName() const {
    return fName_;
}

const double ParticleType::GetfMass() const {  // questa funzione, fa si che se scriviamo, più avanti nel codice, "P.GetfMass"
                                               // ci ritorna il valore della massa dell'oggetto P.
    return fMass_;
} 

const int ParticleType::GetfCharge() const {  //stessa cosa della funzione GetfMass
    return fCharge_;
}

void ParticleType::Print() const {
    cout << "Particle Name: " << GetfName << endl;
    cout << "Particle Mass: " << GetfMass << endl;
    cout << "Particle Charge: " << GetfCharge << endl;
}