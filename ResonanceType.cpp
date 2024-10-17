#include "ResonanceType.hpp"
#include <iostream>

double ResonanceType::GetfWidth() const {return fWidth_;}

void ResonanceType::Print() const {
    ParticleType::Print();
    std::cout << "Particle Width: " << GetfWidth() << '\n';    
}

