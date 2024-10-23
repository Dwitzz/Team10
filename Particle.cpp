
#include "Particle.hpp"

#include <algorithm>
#include <cmath>
#include <cmath>    // for M_PI
#include <cstdlib>  //for RAND_MAX

/* const inline static std::vector<std::string> nameList{"pi+", "pi-", "K+",
"K-","P+",  "P-",  "K*"}; */ // commentato via, non dovrebbe servire piu

int Particle::FindParticle(const std::string& particleName) {
  int index{};

  for (int i{0}; i < fNParticleType; i++) {
    if (ParticleTable[i] && ParticleTable[i]->GetfName() == particleName) {
      index = i;
      return index;
    }
  }

  std::cout << "No match for given name: " << particleName << '\n';
  return -1;
}

Particle::Particle(const std::string& particleName, double Px, double Py,
                   double Pz)
    : fIndex(FindParticle(particleName)), fPx(Px), fPy(Py), fPz(Pz) {}

int Particle::getParticle(Particle particle) const {
  return particle.fIndex;
}

void Particle::setParticle(const int index) {
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
      if (ParticleTable[i] == nullptr || ParticleTable[i]->GetfName().empty()) {
        setParticleType(i, name, mass, charge, width);
        ++fNParticleType;
        return;
      }
    }

  } else {
    std::cout << "The particle " << name << "has already been defined\n";
  }
}

void Particle::setParticleType(const int i, const std::string& name,
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

void Particle::ClearParticleTable() {
  for (int i = 0; i < fNParticleType; ++i) {
    if (ParticleTable[i] != nullptr) {
      delete ParticleTable[i];
      ParticleTable[i] = nullptr;
    }
  }
  fNParticleType = 0;
}

void Particle::Boost(double bx, double by, double bz) {
  double energy = getEnergy();

  // Boost this Lorentz vector
  double b2 = bx * bx + by * by + bz * bz;
  double gamma = 1.0 / sqrt(1.0 - b2);
  double bp = bx * fPx + by * fPy + bz * fPz;
  double gamma2 = b2 > 0 ? (gamma - 1.0) / b2 : 0.0;

  fPx += gamma2 * bp * bx + gamma * bx * energy;
  fPy += gamma2 * bp * by + gamma * by * energy;
  fPz += gamma2 * bp * bz + gamma * bz * energy;
}

int Particle::Decay2body(Particle& dau1, Particle& dau2) const {
  if (getMass() == 0.0) {
    printf("Decayment cannot be preformed if mass is zero\n");
    return 1;
  }

  double massMot = getMass();
  double massDau1 = dau1.getMass();
  double massDau2 = dau2.getMass();

  if (fIndex > -1) {  // add width effect

    // gaussian random numbers

    float x1, x2, w, y1;

    double invnum = 1. / RAND_MAX;
    do {
      x1 = 2.0 * rand() * invnum - 1.0;
      x2 = 2.0 * rand() * invnum - 1.0;
      w = x1 * x1 + x2 * x2;
    } while (w >= 1.0);

    w = sqrt((-2.0 * log(w)) / w);
    y1 = x1 * w;

    massMot += ParticleTable[fIndex]->GetfWidth() * y1;
  }

  if (massMot < massDau1 + massDau2) {
    printf(
        "Decayment cannot be preformed because mass is too low in this "
        "channel\n");
    return 2;
  }

  double pout =
      sqrt(
          (massMot * massMot - (massDau1 + massDau2) * (massDau1 + massDau2)) *
          (massMot * massMot - (massDau1 - massDau2) * (massDau1 - massDau2))) /
      massMot * 0.5;

  double norm = 2 * M_PI / RAND_MAX;

  double phi = rand() * norm;
  double theta = rand() * norm * 0.5 - M_PI / 2.;
  dau1.setP(pout * sin(theta) * cos(phi), pout * sin(theta) * sin(phi),
            pout * cos(theta));
  dau2.setP(-pout * sin(theta) * cos(phi), -pout * sin(theta) * sin(phi),
            -pout * cos(theta));

  double energy = sqrt(fPx * fPx + fPy * fPy + fPz * fPz + massMot * massMot);

  double bx = fPx / energy;
  double by = fPy / energy;
  double bz = fPz / energy;

  dau1.Boost(bx, by, bz);
  dau2.Boost(bx, by, bz);

  return 0;
}