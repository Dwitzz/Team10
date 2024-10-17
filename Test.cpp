#include "Particle.hpp"
#include "ResonanceType.hpp"


int main() {
    // Creiamo un'istanza di ParticleType
    ParticleType electron("Electron", 9.11e-31, -1); 

    
    ResonanceType rho("Rho", 0.775, 0, 0.149); 

    
    ParticleType* particles[2];
    particles[0] = &electron;  
    particles[1] = &rho;       


    for (int i = 0; i < 2; i++) {
        particles[i]->Print();
        std::cout << "----\n";  
    }

    return 0;
}