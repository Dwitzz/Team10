#include "ParticleType.hpp"

#ifndef RESONANCETYPE_H
#define RESONANCETYPE_H

//Definiamo la classe ReconanceType come classe derivata di 
//Particle Type, che quindi avrà tutti gli attributi sia pubblici che privati
//della classe Particle. In più ne possiamo aggiungere altri
class ResonanceType : public ParticleType {

    //sono già sottointesi tutti gli altri attributi della classe Particle, 
    // fWidth è aggiuntivo e caratteristico solo di Resonance.
    private:
    const double fWidth_;

    public:
    ResonanceType(const char* fName, double fMass, int fCharge, double fWidth) 
    : ParticleType(fName, fMass, fCharge), fWidth_(fWidth) {}
    double GetfWidth() const;
    virtual void Print() const override;
};

#endif