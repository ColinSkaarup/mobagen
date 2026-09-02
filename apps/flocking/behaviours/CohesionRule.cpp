#include "CohesionRule.h"
#include <glm/glm.hpp>

glm::vec2 CohesionRule::computeForce(const std::vector<BoidView>& neighborhood, const BoidView& boid) {
  glm::vec2 cohesionForce(0.f);

  // glm::length(vec) returns the length of a vector,
  // glm::normalize(vec) returns the normalized vector (length 1) in the same direction as vec.

  // begin solution

  if (neighborhood.size() <= 0) {
    return cohesionForce;
  }

  float force = 0.0f;
  glm::vec2 avgCenter(0.0f);

  for (BoidView neighbor : neighborhood) {
    avgCenter += neighbor.position;
  }

  avgCenter /= neighborhood.size();

  //FIX THIS!!!!!!
  glm::vec2 dir = glm::normalize(boid.position + force);

  cohesionForce += dir * force;
  // end solution

  return cohesionForce;
}
