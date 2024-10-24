#include "Particle.hpp"
#include "ParticleType.hpp"
#include "ResonanceType.hpp"

static constexpr int N = 130;  // constexpr implies inline so it can be defined
                               // in multiple files for clarity purposes

int checkEmptySlot(std::array<Particle, N>& eventParticles) {
  for (int i{100}; i < N; ++i) {
    if (eventParticles[i].getIndex() == -1)
      ;
    return i;
  }

  std::cout << "Maximum capacity reached. Cannot compute. \n";

  return -1;  // voluntarily return invalid element
}

int main() {
  Particle::AddParticleType("pi+", 0.13957, 1);        // index 0
  Particle::AddParticleType("pi-", 0.13957, -1);       // index 1
  Particle::AddParticleType("K+", 0.49367, 1);         // index 2
  Particle::AddParticleType("K-", 0.49367, -1);        // index 3
  Particle::AddParticleType("P+", 0.93827, 1);         // index 4
  Particle::AddParticleType("P-", 0.93827, -1);        // index 5
  Particle::AddParticleType("K*", 0.89166, 0, 0.050);  // index 6

  std::array<Particle, N> eventParticles{};

  int firstEmptySlot{};  // used in the for loop below (j) to indicate the first
                         // empty slot

  double phi{};
  double theta{};
  double P{};

  double rndm{};  // used below to decide which type of particles is generated

  gRandom->SetSeed();

  for (int i{}; i < 1E5; i++) {
    for (int j{}; j < 100; ++j) {
      phi = gRandom->Uniform(0.0, 2 * TMath::Pi());
      theta = gRandom->Uniform(0.0, TMath::Pi());
      P = gRandom->Exp(1);

      eventParticles[j].setP(P * TMath::Sin(theta) * TMath::Cos(phi),
                             P * TMath::Sin(theta) * TMath::Sin(phi),
                             P * TMath::Cos(theta));

      rndm = gRandom->Uniform(0., 1.);

      if (rndm <= 0.4) {
        eventParticles[j].setParticle(0);
      } else if (rndm > 0.4 && rndm <= 0.8) {
        eventParticles[j].setParticle(1);
      } else if (rndm > 0.8 && rndm <= 0.85) {
        eventParticles[j].setParticle(2);
      } else if (rndm > 0.85 && rndm <= 0.9) {
        eventParticles[j].setParticle(3);
      } else if (rndm > 0.9 && rndm <= 0.945) {
        eventParticles[j].setParticle(4);
      } else if (rndm > 0.945 && rndm <= 0.99) {
        eventParticles[j].setParticle(5);
      } else {
        if (rndm <= 0.5) {
          eventParticles[j].setParticle(6);

          firstEmptySlot = checkEmptySlot(eventParticles);

          eventParticles[firstEmptySlot].setParticle(
              0);  // sets the first empty slot to pi+
          eventParticles[firstEmptySlot + 1].setParticle(
              3);  // sets the first empty slot to K- (the one after the above
                   // pi+)

          eventParticles[j].Decay2body(
              eventParticles[firstEmptySlot],  // passes the above pi+ by
                                               // reference
              eventParticles[firstEmptySlot +
                             1]);  // passes the above K- by reference
        } else {
          eventParticles[j].setParticle(6);

          firstEmptySlot = checkEmptySlot(eventParticles);

          eventParticles[firstEmptySlot].setParticle(
              1);  // sets the first empty slot to pi-
          eventParticles[firstEmptySlot + 1].setParticle(
              2);  // sets the first empty slot to K+ (the one after the above
                   // pi-)

          eventParticles[j].Decay2body(
              eventParticles[firstEmptySlot],  // passes the above pi- by
                                               // reference
              eventParticles[firstEmptySlot +
                             1]);  // passes the above K+ by reference
        }
      }
    }
  }
}
