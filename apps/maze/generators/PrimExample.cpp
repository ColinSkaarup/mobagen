#include "PrimExample.h"
#include "../World.h"
#include "Random.h"

bool PrimExample::Step(World* w) {
  // todo: code this

  if (toBeVisited.empty()) { return false; }

  Point2D current = toBeVisited.back();

  for (auto point : getVisitables(w, current)) {
    toBeVisited.push_back(point);
  }

  return true;
}
void PrimExample::Clear(World* world) {
  toBeVisited.clear();
  visited.clear();

  visited.assign(world->GetWidth() * world->GetHeight(), false);
  initialized = false;
  toBeVisited.push_back({0, 0});
}

std::vector<Point2D> PrimExample::getVisitables(World* w, const Point2D& p) {
  std::vector<Point2D> visitables;
  auto clearColor = Color32(169.0f / 255.0f, 169.0f / 255.0f, 169.0f / 255.0f, 1.0f);  // dark gray
  std::vector<Point2D> deltas = {Point2D(0, -1), Point2D(0, 1), Point2D(-1, 0), Point2D(1, 0)};
  // todo: code this

  for (uint8_t i = 0; i < 4; i++) {
    Point2D potentialPoint = p + deltas[i];

    if (potentialPoint.x >= 0 && potentialPoint.x < w->GetWidth()
      && potentialPoint.y >= 0 && potentialPoint.y < w->GetHeight()
      && !visited[CoordsToIndex(w, potentialPoint.x, potentialPoint.y)]) {
      visitables.push_back(potentialPoint);
      }
  }

  return visitables;
}

std::vector<Point2D> PrimExample::getVisitedNeighbors(World* w, const Point2D& p) {
  std::vector<Point2D> deltas = {Point2D(0, -1), Point2D(0, 1), Point2D(-1, 0), Point2D(1, 0)};  // N, S, W, E
  std::vector<Point2D> neighbors;

  // todo: code this

  for (uint8_t i = 0; i < 4; i++) {
    Point2D potentialPoint = p + deltas[i];

    if (potentialPoint.x >= 0 && potentialPoint.x < w->GetWidth()
      && potentialPoint.y >= 0 && potentialPoint.y < w->GetHeight()
      && visited[CoordsToIndex(w, potentialPoint.x, potentialPoint.y)]) {
      neighbors.push_back(potentialPoint);
      }
  }

  return neighbors;
}
