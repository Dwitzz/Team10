#include <cmath>

#include "Particle.hpp"
#include "ParticleType.hpp"
#include "ResonanceType.hpp"

static constexpr int N = 130;  // constexpr implies inline so it can be defined
                               // in multiple files for clarity purposes

int checkEmptySlot(std::array<Particle, N> &eventParticles) {
  for (int i{100}; i < N; ++i) {
    if (eventParticles[i].getIndex() == -1) return i;
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
  int lastFilledSlot{};
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

  TH1F *h_Invariant_mass_opp_sign_pi_k =
      new TH1F("h_Invariant_mass_opp_sign_pi_k",
               "Invariant mass: same opposite charge pi-k pairs", 100, 0., 2);
  h_Invariant_mass_opp_sign_pi_k->Sumw2();

  TH1F *h_Invariant_mass_same_sign_pi_k =
      new TH1F("h_Invariant_mass_same_sign_pi_k",
               "Invariant mass: same signed charge pi-k pairs", 100, 0., 2);
  h_Invariant_mass_same_sign_pi_k->Sumw2();

  TH1F *h_Benchmark =
      new TH1F("h_Benchmark", "Invariant mass: K* decay pairs", 100, 0., 2.);
 // h_Benchmark->Sumw2();

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
        //rndm = gRandom->Uniform(0., 1.);

        if (rndm <= 0.995) {
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

          h_Benchmark->Fill(eventParticles[firstEmptySlot].getInvMass(
              eventParticles[firstEmptySlot + 1]));
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
          h_Benchmark->Fill(eventParticles[firstEmptySlot].getInvMass(
              eventParticles[firstEmptySlot + 1]));
        }
      }

      h_Energy->Fill(eventParticles[j].getEnergy());
      h_Impulse->Fill(P);
      h_Particle_Type->Fill(eventParticles[j].getIndex());
      h_Phi_Theta->Fill(phi, theta);
      h_Trasverse_Impulse->Fill(
          std::sqrt((std::pow((eventParticles[j].getPx()), 2.) -
                     std::pow((eventParticles[j].getPy()), 2.))));
    }
    if (firstEmptySlot == -1) {
      lastFilledSlot = 99;
    } else {
      lastFilledSlot = firstEmptySlot + 1;
    }

    // fills h_Invariant_mass_opp_sign
    for (int k{}; k < lastFilledSlot;
         ++k)  // lastFilledSlot is the last defined particle in the array
    {
      for (int a{k + 1}; a <=  lastFilledSlot; ++a) {
        if (eventParticles[a].getIndex() == 6) {
        }
        // fills h_Invariant_mass_opp_sign
        else if (eventParticles[a].getCharge() !=
                 eventParticles[k].getCharge()) {
          h_Invariant_mass_opp_sign->Fill(
              eventParticles[k].getInvMass(eventParticles[a]));
        }
        // fills h_Invariant_mass_same_sign
        else if (eventParticles[a].getCharge() ==
                 eventParticles[k].getCharge()) {
          h_Invariant_mass_same_sign->Fill(
              eventParticles[k].getInvMass(eventParticles[a]));
        }

        if (eventParticles[k].getIndex() == 0 ||
            eventParticles[k].getIndex() == 1) {
          // fills h_Invariant_mass_opp_sign_pi_k
          if ((eventParticles[a].getIndex() == 2 ||
               eventParticles[a].getIndex() == 3) &&
              eventParticles[a].getCharge() != eventParticles[k].getCharge()) {
            h_Invariant_mass_opp_sign_pi_k->Fill(
                eventParticles[k].getInvMass(eventParticles[a]));
          }
          // fills h_Invariant_mass_same_sign_pi_k
          if ((eventParticles[a].getIndex() == 2 ||
               eventParticles[a].getIndex() == 3) &&
              eventParticles[a].getCharge() == eventParticles[k].getCharge()) {
            h_Invariant_mass_same_sign_pi_k->Fill(
                eventParticles[k].getInvMass(eventParticles[a]));
          }
        }
      }
    }

    //std::cout << lastFilledSlot << '\n';
    if (firstEmptySlot != -1) {
      for (int i{100}; i <= lastFilledSlot; ++i) {
        eventParticles[i].setNeutral();
        //std::cout << eventParticles[i].getIndex() << '\n';
      }
    }
    firstEmptySlot = -1;
  }

  TCanvas *c1 = new TCanvas("c1", "2x2 Canvas", 800, 800);
  c1->Divide(2, 2);
  c1->cd(1);
  h_Particle_Type->Draw("APE");
  c1->cd(2);
  h_Phi_Theta->Draw("APE");
  c1->cd(3);
  h_Impulse->Draw("APE");
  c1->cd(4);
  h_Trasverse_Impulse->Draw("APE");

  c1->Update();

  TCanvas *c2 = new TCanvas("c2", "2x2 Canvas", 800, 800);
  c2->Divide(2, 2);
  c2->cd(1);
  h_Invariant_mass_same_sign_pi_k->Draw("APE");
  c2->cd(2);
  h_Invariant_mass_opp_sign->Draw("APE");
  c2->cd(3);
  h_Invariant_mass_same_sign->Draw("APE");
  c2->cd(4);
  h_Invariant_mass_opp_sign_pi_k->Draw("APE");
  c2->Update();

  h_Energy->Draw("APE");

  TCanvas *c3 = new TCanvas("c3", "2x2 Canvas", 800, 800);
  c3->Divide(1, 1);
  h_Energy->Draw("APE");
  c3->cd(1);

  h_Benchmark->Draw("H");
  c3->cd(2);
  // h_Benchmark->Draw("E,P,SAME");

  Particle::ClearParticleTable();
}
