#include <iostream>

#ifndef PARTICLETYPE_H
#define PARTICLETYPE_H

class ParticleType{
    private:             // dichiariamo le caratteristiche genrelai delle particelle
                         // come costanti, invariabili nel codice

    const char* fName_;   //nome della particella
    const double fMass_;  //massa della particella
    const int fCharge_;   // carica della particella

    public:

    //costruttore parametrico
    ParticleType(const char* fName, double fMass, int fCharge) :
        fName_(fName), fMass_(fMass), fCharge_(fCharge) {};

    //metodi getter
    const char* GetfName() const;
    const double GetfMass() const;
    const int GetfCharge() const;

    //metodo print
    void Print() const;
};


#endif