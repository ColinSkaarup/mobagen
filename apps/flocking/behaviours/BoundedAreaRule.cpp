#include "BoundedAreaRule.h"
#include "imgui.h"
#include <glm/glm.hpp>
#include <algorithm>

glm::vec2 BoundedAreaRule::computeForce(const std::vector<BoidView>& neighborhood, const BoidView& boid) {
  glm::vec2 force(0.f);
  ImVec2 displaySize = ImGui::GetIO().DisplaySize;
  // desiredDistance is the distance from the borders that the boids should try to maintain. 

  // begin solution

  float tempForce = 0.0f;

  const float width = displaySize.x;
  const float height = displaySize.y;

  const glm::vec2 worldBorder(width, height);
  const glm::vec2 zeroVec(0.0f);

  if (boid.position.x > worldBorder.x - (float)desiredDistance) {
    tempForce = (float)desiredDistance / abs(boid.position.x - worldBorder.x);
  }

  else if (boid.position.x < zeroVec.x + (float)desiredDistance) {
    tempForce = (float)desiredDistance / abs(boid.position.x - zeroVec.x);
  }

  else if (boid.position.y > worldBorder.y - (float)desiredDistance) {
    tempForce = (float)desiredDistance / abs(boid.position.y - worldBorder.y);
  }

  else if (boid.position.y < zeroVec.y + (float)desiredDistance) {
    tempForce = (float)desiredDistance / abs(boid.position.y - zeroVec.y);
  }

  force += /*dir **/ tempForce;
  // end solution

  return force;
}

bool BoundedAreaRule::drawImguiRuleExtra() {
  ImVec2 displaySize = ImGui::GetIO().DisplaySize;
  float widthWindows = displaySize.x > 0.f ? displaySize.x : 1280.f;
  float heightWindows = displaySize.y > 0.f ? displaySize.y : 800.f;
  bool valueHasChanged = false;
  int minHeightWidth = static_cast<int>(std::min(widthWindows, heightWindows));

  if (ImGui::SliderInt("Desired Distance From Borders", &desiredDistance, 0, minHeightWidth / 3, "%i")) {
    valueHasChanged = true;
  }
  return valueHasChanged;
}

void BoundedAreaRule::drawWorldOverlay(ImDrawList* dl) const {
  ImVec2 displaySize = ImGui::GetIO().DisplaySize;
  float w = displaySize.x > 0.f ? displaySize.x : 1280.f;
  float h = displaySize.y > 0.f ? displaySize.y : 800.f;
  float d = static_cast<float>(desiredDistance);
  ImU32 col = IM_COL32(128, 128, 128, 200);

  dl->AddLine({d, d}, {w - d, d}, col);
  dl->AddLine({w - d, d}, {w - d, h - d}, col);
  dl->AddLine({w - d, h - d}, {d, h - d}, col);
  dl->AddLine({d, h - d}, {d, d}, col);
}
