#include <array>
#include "ResonanceType.hpp"
#include "Particle.hpp"
#include "ParticleType.hpp"
int main () {
constexpr int N{130};
std::array < Particle, N> eventParticle{};

double phi{};
double theta{};
double P{};

for (Particle& element : eventParticle) {
    phi = gRandom -> Uniform(0.0, 2 * TMath::Pi());
    theta = gRandom -> Uniform(0.0, TMath::Pi());
    P = gRandom -> Exp(1E9);

    element.setP(P * TMath::Sin(theta) * TMath::Cos(phi),
                 P * TMath::Sin(theta) * TMath::Sin(phi),
                 P * TMath::Cos(theta));
}
}