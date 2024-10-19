
#include "Particle.hpp"

#include <algorithm>
#include <cmath>

const inline static std::vector<std::string> nameList{"pi+", "pi-", "K+", "K-",
                                                      "P+",  "P-",  "K*"};

const int Particle::FindParticle(const std::string& particleName) {
  int index{};

  for (int i{0}; i < fNParticleType; i++) {
    if (ParticleTable[i]->GetfName() == particleName) {
      index = i;
      return index;
    }

    if (i == fNParticleType) {
      std::cout << "No match for given name: " << particleName << '\n';
      return -1;
    }
  }
}

Particle::Particle(const std::string& particleName, double Px, double Py,
                   double Pz)
    : fIndex(FindParticle(particleName)), fPx(Px), fPy(Py), fPz(Pz) {}

const int Particle::getParticle(Particle particle) const {
  return particle.fIndex;
}

void Particle::setParcticle(const int index) {
  if (index < fNParticleType) {
    fIndex = index;
  } else {
    std::cout << "Indexed particled type has yes to be defined\n";
  }
}

void Particle::setParticle(const std::string& particleName) {
  int index = FindParticle(particleName);
  if (index != -1 &&
      index < fNParticleType) {  // check that the particle type was defined and
                                 // that the index is of an acceptable value
    fIndex = index;
  } else {
    std::cout << "Indexed particled type has yes to be defined\n";
  }
}

void Particle::AddParticleType(const std::string& name, const double mass,
                               const int charge, const double width) {
  if (fNParticleType >= 7) {
    std::cout << "Maximum number of particles reached. Cannot define more.\n";
    return;
  }

  if (FindParticle(name) == -1) {
    std::cout << "Now defining " << name << '\n';

    for (int i{}; i < 7; ++i) {
      if (ParticleTable[i]->GetfName().empty()) {
        setParcticleType(i, name, mass, charge, width);
        ++fNParticleType;
        return;
      }
    }

  } else {
    std::cout << "The particle " << name << "has already been defined\n";
  }
}

void Particle::setParcticleType(const int i, const std::string& name,
                                const double mass, const int charge,
                                const double width) {
  if (width == 0) {
    ParticleTable[i] = new ParticleType(name, mass, charge);
  }

  if (width != 0) {
    ParticleTable[i] = new ResonanceType(name, mass, charge, width);
  }
}

void Particle::printTable() {
  for (int i{}; i < fNParticleType; ++i) {
    ParticleTable[i]->Print();
  }
}

void Particle::printParticle() const {
  std::cout << "Particle index: " << fIndex
            << "\tParticle name: " << ParticleTable[fIndex]->GetfName()
            << "\tImpulse vector: ( " << fPx << " , " << fPy << " , " << fPz
            << " )\n";
}

double Particle::getPx() const { return fPx; }
double Particle::getPy() const { return fPy; }
double Particle::getPz() const { return fPz; }
double Particle::getMass() const { return ParticleTable[fIndex]->GetfMass(); }

double Particle::getEnergy() const {
  return std::sqrt(std::pow(getMass(), 2) +
                   std::pow(vectorNorm(fPx, fPy, fPz), 2));
}

double Particle::getInvMass(Particle& other) const {
  return std::sqrt(std::pow(getEnergy() + other.getEnergy(), 2) -
                   std::pow(vectorNorm(fPx - other.getPx(), fPy - other.getPy(),
                                       fPz - other.getPz()),
                            2));
}

double vectorNorm(double x, double y, double z) {
  return std::sqrt(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2));
}

void Particle::setP(double Px, double Py, double Pz) {
  fPx = Px;
  fPy = Py;
  fPz = Pz;
}