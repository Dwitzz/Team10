#include <cmath>

#include "Particle.hpp"
#include "ParticleType.hpp"
#include "ResonanceType.hpp"

static constexpr int N = 130;  // constexpr implies inline so it can be defined
                               // in multiple files for clarity purposes

int checkEmptySlot(std::array<Particle, N> &eventParticles) {
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

  TH1F *h_Particle_Type =
      new TH1F("h_Particle_Type", "Particle Type", 7, 0., 7.);
  h_Particle_Type->Sumw2();

  TH2F *h_Phi_Theta =
      new TH2F("h_Phi_Theta", "Azimuthal(phi)_x & polar(theta)_y angles", 100,
               0., 2 * TMath::Pi(), 200, 0., TMath::Pi());
  h_Phi_Theta->Sumw2();

  TH1F *h_Impulse = new TH1F("h_Impulse", "Impulse", 100, 0., 7);
  h_Impulse->Sumw2();

  TH1F *h_Trasverse_Impulse =
      new TH1F("h_Trasverse_Impulse", "Trasverse Impulse", 100, 0., 7.);
  h_Trasverse_Impulse->Sumw2();

  TH1F *h_Energy = new TH1F("h_Energy", "Energy", 100, 0., 2.);
  h_Energy->Sumw2();

  TH1F *h_Invariant_mass_opp_sign =
      new TH1F("h_Invariant_mass_opp_sign",
               "Invariant mass: opposite signed particles", 100, 0., 2);
  h_Invariant_mass_opp_sign->Sumw2();

  TH1F *h_Invariant_mass_same_sign =
      new TH1F("h_Invariant_mass_same_sign",
               "Invariant mass: same signed particles", 100, 0., 2);
  h_Invariant_mass_same_sign->Sumw2();

  TH1F *h_Invariant_mass_opp_sign_decay =
      new TH1F("h_Invariant_mass_opp_sign_decay",
               "Invariant mass: opposite signed decayed particles", 100, 0., 2);
  h_Invariant_mass_opp_sign_decay->Sumw2();

  TH1F *h_Invariant_mass_same_sign_decay =
      new TH1F("h_Invariant_mass_same_sign_decay",
               "Invariant mass: same signed decayed particles", 100, 0., 2);
  h_Invariant_mass_same_sign_decay->Sumw2();

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
        eventParticles[j].setParticle(6);

        firstEmptySlot = checkEmptySlot(eventParticles);

        if (rndm <= 0.5) {
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

      h_Impulse->Fill(P);
      h_Particle_Type->Fill(eventParticles[j].getIndex());
      h_Phi_Theta->Fill(phi, theta);
      h_Trasverse_Impulse->Fill(std::sqrt(
          (std::pow(P, 2.) - std::pow((eventParticles[j].getPz()), 2.))));
    }

    // fills h_Invariant_mass_opp_sign
    for (int k{}; k <= firstEmptySlot + 1;
         ++k)  // firstEmptySlot + 1 is the last defined particle in the array
    {
      for (int a{k + 1}; a <= firstEmptySlot + 1; ++a) {
        if (eventParticles[a].getIndex() == 6) {
        } else if (eventParticles[a].getCharge() !=
                   eventParticles[k].getCharge()) {
          h_Invariant_mass_opp_sign->Fill(
              eventParticles[k].getInvMass(eventParticles[a]));
        }
      }
    }

    // fills h_Invariant_mass_same_sign
    for (int k{}; k <= firstEmptySlot + 1;
         ++k)  // firstEmptySlot + 1 is the last defined particle in the array
    {
      for (int a{k + 1}; a <= firstEmptySlot + 1; ++a) {
        if (eventParticles[a].getIndex() == 6) {
        } else if (eventParticles[a].getCharge() ==
                   eventParticles[k].getCharge()) {
          h_Invariant_mass_same_sign->Fill(
              eventParticles[k].getInvMass(eventParticles[a]));
        }
      }
    }

    // fills h_Invariant_mass_opp_sign_decay
    for (int k{}; k <= firstEmptySlot + 1;
         ++k)  // firstEmptySlot + 1 is the last defined particle in the array
    {
      if (eventParticles[k].getIndex() == 0 ||
          eventParticles[k].getIndex() == 1) {
        for (int a{k + 1}; a <= firstEmptySlot + 1; ++a) {
          // check that both the index numbers and the charge pairing are the
          // desired ones
          if ((eventParticles[a].getIndex() == 2 ||
               eventParticles[a].getIndex() == 3) &&
              eventParticles[a].getCharge() != eventParticles[k].getCharge()) {
            h_Invariant_mass_opp_sign_decay->Fill(
                eventParticles[k].getInvMass(eventParticles[a]));
          }
        }
      }
    }

    // fills h_Invariant_mass_same_sign_decay
    for (int k{}; k <= firstEmptySlot + 1;
         ++k)  // firstEmptySlot + 1 is the last defined particle in the array
    {
      if (eventParticles[k].getIndex() == 0 ||
          eventParticles[k].getIndex() == 1) {
        for (int a{k + 1}; a <= firstEmptySlot + 1; ++a) {
          // check that both the index numbers and the charge pairing are the
          // desired ones
          if ((eventParticles[a].getIndex() == 2 ||
               eventParticles[a].getIndex() == 3) &&
              eventParticles[a].getCharge() == eventParticles[k].getCharge()) {
            h_Invariant_mass_same_sign_decay->Fill(
                eventParticles[k].getInvMass(eventParticles[a]));
          }
        }
      }
    }
  }
}
