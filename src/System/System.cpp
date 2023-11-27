#include "System.hpp"

namespace NBodyEnv {
void System::addParticle(Particle particle) {
  _systemParticles.push_back(particle);
}

const Particle &System::getParticle(int index) const {
  return _systemParticles[index];
}

void System::compute() {
  for (auto iter = _systemParticles.begin(); iter != _systemParticles.end();
       iter++) {
    for (auto secIter = iter + 1; secIter != _systemParticles.end();
         secIter++) {
      // Compute new force
      iter->computeForce(*secIter, _func);

      // Update position
      iter->updatePos(_deltaTime);
      secIter->updatePos(_deltaTime);

      // Update velocity
      iter->updateVel(_deltaTime);
      secIter->updateVel(_deltaTime);
    }
  }
}
} // namespace NBodyEnv