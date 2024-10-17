#include "ResonanceType.hpp"

const double ResonanceType::GetfWidth() const {return fWidth_;}
void ResonanceType::Print() const {
    ParticleType::Print();
    std::cout << "Particle Width: " << GetfWidth() << '\n';    
}
