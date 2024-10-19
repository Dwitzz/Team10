#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "Particle.hpp" 
#include "doctest.h"

TEST_SUITE("Particle") {

  TEST_CASE("FindParticle (indirectly)") { //you cannot test FindParticle directly as it is private (would have to make it protected or make a friend class)
    Particle::ClearParticleTable();
    Particle::AddParticleType("electron", 0.511, -1);
    Particle::AddParticleType("proton", 938.27, 1);
    
    Particle electron("electron");
    Particle proton("proton");

    CHECK(electron.getParticle(electron) == 0);
    CHECK(proton.getParticle(proton) == 1);
}

  TEST_CASE("ParticleCreation") {
    Particle::ClearParticleTable();
    Particle::AddParticleType("muon", 105.66, -1);
    Particle muon("muon", 1., 2., 3.);

    CHECK(muon.getParticle(muon) ==
          0);  //should be first particle type
    CHECK(muon.getPx() == 1.);
    CHECK(muon.getPy() == 2.);
    CHECK(muon.getPz() == 3.);
  }

  TEST_CASE("EnergyCalculation") {
    Particle::ClearParticleTable();
    Particle::AddParticleType("neutron", 939.57, 0);
    Particle neutron("neutron", 3., 4., 0.);

    double expectedEnergy =
        std::sqrt(std::pow(939.57, 2) + std::pow(vectorNorm(3.0, 4.0, 0.0), 2)); //brutto calcolo spero vada bene
    CHECK(neutron.getEnergy() == doctest::Approx(expectedEnergy));
  }

  TEST_CASE("InvariantMassCalculation") {
    Particle::ClearParticleTable();
    Particle::AddParticleType("electron", 0.511, -1);
    Particle::AddParticleType("positron", 0.511, 1);

    Particle electron("electron", 1., 0., 0.);
    Particle positron("positron", -1., 0., 0.);

    double expectedInvMass =
        std::sqrt(std::pow(electron.getEnergy() + positron.getEnergy(), 2) -
                  std::pow(vectorNorm(2.0, 0.0, 0.0), 2)); //brutto calcolo spero vada bene
    CHECK(electron.getInvMass(positron) == doctest::Approx(expectedInvMass));
  }

  TEST_CASE("SetMomentum") {
    Particle::ClearParticleTable();
    Particle::AddParticleType("kaon", 493.67, 1);
    Particle kaon("kaon", 0., 0., 0.);

    kaon.setP(1., 2., 3.);
    CHECK(kaon.getPx() == 1.);
    CHECK(kaon.getPy() == 2.);
    CHECK(kaon.getPz() == 3.);
  }
}
