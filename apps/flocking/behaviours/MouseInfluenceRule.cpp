#include "MouseInfluenceRule.h"
#include "imgui.h"

glm::vec2 MouseInfluenceRule::computeForce(const std::vector<BoidView>& neighborhood, const BoidView& boid) {
  glm::vec2 force(0.f);

  // ImGui::IsMouseDown(ImGuiMouseButton_Left) returns true if the left mouse button is currently pressed.
  // ImGui::GetIO().MousePos returns the current mouse position as an ImVec2.
  // glm::length(vec) returns the length of a vector

  // begin solution

  if (ImGui::IsMouseDown(ImGuiMouseButton_Left)) {
    const ImVec2 mousePos = ImGui::GetIO().MousePos;
    const glm::vec2 mouseVec = {mousePos.x, mousePos.y};
    float mouseDist = glm::distance(boid.position, mouseVec);

    if (mouseDist <= 0.1f)
      return force;

    float mouseForce = mouseInfluenceRadius / mouseDist;

    glm::vec2 dir = {0.0f, 0.0f};
    if (!isRepulsive) {
      dir = glm::normalize(mouseVec - boid.position);
    }
    else {
      dir = glm::normalize(boid.position - mouseVec);
    }

    force += clamp(dir * mouseForce, -50.0f, 50.0f);
  }

  // end solution

  return force;
}

bool MouseInfluenceRule::drawImguiRuleExtra() {
  bool valueHasChanged = false;

  ImGui::DragFloat("Mouse Effect Radius", &mouseInfluenceRadius, 1, 0);

  if (ImGui::RadioButton("Attractive", !isRepulsive)) {
    isRepulsive = false;
    valueHasChanged = true;
  }
  ImGui::SameLine();
  if (ImGui::RadioButton("Repulsive", isRepulsive)) {
    isRepulsive = true;
    valueHasChanged = true;
  }

  return valueHasChanged;
}
