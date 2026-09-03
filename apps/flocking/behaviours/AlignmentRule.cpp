#include "AlignmentRule.h"
#include <glm/glm.hpp>

glm::vec2 AlignmentRule::computeForce(const std::vector<BoidView>& neighborhood, const BoidView& boid) {
  glm::vec2 averageVelocity(0.f);
  // glm::vec2 can be divided by a float, which will divide each component of the vector by that float.

  // begin solution

  if (neighborhood.empty()) {
    return averageVelocity;
  }

  for (const BoidView neighbor : neighborhood) {
    if (glm::distance(boid.position, neighbor.position) <= 0.0001f) {
      continue;
    }
    averageVelocity += neighbor.velocity;
  }

  averageVelocity /= neighborhood.size();

  return averageVelocity;
  // end solution
}
