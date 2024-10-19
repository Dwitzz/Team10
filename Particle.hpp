#include <array>
#include <vector>

#include "ResonanceType.hpp"

#ifndef PARTICLE_H
#define PARTICLE_H

class Particle {
  constexpr static int fMaxNumParticleType = 10;
  inline static std::array<ParticleType*, fMaxNumParticleType> ParticleTable{};
  inline static int fNParticleType{0};

  int fIndex;
  double fPx;
  double fPy;
  double fPz;

  const static int FindParticle(const std::string& particleName);

 public:
  Particle(const std::string& particleName, double Px = 0, double Py = 0,
           double Pz = 0);

  const int getParticle(Particle particle) const;

  static void AddParticleType(const std::string& name, const double mass,
                              const int charge, const double width = 0);

  void setParticle(const int index);
  void setParticle(const std::string&);

  void static setParticleType(const int i, const std::string& name,
                              const double mass, const int charge,
                              const double width = 0);

  static void printTable();

  void printParticle() const;

  double getPx() const;
  double getPy() const;
  double getPz() const;
  double getMass() const;
  double getEnergy() const;
  double getInvMass(Particle& p) const;
  void setP(double Px, double Py, double Pz);

  static void ClearParticleTable(); //use it in tests to try to avoid memory problems
};

double vectorNorm(double x, double y, double z);

#endif
